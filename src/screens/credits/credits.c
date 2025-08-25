#include "game.h"

#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/credits.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "screens/credits/credits.h"

s_801E5558 D_801E5558[6] =
{
    {
        .field_0 = 0x12D5,
        .field_2 = 0x0000,
        .field_4 = 0x21FC,
    },
    {
        .field_0 = 0x12D3,
        .field_2 = 0xF6A0,
        .field_4 = 0x20D0,
    },
    {
        .field_0 = 0x12D4,
        .field_2 = 0xFC7C,
        .field_4 = 0x21FC,
    },
    {
        .field_0 = 0x12D5,
        .field_2 = 0xFF4C,
        .field_4 = 0x2148,
    },
    {
        .field_0 = 0x12D6,
        .field_2 = 0xFF4C,
        .field_4 = 0x2274,
    },
    {
        .field_0 = 0x12D6,
        .field_2 = 0xFF88,
        .field_4 = 0x20D0
    }
};

RECT D_801E557C[2] =
{
    {
        .x = 320,
        .y = 256,
        .w = 160,
        .h = 240
    },
    {
        .x = 480,
        .y = 16,
        .w = 32,
        .h = 480
    }
};

void func_801E2E28(s32 idx) // 0x801E2E28
{
    s32 var0;
    s32 var1;

    D_801E5E8C = idx;

    func_8004729C(D_801E5558[idx].field_0);
    var1 = (D_801E5558[idx].field_4 * 2) - 0x1F8;
    var0 = var1 / D_801E5C20;

    D_801E5E7C = var1;
    D_801E5E88 = 1;
    D_801E5E7C = var0;
    D_801E5E84 = (var0 * D_801E5C20) + 0x1E0;
    D_801E5E80 = 0x10000 / var0;
}

bool func_801E2ED8() // 0x801E2ED8
{
    switch (D_801E5E88)
    {
        case 0:
            break;

        case 1:
            Sd_EngineCmd((u16)D_801E5558[D_801E5E8C].field_0);
            D_801E5E88++;
            break;

        case 2:
            switch (func_80045B28())
            {
                case 0:
                    return false;

                case 1:
                    D_800C48F0 = D_801E5558[D_801E5E8C].field_2;
                    return true;

                default:
                    break;
            }

        default:
            break;
    }

    return false;
}

bool func_801E2FC0() // 0x801E2FC0
{
    switch (g_Gfx_ScreenFade)
    {
        case 4:
        case 5:
        case 12:
        case 13:
            if (Fs_QueueGetLength() != 0)
            {
                break;
            }

            Game_StateSetNext(GameState_Unk15);
            return true;

        case 2:
        case 3:
        case 10:
        case 11:
            break;

        default:
            g_Gfx_ScreenFade = 10;
            D_800B5C30       = FP_TIME(1.0f);
            break;
    }

    return false;
}

void GameState_Unk15_Update() // 0x801E3094
{
    s32* (*routines[3])() = { func_801E3124, func_801E342C, func_801E3304 };

    D_800C48F0 += g_VBlanks;
    if (routines[g_GameWork.gameStateStep_598[0]]() != 0)
    {
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        g_GameWork.gameStateStep_598[0]++;
    }
}

bool func_801E3124() // 0x801E3124
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            switch (g_Gfx_ScreenFade)
            {
                case 13:
                    g_GameWork.background2dColor_R_58C = FP_COLOR(1.0f);
                    g_GameWork.background2dColor_G_58D = FP_COLOR(1.0f);
                    g_GameWork.background2dColor_B_58E = FP_COLOR(1.0f);
                    break;

                case 5:
                    g_GameWork.background2dColor_R_58C = FP_COLOR(0.0f);
                    g_GameWork.background2dColor_G_58D = FP_COLOR(0.0f);
                    g_GameWork.background2dColor_B_58E = FP_COLOR(0.0f);
                    break;
            }

            Sd_EngineCmd(18);
            Sd_EngineCmd(16);
            g_GameWork.gameStateStep_598[1]++;
            break;

        case 1:
            StoreImage(&D_801E557C[0], (u_long*)IMAGE_BUFFER_0);
            StoreImage(&D_801E557C[1], (u_long*)IMAGE_BUFFER_1);
            DrawSync(0);

            switch (g_Gfx_ScreenFade)
            {
                case 13:
                    Gfx_ClearRectInterlaced(0, 32, 512, 448, FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(1.0f));
                    break;

                case 5:
                    Gfx_ClearRectInterlaced(0, 32, 512, 448, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                    break;
            }

            g_GameWork.gameStateStep_598[1]++;
            break;

        case 2:
            Gfx_Init(0x200, 1);
            g_IntervalVBlanks = 1;
            D_801E5E74        = 0x3C;
            g_GameWork.gameStateStep_598[1]++;
            break;

        case 3:
            D_801E5E74--;

            if (D_801E5E74 <= 0 && func_80045B28() < 2)
            {
                g_GameWork.background2dColor_R_58C = 0;
                g_GameWork.background2dColor_G_58D = 0;
                g_GameWork.background2dColor_B_58E = 0;
                return true;
            }

            break;
    }

    return false;
}

