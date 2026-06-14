#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/ranking.h"
#include "main/fsqueue.h"

static const s32 pad_rodata_8002B2F8 = 0;

s16 g_RankingSavegameCount;

u16 g_RankingGameplayHours;

u16 g_RankingWalkDistKm;

u16 g_RankingWalkDistM;

u16 g_RankingRunDistKm;

u16 g_RankingRunDistM;

u16 g_RankingPickedUpItemCount;

u8 g_RankingGameplayMinutes;

u8 g_RankingGameplaySeconds;

u8 g_RankingClearGameCount;

u8 g_RankingClearGameEndings;

u8 g_RankingCurrentEndingFlags;

u8 g_RankingEndLocationId;

u8 g_RankingPickedUpSpecialItemCount;

s8 g_RankingScore;

u8 g_RankingHasEventFlag61;

u8 g_RankingHasEventFlag183;

u16 g_RankingEnemyKillsShooting;

u16 g_RankingEnemyKillsMelee;

bool g_RankingHasFiredShot;

u32 g_RankingCloseRangeShotPercent;

u32 g_RankingMidRangeShotPercent;

u32 g_RankingLongRangeShotPercent;

u32 g_RankingNoAimingShotPercent;

s8 g_RankingGameDifficulty;

u8 g_RankingContinueCount;

s8 __pad_bss_800C48D2[14];

s_800C48E0 D_800C48E0;

struct
{
    char f0[5];
    char f1[5];
    char f2[5];
    char f3[5];
} g_Credits_Digits = { "0.00", "0.00", "0.00", "0.00" };

void func_8008F94C() // 0x8008F94C
{
    s16 gameplayMinutes;
    s32 var_a0_3;
    s32 var_v1;
    u16 firedShotCount;
    u16 var_v0_5;
    u8  temp_a0_2;
    u8  temp;
    s8* temp3;

    g_RankingScore = 0;
    g_RankingGameDifficulty = g_SavegamePtr->gameDifficulty;
    g_RankingSavegameCount = g_SavegamePtr->savegameCount;
    g_RankingSavegameCount = CLAMP(g_RankingSavegameCount, 0, 999);
    g_RankingContinueCount = g_SavegamePtr->continueCount;
    g_RankingGameplayHours = g_SavegamePtr->add290Hours * 24 + FP_FROM(g_SavegamePtr->gameplayTimer, Q12_SHIFT) / 3600;
    g_RankingWalkDistKm = FP_FROM(g_SavegamePtr->walkDistance, Q12_SHIFT) / 1000;
    g_RankingWalkDistM = FP_FROM(g_SavegamePtr->walkDistance, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->walkDistance, Q12_SHIFT) / 1000) * 1000;
    g_RankingRunDistKm = FP_FROM(g_SavegamePtr->runDistance, Q12_SHIFT) / 1000;
    g_RankingRunDistM = FP_FROM(g_SavegamePtr->runDistance, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->runDistance, Q12_SHIFT) / 1000) * 1000;
    g_RankingPickedUpItemCount = g_SavegamePtr->pickedUpItemCount;
    g_RankingGameplayMinutes = (FP_FROM(g_SavegamePtr->gameplayTimer, Q12_SHIFT) / 60) % 60;
    g_RankingGameplaySeconds = FP_FROM(g_SavegamePtr->gameplayTimer, Q12_SHIFT) - (FP_FROM(g_SavegamePtr->gameplayTimer, Q12_SHIFT) / 60) * 60;
    g_RankingClearGameCount = g_SavegamePtr->clearGameCount;
    g_RankingClearGameEndings = g_SavegamePtr->clearGameEndings;
    g_RankingCurrentEndingFlags = g_SavegamePtr->currentEndingFlags;
    g_RankingHasEventFlag61 = Savegame_EventFlagGetAlt(EventFlag_61);
    g_RankingPickedUpSpecialItemCount = 0;
    g_RankingHasEventFlag183 = Savegame_EventFlagGetAlt(EventFlag_183);
    g_RankingEnemyKillsShooting = func_8009146C(1);
    g_RankingEnemyKillsMelee = func_8009146C(0);

    firedShotCount = g_SavegamePtr->firedShotCount;
    g_RankingHasFiredShot = firedShotCount != 0;

    if (g_RankingHasFiredShot)
    {
        g_RankingCloseRangeShotPercent = g_SavegamePtr->closeRangeShotCount;
        g_RankingMidRangeShotPercent = g_SavegamePtr->midRangeShotCount;
        g_RankingLongRangeShotPercent = g_SavegamePtr->longRangeShotCount;
        g_RankingMidRangeShotPercent = g_RankingMidRangeShotPercent + g_SavegamePtr->field_26C;
        g_RankingCloseRangeShotPercent = g_RankingCloseRangeShotPercent * 100 / firedShotCount;
        g_RankingMidRangeShotPercent = g_RankingMidRangeShotPercent * 100 / firedShotCount;
        g_RankingLongRangeShotPercent = g_RankingLongRangeShotPercent * 100 / firedShotCount;
        g_RankingNoAimingShotPercent = ((100 - g_RankingCloseRangeShotPercent) - g_RankingMidRangeShotPercent) - g_RankingLongRangeShotPercent;

        g_Credits_Digits.f0[0] = (((g_RankingCloseRangeShotPercent) / 100) % 10) + '0';
        g_Credits_Digits.f0[2] = (((g_RankingCloseRangeShotPercent) / 10) - (((g_RankingCloseRangeShotPercent) / 100) * 10)) + '0';
        g_Credits_Digits.f0[3] = ((g_RankingCloseRangeShotPercent) % 10) + '0';

        g_Credits_Digits.f1[0] = (((g_RankingMidRangeShotPercent) / 100) % 10) + '0';
        g_Credits_Digits.f1[2] = (((g_RankingMidRangeShotPercent) / 10) - (((g_RankingMidRangeShotPercent) / 100) * 10)) + '0';
        g_Credits_Digits.f1[3] = ((g_RankingMidRangeShotPercent) % 10) + '0';

        g_Credits_Digits.f2[0] = (((g_RankingLongRangeShotPercent) / 100) % 10) + '0';
        g_Credits_Digits.f2[2] = (((g_RankingLongRangeShotPercent) / 10) - (((g_RankingLongRangeShotPercent) / 100) * 10)) + '0';
        g_Credits_Digits.f2[3] = ((g_RankingLongRangeShotPercent) % 10) + '0';

        g_Credits_Digits.f3[0] = (((g_RankingNoAimingShotPercent) / 100) % 10) + '0';
        g_Credits_Digits.f3[2] = (((g_RankingNoAimingShotPercent) / 10) - (((g_RankingNoAimingShotPercent) / 100) * 10)) + '0';
        g_Credits_Digits.f3[3] = ((g_RankingNoAimingShotPercent) % 10) + '0';
    }

    gameplayMinutes    = g_RankingGameplayMinutes + (g_RankingGameplayHours * 60);

    // @bugfix Pre-JAP1 accidentally included unlocked Hyper Blaster colors in the picked up item count.
    // JAP1 onwards fix this by ignoring the top-most bit.
    // See `pickedUpSpecialItemCount` field comment for more info.
