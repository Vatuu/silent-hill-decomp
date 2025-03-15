#ifndef _COMMON_H
#define _COMMON_H

#include "include_asm.h"
#include "types.h"

#define PSX_SCRATCH ((void*)0x1F800000)

#define ALIGN(x, a) \
    (((u32)(x) + ((a)-1)) & ~((a)-1))

#define SECTION(x) \
    __attribute__((section(x)))

#define STATIC_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]

#define STATIC_ASSERT_SIZEOF(type, size) \
    typedef char static_assertion_sizeof_##type[(sizeof(type) == (size)) ? 1 : -1]

#endif
