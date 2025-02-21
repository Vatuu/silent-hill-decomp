; $PSLibId: Run-time Library Release 4.3$
;
;	Macro definitions of DMPSX version 3 for Assembler programs
;	inline_a.h
;	Copyright(C) 1996,  Sony Computer Entertainment Inc.
;	All rights reserved.
;

;
; GTE commands with 2 nops
;
nRTPS		macro
		nop
		nop
		dw	$0000007f
		endm

nRTPT		macro
		nop
		nop
		dw	$000000bf
		endm

nDCPL		macro
		nop
		nop
		dw	$00000dff
		endm

nDPCS		macro
		nop
		nop
		dw	$00000e3f
		endm

nDPCT		macro
		nop
		nop
		dw	$00000e7f
		endm

nINTPL		macro
		nop
		nop
		dw	$00000ebf
		endm

nNCS		macro
		nop
		nop
		dw	$00000f7f
		endm

nNCT		macro
		nop
		nop
		dw	$00000fbf
		endm

nNCDS		macro
		nop
		nop
		dw	$00000fff
		endm

nNCDT		macro
		nop
		nop
		dw	$0000103f
		endm

nNCCS		macro
		nop
		nop
		dw	$0000107f
		endm

nNCCT		macro
		nop
		nop
		dw	$000010bf
		endm

nCDP		macro
		nop
		nop
		dw	$000010ff
		endm

nCC		macro
		nop
		nop
		dw	$0000113f
		endm

nNCLIP		macro
		nop
		nop
		dw	$0000117f
		endm

nAVSZ3		macro
		nop
		nop
		dw	$000011bf
		endm

nAVSZ4		macro
		nop
		nop
		dw	$000011ff
		endm

nMVMVA		macro	sf,mx,v,cv,lm
		nop
		nop
		dw	$000013bf|sf<<25|mx<<23|v<<21|cv<<19|lm<<18
		endm

nSQR		macro	sf
		nop
		nop
		dw	$000013ff|sf<<25
		endm

nOP		macro	sf
		nop
		nop
		dw	$0000143f|sf<<25
		endm

nGPF		macro	sf
		nop
		nop
		dw	$0000147f|sf<<25
		endm

nGPL		macro	sf
		nop
		nop
		dw	$000014bf|sf<<25
		endm

;
; GTE commands without nops
;
RTPS		macro
		dw	$0000007f
		endm

RTPT		macro
		dw	$000000bf
		endm

DCPL		macro
		dw	$00000dff
		endm

DPCS		macro
		dw	$00000e3f
		endm

DPCT		macro
		dw	$00000e7f
		endm

INTPL		macro
		dw	$00000ebf
		endm

NCS		macro
		dw	$00000f7f
		endm

NCT		macro
		dw	$00000fbf
		endm

NCDS		macro
		dw	$00000fff
		endm

NCDT		macro
		dw	$0000103f
		endm

NCCS		macro
		dw	$0000107f
		endm

NCCT		macro
		dw	$000010bf
		endm

CDP		macro
		dw	$000010ff
		endm

CC		macro
		dw	$0000113f
		endm

NCLIP		macro
		dw	$0000117f
		endm

AVSZ3		macro
		dw	$000011bf
		endm

AVSZ4		macro
		dw	$000011ff
		endm

MVMVA		macro	sf,mx,v,cv,lm
		dw	$000013bf|sf<<25|mx<<23|v<<21|cv<<19|lm<<18
		endm

SQR		macro	sf
		dw	$000013ff|sf<<25
		endm

OP		macro	sf
		dw	$0000143f|sf<<25
		endm

GPF		macro	sf
		dw	$0000147f|sf<<25
		endm

GPL		macro	sf
		dw	$000014bf|sf<<25
		endm
