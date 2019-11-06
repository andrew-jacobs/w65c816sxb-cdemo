/*============================================================================*
 * __        ____  ____   ____ ___  _  __  ______  ______                     *
 * \ \      / / /_| ___| / ___( _ )/ |/ /_/ ___\ \/ / __ )                    *
 *  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \___ \\  /|  _ \                    *
 *   \ V  V /| (_) |__) | |__| (_) | | (_) |__) /  \| |_) |                   *
 *    \_/\_/  \___/____/ \____\___/|_|\___/____/_/\_\____/                    *                                       
 *                                                                            *
 * W65C816SXB Developer Board Definitions                                     *
 *----------------------------------------------------------------------------*
 * Copyright (C),2019 Andrew Jacobs                                           *
 * All rights reserved.                                                       *
 *                                                                            *
 * This work is made available under the terms of the Creative Commons        *
 * Attribution-NonCommercial-ShareAlike 4.0 International license. Open the   *
 * following URL to see the details.                                          *
 *                                                                            *
 * http://creativecommons.org/licenses/by-nc-sa/4.0/                          *
 *                                                                            *
 *============================================================================*
 * Notes:                                                                     *
 *                                                                            *
 * The user VIA is used to generate a regular 1KHz interrupt to update the    *
 * millisecond counter and T2 in system VIA is used to generate interrupts    *
 * to drive ACIA character transmission (as the transmit buffer empty bit is  *
 * broken).                                                                   * 
 *----------------------------------------------------------------------------*/

#include "w65c816sxb.h"

#include <stdio.h>

#define BAUD_RATE       9600

#define MSB(XX)         (((XX) >> 8) & 0xff)
#define LSB(XX)         (((XX) >> 0) & 0xff)

#define MSEC_COUNT      (FCLK / 1000)
#define BAUD_COUNT      (FCLK / (BAUD_RATE / 11))

#if MSEC_COUNT & 0xffff0000ul
#error "MSEC count does not fit in 16-bits"
#endif

#if BAUD_COUNT & 0xffff0000ul
#error "BAUD count does not fit in 16-bits"
#endif

/* A simple FIFO queue */
typedef struct {
    uint8_t             head;
    uint8_t             tail;
    uint8_t             data [64];
} fifo_t;

/* FIFOs for serial I/O */
static volatile fifo_t  rx;
static volatile fifo_t  tx;

/* An incrementing counter */
static volatile uint32_t ticks;

/* Initialise the SXB board hardware */
void initialise (void)
{
    /* Set T1 for 1mS continuous */
    VIA_ACR (USR_VIA) &= ~VIA_ACR_T1C_MASK;
    VIA_ACR (USR_VIA) |= VIA_ACR_T1C_CONTINUOUS;
    VIA_IER (USR_VIA) = VIA_IER_SET_MASK | VIA_IER_T1_MASK;
    VIA_T1C (USR_VIA) = MSEC_COUNT;

    /* Set T2 for serial delay */
    VIA_ACR (SYS_VIA) &= ~VIA_ACR_T2C_MASK;
    VIA_ACR (SYS_VIA) |= VIA_ACR_T2C_TIMED_INTERRUPT;
    VIA_IER (SYS_VIA) = VIA_IER_SET_MASK | VIA_IER_T2_MASK;
    VIA_T2C (SYS_VIA) = BAUD_COUNT;

    /* Set ACIA for 9600 8-N-1 */
    ACIA_CTL (ACIA) = ACIA_CTL_SBN_1 | ACIA_CTL_WL_8 | ACIA_CTL_RCS_BAUD | ACIA_CTL_SBR_9600;
    ACIA_CMD (ACIA) = ACIA_CMD_PMC_SPACE | ACIA_CMD_PME_DISABLE | ACIA_CMD_REM_NORMAL
                    | ACIA_CMD_TIC_DISABLE | ACIA_CMD_IRD_ENABLE | ACIA_CMD_DTR_ENABLE;

    /* Clear the receive buffer */
    ACIA_BUF (ACIA);

    enableInterrupts ();
}

/* Return the timer count */
uint32_t millis (void)
{
    uint32_t        now;

    suspendInterrupts ();
    now = ticks;
    restoreInterrupts ();

    return (now);
}

/* A timed delay */
void delay (uint32_t msec)
{
    uint32_t        start = millis ();

    while ((millis () - start) < msec) /* Busy Wait */ ;
}

/* The Native IRQ handler. */
void interrupt IRQHandler (void)
{
    uint8_t         next;

    /* Handle User VIA interrupts */
    if (VIA_IFR (USR_VIA) & VIA_IFR_IRQ_MASK) {
        /* Time to update the counter? */
        if (VIA_IFR (USR_VIA) & VIA_IFR_T1_MASK) {
            next = VIA_T1CL (USR_VIA);
            ++ticks;
        }
    }

    /* Handle System VIA interrupts */
    if (VIA_IFR (SYS_VIA) & VIA_IFR_IRQ_MASK) {
        /* Time to send another character? */
        if (VIA_IFR (SYS_VIA) & VIA_IFR_T2_MASK) {
            if (tx.head != tx.tail) {
                ACIA_BUF (ACIA) = tx.data [tx.head];
                tx.head = (tx.head + 1) % sizeof (tx.data);
            }
            VIA_T2C (SYS_VIA) = BAUD_COUNT;
        }
    }

    /* Handle ACIA receive interrupts */
    if (ACIA_SR (ACIA) & ACIA_SR_IRQ_MASK) {
        /* Has a character been recieved? */
        if (ACIA_SR (ACIA) & ACIA_SR_RDRF_MASK) {
            rx.data [rx.tail] = ACIA_BUF (ACIA);
            next = (rx.tail + 1) % sizeof (rx.data);
            if (next != rx.head) rx.tail = next;
        }
    }
}

/* Put a character in the ACIA transmit FIFO. Wait for a space if necessary */
int16_t aciaTx (uint8_t ch)
{
    uint8_t         next;

    tx.data [tx.tail] = ch;
    next = (tx.tail + 1) % sizeof (tx.data);

    while (next == tx.head) /* FIFO is full */ ;

    tx.tail = next;
    return (0);
}

/* Reads the next character from the input fifo */
int16_t aciaRx (int16_t wait)
{
    uint8_t         ch;

    while (rx.head == rx.tail)
        if (!wait) return (-1);

    ch = rx.data [rx.head];
    rx.head = (rx.head + 1) % sizeof (rx.data);
    return (ch);
}