#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/text/text_draw.h"
#include "main/fsqueue.h"
#include "main/rng.h"

s32 g_Demo_DemoFileIdx;

s32 g_Demo_PlayFileIdx;

s32 pad_bss_800C4848[2];

s_SaveUserConfig g_Demo_UserConfigBackup;

u32 g_Demo_PrevRandSeed;

u32 g_Demo_RandSeedBackup;

s_DemoFrameData* g_Demo_CurFrameData;

s32 g_Demo_DemoStep;

s32 g_Demo_VideoPresentInterval;

bool D_800C489C;

s32 g_Demo_DemoId = 0;
u16 g_Demo_RandSeed = 0;
// 2 bytes of padding.
s_DemoFrameData* g_Demo_PlayFileBufferPtr = (s_DemoFrameData*)0x800F5E00;

bool Demo_SequenceAdvance(s32 incrementAmt) // 0x8008EF20
{
    #define DEMO_FILE_COUNT_MAX 5

    static s_DemoFileInfo DEMO_FILE_INFOS[DEMO_FILE_COUNT_MAX] =
    {
        { FILE_MISC_DEMO0009_DAT, FILE_MISC_PLAY0009_DAT, 0 },
        { FILE_MISC_DEMO000A_DAT, FILE_MISC_PLAY000A_DAT, 0 },
        { FILE_MISC_DEMO0003_DAT, FILE_MISC_PLAY0003_DAT, 0 },
        { FILE_MISC_DEMO000B_DAT, FILE_MISC_PLAY000B_DAT, 0 },
        { FILE_MISC_DEMO0005_DAT, FILE_MISC_PLAY0005_DAT, 0 },
    };

    g_Demo_DemoId += incrementAmt;

    while (true)
    {
        // Cycle demo ID.
        while (g_Demo_DemoId < 0)
        {
            g_Demo_DemoId += DEMO_FILE_COUNT_MAX;
        }
        while ((u32)g_Demo_DemoId >= DEMO_FILE_COUNT_MAX)
        {
            g_Demo_DemoId -= DEMO_FILE_COUNT_MAX;
        }

        // Call optional funcptr associated with this demo.
        // If funcptr is set, return whether demo is eligible to play, possibly based on game progress or other conditions.
        // In retail demos this pointer is always `NULL`.
        if (DEMO_FILE_INFOS[g_Demo_DemoId].canPlayDemo_4 == NULL || DEMO_FILE_INFOS[g_Demo_DemoId].canPlayDemo_4() == 1)
        {
            break;
        }

        // If funcptr is set and returned false, skip to next demo.
        // Direction to skip depends on sign of `incrementAmt` (forward or backward).
        if (incrementAmt >= 0)
        {
            g_Demo_DemoId++;
        }
        else
        {
            g_Demo_DemoId--;
        }
    }

    g_Demo_DemoFileIdx = DEMO_FILE_INFOS[g_Demo_DemoId].demoFileId_0;
    g_Demo_PlayFileIdx = DEMO_FILE_INFOS[g_Demo_DemoId].playFileId_2;
    return true;
}

void Demo_DemoDataRead(void) // 0x8008F048
{
    if (g_Demo_DemoFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_DemoFileIdx, DEMO_WORK());
    }
}

void Demo_PlayDataRead(void) // 0x8008F07C
{
    Demo_SequenceAdvance(0);

    if (g_Demo_PlayFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_PlayFileIdx, g_Demo_PlayFileBufferPtr);
    }
}

s32 Demo_PlayFileBufferSetup(void) // 0x8008F0BC
{
    s32 mapOverlaySize;
    s32 playFileSize;

    // Get map overlay size used in demo.
    mapOverlaySize = Fs_GetFileSize(FILE_VIN_MAP0_S00_BIN + DEMO_WORK()->savegame_100.mapOverlayId_A4);

    // Get play file size, rounded up to next 0x800-byte boundary.
    playFileSize = ALIGN(Fs_GetFileSize(g_Demo_PlayFileIdx), 0x800);

    // Try placing play file buffer just before `DEMO_WORK` in memory.
    g_Demo_PlayFileBufferPtr = (void*)((s32)DEMO_WORK() - playFileSize);

    // If play file or map overlay is too large, buffer ptr may overlap with map.
    // Return 1 if buffer fits (no overlap with map overlay); otherwise, return 0.
    return ((u32)g_Demo_PlayFileBufferPtr >= (u32)(g_OvlDynamic + mapOverlaySize));
}

