#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define FP_POS_Q 4
#define FP_SIN_Q 12

// TODO: Add DEG_TO_FPA macro to convert from degrees to fixed point Q angles.

void func_80096C94(SVECTOR*, MATRIX*); // Custom vwRotMatrix*** ?
void func_80096E78(SVECTOR*, MATRIX*); // Another custom vwRotMatrix*** ?

s32 shRcos(s32);
s32 shRsin(s32);

#endif /* _BODYPROG_MATH_H */
