#ifndef _GPU_H
#define _GPU_H

#include "common.h"

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/** Primitive types */
enum PrimType
{
    PRIM_POLY = 0x20, /** Polygon (`POLY`) */
    PRIM_LINE = 0x40, /** Line (`LINE`) */
    PRIM_RECT = 0x60  /** Rectangle (`TILE` or `SPRT`) */
};

/** Rectangle flags */
enum PrimRectFlags
{
    RECT_SIZE_16  = 0x18, /** Rectangle is 16x16 (`TILE_16` or `SPRT_16`). */
    RECT_SIZE_8   = 0x10, /** Rectangle is 8x8 (`TILE_8` or `SPRT_8`). */
    RECT_SIZE_1   = 0x08, /** Rectangle is 1x1 (`TILE_1`). */
    RECT_TEXTURE  = 0x04, /** Rectangle is textured (is a `SPRT`). */
    RECT_BLEND    = 0x02, /** Semi-transparency flag. */
    RECT_MODULATE = 0x01  /** Use primitive color to modulate texture. */
};

/** Same as `getTPage()`, but `xn` and `yn` are indices instead of VRAM coordinates. */
#define getTPageN(tp, abr, xn, yn) \
    ((((tp) & 0x3) << 7)|(((abr) & 0x3) << 5)|((xn) & 0xF)|(((yn) & 1) << 4))

/** Same as `setRECT()`, but uses 2x 32-bit stores instead of 4x 16-bit stores. */
#define setRECTFast(r, x, y, w, h) \
    ((u32*)(r))[0] = ((x) | ((y) << 16)), \
    ((u32*)(r))[1] = ((w) | ((h) << 16))

/** Same as `setXY0()`, but uses 1x 32-bit store instead of 2x 16-bit stores. */
#define setXY0Fast(p, x, y) \
    *(u32*)(&(p)->x0) = (((x) & 0xFFFF) + ((y) << 16))

/** Same as `setWH()`, but uses 1x 32-bit store instead of 2x 16-bit stores. */
#define setWHFast(p, _w, _h) \
    *(u32*)(&(p)->w) = (((_w) & 0xFFFF) + ((_h) << 16))

/** Combines `setUV0()` and `setClut()` into a single 32-bit stores; also does not call `GetClut()`. */
#define setUV0AndClut(p, u, v, cx, cy) \
    *(u32*)(&(p)->u0) = (((((cy) << 6) | (((cx) >> 4) & 0x3F)) << 16) | ((v) << 8) | (u))

/** Combines `setcode()` and `setRGB0()`. */
#define setCodeWord(p, c, rgb24) \
    *(u32*)(((u8*)(p)) + 4) = (((c) << 24) | ((rgb24) & 0xFFFFFF))

/** Combines `addPrim()` and `setlen()`. */
#define addPrimFast(ot, p ,_len) \
    (((p)->tag = getaddr(ot) | (_len << 24)), setaddr(ot, p))

#endif
