#include "game.h"

#include <libetc.h>
#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/credits.h"
#include "bodyprog/demo.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

void GameState_Unk0_Update() // 0x80032D1C
{
    s32 gameState;
    s32 unkGameStateVar;

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            Gfx_Init(SCREEN_WIDTH, 0);
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 1:
            if (!func_80045B28())
            {
                unkGameStateVar = D_800A9774[g_GameWork.gameStateStep_598[1]];
                if (unkGameStateVar != 0)
                {
                    Sd_EngineCmd(unkGameStateVar);
                    g_GameWork.gameStateStep_598[1]++;
                }
                else
                {
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_GameWork.gameStateStep_598[0]++;
                }
            }
            break;

        case 2:
            Fs_QueueStartReadTim(FILE_1ST_FONT16_TIM, FS_BUFFER_1, &g_Font16AtlasImg);
            Fs_QueueStartReadTim(FILE_1ST_KONAMI_TIM, FS_BUFFER_1, &g_KonamiLogoImg);

            g_Gfx_ScreenFade = 2;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 3:
            if ((g_Gfx_ScreenFade & 0x7) == ((1 << 0) | (1 << 2)))
            {
                Fs_QueueWaitForEmpty();

                gameState = g_GameWork.gameState_594;
                
                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameState_594        = gameState + 1;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;
    }

    func_80033548();
    Gfx_BackgroundSpriteDraw(&g_MainImg0);
    func_80089090(1);
}

void MainLoop() // 0x80032EE0
{
    #define TICKS_PER_SECOND_MIN (TICKS_PER_SECOND / 4)
    #define H_BLANKS_PER_TICK    263

    #define H_BLANKS_PER_SECOND               (H_BLANKS_PER_TICK * TICKS_PER_SECOND)              // 15780
    #define H_BLANKS_TO_SEC_CONVERSION_FACTOR ((float)FP_TIME(1.0f) / (float)H_BLANKS_PER_SECOND) // 0.25956907477f

    #define H_BLANKS_PER_FRAME_MIN   (H_BLANKS_PER_SECOND / TICKS_PER_SECOND_MIN)                    // 1052
    #define H_BLANKS_FP_TO_SEC_SCALE (s32)(H_BLANKS_TO_SEC_CONVERSION_FACTOR * (float)FP_TIME(1.0f)) // 1063
    #define H_BLANKS_UNKNOWN_SCALE   10419                                                           // TODO: Somehow derive this value.
    #define V_BLANKS_MAX             4

    s32 vBlanks;
    s32 vCount;
    s32 vCountCopy;
    s32 interval;

    // Initialize engine.
    GsInitVcount();
    Savegame_CardCleanInit();
    func_8002E7BC();
    func_8002E85C();
    Joy_Init();
    VSyncCallback(&Gfx_VSyncCallback);
    InitGeom();
    func_8004BB10(); // Initializes something for graphics.
    func_800890B8();
    sd_init();

    // Run game.
    while (true)
    {
        g_MainLoop_FrameCount++;

        // Update input.
        Joy_ReadP1();
        Demo_ControllerDataUpdate();
        Joy_ControllerDataUpdate();

        if (MainLoop_ShouldWarmReset() == 2)
        {
            Game_WarmBoot();
            continue;
        }

        g_ObjectTableIdx = GsGetActiveBuff();

        if (g_GameWork.gameState_594 == GameState_MainLoadScreen ||
            g_GameWork.gameState_594 == GameState_InGame)
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 17));
        }
        else if (g_GameWork.gameState_594 == GameState_InventoryScreen)
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx * 40000));
        }
        else
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 15));
        }

        GsClearOt(0, 0, &g_ObjectTable0[g_ObjectTableIdx]);
        GsClearOt(0, 0, &g_ObjectTable1[g_ObjectTableIdx]);

        g_SysWork.field_22A0 = 0;

        // Call update function for current GameState.
        g_GameStateUpdateFuncs[g_GameWork.gameState_594]();

        Demo_Update();
        Demo_GameRandSeedSet();

        if (MainLoop_ShouldWarmReset() == 2)
        {
            Game_WarmBoot();
            continue;
        }

        func_8003260C();
        func_8002EB88();
        func_800485D8();

        if (!func_80045B28())
        {
            Fs_QueueUpdate();
        }

        func_80089128();
        func_8008D78C(); // Camera update?
        DrawSync(0);

        // Handle V sync.
        if (g_SysWork.flags_22A4 & (1 << 1))
        {
            vBlanks   = VSync(-1);
            g_VBlanks = vBlanks - g_PrevVBlanks;

            Demo_PresentIntervalUpdate();

            interval      = g_Demo_VideoPresentInterval;
            g_PrevVBlanks = vBlanks;

            if (interval < g_IntervalVBlanks)
            {
                interval = g_IntervalVBlanks;
            }

            do
            {
                VSync(0);
                g_VBlanks++;
                g_PrevVBlanks++;
            }
            while (g_VBlanks < interval);

            g_UncappedVBlanks = g_VBlanks;
            g_VBlanks         = MIN(g_VBlanks, 4);

            vCount     = g_Demo_VideoPresentInterval * H_BLANKS_PER_TICK;
            vCountCopy = g_UncappedVBlanks * H_BLANKS_PER_TICK;
            g_VBlanks  = g_Demo_VideoPresentInterval;
        }
        else
        {
            if (g_SysWork.sysState_8 != SysState_Gameplay)
            {
                g_VBlanks     = VSync(-1) - g_PrevVBlanks;
                g_PrevVBlanks = VSync(-1);
                VSync(0);
            }
            else
            {
                if (g_Gfx_ScreenFade != 1)
                {
                    VSync(0);
                }

                g_VBlanks     = VSync(-1) - g_PrevVBlanks;
                g_PrevVBlanks = VSync(-1);

                while (g_VBlanks < g_IntervalVBlanks)
                {
                    VSync(0);
                    g_VBlanks++;
                    g_PrevVBlanks++;
                }
            }

            // Update V blanks.
            g_UncappedVBlanks = g_VBlanks;
            g_VBlanks         = MIN(g_VBlanks, V_BLANKS_MAX);
            
            // Update V count.
            vCount     = MIN(GsGetVcount(), H_BLANKS_PER_FRAME_MIN); // NOTE: Will call `GsGetVcount` twice.
            vCountCopy = vCount;
        }

        // Update delta time.
        g_DeltaTime0 = FP_MULTIPLY(vCount, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime1 = FP_MULTIPLY(vCountCopy, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime2 = FP_MULTIPLY(vCount, H_BLANKS_UNKNOWN_SCALE, Q12_SHIFT); // TODO: Unknown time scale.
        GsClearVcount();

        // Draw objects?
        GsSwapDispBuff();
        GsSortClear(g_GameWork.background2dColor_R_58C, g_GameWork.background2dColor_G_58D, g_GameWork.background2dColor_B_58E, &g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable1[g_ObjectTableIdx]);
    }
}

