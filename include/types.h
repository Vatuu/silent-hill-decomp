#ifndef TYPES_H
#define TYPES_H

#include "psyq/SYS/TYPES.H"

#ifndef NULL
#define NULL 0
#endif

typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char byte;

#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

#endif
