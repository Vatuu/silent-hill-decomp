#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/math/math.h"

const s32 rodataPad_80025EAC = 0;

static const s8 D_80025EB0[] =
{
    0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x4a, 0x16, 0x17, 0x18, 0x19, 0x20, 0x1f, 0x21,
    0x23, 0x26, 0x27, 0x28, 0x31, 0x32, 0x3f, 0x40,
    0x41, 0x42, 0x43, 0x14, 0x15, 0x1e, 0x00, 0x33,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1a, 0x1b, 0x1c, 0x1d, 0x22, 0x24, 0x25, 0x2f,
    0x2e, 0x30, 0x2d, 0x29, 0x2a, 0x2b, 0x2c, 0x00,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
    0x3c, 0x3d, 0x3e, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x0a, 0x0b, 0x0f, 0x00, 0x0c, 0x0e, 0x10, 0x0d,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x07, 0x05, 0x09, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00
};

void Game_TimerUpdate() // 0x8004C8DC
{
    #define TIME_290_HOURS        FP_TO(290 * 60 * 60, Q12_SHIFT)
    #define TIME_130_HOURS        FP_TO(130 * 60 * 60, Q12_SHIFT)
    #define TIME_290_OVERFLOW_MAX 3 // `add290Hours_25C_1` has max value of 3.

    g_SavegamePtr->gameplayTimer_250 += g_DeltaTime1;

    if (g_SavegamePtr->gameplayTimer_250 >= TIME_290_HOURS)
    {
        if (g_SavegamePtr->add290Hours_25C_1 < TIME_290_OVERFLOW_MAX)
        {
            g_SavegamePtr->add290Hours_25C_1++;
            g_SavegamePtr->gameplayTimer_250 += (UINT_MAX - TIME_290_HOURS + 1); // Wrap timer to 0 using unsigned overflow.
        }
        else
        {
            g_SavegamePtr->gameplayTimer_250 = TIME_290_HOURS - 1;
        }
    }

    if (g_SavegamePtr->add290Hours_25C_1 == TIME_290_OVERFLOW_MAX)
    {
        g_SavegamePtr->gameplayTimer_250 = CLAMP(g_SavegamePtr->gameplayTimer_250, 1, TIME_130_HOURS);
    }
}

