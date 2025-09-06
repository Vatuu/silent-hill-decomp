#include "game.h"

#include <libetc.h>
#include <libpad.h>
#include <ctype.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"
#include "screens/stream/stream.h"

const s32 rodataPad_80024CA0 = 0;

void Gfx_BackgroundSpriteDraw(s_FsImageDesc* image) // 0x800314EC
{
    s32       baseYOffset;
    s32       tileX;
    s32       tileIndexX;
    s32       x;
    s32       y;
    GsOT*     ot;
    u32       textureShift;
    s32       texturePageX;
    u32       textureYOffset;
    DR_TPAGE* tPage;
    SPRT*     sprt;
    PACKET*   packet;

    ot             = (GsOT*)&D_800B7CC4[g_ObjectTableIdx];
    packet         = GsOUT_PACKET_P;
    baseYOffset    = -120 << (g_GameWork.gsScreenHeight_58A >> 8);
    textureShift   = image->tPage[0];
    texturePageX   = image->tPage[1];
    textureYOffset = image->v;

    for (y = 0; (g_GameWork.gsScreenHeight_58A >> 8) >= y; y++)
    {
        for (x = 0; ((g_GameWork.gsScreenWidth_588 - 1) >> (8 - textureShift)) >= x; x++)
        {
            sprt = (SPRT*)packet;

            addPrimFast(ot, sprt, 4);
            setRGBC0(sprt, g_BackgroundColor, g_BackgroundColor, g_BackgroundColor, FP_COLOR(0.390625f));

            if (y == 0)
            {
                setWH(sprt, 256, 256 - textureYOffset);
                *((u32*)&sprt->u0) = (textureYOffset << 8) + (getClut(image->clutX, image->clutY) << 16);
            }
            else
            {
                setWH(sprt, 256, 256);
                *((u32*)&sprt->u0) = getClut(image->clutX, image->clutY) << 16;
            }

            tileX = x << 8;

            setXY0Fast(sprt,
                       (tileX - (g_GameWork.gsScreenWidth_588 >> 1)) - (image->u << (2 - textureShift)),
                       baseYOffset + ((256 - textureYOffset) * y));

            packet += sizeof(SPRT);
            tPage   = (DR_TPAGE*)packet;

            tileIndexX = x << textureShift;
            setDrawTPage(tPage, 0, 1, getTPage(textureShift, 0, (texturePageX + tileIndexX) << 6, ((texturePageX << 4) & 0x100) + (y << 8)));

            AddPrim(ot, tPage);
            packet = (PACKET*)tPage + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P        = packet;
    g_SysWork.field_22A0 |= 1 << 0;
    g_BackgroundColor     = 0x80;
}

void Gfx_BackgroundSpritesTransition(s_FsImageDesc* image0, s_FsImageDesc* image1, s16 arg2) // 0x800317CC
{
    volatile int   pad;
    s32            i;
    s32            j;
    u32            color;
    s_FsImageDesc* image;
    POLY_FT4*      poly;
    u8             tPageY;
    s32            xOffset;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    for (i = 0; i < 3; i++)
    {
        image = (i > 0) ? image0 : image1;
        color = (i < 2) ? FP_MULTIPLY_PRECISE(arg2, 128, Q12_SHIFT) : 0x80;

        for (j = 0; j < 3; j++)
        {
            setPolyFT4(poly);

            setXY0Fast(poly, -160 + (128 * j), -120);
            setXY1Fast(poly, (128 * j) + ((j != 2) ? -32 : -96), -120);

            xOffset = 128 * j;

            setXY2Fast(poly, -160 + xOffset, 120);
            setXY3Fast(poly, xOffset + ((j != 2) ? -32 : -96), 120);

            *((u32*)&poly->u0) = (image->v << 8) + (getClut(image->clutX, image->clutY) << 16);

            tPageY = image->tPage[1];

            *((u32*)&poly->u1) = (image->v << 8) + ((j != 2) ? 128 : 64) +
                                 (getTPage(image->tPage[0], i + 1, (image->tPage[1] + j) << 6, (tPageY << 4) & 0x100) << 16);

            *((u16*)&poly->u2) = (image->v + 239) << 8;
            *((u16*)&poly->u3) = ((image->v + 239) << 8) + ((j != 2) ? 128 : 64);

            setSemiTrans(poly, i < 2);

            *((u16*)&poly->r0) = color + (color << 8);
            poly->b0           = color;

            addPrim(g_ObjectTable0[g_ObjectTableIdx].org, poly);
            poly++;
        }
    }

    g_SysWork.field_22A0 |= 1 << 0;
    GsOUT_PACKET_P = (PACKET*)poly;
}

void Gfx_BackgroundSpriteDraw_2(s_FsImageDesc* image) // 0x80031AAC
{
    volatile s32 pad; // TODO: Is there a better solution?
    s32          i;
    s32          xOffset;
    u8           tPageY;
    POLY_FT4*    poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    for (i = 0; i < 3; i++)
    {
        setPolyFT4(poly);
        setXY0Fast(poly, -160 + (128 * i), -120);
        setXY1Fast(poly, (128 * i) + ((i == 2) ? -96 : -32), -120);

        xOffset = 128 * i;

        setXY2Fast(poly, -160 + xOffset, 120);
        setXY3Fast(poly, xOffset + (i == 2 ? -96 : -32), 120);

        *((u32*)&poly->u0) = (image->v << 8) + (getClut(image->clutX, image->clutY) << 16);

        tPageY = image->tPage[1];

        *((u32*)&poly->u1) = (image->v << 8) + ((i == 2) ? 64 : 128) +
                             (getTPage(image->tPage[0], 0, (image->tPage[1] + i) << 6, (tPageY << 4) & 0x100) << 16);

        *((u16*)&poly->u2) = (image->v + 239) << 8;
        *((u16*)&poly->u3) = ((image->v + 239) << 8) + ((i == 2) ? 64 : 128);

        setSemiTrans(poly, 0);

        *((u16*)&poly->r0) = g_BackgroundColor + (g_BackgroundColor << 8);
        poly->b0           = g_BackgroundColor;

        addPrim(&g_ObjectTable0[g_ObjectTableIdx].org[2], poly);
        poly++;
    }

    GsOUT_PACKET_P        = (PACKET*)poly;
    g_SysWork.field_22A0 |= 1 << 0;
    g_BackgroundColor     = 0x80;
}

s32 Gfx_MotionBlur(s32 arg0) // 0x80031CCC
{
    s32       sp10;
    s32       i;
    s32       yOffset;
    s32       texUOffset;
    s32       tPageYOffset;
    s32       j;
    GsOT*     ot;
    SPRT*     sprt;
    DR_TPAGE* tPage;

    ot   = (GsOT*)&D_800B7CC4[g_ObjectTableIdx];
    sprt = (SPRT*)GsOUT_PACKET_P;
    sp10 = D_800C6E90;

    for (i = 0; (i == 0 || (sp10 != 0 && i == 1)); i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (sp10 != 0)
            {
                texUOffset   = (-(i == 0)) & 0x20;
                yOffset      = (i == 0) ? -224 : 0;
                tPageYOffset = i << 8;
            }
            else
            {
                yOffset      = -112;
                texUOffset   = (g_ObjectTableIdx == 0) << 5;
                tPageYOffset = g_ObjectTableIdx << 8;
            }

            addPrimFast(ot, sprt, 4);

            if ((VSync(-1) % arg0) == 0)
            {
                setRGBC0(sprt, FP_COLOR(0.49609375), FP_COLOR(0.49609375), FP_COLOR(0.49609375), PRIM_RECT | RECT_TEXTURE);
            }
            else
            {
                setRGBC0(sprt, FP_COLOR(0.5f), FP_COLOR(0.5f), FP_COLOR(0.5f), PRIM_RECT | RECT_TEXTURE);
            }

            setWH(sprt, 256, 224);
            *((u32*)&sprt->u0) = texUOffset << 8;

            setXY0Fast(sprt, (-g_GameWork.gsScreenWidth_588 / 2) + (j << 8), yOffset);

            sprt++;
            tPage = (DR_TPAGE*)sprt;

            setDrawTPage(tPage, 0, 1, getTPage(2, 0, (j << 8), tPageYOffset));
            AddPrim(ot, tPage);

            sprt = (PACKET*)sprt + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P = sprt;
    return 0;
}

void Gfx_DebugStringPosition(s16 x, s16 y) // 0x80031EFC
{
    #define OFFSET_X SCREEN_POSITION_X(50.0f)
    #define OFFSET_Y SCREEN_POSITION_Y(47.0f)

    if (x != NO_VALUE)
    {
        g_Gfx_DebugStringPosition0.vx =
        g_Gfx_DebugStringPosition1.vx = x - OFFSET_X;
    }

    if (y != NO_VALUE)
    {
        g_Gfx_DebugStringPosition1.vy = y - OFFSET_Y;
    }
}

void Gfx_DebugStringDraw(char* str)
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

    ot     = (GsOT*)&D_800B5C58[g_ObjectTableIdx];
    strCpy = str;
    packet = GsOUT_PACKET_P;
    posX   = g_Gfx_DebugStringPosition1.vx;
    posY   = g_Gfx_DebugStringPosition1.vy;

    while (*strCpy != 0)
    {
        charCode = *strCpy;
        switch (charCode)
        {
            default:
                glyphSprt = (SPRT_8*)packet;
                addPrimFast(ot, glyphSprt, 3);
                setRGBC0(glyphSprt, FP_COLOR(0.5f), FP_COLOR(0.5f), FP_COLOR(0.5f), 0x74);
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
                posX  = g_Gfx_DebugStringPosition0.vx;
                posY += GLYPH_SIZE_Y;
                break;
        }

        strCpy++;
        packet += sizeof(SPRT_8);
    }

    *((u32*)&g_Gfx_DebugStringPosition1) = (posX & 0xFFFF) + (posY << 16);
    tPage                                = (DR_TPAGE*)packet;

    setDrawTPage(tPage, 0, 1, 20);
    addPrim(ot, tPage);

    packet        += sizeof(DR_TPAGE);
    GsOUT_PACKET_P = packet;
}

char* Math_IntegerToString(s32 widthMin, s32 value) // 0x80032154
{
    s32   isNegative;
    char* str = PSX_SCRATCH_ADDR(0x1E);

    if (value < 0)
    {
        isNegative = 1;
        value      = -value;
    }
    else
    {
        isNegative = 0;
    }

    *str = 0;

    do
    {
        str--;
        widthMin--;
        *str = '0' + (value % 10);
        value /= 10;
    }
    while (value > 0);

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

void func_800321EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800321EC
{
    s32  quotient;
    s32  i;
    bool isNegative;
    s8*  str;

    for (i = 0; i < (arg0 - 1); i++)
    {
        g_Gfx_DebugStringPosition1.vx += 8;
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
        g_Gfx_DebugStringPosition1.vx -= 8;
    }

    str--;
    *str = arg2 + '0';

    if (isNegative != 0)
    {
        str--;
        *str                          = '-';
        g_Gfx_DebugStringPosition1.vx -= 8;
    }
}

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b) // 0x80032358
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(0);
}

void Gfx_ScreenRefresh(s32 screenWidth, s32 isInterlaced) // 0x800323C8
{
    DrawSync(0);
    Gfx_ClearRectInterlaced(0, 32, 320, 448, 0, 0, 0);
    Gfx_Init(screenWidth, isInterlaced);
}

void Gfx_Init(s32 screenWidth, s32 isInterlaced) // 0x80032428
{
    g_GameWork.gsScreenWidth_588  = screenWidth;
    g_GameWork.gsScreenHeight_58A = !isInterlaced ? FRAMEBUFFER_HEIGHT_PROGRESSIVE : FRAMEBUFFER_HEIGHT_INTERLACED;

    DrawSync(0);
    GsInitGraph2(g_GameWork.gsScreenWidth_588, g_GameWork.gsScreenHeight_58A, (isInterlaced | 0x4), 1, 0);
    GsDefDispBuff2(0, 32, 0, isInterlaced ? 32 : 256);

    D_800C6E8E =
    D_800C6E26 = FRAMEBUFFER_HEIGHT_PROGRESSIVE;

    GsInit3D();
    Settings_ScreenXYSet(g_GameWorkConst->config_0.optScreenPosX_1C, g_GameWorkConst->config_0.optScreenPosY_1D);
    GsSwapDispBuff();
    GsSwapDispBuff();
}

void Settings_ScreenXYSet(s32 x, s32 y) // 0x800324F4
{
    Settings_DispEnvXYSet(&GsDISPENV, x, y);
}

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y) // 0x80032524
{
    x = CLAMP(x, -11, 11);
    y = CLAMP(y, -8, 8);

    g_GameWorkConst->config_0.optScreenPosX_1C = x;
    g_GameWorkConst->config_0.optScreenPosY_1D = y;

    display->screen.x = g_GameWorkConst->config_0.optScreenPosX_1C;
    display->screen.y = g_GameWorkConst->config_0.optScreenPosY_1D + 8;
}

