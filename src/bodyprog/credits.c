#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/ranking.h"
#include "main/fsqueue.h"

const s32 rodataPad_8002B2F8 = 0;

struct
{
    char f0[5];
    char f1[5];
    char f2[5];
    char f3[5];
} g_Credits_Digits = { "0.00", "0.00", "0.00", "0.00" };

s_800AFE08 D_800AFE08 = {
    .field_6  = 0x18,
    .field_8  = 0x64FFFFFF,
    .field_C  = (s16*)0x801E5C24,
    .field_10 = (s32*)0x801E5E24
};

s_800AFE24 D_800AFE24 = {
    .sub_0 = {
        .field_6   = 24,
        .field_8   = 0x2CFFFFFF,
        .field_C   = (s16*)0x801E5C24,
        .field_10  = (s32*)0x801E5E40
    },
    .field_1C  = 4096,
    .field_24  = 240,
    .field_30  = 0xF0000,
    .field_34  = 4096,
    .field_3C  = -4096,
    .field_48  = 4096,
    .field_4C  = 4551
};

void func_8008F94C() // 0x8008F94C
{
    s16 temp_s1;
    s32 var_a0;
    s32 var_a0_3;
    s32 var_v1;
    u16 firedShotCount;
    u16 var_v0_5;
    u8  temp_a0_2;
    u8  temp;
    s8* temp3;

    D_800C48B5 = 0;
    D_800C48D0 = g_SavegamePtr->gameDifficulty_260;
    D_800C48A0 = g_SavegamePtr->savegameCount_A6;
    D_800C48A0 = CLAMP(D_800C48A0, 0, 999);
    D_800C48D1 = g_SavegamePtr->continueCount_27B;
    D_800C48A2 = g_SavegamePtr->add290Hours_25C_1 * 24 + FP_FROM(g_SavegamePtr->gameplayTimer_250, Q12_SHIFT) / 3600;
    D_800C48A4 = FP_FROM(g_SavegamePtr->walkDistance_258, Q12_SHIFT) / 1000;
    D_800C48A6 = FP_FROM(g_SavegamePtr->walkDistance_258, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->walkDistance_258, Q12_SHIFT) / 1000) * 1000;
    D_800C48A8 = FP_FROM(g_SavegamePtr->runDistance_254, Q12_SHIFT) / 1000;
    D_800C48AA = FP_FROM(g_SavegamePtr->runDistance_254, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->runDistance_254, Q12_SHIFT) / 1000) * 1000;
    D_800C48AC = g_SavegamePtr->pickedUpItemCount_23C;
    D_800C48AE = (FP_FROM(g_SavegamePtr->gameplayTimer_250, Q12_SHIFT) / 60) % 60;
    D_800C48AF = FP_FROM(g_SavegamePtr->gameplayTimer_250, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->gameplayTimer_250, Q12_SHIFT) / 60) * 60;
    D_800C48B0 = g_SavegamePtr->clearGameCount_24A;
    D_800C48B1 = g_SavegamePtr->clearGameEndings_24B;
    D_800C48B2 = g_SavegamePtr->field_27A;
    D_800C48B6 = Savegame_EventFlagGetAlt(EventFlag_61);
    D_800C48B4 = 0;
    D_800C48B7 = Savegame_EventFlagGetAlt(EventFlag_183);
    D_800C48B8 = func_8009146C(1);
    D_800C48BA = func_8009146C(0);

    firedShotCount = g_SavegamePtr->firedShotCount_264;
    D_800C48BC     = firedShotCount != 0;

    if (D_800C48BC)
    {
        D_800C48C0 = g_SavegamePtr->closeRangeShotCount_266;
        D_800C48C4 = g_SavegamePtr->midRangeShotCount_268;
        D_800C48C8 = g_SavegamePtr->longRangeShotCount_26A;
        D_800C48C4 = D_800C48C4 + g_SavegamePtr->field_26C;
        D_800C48C0 = D_800C48C0 * 100 / firedShotCount;
        D_800C48C4 = D_800C48C4 * 100 / firedShotCount;
        D_800C48C8 = D_800C48C8 * 100 / firedShotCount;
        D_800C48CC = ((100 - D_800C48C0) - D_800C48C4) - D_800C48C8;

        g_Credits_Digits.f0[0] = (((D_800C48C0) / 100) % 10) + '0';
        g_Credits_Digits.f0[2] = (((D_800C48C0) / 10) - (((D_800C48C0) / 100) * 10)) + '0';
        g_Credits_Digits.f0[3] = ((D_800C48C0) % 10) + '0';

        g_Credits_Digits.f1[0] = (((D_800C48C4) / 100) % 10) + '0';
        g_Credits_Digits.f1[2] = (((D_800C48C4) / 10) - (((D_800C48C4) / 100) * 10)) + '0';
        g_Credits_Digits.f1[3] = ((D_800C48C4) % 10) + '0';

        g_Credits_Digits.f2[0] = (((D_800C48C8) / 100) % 10) + '0';
        g_Credits_Digits.f2[2] = (((D_800C48C8) / 10) - (((D_800C48C8) / 100) * 10)) + '0';
        g_Credits_Digits.f2[3] = ((D_800C48C8) % 10) + '0';

        g_Credits_Digits.f3[0] = (((D_800C48CC) / 100) % 10) + '0';
        g_Credits_Digits.f3[2] = (((D_800C48CC) / 10) - (((D_800C48CC) / 100) * 10)) + '0';
        g_Credits_Digits.f3[3] = ((D_800C48CC) % 10) + '0';
    }

    temp_s1    = D_800C48AE + (D_800C48A2 * 60);
    D_800C48B4 = g_SavegamePtr->pickedUpSpecialItemCount_25C_3 & 0xF;

    D_800C48B3 = g_SavegamePtr->locationId_A8;
    D_800C3E40 = 7;
    temp_a0_2  = g_GameWork.config_0.optExtraOptionsEnabled_27;

    if ((temp_a0_2 & 0x3) && (temp_a0_2 & 0xC))
    {
        D_800C3E40 = 0xF;
    }

    if (g_GameWork.config_0.optExtraOptionsEnabled_27 & 1)
    {
        D_800C3E40 |= 0x10;
    }

    if (Inventory_HyperBlasterUnlockTest() == NO_VALUE || (D_800C48B2 & 0x10))
    {
        D_800C3E40 |= 0x20;
    }

    D_800C48E0.field_0 = 7;

    switch (D_800C48B2)
    {
        case 3:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;

        case 1:
            D_800C48E0.field_0 = 0;
            D_800C48B5 += 10;
            break;

        case 2:
            D_800C48B5 += 5;
            break;

        case 4:
            D_800C48B5 += 3;
            break;

        case 8:
            D_800C48B5 += 1;
            break;

        case 16:
            D_800C48B5 += 0;
            break;
    }

    D_800C48E0.field_5 = 7;

    if ((D_800C48AC / 15) < 0 || (D_800C48AC / 15) >= 10)
    {
        D_800C48E0.field_5 = 0;
        D_800C48B5 += 10;
    }
    else
    {
        D_800C48B5 += D_800C48AC / 15;
    }

    D_800C48E0.field_2 = 7;

    if (D_800C48A0 < 3)
    {
        D_800C48E0.field_2 = 0;
        D_800C48B5 += 5;
    }
    else if (D_800C48A0 < 6)
    {
        D_800C48B5 += 4;
    }
    else if (D_800C48A0 < 11)
    {
        D_800C48B5 += 3;
    }
    else if (D_800C48A0 < 21)
    {
        D_800C48B5 += 2;
    }
    else if (D_800C48A0 < 31)
    {
        D_800C48B5 += 1;
    }

    D_800C48E0.field_3 = 7;

    if (D_800C48D1 < 2)
    {
        D_800C48E0.field_3 = 0;
        D_800C48B5 += 5;
    }
    else if (D_800C48D1 < 4)
    {
        D_800C48B5 += 4;
    }
    else if (D_800C48D1 < 6)
    {
        D_800C48B5 += 3;
    }
    else if (D_800C48D1 < 8)
    {
        D_800C48B5 += 2;
    }
    else if (D_800C48D1 < 10)
    {
        D_800C48B5 += 1;
    }

    D_800C48E0.field_4 = 7;

    if (temp_s1 < 90)
    {
        D_800C48E0.field_4 = 0;
        D_800C48B5 += 10;
    }
    else if (temp_s1 < 180)
    {
        D_800C48B5 += 5;
    }
    else if (temp_s1 < 240)
    {
        D_800C48B5 += 3;
    }
    else if (temp_s1 < 360)
    {
        D_800C48B5 += 2;
    }
    else if (temp_s1 < 720)
    {
        D_800C48B5 += 1;
    }

    D_800C48E0.field_1 = 7;

    temp = D_800C48B0;

    if (temp >= 5)
    {
        D_800C48E0.field_1 = 0;
        D_800C48B5        += 10;
    }
    else
    {
        D_800C48B5 += temp * 2;
    }

    D_800C48E0.field_6 = 7;
    temp               = D_800C48B4;

    if (temp >= 5)
    {
        D_800C48E0.field_6 = 0;
        D_800C48B5        += 10;
    }
    else
    {
        D_800C48B5 += temp * 2;
    }

    D_800C48E0.field_8 = 7;

    if (D_800C48BC)
    {
        var_a0 = ((D_800C48C0 + D_800C48C4 * 2) + (D_800C48C8 * 3)) - (D_800C48CC * 4);
        var_a0 = var_a0 / 10;

        if (var_a0 < 0)
        {
            var_a0 = 0;
        }
        else if (var_a0 > 10)
        {
            var_a0 = 10;
        }

        D_800C48B5 += var_a0;

        if (var_a0 == 10)
        {
            D_800C48E0.field_8 = 0;
        }
    }
    else
    {
        D_800C48E0.field_8 = 0;
        D_800C48B5        += 10;
    }

    D_800C48E0.field_7 = 7;
    var_a0_3           = g_SavegamePtr->field_278;
    var_a0_3           = var_a0_3 - 15;
    var_a0_3           = var_a0_3 - (D_800C48B0 * 5);

    if (var_a0_3 < 0)
    {
        var_a0_3 = 0;
    }

    var_a0_3 += 5;

    var_v0_5 = D_800C48BC ? D_800C48B8 : 100;

    var_v1   = var_v0_5 / var_a0_3;
    var_a0_3 = D_800C48BA / var_a0_3;

    if (var_a0_3 < var_v1)
    {
        var_v1 /= 2;
    }
    else
    {
        var_a0_3 /= 2;
    }

    var_v1 = var_v1 + var_a0_3;

    if (var_v1 >= 31)
    {
        var_v1 = 30;
    }
    else if (var_v1 < 0)
    {
        var_v1 = 0;
    }

    temp3       = &D_800C48B5;
    D_800C48B5 += var_v1;

    if (temp3 == NULL)
    {
        D_800C48B5 += 0;
    }

    if (var_v1 == 30)
    {
        D_800C48E0.field_7 = 0;
    }

    if (D_800C48D0 == GameDifficulty_Easy)
    {
        D_800C48B5 += -5;
    }

    D_800C48B5 = CLAMP(D_800C48B5, 0, 100);
}

