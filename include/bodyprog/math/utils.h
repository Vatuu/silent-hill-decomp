
#ifndef _BODYPROG_MATH_UTILS_H
#define _BODYPROG_MATH_UTILS_H

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

#endif
