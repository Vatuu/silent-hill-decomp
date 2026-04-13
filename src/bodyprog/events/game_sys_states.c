#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/events_main.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/player.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"

#ifndef PAD_HACK_IGNORE
    s8  pad_bss_800BCD81[3];
    s32 pad_bss_800BCD88[2];
    s32 pad_bss_800BCD94[5];
    s32 pad_bss_800BCDD0;
    s8  pad_bss_800BCDD5[3];
#endif

// ========================================
// STATIC VARIABLES
// ========================================

static void (*g_SysStateFuncs[])(void) = {
    SysState_Gameplay_Update,
    SysState_OptionsMenu_Update,
    SysState_StatusMenu_Update,
    SysState_MapScreen_Update,
    SysState_Fmv_Update,
    SysState_LoadArea_Update,
    SysState_LoadArea_Update,
    SysState_ReadMessage_Update,
    SysState_SaveMenu_Update,
    SysState_SaveMenu_Update,
    SysState_EventCallFunc_Update,
    SysState_EventSetFlag_Update,
    SysState_EventPlaySound_Update,
    SysState_GameOver_Update,
    SysState_GamePaused_Update
};

/** Used to store the previous delta time state of the delta timer. There are some instances where 2D backgrounds
 * are drawn using `g_DeltaTimeRaw` while `g_DeltaTime` is stopped.
 */
static s32 g_DeltaTimeCpy;

// ========================================
// GLOBAL VARIABLES
// ========================================

s_EventData* g_ItemTriggerEvents[];
s_800BCDA8   D_800BCDA8[2];
s_MapPoint2d D_800BCDB0;
s32          g_ItemTriggerItemIds[5];
u8           D_800BCDD4;
s_EventData* g_MapEventData;

void GameState_InGame_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    Demo_DemoRandSeedBackup();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep            = Q12(3.0f);
            g_GameWork.gameStateStep_598[0] = 1;

        case 1:
            DrawSync(SyncMode_Wait);
            func_80037154();
            Savegame_MapRoomIdxUpdate();
            func_800892A4(1);

            g_IntervalVBlanks = 2;
            g_GameWork.gameStateStep_598[0]++;
            g_SysWork.sysFlags_22A0 |= SysFlag_6;
            break;
    }

    if (g_SysWork.sysState_8 != SysState_Gameplay && g_SysWork.playerWork.player.health <= Q12(0.0f))
    {
        SysWork_StateSetNext(SysState_Gameplay);
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        g_DeltaTimeCpy = g_DeltaTime;
    }
    else
    {
        g_DeltaTimeCpy = g_DeltaTimeRaw;
    }

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        g_SysWork.isMgsStringSet_18 = false;
        g_SysStateFuncs[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime = Q12(0.0f);
        g_SysStateFuncs[g_SysWork.sysState_8]();

        if (g_SysWork.sysState_8 == SysState_Gameplay)
        {
            Event_Update(true);

            if (g_MapEventSysState != SysState_Invalid)
            {
                SysWork_StateSetNext(g_MapEventSysState);
            }
        }
    }
    Demo_DemoRandSeedRestore();

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze) && g_MapOverlayHeader.worldObjectsUpdate_40 != NULL)
    {
        g_MapOverlayHeader.worldObjectsUpdate_40();
    }

    Screen_CutsceneCameraStateUpdate();
    Bgm_TrackUpdate(false);
    Demo_DemoRandSeedRestore();
    Demo_DemoRandSeedRestore();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze))
    {
        func_80040014();
        vcMoveAndSetCamera(false, false, false, false, false, false, false, false);

        if (g_MapOverlayHeader.func_44 != NULL)
        {
            g_MapOverlayHeader.func_44();
        }

        Demo_DemoRandSeedRestore();

        player = &g_SysWork.playerWork.player;
        Player_Update(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        Gfx_FlashlightUpdate();

        if (g_SavegamePtr->mapOverlayId_A4 != MapOverlayId_MAP7_S03)
        {
            g_MapOverlayHeader.particlesUpdate_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();

        if (player->model.anim.flags & AnimFlag_Visible)
        {
            func_8003DA9C(Chara_Harry, g_SysWork.playerBoneCoords_890, 1, g_SysWork.playerWork.player.timer_C6, 0);
            Chara_Flag8Clear(&g_SysWork.playerWork.player);
            Player_CombatUpdate(&g_SysWork.playerWork, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.playerWork.player);
        }

        Demo_DemoRandSeedRestore();
        Game_NpcRoomInitSpawn(true);
        Game_NpcUpdate();
        func_8005E89C();
        Ipd_CloseRangeChunksInit();
        Gfx_InGameDraw(1);
        Demo_DemoRandSeedAdvance();
    }
}

void SysState_Gameplay_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    player = &g_SysWork.playerWork.player;

    Event_Update(player->attackReceived != NO_VALUE);
    Savegame_MapRoomIdxUpdate();

    switch (FP_ROUND_SCALED(player->health, 10, Q12_SHIFT))
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

    if (g_SysWork.playerWork.player.health <= Q12(0.0f))
    {
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.light_A &&
        g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        Game_FlashlightToggle();
    }

    if (g_MapEventSysState != SysState_Invalid)
    {
        SysWork_StateSetNext(g_MapEventSysState);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        SysWork_StateSetNext(SysState_GamePaused);
    }
    else if (Player_IsAttacking() == true)
    {
        return;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
    {
        SysWork_StateSetNext(SysState_StatusMenu);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18)
    {
        SysWork_StateSetNext(SysState_MapScreen);
        g_SysWork.isMgsStringSet_18 = false;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
    }

    if (g_SysWork.sysState_8 == SysState_OptionsMenu ||
        g_SysWork.sysState_8 == SysState_StatusMenu ||
        g_SysWork.sysState_8 == SysState_MapScreen)
    {
        g_SysWork.flags_22A4 |= SysFlag2_MenuOpen;
    }
    else if (ScreenFade_IsNone())
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_MenuOpen;
    }
}

