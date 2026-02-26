#include "game.h"

#include <libetc.h>
#include <libgs.h>

#include "main/fsqueue.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/view/structs.h"
#include "bodyprog/view/vc_main.h"
#include "bodyprog/view/vc_util.h"
#include "bodyprog/math/math.h"

static DR_MODE D_800A8E98[] = {
    { 0x3000000, { 0xE1000240, 0x0 } },
    { 0x3000000, { 0xE1000240, 0x0 } }
};

// TODO: Make a macro?
static POLY_G4 D_800A8EB0[] = {
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        -160, -112,
        0x0, 0x0, 0x0, 0x0,
        0xA0, -112,
        0x0, 0x0, 0x0, 0x0,
        -160, -96,
        0x0, 0x0, 0x0, 0x0,
        0xA0, -96
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        -160, -112,
        0x0, 0x0, 0x0, 0x0,
        0xA0, -112,
        0x0, 0x0, 0x0, 0x0,
        -160, -96,
        0x0, 0x0, 0x0, 0x0,
        0xA0, -96
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        -160, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        -160, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x60
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        -160, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        -160, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xA0, 0x60
    }
};

static q19_12 g_BlackBorderShade = Q12(0.0f);

// ========================================
// CUTSCENE BORDER DRAWING
// ========================================

void Screen_CutsceneCameraStateUpdate(void) // 0x80032904
{
    void Screen_BlackBorderDraw(POLY_G4* poly, s32 color)
    {
        s32 i;
        s32 color0;
        s32 color1;

        color0 = color >> 4;
        color1 = color >> 5;

        if (color == Q12_CLAMPED(1.0f))
        {
            color1 = Q8_CLAMPED(1.0f);
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