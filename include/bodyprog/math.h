#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#include <limits.h>

#define PI    3.1415927f
#define FP_PI (0x5000 / 2)

#define Q4_SHIFT  4  /** Used for: Q27.4 positions. */
#define Q8_SHIFT  8  /** Used for: Q7.8 camera AABBs. */
#define Q12_SHIFT 12 /** Used for: Q3.12 alphas, angles. Q19.12 meters, timers, trigonometry. */

/** @brief Squares a value.
 *
 * @param x Value to be squared.
 * @return `x` squared.
 */
#define SQUARE(x) \
    ((x) * (x))

/** @brief Cubes a value.
 *
 * @param x Value to be cubed.
 * @return `x` cubed.
 */
#define CUBE(x) \
    ((x) * (x) * (x))

/** @brief Determines the smaller of two values.
 *
 * @param a First value.
 * @param b Second value.
 * @return `true` if `a` is smaller than `b`, `false` otherwise.
 */
#define MIN(a, b) \
    (((a) < (b)) ? (a) : (b))

/** @brief Determines the larger of two values.
 *
 * @param a First value.
 * @param b Second value.
 * @return `true` if `a` is larger than `b`, `false` otherwise.
 */
#define MAX(a, b) \
    (((a) > (b)) ? (a) : (b))

/** @brief Clamps a value to the range `[min, max]`.
 *
 * @param x Value to be clamped.
 * @param min Lower range.
 * @param max Upper range.
 * @return `x` clamped to the range `[min, max]`.
 */
