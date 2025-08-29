#ifndef _BODYPROG_MATH_FIXED_POINT_H
#define _BODYPROG_MATH_FIXED_POINT_H

#include "types.h"
#include "bodyprog/math/constants.h"

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

/** @brief Converts a floating-point value to a fixed-point value in Q19.12.
 *
 * @param val `float` to convert.
 * @return `val` converted to fixed-point Q19.12.
 */
#define Q19_12(val) \
    (s32)FP_FLOAT_TO((val), Q12_SHIFT)

#define Q19_12_TO_Q3_12(val) \
    (s32)(((val) >> 4))

#define Q3_12(val) \
    (s16)FP_FLOAT_TO((val), Q12_SHIFT)

#define Q23_8(val) \
    (s32)FP_FLOAT_TO((val), Q8_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q7.8.
 *
 * @param val `float` to convert.
 * @return `val` converted to fixed-point Q7.8.
 */
#define Q7_8(val) \
    (s16)FP_FLOAT_TO((val), Q8_SHIFT)

#define Q0_8(val) \
    (u8)FP_FLOAT_TO((val), Q8_SHIFT)

#endif
