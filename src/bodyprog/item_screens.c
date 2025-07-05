#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens_system.h"
#include "bodyprog/math.h"

s32 func_8004C45C() // 0x8004C45C
{
    s32 i;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        // Already in inventory, can't add new one.
        if (g_SavegamePtr->items_0[i].id_0 == InventoryItemId_HyperBlaster)
        {
            return NO_VALUE;
        }
    }

    if (g_SavegamePtr->mapOverlayId_A4 > MapOverlayId_MAP0_S00)
    {
        // Konami gun controller connected.
        if (g_GameWork.controllers_38[1].analogController_0.status         == 0 &&
            g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
            g_GameWork.controllers_38[1].analogController_0.terminal_type  == PadTerminalType_GunControllerKonami)
        {
            return 1;
        }

        // Game completed with some condition met?
        if (g_SavegamePtr->clearGameCount_24A != 0 && (g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            return 1;
        }
    }

    return 0;
}

s32 func_8004C4F8() // 0x8004C4F8
{
    if (g_SavegamePtr->mapOverlayId_A4 > MapOverlayId_MAP0_S00)
    {
        if ((g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            // Game completed with some condition met?
            return 2;
        }

        // Returns 1 if controller port 2 has Konami gun controller connected.
        return g_GameWork.controllers_38[1].analogController_0.status         == 0 &&
               g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
               g_GameWork.controllers_38[1].analogController_0.terminal_type  == PadTerminalType_GunControllerKonami;
    }

    return 0;
}

u32 func_8004C54C() // 0x8004C54C
{
    return g_SavegamePtr->hyperBlasterFlags_25C_3 >> 3;
}

void func_8004C564(u8 arg0, s32 arg1) // 0x8004C564
{
    s32 temp_v1;
    s8  temp_a1;

    temp_a1 = arg1 + 1;
    switch (temp_a1)
    {
        case 0:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3963 = 0;
            D_800C3961 = 32;

            func_8008B398();
            g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
            break;

        case 1:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3961 = 32;

            func_8008B438(arg0 != (1 << 1), 32, 0);
            func_8008B3E4(0);

            if (arg0 != (1 << 1))
            {
                D_800C3963 |= 1 << 0;
            }
            else
            {
                D_800C3963 |= 1 << 1;
            }
            break;

        case 2:
            if (arg0 == (1 << 1))
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
                D_800C3963 |= 1 << 2;
            }
            break;

        case 3:
            if (D_800C3961 != 0)
            {
                D_800C3961 -= ((g_DeltaTime0 / 68) == 0) ? 1 : (g_DeltaTime0 / 68);
                D_800C3962  = D_800C3961 - 32;
                D_800C3961  = CLAMP(D_800C3961, 0, 32);

                func_8008B438(arg0 != 2, 0, 0);
                func_8008B3E4(NO_VALUE);

                if (arg0 == 2)
                {
                    func_8008B40C((u8)D_800C3961, D_800C3962);
                }

                if (D_800C3961 == 0)
                {
                    func_8008B398();
                    D_800C3963                                                 = 0;
                    D_800C3962                                                 = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
                    g_SysWork.player_4C.chara_0.field_44                       = 0;
                }
            }
            break;

        case 4:
            if (D_800C3963 & (1 << 1))
            {
                if (!(D_800C3963 & (1 << 2)))
                {
                    func_8008B438(0, 0, 0);
                    func_8008B3E4(0);

                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
                    D_800C3963                                                -= 2;
                }
            }
            break;

        case 5:
            if (g_SavegamePtr->mapOverlayId_A4 != D_800C3960)
            {
                D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
                D_800C3963 = 0;
                D_800C3962 = 0;
                D_800C3961 = 32;

                temp_v1 = arg0;
                if (temp_v1 != (1 << 1))
                {
                    D_800C3963 = 1 << 0;
                }
                else
                {
                    D_800C3963 = temp_v1;
                }

                if (arg0 == (1 << 1))
                {
                    D_800C3963 |= 1 << 2;
                }
            }

            func_8008B438(arg0 != 2, (u8)D_800C3961, D_800C3962);

            if (arg0 == (1 << 1))
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
            }

            func_8008B3E4(NO_VALUE);
            break;
    }
}

static const s32 pad = 0; // Rodata padding.

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