void Settings_ScreenAndVolUpdate() // 0x0x800333CC
{
    Settings_ScreenXYSet(g_GameWork.config_0.optScreenPosX_1C, g_GameWork.config_0.optScreenPosY_1D);
    Sd_EngineCmd((g_GameWork.config_0.optSoundType_1E != 0) ? 1 : 2);
    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Settings_RestoreDefaults() // 0x8003342c
{
    g_GameWork.config_0.optExtraWeaponCtrl_23 = 1;
    g_GameWork.config_0.optBrightness_22      = 3;

    Settings_RestoreControlDefaults(0);

    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_ENABLED;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MAX;
    g_GameWork.config_0.optVolumeSe_20         = OPT_SOUND_VOLUME_MAX;

    Settings_ScreenAndVolUpdate();

    g_GameWork.config_0.optExtraBloodColor_24 = 0;
}

void Settings_RestoreControlDefaults(s32 arg0) // 0x80033480
{
    // TODO: D_8002511C .rodata
    u32  i;
    u16* ptr;

    for (i = 0, ptr = &g_GameWorkPtr->config_0.controllerConfig_0; i < INPUT_ACTION_COUNT; i++, ptr++)
    {
        *ptr = (&D_8002511C[arg0].enter_0)[i];
    }
}

void nullsub_800334C8() {}

void func_800334D0() {}

// Possibly related to save functionallity
s32 func_800334D8(s32 idx) // 0x800334D8
{
    s32 i;
    s32 res;
    s32 var0;
    s32 var1;

    res  = 0;
    var0 = Savegame_CardFilesGetUsageBits(idx);

    for (i = 0; i < 15; i++)
    {
        var1 = (var0 >> (i * 2)) & 0x3;
        if (var1 == 1)
        {
            return 0;
        }

        if (var1 == 3)
        {
            res = 1;
        }
    }

    return res;
}

static inline s32 WrapIdx(s32 idx)
{
    return (idx < 0) ? (idx + 3) : idx;
}

bool func_80033548() // 0x80033548
{
    u32                 sp10[2];
    s32                 sp18[8];
    u32                 sp38;
    s32                 sp3C;
    s32                 temp_t0;
    s32                 temp_v0_4;
    u32                 temp_v0_6;
    s32                 temp_v0_8;
    u32                 temp_v1_7;
    s32                 var_a0;
    s32                 var_a1;
    s32                 i;
    s32                 j;
    s32                 k;
    s32                 var_v1;
    s_SavegameMetadata* savegameMetaPtr;
    u32                 temp_a2;

    sp3C = 1;

    memset(&sp10, 0, 8);
    func_8002E7BC();
    func_8002E85C();

    if (g_GameWork.gameState_594 == GameState_Unk10 ||
        g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        g_SaveScreenPlayerState = 2;
    }
    else
    {
        g_SaveScreenPlayerState = 3;
    }

    sp38                        = D_800BCD34;
    D_800BCD34                  = func_8002E898();
    g_MemCardsTotalElementCount = 0;
    g_SavegameCount             = 0;

    for (i = 0; i < 8; i += 4)
    {
        temp_a2 = (D_800BCD34 >> (i * 3)) & 0x7;
        sp3C   *= temp_a2;
        temp_t0 = (sp38 >> (i * 3)) & 0x7;
        var_a0  = WrapIdx(i);

        g_ActiveSavegameEntry                              = GetActiveSavegameEntry(var_a0 >> 2);
        g_SlotElementCount[var_a0 >> 2]                    = 0;
        g_MemCardElementCount[var_a0 >> 2]                 = 0;
        sp18[i]                                            = 0;
        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
        g_ActiveSavegameEntry->field_5                     = i;
        g_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_ActiveSavegameEntry->elementIdx_7                = 0;
        g_ActiveSavegameEntry->field_C                     = NULL;

        if (temp_t0 == 3)
        {
            if (temp_a2 != 3)
            {
                sp10[var_a0 >> 2] = 1;
            }
        }
        else if (temp_a2 == 3)
        {
            sp10[var_a0 >> 2] = 1;
        }

        if (g_SaveScreenPlayerState == 2)
        {
            if (temp_t0 == 4 && temp_a2 != temp_t0)
            {
                sp10[WrapIdx(i) >> 2] = 1;
            }

            if (temp_t0 != 4 && temp_a2 == 4)
            {
                sp10[WrapIdx(i) >> 2] = 1;
            }
        }

        if (temp_a2 != 3)
        {
            switch (temp_a2)
            {
                case 1:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_NoMemCard;
                    break;

                case 4:
                    if (g_SaveScreenPlayerState == 2)
                    {
                        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31600;
                        var_a0                                             = WrapIdx(i);
                        g_MemCardElementCount[var_a0 >> 2]++;
                    }

                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case 5:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case 0:
                case 2:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_LoadMemCard;
                    break;
            }

            g_SlotElementCount[WrapIdx(i) >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else if (Savegame_CardFileUsageCount(i) == 0)
        {
            if (g_SaveScreenPlayerState == 3)
            {
                g_ActiveSavegameEntry->type_4 = SavegameEntryType_NoDataInMemCard;
            }
            else if (Savegame_CardFileUsageFreeCount(i) == 0)
            {
                g_ActiveSavegameEntry->type_4 = SavegameEntryType_OutOfBlocks;
            }
            else
            {
                g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31700;
                g_ActiveSavegameEntry->type_4                      = SavegameEntryType_NewFile;

                var_a0 = WrapIdx(i);
                g_MemCardElementCount[var_a0 >> 2]++;
            }

            g_SlotElementCount[WrapIdx(i) >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else if (g_SaveScreenPlayerState == 3 && func_800334D8(i) != 0)
        {
            g_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedSave;

            var_a0 = WrapIdx(i);
            g_SlotElementCount[var_a0 >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else
        {
            D_800A97E4[i] = Savegame_CardFilesGetUsageBits(i);

            for (j = 0; j < 15; j++)
            {
                temp_v0_4 = (D_800A97E4[i] >> (j * 2)) & 0x3;

                if (temp_v0_4 == 0)
                {
                    continue;
                }

                if (temp_v0_4 == 3)
                {
                    g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 0;
                    g_ActiveSavegameEntry->field_5                     = i;
                    g_ActiveSavegameEntry->fileIdx_6                   = j;
                    g_ActiveSavegameEntry->elementIdx_7                = 0;
                    g_ActiveSavegameEntry->type_4                      = SavegameEntryType_CorruptedSave;

                    var_a0 = WrapIdx(i);

                    g_MemCardElementCount[var_a0 >> 2]++;
                    g_SavegameCount--;
                    g_SlotElementCount[var_a0 >> 2]++;

                    g_ActiveSavegameEntry++;
                }
                else
                {
                    for (k = 0; k < 11; k++)
                    {
                        savegameMetaPtr = Savegame_MetadataGet(i, j, k);

                        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = savegameMetaPtr->field_0;
                        g_ActiveSavegameEntry->field_5                     = i;
                        g_ActiveSavegameEntry->fileIdx_6                   = j;
                        g_ActiveSavegameEntry->elementIdx_7                = k;
                        g_ActiveSavegameEntry->savegameCount_2             = savegameMetaPtr->savegameCount_8;
                        g_ActiveSavegameEntry->locationId_8                = savegameMetaPtr->locationId_A;
                        g_ActiveSavegameEntry->field_C                     = savegameMetaPtr;

                        if (savegameMetaPtr->field_0 > 0)
                        {
                            g_ActiveSavegameEntry->type_4 = SavegameEntryType_Save;

                            var_v1 = WrapIdx(i);

                            g_MemCardElementCount[var_v1 >> 2]++;
                            g_SlotElementCount[var_v1 >> 2]++;
                            g_ActiveSavegameEntry++;
                        }
                        else if (g_SaveScreenPlayerState == 2 && sp18[i] == 0)
                        {
                            sp18[i]                                            = 1;
                            g_ActiveSavegameEntry->type_4                      = SavegameEntryType_NewSave;
                            g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31900;

                            var_a1 = WrapIdx(i);
                            g_MemCardElementCount[var_a1 >> 2]++;
                            g_SlotElementCount[var_a1 >> 2]++;
                            g_ActiveSavegameEntry++;
                        }
                    }
                }
            }

            if (g_SaveScreenPlayerState == 2 && sp18[i] == 0 && Savegame_CardFileUsageFreeCount(i) > 0)
            {
                g_ActiveSavegameEntry->savegameCount_2             = 0;
                g_ActiveSavegameEntry->field_C                     = NULL;
                sp18[i]                                            = 1;
                g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31800;
                temp_v1_7                                          = D_800A97E4[i];
                temp_v0_6                                          = temp_v1_7 & 0x3;

                for (j = 0; temp_v0_6 == 3 || temp_v0_6 == 1; j++)
                {
                    j++;
                    temp_v0_6 = (temp_v1_7 >> (j * 2)) & 0x3;
                    j--;
                }

                g_ActiveSavegameEntry->field_5   = i;
                g_ActiveSavegameEntry->fileIdx_6 = j;

                g_ActiveSavegameEntry->elementIdx_7 = 0;
                g_ActiveSavegameEntry->type_4       = SavegameEntryType_NewFile;

                var_a0 = WrapIdx(i);

                g_MemCardElementCount[var_a0 >> 2]++;

                temp_v0_4 = ((D_800A97E4[i]) >> (j * 2)) & 0x3; // Not needed here but fixes stack order.

                g_SlotElementCount[var_a0 >> 2]++;
                g_ActiveSavegameEntry++;
            }
        }

        g_MemCardsTotalElementCount += g_MemCardElementCount[WrapIdx(i) >> 2];
    }

    g_SavegameCount += g_MemCardsTotalElementCount;

    for (i = 0; i < 8; i += 4)
    {
        temp_v0_8 = (D_800BCD34 >> (i * 3)) & 0x7;
        if (temp_v0_8 == 0 || temp_v0_8 == 2)
        {
            D_800A97E0            = (WrapIdx(i) >> 2) == 0;
            g_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0);

            if (g_ActiveSavegameEntry->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (g_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (g_SaveScreenPlayerState == 2)
                {
                    D_800A97DC = 22;
                }
                else
                {
                    D_800A97DC = g_ActiveSavegameEntry->type_4;
                }
            }
            else
            {
                D_800A97DC = 24;
            }
            break;
        }
    }

    D_800A97DC--;

    if (D_800A97DC == 0)
    {
        sp10[D_800A97E0 == 0] = 1;
        D_800A97E0            = NO_VALUE;
    }

    if (D_800A97E0 >= 0)
    {
        g_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0 == 0);

        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
        g_ActiveSavegameEntry->field_5                     = 0;
        g_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_ActiveSavegameEntry->elementIdx_7                = 0;
        g_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
        g_SlotElementCount[D_800A97E0 == 0]                = 1;
        g_ActiveSavegameEntry                              = GetActiveSavegameEntry(D_800A97E0);

        if ((g_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreenPlayerState == SavegameEntryType_CorruptedMemCard) ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_Save ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_NewSave ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_NewFile)
        {
            g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
            g_ActiveSavegameEntry->field_5                     = 0;
            g_ActiveSavegameEntry->fileIdx_6                   = 0;
            g_ActiveSavegameEntry->elementIdx_7                = 0;
            g_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
            g_SlotElementCount[D_800A97E0]                     = 1;
        }

        sp3C = 0;
    }

    if (D_800A97D9 == 0 && (sp10[0] != 0 || sp10[1] != 0))
    {
        for (j = 0; j < 2; j++)
        {
            g_ActiveSavegameEntry = GetActiveSavegameEntry(j);
            D_800BCD18[j]         = 0;
            D_800BCD20[j]         = 0;

            for (i = 0; i < g_SlotElementCount[j]; i++)
            {
                if (D_800BCD18[j] < g_ActiveSavegameEntry->currentScreenSessionSaves_0)
                {
                    D_800BCD18[j] = g_ActiveSavegameEntry->currentScreenSessionSaves_0;
                    D_800BCD20[j] = i;
                }

                g_ActiveSavegameEntry++;
            }

            if (sp10[j] != 0)
            {
                g_SlotElementSelectedIdx[j] = D_800BCD20[j];
            }
        }

        if (D_800BCD18[1] > D_800BCD18[0])
        {
            g_SelectedSaveSlotIdx = 1;
        }
        else
        {
            g_SelectedSaveSlotIdx = 0;
        }

        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    switch (sp3C)
    {
        case 1:
        case 3:
        case 4:
        case 5:
        case 9:
        case 12:
        case 15:
        case 16:
        case 20:
        case 25:
            return true;

        default:
            return false;
    }
}

void SysWork_Clear() // 0x800340E0
{
    bzero(&g_SysWork, sizeof(s_SysWork));
}

s32 MainLoop_ShouldWarmReset() // 0x80034108
{
    #define RESET_BTN_FLAGS (ControllerFlag_Select | ControllerFlag_Start)
    #define UNK_BTN_FLAGS_0 (ControllerFlag_Select | ControllerFlag_Start | ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1)
    #define UNK_BTN_FLAGS_1 (ControllerFlag_Start | ControllerFlag_Triangle | ControllerFlag_Square)

    if (g_GameWork.gameState_594 < GameState_MovieIntroAlternate)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_SaveScreen && g_GameWork.gameStateStep_598[0] == 4)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_Unk10 && (g_GameWork.gameStateStep_598[0] == 2 || g_GameWork.gameStateStep_598[0] == 3))
    {
        return 0;
    }

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        if (g_Demo_FrameCount > (TICKS_PER_SECOND * 30))
        {
            return 2;
        }
    }
    else
    {
        g_Demo_FrameCount = 0;
    }

    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        return 0;
    }

    // Reset something.
    if ((g_Controller0->btnsHeld_C & RESET_BTN_FLAGS) != RESET_BTN_FLAGS)
    {
        g_UnknownFrameCounter = 0;
    }

    if (g_UnknownFrameCounter >= 121)
    {
        return 2; 
    }
    else if (g_Controller0->btnsHeld_C == UNK_BTN_FLAGS_0 && (g_Controller0->btnsClicked_10 & UNK_BTN_FLAGS_0))
    {
        return 2; 
    }
    else if (g_Controller0->btnsHeld_C == UNK_BTN_FLAGS_1 && (g_Controller0->btnsClicked_10 & ControllerFlag_Start))
    {
        return 2; 
    }

    return (g_SysWork.flags_22A4 & (1 << 8)) ? 2 : 0;
}

void Game_WarmBoot() // 0x80034264
{
    e_GameState prevState;

    DrawSync(0);
    Gfx_ClearRectInterlaced(0, 32, 512, 448, 0, 0, 0);
    func_800892A4(4);
    func_80089128();
    Sd_EngineCmd(19);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    Sd_EngineCmd(20);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    Fs_QueueReset();
    Fs_QueueWaitForEmpty();
    sd_work_init();
    func_80035AC8(1);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Demo_Stop();
    }

    SysWork_Clear();
    Demo_SequenceAdvance(1);
    Demo_DemoDataRead();
    GameFs_TitleGfxLoad();
    Fs_QueueWaitForEmpty();
    Joy_Update();

    prevState                = g_GameWork.gameState_594;
    g_GameWork.gameState_594 = GameState_MainMenu;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_Gfx_ScreenFade = 6;

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;

    D_800B5C30 = FP_TIME(0.0f);
}

void Joy_Init() // 0x8003441C
{
    PadInitDirect(&g_GameWork.rawController_5B4, g_Controller1);
    PadStartCom();
}

void Joy_ReadP1() // 0x80034450
{
    s_ControllerData* cont = &g_GameWork.controllers_38[0];

    // NOTE: `memcpy` is close, reads `rawController_5B4` as two `s32`s, but doesn't give match.
    // memcpy(&cont->analogController_0, &g_GameWork.rawController_5B4, sizeof(s_AnalogController));

    *(s32*)&cont->analogController_0        = *(s32*)&g_GameWork.rawController_5B4;
    *(s32*)&cont->analogController_0.rightX = *(s32*)&g_GameWork.rawController_5B4.rightX;

    // Alternate
    // ((s32*)&cont->analogController_0)[0] = ((s32*)&g_GameWork.rawController_5B4)[0];
    // ((s32*)&cont->analogController_0)[1] = ((s32*)&g_GameWork.rawController_5B4)[1];
}

void Joy_Update() // 0x8003446C
{
    Joy_ReadP1();
    Joy_ControllerDataUpdate();
}

void Joy_ControllerDataUpdate() // 0x80034494
{
    #define CONTROLLER_COUNT             2
    #define PULSE_INITIAL_INTERVAL_TICKS (TICKS_PER_SECOND / 2)
    #define PULSE_INTERVAL_TICKS         (PULSE_INITIAL_INTERVAL_TICKS / 10)

    s_ControllerData* cont;
    s32               i;
    s32               prevBtnsHeld;
    s32               pulseTicks;
    s32               btnsPulsed;

    // Update controller button flags.
    for (i = CONTROLLER_COUNT, cont = g_Controller0; i > 0; i--, cont++)
    {
        prevBtnsHeld = cont->btnsHeld_C;

        // Update held button flags.
        if (cont->analogController_0.status == 0xFF)
        {
            cont->btnsHeld_C = 0;
        }
        else
        {
            cont->btnsHeld_C = ~cont->analogController_0.digitalButtons & 0xFFFF;
        }

        // TODO: Demagic hex values.
        ControllerData_AnalogToDigital(cont, (*(u16*)&cont->analogController_0.status & 0x5300) == 0x5300);

        // Directional held flag sanitation? TODO: Find out what it's doing.
        cont->btnsHeld_C = cont->btnsHeld_C | (((cont->btnsHeld_C << 20) | (cont->btnsHeld_C << 8)) &
                                                (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft));

        // Clear up/down held flags if concurrent.
        if ((cont->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
        {
            cont->btnsHeld_C &= ~(ControllerFlag_LStickUp | ControllerFlag_LStickDown);
        }

        // Clear left/right held flags if concurrent.
        if ((cont->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
        {
            cont->btnsHeld_C = cont->btnsHeld_C & ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }

        // Update clicked and released button flags.
        cont->btnsClicked_10  = ~prevBtnsHeld & cont->btnsHeld_C;
        cont->btnsReleased_14 = prevBtnsHeld  & ~cont->btnsHeld_C;

        // Update pulse ticks.
        pulseTicks = cont->pulseTicks_8;
        if (cont->btnsHeld_C != prevBtnsHeld)
        {
            pulseTicks = 0;
        }
        else
        {
            pulseTicks += g_VBlanks;
        }

        // Update pulsed button flags.
        if (pulseTicks >= PULSE_INITIAL_INTERVAL_TICKS)
        {
            cont->btnsPulsed_18 = cont->btnsHeld_C;
            pulseTicks          = PULSE_INITIAL_INTERVAL_TICKS - PULSE_INTERVAL_TICKS;
        }
        else
        {
            cont->btnsPulsed_18 = cont->btnsClicked_10;
        }

        btnsPulsed             = cont->btnsPulsed_18;
        cont->pulseTicks_8     = pulseTicks;
        cont->btnsPulsedGui_1C = btnsPulsed;

        // Clear left/right pulse flags if concurrent.
        if ((btnsPulsed & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }

        // Clear up/down pulse flags if concurrent.
        if ((cont->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickUp | ControllerFlag_LStickDown);
        }

        // Clear left/right pulse flags if up/down is concurrent.
        if ((cont->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) != 0)
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }
    }
}

void ControllerData_AnalogToDigital(s_ControllerData* cont, s32 arg1) // 0x80034670
{
    s32 val;
    s32 axisIdx;
    s32 processedInputFlags;
    s32 normalizedAnalogData;
    s32 xorShiftedRawAnalog;
    s32 btnsHeld;
    s32 signedRawAnalog;
    s32 negativeDirBitIdx;
    s32 positiveDirBitIdx;

    btnsHeld = cont->btnsHeld_C;

    if (arg1 != 0)
    {
        signedRawAnalog     = *(u32*)&cont->analogController_0.rightX ^ 0x80808080;
        xorShiftedRawAnalog = signedRawAnalog;

        for (normalizedAnalogData = 0, axisIdx = 3; axisIdx >= 0; axisIdx--)
        {
            normalizedAnalogData <<= 8;
            val                    = xorShiftedRawAnalog >> 24;
            xorShiftedRawAnalog  <<= 8;

            if (val < -0x40)
            {
                normalizedAnalogData |= (val + 0x40) & 0xFF;
                negativeDirBitIdx     = 23 - (axisIdx & 1);
                btnsHeld             |= 1 << (negativeDirBitIdx - (axisIdx * 2));
            }
            else if (val >= 0x40)
            {
                normalizedAnalogData |= (val - 0x3F) & 0xFF;
                positiveDirBitIdx     = ((axisIdx & 0x1) + 21);
                btnsHeld             |= 1 << (positiveDirBitIdx - ((axisIdx >> 1) * 4));
            }
        }

        cont->btnsHeld_C = btnsHeld;
    }
    else
    {
        signedRawAnalog      = 0;
        normalizedAnalogData = 0;
    }

    processedInputFlags      = normalizedAnalogData;
    cont->sticks_20.rawData_0 = signedRawAnalog;

    if (cont == g_Controller0)
    {
        if (!(processedInputFlags & 0xFF000000))
        {
            val = btnsHeld & 0x50;
            if (val == 0x40)
            {
                normalizedAnalogData = processedInputFlags | 0x2D000000;
            }
            else if (val == 0x10)
            {
                normalizedAnalogData = processedInputFlags | 0xD3000000;
            }
        }
        if (!(normalizedAnalogData & 0xFF0000))
        {
            val = btnsHeld & 0xA0;
            if (val == 0x20)
            {
                normalizedAnalogData |= 0x2D0000;
            }
            else if (val == 0x80)
            {
                normalizedAnalogData |= 0xD30000;
            }
        }
        if (!(processedInputFlags & 0xFF000000))
        {
            val = btnsHeld & 0x50;
            if (val == 0x40)
            {
                processedInputFlags |= 0x20000000;
            }
            else if (val == 0x10)
            {
                if (!(btnsHeld & g_GameWorkPtr->config_0.controllerConfig_0.run_C))
                {
                    processedInputFlags |= 0xE0000000;
                }
                else
                {
                    processedInputFlags |= 0xC0000000;
                }
            }
        }
        if (!(processedInputFlags & 0xFF0000))
        {
            val = btnsHeld & 0xA0;
            if (val == 0x20)
            {
                processedInputFlags |= 0x200000;
            }
            else if (val == 0x80)
            {
                processedInputFlags |= 0xE00000;
            }
        }
    }

    cont->field_24 = normalizedAnalogData;
    cont->field_28 = processedInputFlags;
}

// Unused.
bool func_8003483C(u16* arg0) // 0x8003483C
{
    if (g_Controller0->btnsClicked_10 & *(*arg0 + arg0))
    {
        *arg0 = *arg0 + 1;
    }
    else if (g_Controller0->btnsClicked_10 & (*(arg0 + 1)))
    {
        *arg0 = 2;
    }
    else if (g_Controller0->btnsClicked_10 & 0xFFFF)
    {
        *arg0 = 1;
    }

    if (*(*arg0 + arg0) == 0xFFFF)
    {
        *arg0 = 1;
        return true;
    }
    else
    {
        return false;
    }
}

void func_800348C0() // 0x800348C0
{
    bzero(&D_800A992C[1], 0x48);
}

void GameState_LoadScreen_Update() // 0x800348E8
{
    Gfx_LoadingScreenDraw();
    GameFs_MapStartup();

    if (g_SysWork.flags_22A4 & (1 << 10))
    {
        D_800BCDD4++;

        // Doesn't trigger audio.
        if ((D_800BCDD4 & 0xFF) >= 21)
        {
            g_SysWork.flags_22A4 &= ~(1 << 10);

            Sd_EngineCmd(Sfx_Unk1502);
            Sd_EngineCmd(Sfx_Unk1501);
        }
    }
}

static inline void Game_StateStepIncrement()
{
    s32 gameStateStep0 = g_GameWork.gameStateStep_598[0];

    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
    g_GameWork.gameStateStep_598[0] = gameStateStep0 + 1;
}

const char rodataPad_800251F4[] = { 0x00, 0x1C, 0x97, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Could this indicate file split nearby?

void GameFs_MapStartup() // 0x80034964
{
    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            g_IntervalVBlanks                  = 1;
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_RoomTransition)
            {
                AreaLoad_UpdatePlayerPosition();
                g_GameWork.gameStateStep_598[0] = 7;
            }
            else if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_BootDemo)
            {
                g_DemoLoadAttempCount           = 0;
                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20              = 1;
            }
            else
            {
                g_GameWork.gameStateStep_598[0] = 3;
            }

            Sd_EngineCmd(19);
            break;

        case 1:
            if (g_SysWork.timer_20 > 1200 && Fs_QueueGetLength() == 0 && !func_80045B28())
            {
                Demo_DemoFileSavegameUpdate();
                Game_PlayerInit();

                if (Demo_PlayFileBufferSetup() != 0)
                {
                    GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);

                    g_GameWork.gameStateStep_598[0] = 2;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
                }

                Demo_SequenceAdvance(1);
                Demo_DemoDataRead();

                g_DemoLoadAttempCount++;
                if (g_DemoLoadAttempCount >= 5)
                {
                    g_DemoLoadAttempCount = 0;
                    g_SysWork.timer_20    = 0;
                    break;
                }
            }
            break;

        case 2:
            if (Fs_QueueGetLength() == 0 && !func_80045B28())
            {
                Demo_PlayDataRead();

                g_GameWork.gameStateStep_598[0] = 3;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateStep_598[0] = 4;
            }
            break;

        case 4:
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
            {
                AreaLoad_UpdatePlayerPosition();
            }
            else if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_LoadSave ||
                     g_SysWork.processFlags_2298 == SysWorkProcessFlag_Continue)
            {
                g_SysWork.loadingScreenIdx_2281 = LoadingScreenId_PlayerRun;
            }

            g_GameWork.gameStateStep_598[0]++;
            break;
        
        case 5:
            func_80035338(1, g_MapOverlayHeader.charaGroupIds_248[0], NULL, 0);
            func_80035338(2, g_MapOverlayHeader.charaGroupIds_248[1], NULL, 0);
            func_80035338(3, g_MapOverlayHeader.charaGroupIds_248[2], NULL, 0);
            func_8003D21C(&g_MapOverlayHeader);

            g_GameWork.gameStateStep_598[0]++;

        case 6:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateStep_598[0]++;
            }
            break;

        case 7:
            if (func_80039F90() & SysWorkProcessFlag_RoomTransition)
            {
                // Maybe some sort of data handling. Calls another function related to texture handling.
                func_8003C30C();
            }

            func_8003C220(&g_MapOverlayHeader, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz);
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
            {
                func_80037188();
            }

            g_GameWork.gameStateStep_598[0]++;

        case 8:
            if (func_8003C850() != 0)
            {
                Game_StateStepIncrement();
            }
            break;

        case 9:
            if (func_80035780() == 0)
            {
                g_GameWork.gameState_594 = GameState_MainLoadScreen;
                Game_StateStepIncrement();
            }
            break;

        case 10:
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_BootDemo && !(g_SysWork.flags_22A4 & (1 << 1)))
            {
                Demo_Start();
                g_SysWork.flags_22A4 |= 1 << 1;
            }

            if (func_80039F90() & (1 << 2) || func_8003599C() == 0)
            {
                Game_StateStepIncrement();
            }
            break;

        case 11:
            if (g_SysWork.timer_1C >= 60)
            {
                if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_RoomTransition)
                {
                    func_80034F18();
                }
                else
                {
                    Game_InGameInit();
                }

                if (g_SysWork.processFlags_2298 <= (u32)SysWorkProcessFlag_OverlayTransition)
                {
                    func_80039F54();
                }

                func_8002E830();
                g_GameWork.gameStateStep_598[0]++;
            }
            break;

        case 12:
            if (!func_80045B28())
            {
                Game_StateSetNext(GameState_InGame);

                if (func_80039F90() & (1 << 1))
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_Gfx_ScreenFade                = (g_Gfx_ScreenFade & 8) | (1 << 2);
                }
            }
            break;

        default:
            break;
    }
}