void GameState_ItemScreens_Update() // 0x8004C9B0
{
    Gfx_StringSetColor(StringColorId_White);
    func_800363D0();

    // Update timer ff current screen is inventory.
    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        Game_TimerUpdate();
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            if (g_SavegamePtr->field_27A & 0x1F)
            {
                g_GameWork.gameStateStep_598[1] = 21;
                g_GameWork.gameStateStep_598[2] = 0;
                return;
            }

            if ((g_SavegamePtr->field_27A & (1 << 6)) &&
                g_GameWork.gameStatePrev_590 == GameState_Unk10)
            {
                g_Demo_ReproducedCount = 0;

                Game_WarmBoot();
                GameFs_StreamBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_MovieIntro);
                return;
            }

            if (Inventory_HyperBlasterUnlockTest() == 1)
            {
                Inventory_AddSpecialItem(InventoryItemId_HyperBlaster, 1);
            }

            Screen_RectInterlacedClear(0, 0x20, 0x140, 0x1C0, 0u, 0u, 0u);
            Screen_Init(0x140, 1);

            g_IntervalVBlanks    = 1;
            g_Screen_FadeStatus  = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);
            g_ScreenFadeTimestep = FP_TIME(3.0f);

            func_80037188();

            g_Inventory_IsScrolling              = true;
            g_Gfx_Inventory_SelectionBordersDraw = 0;
            D_800AE178                           = 0;
            g_Inventory_CmdSelectedIdx           = 0;
            g_Inventory_SelectedItemIdx          = g_SysWork.inventoryItemSelectedIdx_2351;

            switch (g_GameWork.gameStatePrev_590)
            {
                case 19:
                    g_Inventory_SelectionId     = InventorySelectionId_Item;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Item;
                    break;

                case 18:
                    g_Inventory_SelectionId     = InventorySelectionId_Settings;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Settings;
                    break;

                case 15:
                    g_Inventory_SelectionId     = InventorySelectionId_Map;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Map;
                    break;

                default:
                    break;
            }

            g_SysWork.player_4C.extra_128.field_28 = 0;
            g_GameWork.background2dColor_R_58C     = 0;
            g_GameWork.background2dColor_G_58D     = 0;
            g_GameWork.background2dColor_B_58E     = 0;

            Gfx_Items_RenderInit();
            func_8004EF48();

            g_GameWork.gameStateStep_598[1] = 1;
            g_GameWork.gameStateStep_598[2] = 0;
            return;

        case 1:
        case 5: // Item equip.
        case 6: // Item unequip.
        case 7:
        case 8:
        case 9:
        case 11:
        case 12:
        case 13:
        case 16:
            if (g_SysWork.inventoryItemSelectedIdx_2351 == g_Inventory_SelectedItemIdx &&
                g_GameWork.gameState_594 == GameState_InventoryScreen &&
                g_Screen_FadeStatus == SCREEN_FADE_STATUS(ScreenFadeState_None, false))
            {
                s32 prevGameState;
                prevGameState = g_GameWork.gameStateStep_598[2];

                Inventory_Logic(g_SysWork.inventoryItemSelectedIdx_2351);

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }

            Gfx_Inventory_CmdOptionsDraw();

            switch (g_GameWork.gameStateStep_598[1])
            {
                // "Can't use here" message. Triggers when attempting to use special items in places where they trigger nothing.
                case 12:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.sysStateStep_C[1]     = 3; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.sysStateStep_C[2]     = 0;
                    break;

                // "Too dark too look at the item" message. Triggers in circumstances like maps in Otherworld with the flashlight off.
                case 16:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.sysStateStep_C[1]     = 4; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.sysStateStep_C[2]     = 0;
                    break;

                default:
                    break;
            }
            break;

        case 17:
            {
                s32 prevGameState;

                prevGameState                   = g_GameWork.gameStateStep_598[2];
                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;

                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }
            break;

        case 18:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                Screen_Refresh(320, 0);
                Fs_QueueWaitForEmpty();
                func_8004C040();

                D_800AE185 = NO_VALUE;
                D_800AE186 = NO_VALUE;

                Game_StateSetNext_ClearStateSteps(GameState_OptionScreen);
                return;
            }
            break;

        case 19:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                func_8004C040();
                Game_StateSetNext(GameState_MapScreen);
                return;
            }
            break;

        // Exiting inventory screen.
        case 20:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                Screen_Refresh(320, 0);
                Inventory_ExitAnimFixes();

                g_SavegamePtr->inventorySlotCount_AB = func_8004F190(g_SavegamePtr);

                func_8003CD6C(&g_SysWork.playerCombatInfo_38);
                func_8003D01C();
                Fs_QueueWaitForEmpty();
                
                Game_StateSetNext(GameState_InGame);
                return;
            }
            break;

        // Results screen triggers here.
        case 21:
            Screen_RectInterlacedClear(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Screen_Init(0x140, 1);

            g_IntervalVBlanks                  = 1;
            g_Screen_FadeStatus                = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);
            g_ScreenFadeTimestep               = FP_TIME(3.0f);
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;
            g_Inventory_SelectionId            = InventorySelectionId_Item;

            Gfx_Items_RenderInit();
            func_8008F94C();

            D_800C3994 = g_SavegamePtr->gameDifficulty_260;

            if (g_SavegamePtr->gameDifficulty_260 <= 0)
            {
                g_SavegamePtr->gameDifficulty_260++;
            }

            Game_SavegameInitialize(0, g_SavegamePtr->gameDifficulty_260);
            func_800904F4();

            g_GameWork.gameStateStep_598[1] = 22;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 22:
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
            {
                g_GameWork.gameStateStep_598[1] = 23;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 23:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                g_Inventory_SelectionId = g_Inventory_SelectionId == 0;
                Sd_PlaySfx(Sfx_Back, 0, 64);
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                s32 prevGameState;
                g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                prevGameState       = g_GameWork.gameStateStep_598[2];

                Sd_PlaySfx(Sfx_Confirm, 0, 64);

                if (g_Inventory_SelectionId == InventorySelectionId_Item)
                {
                    GameFs_SaveLoadBinLoad();
                    g_GameWork.gameStateStep_598[1] = 24;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    g_GameWork.gameStateStep_598[1] = 25;
                    g_GameWork.gameStateStep_598[2] = 0;
                }

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }
            break;

        case 24:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                Screen_Refresh(320, 0);
                GameFs_SaveLoadBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_Unk10);
                return;
            }
            break;

        case 25:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                if (Fs_QueueDoThingWhenEmpty())
                {
                    g_Demo_ReproducedCount = 0;

                    Game_WarmBoot();
                    GameFs_StreamBinLoad();
                    Fs_QueueWaitForEmpty();
                    Game_StateSetNext(GameState_MovieIntro);
                    return;
                }
            }
            break;
    }

    Gfx_ItemScreens_RenderInit(&g_Inventory_SelectionId);

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        Gfx_Inventory_ScrollArrowsDraw(&g_Inventory_SelectionId);
    }

    if (g_GameWork.gameStateStep_598[1] >= 23)
    {
        Gfx_Results_Save();
    }
}

