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

uint8_t             heap_start [8192];
uint8_t             heap_end [1];

uint32_t         ticks;

void initialise (void)
{
    /* Set T1 for 1mS continuous */
    USR_VIA -> acr.bits.t1c = VIA_T1C_CONTINUOUS;
    USR_VIA -> acr.bits.t2c = VIA_T2C_TIMED_INTERRUPT;
    USR_VIA -> ier.data = VIA_IER_SET | VIA_IER_T1 | VIA_IER_T2;
    USR_VIA -> t1cl = LSB (MSEC_COUNT);
    USR_VIA -> t1ch = MSB (MSEC_COUNT);
    USR_VIA -> t2cl = LSB (BAUD_COUNT);
    USR_VIA -> t2ch = MSB (BAUD_COUNT);

    /* Set T2 for serial delay */

    /* Set ACIA for 9600 8-N-1 */
    ACIA -> ctl.bits.sbr = ACIA_SBR_9600;

   /* ACIA_SBR (ACIA) = ACIA_SBR_9600; */
    ACIA_RCS (ACIA) = ACIA_RCS_BAUD;
    ACIA_WL  (ACIA) = ACIA_WL_8;
    ACIA_SBN (ACIA) = ACIA_SBN_1;

    ACIA_DTR (ACIA) = ACIA_DTR_ENABLE;
    ACIA_IRD (ACIA) = ACIA_IRD_ENABLE;
    ACIA_TIC (ACIA) = ACIA_TIC_DISABLE;
    ACIA_REM (ACIA) = ACIA_REM_NORMAL;
    ACIA_PME (ACIA) = ACIA_PME_DISABLE;
    ACIA_PMC (ACIA) = ACIA_PMC_SPACE;

    /* Clear the receive buffer */
    ACIA_RXD (ACIA);

    enableInterrupts ();
}


void interrupt IRQHandler (void)
{
    uint8_t         next;

    /* Handle User VIA interrupts */
    if (USR_VIA -> ifr.bits.irq) {
        if (USR_VIA -> ifr.bits.t1) {
            next = USR_VIA -> t1cl;
            ++ticks;
        }

        if (USR_VIA -> ifr.bits.t2) {
            if (tx.head != tx.tail) {
                ACIA -> buf = tx.data [tx.head];
                tx.head = (tx.head + 1) % sizeof (tx.data);
            }

            USR_VIA -> t2cl = LSB (BAUD_COUNT);
            USR_VIA -> t2ch = MSB (BAUD_COUNT);
        }
    }

    /* Handle ACIA receive interrupts */
    if (ACIA_IRQ (ACIA)) {
        rx.data [rx.tail] = ACIA -> buf;
        next = (rx.tail + 1) % sizeof (rx.data);
        if (next != rx.head) rx.tail = next;
    }
}

void aciaTx (uint8_t ch)
{
    uint8_t         next;

    tx.data [tx.tail] = ch;
    next = (tx.tail + 1) % sizeof (tx.data);

    while (next == tx.head) ;
    tx.tail = next;
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

/*----------------------------------------------------------------------------*/

int putchar (int ch)
{
    aciaTx (ch);
    return (0);
}

int puts (const char *pFormat)
{
    uint8_t ch;

    while (ch = *pFormat) {
        aciaTx (ch);
        ++pFormat;
    }
    return (0);
}

int printf (const char *pFormat, ...)
{
    uint8_t ch;

    while (ch = *pFormat) {
        aciaTx (ch);
        ++pFormat;
    }
    return (0);
}

