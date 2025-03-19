#ifndef _BODYPROG_MATH_H
#define _BODYPROG_MATH_H

#define Q4_SHIFT       4     /** Used for: Q27.4 positions. */
#define Q8_SHIFT       8     /** Used for: Q8.8 range limits. */
#define Q12_SHIFT      12    /** Used for: Q3.12 alphas. Q19.12 timers, trigonometry. */
#define FP_ANGLE_COUNT 65536 /** Number of possible fixed-point angles in Q1.15 format. */

/** Returns the larger of two values. */
#define MAX(val0, val1) \
    (((val0) > (val1)) ? (val0) : (val1))

/** Returns the smaller of two values. */
#define MIN(val0, val1) \
    (((val0) < (val1)) ? (val0) : (val1))

/** Clamps a value to the range [min, max]. */
#define CLAMP(val, min, max) \
    (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))

/** Converts an integer to a fixed-point Q format. */
#define TO_FIXED(val, shift) \
	((val) << (shift))

/** Converts an integer from a fixed-point Q format. */
#define FROM_FIXED(val, shift) \
	((val) >> (shift))

/** Multiplies two integers and converts the result from a fixed-point Q format. */
#define MUL_FIXED(val0, val1, shift) \
    FROM_FIXED((val0) * (val1), (shift))

// TODO: Inferred, but not used yet.
/** Converts an alpha in the range [0.0f, 1.0f] to a fixed-point alpha in Q3.12 format. */
#define FP_ALPHA(alpha) \
    (s16)((alpha) * TO_FIXED(1, Q12_SHIFT))

// TODO: Rename to `FP_ANGLE`?
/** Converts degrees to fixed-point angles in Q1.15 format (used at Q4.12 resolution). */
#define DEG_TO_FPA(deg) \
	(s16)((deg) * ((FP_ANGLE_COUNT) / 360.0f))

void func_80096C94(SVECTOR* vec, MATRIX* mtx); // Custom vwRotMatrix...?
void func_80096E78(SVECTOR* vec, MATRIX* mtx); // Another custom vwRotMatrix...]?

s32 shRsin(s32);
s32 shRcos(s32);

static inline s16 shAngleRegulate(s32 a)
{
    return (a << 20) >> 20;
}

static inline void Math_SVectorZero(SVECTOR* v)
{
    v->vx = 0;
    v->vy = 0;
    v->vz = 0;
}

static inline void Math_Vector3Zero(VECTOR3* v)
{
    v->vx = 0;
    v->vy = 0;
    v->vz = 0;
}

#endif
