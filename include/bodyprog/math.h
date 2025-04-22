#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for: Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for: Q8.8 camera AABBs. Q24.8 meters. */
#define Q12_SHIFT      12    /** Used for: Q3.12 alphas. Q19.12 timers, trigonometry. */
#define SIN_LUT_SIZE   4096  /** Number of entries in the sine lookup table. */
#define FP_ANGLE_COUNT 65536 /** Number of fixed-point angles in Q1.15 format. */

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

/** @brief Clamps a value to the range [min, max]. */
#define CLAMP(x, min, max) \
    (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

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

/** @brief Converts a floating-point alpha in the range [0.0f, 1.0f] to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)FP_FLOAT_TO(alpha, (Q12_SHIFT))

/** @brief Converts a normalized color value in the range [0.0f, 1.0f] to an 8-bit color value in the range [0, 255]. */
#define FP_COLOR(val) \
    (u8)((val) * 255)

/** @brief Converts floating-point degrees to fixed-point angles in Q1.15 format. */
#define FP_ANGLE(deg) \
    (s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

/** @brief Converts floating-point meters to fixed-point meters in Q24.8 format. */
#define FP_METER(met) \
    FP_FLOAT_TO(met, Q8_SHIFT)

/** @brief Tests if a probability, determined by the number of set bits in a mask, is met.
 *
 * Bits | Percent | Mask
 * -----|---------|------
 * 1    | 50%     | 0x1
 * 2    | 25%     | 0x3
 * 3    | 12.5%   | 0x7
 * 4    | 6.25%   | 0xF
 * 5    | 3.125%  | 0x1F
 * 6    | 1.563%  | 0x3F
 * 7    | 0.781%  | 0x7F
 * 8    | 0.391%  | 0xFF
 * 9    | 0.195%  | 0x1FF
 * 10   | 0.098%  | 0x3FF
 * 11   | 0.049%  | 0x7FF
 * 12   | 0.024%  | 0xFFF
 * 13   | 0.012%  | 0x1FFF
 * 14   | 0.006%  | 0x3FFF
 * 15   | 0.003%  | 0x7FFF
 * 16   | 0.002%  | 0xFFFF
 */
#define TEST_RNG(bits) \
    (Rng_Rand16() & ((1 << (bits)) - 1))

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
