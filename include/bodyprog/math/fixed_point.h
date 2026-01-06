#ifndef _BODYPROG_MATH_FIXEDPOINT_H
#define _BODYPROG_MATH_FIXEDPOINT_H

#include "types.h"

#include "bodyprog/math/arithmetic.h"
#include "bodyprog/math/constants.h"

// =====================
// ARITHMETIC AND UTILS
// =====================

/** @brief Converts an integer to a fixed-point Q format.
 *
 * @note Deprecated.
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
#define TO_FIXED(x, shift) \
    (s32)((x) * (1 << (shift)))

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
    (((x) + ((TO_FIXED(1.0f, shift) * (scale)) - 1)) / (TO_FIXED(1.0f, shift) * (scale)))

/** @brief Converts an integer from a fixed-point Q format rounded toward 0.
 *
 * @param x Fixed-point value to convert.
 * @param shift Fixed-point shift.
 * @return `x` rounded toward 0 and converted from fixed-point.
 */
#define FP_ROUND_TO_ZERO(x, shift) \
    ((s32)(FP_FROM(x, shift) + ((u32)(x) >> 31)) >> 1)

/** @brief Multiplies two integers in a fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Fixed-point product of `a` and `b`.
 */
#define FP_MULTIPLY(a, b, shift) \
    (((a) * (b)) >> (shift))

/** @brief Multiplies two integers in a fixed-point Q format, using 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Precise fixed-point product of `a` and `b`.
 */
#define FP_MULTIPLY_PRECISE(a, b, shift) \
    ((s32)(((s64)(a) * (s64)(b)) >> (shift)))

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to a fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Fixed-point product of `a` and `b`.
 */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY(aInt, TO_FIXED(bFlt, shift), shift)

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to fixed-point Q format,
 * using a 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT_PRECISE(aInt, bFlt, shift) \
    FP_MULTIPLY((s64)(aInt), (s64)TO_FIXED(bFlt, shift), shift)

/** @brief Squares a fixed-point value, using 64-bit intermediates for higher precision.
 *
 * @param x Fixed-point value to be squared.
 * @param shift Fixed-point shift.
 * @return Fixed-point square of `x`.
 */
#define FP_SQUARE_PRECISE(x, shift) \
    FP_MULTIPLY_PRECISE(x, x, shift)

/** @brief Computes the square 2D distance between two positions in Q19.12 fixed-point,
 * using Q21.8 fixed-point intermediates to avoid overflow.
 *
 * @param from First position.
 * @param to Second position.
 * @param return 2D distance between two positions.
 */
#define Q12_2D_DISTANCE_SQR(from, to)         \
    (SQUARE(Q12_TO_Q8((to).vx - (from).vx)) + \
     SQUARE(Q12_TO_Q8((to).vz - (from).vz)))

/** @brief Multiplies two integers in Q*.12 fixed-point.
 *
 * @param a First Q*.12 fixed-point factor.
 * @param b Second Q*.12 fixed-point factor.
 * @return Q*.12 product of `a` and `b`.
 */
#define Q12_MULT(a, b) \
    FP_MULTIPLY(a, b, Q12_SHIFT)

/** @brief Multiplies two integers in Q*.12 fixed-point, using 64-bit intermediates for higher precision.
 *
 * @param a First Q*.12 fixed-point factor.
 * @param b Second Q*.12 fixed-point factor.
 * @return Precise Q*.12 product of `a` and `b`.
 */
#define Q12_MULT_PRECISE(a, b) \
    FP_MULTIPLY_PRECISE(a, b, Q12_SHIFT)

/** @brief Multiplies an integer in Q*.12 fixed-point by a float converted to Q*.12 fixed-point.
 *
 * @param a First Q*.12 fixed-point factor.
 * @param b Second floating-point factor.
 * @return Q*.12 product of `a` and `b`.
 */
#define Q12_MULT_FLOAT(a, b) \
    FP_MULTIPLY_FLOAT(a, b, Q12_SHIFT)

/** @brief Multiplies an integer in Q*.12 fixed-point by a float converted to Q*.12 fixed-point,
 * using 64-bit intermediates for higher precision.
 *
 * @param a First Q*.12 fixed-point factor.
 * @param b Second floating-point factor.
 * @return Precise Q*.12 product of `a` and `b`.
 */