void Gfx_Results_Save() // 0x8004D1A0
{
    s32      i;
    s32      colorVar0;
    s32      colorVar1;
    s8       rgColor;
    LINE_F2* line;

    s_ResultStringOffset strOffsets[] = 
    {
        {   0,   0,   0,  64 },
        {   0,   0, 100,   0 },
        { 208, 144, 208,  80 },
        { 208, 144, 108, 144 },
        {   4,   8, 204,   8 },
        {   4, 136, 204, 136 },
        {   4,   8,   4, 136 },
        { 204,   8, 204, 136 },
        {   0,   1, 100,   1 },
        { 208, 143, 108, 143 },
        {   4,   7, 204,   7 },
        {   4, 137, 204, 137 },
        {   0,   0,   0,  20 },
        {   0,   0,  22,   0 },
        {  48,  48,  48,  28 },
        {  48,  48,  26,  48 },
        {   2,   4,  46,   4 },
        {   2,  44,  46,  44 },
        {   2,   4,   2,  44 },
        {  46,   4,  46,  44 },
        {   0,   1,  22,   1 },
        {  48,  47,  26,  47 },
        {   2,   3,  46,   3 },
        {   2,  45,  46,  45 }
    };

    GsOT* ot = &g_OrderingTable2[g_ActiveBufferIdx];

    char* saveDialogStrs[] =
    {
        "\x07Is_it_OK_to_save?",
        "\x07Yes_____________No"
    };
    
    for (i = 0; i < 24; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);
        
        if (i % 12 < 8) 
        {
            colorVar0  = i % 12;
            colorVar0 += ((i % 12) < 0) ? 3 : 0;
            colorVar1  = colorVar0 >> 2;
            rgColor    = FP_COLOR(0.375f) - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        } 
        else 
        {
            colorVar1 = ((i % 12) - 4) / 2;
            rgColor   = FP_COLOR(0.375f) - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        }

        if (i < 12) 
        {
            setXY2(line,
                   strOffsets[i].x0_0 + 0xFF98, strOffsets[i].y0_1 + 0xFFB8,
                   strOffsets[i].x1_2 + 0xFF98, strOffsets[i].y1_3 + 0xFFB8);
        }
        else 
        {
            setXY2(line,
                   (strOffsets[i].x0_0 + 0xFFB4) + (g_Inventory_SelectionId * 102), strOffsets[i].y0_1 + 6,
                   (strOffsets[i].x1_2 + 0xFFB4) + (g_Inventory_SelectionId * 102), strOffsets[i].y1_3 + 6);
        }

        addPrim(&ot->org[7], line);
        GsOUT_PACKET_P = (PACKET*)line + sizeof(LINE_F2);
    }

    g_SysWork.enableHighResGlyphs_2350_0 = true;

    Gfx_StringSetPosition(90, 92);
    Gfx_StringDraw("\x07Is_it_OK_to_save?", 99);

    Gfx_StringSetPosition(94, 122);
    Gfx_StringDraw("\x07Yes_____________No", 99);

    g_SysWork.enableHighResGlyphs_2350_0 = false;

    Gfx_StringSetPosition(82, 200);
    Gfx_StringDraw("NEXT_GAME_MODE", 15);

    switch (D_800C3994)
    {
        case GameDifficulty_Easy:
            Gfx_StringSetPosition(123, 240);
            Gfx_StringDraw("NORMAL", 10);
            break;

        case GameDifficulty_Normal:
        case GameDifficulty_Hard:
            Gfx_StringSetPosition(136, 240);
            Gfx_StringDraw("HARD", 10);
            break;

        default:
            break;
    }
}

