/*============================================================================*
 * __        ____  ____   ____ ___  _  __  ______  ______                     * 
 * \ \      / / /_| ___| / ___( _ )/ |/ /_/ ___\ \/ / __ )                    *
 *  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \___ \\  /|  _ \                    *
 *   \ V  V /| (_) |__) | |__| (_) | | (_) |__) /  \| |_) |                   *
 *   _\_/\_/__\___/____/ \____\___/|_|\___/____/_/\_\____/                    *
 *  / ___|  _ \  ___ _ __ ___   ___                                           *
 * | |   | | | |/ _ \ '_ ` _ \ / _ \                                          *
 * | |___| |_| |  __/ | | | | | (_) |                                         *
 *  \____|____/ \___|_| |_| |_|\___/                                          *                                                         
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

int main (int argc, char **argv)
{
	int			count;

	initialise ();

	/* Timer test */
	puts ("\nStarting");
	for (count = 0; count < 5; ++count) {
		putchar ('.');
		delay (1000);
	}
	puts ("\n\n");

	printf ("W65C816SXB Echo Demo\n");
	printf ("Type some characters:\n");
	
	/* Echo I/O */
	for (;;)
		putchar (getchar ());
	
	return (0);
}