#if VERSION_EQUAL_OR_NEWER(JAP1)
    g_RankingPickedUpSpecialItemCount = g_SavegamePtr->pickedUpSpecialItemCount & 0x7;
#else
    g_RankingPickedUpSpecialItemCount = g_SavegamePtr->pickedUpSpecialItemCount & 0xF;
#endif

    g_RankingEndLocationId = g_SavegamePtr->locationId;
    D_800C3E40 = 7;
    temp_a0_2  = g_GameWork.config.extraOptionsEnabled;

    if ((temp_a0_2 & 0x3) && (temp_a0_2 & 0xC))
    {
        D_800C3E40 = 0xF;
    }

    if (g_GameWork.config.extraOptionsEnabled & 1)
    {
        D_800C3E40 |= 0x10;
    }

    if (Inventory_HyperBlasterUnlockTest() == NO_VALUE || (g_RankingCurrentEndingFlags & GameEndingFlag_Ufo))
    {
        D_800C3E40 |= 0x20;
    }

    D_800C48E0.field_0 = 7;

    switch (g_RankingCurrentEndingFlags)
    {
        // @bug These cases could never be used? `currentEndingFlags` only holds the current ending that was triggered.
        // Maybe this was meant to check `clearGameEndings` instead?
        case GameEndingFlag_GoodPlus + GameEndingFlag_Good:
        case GameEndingFlag_GoodPlus + GameEndingFlag_BadPlus:
        case GameEndingFlag_Good + GameEndingFlag_BadPlus:
        case GameEndingFlag_GoodPlus + GameEndingFlag_Good + GameEndingFlag_BadPlus:
        case GameEndingFlag_GoodPlus + GameEndingFlag_Bad:
        case GameEndingFlag_Good + GameEndingFlag_Bad:
        case GameEndingFlag_GoodPlus + GameEndingFlag_Good + GameEndingFlag_Bad:
        case GameEndingFlag_BadPlus + GameEndingFlag_Bad:
        case GameEndingFlag_GoodPlus + GameEndingFlag_BadPlus + GameEndingFlag_Bad:
        case GameEndingFlag_Good + GameEndingFlag_BadPlus + GameEndingFlag_Bad:
        case GameEndingFlag_GoodPlus + GameEndingFlag_Good + GameEndingFlag_BadPlus + GameEndingFlag_Bad:
            break;

        case GameEndingFlag_GoodPlus:
            D_800C48E0.field_0 = 0;
            g_RankingScore += 10;
            break;

        case GameEndingFlag_Good:
            g_RankingScore += 5;
            break;

        case GameEndingFlag_BadPlus:
            g_RankingScore += 3;
            break;

        case GameEndingFlag_Bad:
            g_RankingScore += 1;
            break;

        case GameEndingFlag_Ufo:
            g_RankingScore += 0;
            break;
    }

    D_800C48E0.field_5 = 7;

    if ((g_RankingPickedUpItemCount / 15) < 0 || (g_RankingPickedUpItemCount / 15) >= 10)
    {
        D_800C48E0.field_5 = 0;
        g_RankingScore += 10;
    }
    else
    {
        g_RankingScore += g_RankingPickedUpItemCount / 15;
    }

    D_800C48E0.field_2 = 7;

    if (g_RankingSavegameCount < 3)
    {
        D_800C48E0.field_2 = 0;
        g_RankingScore += 5;
    }
    else if (g_RankingSavegameCount < 6)
    {
        g_RankingScore += 4;
    }
    else if (g_RankingSavegameCount < 11)
    {
        g_RankingScore += 3;
    }
    else if (g_RankingSavegameCount < 21)
    {
        g_RankingScore += 2;
    }
    else if (g_RankingSavegameCount < 31)
    {
        g_RankingScore += 1;
    }

    D_800C48E0.field_3 = 7;

    if (g_RankingContinueCount < 2)
    {
        D_800C48E0.field_3 = 0;
        g_RankingScore += 5;
    }
    else if (g_RankingContinueCount < 4)
    {
        g_RankingScore += 4;
    }
    else if (g_RankingContinueCount < 6)
    {
        g_RankingScore += 3;
    }
    else if (g_RankingContinueCount < 8)
    {
        g_RankingScore += 2;
    }
    else if (g_RankingContinueCount < 10)
    {
        g_RankingScore += 1;
    }

    D_800C48E0.field_4 = 7;

    if (gameplayMinutes < 90)
    {
        D_800C48E0.field_4 = 0;
        g_RankingScore += 10;
    }
    else if (gameplayMinutes < 180)
    {
        g_RankingScore += 5;
    }
    else if (gameplayMinutes < 240)
    {
        g_RankingScore += 3;
    }
    else if (gameplayMinutes < 360)
    {
        g_RankingScore += 2;
    }
    else if (gameplayMinutes < 720)
    {
        g_RankingScore += 1;
    }

    D_800C48E0.field_1 = 7;

    temp = g_RankingClearGameCount;

    if (temp >= 5)
    {
        D_800C48E0.field_1 = 0;
        g_RankingScore        += 10;
    }
    else
    {
        g_RankingScore += temp * 2;
    }

    D_800C48E0.field_6 = 7;
    temp               = g_RankingPickedUpSpecialItemCount;

    if (temp >= 5)
    {
        D_800C48E0.field_6 = 0;
        g_RankingScore    += 10;
    }
    else
    {
        g_RankingScore += temp * 2;
    }

    D_800C48E0.field_8 = 7;

    if (g_RankingHasFiredShot)
    {
        s32 shootingScore;
        shootingScore = ((g_RankingCloseRangeShotPercent + g_RankingMidRangeShotPercent * 2) + (g_RankingLongRangeShotPercent * 3)) - (g_RankingNoAimingShotPercent * 4);
        shootingScore = shootingScore / 10;

        if (shootingScore < 0)
        {
            shootingScore = 0;
        }
        else if (shootingScore > 10)
        {
            shootingScore = 10;
        }

        g_RankingScore += shootingScore;

        if (shootingScore == 10)
        {
            D_800C48E0.field_8 = 0;
        }
    }
    else
    {
        D_800C48E0.field_8 = 0;
        g_RankingScore    += 10;
    }

    D_800C48E0.field_7 = 7;
    var_a0_3           = g_SavegamePtr->field_278;
    var_a0_3           = var_a0_3 - 15;
    var_a0_3           = var_a0_3 - (g_RankingClearGameCount * 5);

    if (var_a0_3 < 0)
    {
        var_a0_3 = 0;
    }

    var_a0_3 += 5;

    var_v0_5 = g_RankingHasFiredShot ? g_RankingEnemyKillsShooting : 100;

    var_v1   = var_v0_5 / var_a0_3;
    var_a0_3 = g_RankingEnemyKillsMelee / var_a0_3;

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

    temp3       = &g_RankingScore;
    g_RankingScore += var_v1;

    if (temp3 == NULL)
    {
        g_RankingScore += 0;
    }

    if (var_v1 == 30)
    {
        D_800C48E0.field_7 = 0;
    }

    if (g_RankingGameDifficulty == GameDifficulty_Easy)
    {
        g_RankingScore += -5;
    }

    g_RankingScore = CLAMP(g_RankingScore, 0, 100);
}

