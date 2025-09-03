#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#include <limits.h>
#include "bodyprog/math/constants.h"
#include "bodyprog/math/fixed_point.h"
#include "bodyprog/math/arithmetic.h"

/** @brief Constructs a `VECTOR3` in a fixed-point Q19.12 format.
 *
 * @param x X component (`float`).
 * @param y Y component (`float`).
 * @param z Z component (`float`).
 * @return `VECTOR3` in a fixed-point Q19.12 format.
 */
#define VECTOR3(x, y, z) \
    { Q19_12(x), Q19_12(y), Q19_12(z) }

/** @brief Constructs an `SVECTOR` containing Euler angles in a fixed-point Q3.12 format.
 *
 * @param x X degree component (`float`).
 * @param y Y degree component (`float`).
 * @param z Z degree component (`float`).
 * @return `SVECTOR` containing Euler angles in a fixed-point Q3.12 format.
 */
#define SVECTOR(x, y, z) \
    { FP_ANGLE(x), FP_ANGLE(y), FP_ANGLE(z) }

/** @brief Constructs a `DVECTOR` containing a screen position in 320x240 screen space.
 *
 * @param x X position in percent (`float`).
 * @param z Y position in percent (`float`).
 * @return `DVECTOR` containing a screen position in 320x240 screen space.
 */
#define DVECTOR(x, y) \
    { SCREEN_POSITION_X(x), SCREEN_POSITION_Y(y) }

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

/** @brief Computes the dot product(?) of the first column of a matrix with a vector in Q17.15(?).
 *
 * @param mat Input matrix.
 * @param vec Input vector.
 * @return Dot product(?).
 */
#define Math_MultiplyMatrix(mat, vec)   \
    (s32)((((mat).m[0][0] * (vec).vx) + \
           ((mat).m[1][0] * (vec).vy) + \
           ((mat).m[2][0] * (vec).vz)) >> 17)

/** @brief Computes the magnitude of a 2D vector in Q19.12, using intermediate components in Q23.8 to avoid overflow.
 *
 * @param x X vector component.
 * @param z Z vector component.
 * @return 2D vector magnitude in Q19.12.
 */
#define Math_Vector2MagCalc(x, z) \
    (SquareRoot0(SQUARE((x) >> 6) + SQUARE((z) >> 6)) << 6)
    
/** @brief Sets an `VECTOR3`'s components to `float`s converted to a fixed-point Q format.
 *
 * @param vec Output vector.
 * @param x X component (`float`).
 * @param y Y component (`float`).
 * @param z Z component (`float`).
 * @param shift Fixed-point shift.
 */
#define Math_Vector3f(vec, x, y, z, shift) \
    Math_Vector3Set(vec, FP_FLOAT_TO(x, shift), FP_FLOAT_TO(y, shift), FP_FLOAT_TO(z, shift))

/** @brief Modulates a distance according to delta time? Unclear what the `/ 136` is doing, but it's a common operation.
 *
 * Possible better name: `Math_DeltaTimeDistScale`
 *
 * @param dist Distance in fixed-point world meters.
 * @return Modulated distance?
 */
#define Math_UnkDistTimeCalc(dist) \
    ((g_DeltaTime0 * (dist)) / 136)

/** @brief Normalizes unsigned fixed-point degrees in Q3.12, range `[0, 4096]` to the signed range `[-2048, 2047]`.
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
/** @brief Computes the sine in Q19.12 of degrees in Q3.12, integer range `[0, 4096]`.
 *
 * Possible original name: `shRsin`
 *
 * @param angle Fixed-point degrees in Q3.12, integer range `[0, 4096]`.
 * @return Sine in Q19.12, integer range `[0, 4096]`.
 */
s32 Math_Sin(s32 angle);

// NOTE: Matched on decomp.me.
/** @brief Computes the cosine in Q19.12 of degrees in Q3.12, integer range `[0, 4096]`.
 *
 * Possible original name: `shRcos`
 *
 * @param angle Fixed-point degrees in Q3.12, integer range `[0, 4096]`.
 * @return Cosine in Q19.12, integer range `[0, 4096]`.
 */
s32 Math_Cos(s32 angle);

MATRIX* shRotMatrixZ(s32, MATRIX*);

#endif
