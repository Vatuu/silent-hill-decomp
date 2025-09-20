#ifndef _BODYPROG_MATH_FIXED_POINT_H
#define _BODYPROG_MATH_FIXED_POINT_H

#include "types.h"
#include "bodyprog/math/constants.h"
#include "bodyprog/math/arithmetic.h"

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
#define FP_FLOAT_TO(x, shift) \
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
    (((x) + ((FP_FLOAT_TO(1.0f, shift) * (scale)) - 1)) / (FP_FLOAT_TO(1.0f, shift) * (scale)))

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
    (((s64)(a) * (s64)(b)) >> (shift))

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to a fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Fixed-point product of `a` and `b`.
 */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY(aInt, FP_FLOAT_TO(bFlt, shift), shift)

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to fixed-point Q format,
 * using a 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT_PRECISE(aInt, bFlt, shift) \
    FP_MULTIPLY((s64)(aInt), (s64)FP_FLOAT_TO(bFlt, shift), shift)

/** @brief Computes the square 2D distance between two positions in Q19.12 fixed-point,
 * using low-precision Q21.8 fixed-point intermediates to avoid overflow.
 *
 * @param from First position.
 * @param to Second position.
 * @param return 2D distance between two positions.
 */
#define FP_2D_DISTANCE_SQR(from, to)                                     \
    ((Q12_TO_Q8((to).vx - (from).vx) * Q12_TO_Q8((to).vx - (from).vx)) + \
     (Q12_TO_Q8((to).vz - (from).vz) * Q12_TO_Q8((to).vz - (from).vz)))

// ==================================
// RAW Q FORMAT CONVERSION AND UTILS
// ==================================

/** @brief Converts a floating-point value to Q*.4 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.4 fixed-point.
 */
#define Q4(x) \
    FP_FLOAT_TO(x, Q4_SHIFT)

/** @brief Converts a floating-point value to Q*.8 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.8 fixed-point.
 */
#define Q8(x) \
    FP_FLOAT_TO(x, Q8_SHIFT)

/** @brief Converts a floating-point value to Q*.12 fixed-point.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q12(x) \
    FP_FLOAT_TO(x, Q12_SHIFT)

/** @brief Converts a fixed-point value from Q*.4 to Q*.12.
 *
 * @param x Q*.4 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q4_TO_Q12(x) \
    ((x) << 8)

/** @brief Converts a fixed-point value from Q*.8 to Q*.12.
 *
 * @param x Q*.8 fixed-point value to convert.
 * @return `x` converted to Q*.12 fixed-point.
 */
#define Q8_TO_Q12(x) \
    ((x) << 4)

/** @brief Converts a fixed-point value from Q*.12 to Q*.8.
 *
 * @param x Q*.12 fixed-point value to convert.
 * @return `x` converted to Q*.8 fixed-point.
 */
#define Q12_TO_Q8(x) \
    ((x) >> 4)

/** @brief Extracts the fractional part of a value in Q*.12 fixed-point.
 *
 * @param x Q*.12 fixed-point value in.
 * @return Fractional part of `x` in Q*.12 fixed-point.
 */
#define Q12_FRACT(x) \
    ((x) & 0xFFF)

// =======================================
// ABSTRACT Q FORMAT CONVERSION AND UTILS
// =======================================

/** @brief Converts a normalized floating-point sound volume in the range `[0.0f, 1.0f]` to Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * @param vol Sound volume (`float`).
 * @return Q0.8 fixed-point sound volume, integer range `[0, 255]` (`u8`).
 */
