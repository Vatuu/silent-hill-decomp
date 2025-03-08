/*
 * $PSLibId: Run-time Library Release 4.3$
 */

/*
 *	Macro definitions of DMPSX version 3
 *	inline_o.h
 *	Copyright(C) 1996, Sony Computer Entertainment Inc.
 *	All rights reserved.
 */

/*
 * Type 1 functions
 */

#define gte_ldv0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv2(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $4,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $5,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,4($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $4,($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $5,4($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv3c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $4,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $5,20($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv3c_vertc(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $4,24($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $5,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv01(r1,r2) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,4($13)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldv01c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $0,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $2,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $3,12($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldrgb(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $6,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldrgb3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $20,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $21,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $22,($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $6,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldrgb3c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $20,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $21,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $22,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $6,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldlv0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("or    $13,$13,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $1,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldlvl(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $9,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $10,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $11,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $14,2($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $15,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldbv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldcv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $15,2($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldclmv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $14,6($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lhu   $15,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lddp(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$8": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsxy0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$12": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsxy1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$13": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsxy2(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$14": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsxy3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$12": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$13": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsxy3c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $13,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $14,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsz3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$17": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$18": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$19": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsz4(r1,r2,r3,r4) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $15,%0": :"r"(r4):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$17": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$18": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $15,$19": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldopv1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$2": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$4": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldopv2(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $11,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $9,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $10,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldlzc(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$30": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetRGBcd(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lwc2  $6,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldbkdir(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$15": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetBackColor(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $12,$12,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $13,$13,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$15": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldfcdir(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$23": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetFarColor(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $12,$12,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $13,$13,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$23": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetGeomOffset(r1,r2) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $12,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $13,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$24": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$25": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetGeomScreen(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$26": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsvrtrow0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$1": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetRotMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$1": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$2": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$3": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$4": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsvllrow0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$8": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$9": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetLightMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$8": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$11": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$12": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldsvlcrow0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$17": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetColorMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$17": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$18": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$19": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$20": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetTransMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,24($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,28($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$7": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldtr(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$7": : :"$12","$13","$14","$15","memory"); \
}
#define gte_SetTransVector(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$7": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_uv0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_uv1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_bv0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_bv1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lbu   $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_sv0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $14,2($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $15,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$23": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ld_intpol_sv1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $14,2($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lh    $15,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ldfc(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $15,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $15,$23": : :"$12","$13","$14","$15","memory"); \
}

/*
 * Type 2 functions
 */

#define gte_rtps() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000007f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtpt() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000000bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rt() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000000ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000013f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv1() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000017f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv2() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000001bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtir() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000001ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtir_sf0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000023f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv0tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000027f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv1tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000002bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv2tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000002ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtirtr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000033f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv0bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000037f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv1bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000003bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtv2bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000003ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_rtirbk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000043f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ll() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000057f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000005bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv1() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000005ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv2() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000063f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llir() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000067f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv0tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000006bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv1tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000006ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv2tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000073f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llirtr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000077f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv0bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000007bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv1bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000007ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llv2bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000083f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_llirbk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000087f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lc() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000009bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000009ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv1() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000a3f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv2() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000a7f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcir() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000abf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv0tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000aff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv1tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000b3f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv2tr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000b7f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcirtr() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000bbf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv0bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000bff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv1bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000c3f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcv2bk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000c7f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_lcirbk() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000cbf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_dpcl() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000dff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_dpcs() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000e3f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_dpct() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000e7f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_intpl() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000ebf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_sqr12() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000eff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_sqr0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000f3f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ncs() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000f7f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_nct() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000fbf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ncds() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x00000fff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ncdt() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000103f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_nccs() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000107f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ncct() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000010bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_cdp() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000010ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_cc() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000113f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_nclip() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000117f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_avsz3() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000011bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_avsz4() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000011ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_op12() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000123f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_op0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000127f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_gpf12() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000012bf": : :"$12","$13","$14","$15","memory"); \
}
#define gte_gpf0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x000012ff": : :"$12","$13","$14","$15","memory"); \
}
#define gte_gpl12() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000133f": : :"$12","$13","$14","$15","memory"); \
}
#define gte_gpl0() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile (".word 0x0000137f": : :"$12","$13","$14","$15","memory"); \
}

