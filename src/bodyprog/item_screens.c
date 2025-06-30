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
        if (g_GameWork.controllers_38[1].analogController_0.status == 0 &&
            g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
            g_GameWork.controllers_38[1].analogController_0.terminal_type == PadTerminalType_GunControllerKonami)
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
        return g_GameWork.controllers_38[1].analogController_0.status == 0 &&
               g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
               g_GameWork.controllers_38[1].analogController_0.terminal_type == PadTerminalType_GunControllerKonami;
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
            D_800C3961 = 0x20;
            func_8008B398();
            g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
            break;

        case 1:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3961 = 0x20;

            func_8008B438(arg0 != 2, 0x20, 0);
            func_8008B3E4(0);

            if (arg0 != 2)
            {
                D_800C3963 |= 1;
            }
            else
            {
                D_800C3963 |= 2;
            }
            break;

        case 2:
            if (arg0 == 2)
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
                D_800C3963 |= 4;
            }
            break;

        case 3:
            if (D_800C3961 != 0)
            {
                D_800C3961 -= g_DeltaTime0 / 68 == 0 ? 1 : g_DeltaTime0 / 68;
                D_800C3962 = D_800C3961 - 0x20;
                D_800C3961 = CLAMP(D_800C3961, 0, 0x20);

                func_8008B438(arg0 != 2, 0, 0);
                func_8008B3E4(-1);

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
            if (D_800C3963 & 2)
            {
                if (!(D_800C3963 & 4))
                {
                    func_8008B438(0, 0, 0);
                    func_8008B3E4(0);
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
                    D_800C3963 -= 2;
                }
            }
            break;

        case 5:
            if (g_SavegamePtr->mapOverlayId_A4 != D_800C3960)
            {
                D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
                D_800C3963 = 0;
                D_800C3962 = 0;
                D_800C3961 = 0x20;

                temp_v1 = arg0;

                if (temp_v1 != 2)
                {
                    D_800C3963 = 1;
                }
                else
                {
                    D_800C3963 = temp_v1;
                }

                if (arg0 == 2)
                {
                    D_800C3963 |= 4;
                }
            }

            func_8008B438(arg0 != 2, (u8)D_800C3961, D_800C3962);
            if (arg0 == 2)
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
            }
            func_8008B3E4(-1);
            break;
    }
}

static const int pad = 0; // Rodata padding.

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
#define TIME_290_HOURS FP_TO(290 * 60 * 60, Q12_SHIFT)
#define TIME_130_HOURS FP_TO(130 * 60 * 60, Q12_SHIFT)
#define TIME_290_OVERFLOW_MAX 3 // add290Hours_25C_1 has max value of 3

    g_SavegamePtr->gameplayTimer_250 += g_DeltaTime1;

    if (g_SavegamePtr->gameplayTimer_250 >= TIME_290_HOURS)
    {
        if (g_SavegamePtr->add290Hours_25C_1 < TIME_290_OVERFLOW_MAX)
        {
            g_SavegamePtr->add290Hours_25C_1++;
            g_SavegamePtr->gameplayTimer_250 += (UINT_MAX - TIME_290_HOURS + 1); // Wrap timer to 0 using unsigned overflow
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

#undef TIME_290_HOURS
}

void GameState_ItemScreens_Update()
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
            if (g_SavegamePtr->field_27A & 31)
            {
                g_GameWork.gameStateStep_598[1] = 21;
                g_GameWork.gameStateStep_598[2] = 0;
                return;
            }

            if ((g_SavegamePtr->field_27A & 64) &&
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

            Gfx_ClearRectInterlaced(0, 0x20, 0x140, 0x1C0, 0U, 0U, 0U);
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
                    D_800ADB5C = 0;
                    D_800C399C = 0;
                    break;

                case 18:
                    D_800ADB5C = 3;
                    D_800C399C = 3;
                    break;

                case 15:
                    D_800ADB5C = 4;
                    D_800C399C = 4;
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
            if (g_SysWork.field_2351 == D_800AE17C && g_GameWork.gameState_594 == GameState_InventoryScreen && g_Gfx_ScreenFade == 1)
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
            D_800ADB5C                         = 0;

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
            if (g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
            {
                g_GameWork.gameStateStep_598[1] = 23;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 23:
            if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                D_800ADB5C = D_800ADB5C == 0;
                func_80046048(0x519, 0, 0x40);
            }

            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                s32 prevGameState;
                g_Gfx_ScreenFade = 2;
                prevGameState    = g_GameWork.gameStateStep_598[2];

                func_80046048(0x51B, 0, 0x40);

                if (!D_800ADB5C)
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

    func_8004F764(&D_800ADB5C);

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        Gfx_Inventory_ScrollArrows(&D_800ADB5C);
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
                   strOffsets[i].x0_0 + 0xFFB4 + (D_800ADB5C * 102), strOffsets[i].y0_1 + 6,
                   strOffsets[i].x1_2 + 0xFFB4 + (D_800ADB5C * 102), strOffsets[i].y1_3 + 6);
        }

        addPrim(&ot->org[7], line);
        GsOUT_PACKET_P = (PACKET*)line + sizeof(LINE_F2);
    }

    g_SysWork.field_2350_0 = 1;

    Gfx_StringSetPosition(90, 92);
    Gfx_StringDraw("\x07Is_it_OK_to_save?", 0x63);

    Gfx_StringSetPosition(94, 122);
    Gfx_StringDraw("\x07Yes_____________No", 0x63);

    g_SysWork.field_2350_0 = 0;

    Gfx_StringSetPosition(82, 200);
    Gfx_StringDraw("NEXT_GAME_MODE", 0xF);

    switch (D_800C3994)
    {
        case GameDifficulty_Easy:
            Gfx_StringSetPosition(123, 240);
            Gfx_StringDraw("NORMAL", 0xA);
            break;

        case GameDifficulty_Normal:
        case GameDifficulty_Hard:
            Gfx_StringSetPosition(136, 240);
            Gfx_StringDraw("HARD", 0xA);
            break;

        default:
            break;
    }
}

