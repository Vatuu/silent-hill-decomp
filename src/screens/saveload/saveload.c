#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "screens/saveload/saveload.h"

void func_801E2D8C() // 0x801E2D8C
{
    s32 i;
    s32 j;

    func_80037124();

    D_801E750C = 0;
    D_801E7510 = 0;
    D_801E76D4 = INVENTORY_ITEM_COUNT_MAX;
    D_801E76D6 = 0;

    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        D_801E76D2[i] = 1;
        D_801E76CE[i] = NO_VALUE;
        D_801E7564[i] = 0;
        D_801E756C[i] = 0;
        D_801E7570[i] = NO_VALUE;
        D_801E7574[i] = NO_VALUE;
        D_801E7578[i] = 0;
        D_801E7514[i] = 1;
        D_801E7518[i] = 0;

        for (j = 0; j < SAVE_COUNT_MAX; j++)
        {
            D_801E7584[j + (SAVE_COUNT_MAX * i)] = 0;
        }

        D_801E76D0 = 1;
    }
}

// TODO: Check objdiff
#ifdef NON_MATCHING
void Gfx_SaveBackgroundDraw() // 0x801E2EBC
{
    s_func_801E5898 var;
    s32             i;
    
    DVECTOR posTable[] = 
    {
        {
            .vx = 59,
            .vy = 16
        },
        {
            .vx = 209,
            .vy = 16
        }
    };

    char* strs[] =
    {
        "SLOT1",
        "SLOT2"
    };

    Gfx_StringSetColor(ColorId_White);
    
    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        Gfx_StringSetPosition(posTable[i].vx, posTable[i].vy);
        Gfx_StringDraw(strs[i], 50);
    }

    var.field_0.vx = -136;
    var.field_0.vy = 60;
    var.field_4.vx = 272;
    var.field_4.vy = 40;
    Gfx_RectSaveInfoDraw(&var);
}
#else
INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SaveBackgroundDraw); // 0x801E3304
#endif

void func_801E2F90(s32 saveSlotIdx) // 0x801E2F90
{
    D_801E7578[saveSlotIdx] = D_800A97D4[saveSlotIdx] - D_801E7570[saveSlotIdx];
}

void func_801E2FCC(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3) // 0x801E2FCC
{
    #define OFFSET_X             SCREEN_POSITION_X(47.0f)
    #define FILE_STR_MARGIN_X    SCREEN_POSITION_X(10.0f)
    #define FILE_ID_STR_MARGIN_X FILE_STR_MARGIN_X + SCREEN_POSITION_X(15.75f)
    #define POS_Y                SCREEN_POSITION_Y(14.75f)

    extern char D_801E2720[]; // "FILE" - needs rodata migration.
    char*       str = D_801E2720;

    if (arg0 == D_800A97D4[saveSlotIdx] && arg3 >= 4)
    {
        Gfx_StringSetColor(ColorId_White);

        // Draw "FILE" string.
        Gfx_StringSetPosition((saveSlotIdx * OFFSET_X) + FILE_STR_MARGIN_X, POS_Y);
        Gfx_StringDraw(str, 50);

        // Draw file ID string.
        Gfx_StringSetPosition((saveSlotIdx * OFFSET_X) + FILE_ID_STR_MARGIN_X, POS_Y);
        Gfx_StringDrawInt(1, fileId);
    }
}

s32 func_801E3078(s_UnkSaveload0* arg0) // 0x801E3078
{
    if (arg0 != NULL && (arg0->field_8 & (1 << 24)))
    {
        Gfx_StringSetColor(ColorId_Gold);
        return 1;
    }

    Gfx_StringSetColor(ColorId_White);
    return 0;
}

void func_801E30C4(s_UnkSaveload0* ptr, s32 arg1, s32 idx) // 0x801E30C4
{
    #define OFFSET_X SCREEN_POSITION_X(47.0f)
    #define MARGIN_X SCREEN_POSITION_X(28.25f)
    #define OFFSET_Y SCREEN_POSITION_Y(8.5f)
    #define MARGIN_Y SCREEN_POSITION_Y(22.25f)

    s32        var0;
    s32        var1;
    s_801E2728 var2;
    s32        idxVar;
    s32        colorId;

    idxVar = (s8)ptr->field_8;
    var2 = D_801E2728;

    var1 = D_801E7570[idx];
    if (arg1 >= var1 && (var1 + 4) >= arg1)
    {
        var0 = arg1 - var1;

        func_801E3078(ptr->field_C);

        if (D_801E76D6 != 0 && D_800A97D6 == idx && D_800A97D4[idx] == arg1)
        {
            if (D_801E76D5 != 0)
            {
                colorId = ColorId_Gold;
            }
            else
            {
                colorId = ColorId_White;
            }
            Gfx_StringSetColor(colorId);
        }

        Gfx_StringSetPosition(((idx * OFFSET_X) + MARGIN_X) - (var2.field_0[idxVar] / 2),
                              (var0 * OFFSET_Y) + MARGIN_Y);
        Gfx_StringDraw(D_801E74A8[idxVar], 50);
    }
}

