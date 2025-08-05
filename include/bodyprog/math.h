#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#include <limits.h>

#define PI    3.1415927f
#define FP_PI (0x5000 / 2)

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

/** @brief Computes the absolute value. */
#define ABS(x) \
    (((x) < 0) ? -(x) : (x))

/** @brief Computes the absolute sum of two values. */
#define ABS_ADD(a, b) \
    (((a) >= 0) ? ((b) + (a)) : ((b) - (a)))

/** @brief Computes the absolute difference between two values. */
#define ABS_DIFF(a, b) \
    ABS((a) - (b))

/** @brief Checks if two values have different signs. */
#define DIFF_SIGN(a, b) \
    (((a) >= 0 && (b) < 0) || ((a) < 0 && (b) >= 0))

/** @brief Converts an integer to a fixed-point Q format. */
#define FP_TO(x, shift) \
    ((x) << (shift))

/** @brief Converts a float to a fixed-point Q format. */
#define FP_FLOAT_TO(x, shift) \
    (s32)((x) * FP_TO(1, (shift)))

/** @brief Converts an integer from a fixed-point Q format. */
#define FP_FROM(x, shift) \
    ((x) >> (shift))

/** @brief Converts an integer from a scaled fixed-point Q format rounded to the nearest value. */
#define FP_ROUND_SCALED(x, scale, shift) \
    (((x) + ((FP_TO(1, shift) * scale) - 1)) / (FP_TO(1, shift) * scale))

/** @brief Converts an integer from a fixed-point Q format rounded toward 0. */
#define FP_ROUND_TO_ZERO(x, shift) \
    ((s32)(FP_FROM((x), (shift)) + ((u32)(x) >> 31)) >> 1)

/** @brief Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY(a, b, shift) \
    (((a) * (b)) >> (shift))

/** @brief Multiplies an integer by a float converted to fixed-point Q format and converts the result from the fixed-point Q format. */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY((aInt), FP_FLOAT_TO((bFlt), (shift)), (shift))

/** @brief Multiplies an integer by a float converted to fixed-point Q format, using 64-bit intermediate via `Math_MulFixed` for higher precision. */
#define FP_MULTIPLY_PRECISE(a, b, shift) \
    Math_MulFixed((a), FP_FLOAT_TO((b), (shift)), (shift))

/** @brief Computes the dot product of the first column of a matrix with a vector in Q17.15 format. */
#define FP_MULTIPLY_MATRIX(mat, vec)    \
    (s32)((((mat).m[0][0] * (vec).vx) + \
           ((mat).m[1][0] * (vec).vy) + \
           ((mat).m[2][0] * (vec).vz)) >> 17)

/** @brief Converts a floating-point alpha in the range `[0.0f, 1.0f]` to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)FP_FLOAT_TO((alpha), Q12_SHIFT)

/** @brief Converts a normalized color value in the range `[0.0f, 1.0f]` to an 8-bit color value in the range `[0, 255]`. */
#define FP_COLOR(val) \
    (u8)((val) * (FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1))

/** @brief Converts floating-point degrees to fixed-point degrees in Q3.12 format. */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((FP_TO(1, Q12_SHIFT)) / 360.0f))

/** @brief Converts floating-point radians in the range `[-PI, PI]` to fixed-point radians in the range `[0, 0x5000]`. */
#define FP_RADIAN(rad)                                                                \
    (s32)(((((rad) < 0.0f) ? (PI + (PI - ABS(rad))) : (rad)) * ((float)FP_PI / PI)) * \
          (((rad) < 0.0f || (rad) >= PI) ? 1.0f : 2.0f))

/** @brief Converts floating-point meters to fixed-point meters in Q12.19 format. */
#define FP_METER(met) \
    FP_FLOAT_TO((met), Q12_SHIFT)

/** @brief Converts floating-point seconds to fixed-point seconds in Q12.19 format. */
#define FP_TIME(sec) \
    FP_FLOAT_TO((sec), Q12_SHIFT)

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

static inline void Math_SVectorSet(SVECTOR* vec, s16 x, s16 y, s16 z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

static inline void Math_Vector3Zero(VECTOR3* vec)
{
    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;
}

static inline void Math_Vector3Set(VECTOR3* vec, s32 x, s32 y, s32 z)
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