void func_800904F4() // 0x800904F4
{
    u8 extraOptions;

    g_SavegamePtr->locationId_A8        = D_800C48B3;
    g_SavegamePtr->clearGameCount_24A   = D_800C48B0;
    g_SavegamePtr->clearGameEndings_24B = D_800C48B1;
    g_SavegamePtr->field_27A            = ((D_800C48B2 & 0x10) * 8) + 64;
    g_SavegamePtr->isNextFearMode_25C   = 1;
    g_SavegamePtr->mapOverlayId_A4      = MapOverlayId_MAP0_S01;

    if (D_800C48B6 != 0)
    {
        Savegame_EventFlagSet(EventFlag_61);
    }

    if (D_800C48B7 != 0)
    {
        Savegame_EventFlagSet(EventFlag_183);
    }

    Savegame_EventFlagSet(EventFlag_62);

    extraOptions = g_GameWork.config_0.optExtraOptionsEnabled_27;

    if ((extraOptions & 0x3) && (extraOptions & 0xC))
    {
        Savegame_EventFlagSet(EventFlag_57);
    }

    if (g_GameWork.config_0.optExtraOptionsEnabled_27 & (1 << 0))
    {
        Savegame_EventFlagSet(EventFlag_58);
    }

    if (D_800C48B5 >= 80)
    {
        g_SavegamePtr->pickedUpSpecialItemCount_25C_3 = 1 << 3;
        if (D_800C48B5 == 100)
        {
            g_SavegamePtr->field_27A                     |= 1 << 5;
            g_SavegamePtr->pickedUpSpecialItemCount_25C_3 = 1 << 4;
        }
    }
}