void Demo_DemoFileSavegameUpdate(void) // 0x8008F13C
{
    g_GameWork.savegame_30C = DEMO_WORK()->savegame_100;
}

void Demo_GameGlobalsUpdate(void) // 0x8008F1A0
{
    // Backup current user config.
    g_Demo_UserConfigBackup = g_GameWork.config_0;

    // Update `Demo_RandSeed`.
    g_Demo_RandSeed = DEMO_WORK()->randSeed_7FC;

    // Replace user config with config from demo file.
    g_GameWork.config_0 = DEMO_WORK()->config_0;

    // Restore user system settings over demo values.
    g_GameWork.config_0.optScreenPosX_1C       = g_Demo_UserConfigBackup.optScreenPosX_1C;
    g_GameWork.config_0.optScreenPosY_1D       = g_Demo_UserConfigBackup.optScreenPosY_1D;
    g_GameWork.config_0.optSoundType_1E        = g_Demo_UserConfigBackup.optSoundType_1E;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MIN;                     // Disable BGM during demo.
    g_GameWork.config_0.optVolumeSe_20         = g_Demo_UserConfigBackup.optVolumeSe_20;
    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_DISABLED;                   // Disable vibration during demo.
    g_GameWork.config_0.optBrightness_22       = g_Demo_UserConfigBackup.optBrightness_22;

    Sd_SetVolume(OPT_SOUND_VOLUME_MIN, OPT_SOUND_VOLUME_MIN, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameGlobalsRestore(void) // 0x8008F2BC
{
    g_GameWork.config_0 = g_Demo_UserConfigBackup;

    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameRandSeedUpdate(void) // 0x8008F33C
{
    g_Demo_PrevRandSeed = Rng_GetSeed();
    Rng_SetSeed(g_Demo_RandSeed);
}

void Demo_GameRandSeedRestore(void) // 0x8008F370
{
    Rng_SetSeed(g_Demo_PrevRandSeed);
}

bool g_Demo_Play = false;

void Demo_Start(void) // 0x8008F398
{
    g_Demo_Play = true;
    g_SysWork.flags_22A4 |= SysFlag2_1;

    Demo_GameGlobalsUpdate();
    Demo_GameRandSeedUpdate();

    g_GameWork.field_5A8 = 1;
    g_GameWork.field_5AC = 1;
}

void Demo_Stop(void) // 0x8008f3f0
{
    g_Demo_Play = false;
    g_SysWork.flags_22A4 &= ~SysFlag2_1;

    Demo_GameGlobalsRestore();
    Demo_GameRandSeedRestore();
}

bool Gfx_ScreenFadeIn_IsInProgress(s32 arg0)
{
    s32 screenFadeStatus;

    screenFadeStatus = arg0 & ~(1 << 0);

    switch (screenFadeStatus)
    {
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, false):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, true):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, true):
        case SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, true):
        case SCREEN_FADE_STATUS(ScreenFadeState_FadeOutComplete, true):
            return false;
    }

    return true;
}

s32 Demo_StateGet(s32 gameState)
{
    switch (gameState)
    {
        case GameState_InGame:
            if (g_SysWork.sysState_8 == SysState_GameOver)
            {
                return DemoState_Exit;
            }
            else if (g_GameWork.gameStatePrev_590 == GameState_SaveScreen)
            {
                return DemoState_Exit;
            }

        case GameState_MapEvent:
        case GameState_ExitMovie:
        case GameState_InventoryScreen:
        case GameState_MapScreen:
            return DemoState_Step;

        case GameState_OptionScreen:
            return DemoState_Step;
    }

    return DemoState_None;
}

void Demo_ExitDemo(void) // 0x8008F4E4
{
    g_Demo_FrameCount     = 999 * TICKS_PER_SECOND;
    g_Demo_CurFrameData   = NULL;
    g_Demo_DemoStep       = 0;
    g_SysWork.flags_22A4 |= SysFlag2_8;
}

void func_8008F518(void) {} // 0x8008F518

bool func_8008F520(void) // 0x8008F520
{
    return false;
}

void Demo_DemoRandSeedBackup(void) // 0x8008F528
{
    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        g_Demo_RandSeedBackup = Rng_GetSeed();
    }
}

