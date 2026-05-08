#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/events/bgm_update.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/game_boot/game_boot.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player.h"
#include "bodyprog/ranking.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/text/text_draw.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// GAME INIT 1
// ========================================

static inline void Game_StateStepIncrement(void) // TODO: Move to header?
{
    s32 gameStateSteps0 = g_GameWork.gameStateSteps[0];

    g_SysWork.counters_1C[1]     = 0;
    g_GameWork.gameStateSteps[1] = 0;
    g_GameWork.gameStateSteps[2] = 0;
    g_GameWork.gameStateSteps[0] = gameStateSteps0 + 1;
}

void Anim_CharaTypeAnimInfoClear(void) // 0x800348C0
{
    bzero(&g_CharaTypeAnimInfo[1], 72);
}

void GameState_LoadScreen_Update(void) // 0x800348E8
{
    GameBoot_LoadingScreen();
    GameBoot_GameStartup();

    if (g_SysWork.flags_22A4 & UnkSysFlag_10)
    {
        D_800BCDD4++;

        if (D_800BCDD4 >= 21)
        {
            g_SysWork.flags_22A4 &= ~UnkSysFlag_10;

            SD_Call(Sfx_Unk1502);
            SD_Call(Sfx_Unk1501);
        }
    }
}

void GameBoot_GameStartup(void) // 0x80034964
{
    // It makes up to 5 attemps. If the load fails, it restarts
    // the entire process by restarting the timer used to check if a demo
    // should be triggered.
    static s32 demoLoadAttempCount;

    // Handle boot startup step.
    switch (g_GameWork.gameStateSteps[0])
    {
        case 0:
            g_IntervalVBlanks              = 1;
            g_GameWork.background2dColor.r = 0;
            g_GameWork.background2dColor.g = 0;
            g_GameWork.background2dColor.b = 0;

            if (g_SysWork.processFlags == ProcessFlag_RoomTransition)
            {
                AreaLoad_UpdatePlayerPosition();
                g_GameWork.gameStateSteps[0] = 7;
            }
            else if (g_SysWork.processFlags == ProcessFlag_BootDemo)
            {
                demoLoadAttempCount          = 0;
                g_GameWork.gameStateSteps[0] = 1;
                g_SysWork.counters_1C[1]     = 1;
            }
            else
            {
                g_GameWork.gameStateSteps[0] = 3;
            }

            SD_Call(19);
            break;

        case 1:
            if (g_SysWork.counters_1C[1] > 1200 && Fs_QueueGetLength() == 0 && !Sd_AudioStreamingCheck())
            {
                Demo_DemoFileSavegameUpdate();
                GameBoot_PlayerInit();

                if (Demo_PlayFileBufferSetup() != 0)
                {
                    GameBoot_MapLoad(g_SavegamePtr->mapIdx);

                    g_GameWork.gameStateSteps[0] = 2;
                    g_SysWork.counters_1C[1]     = 0;
                    g_GameWork.gameStateSteps[1] = 0;
                    g_GameWork.gameStateSteps[2] = 0;
                    break;
                }

                Demo_SequenceAdvance(1);
                Demo_DemoDataRead();

                demoLoadAttempCount++;
                if (demoLoadAttempCount >= 5)
                {
                    demoLoadAttempCount      = 0;
                    g_SysWork.counters_1C[1] = 0;
                    break;
                }
            }
            break;

        case 2:
            if (Fs_QueueGetLength() == 0 && !Sd_AudioStreamingCheck())
            {
                Demo_PlayDataRead();

                g_GameWork.gameStateSteps[0] = 3;
                g_SysWork.counters_1C[1]     = 0;
                g_GameWork.gameStateSteps[1] = 0;
                g_GameWork.gameStateSteps[2] = 0;
            }
            break;

        case 3:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateSteps[0] = 4;
            }
            break;

        case 4:
            if (g_SysWork.processFlags == ProcessFlag_OverlayTransition)
            {
                AreaLoad_UpdatePlayerPosition();
            }
            else if (g_SysWork.processFlags == ProcessFlag_LoadSave ||
                     g_SysWork.processFlags == ProcessFlag_Continue)
            {
                g_SysWork.loadingScreenIdx = LoadingScreenId_PlayerRun;
            }

            g_GameWork.gameStateSteps[0]++;
            break;

        case 5:
            Fs_CharaAnimDataAlloc(1, g_MapOverlayHeader.charaGroupIds[0], NULL, 0);
            Fs_CharaAnimDataAlloc(2, g_MapOverlayHeader.charaGroupIds[1], NULL, 0);
            Fs_CharaAnimDataAlloc(3, g_MapOverlayHeader.charaGroupIds[2], NULL, 0);
            WorldGfx_MapInitCharaLoad(&g_MapOverlayHeader);

            g_GameWork.gameStateSteps[0]++;

        case 6:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateSteps[0]++;
            }
            break;

        case 7:
            if (func_80039F90() & EventParamUnkState_0)
            {
                Map_WorldClear();
            }

            Ipd_PlayerChunkInit(&g_MapOverlayHeader, g_SysWork.playerWork.player.position.vx, g_SysWork.playerWork.player.position.vz);
            if (g_SysWork.processFlags == ProcessFlag_OverlayTransition)
            {
                Game_RadioSoundStop();
            }

            g_GameWork.gameStateSteps[0]++;

        case 8:
            if (Ipd_ChunkInitCheck() != false)
            {
                Game_StateStepIncrement();
            }
            break;

        case 9:
            if (!Bgm_Init())
            {
                g_GameWork.gameState = GameState_MainLoadScreen;
                Game_StateStepIncrement();
            }
            break;

        case 10:
            if (g_SysWork.processFlags == ProcessFlag_BootDemo && !(g_SysWork.flags_22A4 & UnkSysFlag_1))
            {
                Demo_Start();
                g_SysWork.flags_22A4 |= UnkSysFlag_1;
            }

            if (func_80039F90() & EventParamUnkState_2 || !Sd_AmbientSfxInit())
            {
                Game_StateStepIncrement();
            }
            break;

        case 11:
            if (g_SysWork.counters_1C[0] >= 60)
            {
                if (g_SysWork.processFlags == ProcessFlag_RoomTransition)
                {
                    GameBoot_NpcInit();
                }
                else
                {
                    GameBoot_InGameInit();
                }

                if (g_SysWork.processFlags <= (u32)ProcessFlag_OverlayTransition)
                {
                    AreaLoad_TransitionSound();
                }

                MemCard_SysDisable();
                g_GameWork.gameStateSteps[0]++;
            }
            break;

        case 12:
            if (!Sd_AudioStreamingCheck())
            {
                Game_StateSetNext(GameState_InGame);

                if (func_80039F90() & EventParamUnkState_1)
                {
                    g_GameWork.gameStateSteps[0] = 1;
                    g_Screen_FadeStatus          = SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, IS_SCREEN_FADE_WHITE(g_Screen_FadeStatus));
                }
            }
            break;

        default:
            break;
    }
}

