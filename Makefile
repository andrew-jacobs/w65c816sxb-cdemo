#===============================================================================
#
# __        ____  ____   ____ ___  _  __  ______  ______  
# \ \      / / /_| ___| / ___( _ )/ |/ /_/ ___\ \/ / __ ) 
#  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \___ \\  /|  _ \ 
#   \ V  V /| (_) |__) | |__| (_) | | (_) |__) /  \| |_) |
#   _\_/\_/__\___/____/ \____\___/|_|\___/____/_/\_\____/ 
#  / ___|  _ \  ___ _ __ ___   ___                        
# | |   | | | |/ _ \ '_ ` _ \ / _ \                       
# | |___| |_| |  __/ | | | | | (_) |                      
#  \____|____/ \___|_| |_| |_|\___/                       
#                                                         
#-------------------------------------------------------------------------------
# Copyright (C)2019 Andrew Jacobs.
# All rights reserved.
#
# This work is made available under the terms of the Creative Commons
# Attribution-NonCommercial-ShareAlike 4.0 International license. Open the
# following URL to see the details.
#
# http://creativecommons.org/licenses/by-nc-sa/4.0/
#
#===============================================================================
# Notes:
#
#-------------------------------------------------------------------------------

AS	=	wdc816as

ASFLAGS	=	-G -LW
 
CC	=	wdc816cc

#CCFLAGS	=	-BS -LW -SOP -MC -MK -MT -MU -MV -SS -PE -DUSING_816
CCFLAGS	=	-BS -LW -SF -MS -PE -DUSING_816

LD	=	wdcln

LDFLAGS	=	-G -T -C0300

RM	=	erase

#-------------------------------------------------------------------------------

.asm.obj:
	$(AS) $(ASFLAGS) $<
	
.c.obj:
	$(CC) $(CCFLAGS) $<
	
#===============================================================================


ASMS	=	boot.asm

SRCS	=	demo.c w65c816sxb.c

OBJS	=	$(ASMS:.asm=.obj) $(SRCS:.c=.obj)

LIBS	=	-LMS -LCS

all:		demo.s28 demo.bin

clean:
		$(RM) *.obj
		$(RM) *.bin
		$(RM) *.lst
		$(RM) *.s28
		$(RM) *.map
		$(RM) *.sym
		$(RM) *.tmp

demo.s28:	$(OBJS)
	$(LD) -G -HM28 $(LDFLAGS) -O$@ $(OBJS) $(LIBS)
	
demo.bin:	$(OBJS)
	$(LD) -G -HZ $(LDFLAGS) -O$@ $(OBJS) $(LIBS)
	
#===============================================================================

w65c816sxb.h:	w65c816.h w65c22.h w65c21.h w65c51.h

demo.obj:	demo.c w65c816sxb.h

w65c816sxb.obj:	w65c816sxb.c w65c816sxb.h

