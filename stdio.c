/*============================================================================*
 * __        ____  ____   ____ ___  _  __  ______  ______                     *
 * \ \      / / /_| ___| / ___( _ )/ |/ /_/ ___\ \/ / __ )                    *
 *  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \___ \\  /|  _ \                    *
 *   \ V  V /| (_) |__) | |__| (_) | | (_) |__) /  \| |_) |                   *
 *  __\_/\_/  \___/____/ \____\___/|_|\___/____/_/\_\____/                    *
 * / ___|(_)_ __ ___  _ __ | | ___   ___| |_ __| (_) ___                      *
 * \___ \| | '_ ` _ \| '_ \| |/ _ \ / __| __/ _` | |/ _ \                     *
 *  ___) | | | | | | | |_) | |  __/ \__ \ || (_| | | (_) |                    *
 * |____/|_|_| |_| |_| .__/|_|\___| |___/\__\__,_|_|\___/                     *
 *                   |_|                                                      *
 *                                                                            *
 * A Simple STDIO Implementtation for the W65C816SXB Developer Board          *
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

/* Define an 8K area to be used for the C heap */
char heap_start [8 * 1024];
char heap_end [1];

/* Assume all file are TTY devices */
int isatty (int fd)
{
    return (1);
}

/* Read a number of bytes from the ACIA into a buffer */
size_t read (int fd, void *pData, size_t len)
{
    size_t          offset;

    for (offset = 0; offset < len; ++offset)
        ((uint8_t *) pData)[offset] = aciaRx (1);

    return (len);
}

/* Write a number of bytes to the ACIA from a buffer */
size_t write (int fd, void *pData, size_t len)
{
    size_t          offset;

    for (offset = 0; offset < len; ++offset)
        aciaTx (((const uint8_t *) pData)[offset]);

    return (len);
}

/* The following are defined only to satisfy the linker */
int lseek (int fd, long pos, int xx)
{
    return (0);
}

int close (int fd)
{
    return (0);
}

int unlink (const char *pFileName)
{
    return (0);
}