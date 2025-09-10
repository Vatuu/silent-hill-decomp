#include "game.h"

#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

const s32 rodataPad_80024CA0 = 0;

void Screen_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b) // 0x80032358
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(0);
}

void Screen_Refresh(s32 screenWidth, s32 isInterlaced) // 0x800323C8
{
    DrawSync(0);
    Screen_ClearRectInterlaced(0, 32, 320, 448, 0, 0, 0);
    Screen_Init(screenWidth, isInterlaced);
}

void Screen_Init(s32 screenWidth, s32 isInterlaced) // 0x80032428
{
    g_GameWork.gsScreenWidth_588  = screenWidth;
    g_GameWork.gsScreenHeight_58A = !isInterlaced ? FRAMEBUFFER_HEIGHT_PROGRESSIVE : FRAMEBUFFER_HEIGHT_INTERLACED;

    DrawSync(0);
    GsInitGraph2(g_GameWork.gsScreenWidth_588, g_GameWork.gsScreenHeight_58A, (isInterlaced | 0x4), 1, 0);
    GsDefDispBuff2(0, 32, 0, isInterlaced ? 32 : 256);

    D_800C6E8E =
    D_800C6E26 = FRAMEBUFFER_HEIGHT_PROGRESSIVE;

    GsInit3D();
    Screen_XyPositionSet(g_GameWorkConst->config_0.optScreenPosX_1C, g_GameWorkConst->config_0.optScreenPosY_1D);
    GsSwapDispBuff();
    GsSwapDispBuff();
}

void Screen_XyPositionSet(s32 x, s32 y) // 0x800324F4
{
    Screen_DisplayEnvXySet(&GsDISPENV, x, y);
}

void Screen_DisplayEnvXySet(DISPENV* display, s32 x, s32 y) // 0x80032524
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

s32 Gfx_FadeInProgress() // 0x800325F8
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

    drMode                   = &D_800A8E5C[g_ActiveBufferIdx];
    tile                     = &D_800A8E74[g_ActiveBufferIdx];
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

    ot = &g_OtTags0[g_ActiveBufferIdx][5];
    AddPrim(ot, tile);
    AddPrim(ot, drMode);
}

void Gfx_CutsceneCameraStateUpdate() // 0x80032904
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

    drMode = &D_800A8E98[g_ActiveBufferIdx];
    poly   = &D_800A8EB0[g_ActiveBufferIdx];

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

    ot = &g_OtTags0[g_ActiveBufferIdx][4];
    AddPrim(ot, poly);
    AddPrim(ot, &poly[2]);
    AddPrim(ot, drMode);

    if (!(g_SysWork.flags_22A4 & 8))
    {
        vcChangeProjectionValue(g_GameWork.gsScreenHeight_58A + FP_MULTIPLY(377 - g_GameWork.gsScreenHeight_58A, D_800A8F40, Q12_SHIFT));
    }
}

void Gfx_VSyncCallback() // 0x80032B80
{
    g_Demo_FrameCount++;
    g_UnknownFrameCounter++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}
