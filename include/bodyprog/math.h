#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

/** Quotient value used for shifting fixed point positions. */
#define FP_POS_Q 4

/** Quotient value used for shifting in sin/cos math. */
#define FP_SIN_Q 12

// TODO: Define DEG_TO_FPA(deg) macro to easily convert from degrees to fixed point Q angles and reduce instances of magic hex values.

void func_80096C94(SVECTOR* vec, MATRIX* mat); // Custom vwRotMatrix...?
void func_80096E78(SVECTOR* vec, MATRIX* mat); // Another custom vwRotMatrix...]?

s32 shRcos(s32);
s32 shRsin(s32);

#endif