void func_800325A4(DR_MODE* arg0) // 0x800325A4
{
    if (IS_SCREEN_FADE_WHITE(g_Gfx_ScreenFade)) 
    {
        SetDrawMode(arg0, 0, 1, 32, NULL);
    }
    else 
    {
        SetDrawMode(arg0, 0, 1, 64, NULL);
    }
}

int Gfx_FadeInProgress() // 0x800325F8
{
    return FP_FLOAT_TO(1.0f, Q12_SHIFT) - g_PrevScreenFadeProgress;
}

void Gfx_FadeUpdate() // 0x8003260C
{
    s32      queueLength;
    s32      timeStep;
    GsOT*    ot;
    TILE*    tile;
    DR_MODE* drMode;

    drMode                   = &D_800A8E5C[g_ObjectTableIdx];
    tile                     = &D_800A8E74[g_ObjectTableIdx];
    g_PrevScreenFadeProgress = g_ScreenFadeProgress;

    switch (g_Gfx_ScreenFade)
    {
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, true):
            g_ScreenFadeProgress = 0;
            g_Gfx_ScreenFade++;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, true):
            func_800325A4(drMode);
            queueLength = Fs_QueueGetLength();

            if (g_ScreenFadeTimestep > FP_TIME(0.0f))
            {
                timeStep = g_ScreenFadeTimestep;
            }
            else
            {
                timeStep = FP_TIME(3.0f) / (queueLength + 1);
            }

            g_ScreenFadeProgress += FP_MULTIPLY_PRECISE(timeStep, g_DeltaTime1, Q12_SHIFT);

            if (g_ScreenFadeProgress >= (FP_TIME(1.0f) - 1))
            {
                g_ScreenFadeProgress = FP_TIME(1.0f) - 1;
                g_Gfx_ScreenFade++;
            }

            tile->r0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->g0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->b0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, true):
            g_ScreenFadeTimestep = FP_TIME(0.0f);

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, true):
            g_ScreenFadeProgress = 0xFFF;
            g_Gfx_ScreenFade++;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, true):
            func_800325A4(drMode);
            tile->r0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->g0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->b0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, true):
            func_800325A4(drMode);

            if (g_ScreenFadeTimestep > FP_TIME(0.0f))
            {
                timeStep = g_ScreenFadeTimestep;
            }
            else
            {
                timeStep = FP_TIME(3.0f);
            }

            g_ScreenFadeProgress -= FP_MULTIPLY_PRECISE(timeStep, g_DeltaTime1, Q12_SHIFT);

            if (g_ScreenFadeProgress <= 0)
            {
                g_ScreenFadeProgress = 0;
                g_Gfx_ScreenFade     = SCREEN_FADE_STATUS(ScreenFadeState_Reset, false);
                return;
            }

            tile->r0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->g0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            tile->b0 = FP_FROM(g_ScreenFadeProgress, Q4_SHIFT);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_Reset, false):
            g_ScreenFadeTimestep = FP_TIME(0.0f);
            g_ScreenFadeProgress = 0;
            g_Gfx_ScreenFade     = SCREEN_FADE_STATUS(ScreenFadeState_None, false);
            return;

        case SCREEN_FADE_STATUS(ScreenFadeState_None, false):
            return;
    }

    ot = &D_800B5C54[g_ObjectTableIdx];
    AddPrim(ot, tile);
    AddPrim(ot, drMode);
}

