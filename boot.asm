;===============================================================================
; __        ____  ____   ____ ___  _  __  ______  ______  
; \ \      / / /_| ___| / ___( _ )/ |/ /_/ ___\ \/ / __ ) 
;  \ \ /\ / / '_ \___ \| |   / _ \| | '_ \___ \\  /|  _ \ 
;   \ V  V /| (_) |__) | |__| (_) | | (_) |__) /  \| |_) |
;  __\_/\_/  \___/____/ \____\___/|_|\___/____/_/\_\____/ 
; | __ )  ___   ___ | |_   / ___|___   __| | ___          
; |  _ \ / _ \ / _ \| __| | |   / _ \ / _` |/ _ \         
; | |_) | (_) | (_) | |_  | |__| (_) | (_| |  __/         
; |____/ \___/ \___/ \__|  \____\___/ \__,_|\___|         
;
; W65C816SXB C Runtime Startup Module (Small Model)
;-------------------------------------------------------------------------------
; Copyright (C)2019 Andrew Jacobs.
; All rights reserved.
;
; This work is made available under the terms of the Creative Commons
; Attribution-NonCommercial-ShareAlike 4.0 International license. Open the
; following URL to see the details.
;
; http://creativecommons.org/licenses/by-nc-sa/4.0/
;
;===============================================================================
; Notes
;
; This code is based on the sample code in the Assembler/Linker manual and the
; examples provided by WDC for the W65C816SXB board.
;-------------------------------------------------------------------------------

		chip	65816

		include "w65c816.inc"
		
;===============================================================================
; Stack Area
;-------------------------------------------------------------------------------

STACK		section

		ds	512		; Reserve 512 bytes for the stack
		
		ends
		
;===============================================================================
; Reset Handler
;-------------------------------------------------------------------------------

		code

		xref	__main
		xref	_BEG_DATA
		xref	_END_DATA
		xref	_ROM_BEG_DATA
		xref	_BEG_UDATA
		xref	_END_UDATA
		xref	_BEG_STACK
		xref	_END_STACK

		longa	off
		longi	off
RESET:
		sei				; Reset flags
		cld
		native				; Go native

		long_ai				; Set stack
		ldx	#_END_STACK-1
		txs

		lda	#_END_DATA-_BEG_DATA	; Any initialised data?
		beq	NoConstData
		dec	a			; Yes, copy into RAM
		ldx	#_ROM_BEG_DATA
		ldy	#_BEG_DATA
		mvn	^_ROM_BEG_DATA,^_BEG_DATA
NoConstData:

		short_a
		lda	#^_BEG_DATA		; Ensure data bank selected
		pha
		plb

		ldx	#_END_UDATA-_BEG_UDATA	; Any uninitialise data?
		beq	NoData
ClearData:	dex				; Yes, clear it
		stz	!_BEG_UDATA,x
		bne	ClearData
NoData:

		long_a				; Start the main application
		pea	0
		pea	0
		pea	0
		jmp	__main
		
;===============================================================================
; Vectors
;-------------------------------------------------------------------------------
		
BadVector:
		stp
		bra	BadVector
		
		xref	__IRQHandler
		
SHADOW		section offset $7ee0

		dw	0		; Native Mode Vectors
		dw	0
		dw	BadVector	; COP
		dw	BadVector	; BRK
		dw	BadVector	; ABORT
		dw	BadVector	; NMI
		dw	0
		dw	__IRQHandler	; IRQ

		dw	0		; Emulation Mode Vectors
		dw	0
		dw	BadVector	; COP
		dw	0
		dw	BadVector	; ABORT
		dw	BadVector	; NMI
		dw	RESET		; RESET
		dw	BadVector	; IRQBRK
		
		ends
	
VECTORS		section	offset $ffe0

		dw	0		; Native Mode Vectors
		dw	0
		dw	BadVector	; COP
		dw	BadVector	; BRK
		dw	BadVector	; ABORT
		dw	BadVector	; NMI
		dw	0
		dw	__IRQHandler	; IRQ

		dw	0		; Emulation Mode Vectors
		dw	0
		dw	BadVector	; COP
		dw	0
		dw	BadVector	; ABORT
		dw	BadVector	; NMI
		dw	RESET		; RESET
		dw	BadVector	; IRQBRK

		end