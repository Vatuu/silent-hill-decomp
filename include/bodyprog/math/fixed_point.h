#ifndef _BODYPROG_MATH_FIXED_POINT_H
#define _BODYPROG_MATH_FIXED_POINT_H

#include "types.h"
#include "bodyprog/math/constants.h"
#include "bodyprog/math/arithmetic.h"

// =================================
// Fixed-Point Utils and Arithmetic
// =================================

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
    (s32)((x) * FP_TO(1, shift))

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
    (((x) + ((FP_TO(1, shift) * (scale)) - 1)) / (FP_TO(1, shift) * (scale)))

/** @brief Converts an integer from a fixed-point Q format rounded toward 0.
 *
 * @param x Fixed-point value to convert.
 * @param shift Fixed-point shift.
 * @return `x` rounded toward 0 and converted from fixed-point.
 */
#define FP_ROUND_TO_ZERO(x, shift) \
    ((s32)(FP_FROM(x, shift) + ((u32)(x) >> 31)) >> 1)

/** @brief Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY(a, b, shift) \
    (((a) * (b)) >> (shift))

/** @brief Multiplies two integers in a fixed-point Q format and converts the result from the fixed-point Q format,
 * using 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_PRECISE(a, b, shift) \
    (((s64)(a) * (s64)(b)) >> (shift))

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to a fixed-point Q format,
 * then converts the result back from the fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT(aInt, bFlt, shift) \
    FP_MULTIPLY(aInt, FP_FLOAT_TO(bFlt, shift), shift)

/** @brief Multiplies an integer in a fixed-point Q format by a float converted to fixed-point Q format,
 * then converts the result back from the fixed-point Q format using a 64-bit intermediates for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Precise product of `a` and `b` converted from fixed-point.
 */
#define FP_MULTIPLY_FLOAT_PRECISE(aInt, bFlt, shift) \
    FP_MULTIPLY((s64)(aInt), (s64)FP_FLOAT_TO(bFlt, shift), (shift))

// ====================================
// Raw Fixed-Point Q Format Conversion
// ====================================

/** @brief Converts a floating-point value to fixed-point Q19.12.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to fixed-point Q19.12 (`s32`).
 */
#define Q19_12(x) \
    (s32)FP_FLOAT_TO(x, Q12_SHIFT)

/** @brief Converts a floating-point value to fixed-point Q23.8.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to fixed-point Q23.8 (`s32`).
 */
#define Q23_8(x) \
    (s32)FP_FLOAT_TO(x, Q8_SHIFT)

/** @brief Converts a floating-point value to fixed-point Q3.12.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to fixed-point Q3.12 (`s16`).
 */
#define Q3_12(x) \
    (s16)FP_FLOAT_TO(x, Q12_SHIFT)

/** @brief Converts a floating-point value to fixed-point Q7.8.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to fixed-point Q7.8 (`s16`).
 */
#define Q7_8(x) \
    (s16)FP_FLOAT_TO(x, Q8_SHIFT)

/** @brief Converts a floating-point value to fixed-point Q0.8.
 *
 * @param x Value to convert (`float`).
 * @return `x` converted to fixed-point Q0.8 ('u8`).
 */
#define Q0_8(x) \
    (u8)FP_FLOAT_TO(x, Q8_SHIFT)

/** @brief Converts a fixed-point value from Q23.8 to Q19.12.
 *
 * @param x Fixed-point value in Q23.8 to convert.
 * @return `x` converted to fixed-point Q19.12 (`s32`).
 */
#define Q23_8_TO_Q19_12(x) \
    (s32)((x) << 4)

/** @brief Converts a fixed-point value from Q0.8 to Q3.12.
 *
 * @param x Fixed-point value in Q0.8 to convert.
 * @return `x` converted to fixed-point Q3.12 (`s16`).
 */
#define Q0_8_TO_Q3_12(x) \
    (s16)((x) << 4)

