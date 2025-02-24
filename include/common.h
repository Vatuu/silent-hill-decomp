#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "types.h"

#define PSX_SCRATCH ((void*)0x1F800000)

#define ALIGN(x, a) (((u32)(x) + ((a)-1)) & ~((a)-1))

#define SECTION(x) __attribute__((section(x)))

#endif
