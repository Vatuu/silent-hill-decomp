#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// MAP EVENTS RELATED
// ========================================

u8 g_SysState_GameOver_TipIdx;

s8 pad_bss_800BCD81[3];

s32 g_DeltaTimeCpy;

s32 pad_bss_800BCD88[2];

s_EventData* g_ItemTriggerEvents[];

s32 pad_bss_800BCD94[5];

s_800BCDA8 D_800BCDA8[2];

s_MapPoint2d D_800BCDB0;

s32 pad_bss_800BCDD0;

s32 g_ItemTriggerItemIds[5];

u8 D_800BCDD4;

s8 pad_bss_800BCDD5[3];

s_EventData* g_MapEventData;

void AreaLoad_UpdatePlayerPosition(void) // 0x80039F30
{
    Chara_PositionSet(&D_800BCDB0);
}

void AreaLoad_TransitionSound(void) // 0x80039F54
{
    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_2);
}

s8 func_80039F90(void) // 0x80039F90
{
    if (g_SysWork.processFlags_2298 & (SysWorkProcessFlag_RoomTransition | SysWorkProcessFlag_OverlayTransition))
    {
        return g_SysWork.field_2282;
    }

    return 0;
}

void SysState_ReadMessage_Update(void) // 0x80039FB8
{
    s32 i;
    void (**unfreezePlayerFunc)(bool);

    // When `SysState_ReadMessage_Update` is called, the game world freezes.
    // The following conditions unfreeze:
    // - A specific event related flag is disenabled.
    // - A specific camera related flag is disenabled.
    // - There is no alive enemy.
    if (!(g_MapEventData->flags_8_13 & EventParamUnkState_0) && !(g_SysWork.flags_22A4 & SysFlag2_5))
    {
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry && g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }

        if (i == ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime = g_DeltaTimeCpy;
        }
    }
    else
    {
        g_DeltaTime = g_DeltaTimeCpy;
    }

    if (g_SysWork.isMgsStringSet_18 == 0)
    {
        g_MapOverlayHeader.playerControlFreeze_C8();
    }

    switch (Gfx_MapMsg_Draw(g_MapEventParam))
    {
        case MapMsgState_Finish:
            break;

        case MapMsgState_Idle:
            break;

        case MapMsgState_SelectEntry0:
            Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);

            unfreezePlayerFunc = &g_MapOverlayHeader.playerControlUnfreeze_CC;

            SysWork_StateSetNext(SysState_Gameplay);

            (*unfreezePlayerFunc)(false);
            break;
    }
}

void SysWork_SavegameUpdatePlayer(void) // 0x8003A120
{
    s_Savegame* save;

    save = g_SavegamePtr;

    save->locationId_A8       = g_MapEventParam;
    save->playerPositionX_244 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.playerWork_4C.player_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.playerWork_4C.player_0.health_B0;
}

void func_8003A16C(void) // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        // Update `savegame_30C` with player info.
        SysWork_SavegameUpdatePlayer();

        g_GameWork.autosave_90 = g_GameWork.savegame_30C;
    }
}

void SysWork_SavegameReadPlayer(void) // 0x8003A1F4
{
    g_SysWork.playerWork_4C.player_0.position_18.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.playerWork_4C.player_0.position_18.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.playerWork_4C.player_0.rotation_24.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.playerWork_4C.player_0.health_B0      = g_SavegamePtr->playerHealth_240;
}

void SysState_SaveMenu_Update(void) // 0x8003A230
{
    s32 gameState;

    func_80033548();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            SysWork_SavegameUpdatePlayer();

            if (Savegame_EventFlagGet(EventFlag_SeenSaveScreen) || g_SavegamePtr->locationId_A8 == SaveLocationId_NextFear || g_MapEventParam == 0)
            {
                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            else if (Gfx_MapMsg_Draw(MapMsgIdx_SaveGame) == MapMsgState_SelectEntry0)
            {
                Savegame_EventFlagSet(EventFlag_SeenSaveScreen);

                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 1:
            if (D_800A9A0C != 0)
            {
                ScreenFade_Start(true, true, false);

                func_8003943C();

                gameState = g_GameWork.gameState_594;

                g_GameWork.gameState_594 = GameState_SaveScreen;

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

void SysState_EventCallFunc_Update(void) // 0x8003A3C8
{
    if (g_MapEventData->flags_8_13 != EventParamUnkState_None)
    {
        Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);
    }

    g_DeltaTime = g_DeltaTimeCpy;
    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventParam]();
}

void SysState_EventSetFlag_Update(void) // 0x8003A460
{
    g_DeltaTime = g_DeltaTimeCpy;
    Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_EventPlaySound_Update(void) // 0x8003A4B4
{
    g_DeltaTime = g_DeltaTimeCpy;

    SD_Call(((u16)g_MapEventParam + Sfx_Base) & 0xFFFF);

    Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_GameOver_Update(void) // 0x8003A52C
{
    #define TIP_COUNT 15

    u16  seenTipIdxs[1];
    s32  tipIdx;
    s32  randTipVal;
    u16* temp_a0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            g_SysWork.field_28 = Q12(0.0f);

            if (g_GameWork.autosave_90.continueCount_27B < 99)
            {
                g_GameWork.autosave_90.continueCount_27B++;
            }

            MainMenu_SelectedOptionIdxReset();

            // If every game over tip has been seen, reset flag bits.
            if (g_GameWork.config_0.seenGameOverTips_2E[0] == SHRT_MAX)
            {
                g_GameWork.config_0.seenGameOverTips_2E[0] = 0;
            }

            randTipVal = 0;

            seenTipIdxs[0] = g_GameWork.config_0.seenGameOverTips_2E[0];
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        randTipVal += 3;
                    }
                    else
                    {
                        randTipVal++;
                    }
                }
            }

            randTipVal = Rng_GenerateInt(0, randTipVal - 1);

            // `randTipVal` seems to go unused after loop, gets checked during loop and can cause early exit,
            // thereby affecting what `tipIdx` will contain.
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
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
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.5f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            g_SysWork.field_28++;

            if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                  g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
                g_SysWork.field_28 > Q12(1.0f / 17.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 4:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
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
                Game_RadioSoundStop();
                SysWork_StateStepIncrement(0);
            }

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(2.0f), false);
            g_SysWork.field_28 = Q12(0.0f);
            Screen_BackgroundImgDraw(&g_DeathTipImg);
            break;

        case 7:
            g_SysWork.field_28++;
            Screen_BackgroundImgDraw(&g_DeathTipImg);

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

            SysWork_StateStepIncrement(0);
            break;

        case 8:
            Screen_BackgroundImgDraw(&g_DeathTipImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        default:
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 2 || g_GameWork.gameState_594 != GameState_InGame)
    {
        g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    }
}

void GameState_MapEvent_Update(void) // 0x8003AA4C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_IntervalVBlanks               = 1;
        ScreenFade_Start(true, true, false);
        g_GameWork.gameStateStep_598[0] = 1;
    }

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);

    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventParam]();

    Screen_BackgroundImgDraw(&g_ItemInspectionImg);
}
