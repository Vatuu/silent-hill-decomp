#ifndef _GPU_H
#define _GPU_H

#include "common.h"

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#define RECT_EDGE_COUNT  4
#define BOX_CORNER_COUNT 8

/** Primitive types */
enum PrimType
{
    PRIM_POLY = 0x20, /** Polygon (`POLY`). */
    PRIM_LINE = 0x40, /** Line (`LINE`). */
    PRIM_RECT = 0x60  /** Rectangle (`TILE` or `SPRT`). */
};

/** Rectangle flags */
enum PrimRectFlags
{
    RECT_SIZE_16  = (1 << 3) | (1 << 4), /** Rectangle is 16x16 (`TILE_16` or `SPRT_16`). */
    RECT_SIZE_8   = 1 << 4,              /** Rectangle is 8x8 (`TILE_8` or `SPRT_8`). */
    RECT_SIZE_1   = 1 << 3,              /** Rectangle is 1x1 (`TILE_1`). */
    RECT_TEXTURE  = 1 << 2,              /** Rectangle is textured (is a `SPRT`). */
    RECT_BLEND    = 1 << 1,              /** Semi-transparency flag. */
    RECT_MODULATE = 1 << 0               /** Use primitive color to modulate texture. */
};

typedef struct _Line2d
{
    DVECTOR vertex0_0;
    DVECTOR vertex1_4;
} s_Line2d;
STATIC_ASSERT_SIZEOF(s_Line2d, 8);

typedef struct _Triangle2d
{
    DVECTOR vertex0_0;
    DVECTOR vertex1_4;
    DVECTOR vertex2_8;
} s_Triangle2d;
STATIC_ASSERT_SIZEOF(s_Triangle2d, 12);

typedef struct _Quad2d
{
    DVECTOR vertex0_0;
    DVECTOR vertex1_4;
    DVECTOR vertex2_8;
    DVECTOR vertex3_C;
} s_Quad2d;
STATIC_ASSERT_SIZEOF(s_Quad2d, 16);

typedef struct _ColoredLine2d
{
    s_Line2d line_0;
    u16      r_8;
    u16      g_A;
    u16      b_C;
    u16      pad_E; // Maybe 4th component of a RGB+code struct?
} s_ColoredLine2d;
STATIC_ASSERT_SIZEOF(s_ColoredLine2d, 16);

typedef struct _LineBorder
{
    s_Line2d lines_0[RECT_EDGE_COUNT];
} s_LineBorder;
STATIC_ASSERT_SIZEOF(s_LineBorder, 32);

typedef struct _QuadBorder
{
    s_Quad2d quads_0[RECT_EDGE_COUNT];
} s_QuadBorder;
STATIC_ASSERT_SIZEOF(s_QuadBorder, 64);

typedef struct
{
    u8 r;
    u8 g;
    u8 b;
    u8 p;
} s_PrimColor;

/** @brief Same as `getTPage`, but `xn` and `yn` are indices instead of VRAM coordinates. */
#define getTPageN(tp, abr, xn, yn) \
    ((((tp) & 0x3) << 7)|(((abr) & 0x3) << 5)|((xn) & 0xF)|(((yn) & 0x1) << 4))

/** @brief Same as `setRECT`, but uses 2x 32-bit stores instead of 4x 16-bit stores. */
#define setRECTFast(r, x, y, w, h) \
    ((u32*)(r))[0] = ((x) | ((y) << 16)), \
    ((u32*)(r))[1] = ((w) | ((h) << 16))

/** @brief Same as `setXY0`, but uses 1x 32-bit store instead of 2x 16-bit stores. */
#define setXY0Fast(p, x, y) \
    *(u32*)(&(p)->x0) = (((x) & 0xFFFF) + ((y) << 16))

#define setXY1Fast(p, x, y) \
    *(u32*)(&(p)->x1) = (((x) & 0xFFFF) + ((y) << 16))

#define setXY2Fast(p, x, y) \
    *(u32*)(&(p)->x2) = (((x) & 0xFFFF) + ((y) << 16))

#define setXY3Fast(p, x, y) \
    *(u32*)(&(p)->x3) = (((x) & 0xFFFF) + ((y) << 16))

/** @brief Same as `setWH`, but uses 1x 32-bit store instead of 2x 16-bit stores. */
#define setWHFast(p, _w, _h) \
    *(u32*)(&(p)->w) = (((_w) & 0xFFFF) + ((_h) << 16))

/** @brief Combines `setUV0` and `setClut` into a single 32-bit stores; also does not call `GetClut`. */
#define setUV0AndClut(p, u, v, cx, cy) \
    *(u32*)(&(p)->u0) = (((((cy) << 6) | (((cx) >> 4) & 0x3F)) << 16) | ((v) << 8) | (u))

/** @brief Combines `setcode` and `setRGB0`. */
#define setCodeWord(p, c, rgb24) \
    *(u32*)(((u8*)(p)) + 4) = (((c) << 24) | ((rgb24) & 0xFFFFFF))

/** @brief Combines `setRGB0` and `setcode` */
#define setRGBC0(prim, r, g, b, code) \
    *(u32*)(&(prim)->r0) = (((r + (g << 8)) + (b << 16)) + (code << 24))

/** @brief Combines `setRGB1` and applies code to padding component? */
#define setRGBC1(prim, r, g, b, code) \
    *(u32*)(&(prim)->r1) = (((r + (g << 8)) + (b << 16)) + (code << 24))

/** @brief Combines `setRGB2` and applies code to padding component? */
#define setRGBC2(prim, r, g, b, code) \
    *(u32*)(&(prim)->r2) = (((r + (g << 8)) + (b << 16)) + (code << 24))

/** @brief Combines `addPrim` and `setlen`. */
#define addPrimFast(ot, p ,_len) \
    (((p)->tag = getaddr(ot) | (_len << 24)), setaddr(ot, p))

extern _GsFCALL GsFCALL4;

void GsTMDfastG3LFG(void* op, VERT* vp, VERT* np, PACKET* pk, int n, int shift, GsOT* ot, u_long* scratch);
void GsTMDfastTG3LFG(void* op, VERT* vp, VERT* np, PACKET* pk, int n, int shift, GsOT* ot, u_long* scratch);
void GsTMDfastG4LFG(void* op, VERT* vp, VERT* np, PACKET* pk, int n, int shift, GsOT* ot, u_long* scratch);
void GsTMDfastTG4LFG(void* op, VERT* vp, VERT* np, PACKET* pk, int n, int shift, GsOT* ot, u_long* scratch);

/** @brief Sets the DQA register in the GTE. Not part of Psy-Q for some reason. */
#define gte_lddqa(r0) __asm__ volatile( \
    "ctc2  %0, $27"                     \
    :                                   \
    : "r"(r0))

/** @brief Sets the DQB register in the GTE to zero. */
#define gte_lddqb_0() __asm__ volatile( \
    "ctc2  $zero, $28")

/** @brief Zeroes transfer vector in the GTE. */
#define gte_ldtr_0() __asm__ volatile( \
    "ctc2  $zero, $5;"                 \
    "ctc2  $zero, $6;"                 \
    "ctc2  $zero, $7")

#endif