void Gfx_LoadingScreenDraw() // 0x80034E58
{
    if (g_SysWork.loadingScreenIdx_2281 != LoadingScreenId_None && g_GameWork.gameStateStep_598[0] < 10)
    {
        g_Gfx_ScreenFade = 7;
        D_800B5C30       = FP_TIME(0.8f);
        g_MapOverlayHeader.loadingScreenFuncs_18[g_SysWork.loadingScreenIdx_2281]();
    }

    Gfx_MotionBlur(2);
}

void func_80034EC8() // 0x80034EC8
{
    s32 i;

    g_SysWork.field_228C = 0;
    g_SysWork.field_2290 = 0;

    bzero(g_SysWork.npcs_1A0, NPC_COUNT_MAX * sizeof(s_SubCharacter));

    for(i = 0; i < 4; i++)
    {
        g_SysWork.field_2284[i] = 0;
    }
}

void func_80034F18() // 0x80034F18
{
    vcSetCameraUseWarp(&g_SysWork.player_4C.chara_0.position_18, g_SysWork.cameraAngleY_237A);
    func_8005E70C();

    if (g_SysWork.field_234A != 0)
    {
        g_MapOverlayHeader.func_16C(g_SysWork.field_2349, 0x7F);
        g_MapOverlayHeader.func_168(NULL, g_SavegamePtr->mapOverlayId_A4, NULL);
    }

    func_80034EC8();
    func_80037F24(0);
    func_80037334();
}

void Game_InGameInit() // 0x80034FB8
{
    s32 mapOvlId;

    mapOvlId = g_SavegamePtr->mapOverlayId_A4;

    vcInitCamera(&g_MapOverlayHeader, &g_SysWork.player_4C.chara_0.position_18);

    vcSetCameraUseWarp(&g_SysWork.player_4C.chara_0.position_18, g_SysWork.cameraAngleY_237A);
    func_80040004(&g_MapOverlayHeader);
    func_80035B58(0);
    func_8003D95C();
    func_8003EBA0();

    g_MapOverlayHeader.func_168(NULL, (void*)mapOvlId, (void*)NO_VALUE);

    func_80034EC8();

    g_SysWork.field_2280 = 5;

    func_8005E650(mapOvlId);
    func_80037124();
    func_8007E8C0();
    func_80037F24(0);
    func_80037334();
    func_8003569C();
    func_8007EBBC();
    GameFs_Tim00TIMLoad();
    Fs_QueueWaitForEmpty();
    GameFs_MapItemsModelLoad(mapOvlId);
}

void Game_SavegameInitialize(s8 overlayId, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* var;

    bzero(g_SavegamePtr, sizeof(s_Savegame));

    g_SavegamePtr->mapOverlayId_A4 = overlayId;

    difficulty = CLAMP(difficulty, GameDifficulty_Easy, GameDifficulty_Hard);

    var = g_SavegamePtr->field_B0;

    g_SavegamePtr->gameDifficulty_260 = difficulty;
    g_SavegamePtr->current2dMapIdx_A9 = 1;

    for (i = 0; i < 45; i++)
    {
        var[44] = NO_VALUE;
        var--;
    }

    Game_SavegameResetPlayer();
}

void Game_PlayerInit() // 0x80035178
{
    func_8003C048();
    func_8003C110();
    func_8003C0C0();
    func_800445A4(FS_BUFFER_0, g_SysWork.playerBoneCoords_890); // Load player anim file?
    func_8003D938();

    g_SysWork.field_229C = NO_VALUE;

    if ((g_SavegamePtr->flags_AC >> 1) & (1 << 0))
    {
        Game_TurnFlashlightOff();
    }
    else
    {
        Game_TurnFlashlightOn();
    }

    D_800A992C->animFileSize2_10 = 0x2E630;
    D_800A992C->animFileSize1_C  = 0x2E630;
    func_8007E5AC();
}

void GameFs_MapLoad(s32 mapIdx) // 0x8003521C
{
    #define BASE_FILE_IDX FILE_VIN_MAP0_S00_BIN
    #define UNK_FLAGS     ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5))

    Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, g_OvlDynamic);
    func_8005E0DC(mapIdx);
    GameFs_PlayerMapAnimLoad(mapIdx);

    if (g_SysWork.processFlags_2298 & UNK_FLAGS)
    {
        func_8003CD6C(&g_SysWork.playerCombatInfo_38);
    }

    func_800546A8((u8)g_SysWork.playerCombatInfo_38.equippedWeapon_F);
}

// ========================================
// ANIMATION MEMORY ALLOC?
// ========================================

bool func_8003528C(s32 idx0, s32 idx1) // 0x8003528C
{
    u32         tempField_8;
    u32         tempField_4;
    s_800A992C* ptr0;
    s_800A992C* ptr1;

    ptr0        = &D_800A992C[idx0];
    ptr1        = &D_800A992C[idx1];
    tempField_4 = ptr0->animFile0_4;
    tempField_8 = ptr1->animFile1_8;

    if (tempField_4 >= (tempField_8 + ptr1->animFileSize2_10) ||
        tempField_8 >= (tempField_4 + ptr0->animFileSize1_C))
    {
        return false;
    }

    return true;
}

s32 func_800352F8(s32 charaId) // 0x800352F8
{
    s32         i;
    s_800A992C* ptr;

    for (i = 1; i < 4; i++)
    {
        if (D_800A992C[i].charaId1_1 == charaId)
        {
            return i;
        }
    }

    return 0;
}

