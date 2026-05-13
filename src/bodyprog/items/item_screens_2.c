#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/events_main.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/game_boot/game_boot.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/math/math.h"

static const s32 pad_rodata_80025EAC = 0;

bool g_Inventory_IsUpClicked;
bool g_Inventory_IsDownClicked;
bool g_Inventory_IsLeftClicked;
bool g_Inventory_IsRightClicked;
bool g_Inventory_IsUpPulsed;
bool g_Inventory_IsDownPulsed;
bool g_Inventory_IsLeftPulsed;
bool g_Inventory_IsRightPulsed;
bool g_Inventory_IsLeftHeld;
bool g_Inventory_IsRightHeld;
bool g_Inventory_IsScrolling;

s32 g_Inventory_GameDifficulty;
s32 g_Inventory_SelectionBordersDraw;
s32 g_Inventory_PrevSelectionId;

s32 __pad_bss_800C39A0[2];

/** Something to do with inventory items. */
static const s8 D_80025EB0[] = {
    0,  1,  2,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    74, 22, 23, 24, 25, 32, 31, 33,
    35, 38, 39, 40, 49, 50, 63, 64,
    65, 66, 67, 20, 21, 30, 0,  51,
    73, 0,  0,  0,  0,  0,  0,  0,
    26, 27, 28, 29, 34, 36, 37, 47,
    46, 48, 45, 41, 42, 43, 44, 0,
    52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 68, 69, 70, 71, 72,
    10, 11, 15, 0,  12, 14, 16, 13,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    3,  7,  5,  9,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    4,  8,  6,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    17, 18, 19, 0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  255,
    0,  0,  0,  0
};

void Game_TimerUpdate(void) // 0x8004C8DC
{
    #define TIME_290_HOURS        Q12((290.0f * 60.0f) * 60.0f)
    #define TIME_130_HOURS        Q12((130.0f * 60.0f) * 60.0f)
    #define TIME_290_OVERFLOW_MAX 3 // `add290Hours` has max value of 3.

    g_SavegamePtr->gameplayTimer += g_DeltaTimeRaw;
    if (g_SavegamePtr->gameplayTimer >= TIME_290_HOURS)
    {
        if (g_SavegamePtr->add290Hours < TIME_290_OVERFLOW_MAX)
        {
            g_SavegamePtr->add290Hours++;
            g_SavegamePtr->gameplayTimer += (UINT_MAX - TIME_290_HOURS) + 1; // Wrap timer to 0 using unsigned overflow.
        }
        else
        {
            g_SavegamePtr->gameplayTimer = TIME_290_HOURS - 1;
        }
    }

    if (g_SavegamePtr->add290Hours == TIME_290_OVERFLOW_MAX)
    {
        g_SavegamePtr->gameplayTimer = CLAMP(g_SavegamePtr->gameplayTimer, 1, TIME_130_HOURS);
    }

    #undef TIME_290_HOURS
    #undef TIME_130_HOURS
    #undef TIME_290_OVERFLOW_MAX
}

void GameState_ItemScreens_Update(void) // 0x8004C9B0
{
    Gfx_StringSetColor(StringColorId_White);
    func_800363D0();

    // Update timer if current screen is inventory.
    if (g_GameWork.gameStateSteps[1] < 21)
    {
        Game_TimerUpdate();
    }

    switch (g_GameWork.gameStateSteps[1])
    {
        case 0:
            if (g_SavegamePtr->field_27A & 0x1F)
            {
                g_GameWork.gameStateSteps[1] = 21;
                g_GameWork.gameStateSteps[2] = 0;
                return;
            }

            if ((g_SavegamePtr->field_27A & (1 << 6)) &&
                g_GameWork.gameStatePrev == GameState_SaveScreen)
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
                Inventory_AddSpecialItem(InvItemId_HyperBlaster, 1);
            }

#if VERSION_REGION_IS(NTSCJ)
            func_8004C7E4();
#endif

            Screen_RectInterlacedClear(0, 0x20, 0x140, 0x1C0, 0u, 0u, 0u);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks = 1;
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep = Q12(3.0f);

            Game_RadioSoundStop();

            g_Inventory_IsScrolling          = true;
            g_Inventory_SelectionBordersDraw = 0;
            D_800AE178                       = 0;
            g_Inventory_CmdSelectedIdx       = 0;
            g_Inventory_SelectedItemIdx      = g_SysWork.invItemSelectedIdx;

            switch (g_GameWork.gameStatePrev)
            {
                case 19:
                    g_Inventory_SelectionId     = InventorySelectionId_Item;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Item;
                    break;

                case 18:
                    g_Inventory_SelectionId     = InventorySelectionId_Settings;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Settings;
#if VERSION_EQUAL_OR_NEWER(JAP1) // @bugfix?
                    g_Inventory_IsScrolling = false;
#endif
                    break;

                case 15:
                    g_Inventory_SelectionId     = InventorySelectionId_Map;
                    g_Inventory_PrevSelectionId = InventorySelectionId_Map;
#if VERSION_EQUAL_OR_NEWER(JAP1) // @bugfix?
                    g_Inventory_IsScrolling = false;
#endif
                    break;

                default:
                    break;
            }

            g_SysWork.playerWork.extra.lastUsedItem = InvItemId_Unequipped;
            g_GameWork.background2dColor.r                = 0;
            g_GameWork.background2dColor.g                = 0;
            g_GameWork.background2dColor.b                = 0;

            Gfx_Items_DrawInit();
            func_8004EF48();

            g_GameWork.gameStateSteps[1] = 1;
            g_GameWork.gameStateSteps[2] = 0;
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
            if (g_SysWork.invItemSelectedIdx == g_Inventory_SelectedItemIdx &&
                g_GameWork.gameState == GameState_InventoryScreen &&
                ScreenFade_IsNone())
            {
                s32 prevGameState;
                prevGameState = g_GameWork.gameStateSteps[2];

                Inventory_Logic();

                g_GameWork.gameStateSteps[2] = prevGameState;
            }

            Gfx_Inventory_CmdOptionsDraw();

            switch (g_GameWork.gameStateSteps[1])
            {
                // "Can't use here" message. Triggers when attempting to use special items in places where they trigger nothing.
                case 12:
                    g_GameWork.gameStateSteps[1] = 1;
                    g_GameWork.gameStateSteps[2] = 0;
                    SysWork_StateStepSet(1, 3); // This specifically make it appear.
                    break;

                // "Too dark too look at the item" message. Triggers in circumstances like maps in Otherworld with the flashlight off.
                case 16:
                    g_GameWork.gameStateSteps[1] = 1;
                    g_GameWork.gameStateSteps[2] = 0;
                    SysWork_StateStepSet(1, 4); // This specifically make it appear.
                    break;

                default:
                    break;
            }
            break;

        case 17:
            {
                s32 prevGameState;

                prevGameState                   = g_GameWork.gameStateSteps[2];
                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;

                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = prevGameState;
            }
            break;

        case 18:
            if (ScreenFade_IsFinished())
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
            if (ScreenFade_IsFinished())
            {
                func_8004C040();
                Game_StateSetNext(GameState_MapScreen);
                return;
            }
            break;

        // Exiting inventory screen.
        case 20:
            if (ScreenFade_IsFinished())
            {
                Screen_Refresh(320, 0);
                Inventory_ExitAnimFixes();

                g_SavegamePtr->inventorySlotCount = func_8004F190(g_SavegamePtr);

                WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat);
                func_8003D01C();
                Fs_QueueWaitForEmpty();

                Game_StateSetNext(GameState_InGame);
                return;
            }
            break;

        // Results screen triggers here.
        case 21:
