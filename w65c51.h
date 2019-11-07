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

#define ACIA_SR_PE_MASK         0x01
#define ACIA_SR_FE_MASK         0x02
#define ACIA_SR_OVRN_MASK       0x04
#define ACIA_SR_RDRF_MASK       0x08
#define ACIA_SR_TDRE_MASK       0x10        /* Faulty on all W65C51 chips */
#define ACIA_SR_DCDB_MASK       0x20
#define ACIA_SR_DSRB_MASK       0x40
#define ACIA_SR_IRQ_MASK        0x80

#define ACIA_CMD_DTR_MASK       0x01
#define ACIA_CMD_IRD_MASK       0x02
#define ACIA_CMD_TIC_MASK       0x0c
#define ACIA_CMD_REM_MASK       0x10
#define ACIA_CMD_PME_MASK       0x20
#define ACIA_CMD_PMC_MASK       0xc0

#define ACIA_CMD_DTR_DISABLE    0x00
#define ACIA_CMD_DTR_ENABLE     0x01

#define ACIA_CMD_IRD_ENABLE     0x00
#define ACIA_CMD_IRD_DISABLE    0x02

#define ACIA_CMD_TIC_RTS        0x00
#define ACIA_CMD_TIC_ENABLE     0x04
#define ACIA_CMD_TIC_DISABLE    0x08
#define ACIA_CMD_TIC_BRK        0x0c

#define ACIA_CMD_REM_NORMAL     0x00
#define ACIA_CMD_REM_ECHO       0x10

#define ACIA_CMD_PME_DISABLE    0x00
#define ACIA_CMD_PME_ENABLE     0x20

#define ACIA_CMD_PMC_ODD        0x00
#define ACIA_CMD_PMC_EVEN       0x40
#define ACIA_CMD_PMC_MARK       0x80
#define ACIA_CMD_PMC_SPACE      0xc0

#define ACIA_CTL_SBR_MASK       0x0f
#define ACIA_CTL_RCS_MASK       0x10
#define ACIA_CTL_WL_MASK        0x60
#define ACIA_CTL_SBN_MASK       0x80

#define ACIA_CTL_SBR_X16        0x00
#define ACIA_CTL_SBR_50         0x01
#define ACIA_CTL_SBR_75         0x02
#define ACIA_CTL_SBR_110        0x03
#define ACIA_CTL_SBR_134        0x04
#define ACIA_CTL_SBR_150        0x05
#define ACIA_CTL_SBR_300        0x06
#define ACIA_CTL_SBR_600        0x07
#define ACIA_CTL_SBR_1200       0x08
#define ACIA_CTL_SBR_1800       0x09
#define ACIA_CTL_SBR_2400       0x0a
#define ACIA_CTL_SBR_3600       0x0b
#define ACIA_CTL_SBR_4800       0x0c
#define ACIA_CTL_SBR_7200       0x0d
#define ACIA_CTL_SBR_9600       0x0e
#define ACIA_CTL_SBR_19200      0x0f

#define ACIA_CTL_RCS_EXT        0x00
#define ACIA_CTL_RCS_BAUD       0x10

#define ACIA_CTL_WL_8           0x00
#define ACIA_CTL_WL_7           0x02
#define ACIA_CTL_WL_6           0x40
#define ACIA_CTL_WL_5           0x60

#define ACIA_CTL_SBN_1          0x00
#define ACIA_CTL_SBN_1_5        0x80        /* Only when WL = 5 */
#define ACIA_CTL_SBN_2          0x80

typedef struct {
	uint8_t             buf;
    uint8_t             sr;
    uint8_t             cmd;
    uint8_t             ctl;
} acia_t;

#define ACIA_BUF(XX)        ((XX) -> buf)
#define ACIA_SR(XX)         ((XX) -> sr)
#define ACIA_CMD(XX)        ((XX) -> cmd)
#define ACIA_CTL(XX)        ((XX) -> ctl)

#define aciaReset(XX)       { ACIA_SR (XX) = 0x00; }

#endif