/** @brief Initalizes drawing of a loading screen. */
static void GameBoot_LoadingScreen(void) // 0x80034E58
{
    if (g_SysWork.loadingScreenIdx != LoadingScreenId_None && g_GameWork.gameStateSteps[0] < 10)
    {
        ScreenFade_Start(false, true, false);
        g_ScreenFadeTimestep = Q12(0.8f);
        g_MapOverlayHeader.loadingScreenFuncs[g_SysWork.loadingScreenIdx]();
    }

    Screen_BackgroundMotionBlur(SyncMode_Wait2);
}

// ========================================
// NPCS INIT
// ========================================

static void GameBoot_NpcClear(void) // 0x80034EC8
{
    s32 i;

    g_SysWork.field_228C[0] = 0;
    g_SysWork.npcFlags = 0;

    bzero(g_SysWork.npcs, ARRAY_SIZE(g_SysWork.npcs) * sizeof(s_SubCharacter));

    for (i = 0; i < CHARA_GROUP_COUNT; i++)
    {
        g_SysWork.charaGroupFlags[i] = 0;
    }
}

static void GameBoot_NpcInit(void) // 0x80034F18
{
    vcSetCameraUseWarp(&g_SysWork.playerWork.player.position, g_SysWork.cameraAngleY);
    func_8005E70C();

    if (g_SysWork.field_234A)
    {
        g_MapOverlayHeader.enviromentSet(g_SysWork.field_2349, 127);
        g_MapOverlayHeader.particlesUpdate(0, g_SavegamePtr->mapIdx, 0);
    }

    GameBoot_NpcClear();
    Game_NpcRoomInitSpawn(false);
    Game_PlayerHeightUpdate();
}

