#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "main/fsqueue.h"
#include "main/rng.h"

s32 Demo_SequenceAdvance(s32 incrementAmt) // 0x8008EF20
{
    g_Demo_DemoId += incrementAmt;

    while (true)
    {
        // Cycle demo ID between 0 - `DEMO_FILE_COUNT_MAX` (5)
        while (g_Demo_DemoId < 0)
        {
            g_Demo_DemoId += DEMO_FILE_COUNT_MAX;
        }

        while ((u32)g_Demo_DemoId >= DEMO_FILE_COUNT_MAX)
        {
            g_Demo_DemoId -= DEMO_FILE_COUNT_MAX;
        }

        // Call optional funcptr associated with this demo.
        // If funcptr is set, returns whether demo is eligible to play, possibly based on game progress or other conditions.
        // In retail demos this pointer is always `NULL`.
        if (g_Demo_FileIds[g_Demo_DemoId].canPlayDemo_4 == NULL || g_Demo_FileIds[g_Demo_DemoId].canPlayDemo_4() == 1)
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

    g_Demo_DemoFileIdx = g_Demo_FileIds[g_Demo_DemoId].demoFileId_0;
    g_Demo_PlayFileIdx = g_Demo_FileIds[g_Demo_DemoId].playFileId_2;
    return 1;
}

void Demo_DemoDataRead() // 0x8008F048
{
    if (g_Demo_DemoFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_DemoFileIdx, DEMO_WORK());
    }
}

void Demo_PlayDataRead() // 0x8008F07C
{
    Demo_SequenceAdvance(0);

    if (g_Demo_PlayFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_PlayFileIdx, g_Demo_PlayFileBufferPtr);
    }
}

s32 Demo_PlayFileBufferSetup() // 0x8008F0BC
{
    s32 mapOverlaySize;
    s32 playFileSize;

    // Get map overlay size used in demo.
    mapOverlaySize = Fs_GetFileSize(FILE_VIN_MAP0_S00_BIN + DEMO_WORK()->savegame_100.mapOverlayId_A4);

    // Get play file size, rounded up to next 0x800-byte boundary.
    playFileSize = (Fs_GetFileSize(g_Demo_PlayFileIdx) + 0x7FF) & ~0x7FF;

    // Try placing play file buffer just before `DEMO_WORK` in memory.
    g_Demo_PlayFileBufferPtr = (void*)((s32)DEMO_WORK() - playFileSize);

    // If play file or map overlay is too large, buffer ptr may overlap with map.
    // Return 1 if buffer fits (no overlap with map overlay); otherwise, return 0.
    return ((u32)g_Demo_PlayFileBufferPtr >= (u32)(g_OvlDynamic + mapOverlaySize));
}

void Demo_DemoFileSavegameUpdate() // 0x8008F13C
{
    g_GameWork.savegame_30C = DEMO_WORK()->savegame_100;
}

void Demo_GameGlobalsUpdate() // 0x8008F1A0
{
    // Backup current user config.
    g_Demo_UserConfigBackup = g_GameWork.config_0;

    // Update `Demo_RandSeed`.
    g_Demo_RandSeed = DEMO_WORK()->randSeed_7FC;

    // Replace user config with config from demo file.
    g_GameWork.config_0 = DEMO_WORK()->config_0;

    // Restore users system settings over demo values.
    g_GameWork.config_0.optScreenPosX_1C       = g_Demo_UserConfigBackup.optScreenPosX_1C;
    g_GameWork.config_0.optScreenPosY_1D       = g_Demo_UserConfigBackup.optScreenPosY_1D;
    g_GameWork.config_0.optSoundType_1E        = g_Demo_UserConfigBackup.optSoundType_1E;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MIN;                     // Disable BGM during demo.
    g_GameWork.config_0.optVolumeSe_20         = g_Demo_UserConfigBackup.optVolumeSe_20;
    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_DISABLED;                   // Disable vibration during demo.
    g_GameWork.config_0.optBrightness_22       = g_Demo_UserConfigBackup.optBrightness_22;

    Sd_SetVolume(OPT_SOUND_VOLUME_MIN, OPT_SOUND_VOLUME_MIN, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameGlobalsRestore() // 0x8008F2BC
{
    g_GameWork.config_0 = g_Demo_UserConfigBackup;

    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameRandSeedUpdate() // 0x8008F33C
{
    g_Demo_PrevRandSeed = Rng_GetSeed();
    Rng_SetSeed(g_Demo_RandSeed);
}

void Demo_GameRandSeedRestore() // 0x8008F370
{
    Rng_SetSeed(g_Demo_PrevRandSeed);
}

void Demo_Start() // 0x8008F398
{
    D_800AFDEC = 1;
    g_SysWork.flags_22A4 |= 1 << 1;

    Demo_GameGlobalsUpdate();
    Demo_GameRandSeedUpdate();

    g_GameWork.field_5A8 = 1;
    g_GameWork.field_5AC = 1;
}

void Demo_Stop() // 0x8008f3f0
{
    D_800AFDEC = 0;
    g_SysWork.flags_22A4 &= ~(1 << 1);

    Demo_GameGlobalsRestore(-3);
    Demo_GameRandSeedRestore();
}

s32 func_8008F434(s32 arg0)
{
    s32 caseVar = arg0 & ~1;

    switch (caseVar)
    {
        case 2:
        case 3:
        case 4:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            return 0;

        default:
            break;
    }

    return 1;
}

s32 func_8008F470(s32 caseArg)
{
    switch (caseArg)
    {
        case 11:
            if (g_SysWork.sysState_8 == SysState_GameOver)
            {
                return -1;
            }
            else if (g_GameWork.gameStatePrev_590 == GameState_Unk10)
            {
                return -1;
            }

        case 12:
        case 13:
        case 14:
        case 15:
            return 1;

        case 18:
            return 1;

        default:
            break;
    }

    return 0;
}

void Demo_ExitDemo() // 0x8008F4E4
{
    D_800A9768 = 0xEA24;
    g_Demo_CurFrameData = NULL;
    g_Demo_DemoStep = 0;
    g_SysWork.flags_22A4 |= 1 << 8;
}

void func_8008F518() {}

s32 func_8008F520()
{
    return 0;
}

void Demo_DemoRandSeedBackup() // 0x8008F528
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        g_Demo_RandSeedBackup = Rng_GetSeed();
    }
}

void Demo_DemoRandSeedRestore() // 0x8008F560
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup);
    }
}