/** @brief Converts a fixed-point value from Q19.12 to Q23.8.
 *
 * @param x Fixed-point value in Q19.12 to convert.
 * @return `x` converted to fixed-point Q23.8 (`s32`).
 */
#define Q19_12_TO_Q23_8(x) \
    (s32)((x) >> 4)

/** @brief Converts a fixed-point value from Q3.12 to Q0.8.
 *
 * @param x Fixed-point value in Q3.12 to convert.
 * @return `x` converted to fixed-point Q0.8 (`u8`).
 */
#define Q3_12_TO_Q0_8(x) \
    (u8)((x) >> 4)

/** @brief Extracts the fractional part of a value in fixed-point QX.12.
 *
 * @param x Fixed-point value in QX.12.
 * @return Fractional part of `x` in QX.12.
 */
#define QX_12_FRACT(x) \
    ((x) & 0xFFF)

// =========================================
// Abstract Fixed-Point Q Format Conversion
// =========================================

/** @brief Converts a floating-point alpha in the range `[0.0f, 1.0f]` to fixed-point Q3.12, integer range `[0, 4096]`.
 *
 * @param alpha Alpha (`float`).
 * @return Fixed-point alpha in Q3.12, integer range `[0, 4096]` (`s16`).
 */
#define FP_ALPHA(alpha) \
    (s16)Q3_12(alpha)

/** @brief Normalizes a fixed-point alpha in Q3.12 to the integer range `[0, 4095]`.
 *
 * @param alpha Fixed-point alpha.
 * @return Normalized fixed-point alpha in Q3.12, integer range `[0, 4095]`.
 */
#define FP_ALPHA_NORM(alpha) \
    QX_12_FRACT(alpha)

/** @brief Converts a normalized floating-point sound volume in the range `[0.0f, 1.0f]` to fixed-point Q0.8, integer range `[0, 255]`.
 *
 * @param vol Sound volume (`float`).
 * @return Fixed-point sound volume in Q0.8, integer range `[0, 255]` (`u8`).
 */