void SysState_GamePaused_Update(void) // 0x800391E8
{
    static s32 D_800A9A68 = 0;

    D_800A9A68 += g_DeltaTimeRaw;
    if (!((D_800A9A68 >> 11) & (1 << 0)))
    {
#if VERSION_REGION_IS(NTSCJ)
        Gfx_StringSetPosition(SCREEN_POSITION_X(41.0f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSE", DEFAULT_MAP_MESSAGE_LENGTH);
#else
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSED", DEFAULT_MAP_MESSAGE_LENGTH);
#endif
    }

    func_80091380();
    Game_TimerUpdate();

    if (g_SysWork.sysStateStep_C[0] == 0)
    {
        SD_Call(3);
        g_SysWork.sysStateStep_C[0]++;
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
        SD_Call(4);
        g_MapEventParam = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        D_800A9A68 = 0;

        SD_Call(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void SysState_OptionsMenu_Update(void) // 0x80039344
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep        = Q12(0.0f);
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                SD_Call(19);
                GameFs_OptionBinLoad();

                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C != 0)
    {
        Game_StateSetNext(GameState_OptionScreen);
    }
}

void func_8003943C(void) // 0x8003943C
{
    s32 roundedVal0;
    s32 roundedVal1;
    s32 val0;
    s32 val1;

    #define isRockDrillAttack (g_SysWork.playerCombat_38.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))

    func_8008B3E4(0);

    if (g_SysWork.field_275C > Q12(256.0f))
    {
        val0        = g_SysWork.field_275C - Q12(256.0f);
        roundedVal0 = FP_ROUND_TO_ZERO(val0, Q12_SHIFT);
        func_8008B438(!isRockDrillAttack, roundedVal0, 0);

        if (isRockDrillAttack)
        {
            val1        = g_SysWork.field_2764 - Q12(256.0f);
            roundedVal1 = FP_ROUND_TO_ZERO(val1, Q12_SHIFT);
            func_8008B40C(roundedVal1, 0);
        }
    }
    else
    {
        func_8008B438(!isRockDrillAttack, 0, 0);

        if (isRockDrillAttack)
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
            Sd_SfxStop(Sfx_Unk1525);
            Sd_SfxStop(Sfx_Unk1527);
            break;

        case MapOverlayId_MAP0_S00:
            Sd_SfxStop(Sfx_Unk1358);
            break;
    }

    #undef isRockDrillAttack
}

void SysState_StatusMenu_Update(void) // 0x80039568
{
    e_GameState gameState;

    gameState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = GameState_LoadStatusScreen;
    g_SysWork.counters_1C[0] = 0;
    g_SysWork.counters_1C[1] = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = gameState;
    g_GameWork.gameStatePrev_590    = gameState;
    g_GameWork.gameStateStep_598[0] = 0;
}

void GameState_LoadStatusScreen_Update(void) // 0x800395C0
{
    s_Savegame* save;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks = 1;
        ScreenFade_Reset();

        func_8003943C();

        if (Sd_AudioStreamingCheck())
        {
            SD_Call(19);
        }

        save = g_SavegamePtr;
        func_800540A4(save->mapOverlayId_A4);
        GameFs_MapItemsTextureLoad(save->mapOverlayId_A4);

        g_GameWork.gameStateStep_598[0]++;
    }

    Screen_BackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_InventoryScreen);
    }
}