void func_801E326C(s8* arg0, s8* arg1, s32 arg2, s32 arg3) // 0x801E326C
{
    if (arg2 == 0)
    {
        D_801E756C[arg3] = 0;
    }

    if (arg2 < D_801E7570[arg3] || (D_801E7570[arg3] + 4) < arg2)
    {
        if (D_801E756C[arg3] != arg0[6])
        {
            D_801E756C[arg3] = arg0[6];
        }
    }
    else
    {
        Gfx_SavesOutlineDraw(arg0, arg1, arg2, arg3);
    }
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3304); // 0x801E3304

// TODO: Check objdiff. Jumptable already added.
// `arg0` = what it's doing. Formatting, saving, or loading.
#ifdef NON_MATCHING
void func_801E3910(s32 arg0, s32 arg1) // 0x801E3910
{
    s32 strIdx;

    char* strs[] =
    {
        " ",
        "\x07You_\x01\x01removed_\x01\x01the_\x01\x01MEMORY_\x01\x01""CARD!",
        "\x07Now_formatting...",
        "\x07Now_saving...",
        "\x07Unable_to_create_a_new_file.",
        "\x07""Finished_saving.",
        "\x07""Failed_to_save!",
        "\x07The_data_is_not_found!",
        "\x07The_data_is_damaged!",
        "\x07""Failed_to_load!",
        "\x07""FInished_loading.",
        "\x07Now_loading..."
    };

    s16 xOffsets[] =
    {
        0,   16,
        141, 107,
        223, 136,
        119, 182,
        170, 117,
        111, 114
    };

    switch (arg0)
    {
        // Format.
        case 1:
            strIdx = (arg1 == arg0) ? 1 : 2;
            break;

        // Save.
        case 2:
            switch (arg1)
            {
                // Memory card removed.
                case 0:
                    strIdx = 1; 
                    break;

                // Now saving.
                case 1:
                    strIdx = 3; 
                    break;

                // Unable to create new file.
                case 7:
                    strIdx = 4;
                    break;

                // Finished saving.
                case 11:
                    strIdx = 5; 
                    break;

                // Failed to save.
                case 10:
                    strIdx = 6; 
                    break;

                default:
                    strIdx = 0; 
                    break;
            }
            break;

        // Load.
        case 3:
            switch (arg1)
            {
                // Now loading.
                case 1:
                    strIdx = 11;
                    break;

                // Data is damaged.
                case 101:
                    strIdx = 8;
                    break;

                // Failed to load.
                case 10:
                    strIdx = 9;
                    break;

                // Finished loading.
                case 11:
                    strIdx = 10;
                    break;

                // Memory card removed.
                case 0:
                    strIdx = 1;
                    break;

                // Memory card removed.
                case 100:
                    strIdx = 1;
                    break;

                default:
                    strIdx = 0;
                    break;
            }
            break;

        default:
            strIdx = 0;
            break;
    }

    switch (D_801E7510)
    {
        case 0:
            D_801E750C = 0;
            D_801E7554 = 0;

            if (strIdx == 1)
            {
                g_GameWork.gameStateStep_598[2] = 0;
                D_801E7570[D_800A97D6] = NO_VALUE;
                D_801E7578[D_800A97D6] = NO_VALUE;
            }

            D_801E7554 = strIdx;
            D_801E7510++;
            
        case 1:
            // Loading and something.
            if (arg0 == 2 && arg1 == 1)
            {
                D_801E76D6 = arg1;
            }

            // Finished saving and `D_801E7554` isn't required string.
            if (strIdx == 5 && D_801E7554 != strIdx)
            {
                D_801E76CE[D_800A97D6] = D_800A97D4[D_800A97D6];
                D_801E76CE[1 - D_800A97D6] = NO_VALUE;
                D_801E76D4 = 0;
            }

            D_801E7554 = strIdx;
            Gfx_StringSetPosition(160 - (xOffsets[strIdx] >> 1), 186);
            Gfx_StringDraw(strs[strIdx], 99);

            // Finished saving.
            if (strIdx == 5)
            {
                D_801E76D6 = 0;
            }
            break;

        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3910);
#endif

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3C44); // 0x801E3C44

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3E78); // 0x801E3E78

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SelectedMemBarDraw); // 0x801E4010

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E43C8); // 0x801E43C8

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesTransparentBgDraw); // 0x801E451C

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesOutlineDraw); // 0x801E4D90

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E52D8); // 0x801E52D8

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_RectMemLoadDraw); // 0x801E54DC

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_RectSaveInfoDraw); // 0x801E5898

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Save_SaveDataInfoDraw); // 0x801E5E18

void GameState_SaveScreen_Update() // 0x801E6320
{
    D_801E76D0 = 1;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7524[0]();
    }

    D_801E7524[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    func_801E7244();
    func_801E70C8();

    if (g_GameWork.gameState_594 == GameState_Unk10)
    {
        func_800363D0();
    }
}