void Inventory_Logic() // 0x8004D518
{
    s32 step;
    s32 cmdCountMax = 0;
    s32 temp;
    s32 curItemIdx;

    Inventory_DirectionalInputSet();

    g_Gfx_Inventory_SelectionBordersDraw++;

    if (g_Gfx_Inventory_SelectionBordersDraw >= 8)
    {
        g_Inventory_PrevSelectionId = g_Inventory_SelectionId;
    }

    g_Gfx_Inventory_SelectionBordersDraw = CLAMP(g_Gfx_Inventory_SelectionBordersDraw, 0, 8);

    if (g_GameWork.gameStateStep_598[1] != 1)
    {
        return;
    }

    if (g_Inventory_SelectionId == InventorySelectionId_Item)
    {
        if (g_Gfx_Inventory_SelectionBordersDraw <= 3)
        {
            return;
        }
    }
    else if (g_Gfx_Inventory_SelectionBordersDraw <= 7)
    {
        return;
    }

    switch (g_Inventory_SelectionId)
    {
        case InventorySelectionId_Item:
            if ((g_Inventory_IsLeftClicked && g_Gfx_Inventory_SelectionBordersDraw == 8) ||
                (g_Inventory_IsLeftHeld && (g_Inventory_IsScrolling || g_Gfx_Inventory_SelectionBordersDraw == 8)))
            {
                if (g_Inventory_IsLeftClicked || g_Inventory_IsLeftHeld)
                {
                    g_Inventory_IsScrolling = true;
                }

                D_800AE178                           = 1;
                g_Gfx_Inventory_SelectionBordersDraw = 2;
                g_Inventory_CmdSelectedIdx           = 0;
                Sd_PlaySfx(Sfx_Back, -64, 64);

                g_SysWork.inventoryItemSelectedIdx_2351 = ((g_SysWork.inventoryItemSelectedIdx_2351 + g_SavegamePtr->inventorySlotCount_AB) - 1) % g_SavegamePtr->inventorySlotCount_AB;
                temp                                    = g_SavegamePtr->inventorySlotCount_AB - 3;
                func_800539A4(0, (g_SysWork.inventoryItemSelectedIdx_2351 + temp) % g_SavegamePtr->inventorySlotCount_AB);
            }
            else if (((g_Inventory_IsRightClicked || g_Inventory_IsRightPulsed) && g_Gfx_Inventory_SelectionBordersDraw == 8) ||
                     (g_Inventory_IsRightHeld && (g_Inventory_IsScrolling || g_Gfx_Inventory_SelectionBordersDraw == 8)))
            {
                if (g_Inventory_IsRightClicked || g_Inventory_IsRightHeld)
                {
                    g_Inventory_IsScrolling = true;
                }

                D_800AE178                           = 1;
                g_Gfx_Inventory_SelectionBordersDraw = 2;
                g_Inventory_CmdSelectedIdx           = 0;
                Sd_PlaySfx(Sfx_Back, 64, 64);

                g_SysWork.inventoryItemSelectedIdx_2351 = (g_SysWork.inventoryItemSelectedIdx_2351 + 1) % g_SavegamePtr->inventorySlotCount_AB;
                func_800539A4(1, (g_SysWork.inventoryItemSelectedIdx_2351 + 3) % g_SavegamePtr->inventorySlotCount_AB);
            }
            else if (g_Inventory_IsUpClicked != InventorySelectionId_Item && g_Gfx_Inventory_SelectionBordersDraw == 8)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_KitchenKnife)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItem;
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
            }
            else if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 || g_Inventory_IsDownClicked) &&
                     g_Gfx_Inventory_SelectionBordersDraw == 8)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;

                if (g_Inventory_IsDownClicked)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0 &&
                     g_Gfx_Inventory_SelectionBordersDraw >= 8)
            {
                if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].id_0 == InventoryItemId_Flauros ||
                    (g_SysWork.field_2388.field_16 && g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].id_0 == InventoryItemId_Flashlight))
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].command_2 == InventoryCmdId_Unk10)
                {
                    g_GameWork.gameStateStep_598[1] = 12;
                    g_GameWork.gameStateStep_598[2] = 0;
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else
                {
                    g_Gfx_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx           = 0;

                    if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].command_2 != InventoryCmdId_Unk11)
                    {
                        g_Inventory_SelectionId = InventorySelectionId_ItemCmd;
                        Sd_PlaySfx(Sfx_Confirm, 64, 64);
                    }
                }
            }
            else if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16))
            {
                g_Inventory_IsScrolling = false;
            }
            else
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_EquippedItem:
            if (g_Inventory_IsDownClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                g_Inventory_CmdSelectedIdx           = 0;

                if (g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12].command_2 != InventoryCmdId_Unk11)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItemCmd;
                    Sd_PlaySfx(Sfx_Confirm, 0, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                g_Inventory_SelectionId              = InventorySelectionId_Exit;
                Sd_PlaySfx(Sfx_Cancel, 0, 64);
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Exit:
            if (g_Inventory_IsUpClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, -64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Settings;
            }
            else if (g_Inventory_IsRightClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, 64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Map;
            }
            else if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.item_16 |
                                                      (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                       g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Settings:
            if (g_Inventory_IsUpClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsRightClicked || (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;

                if (!g_Inventory_IsRightClicked || (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
                else
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_Confirm, -64, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 18;
                g_GameWork.gameStateStep_598[2] = 0;

                GameFs_OptionBinLoad();
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Map:
            if (g_Inventory_IsUpClicked)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked || g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;

                if (!g_Inventory_IsLeftClicked || g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if ((!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.isFlashlightOn_15 ||
                     (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                      !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0)))) &&
                    HAS_MAP(g_SavegamePtr->current2dMapIdx_A9))
                {
                    Sd_PlaySfx(Sfx_Confirm, 64, 64);

                    if (g_MapMarkingTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9] != NO_VALUE)
                    {
                        Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_MapMarkingTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9], FS_BUFFER_1, &g_MapMarkerAtlasImg);
                    }
                    Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9]);

                    g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                    g_GameWork.gameStateStep_598[1] = 19;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }

            if (!HAS_MAP(g_SavegamePtr->current2dMapIdx_A9))
            {
                Gfx_Inventory_UnavailableMapText(1);
            }
            else if (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1) && !g_SysWork.field_2388.isFlashlightOn_15 &&
                     (g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0) ||
                      g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0)))
            {
                Gfx_Inventory_UnavailableMapText(0);
            }
            break;

        case InventorySelectionId_ItemCmd:
        case InventorySelectionId_EquippedItemCmd:
            if (g_Inventory_SelectionId == InventorySelectionId_ItemCmd)
            {
                curItemIdx = g_SysWork.inventoryItemSelectedIdx_2351;
            }
            else
            {
                curItemIdx = g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12;
            }

            switch (g_SavegamePtr->items_0[curItemIdx].command_2)
            {
                case InventoryCmdId_UseHealth:
                case InventoryCmdId_Use:
                case InventoryCmdId_Equip:
                case InventoryCmdId_Unequip:
                case InventoryCmdId_Reload:
                case InventoryCmdId_Look:
                    cmdCountMax = 1;
                    break;

                case InventoryCmdId_EquipReload:
                case InventoryCmdId_UnequipReload:
                case InventoryCmdId_OnOff:
                case InventoryCmdId_UseLook:
                    cmdCountMax = 2;
                    break;

                case InventoryCmdId_Unk10:
                    cmdCountMax = 0;
                    break;
            }

            if (g_Inventory_IsDownPulsed)
            {
                if (g_Inventory_CmdSelectedIdx < (cmdCountMax - 1))
                {
                    g_Gfx_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx++;
                    Sd_PlaySfx(Sfx_Back, 64, 64);
                }
            }
            else if (g_Inventory_IsUpPulsed)
            {
                if (g_Inventory_CmdSelectedIdx > 0)
                {
                    g_Gfx_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx--;
                    Sd_PlaySfx(Sfx_Back, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;

                switch (g_SavegamePtr->items_0[curItemIdx].command_2)
                {
                    case InventoryCmdId_OnOff:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_Item;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_Flashlight:
                                    Game_TurnFlashlightOn();
                                    break;

                                case InventoryItemId_PocketRadio:
                                    g_SavegamePtr->flags_AC |= 1 << 0;
                                    break;
                            }
                        }
                        else
                        {
                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_Flashlight:
                                    Game_TurnFlashlightOff();
                                    break;

                                case InventoryItemId_PocketRadio:
                                    g_SavegamePtr->flags_AC &= ~(1 << 0);
                                    break;
                            }
                        }

                        g_GameWork.gameStateStep_598[1] = 1;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_UseLook:
                        if (g_Inventory_CmdSelectedIdx != 0)
                        {
                            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.isFlashlightOn_15 ||
                                (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                                 !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
                            {
                                g_Gfx_Inventory_SelectionBordersDraw = 1;
                                g_Inventory_SelectionId              = InventorySelectionId_Examine;
                                g_GameWork.gameStateStep_598[1]      = 13;
                                g_GameWork.gameStateStep_598[2]      = 0;

                                switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                                {
                                    case InventoryItemId_KeyOfLion:
                                        Fs_QueueStartReadTim(FILE_TIM_LION_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfWoodman:
                                        Fs_QueueStartReadTim(FILE_TIM_KIKORI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfScarecrow:
                                        Fs_QueueStartReadTim(FILE_TIM_KAKASHI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfOphiel:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_A_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfHagith:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_B_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfPhaleg:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_C_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfBethor:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_D_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfAratron:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_E_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KGordonKey:
                                        Fs_QueueStartReadTim(FILE_TIM_K_GORDON_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KaufmannKey:
                                        Fs_QueueStartReadTim(FILE_TIM_MOTEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_AntiqueShopKey:
                                        if (Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
                                        {
                                            g_SavegamePtr->mapMarkingFlags_1DC |= 1 << 16;
                                        }

                                        Fs_QueueStartReadTim(FILE_TIM_ANTIQUE_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_ClassroomKey:
                                        Fs_QueueStartReadTim(FILE_TIM_KEY_OF_2_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;
                                }
                            }
                            else
                            {
                                g_GameWork.gameStateStep_598[1] = 16;
                                g_GameWork.gameStateStep_598[2] = 0;
                            }
                        }
                        else
                        {
                            Inventory_ItemUse(curItemIdx);
                        }
                        break;

                    case InventoryCmdId_Look:
                        if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.isFlashlightOn_15 ||
                            (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                             !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
                        {
                            g_Gfx_Inventory_SelectionBordersDraw = 1;
                            g_Inventory_SelectionId              = InventorySelectionId_Examine;
                            g_GameWork.gameStateStep_598[1]      = 13;
                            g_GameWork.gameStateStep_598[2]      = 0;

                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_NoteToSchool:
                                    Fs_QueueStartReadTim(FILE_TIM_TOSCHOOL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InventoryItemId_NoteDoghouse:
                                    Fs_QueueStartReadTim(FILE_TIM_STKENNEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InventoryItemId_Receipt:
                                    Fs_QueueStartReadTim(FILE_TIM_RECEIPT_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;
                            }
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 16;
                            g_GameWork.gameStateStep_598[2] = 0;
                            break;
                        }
                        break;

                    case InventoryCmdId_UseHealth:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_Health;
                        g_GameWork.gameStateStep_598[1]      = 9;
                        g_GameWork.gameStateStep_598[2]      = 0;
                        break;

                    case InventoryCmdId_Use:
                        Inventory_ItemUse(curItemIdx);
                        break;

                    case InventoryCmdId_Equip:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1]      = 5;
                        g_GameWork.gameStateStep_598[2]      = 0;
                        break;

                    case InventoryCmdId_Unequip:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1]      = 6;
                        g_GameWork.gameStateStep_598[2]      = 0;
                        break;

                    case InventoryCmdId_Reload:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;

                        if (curItemIdx != g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;

                    case InventoryCmdId_EquipReload:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 5;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;

                    case InventoryCmdId_UnequipReload:
                        g_Gfx_Inventory_SelectionBordersDraw = 1;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 6;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;
                }

                if (g_GameWork.gameStateStep_598[1] == 12)
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Confirm, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                g_Inventory_CmdSelectedIdx           = 0;
                g_Inventory_SelectionId              = InventorySelectionId_Item;
                Sd_PlaySfx(Sfx_Cancel, 0, 64);
            }

            do {} while (0); // @hack Required for match.
            break;

        case InventorySelectionId_Examine:
            g_Gfx_Inventory_SelectionBordersDraw = 1;
            break;
    }
}

void Inventory_ItemUse(s32 inventoryItemIdx) // 0x8004E6D4
{
    s32 i;

    g_GameWork.gameStateStep_598[1] = 12;
    g_GameWork.gameStateStep_598[2] = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
    {
        if (Math_Distance2dCheck(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.npcs_1A0[0].position_18, FP_METER(0.7f)) == 0 &&
            ABS(g_SysWork.player_4C.chara_0.position_18.vy - g_SysWork.npcs_1A0[0].position_18.vy) < FP_METER(0.3f) &&
            g_SysWork.player_4C.extra_128.state_1C == PlayerState_None &&
            g_SavegamePtr->items_0[inventoryItemIdx].id_0 == InventoryItemId_UnknownLiquid)
        {
            g_Gfx_Inventory_SelectionBordersDraw = 1;
            g_Inventory_SelectionId              = InventorySelectionId_Item;
            g_GameWork.gameStateStep_598[1]      = 11;
            g_GameWork.gameStateStep_598[2]      = 0;

            Game_TurnFlashlightOn();
            Savegame_EventFlagSet(EventFlag_448);
        }
    }
    else
    {
        for (i = 0; D_800BCDC0[i] != NO_VALUE; i++)
        {
            if (D_800BCDC0[i] == g_SavegamePtr->items_0[inventoryItemIdx].id_0)
            {
                g_Gfx_Inventory_SelectionBordersDraw = 1;
                g_Inventory_SelectionId              = InventorySelectionId_Item;
                g_GameWork.gameStateStep_598[1]      = 11;
                g_GameWork.gameStateStep_598[2]      = 0;

                Game_TurnFlashlightOn();
                g_SysWork.player_4C.extra_128.field_28 = D_800BCDC0[i];
                break;
            }
        }
    }
}

void Gfx_Inventory_CmdOptionsDraw() // 0x8004E864
{
    GsOT*    ot;
    s32      i;
    s32      idx;
    POLY_G4* poly;
    s32      x0;
    s32      y0;

    char* strs[] = // 0x80026214
    {
        "Use",
        "Equip",
        "Unequip",
        "Reload",
        "Detail",
        "On",
        "Off",
        "Look"
    };

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        Gfx_StringSetColor(StringColorId_White);
    }
    else
    {
        Gfx_StringSetColor(StringColorId_DarkGrey);
    }

    if (g_Inventory_SelectionId != InventorySelectionId_EquippedItem &&
        g_Inventory_SelectionId != InventorySelectionId_EquippedItemCmd)
    {
        idx = g_SysWork.inventoryItemSelectedIdx_2351;
    }
    else
    {
        idx = g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12;
    }

    switch (g_SavegamePtr->items_0[idx].command_2)
    {
        case InventoryCmdId_OnOff:
            if (!g_SysWork.field_2388.field_16 || g_SavegamePtr->items_0[idx].id_0 != InventoryItemId_Flashlight)
            {
                Gfx_StringSetPosition(222, -42);
                Gfx_StringDraw(strs[5], 10);
                Gfx_StringSetPosition(222, -26);
                Gfx_StringDraw(strs[6], 10);
            }
            break;

        case InventoryCmdId_UseHealth:
        case InventoryCmdId_Use:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[0], 10);
            break;

        case InventoryCmdId_Equip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[1], 10);
            break;

        case InventoryCmdId_Unequip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[2], 10);
            break;

        case InventoryCmdId_Reload:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_UseLook:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[0], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[7], 10);
            break;

        case InventoryCmdId_EquipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[1], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_UnequipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[2], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_Look:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[7], 10);
            break;

        case 10:
        case 11:
            break;
    }

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        switch (g_SavegamePtr->items_0[idx].command_2)
        {
            case 4:
            case 5:
            case 6:
            case 9:
                y0 = -154;
                break;

            default:
                y0 = -146;
                break;
        }

        for (i = 0; i < 2; i++)
        {
            poly = (POLY_G4*)GsOUT_PACKET_P;

            x0 = 56;

            setPolyG4(poly);

            if (i != 0)
            {
                setRGB0(poly, FP_COLOR(0.0f), FP_COLOR(0.75f), FP_COLOR(0.25f));
                setRGB1(poly, FP_COLOR(0.0f), FP_COLOR(0.0f),  FP_COLOR(0.0f));
                setRGB2(poly, FP_COLOR(0.0f), FP_COLOR(0.75f), FP_COLOR(0.25f));
                setRGB3(poly, FP_COLOR(0.0f), FP_COLOR(0.0f),  FP_COLOR(0.0f));
            }
            else
            {
                setRGB0(poly, FP_COLOR(0.0f), FP_COLOR(0.0f),  FP_COLOR(0.0f));
                setRGB1(poly, FP_COLOR(0.0f), FP_COLOR(0.75f), FP_COLOR(0.25f));
                setRGB2(poly, FP_COLOR(0.0f), FP_COLOR(0.0f),  FP_COLOR(0.0f));
                setRGB3(poly, FP_COLOR(0.0f), FP_COLOR(0.75f), FP_COLOR(0.25f));
            }

            setXY4(poly,
                   x0,  (y0 + (i * 6))       + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   x0,  (y0 + ((i + 1) * 6)) + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   136, (y0 + (i * 6))       + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   136, (y0 + ((i + 1) * 6)) + ((u16)g_Inventory_CmdSelectedIdx * 16));

            addPrim(&ot->org[7], poly);
            GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_G4);
        }
    }
}