void SysState_MapScreen_Update(void) // 0x800396D4
{
    if (!HAS_MAP(g_SavegamePtr->paperMapIdx_A9))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_NoMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) && !g_SysWork.field_2388.isFlashlightOn_15 &&
             ((g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) ||
              (g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_TooDarkForMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else
    {
        if (g_SysWork.sysStateStep_C[0] == 0)
        {
            if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
            {
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
            }

            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9]);

            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep = Q12(0.0f);
            g_SysWork.sysStateStep_C[0]++;
        }

        if (D_800A9A0C != 0)
        {
            Game_StateSetNext(GameState_MapScreen);
        }
    }
}

void GameState_LoadMapScreen_Update(void) // 0x8003991C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks = 1;

        func_8003943C();
        func_80066E40();

        if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
        {
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
        }

        Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_2, &g_PaperMapImg);
        g_GameWork.gameStateStep_598[0]++;
    }

    Screen_BackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_MapScreen);
    }
}

void SysState_Fmv_Update(void) // 0x80039A58
{
    #define BASE_AUDIO_FILE_IDX FILE_XA_ZC_14392

    static RECT D_800A9A6C = { 320, 256, 160, 240 };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(false, false, false);
            D_800A9A0C                  = 0;
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                GameFs_StreamBinLoad();
                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C == 0)
    {
        return;
    }

    // Copy framebuffer into `IMAGE_BUFFER_0` before movie playback.
    DrawSync(SyncMode_Wait);
    StoreImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    func_800892A4(0);
    func_80089128();

    // Start playing movie. File to play is based on file ID `BASE_AUDIO_FILE_IDX - g_MapEventParam`.
    // Blocks until movie has finished playback or user has skipped it.
    open_main(BASE_AUDIO_FILE_IDX - g_MapEventParam, g_FileTable[BASE_AUDIO_FILE_IDX - g_MapEventParam].blockCount_0_19);

    func_800892A4(1);

    // Restore copied framebuffer from `IMAGE_BUFFER_0`.
    GsSwapDispBuff();
    LoadImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    // Set savegame flag based on `g_MapEventData->disabledEventFlag_2` flag ID.
    Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);

    // Return to game.
    Game_StateSetNext(GameState_InGame);

    // If flag is set, returns to `GameState_InGame` with `gameStateStep[0]` = 1.
    if (g_MapEventData->flags_8_13 & EventParamUnkState_1)
    {
        g_GameWork.gameStateStep_598[0] = 1;
    }
}

