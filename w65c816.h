/*============================================================================*
 * __        ____  ____   ____ ___  _  __                                     *
 * \ \      / / /_| ___| / ___( _ )/ |/ /_                                    *
 *  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \                                   *
 *   \ V  V /| (_) |__) | |__| (_) | | (_) |                                  *
 *    \_/\_/  \___/____/ \____\___/|_|\___/                                   *
 *                                                                            *
 * W65C816 Specific Definitions                                               *
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

#ifndef _W65C816_H
#define _W65C816_H

#define enableInterrupts()      asm { cli; }
#define disableInterrupts()     asm { sei; }

#define suspendInterrupts()     asm { php; sei; }
#define restoreInterrupts()     asm { plp; }

#endif