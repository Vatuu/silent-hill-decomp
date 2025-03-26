#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for: Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for: Q8.8 range limits. Q24.8 tile units. */
#define Q12_SHIFT      12    /** Used for: Q3.12 alphas. Q19.12 timers, trigonometry. */
#define SIN_LUT_SIZE   4096  /** Number of entries in the sine lookup table. */
#define FP_ANGLE_COUNT 65536 /** Number of fixed-point angles in Q1.15 format. */

/** Returns the larger of two values. */
#define MAX(val0, val1) \
    (((val0) > (val1)) ? (val0) : (val1))

/** Returns the smaller of two values. */
#define MIN(val0, val1) \
    (((val0) < (val1)) ? (val0) : (val1))

/** Clamps a value to the range [min, max]. */
#define CLAMP(val, min, max) \
    (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))

/** Converts an integer to a fixed-point Q format. */
#define FP_TO(val, shift) \
	((val) << (shift))

/** Converts an integer from a fixed-point Q format. */
#define FP_FROM(val, shift) \
	((val) >> (shift))

/** Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY(val0, val1, shift) \
    (((val0) * (val1)) >> (shift))

/** Converts a floating-point alpha in the range [0.0f, 1.0f] to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)((alpha) * (1 << (Q12_SHIFT)))

/** Converts floating-point degrees to fixed-point angles in Q1.15 format. */
#define FP_ANGLE(deg) \
	(s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

/** Converts floating-point tile units to fixed-point world units in Q12.8 format. */
#define FP_TILE(val) \
    (s32)((val) * (1 << (Q8_SHIFT)))

static inline s16 shAngleRegulate(s32 angle)
{
    return (angle << 20) >> 20;
}

static inline void Math_SVectorZero(SVECTOR* vec)
{
    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;
}

static inline void Math_Vector3Zero(VECTOR3* vec)
{
    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;
}

void func_80096C94(SVECTOR* vec, MATRIX* mat); // Custom vwRotMatrix...?
void func_80096E78(SVECTOR* vec, MATRIX* mat); // Another custom vwRotMatrix...]?

s32 shRsin(s32 angle);
s32 shRcos(s32 angle);

#endif
