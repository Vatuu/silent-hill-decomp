#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/joy.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "main/fsqueue.h"
#include "screens/b_konami/b_konami.h"
#include "screens/b_konami/lzss.h"
#include "screens/stream/stream.h"

void GameState_KonamiLogo_Update(void) // 0x800C95AC
{
    while (g_GameWork.gameState_594 == GameState_KonamiLogo)
    {
        Joy_Update();

        switch (g_GameWork.gameStateStep_598[0])
        {
            case KonamiLogoStateStep_Init:
                Screen_Init(SCREEN_WIDTH * 2, true);

                ScreenFade_Start(true, true, false);
                g_ScreenFadeTimestep = Q12(0.2f);

                // Load `1ST/KONAMI2.TIM` (Konami logo).
                Fs_QueueStartReadTim(FILE_1ST_KONAMI2_TIM, FS_BUFFER_1, &g_KcetLogoImg);

                WorldGfx_HarryCharaLoad();
                GameFs_BgItemLoad();
                Map_EffectTexturesLoad(NO_VALUE);

                // Start loading `ANIM/HB_BASE.ANM` (base Harry animations).
                Fs_QueueStartRead(FILE_ANIM_HB_BASE_ANM, FS_BUFFER_0);

                g_GameWork.gameStateStep_598[0]++;
                break;

            case KonamiLogoStateStep_WaitForFade:
                if (ScreenFade_IsNone())
                {
                    g_GameWork.gameStateStep_598[0] = KonamiLogoStateStep_LogoDelay;
                }
                break;

            case KonamiLogoStateStep_LogoDelay:
                if (g_Controller0->btnsHeld_C != 0 || g_SysWork.timer_1C > 180)
                {
                    ScreenFade_Start(false, false, false);
                    g_ScreenFadeTimestep            = Q12(0.2f);
                    g_GameWork.gameStateStep_598[0] = KonamiLogoStateStep_FinishAfterFade;
                }
                break;

            case KonamiLogoStateStep_FinishAfterFade:
                if (ScreenFade_IsFinished())
                {
                    Fs_QueueWaitForEmpty();
                    Game_StateSetNext(GameState_KcetLogo);
                }
                break;
        }

        BootScreen_KonamiScreenDraw();
        Screen_FadeUpdate();
        Fs_QueueUpdate();
        MemCard_Update();
        func_80033548();
        nullsub_800334C8();
        VSync(SyncMode_Wait);
        GsSwapDispBuff();
        GsDrawOt(&g_OrderingTable2[g_ActiveBufferIdx]);

        g_ActiveBufferIdx = GsGetActiveBuff();
        GsOUT_PACKET_P   = (PACKET*)(TEMP_MEMORY_ADDR + (g_ActiveBufferIdx << 15));

        GsClearOt(0, 0, &g_OrderingTable0[g_ActiveBufferIdx]);
        GsClearOt(0, 0, &g_OrderingTable2[g_ActiveBufferIdx]);
    }
}

s32 GameState_KcetLogo_MemCardCheck(void) // 0x800C9874
{
    s32 saveEntryType0;
    s32 saveEntryType1;

    // Memory cards not ready yet, rerun this on next frame.
    if (func_80033548() == false)
    {
        return KcetLogoStateStep_CheckMemCards;
    }

    g_MemCard_ActiveSavegameEntry = (s_SaveScreenElement*)SAVEGAME_ENTRY_BUFFER_0;
    saveEntryType0                = g_MemCard_ActiveSavegameEntry->type_4;

    g_MemCard_ActiveSavegameEntry = (s_SaveScreenElement*)SAVEGAME_ENTRY_BUFFER_1;
    saveEntryType1                = g_MemCard_ActiveSavegameEntry->type_4;

    // No memory cards.
    if (saveEntryType0 == SavegameEntryType_NoMemCard && saveEntryType1 == SavegameEntryType_NoMemCard)
    {
        return KcetLogoStateStep_NoMemCard;
    }

    // No free space on any card.
    if ((saveEntryType0 == SavegameEntryType_OutOfBlocks && (saveEntryType1 == SavegameEntryType_OutOfBlocks || saveEntryType1 == SavegameEntryType_NoMemCard)) ||
        (saveEntryType0 == SavegameEntryType_NoMemCard && saveEntryType1 == SavegameEntryType_OutOfBlocks))
    {
        return KcetLogoStateStep_NoMemCardFreeSpace;
    }

    if (saveEntryType0 == SavegameEntryType_Save || saveEntryType1 == SavegameEntryType_Save)
    {
        g_MemCard_ActiveSavegameEntry = MemCard_ActiveSavegameEntryGet(g_SelectedSaveSlotIdx);
        g_MemCard_ActiveSavegameEntry = &g_MemCard_ActiveSavegameEntry[g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx]];

        g_SelectedDeviceId            = g_MemCard_ActiveSavegameEntry->deviceId_5;
        g_SelectedFileIdx             = g_MemCard_ActiveSavegameEntry->fileIdx_6;
        g_Savegame_SelectedElementIdx = g_MemCard_ActiveSavegameEntry->elementIdx_7;

        return KcetLogoStateStep_HasSavegame;
    }

    return KcetLogoStateStep_NoSaveGame;
}

