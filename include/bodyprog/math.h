#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for: Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for: Q8.8 camera AABBs. Q24.8 meters. */
#define Q12_SHIFT      12    /** Used for: Q3.12 alphas. Q19.12 timers, trigonometry. */
#define SIN_LUT_SIZE   4096  /** Number of entries in the sine lookup table. */
#define FP_ANGLE_COUNT 65536 /** Number of fixed-point angles in Q1.15 format. */

/** Squares a value. */
#define SQUARE(val) \
    ((val) * (val))

/** Cubes a value. */
#define CUBE(val) \
    ((val) * (val) * (val))

/** Determines the smaller of two values. */
#define MIN(val0, val1) \
    (((val0) < (val1)) ? (val0) : (val1))

/** Determines the larger of two values. */
#define MAX(val0, val1) \
    (((val0) > (val1)) ? (val0) : (val1))

/** Clamps a value to the range [min, max]. */
#define CLAMP(val, min, max) \
    (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))

/** Computes the absolute difference between two values. */
#define ABS_DIFF(a, b) \
    (((a) - (b)) < 0 ? (b) - (a) : (a) - (b))

/** Converts an integer to a fixed-point Q format. */
#define FP_TO(val, shift) \
	((val) << (shift))

/** Converts a float to a fixed-point Q format. */
#define FP_FLOAT_TO(val, shift) \
    ((val) * FP_TO(1, (shift)))

/** Converts an integer from a fixed-point Q format. */
#define FP_FROM(val, shift) \
	((val) >> (shift))

/** Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY(val0, val1, shift) \
    (((val0) * (val1)) >> (shift))

/** Multiplies an integer by a float converted to fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY_FLOAT(val0, val1, shift) \
    (FP_MULTIPLY((val0), (s32)FP_FLOAT_TO((val1), (shift)), (shift)))

/** Multiplies an integer by a float converted to fixed-point Q format, using 64-bit intermediate via `Math_MulFixed` for higher precision. */
#define FP_MULTIPLY_PRECISE(val0, val1, shift) \
    (Math_MulFixed((val0), FP_FLOAT_TO((val1), (shift)), (shift)))

/** Converts a floating-point alpha in the range [0.0f, 1.0f] to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)FP_FLOAT_TO(alpha, (Q12_SHIFT))

/** Converts a normalized color value in the range [0.0f, 1.0f] to an 8-bit color value in the range [0, 255]. */
#define FP_COLOR(val) \
    (u8)((val) * 255)

/** Converts floating-point degrees to fixed-point angles in Q1.15 format. */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

/** Converts floating-point meters to fixed-point meters in Q24.8 format. */
#define FP_METER(met) \
    (s32)((met) * (1 << (Q8_SHIFT)))

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

void func_80096C94(SVECTOR* vec, MATRIX* mat); // Custom vwRotMatrix[...]?
void func_80096E78(SVECTOR* vec, MATRIX* mat); // Another custom vwRotMatrix[...]?

s32 shRsin(s32 angle);
s32 shRcos(s32 angle);

#endif
