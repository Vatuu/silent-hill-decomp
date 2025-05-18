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

typedef signed short       q3_12;  // Q3.12 fixed-point.
typedef signed int         q19_12; // Q19.12 fixed-point.
typedef unsigned int       q20_12; // Q20.12 fixed-point.

#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

#define NO_VALUE -1

// Smaller `VECTOR` with padding removed. Seems to be used frequently.
typedef struct
{
    long vx;
    long vy;
    long vz;
} VECTOR3;

// Smaller `SVECTOR` with padding removed. Seems to be used frequently.
typedef struct
{
    short vx;
    short vy;
    short vz;
} SVECTOR3;

#endif