void func_80035338(s32 idx, e_CharacterId charaId, s_AnimFile* animFile, GsCOORDINATE2* coord) // 0x80035338
{
    s32         i;
    s_AnimFile* animFileCpy;
    s_800A992C* ptr;
    s_800A992C* playerAnim;

    animFileCpy = animFile;
    ptr         = &D_800A992C[idx];

    if (charaId == Chara_None)
    {
        return;
    }

    for (playerAnim = &ptr[-1]; animFileCpy == NULL; playerAnim--)
    {
        animFileCpy = playerAnim->animFile0_4 + playerAnim->animFileSize1_C;
    }

    if (ptr->charaId1_1 == charaId)
    {
        if (idx == 1 || animFileCpy == ptr->animFile1_8)
        {
            func_80035560(idx, charaId, ptr->animFile1_8, coord);
            return;
        }
        else if (animFileCpy < ptr->animFile1_8)
        {
            ptr->animFile0_4 = animFileCpy;

            Mem_Move32(animFileCpy, D_800A992C[idx].animFile1_8, D_800A992C[idx].animFileSize2_10);
            func_80035560(idx, charaId, animFileCpy, coord);
            return;
        }
    }

    ptr->npcCoords_14     = &g_SysWork.npcCoords_FC0[0];
    ptr->charaId1_1       = Chara_None;
    ptr->animFile1_8      = NULL;
    ptr->animFileSize2_10 = 0;
    ptr->charaId0_0       = charaId;
    ptr->animFile0_4      = animFileCpy;
    ptr->animFileSize1_C  = Fs_GetFileSectorAlignedSize(g_Chara_FileInfo[charaId].animFileIdx);

    i = func_800352F8(charaId);

    if (i > 0)
    {
        Mem_Move32(D_800A992C[idx].animFile0_4, D_800A992C[i].animFile1_8, D_800A992C[i].animFileSize2_10);
        func_80035560(idx, charaId, ptr->animFile0_4, coord);
    }
    else
    {
        Fs_QueueStartReadAnm(idx, charaId, animFileCpy, coord);
    }

    for (i = 1; i < 4; i++)
    {
        if (i != idx && D_800A992C[i].charaId1_1 != Chara_None && func_8003528C(idx, i) != 0)
        {
            bzero(&D_800A992C[i], sizeof(s_800A992C));
        }
    }
}

void func_80035560(s32 idx, e_CharacterId charaId, s_AnimFile* animFile, GsCOORDINATE2* coord) // 0x80035560
{
    s32            idx0;
    GsCOORDINATE2* coordCpy;
    s_800A992C*    ptr;

    coordCpy = coord;
    ptr      = &D_800A992C[idx];

    if (coordCpy == 0)
    {
        if (idx == 1)
        {
            coordCpy = &g_SysWork.npcCoords_FC0[0];
        }
        else if (idx >= 2)
        {
            idx0      = D_800A992C[idx - 1].animFile1_8->field_6;
            coordCpy  = D_800A992C[idx - 1].npcCoords_14;
            coordCpy += idx0 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&coordCpy[animFile->field_6] + 1) >= (u32)&g_SysWork.field_2280)
            {
                coordCpy = g_MapOverlayHeader.field_28;
            }
        }
    }

    ptr->charaId1_1       = charaId;
    ptr->animFile1_8      = animFile;
    ptr->animFileSize2_10 = Fs_GetFileSectorAlignedSize(g_Chara_FileInfo[charaId].animFileIdx);
    ptr->npcCoords_14     = coordCpy;

    func_800445A4(animFile, coordCpy);

    D_800A98FC[charaId] = idx;
}

void func_8003569C() // 0x8003569C
{
    s32            i;
    GsCOORDINATE2* coord;
    s_AnimFile*    animFile;

    for (i = 1; i < 3; i++)
    {
        if ((s8)g_MapOverlayHeader.charaGroupIds_248[i] != 0)
        {
            coord    = D_800A992C[i].npcCoords_14;
            animFile = D_800A992C[i + 1].animFile1_8;
            coord   += D_800A992C[i].animFile1_8->field_6 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&coord[animFile->field_6] + 1) >= &g_SysWork.field_2280)
            {
                coord = g_MapOverlayHeader.field_28;
            }

            D_800A992C[i + 1].npcCoords_14 = coord;
            func_800445A4(animFile, coord);
        }
    }
}

// ========================================
// AUDIO HANDLING?
// ========================================

s32 func_80035780() // 0x80035780
{
    if (func_80045B28())
    {
        return NO_VALUE;
    }

    if (Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            func_8003596C();
            g_GameWork.gameStateStep_598[1]++;

        case 1:
            if (func_800358A8(g_MapOverlayHeader.field_14) == 0)
            {
                g_GameWork.gameStateStep_598[1] += 2;
            }
            else
            {
                Sd_EngineCmd(18);
                func_80035E1C();
        
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case 2:
            if (!func_80045BC8())
            {
                func_800358DC(g_MapOverlayHeader.field_14);
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        default:
            return 0;
    }

    return 1;
}

bool func_800358A8(s32 cmd) // 0x800358A8
{
    if (cmd == 0)
    {
        return false;
    }

    if (cmd == 1)
    {
        return false;
    }

    return g_GameWork.soundCmd_5B2 != cmd;
}

void func_800358DC(s32 cmd) // 0x800358DC
{
    if (cmd == 0)
    {
        return;
    }

    if (cmd == 1)
    {
        return;
    }

    g_GameWork.soundCmd_5B2 = cmd;
    Sd_EngineCmd(g_UnknownEngineCmdTable0[cmd]);
}

void func_80035924() // 0x80035924
{
    s8 cmd;

    cmd = g_GameWork.soundCmd_5B2;
    if (cmd == 0 || g_GameWork.soundCmd_5B2 == 1)
    {
        return;
    }

    Sd_EngineCmd(g_UnknownEngineCmdTable1[cmd]);
}

void func_8003596C() // 0x8003596C
{
    if (g_MapOverlayHeader.field_14 == 1)
    {
        func_80035DB4(1);
    }
}

s32 func_8003599C() // 0x8003599C
{
    if (func_80045B28() || Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S00)
            {
                if ((g_SavegamePtr->eventFlags_168[4] & (1 << 5)) || (g_SavegamePtr->eventFlags_168[5] & (1 << 21)))
                {
                    g_MapOverlayHeader.field_15 = 11;
                }
                else
                {
                    g_MapOverlayHeader.field_15 = 4;
                }
            }

            if (func_80035AB0((s8)g_MapOverlayHeader.field_15) != 0)
            {
                Sd_EngineCmd(17);
                g_GameWork.gameStateStep_598[1]++;
                return 1;
            }
            break;
            
        case 1:
            func_80035AC8((s8)g_MapOverlayHeader.field_15);
            g_GameWork.gameStateStep_598[1]++;
            return 1;

        default:
           break;
    }

    return 0;
}

s32 func_80035AB0(s32 arg0) // 0x80035AB0
{
    return g_GameWork.field_5B3 != arg0;
}

void func_80035AC8(s32 idx) // 0x80035AC8
{
    g_GameWork.field_5B3 = idx;
    Sd_EngineCmd(g_UnknownEngineCmdTable2[idx]);
}

// ========================================
// LOADING SCREEN RELATED?
// ========================================

void func_80035B04(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord) // 0x80035B04
{
    coord->flg = 0;

    coord->coord.t[0] = FP_FROM(pos->vx, Q4_SHIFT);
    coord->coord.t[1] = FP_FROM(pos->vy, Q4_SHIFT);
    coord->coord.t[2] = FP_FROM(pos->vz, Q4_SHIFT);

    func_80096E78(rot, (MATRIX*)&coord->coord);
}

void func_80035B58(s32 arg0) // 0x80035B58
{
    func_8003EBF4(&g_MapOverlayHeader);
    g_MapOverlayHeader.func_16C(g_MapOverlayHeader.field_17, g_MapOverlayHeader.field_16);
}

void func_80035B98() // 0x80035B98
{
    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}

void Gfx_LoadingScreen_BackgroundTexture() // 0x80035BBC
{
    Gfx_BackgroundSpriteDraw(&D_800A9034);
}

void Gfx_LoadingScreen_PlayerRun() // 0x80035BE0
{
    GsCOORDINATE2* boneCoords;
    VECTOR3        camLookAt;
    s_Model*       model;
    s32            temp;

    boneCoords = g_SysWork.playerBoneCoords_890;
    model      = &g_SysWork.player_4C.chara_0.model_0;

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
        {
            AreaLoad_UpdatePlayerPosition();
        }

        vcInitCamera(&g_MapOverlayHeader, &g_SysWork.player_4C.chara_0.position_18);
        func_80040004(&g_MapOverlayHeader);

        camLookAt.vy = FP_METER(-0.6f);
        camLookAt.vx = g_SysWork.player_4C.chara_0.position_18.vx;
        camLookAt.vz = g_SysWork.player_4C.chara_0.position_18.vz;

        vcUserWatchTarget(&camLookAt, NULL, true);

        camLookAt.vx -= Math_Sin(g_SysWork.player_4C.chara_0.rotation_24.vy - FP_ANGLE(22.5f)) * 2;
        temp          = Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy - FP_ANGLE(22.5f));
        camLookAt.vy  = FP_METER(-1.0f);
        camLookAt.vz -= temp * 2;

        vcUserCamTarget(&camLookAt, NULL, true);
        func_8003EB54();
        func_8003EEDC(0, 0);

        model->anim_4.flags_2                     |= AnimFlag_Visible;
        g_SysWork.player_4C.extra_128.field_18     = 0;
        model->anim_4.flags_2                     |= AnimFlag_Unk1 | AnimFlag_Visible;
        model->anim_4.time_4                       = FP_TIME(26.0f);
        g_SysWork.player_4C.chara_0.position_18.vy = FP_METER(0.2f);

        /*D_800A9990*/ D_800A998C.field_4 = model->anim_4.animIdx_0;

        func_80035B04(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, boneCoords);
        g_SysWork.sysState_8++;
    }

    Anim_Update1(model, (s_Skeleton*)FS_BUFFER_0, boneCoords, &D_800A998C);
    vcMoveAndSetCamera(1, 0, 0, 0, 0, 0, 0, 0);
    func_8003F170();
    func_8003DA9C(1, boneCoords, 1, g_SysWork.player_4C.chara_0.timer_C6, 0);
}

// ========================================
// UNKNOWN
// ========================================

void func_80035DB4(s32 arg0) // 0x80035DB4
{
    D_800BCD5C = 0;

    if (g_MapOverlayHeader.func_10)
    {
        g_MapOverlayHeader.func_10(arg0);
        if (arg0 == 0 && D_800BCD5C == 0)
        {
            func_80035F4C(1, 0xF0000, 0);
        }
    }
}

void func_80035E1C() // 0x80035E1C
{
    s32 i;

    for (i = 0; i < 9; i++)
    {
        g_SysWork.field_2748[i] = 0;
    }
}

bool func_80035E44()
{
    s32 i;
    u16 val;
    
    for (i = 0; i < 8; i++)
    {
        if (g_SysWork.field_2748[i] != 0) 
        {
            return false;
        }
    }

    val = func_80045BC8();
    if (val == 0) 
    {
        return true;
    }
    else if (val == 0xFFFF) 
    {
        return false;
    }

    for (i = 1; i < 8; i++) 
    {
        if (func_80046BB4(i))
        {
            return false;
        }
    }

    return true;
}

void func_80035ED0() // 0x80035ED0
{
    s32 i;

    for (i = 1; i < 8; i++)
    {
        g_SysWork.field_2748[i] = func_80046BB4(i) << 5;
    }

    if (!func_80045BC8())
    {
        g_SysWork.field_2748[0] = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    }

    g_SysWork.field_2748[8] = 0;
}

void func_80035F4C(s32 arg0, s32 arg1, u8* arg2) // 0x80035F4C
{
    s16  temp_v0;
    s32  var_a0;
    s32  var_a2;
    s32  var_a3;
    s32  var_v1;
    s32  temp_s2;
    s32  i;
    s32  var_s1;
    s32  var_s3;
    s32  var_s4;
    s32  var_t0;
    s32  var_v0_2;
    s32  temp_s7;
    s16* ptr;
    u8*  var_t4;

    var_s1 = arg0;
    var_t4 = arg2;
    ptr    = g_SysWork.field_2748;

    if (var_t4 == NULL)
    {
        var_t4 = D_800A99A4;
    }

    if (g_SysWork.player_4C.chara_0.health_B0 <= 0 || g_SysWork.sysState_8 == SysState_GameOver)
    {
        var_s1 &= 1 << 8;
        var_s1 |= 1 << 0;
        arg1    = 0x333;
    }
    
    if ((var_s1 & (1 << 8)) == 0)
    {
        if (D_800A9A1C > 0 && g_SavegamePtr->flags_AC & (1 << 0))
        {
            g_SysWork.field_22A0 |= 1 << 2;
        }
    }

    if (g_SysWork.field_22A0 & (1 << 7))
    {
        var_s1                = (1 << 0) | (1 << 9);
        g_SysWork.field_22A0 |= 1 << 1;
    }

    if (var_s1 & (1 << 0))
    {
        var_s1 &= (1 << 8) | (1 << 9);
    }
    else
    {
        var_s1 ^= 1 << 0;
    }

    for (i = 0, temp_s7 = 8; i < 9; i++)
    {
        var_a3 = ptr[i];

        if (i == temp_s7) 
        {
            var_t0 = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime1, 0.25f, Q12_SHIFT);
            if (g_SysWork.field_22A0 & (1 << 1)) 
            {
                var_a0 = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            } 
            else if (g_SysWork.field_22A0 & (1 << 2)) 
            {
                var_a0 = FP_FLOAT_TO(0.75f, Q12_SHIFT);
            } 
            else 
            {
                var_a0 = (g_SysWork.field_22A0 << 8) & 0x800;
            }
        } 
        else 
        {
            if ((var_s1 >> i) & (1 << 0)) 
            {
                var_t0 = FP_MULTIPLY(g_DeltaTime1, arg1, Q12_SHIFT - 1); // Should be multiplied by 2 but doesn't match.
                var_a0 = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            } 
            else 
            {
                var_t0 = FP_MULTIPLY(g_DeltaTime1, arg1, Q12_SHIFT);
                var_a0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            }
        }

        var_a2 = var_a0 - var_a3;

        if (var_a3 != var_a0) 
        {
            if (var_t0 < var_a2) 
            {
                var_a3 += var_t0;
            } 
            else if (var_a2 >= -var_t0) 
            {
                var_a3 = var_a0;
            }
            else
            {
                var_a3 -= var_t0;
            }
        }

        ptr[i] = var_a3;
    }

    var_s3  = 0;
    temp_v0 = FP_FLOAT_TO(1.0f, Q12_SHIFT) - ptr[8];

    for (i = 0; i < 8; i++)
    {
        var_v1  = ptr[i];
        var_s3 |= var_v1 != 0;

        if (i == 0) 
        {
            var_v1 = FP_MULTIPLY_PRECISE(var_v1, temp_v0, Q12_SHIFT);
        }

        var_v1 = FP_MULTIPLY_PRECISE(var_v1, 0x7F, Q12_SHIFT);
        if (var_v1 >= 0x80) 
        {
            var_v1 = 0x7F;
        }

        var_v1 = (var_v1 * var_t4[i]) >> 7;
        if (var_v1 >= 0x80) 
        {
            var_v1 = 0x7F;
        }

        D_800BCD50[i] = var_v1;
    }

    var_s4  = 0;
    temp_s2 = func_80045BC8();

    var_v0_2 = temp_s2;
    var_v0_2 = temp_s2 != 0 && var_v0_2 != 0xFFFF;

    if (var_s3 != 0) 
    {
        switch (D_800A99A0) 
        {
            case 3:
                func_80035E1C();

                if (var_v0_2 != 0) 
                {
                    D_800A99A0 = 0;
                } 
                else 
                {
                    func_80035924();
                    D_800A99A0 = 2;
                }
                break;

            case 2:
                func_80035E1C();
                D_800A99A0 = 1;
                break;

            case 1:
                if (var_v0_2 != 0) 
                {
                    func_80035ED0();
                } 
                else 
                {
                    func_80035E1C();
                }

                D_800A99A0 = 0;
                break;

            case 0:
                var_s4 = 1;
                break;
        }
    } 
    else if (var_s1 & (1 << 9)) 
    {
        if (D_800A99A0 != 3) 
        {
            D_800A99A0 = 3;
            Sd_EngineCmd(18);
        }
    } 
    else if (D_800A99A0 == 0) 
    {
        var_s4 = 1;
    }

    if (var_s4 != 0) 
    {
        if (var_v0_2 != 0) 
        {
            for (i = 0; i < 8; i++)
            {
                func_80046C54(i, D_800BCD50[i]);
            }
        } 
        else 
        {
            func_80035E1C();
            D_800A99A0 = 3;
        }
    }

    D_800BCD5C = 1;
}