#if VERSION_REGION_IS(NTSCJ)
            func_8004C7E4();
#endif
            Screen_RectInterlacedClear(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks                  = 1;

            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep               = Q12(3.0f);

            g_GameWork.background2dColor.r = 0;
            g_GameWork.background2dColor.g = 0;
            g_GameWork.background2dColor.b = 0;
            g_Inventory_SelectionId            = InventorySelectionId_Item;

            Gfx_Items_DrawInit();
            func_8008F94C();

            g_Inventory_GameDifficulty = g_SavegamePtr->gameDifficulty;
            if (g_SavegamePtr->gameDifficulty <= GameDifficulty_Normal)
            {
                g_SavegamePtr->gameDifficulty++;
            }

            GameBoot_SavegameInitialize(0, g_SavegamePtr->gameDifficulty);
            func_800904F4();

#if VERSION_REGION_IS(NTSCJ)
            func_8004C870();
#endif

            g_GameWork.gameStateSteps[1] = 22;
            g_GameWork.gameStateSteps[2] = 0;
            break;

        case 22:
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.enter |
                                                 g_GameWorkPtr->config.controllerConfig.skip))
            {
                g_GameWork.gameStateSteps[1] = 23;
                g_GameWork.gameStateSteps[2] = 0;
            }
            break;

        case 23:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                g_Inventory_SelectionId = g_Inventory_SelectionId == 0;
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                s32 prevGameState;
                ScreenFade_Start(true, false, false);
                prevGameState       = g_GameWork.gameStateSteps[2];

                Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);

                if (g_Inventory_SelectionId == InventorySelectionId_Item)
                {
                    GameFs_SaveLoadBinLoad();
                    g_GameWork.gameStateSteps[1] = 24;
                    g_GameWork.gameStateSteps[2] = 0;
                }
                else
                {
                    g_GameWork.gameStateSteps[1] = 25;
                    g_GameWork.gameStateSteps[2] = 0;
                }

                g_GameWork.gameStateSteps[2] = prevGameState;
            }
            break;

        case 24:
            if (ScreenFade_IsFinished())
            {
                Screen_Refresh(320, 0);
                GameFs_SaveLoadBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_SaveScreen);
                return;
            }
            break;

        case 25:
            if (ScreenFade_IsFinished())
            {
                if (Fs_QueueChunksLoad())
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

    Gfx_ItemScreens_DrawInit(&g_Inventory_SelectionId);

    if (g_GameWork.gameStateSteps[1] < 21)
    {
        Gfx_Inventory_ScrollArrowsDraw(&g_Inventory_SelectionId);
    }

    if (g_GameWork.gameStateSteps[1] >= 23)
    {
        Gfx_Results_Save();
    }
}

void Gfx_Results_Save(void) // 0x8004D1A0
{
    s32      i;
    s32      colorVar0;
    s32      colorVar1;
    s8       rgColor;
    LINE_F2* line;

    const s_ResultStringOffset STR_OFFSETS[] =
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

#if VERSION_REGION_IS(NTSC)
    const char* SAVE_DIALOG_STRS[] = {
        "\x07Is_it_OK_to_save?",
        "\x07Yes_____________No"
    };
#endif

    for (i = 0; i < 24; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);

        if (i % 12 < 8)
        {
            colorVar0  = i % 12;
            colorVar0 += ((i % 12) < 0) ? 3 : 0;
            colorVar1  = colorVar0 >> 2;
            rgColor    = Q8_COLOR(0.375f) - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        }
        else
        {
            colorVar1 = ((i % 12) - 4) / 2;
            rgColor   = Q8_COLOR(0.375f) - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        }

        if (i < 12)
        {
            setXY2(line,
                   STR_OFFSETS[i].x0_0 + 0xFF98, STR_OFFSETS[i].y0_1 + 0xFFB8,
                   STR_OFFSETS[i].x1_2 + 0xFF98, STR_OFFSETS[i].y1_3 + 0xFFB8);
        }
        else
        {
            setXY2(line,
                   (STR_OFFSETS[i].x0_0 + 0xFFB4) + (g_Inventory_SelectionId * 102), STR_OFFSETS[i].y0_1 + 6,
                   (STR_OFFSETS[i].x1_2 + 0xFFB4) + (g_Inventory_SelectionId * 102), STR_OFFSETS[i].y1_3 + 6);
        }

        addPrim(&ot->org[7], line);
        GsOUT_PACKET_P = &line[1];
    }