void func_800904F4() // 0x800904F4
{
    u8 extraOptions;

    g_SavegamePtr->locationId         = g_RankingEndLocationId;
    g_SavegamePtr->clearGameCount     = g_RankingClearGameCount;
    g_SavegamePtr->clearGameEndings   = g_RankingClearGameEndings;
    g_SavegamePtr->currentEndingFlags = ((g_RankingCurrentEndingFlags & GameEndingFlag_Ufo) * 8) + GameEndingFlag_6; // Adds `GameEndingFlag_7` if `GameEndingFlag_Ufo` is set? TODO: Deoptimize.
    g_SavegamePtr->isNextFearMode     = 1;
    g_SavegamePtr->mapIdx             = MapIdx_MAP0_S01;

    if (g_RankingHasEventFlag61)
    {
        Savegame_EventFlagSet(EventFlag_61);
    }

    if (g_RankingHasEventFlag183)
    {
        Savegame_EventFlagSet(EventFlag_183);
    }

    Savegame_EventFlagSet(EventFlag_62);

    extraOptions = g_GameWork.config.extraOptionsEnabled;

    if ((extraOptions & 0x3) && (extraOptions & 0xC))
    {
        Savegame_EventFlagSet(EventFlag_57);
    }

    if (g_GameWork.config.extraOptionsEnabled & (1 << 0))
    {
        Savegame_EventFlagSet(EventFlag_58);
    }

    if (g_RankingScore >= 80)
    {
        g_SavegamePtr->pickedUpSpecialItemCount = 8;
        if (g_RankingScore == 100)
        {
            g_SavegamePtr->currentEndingFlags      |= GameEndingFlag_5;
            g_SavegamePtr->pickedUpSpecialItemCount = 16;
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

    if (g_GameWork.gameStateSteps[1] < 0x17)
    {
        Gfx_StringSetPosition(0x64, -0x54);
        Gfx_StringDraw(D_8002B4C0[0], 20);
        Gfx_StringSetPosition(0x18, -0x38);
        Gfx_StringDraw(D_8002B4C0[1], 20);

        switch (g_RankingGameDifficulty)
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

        temp_s1 = func_8009134C(g_RankingSavegameCount);
        Gfx_StringSetPosition(0x18, 7);
        Gfx_StringDraw(D_8002B4C0[5], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 0xA), 7);
        Gfx_StringSetColor(D_800C48E0.field_2);
        Gfx_StringDrawInt(3, g_RankingSavegameCount);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(g_RankingContinueCount);
        Gfx_StringSetPosition(0x18, 0x1C);
        Gfx_StringDraw(D_8002B4C0[6], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 0xA), 0x1C);
        Gfx_StringSetColor(D_800C48E0.field_3);
        Gfx_StringDrawInt(3, g_RankingContinueCount);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(g_RankingGameplayHours);
        Gfx_StringSetPosition(0x18, 0x31);
        Gfx_StringDraw(D_8002B4C0[7], 20);
        Gfx_StringSetPosition(0xDC - (temp_s1 * 0xA), 0x31);
        Gfx_StringSetColor(D_800C48E0.field_4);
        Gfx_StringDrawInt(5, g_RankingGameplayHours);
        Gfx_StringSetPosition(0xDC, 0x31);
        Gfx_StringDraw(D_8002B4C0[8], 5);
        Gfx_StringSetPosition(0xFE - (func_8009134C(g_RankingGameplayMinutes) * 0xA), 0x31);
        Gfx_StringDrawInt(2, g_RankingGameplayMinutes);
        Gfx_StringSetPosition(0xFE, 0x31);
        Gfx_StringDraw(D_8002B4C0[9], 5);
        Gfx_StringSetPosition(0x120 - (func_8009134C(g_RankingGameplaySeconds) * 0xA), 0x31);
        Gfx_StringDrawInt(2, g_RankingGameplaySeconds);
        Gfx_StringSetPosition(0x120, 0x31);
        Gfx_StringDraw(D_8002B4C0[10], 5);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(g_RankingWalkDistKm);
        Gfx_StringSetPosition(0x18, 0x46);
        Gfx_StringDraw(D_8002B4C0[13], 20);
        Gfx_StringSetPosition(0xE5 - ((temp_s1 - 1) * 0xA), 0x46);
        Gfx_StringDrawInt(4, g_RankingWalkDistKm);
        Gfx_StringDraw(D_8002B4C0[11], 5);

        if (g_RankingWalkDistM < 0x64u)
        {
            Gfx_StringDrawInt(1, 0);
        }

        if (g_RankingWalkDistM < 0xAu)
        {
            Gfx_StringDrawInt(1, 0);
        }

        Gfx_StringDrawInt(3, g_RankingWalkDistM);
        Gfx_StringDraw(D_8002B4C0[12], 5);

        temp_s1 = func_8009134C(g_RankingRunDistKm);
        Gfx_StringSetPosition(0x18, 0x5B);
        Gfx_StringDraw(D_8002B4C0[14], 0x14);
        Gfx_StringSetPosition(0xE5 - ((temp_s1 - 1) * 0xA), 0x5B);
        Gfx_StringDrawInt(4, g_RankingRunDistKm);
        Gfx_StringDraw(D_8002B4C0[11], 5);

        if (g_RankingRunDistM < 0x64u)
        {
            Gfx_StringDrawInt(1, 0);
        }

        if (g_RankingRunDistM < 0xAu)
        {
            Gfx_StringDrawInt(1, 0);
        }

        Gfx_StringDrawInt(3, g_RankingRunDistM);
        Gfx_StringDraw(D_8002B4C0[12], 5);

        temp_s1 = func_8009134C(g_RankingPickedUpItemCount);
        Gfx_StringSetPosition(0x18, 0x70);
        Gfx_StringDraw(D_8002B4C0[15], 0x14);
        Gfx_StringSetPosition(0xDA - ((temp_s1 - 1) * 0xA), 0x70);
        Gfx_StringSetColor(D_800C48E0.field_5);
        Gfx_StringDrawInt(3, (s32) g_RankingPickedUpItemCount);
        Gfx_StringDraw(D_8002B4C0[16], 5);
        Gfx_StringDrawInt(3, 0xCC);
        Gfx_StringSetColor(D_800C48E0.field_6);
        Gfx_StringDraw("(", 1);

        if (g_RankingPickedUpSpecialItemCount != 0)
        {
            Gfx_StringDraw(D_8002B4C0[17], 5);
            Gfx_StringDrawInt(1, g_RankingPickedUpSpecialItemCount);
        }

        Gfx_StringSetPosition(0x124, 0x70);
        Gfx_StringDraw(")", 1);
        Gfx_StringSetColor(StringColorId_White);

        temp_s1 = func_8009134C(g_RankingClearGameCount);
        Gfx_StringSetPosition(0x18, -0x23);
        Gfx_StringDraw(D_8002B4C0[18], 20);
        Gfx_StringSetPosition(0x11E - ((temp_s1 - 1) * 10), -0x23);
        Gfx_StringSetColor(D_800C48E0.field_1);
        Gfx_StringDrawInt(3, g_RankingClearGameCount);
        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, -0xE);
        Gfx_StringDraw(D_8002B4C0[19], 20);
        Gfx_StringSetColor(D_800C48E0.field_0);

        switch (g_RankingCurrentEndingFlags & 0x1F)
        {
            case GameEndingFlag_GoodPlus:
                Gfx_StringSetPosition(0xEA, -0xE);
                Gfx_StringDraw(D_8002B4C0[20], 10);
                break;

            case GameEndingFlag_Good:
                Gfx_StringSetPosition(0xF4, -0xE);
                Gfx_StringDraw(D_8002B4C0[21], 10);
                break;

            case GameEndingFlag_BadPlus:
                Gfx_StringSetPosition(0xF9, -0xE);
                Gfx_StringDraw(D_8002B4C0[22], 10);
                break;

            case GameEndingFlag_Bad:
                Gfx_StringSetPosition(0x102, -0xE);
                Gfx_StringDraw(D_8002B4C0[23], 10);
                break;

            case GameEndingFlag_Ufo:
                Gfx_StringSetPosition(0x100, -0xE);
                Gfx_StringDraw(D_8002B4C0[24], 10);
                break;

            default:
                break;
        }

        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, 0x9A);
        Gfx_StringDraw(D_8002B4C0[27], 0x20);
        Gfx_StringSetPosition(0x128 - (func_8009134C(g_RankingEnemyKillsShooting) * 10), 154);
        Gfx_StringSetColor(D_800C48E0.field_7);
        Gfx_StringDrawInt(4, g_RankingEnemyKillsShooting);
        Gfx_StringSetColor(StringColorId_White);
        Gfx_StringSetPosition(0x18, 0x85);
        Gfx_StringDraw(D_8002B4C0[28], 0x20);
        Gfx_StringSetPosition(0x128 - (func_8009134C(g_RankingEnemyKillsMelee) * 10), 133);
        Gfx_StringSetColor(D_800C48E0.field_7);
        Gfx_StringDrawInt(4, g_RankingEnemyKillsMelee);

        if (g_RankingHasFiredShot)
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

        if (g_RankingScore >= 0x64)
        {
            Gfx_StringSetColor(0);
        }
        else
        {
            Gfx_StringSetColor(StringColorId_White);
        }

        temp_v1 = g_RankingScore / 10;
        temp_a0 = g_RankingScore % 10;

        if (temp_v1 != 0 && temp_a0 == 0)
        {
            Gfx_StringSetPosition(0xA0, 0xC6);

            g_SysWork.enableHighResGlyphs = true;

            for (i = 0; i < temp_v1; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 1);
            }

            g_SysWork.enableHighResGlyphs = false;
        }
        else if (temp_v1 == 0 && temp_a0 != 0)
        {
            Gfx_StringSetPosition(0xA0, 0x124);

            g_SysWork.enableHighResGlyphs = false;

            for (i = 0; i < temp_a0; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 1);
            }
        }
        else
        {
            g_SysWork.enableHighResGlyphs = true;
            Gfx_StringSetPosition(160, 194);

            for (i = 0; i < temp_v1; i++)
            {
                Gfx_StringDraw(D_8002B4C0[26], 20);
            }

            g_SysWork.enableHighResGlyphs = false;
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

            switch (g_RankingGameDifficulty)
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
            arg2  -= Q12_TRUNC(arg2);
            arg2  *= 10;
            var_a0 = arg2 % Q12(10.0f);
            Text_Debug_Draw(Text_Debug_IntToString(1, FP_FROM(var_a0, Q12_SHIFT)));
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
        var_v1_2 = g_SavegamePtr->meleeKillCount;
        var_v0   = (g_SavegamePtr->meleeKillCountB & 0xF) << 8;
    }
    else
    {
        var_v1_2 = g_SavegamePtr->rangedKillCount;
        var_v0 = (g_SavegamePtr->meleeKillCountB & 0xF0) * 16;
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
        g_SavegamePtr->meleeKillCount  = val;
        g_SavegamePtr->meleeKillCountB = (g_SavegamePtr->meleeKillCountB & 0xF0) | ((val >> 8) & 0x0F);
    }
    else
    {
        g_SavegamePtr->rangedKillCount = val;
        g_SavegamePtr->meleeKillCountB = (g_SavegamePtr->meleeKillCountB & 0x0F) | ((val >> 4) & 0xF0);
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
            if (g_SavegamePtr->firedShotCount < 50000)
            {
                g_SavegamePtr->firedShotCount++;

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
                        if (g_SavegamePtr->closeRangeShotCount < 50000)
                        {
                            g_SavegamePtr->closeRangeShotCount++;
                            return;
                        }
                        break;

                    case 1:
                        if (g_SavegamePtr->midRangeShotCount < 50000)
                        {
                            g_SavegamePtr->midRangeShotCount++;
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
                        if (g_SavegamePtr->longRangeShotCount < 50000)
                        {
                            g_SavegamePtr->longRangeShotCount++;
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