void func_800363D0() // 0x800363D0
{
    D_800A9A1C            = 0;
    g_SysWork.field_22A0 |= 1 << 3;
    func_80035DB4(0);
}

void func_8003640C(s32 arg0) // 0x8003640C
{
    if (arg0 != 0)
    {
        g_MapOverlayHeader.field_14 = arg0;
    }
}

void Savegame_MapRoomIdxSet() // 0x80036420
{
    s32 x;
    s32 z;
    s8  newMapRoomIdx;

    x = g_SysWork.player_4C.chara_0.position_18.vx;
    z = g_SysWork.player_4C.chara_0.position_18.vz;

    // Set map room index based on current player position.
    if (g_MapOverlayHeader.getMapRoomIdxFunc_4 == NULL)
    {
        newMapRoomIdx = 0;
    } 
    else 
    {
        newMapRoomIdx = g_MapOverlayHeader.getMapRoomIdxFunc_4(x, z);
    }
    g_SavegamePtr->mapRoomIdx_A5 = newMapRoomIdx;
}

s32 func_8003647C() // 0x8003647C
{
    return g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8;
}

s32 func_80036498() // 80036498
{
    return !(g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8);
}

u32 func_800364BC() // 0x800364BC
{
    u32 var0;
    u32 var1;

    D_800BCD58 += g_DeltaTime1 * 0x40001;

    var0  = 0x40000;
    var0 += Math_Sin(D_800BCD58 >> 18) * 8;
    var1  = Math_Sin((D_800BCD58 & 0xFFFF) / 16) * 32;
    return FP_FROM(var0 + var1, Q12_SHIFT);
}

// `RECT`s?
const char rodataPad_80025234[] = { 0, 177, 58, 204, 0, 0, 0, 0 }; // Could this indicate file split nearby?

