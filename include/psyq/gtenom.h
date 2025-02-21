;
; $PSLibId: Run-time Library Release 4.3$
;

;
;	gtenom.h
;	Copyright(C) 1995,1996,1997 Sony Computer Entertainment Inc.
;	All rights reserved.
;

read_sz_fifo3			macro	reg1,reg2,reg3
				mfc2	reg1,r17
				mfc2	reg2,r18
				mfc2	reg3,r19
				nop
				endm

read_sz_fifo4			macro	reg1,reg2,reg3,reg4 	
				mfc2	reg1,r16
				mfc2	reg2,r17
				mfc2	reg3,r18
				mfc2	reg4,r19
				nop
				endm

read_szx			macro	reg1
				mfc2	reg1,r16
				nop
				endm
			
read_sz0			macro	reg1
				mfc2	reg1,r17
				nop
				endm
			
read_sz1			macro	reg1				
				mfc2	reg1,r18
				nop
				endm
			
read_sz2			macro	reg1
				mfc2	reg1,r19
				nop
				endm
			
read_sxsy_fifo3			macro	reg1,reg2,reg3
				mfc2	reg1,r12
				mfc2	reg2,r13
				mfc2	reg3,r14
				nop
				endm

read_sxsy0			macro	reg1	
				mfc2	reg1,r12
				nop
				endm

read_sxsy1			macro	reg1
				mfc2	reg1,r13
				nop
				endm

read_sxsy2			macro	reg1
				mfc2	reg1,r14
				nop
				endm

read_rgb_fifo			macro	reg1,reg2,reg3
				mfc2	reg1,r20
				mfc2	reg2,r21
				mfc2	reg3,r22
				nop
				endm

read_rgb0			macro	reg1
				mfc2	reg1,r20
				nop
				endm

read_rgb1			macro	reg1	
				mfc2	reg1,r21
				nop
				endm

read_rgb2			macro	reg1
				mfc2	reg1,r22
				nop
				endm

read_flag			macro	reg1
				cfc2	reg1,r31
				nop
				endm

read_p				macro	reg1
				mfc2	reg1,r8
				nop
				endm

read_otz			macro	reg1
				mfc2	reg1,r7
				nop
				endm

read_opz			macro	reg1
				mfc2	reg1,r24
				nop
				endm

read_mt				macro	reg1,reg2,reg3
				mfc2	reg1,r25
				mfc2	reg2,r26
				mfc2	reg3,r27
				nop
				endm

store_sxsy_fifo3		macro	reg1,reg2,reg3
				swc2	r12,(reg1)
				swc2	r13,(reg2)
				swc2	r14,(reg3)
				nop
				endm

store_sxsy0			macro	reg1
				swc2	r12,(reg1)
				nop
				endm

store_sxsy1			macro	reg1
				swc2	r13,(reg1)
				nop
				endm

store_sxsy2			macro	reg1
				swc2	r14,(reg1)
				nop
				endm

store_rgb_fifo			macro	reg1,reg2,reg3
				swc2	r20,(reg1)
				swc2	r21,(reg2)
				swc2	r22,(reg3)
				nop
				endm

store_rgb0			macro	reg1
				swc2	r20,(reg1)
				nop
				endm

store_rgb1			macro	reg1
				swc2	r21,(reg1)
				nop
				endm

store_rgb2			macro	reg1
				swc2	r22,(reg1)
				nop
				endm

set_trans_matrix		macro	reg1,reg2,reg3
				ctc2	reg1,r5
				ctc2	reg2,r6
				ctc2	reg3,r7
				nop
				endm