void Gfx_Inventory_ScrollArrowsDraw(s32* invSelectionId) // 0x8004EC7C
{
    #define ARROW_COUNT 4

    s32      baseColor;
    s32      i;
    s8       timeStep;
    POLY_G3* arrowPoly;
    GsOT*    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    s_Triangle2d ARROW_TRIS[] =
    {
        { { 0xFFC4, 0x000C }, { 0xFFCC, 0x0004 }, { 0xFFCC, 0x0014 } },
        { { 0xFFCC, 0x000C }, { 0xFFD4, 0x0004 }, { 0xFFD4, 0x0014 } },
        { { 0x0034, 0x000C }, { 0x002C, 0x0004 }, { 0x002C, 0x0014 } },
        { { 0x003C, 0x000C }, { 0x0034, 0x0004 }, { 0x0034, 0x0014 } },
        { { 0x0060, 0xFF53 }, { 0x0066, 0xFF60 }, { 0x005A, 0xFF60 } }, // @unused
        { { 0x0060, 0xFFA4 }, { 0x005B, 0xFF98 }, { 0x0065, 0xFF98 } }  // @unused
    };

    // Only draw arrows when item is selected.
    if (*invSelectionId != InventorySelectionId_Item) 
    {
        return;
    }

    // Draw 2 flashing left/right double arrows.
    for (i = 0; i < ARROW_COUNT; i++) 
    {
        timeStep = g_SysWork.timer_1C & 0x1F;

        arrowPoly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(arrowPoly);
        setSemiTrans(arrowPoly, 1);

        baseColor = 255 - (timeStep * 8);
        setRGB0(arrowPoly, baseColor, baseColor, baseColor);
        setRGB1(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);
        setRGB2(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);

        setXY3(arrowPoly,
               ARROW_TRIS[i].vertex0_0.vx, ARROW_TRIS[i].vertex0_0.vy,
               ARROW_TRIS[i].vertex1_4.vx, ARROW_TRIS[i].vertex1_4.vy,
               ARROW_TRIS[i].vertex2_8.vx, ARROW_TRIS[i].vertex2_8.vy);

        addPrim(&ot->org[7], arrowPoly);
        GsOUT_PACKET_P = (PACKET*)arrowPoly + sizeof(POLY_G3);
    }

    // Set texture.
    Gfx_Primitive2dTextureSet(0, 0, 7, 1);
}