s32 func_801E3304() // 0x801E3304
{
    if (g_GameWork.gameStatePrev_590 == GameState_InGame)
    {
        if (g_GameWork.gameStateStep_598[1] == 0)
        {
            Gfx_Init(SCREEN_WIDTH, 0);
            g_Gfx_ScreenFade = 0;
            g_GameWork.gameStateStep_598[1]++;
        }
        else if (g_GameWork.gameStateStep_598[1] != 10)
        {
            g_GameWork.gameStateStep_598[1]++;
        }
        else
        {
            Gfx_ClearRectInterlaced(0, 32, 320, 448, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
            LoadImage(&D_801E557C[0], IMAGE_BUFFER_0);
            LoadImage(&D_801E557C[1], IMAGE_BUFFER_1);
            DrawSync(0);
            VSync(2);

            Game_StateSetPrevious();
        }

        return 0;
    }

    return 0;
}

bool func_801E342C() // 0x801E342C
{
    s32   temp;
    GsOT* ot;
    TILE* tile;

    if (((g_GameWork.config_0.optExtraOptionsEnabled_27 >> (D_801E5E8C - 1)) & (1 << 0)) &&
        (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        D_800C48F0 = D_801E5558[D_801E5E8C].field_4 + (D_801E5E84 / 2);
        Sd_EngineCmd(19);
    }

    ot   = (GsOT*)&D_800B7CC4[g_ObjectTableIdx];
    tile = (TILE*)GsOUT_PACKET_P;

    addPrimFast(ot, tile, 3);
    setCodeWord(tile, PRIM_RECT, 0);
    setXY0Fast(tile, -256, -224);
    setWHFast(tile, 512, 2);

    GsOUT_PACKET_P += sizeof(TILE);
    temp = func_801E3684();

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            switch (g_Gfx_ScreenFade)
            {
                case 13:
                    g_Gfx_ScreenFade = 14;
                    break;

                case 5:
                    g_Gfx_ScreenFade = 6;
                    break;
            }

            D_800B5C30 = FP_TIME(1.0f);
            g_GameWork.gameStateStep_598[1]++;
            D_801E5E78 = 180;
            break;

        case 1:
            if (temp == 0)
            {
                break;
            }

            D_801E5E78--;
            if (!func_80045B28())
            {
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case 2:
            D_801E5E78--;
            if (D_801E5E78 <= 0)
            {
                g_Gfx_ScreenFade                      = g_GameWork.gameStateStep_598[1];
                g_GameWork.gameStateStep_598[1] = 3;
            }
            break;

        case 3:
            if (g_Gfx_ScreenFade == 5)
            {
                g_GameWork.gameStateStep_598[1] = 4;
                return true;
            }
            break;

        default:
            break;
    }

    return false;
}

#include "stringtable.h"

/** Unknown Rodata values.
 * The types are assumed. It is unknown where
 * are this applied, they could be also some
 * sort of value defined with an macro.
*/
static const s16 D_801E2E1E = 0x50;    // 80
static const s32 D_801E2E20 = 0x1800;  // 6144
static const s32 D_801E2E24 = 0x21700; // 136960

s32 D_801E5C20 = 400;

#include "widthtable.h"

s32 D_801E5E24[7] =
{
    0x64FF0000,
    0x640000FF,
    0x64FF00FF,
    0x6400FF00,
    0x64FFFF00,
    0x6400FFFF,
    0x64FFFFFF,
};

s32 D_801E5E40[7] =
{
    0x2CFF0000,
    0x2C0000FF,
    0x2CFF00FF,
    0x2C00FF00,
    0x2CFFFF00,
    0x2C00FFFF,
    0x2CFFFFFF
};

u8 D_801E5E5C[16] =
{
    '\x7F', '1', '9', 'A',
    'C', 'D', 'E', 'G',
    'H', 'I', 'K', 'L',
    'M', 'N', 'O', 'P'
};

u8 D_801E5E6C[8] =
{
    '.', 'Y', 'V', 'U',
    'T', 'S', 'R', ' '
};

s32 D_801E5E74 = 0;

s32 D_801E5E78 = 0;

s32 D_801E5E7C = 0;

s32 D_801E5E80 = 0;

s32 D_801E5E84 = 0;

s32 D_801E5E88 = 0;

s32 D_801E5E8C = 0;

u8 D_801E5E90[320] = { 0 };

u8 D_801E5FD0[40] = { 0 };

u8 D_801E5FF8[20] = { 0 };

s32 D_801E600C = 0;

bool func_801E3684() // 0x801E3684
{
    s32  sp10;
    s32  sp14;
    s32  sp18;
    s8*  temp_s0;
    s32* var_s2;
    s32  temp_fp;
    s32  temp_v1;
    s32  var_s0;
    s32  var_s1;
    s32  var_s3;
    s32  var_s4;
    s32  var_s5;
    s32  var_s6;
    s32  var_v1;
    bool ret;

    temp_v1 = D_800C48F0 * 2;
    var_s0  = (s32)((temp_v1 - 504) * D_801E5E80);
    var_s0  = var_s0 >> 16;
    var_s6  = D_801E5E84;
    sp10    = D_801E5E7C;

    if (var_s0 < 0)
    {
        var_s0 = 0;
    }

    var_v1 = (s32)(temp_v1 * D_801E5E80);
    var_v1 = var_v1 >> 16;
    if (var_v1 >= D_801E5C20)
    {
        var_v1 = D_801E5C20 - 1;
    }

    sp14 = ((var_s0 * sp10) - temp_v1) + SCREEN_HEIGHT;
    sp18 = (var_v1 - var_s0) + 1;

    var_s6  = (var_s6 - temp_v1);
    var_s6  = var_s6 + SCREEN_HEIGHT;
    temp_fp = var_s6 < SCREEN_HEIGHT;

    if (temp_fp != 0)
    {
        ret    = var_s6 < -23;
        var_s4 = -1;

        if (ret)
        {
            var_s6 = -24;
        }
    }
    else
    {
        ret    = false;
        var_s4 = -1;
    }

    func_801E434C(1, 1);
    func_801E4310(FP_COLOR(0.19f), FP_COLOR(0.19f), FP_COLOR(0.19f));

    for (var_s5 = 2; var_s5 >= 0; var_s5--, var_s4 += 2)
    {
        if (var_s5 == 0)
        {
            var_s4 = 0;
            func_801E434C(0, 0);
            func_801E4310(FP_COLOR(0.2525f), FP_COLOR(0.2525f), FP_COLOR(0.2525f));
        }

        var_s3 = sp14 + var_s4;
        var_s2 = &g_CreditList[var_s0];

        for (var_s1 = sp18; var_s1 > 0; var_s1--, var_s2++, var_s3 += sp10)
        {
            temp_s0 = *var_s2;
            func_801E42F8(0, var_s3);
            func_801E4394(temp_s0);
        }

        if (temp_fp != 0)
        {
            func_801E42F8(0, var_s6 + var_s4);
            func_801E4394(D_801E5BD0);
        }
    }

    return ret;
}

void func_801E386C() // 0x801E386C
{
    s_801E5558* ptr;
    s32            var0;
    s64            var1;
    s32            var2;

    var2 = 5;

    func_8009185C(0, 0, SCREEN_HEIGHT, 0x1000, 0, 0x22000, 0xF0000, 0xB33, 899, -0xF9C);
    ptr  = D_801E5558;
    ptr  = &ptr[5];
    var0 = (u16)ptr->field_4;

    var1 = (s16)var0;
    var1 = FP_TO(var1, Q12_SHIFT);
    var1 = FP_FROM(var1, Q12_SHIFT);

    D_801E5E8C = var2;
    D_801E5E7C = var1 - 264;
    D_800C48F0 = (s32)ptr->field_2;
    D_801E5E7C = D_801E5E7C / D_801E5C20;
    D_801E5E84 = (D_801E5E7C * D_801E5C20) + SCREEN_HEIGHT;
    D_801E5E80 = 0x10000 / D_801E5E7C;
}

bool func_801E3970() // 0x801E3970
{
    bool   showKcet;
    bool   animateKcet;
    bool   isFinished;
    char*  lineStrPtr;
    char** currentLinePtr;
    s32    temp_a1;
    s32    temp_a2;
    s32    currentLinePosY;
    s32    lineHeight;
    s32    temp_v0;
    s32    temp_v0_4;
    s32    vBlank;
    s32    var_a0;
    s32    var_fp;
    s32    lineIdx;
    s32    i;
    s32    lineY;
    s32    var_s5;
    s32    sin;
    s32    cos;
    s32    linesToDraw;
    s32    var_t3;
    s32    skipTo;
    s32    skipToInt;

    showKcet    = false;
    animateKcet = false;
    isFinished  = false;

    vBlank = FP_MULTIPLY_PRECISE(D_800C48F0, 0x1000, Q12_SHIFT);

    temp_a2    = D_801E5E84;
    lineHeight = D_801E5E7C;

    lineIdx = (vBlank - 0x198) * D_801E5E80;
    lineIdx = lineIdx >> 16;
    if (lineIdx < 0)
    {
        lineIdx = 0;
    }

    var_a0 = vBlank * D_801E5E80;
    var_a0 = var_a0 >> 16;
    if (var_a0 >= D_801E5C20)
    {
        var_a0 = D_801E5C20 - 1;
    }

    temp_a2 = (temp_a2 - vBlank);
    var_fp  = temp_a2 + 0x78;

    temp_a2 = var_fp;
    var_s5  = 0;

    showKcet = var_fp < 0x78;

    var_t3          = lineIdx * lineHeight;
    temp_v0         = var_t3 - vBlank;
    currentLinePosY = temp_v0 + 0x78;

    temp_v0     = (var_a0 - lineIdx);
    linesToDraw = temp_v0 + 1;

    if (showKcet)
    {
        animateKcet = var_fp < -0x2F;
        if (animateKcet)
        {
            var_fp = -0x30;
            var_s5 = -0x30 - temp_a2;
        }
    }
    else
    {
        animateKcet = false;
    }

    func_801E4310(FP_COLOR(0.6275f), FP_COLOR(0.6275f), FP_COLOR(0.6275f));
    func_801E434C(0, 0);

    lineY          = currentLinePosY;
    currentLinePtr = &g_CreditList[lineIdx];

    for (i = linesToDraw; i > 0; i--, lineY += lineHeight, currentLinePtr++)
    {
        lineStrPtr = *currentLinePtr;
        func_801E47E0(0, lineY);
        func_801E4C1C(lineStrPtr);
    }

    if (animateKcet)
    {
        temp_a1 = var_s5;

        // Rotate.
        if (var_s5 < 120)
        {
            temp_a1 = (var_s5 * 0x1000) / 120;
            temp_a1 = FP_MULTIPLY_PRECISE((0x1000 - temp_a1), 0x36F, Q12_SHIFT);
            sin     = -Math_Sin(temp_a1);
            cos     = Math_Cos(temp_a1);
            func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, 0xF0000, 0xB33, cos, sin);
        }
        // Zoom in.
        else if (var_s5 < 0xB4)
        {
            temp_a1   = var_s5 - 120;
            temp_a1   = (temp_a1 * 0x1000) / 0x3C;
            temp_v0_4 = FP_MULTIPLY_PRECISE((0x1000 - temp_a1), 0x1E000, Q12_SHIFT) + 0xD2000;
            func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, temp_v0_4, 0xB33, 0x1000, 0);
        }
        else if (var_s5 >= 0x168)
        {
            // Zoom out.
            if (var_s5 < 0x1E0)
            {
                temp_a1   = var_s5 - 0x168;
                temp_a1   = (temp_a1 * 0x1000) / 0x78;
                temp_v0_4 = FP_MULTIPLY_PRECISE((0x1000 - temp_a1), -0xE2E000, Q12_SHIFT) + 0xF00000;
                func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, temp_v0_4, 0xB33, 0x1000, 0);
            }
            // Hide and finish.
            else
            {
                isFinished = true;
                showKcet   = false;
            }
        }
    }
    else if (((g_GameWork.config_0.optExtraOptionsEnabled_27 >> (D_801E5E8C - 1)) & (1 << 0)) &&
             (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        skipTo    = D_801E5E84 + 168;
        skipToInt = FP_TO(skipTo, Q12_SHIFT);

        if (skipToInt < 0)
        {
            skipToInt += 0xFFF;
        }

        skipTo     = FP_FROM(skipToInt, Q12_SHIFT);
        D_800C48F0 = skipTo;
        Sd_EngineCmd(19);
    }

    if (showKcet)
    {
        func_801E47E0(0, var_fp);
        func_801E4C1C(D_801E5BD0);
    }

    return isFinished;
}

