#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for Q8.8 range limits. */
#define Q12_SHIFT      12    /** Used for Q19.12 trigonometry. */
#define FP_ANGLE_COUNT 65536 /** Number of possible fixed-point angles in Q1.15 format. */

/** Converts a value to a fixed-point Q format. */
#define TO_FIXED(value, shift) \
	((value) << (shift))

/** Converts a value from a fixed-point Q format. */
#define FROM_FIXED(value, shift) \
	((value) >> (shift))

/** Converts degrees to fixed-point angles in Q1.15 format (used at Q4.12 resolution). */
#define DEG_TO_FPA(deg) \
	(s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

/** Clamps a value to the range [min, max]. */
#define CLAMP(value, min, max) \
    (((value) < (min)) ? (min) : (((value) > (max)) ? (max) : (value)))

void func_80096C94(SVECTOR* vec, MATRIX* mat); // Custom vwRotMatrix...?
void func_80096E78(SVECTOR* vec, MATRIX* mat); // Another custom vwRotMatrix...]?

s32 shRsin(s32);
s32 shRcos(s32);

#endif