#define Q12_MULT_FLOAT_PRECISE(a, b) \
    FP_MULTIPLY_FLOAT_PRECISE(a, b, Q12_SHIFT)

// ==================================
// RAW Q FORMAT CONVERSION AND UTILS
// ==================================

/** @brief Converts a floating-point value to Q*.4 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.4 fixed-point.
 */
#define Q4(x) \
    TO_FIXED(x, Q4_SHIFT)

/** @brief Converts a floating-point value to Q*.6 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.6 fixed-point.
 */
#define Q6(x) \
    TO_FIXED(x, Q6_SHIFT)

/** @brief Converts a floating-point value to Q*.8 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.8 fixed-point.
 */
#define Q8(x) \
    TO_FIXED(x, Q8_SHIFT)

/** @brief Converts a floating-point value to clamped Q*.8 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to clamped Q*.8 fixed-point.
 */
#define Q8_CLAMPED(x) \
    CLAMP(Q8(x), 0, Q8(1.0f) - 1)

/** @brief Converts a floating-point value to Q*.12 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q12(x) \
    TO_FIXED(x, Q12_SHIFT)

/** @brief Converts a floating-point value to clamped Q*.12 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to clamped Q*.12 fixed-point.
 */
#define Q12_CLAMPED(x) \
    CLAMP(Q12(x), 0, Q12(1.0f) - 1)

/** @brief Converts a fixed-point value from Q*.4 to Q*.8.
 *
 * @param x Q*.4 fixed-point value to convert.
 * @return `x` converted to Q*.8 fixed-point.
 */
#define Q4_TO_Q8(x) \
    ((x) << 4)

/** @brief Converts a fixed-point value from Q*.4 to Q*.12.
 *
 * @param x Q*.4 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q4_TO_Q12(x) \
    ((x) << 8)

/** @brief Converts a fixed-point value from Q*.6 to Q*.12.
 *
 * @param x Q*.6 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q6_TO_Q12(x) \
    ((x) << 6)

/** @brief Converts a fixed-point value from Q*.8 to Q*.12.
 *
 * @param x Q*.8 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q8_TO_Q12(x) \
    ((x) << 4)

/** @brief Converts a fixed-point value from Q*.8 to Q*.4.
 *
 * @param x Q*.8 fixed-point value to convert.
 * @return `x` converted to Q*.4 fixed-point.
 */
#define Q8_TO_Q4(x) \
    ((x) >> 4)

/** @brief Converts a fixed-point value from Q*.10 to Q*.12.
 *
 * @param x Q*.10 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q10_TO_Q12(x) \
    ((x) << 2)

/** @brief Converts a fixed-point value from Q*.12 to Q*.4.
 *
 * @param x Q*.12 fixed-point value to convert.
 * @return `x` converted to Q*.4 fixed-point.
 */
#define Q12_TO_Q4(x) \
    ((x) >> 8)

/** @brief Converts a fixed-point value from Q*.12 to Q*.6.
 *
 * @param x Q*.12 fixed-point value to convert.
 * @return `x` converted to Q*.6 fixed-point.
 */
#define Q12_TO_Q6(x) \
    ((x) >> 6)

/** @brief Converts a fixed-point value from Q*.12 to Q*.8.
 *
 * @param x Q*.12 fixed-point value to convert.
 * @return `x` converted to Q*.8 fixed-point.
 */
#define Q12_TO_Q8(x) \
    ((x) >> 4)

/** @brief Converts a fixed-point value from Q*.12 to Q*.10.
 *
 * @param x Q*.12 fixed-point value to convert.
 * @return `x` converted to Q*.10 fixed-point.
 */
#define Q12_TO_Q10(x) \
    ((x) >> 2)

/** @brief Extracts the fractional part of a value in Q*.12 fixed-point.
 *
 * @param x Q*.12 fixed-point value.
 * @return Fractional part of `x` in Q*.12 fixed-point.
 */
#define Q12_FRACT(x) \
    ((x) & 0xFFF)

// =======================================
// ABSTRACT Q FORMAT CONVERSION AND UTILS
// =======================================

/** @brief Converts a normalized floating-point analog stick value in the range `[-1.0f, 1.0f]` to Q0.7 fixed-point, clamped integer range `[-128, 127]`.
 *
 * @param analog Analog stick value (`float`).
 * @return Analog stick value in Q0.7 fixed-point, clamped integer range `[-128, 127]`.
 */