void GameState_KcetLogo_Update(void) // 0x800C99A4
{
    static u8 nextGameState = GameState_Init; // 0x800CA4F0

    while (g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        Joy_Update();

        switch (g_GameWork.gameStateStep_598[0])
        {
            case KcetLogoStateStep_Init:
                Settings_RestoreDefaults();

                ScreenFade_Start(true, true, false);
                g_ScreenFadeTimestep = Q12(0.2f);

                GameFs_BgEtcGfxLoad();
                Fs_QueueStartRead(FILE_BG_HP_SAFE1_BIN, FS_BUFFER_5);
                Fs_QueueStartRead(FILE_BG_S__SAFE2_BIN, FS_BUFFER_6);
                g_GameWork.gameStateStep_598[0]++;
                break;

            case KcetLogoStateStep_CheckMemCards:
                if (ScreenFade_IsNone())
                {
                    s32 curTime;

                    Fs_QueueWaitForEmpty();

#if defined(VERSION_NTSCJ)
                    // WIP: Anti-modchip code from NTSC-J releases, not checked if matching yet.
                    // TODO:
                    // - `CdDiskReady` and `CdGetDiskType` are part of `libcd/type.o`, not included in US release, need conversion from SDK libs.
                    // - Add `FS_BUFFER_` constants for the addresses used here.
                    // - Split `SAFEx.BIN` and make function symbol for `0x801E7EB4`

                    while (CdDiskReady(false) != CdlComplete || CdGetDiskType() == CdlStatShellOpen)
                    {
                        VSync(0);
                    }

                    // Decompress the `HP_SAFE1/S__SAFE2` overlays.
                    Lzss_Init(FS_BUFFER_5, FS_BUFFER_21, 3000); // Larger than actual `HP_SAFE1` size?
                    Lzss_Decode(NO_VALUE);
                    Lzss_Init(FS_BUFFER_6, (void*)0x801E6600, 3000);
                    Lzss_Decode(NO_VALUE);

                    // Decrypt `S__SAFE2` and run `SafetyCheck`
                    Fs_DecryptOverlay((void*)0x801E7600, (void*)0x801E6600, 4096);
                    curTime = g_SysWork.timer_1C;

                    // TODO: call 0x801E7EB4 here.

                    // Decrypt `HP_SAFE1` and run `SafetyCheck` if enough time has passed.
                    Fs_DecryptOverlay((void*)0x801E7600, FS_BUFFER_21, 4096);
                    if (g_SysWork.timer_1C - curTime > 100)
                    {
                        // TODO: call 0x801E7EB4 here.
                    }

                    // Reset drive & sound driver
                    CdReset(1);
                    sd_work_init();
#endif

                    while (g_GameWork.gameStateStep_598[0] < KcetLogoStateStep_NoMemCard)
                    {
                        g_GameWork.gameStateStep_598[0] = GameState_KcetLogo_MemCardCheck();
                        MemCard_Update();
                        VSync(SyncMode_Wait);
                    }
                }
                break;

            case KcetLogoStateStep_NoMemCard:
                Fs_QueueStartReadTim(FILE_1ST_NO_MCD_E_TIM, FS_BUFFER_1, &D_800A900C);
                GameFs_StreamBinLoad();
                nextGameState = GameState_MovieIntroFadeIn;

                g_GameWork.gameStateStep_598[0] = KcetLogoStateStep_LogoDelay;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;

            case KcetLogoStateStep_NoMemCardFreeSpace:
                Fs_QueueStartReadTim(FILE_1ST_NO_BLK_E_TIM, FS_BUFFER_1, &D_800A900C);
                GameFs_StreamBinLoad();
                nextGameState = GameState_MovieIntroFadeIn;

                g_GameWork.gameStateStep_598[0] = KcetLogoStateStep_LogoDelay;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;

            case KcetLogoStateStep_NoSaveGame:
                GameFs_StreamBinLoad();
                GameFs_TitleGfxSeek();
                nextGameState = GameState_MovieIntro;

                g_GameWork.gameStateStep_598[0] = KcetLogoStateStep_LogoDelay;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;

            case KcetLogoStateStep_HasSavegame:
                while (g_GameWork.gameStateStep_598[1] < 3)
                {
                    switch (g_GameWork.gameStateStep_598[1])
                    {
                        case 0:
                            MemCard_ProcessSet(MemCardProcess_Load_Game, g_SelectedDeviceId, 0, 0);
                            g_GameWork.gameStateStep_598[2] = 0;
                            g_GameWork.gameStateStep_598[1]++;

                        case 1:
                            if (MemCard_LastMemCardResultGet() != MemCardResult_Success)
                            {
                                g_GameWork.gameStateStep_598[2] = 0;
                                g_GameWork.gameStateStep_598[1]++;
                            }
                            break;

                        case 2:
                            if (g_GameWorkConst->config_0.optAutoLoad_25)
                            {
                                Fs_QueueStartRead(FILE_VIN_SAVELOAD_BIN, FS_BUFFER_1);
                                Fs_QueueStartSeek(FILE_TIM_SAVELOAD_TIM);
                                nextGameState = GameState_AutoLoadSavegame;
                            }
                            else
                            {
                                GameFs_StreamBinLoad();
                                GameFs_TitleGfxSeek();
                                nextGameState = GameState_MovieIntro;
                            }

                            g_GameWork.gameStateStep_598[2] = 0;
                            g_GameWork.gameStateStep_598[1]++;
                            break;
                    }

                    func_80033548();
                    MemCard_Update();
                    VSync(SyncMode_Wait);
                }

                g_GameWork.gameStateStep_598[0] = KcetLogoStateStep_LogoDelay;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;

            case KcetLogoStateStep_LogoDelay:
                if (g_Controller0->btnsHeld_C != 0 || g_SysWork.timer_1C > 180)
                {
                    ScreenFade_Start(false, false, false);
                    g_ScreenFadeTimestep = Q12(0.2f);
                    g_GameWork.gameStateStep_598[0]++;
                }
                break;

            case KcetLogoStateStep_FinishAfterFade:
                if (ScreenFade_IsFinished())
                {
                    Settings_ScreenAndVolUpdate();
                    Screen_Init(SCREEN_WIDTH, false);

                    switch (nextGameState)
                    {
                        case GameState_AutoLoadSavegame:
                            Fs_QueueStartReadTim(FILE_TIM_SAVELOAD_TIM, FS_BUFFER_7, &g_ItemInspectionImg);
                            break;

                        case GameState_MovieIntroFadeIn:
                            break;

                        case GameState_MovieIntroAlternate:
                        default:
                            GameFs_TitleGfxLoad();
                            break;
                    }

                    Demo_SequenceAdvance(0);
                    Demo_DemoDataRead();
                    Fs_QueueWaitForEmpty();

                    g_SysWork.timer_1C = 0;
                    g_SysWork.timer_20 = 0;

                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;

                    SysWork_StateSetNext(SysState_Gameplay);

                    g_GameWork.gameStateStep_598[0] = g_GameWork.gameState_594;
                    g_GameWork.gameState_594        = nextGameState;
                    g_GameWork.gameStatePrev_590    = g_GameWork.gameStateStep_598[0];
                    g_GameWork.gameStateStep_598[0] = 0;
                }
                break;
        }

        BootScreen_KcetScreenDraw();
        Screen_FadeUpdate();
        Fs_QueueUpdate();
        MemCard_Update();
        func_80033548();
        nullsub_800334C8();
        VSync(SyncMode_Wait);
        GsSwapDispBuff();
        GsDrawOt(&g_OrderingTable2[g_ActiveBufferIdx]);

        g_ActiveBufferIdx = GsGetActiveBuff();
        GsOUT_PACKET_P   = (g_ActiveBufferIdx << 0xF) + (u32)TEMP_MEMORY_ADDR;

        GsClearOt(0, 0, &g_OrderingTable0[g_ActiveBufferIdx]);
        GsClearOt(0, 0, &g_OrderingTable2[g_ActiveBufferIdx]);
    }
}