void func_801E3DD0() // 0x801E3DD0
{
    D_801E600C = Rng_Rand16();
}

s32 func_801E3DF8(u8 arg0) // 0x801E3DF8
{
    return ((u32)(arg0 * 0x31) >> 6) | 0x38;
}

void func_801E3E18(s32 arg0, s32 arg1) // 0x801E3E18
{
    s32      j;
    s32      i;
    PACKET*  packet;
    s32*     addr;
    u8*      bufA;
    u8*      bufB;
    POLY_G4* poly;
    u32      x0;
    u16      x1, x2, x3;

    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    u8* ptr;
    u8* ptr2;

    s32  temp_t6;
    s32  temp_t1;
    u32  sp1C;
    u32  sp20;
    u32  sp24;
    u32  sp28;
    u32  sp2C;
    u32  temp_v1_2;
    s32  var_s4;
    s32* var_a0;
    s32* var_a1_2;
    u32  temp_a2;
    u32  temp_v1;
    u32  var_v1;
    u8   temp_a0;
    u32  var_a1;
    u32  var_a2;
    u32  var_a3;
    s32* var_a0_2;
    u8*  var_s1_2;
    u8*  var_s2_2;
    u8*  var_t0;
    s32* temp_t2;

    packet  = GsOUT_PACKET_P;
    temp_t2 = &D_800B5C58[g_ObjectTableIdx];
    addr    = temp_t2 + 1;
    temp_a2 = D_801E600C;

    bufA = &D_801E5FD0[0];

    for (i = 1; i < 17; i++)
    {
        temp_a2 = temp_a2 * 0x19660D + 0x3C6EF35F;
        temp_v1 = (temp_a2 >> 20);
        temp_v1 -= 0x200;
        if (temp_v1 >= 0xC00)
        {
            var_v1 = 0xFF;
        }
        else if (temp_v1 >= 0xA00)
        {
            temp_v1 = (temp_v1 - 0xE00) >> 3;
            var_v1  = temp_v1 + 192;
        }
        else if (temp_v1 < 0x200u)
        {
            var_v1 = temp_v1 >> 3;
        }
        else
        {
            temp_v1 = (temp_v1 - 0x200) >> 4;
            var_v1  = temp_v1 + 64;
        }

        D_801E5FD0[i] = var_v1;
    }

    D_801E600C     = temp_a2;
    D_801E5FD0[0]  = D_801E5FD0[16];
    D_801E5FD0[17] = D_801E5FD0[1];

    bufA = &D_801E5FD0[0];
    bufB = &D_801E5FD0[20];

    j       = 0;
    var_s4  = 0;
    temp_t1 = arg0 + 0x1E0;
    sp1C    = 0xffffff;
    temp_t6 =
    sp28    = temp_t1 << 0x10;
    sp2C    = temp_t6 + 0x200000;

    for (; j < 16; j++, var_s4 -= 16, sp28 += 0xFFE00000, sp2C += 0xFFE00000, temp_t1 -= 32)
    {
        ptr2 = D_801E5FF8;

        ptr  = bufB;
        bufB = bufA;
        bufA = ptr;

        ptr = D_801E5E90 + j * 20;

        var_a1_2 = (s32*)D_801E5FF8;
        var_a0   = (s32*)ptr;

        for (i = 0; i < 20; i += 4)
        {
            var_a1_2[i * 5] = var_a0[i * 5];
        }

        var_s2_2 = ptr2;
        var_a1   = *var_s2_2++;
        var_a3   = *var_s2_2++;

        var_t0 = bufA + 1;

        var_s1_2 = bufB;
        var_a2   = *bufB;
        var_s1_2++;

        for (i = 16; i > 0; i--)
        {
            s16 var = 0x1000;

            temp_v1_2 = var_a1;

            temp_a0 = var_a2;
            var_a1  = var_a3;
            temp_v1_2 += temp_a0;

            var_a3 = *var_s2_2;
            var_a2 = *var_s1_2;
            var_a3 += var_a2;

            var_s2_2++;
            var_s1_2++;

            var_a1 = var_a1 + (((temp_v1_2 * (var - arg1)) + (var_a3 * arg1)) >> 13);
            var_a1 = var_a1 + ((temp_a0 + var_a2) >> 1);
            var_a1 = (((var_a1 + var_a2 + temp_a0) * 2) + (var_a3 + temp_v1_2)) >> 1;
            var_a1--;

            *var_t0 = var_a1;
            var_t0++;
        }

        bufA[0]  = bufA[16];
        bufA[17] = bufA[1];

        var_a1_2 = (s32*)ptr;
        var_a0_2 = (s32*)bufA;

        for (i = 0; i < 20; i += 4)
        {
            var_a1_2[i * 5] = var_a0_2[i * 5];
        }

        if (temp_t1 >= 0x1E0)
        {
            continue;
        }

        var_s2_2 = bufA;
        color1   = func_801E3DF8(*var_s2_2++);

        var_s1_2 = bufB;
        color3   = func_801E3DF8(*var_s1_2++);

        sp20 = sp2C;
        sp24 = sp28;

        for (i = 0; i < 16; i++)
        {
            color0 = color1;
            color1 = func_801E3DF8(*var_s2_2++);
            var_s2_2++;

            color2 = color3;
            color3 = func_801E3DF8(*var_s1_2++);
            var_s1_2++;

            var_v1 = 0x200;
            var_a1 = var_v1;
            x0     = var_s4 + var_a1;

            if ((var_s4 + 48) > 0)
            {
                x0 = var_s4;
                if (var_s4 < 0)
                {
                    poly = (POLY_G4*)packet;
                    // addPrimFast(addr, poly, 8);
                    poly->tag = ((*addr & sp1C) | 0x08000000);
                    *addr     = (*addr & 0xFF000000) | ((u32)poly & sp1C);

                    x0 = var_s4 + 0x200;
                    x1 = var_s4 + 0x220;
                    x2 = var_s4 + 0x210;
                    x3 = var_s4 + 0x230;

                    *(u32*)(&poly->x0) = (((x0) & 0xFFFF) + (sp28));
                    *(u32*)(&poly->x1) = (((x1) & 0xFFFF) + (sp28));
                    *(u32*)(&poly->x2) = (((x2) & 0xFFFF) + (sp20));
                    *(u32*)(&poly->x3) = (((x3) & 0xFFFF) + (sp20));

                    *(u32*)(&poly->r0) = color0;
                    *(u32*)(&poly->r1) = color1;
                    *(u32*)(&poly->r2) = color2;
                    *(u32*)(&poly->r3) = color3;

                    packet += sizeof(POLY_G4);

                    x0 = var_s4;
                }
            }

            x1 = x0 + 32;
            x2 = x0 + 16;
            x3 = x0 + 48;

            poly = (POLY_G4*)packet;
            // addPrimFast(addr, poly, 8);
            poly->tag = ((*addr & sp1C) | 0x08000000);
            *addr     = (*addr & 0xFF000000) | ((u32)poly & sp1C);

            *(u32*)(&poly->x0) = (((x0) & 0xFFFF) + (sp24));
            *(u32*)(&poly->x1) = (((x1) & 0xFFFF) + (sp24));
            *(u32*)(&poly->x2) = (((x2) & 0xFFFF) + (sp20));
            *(u32*)(&poly->x3) = (((x3) & 0xFFFF) + (sp20));

            *(u32*)(&poly->r0) = color0;
            *(u32*)(&poly->r1) = color1;
            *(u32*)(&poly->r2) = color2;
            *(u32*)(&poly->r3) = color3;

            packet += sizeof(POLY_G4);
        }
    }
    GsOUT_PACKET_P = packet;
}