#define FP_STICK(analog)                                                  \
    (s8)(((analog) >= 0) ? CLAMP(Q8(analog) / 2, 0, (Q8(1.0f) / 2) - 1) : \
                          -CLAMP(Q8(ABS(analog)) / 2, 0, Q8(1.0f) / 2))

/** @brief Converts a normalized floating-point color component in the range `[0.0f, 1.0f]` to Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * TODO: Deprecated, don't use. Doesn't make sense to have `float` color components in this project.
 *
 * @param comp Color component (`float`).
 * @return Q0.8 fixed-point color component, clamped integer range `[0, 255]` (`u8`).
 */
#define FP_COLOR(comp) \
    (u8)Q8_CLAMPED(comp)

/** @brief Converts floating-point degrees to signed Q3.12 fixed-point, full rotation integer range `[0, 4096]`.
 *
 * This angle format is used in world space.
 *
 * @note 1 degree = 11.377778 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((float)Q12(1.0f) / 360.0f))

/** @brief Converts floating-point degrees to unsigned Q0.8 fixed-point, clamped full rotation integer range `[0, 255]`.
 *
 * This angle format is used in map data.
 *
 * @note 1 degree = 0.711111 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned Q0.8 fixed-point packed angle, clamped full rotation integer range `[0, 255]` (`u8`).
 */
#define FP_ANGLE_PACKED(deg) \
    (u8)Q8_CLAMPED((deg) / 360.0f)

/** @brief Converts a signed Q3.12 fixed-point angle, full rotation integer range `[0, 4096]` to
 * unsigned Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * @param angle Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]`.
 * @return Unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]` (`s16`).
 */
#define FP_ANGLE_TO_PACKED(angle) \
    Q12_TO_Q8(deg);

/** @brief Converts an unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]` to
 * unsigned Q3.12 fixed-point, full rotation integer range `[0, 4096]`.
 *
 * @param packedAngle Unsigned Q0.8 fixed-point packed angle, full rotation integer range `[0, 255]`.
 * @return Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE_FROM_PACKED(packedAngle) \
    (s16)Q8_TO_Q12(packedAngle)

/** @brief Normalizes a signed Q3.12 fixed-point angle to the clamped unsigned integer range `[0, 4095]`.
 *
 * @note Has the same effect as `FP_ANGLE_NORM_U`. Could they somehow be combined?
 *
 * @param angle Signed Q3.12 fixed-point angle, full rotation integer range `[-2048, 2047]`.
 * @return Unsigned Q3.12 fixed-point angle, wrapped to the clamped integer range `[0, 4095]` (`s16`).
 */
#define FP_ANGLE_ABS(angle) \
    Q12_FRACT((angle) + FP_ANGLE(360.0f))

/** @brief Normalizes an unsigned Q3.12 fixed-point angle to the clamped signed integer range `[-2048, 2047]`.
 *
 * @param angle Unsigned Q3.12 fixed-point angle, full rotation integer range `[0, 4095]`.
 * @return Signed Q3.12 fixed-point angle wrapped to the clamped integer range `[-2048, 2047]` (`s16`).
 */
#define FP_ANGLE_NORM_S(angle) \
    (((angle) << 20) >> 20)

/** @brief Normalizes a signed Q3.12 fixed-point angle to the clamped unsigned range `[0, 4095]`.
 *
 * @param angle Signed Q3.12 fixed-point angle, full rotation integer range `[-2048, 2047]`.
 * @return Unsigned Q3.12 fixed-point angle, wrapped to the clamped integer range `[0, 4095]` (`s16`).
 */
#define FP_ANGLE_NORM_U(angle) \
    ((angle) & (FP_ANGLE(360.0f) - 1))

/** @brief Converts floating-point radians in the range `[-PI, PI]` to the fixed-point full rotation integer range `[0, 20480]`.
 *
 * This angle format is only used in `vcSetDataToVwSystem`.
 *
 * @note π = 10240 units.
 *
 * @param rad Radians (`float`).
 * @return Fixed-point radian representation, full rotation integer range `[0, 20480]` (`s32`).
 */
#define FP_RADIAN(rad)                                                                \
    (s32)(((((rad) < 0.0f) ? (PI + (PI - ABS(rad))) : (rad)) * ((float)FP_PI / PI)) * \
          (((rad) < 0.0f || (rad) >= PI) ? 1.0f : 2.0f))

#endif
