#ifndef _BODYPROG_MATH_MATH_H
#define _BODYPROG_MATH_MATH_H

#include <limits.h>

#include "bodyprog/math/arithmetic.h"
#include "bodyprog/math/constants.h"
#include "bodyprog/math/fixed_point.h"

/** @brief Constructs a `VECTOR3` in a fixed-point Q19.12 format.
 *
 * @param x X component (`float`).
 * @param y Y component (`float`).
 * @param z Z component (`float`).
 * @return `VECTOR3` in a fixed-point Q19.12 format.
 */
#define VECTOR3(x, y, z) \
    { Q12(x), Q12(y), Q12(z) }

/** @brief Constructs a `VECTOR3` in a fixed-point Q19.12 format for RODATA vectors used as inlined function parameters.
 *
 * @param x X component (`float`).
 * @param y Y component (`float`).
 * @param z Z component (`float`).
 * @return `VECTOR3` in a fixed-point Q19.12 format.
 */
#define QVECTOR3(x, y, z) \
    (VECTOR3)VECTOR3(x, y, z)

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

/** @brief Packs an RGB + code color.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 * @param code Code component.
 * @return Packed RGB + code color.
 */
#define PACKED_COLOR(r, g, b, code) \
    ((r) | ((g) << 8) | ((b) << 16) | ((code) << 24))

/** @brief Checks if a flag in a bitfield is set to a required status.
 *
 * @param bitfield Bitfield to check.
 * @param flag Flag to check in the bitfield.
 * @param isSet Required status to check for.
 * @return `true` if the flag is set to the required status, `false` otherwise.
 */
#define CHECK_FLAG(bitfield, flag, isSet) \
    (!((bitfield) & (flag)) == !(isSet))

/** @brief Scales a Q19.12 fixed-point value by a delta time relative to a 30 FPS timestep.
 *
 * @param deltaTime Time delta.
 * @param x Q19.12 fixed-point value to scale.
 * @return Scaled Q19.12 fixed-point value.
 */
#define TIMESTEP_SCALE(deltaTime, x) \
    (((x) * (deltaTime)) / TIMESTEP_30_FPS)

/** @brief Multiplies an integer in fixed-point Q format by a float converted to fixed-point Q format,
 * using a 64-bit intermediate via `Math_MulFixed` for higher precision.
 *
 * @param a First fixed-point factor.
 * @param b Second floating-point factor.
 * @param shift Fixed-point shift.
 * @return Fixed-point product of `a` and `b`.
 */
#define Math_MultiplyFloatPrecise(a, b, shift) \
    Math_MulFixed(a, TO_FIXED(b, shift), shift)

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

/** @brief Computes the magnitude of a 2D vector in Q19.12, using intermediate components in Q25.6 to avoid overflow.
 *
 * @param x X vector component (Q19.12).
 * @param z Z vector component (Q19.12).
 * @return 2D vector magnitude (Q19.12).
 */
#define Math_Vector2MagCalc(x, z) \
    Q6_TO_Q12(SquareRoot0(SQUARE(Q12_TO_Q6(x)) + SQUARE(Q12_TO_Q6(z))))

#define SetSVectorFast(vec, x, y, z)                            \
    *(s32*)&(vec)->vx = (s32)((x) & 0xFFFF) | (s32)((y) << 16); \
    (vec)->vz = (z)

/** @brief Normalizes Q19.12 fixed-point degrees, unsigned integer range `[0, 4096]` to the signed integer range `[-2048, 2047]`.
 * Thin wrapper for `FP_ANGLE_NORM_S`.
 *
 * @param angle Unsigned fixed-point degrees, integer range `[0, 4096]`.
 * @return Signed fixed-point degrees wrapped to the integer range `[-2048, 2047]` (`s16`).
 */
static inline q3_12 Math_AngleNormalize(q19_12 angle)
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

void Math_MatrixRotate0(SVECTOR* rot, MATRIX* mat); // Custom `vwRotMatrix[...]`?
void Math_MatrixRotate1(SVECTOR* rot, MATRIX* mat); // Another custom `vwRotMatrix[...]`?

/** @brief Multiplies two integers in a fixed-point Q format.
 *
 * @param a First fixed-point factor.
 * @param b Second fixed-point factor.
 * @param shift Fixed-point shift.
 * @return Fixed-point product of `a` and `b`.
 */
s32 Math_MulFixed(s32 a, s32 b, s32 shift);

/** @brief Computes the sine in Q19.12 of degrees in Q19.12, integer range `[0, 4096]`.
 *
 * TODO: Matched on decomp.me.
 * Possible original name: `shRsin`.
 *
 * @param angle Fixed-point degrees in Q19.12, integer range `[0, 4096]`.
 * @return Sine in Q19.12, integer range `[0, 4096]`.
 */
q19_12 Math_Sin(q19_12 angle);

/** @brief Computes the cosine in Q19.12 of degrees in Q19.12, integer range `[0, 4096]`.
 *
 * TODO: Matched on decomp.me.
 * Possible original name: `shRcos`.
 *
 * @param angle Fixed-point degrees in Q19.12, integer range `[0, 4096]`.
 * @return Cosine in Q19.12, integer range `[0, 4096]`.
 */
q19_12 Math_Cos(q19_12 angle);

MATRIX* shRotMatrixZ(s32, MATRIX*);

#endif
