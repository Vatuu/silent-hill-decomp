#ifndef _GPU_H
#define _GPU_H

#include "common.h"
#include <LIBGTE.H>
#include <LIBGPU.H>

/** setRECT() does not produce a match in main(), so we have this */
#define SET_RECT(r, x, y, w, h) \
    ((u32 *)(r))[0] = ((x) | ((y) << 16)), ((u32 *)(r))[1] = ((w) | ((h) << 16))

/** same as above */
#define SET_DR_TPAGE(t)

#endif
