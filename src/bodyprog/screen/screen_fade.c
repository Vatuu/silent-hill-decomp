#include "game.h"

#include <libetc.h>
#include <libgs.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

const s32 rodataPad_80024CA0 = 0;

q19_12 g_PrevScreenFadeProgress;

s32 pad_bss_0x800B5C2C;

q19_12 g_ScreenFadeTimestep;

DR_MODE D_800A8E5C[] = {
    { 0x3000000, { 0xE1000240, 0x0 } },
    { 0x3000000, { 0xE1000240, 0x0 } }
};

TILE D_800A8E74[] = {
    { 0x3000000, 255, 0, 0, 0x62, -320, -240, 640, 480 },
    { 0x3000000, 255, 0, 0, 0x62, -320, -240, 640, 480 }
};

q19_12 g_ScreenFadeProgress = Q12(0.0f);

DR_MODE D_800A8E98[] = {
    { 0x3000000, { 0xE1000240, 0x0 } },
    { 0x3000000, { 0xE1000240, 0x0 } }
};

// TODO: Make a macro?
POLY_G4 D_800A8EB0[] = {
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0xFFA0,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0xFFA0
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0xFFA0,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0xFFA0
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x60
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x60
    }
};

q19_12 g_BlackBorderShade = Q12(0.0f);

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

q19_12 Screen_FadeInProgressGet(void) // 0x800325F8
{
    return Q12(1.0f) - g_PrevScreenFadeProgress;
}

void Screen_FadeUpdate(void) // 0x8003260C
{
    s32      queueLength;
    s32      timestep;
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

            if (g_ScreenFadeTimestep > Q12(0.0f))
            {
                timestep = g_ScreenFadeTimestep;
            }
            else
            {
                timestep = Q12(3.0f) / (queueLength + 1);
            }

            g_ScreenFadeProgress += Q12_MULT_PRECISE(timestep, g_DeltaTimeRaw);
            if (g_ScreenFadeProgress >= Q12_CLAMPED(1.0f))
            {
                g_ScreenFadeProgress = Q12_CLAMPED(1.0f);
                g_Screen_FadeStatus++;
            }

            tile->r0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->g0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->b0 = Q12_TO_Q8(g_ScreenFadeProgress);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, true):
            g_ScreenFadeTimestep = Q12(0.0f);

        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, true):
            g_ScreenFadeProgress = Q12_CLAMPED(1.0f);
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

            if (g_ScreenFadeTimestep > Q12(0.0f))
            {
                timestep = g_ScreenFadeTimestep;
            }
            else
            {
                timestep = Q12(3.0f);
            }

            g_ScreenFadeProgress -= Q12_MULT_PRECISE(timestep, g_DeltaTimeRaw);

            if (g_ScreenFadeProgress <= Q12(0.0f))
            {
                g_ScreenFadeProgress = Q12(0.0f);
                ScreenFade_Reset();
                return;
            }

            tile->r0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->g0 = Q12_TO_Q8(g_ScreenFadeProgress);
            tile->b0 = Q12_TO_Q8(g_ScreenFadeProgress);
            break;

        case SCREEN_FADE_STATUS(ScreenFadeState_Reset, false):
            g_ScreenFadeTimestep = Q12(0.0f);
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

void Screen_CutsceneCameraStateUpdate(void) // 0x80032904
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

    vcSetEvCamRate(g_BlackBorderShade);

    if (g_SysWork.sysFlags_22A0 & SysFlag_Freeze)
    {
        return;
    }

    switch (g_SysWork.field_30)
    {
        case 18:
            g_SysWork.field_30++;

        case 19:
            g_BlackBorderShade += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.0f);
            if (g_BlackBorderShade >= Q12_CLAMPED(1.0f))
            {
                g_BlackBorderShade = Q12_CLAMPED(1.0f);
                g_SysWork.field_30++;
            }

            Screen_BlackBorderDraw(poly, g_BlackBorderShade);
            break;

        case 20:
        case 22:
            g_BlackBorderShade = Q12_CLAMPED(1.0f);
            g_SysWork.field_30++;

        case 21:
            Screen_BlackBorderDraw(poly, g_BlackBorderShade);
            break;

        case 23:
            g_BlackBorderShade -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.0f);
            if (g_BlackBorderShade <= Q12(0.0f))
            {
                g_BlackBorderShade = Q12(0.0f);
                g_SysWork.field_30 = 0;
                return;
            }

            Screen_BlackBorderDraw(poly, g_BlackBorderShade);
            break;

        case 0:
            g_BlackBorderShade    = Q12(0.0f);
            g_SysWork.field_30    = 1;
            g_SysWork.flags_22A4 &= ~SysFlag2_3;
            return;

        case 1:
            return;
    }

    ot = &g_OtTags0[g_ActiveBufferIdx][4];
    AddPrim(ot, poly);
    AddPrim(ot, &poly[2]);
    AddPrim(ot, drMode);

    if (!(g_SysWork.flags_22A4 & SysFlag2_3))
    {
        vcChangeProjectionValue(g_GameWork.gsScreenHeight_58A + Q12_MULT(377 - g_GameWork.gsScreenHeight_58A, g_BlackBorderShade));
    }
}

void Screen_VSyncCallback(void) // 0x80032B80
{
    g_Demo_FrameCount++;
    g_UnknownFrameCounter++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}