void func_801E42F8(s32 arg0, s32 arg1) // 0x801E42F8
{
    D_800AFE08.field_0 = arg0;
    D_800AFE08.field_2 = arg1;
    D_800AFE08.field_4 = arg0;
}

void func_801E4310(s32 r, s32 g, s32 b) // 0x801E4310
{
    D_800AFE08.field_8 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((PRIM_RECT | RECT_TEXTURE) << 24);
}

void func_801E4340(s8 arg0) // 0x801E4340
{
    D_800AFE08.field_6 = arg0;
}

void func_801E434C(u32 arg0, u32 arg1) // 0x801E434C
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE08.field_7 = arg0 != 0;

    if (arg1 < 4)
    {
        maskedField_18  = D_800AFE08.field_18;
        shiftedField_18 = (maskedField_18 << 4) & (1 << 8);

        maskedField_18   &= 0xF;
        shiftedField_18 >>= 4;

        shiftedArg1   = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1  |= shiftedField_18;
        shiftedArg1  |= (u8)maskedField_18;

        D_800AFE08.field_14 = shiftedArg1;
    }
}

void func_801E4394(u8* str) // 0x801E4394
{
    s32       textX;
    s32       textY;
    s32       marginX;
    s32       fontH;
    u32       blendFlag;
    u32       charCode;
    u32       colorCode;
    u32       clut;
    s32       charWidth;
    s32       widthSum;
    s32       idx;
    u32       temp;
    u32       nextChar;
    u8*       strPtr;
    u8*       scanPtr;
    s16*      widthTable;
    s32*      colorTable;
    PACKET*   packet;
    SPRT*     sprite;
    SPRT_16*  sprite16;
    DR_TPAGE* tPage;
    GsOT*     ot;

    strPtr     = str;
    textX      = D_800AFE08.field_0;
    textY      = D_800AFE08.field_2;
    marginX    = D_800AFE08.field_4;
    fontH      = D_800AFE08.field_6;
    widthTable = D_800AFE08.field_C;
    colorTable = D_800AFE08.field_10;
    packet     = GsOUT_PACKET_P;
    blendFlag  = (u8)D_800AFE08.field_7;
    charCode   = *strPtr;
    colorCode  = D_800AFE08.field_8 | (blendFlag << 25); // RBG + code + semi-transparency flag.
    clut       = (u16)D_800AFE08.field_16;               // Clut Y, clut Y.
    ot         = &D_800B5C58[g_ObjectTableIdx];

    while (charCode != 0)
    {
        charWidth = widthTable[charCode];

        // Normal font.
        if (charCode >= 0x21 && charCode < 0x85)
        {
            sprite = (SPRT*)packet;
            addPrimFast(ot, sprite, 4);
            *(u32*)(&sprite->r0) = colorCode;
            setXY0Fast(sprite, textX, textY);

            idx                   = charCode - 0x21;
            temp                  = idx / 10;
            idx                   = idx % 10;
            idx                   = idx * 24;
            *(u32*)(&sprite->u0)  = idx + ((temp * 24) * 256);
            *(u32*)(&sprite->u0) += clut << 16;

            setWHFast(sprite, 24, 24);
            packet += sizeof(SPRT);
        }
        else
        {
            sprite16 = (SPRT_16*)packet;

            // KCET font.
            if (charCode >= 0xA0 && charCode < 0xB0)
            {
                addPrimFast(ot, sprite16, 3);
                *(u32*)(&sprite16->r0) = colorCode ^ (0x18 << 24); // GP0(7Ch) - Textured Rectangle, 16x16, opaque, texture-blending.
                setXY0Fast(sprite16, textX, textY + 4);

                idx                     = charCode - 0xA0;
                *(u32*)(&sprite16->u0)  = ((idx * 256 )* 16) + (16 * (16 - 1));
                *(u32*)(&sprite16->u0) += clut << 16;

                packet += sizeof(SPRT_16);
            }
            // KCET font, .YVUTSR.
            else if (charCode >= 0xB8 && charCode < 0xBF)
            {
                addPrimFast(ot, sprite16, 3);
                *(u32*)(&sprite16->r0) = colorCode ^ (0x18 << 24); // GP0(7Ch) - Textured Rectangle, 16x16, opaque, texture-blending.
                setXY0Fast(sprite16, textX, textY + 4);

                idx                     = charCode - 0xB8;
                *(u32*)(&sprite16->u0)  = (idx * 16) + (((256 * 16) * (16 - 1)) + (16 * 8));
                *(u32*)(&sprite16->u0) += clut << 16;

                packet += sizeof(SPRT_16);
            }
            // Change font color.
            else if (charCode >= 1 && charCode < 8)
            {
                colorCode = colorTable[charCode - 1] | ((u8)D_800AFE08.field_7 << 25);
            }
            // Change font width table?
            else if (charCode >= 0xD0 && charCode < 0xD8)
            {
                scanPtr  = strPtr + 1;
                widthSum = 0;
                while (1)
                {
                    s32 var  = 8;
                    nextChar = *scanPtr++;
                    if (nextChar == (charCode + 8) || (nextChar == charCode || nextChar == 10) || nextChar == 0xD || nextChar == 0xc)
                    {
                        break;
                    }

                    if (((nextChar - 0xF0) >= var) && ((nextChar - 0xF8) > 7) && ((nextChar - 0xE0) > 7) && ((nextChar - 0xE8) > 7))
                    {
                        widthSum += widthTable[nextChar];
                    }
                }

                (&widthTable[charCode])[16] = widthSum / 2;
                (&widthTable[charCode])[32] = -(&widthTable[charCode])[16];
                (&widthTable[charCode])[24] = widthSum;
                (&widthTable[charCode])[40] = -(&widthTable[charCode])[24];
            }
        }

        // Offsets.
        switch ((s32)charCode)
        {
            // Newline.
            case 10:
                textX = marginX;
                textY += fontH;
                break;

            // Vertical tab.
            case 11:
                textY += fontH;
                break;

            // Carriage return.
            case 13:
                textX = marginX;
                break;

            // Form feed.
            case 12:
                textX = D_800AFE08.field_0;
                textY = D_800AFE08.field_2;
                break;

            default:
                textX += charWidth;
                break;
        }

        strPtr++;
        charCode = *strPtr;
    }

    tPage = (DR_TPAGE*)packet;
    setDrawTPage(tPage, 0, 1, D_800AFE08.field_14);
    addPrim(ot, tPage);

    D_800AFE08.field_0 = textX;
    D_800AFE08.field_2 = textY;
    GsOUT_PACKET_P     = packet + sizeof(DR_TPAGE);
}