void Results_DisplayInfo(u32* arg0) // 0x80090664
{
    s32      temp_s1;
    s32      i;
    s32      temp_a0;
    s32      temp_v1;
    POLY_G4* poly;

    GsOT* ot = &g_OrderingTable2[g_ActiveBufferIdx];

    char* D_8002B4C0[] = {
        "GAME_RESULT",
        "Mode",
        "EASY",
        "NORMAL",
        "HARD",
        "Saves",
        "Continues",
        "Total_time",
        "h",
        "m",
        "s",
        ".",
        "km",
        "Walking_distance",
        "Running_distance",
        "Items",
        "/",
        "+",
        "Game_clear",
        "Ending",
        "GOOD+",
        "GOOD",
        "BAD+",
        "BAD",
        "UFO",
        "==Your_rank==",
        "@",
        "Defeated_\x01\x01""enemy_\x01\x01""by_\x01\x01shooting",
        "Defeated_\x01\x01""enemy_\x01\x01""by_\x01\x01""fighting",
        "Shooting_style",
        "Short_range_shots",
        "Middle_range_shots",
        "Long_range_shots",
        "No_aiming_shots"
    };

    Gfx_StringSetColor(StringColorId_White);

    if (g_GameWork.gameStateStep_598[1] < 0x17)
    {
        Gfx_StringSetPosition(0x64, -0x54);
        Gfx_StringDraw(D_8002B4C0[0], 20);
        Gfx_StringSetPosition(0x18, -0x38);
        Gfx_StringDraw(D_8002B4C0[1], 20);

        switch (D_800C48D0)
        {
            case -1:
                Gfx_StringSetPosition(0xFC, -0x38);
                Gfx_StringDraw(D_8002B4C0[2], 20);
                break;

            case 0:
                Gfx_StringSetPosition(0xDE, -0x38);
                Gfx_StringDraw(D_8002B4C0[3], 20);
                break;

            case 1:
                Gfx_StringSetPosition(0xF7, -0x38);
                Gfx_StringDraw(D_8002B4C0[4], 20);
                break;

            default:
                break;
        }

        temp_s1 = func_8009134C(D_800C48A0);
        Gfx_StringSetPosition(0x18, 7);
        Gfx_StringDraw(D_8002B4C0[5], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 0xA), 7);
        Gfx_StringSetColor(D_800C48E0.field_2);
        Gfx_StringDrawInt(3, D_800C48A0);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(D_800C48D1);
        Gfx_StringSetPosition(0x18, 0x1C);
        Gfx_StringDraw(D_8002B4C0[6], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 0xA), 0x1C);
        Gfx_StringSetColor(D_800C48E0.field_3);
        Gfx_StringDrawInt(3, D_800C48D1);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(D_800C48A2);
        Gfx_StringSetPosition(0x18, 0x31);
        Gfx_StringDraw(D_8002B4C0[7], 20);
        Gfx_StringSetPosition(0xDC - (temp_s1 * 0xA), 0x31);
        Gfx_StringSetColor(D_800C48E0.field_4);
        Gfx_StringDrawInt(5, D_800C48A2);
        Gfx_StringSetPosition(0xDC, 0x31);
        Gfx_StringDraw(D_8002B4C0[8], 5);
        Gfx_StringSetPosition(0xFE - (func_8009134C(D_800C48AE) * 0xA), 0x31);
        Gfx_StringDrawInt(2, D_800C48AE);
        Gfx_StringSetPosition(0xFE, 0x31);
        Gfx_StringDraw(D_8002B4C0[9], 5);
        Gfx_StringSetPosition(0x120 - (func_8009134C(D_800C48AF) * 0xA), 0x31);
        Gfx_StringDrawInt(2, D_800C48AF);
        Gfx_StringSetPosition(0x120, 0x31);
        Gfx_StringDraw(D_8002B4C0[10], 5);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(D_800C48A4);
        Gfx_StringSetPosition(0x18, 0x46);
        Gfx_StringDraw(D_8002B4C0[13], 20);
        Gfx_StringSetPosition(0xE5 - ((temp_s1 - 1) * 0xA), 0x46);
        Gfx_StringDrawInt(4, D_800C48A4);
        Gfx_StringDraw(D_8002B4C0[11], 5);

        if (D_800C48A6 < 0x64u)
        {
            Gfx_StringDrawInt(1, 0);
        }

        if (D_800C48A6 < 0xAu)
        {
            Gfx_StringDrawInt(1, 0);
        }

        Gfx_StringDrawInt(3, D_800C48A6);
        Gfx_StringDraw(D_8002B4C0[12], 5);

        temp_s1 = func_8009134C(D_800C48A8);
        Gfx_StringSetPosition(0x18, 0x5B);
        Gfx_StringDraw(D_8002B4C0[14], 0x14);
        Gfx_StringSetPosition(0xE5 - ((temp_s1 - 1) * 0xA), 0x5B);
        Gfx_StringDrawInt(4, D_800C48A8);
        Gfx_StringDraw(D_8002B4C0[11], 5);

        if (D_800C48AA < 0x64u)
        {
            Gfx_StringDrawInt(1, 0);
        }

        if (D_800C48AA < 0xAu)
        {
            Gfx_StringDrawInt(1, 0);
        }

        Gfx_StringDrawInt(3, D_800C48AA);
        Gfx_StringDraw(D_8002B4C0[12], 5);

        temp_s1 = func_8009134C(D_800C48AC);
        Gfx_StringSetPosition(0x18, 0x70);
        Gfx_StringDraw(D_8002B4C0[15], 0x14);
        Gfx_StringSetPosition(0xDA - ((temp_s1 - 1) * 0xA), 0x70);
        Gfx_StringSetColor(D_800C48E0.field_5);
        Gfx_StringDrawInt(3, (s32) D_800C48AC);
        Gfx_StringDraw(D_8002B4C0[16], 5);
        Gfx_StringDrawInt(3, 0xCC);
        Gfx_StringSetColor(D_800C48E0.field_6);
        Gfx_StringDraw("(", 1);

        if (D_800C48B4 != 0)
        {
            Gfx_StringDraw(D_8002B4C0[17], 5);
            Gfx_StringDrawInt(1, D_800C48B4);
        }

        Gfx_StringSetPosition(0x124, 0x70);
        Gfx_StringDraw(")", 1);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(D_800C48B0);
        Gfx_StringSetPosition(0x18, -0x23);
        Gfx_StringDraw(D_8002B4C0[18], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 10), -0x23);
        Gfx_StringSetColor(D_800C48E0.field_1);
        Gfx_StringDrawInt(3, D_800C48B0);
        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, -0xE);
        Gfx_StringDraw(D_8002B4C0[19], 20);
        Gfx_StringSetColor(D_800C48E0.field_0);

        switch (D_800C48B2 & 0x1F)
        {
            case 1:
                Gfx_StringSetPosition(0xEA, -0xE);
                Gfx_StringDraw(D_8002B4C0[20], 10);
                break;

            case 2:
                Gfx_StringSetPosition(0xF4, -0xE);
                Gfx_StringDraw(D_8002B4C0[21], 10);
                break;

            case 4:
                Gfx_StringSetPosition(0xF9, -0xE);
                Gfx_StringDraw(D_8002B4C0[22], 10);
                break;

            case 8:
                Gfx_StringSetPosition(0x102, -0xE);
                Gfx_StringDraw(D_8002B4C0[23], 10);
                break;

            case 16:
                Gfx_StringSetPosition(0x100, -0xE);
                Gfx_StringDraw(D_8002B4C0[24], 10);
                break;

            default:
                break;
        }

        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, 0x9A);
        Gfx_StringDraw(D_8002B4C0[27], 0x20);
        Gfx_StringSetPosition(0x128 - (func_8009134C(D_800C48B8) * 10), 154);
        Gfx_StringSetColor(D_800C48E0.field_7);
        Gfx_StringDrawInt(4, D_800C48B8);
        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, 0x85);
        Gfx_StringDraw(D_8002B4C0[28], 0x20);
        Gfx_StringSetPosition(0x128 - (func_8009134C(D_800C48BA) * 10), 133);
        Gfx_StringSetColor(D_800C48E0.field_7);
        Gfx_StringDrawInt(4, D_800C48BA);

        if (D_800C48BC)
        {
            Gfx_StringSetColor(StringColorId_White);
            Gfx_StringSetPosition(0x18, 0xAF);
            Gfx_StringDraw(D_8002B4C0[29], 0x20);
            Gfx_StringSetPosition(0x48, 0xC4);
            Gfx_StringDraw(D_8002B4C0[30], 0x20);
            Gfx_StringSetPosition(0x106, 0xC4);
            Gfx_StringSetColor(D_800C48E0.field_8);
            Gfx_StringDraw(g_Credits_Digits.f0, 5);
            Gfx_StringSetColor(StringColorId_White);
            Gfx_StringSetPosition(0x48, 0xD9);
            Gfx_StringDraw(D_8002B4C0[31], 0x20);
            Gfx_StringSetPosition(0x106, 0xD9);
            Gfx_StringSetColor(D_800C48E0.field_8);
            Gfx_StringDraw(g_Credits_Digits.f1, 5);
            Gfx_StringSetColor(StringColorId_White);
            Gfx_StringSetPosition(0x48, 0xEE);
            Gfx_StringDraw(D_8002B4C0[32], 0x20);
            Gfx_StringSetPosition(0x106, 0xEE);
            Gfx_StringSetColor(D_800C48E0.field_8);
            Gfx_StringDraw(g_Credits_Digits.f2, 5);
            Gfx_StringSetColor(StringColorId_White);
            Gfx_StringSetPosition(0x48, 0x103);
            Gfx_StringDraw(D_8002B4C0[33], 0x20);
            Gfx_StringSetPosition(0x106, 0x103);
            Gfx_StringSetColor(D_800C48E0.field_8);
            Gfx_StringDraw(g_Credits_Digits.f3, 5);
        }

        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, 0x124);
        Gfx_StringDraw(D_8002B4C0[25], 0x14);

        if (D_800C48B5 >= 0x64)
        {
            Gfx_StringSetColor(0);
        }
        else
        {
            Gfx_StringSetColor(StringColorId_White);
        }

        temp_v1 = D_800C48B5 / 10;
        temp_a0 = D_800C48B5 % 10;

        if (temp_v1 != 0 && temp_a0 == 0)
        {
            Gfx_StringSetPosition(0xA0, 0xC6);

            g_SysWork.enableHighResGlyphs_2350_0 = true;

            for (i = 0; i < temp_v1; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 1);
            }

            g_SysWork.enableHighResGlyphs_2350_0 = false;
        }
        else if (temp_v1 == 0 && temp_a0 != 0)
        {
            Gfx_StringSetPosition(0xA0, 0x124);

            g_SysWork.enableHighResGlyphs_2350_0 = false;

            for (i = 0; i < temp_a0; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 1);
            }
        }
        else
        {
            g_SysWork.enableHighResGlyphs_2350_0 = true;
            Gfx_StringSetPosition(160, 194);

            for (i = 0; i < temp_v1; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 20);
            }

            g_SysWork.enableHighResGlyphs_2350_0 = false;
            Gfx_StringSetPosition(160, 300);

            for (i = 0; i < temp_a0; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 20);
            }
        }

        Gfx_StringSetColor(StringColorId_White);

        for (i = 0; i < 2; i++)
        {
            poly = (POLY_G4*)GsOUT_PACKET_P;
            setPolyG4(poly);

            switch (D_800C48D0)
            {
                case -1:
                    setRGB1(poly, -0x80 - (i << 7), -0x40 - i * 0xC0, 0);
                    setRGB3(poly, -0x80 - (i << 7), -0x40 - i * 0xC0, 0);
                    setRGB0(poly, i << 7, i * 0xC0, 0);
                    setRGB2(poly, i << 7, i * 0xC0, 0);
                    break;

                case 0:
                    setRGB1(poly, 0, -0x80 - (i << 7), -0x40 - i * 0xC0);
                    setRGB3(poly, 0, -0x80 - (i << 7), -0x40 - i * 0xC0);
                    setRGB0(poly, 0, i << 7, i * 0xC0);
                    setRGB2(poly, 0, i << 7, i * 0xC0);
                    break;

                case 1:
                    setRGB1(poly, -0x80 - (i << 7), 0, -0x40 - i * 0xC0);
                    setRGB3(poly, -0x80 - (i << 7), 0, -0x40 - i * 0xC0);
                    setRGB0(poly, i << 7, 0, i * 0xC0);
                    setRGB2(poly, i << 7, 0, i * 0xC0);
                    break;

                default:
                    break;
            }

            setXY4(poly,
                   -0x40, (i * 6) - 0xC4,
                   -0x40, ((i + 1) * 6) - 0xC4,
                    0x42, (i * 6) - 0xC4,
                    0x42, ((i + 1) * 6) - 0xC4);

            addPrim((u8*)ot->org + 0x1C, poly);
            GsOUT_PACKET_P = (u8*)poly + 0x24;
        }
    }
}