#if VERSION_REGION_IS(NTSC)
    g_SysWork.enableHighResGlyphs = true;

    Gfx_StringSetPosition(90, 92);
    Gfx_StringDraw("\x07Is_it_OK_to_save?", DEFAULT_MAP_MESSAGE_LENGTH);

    Gfx_StringSetPosition(94, 122);
    Gfx_StringDraw("\x07Yes_____________No", DEFAULT_MAP_MESSAGE_LENGTH);

    g_SysWork.enableHighResGlyphs = false;

#elif VERSION_REGION_IS(NTSCJ)
    for (i = 0; i < 2; i++)
    {
        s32       isSecondLoop; // @hack?
        POLY_FT4* poly;

        isSecondLoop = i != 0;
        poly         = GsOUT_PACKET_P;

        setPolyFT4(poly);
        poly->tpage = 4;
        poly->clut  = 0x7f93;
        setRGB0(poly, 0x80, 0x80, 0x80);

        if (isSecondLoop)
        {
            setUV4(poly, 0x6c, 0x10, 0x6c, 0x20, 0xf0, 0x10, 0xf0, 0x20);
            setXY4(poly, -0x3F, 0x10, -0x3F, 0x30, 0x45, 0x10, 0x45, 0x30);
        }
        else
        {
            setUV4(poly, 0x0, 0x10, 0x0, 0x20, 0x60, 0x10, 0x60, 0x20);
            setXY4(poly, -0x30, -0x30, -0x30, -0x10, 0x30, -0x30, 0x30, -0x10);
        }

        addPrim(&ot->org[6], poly);
        GsOUT_PACKET_P = &poly[1];
    }
#endif

    Gfx_StringSetPosition(82, 200);
    Gfx_StringDraw("NEXT_GAME_MODE", 15);

    switch (g_Inventory_GameDifficulty)
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