void BootScreen_ImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y) // 0x800C9E6C
{
    DR_TPAGE* tPage;
    SPRT*     prim     = (SPRT*)GsOUT_PACKET_P;
    u32       vramBase = image->tPage[1] + (u32)(vramX >> 8) + (((u32)(vramY >> 8)) << 4);
    u32*      addr     = &g_OtTags0[g_ActiveBufferIdx][otz];

    addPrimFast(addr, prim, 4);
    setCodeWord(prim, PRIM_RECT | RECT_TEXTURE, 0x808080);
    setWH(prim, w, h);

    vramX = vramX & 0xFF;
    vramY = vramY & 0xFF;

    //setUV0AndClut(prim, vramX, vramY, image->clutX, image->clutY);
    *(u32*)(&prim->u0) = vramX + (vramY << 8) + (((image->clutY << 6) | ((image->clutX >> 4) & 0x3F)) << 16);

    setXY0Fast(prim, (u16)x, y);

    tPage = (DR_TPAGE*)((u8*)prim + sizeof(SPRT));
    setDrawTPage(tPage, 0, 1, getTPage(image->tPage[0], 0, (vramBase << 6), (((vramBase >> 4) & (1 << 0)) << 8)));
    AddPrim(addr, tPage);

    GsOUT_PACKET_P = (u8*)prim + 28;
}