u32 func_8009134C(u32 n) // 0x8009134C
{
    u32 digits = 1;

    while (n >= 10)
    {
        n /= 10;
        digits++;
    }

    return digits;
}

void func_80091380(void) {} // 0x80091380

void func_80091388(s32 arg0, s32 arg1, s32 arg2) // 0x80091388
{
    s32 var_a0;
    s32 var_v0;

    if (arg1 <= 0)
    {
        arg1 = 0;
    }
    else
    {
        arg0 = (arg0 - arg1) - 1;
    }

    Text_Debug_Draw(Text_Debug_IntToString(arg0, FP_FROM(arg2, Q12_SHIFT)));

    if (arg1 > 0)
    {
        Text_Debug_Draw(".");
        do
        {
            var_v0 = (arg2 < 0) ? (arg2 + 0xFFF) : arg2;
            arg2  -= Q12_FLOOR(var_v0);
            arg2  *= 10;
            var_a0 = arg2 % Q12(10.0f);
            Text_Debug_Draw(Math_IntegerToString(1, FP_FROM(var_a0, Q12_SHIFT)));
        }
        while (--arg1 > 0);
    }
}

void func_80091464(void) {} // 0x80091464

u32 func_8009146C(s32 arg0) // 0x8009146C
{
    s32 var_v0;
    u32 res;
    u32 var_v1_2;

    if (arg0 == 0)
    {
        var_v1_2 = g_SavegamePtr->meleeKillCount_25D;
        var_v0   = (g_SavegamePtr->meleeKillCountB_25E & 0xF) << 8;
    }
    else
    {
        var_v1_2 = g_SavegamePtr->rangedKillCount_25F;
        var_v0 = (g_SavegamePtr->meleeKillCountB_25E & 0xF0) * 16;
    }

    res = var_v1_2 + var_v0;
    if (res > 4000)
    {
        res = 4000;
    }
    return res;
}

