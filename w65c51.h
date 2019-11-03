/*============================================================================*
 * __        ____  ____   ____ ____  _                                        *
 * \ \      / / /_| ___| / ___| ___|/ |                                       *
 *  \ \ /\ / / '_ \___ \| |   |___ \| |                                       *
 *   \ V  V /| (_) |__) | |___ ___) | |                                       *
 *    \_/\_/  \___/____/ \____|____/|_|                                       *
 *                                                                            *
 * Asynchronous Communications Interface Adapter (ACIA) Definitions           *
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
 * The baud rate enumerations assume that the normal 1.8432 MHz oscillator    *
 * crystal is in use.                                                         *
 *----------------------------------------------------------------------------*/

#ifndef _W65C51_H
#define _W65C51_H

#include <inttypes.h>

typedef enum {
    ACIA_SBR_16X        = 0,
    ACIA_SBR_50         = 1,
    ACIA_SBR_75         = 2,
    ACIA_SBR_110        = 3,
    ACIA_SBR_134        = 4,
    ACIA_SBR_150        = 5,
    ACIA_SBR_300        = 6,
    ACIA_SBR_600        = 7,
    ACIA_SBR_1200       = 8,
    ACIA_SBR_1800       = 9,
    ACIA_SBR_2400       = 10,
    ACIA_SBR_3600       = 11,
    ACIA_SBR_4800       = 12,
    ACIA_SBR_7200       = 13,
    ACIA_SBR_9600       = 14,
    ACIA_SBR_19200      = 15
} acia_sbr_t;

typedef enum {
    ACIA_RCS_EXT        = 0,
    ACIA_RCS_BAUD       = 1
} acia_rcs_t;

typedef enum {
    ACIA_WL_8           = 0,
    ACIA_WL_7           = 1,
    ACIA_WL_6           = 2,
    ACIA_WL_5           = 3
} acia_wl_t;

typedef enum {
    ACIA_SBN_1          = 0,
    ACIA_SBN_1_5        = 1,          /* Only when WL = 5 */
    ACIA_SBN_2          = 1
} acia_sbn_t;

typedef enum {
    ACIA_DTR_DISABLE    = 0,
    ACIA_DTR_ENABLE     = 1
} acia_dtr_t;

typedef enum {
    ACIA_IRD_ENABLE     = 0,
    ACIA_IRD_DISABLE    = 1
} acia_ird_t;

typedef enum {
    ACIA_TIC_RTS        = 0,
    ACIA_TIC_ENABLE     = 1,
    ACIA_TIC_DISABLE    = 2,
    ACIA_TIC_BRK        = 3
} acia_tic_t;

typedef enum {
    ACIA_REM_NORMAL     = 0,
    ACIA_REM_ECHO       = 1
} acia_rem_t;

typedef enum {
    ACIA_PME_DISABLE    = 0,
    ACIA_PME_ENABLE     = 1
} acia_pme_t;

typedef enum {
    ACIA_PMC_ODD        = 0,
    ACIA_PMC_EVEN       = 1,
    ACIA_PMC_MARK       = 2,
    ACIA_PMC_SPACE      = 3
} acia_pmc_t;

typedef union {
    struct {
        uint8_t             pe   : 1;   /* Parity error */
        uint8_t             fe   : 1;   /* Framing error */
        uint8_t             ovrn : 1;   /* Overrun */
        uint8_t             rdrf : 1;   /* Receive data regsister full */
        uint8_t             tdre : 1;   /* Transmit data register empty */
        uint8_t             dcdb : 1;   /* /Data carrier detect */
        uint8_t             dsrb : 1;   /* /Data set ready */
        uint8_t             irq  : 1;   /* Interrupt */
    }                   bits;
    uint8_t             data;
} acia_sr_t;

typedef union {
    struct {
        acia_dtr_t          dtr  : 1;   /* Data Terminal Ready */
        acia_ird_t          ird  : 1;   /* Receiver Interrupt Request Disabled */
        acia_tic_t          tic  : 2;
        acia_rem_t          rem  : 1;   /* Receiver echo mode */
        acia_pme_t          pme  : 1;   /* Parity enable mode */
        acia_pmc_t          pmc  : 2;   /* Parity mode control */
    }                   bits;
    uint8_t             data;
} acia_cmd_t;

typedef union {
    struct {
        uint8_t             sbr  : 4;   /* Selected baud rate */
        uint8_t             rcs  : 1;   /* Receiver clock source */
        uint8_t             wl   : 2;   /* word length */
        uint8_t             sbn  : 1;   /* Stop bits */
    }                   bits;
    uint8_t             data;
} acia_ctl_t;

typedef struct {
	uint8_t             buf;
    acia_sr_t           sr;
    acia_cmd_t          cmd;
    acia_ctl_t          ctl;
} acia_t;

#define ACIA_TXD(XX)        ((XX) -> buf)
#define ACIA_RXD(XX)        ((XX) -> buf)

/* Flags are Read Only */
#define ACIA_PE(XX)         ((XX) -> sr.bits.pe)
#define ACIA_FE(XX)         ((XX) -> sr.bits.fe)
#define ACIA_OVRN(XX)       ((XX) -> sr.bits.ovrn)
#define ACIA_RDRF(XX)       ((XX) -> sr.bits.rdrf)
#define ACIA_TDRE(XX)       ((XX) -> sr.bits.tdre)  /* Faulty on all W65C51 chips */
#define ACIA_DCDB(XX)       ((XX) -> sr.bits.dcdb)
#define ACIA_DSRB(XX)       ((XX) -> sr.bits.dsrb)
#define ACIA_IRQ(XX)        ((XX) -> sr.bits.irq)

#define ACIA_DTR(XX)        ((XX) -> cmd.bits.dtr)
#define ACIA_IRD(XX)        ((XX) -> cmd.bits.ird)
#define ACIA_TIC(XX)        ((XX) -> cmd.bits.tic)
#define ACIA_REM(XX)        ((XX) -> cmd.bits.rem)
#define ACIA_PME(XX)        ((XX) -> cmd.bits.pme)
#define ACIA_PMC(XX)        ((XX) -> cmd.bits.pmc)

#define ACIA_SBR(XX)        ((XX) -> ctl.bits.sbr)
#define ACIA_RCS(XX)        ((XX) -> ctl.bits.rcs)
#define ACIA_WL(XX)         ((XX) -> ctl.bits.wl)
#define ACIA_SBN(XX)        ((XX) -> ctl.bits.sbn)

#define aciaReset(XX)      { (XX) -> sr.data = 0x00; }

#endif