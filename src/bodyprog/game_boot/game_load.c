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

static inline void Game_StateStepIncrement(void) // TODO: Move to header?
{
    s32 gameStateSteps0 = g_GameWork.gameStateSteps[0];

    g_SysWork.counters_1C[1]        = 0;
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

    if (g_SysWork.flags_22A4 & SysFlag2_10)
    {
        D_800BCDD4++;

        if (D_800BCDD4 >= 21)
        {
            g_SysWork.flags_22A4 &= ~SysFlag2_10;

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

    switch (g_GameWork.gameStateSteps[0])
    {
        case 0:
            g_IntervalVBlanks                  = 1;
            g_GameWork.background2dColor.r = 0;
            g_GameWork.background2dColor.g = 0;
            g_GameWork.background2dColor.b = 0;

            if (g_SysWork.processFlags == SysWorkProcessFlag_RoomTransition)
            {
                AreaLoad_UpdatePlayerPosition();
                g_GameWork.gameStateSteps[0] = 7;
            }
            else if (g_SysWork.processFlags == SysWorkProcessFlag_BootDemo)
            {
                demoLoadAttempCount             = 0;
                g_GameWork.gameStateSteps[0] = 1;
                g_SysWork.counters_1C[1]        = 1;
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
                    GameBoot_MapLoad(g_SavegamePtr->mapOverlayId_A4);

                    g_GameWork.gameStateSteps[0] = 2;
                    g_SysWork.counters_1C[1]              = 0;
                    g_GameWork.gameStateSteps[1] = 0;
                    g_GameWork.gameStateSteps[2] = 0;
                    break;
                }

                Demo_SequenceAdvance(1);
                Demo_DemoDataRead();

                demoLoadAttempCount++;
                if (demoLoadAttempCount >= 5)
                {
                    demoLoadAttempCount = 0;
                    g_SysWork.counters_1C[1]  = 0;
                    break;
                }
            }
            break;

        case 2:
            if (Fs_QueueGetLength() == 0 && !Sd_AudioStreamingCheck())
            {
                Demo_PlayDataRead();

                g_GameWork.gameStateSteps[0] = 3;
                g_SysWork.counters_1C[1]              = 0;
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
            if (g_SysWork.processFlags == SysWorkProcessFlag_OverlayTransition)
            {
                AreaLoad_UpdatePlayerPosition();
            }
            else if (g_SysWork.processFlags == SysWorkProcessFlag_LoadSave ||
                     g_SysWork.processFlags == SysWorkProcessFlag_Continue)
            {
                g_SysWork.loadingScreenIdx = LoadingScreenId_PlayerRun;
            }

            g_GameWork.gameStateSteps[0]++;
            break;

        case 5:
            Fs_CharaAnimDataAlloc(1, g_MapOverlayHeader.charaGroupIds_248[0], NULL, 0);
            Fs_CharaAnimDataAlloc(2, g_MapOverlayHeader.charaGroupIds_248[1], NULL, 0);
            Fs_CharaAnimDataAlloc(3, g_MapOverlayHeader.charaGroupIds_248[2], NULL, 0);
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
            if (g_SysWork.processFlags == SysWorkProcessFlag_OverlayTransition)
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
            if (Bgm_Init() == 0)
            {
                g_GameWork.gameState = GameState_MainLoadScreen;
                Game_StateStepIncrement();
            }
            break;

        case 10:
            if (g_SysWork.processFlags == SysWorkProcessFlag_BootDemo && !(g_SysWork.flags_22A4 & SysFlag2_1))
            {
                Demo_Start();
                g_SysWork.flags_22A4 |= SysFlag2_1;
            }

            if (func_80039F90() & EventParamUnkState_2 || Sd_AmbientSfxInit() == 0)
            {
                Game_StateStepIncrement();
            }
            break;

        case 11:
            if (g_SysWork.counters_1C[0] >= 60)
            {
                if (g_SysWork.processFlags == SysWorkProcessFlag_RoomTransition)
                {
                    GameBoot_NpcInit();
                }
                else
                {
                    GameBoot_InGameInit();
                }

                if (g_SysWork.processFlags <= (u32)SysWorkProcessFlag_OverlayTransition)
                {
                    AreaLoad_TransitionSound();
                }

                MemCard_Disable();
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
                    g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, IS_SCREEN_FADE_WHITE(g_Screen_FadeStatus));
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
        g_MapOverlayHeader.loadingScreenFuncs_18[g_SysWork.loadingScreenIdx]();
    }

    Screen_BackgroundMotionBlur(SyncMode_Wait2);
}