void func_800914C4(s32 arg0, u32 val) // 0x800914C4
{
    if (val > 4000)
    {
        val = 4000;
    }

    if (arg0 == 0)
    {
        g_SavegamePtr->meleeKillCount_25D  = val;
        g_SavegamePtr->meleeKillCountB_25E = (g_SavegamePtr->meleeKillCountB_25E & 0xF0) | ((val >> 8) & 0x0F);
    }
    else
    {
        g_SavegamePtr->rangedKillCount_25F = val;
        g_SavegamePtr->meleeKillCountB_25E = (g_SavegamePtr->meleeKillCountB_25E & 0x0F) | ((val >> 4) & 0xF0);
    }
}

void func_8009151C(u32 arg0, s32 arg1, s32 arg2)
{
    switch (arg0)
    {
        case 4:
            if (g_SavegamePtr->field_278 < 50000)
            {
                g_SavegamePtr->field_278++;
            }
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            if (g_SavegamePtr->firedShotCount_264 < 50000)
            {
                g_SavegamePtr->firedShotCount_264++;

                if (arg0 != 5)
                {
                    if (arg2 > 0x8000)
                    {
                        arg2 = 0x8000;
                    }
                    g_SavegamePtr->field_260 += arg2 >> 4;
                }

                switch (arg0)
                {
                    case 0:
                        if (g_SavegamePtr->closeRangeShotCount_266 < 50000)
                        {
                            g_SavegamePtr->closeRangeShotCount_266++;
                            return;
                        }
                        break;

                    case 1:
                        if (g_SavegamePtr->midRangeShotCount_268 < 50000)
                        {
                            g_SavegamePtr->midRangeShotCount_268++;
                        }
                        if (arg1 != 0)
                        {
                            if (g_SavegamePtr->field_26E < 50000)
                            {
                                g_SavegamePtr->field_26E++;
                                return;
                            }
                        }
                        break;

                    case 2:
                        if (g_SavegamePtr->longRangeShotCount_26A < 50000)
                        {
                            g_SavegamePtr->longRangeShotCount_26A++;
                        }
                        if (arg1 != 0)
                        {
                            if (g_SavegamePtr->field_270 < 50000)
                            {
                                g_SavegamePtr->field_270++;
                                return;
                            }
                        }
                        break;

                    case 3:
                        if (g_SavegamePtr->field_26C < 50000)
                        {
                            g_SavegamePtr->field_26C++;
                        }
                        if (arg1 != 0)
                        {
                            if (g_SavegamePtr->field_272 < 50000)
                            {
                                g_SavegamePtr->field_272++;
                                return;
                            }
                        }
                        break;

                    case 4:
                    case 5:
                        break;
                }
            }
            break;

        case 7:
            if (g_SavegamePtr->field_278 < 50000)
            {
                g_SavegamePtr->field_278++;
            }

        case 6:
            if (g_SavegamePtr->field_274 < 50000)
            {
                g_SavegamePtr->field_274++;
            }

            if (arg1 != 0)
            {
                if (g_SavegamePtr->field_276 < 50000)
                {
                    g_SavegamePtr->field_276++;
                }
            }
            break;
    }
}