#define FP_VOLUME(vol) \
    (u8)CLAMP(FP_FLOAT_TO(vol, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts a normalized floating-point analog stick value in the range `[-1.0f, 1.0f]` to Q0.7 fixed-point, integer range `[-128, 127]`.
 *
 * @param analog Analog stick value (`float`).
 * @return Analog stick value in Q0.7 fixed-point, integer range `[-128, 127]`.
 */
#define FP_STICK(analog)                                                                                        \
    (s8)(((analog) >= 0) ? CLAMP(FP_FLOAT_TO(analog, Q8_SHIFT) / 2, 0, (FP_FLOAT_TO(1.0f, Q8_SHIFT) / 2) - 1) : \
                          -CLAMP(FP_FLOAT_TO(ABS(analog), Q8_SHIFT) / 2, 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) / 2))

/** @brief Converts a normalized floating-point color component in the range `[0.0f, 1.0f]` to Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * TODO: Deprecated, don't use. Doesn't make sense to have `float` color components in this project.
 *
 * @param comp Color component (`float`).
 * @return Q0.8 fixed-point color component, integer range `[0, 255]` (`u8`).
 */
#define FP_COLOR(comp) \
    (u8)CLAMP(FP_FLOAT_TO(comp, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts floating-point degrees to signed Q3.12 fixed-point, integer range `[0, 4096]`.
 *
 * This angle format is used in world space.
 *
 * @note 1 degree = 11.377778 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned Q3.12 fixed-point degrees, integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((float)Q12(1.0f) / 360.0f))

/** @brief Converts floating-point degrees to unsigned Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * This angle format is used in map data.
 *
 * @note 1 degree = 0.711111 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned Q0.8 fixed-point degrees, integer range `[0, 255]` (`u8`).
 */
#define FP_ANGLE_PACKED(deg) \
    (u8)CLAMP(FP_FLOAT_TO((deg) / 360.0f, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts signed Q3.12 fixed-point degrees, integer range `[0, 4096]` to
 * unsigned Q0.8 fixed-point, integer range `[0, 255]`.
 *
 * @param deg Unsigned Q3.12fixed-point degrees, integer range `[0, 4096]`.
 * @return Unsigned Q0.8 fixed-point degrees, integer range `[0, 255]` (`s16`).
 */
#define FP_ANGLE_TO_PACKED(deg) \
    Q12_TO_Q8(deg);

/** @brief Converts unsigned Q0.8 fixed-point degrees, integer range `[0, 255]` to
 * unsigned Q3.12 fixed-point, integer range `[0, 4096]`.
 *
 * @param packedDeg Unsigned Q0.8 fixed-point degrees, integer range `[0, 255]`.
 * @return Unsigned Q3.12 fixed-point degrees, integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE_FROM_PACKED(deg) \
    (s16)Q8_TO_Q12(deg)

/** @brief Normalizes signed Q3.12 fixed-point degrees to the unsigned range `[0, 4095]`.
 *
 * @note Has the same effect as `FP_ANGLE_NORM_U`. Could they somehow be combined?
 *
 * @param deg Signed Q3.12 fixed-point degrees, integer range `[-2048, 2047]`.
 * @return Unsigned Q3.12 fixed-point degrees, wrapped to the integer range `[0, 4095]` (`s16`).
 */
#define ABS_ANGLE(deg) \
    Q12_FRACT((deg) + FP_ANGLE(360.0f))

/** @brief Normalizes unsigned Q3.12 fixed-point degrees to the signed integer range `[-2048, 2047]`.
 *
 * @param deg Unsigned Q3.12 fixed-point degrees, integer range `[0, 4095]`.
 * @return Signed Q3.12 fixed-point degrees wrapped to the integer range `[-2048, 2047]` (`s16`).
 */
#define FP_ANGLE_NORM_S(deg) \
    (((deg) << 20) >> 20)

/** @brief Normalizes signed Q3.12 fixed-point degrees to the unsigned range `[0, 4095]`.
 *
 * @param deg Signed Q3.12 fixed-point degrees, integer range `[-2048, 2047]`.
 * @return Unsigned Q3.12 fixed-point degrees, wrapped to the integer range `[0, 4095]` (`s16`).
 */
#define FP_ANGLE_NORM_U(deg) \
    ((deg) & (FP_ANGLE(360.0f) - 1))

/** @brief Converts floating-point radians in the range `[-PI, PI]` to the fixed-point integer range `[0, 20480]`.
 *
 * This angle format is only used in `vcSetDataToVwSystem`.
 *
 * @note π = 10240 units.
 *
 * @param rad Radians (`float`).
 * @return Fixed-point radians, integer range `[0, 20480]` (`s32`).
 */
#define FP_RADIAN(rad)                                                                \
    (s32)(((((rad) < 0.0f) ? (PI + (PI - ABS(rad))) : (rad)) * ((float)FP_PI / PI)) * \
          (((rad) < 0.0f || (rad) >= PI) ? 1.0f : 2.0f))

/** @brief Converts floating-point meters to Q19.12 fixed-point world space.
 *
 * @note 1 meter = 4096 units.
 *
 * @param met Meters (`float`).
 * @return Q19.12 fixed-point world space meters (`s32`).
 */
#define FP_METER(met) \
    Q12(met)

/** @brief Converts floating-point meters to Q23.8 fixed-point geometry space.
 *
 * @note 1 meter = 256 units.
 *
 * @param met Meters (`float`).
 * @return Q23.8 fixed-point geometry space meters (`s32`).
 */
#define FP_METER_GEO(met) \
    Q8(met)

/** @brief Converts Q19.12 fixed-point world space meters to Q23.8 fixed-point geometry space.
 *
 * @param met Q19.12 fixed-point world space meters.
 * @return Q23.8 fixed-point geometry space meters (`s32`).
 */
#define FP_METER_TO_GEO(met) \
    Q12_TO_Q8(met)

/** @brief Converts Q23.8 fixed-point geometry space meters to Q19.12 fixed-point world space meters.
 *
 * @param met Q23.8 fixed-point geometry space meters.
 * @return Q19.12 fixed-point world space meters (`s32`).
 */
#define FP_METER_FROM_GEO(met) \
    Q8_TO_Q12(met)

/** @brief Converts floating-point seconds to Q19.12 fixed-point.
 *
 * @note 1 second == 4096 units.
 *
 * @param sec Seconds (`float`).
 * @return Q19.12 fixed-point seconds (`s32`).
 */
#define FP_TIME(sec) \
    Q12(sec)

#endif