/** Function mainly responsible for handling the inventory screen. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Inventory_Logic); // 0x8004D518

/** Something related to items commands.
 * This is used when the player does some action in in the commands space.
 */
void func_8004E6D4(s32 arg0) // 0x8004E6D4
{
    s32 i;

    g_GameWork.gameStateStep_598[1] = 12;
    g_GameWork.gameStateStep_598[2] = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
    {
        if (func_80038A6C(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.npcs_1A0[0].position_18, 0xB33) == 0 &&
            ABS(g_SysWork.player_4C.chara_0.position_18.vy - g_SysWork.npcs_1A0[0].position_18.vy) < 0x4CC &&
            g_SysWork.player_4C.extra_128.field_1C == 0 && g_SavegamePtr->items_0[arg0].id_0 == InventoryItemId_UnknownLiquid)
        {
            D_800C3998                      = 1;
            D_800ADB5C                      = 0;
            g_GameWork.gameStateStep_598[1] = 11;
            g_GameWork.gameStateStep_598[2] = 0;
            func_8003ECBC();
            g_SavegamePtr->eventFlags_1A0 |= 1;
        }
    }
    else
    {
        for (i = 0; D_800BCDC0[i] != -1; i++)
        {
            if (D_800BCDC0[i] == g_SavegamePtr->items_0[arg0].id_0)
            {
                D_800C3998                      = 1;
                D_800ADB5C                      = 0;
                g_GameWork.gameStateStep_598[1] = 11;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8003ECBC();
                g_SysWork.player_4C.extra_128.field_28 = D_800BCDC0[i];
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_CmdOptionsDraw); // 0x8004E864

// TODO: RODATA Migration
#ifdef NON_MATCHING
void Gfx_Inventory_ScrollArrows(s32* arg0) // 0x8004EC7C
{
    s32 i;
    s32 temp_v0;
    s8 temp_v1;

    POLY_G3* poly;

    GsOT* ot = &g_ObjectTable1[g_ObjectTableIdx];

    s_Triangle2d tris[] =
    {
        { { 0xFFC4, 0x000C }, { 0xFFCC, 0x0004 }, { 0xFFCC, 0x0014 } },
        { { 0xFFCC, 0x000C }, { 0xFFD4, 0x0004 }, { 0xFFD4, 0x0014 } },
        { { 0x0034, 0x000C }, { 0x002C, 0x0004 }, { 0x002C, 0x0014 } },
        { { 0x003C, 0x000C }, { 0x0034, 0x0004 }, { 0x0034, 0x0014 } },
        { { 0x0060, 0xFF53 }, { 0x0066, 0xFF60 }, { 0x005A, 0xFF60 } },
        { { 0x0060, 0xFFA4 }, { 0x005B, 0xFF98 }, { 0x0065, 0xFF98 } }
    };

    if (*arg0 != 0) 
    {
        return;
    }

    for (i = 0; i < 4; i++) 
    {
        temp_v1 = g_SysWork.timer_1C & 0x1F;

        poly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(poly);
        setSemiTrans(poly, 1);

        temp_v0 = 0xFF - temp_v1 * 8;

        setRGB0(poly, temp_v0, temp_v0, temp_v0);
        setRGB1(poly, temp_v1 * 8, temp_v1 * 8, temp_v1 * 8);
        setRGB2(poly, temp_v1 * 8, temp_v1 * 8, temp_v1 * 8);

        setXY3(poly,
               tris[i].vertex0_0.vx, tris[i].vertex0_0.vy,
               tris[i].vertex1_4.vx, tris[i].vertex1_4.vy,
               tris[i].vertex2_8.vx, tris[i].vertex2_8.vy);

        addPrim(&ot->org[7], poly);

        GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_G3);
    }

    func_80052088(0, 0, 7, 1);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_ScrollArrows); // 0x8004EC7C
#endif

// Unused?
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

/** This function draws the two messages that indicate
 * the player can't open the map in the inventory.
 */
// TODO: RODATA Migration
#ifdef NON_MATCHING
void Gfx_Inventory_UnavailableMapText(s32 stringIdx)
{
    char* D_800262AC[2] =
    {
        "Too_dark_to_look_at\n\t\tthe_map_here.",
        "I_don't_have_the_map\n\t\tfor_this_place"
    };

    Gfx_StringSetPosition(30, 232);
    Gfx_StringSetColor(7);
    Gfx_StringDraw(D_800262AC[stringIdx], 0x63);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_UnavailableMapText); // 0x8004F57C
#endif

/** Likely controls handling in inventory screen. */
void func_8004F5DC() // 0x8004F5DC
{
    if (g_ControllerPtrConst->field_23 < -64 || g_ControllerPtrConst->field_23 >= 64 ||
        g_ControllerPtrConst->field_22 < -64 || g_ControllerPtrConst->field_22 >= 64)
    {
        D_800C3968 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickUp2;
        D_800C3978 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp2;
        D_800C396C = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickDown2;
        D_800C397C = g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown2;
        D_800C3970 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft2;
        D_800C3988 = g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickLeft2;
        D_800C3980 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft2;
        D_800C3974 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight2;
        D_800C398C = g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickRight2;
        D_800C3984 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight2;
    }
    else
    {
        D_800C3968 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickUp;
        D_800C3978 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp;
        D_800C396C = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickDown;
        D_800C397C = g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown;
        D_800C3970 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft;
        D_800C3988 = g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickLeft;
        D_800C3980 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft;
        D_800C3974 = g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight;
        D_800C398C = g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickRight;
        D_800C3984 = g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight;
    }
}

/** This function is some sort of handler for the inventory and result screen. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004F764); // 0x8004F764

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

/** Related to the drawing of arrows next to
 * the selected item in the inventory.
 * Breaking it reveals that it whitens the arrows,
 * as without this function, the arrows look a bit grey.
 */
void func_80052088(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x80052088
{
    GsOT*     ot0;
    GsOT*     ot1;
    s32       idx   = g_ObjectTableIdx;
    DR_TPAGE* tPage = (DR_TPAGE*)GsOUT_PACKET_P;

    setDrawTPage(tPage, 0, 1, getTPage(0, arg3, arg0, arg1));

    ot1 = &g_ObjectTable1[idx];
    ot0 = &g_ObjectTable0[idx];

    if (arg3 < 4)
    {
        addPrim(&ot1->org[arg2], tPage);
    }
    else
    {
        addPrim(&ot0->org[arg2], tPage);
    }

    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);
}

/** Results screen related.
 * Used in: `func_8004F764`
 */
void func_800521A8() // 0x800521A8
{
    GsDOBJ2* ptr;
    s32      i;

    for (i = 0, ptr = D_800C3D78; i < 6; i++, ptr++)
    {
        if ((D_800C3E40 >> i) & 1)
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

/** Used to toggle visibility of object while the inventory scrolring rotates.
 *
 * Used in: `Inventory_Logic`
 *
 * If removed, it may cause items to no longer appear when scrolling,
 * and seems to depend on the scroll direction.
 * Removing some parts will result in no issues rotating one way, but
 * will in the other.
 */
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
        for (i = 0; i < 40; i++)
        {
            if (g_SavegamePtr->items_0[arg1].id_0 == D_800C3BB8[i])
            {
                func_80054720(FS_BUFFER_8, var_s0, i);
                func_8005487C(var_s0);
                i = 40;
            }
        }
    }

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = sp10[i];
    }
}
