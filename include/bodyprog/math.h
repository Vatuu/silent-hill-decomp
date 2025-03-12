#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for Q8.8 range limits. */
#define Q12_SHIFT      12    /** Used for Q19.12 trigonometry. */
#define FP_ANGLE_COUNT 65536 /** Number of possible fixed-point angles in Q1.15 format. */

/** Multiplies two integers and converts the result from a fixed-point Q format. */
#define MUL_FIXED(val0, val1, shift) \
    (((val0) * (val1)) >> (shift))

/** Converts an integer to a fixed-point Q format. */
#define TO_FIXED(val, shift) \
	((val) << (shift))

/** Converts an integer from a fixed-point Q format. */
#define FROM_FIXED(val, shift) \
	((val) >> (shift))

/** Converts degrees to fixed-point angles in Q1.15 format (used at Q4.12 resolution). */
#define DEG_TO_FPA(deg) \
	(s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

/** Clamps a value to the range [min, max]. */
#define CLAMP(val, min, max) \
    (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))

void func_80096C94(SVECTOR* vec, MATRIX* mat); // Custom vwRotMatrix...?
void func_80096E78(SVECTOR* vec, MATRIX* mat); // Another custom vwRotMatrix...]?

s32 shRsin(s32);
s32 shRcos(s32);

#endif