// ========================================
// GAME INIT 2
// ========================================

void GameBoot_InGameInit(void) // 0x80034FB8
{
    s32 mapOvlId;

    mapOvlId = g_SavegamePtr->mapIdx;

    vcInitCamera(&g_MapOverlayHeader, &g_SysWork.playerWork.player.position);

    vcSetCameraUseWarp(&g_SysWork.playerWork.player.position, g_SysWork.cameraAngleY);
    Collision_MapTriggerZonesSet(&g_MapOverlayHeader);
    Gfx_MapEffectsSet(0);
    WorldGfx_CharaModelProcessAllLoads();
    Game_FlashlightAttributesFix();

    g_MapOverlayHeader.particlesUpdate(0, mapOvlId, NO_VALUE);

    GameBoot_NpcClear();

    g_SysWork.npcFlagsId = 5;

    func_8005E650(mapOvlId);
    func_80037124();
    func_8007E8C0();
    Game_NpcRoomInitSpawn(false);
    Game_PlayerHeightUpdate();
    Fs_CharaAnimBoneInfoUpdate();
    GameFs_WeaponInfoUpdate();
    GameFs_Tim00TIMLoad();
    Fs_QueueWaitForEmpty();
    GameFs_MapItemsModelLoad(mapOvlId);
}

void GameBoot_SavegameInitialize(s8 overlayId, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* ovlEnemyStatesPtr;

    bzero(g_SavegamePtr, sizeof(s_Savegame));

    g_SavegamePtr->mapIdx = overlayId;

    difficulty = CLAMP(difficulty, GameDifficulty_Easy, GameDifficulty_Hard);

    ovlEnemyStatesPtr = g_SavegamePtr->ovlEnemyStates;

    g_SavegamePtr->gameDifficulty = difficulty;
    g_SavegamePtr->paperMapIdx    = PaperMapIdx_OldTown;

    // Define all enemies from an overlay as alive.
    // Odd code. Possibly a hack.
    for (i = 0; i < Chara_Count; i++)
    {
        ovlEnemyStatesPtr[44] = NO_VALUE;
        ovlEnemyStatesPtr--;
    }

    Game_SavegameResetPlayer();
}

void GameBoot_PlayerInit(void) // 0x80035178
{
    WorldGfx_MapInit();
    CharaModel_AllModelsFree();
    Item_HeldItemModelFree();
    Anim_BoneInit(FS_BUFFER_0, g_SysWork.playerBoneCoords); // Load player anim file?
    WorldGfx_PlayerModelProcessLoad();

    g_SysWork.field_229C = NO_VALUE;

    if ((g_SavegamePtr->itemToggleFlags >> 1) & (1 << 0)) // `& ItemToggleFlag_FlashlightOff`
    {
        Game_TurnFlashlightOff();
    }
    else
    {
        Game_TurnFlashlightOn();
    }

    g_CharaTypeAnimInfo[0].animBufferSize2_10 = 0x2E630;
    g_CharaTypeAnimInfo[0].animBufferSize1_C  = 0x2E630;
    Game_PlayerInfoInit();
}

void GameBoot_MapLoad(s32 mapIdx) // 0x8003521C
{
    Fs_QueueStartRead(FILE_VIN_MAP0_S00_BIN + mapIdx, g_OvlDynamic);
    Map_EffectTexturesLoad(mapIdx);
    GameFs_PlayerMapAnimLoad(mapIdx);

    // If the player spawns in the map with a weapon equipped (either because it's a demo
    // or because the player saved the game with a weapon equipped), this and the next function
    // make it appear and allocate its data.
    // @note This code has some special functionallity if the player spawns without an equipped weapon.
    if (g_SysWork.processFlags & (ProcessFlag_NewGame | ProcessFlag_LoadSave |
                                   ProcessFlag_Continue | ProcessFlag_BootDemo))
    {
        WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat);
    }

    Gfx_PlayerHeldItemAttach(g_SysWork.playerCombat.weaponAttack);
}