void func_801E47E0(s32 arg0, s32 arg1) // 0x801E47E0
{
    s32  temp_a2;
    s32  temp_lo;
    s32  temp_lo_11;
    s32  temp_lo_12;
    s32  temp_lo_15;
    s32  temp_lo_3;
    s32  temp_lo_4;
    s32  temp_lo_6;
    s32  temp_lo_7;
    s32  temp_t0;
    s32  temp_t1;
    s32  temp_t2;
    s32  temp_v0;
    s32  temp_v0_2;
    s32  temp_v0_3;
    s32  temp_v0_4;
    bool check = D_800AFE24.field_0 != arg0;

    if (D_800AFE24.field_2 != arg1)
    {
        temp_lo   = arg1 * D_800AFE24.field_3C;
        temp_t1   = D_800AFE24.field_24 << 0x16;
        temp_lo_3 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, temp_lo, Q12_SHIFT)) >> 2;
        temp_lo_3 = temp_t1 / temp_lo_3;

        temp_t2   = arg1 + 0x18;
        temp_lo_4 = temp_t2 * D_800AFE24.field_3C;
        temp_lo_6 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, temp_lo_4, Q12_SHIFT)) >> 2;
        temp_lo_6 = temp_t1 / temp_lo_6;

        temp_lo_7 = arg0 * D_800AFE24.field_34;
        temp_v0   = D_800AFE24.field_28 + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, temp_lo_7, Q12_SHIFT);
        temp_t0   = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0, Q12_SHIFT);
        temp_v0_2 = D_800AFE24.field_28 + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, D_800AFE24.field_34, Q12_SHIFT);

        D_800AFE24.field_0  = arg0;
        D_800AFE24.field_2  = arg1;
        D_800AFE24.field_4  = arg0;
        D_800AFE24.field_40 = temp_t0;
        D_800AFE24.field_44 = FP_MULTIPLY_PRECISE(temp_lo_6, temp_v0, Q12_SHIFT);
        D_800AFE24.field_48 = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0_2, Q12_SHIFT) - FP_MULTIPLY_PRECISE(temp_lo_3, D_800AFE24.field_28, Q12_SHIFT);
        D_800AFE24.field_4C = FP_MULTIPLY_PRECISE(temp_lo_6, temp_v0_2, Q12_SHIFT) - FP_MULTIPLY_PRECISE(temp_lo_6, D_800AFE24.field_28, Q12_SHIFT);
        temp_lo_11          = arg1 * D_800AFE24.field_38;
        temp_v0_3           = D_800AFE24.field_2C + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, temp_lo_11, Q12_SHIFT);
        D_800AFE24.field_50 = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0_3, Q12_SHIFT);

        temp_lo_12          = temp_t2 * D_800AFE24.field_38;
        temp_t0             = D_800AFE24.field_2C + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, temp_lo_12, Q12_SHIFT);
        D_800AFE24.field_54 = FP_MULTIPLY_PRECISE(temp_lo_6, temp_t0, Q12_SHIFT);
    }
    else if (check)
    {
        temp_v0_4            = arg0 - D_800AFE24.field_0;
        temp_a2              = temp_v0_4 * D_800AFE24.field_48;
        temp_lo_15           = temp_v0_4 * D_800AFE24.field_4C;
        D_800AFE24.field_0   = arg0;
        D_800AFE24.field_40 += temp_a2;
        D_800AFE24.field_44 += temp_lo_15;
    }
}

