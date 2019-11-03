/*============================================================================*
 * __        ____  ____   ____ ___  _  __        
 * \ \      / / /_| ___| / ___( _ )/ |/ /_       
 *  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \      
 *   \ V  V /| (_) |__) | |__| (_) | | (_) |     
 *  __\_/\_/  \___/____/ \____\___/|_|\___/      
 * |  _ \  ___ / _(_)_ __ | |_(_) ___  _ __  ___ 
 * | | | |/ _ \ |_| | '_ \| __| |/ _ \| '_ \/ __|
 * | |_| |  __/  _| | | | | |_| | (_) | | | \__ \
 * |____/ \___|_| |_|_| |_|\__|_|\___/|_| |_|___/
 *
 * ---------------------------------------------------------------------------*                                               
 *============================================================================*/

#ifndef _W65C816_H
#define _W65C816_H

#define enableInterrupts()      asm { cli; }
#define disableInterrupts()     asm { sei; }

#endif