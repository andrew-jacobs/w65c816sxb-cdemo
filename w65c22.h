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
    VIA_T1C_TIMED_INTERRUPT = 0,
    VIA_T1C_CONTINUOUS      = 1,
    VIA_T1C_ONE_SHOT        = 2,
    VIA_T1C_SQUARE_WAVE     = 3
} via_t1c_t;

typedef enum {
    VIA_T2C_TIMED_INTERRUPT = 0,
    VIA_T2C_COUNT_DOWN      = 1
} via_t2c_t;

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

typedef union {
    struct {
        uint8_t             b0  : 1;
        uint8_t             b1  : 1;
        uint8_t             b2  : 1;
        uint8_t             b3  : 1;
        uint8_t             b4  : 1;
        uint8_t             b5  : 1;
        uint8_t             b6  : 1;
        uint8_t             b7  : 1;
    }                   bits;
    uint8_t             data;
} via_port_t;

typedef union {
    struct {
        uint8_t             b0  : 1;
        uint8_t             b1  : 1;
        uint8_t             b2  : 1;
        uint8_t             b3  : 1;
        uint8_t             b4  : 1;
        uint8_t             b5  : 1;
        uint8_t             b6  : 1;
        uint8_t             b7  : 1;
    }                   bits;
    uint8_t             data;
} via_sr_t;

typedef union {
    struct {
        uint8_t             pa  : 1;
        uint8_t             pb  : 1;
        via_src_t           src : 3;
        via_t2c_t           t2c : 1;
        via_t1c_t           t1c : 2;
    }                   bits;
    uint8_t             data;
} via_acr_t;

typedef union {
    struct {
        via_edge_t          ca1 : 1;
        via_ctrl_t          ca2 : 3;
        via_edge_t          cb1 : 1;
        via_ctrl_t          cb2 : 3;
    }                   bits;
    uint8_t             data;
} via_pcr_t;

typedef union {
    struct {
        uint8_t             ca2 : 1;
        uint8_t             ca1 : 1;
        uint8_t             sr  : 1;
        uint8_t             cb2 : 1;
        uint8_t             cb1 : 1;
        uint8_t             t2  : 1;
        uint8_t             t1  : 1;
        uint8_t             irq : 1;
    }                   bits;
    uint8_t             data;
} via_ifr_t;

typedef union {
    struct {
        uint8_t             ca2 : 1;
        uint8_t             ca1 : 1;
        uint8_t             sr  : 1;
        uint8_t             cb2 : 1;
        uint8_t             cb1 : 1;
        uint8_t             t2  : 1;
        uint8_t             t1  : 1;
        uint8_t             set : 1;
    }                   bits;
    uint8_t             data;
} via_ier_t;

#define VIA_IER_SET         0x80
#define VIA_IER_CLR         0x00
#define VIA_IER_T1          0x40
#define VIA_IER_T2          0x20

typedef struct {
    via_port_t          orb;
    via_port_t          ora;
    via_port_t          ddrb;
    via_port_t          ddra;
    uint8_t             t1cl;
    uint8_t             t1ch;
    uint8_t             t1ll;
    uint8_t             t1lh;
    uint8_t             t2cl;
    uint8_t             t2ch;
    via_sr_t            sr;
    via_acr_t           acr;
    via_pcr_t           pcr;
    via_ifr_t           ifr;
    via_ier_t           ier;
    via_port_t          oran;   
} via_t;

#define VIA_TICL(XX)        ((XX) -> t1cl)
#define VIA_TICH(XX)        ((XX) -> t1ch)

#define VIA_ACR_T2C(XX)     ((XX)) -> acr.t2c)
#define VIA_ACR_T1C(XX)     ((XX)) -> acr.t1c)


#endif