#define FP_VOLUME(vol) \
    (u8)CLAMP(FP_FLOAT_TO(vol, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts a normalized floating-point analog stick value in the range `[-1.0f, 1.0f]` to fixed point Q0.7, integer range `[-128, 127]`.
 *
 * @param analog Analog stick value (`float`).
 * @return Analog stick value in Q0.7, integer range `[-128, 127]`.
 */
#define FP_STICK(analog)                                                                                        \
    (s8)(((analog) >= 0) ? CLAMP(FP_FLOAT_TO(analog, Q8_SHIFT) / 2, 0, (FP_FLOAT_TO(1.0f, Q8_SHIFT) / 2) - 1) : \
                          -CLAMP(FP_FLOAT_TO(ABS(analog), Q8_SHIFT) / 2, 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) / 2))

/** @brief Converts a normalized floating-point color component in the range `[0.0f, 1.0f]` to fixed-point Q0.8, integer range `[0, 255]`.
 *
 * TODO: Deprecated, don't use. Doesn't make sense to have `float` color components in this project.
 *
 * @param comp Color component (`float`).
 * @return Fixed-point color component in Q0.8, integer range `[0, 255]` (`u8`).
 */
#define FP_COLOR(comp) \
    (u8)CLAMP(FP_FLOAT_TO(comp, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts floating-point degrees to signed fixed-point Q3.12, integer range `[0, 4096]`.
 *
 * This angle format is used in world space.
 *
 * @note 1 degree = 11.377778 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned fixed-point degrees in Q3.12, integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((float)Q3_12(1.0f) / 360.0f))

/** @brief Converts floating-point degrees to unsigned fixed-point in Q0.8, integer range `[0, 255]`.
 *
 * This angle format is used in map data.
 *
 * @note 1 degree = 0.711111 units.
 *
 * @param deg Degrees (`float`).
 * @return Unsigned fixed-point degrees in Q0.8, integer range `[0, 255]` (`u8`).
 */
#define FP_ANGLE_PACKED(deg) \
    (u8)CLAMP(FP_FLOAT_TO((deg) / 360.0f, Q8_SHIFT), 0, FP_FLOAT_TO(1.0f, Q8_SHIFT) - 1)

/** @brief Converts signed fixed-point degrees in Q3.12, integer range `[0, 4096]` to
 * unsigned fixed-point Q0.8, integer range `[0, 255]`.
 *
 * @param deg Unsigned fixed-point degrees in Q3.12, integer range `[0, 4096]`.
 * @return Unsigned fixed-point degrees in Q0.8, integer range `[0, 255]` (`s16`).
 */
#define FP_ANGLE_TO_PACKED(deg) \
    Q3_12_TO_Q0_8(deg);

/** @brief Converts unsigned fixed-point degrees in Q0.8, integer range `[0, 255]` to
 * unsigned fixed-point Q3.12, integer range `[0, 4096]`.
 *
 * @param packedDeg Unsigned fixed-point degrees in Q0.8, integer range `[0, 255]`.
 * @return Unsigned fixed-point degrees in Q3.12, integer range `[0, 4096]` (`s16`).
 */
#define FP_ANGLE_FROM_PACKED(deg) \
    Q0_8_TO_Q3_12(deg)

/** @brief Normalizes unsigned fixed-point degrees in Q3.12 to the signed integer range `[-2048, 2047]`.
 *
 * @param deg Unsigned fixed-point degrees in Q3.12, integer range `[0, 4095]`.
 * @return Signed fixed-point degrees in Q3.12, wrapped to the integer range `[-2048, 2047]` (`s16`).
 */
#define FP_ANGLE_NORM_S(deg) \
    (((deg) << 20) >> 20)

/** @brief Normalizes signed fixed-point degrees in Q3.12 to the unsigned range `[0, 4095]`.
 *
 * @param deg Signed fixed-point degrees in Q3.12, integer range `[-2048, 2047]`.
 * @return Unsigned fixed-point degrees in Q3.12, wrapped to the integer range `[0, 4095]` (`s16`).
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

/** @brief Converts floating-point meters to fixed-point world space Q19.12.
 *
 * @note 1 meter = 4096 units.
 *
 * @param met Meters (`float`).
 * @return Fixed-point world space meters in Q19.12 (`s32`).
 */
#define FP_METER(met) \
    Q19_12(met)

/** @brief Converts floating-point meters to fixed-point geometry space Q23.8.
 *
 * @note 1 meter = 256 units.
 *
 * @param met Meters (`float`).
 * @return Fixed-point geometry space meters in Q23.8 (`s32`).
 */
#define FP_METER_GEO(met) \
    Q23_8(met)

/** @brief Converts fixed-point world space meters in Q19.12 to geometry space Q23.8.
 *
 * @param met Fixed-point world space meters in Q19.12.
 * @return Fixed-point geometry space meters in Q23.8 (`s32`).
 */
#define FP_METER_TO_GEO(met) \
    Q19_12_TO_Q23_8(met)

/** @brief Converts fixed-point geometry space meters in Q23.8 to world space Q19.12.
 *
 * @param met Fixed-point world space meters in Q23.8.
 * @return Fixed-point world space meters in Q19.12 (`s32`).
 */
#define FP_METER_FROM_GEO(met) \
    Q23_8_TO_Q19_12(met)

/** @brief Converts floating-point seconds to fixed-point Q19.12.
 *
 * @note 1 second == 4096 units.
 *
 * @param sec Seconds (`float`).
 * @return Fixed-point seconds in Q19.12 (`s32`).
 */
#define FP_TIME(sec) \
    Q19_12(sec)

/** @brief Converts floating-point health to fixed-point Q19.12.
 *
 * @note 1 health == 4096 units.
 *
 * @param health Health (`float`).
 * @return Fixed-point health in Q19.12 (`s32`).
 */
#define FP_HEALTH(health) \
    Q19_12(health)

#endif
