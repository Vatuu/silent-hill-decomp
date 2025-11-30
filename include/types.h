#ifndef _TYPES_H
#define _TYPES_H

#include "psyq/sys/types.h"

#ifndef NULL
#define NULL 0
#endif

typedef signed char        byte;
typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char        q0_8;   // Q0.8 fixed-point.
typedef signed short       q11_4;  // Q11.4 fixed-point.
typedef signed short       q7_8;   // Q7.8 fixed-point.
typedef signed short       q3_12;  // Q3.12 fixed-point.
typedef signed int         q27_4;  // Q27.4 fixed-point.
typedef signed int         q25_6;  // Q25.6 fixed-point.
typedef signed int         q23_8;  // Q23.8 fixed-point.
typedef signed int         q19_12; // Q19.12 fixed-point.
typedef signed long long   q51_12; // Q51.12 fixed-point.
typedef unsigned short     q8_8;   // Q8.8 fixed-point.
typedef unsigned short     q4_12;  // Q4.12 fixed-point.
typedef unsigned int       q24_8;  // Q24.8 fixed-point.
typedef unsigned int       q20_12; // Q20.12 fixed-point.

#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

#define NO_VALUE -1

/** @brief Smaller `VECTOR` with padding removed. Used for fixed-point positions. */
typedef struct
{
    long vx;
    long vy;
    long vz;
} VECTOR3;

/** @brief Smaller `SVECTOR` with padding removed. Used for fixed-point rotations. */
typedef struct
{
    s16 vx;
    s16 vy;
    s16 vz;
} SVECTOR3;

/** @brief `DVECTOR` variant with a `vz` component instead of `vy`. */
typedef struct
{
    s16 vx;
    s16 vz;
} DVECTOR_XZ;

#endif
