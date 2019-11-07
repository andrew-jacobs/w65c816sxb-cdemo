/*============================================================================*
 * __        ____  ____   ____ ____  _                                        *
 * \ \      / / /_| ___| / ___|___ \/ |                                       *
 *  \ \ /\ / / '_ \___ \| |     __) | |                                       *
 *   \ V  V /| (_) |__) | |___ / __/| |                                       *
 *    \_/\_/  \___/____/ \____|_____|_|                                       *
 *                                                                            *
 * Peripheral Interface Adapter (PIA) Definitions                             *
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

#ifndef _W65C21_H
#define _W65C21_H

#include <inttypes.h>

#define PIA_CRA_CA1_MASK        0x03
#define PIA_CRA_DDRA_MASK       0x04
#define PIA_CRA_CA2_MASK        0x38
#define PIA_CRA_IRQA2_MASK      0x40
#define PIA_CRA_IRQA1_MASK      0x80

#define PIC_CRA_CA1_IN_NEG_DI   0x00
#define PIC_CRA_CA1_IN_NEG_EN   0x01
#define PIC_CRA_CA1_IN_POS_DI   0x02
#define PIC_CRA_CA1_IN_POS_EN   0x03

#define PIC_CRA_CA2_IN_NEG_DI   0x00
#define PIC_CRA_CA2_IN_NEG_EN   0x08
#define PIC_CRA_CA2_IN_POS_DI   0x10
#define PIC_CRA_CA2_IN_POS_EN   0x18
#define PIC_CRA_CA2_HANDSHAKE   0x20
#define PIC_CRA_CA2_PULSE_OUT   0x28
#define PIC_CRA_CA2_OUT_LO      0x30
#define PIC_CRA_CA2_OUT_HI      0x38

#define PIA_CRB_CB1_MASK        0x03
#define PIA_CRB_DDRB_MASK       0x04
#define PIA_CRB_CB2_MASK        0x38
#define PIA_CRB_IRQB2_MASK      0x40
#define PIA_CRB_IRQB1_MASK      0x80

#define PIC_CRB_CA1_IN_NEG_DI   0x00
#define PIC_CRB_CA1_IN_NEG_EN   0x01
#define PIC_CRB_CA1_IN_POS_DI   0x02
#define PIC_CRB_CA1_IN_POS_EN   0x03

#define PIC_CRB_CA2_IN_NEG_DI   0x00
#define PIC_CRB_CA2_IN_NEG_EN   0x08
#define PIC_CRB_CA2_IN_POS_DI   0x10
#define PIC_CRB_CA2_IN_POS_EN   0x18
#define PIC_CRB_CA2_HANDSHAKE   0x20
#define PIC_CRB_CA2_PULSE_OUT   0x28
#define PIC_CRB_CA2_OUT_LO      0x30
#define PIC_CRB_CA2_OUT_HI      0x38

typedef struct {
    uint8_t             pia;
    uint8_t             cra;
    uint8_t             pib;
    uint8_t             crb;
} pia_t;

#define PIA_ORA(XX)     ((XX) -> cra &= ~PIA_CRA_DDRA_MASK),((XX) -> pia)
#define PIA_DDRA(XX)    ((XX) -> cra |=  PIA_CRA_DDRA_MASK),((XX) -> pia)
#define PIA_ORB(XX)     ((XX) -> crb &= ~PIA_CRB_DDRB_MASK),((XX) -> pib)
#define PIA_DDRB(XX)    ((XX) -> crb |=  PIA_CRB_DDRB_MASK),((XX) -> pib)

#endif