void func_8003652C() // 0x8003652C
{
    RECT rect;

    u32 vals[] = // 0x8002523C
    {
        0xFFFF0000, 0xBBEEE318, 0xFFEC9304, 0x83FFE30C,
        0x001F8318, 0x90840018, 0x90808080, 0x80048084
    };

    rect.x = 304;
    rect.y = 510;
    rect.w = 16;
    rect.h = 1;

    LoadImage(&rect, vals);
}

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx) // 0x800365B8
{
    #define MSG_TIMER_MAX   (FP_TIME(524288.0f) - 1)
    #define FINISH_CUTSCENE 0xFF
    #define FINISH_MAP_MSG  0xFF

    s32  temp_s1;
    s32  temp_v0;
    s32  temp_v1;
    s32  temp_v1_2;
    s32  var_a0;
    s32  var_a1;
    bool hasInput;
    s32  res;
    s32  var_v1;
    u16  var_a0_2;
    u32* new_var;
    s32  temp;

    // Check for user input.
    hasInput = false;
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
        (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        hasInput = true;
    }

    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
    func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, EquippedWeaponId_RockDrill);

    if (g_MapMsg_MainIdx != mapMsgIdx)
    {
        g_SysWork.field_18 = 0;
    }

    switch (g_SysWork.field_18)
    {
        case 0:
            g_SysWork.mapMsgTimer_234C         = NO_VALUE;
            g_MapMsg_Select.maxIdx_0           = NO_VALUE;
            g_MapMsg_Select.selectedEntryIdx_1 = 0;
            g_MapMsg_AudioLoadBlock            = 0;
            g_MapMsg_CurrentIdx                = mapMsgIdx;
            g_MapMsg_StateMachineIdx1          = 0;
            g_MapMsg_StateMachineIdx2          = 0;
            g_MapMsg_MainIdx                   = mapMsgIdx;
            g_MapMsg_DisplayLength             = 0;
            g_MapMsg_DisplayInc                = 2; // Advance 2 glyphs at a time.

            func_8004B684();
            Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

            D_800BCD74 = 1;
            g_SysWork.field_18++;
            return MapMsgState_Finish;

        case 1:
            if (g_SysWork.field_22A0 & (1 << 5))
            {
                if (func_80045B28() == 4)
                {
                    D_800BCD74 = 0;
                    break;
                }

                if (D_800BCD74 != 0)
                {
                    break;
                }
            }
            else
            {
                D_800BCD74 = 0;
            }

            Gfx_StringSetColor(ColorId_White);
            Gfx_StringSetPosition(40, 160);

            g_MapMsg_DisplayLength += g_MapMsg_DisplayInc;
            g_MapMsg_DisplayLength  = CLAMP(g_MapMsg_DisplayLength, 0, MAP_MESSAGE_DISPLAY_ALL_LENGTH);

            if (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C > 0)
            {
                g_SysWork.mapMsgTimer_234C -= g_DeltaTime1;
                g_SysWork.mapMsgTimer_234C  = CLAMP(g_SysWork.mapMsgTimer_234C, FP_TIME(0.0f), MSG_TIMER_MAX);
            }

            temp_s1 = g_MapMsg_StateMachineIdx1;
            if (temp_s1 == NO_VALUE)
            {
                if (g_MapMsg_AudioLoadBlock == 0)
                {
                    Game_TimerUpdate();
                }

                temp = g_MapMsg_StateMachineIdx2;
                if (temp == temp_s1)
                {
                    if (g_MapMsg_Select.maxIdx_0 == temp)
                    {
                        if (!((g_MapMsg_AudioLoadBlock & (1 << 0)) || !hasInput) || 
                            (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                        {
                            g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;

                            if (g_SysWork.field_22A0 & (1 << 5))
                            {
                                Sd_EngineCmd(19);
                            }
                            break;
                        }
                    } 
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                    {
                        g_MapMsg_Select.maxIdx_0           = temp;
                        g_MapMsg_Select.selectedEntryIdx_1 = g_MapMsg_SelectCancelIdx3;

                        Sd_PlaySfx(Sfx_Cancel, 0, 64);

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                    {
                        g_MapMsg_Select.maxIdx_0 = temp;

                        if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == (s8)g_MapMsg_SelectCancelIdx3)
                        {
                            Sd_PlaySfx(Sfx_Cancel, 0, 64);
                        }
                        else if (!g_SysWork.silentYesSelection_2350_4)
                        {
                            Sd_PlaySfx(Sfx_Confirm, 0, 64);
                        }

                        // Exit 480i mode (used by map screen).
                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                }
                else if ((!(g_MapMsg_AudioLoadBlock & (1 << 0)) && hasInput && g_MapMsg_Select.maxIdx_0 != 0) ||
                         (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                {
                    if (g_MapMsg_Select.maxIdx_0 != NO_VALUE)
                    {
                        g_MapMsg_Select.maxIdx_0  = NO_VALUE;
                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }

                    g_MapMsg_CurrentIdx++;
                    g_SysWork.mapMsgTimer_234C = g_MapMsg_Select.maxIdx_0;

                    Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

                    g_MapMsg_DisplayLength    = 0;
                    g_MapMsg_StateMachineIdx1 = 0;

                    if (g_MapMsg_AudioLoadBlock == MapMsgAudioLoadBlock_J2)
                    {
                        D_800BCD74 = 0;
                        return MapMsgState_Idle;
                    }

                    if (g_SysWork.field_22A0 & (1 << 5))
                    {
                        Sd_EngineCmd(19);
                    }

                    D_800BCD74 = 1;
                    return MapMsgState_Finish;
                }
            }
            else
            {
                if (hasInput)
                {
                    g_MapMsg_DisplayLength = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
                }
            }

            g_MapMsg_StateMachineIdx1 = 0;
            g_MapMsg_StateMachineIdx2 = Gfx_MapMsg_SelectionUpdate(g_MapMsg_CurrentIdx, &g_MapMsg_DisplayLength);

            if (g_MapMsg_StateMachineIdx2 != 0 && g_MapMsg_StateMachineIdx2 < MapMsgCode_Select4)
            {
                g_MapMsg_StateMachineIdx1 = NO_VALUE;
            }
    }

    if (g_MapMsg_StateMachineIdx2 != FINISH_MAP_MSG)
    {
        return MapMsgState_Idle;;
    }

    g_SysWork.field_18                   = 0;
    g_SysWork.enableHighResGlyphs_2350_0 = false;
    g_MapMsg_DisplayLength               = 0;

    if (g_SysWork.field_22A0 & (1 << 5))
    {
        D_800BCD74 = 1;
    }

    return g_MapMsg_Select.selectedEntryIdx_1 + 1;
}

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1) // 0x80036B5C
{
    #define STRING_LINE_OFFSET 16

    s32 i;
    s32 posY;
    s32 mapMsgCode;
    s16 temp;
    s8* str;

    mapMsgCode = Gfx_MapMsg_StringDraw(g_MapOverlayHeader.mapMessageStrings_30[mapMsgIdx], *arg1);

    g_MapMsg_SelectFlashTimer += g_DeltaTime1;
    if (g_MapMsg_SelectFlashTimer >= FP_TIME(0.5f))
    {
        g_MapMsg_SelectFlashTimer -= FP_TIME(0.5f);
    }

    switch (mapMsgCode)
    {
        case NO_VALUE:
        case MapMsgCode_None:
            g_MapMsg_SelectFlashTimer = FP_TIME(0.0f);
            break;

        case MapMsgCode_Select2:
        case MapMsgCode_Select3:
        case MapMsgCode_Select4:
            g_MapMsg_Select.maxIdx_0  = 1;
            g_MapMsg_SelectCancelIdx3 = (mapMsgCode == 3) ? 2 : 1;

            if (mapMsgCode == MapMsgCode_Select4)
            {
                // Shows selection prompt with map messages at indices 0 and 1.
                // All maps have "Yes" and "No" as messages 0 and 1, respectively.
                for (i = 0; i < 2; i++)
                {
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(ColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 98);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessageStrings_30[i], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
                }

                mapMsgCode = 2;
            }
            else
            {
                // Shows selection prompt with 2 or 3 map messages from current index + 1/2/3.
                // Requires prompt options to be arranged sequentially in the map message array, e.g.
                // `[idx]`:     "Select one of 3 options. ~S3"
                // `[idx + 1]`: "Option 1"
                // `[idx + 2]`: "Option 2"
                // `[idx + 3]`: "Option 3"
                for (i = 0; i < mapMsgCode; i++)
                {
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(ColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 96);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessageStrings_30[(mapMsgIdx + i) + 1], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != 0)
            {
                g_MapMsg_SelectFlashTimer = FP_TIME(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1--;

                Sd_PlaySfx(Sfx_Back, 0, 64);
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != (mapMsgCode - 1))
            {
                g_MapMsg_SelectFlashTimer = FP_TIME(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1++;

                Sd_PlaySfx(Sfx_Back, 0, 64);
            }

            mapMsgCode = NO_VALUE;
            break;

        case MapMsgCode_DisplayAll:
            *arg1 = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
            break;
    }

    return mapMsgCode;
}

const s32 RodataPad_800252B8 = 0;

/** @brief SFX pairs.
 * 
 * @note Used when loading areas. Maybe facilitates things like the
 * opening and closing door SFX when the player moves between rooms. */
s_AreaLoadSfx const SfxPairs[25] = // 0x800252BC
{
    { Sfx_Base,    Sfx_Base },
    { Sfx_Unk1309, Sfx_Unk1310 },
    { Sfx_Unk1323, Sfx_Unk1324 },
    { Sfx_Unk1418, Sfx_Base },
    { Sfx_Unk1354, Sfx_Base },
    { Sfx_Unk1387, Sfx_Base },
    { Sfx_Unk1391, Sfx_Base },
    { Sfx_Unk1521, Sfx_Base },
    { Sfx_Unk1458, Sfx_Unk1459 },
    { Sfx_Unk1604, Sfx_Unk1605 },
    { Sfx_Unk1609, Sfx_Unk1610 },
    { Sfx_Unk1396, Sfx_Unk1397 },
    { Sfx_Unk1336, Sfx_Unk1337 },
    { Sfx_Unk1338, Sfx_Unk1339 },
    { Sfx_Unk1340, Sfx_Unk1341 },
    { Sfx_Unk1601, Sfx_Unk1602 },
    { Sfx_Unk1490, Sfx_Unk1491 },
    { Sfx_Unk1431, Sfx_Unk1432 },
    { Sfx_Unk1398, Sfx_Unk1399 },
    { Sfx_Unk1504, Sfx_Unk1505 },
    { Sfx_Unk1309, Sfx_Base },
    { Sfx_Unk1323, Sfx_Base },
    { Sfx_Base,    Sfx_Unk1324 },
    { Sfx_Unk1351, Sfx_Unk1352 },
    { Sfx_Unk1487, Sfx_Base }
};

// These are referenced by pointers at `0x800A99E8`, which are then used by `func_800D3EAC`.
// Maybe meant to be separate .c file with .h externs.
const char g_80025320[] = "SHOT_NEA";
const char g_8002532C[] = "SHELL_NE";
const char g_80025338[] = "BULLET_N";
const char g_80025344[] = "AMPULE_N";
const char g_80025350[] = "DRINK_NE";
const char g_8002535C[] = "AIDKIT_N";
const char g_80025368[] = "PAD_NEAR";

void func_80036E48(u16* arg0, s16* arg1) // 0x80036E48
{
    u16  sp10[4];
    u8   sp18[16];
    u8   sp28[12];
    s32  temp_a0;
    s32  temp_v0_2;
    s32  var_a2;
    s32  var_t3;
    u8   var_t4;
    s32  var_v0;
    u16  temp_v0;
    u16  var_a3;
    s16* var_t2;
    u16* var_t7;

    var_t2 = arg1;
    var_t4 = 0;
    var_t7 = arg0;

    for (var_t3 = 0; var_t3 < 15;)
    {
        temp_v0 = *var_t7;

        for (var_a2 = 0; var_a2 < 15; var_a2++)
        {
            if ((((temp_v0 >> 8) | ((temp_v0 & 0xFF) << 8)) >> (0xF - var_a2)) & 1)
            {
                sp18[var_a2] = 1;
            }
            else
            {
                sp18[var_a2] = 0;
            }
        }

        sp18[15] = 0;
        sp28[0]  = sp18[0];
        sp28[1]  = sp18[1] | sp18[2];
        sp28[2]  = sp18[3];
        sp28[3]  = sp18[4];
        sp28[4]  = sp18[5] | sp18[6];
        sp28[5]  = sp18[7];
        sp28[6]  = sp18[8] | sp18[9];
        sp28[7]  = sp18[10];
        sp28[8]  = sp18[11];
        sp28[9]  = sp18[12] | sp18[13];
        var_v0   = 2;
        sp28[10] = sp18[14];
        sp28[11] = 0;

        for (var_a3 = 0, var_a2 = 0; var_a2 < 12; var_a2++)
        {
            var_v0  = 2;
            temp_a0 = (var_a2 & 0x3) * 4;

            if (sp28[var_a2] != 0)
            {
                var_a3 |= var_v0 << temp_a0;
            }
            else
            {
                if (var_a2 > 0 && sp28[var_a2 - 1] != 0)
                {
                    var_a3 |= 0xB << temp_a0;
                }

                if (var_t3 > 0)
                {
                    if (var_a2 != 0 && ((sp10[var_a2 >> 2] >> temp_a0) & 0xF) == 0xB && (var_t4 & 0xFF))
                    {
                        var_a3 |= 0xB << temp_a0;
                    }

                    temp_v0_2 = (sp10[var_a2 >> 2] >> temp_a0) & 0xF;

                    if (temp_v0_2 > 0 && temp_v0_2 != 0xB)
                    {
                        var_a3 |= 0xB << temp_a0;
                        var_t4 = 1;
                    }
                    else
                    {
                        var_t4 = 0;
                    }
                }
            }

            if ((var_a2 & 3) == 3)
            {
                sp10[var_a2 >> 2] = var_a3;
                *var_t2           = var_a3;
                var_t2++;
                var_a3 = 0;
            }
        }

        do { var_t3++; } while (0); // HACK: Required for match.
        var_t7++;
        var_t2 += (D_800C3920 - 1) * 3;
    }

    func_8003708C(var_t2, sp10);
}

void func_8003708C(s16* ptr0, u16* ptr1) // 0x8003708C
{
    s32 var0;
    s16 var1;
    s32 var3;
    s32 shift;
    s32 i;

    var0 = 0;
    var1 = 0;

    for (i = 0; i < 12; i++)
    {
        shift = (i & 3) * 4;
        var3  = (*ptr1 >> shift) & 0xF;
        if (i != 0 && var3 == 11 && var0 != 0)
        {
            var1 |= 11 << shift;
        }

        var0 = 0;
        if (var3 != 0 && var3 != 11)
        {
            var1 |= 11 << shift;
            var0  = 1;
        }

        if ((i & 3) == 3 || i == 12)
        {
            ptr1++;
            *ptr0++ = var1;
            var1    = 0;
        }
    } 
}

void func_80037124() // 0x80037124
{
    g_MapMsg_Select.maxIdx_0 = NO_VALUE;
    func_8003652C();
    DrawSync(0);
}

void func_80037154() // 0x80037154
{
    s32         i;
    s_800BCDA8* element;

    for (i = 0; i < 2; i++)
    {
        element = &D_800BCDA8[i];

        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void func_80037188() // 0x80037188
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < 2; i++)
    {
        func_8004690C(Sfx_Unk1321 + i);
    }
}

void Chara_PositionUpdateFromParams(s_AreaLoadParams* params) // 0x800371E8
{
    s32 rotY;
    
    rotY = FP_ANGLE_PACKED_FROM(params->rotationY_4_16);
    Math_SVectorSet(&g_SysWork.player_4C.chara_0.rotation_24, FP_ANGLE(0.0f), rotY, FP_ANGLE(0.0f));

    g_SysWork.player_4C.chara_0.position_18.vy = FP_METER(0.0f);
    g_SysWork.player_4C.chara_0.position_18.vx = params->char_x_0;
    g_SysWork.player_4C.chara_0.position_18.vz = params->char_z_8;

    if (params->field_4_24 >= 2)
    {
        g_SysWork.player_4C.chara_0.position_18.vx += FP_MULTIPLY_FLOAT_PRECISE(Math_Sin(rotY), 0.4f, Q12_SHIFT);
        g_SysWork.player_4C.chara_0.position_18.vz += FP_MULTIPLY_FLOAT_PRECISE(Math_Cos(rotY), 0.4f, Q12_SHIFT);
    }

    g_SysWork.loadingScreenIdx_2281 = params->loadingScreenId_4_9;

    if (params->mapIdx_4_0 == 24)
    {
        g_SavegamePtr->current2dMapIdx_A9 = Current2dMap_OtherPlaces;
    }
    else if (params->mapIdx_4_0 != Current2dMap_OtherPlaces)
    {
        g_SavegamePtr->current2dMapIdx_A9 = params->mapIdx_4_0;
    }

    g_SysWork.cameraAngleY_237A = rotY;

    func_8007E9C4();
    Savegame_MapRoomIdxSet();
}

void func_80037334() // 0x80037334
{
    s_func_800699F8 sp10;

    if (g_MapOverlayHeader.func_40 != 0)
    {
        g_MapOverlayHeader.func_40();
    }

    func_800699F8(&sp10, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz);
    g_SysWork.player_4C.chara_0.position_18.vy = sp10.groundHeight_0;
}

void func_80037388() // 0x80037388
{
    volatile s32 v1;
    s32          v2;
    s32          i;

    v1 = v2;
    for (i = 0; i < 5; i++)
    { 
        D_800BCDC0[i] = NO_VALUE;
        D_800BCD90[i] = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80032D1C", func_800373CC); // 0x800373CC

bool func_800378D4(s_AreaLoadParams* areaLoadParams) // 0x800378D4
{
    s16 rotY;
    s32 x;
    s32 z;
    s32 deltaRotY;

    if (g_MainLoop_FrameCount > D_800A9A20)
    {
        rotY       = g_SysWork.player_4C.chara_0.rotation_24.vy;
        D_800A9A24 = g_SysWork.player_4C.chara_0.position_18.vx - (Math_Sin(rotY) >> 3);
        D_800A9A28 = g_SysWork.player_4C.chara_0.position_18.vz - (Math_Cos(rotY) >> 3);
        D_800A9A20 = g_MainLoop_FrameCount;
    }

    x = areaLoadParams->char_x_0 - D_800A9A24;
    if (ABS(x) > FP_METER(0.8f))
    {
        return false;
    }

    z = areaLoadParams->char_z_8 - D_800A9A28;
    if (ABS(z) > FP_METER(0.8f))
    {
        return false;
    }

    if ((SQUARE(x) + SQUARE(z)) > SQUARE(FP_METER(0.8f)))
    {
        return false;
    }

    deltaRotY = g_SysWork.player_4C.chara_0.rotation_24.vy - ratan2(x, z);
    if (deltaRotY >= FP_ANGLE(180.0f))
    {
        deltaRotY -= FP_ANGLE(360.0f);
    }

    if (FP_ANGLE(30.0f) < ABS(deltaRotY))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool func_80037A4C(s_AreaLoadParams* areaLoadParams) // 0x80037A4C
{
    s32  temp_a0_2;
    s32  temp_a2;
    s32  halfCosPlayerRotY;
    s32  temp_s2;
    s32  halfSinRotY;
    s32  temp_s4;
    s32  deltaX;
    s32  deltaZ;
    s32  temp_v1;
    s32  var_a0;
    s32  var_a0_2;
    s32  clampedHalfCosPlayerRotY;
    bool cond;
    s32  var_v1;
    s32  scaledSinPlayerRotY;
    s32  scaledCosRotY;

    halfSinRotY   = Math_Sin(g_SysWork.player_4C.chara_0.rotation_24.vy) >> 1;
    scaledCosRotY = -Math_Cos(FP_ANGLE_PACKED_FROM(areaLoadParams->rotationY_4_16)) * areaLoadParams->field_4_24;

    clampedHalfCosPlayerRotY = halfSinRotY;

    temp_a0_2 = scaledCosRotY >> 4;
    deltaX    = areaLoadParams->char_x_0 - g_SysWork.player_4C.chara_0.position_18.vx;
    temp_s2   = deltaX - temp_a0_2;
    temp_s4   = deltaX + temp_a0_2;

    clampedHalfCosPlayerRotY = MAX(halfSinRotY, 0);

    if (temp_s4 >= temp_s2)
    {
        cond = clampedHalfCosPlayerRotY < temp_s2;
    }
    else
    {
        cond = clampedHalfCosPlayerRotY < temp_s4;
    }

    if (!cond)
    {
        if (MIN(halfSinRotY, 0) <= MAX(temp_s2, temp_s4))
        {
            halfCosPlayerRotY   = Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy) >> 1;
            scaledSinPlayerRotY = Math_Sin(FP_ANGLE_PACKED_FROM(areaLoadParams->rotationY_4_16)) * areaLoadParams->field_4_24;

            clampedHalfCosPlayerRotY = halfCosPlayerRotY;

            temp_a0_2 = scaledSinPlayerRotY >> 4;
            deltaZ    = areaLoadParams->char_z_8 - g_SysWork.player_4C.chara_0.position_18.vz;
            temp_v1   = deltaZ - temp_a0_2;
            temp_a2   = deltaZ + temp_a0_2;

            clampedHalfCosPlayerRotY = MAX(halfCosPlayerRotY, 0);

            if (temp_a2 >= temp_v1)
            {
                cond = clampedHalfCosPlayerRotY < temp_v1;
            }
            else
            {
                cond = clampedHalfCosPlayerRotY < temp_a2;
            }

            if (!cond)
            {
                if (MIN(halfCosPlayerRotY, 0) <= MAX(temp_v1, temp_a2) &&
                   (((temp_s2 * halfCosPlayerRotY) - (halfSinRotY * temp_v1)) <= 0) && ((temp_s4 * halfCosPlayerRotY) - (halfSinRotY * temp_a2)) >= 0 &&
                   ((-temp_s2 * (temp_a2 - temp_v1)) + ((temp_s4 - temp_s2) * temp_v1)) >= 0)
                {
                    return (((halfSinRotY - temp_s2) * (temp_a2 - temp_v1)) -
                            ((temp_s4 - temp_s2) * (halfCosPlayerRotY - temp_v1))) < 1;
                }
            }
        }
    }

    return false;
}

bool func_80037C5C(s_func_80037A4C* arg0) // 0x80037C5C
{
    s32 sinAngle;
    s32 cosAngle;
    s32 angle;
    s32 deltaZ;
    s32 deltaX;
    s32 shift8Field_7;
    s32 temp_v0;
    s32 scale;
    u32 temp;

    shift8Field_7 = arg0->field_7 << 8;
    deltaX        = g_SysWork.player_4C.chara_0.position_18.vx - arg0->field_0;

    if (arg0->field_7 << 9 < ABS(deltaX))
    {
        return false;
    }

    deltaZ = g_SysWork.player_4C.chara_0.position_18.vz - arg0->field_8;
    scale  = 2;

    if ((shift8Field_7 * scale) < ABS(deltaZ))
    {
        return false;
    }

    angle    = -(arg0->field_6 << 20) >> 16;
    sinAngle = Math_Sin(angle);

    temp = FP_FROM((-deltaX * sinAngle) + (deltaZ * Math_Cos(angle)), Q12_SHIFT);
    if (temp > 0x4000)
    {
        return false;
    }

    cosAngle = Math_Cos(angle);
    temp_v0  = FP_FROM((deltaX * cosAngle) + (deltaZ * Math_Sin(angle)), Q12_SHIFT);

    if (shift8Field_7 < ABS(temp_v0))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void func_80037DC4(s_SubCharacter* chara) // 0x80037DC4
{
    if (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || func_80080514() >= 1228)
    {
        g_SavegamePtr->field_B0[g_SavegamePtr->mapOverlayId_A4] &= ~(1 << chara->field_40);
    }
}

void func_80037E40(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->damageReceived_C0 > FP_FLOAT_TO(0.0f, Q12_SHIFT))
    {
        chara->flags_3E |= CharaFlag_Unk6;
    }
    else
    {
        chara->flags_3E &= ~CharaFlag_Unk6;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle_3C` access.
    if (chara->health_B0 <= 0 && (*(s32*)&chara->headingAngle_3C & 0x600000) == 0x200000)
    {
        idx = chara->field_41;
        if (idx < 39)
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags_3E |= CharaFlag_Unk7;
    }
}

/** Responsible for loading NPCs on the map. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80032D1C", func_80037F24); // 0x80037F24

s32 func_800382B0(s32 arg0) // 0x800382B0
{
    s32         i;
    s_800382B0* ptr;
    s_800382B0* stack[2];

    stack[0] = ptr;

    for (i = 0; i < 2; ++i)
    {
        if (arg0 == ptr[i].field_0)
        {
            return i;
        }
    }

    return NO_VALUE;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80032D1C", func_800382EC); // 0x800382EC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80032D1C", func_80038354); // 0x80038354

bool Math_Distance2dCheck(VECTOR3* pos0, VECTOR3* pos1, s32 radius) // 0x80038A6C
{
    s32 deltaX;
    s32 deltaZ;
    s32 radiusSqr;
    s32 sum;

    // Check rough radius intersection on X axis.
    deltaX = pos0->vx - pos1->vx;
    if (radius < deltaX)
    {
        return true;
    }
    if (radius < -deltaX)
    {
        return true;
    }

    // Check rough radius intersection on Z axis.
    deltaZ = pos0->vz - pos1->vz;
    if (radius < deltaZ)
    {
        return true;
    }
    if (radius < -deltaZ)
    {
        return true;
    }

    // Check distance.
    sum       = FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT);
    radiusSqr = FP_MULTIPLY_PRECISE(radius, radius, Q12_SHIFT);
    return sum > radiusSqr;
}

s32 func_80038B44(VECTOR3* pos) // 0x80038B44
{
    VECTOR3 camPos;
    s32     x;
    s32     y;

    vwGetViewPosition(&camPos);

    x = (camPos.vx - pos->vx) >> 6;
    y = (camPos.vz - pos->vz) >> 6;
    return FP_MULTIPLY_PRECISE(x, x, Q12_SHIFT) + FP_MULTIPLY_PRECISE(y, y, Q12_SHIFT);
}

void GameState_InGame_Update() // 0x80038BD4
{
    s_SubCharacter* player;

    Demo_DemoRandSeedBackup();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            g_Gfx_ScreenFade                = 6;
            D_800B5C30                      = FP_TIME(3.0f);
            g_GameWork.gameStateStep_598[0] = 1;

        case 1:
            DrawSync(0);
            func_80037154();
            Savegame_MapRoomIdxSet();
            func_800892A4(1);

            g_IntervalVBlanks     = 2;
            g_GameWork.gameStateStep_598[0]++;
            g_SysWork.field_22A0 |= 1 << 6;
            break;
    }

    if (g_SysWork.sysState_8 != SysState_Gameplay && g_SysWork.player_4C.chara_0.health_B0 <= 0)
    {
        SysWork_StateSetNext(SysState_Gameplay);
    }

    if (g_DeltaTime0 != FP_TIME(0.0f))
    {
        D_800BCD84 = g_DeltaTime0;
    }
    else
    {
        D_800BCD84 = g_DeltaTime1;
    }

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        g_SysWork.field_18 = 0;
        g_SysStateFuncs[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime0 = 0;
        g_SysStateFuncs[g_SysWork.sysState_8]();

        if (g_SysWork.sysState_8 == SysState_Gameplay)
        {
            func_800373CC(1);
            if (D_800A9A10 != SysState_Unk15)
            {
                SysWork_StateSetNext(D_800A9A10);
            }
        }
    }
    Demo_DemoRandSeedRestore();

    D_800A9A0C = (g_Gfx_ScreenFade & 0x7) == 5 && Fs_QueueDoThingWhenEmpty() != 0;

    if (!(g_SysWork.field_22A0 & (1 << 0)) && g_MapOverlayHeader.func_40 != NULL)
    {
        g_MapOverlayHeader.func_40();
    }

    func_80032904();
    func_80035DB4(0);
    Demo_DemoRandSeedRestore();
    Demo_DemoRandSeedRestore();

    if (!(g_SysWork.field_22A0 & (1 << 0)))
    {
        func_80040014();
        vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
        if (g_MapOverlayHeader.func_44 != NULL)
        {
            g_MapOverlayHeader.func_44();
        }
        Demo_DemoRandSeedRestore();

        player = &g_SysWork.player_4C.chara_0;
        Player_Logic_Update(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        func_8003F170();

        if (g_SavegamePtr->mapOverlayId_A4 != MapOverlayId_MAP7_S03)
        {
            g_MapOverlayHeader.func_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();
        if (player->model_0.anim_4.flags_2 & AnimFlag_Visible)
        {
            func_8003DA9C(1, g_SysWork.playerBoneCoords_890, 1, g_SysWork.player_4C.chara_0.timer_C6, 0);
            func_8008A384(&g_SysWork.player_4C.chara_0);
            func_8007D970(&g_SysWork.player_4C, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.player_4C.chara_0);
        }

        Demo_DemoRandSeedRestore();
        func_80037F24(1);
        func_80038354();
        func_8005E89C();
        func_8003C3AC();
        func_8003C878(1);
        Demo_DemoRandSeedAdvance();
    }
}

void SysState_Gameplay_Update() // 0x80038BD4
{
    s32             state;
    s_SubCharacter* playerChara;

    playerChara = &g_SysWork.player_4C.chara_0;

    func_800373CC(~playerChara->field_41 != 0);
    Savegame_MapRoomIdxSet();

    switch (FP_ROUND_SCALED(playerChara->health_B0, 10, Q12_SHIFT))
    {
        case 0:
            func_800892A4(17);
            break;

        case 1:
        case 2:
            func_800892A4(16);
            break;

        case 3:
            func_800892A4(15);
            break;

        case 4:
            func_800892A4(14);
            break;

        case 5:
            func_800892A4(13);
            break;

        case 6:
            func_800892A4(12);
            break;
    }

    if (g_SysWork.player_4C.chara_0.health_B0 <= FP_FLOAT_TO(0.0f, Q12_SHIFT))
    {
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.light_A &&
        g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        func_8003ED08();
    }

    if (D_800A9A10 != SysState_Unk15)
    {
        SysWork_StateSetNext(D_800A9A10);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        //SysWork_StateSetNext(SysState_GamePaused); // TODO: Doesn't match?
        g_SysWork.sysState_8     = SysState_GamePaused;
        g_SysWork.timer_24       = 0;
        g_SysWork.sysStateStep_C = 0;
        g_SysWork.field_28       = 0;
        g_SysWork.field_10       = 0;
        g_SysWork.timer_2C       = 0;
        g_SysWork.field_14       = 0;
    }
    else if (func_8007F26C() == true)
    {
        return;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
    {
        //SysWork_StateSetNext(SysState_StatusMenu); // TODO: Doesn't match?
        g_SysWork.sysState_8     = SysState_StatusMenu;
        g_SysWork.timer_24       = 0;
        g_SysWork.sysStateStep_C = 0;
        g_SysWork.field_28       = 0;
        g_SysWork.field_10       = 0;
        g_SysWork.timer_2C       = 0;
        g_SysWork.field_14       = 0;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18)
    {
        //SysWork_StateSetNext(SysState_MapScreen); // TODO: Doesn't match?
        g_SysWork.sysState_8     = SysState_MapScreen;
        g_SysWork.timer_24       = 0;
        g_SysWork.sysStateStep_C = 0;
        g_SysWork.field_28       = 0;
        g_SysWork.field_10       = 0;
        g_SysWork.timer_2C       = 0;
        g_SysWork.field_14       = 0;
        g_SysWork.field_18       = 0;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
    }

    if (g_SysWork.sysState_8 == SysState_OptionsMenu ||
        g_SysWork.sysState_8 == SysState_StatusMenu ||
        g_SysWork.sysState_8 == SysState_MapScreen)
    {
        g_SysWork.flags_22A4 |= 1 << 7;
    }
    else if (g_Gfx_ScreenFade == 1)
    {
        g_SysWork.flags_22A4 &= ~(1 << 7);
    }
}

void SysState_GamePaused_Update() // 0x800391E8
{
    D_800A9A68 += g_DeltaTime1;
    if (((D_800A9A68 >> 11) & (1 << 0)) == 0)
    {
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSED", 99);
    }

    func_80091380();
    Game_TimerUpdate();

    if (g_SysWork.sysStateStep_C == 0)
    {
        Sd_EngineCmd(3);
        g_SysWork.sysStateStep_C++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_Controller0->btnsHeld_C == (ControllerFlag_L3 |
                                       ControllerFlag_DpadLeft |
                                       ControllerFlag_L2 |
                                       ControllerFlag_L1 |
                                       ControllerFlag_LStickLeft2 |
                                       ControllerFlag_RStickLeft |
                                       ControllerFlag_LStickLeft)) &&
        (g_Controller0->btnsClicked_10 & ControllerFlag_L3))
    {
        D_800A9A68 = 0;
        Sd_EngineCmd(4);
        g_MapEventIdx = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        D_800A9A68 = 0;
        Sd_EngineCmd(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void SysState_OptionsMenu_Update() // 0x80039344
{
    s32 gameState;

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            g_Gfx_ScreenFade         = 2;
            D_800B5C30               = FP_TIME(0.0f);
            g_SysWork.sysStateStep_C = 1;

        case 1:
            if (func_8003C850() != 0)
            {
                Sd_EngineCmd(19);
                GameFs_OptionBinLoad();

                g_SysWork.sysStateStep_C++;
            }
            break;
    }

    if (D_800A9A0C != 0)
    {
        Game_StateSetNext(GameState_OptionScreen);
    }
}

void func_8003943C()
{
    s32 roundedVal0;
    s32 roundedVal1;
    s32 val0;
    s32 val1;

    func_8008B3E4(0);

    if (g_SysWork.field_275C > FP_TO(256, Q12_SHIFT))
    {
        val0        = g_SysWork.field_275C - FP_TO(256, Q12_SHIFT);
        roundedVal0 = FP_ROUND_TO_ZERO(val0, Q12_SHIFT);
        func_8008B438(g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill, roundedVal0, 0);

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
        {
            val1        = g_SysWork.field_2764 - FP_TO(256, Q12_SHIFT);
            roundedVal1 = FP_ROUND_TO_ZERO(val1, Q12_SHIFT);
            func_8008B40C(roundedVal1, 0);
        }
    }
    else
    {
        func_8008B438(g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill, 0, 0);

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
        {
            func_8008B40C(0, 0);
        }
    }
    
    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S04:
        case MapOverlayId_MAP1_S05:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S03:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S04:
        case MapOverlayId_MAP4_S05:
        case MapOverlayId_MAP4_S06:
        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
        case MapOverlayId_MAP6_S05:
        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
        case MapOverlayId_MAP7_S02:
            break;

        case MapOverlayId_MAP3_S03:
            func_8004690C(Sfx_Unk1525);
            func_8004690C(Sfx_Unk1527);
            break;

        case MapOverlayId_MAP0_S00:
            func_8004690C(Sfx_Unk1358);
            break;
    }
}

void SysState_StatusMenu_Update() // 0x80039568
{
    e_GameState gameState;

    gameState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = GameState_LoadStatusScreen;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = gameState;
    g_GameWork.gameStatePrev_590    = gameState;
    g_GameWork.gameStateStep_598[0] = 0;
}

void GameState_LoadStatusScreen_Update() // 0x800395C0
{
    s_Savegame* savegame;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(0);
        g_IntervalVBlanks = 1;
        g_Gfx_ScreenFade  = 0;

        func_8003943C();

        if (func_80045B28())
        {
            Sd_EngineCmd(19);
        }

        savegame = g_SavegamePtr;
        func_800540A4(savegame->mapOverlayId_A4);
        GameFs_MapItemsTextureLoad(savegame->mapOverlayId_A4);

        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_MotionBlur(2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_InventoryScreen);
    }
}

void SysState_MapScreen_Update() // 0x800396D4
{
    s32         idx;
    s_Savegame* save;

    if (!HAS_MAP(g_SavegamePtr->current2dMapIdx_A9))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_NoMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) && !g_SysWork.field_2388.isFlashlightOn_15 &&
             ((g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) ||
              (g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_TooDarkForMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else
    {
        if (g_SysWork.sysStateStep_C == 0)
        {
            if (g_MapMarkingTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9] != NO_VALUE)
            {
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_MapMarkingTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9], FS_BUFFER_1, &g_MapMarkerAtlasImg);
            }

            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9]);

            g_Gfx_ScreenFade = 2;
            D_800B5C30       = FP_TIME(0.0f);
            g_SysWork.sysStateStep_C++;
        }

        if (D_800A9A0C != 0)
        {
            Game_StateSetNext(GameState_MapScreen);
        }
    }
}

void GameState_LoadMapScreen_Update() // 0x8003991C
{
    s_Savegame* save;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(0);
        g_IntervalVBlanks = 1;

        func_8003943C();
        func_80066E40();

        save = g_SavegamePtr;

        if (g_MapMarkingTimFileIdxs[save->current2dMapIdx_A9] != NO_VALUE)
        {
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_MapMarkingTimFileIdxs[save->current2dMapIdx_A9], FS_BUFFER_1, &g_MapMarkerAtlasImg);
        }

        Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[save->current2dMapIdx_A9], FS_BUFFER_2, &g_MapImg);
        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_MotionBlur(2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_MapScreen);
    }
}

void SysState_Fmv_Update() // 0x80039A58
{
    #define BASE_AUDIO_FILE_IDX FILE_XA_ZC_14392

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            g_Gfx_ScreenFade         = 3;
            D_800A9A0C               = 0;
            g_SysWork.sysStateStep_C = 1;

        case 1:
            if (func_8003C850() != 0)
            {
                GameFs_StreamBinLoad();
                g_SysWork.sysStateStep_C++;
            }
            break;
    }

    if (D_800A9A0C == 0)
    {
        return;
    }

    // Copy framebuffer into `IMAGE_BUFFER_0` before movie playback.
    DrawSync(0);
    StoreImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(0);

    func_800892A4(0);
    func_80089128();

    // Start playing movie. File to play is based on file ID `BASE_AUDIO_FILE_IDX - g_MapEventIdx`.
    // Blocks until movie has finished playback or user has skipped it.
    open_main(BASE_AUDIO_FILE_IDX - g_MapEventIdx, g_FileTable[BASE_AUDIO_FILE_IDX - g_MapEventIdx].blockCount_0_13);

    func_800892A4(1);

    // Restore copied framebuffer from `IMAGE_BUFFER_0`.
    GsSwapDispBuff();
    LoadImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(0);

    // Set savegame flag based on `D_800BCDD8->eventFlagNum_2` flag ID.
    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

    // Return to game.
    Game_StateSetNext(GameState_InGame);

    // If flag is set, returns to `GameState_InGame` with `gameStateStep[0]` = 1.
    if (g_MapEventParam->flags_8_13 & (1 << 1))
    {
        g_GameWork.gameStateStep_598[0] = 1;
    }
}

void SysState_LoadArea_Update() // 0x80039C40
{
    u32               var1;
    s_AreaLoadParams* areaLoadParams;

    g_SysWork.field_229C            = 0;
    g_SysWork.loadingScreenIdx_2281 = D_800BCDB0.loadingScreenId_4_9;
    g_SysWork.field_2283            = g_MapEventParam->field_8_19;
    g_SysWork.field_2282            = g_MapEventParam->flags_8_13;

    Sd_EngineCmd(SfxPairs[g_SysWork.field_2283].sfx_0);

    if (g_SysWork.field_2283 == 7)
    {
        D_800BCDD4            = 0;
        g_SysWork.flags_22A4 |= 1 << 10;
    }

    D_800BCDB0 = g_MapOverlayHeader.mapAreaLoadParams_1C[g_MapEventParam->pointOfInterestIdx_8_5];

    if (D_800BCDB0.field_4_24 == 1)
    {
        areaLoadParams       = &g_MapOverlayHeader.mapAreaLoadParams_1C[g_MapEventParam->field_5];
        var1                 = g_SysWork.player_4C.chara_0.position_18.vz - areaLoadParams->char_z_8;
        D_800BCDB0.char_x_0 += g_SysWork.player_4C.chara_0.position_18.vx - areaLoadParams->char_x_0;
        D_800BCDB0.char_z_8 += var1;
    }

    // Handle `SysState_LoadArea0` and `SysState_LoadArea1`.
    // TODO: Document what the difference here is.
    if (g_SysWork.sysState_8 == SysState_LoadArea0)
    {
        g_SysWork.processFlags_2298    = SysWorkProcessFlag_OverlayTransition;
        g_SavegamePtr->mapOverlayId_A4 = g_MapEventParam->mapOverlayIdx_8_25;
        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
    }
    else
    {
        g_SysWork.processFlags_2298 = SysWorkProcessFlag_RoomTransition;
        func_8003640C(g_MapEventParam->mapOverlayIdx_8_25);

        if (g_MapOverlayHeader.mapAreaLoadParams_1C[g_MapEventParam->pointOfInterestIdx_8_5].field_4_5 != 0)
        {
            g_SysWork.field_2349 = g_MapOverlayHeader.mapAreaLoadParams_1C[g_MapEventParam->pointOfInterestIdx_8_5].field_4_5 - 1;
        }
    }

    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

    if (g_MapEventParam->field_8_24)
    {
        g_SysWork.flags_22A4 |= 1 << 6;
    }
    else
    {
        g_SysWork.flags_22A4 &= ~(1 << 6);
    }

    g_SysWork.field_22A0 |= 1 << 0;
    Game_StateSetNext(GameState_MainLoadScreen);
    Gfx_MotionBlur(1);
}

void AreaLoad_UpdatePlayerPosition() // 0x80039F30
{
    Chara_PositionUpdateFromParams(&D_800BCDB0);
}

void func_80039F54() // 0x80039F54
{
    Sd_EngineCmd(SfxPairs[g_SysWork.field_2283].sfx_2);
}

s8 func_80039F90() // 0x80039F90
{
    if (g_SysWork.processFlags_2298 & (SysWorkProcessFlag_RoomTransition | SysWorkProcessFlag_OverlayTransition))
    {
        return g_SysWork.field_2282;
    }

    return 0;
}

void SysState_ReadMessage_Update(s32 arg0) // 0x80039FB8
{
    s32 i;
    u32 charaId;
    void (**func)(s32);

    i = arg0;

    if (!(g_MapEventParam->flags_8_13 & (1 << 0)) && !(g_SysWork.flags_22A4 & (1 << 5)))
    {
        for (i = 0; i < NPC_COUNT_MAX; i++) 
        {
            charaId = (u8)g_SysWork.npcs_1A0[i].model_0.charaId_0 - 1;
            if (charaId < Chara_MonsterCybil && g_SysWork.npcs_1A0[i].health_B0 > FP_FLOAT_TO(0.0f, Q12_SHIFT))
            {
                break;
            }
        }

        if (i == 6)
        {
            g_DeltaTime0 = D_800BCD84;
        }
    }
    else
    {
        g_DeltaTime0 = D_800BCD84;
    }

    if (g_SysWork.field_18 == 0)
    {
        g_MapOverlayHeader.freezePlayerControl_C8(i);
    }

    switch (Gfx_MapMsg_Draw(g_MapEventIdx)) 
    {
        case MapMsgState_Finish:
            break;

        case MapMsgState_Idle:
            break;
        
        case MapMsgState_SelectEntry0:
            Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

            func = &g_MapOverlayHeader.unfreezePlayerControl_CC;

            SysWork_StateSetNext(SysState_Gameplay);

            (*func)(0);
            break;
    }
}

void SysWork_SavegameUpdatePlayer() // 0x8003A120
{
    s_Savegame* save;

    save = g_SavegamePtr;

    save->locationId_A8       = g_MapEventIdx;
    save->playerPositionX_244 = g_SysWork.player_4C.chara_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.player_4C.chara_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.player_4C.chara_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.player_4C.chara_0.health_B0;
}

void func_8003A16C() // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & 2))
    {
        // Update `savegame_30C` with player info.
        SysWork_SavegameUpdatePlayer();

        g_GameWork.autosave_90 = g_GameWork.savegame_30C;
    }
}

void SysWork_SavegameReadPlayer() // 0x8003A1F4
{
    g_SysWork.player_4C.chara_0.position_18.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.player_4C.chara_0.position_18.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.player_4C.chara_0.rotation_24.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.player_4C.chara_0.health_B0      = g_SavegamePtr->playerHealth_240;
}

void SysState_SaveMenu_Update() // 0x8003A230
{
    s32 gameState;

    func_80033548();

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            SysWork_SavegameUpdatePlayer();

            if ((g_SavegamePtr->eventFlags_168[5] & EVENT_FLAG5_FIRST_TIME_SAVE_GAME) || g_SavegamePtr->locationId_A8 == 24 || g_MapEventIdx == 0)
            {
                GameFs_SaveLoadBinLoad();

                g_Gfx_ScreenFade = 2;
                SysWork_StateStepIncrement();
            }

            else if (Gfx_MapMsg_Draw(MapMsgIdx_SaveGame) == MapMsgState_SelectEntry0)
            {
                g_SavegamePtr->eventFlags_168[5] |= EVENT_FLAG5_FIRST_TIME_SAVE_GAME;

                GameFs_SaveLoadBinLoad();

                g_Gfx_ScreenFade   = 2;
                SysWork_StateStepIncrement();
            }
            break;
        
        case 1:
            if (D_800A9A0C != 0)
            {
                g_Gfx_ScreenFade = 6;

                func_8003943C();

                gameState = g_GameWork.gameState_594;

                g_GameWork.gameState_594 = GameState_Unk10;

                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;
    }
}

void SysState_EventCallFunc_Update() // 0x8003A3C8
{
    if (g_MapEventParam->flags_8_13 != 0)
    {
        Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    }

    g_DeltaTime0 = D_800BCD84;
    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();
}

void SysState_EventSetFlag_Update() // 0x8003A460
{
    g_DeltaTime0 = D_800BCD84;
    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_EventPlaySound_Update() // 0x8003A4B4
{
    g_DeltaTime0 = D_800BCD84;

    Sd_EngineCmd(((u16)g_MapEventIdx + 0x500) & 0xFFFF);

    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_GameOver_Update() // 0x8003A52C
{
    #define TIP_COUNT 15

    extern u8   g_SysState_GameOver_TipIdx; // Only used in this func, maybe static.

    u16  seenTipIdxs[1];
    s32  tipIdx;
    s32  randTipVal;
    u16* temp_a0;

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            g_SysWork.field_28 = 0;

            if (g_GameWork.autosave_90.continueCount_27B < 99)
            {
                g_GameWork.autosave_90.continueCount_27B++;
            }

            MainMenu_SelectedOptionIdxReset();

            // If every game over tip has been seen, reset flag bits.
            if (g_GameWork.config_0.seenGameOverTips_2E[0] == 0x7FFF)
            {
                g_GameWork.config_0.seenGameOverTips_2E[0] = 0;
            }

            randTipVal = 0;

            seenTipIdxs[0] = g_GameWork.config_0.seenGameOverTips_2E[0];
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) < 2u))
                    {
                        randTipVal += 3;
                    }
                    else
                    {
                        randTipVal++;
                    }
                }
            }

            randTipVal = Rng_GenerateInt(Rng_Rand16(), 0, randTipVal - 1);

            // `randTipVal` seems to go unused after loop, gets checked during loop and can cause early exit,
            // thereby affecting what `tipIdx` will contain.
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        if (randTipVal < 3)
                        {
                            break;
                        }

                        randTipVal -= 3;
                    }
                    else
                    {
                        if (randTipVal <= 0)
                        {
                            break;
                        }

                        randTipVal--;
                    }
                }
            }

            // Store current shown `tipIdx`, later `sysStateStep_C == 7` will set it inside `seenGameOverTips_2E`.
            g_SysState_GameOver_TipIdx = tipIdx;

            Fs_QueueStartReadTim(FILE_TIM_TIPS_E01_TIM + tipIdx, FS_BUFFER_1, &g_DeathTipImg);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 0, FP_TIME(0.5f), false);
            break;

        case 2:
            func_8008616C(0, false, 0, FP_TIME(0.5f), false);
            SysWork_StateStepIncrement();

        case 3:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", 0x63);
            g_SysWork.field_28++;

            if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                  g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
                g_SysWork.field_28 > 240)
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 4:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", 0x63);
            func_8008616C(2, true, 0, FP_TIME(2.0f), false);
            break;

        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                SysWork_StateStepReset();
                break;
            }
            else
            {
                Fs_QueueWaitForEmpty();
                func_80037188();
                SysWork_StateStepIncrement();
            }

        case 6:
            func_8008616C(2, false, 0, FP_TIME(2.0f), false);
            g_SysWork.field_28 = 0;
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            break;

        case 7:
            g_SysWork.field_28++;
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);

            if (!(g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                   g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                if (g_SysWork.field_28 <= 480)
                {
                    break;
                }
            }

            // TODO: some inline FlagSet func? couldn't get matching ver, but pretty sure temp_a0 can be removed somehow
            temp_a0 = &g_GameWork.config_0.seenGameOverTips_2E[(g_SysState_GameOver_TipIdx >> 5)];
            *temp_a0 |= (1 << 0) << (g_SysState_GameOver_TipIdx & 0x1F);

            SysWork_StateStepIncrement();
            break;

        case 8:
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            func_8008616C(2, true, 0, FP_TIME(2.0f), false);
            break;

        default:
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();
            break;
    }

    if (g_SysWork.sysStateStep_C >= 2 || g_GameWork.gameState_594 != GameState_InGame)
    {
        g_SysWork.field_22A0 |= 1 << 0;
    }
}

void GameState_MapEvent_Update() // 0x8003AA4C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_IntervalVBlanks               = 1;
        g_Gfx_ScreenFade                = 6;
        g_GameWork.gameStateStep_598[0] = 1;
    }

    D_800A9A0C = (g_Gfx_ScreenFade & 0x7) == 5 && Fs_QueueDoThingWhenEmpty();

    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();

    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}
