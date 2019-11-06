/*============================================================================*
 * __        ____  ____   ____ ____  ____                                     *
 * \ \      / / /_| ___| / ___|___ \|___ \                                    *
 *  \ \ /\ / / '_ \___ \| |     __) | __) |                                   *
 *   \ V  V /| (_) |__) | |___ / __/ / __/                                    *
 *    \_/\_/  \___/____/ \____|_____|_____|                                   *
 *                                                                            *
 * Versatile Interace Adapter (VIA) Definitions                               *
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

#ifndef _W65C22_H
#define _W65C22_H

#include <inttypes.h>

/*
typedef enum {
    VIA_SRC_DISABLED        = 0,
    VIA_SRC_SHIFT_IN_T2     = 1,
    VIA_SRC_SHIFT_IN_PHI2   = 2,
    VIA_SRC_SHIFT_IN_CB1    = 3,
    VIA_SRC_SHIFT_OUT_FREE  = 4,
    VIA_SRC_SHIFT_OUT_T2    = 5,
    VIA_SRC_SHIFT_OUT_PHI2  = 6, 
    VIA_SRC_SHIFT_OUT_CB1   = 7
} via_src_t;


typedef enum {
    VIA_EDGE_NEGATIVE       = 0,
    VIA_EDGE_POSITIVE       = 1
} via_edge_t;

typedef enum {
    VIA_INPUT_NEGATIVE_EDGE = 0,

    VIA_HANDSHAKE           = 4,
    VIA_PULSE_OUTPUT        = 5,
    VIA_LOW_OUTPUT          = 6,
    VIA_HIGH_OUTPUT         = 7
} via_ctrl_t;
*/

#define VIA_ACR_PA_MASK         0x01
#define VIA_ACR_PB_MASK         0x02
#define VIA_ACR_SRC_MASK        0x1c
#define VIA_ACR_T2C_MASK        0x20
#define VIA_ACR_T1C_MASK        0xc0

#define VIA_ACR_T2C_TIMED_INTERRUPT     0x00
#define VIA_ACR_T2C_COUNT_DOWN          0x20

#define VIA_ACR_T1C_TIMED_INTERRUPT     0x00
#define VIA_ACR_T1C_CONTINUOUS          0x40
#define VIA_ACR_T1C_ONE_SHOT            0x80
#define VIA_ACR_T1C_SQUARE_WAVE         0xc0

/*
typedef union {
    struct {
        via_edge_t          ca1 : 1;
        via_ctrl_t          ca2 : 3;
        via_edge_t          cb1 : 1;
        via_ctrl_t          cb2 : 3;
    }                   bits;
    uint8_t             data;
} via_pcr_t;
*/

#define VIA_IFR_CA2_MASK        0x01
#define VIA_IFR_CA1_MASK        0x02
#define VIA_IFR_SR_MASK         0x04
#define VIA_IFR_CB2_MASK        0x08
#define VIA_IFR_CB1_MASK        0x10
#define VIA_IFR_T2_MASK         0x20
#define VIA_IFR_T1_MASK         0x40
#define VIA_IFR_IRQ_MASK        0x80

#define VIA_IER_CA2_MASK        0x01
#define VIA_IER_CA1_MASK        0x02
#define VIA_IER_SR_MASK         0x04
#define VIA_IER_CB2_MASK        0x08
#define VIA_IER_CB1_MASK        0x10
#define VIA_IER_T2_MASK         0x20
#define VIA_IER_T1_MASK         0x40
#define VIA_IER_SET_MASK        0x80
#define VIA_IER_CLR_MASK        0x00

typedef struct {
    uint8_t             orb;
    uint8_t             ora;
    uint8_t             ddrb;
    uint8_t             ddra;
    uint8_t             t1cl;
    uint8_t             t1ch;
    uint8_t             t1ll;
    uint8_t             t1lh;
    uint8_t             t2cl;
    uint8_t             t2ch;
    uint8_t             sr;
    uint8_t             acr;
    uint8_t             pcr;
    uint8_t             ifr;
    uint8_t             ier;
    uint8_t             oran;   
} via_t;

#define VIA_ORB(XX)         ((XX) -> orb)
#define VIA_ORA(XX)         ((XX) -> ora)
#define VIA_DDRB(XX)        ((XX) -> ddrb)
#define VIA_DDRA(XX)        ((XX) -> ddra)
#define VIA_T1CL(XX)        ((XX) -> t1cl)
#define VIA_T1CH(XX)        ((XX) -> t1ch)
#define VIA_T1LL(XX)        ((XX) -> t1ll)
#define VIA_T1LH(XX)        ((XX) -> t1Lh)
#define VIA_T2CL(XX)        ((XX) -> t2cl)
#define VIA_T2CH(XX)        ((XX) -> t2ch)
#define VIA_SR(XX)          ((XX) -> sr)
#define VIA_ACR(XX)         ((XX) -> acr)
#define VIA_PCR(XX)         ((XX) -> pcr)
#define VIA_IFR(XX)         ((XX) -> ifr)
#define VIA_IER(XX)         ((XX) -> ier)
#define VIA_ORAN(XX)        ((XX) -> oran)

#define VIA_T1C(XX)         (*((uint16_t *) &VIA_T1CL(XX)))
#define VIA_T1L(XX)         (*((uint16_t *) &VIA_T1LL(XX)))
#define VIA_T2C(XX)         (*((uint16_t *) &VIA_T2CL(XX)))

#endif