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

// ========================================
// GAME STATES UPDATERS
// ========================================

const s32 pad_rodata_800252B8 = 0;

/** @brief SFX pairs.
 *
 * @note Used when loading areas. Maybe facilitates things like the
 * opening and closing door SFX when the player moves between rooms. */
s_AreaLoadSfx const SfxPairs[25] = {
    { Sfx_Base, Sfx_Base },
    { Sfx_DoorOpen0, Sfx_DoorClose0 },
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
    { Sfx_DoorOpen0, Sfx_Base },
    { Sfx_Unk1323, Sfx_Base },
    { Sfx_Base, Sfx_Unk1324 },
    { Sfx_Unk1351, Sfx_Unk1352 },
    { Sfx_Unk1487, Sfx_Base }
};


// These are referenced by pointers at `0x800A99E8`, which are then used by `Map_WorldObjectsInit`.
// Maybe meant to be separate .c file with .h externs.
const char g_80025320[] = "SHOT_NEA";
const char g_8002532C[] = "SHELL_NE";
const char g_80025338[] = "BULLET_N";
const char g_80025344[] = "AMPULE_N";
const char g_80025350[] = "DRINK_NE";
const char g_8002535C[] = "AIDKIT_N";
const char g_80025368[] = "PAD_NEAR";

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

    if (g_SysWork.sysState_8 != SysState_Gameplay && g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
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
        g_SysWork.isMgsStringSet_18 = 0;
        g_SysStateFuncs[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime = 0;
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

        player = &g_SysWork.playerWork_4C.player_0;
        Player_Update(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        Gfx_FlashlightUpdate();

        if (g_SavegamePtr->mapOverlayId_A4 != MapOverlayId_MAP7_S03)
        {
            g_MapOverlayHeader.particlesUpdate_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();

        if (player->model_0.anim_4.flags_2 & AnimFlag_Visible)
        {
            func_8003DA9C(Chara_Harry, g_SysWork.playerBoneCoords_890, 1, g_SysWork.playerWork_4C.player_0.timer_C6, 0);
            Chara_Flag8Clear(&g_SysWork.playerWork_4C.player_0);
            Player_CombatUpdate(&g_SysWork.playerWork_4C, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.playerWork_4C.player_0);
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

    player = &g_SysWork.playerWork_4C.player_0;

    Event_Update(player->attackReceived_41 != NO_VALUE);
    Savegame_MapRoomIdxUpdate();

    switch (FP_ROUND_SCALED(player->health_B0, 10, Q12_SHIFT))
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

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
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
        g_SysWork.isMgsStringSet_18 = 0;
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
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSED", DEFAULT_MAP_MESSAGE_LENGTH);
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

    func_8008B3E4(0);

    if (g_SysWork.field_275C > Q12(256.0f))
    {
        val0        = g_SysWork.field_275C - Q12(256.0f);
        roundedVal0 = FP_ROUND_TO_ZERO(val0, Q12_SHIFT);
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), roundedVal0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
        {
            val1        = g_SysWork.field_2764 - Q12(256.0f);
            roundedVal1 = FP_ROUND_TO_ZERO(val1, Q12_SHIFT);
            func_8008B40C(roundedVal1, 0);
        }
    }
    else
    {
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), 0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
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
}

void SysState_StatusMenu_Update(void) // 0x80039568
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

void GameState_LoadStatusScreen_Update(void) // 0x800395C0
{
    s_Savegame* save;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks   = 1;
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
    u32           var1;
    s_MapPoint2d* mapPoint;

    g_SysWork.field_229C            = 0;
    g_SysWork.loadingScreenIdx_2281 = D_800BCDB0.loadingScreenId_4_9;
    g_SysWork.field_2283            = g_MapEventData->field_8_19;
    g_SysWork.field_2282            = g_MapEventData->flags_8_13;

    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_0);

    if (g_SysWork.field_2283 == 7)
    {
        D_800BCDD4            = 0;
        g_SysWork.flags_22A4 |= SysFlag2_10;
    }

    D_800BCDB0 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->eventParam_8_5];

    if (D_800BCDB0.triggerParam1_4_24 == 1)
    {
        mapPoint                = &g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventData->pointOfInterestIdx_5];
        var1                    = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
        D_800BCDB0.positionX_0 += g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
        D_800BCDB0.positionZ_8 += var1;
    }

    if (g_SysWork.sysState_8 == SysState_LoadOverlay)
    {
        g_SysWork.processFlags_2298    = SysWorkProcessFlag_OverlayTransition;
        g_SavegamePtr->mapOverlayId_A4 = g_MapEventData->mapOverlayIdx_8_25;
        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
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
