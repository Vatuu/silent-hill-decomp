#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT  4  /** Used for: Q27.4 positions. */
#define Q8_SHIFT  8  /** Used for: Q7.8 camera AABBs. */
#define Q12_SHIFT 12 /** Used for: Q3.12 alphas, angles. Q19.12 meters, timers, trigonometry. */

/** @brief Squares a value. */
#define SQUARE(x) \
    ((x) * (x))

/** @brief Cubes a value. */
#define CUBE(x) \
    ((x) * (x) * (x))

/** @brief Determines the smaller of two values. */
#define MIN(a, b) \
    (((a) < (b)) ? (a) : (b))

/** @brief Determines the larger of two values. */
#define MAX(a, b) \
    (((a) > (b)) ? (a) : (b))

/** @brief Clamps a value to the range `[min, max]`. */
#define CLAMP(x, min, max) \
    (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

/** @brief Computes the absolute sum of two values. */
#define ABS_ADD(a,b) \
    (((a) >= 0) ? ((b) + (a)) : ((b) - (a)))

/** @brief Computes the absolute difference between two values. */
#define ABS_DIFF(a, b) \
    ((((a) - (b)) < 0) ? ((b) - (a)) : ((a) - (b)))

/** @brief Converts an integer to a fixed-point Q format. */
#define FP_TO(x, shift) \
    ((x) << (shift))

/** @brief Converts a float to a fixed-point Q format. */
#define FP_FLOAT_TO(x, shift) \
    (s32)((x) * FP_TO(1, (shift)))

/** @brief Converts an integer from a fixed-point Q format. */
#define FP_FROM(x, shift) \
    ((x) >> (shift))

/** @brief Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY(a, b, shift) \
    (((a) * (b)) >> (shift))

/** @brief Multiplies an integer by a float converted to fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY((aInt), FP_FLOAT_TO((bFlt), (shift)), (shift))

/** @brief Multiplies an integer by a float converted to fixed-point Q format, using 64-bit intermediate via `Math_MulFixed` for higher precision. */
#define FP_MULTIPLY_PRECISE(a, b, shift) \
    Math_MulFixed((a), FP_FLOAT_TO((b), (shift)), (shift))

/** @brief Converts a floating-point alpha in the range `[0.0f, 1.0f]` to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)FP_FLOAT_TO((alpha), (Q12_SHIFT))

/** @brief Converts a normalized color value in the range `[0.0f, 1.0f]` to an 8-bit color value in the range `[0, 255]`. */
#define FP_COLOR(val) \
    (u8)((val) * (FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1))

/** @brief Converts floating-point degrees to fixed-point angles in Q3.12 format. */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((FP_TO(1, Q12_SHIFT)) / 360.0f))

/** @brief Converts floating-point meters to fixed-point meters in Q23.8 format. */
#define FP_METER(met) \
    FP_FLOAT_TO(met, Q8_SHIFT)

// TODO: `FP_METER` above uses an incorrect format and should be phased out. Meters are actually in Q12.19 format.
/** @brief Converts floating-point meters to fixed-point meters in Q23.8 format. */
#define FP_METER_REAL(met) \
    FP_FLOAT_TO(met, Q12_SHIFT)

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

static inline void Math_SVectorSet(SVECTOR* vec, s16 x, s16 y, s16 z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void func_80096C94(SVECTOR* rot, MATRIX* mat); // Custom `vwRotMatrix[...]`?
void func_80096E78(SVECTOR* rot, MATRIX* mat); // Another custom `vwRotMatrix[...]`?

s32 Math_MulFixed(s32 val0, s32 val1, s32 shift);

s32 shRsin(s32 angle);
s32 shRcos(s32 angle);

#endif