void func_801E63C0() // 0x801E63C0
{
    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        VSync(8);
    }

    g_IntervalVBlanks = 1;
    D_800BCD0C = 6;

    g_GameWork.field_58C = 0;
    g_GameWork.field_58D = 0;
    g_GameWork.field_58E = 0;

    D_800BCD39 = 0;
    if (g_GameWork.gameState_594 == GameState_DeathLoadScreen || g_GameWork.gameState_594 == GameState_SaveScreen)
    {
        if (D_800A97D8 != 0)
        {
            D_800BCD34 = 0;
        }
    }

    D_801E7520 = 0;
    D_800A97D8 = (g_GameWork.gameState_594 == GameState_Unk10);

    func_801E2D8C();

    g_SysWork.timer_20 = 0;
    g_GameWork.gameStateStep_598[0]++;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E649C); // 0x801E649C

void func_801E69E8() // 0x801E69E8
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            D_801E751C = 1;
            D_801E7520 = 30;
            g_GameWork.gameStateStep_598[1] = 1;
            g_GameWork.gameStateStep_598[2] = 0;

        case 1:
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 2:
            func_8002E94C(6, D_800BCD40, 0, 0);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 3:
            switch (func_8002E990())
            {
                case 10:
                    D_801E7520 = 30;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                case 11:
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[0]++;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6B18); // 0x801E6B18

void func_801E6DB0() // 0x801E6DB0
{
    s32 var0;
    s32 var1;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            D_801E751C = 3;

            func_8002E94C(4, D_800BCD40, D_800BCD3F, D_800BCD3E);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;

        case 1:
            var0 = func_8002E990();
            if (var0 != 1)
            {
                if (var0 != 11)
                {
                    D_800BCD39 = 1;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
                }

                func_8002E94C(2, D_800BCD40, 0, 0);

                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            D_801E7520 = 30;
            break;

        case 2:
            var1 = func_8002E990();
            if (var1 == 1)
            {
                D_801E7520 = 30;
                break;
            }

            if (var1 != 11)
            {
                D_800BCD39 = 1;
                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20 = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            D_801E7520 = 300;
            g_SysWork.timer_20 = 0;
            g_GameWork.gameStateStep_598[0]++;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        default:
            break;
    }
}

void func_801E6F38() // 0x801E6F38
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        // TODO: Are these meant to use GameState? `gameStateStep` is normally something different?
        // First case here increments it too.
        case GameState_Unk0:
            func_8002E830();

            D_800A97D7 = 1;

            // Backup current savegame? Does anything ever restore from this?
            g_GameWork.saveGame_90 = g_GameWork.saveGame_30C;

            func_80035178();
            
            g_SysWork.flags_2298 = 8;

            GameFs_MapLoad(g_SaveGamePtr->mapOverlayIdx_A4);

            D_800BCD0C = 2;
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case GameState_KonamiLogo:
        {
            if ((D_800BCD0C & 0x7) == 0x5)
            {
                Fs_QueueWaitForEmpty();
                Settings_ScreenAndVolUpdate();

                Game_StateSetNext(GameState_MainLoadScreen);
            }
            break;
        }

        default:
            break;
    }
}

void Gfx_SaveBackground() // 0x801E709C
{
    // Draw "SLOT 1"/"SLOT 2" strings and bottom transparent frame.
    Gfx_SaveBackgroundDraw();

    // Draws background image.
    Gfx_BackgroundSpriteDraw(&D_800A902C);
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E70C8); // 0x801E70C8

void func_801E7244() // 0x801E7244
{
    if (D_801E7520 <= 0)
    {
        return;
    }

    D_801E76D0 = 0;
    D_801E7520--;

    switch (D_801E751C) 
    {
        case 1:
            func_801E3910(D_801E751C, (D_800BCD34 >> (D_800BCD40 * 3)) & 0x7);
            break;

        case 2:
        case 3:
            func_801E3910(D_801E751C, func_8002E990());
            break;
    }
}

void func_801E72DC() // 0x801E72DC
{
    func_801E3C44();
}

void GameState_DeathLoadScreen_Update() // 0x801E72FC
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7544[0]();
    }

    D_801E7544[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    func_801E7244();
    func_801E70C8();
}

void func_801E737C() // 0x801E737C
{
    if (!func_80033548())
    {
        return;
    }

    if (D_800BCD28 == 0 || D_800BCD39 != 0 || !func_80033548())
    {
        g_GameWork.gameState_594 = GameState_SaveScreen;

        if (g_GameWork.gameStatePrev_590 == GameState_KcetLogo)
        {
            g_GameWork.gameStateStep_598[0] = 1;
            g_GameWork.gameStateStep_598[1] = g_GameWork.gameStatePrev_590;

            D_800BCD0C = 3;

            GameFs_TitleGfxLoad();
        }

        return;
    }

    D_800BCD2C = BOOT_ADDR_0 + (D_800A97D6 * 2640);
    D_800BCD2C = D_800BCD2C + (D_800A97D4[D_800A97D6] * 16);
    D_800BCD40 = D_800BCD2C[5];
    D_800BCD3F = D_800BCD2C[6];
    D_800BCD3E = D_800BCD2C[7];

    g_GameWork.gameStateStep_598[0]++;
    g_SysWork.timer_20 = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}
