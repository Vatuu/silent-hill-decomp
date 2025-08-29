#ifndef _BODYPROG_MATH_FIXED_POINT_H
#define _BODYPROG_MATH_FIXED_POINT_H

#include "types.h"
#include "bodyprog/math/constants.h"
#include "bodyprog/math/arithmetic.h"

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
 * @param val Value to convert (`float`).
 * @return `val` converted to fixed-point Q19.12 (`s32`).
 */
#define Q19_12(val) \
    (s32)FP_FLOAT_TO((val), Q12_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q23.8.
 *
 * @param val Value to convert (`float`).
 * @return `val` converted to fixed-point Q23.8 (`s32`).
 */
#define Q23_8(val) \
    (s32)FP_FLOAT_TO((val), Q8_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q3.12.
 *
 * @param val Value to convert (`float`).
 * @return `val` converted to fixed-point Q3.12 (`s16`).
 */
#define Q3_12(val) \
    (s16)FP_FLOAT_TO((val), Q12_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q7.8.
 *
 * @param val Value to convert (`float`).
 * @return `val` converted to fixed-point Q7.8 (`s16`).
 */
#define Q7_8(val) \
    (s16)FP_FLOAT_TO((val), Q8_SHIFT)

/** @brief Converts a floating-point value to a fixed-point value in Q0.8.
 *
 * @param val Value to convert (`float`).
 * @return `val` converted to fixed-point Q0.8 ('u8`).
 */
#define Q0_8(val) \
    (u8)FP_FLOAT_TO((val), Q8_SHIFT)

/** @brief Converts a floating-point value in Q19.12 to a fixed-point value in Q23.8.
 *
 * @param val Fixed-point value in Q19.12 to convert.
 * @return `val` converted to fixed-point Q23.8 (`s32`).
 */
#define Q19_12_TO_Q23_8(val) \
    (s32)(((val) >> 4))

/** @brief Converts a floating-point alpha in the range `[0.0f, 1.0f]` to a fixed-point alpha in Q3.12, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @param alpha Alpha (`float`).
 * @return Fixed-point alpha in Q3.12, range `[0, 4096]` (`s16`).
 */
#define FP_ALPHA(alpha) \
    (s16)Q3_12(alpha)

/** @brief Normalizes a fixed-point alpha in Q3.12 to the range `[0, 4095]`.
 *
 * @param alpha Fixed-point alpha.
 * @return Normalized fixed-point alpha in Q3.12, range `[0, 4095]`.
 */
#define FP_ALPHA_NORM(alpha) \
    ((alpha) & 0xFFF)

/** @brief Converts a floating-point sound volume in the range `[0.0f, 1.0f]` to a fixed-point sound volume in Q0.8, range `[0, 255]`.
 * Mapping is direct.
 *
 * @param vol Sound volume (`float`).
 * @return Fixed-point sound volume in Q0.8, range `[0, 255]` (`u8`).
 */
#define FP_VOLUME(vol) \
    (u8)CLAMP(FP_FLOAT_TO((vol), Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

// TODO: Maybe not appropriate for this project since it often results in ugly floats.
/** @brief Converts a normalized color value in the range `[0.0f, 1.0f]` to an 8-bit color value in Q0.8, range `[0, 255]`.
 * Mapping is direct.
 *
 * @param val Color component (`float`).
 * @return Fixed-point color component in Q0.8, range `[0, 255]` (`u8`).
 */
#define FP_COLOR(val) \
    (u8)((val) * 0xFF)

/** @brief Converts floating-point degrees to unsigned fixed-point degrees in Q3.12, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @note 1 degree = 11.377778 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned fixed-point degrees in Q3.12, range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((float)Q3_12(1.0f) / 360.0f))

/** @brief Converts floating-point degrees to unsigned fixed-point degrees in Q7.8, packed range `[0, 256]`.
 * Mapping is direct.
 *
 * @note 1 degree = 0.711111 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned fixed-point degrees in Q7.8, packed range `[0, 256]` (`s16`).
 */
#define FP_ANGLE_PACKED(deg) \
    (s16)((deg) * ((float)Q23_8(1.0f) / 360.0f))

/** @brief Converts unsigned fixed-point degrees in Q7.8, packed range `[0, 256]` to
 * unsigned fixed-point degrees in Q3.12, range `[0, 4096]`.
 * Mapping is direct.
 *
 * @param packedDeg Unsigned fixed-point degrees in Q7.8, packed range `[0, 256]`.
 * @return Unsigned fixed-point degrees in Q3.12, range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE_FROM_PACKED(packedDeg) \
    (s16)((packedDeg) * 16)

/** @brief Normalizes unsigned fixed-point degrees in Q3.12 to the signed range `[-2048, 2047]`.
 *
 * @param deg Unsigned fixed-point degrees in Q3.12, range `[0, 4095]`.
 * @return Signed fixed-point degrees wrapped to the range `[-2048, 2047]` (`s16`).
 */
#define FP_ANGLE_NORM_S(deg) \
    (((deg) << 20) >> 20)

/** @brief Normalizes signed fixed-point degrees in Q3.12 to the unsigned range `[0, 4095]`.
 *
 * @param deg Signed fixed-point degrees in Q3.12, range `[-2048, 2047]`.
 * @return Unsigned fixed-point degrees wrapped to the range `[0, 4095]` (`s16`).
 */
#define FP_ANGLE_NORM_U(deg) \
    ((deg) & (FP_ANGLE(360.0f) - 1))

/** @brief Converts floating-point radians in the range `[-PI, PI]` to fixed-point radians in the range `[0, 0x5000]`.
 * Mapping is direct.
 *
 * @note Pi = 10240 units.
 *
 * @param rad Radians (`float`).
 * @return Fixed-point radians, range `[0, 0x5000]` (`s32`).
 */
#define FP_RADIAN(rad)                                                                \
    (s32)(((((rad) < 0.0f) ? (PI + (PI - ABS(rad))) : (rad)) * ((float)FP_PI / PI)) * \
          (((rad) < 0.0f || (rad) >= PI) ? 1.0f : 2.0f))

/** @brief Converts floating-point meters to fixed-point world meters in Q19.12.
 *
 * @note 1 meter = 4096 units.
 *
 * @param met Meters (`float`).
 * @return Fixed-point world meters in Q19.12 (`s32`).
 */
#define FP_METER(met) \
    Q19_12(met)

// TODO: Find better name.
/** @brief Converts floating-point world meters in Q19.12 to fixed-point collision meters in Q23.8.
 *
 * @note 1 meter = 256 units.
 *
 * @param met Meters (`float`).
 * @return Fixed-point collision meters in Q23.8 (`s32`).
 */
#define FP_METER_COLL(met) \
    Q23_8(met)

// TODO: Find better name.
/** @brief Converts fixed-point world meters in Q19.12 to fixed-point collision meters in Q23.8.
 *
 * @param met Fixed-point world meters in Q19.12.
 * @return Fixed-point collision meters in Q23.8 (`s32`).
 */
#define FP_METER_TO_COLL(met) \
    Q19_12_TO_Q23_8(met)

/** @brief Converts floating-point seconds to fixed-point seconds in Q19.12.
 *
 * @note 1 second == 4096 units.
 *
 * @param sec Seconds (`float`).
 * @return Fixed-point seconds in Q19.12 (`s32`).
 */
#define FP_TIME(sec) \
    Q19_12(sec)

/** @brief Converts floating-point health to fixed-point health in Q19.12.
 *
 * @note 1 health == 4096 units.
 *
 * @param health Health (`float`).
 * @return Fixed-point health in Q19.12 (`s32`).
 */
#define FP_HEALTH(health) \
    Q19_12(health)

#endif