void GameFs_StfRollBinLoad() // 0x80091778
{
    // Required for match.
    if (g_Font24AtlasImg.tPage != 0) {}

    Fs_QueueStartRead(FILE_VIN_STF_ROLL_BIN, FS_BUFFER_1);
    func_800917C0(FONT24_BUFFER, 1, &g_Font24AtlasImg);
}

void func_800917C0(void* arg0, s32 arg1, s_FsImageDesc* img) // 0x800917C0
{
    u32 tPage;

    if (arg1 != 0)
    {
        arg0 -= ALIGN(Fs_GetFileSize(FILE_TIM_FONT24_TIM), 0x800);
    }

    Fs_QueueStartReadTim(FILE_TIM_FONT24_TIM, arg0, img);

    D_800AFE08.field_18 = ((u8*)&img->tPage)[1]; // `Fs_QueuePostLoadTim` does something similar.
    tPage               = ((u8*)&img->tPage)[1];

    D_800AFE08.field_14  = tPage & 0x10;
    D_800AFE08.field_14 |= tPage & 0xF;
    D_800AFE08.field_16  = (img->clutY << 6) | ((img->clutX >> 4) & 0x3F);
}

void func_8009185C(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) // 0x8009185C
{
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_4;
    s32 temp_lo_7;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_v0;
    u16 temp_t0 = 24;

    temp_t1   = arg2 << 22;
    temp_lo   = temp_t1 / (arg6 >> 2);
    temp_lo_2 = arg9 * temp_t0;
    temp_lo_4 = (arg6 + (s32)Q12_MULT_PRECISE(arg3, temp_lo_2)) >> 2;
    temp_lo_4 = temp_t1 / temp_lo_4;

    D_800AFE24.sub_0.field_0  = 0;
    D_800AFE24.sub_0.field_2  = 0;
    D_800AFE24.sub_0.field_4  = 0;
    D_800AFE24.sub_0.field_6  = 24;
    D_800AFE24.sub_0.field_7  = 0;
    D_800AFE24.sub_0.field_8  = 0x2CFFFFFF;
    D_800AFE24.sub_0.field_18 = D_800AFE08.field_18;
    D_800AFE24.sub_0.field_16 = D_800AFE08.field_16;
    D_800AFE24.sub_0.field_14 = D_800AFE08.field_14;
    D_800AFE24.field_1C = arg3;
    D_800AFE24.field_20 = arg0;
    D_800AFE24.field_22 = arg1;
    D_800AFE24.field_24 = arg2;
    D_800AFE24.field_28 = arg4;
    D_800AFE24.field_2C = arg5;
    D_800AFE24.field_30 = arg6;
    D_800AFE24.field_34 = arg7;
    D_800AFE24.field_38 = arg8;
    D_800AFE24.field_3C = arg9;
    D_800AFE24.field_40 = Q12_MULT_PRECISE(temp_lo, arg4);
    D_800AFE24.field_44 = Q12_MULT_PRECISE(temp_lo_4, arg4);

    temp_v0             = arg4 + Q12_MULT_PRECISE(arg3, arg7);
    D_800AFE24.field_48 = Q12_MULT_PRECISE(temp_lo, temp_v0) - D_800AFE24.field_40;
    D_800AFE24.field_4C = Q12_MULT_PRECISE(temp_lo_4, temp_v0) - D_800AFE24.field_44;
    D_800AFE24.field_50 = Q12_MULT_PRECISE(temp_lo, arg5);

    temp_lo_7           = arg8 * temp_t0;
    temp_t2             = arg5 + Q12_MULT_PRECISE(arg3, temp_lo_7);
    D_800AFE24.field_54 = Q12_MULT_PRECISE(temp_lo_4, temp_t2);
}

INCLUDE_RODATA("bodyprog/nonmatchings/credits", D_8002B5CC);