bool func_8004EE94(u8 arg0, u8 arg1) // 0x8004EE94
{
    s32 i;

    for (i = 0; i < g_SavegamePtr->inventorySlotCount_AB; i++)
    {
        if (arg0 == g_SavegamePtr->items_0[i].id_0)
        {
            if (arg1 != 0)
            {
                if (arg1 == 1)
                {
                    g_SavegamePtr->items_0[i].count_1--;
                    if (!(g_SavegamePtr->items_0[i].count_1 & 0xFF))
                    {
                        g_SavegamePtr->items_0[i].id_0       = 0xFF;
                        g_SavegamePtr->inventorySlotCount_AB = func_8004F190(g_SavegamePtr);
                    }
                }
            }

            return true;
        }
    }

    return false;
}

/** Used for equipping or interacting items in the inventory.
 * Used in:
 * `GameState_ItemScreens_Update`
 * `Inventory_PlayerItemScroll`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_2", func_8004EF48); // 0x8004EF48

void func_8004F10C(s32* arg0) // 0x8004F10C
{
    s32 i;

    g_SavegamePtr->inventorySlotCount_AB = func_8004F190(g_SavegamePtr);

    for (i = *arg0; i >= 0; i--)
    {
        if (g_SavegamePtr->items_0[i].id_0 != 0xFF)
        {
            *arg0 = i;
            return;
        }
    }

    *arg0 = 0;
}

s32 func_8004F190(s_Savegame* save) // 0x8004F190
{
    s32              i;
    s32              j;
    s32              count;
    u32              id;
    s_InventoryItem  tempItem;
    s_InventoryItem* item;
    s_Savegame*      savePtr;

    savePtr = save;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        if (savePtr->items_0[i].count_1 == 0 && (savePtr->items_0[i].id_0 >> 5) != 5)
        {
            savePtr->items_0[i].id_0 = 0xFF;
        }
    }
    
    for (i = 0; i < (INVENTORY_ITEM_COUNT_MAX - 1); i++)
    {
        savePtr->items_0[i].field_3 = D_80025EB0[savePtr->items_0[i].id_0 - 32];
    }

    for (i = 0; i < (INVENTORY_ITEM_COUNT_MAX - 1); i++)
    {
        for (j = i + 1; j < INVENTORY_ITEM_COUNT_MAX; j++)
        {
            if (savePtr->items_0[i].field_3 > savePtr->items_0[j].field_3)
            {
                *(s32*)&tempItem                 = savePtr->items_0[i].id_0 +
                                                   (savePtr->items_0[i].count_1 << 8) +
                                                   (savePtr->items_0[i].command_2 << 16) +
                                                   (savePtr->items_0[i].field_3 << 24);
                *(s32*)&savePtr->items_0[i].id_0 = savePtr->items_0[j].id_0 +
                                                   (savePtr->items_0[j].count_1 << 8) +
                                                   (savePtr->items_0[j].command_2 << 16) +
                                                   (savePtr->items_0[j].field_3 << 24);
                *(s32*)&savePtr->items_0[j].id_0 = tempItem.id_0 +
                                                   (tempItem.count_1 << 8) +
                                                   (tempItem.command_2 << 16) +
                                                   (tempItem.field_3 << 24);
            }
        }
    }

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        item = &savePtr->items_0[0];

        if (item[i].id_0 != 0xFF)
        {
            if (i != 0)
            {
                savePtr->items_0[0].id_0    = savePtr->items_0[i].id_0;
                savePtr->items_0[0].count_1 = savePtr->items_0[i].count_1;
                savePtr->items_0[i].id_0    = 0xFF;
                savePtr->items_0[i].count_1 = 0;
            }

            i = 0xFF;
        }
    }

    if (i < 0xFF)
    {
        return 8;
    }

    for (i = 1; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (savePtr->items_0[i].id_0 == 0xFF)
            {
                j = i;
            }
            else 
            {
                item = &savePtr->items_0[0];
                id = item[j].id_0;
                
                if (savePtr->items_0[j].id_0 == savePtr->items_0[i].id_0)
                {
                    if ((id >> 5) == 6)
                    {
                        if ((savePtr->items_0[j].count_1 + savePtr->items_0[i].count_1) > 200)
                        {
                            savePtr->items_0[j].count_1 = 200;
                        }
                        else
                        {
                            savePtr->items_0[j].count_1 += savePtr->items_0[i].count_1;
                        }
                    }
                    else if ((id >> 5) == 1)
                    {
                        if ((savePtr->items_0[j].count_1 + savePtr->items_0[i].count_1) <= 100)
                        {
                            savePtr->items_0[j].count_1 += savePtr->items_0[i].count_1;
                        }
                        else
                        {
                            savePtr->items_0[j].count_1 = 100;
                        }
                    }

                    savePtr->items_0[i].id_0    = 0xFF;
                    savePtr->items_0[i].count_1 = 0;
                }
                else if (id == 0xFF)
                {
                    savePtr->items_0[j].id_0    = savePtr->items_0[i].id_0;
                    savePtr->items_0[j].count_1 = savePtr->items_0[i].count_1;
                    savePtr->items_0[i].id_0    = id;
                    savePtr->items_0[i].count_1 = 0;
                }
            }
        }
    }

    if (g_SavegamePtr->equippedWeapon_AA != InventoryItemId_Unequipped)
    {
        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items_0[i].id_0 == g_SavegamePtr->equippedWeapon_AA)
            {
                g_SysWork.playerCombatInfo_38.weaponInventoryIdx_12 = i;

                if (g_SavegamePtr->equippedWeapon_AA >= InventoryItemId_Handgun)
                {
                    for (j = 0; j < INVENTORY_ITEM_COUNT_MAX; j++)
                    {
                        if (g_SavegamePtr->items_0[j].id_0 == (g_SavegamePtr->items_0[i].id_0 + 32))
                        {
                            g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = g_SavegamePtr->items_0[j].count_1;
                            j                                                = INVENTORY_ITEM_COUNT_MAX + 1;
                        }
                    }

                    if (j == INVENTORY_ITEM_COUNT_MAX)
                    {
                        g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = 0;
                    }
                }

                i = INVENTORY_ITEM_COUNT_MAX;
            }
        }
    }

    for (j = 0, i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        if (g_SavegamePtr->items_0[i].id_0 != 0xFF)
        {
            j++;
        }
    }

    if (j < 8)
    {
        count = 8;
    }
    else if (j < (INVENTORY_ITEM_COUNT_MAX + 1))
    {
        count = j;
    }
    else
    {
        count = INVENTORY_ITEM_COUNT_MAX;
    }

    j = count;
    count--;

    if (count < g_SysWork.inventoryItemSelectedIdx_2351)
    {
        g_SysWork.inventoryItemSelectedIdx_2351 = count;
    }

    return j;
}

void Gfx_Inventory_UnavailableMapText(s32 strIdx) // 0x0x8004F57C
{
    char* strs[2] = // 0x800262AC
    {
        "Too_dark_to_look_at\n\t\tthe_map_here.",
        "I_don't_have_the_map\n\t\tfor_this_place."
    };

    Gfx_StringSetPosition(30, 232);
    Gfx_StringSetColor(StringColorId_White);
    Gfx_StringDraw(strs[strIdx], 99);
}

const u8 g_rodataData_800262F6 = 0x2A; // '*' as `char`.