void BootScreen_KonamiScreenDraw(void) // 0x800C9FB8
{
    s32* ptr;

    // Draw Konami logo.
    BootScreen_ImageSegmentDraw(&g_KonamiLogoImg, 0xF, 0, 0, 256, 256, -192, -192);
    BootScreen_ImageSegmentDraw(&g_KonamiLogoImg, 0xF, 256, 0, 128, 256, 64, -192);
    BootScreen_ImageSegmentDraw(&g_KonamiLogoImg, 0xF, 0, 256, 256, 128, -192, 64);
    BootScreen_ImageSegmentDraw(&g_KonamiLogoImg, 0xF, 256, 256, 128, 128, 64, 64);

    // Draw fading overlay tile.
    ptr = &g_OtTags0[g_ActiveBufferIdx][15];
    addPrimFast(ptr, (TILE*)GsOUT_PACKET_P, 3);
    setCodeWord((TILE*)GsOUT_PACKET_P, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)GsOUT_PACKET_P, -SCREEN_WIDTH, -SCREEN_HEIGHT);
    setWH((TILE*)GsOUT_PACKET_P, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
    GsOUT_PACKET_P = (PACKET*)((u8*)GsOUT_PACKET_P + sizeof(TILE));
}

void BootScreen_KcetScreenDraw(void) // 0x800CA120
{
    u32* ptr;

    // Draw KCET logo.
    BootScreen_ImageSegmentDraw(&g_KcetLogoImg, 0xF, 0, 0, 256, 160, -208, -80);
    BootScreen_ImageSegmentDraw(&g_KcetLogoImg, 0xF, 256, 0, 160, 160, 48, -80);

    // Draw fading overlay tile.
    ptr = &g_OtTags0[g_ActiveBufferIdx][15];
    addPrimFast(ptr, (TILE*)GsOUT_PACKET_P, 3);
    setCodeWord((TILE*)GsOUT_PACKET_P, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)GsOUT_PACKET_P, -SCREEN_WIDTH, -SCREEN_HEIGHT);
    setWH((TILE*)GsOUT_PACKET_P, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
    GsOUT_PACKET_P = (PACKET*)((u8*)GsOUT_PACKET_P + sizeof(TILE));
}
