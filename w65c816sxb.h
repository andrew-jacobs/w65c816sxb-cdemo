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

#ifndef _W65C816SXB_H
#define _W65C816SXB_H

#include <w65c816.h>
#include <w65c22.h>
#include <w65c21.h>
#include <w65c51.h>

#define FCLK            8000000ul       /* 8Mhz Crystal */ 

#define ACIA            ((volatile acia_t *) 0x7f80)
#define PIA             ((volatile pia_t  *) 0x7fa0)
#define USR_VIA         ((volatile via_t  *) 0x7fc0)
#define SYS_VIA         ((volatile via_t  *) 0x7fe0)

extern void initialise (void);

extern interrupt void IRQHandler (void);

extern uint32_t millis (void);

extern void aciaTx (uint8_t ch);
extern int16_t aciaRx (int16_t wait);

#endif