void func_801E4B98(s32 r, s32 g, s32 b)
{
    D_800AFE24.field_8 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (GPU_COM_TF4 << 24);
}

void func_801E4BC8(s8 arg0) // 0x801E4BC8
{
    D_800AFE24.field_6 = arg0;
}

void func_801E4BD4(u32 arg0, u32 arg1) // 0x801E4BD4
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE24.field_7 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18  = D_800AFE24.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;

        maskedField_18 &= 0xF;
        shiftedField_18 >>= 4;

        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;

        D_800AFE24.field_14 = shiftedArg1;
    }
}

void func_801E4C1C(u8* str) // 0x801E4C1C
{
    PACKET* packet;
    GsOT*   ot;

    s32 textX   = D_800AFE24.field_0;
    s32 textY   = D_800AFE24.field_2;
    s32 marginX = D_800AFE24.field_4;
    s32 fontH   = D_800AFE24.field_6;
    u32 colorCode;

    s32 var_a3 = D_800AFE24.field_40;
    s32 var_t3 = D_800AFE24.field_44;
    s32 var_t7 = D_800AFE24.field_48;
    s32 var_t6 = D_800AFE24.field_4C;
    s32 var_t4 = D_800AFE24.field_50;
    s32 var_t5 = D_800AFE24.field_54;

    u32       clut       = (u16)D_800AFE24.field_16;
    u32       tPage      = D_800AFE24.field_14;
    s16*      widthTable = D_800AFE24.field_C;
    s32*      colorTable = D_800AFE24.field_10;
    u32       blendFlag  = (u8)D_800AFE24.field_7 << 25;
    s32       charWidth;
    bool      textXChanged;
    bool      textYChanged;
    u32       nextChar;
    u8*       scanPtr;
    POLY_FT4* poly;
    s32       widthSum;
    u32       charCode;

    s32 temp_a0_4;
    s32 temp_a1_2;
    s32 temp_lo_3;
    s32 temp_lo_6;
    s32 temp_v0_5;
    s32 temp_v0_7;

    s32 var_a1;
    s32 var_a2;
    s32 var_t0;
    s32 var_t0_2;

    u32 temp_v1;
    u32 temp;
    s32 idx;

    packet = GsOUT_PACKET_P;
    ot     = &D_800B5C58[g_ObjectTableIdx];

    charCode  = *str;
    colorCode = D_800AFE24.field_8 | blendFlag; // RGB + code + semi-transparency flag.

    while (charCode != 0)
    {
        poly = (POLY_FT4*)packet;

        var_t0 = (charCode - 0xA0) < 0x10u | (charCode - 0xB8 < 7u) << 1;

        // Map KCET font to normal.
        if (var_t0 != 0)
        {
            if (var_t0 == 1)
            {
                charCode = D_801E5E5C[charCode - 0xA0];
            }
            else
            {
                charCode = D_801E5E6C[charCode - 0xB8];
            }
        }

        charWidth = widthTable[charCode];

        // Normal font.
        if (charCode >= 0x21 && charCode < 0x85)
        {
            s32 offset         = 24 * 256;
            idx                = charCode - 0x21;
            temp               = idx / 10;
            idx                = idx % 10;
            idx                = idx * 24;
            temp               = temp * 24;
            *(u32*)(&poly->u0) = idx + (temp * 256);
            *(u32*)(&poly->u0) += clut << 16;
            *(u32*)(&poly->u1) = (idx + charWidth) + (temp * 256);
            *(u32*)(&poly->u1) += tPage << 16;
            temp_v1            = temp * (u64)256; // From permuter, not sure why this works.
            *(u32*)(&poly->u2) = idx + (temp_v1 + offset);
            *(u32*)(&poly->u3) = (idx + charWidth) + (temp_v1 + offset);

            if (var_t0 != 0)
            {
                charWidth = (charWidth * 2) / 3;
                var_a1    = var_t7 * charWidth;
                var_a2    = var_t6 * charWidth;
                var_a2    = ((var_a2 - var_a1) * 2) / 3 + var_a1;
                var_t0_2  = ((var_t5 - var_t4) * 2) / 3 + var_t4;
            }
            else
            {
                var_a1   = var_t7 * charWidth;
                var_t0_2 = var_t5;
                var_a2   = var_t6 * charWidth;
            }

            addPrimFast(ot, (POLY_FT4*)packet, 9);
            *(u32*)(&poly->r0) = colorCode; // GP0(2Ch) - Textured four-point polygon, opaque, texture-blending.
            setXY0Fast(poly, FP_FROM(var_a3, Q12_SHIFT), FP_FROM(var_t4, Q12_SHIFT));
            setXY1Fast(poly, FP_FROM(var_a3 + var_a1, Q12_SHIFT), FP_FROM(var_t4, Q12_SHIFT));
            setXY2Fast(poly, FP_FROM(var_t3, Q12_SHIFT), FP_FROM(var_t0_2, Q12_SHIFT));
            setXY3Fast(poly, FP_FROM(var_t3 + var_a2, Q12_SHIFT), FP_FROM(var_t0_2, Q12_SHIFT));
            packet += sizeof(POLY_FT4);
        }
        // Change font color.
        else if (charCode >= 1 && charCode < 8)
        {
            colorCode = colorTable[charCode - 1] | ((u8)D_800AFE24.field_7 << 25);
        }
        // Change font width table?
        else if (charCode >= 0xD0 && charCode < 0xD8)
        {
            widthSum = 0;
            scanPtr  = str + 1;
            while (1)
            {
                s32 var  = 8;
                nextChar = *scanPtr++;
                if (nextChar == (charCode + 8) || nextChar == charCode || nextChar == 0xA || nextChar == 0xD || nextChar == 0xC)
                {
                    break;
                }

                if ((nextChar - 0xF0) >= var && (nextChar - 0xF8) >= 8u && (nextChar - 0xE0) >= 8u && (nextChar - 0xE8) >= 8u)
                {
                    var_t0 = (nextChar >= 0xA0 && nextChar < 0xB0) | (nextChar >= 0xB8 && nextChar < 0xBF) << 1;
                    if (var_t0 != 0) // map kcet font to normal
                    {
                        if (var_t0 == 1)
                        {
                            nextChar = D_801E5E5C[nextChar - 0xA0];
                        }
                        else
                        {
                            nextChar = D_801E5E6C[nextChar - 0xB8];
                        }
                        widthSum += (widthTable[nextChar] * 2) / 3;
                    }
                    else
                    {
                        widthSum += widthTable[nextChar];
                    }
                }
            }

            (&widthTable[charCode])[16] = widthSum / 2;
            (&widthTable[charCode])[32] = -(&widthTable[charCode])[16];
            (&widthTable[charCode])[24] = widthSum;
            (&widthTable[charCode])[40] = -(&widthTable[charCode])[24];
        }

        textXChanged = false;
        textYChanged = false;

        // Offsets.
        switch ((s32)charCode)
        {
            // Newline.
            case 10:
                textX = marginX;
                textY += fontH;
                textYChanged = true;
                break;

            // Vertical tab.
            case 11:
                textY += fontH;
                textYChanged = true;
                break;

            // Carriage return.
            case 13:
                charWidth    = textX - marginX;
                textX        = marginX;
                textXChanged = true;
                break;

            // Form feed.
            case 12:
                textX        = D_800AFE24.field_0;
                textY        = D_800AFE24.field_2;
                textYChanged = true;
                break;

            default:
                textX += charWidth;
                textXChanged = true;
                break;
        }

        if (textYChanged)
        {
            temp_a1_2 = D_800AFE24.field_24 << 0x16;

            temp_lo_3 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, textY * D_800AFE24.field_3C, Q12_SHIFT)) >> 2;
            temp_lo_3 = temp_a1_2 / temp_lo_3;

            temp_lo_6 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, (textY + 0x18) * D_800AFE24.field_3C, Q12_SHIFT)) >> 2;
            temp_lo_6 = temp_a1_2 / temp_lo_6;

            temp_v0_5 = D_800AFE24.field_28 + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, textX * D_800AFE24.field_34, Q12_SHIFT);

            var_a3 = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0_5, Q12_SHIFT);
            var_t3 = FP_MULTIPLY_PRECISE(temp_lo_6, temp_v0_5, Q12_SHIFT);

            temp_v0_5 = D_800AFE24.field_28 + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, D_800AFE24.field_34, Q12_SHIFT);

            var_t7 = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0_5, Q12_SHIFT) - FP_MULTIPLY_PRECISE(temp_lo_3, D_800AFE24.field_28, Q12_SHIFT);
            var_t6 = FP_MULTIPLY_PRECISE(temp_lo_6, temp_v0_5, Q12_SHIFT) - FP_MULTIPLY_PRECISE(temp_lo_6, D_800AFE24.field_28, Q12_SHIFT);

            temp_v0_7 = D_800AFE24.field_2C + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, textY * D_800AFE24.field_38, Q12_SHIFT);
            var_t4    = FP_MULTIPLY_PRECISE(temp_lo_3, temp_v0_7, Q12_SHIFT);

            temp_a0_4 = D_800AFE24.field_2C + FP_MULTIPLY_PRECISE(D_800AFE24.field_1C, (textY + 0x18) * D_800AFE24.field_38, Q12_SHIFT);
            var_t5    = FP_MULTIPLY_PRECISE(temp_lo_6, temp_a0_4, Q12_SHIFT);
        }
        else if (textXChanged)
        {
            var_a3 += charWidth * var_t7;
            var_t3 += charWidth * var_t6;
        }

        str++;
        charCode = *str;
    }

    GsOUT_PACKET_P      = packet;
    D_800AFE24.field_0  = textX;
    D_800AFE24.field_2  = textY;
    D_800AFE24.field_40 = var_a3;
    D_800AFE24.field_44 = var_t3;
    D_800AFE24.field_48 = var_t7;
    D_800AFE24.field_4C = var_t6;
    D_800AFE24.field_50 = var_t4;
    D_800AFE24.field_54 = var_t5;
}