void func_8004C8DC() // 0x8004C8DC
{
    #define TIME_290_HOURS        FP_TO(290 * 60 * 60, Q12_SHIFT)
    #define TIME_130_HOURS        FP_TO(130 * 60 * 60, Q12_SHIFT)
    #define TIME_290_OVERFLOW_MAX 3                               // `add290Hours_25C_1` has max value of 3.

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
    Gfx_StringSetColor(7);
    func_800363D0();

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        func_8004C8DC();
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
                g_GameWork.gameStatePrev_590 == 16)
            {
                D_800A9A80 = 0;
                Game_WarmBoot();
                GameFs_StreamBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_MovieIntro);
                return;
            }

            if (func_8004C45C() == 1)
            {
                func_80054CAC(163, 1);
            }

            Gfx_ClearRectInterlaced(0, 0x20, 0x140, 0x1C0, 0u, 0u, 0u);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks = 1;
            g_Gfx_ScreenFade  = 6;
            D_800B5C30        = 0x3000;

            func_80037188();

            D_800C3990                 = 1;
            D_800C3998                 = 0;
            D_800AE178                 = 0;
            g_Inventory_CmdSelectedIdx = 0;
            D_800AE17C                 = g_SysWork.field_2351;

            switch (g_GameWork.gameStatePrev_590)
            {
                case 19:
                    g_Inventory_SelectionId = InventorySelectionId_Item;
                    D_800C399C              = InventorySelectionId_Item;
                    break;

                case 18:
                    g_Inventory_SelectionId = InventorySelectionId_Settings;
                    D_800C399C              = InventorySelectionId_Settings;
                    break;

                case 15:
                    g_Inventory_SelectionId = InventorySelectionId_Map;
                    D_800C399C              = InventorySelectionId_Map;
                    break;

                default:
                    break;
            }

            g_SysWork.player_4C.extra_128.field_28 = 0;
            g_GameWork.background2dColor_R_58C     = 0;
            g_GameWork.background2dColor_G_58D     = 0;
            g_GameWork.background2dColor_B_58E     = 0;

            func_80054558();
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
            if (g_SysWork.field_2351 == D_800AE17C &&
                g_GameWork.gameState_594 == GameState_InventoryScreen &&
                g_Gfx_ScreenFade == 1)
            {
                s32 prevGameState;
                prevGameState = g_GameWork.gameStateStep_598[2];

                Inventory_Logic(g_SysWork.field_2351);

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }

            Gfx_Inventory_CmdOptionsDraw();

            switch (g_GameWork.gameStateStep_598[1])
            {
                // "Can't use here" message. Triggers when attempting to use special items in places where they trigger nothing.
                case 12:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.field_10              = 3; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.field_14              = 0;
                    break;

                // "Too dark too look at the item" message. Triggers in circumstances like maps in Otherworld with the flashlight off.
                case 16:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.field_10              = 4; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.field_14              = 0;
                    break;

                default:
                    break;
            }
            break;

        case 17:
            {
                s32 prevGameState;

                prevGameState                   = g_GameWork.gameStateStep_598[2];
                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;

                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }
            break;

        case 18:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                s32 prevGameState;

                func_800323C8(0x140, 0);
                Fs_QueueWaitForEmpty();
                func_8004C040();

                D_800AE185 = 0xFF;
                D_800AE186 = 0xFF;

                Game_StateSetNext_ClearStateSteps(GameState_OptionScreen);
                return;
            }
            break;

        case 19:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                func_8004C040();
                Game_StateSetNext(GameState_MapScreen);
                return;
            }
            break;

        case 20:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                func_800323C8(0x140, 0);
                func_80054634();

                g_SavegamePtr->field_AB = func_8004F190(g_SavegamePtr);

                func_8003CD6C(&g_SysWork.field_38);
                func_8003D01C();
                Fs_QueueWaitForEmpty();
                
                Game_StateSetNext(GameState_InGame);
                return;
            }
            break;

        // Results screen triggers here.
        case 21:
            Gfx_ClearRectInterlaced(0, 0x20, 0x140, 0x1C0, 0, 0, 0);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks                  = 1;
            g_Gfx_ScreenFade                   = 6;
            D_800B5C30                         = 0x3000;
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;
            g_Inventory_SelectionId            = InventorySelectionId_Item;

            func_80054558();
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
            if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
            {
                g_GameWork.gameStateStep_598[1] = 23;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 23:
            if (g_ControllerPtrConst->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                g_Inventory_SelectionId = g_Inventory_SelectionId == 0;
                func_80046048(0x519, 0, 0x40);
            }

            if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                s32 prevGameState;
                g_Gfx_ScreenFade = 2;
                prevGameState    = g_GameWork.gameStateStep_598[2];

                func_80046048(0x51B, 0, 0x40);

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
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                func_800323C8(0x140, 0);
                GameFs_SaveLoadBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_Unk10);
                return;
            }
            break;

        case 25:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                if (Fs_QueueDoThingWhenEmpty() != 0)
                {
                    D_800A9A80 = 0;

                    Game_WarmBoot();
                    GameFs_StreamBinLoad();
                    Fs_QueueWaitForEmpty();
                    Game_StateSetNext(GameState_MovieIntro);
                    return;
                }
            }
            break;
    }

    func_8004F764(&g_Inventory_SelectionId);

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

    GsOT* ot = &g_ObjectTable1[g_ObjectTableIdx];

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
            rgColor    = 0x60 - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        } 
        else 
        {
            colorVar1 = ((i % 12) - 4) / 2;
            rgColor   = 0x60 - (colorVar1 << 6);
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

    g_SysWork.field_2350_0 = 1;

    Gfx_StringSetPosition(90, 92);
    Gfx_StringDraw("\x07Is_it_OK_to_save?", 99);

    Gfx_StringSetPosition(94, 122);
    Gfx_StringDraw("\x07Yes_____________No", 99);

    g_SysWork.field_2350_0 = 0;

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

    D_800C3998++;

    if (D_800C3998 >= InventorySelectionId_Examine)
    {
        D_800C399C = g_Inventory_SelectionId;
    }

    D_800C3998 = CLAMP(D_800C3998, InventorySelectionId_Item, InventorySelectionId_Examine);

    if (g_GameWork.gameStateStep_598[1] != 1)
    {
        return;
    }

    if (g_Inventory_SelectionId == InventorySelectionId_Item)
    {
        if (D_800C3998 <= InventorySelectionId_Settings)
        {
            return;
        }
    }
    else if (D_800C3998 <= InventorySelectionId_Health)
    {
        return;
    }

    switch (g_Inventory_SelectionId)
    {
        case InventorySelectionId_Item:
            if ((g_Inventory_IsLeftClicked && D_800C3998 == InventorySelectionId_Examine) ||
                (g_Inventory_IsLeftHeld && (D_800C3990 != 0 || D_800C3998 == InventorySelectionId_Examine)))
            {
                if (g_Inventory_IsLeftClicked || g_Inventory_IsLeftHeld)
                {
                    D_800C3990 = 1;
                }

                D_800AE178                 = 1;
                D_800C3998                 = InventorySelectionId_Exit;
                g_Inventory_CmdSelectedIdx = 0;
                func_80046048(SFX_BACK, -64, 64);

                g_SysWork.field_2351 = ((g_SysWork.field_2351 + g_SavegamePtr->field_AB) - 1) % g_SavegamePtr->field_AB;
                temp                 = g_SavegamePtr->field_AB - 3;
                func_800539A4(0, (g_SysWork.field_2351 + temp) % g_SavegamePtr->field_AB);
            }
            else if (((g_Inventory_IsRightClicked || g_Inventory_IsRightPulsed) && D_800C3998 == InventorySelectionId_Examine) ||
                     (g_Inventory_IsRightHeld && (D_800C3990 != 0 || D_800C3998 == InventorySelectionId_Examine)))
            {
                if (g_Inventory_IsRightClicked || g_Inventory_IsRightHeld)
                {
                    D_800C3990 = 1;
                }

                D_800AE178                 = 1;
                D_800C3998                 = InventorySelectionId_Exit;
                g_Inventory_CmdSelectedIdx = 0;
                func_80046048(SFX_BACK, 64, 64);

                g_SysWork.field_2351 = (g_SysWork.field_2351 + 1) % g_SavegamePtr->field_AB;
                func_800539A4(1, (g_SysWork.field_2351 + 3) % g_SavegamePtr->field_AB);
            }
            else if (g_Inventory_IsUpClicked != InventorySelectionId_Item && D_800C3998 == InventorySelectionId_Examine)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;

                if (g_SysWork.field_38.field_F >= 0)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItem;
                    func_80046048(SFX_BACK, 0, 64);
                }
            }
            else if ((g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 || g_Inventory_IsDownClicked != 0) && D_800C3998 == 8)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;

                if (g_Inventory_IsDownClicked != 0)
                {
                    func_80046048(SFX_BACK, 0, 64);
                }
                else
                {
                    func_80046048(SFX_CANCEL, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0 &&
                     D_800C3998 >= InventorySelectionId_Examine)
            {
                if (g_SavegamePtr->items_0[g_SysWork.field_2351].id_0 == InventoryItemId_Flauros ||
                    (g_SysWork.field_239E != 0 && g_SavegamePtr->items_0[g_SysWork.field_2351].id_0 == InventoryItemId_Flashlight))
                {
                    func_80046048(SFX_DENIED, 64, 64);
                }
                else if (g_SavegamePtr->items_0[g_SysWork.field_2351].command_2 == InventoryCmdId_Unk10)
                {
                    g_GameWork.gameStateStep_598[1] = 12;
                    g_GameWork.gameStateStep_598[2] = 0;
                    func_80046048(SFX_DENIED, 64, 64);
                }
                else
                {
                    D_800C3998                 = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx = 0;

                    if (g_SavegamePtr->items_0[g_SysWork.field_2351].command_2 != InventoryCmdId_Unk11)
                    {
                        g_Inventory_SelectionId = InventorySelectionId_ItemCmd;
                        func_80046048(SFX_CONFIRM, 64, 64);
                    }
                }
            }
            else if (!(g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16))
            {
                D_800C3990 = 0;
            }
            else
            {
                step = g_GameWork.gameStateStep_598[2];
                func_80046048(SFX_CANCEL, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_EquippedItem:
            if (g_Inventory_IsDownClicked != 0)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                D_800C3998                 = InventorySelectionId_EquippedItem;
                g_Inventory_CmdSelectedIdx = 0;

                if (g_SavegamePtr->items_0[g_SysWork.field_4A].command_2 != InventoryCmdId_Unk11)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItemCmd;
                    func_80046048(SFX_CONFIRM, 0, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                g_Inventory_SelectionId = InventorySelectionId_Exit;
                func_80046048(SFX_CANCEL, 0, 64);
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                func_80046048(SFX_CANCEL, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Exit:
            if (g_Inventory_IsUpClicked)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, -64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Settings;
            }
            else if (g_Inventory_IsRightClicked)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, 64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Map;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.item_16 | (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                                                                                    g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                step = g_GameWork.gameStateStep_598[2];
                func_80046048(SFX_CANCEL, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Settings:
            if (g_Inventory_IsUpClicked)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsRightClicked || (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                D_800C3998 = InventorySelectionId_EquippedItem;

                if (!g_Inventory_IsRightClicked || (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    func_80046048(SFX_CANCEL, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
                else
                {
                    func_80046048(SFX_BACK, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                func_80046048(SFX_CONFIRM, -64, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 18;
                g_GameWork.gameStateStep_598[2] = 0;

                GameFs_OptionBinLoad();
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                func_80046048(SFX_CANCEL, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Map:
            if (g_Inventory_IsUpClicked)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;
                func_80046048(SFX_BACK, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked || g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;

                if (!g_Inventory_IsLeftClicked || g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                {
                    func_80046048(SFX_CANCEL, 0, 64);
                }
                else
                {
                    func_80046048(SFX_BACK, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if ((!((u8)g_SysWork.field_24DC & (1 << 1)) || g_SysWork.field_239D != 0 || (!(g_SysWork.field_23A4 & (1 << 0)) && !(g_SysWork.field_23D8 & (1 << 0)))) &&
                    HAS_MAP(g_SavegamePtr->current2dMap_A9))
                {
                    func_80046048(SFX_CONFIRM, 64, 64);

                    if (D_800A99CC[g_SavegamePtr->current2dMap_A9] != -1)
                    {
                        Fs_QueueStartReadTim(D_800A99CC[g_SavegamePtr->current2dMap_A9] + 0x776, FS_BUFFER_1, &D_800A9024);
                    }
                    Fs_QueueStartSeek(D_800A99B4[g_SavegamePtr->current2dMap_A9] + 0x768);

                    g_Gfx_ScreenFade                = 2;
                    g_GameWork.gameStateStep_598[1] = 19;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    func_80046048(SFX_DENIED, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                func_80046048(SFX_CANCEL, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }

            if (!HAS_MAP(g_SavegamePtr->current2dMap_A9))
            {
                Gfx_Inventory_UnavailableMapText(1);
            }
            else if ((u8)g_SysWork.field_24DC & (1 << 1) && g_SysWork.field_239D == 0 &&
                     (g_SysWork.field_23A4 & (1 << 0) || g_SysWork.field_23D8 & (1 << 0)))
            {
                Gfx_Inventory_UnavailableMapText(0);
            }
            break;

        case InventorySelectionId_ItemCmd:
        case InventorySelectionId_EquippedItemCmd:
            if (g_Inventory_SelectionId == InventorySelectionId_ItemCmd)
            {
                curItemIdx = g_SysWork.field_2351;
            }
            else
            {
                curItemIdx = g_SysWork.field_4A;
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
                    D_800C3998 = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx++;
                    func_80046048(SFX_BACK, 64, 64);
                }
            }
            else if (g_Inventory_IsUpPulsed)
            {
                if (g_Inventory_CmdSelectedIdx > 0)
                {
                    D_800C3998 = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx--;
                    func_80046048(SFX_BACK, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                D_800C3998 = InventorySelectionId_EquippedItem;

                switch (g_SavegamePtr->items_0[curItemIdx].command_2)
                {
                    case InventoryCmdId_OnOff:
                        D_800C3998              = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId = InventorySelectionId_Item;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_Flashlight:
                                    func_8003ECBC();
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
                                    func_8003ECE4();
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
                            if (!((u8)g_SysWork.field_24DC & (1 << 1)) || g_SysWork.field_239D != 0 ||
                                (!(g_SysWork.field_23A4 & (1 << 0)) && !(g_SysWork.field_23D8 & (1 << 0))))
                            {
                                D_800C3998                      = InventorySelectionId_EquippedItem;
                                g_Inventory_SelectionId         = InventorySelectionId_Examine;
                                g_GameWork.gameStateStep_598[1] = 13;
                                g_GameWork.gameStateStep_598[2] = 0;

                                switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                                {
                                    case InventoryItemId_KeyOfLion:
                                        Fs_QueueStartReadTim(FILE_TIM_LION_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfWoodman:
                                        Fs_QueueStartReadTim(FILE_TIM_KIKORI_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfScarecrow:
                                        Fs_QueueStartReadTim(FILE_TIM_KAKASHI_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfOphiel:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_A_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfHagith:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_B_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfPhaleg:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_C_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfBethor:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_D_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KeyOfAratron:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_E_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KGordonKey:
                                        Fs_QueueStartReadTim(FILE_TIM_K_GORDON_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_KaufmannKey:
                                        Fs_QueueStartReadTim(FILE_TIM_MOTEL_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_AntiqueShopKey:
                                        if (g_SavegamePtr->eventFlags_168[5] & (1 << 11))
                                        {
                                            g_SavegamePtr->mapMarkingFlags_1DC |= 1 << 16;
                                        }

                                        Fs_QueueStartReadTim(FILE_TIM_ANTIQUE_TIM, FS_BUFFER_1, &D_800A902C);
                                        break;

                                    case InventoryItemId_ClassroomKey:
                                        Fs_QueueStartReadTim(FILE_TIM_KEY_OF_2_TIM, FS_BUFFER_1, &D_800A902C);
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
                            func_8004E6D4(curItemIdx);
                        }
                        break;

                    case InventoryCmdId_Look:
                        if (!((u8)g_SysWork.field_24DC & (1 << 1)) || g_SysWork.field_239D != 0 ||
                            (!(g_SysWork.field_23A4 & (1 << 0)) && !(g_SysWork.field_23D8 & (1 << 0))))
                        {
                            D_800C3998                      = InventorySelectionId_EquippedItem;
                            g_Inventory_SelectionId         = InventorySelectionId_Examine;
                            g_GameWork.gameStateStep_598[1] = 13;
                            g_GameWork.gameStateStep_598[2] = 0;

                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_NoteToSchool:
                                    Fs_QueueStartReadTim(FILE_TIM_TOSCHOOL_TIM, FS_BUFFER_1, &D_800A902C);
                                    break;

                                case InventoryItemId_NoteDoghouse:
                                    Fs_QueueStartReadTim(FILE_TIM_STKENNEL_TIM, FS_BUFFER_1, &D_800A902C);
                                    break;

                                case InventoryItemId_Receipt:
                                    Fs_QueueStartReadTim(FILE_TIM_RECEIPT_TIM, FS_BUFFER_1, &D_800A902C);
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
                        D_800C3998                      = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_Health;
                        g_GameWork.gameStateStep_598[1] = 9;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Use:
                        func_8004E6D4(curItemIdx);
                        break;

                    case InventoryCmdId_Equip:
                        D_800C3998                      = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1] = 5;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Unequip:
                        D_800C3998                      = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1] = 6;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Reload:
                        D_800C3998 = InventorySelectionId_EquippedItem;

                        if (curItemIdx != g_SysWork.field_4A)
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
                        D_800C3998 = InventorySelectionId_EquippedItem;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 5;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.field_4A)
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
                        D_800C3998 = InventorySelectionId_EquippedItem;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 6;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.field_4A)
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
                    func_80046048(SFX_DENIED, 64, 64);
                }
                else
                {
                    func_80046048(SFX_CONFIRM, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                D_800C3998                 = InventorySelectionId_EquippedItem;
                g_Inventory_CmdSelectedIdx = 0;
                g_Inventory_SelectionId    = InventorySelectionId_Item;
                func_80046048(SFX_CANCEL, 0, 64);
            }

            do {} while (0); // HACK: Required for match.
            break;

        case InventorySelectionId_Examine:
            D_800C3998 = InventorySelectionId_EquippedItem;
            break;
    }
}

void func_8004E6D4(s32 arg0) // 0x8004E6D4
{
    s32 i;

    g_GameWork.gameStateStep_598[1] = 12;
    g_GameWork.gameStateStep_598[2] = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
    {
        if (func_80038A6C(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.npcs_1A0[0].position_18, FP_METER(0.7f)) == 0 &&
            ABS(g_SysWork.player_4C.chara_0.position_18.vy - g_SysWork.npcs_1A0[0].position_18.vy) < FP_METER(0.3f) &&
            g_SysWork.player_4C.extra_128.field_1C == 0 &&
            g_SavegamePtr->items_0[arg0].id_0 == InventoryItemId_UnknownLiquid)
        {
            D_800C3998                      = InventorySelectionId_EquippedItem;
            g_Inventory_SelectionId         = InventorySelectionId_Item;
            g_GameWork.gameStateStep_598[1] = 11;
            g_GameWork.gameStateStep_598[2] = 0;

            func_8003ECBC();
            g_SavegamePtr->eventFlags_1A0 |= 1 << 0;
        }
    }
    else
    {
        for (i = 0; D_800BCDC0[i] != NO_VALUE; i++)
        {
            if (D_800BCDC0[i] == g_SavegamePtr->items_0[arg0].id_0)
            {
                D_800C3998                      = InventorySelectionId_EquippedItem;
                g_Inventory_SelectionId         = InventorySelectionId_Item;
                g_GameWork.gameStateStep_598[1] = 11;
                g_GameWork.gameStateStep_598[2] = 0;

                func_8003ECBC();
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

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        Gfx_StringSetColor(ColorId_White);
    }
    else
    {
        Gfx_StringSetColor(ColorId_DarkGrey);
    }

    if (g_Inventory_SelectionId != InventorySelectionId_EquippedItem &&
        g_Inventory_SelectionId != InventorySelectionId_EquippedItemCmd)
    {
        idx = g_SysWork.field_2351;
    }
    else
    {
        idx = g_SysWork.field_4A;
    }

    switch (g_SavegamePtr->items_0[idx].command_2)
    {
        case InventoryCmdId_OnOff:
            if (g_SysWork.field_239E == 0 || g_SavegamePtr->items_0[idx].id_0 != InventoryItemId_Flashlight)
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
                setRGB0(poly, 0, 0xC0, 0x40);
                setRGB1(poly, 0, 0, 0);
                setRGB2(poly, 0, 0xC0, 0x40);
                setRGB3(poly, 0, 0, 0);
            }
            else
            {
                setRGB0(poly, 0, 0, 0);
                setRGB1(poly, 0, 0xC0, 0x40);
                setRGB2(poly, 0, 0, 0);
                setRGB3(poly, 0, 0xC0, 0x40);
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

    POLY_G3* arrowPoly;
    s32      baseColor;
    s32      i;
    s8       timeStep;

    GsOT* ot = &g_ObjectTable1[g_ObjectTableIdx];

    // TODO: Why the large values for some positions?
    s_Triangle2d arrowTris[] =
    {
        { { 0xFFC4, 0x000C }, { 0xFFCC, 0x0004 }, { 0xFFCC, 0x0014 } },
        { { 0xFFCC, 0x000C }, { 0xFFD4, 0x0004 }, { 0xFFD4, 0x0014 } },
        { { 0x0034, 0x000C }, { 0x002C, 0x0004 }, { 0x002C, 0x0014 } },
        { { 0x003C, 0x000C }, { 0x0034, 0x0004 }, { 0x0034, 0x0014 } },
        { { 0x0060, 0xFF53 }, { 0x0066, 0xFF60 }, { 0x005A, 0xFF60 } }, // Unused.
        { { 0x0060, 0xFFA4 }, { 0x005B, 0xFF98 }, { 0x0065, 0xFF98 } }  // Unused.
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

        baseColor = 0xFF - (timeStep * 8);
        setRGB0(arrowPoly, baseColor, baseColor, baseColor);
        setRGB1(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);
        setRGB2(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);

        setXY3(arrowPoly,
               arrowTris[i].vertex0_0.vx, arrowTris[i].vertex0_0.vy,
               arrowTris[i].vertex1_4.vx, arrowTris[i].vertex1_4.vy,
               arrowTris[i].vertex2_8.vx, arrowTris[i].vertex2_8.vy);

        addPrim(&ot->org[7], arrowPoly);
        GsOUT_PACKET_P = (PACKET*)arrowPoly + sizeof(POLY_G3);
    }

    // Set texture.
    Gfx_Primitive2dTextureSet(0, 0, 7, 1);
}

s32 func_8004EE94(u8 arg0, u8 arg1) // 0x8004EE94
{
    s32 i;

    for (i = 0; i < g_SavegamePtr->field_AB; i++)
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
                        g_SavegamePtr->items_0[i].id_0 = 0xFF;
                        g_SavegamePtr->field_AB        = func_8004F190(g_SavegamePtr);
                    }
                }
            }

            return 1;
        }
    }

    return 0;
}

/** Does something with data of items and also something with map.
 * Used in:
 * `GameState_ItemScreens_Update`
 * `Inventory_PlayerItemScroll`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004EF48); // 0x8004EF48

// Unused?
void func_8004F10C(s32* arg0) // 0x8004F10C
{
    s32 i;

    g_SavegamePtr->field_AB = func_8004F190(g_SavegamePtr);

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

/** Used in:
 * `func_8004EE94`
 * `func_8004F10C`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004F190); // 0x8004F190

void Gfx_Inventory_UnavailableMapText(s32 strIdx) // 0x0x8004F57C
{
    char* D_800262AC[2] =
    {
        "Too_dark_to_look_at\n\t\tthe_map_here.",
        "I_don't_have_the_map\n\t\tfor_this_place."
    };

    Gfx_StringSetPosition(30, 232);
    Gfx_StringSetColor(7);
    Gfx_StringDraw(D_800262AC[strIdx], 0x63);
}

// Unknown RODATA values.
static const u8  unk0 = 0x2A; // '*' as `char`.
static const s32 unk1 = 0;

void Inventory_DirectionalInputSet() // 0x8004F5DC
{
    if (g_ControllerPtrConst->field_23 < -64 || g_ControllerPtrConst->field_23 >= 64 ||
        g_ControllerPtrConst->field_22 < -64 || g_ControllerPtrConst->field_22 >= 64)
    {
        // Up.
        g_Inventory_IsUpClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickUp2;
        g_Inventory_IsUpPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickUp2;

        // Down.
        g_Inventory_IsDownClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickDown2;
        g_Inventory_IsDownPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickDown2;

        // Left.
        g_Inventory_IsLeftClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickLeft2;

        // Right.
        g_Inventory_IsRightClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickRight2;
        g_Inventory_IsRightHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickRight2;
        g_Inventory_IsRightPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickRight2;
    }
    else
    {
        // Up.
        g_Inventory_IsUpClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickUp;
        g_Inventory_IsUpPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickUp;

        // Down.
        g_Inventory_IsDownClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickDown;
        g_Inventory_IsDownPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickDown;

        // Left.
        g_Inventory_IsLeftClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickLeft;

        // Right.
        g_Inventory_IsRightClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickRight;
        g_Inventory_IsRightHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickRight;
        g_Inventory_IsRightPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickRight;
    }
}

// TODO: `D_800262FC` is used by functions in different files (`func_8004F764` and `func_80054AD8` from `bodyprog_80053B08`).
#if 0
static const DVECTOR D_800262FC[] =
{
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0xFE00, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0800 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0200 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0A00, 0x0800 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 }
};
#endif

/** Some sort of handler for the inventory and result screen. */
// TODO: RODATA migration.
#ifdef NON_MATCHING
extern DVECTOR D_800262FC[];

void func_8004F764(s32 arg0) // 0x8004F764
{
    GsDOBJ2* ptr;
    s32      i;

    DVECTOR strPosTable[] = // 0x80027DD8
    {
        { 0x0076, 0xFFB0 },
        { 0x0090, 0x0130 },
        { 0x0024, 0x0130 },
        { 0x00F0, 0x0130 }, 
        { 0x00DA, 0xFFB0 },
        { 0x0028, 0xFFB0 },
        { 0x0010, 0x00B8 },
        { 0x0010, 0x00C8 }
    };

    char* strs[] = // 0x80027E34
    {
        "Equipment",
        "Exit",
        "Option",
        "Map",
        "Command",
        "Status",
        "No.",
        "Name:"
    };

    Gfx_StringSetColor(ColorId_White);

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        for (i = 0; i < 8; i++)
        {
            Gfx_StringSetPosition(strPosTable[i].vx, strPosTable[i].vy);
            Gfx_StringDraw(strs[i], 10);
        }

        func_800523D8(arg0);

        for (i = 0, ptr = &D_800C3D78; i < 7; i++, ptr++)
        {
            if (D_800C3E18[i] != NO_VALUE)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[i]].id_0 != 0xFF)
                {
                    D_800C3BE8[i].field_10.vx = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vx;
                    D_800C3BE8[i].field_10.vz = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vy;

                    func_8004BCDC(&D_800C3E48[i].param->rotate, &D_800C3E48[i]);
                    func_800548D8(i);
                    GsSetFlatLight(0, &D_800C39A8[i][0]);
                    GsSetFlatLight(1, &D_800C39A8[i][1]);
                    func_8004BD74(i, ptr, 0);
                }
            }
        }

        if ((g_SavegamePtr->items_0[D_800C3E34].id_0 != 0xFF) && (D_800C3E34 != NO_VALUE))
        {
            D_800C3BE8[7].field_10.vx = D_800262FC[g_SavegamePtr->items_0[D_800C3E34].id_0 - 32].vx;
            D_800C3BE8[7].field_10.vz = D_800262FC[g_SavegamePtr->items_0[D_800C3E34].id_0 - 32].vy;

            func_8004BCDC(&D_800C3E48[7].param->rotate, &D_800C3E48[7]);
            func_800548D8(7);
            GsSetFlatLight(0, &D_800C3A88[0]);
            GsSetFlatLight(1, &D_800C3A88[1]);
            func_8004BD74(7, ptr, 0);
        }

        Gfx_Inventory_ItemDescription(arg0);
        func_8004FBCC(arg0);
    }
    else
    {
        func_8005227C(g_SavegamePtr->clearGameCount_24A);
        func_800521A8(g_SavegamePtr->clearGameCount_24A);
        func_80090664(arg0);
    }

    func_8004FB0C();
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004F764); // 0x8004F764
#endif

void func_8004FB0C() // 0x8004FB0C
{
    GsOT*    ot;
    POLY_F4* poly;

    ot   = &g_ObjectTable1[g_ObjectTableIdx];
    poly = (POLY_F4*)GsOUT_PACKET_P;

    setPolyF4(poly);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly,
           -160, -224,
           -160, -222,
            160, -224,
            160, -222);
    addPrim(ot->org, poly);

    GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_F4);
}

/** Draws many 2D menu elements.
 * The background behind the text
 * in the upper and lower part of the inventory
 * screen, the box used to indicate what the player
 * has selected, and triggers the draw of the health
 * status.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004FBCC); // 0x8004FBCC

INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_HealthStatusDraw); // 0x80051020

INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_ItemDescription); // 0x8005192C

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr) // 0x80052088
{
    GsOT*     ot0;
    GsOT*     ot1;
    s32       idx   = g_ObjectTableIdx;
    DR_TPAGE* tPage = (DR_TPAGE*)GsOUT_PACKET_P;

    setDrawTPage(tPage, 0, 1, getTPage(0, abr, x, y));

    ot1 = &g_ObjectTable1[idx];
    ot0 = &g_ObjectTable0[idx];

    if (abr < 4)
    {
        addPrim(&ot1->org[otIdx], tPage);
    }
    else
    {
        addPrim(&ot0->org[otIdx], tPage);
    }

    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);
}

void func_800521A8() // 0x800521A8
{
    GsDOBJ2* ptr;
    s32      i;

    for (i = 0, ptr = D_800C3D78; i < 6; i++, ptr++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            func_8004BCDC(&D_800C3E48[i].param->rotate, &D_800C3E48[i]);
            func_800548D8(i);
            GsSetFlatLight(0, &D_800C39A8[i][0]);
            GsSetFlatLight(1, &D_800C39A8[i][1]);
            func_8004BD74(i, ptr, 3);
        }
    }
}

/** Results screen related.
 * Used in: `func_8004F764`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8005227C); // 0x8005227C

/** Name could be inaccurate.
 * Breaking this function call makes items no longer rotate,
 * and trying to scroll through the items will softlock the game.
 * If the user breaks the function before entering the
 * inventory, all items will be at the center of the screen
 * and the equiped item will appear frozen in its base pose.
 * If the user doesn't try scrolling through items, they
 * will be able to navigate through other functions. However,
 * messing with commands also will softlock the game.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Inventory_PlayerItemScroll); // 0x800523D8

void func_800539A4(s32 arg0, s32 arg1) // 0x800539A4
{
    s32 sp10[10];
    s32 i;
    s32 var_a3_2;
    s32 var_s0;

    var_s0 = 0;

    for (i = 0; i < 10; i++)
    {
        sp10[i] = D_800C3E18[i];
    }

    var_a3_2 = (arg0 != 0) ? -7 : 7;
    var_a3_2 = (arg1 + var_a3_2 + g_SavegamePtr->field_AB) % g_SavegamePtr->field_AB;

    for (i = 0; i < 7; i++)
    {
        if (sp10[i] == var_a3_2)
        {
            var_s0 = i;
            i      = 7;
        }
    }

    sp10[var_s0] = arg1;

    if (g_SavegamePtr->items_0[arg1].id_0 != 0xFF)
    {
        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items_0[arg1].id_0 == D_800C3BB8[i])
            {
                func_80054720(FS_BUFFER_8, var_s0, i);
                func_8005487C(var_s0);
                i = INVENTORY_ITEM_COUNT_MAX;
            }
        }
    }

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = sp10[i];
    }
}