/*
 * Type 3 functions
 */

#define gte_stsxy(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy2(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy01(r1,r2) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,($13)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy01c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_f3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,16($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_g3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,24($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_ft3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,24($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_gt3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,32($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_f4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,16($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_g4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,24($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_ft4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,24($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsxy3_gt4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $12,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $14,32($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stdp(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $8,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stflg(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$31": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stflg_4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$31": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("addi  $14,$0,4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("and   $13,$13,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsz(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $19,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsz3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $17,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $18,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $19,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsz4(r1,r2,r3,r4) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $15,%0": :"r"(r4):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $16,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $17,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $18,($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $19,($15)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsz3c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $17,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $18,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $19,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsz4c(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $16,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $17,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $18,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $19,12($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stszotz(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$19": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $13,$13,2": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stotz(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $7,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stopz(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $24,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlvl(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $9,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $10,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $11,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlvnl(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $25,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $26,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $27,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlvnl0(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $25,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlvnl1(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $26,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlvnl2(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $27,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stsv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $14,2($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $15,4($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stclmv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $14,6($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $15,12($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stbv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sb    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sb    $14,1($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stcv(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $14,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $15,$11": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sb    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sb    $14,1($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sb    $15,2($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb3(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $20,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $21,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb3_g3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $20,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $21,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,20($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb3_gt3(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $20,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $21,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb3_g4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $20,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $21,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,20($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_strgb3_gt4(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $20,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $21,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $22,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ReadGeomOffset(r1,r2) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$24": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$25": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $15,$15,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,($13)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ReadGeomScreen(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$26": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ReadRotMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$1": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$2": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$3": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$4": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$7": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,24($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_sttr(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$7": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ReadLightMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$8": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$11": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$12": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$15": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,24($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_ReadColorMatrix(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$17": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$18": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$19": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$20": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,8($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,12($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,16($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$23": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,20($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,24($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,28($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stlzc(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("swc2  $31,($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_stfc(r1) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$21": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $14,$22": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $15,$23": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $13,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $14,4($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,8($12)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_mvlvtr() { \
  __asm__ volatile ("mfc2  $12,$25": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$26": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $14,$27": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $13,$6": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$7": : :"$12","$13","$14","$15","memory"); \
}
#define gte_nop() { \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
}
#define gte_subdvl(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $12,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $13,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $15,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,4($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $12,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $12,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_subdvd(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $12,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $13,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $15,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $15,2($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $12,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $12,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_adddvl(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $12,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $13,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("addu  $15,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $15,4($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("addu  $12,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sw    $12,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_adddvd(r1,r2,r3) { \
  __asm__ volatile ("move  $12,%0": :"r"(r1):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $13,%0": :"r"(r2):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("move  $14,%0": :"r"(r3):"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $12,($12)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("lw    $13,($13)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mtc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $12,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $13,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("addu  $15,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $12,$9": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("mfc2  $13,$10": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $15,2($14)": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("addu  $12,$12,$13": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sh    $12,($14)": : :"$12","$13","$14","$15","memory"); \
}
#define gte_FlipRotMatrixX() { \
  __asm__ volatile ("cfc2  $12,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("cfc2  $13,$1": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $14,$0,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $15,$12,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $15,$0,$15": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $15,$15,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("srl   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("or    $14,$14,$15": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$0": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $14,$0,$14": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sra   $15,$13,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $15,$15,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("sll   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("srl   $14,$14,16": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("or    $14,$14,$15": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $14,$1": : :"$12","$13","$14","$15","memory"); \
}
#define gte_FlipTRX() { \
  __asm__ volatile ("cfc2  $12,$5": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("nop   ": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("subu  $12,$0,$12": : :"$12","$13","$14","$15","memory"); \
  __asm__ volatile ("ctc2  $12,$5": : :"$12","$13","$14","$15","memory"); \
}
