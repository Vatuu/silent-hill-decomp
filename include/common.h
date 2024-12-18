#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "types.h"

#define ALIGN(x, a) (((u32)(x) + ((a)-1)) & ~((a)-1))

#endif