void Demo_DemoRandSeedAdvance() // 0x8008F598
{
    #define SEED_OFFSET 0x3C6EF35F

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup + SEED_OFFSET);
    }
}

s32 Demo_Update() // 0x8008F5D8
{
    s32               var0;
    s32               var1;
    u32               demoStep;
    s_ControllerData* cont;
    s_GameWork*       work;

    var0       = D_800AFDF0;
    var1       = D_800C489C;
    D_800C489C = 0;
    D_800AFDF0 = g_Gfx_ScreenFade;

    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        g_Demo_CurFrameData = NULL;
        g_Demo_DemoStep     = 0;
        return 1;
    }

    if (g_Demo_PlayFileBufferPtr == NULL)
    {
        g_Demo_CurFrameData = NULL;
        return 0;
    }

    demoStep = g_Demo_DemoStep;
    do {} while (0); // HACK: Required for match.
    if (D_800FE5F8 <= demoStep)
    {
        func_8008F518();
        Demo_ExitDemo();
        return 0;
    }

    if (func_8008F434(var0) == 0 || func_8008F434(g_Gfx_ScreenFade) == 0 || var1 != 0)
    {
        g_Demo_CurFrameData = NULL;
        return 1;
    }

    work = &g_GameWork;
    switch (func_8008F470(work->gameState_594))
    {
        case 1:
            g_Demo_CurFrameData = &g_Demo_PlayFileBufferPtr[g_Demo_DemoStep];
            if (g_Demo_CurFrameData->gameStateExpected_8 != work->gameState_594)
            {
                Gfx_DebugStringPosition(8, 0x50);
                Gfx_DebugStringDraw(D_8002B2D8); // "STEP ERROR:[H:"
                Gfx_DebugStringDraw(Math_IntegerToString(2, g_Demo_CurFrameData->gameStateExpected_8));
                Gfx_DebugStringDraw(D_8002B2E8); // "]/[M:"
                Gfx_DebugStringDraw(Math_IntegerToString(2, work->gameState_594));
                Gfx_DebugStringDraw(D_8002B2F0); // "]"

                g_Demo_CurFrameData = NULL;
            }

            g_Demo_DemoStep++;
            func_8008F518();
            return 1;

        case -1:
            func_8008F518();
            Demo_ExitDemo();
            return 0;

        case 0:
            break;
    }

    g_Demo_CurFrameData = NULL;
    return 1;
}

s32 Demo_ControllerDataUpdate() // 0x8008F7CC
{
    u32 btns;

    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        return 0;
    }

    btns = g_ControllerPtrConst->analogController_0.digitalButtons;
    if (btns != 0xFFFF)
    {
        Demo_ExitDemo();
        return 1;
    }

    D_800A9768 = 0; // `Demo_FrameCnt`

    if (g_Demo_CurFrameData != NULL)
    {
        g_ControllerPtrConst->analogController_0 = g_Demo_CurFrameData->analogController_0;
        return 1;
    }

    *(u16*)&g_ControllerPtrConst->analogController_0.status  = 0x7300;
    g_ControllerPtrConst->analogController_0.digitalButtons  = btns;
    *(u32*)&g_ControllerPtrConst->analogController_0.rightX = 0x80808080;
    return 1;
}

s32 Demo_PresentIntervalUpdate() // 0x8008F87C
{
    g_Demo_VideoPresentInterval = 1;

    if (g_Demo_CurFrameData == NULL)
    {
        return 0;
    }

    g_Demo_VideoPresentInterval = g_Demo_CurFrameData->videoPresentInterval_9;
    return 1;
}

s32 Demo_GameRandSeedSet() // 0x8008F8A8
{
    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        return 1;
    }
    else if (g_Demo_CurFrameData == NULL)
    {
        Rng_SetSeed(g_Demo_RandSeed);
        return 0;
    }
    else
    {
        Rng_SetSeed(g_Demo_CurFrameData->randSeed_C);
        return 1;
    }
}

s32 func_8008F914()
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        return func_8004393C();
    }

    return 1;
}