void Gfx_CutsceneCameraStateUpdate()
{
    void Gfx_BlackBorderDraw(POLY_G4* poly, s32 color)
    {
        s32 i;
        s32 color0;
        s32 color1;

        color0 = color >> 4;
        color1 = color >> 5;

        if (color == 4095)
        {
            color1 = 255;
        }

        for (i = 0; i < 2; i++)
        {
            poly[i * 2].r0 = color0;
            poly[i * 2].g0 = color0;
            poly[i * 2].b0 = color0;
            poly[i * 2].r1 = color0;
            poly[i * 2].g1 = color0;
            poly[i * 2].b1 = color0;
            poly[i * 2].r2 = color1;
            poly[i * 2].g2 = color1;
            poly[i * 2].b2 = color1;
            poly[i * 2].r3 = color1;
            poly[i * 2].g3 = color1;
            poly[i * 2].b3 = color1;
        }
    }

    GsOT*    ot;
    POLY_G4* poly;
    DR_MODE* drMode;

    drMode = &D_800A8E98[g_ObjectTableIdx];
    poly   = &D_800A8EB0[g_ObjectTableIdx];

    vcSetEvCamRate(D_800A8F40);

    if (g_SysWork.field_22A0 & (1 << 0))
    {
        return;
    }

    switch (g_SysWork.field_30)
    {
        case 18:
            g_SysWork.field_30++;

        case 19:
            D_800A8F40 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);

            if (D_800A8F40 >= 0xFFF)
            {
                D_800A8F40 = 0xFFF;
                g_SysWork.field_30++;
            }

            Gfx_BlackBorderDraw(poly, D_800A8F40);
            break;

        case 20:
        case 22:
            D_800A8F40 = 0xFFF;
            g_SysWork.field_30++;

        case 21:
            Gfx_BlackBorderDraw(poly, D_800A8F40);
            break;

        case 23:
            D_800A8F40 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);

            if (D_800A8F40 <= 0)
            {
                D_800A8F40         = 0;
                g_SysWork.field_30 = 0;
                return;
            }

            Gfx_BlackBorderDraw(poly, D_800A8F40);
            break;

        case 0:
            D_800A8F40            = 0;
            g_SysWork.field_30    = 1;
            g_SysWork.flags_22A4 &= ~(1 << 3);
            return;

        case 1:
            return;
    }

    ot = &D_800B5C50[g_ObjectTableIdx];
    AddPrim(ot, poly);
    AddPrim(ot, &poly[2]);
    AddPrim(ot, drMode);

    if (!(g_SysWork.flags_22A4 & 8))
    {
        vcChangeProjectionValue(g_GameWork.gsScreenHeight_58A + FP_MULTIPLY(377 - g_GameWork.gsScreenHeight_58A, D_800A8F40, Q12_SHIFT));
    }
}

void Gfx_VSyncCallback() // 0x80032b80
{
    g_Demo_FrameCount++;
    g_UnknownFrameCounter++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}
