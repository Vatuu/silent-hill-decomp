#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "types.h"

#define PSX_SCRATCH ((void*)0x1F800000)

#define ALIGN(x, a) (((u32)(x) + ((a)-1)) & ~((a)-1))

#define SECTION(x) __attribute__((section(x)))

#define STATIC_ASSERT(COND, MSG) typedef char static_assertion_##MSG[(COND) ? 1 : -1]
#define STATIC_ASSERT_SIZEOF(TYPE, SIZE) typedef char static_assertion_sizeof_##TYPE[(sizeof(TYPE) == (SIZE)) ? 1 : -1]

#define CLAMP(val, min, max) \
    (((val) < (min)) ? (min) : ((val) > (max)) ? (max) : (val))

#endif
