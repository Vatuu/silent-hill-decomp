/*
 * $PSLibId: Run-time Library Release 4.3$
 */

/*
 *	Macro definitions of DMPSX version 3
 *	inline_c.h
 *	Copyright(C) 1996, Sony Computer Entertainment Inc.
 *	All rights reserved.
 */

/*
 * Type 1 functions
 */

#define gte_ldv0( r0 ) __asm__ volatile (			\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldv1( r0 ) __asm__ volatile (			\
	"lwc2	$2, 0( %0 );"					\
	"lwc2	$3, 4( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldv2( r0 ) __asm__ volatile (			\
	"lwc2	$4, 0( %0 );"					\
	"lwc2	$5, 4( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldv3( r0, r1, r2 ) __asm__ volatile (		\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 );"					\
	"lwc2	$2, 0( %1 );"					\
	"lwc2	$3, 4( %1 );"					\
	"lwc2	$4, 0( %2 );"					\
	"lwc2	$5, 4( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv3c( r0 ) __asm__ volatile (			\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 );"					\
	"lwc2	$2, 8( %0 );"					\
	"lwc2	$3, 12( %0 );"					\
	"lwc2	$4, 16( %0 );"					\
	"lwc2	$5, 20( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldv3c_vertc( r0 ) __asm__ volatile (		\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 );"					\
	"lwc2	$2, 12( %0 );"					\
	"lwc2	$3, 16( %0 );"					\
	"lwc2	$4, 24( %0 );"					\
	"lwc2	$5, 28( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldv01( r0, r1 ) __asm__ volatile (			\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 );"					\
	"lwc2	$2, 0( %1 );"					\
	"lwc2	$3, 4( %1 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ) )

#define gte_ldv01c( r0 ) __asm__ volatile (			\
	"lwc2	$0, 0( %0 );"					\
	"lwc2	$1, 4( %0 );"					\
	"lwc2	$2, 8( %0 );"					\
	"lwc2	$3, 12( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldrgb( r0 ) __asm__ volatile (			\
	"lwc2	$6, 0( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldrgb3( r0, r1, r2 ) __asm__ volatile (		\
	"lwc2	$20, 0( %0 );"					\
	"lwc2	$21, 0( %1 );"					\
	"lwc2	$22, 0( %2 );"					\
	"lwc2	$6, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb3c( r0 ) __asm__ volatile (			\
	"lwc2	$20, 0( %0 );"					\
	"lwc2	$21, 4( %0 );"					\
	"lwc2	$22, 8( %0 );"					\
	"lwc2	$6, 8( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldlv0( r0 ) __asm__ volatile (			\
	"lhu	$13, 4( %0 );"					\
	"lhu	$12, 0( %0 );"					\
	"sll	$13, $13, 16;"					\
	"or	$12, $12, $13;"					\
	"mtc2	$12, $0;"					\
	"lwc2	$1, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ldlvl( r0 ) __asm__ volatile (			\
	"lwc2	$9, 0( %0 );"					\
	"lwc2	$10, 4( %0 );"					\
	"lwc2	$11, 8( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsv( r0 ) __asm__ volatile (			\
	"lhu	$12, 0( %0 );"					\
	"lhu	$13, 2( %0 );"					\
	"lhu	$14, 4( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"mtc2	$14, $11"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldbv( r0 ) __asm__ volatile (			\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ldcv( r0 ) __asm__ volatile (			\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"lbu	$14, 2( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"mtc2	$14, $11"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldclmv( r0 ) __asm__ volatile (			\
	"lhu	$12, 0( %0 );"					\
	"lhu	$13, 6( %0 );"					\
	"lhu	$14, 12( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"mtc2	$14, $11"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_lddp( r0 ) __asm__ volatile (			\
	"mtc2	%0, $8"						\
	:							\
	: "r"( r0 ) )

#define gte_ldsxy0( r0 ) __asm__ volatile (			\
	"mtc2	%0, $12"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsxy1( r0 ) __asm__ volatile (			\
	"mtc2	%0, $13"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsxy2( r0 ) __asm__ volatile (			\
	"mtc2	%0, $14"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsxy3( r0, r1, r2 ) __asm__ volatile (		\
	"mtc2	%0, $12;"					\
	"mtc2	%2, $14;"					\
	"mtc2	%1, $13"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldsxy3c( r0 ) __asm__ volatile (			\
	"lwc2	$12, 0( %0 );"					\
	"lwc2	$13, 4( %0 );"					\
	"lwc2	$14, 8( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsz3( r0, r1, r2 ) __asm__ volatile (		\
	"mtc2	%0, $17;"					\
	"mtc2	%1, $18;"					\
	"mtc2	%2, $19"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldsz4( r0, r1, r2, r3 ) __asm__ volatile (	\
	"mtc2	%0, $16;"					\
	"mtc2	%1, $17;"					\
	"mtc2	%2, $18;"					\
	"mtc2	%3, $19"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) )

#define gte_ldopv1( r0 ) __asm__ volatile (			\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $0;"					\
	"lw	$14, 8( %0 );"					\
	"ctc2	$13, $2;"					\
	"ctc2	$14, $4"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldopv2( r0 ) __asm__ volatile (			\
	"lwc2	$11, 8( %0 );"					\
	"lwc2	$9, 0( %0 );"					\
	"lwc2	$10, 4( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldlzc( r0 ) __asm__ volatile (			\
	"mtc2	%0, $30"					\
	:							\
	: "r"( r0 ) )

#define gte_SetRGBcd( r0 ) __asm__ volatile (			\
	"lwc2	$6, 0( %0 )"					\
	:							\
	: "r"( r0 ) )

#define gte_ldbkdir( r0, r1, r2 ) __asm__ volatile (		\
	"ctc2	%0, $13;"					\
	"ctc2	%1, $14;"					\
	"ctc2	%2, $15"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_SetBackColor( r0, r1, r2 ) __asm__ volatile (	\
	"sll	$12, %0, 4;"					\
	"sll	$13, %1, 4;"					\
	"sll	$14, %2, 4;"					\
	"ctc2	$12, $13;"					\
	"ctc2	$13, $14;"					\
	"ctc2	$14, $15"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14" )

#define gte_ldfcdir( r0, r1, r2 ) __asm__ volatile (		\
	"ctc2	%0, $21;"					\
	"ctc2	%1, $22;"					\
	"ctc2	%2, $23"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_SetFarColor( r0, r1, r2 ) __asm__ volatile (	\
	"sll	$12, %0, 4;"					\
	"sll	$13, %1, 4;"					\
	"sll	$14, %2, 4;"					\
	"ctc2	$12, $21;"					\
	"ctc2	$13, $22;"					\
	"ctc2	$14, $23"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14" )

#define gte_SetGeomOffset( r0, r1 ) __asm__ volatile (	\
	"sll	$12, %0, 16;"					\
	"sll	$13, %1, 16;"					\
	"ctc2	$12, $24;"					\
	"ctc2	$13, $25"					\
	:							\
	: "r"( r0 ), "r"( r1 )					\
	: "$12", "$13" )

#define gte_SetGeomScreen( r0 ) __asm__ volatile (		\
	"ctc2	%0, $26"					\
	:							\
	: "r"( r0 ) )

#define gte_ldsvrtrow0( r0 ) __asm__ volatile (			\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $0;"					\
	"ctc2	$13, $1"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_SetRotMatrix( r0 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $0;"					\
	"ctc2	$13, $1;"					\
	"lw	$12, 8( %0 );"					\
	"lw	$13, 12( %0 );"					\
	"lw	$14, 16( %0 );"					\
	"ctc2	$12, $2;"					\
	"ctc2	$13, $3;"					\
	"ctc2	$14, $4"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldsvllrow0( r0 ) __asm__ volatile (			\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $8;"					\
	"ctc2	$13, $9"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_SetLightMatrix( r0 ) __asm__ volatile ( 		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $8;"					\
	"ctc2	$13, $9;"					\
	"lw	$12, 8( %0 );"					\
	"lw	$13, 12( %0 );"					\
	"lw	$14, 16( %0 );"					\
	"ctc2	$12, $10;"					\
	"ctc2	$13, $11;"					\
	"ctc2	$14, $12"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldsvlcrow0( r0 ) __asm__ volatile (			\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $16;"					\
	"ctc2	$13, $17"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_SetColorMatrix( r0 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"ctc2	$12, $16;"					\
	"ctc2	$13, $17;"					\
	"lw	$12, 8( %0 );"					\
	"lw	$13, 12( %0 );"					\
	"lw	$14, 16( %0 );"					\
	"ctc2	$12, $18;"					\
	"ctc2	$13, $19;"					\
	"ctc2	$14, $20"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_SetTransMatrix( r0 ) __asm__ volatile (		\
	"lw	$12, 20( %0 );"					\
	"lw	$13, 24( %0 );"					\
	"ctc2	$12, $5;"					\
	"lw	$14, 28( %0 );"					\
	"ctc2	$13, $6;"					\
	"ctc2	$14, $7"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldtr( r0, r1, r2 ) __asm__ volatile (		\
	"ctc2	%0, $5;"					\
	"ctc2	%1, $6;"					\
	"ctc2	%2, $7"						\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_SetTransVector( r0 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"lw	$14, 8( %0 );"					\
	"ctc2	$12, $5;"					\
	"ctc2	$13, $6;"					\
	"ctc2	$14, $7"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ld_intpol_uv0( r0 ) __asm__ volatile (		\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"ctc2	$12, $21;"					\
	"ctc2	$13, $22"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ld_intpol_uv1( r0 ) __asm__ volatile (		\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ld_intpol_bv0( r0 ) __asm__ volatile (		\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"ctc2	$12, $21;"					\
	"ctc2	$13, $22"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ld_intpol_bv1( r0 ) __asm__ volatile (		\
	"lbu	$12, 0( %0 );"					\
	"lbu	$13, 1( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13" )

#define gte_ld_intpol_sv0( r0 ) __asm__ volatile (		\
	"lh	$12, 0( %0 );"					\
	"lh	$13, 2( %0 );"					\
	"lh	$14, 4( %0 );"					\
	"ctc2	$12, $21;"					\
	"ctc2	$13, $22;"					\
	"ctc2	$14, $23"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ld_intpol_sv1( r0 ) __asm__ volatile (		\
	"lh	$12, 0( %0 );"					\
	"lh	$13, 2( %0 );"					\
	"lh	$14, 4( %0 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"mtc2	$14, $11"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldfc( r0 ) __asm__ volatile (			\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 4( %0 );"					\
	"lw	$14, 8( %0 );"					\
	"ctc2	$12, $21;"					\
	"ctc2	$13, $22;"					\
	"ctc2	$14, $23"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

#define gte_ldopv2SV( r0 ) __asm__ volatile (			\
 	"lh	$12, 0( %0 );"					\
 	"lh	$13, 2( %0 );"					\
 	"lh	$14, 4( %0 );"					\
 	"mtc2	$12, $9;"					\
 	"mtc2	$13, $10;"					\
 	"mtc2	$14, $11"					\
 	:							\
 	: "r"( r0 )						\
 	: "$12", "$13", "$14" )

#define gte_ldopv1SV( r0 ) __asm__ volatile (			\
 	"lh	$12, 0( %0 );"					\
 	"lh	$13, 2( %0 );"					\
 	"ctc2	$12, $0;"					\
 	"lh	$14, 4( %0 );"					\
 	"ctc2	$13, $2;"					\
 	"ctc2	$14, $4"					\
 	:							\
 	: "r"( r0 )						\
 	: "$12", "$13", "$14" )

/*
 * Type 2 functions
 */

#define gte_rtps() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000007f" )

#define gte_rtpt() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000000bf" )

#define gte_rt() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000000ff" )

#define gte_rtv0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000013f" )

#define gte_rtv1() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000017f" )

#define gte_rtv2() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000001bf" )

#define gte_rtir() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000001ff" )

#define gte_rtir_sf0() __asm__ volatile (			\
	"nop;"							\
	"nop;"							\
	".word 0x0000023f" )

#define gte_rtv0tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000027f" )

#define gte_rtv1tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000002bf" )

#define gte_rtv2tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000002ff" )

#define gte_rtirtr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000033f" )

#define gte_rtv0bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000037f" )

#define gte_rtv1bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000003bf" )

#define gte_rtv2bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000003ff" )

#define gte_rtirbk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000043f" )

#define gte_ll() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000057f" )

#define gte_llv0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000005bf" )

#define gte_llv1() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000005ff" )

#define gte_llv2() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000063f" )

#define gte_llir() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000067f" )

#define gte_llv0tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000006bf" )

#define gte_llv1tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000006ff" )

#define gte_llv2tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000073f" )

#define gte_llirtr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000077f" )

#define gte_llv0bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000007bf" )

#define gte_llv1bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000007ff" )

#define gte_llv2bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000083f" )

#define gte_llirbk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000087f" )

#define gte_lc() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000009bf" )

#define gte_lcv0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000009ff" )

#define gte_lcv1() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000a3f" )

#define gte_lcv2() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000a7f" )

#define gte_lcir() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000abf" )

#define gte_lcv0tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000aff" )

#define gte_lcv1tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000b3f" )

#define gte_lcv2tr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000b7f" )

#define gte_lcirtr() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000bbf" )

#define gte_lcv0bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000bff" )

#define gte_lcv1bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000c3f" )

#define gte_lcv2bk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000c7f" )

#define gte_lcirbk() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000cbf" )

#define gte_dpcl() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000dff" )

#define gte_dpcs() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000e3f" )

#define gte_dpct() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000e7f" )

#define gte_intpl() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000ebf" )

#define gte_sqr12() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000eff" )

#define gte_sqr0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000f3f" )

#define gte_ncs() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000f7f" )

#define gte_nct() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000fbf" )

#define gte_ncds() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x00000fff" )

#define gte_ncdt() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000103f" )

#define gte_nccs() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000107f" )

#define gte_ncct() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000010bf" )

#define gte_cdp() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000010ff" )

#define gte_cc() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000113f" )

#define gte_nclip() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000117f" )

#define gte_avsz3() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000011bf" )

#define gte_avsz4() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000011ff" )

#define gte_op12() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000123f" )

#define gte_op0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000127f" )

#define gte_gpf12() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000012bf" )

#define gte_gpf0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x000012ff" )

#define gte_gpl12() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000133f" )

#define gte_gpl0() __asm__ volatile (				\
	"nop;"							\
	"nop;"							\
	".word 0x0000137f" )

#define gte_mvmva_core( r0 ) __asm__ volatile (			\
	"nop;"							\
	"nop;"							\
	".word %0"						\
	:							\
	: "g"( r0 ) )

#define gte_mvmva(sf,mx,v,cv,lm) gte_mvmva_core( 0x000013bf |	\
	((sf)<<25) | ((mx)<<23) | ((v)<<21) | ((cv)<<19) | ((lm)<<18))


/*
 * Type 2 functions without nop
 */

#define gte_rtps_b()		__asm__ volatile ( ".word 0x0000007f" )
#define gte_rtpt_b()		__asm__ volatile ( ".word 0x000000bf" )
#define gte_rt_b()		__asm__ volatile ( ".word 0x000000ff" )
#define gte_rtv0_b()		__asm__ volatile ( ".word 0x0000013f" )
#define gte_rtv1_b()		__asm__ volatile ( ".word 0x0000017f" )
#define gte_rtv2_b()		__asm__ volatile ( ".word 0x000001bf" )
#define gte_rtir_b()		__asm__ volatile ( ".word 0x000001ff" )
#define gte_rtir_sf0_b()	__asm__ volatile ( ".word 0x0000023f" )
#define gte_rtv0tr_b()		__asm__ volatile ( ".word 0x0000027f" )
#define gte_rtv1tr_b()		__asm__ volatile ( ".word 0x000002bf" )
#define gte_rtv2tr_b()		__asm__ volatile ( ".word 0x000002ff" )
#define gte_rtirtr_b()		__asm__ volatile ( ".word 0x0000033f" )
#define gte_rtv0bk_b()		__asm__ volatile ( ".word 0x0000037f" )
#define gte_rtv1bk_b()		__asm__ volatile ( ".word 0x000003bf" )
#define gte_rtv2bk_b()		__asm__ volatile ( ".word 0x000003ff" )
#define gte_rtirbk_b()		__asm__ volatile ( ".word 0x0000043f" )
#define gte_ll_b()		__asm__ volatile ( ".word 0x0000057f" )
#define gte_llv0_b()		__asm__ volatile ( ".word 0x000005bf" )
#define gte_llv1_b()		__asm__ volatile ( ".word 0x000005ff" )
#define gte_llv2_b()		__asm__ volatile ( ".word 0x0000063f" )
#define gte_llir_b()		__asm__ volatile ( ".word 0x0000067f" )
#define gte_llv0tr_b()		__asm__ volatile ( ".word 0x000006bf" )
#define gte_llv1tr_b()		__asm__ volatile ( ".word 0x000006ff" )
#define gte_llv2tr_b()		__asm__ volatile ( ".word 0x0000073f" )
#define gte_llirtr_b()		__asm__ volatile ( ".word 0x0000077f" )
#define gte_llv0bk_b()		__asm__ volatile ( ".word 0x000007bf" )
#define gte_llv1bk_b()		__asm__ volatile ( ".word 0x000007ff" )
#define gte_llv2bk_b()		__asm__ volatile ( ".word 0x0000083f" )
#define gte_llirbk_b()		__asm__ volatile ( ".word 0x0000087f" )
#define gte_lc_b()		__asm__ volatile ( ".word 0x000009bf" )
#define gte_lcv0_b()		__asm__ volatile ( ".word 0x000009ff" )
#define gte_lcv1_b()		__asm__ volatile ( ".word 0x00000a3f" )
#define gte_lcv2_b()		__asm__ volatile ( ".word 0x00000a7f" )
#define gte_lcir_b()		__asm__ volatile ( ".word 0x00000abf" )
#define gte_lcv0tr_b()		__asm__ volatile ( ".word 0x00000aff" )
#define gte_lcv1tr_b()		__asm__ volatile ( ".word 0x00000b3f" )
#define gte_lcv2tr_b()		__asm__ volatile ( ".word 0x00000b7f" )
#define gte_lcirtr_b()		__asm__ volatile ( ".word 0x00000bbf" )
#define gte_lcv0bk_b()		__asm__ volatile ( ".word 0x00000bff" )
#define gte_lcv1bk_b()		__asm__ volatile ( ".word 0x00000c3f" )
#define gte_lcv2bk_b()		__asm__ volatile ( ".word 0x00000c7f" )
#define gte_lcirbk_b()		__asm__ volatile ( ".word 0x00000cbf" )
#define gte_dpcl_b()		__asm__ volatile ( ".word 0x00000dff" )
#define gte_dpcs_b()		__asm__ volatile ( ".word 0x00000e3f" )
#define gte_dpct_b()		__asm__ volatile ( ".word 0x00000e7f" )
#define gte_intpl_b()		__asm__ volatile ( ".word 0x00000ebf" )
#define gte_sqr12_b()		__asm__ volatile ( ".word 0x00000eff" )
#define gte_sqr0_b()		__asm__ volatile ( ".word 0x00000f3f" )
#define gte_ncs_b()		__asm__ volatile ( ".word 0x00000f7f" )
#define gte_nct_b()		__asm__ volatile ( ".word 0x00000fbf" )
#define gte_ncds_b()		__asm__ volatile ( ".word 0x00000fff" )
#define gte_ncdt_b()		__asm__ volatile ( ".word 0x0000103f" )
#define gte_nccs_b()		__asm__ volatile ( ".word 0x0000107f" )
#define gte_ncct_b()		__asm__ volatile ( ".word 0x000010bf" )
#define gte_cdp_b()		__asm__ volatile ( ".word 0x000010ff" )
#define gte_cc_b()		__asm__ volatile ( ".word 0x0000113f" )
#define gte_nclip_b()		__asm__ volatile ( ".word 0x0000117f" )
#define gte_avsz3_b()		__asm__ volatile ( ".word 0x000011bf" )
#define gte_avsz4_b()		__asm__ volatile ( ".word 0x000011ff" )
#define gte_op12_b()		__asm__ volatile ( ".word 0x0000123f" )
#define gte_op0_b()		__asm__ volatile ( ".word 0x0000127f" )
#define gte_gpf12_b()		__asm__ volatile ( ".word 0x000012bf" )
#define gte_gpf0_b()		__asm__ volatile ( ".word 0x000012ff" )
#define gte_gpl12_b()		__asm__ volatile ( ".word 0x0000133f" )
#define gte_gpl0_b()		__asm__ volatile ( ".word 0x0000137f" )
#define gte_mvmva_core_b( r0 )	__asm__ volatile (		\
	".word %0"						\
	:							\
	: "g"( r0 ) )
#define gte_mvmva_b(sf,mx,v,cv,lm) gte_mvmva_core_b( 0x000013bf |\
	((sf)<<25) | ((mx)<<23) | ((v)<<21) | ((cv)<<19) | ((lm)<<18))

/*
 * Type 3 functions
 */

#define gte_stsxy( r0 ) __asm__ volatile (			\
	"swc2	$14, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3( r0, r1, r2 ) __asm__ volatile (		\
	"swc2	$12, 0( %0 );"					\
	"swc2	$13, 0( %1 );"					\
	"swc2	$14, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "memory" )

#define gte_stsxy3c( r0 ) __asm__ volatile (			\
	"swc2	$12, 0( %0 );"					\
	"swc2	$13, 4( %0 );"					\
	"swc2	$14, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy2( r0 ) __asm__ volatile (			\
	"swc2	$14, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy1( r0 ) __asm__ volatile (			\
	"swc2	$13, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy0( r0 ) __asm__ volatile (			\
	"swc2	$12, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy01( r0, r1 ) __asm__ volatile (		\
	"swc2	$12, 0( %0 );"					\
	"swc2	$13, 0( %1 )"					\
	:							\
	: "r"( r0 ), "r"( r1 )					\
	: "memory" )

#define gte_stsxy01c( r0 ) __asm__ volatile (			\
	"swc2	$12, 0( %0 );"					\
	"swc2	$13, 4( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_f3( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 12( %0 );"					\
	"swc2	$14, 16( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_g3( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 16( %0 );"					\
	"swc2	$14, 24( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_ft3( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 16( %0 );"					\
	"swc2	$14, 24( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_gt3( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 20( %0 );"					\
	"swc2	$14, 32( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_f4( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 12( %0 );"					\
	"swc2	$14, 16( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_g4( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 16( %0 );"					\
	"swc2	$14, 24( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_ft4( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 16( %0 );"					\
	"swc2	$14, 24( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsxy3_gt4( r0 ) __asm__ volatile (			\
	"swc2	$12, 8( %0 );"					\
	"swc2	$13, 20( %0 );"					\
	"swc2	$14, 32( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stdp( r0 ) __asm__ volatile (			\
	"swc2	$8, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stflg( r0 ) __asm__ volatile (			\
	"cfc2	$12, $31;"					\
	"nop;"							\
	"sw	$12, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "memory" )

#define gte_stflg_4( r0 ) __asm__ volatile (			\
	"cfc2	$12, $31;"					\
	"addi	$13, $0, 4;"					\
	"sll	$13, $13, 16;"					\
	"and	$12, $12, $13;"					\
	"sw	$12, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "memory" )

#define gte_stsz( r0 ) __asm__ volatile (			\
	"swc2	$19, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsz3( r0, r1, r2 ) __asm__ volatile (		\
	"swc2	$17, 0( %0 );"					\
	"swc2	$18, 0( %1 );"					\
	"swc2	$19, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "memory" )

#define gte_stsz4( r0, r1, r2, r3 ) __asm__ volatile (		\
	"swc2	$16, 0( %0 );"					\
	"swc2	$17, 0( %1 );"					\
	"swc2	$18, 0( %2 );"					\
	"swc2	$19, 0( %3 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 )		\
	: "memory" )

#define gte_stsz3c( r0 ) __asm__ volatile (			\
	"swc2	$17, 0( %0 );"					\
	"swc2	$18, 4( %0 );"					\
	"swc2	$19, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsz4c( r0 ) __asm__ volatile (			\
	"swc2	$16, 0( %0 );"					\
	"swc2	$17, 4( %0 );"					\
	"swc2	$18, 8( %0 );"					\
	"swc2	$19, 12( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stszotz( r0 ) __asm__ volatile (			\
	"mfc2	$12, $19;"					\
	"nop;"							\
	"sra	$12, $12, 2;"					\
	"sw	$12, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "memory" )

#define gte_stotz( r0 ) __asm__ volatile (			\
	"swc2	$7, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stopz( r0 ) __asm__ volatile (			\
	"swc2	$24, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stlvl( r0 ) __asm__ volatile (			\
	"swc2	$9, 0( %0 );"					\
	"swc2	$10, 4( %0 );"					\
	"swc2	$11, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stlvnl( r0 ) __asm__ volatile (			\
	"swc2	$25, 0( %0 );"					\
	"swc2	$26, 4( %0 );"					\
	"swc2	$27, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stlvnl0( r0 ) __asm__ volatile (			\
	"swc2	$25, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stlvnl1( r0 ) __asm__ volatile (			\
	"swc2	$26, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stlvnl2( r0 ) __asm__ volatile (			\
	"swc2	$27, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stsv( r0 ) __asm__ volatile (			\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"mfc2	$14, $11;"					\
	"sh	$12, 0( %0 );"					\
	"sh	$13, 2( %0 );"					\
	"sh	$14, 4( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_stclmv( r0 ) __asm__ volatile (			\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"mfc2	$14, $11;"					\
	"sh	$12, 0( %0 );"					\
	"sh	$13, 6( %0 );"					\
	"sh	$14, 12( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_stbv( r0 ) __asm__ volatile (			\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"sb	$12, 0( %0 );"					\
	"sb	$13, 1( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "memory" )

#define gte_stcv( r0 ) __asm__ volatile (			\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"mfc2	$14, $11;"					\
	"sb	$12, 0( %0 );"					\
	"sb	$13, 1( %0 );"					\
	"sb	$14, 2( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_strgb( r0 ) __asm__ volatile (			\
	"swc2	$22, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_strgb3( r0, r1, r2 ) __asm__ volatile (		\
	"swc2	$20, 0( %0 );"					\
	"swc2	$21, 0( %1 );"					\
	"swc2	$22, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "memory" )

#define gte_strgb3_g3( r0 ) __asm__ volatile (			\
	"swc2	$20, 4( %0 );"					\
	"swc2	$21, 12( %0 );"					\
	"swc2	$22, 20( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_strgb3_gt3( r0 ) __asm__ volatile (			\
	"swc2	$20, 4( %0 );"					\
	"swc2	$21, 16( %0 );"					\
	"swc2	$22, 28( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_strgb3_g4( r0 ) __asm__ volatile (			\
	"swc2	$20, 4( %0 );"					\
	"swc2	$21, 12( %0 );"					\
	"swc2	$22, 20( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_strgb3_gt4( r0 ) __asm__ volatile (			\
	"swc2	$20, 4( %0 );"					\
	"swc2	$21, 16( %0 );"					\
	"swc2	$22, 28( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_ReadGeomOffset( r0, r1 ) __asm__ volatile (		\
	"cfc2	$12, $24;"					\
	"cfc2	$13, $25;"					\
	"sra	$12, $12, 16;"					\
	"sra	$13, $13, 16;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 0( %1 )"					\
	:							\
	: "r"( r0 ), "r"( r1 )					\
	: "$12", "$13", "memory" )

#define gte_ReadGeomScreen( r0 ) __asm__ volatile (		\
	"cfc2	$12, $26;"					\
	"nop;"							\
	"sw	$12, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "memory" )

#define gte_ReadRotMatrix( r0 ) __asm__ volatile (		\
	"cfc2	$12, $0;"					\
	"cfc2	$13, $1;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 4( %0 );"					\
	"cfc2	$12, $2;"					\
	"cfc2	$13, $3;"					\
	"cfc2	$14, $4;"					\
	"sw	$12, 8( %0 );"					\
	"sw	$13, 12( %0 );"					\
	"sw	$14, 16( %0 );"					\
	"cfc2	$12, $5;"					\
	"cfc2	$13, $6;"					\
	"cfc2	$14, $7;"					\
	"sw	$12, 20( %0 );"					\
	"sw	$13, 24( %0 );"					\
	"sw	$14, 28( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_sttr( r0 ) __asm__ volatile (			\
	"cfc2	$12, $5;"					\
	"cfc2	$13, $6;"					\
	"cfc2	$14, $7;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 4( %0 );"					\
	"sw	$14, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_ReadLightMatrix( r0 ) __asm__ volatile (		\
	"cfc2	$12, $8;"					\
	"cfc2	$13, $9;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 4( %0 );"					\
	"cfc2	$12, $10;"					\
	"cfc2	$13, $11;"					\
	"cfc2	$14, $12;"					\
	"sw	$12, 8( %0 );"					\
	"sw	$13, 12( %0 );"					\
	"sw	$14, 16( %0 );"					\
	"cfc2	$12, $13;"					\
	"cfc2	$13, $14;"					\
	"cfc2	$14, $15;"					\
	"sw	$12, 20( %0 );"					\
	"sw	$13, 24( %0 );"					\
	"sw	$14, 28( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_ReadColorMatrix( r0 ) __asm__ volatile (		\
	"cfc2	$12, $16;"					\
	"cfc2	$13, $17;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 4( %0 );"					\
	"cfc2	$12, $18;"					\
	"cfc2	$13, $19;"					\
	"cfc2	$14, $20;"					\
	"sw	$12, 8( %0 );"					\
	"sw	$13, 12( %0 );"					\
	"sw	$14, 16( %0 );"					\
	"cfc2	$12, $21;"					\
	"cfc2	$13, $22;"					\
	"cfc2	$14, $23;"					\
	"sw	$12, 20( %0 );"					\
	"sw	$13, 24( %0 );"					\
	"sw	$14, 28( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_stlzc( r0 ) __asm__ volatile (			\
	"swc2	$31, 0( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "memory" )

#define gte_stfc( r0 ) __asm__ volatile (			\
	"cfc2	$12, $21;"					\
	"cfc2	$13, $22;"					\
	"cfc2	$14, $23;"					\
	"sw	$12, 0( %0 );"					\
	"sw	$13, 4( %0 );"					\
	"sw	$14, 8( %0 )"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14", "memory" )

#define gte_mvlvtr() __asm__ volatile (				\
	"mfc2	$12, $25;"					\
	"mfc2	$13, $26;"					\
	"mfc2	$14, $27;"					\
	"ctc2	$12, $5;"					\
	"ctc2	$13, $6;"					\
	"ctc2	$14, $7"					\
	:							\
	:							\
	: "$12", "$13", "$14" )

#define gte_nop() __asm__ volatile (				\
	"nop" )

#define gte_subdvl( r0, r1, r2 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 0( %1 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"sra	$12, $12, 16;"					\
	"sra	$13, $13, 16;"					\
	"subu	$15, $12, $13;"					\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"sw	$15, 4( %2 );"					\
	"subu	$12, $12, $13;"					\
	"sw	$12, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14", "$15", "memory" )

#define gte_subdvd( r0, r1, r2 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 0( %1 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"sra	$12, $12, 16;"					\
	"sra	$13, $13, 16;"					\
	"subu	$15, $12, $13;"					\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"sh	$15, 2( %2 );"					\
	"subu	$12, $12, $13;"					\
	"sh	$12, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14", "$15", "memory" )

#define gte_adddvl( r0, r1, r2 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 0( %1 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"sra	$12, $12, 16;"					\
	"sra	$13, $13, 16;"					\
	"addu	$15, $12, $13;"					\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"sw	$15, 4( %2 );"					\
	"addu	$12, $12, $13;"					\
	"sw	$12, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14", "$15", "memory" )

#define gte_adddvd( r0, r1, r2 ) __asm__ volatile (		\
	"lw	$12, 0( %0 );"					\
	"lw	$13, 0( %1 );"					\
	"mtc2	$12, $9;"					\
	"mtc2	$13, $10;"					\
	"sra	$12, $12, 16;"					\
	"sra	$13, $13, 16;"					\
	"addu	$15, $12, $13;"					\
	"mfc2	$12, $9;"					\
	"mfc2	$13, $10;"					\
	"sh	$15, 2( %2 );"					\
	"addu	$12, $12, $13;"					\
	"sh	$12, 0( %2 )"					\
	:							\
	: "r"( r0 ), "r"( r1 ), "r"( r2 )			\
	: "$12", "$13", "$14", "$15", "memory" )

#define gte_FlipRotMatrixX() __asm__ volatile (			\
	"cfc2	$12, $0;"					\
	"cfc2	$13, $1;"					\
	"sll	$14, $12, 16;"					\
	"sra	$14, $14, 16;"					\
	"subu	$14, $0, $14;"					\
	"sra	$15, $12, 16;"					\
	"subu	$15, $0, $15;"					\
	"sll	$15, $15, 16;"					\
	"sll	$14, $14, 16;"					\
	"srl	$14, $14, 16;"					\
	"or	$14, $14, $15;"					\
	"ctc2	$14, $0;"					\
	"sll	$14, $13, 16;"					\
	"sra	$14, $14, 16;"					\
	"subu	$14, $0, $14;"					\
	"sra	$15, $13, 16;"					\
	"sll	$15, $15, 16;"					\
	"sll	$14, $14, 16;"					\
	"srl	$14, $14, 16;"					\
	"or	$14, $14, $15;"					\
	"ctc2	$14, $1"					\
	:							\
	:							\
	: "$12", "$13", "$14", "$15" )

#define gte_FlipTRX() __asm__ volatile (			\
	"cfc2	$12, $5;"					\
	"nop;"							\
	"subu	$12, $0, $12;"					\
	"ctc2	$12, $5"					\
	:							\
	:							\
	: "$12" )
