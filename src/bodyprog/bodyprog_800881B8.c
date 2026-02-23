#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

// ========================================
// ADDITIONAL 2D GFX
// ========================================

void Gfx_CursorDraw(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB) // 0x800881B8
{
    POLY_FT4* poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;
    setPolyFT4(poly);

    setXY0Fast(poly, x0 - x1, y0 - y1);
    setXY1Fast(poly, x0 + x1, y0 - y1);
    setXY2Fast(poly, x0 - x1, y0 + y1);
    setXY3Fast(poly, x0 + x1, y0 + y1);

    *(u32*)(&poly->u0) = arg4 + (arg5 << 8) + (getClut(arg9, argA) << 16);
    *(u32*)(&poly->u1) = (arg4 + arg6) + (arg5 << 8) + (getTPage(0, 0, argB << 6, (((argB >> 4) & 1) << 8)) << 16);
    *(u16*)(&poly->u2) = arg4 + ((arg5 + arg7) << 8);
    *(u16*)(&poly->u3) = (arg4 + arg6) + ((arg5 + arg7) << 8);

    *(u16*)(&poly->r0) = arg8 + (arg8 << 8);
    poly->b0 = arg8;

    setSemiTrans(poly, false);

    addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, poly);
    poly++;

    GsOUT_PACKET_P = (PACKET*)poly;
}

void Map_BoxOutlineDraw(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) // 0x80088370
{
    s32      iVar1;
    s16      iVar4;
    u16      uVar6[2];
    s16      sVar5[2];
    s32      i;
    LINE_F3* line;
    s32      temp;
    s16      temp2;
    s32      temp_v0;

    line = (LINE_F3*)GsOUT_PACKET_P;

    for (i = 0; i < 5; i++)
    {
        if (arg0 > 0)
        {
            iVar4 = CLAMP_LOW_THEN_MIN(FP_TO(arg0 - (i * Q12(0.5f)) / 5, Q12_SHIFT) /  Q12(0.5f), 0,  Q12(1.0f));
        }
        else
        {
            iVar4 = -arg0;
        }

        iVar1   = iVar4;
        temp_v0 = Q12(1.0f) - iVar1;

        uVar6[0] = Q12_MULT_PRECISE(arg1, temp_v0) + Q12_MULT_PRECISE(arg5, iVar1);
        sVar5[0] = Q12_MULT_PRECISE(arg2, temp_v0) + Q12_MULT_PRECISE(arg6, iVar1);

        temp2    = uVar6[0] + Q12_MULT_PRECISE(arg3, temp_v0);
        uVar6[1] = Q12_MULT_PRECISE(arg7, iVar1) + temp2;

        temp2    = sVar5[0] + Q12_MULT_PRECISE(arg4, temp_v0);
        sVar5[1] = Q12_MULT_PRECISE(arg8, iVar1) + temp2;

        setLineF3(line);
        setXY0Fast(line, uVar6[0], sVar5[0]);
        setXY1Fast(line, uVar6[1], sVar5[0]);
        setXY2Fast(line, uVar6[1], sVar5[1]);

        setSemiTrans(line, 0);

        temp = 0x80 - ((i << 6) / 5);

        *(u16*)(&line->r0) = 0;
        line->b0           = temp;

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, line);

        line[1] = line[0];
        line[2] = line[1];
        line[3] = line[2];

        line++;

        setXY0Fast(line, uVar6[0], sVar5[0] - 1);
        setXY1Fast(line, uVar6[1], sVar5[0] - 1);
        setXY2Fast(line, uVar6[1], sVar5[1] + 1);

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, line);

        line++;

        setXY0Fast(line, uVar6[1], sVar5[1]);
        setXY1Fast(line, uVar6[0], sVar5[1]);
        setXY2Fast(line, uVar6[0], sVar5[0]);

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, line);

        line++;

        setXY0Fast(line, uVar6[1], sVar5[1] + 1);
        setXY1Fast(line, uVar6[0], sVar5[1] + 1);
        setXY2Fast(line, uVar6[0], sVar5[0] - 1);

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, line);
        line++;
    }

    GsOUT_PACKET_P = line;
}