void Inventory_Logic(void) // 0x8004D518
{
    s32 step;
    s32 cmdCountMax = 0;
    s32 temp;
    s32 curItemIdx;

    Inventory_DirectionalInputSet();

    g_Inventory_SelectionBordersDraw++;

    if (g_Inventory_SelectionBordersDraw >= 8)
    {
        g_Inventory_PrevSelectionId = g_Inventory_SelectionId;
    }

    g_Inventory_SelectionBordersDraw = CLAMP(g_Inventory_SelectionBordersDraw, 0, 8);

    if (g_GameWork.gameStateSteps[1] != 1)
    {
        return;
    }

    if (g_Inventory_SelectionId == InventorySelectionId_Item)
    {
        if (g_Inventory_SelectionBordersDraw <= 3)
        {
            return;
        }
    }
    else if (g_Inventory_SelectionBordersDraw <= 7)
    {
        return;
    }

    switch (g_Inventory_SelectionId)
    {
        case InventorySelectionId_Item:
            if ((g_Inventory_IsLeftClicked && g_Inventory_SelectionBordersDraw == 8) ||
                (g_Inventory_IsLeftHeld && (g_Inventory_IsScrolling || g_Inventory_SelectionBordersDraw == 8)))
            {
                if (g_Inventory_IsLeftClicked || g_Inventory_IsLeftHeld)
                {
                    g_Inventory_IsScrolling = true;
                }

                D_800AE178                           = 1;
                g_Inventory_SelectionBordersDraw = 2;
                g_Inventory_CmdSelectedIdx       = 0;
                Sd_PlaySfx(Sfx_MenuMove, -64, 64);

                g_SysWork.invItemSelectedIdx = ((g_SysWork.invItemSelectedIdx + g_SavegamePtr->inventorySlotCount) - 1) % g_SavegamePtr->inventorySlotCount;
                temp                                    = g_SavegamePtr->inventorySlotCount - 3;
                func_800539A4(0, (g_SysWork.invItemSelectedIdx + temp) % g_SavegamePtr->inventorySlotCount);
            }
            else if (((g_Inventory_IsRightClicked || g_Inventory_IsRightPulsed) && g_Inventory_SelectionBordersDraw == 8) ||
                     (g_Inventory_IsRightHeld && (g_Inventory_IsScrolling || g_Inventory_SelectionBordersDraw == 8)))
            {
                if (g_Inventory_IsRightClicked || g_Inventory_IsRightHeld)
                {
                    g_Inventory_IsScrolling = true;
                }

                D_800AE178                           = 1;
                g_Inventory_SelectionBordersDraw = 2;
                g_Inventory_CmdSelectedIdx           = 0;
                Sd_PlaySfx(Sfx_MenuMove, 64, 64);

                g_SysWork.invItemSelectedIdx = (g_SysWork.invItemSelectedIdx + 1) % g_SavegamePtr->inventorySlotCount;
                func_800539A4(1, (g_SysWork.invItemSelectedIdx + 3) % g_SavegamePtr->inventorySlotCount);
            }
            else if (g_Inventory_IsUpClicked != InventorySelectionId_Item && g_Inventory_SelectionBordersDraw == 8)
            {
                g_Inventory_SelectionBordersDraw = 1;

                if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap))
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItem;
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                }
            }
            else if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel ||
                      g_Inventory_IsDownClicked) &&
                     g_Inventory_SelectionBordersDraw == 8)
            {
                g_Inventory_SelectionBordersDraw = 1;

                if (g_Inventory_IsDownClicked)
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter &&
                     g_Inventory_SelectionBordersDraw >= 8)
            {
                if (g_SavegamePtr->items[g_SysWork.invItemSelectedIdx].id_0 == InvItemId_Flauros ||
                    (g_SysWork.field_2388.isFlashlightUnavailable_16 &&
                     g_SavegamePtr->items[g_SysWork.invItemSelectedIdx].id_0 == InvItemId_Flashlight))
                {
                    Sd_PlaySfx(Sfx_MenuError, 64, 64);
                }
                else if (g_SavegamePtr->items[g_SysWork.invItemSelectedIdx].command_2 == InvCmdId_Unk10)
                {
                    g_GameWork.gameStateSteps[1] = 12;
                    g_GameWork.gameStateSteps[2] = 0;
                    Sd_PlaySfx(Sfx_MenuError, 64, 64);
                }
                else
                {
                    g_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx           = 0;

                    if (g_SavegamePtr->items[g_SysWork.invItemSelectedIdx].command_2 != InvCmdId_Unk11)
                    {
                        g_Inventory_SelectionId = InventorySelectionId_ItemCmd;
                        Sd_PlaySfx(Sfx_MenuConfirm, 64, 64);
                    }
                }
            }
            else if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.item))
            {
                g_Inventory_IsScrolling = false;
            }
            else
            {
                step = g_GameWork.gameStateSteps[2];
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;
                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = step;
            }
            break;

        case InventorySelectionId_EquippedItem:
            if (g_Inventory_IsDownClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                g_Inventory_SelectionBordersDraw = 1;
                g_Inventory_CmdSelectedIdx           = 0;

                if (g_SavegamePtr->items[g_SysWork.playerCombat.weaponInventoryIdx].command_2 != InvCmdId_Unk11)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItemCmd;
                    Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel)
            {
                g_Inventory_SelectionBordersDraw = 1;
                g_Inventory_SelectionId              = InventorySelectionId_Exit;
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.item)
            {
                step = g_GameWork.gameStateSteps[2];
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;
                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = step;
            }
            break;

        case InventorySelectionId_Exit:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, -64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Settings;
            }
            else if (g_Inventory_IsRightClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, 64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Map;
            }
            else if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.item |
                                                      (g_GameWorkPtr->config.controllerConfig.enter |
                                                       g_GameWorkPtr->config.controllerConfig.cancel)))
            {
                step = g_GameWork.gameStateSteps[2];
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;
                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = step;
            }
            break;

        case InventorySelectionId_Settings:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsRightClicked ||
                     (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel))
            {
                g_Inventory_SelectionBordersDraw = 1;

                if (!g_Inventory_IsRightClicked ||
                    (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel))
                {
                    Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                Sd_PlaySfx(Sfx_MenuConfirm, -64, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 18;
                g_GameWork.gameStateSteps[2] = 0;

                GameFs_OptionBinLoad();
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.item)
            {
                step = g_GameWork.gameStateSteps[2];
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;
                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = step;
            }
            break;

        case InventorySelectionId_Map:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_SelectionBordersDraw = 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked ||
                     (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel))
            {
                g_Inventory_SelectionBordersDraw = 1;

                if (!g_Inventory_IsLeftClicked ||
                    (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel))
                {
                    Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                if ((!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ||
                     g_SysWork.field_2388.isFlashlightOn_15 ||
                     (!(g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                      !(g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))) &&
                    HAS_MAP(g_SavegamePtr->paperMapIdx))
                {
                    Sd_PlaySfx(Sfx_MenuConfirm, 64, 64);

                    if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx] != NO_VALUE)
                    {
                        Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
                    }
                    Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx]);

                    ScreenFade_Start(true, false, false);
                    g_GameWork.gameStateSteps[1] = 19;
                    g_GameWork.gameStateSteps[2] = 0;
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuError, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.item)
            {
                step = g_GameWork.gameStateSteps[2];
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateSteps[1] = 20;
                g_GameWork.gameStateSteps[2] = 0;
                GameFs_WeaponInfoUpdate();

                g_GameWork.gameStateSteps[2] = step;
            }

            if (!HAS_MAP(g_SavegamePtr->paperMapIdx))
            {
                Gfx_Inventory_UnavailableMapText(1);
            }
            else if (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1) &&
                     !g_SysWork.field_2388.isFlashlightOn_15 &&
                     (g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0) ||
                      g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
            {
                Gfx_Inventory_UnavailableMapText(0);
            }
            break;

        case InventorySelectionId_ItemCmd:
        case InventorySelectionId_EquippedItemCmd:
            if (g_Inventory_SelectionId == InventorySelectionId_ItemCmd)
            {
                curItemIdx = g_SysWork.invItemSelectedIdx;
            }
            else
            {
                curItemIdx = g_SysWork.playerCombat.weaponInventoryIdx;
            }

            switch (g_SavegamePtr->items[curItemIdx].command_2)
            {
                case InvCmdId_UseHealth:
                case InvCmdId_Use:
                case InvCmdId_Equip:
                case InvCmdId_Unequip:
                case InvCmdId_Reload:
                case InvCmdId_Look:
                    cmdCountMax = 1;
                    break;

                case InvCmdId_EquipReload:
                case InvCmdId_UnequipReload:
                case InvCmdId_OnOff:
                case InvCmdId_UseLook:
                    cmdCountMax = 2;
                    break;

                case InvCmdId_Unk10:
                    cmdCountMax = 0;
                    break;
            }

            if (g_Inventory_IsDownPulsed)
            {
                if (g_Inventory_CmdSelectedIdx < (cmdCountMax - 1))
                {
                    g_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx++;
                    Sd_PlaySfx(Sfx_MenuMove, 64, 64);
                }
            }
            else if (g_Inventory_IsUpPulsed)
            {
                if (g_Inventory_CmdSelectedIdx > 0)
                {
                    g_Inventory_SelectionBordersDraw = 1;
                    g_Inventory_CmdSelectedIdx--;
                    Sd_PlaySfx(Sfx_MenuMove, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                g_Inventory_SelectionBordersDraw = 1;

                switch (g_SavegamePtr->items[curItemIdx].command_2)
                {
                    case InvCmdId_OnOff:
                        g_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId          = InventorySelectionId_Item;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            switch (g_SavegamePtr->items[curItemIdx].id_0)
                            {
                                case InvItemId_Flashlight:
                                    Game_TurnFlashlightOn();
                                    break;

                                case InvItemId_PocketRadio:
                                    g_SavegamePtr->itemToggleFlags |= ItemToggleFlag_RadioOn;
                                    break;
                            }
                        }
                        else
                        {
                            switch (g_SavegamePtr->items[curItemIdx].id_0)
                            {
                                case InvItemId_Flashlight:
                                    Game_TurnFlashlightOff();
                                    break;

                                case InvItemId_PocketRadio:
                                    g_SavegamePtr->itemToggleFlags &= ~ItemToggleFlag_RadioOn;
                                    break;
                            }
                        }

                        g_GameWork.gameStateSteps[1] = 1;
                        g_GameWork.gameStateSteps[2] = 0;
                        break;

                    case InvCmdId_UseLook:
                        if (g_Inventory_CmdSelectedIdx != 0)
                        {
                            if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ||
                                g_SysWork.field_2388.isFlashlightOn_15 ||
                                (!(g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                                 !(g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))))
                            {
                                g_Inventory_SelectionBordersDraw = 1;
                                g_Inventory_SelectionId              = InventorySelectionId_Examine;
                                g_GameWork.gameStateSteps[1]      = 13;
                                g_GameWork.gameStateSteps[2]      = 0;

                                switch (g_SavegamePtr->items[curItemIdx].id_0)
                                {
                                    case InvItemId_KeyOfLion:
                                        Fs_QueueStartReadTim(FILE_TIM_LION_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfWoodman:
                                        Fs_QueueStartReadTim(FILE_TIM_KIKORI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfScarecrow:
                                        Fs_QueueStartReadTim(FILE_TIM_KAKASHI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfOphiel:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_A_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfHagith:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_B_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfPhaleg:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_C_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfBethor:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_D_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KeyOfAratron:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_E_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KGordonKey:
                                        Fs_QueueStartReadTim(FILE_TIM_K_GORDON_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_KaufmannKey:
                                        Fs_QueueStartReadTim(FILE_TIM_MOTEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_AntiqueShopKey:
                                        if (Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
                                        {
                                            Savegame_EventFlagSet(EventFlag_MapMark_FogCentralTown_AntiqueWholeSign);
                                        }

                                        Fs_QueueStartReadTim(FILE_TIM_ANTIQUE_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InvItemId_ClassroomKey:
                                        Fs_QueueStartReadTim(FILE_TIM_KEY_OF_2_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;
                                }
                            }
                            else
                            {
                                g_GameWork.gameStateSteps[1] = 16;
                                g_GameWork.gameStateSteps[2] = 0;
                            }
                        }
                        else
                        {
                            Inventory_ItemUse(curItemIdx);
                        }
                        break;

                    case InvCmdId_Look:
                        if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ||
                            g_SysWork.field_2388.isFlashlightOn_15 ||
                            (!(g_SysWork.field_2388.field_1C[0].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                             !(g_SysWork.field_2388.field_1C[1].effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))))
                        {
                            g_Inventory_SelectionBordersDraw = 1;
                            g_Inventory_SelectionId              = InventorySelectionId_Examine;
                            g_GameWork.gameStateSteps[1]      = 13;
                            g_GameWork.gameStateSteps[2]      = 0;

                            switch (g_SavegamePtr->items[curItemIdx].id_0)
                            {
                                case InvItemId_NoteToSchool:
                                    Fs_QueueStartReadTim(FILE_TIM_TOSCHOOL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InvItemId_NoteDoghouse:
                                    Fs_QueueStartReadTim(FILE_TIM_STKENNEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InvItemId_Receipt:
                                    Fs_QueueStartReadTim(FILE_TIM_RECEIPT_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;
                            }
                        }
                        else
                        {
                            g_GameWork.gameStateSteps[1] = 16;
                            g_GameWork.gameStateSteps[2] = 0;
                            break;
                        }
                        break;

                    case InvCmdId_UseHealth:
                        g_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_Health;
                        g_GameWork.gameStateSteps[1]      = 9;
                        g_GameWork.gameStateSteps[2]      = 0;
                        break;

                    case InvCmdId_Use:
                        Inventory_ItemUse(curItemIdx);
                        break;

                    case InvCmdId_Equip:
                        g_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateSteps[1]      = 5;
                        g_GameWork.gameStateSteps[2]      = 0;
                        break;

                    case InvCmdId_Unequip:
                        g_Inventory_SelectionBordersDraw = 1;
                        g_Inventory_SelectionId              = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateSteps[1]      = 6;
                        g_GameWork.gameStateSteps[2]      = 0;
                        break;

                    case InvCmdId_Reload:
                        g_Inventory_SelectionBordersDraw = 1;

                        if (curItemIdx != g_SysWork.playerCombat.weaponInventoryIdx)
                        {
                            g_GameWork.gameStateSteps[1] = 8;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateSteps[1] = 7;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        break;

                    case InvCmdId_EquipReload:
                        g_Inventory_SelectionBordersDraw = 1;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateSteps[1] = 5;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombat.weaponInventoryIdx)
                        {
                            g_GameWork.gameStateSteps[1] = 8;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateSteps[1] = 7;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        break;

                    case InvCmdId_UnequipReload:
                        g_Inventory_SelectionBordersDraw = 1;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateSteps[1] = 6;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombat.weaponInventoryIdx)
                        {
                            g_GameWork.gameStateSteps[1] = 8;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateSteps[1] = 7;
                            g_GameWork.gameStateSteps[2] = 0;
                        }
                        break;
                }

                if (g_GameWork.gameStateSteps[1] == 12)
                {
                    Sd_PlaySfx(Sfx_MenuError, 64, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuConfirm, 64, 64);
                }
            }
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel)
            {
                g_Inventory_SelectionBordersDraw = 1;
                g_Inventory_CmdSelectedIdx           = 0;
                g_Inventory_SelectionId              = InventorySelectionId_Item;
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
            }

            do {} while (false); // @hack Required for match.
            break;

        case InventorySelectionId_Examine:
            g_Inventory_SelectionBordersDraw = 1;
            break;
    }
}

void Inventory_ItemUse(s32 inventoryItemIdx) // 0x8004E6D4
{
    s32 i;

    // @bugfix Pre-JAP1 versions don't check which NPC the Aglaophotis is being used on, allowing for a skip by using it
    // on any NPC. JAP1 onward added an extra check before allowing it to be used.
    #if VERSION_EQUAL_OR_NEWER(JAP1)
        #define CHARA_ID_CHECK (g_SysWork.npcs[0].model.charaId == Chara_MonsterCybil)
    #else
        #define CHARA_ID_CHECK true
    #endif

    #define playerChara g_SysWork.playerWork.player
    #define playerExtra g_SysWork.playerWork.extra

    g_GameWork.gameStateSteps[1] = 12;
    g_GameWork.gameStateSteps[2] = 0;

    if (g_SavegamePtr->mapIdx == MapIdx_MAP6_S04)
    {
        if ((CHARA_ID_CHECK && !Math_Distance2dCheck(&playerChara.position, &g_SysWork.npcs[0].position, Q12(0.7f))) &&
            ABS(playerChara.position.vy - g_SysWork.npcs[0].position.vy) < Q12(0.3f) &&
            playerExtra.state == PlayerState_None &&
            g_SavegamePtr->items[inventoryItemIdx].id_0 == InvItemId_UnknownLiquid)
        {
            g_Inventory_SelectionBordersDraw = 1;
            g_Inventory_SelectionId              = InventorySelectionId_Item;
            g_GameWork.gameStateSteps[1]      = 11;
            g_GameWork.gameStateSteps[2]      = 0;

            Game_TurnFlashlightOn();
            Savegame_EventFlagSet(EventFlag_448);
        }
    }
    else
    {
        // If any active events are requesting the item ID that was used, set `extra.lastUsedItem` for
        // `Event_Update` to make use of it.
        for (i = 0; g_ItemTriggerItemIds[i] != NO_VALUE; i++)
        {
            if (g_ItemTriggerItemIds[i] == g_SavegamePtr->items[inventoryItemIdx].id_0)
            {
                g_Inventory_SelectionBordersDraw = 1;
                g_Inventory_SelectionId              = InventorySelectionId_Item;
                g_GameWork.gameStateSteps[1]      = 11;
                g_GameWork.gameStateSteps[2]      = 0;

                Game_TurnFlashlightOn();
                playerExtra.lastUsedItem = g_ItemTriggerItemIds[i];
                break;
            }
        }
    }

    #undef CHARA_ID_CHECK
    #undef playerChara
    #undef playerExtra
}

void Gfx_Inventory_CmdOptionsDraw(void) // 0x8004E864
{
    s32      i;
    s32      idx;
    s32      x0;
    s32      y0;
    GsOT*    ot;
    POLY_G4* poly;

    const char* STRS[] = {
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
        idx = g_SysWork.invItemSelectedIdx;
    }
    else
    {
        idx = g_SysWork.playerCombat.weaponInventoryIdx;
    }

    switch (g_SavegamePtr->items[idx].command_2)
    {
        case InvCmdId_OnOff:
            if (!g_SysWork.field_2388.isFlashlightUnavailable_16 ||
                g_SavegamePtr->items[idx].id_0 != InvItemId_Flashlight)
            {
                Gfx_StringSetPosition(222, -42);
                Gfx_StringDraw(STRS[5], 10);
                Gfx_StringSetPosition(222, -26);
                Gfx_StringDraw(STRS[6], 10);
            }
            break;

        case InvCmdId_UseHealth:
        case InvCmdId_Use:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(STRS[0], 10);
            break;

        case InvCmdId_Equip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(STRS[1], 10);
            break;

        case InvCmdId_Unequip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(STRS[2], 10);
            break;

        case InvCmdId_Reload:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(STRS[3], 10);
            break;

        case InvCmdId_UseLook:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(STRS[0], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(STRS[7], 10);
            break;

        case InvCmdId_EquipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(STRS[1], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(STRS[3], 10);
            break;

        case InvCmdId_UnequipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(STRS[2], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(STRS[3], 10);
            break;

        case InvCmdId_Look:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(STRS[7], 10);
            break;

        case 10:
        case 11:
            break;
    }

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        switch (g_SavegamePtr->items[idx].command_2)
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
                setRGB0(poly, Q8_COLOR(0.0f), Q8_COLOR(0.75f), Q8_COLOR(0.25f));
                setRGB1(poly, Q8_COLOR(0.0f), Q8_COLOR(0.0f),  Q8_COLOR(0.0f));
                setRGB2(poly, Q8_COLOR(0.0f), Q8_COLOR(0.75f), Q8_COLOR(0.25f));
                setRGB3(poly, Q8_COLOR(0.0f), Q8_COLOR(0.0f),  Q8_COLOR(0.0f));
            }
            else
            {
                setRGB0(poly, Q8_COLOR(0.0f), Q8_COLOR(0.0f),  Q8_COLOR(0.0f));
                setRGB1(poly, Q8_COLOR(0.0f), Q8_COLOR(0.75f), Q8_COLOR(0.25f));
                setRGB2(poly, Q8_COLOR(0.0f), Q8_COLOR(0.0f),  Q8_COLOR(0.0f));
                setRGB3(poly, Q8_COLOR(0.0f), Q8_COLOR(0.75f), Q8_COLOR(0.25f));
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
    s8       timestep;
    POLY_G3* arrowPoly;
    GsOT*    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    const s_Triangle2d ARROW_TRIS[] = {
        { { -60,  12  }, { -52,   4   }, { -52,   20  } },
        { { -52,  12  }, { -44,   4   }, { -44,   20  } },
        { {  52,  12  }, {  44,   4   }, {  44,   20  } },
        { {  60,  12  }, {  52,   4   }, {  52,   20  } },
        { {  96, -173 }, {  102, -160 }, {  90,  -160 } }, // @unused
        { {  96, -92  }, {  91,  -104 }, {  101, -104 } }  // @unused
    };

    // Only draw arrows when item is selected.
    if (*invSelectionId != InventorySelectionId_Item)
    {
        return;
    }

    // Draw 2 flashing left/right double arrows.
    for (i = 0; i < ARROW_COUNT; i++)
    {
        timestep = g_SysWork.counters_1C[0] & 0x1F;

        arrowPoly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(arrowPoly);
        setSemiTrans(arrowPoly, true);

        baseColor = 255 - (timestep * 8);
        setRGB0(arrowPoly, baseColor, baseColor, baseColor);
        setRGB1(arrowPoly, timestep * 8, timestep * 8, timestep * 8);
        setRGB2(arrowPoly, timestep * 8, timestep * 8, timestep * 8);

        setXY3(arrowPoly,
               ARROW_TRIS[i].vertex0.vx, ARROW_TRIS[i].vertex0.vy,
               ARROW_TRIS[i].vertex1.vx, ARROW_TRIS[i].vertex1.vy,
               ARROW_TRIS[i].vertex2.vx, ARROW_TRIS[i].vertex2.vy);

        addPrim(&ot->org[7], arrowPoly);
        GsOUT_PACKET_P = (PACKET*)arrowPoly + sizeof(POLY_G3);
    }

    // Set texture.
    Gfx_Primitive2dTextureSet(0, 0, 7, 1);

    #undef ARROW_COUNT
}

bool Player_ItemRemove(u8 itemId, u8 count) // 0x8004EE94
{
    s32 i;

    for (i = 0; i < g_SavegamePtr->inventorySlotCount; i++)
    {
        if (itemId != g_SavegamePtr->items[i].id_0)
        {
            continue;
        }

        switch (count)
        {
            case 0:
                break;

            case 1:
                g_SavegamePtr->items[i].count_1--;
                if (g_SavegamePtr->items[i].count_1 == 0)
                {
                    g_SavegamePtr->items[i].id_0       = InvItemId_Empty;
                    g_SavegamePtr->inventorySlotCount = func_8004F190(g_SavegamePtr);
                }
                break;
        }

        return true;
    }

    return false;
}

void func_8004EF48(void) // 0x8004EF48
{
    u8  itemIdGroup; // `e_InvItemGroup`
    u8  inventoryItemId;
    s32 i;
    s16 equippedItemId;
    s32 weaponsGroup;
    s32 ammoGroup;
    s32 reloadCmd;
    s32 hyperBlaster;
    s32 cmd;

    hyperBlaster   = InvItemId_HyperBlaster;
    reloadCmd      = InvCmdId_Reload;
    equippedItemId = g_Inventory_EquippedItem;

    for (i = 0; i < INV_ITEM_COUNT_MAX; i++)
    {
        inventoryItemId = g_SavegamePtr->items[i].id_0;

        if (inventoryItemId == (u8)InvItemId_Empty)
        {
            g_SavegamePtr->items[i].command_2 = InvCmdId_Unk11;
        }
        else if (inventoryItemId >= InvItemId_HealthDrink && inventoryItemId < InvItemId_LobbyKey)
        {
            g_SavegamePtr->items[i].command_2 = InvCmdId_UseHealth;
        }
        else if (inventoryItemId >= InvItemId_KitchenKnife && inventoryItemId < InvItemId_Flashlight)
        {
            if (inventoryItemId == equippedItemId)
            {
                itemIdGroup = INV_ITEM_GROUP(inventoryItemId);
                if (itemIdGroup == InvItemGroup_MeleeWeapons || inventoryItemId == InvItemId_HyperBlaster)
                {
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Unequip;
                }
                else
                {
                    g_SavegamePtr->items[i].command_2 = InvCmdId_UnequipReload;
                }
            }
            else
            {
                itemIdGroup = INV_ITEM_GROUP(inventoryItemId);
                if (itemIdGroup == InvItemGroup_GunAmmo)
                {
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Reload;
                    if (INV_WEAPON_AMMO_ID(equippedItemId))
                    {
                        g_SavegamePtr->items[i].command_2 = InvCmdId_Reload;
                    }
                }
                else if (itemIdGroup == InvItemGroup_GunWeapons && inventoryItemId != InvItemId_HyperBlaster)
                {
                    g_SavegamePtr->items[i].command_2 = InvCmdId_EquipReload;
                }
                else
                {
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Equip;
                }
            }
        }
        else
        {
            switch (inventoryItemId)
            {
                case InvItemId_Flashlight:
                    g_SavegamePtr->items[i].command_2 = InvCmdId_OnOff;
                    break;

                case InvItemId_PocketRadio:
                    if (g_SavegamePtr->mapIdx == MapIdx_MAP5_S00 ||
                        g_SavegamePtr->mapIdx == MapIdx_MAP6_S03)
                    {
                        g_SavegamePtr->items[i].command_2 = InvCmdId_Unk10;
                    }
                    else
                    {
                        g_SavegamePtr->items[i].command_2 = InvCmdId_OnOff;
                    }
                    break;

                case InvItemId_NoteToSchool:
                case InvItemId_NoteDoghouse:
                case InvItemId_Receipt:
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Look;
                    break;

                case InvItemId_KeyOfLion:
                case InvItemId_KeyOfWoodman:
                case InvItemId_KeyOfScarecrow:
                case InvItemId_ClassroomKey:
                case InvItemId_KGordonKey:
                case InvItemId_AntiqueShopKey:
                case InvItemId_KeyOfOphiel:
                case InvItemId_KeyOfHagith:
                case InvItemId_KeyOfPhaleg:
                case InvItemId_KeyOfBethor:
                case InvItemId_KeyOfAratron:
                case InvItemId_KaufmannKey:
                    g_SavegamePtr->items[i].command_2 = InvCmdId_UseLook;
                    break;

                case InvItemId_Flauros:
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Unk10;
                    break;

                case InvItemId_GasolineTank:
                default:
                    g_SavegamePtr->items[i].command_2 = InvCmdId_Use;
                    break;
            }
        }
    }
}

void func_8004F10C(s32* arg0) // 0x8004F10C
{
    s32 i;

    g_SavegamePtr->inventorySlotCount = func_8004F190(g_SavegamePtr);

    for (i = *arg0; i >= 0; i--)
    {
        if (g_SavegamePtr->items[i].id_0 != (u8)InvItemId_Empty)
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

    for (i = 0; i < INV_ITEM_COUNT_MAX; i++)
    {
        if (savePtr->items[i].count_1 == 0 && INV_ITEM_GROUP(savePtr->items[i].id_0) != InvItemGroup_GunWeapons)
        {
            savePtr->items[i].id_0 = 0xFF;
        }
    }

    for (i = 0; i < (INV_ITEM_COUNT_MAX - 1); i++)
    {
        savePtr->items[i].field_3 = D_80025EB0[savePtr->items[i].id_0 - InvItemId_HealthDrink];
    }

    for (i = 0; i < (INV_ITEM_COUNT_MAX - 1); i++)
    {
        for (j = i + 1; j < INV_ITEM_COUNT_MAX; j++)
        {
            if (savePtr->items[i].field_3 > savePtr->items[j].field_3)
            {
                *(s32*)&tempItem                 = savePtr->items[i].id_0 +
                                                   (savePtr->items[i].count_1 << 8) +
                                                   (savePtr->items[i].command_2 << 16) +
                                                   (savePtr->items[i].field_3 << 24);
                *(s32*)&savePtr->items[i].id_0 = savePtr->items[j].id_0 +
                                                   (savePtr->items[j].count_1 << 8) +
                                                   (savePtr->items[j].command_2 << 16) +
                                                   (savePtr->items[j].field_3 << 24);
                *(s32*)&savePtr->items[j].id_0 = tempItem.id_0 +
                                                   (tempItem.count_1 << 8) +
                                                   (tempItem.command_2 << 16) +
                                                   (tempItem.field_3 << 24);
            }
        }
    }

    for (i = 0; i < INV_ITEM_COUNT_MAX; i++)
    {
        item = &savePtr->items[0];

        if (item[i].id_0 != (u8)InvItemId_Empty)
        {
            if (i != 0)
            {
                savePtr->items[0].id_0    = savePtr->items[i].id_0;
                savePtr->items[0].count_1 = savePtr->items[i].count_1;
                savePtr->items[i].id_0    = InvItemId_Empty;
                savePtr->items[i].count_1 = 0;
            }

            i = 0xFF;
        }
    }

    if (i < 0xFF)
    {
        return 8;
    }

    for (i = 1; i < INV_ITEM_COUNT_MAX; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (savePtr->items[i].id_0 == (u8)InvItemId_Empty)
            {
                j = i;
            }
            else
            {
                item = &savePtr->items[0];
                id = item[j].id_0;

                if (savePtr->items[j].id_0 == savePtr->items[i].id_0)
                {
                    if (INV_ITEM_GROUP(id) == InvItemGroup_GunAmmo)
                    {
                        if ((savePtr->items[j].count_1 + savePtr->items[i].count_1) > 200)
                        {
                            savePtr->items[j].count_1 = 200;
                        }
                        else
                        {
                            savePtr->items[j].count_1 += savePtr->items[i].count_1;
                        }
                    }
                    else if (INV_ITEM_GROUP(id) == InvItemGroup_HealthItems)
                    {
                        if ((savePtr->items[j].count_1 + savePtr->items[i].count_1) <= 100)
                        {
                            savePtr->items[j].count_1 += savePtr->items[i].count_1;
                        }
                        else
                        {
                            savePtr->items[j].count_1 = 100;
                        }
                    }

                    savePtr->items[i].id_0    = 0xFF;
                    savePtr->items[i].count_1 = 0;
                }
                else if (id == (u8)InvItemId_Empty)
                {
                    savePtr->items[j].id_0    = savePtr->items[i].id_0;
                    savePtr->items[j].count_1 = savePtr->items[i].count_1;
                    savePtr->items[i].id_0    = id;
                    savePtr->items[i].count_1 = 0;
                }
            }
        }
    }

    if (g_SavegamePtr->equippedWeapon != InvItemId_Unequipped)
    {
        for (i = 0; i < INV_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items[i].id_0 == g_SavegamePtr->equippedWeapon)
            {
                g_SysWork.playerCombat.weaponInventoryIdx = i;

                if (g_SavegamePtr->equippedWeapon >= InvItemId_Handgun)
                {
                    for (j = 0; j < INV_ITEM_COUNT_MAX; j++)
                    {
                        if (g_SavegamePtr->items[j].id_0 == INV_WEAPON_AMMO_ID(g_SavegamePtr->items[i].id_0))
                        {
                            g_SysWork.playerCombat.totalWeaponAmmo = g_SavegamePtr->items[j].count_1;

                            j = INV_ITEM_COUNT_MAX + 1;
                        }
                    }

                    if (j == INV_ITEM_COUNT_MAX)
                    {
                        g_SysWork.playerCombat.totalWeaponAmmo = 0;
                    }
                }

                i = INV_ITEM_COUNT_MAX;
            }
        }
    }

    for (j = 0, i = 0; i < INV_ITEM_COUNT_MAX; i++)
    {
        if (g_SavegamePtr->items[i].id_0 != (u8)InvItemId_Empty)
        {
            j++;
        }
    }

    if (j < 8)
    {
        count = 8;
    }
    else if (j < (INV_ITEM_COUNT_MAX + 1))
    {
        count = j;
    }
    else
    {
        count = INV_ITEM_COUNT_MAX;
    }

    j = count;
    count--;

    if (count < g_SysWork.invItemSelectedIdx)
    {
        g_SysWork.invItemSelectedIdx = count;
    }

    return j;
}

void Gfx_Inventory_UnavailableMapText(s32 strIdx) // 0x8004F57C
{
#if VERSION_REGION_IS(NTSCJ)
    GsOT* ot;
    SPRT* sprt;

    ot   = &g_OrderingTable2[g_ActiveBufferIdx];
    sprt = GsOUT_PACKET_P;

    setSprt(sprt);

    setRGBC0(sprt, 0x80, 0x80, 0x80, 0x64);
    setXY0Fast(sprt, -120, 116);

    if (strIdx)
    {
        *(u32*)&sprt->w = 156 + (16 << 16); // setWHFast(sprt, 156, 16);
        setUV0AndClutSum(sprt, 0, 224, 0x7F93);
    }
    else
    {
        *(u32*)&sprt->w = 192 + (16 << 16); // setWHFast(sprt, 192, 16);
        setUV0AndClutSum(sprt, 0, 16, 0x7F93);
    }

    addPrim(&ot->org[6], sprt);

    GsOUT_PACKET_P = &sprt[1];

    if (strIdx)
    {
        Gfx_Primitive2dTextureSet(256, 256, 6, 1);
    }
    else
    {
        Gfx_Primitive2dTextureSet(192, 0, 6, 1);
    }
#else
    char* STRS[2] =
    {
        "Too_dark_to_look_at\n\t\tthe_map_here.",
        "I_don't_have_the_map\n\t\tfor_this_place."
    };

    Gfx_StringSetPosition(30, 232);
    Gfx_StringSetColor(StringColorId_White);
    Gfx_StringDraw(STRS[strIdx], DEFAULT_MAP_MESSAGE_LENGTH);
#endif
}

#if VERSION_IS(USA)
const u8 g_rodataData_800262F6 = 0x2A; // '*' as `char`.
#endif
