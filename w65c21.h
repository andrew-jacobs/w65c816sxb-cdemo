/*============================================================================*
 * Peripheral Interface Adapter (PIA) Definitions                             *
 *----------------------------------------------------------------------------*/

#ifndef _W65C21_H
#define _W65C21_H

#include <inttypes.h>

typedef union {
    struct {
        uint8_t             b0 : 1;
        uint8_t             b1 : 1;
        uint8_t             b2 : 1;
        uint8_t             b3 : 1;
        uint8_t             b4 : 1;
        uint8_t             b5 : 1;
        uint8_t             b6 : 1;
        uint8_t             b7 : 1;
    }                   bits;
    uint8_t             data;
} pia_data_t;

typedef union {
    struct {
        uint8_t             b0 : 1;
        uint8_t             b1 : 1;
        uint8_t             b2 : 1;
        uint8_t             b3 : 1;
        uint8_t             b4 : 1;
        uint8_t             b5 : 1;
        uint8_t             b6 : 1;
        uint8_t             b7 : 1;
    }                   bits;
    uint8_t             data;
} pia_ctrl_t;

typedef struct {
    uint8_t             pia;
    pia_ctrl_t          cra;
    uint8_t             pib;
    pia_ctrl_t          crb;
} pia_t;

#define VIA_PIA(VIA)    ((VIA) -> cra.b2 = 1, (VIA) -> pia)
#define VIA_ORA(VIA)    ((VIA) -> cra.b2 = 0, (VIA) -> pia)

#endif