#include "game.h"

#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

const s32 rodataPad_80024CA0 = 0;

void Screen_RectInterlacedClear(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b) // 0x80032358
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(SyncMode_Wait);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(SyncMode_Wait);
}

void Screen_Refresh(s32 screenWidth, bool isInterlaced) // 0x800323C8
{
    DrawSync(SyncMode_Wait);
    Screen_RectInterlacedClear(0, 32, 320, 448, 0, 0, 0);
    Screen_Init(screenWidth, isInterlaced);
}

void Screen_Init(s32 screenWidth, bool isInterlaced) // 0x80032428
{
    g_GameWork.gsScreenWidth_588  = screenWidth;
    g_GameWork.gsScreenHeight_58A = !isInterlaced ? FRAMEBUFFER_HEIGHT_PROGRESSIVE : FRAMEBUFFER_HEIGHT_INTERLACED;

    DrawSync(SyncMode_Wait);
    GsInitGraph2(g_GameWork.gsScreenWidth_588, g_GameWork.gsScreenHeight_58A, isInterlaced | 0x4, 1, 0);
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

void Screen_DisplayEnvXySet(DISPENV* displayEnv, s32 x, s32 y) // 0x80032524
{
    #define RANGE_X 11
    #define RANGE_Y 8

    x = CLAMP(x, -RANGE_X, RANGE_X);
    y = CLAMP(y, -RANGE_Y, RANGE_Y);

    g_GameWorkConst->config_0.optScreenPosX_1C = x;
    g_GameWorkConst->config_0.optScreenPosY_1D = y;

    displayEnv->screen.x = g_GameWorkConst->config_0.optScreenPosX_1C;
    displayEnv->screen.y = g_GameWorkConst->config_0.optScreenPosY_1D + RANGE_Y;
}

void Screen_FadeDrawModeSet(DR_MODE* drMode) // 0x800325A4
{
    if (IS_SCREEN_FADE_WHITE(g_Screen_FadeStatus)) 
    {
        SetDrawMode(drMode, 0, 1, 32, NULL);
    }
    else 
    {
        SetDrawMode(drMode, 0, 1, 64, NULL);
    }
}

q19_12 Screen_FadeInProgressGet() // 0x800325F8
{
    return Q12(1.0f) - g_PrevScreenFadeProgress;
}

void Screen_FadeUpdate() // 0x8003260C
{
    s32      queueLength;
    s32      timeStep;
    GsOT*    ot;
    TILE*    tile;
    DR_MODE* drMode;

    drMode                   = &D_800A8E5C[g_ActiveBufferIdx];
    tile                     = &D_800A8E74[g_ActiveBufferIdx];
    g_PrevScreenFadeProgress = g_ScreenFadeProgress;

    switch (g_Screen_FadeStatus)
    {
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, true):
            g_ScreenFadeProgress = Q12(0.0f);
            g_Screen_FadeStatus++;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, true):
            Screen_FadeDrawModeSet(drMode);
            queueLength = Fs_QueueGetLength();

            if (g_ScreenFadeTimeStep > Q12(0.0f))
            {
                timeStep = g_ScreenFadeTimeStep;
            }
            else
            {
                timeStep = Q12(3.0f) / (queueLength + 1);
            }

            g_ScreenFadeProgress += FP_MULTIPLY_PRECISE(timeStep, g_DeltaTime1, Q12_SHIFT);
            if (g_ScreenFadeProgress >= (Q12(1.0f) - 1))
            {
                g_ScreenFadeProgress = Q12(1.0f) - 1;
                g_Screen_FadeStatus++;
            }

            tile->r0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->g0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->b0 = Q12_TO_Q8(g_ScreenFadeProgress);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, true):
            g_ScreenFadeTimeStep = Q12(0.0f);

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, true):
            g_ScreenFadeProgress = Q12(1.0f) - 1;
            g_Screen_FadeStatus++;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, true):
            Screen_FadeDrawModeSet(drMode);
            tile->r0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->g0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->b0 = Q12_TO_Q8(g_ScreenFadeProgress);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, true):
            Screen_FadeDrawModeSet(drMode);

            if (g_ScreenFadeTimeStep > Q12(0.0f))
            {
                timeStep = g_ScreenFadeTimeStep;
            }
            else
            {
                timeStep = Q12(3.0f);
            }

            g_ScreenFadeProgress -= FP_MULTIPLY_PRECISE(timeStep, g_DeltaTime1, Q12_SHIFT);

            if (g_ScreenFadeProgress <= Q12(0.0f))
            {
                g_ScreenFadeProgress = Q12(0.0f);
                g_Screen_FadeStatus  = SCREEN_FADE_STATUS(ScreenFadeState_Reset, false);
                return;
            }

            tile->r0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->g0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->b0 = Q12_TO_Q8(g_ScreenFadeProgress);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_Reset, false):
            g_ScreenFadeTimeStep = Q12(0.0f);
            g_ScreenFadeProgress = Q12(0.0f);
            g_Screen_FadeStatus  = SCREEN_FADE_STATUS(ScreenFadeState_None, false);
            return;

        case SCREEN_FADE_STATUS(ScreenFadeState_None, false):
            return;
    }

    ot = &g_OtTags0[g_ActiveBufferIdx][5];
    AddPrim(ot, tile);
    AddPrim(ot, drMode);
}

void Screen_CutsceneCameraStateUpdate() // 0x80032904
{
    void Screen_BlackBorderDraw(POLY_G4* poly, s32 color)
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

            Screen_BlackBorderDraw(poly, D_800A8F40);
            break;

        case 20:
        case 22:
            D_800A8F40 = 0xFFF;
            g_SysWork.field_30++;

        case 21:
            Screen_BlackBorderDraw(poly, D_800A8F40);
            break;

        case 23:
            D_800A8F40 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);

            if (D_800A8F40 <= 0)
            {
                D_800A8F40         = 0;
                g_SysWork.field_30 = 0;
                return;
            }

            Screen_BlackBorderDraw(poly, D_800A8F40);
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

    if (!(g_SysWork.flags_22A4 & (1 << 3)))
    {
        vcChangeProjectionValue(g_GameWork.gsScreenHeight_58A + FP_MULTIPLY(377 - g_GameWork.gsScreenHeight_58A, D_800A8F40, Q12_SHIFT));
    }
}

void Screen_VSyncCallback() // 0x80032B80
{
    g_Demo_FrameCount++;
    g_UnknownFrameCounter++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}