#define CLAMP(x, min, max) \
    (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

/** @brief Computes the absolute value.
 *
 * @param x Value.
 * @return Absolute value of `x`.
 */
#define ABS(x) \
    (((x) < 0) ? -(x) : (x))

/** @brief Computes the absolute value of an `s32` by shifting. */
#define ABS_32(x) \
    (((x) ^ ((x) >> 31)) - ((x) >> 31))

/** @brief Computes the absolute sum of two values.
 *
 * @param a First value.
 * @param b Second value.
 * @return Absolute sum of `a` and `b`.
 */
#define ABS_ADD(a, b) \
    (((a) >= 0) ? ((b) + (a)) : ((b) - (a)))

/** @brief Computes the absolute difference between two values.
 *
 * @param a First value.
 * @param b Second value.
 * @return Absolute difference between `a` and `b`.
 */
#define ABS_DIFF(a, b) \
    ABS((a) - (b))

/** @brief Checks if two values have different signs.
 *
 * @param a First value.
 * @param b Second value.
 * @return `true` if `a` and `b` have different signs, `false` otherwise.
 */
#define DIFF_SIGN(a, b) \
    (((a) >= 0 && (b) < 0) || ((a) < 0 && (b) >= 0))

/** @brief Converts an integer to a fixed-point Q format.
 *
 * @param x `int` to convert.
 * @param shift Fixed-point shift.
 * @return `x` converted to fixed-point.
 */
#define FP_TO(x, shift) \
    ((x) << (shift))

/** @brief Converts a float to a fixed-point Q format.
 *
 * @param x `float` to convert.
 * @param shift Fixed-point shift.
 * @return `x` converted to fixed-point (`s32`).
 */
#define FP_FLOAT_TO(x, shift) \
    (s32)((x) * FP_TO(1, (shift)))

/** @brief Converts a floating-point value to a fixed-point value in Q19.12 format.
 *
 * @param val `float` to convert.
 * @return `val` converted to fixed-point Q19.12.
 */
#define Q19_12(val) \
    FP_FLOAT_TO((val), Q12_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q7.8 format.
 *
 * @param val `float` to convert.
 * @return `val` converted to fixed-point Q7.8.
 */
#define Q7_8(val) \
    FP_FLOAT_TO((val), Q8_SHIFT)

/** @brief Converts an integer from a fixed-point Q format.
 *
 * @param x `int` to convert.
 * @param shift Fixed-point shift.
 * @return `x` converted from fixed-point.
 */
#define FP_FROM(x, shift) \
    ((x) >> (shift))

/** @brief Converts an integer from a scaled fixed-point Q format rounded to the nearest value.
 *
 * @param x Fixed-point value to convert.
 * @param scale Fixed-point scale.
 * @param shift Fixed-point shift.
 * @return `x` rounded and converted from fixed-point.
 */
#define FP_ROUND_SCALED(x, scale, shift) \
    (((x) + ((FP_TO(1, (shift)) * (scale)) - 1)) / (FP_TO(1, (shift)) * (scale)))

/** @brief Converts an integer from fixed-point Q format rounded toward 0.
 *
 * @param x Fixed-point value to convert.
 * @param shift Fixed-point shift.
 * @return `x` rounded toward 0 and converted from fixed-point.
 */
#define FP_ROUND_TO_ZERO(x, shift) \
    ((s32)(FP_FROM((x), (shift)) + ((u32)(x) >> 31)) >> 1)

/** @brief Multiplies two integers in fixed-point Q format and converts the result from the fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY(a, b, shift) \
    (((a) * (b)) >> (shift))

/** @brief Multiplies two integers in fixed-point Q format and converts the result from the fixed-point Q format,
 * using 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_PRECISE(a, b, shift) \
    (((s64)(a) * (s64)(b)) >> (shift))

/** @brief Multiplies an integer in fixed-point Q format by a float converted to fixed-point Q format,
 * then converts the result back from the fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY((aInt), FP_FLOAT_TO((bFlt), (shift)), (shift))

/** @brief Multiplies an integer in fixed-point Q format by a float converted to fixed-point Q format,
 * then converts the result back from the fixed-point Q format using a 64-bit intermediate for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT_PRECISE(aInt, bFlt, shift) \
    FP_MULTIPLY((s64)(aInt), FP_FLOAT_TO((bFlt), (shift)), (shift))

/** @brief Converts a floating-point alpha in the range `[0.0f, 1.0f]` to a fixed-point alpha in Q3.12 format, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @param alpha Alpha as `float`.
 * @return Fixed-point alpha in Q3.12, range `[0, 4096]` (`s16`).
 */
#define FP_ALPHA(alpha) \
    (s16)FP_FLOAT_TO((alpha), Q12_SHIFT)

/** @brief Normalizes a fixed-point alpha in Q3.12 format to the range `[0, 4095]`.
 *
 * @param alpha Fixed-point alpha.
 * @return Normalized fixed-point alpha in Q3.12, range `[0, 4095]`.
 */
#define FP_ALPHA_NORM(alpha) \
    ((alpha) & 0xFFF)

// TODO: Maybe not appropriate for this project since it often results in ugly floats.
/** @brief Converts a normalized color value in the range `[0.0f, 1.0f]` to an 8-bit color value in the range `[0, 255]`.
 * Mapping is direct.
 *
 * @param val Color component as `float`.
 * @return Fixed-point color component, range `[0, 255]`.
 */
#define FP_COLOR(val) \
    (u8)((val) * 0xFF)

/** @brief Converts floating-point degrees to unsigned fixed-point degrees in Q3.12 format, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @note 1 degree = 11.377778 units.
 *
 * @param deg Degrees as `float`.
 * @return Unsigned fixed-point degrees in Q3.12, range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((float)FP_TO(1, Q12_SHIFT) / 360.0f))

/** @brief Converts floating-point degrees to unsigned fixed-point degrees in Q3.12 format, packed range `[0, 256]`.
 * Mapping is direct.
 *
 * @note 1 degree = 0.711111 units.
 *
 * @param deg Degrees as `float`.
 * @return Unsigned fixed-point degrees in Q3.12, packed range `[0, 256]` (`s16`).
 */
#define FP_ANGLE_PACKED(deg) \
    (s16)((deg) * ((float)FP_TO(1, Q8_SHIFT) / 360.0f))

/** @brief Converts unsigned fixed-point degrees in Q3.12, packed range `[0, 256]` to
 * unsigned fixed-point degrees in Q3.12, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @param packedDeg Packed unsigned fixed-point degrees in Q3.12, range `[0, 256]`.
 * @return Unsigned fixed-point degrees converted to range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE_PACKED_FROM(packedDeg) \
    (s16)((packedDeg) * 16)

/** @brief Normalizes unsigned fixed-point degrees in Q3.12 format to the signed range `[-2048, 2047]`.
 *
 * @param angle Unsigned fixed-point degrees in Q3.12, range `[0, 4095]`.
 * @return Signed fixed-point degrees wrapped to the range `[-2048, 2047]` (`s16`).
 */
#define FP_ANGLE_NORM_S(angle) \
    (((angle) << 20) >> 20)

/** @brief Normalizes signed fixed-point degrees in Q3.12 format to the unsigned range `[0, 4095]`.
 *
 * @param angle Signed fixed-point degrees in Q3.12, range `[-2048, 2047]`.
 * @return Unsigned fixed-point degrees wrapped to the range `[0, 4095]` (`s16`).
 */
#define FP_ANGLE_NORM_U(angle) \
    ((angle) & (FP_ANGLE(360.0f) - 1))

/** @brief Converts floating-point radians in the range `[-PI, PI]` to fixed-point radians in the range `[0, 0x5000]`.
 * Mapping is direct.
 *
 * @note Pi = 10240 units.
 *
 * @param rad Radians as `float`.
 * @return Fixed-point radians, range `[0, 0x5000]` (`s32`).
 */
#define FP_RADIAN(rad)                                                                \
    (s32)(((((rad) < 0.0f) ? (PI + (PI - ABS(rad))) : (rad)) * ((float)FP_PI / PI)) * \
          (((rad) < 0.0f || (rad) >= PI) ? 1.0f : 2.0f))

/** @brief Converts floating-point meters to fixed-point meters in Q19.12 format.
 *
 * @note 1 meter = 4096 units.
 *
 * @param met Meters as `float`.
 * @return Fixed-point meters in Q19.12 (`s32`).
 */
#define FP_METER(met) \
    FP_FLOAT_TO((met), Q12_SHIFT)

/** @brief Converts floating-point seconds to fixed-point seconds in Q19.12 format.
 *
 * @note 1 second == 4096 units.
 *
 * @param sec Seconds as `float`.
 * @return Fixed-point seconds in Q19.12 (`s32`).
 */
#define FP_TIME(sec) \
    FP_FLOAT_TO((sec), Q12_SHIFT)

/** @brief Multiplies an integer in fixed-point Q format by a float converted to fixed-point Q format,
 * then converts the result back from the fixed-point Q format using a 64-bit intermediate via
 * `Math_MulFixed` for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
#define Math_MultiplyFloatPrecise(a, b, shift) \
    Math_MulFixed((a), FP_FLOAT_TO((b), (shift)), (shift))

/** @brief Computes the dot product(?) of the first column of a matrix with a vector in Q17.15(?) format.
 *
 * @param mat Input matrix.
 * @param vec Input vector.
 * @return Dot product(?).
 */
#define Math_MultiplyMatrix(mat, vec)   \
    (s32)((((mat).m[0][0] * (vec).vx) + \
           ((mat).m[1][0] * (vec).vy) + \
           ((mat).m[2][0] * (vec).vz)) >> 17)

/** @brief Sets an `VECTOR3`'s components to `float`s converted to a fixed-point format.
 *
 * @param vec Output vector.
 * @param x X component as `float`.
 * @param y Y component as `float`.
 * @param z Z component as `float`.
 * @param shift Fixed-point shift.
 */
#define Math_Vector3f(vec, x, y, z, shift) \
    Math_Vector3Set(vec, FP_FLOAT_TO(x, shift), FP_FLOAT_TO(y, shift), FP_FLOAT_TO(z, shift))

/** @brief Normalizes unsigned fixed-point degrees in Q3.12 format to the signed range `[-2048, 2047]`.
 * Thin wrapper for `FP_ANGLE_NORM_S`.
 *
 * @param angle Unsigned fixed-point degrees in Q3.12, range `[0, 4096]`.
 * @return Fixed-point degrees wrapped to the range `[-2048, 2047]` (`s16`).
 */
static inline s16 Math_AngleNormalize(s32 angle)
{
    return FP_ANGLE_NORM_S(angle);
}

/** @brief Clears an `SVECTOR`'s components.
 *
 * @param vec Output vector.
 */
static inline void Math_SVectorZero(SVECTOR* vec)
{
    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;
}

/** @brief Sets an `SVECTOR`'s components.
 *
 * @param vec Output vector.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 */
static inline void Math_SVectorSet(SVECTOR* vec, s16 x, s16 y, s16 z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

/** @brief Clears a `VECTOR3`'s components.
 *
 * @param vec Output vector.
 */
static inline void Math_Vector3Zero(VECTOR3* vec)
{
    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;
}

/** @brief Sets a `VECTOR3`'s components.
 *
 * @param vec Output vector.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 */
static inline void Math_Vector3Set(VECTOR3* vec, s32 x, s32 y, s32 z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void func_80096C94(SVECTOR* rot, MATRIX* mat); // Custom `vwRotMatrix[...]`?
void func_80096E78(SVECTOR* rot, MATRIX* mat); // Another custom `vwRotMatrix[...]`?

/** @brief Multiplies two integers in fixed-point Q format and converts the result from the fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
s32 Math_MulFixed(s32 a, s32 b, s32 shift);

// NOTE: Matched on decomp.me.
/** @brief Computes the sine in Q19.12 format of degrees in Q3.12 format.
 *
 * Possible original name: `shRsin`
 *
 * @param angle Fixed-point degrees in Q3.12, range `[0, 4096]`.
 * @return Sine in Q19.12 format, range `[0, 4096]`.
 */
s32 Math_Sin(s32 angle);

// NOTE: Matched on decomp.me.
/** @brief Computes the cosine in Q19.12 format of degrees in Q3.12 format.
 *
 * Possible original name: `shRcos`
 *
 * @param angle Fixed-point degrees in Q3.12, range `[0, 4096]`.
 * @return Cosine in Q19.12 format, range `[0, 4096]`.
 */
s32 Math_Cos(s32 angle);

MATRIX* shRotMatrixZ(s32, MATRIX*);

#endif