void SysState_LoadArea_Update(void) // 0x80039C40
{
    u32           offsetZ;
    s_MapPoint2d* mapPoint;

    g_SysWork.field_229C            = 0;
    g_SysWork.loadingScreenIdx_2281 = D_800BCDB0.loadingScreenId_4_9;
    g_SysWork.sfxPairIdx_2283       = g_MapEventData->sfxPairIdx_8_19;
    g_SysWork.field_2282            = g_MapEventData->flags_8_13;

    SD_Call(SFX_PAIRS[g_SysWork.sfxPairIdx_2283].sfx_0);

    if (g_SysWork.sfxPairIdx_2283 == SfxPairIdx_7)
    {
        D_800BCDD4            = 0;
        g_SysWork.flags_22A4 |= SysFlag2_10;
    }

    D_800BCDB0 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->eventParam_8_5];

    if (D_800BCDB0.triggerParam1_4_24 == 1)
    {
        mapPoint                = &g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->pointOfInterestIdx_5];
        offsetZ                 = g_SysWork.playerWork.player.position.vz - mapPoint->positionZ_8;
        D_800BCDB0.positionX_0 += g_SysWork.playerWork.player.position.vx - mapPoint->positionX_0;
        D_800BCDB0.positionZ_8 += offsetZ;
    }

    if (g_SysWork.sysState_8 == SysState_LoadOverlay)
    {
        g_SysWork.processFlags_2298    = SysWorkProcessFlag_OverlayTransition;
        g_SavegamePtr->mapOverlayId_A4 = g_MapEventData->mapOverlayIdx_8_25;
        GameBoot_MapLoad(g_SavegamePtr->mapOverlayId_A4);
    }
    else
    {
        g_SysWork.processFlags_2298 = SysWorkProcessFlag_RoomTransition;
        Bgm_TrackChange(g_MapEventData->mapOverlayIdx_8_25);

        if (g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->eventParam_8_5].field_4_5 != 0)
        {
            g_SysWork.field_2349 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->eventParam_8_5].field_4_5 - 1;
        }
    }

    Savegame_EventFlagSetAlt(g_MapEventData->disabledEventFlag_2);

    if (g_MapEventData->field_8_24)
    {
        g_SysWork.flags_22A4 |= SysFlag2_6;
    }
    else
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_6;
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    Game_StateSetNext(GameState_MainLoadScreen);
    Screen_BackgroundMotionBlur(SyncMode_Immediate);
}

void AreaLoad_UpdatePlayerPosition(void) // 0x80039F30
{
    Chara_PositionSet(&D_800BCDB0);
}

void AreaLoad_TransitionSound(void) // 0x80039F54
{
    SD_Call(SFX_PAIRS[g_SysWork.sfxPairIdx_2283].sfx_2);
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
            if (g_SysWork.npcs_1A0[i].model.charaId_0 >= Chara_Harry && g_SysWork.npcs_1A0[i].model.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health > Q12(0.0f))
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

    if (g_SysWork.isMgsStringSet_18 == false)
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
    save->playerPositionX_244 = g_SysWork.playerWork.player.position.vx;
    save->playerPositionZ_24C = g_SysWork.playerWork.player.position.vz;
    save->playerRotationY_248 = g_SysWork.playerWork.player.rotation.vy;
    save->playerHealth_240    = g_SysWork.playerWork.player.health;
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
    g_SysWork.playerWork.player.position.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.playerWork.player.position.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.playerWork.player.rotation.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.playerWork.player.health      = g_SavegamePtr->playerHealth_240;
}

void SysState_SaveMenu_Update(void) // 0x8003A230
{
    s32 gameState;

    func_80033548();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            SysWork_SavegameUpdatePlayer();

            if (Savegame_EventFlagGet(EventFlag_SeenSaveScreen) ||
                g_SavegamePtr->locationId_A8 == SaveLocationId_NextFear || g_MapEventParam == 0)
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

                g_SysWork.counters_1C[0] = 0;
                g_SysWork.counters_1C[1] = 0;

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

    static u8 prevTipIdx;
    u16       seenTipIdxs[1];
    s32       tipIdx;
    s32       randTipVal;
    u16*      temp_a0;

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
            prevTipIdx = tipIdx;

#if VERSION_REGION_IS(NTSC)
            Fs_QueueStartReadTim(FILE_TIM_TIPS_E01_TIM + tipIdx, FS_BUFFER_1, &g_DeathTipImg);
#elif VERSION_REGION_IS(NTSCJ)
            Fs_QueueStartReadTim(FILE_TIM_TIPS_J01_TIM + tipIdx, FS_BUFFER_1, &g_DeathTipImg);
#endif
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
            temp_a0 = &g_GameWork.config_0.seenGameOverTips_2E[(prevTipIdx >> 5)];
            *temp_a0 |= (1 << 0) << (prevTipIdx & 0x1F);

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

    #undef TIP_COUNT
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