void Demo_DemoRandSeedRestore(void) // 0x8008F560
{
    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        Rng_SetSeed(g_Demo_RandSeedBackup);
    }
}

void Demo_DemoRandSeedAdvance(void) // 0x8008F598
{
    #define SEED_OFFSET 0x3C6EF35F

    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        Rng_SetSeed(g_Demo_RandSeedBackup + SEED_OFFSET);
    }
}

bool Demo_Update(void) // 0x8008F5D8
{
    s32         prevScreenFadeCpy;
    bool        cond;
    u32         demoStep;
    s_GameWork* gameWork;

    static s32 prevScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_Reset, false);

    prevScreenFadeCpy = prevScreenFade;
    cond              = D_800C489C;
    D_800C489C        = false;
    prevScreenFade    = g_Screen_FadeStatus;

    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        g_Demo_CurFrameData = NULL;
        g_Demo_DemoStep     = 0;
        return true;
    }

    if (g_Demo_PlayFileBufferPtr == NULL)
    {
        g_Demo_CurFrameData = NULL;
        return false;
    }

    demoStep = g_Demo_DemoStep;

    if (DEMO_WORK()->frameCount_7F8 <= demoStep)
    {
        func_8008F518();
        Demo_ExitDemo();
        return false;
    }

    if (!Gfx_ScreenFadeIn_IsInProgress(prevScreenFadeCpy) || !Gfx_ScreenFadeIn_IsInProgress(g_Screen_FadeStatus) || cond)
    {
        g_Demo_CurFrameData = NULL;
        return true;
    }

    gameWork = &g_GameWork;

    // Handle demo state.
    switch (Demo_StateGet(gameWork->gameState_594))
    {
        case DemoState_Step:
            g_Demo_CurFrameData = &g_Demo_PlayFileBufferPtr[g_Demo_DemoStep];

            if (g_Demo_CurFrameData->gameStateExpected_8 != gameWork->gameState_594)
            {
                Text_Debug_PositionSet(8, 80);
                Text_Debug_Draw("STEP ERROR:[H:");
                Text_Debug_Draw(Text_Debug_IntToStringConversion(2, g_Demo_CurFrameData->gameStateExpected_8));
                Text_Debug_Draw("]/[M:");
                Text_Debug_Draw(Text_Debug_IntToStringConversion(2, gameWork->gameState_594));
                Text_Debug_Draw("]");

                g_Demo_CurFrameData = NULL;
            }

            g_Demo_DemoStep++;
            func_8008F518();
            return true;

        case DemoState_Exit:
            func_8008F518();
            Demo_ExitDemo();
            return false;

        case DemoState_None:
            break;
    }

    g_Demo_CurFrameData = NULL;
    return true;
}

const s16 unkRodata_8002B2F2 = 0x8008;

bool Demo_ControllerDataUpdate(void) // 0x8008F7CC
{
    u32 btns;

    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        return false;
    }

    btns = g_Controller0->analogController_0.digitalButtons;
    if (btns != 0xFFFF)
    {
        Demo_ExitDemo();
        return true;
    }

    g_Demo_FrameCount = 0;

    if (g_Demo_CurFrameData != NULL)
    {
        g_Controller0->analogController_0 = g_Demo_CurFrameData->analogController_0;
        return true;
    }

    *(u16*)&g_Controller0->analogController_0.status = 0x7300;
    g_Controller0->analogController_0.digitalButtons = btns;
    *(u32*)&g_Controller0->analogController_0.rightX = 0x80808080;
    return true;
}

bool Demo_PresentIntervalUpdate(void) // 0x8008F87C
{
    g_Demo_VideoPresentInterval = 1;

    if (g_Demo_CurFrameData == NULL)
    {
        return false;
    }

    g_Demo_VideoPresentInterval = g_Demo_CurFrameData->videoPresentInterval_9;
    return true;
}

bool Demo_GameRandSeedSet(void) // 0x8008F8A8
{
    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        return true;
    }
    else if (g_Demo_CurFrameData == NULL)
    {
        Rng_SetSeed(g_Demo_RandSeed);
        return false;
    }
    else
    {
        Rng_SetSeed(g_Demo_CurFrameData->randSeed_C);
        return true;
    }
}

bool func_8008F914(s32 posX, s32 posZ)
{
    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        return func_8004393C(posX, posZ);
    }

    return true;
}
