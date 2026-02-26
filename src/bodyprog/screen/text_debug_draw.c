#include "game.h"

#include "bodyprog/screen/screen_data.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/text/text_debug_draw.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"

#include <ctype.h>

// ========================================
// STATIC VARIABLES
// ========================================

static DVECTOR g_Text_Debug_PositionSet0;
static DVECTOR g_Text_Debug_PositionSet1;

// ========================================
// TEXT (DEBUG) DRAW
// ========================================

void Text_Debug_PositionSet(s16 x, s16 y) // 0x80031EFC
{
    #define OFFSET_X SCREEN_POSITION_X(50.0f)
    #define OFFSET_Y SCREEN_POSITION_Y(47.0f)

    if (x != NO_VALUE)
    {
        g_Text_Debug_PositionSet0.vx =
        g_Text_Debug_PositionSet1.vx = x - OFFSET_X;
    }

    if (y != NO_VALUE)
    {
        g_Text_Debug_PositionSet1.vy = y - OFFSET_Y;
    }
}

void Text_Debug_Draw(char* str) // 0x80031F40
{
    #define GLYPH_SIZE_X 8
    #define GLYPH_SIZE_Y 8
    #define ATLAS_BASE_Y 240

    #define SET_SPRT_U_V_CLUT(sprt, charIdx, clut)                                                                                           \
        *((u32*)&(sprt)->u0) = (((charIdx) & 0x1F) * GLYPH_SIZE_X)                       + /* `u0`:   column in 32-column atlas. */          \
                               (((((charIdx) >> 5) * GLYPH_SIZE_Y) + ATLAS_BASE_Y) << 8) + /* `v0`:   row in 32-column atlas with offset. */ \
                               ((clut) << 16)                                              /* `clut`: packed magic value. */

    s32       posX;
    s32       posY;
    s32       charIdx;
    GsOT*     ot;
    u8*       strCpy;
    s32       charCode;
    PACKET*   packet;
    SPRT_8*   glyphSprt;
    DR_TPAGE* tPage;

    ot     = (GsOT*)&g_OtTags0[g_ActiveBufferIdx][6];
    strCpy = str;
    packet = GsOUT_PACKET_P;
    posX   = g_Text_Debug_PositionSet1.vx;
    posY   = g_Text_Debug_PositionSet1.vy;

    while (*strCpy != 0)
    {
        charCode = *strCpy;
        switch (charCode)
        {
            default:
                glyphSprt = (SPRT_8*)packet;
                addPrimFast(ot, glyphSprt, 3);
                setRGBC0(glyphSprt, Q8_COLOR(0.5f), Q8_COLOR(0.5f), Q8_COLOR(0.5f), 0x74);
                setXY0Fast(glyphSprt, posX, posY);

                charIdx = (char)toupper(charCode) - '*';
                SET_SPRT_U_V_CLUT(glyphSprt, charIdx, 0x7FD2); // TODO: Demagic CLUT arg.

            case 95:
            case 32:
            case 9:
            case 11:
                posX += GLYPH_SIZE_X;
                break;

            case 126:
                posX -= GLYPH_SIZE_X;
                break;

            case 10:
                posX  = g_Text_Debug_PositionSet0.vx;
                posY += GLYPH_SIZE_Y;
                break;
        }

        strCpy++;
        packet += sizeof(SPRT_8);
    }

    *((u32*)&g_Text_Debug_PositionSet1) = (posX & 0xFFFF) + (posY << 16);
    tPage                                = (DR_TPAGE*)packet;

    setDrawTPage(tPage, 0, 1, getTPageN(0, 0, 4, 1));
    addPrim(ot, tPage);

    packet        += sizeof(DR_TPAGE);
    GsOUT_PACKET_P = packet;
}

char* Text_Debug_IntToStringConversion(s32 widthMin, s32 val) // 0x80032154
{
    bool  isNegative;
    char* str;

    str = PSX_SCRATCH_ADDR(0x1E);

    if (val < 0)
    {
        isNegative = true;
        val        = -val;
    }
    else
    {
        isNegative = false;
    }

    *str = 0;

    do
    {
        str--;
        widthMin--;
        *str = '0' + (val % 10);
        val /= 10;
    }
    while (val > 0);

    if (isNegative)
    {
        str--;
        *str = '-';
        widthMin--;
    }

    while (widthMin > 0)
    {
        str--;
        *str = '\v';
        widthMin--;
    }

    return str;
}

#if VERSION_DATE <= VERSION_DATE_PROTO_981216
void Text_Debug_DecToStringConversion(s32 offsetX, s32 fracDigits, q19_12 val) // 0x8002BCAC in 98-12-16, not included in retail.
{
    s32 i;

    for (i = 0; i <= fracDigits; i++)
    {
        val *= 10;
    }

    func_800321EC((offsetX - fracDigits) - ((fracDigits > 0) ? 1 : 0), fracDigits, val / Q12(1.0f), 1);
}
#endif

void func_800321EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800321EC
{
    s32  quotient;
    s32  i;
    bool isNegative;
    s8*  str;

    for (i = 0; i < (arg0 - 1); i++)
    {
        g_Text_Debug_PositionSet1.vx += 8;
    }

    str  = PSX_SCRATCH_ADDR(0x2F);
    *str = 0;

    if (arg2 < 0)
    {
        isNegative = true;
        arg2       = -arg2;
    }
    else
    {
        isNegative = false;
    }

    if (arg3 != 0)
    {
        arg2 = (arg2 + 5) / 10;
    }

    if (arg1 != 0)
    {
        for (i = 0; i < arg1; i++)
        {
            str--;
            *str = (arg2 % 10) + '0';
            arg2 /= 10;
        }

        str--;
        *str = '.';
    }

    while (arg2 >= 10)
    {
        str--;
        quotient                      = arg2 / 10;
        *str                          = (arg2 - (quotient * 10)) + '0';
        arg2                          = quotient;
        g_Text_Debug_PositionSet1.vx -= 8;
    }

    str--;
    *str = arg2 + '0';

    if (isNegative != 0)
    {
        str--;
        *str                          = '-';
        g_Text_Debug_PositionSet1.vx -= 8;
    }
}
