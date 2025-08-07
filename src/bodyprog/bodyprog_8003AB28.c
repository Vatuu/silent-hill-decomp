#include "game.h"

#include <libetc.h>
#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/memcard.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

/** Known contents:
 * - Main Menu Funcs
 * - General Game Funcs
 * - Boot Loading Files Funcs
 */

// ========================================
// MAIN MENU
// ========================================

#define MAIN_MENU_OPTION_COUNT 5
#define MAIN_MENU_FOG_COUNT    21

const s32 rodataPad_8002547C = 0;

void GameState_MainMenu_Update() // 0x8003AB28
{
    s32 nextGameStates[5] = // 0x80025480
    {
        GameState_SaveScreen, 
        GameState_DeathLoadScreen,
        GameState_MovieOpening,
        GameState_OptionScreen,
        GameState_MovieIntro
    };

    s32           playIntroFmv;
    s32           prevGameDifficultyIdx;
    s32           nextGameDifficultyIdx;
    s_ShSavegame* save;
    e_GameState   prevState;

    func_80033548();

	/** After staying idle in the title screen for some time, checks if the intro FMV or a
	 * demo gameplay segment should be played. If the next value from `g_Demo_ReproducedCount`
	 * is a value divisible by 3, the intro FMV will play. Otherwise, it defaults to a gameplay
     * demo.
	 */
    playIntroFmv = ((g_Demo_ReproducedCount + 1) % 3) != 0;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_MainMenuState = 0;
        
        if (playIntroFmv != 0)
        {
            g_SysWork.flags_2298 = 1 << 5; // This flag disables player control.
        }
        else
        {
            g_GameWork.gameStateStep_598[0] = 1;
        }
    }

    switch (g_MainMenuState)
    {
        case MenuState_Start:
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            Gfx_ClearRectInterlaced(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Gfx_Init(SCREEN_WIDTH, 1);

            g_IntervalVBlanks = 1;
            g_Gfx_ScreenFade  = 6;
            D_800B5C30        = FP_TIME(2.0f);
            g_MainMenuState++;

        case MenuState_Main:
            if (playIntroFmv != 0)
            {
                GameFs_MapStartUp();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == 0)
                {
                    g_Demo_ReproducedCount++;
                }

                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    g_Demo_ReproducedCount++;
                }
            }

            D_800A9A7C = (1 << 2) | (1 << 3);

            if (g_GameWork.savegame_90.playerHealth_240 > 0)
            {
                D_800A9A7C = (1 << 1) | (1 << 2) | (1 << 3);
            }

            if (D_800BCD28 > 0)
            {
                D_800A9A7C |= (1 << 0) | (1 << 1);
                
                if (D_800A9A88 < D_800BCD28 && g_MainMenu_SelectedOptionIdx != 0)
                {
                    g_MainMenu_SelectedOptionIdx = 1;
                }
            }
            else if (D_800A9A88 > 0)
            {
                while(!(D_800A9A7C & (1 << g_MainMenu_SelectedOptionIdx)))
                {
                    g_MainMenu_SelectedOptionIdx++;
                }
            }

            D_800A9A7C |= D_800A9A7C << MAIN_MENU_OPTION_COUNT;

            if (g_Controller0->btnsPulsed_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                Sd_EngineCmd(Sfx_Back);
                g_GameWork.gameState_594 = GameState_MainMenu;

                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                g_MainMenu_SelectedOptionIdx += MAIN_MENU_OPTION_COUNT;
                while(!(D_800A9A7C & (1 << --g_MainMenu_SelectedOptionIdx)))
                {
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {                
                while(!(D_800A9A7C & (1 << ++g_MainMenu_SelectedOptionIdx)))
                {
                }
            }

            // Wrap selection.
            g_MainMenu_SelectedOptionIdx %= MAIN_MENU_OPTION_COUNT;

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_GameWork.gameState_594 = GameState_MainMenu;

                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }

                g_Gfx_ScreenFade = 2;
                g_MainMenuState++;

                if (g_MainMenu_SelectedOptionIdx < 2u)
                {
                    Sd_EngineCmd(Sfx_StartGame);
                }
                else
                {
                    Sd_EngineCmd(Sfx_Confirm);
                }

                switch (g_MainMenu_SelectedOptionIdx)
                {
                    case 1: // Quick load.
                        if (g_GameWork.savegame_90.playerHealth_240 > 0)
                        {
                            g_GameWork.savegame_30C = g_GameWork.savegame_90;
                        }
                        else
                        {
                            GameFs_SaveLoadBinLoad();
                        }

                        Game_PlayerHeroInit();
                        g_SysWork.flags_2298 = 1 << 4;
                        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
                        break;

                    case 0: // Load save and load menu.
                        GameFs_SaveLoadBinLoad();
                        break;

                    case 2:
                        g_Gfx_ScreenFade = 0;
                        g_MainMenuState  = MenuState_DifficultySelector;
                        break;

                    case 3: // Load options menu.
                        GameFs_OptionBinLoad();
                        break;

                    case 4:
                        break;
                }
            }

            D_800A9A88 = D_800BCD28;

        default:
            break;

        case MenuState_DifficultySelector:
            if (playIntroFmv != 0)
            {
                GameFs_MapStartUp();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == 0)
                {
                    g_Demo_ReproducedCount++;
                }

                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    g_Demo_ReproducedCount++;
                }
            }

            if (g_Controller0->btnsPulsed_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown) ||
                g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_GameWork.gameState_594 = GameState_MainMenu;
                
                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }
            }

            // Scroll game difficulty options.
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                prevGameDifficultyIdx = 2;
                if (g_MainMenu_NewGameSelectedDifficultyIdx > 0)
                {
                    prevGameDifficultyIdx = g_MainMenu_NewGameSelectedDifficultyIdx - 1;
                }
                g_MainMenu_NewGameSelectedDifficultyIdx = prevGameDifficultyIdx;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                nextGameDifficultyIdx = 0;
                if (g_MainMenu_NewGameSelectedDifficultyIdx < 2)
                {
                    nextGameDifficultyIdx = g_MainMenu_NewGameSelectedDifficultyIdx + 1;
                }
                g_MainMenu_NewGameSelectedDifficultyIdx = nextGameDifficultyIdx;
            }

            // Play scroll sound.
            if (g_Controller0->btnsPulsed_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                Sd_EngineCmd(Sfx_Back);
            }

            // Select game difficulty.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Game_SavegameInitialize(0, g_MainMenu_NewGameSelectedDifficultyIdx - 1);
                Game_PlayerHeroInit();

                g_SysWork.flags_2298 = 1 << 2;

                GameFs_MapLoad(MapOverlayId_MAP0_S00);
                GameFs_StreamBinLoad();
                Sd_EngineCmd(Sfx_StartGame);

                g_Gfx_ScreenFade = 2;
                g_MainMenuState  = 4;
            }
            // Cancel
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(Sfx_Cancel);
                g_MainMenuState = 1;
            }
            break;

        case MenuState_LoadGame:
        case MenuState_NewGameStart:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                Gfx_ScreenRefresh(SCREEN_WIDTH, 0);
                Fs_QueueWaitForEmpty();

                if (g_GameWork.savegame_90.playerHealth_240 > 0)
                {
                    nextGameStates[1] = 10;
                }

                if (g_MainMenu_SelectedOptionIdx == 2)
                {
                    Chara_PositionUpdateFromParams(g_MapOverlayHeader.mapAreaLoadParams_1C);
                }

                func_8002E830();

                prevState                       = g_GameWork.gameState_594;
                g_GameWork.gameStateStep_598[0] = prevState;
                g_GameWork.gameState_594        = nextGameStates[g_MainMenu_SelectedOptionIdx];
                g_SysWork.timer_1C              = 0;
                g_GameWork.gameStatePrev_590    = prevState;
                g_GameWork.gameStateStep_598[0] = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);
            }
            break;
    }

    if (g_Controller0->btnsHeld_C != 0)
    {
        g_SysWork.timer_20 = 0;
    }

    if (playIntroFmv == 0)
    {
        switch (g_GameWork.gameStateStep_598[0])
        {
            case 1:
                if (g_SysWork.timer_20 > 1740)
                {
                    GameFs_StreamBinLoad();
                    g_GameWork.gameStateStep_598[0]++;
                }
                break;

            case 2:
                if (Fs_QueueGetLength() == 0)
                {
                    g_Demo_ReproducedCount++;

                    g_GameWork.background2dColor_R_58C = 0;
                    g_GameWork.background2dColor_G_58D = 0;
                    g_GameWork.background2dColor_B_58E = 0;

                    Game_StateSetNext(GameState_MovieIntro);
                }
                break;
        }
    }

    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        Gfx_MainMenu_BackgroundDraw();
        func_8003B560();

        if (g_MainMenuState < 3)
        {
            Gfx_MainMenu_MainTextDraw();
            return;
        }

        Gfx_MainMenu_DifficultyTextDraw(g_MainMenu_NewGameSelectedDifficultyIdx);
        return;
    }

    *(s32*)0x1F800000 = 0x200000;
    *(s32*)0x1F800004 = 0x01C00140;
    ClearImage2((RECT*)0x1F800000, 0u, 0u, 0u);
    Gfx_Init(SCREEN_WIDTH, 0);
}

void MainMenu_SelectedOptionIdxReset() // 0x8003B550
{
    g_MainMenu_SelectedOptionIdx = 1;
}

void func_8003B560() {}

const char D_800254C0[] = "EXTRA";
const char D_800254C8[] = "OPTION";
const char D_800254D0[] = "START";
const char D_800254D8[] = "CONTINUE";
const char D_800254E4[] = "LOAD";

void Gfx_MainMenu_MainTextDraw() // 0x8003B568
{
    static const u8 D_800254EC[] = { 0x1D, 0x32, 0x20, 0x27, 0x21 };
    extern char*    D_800A9A8C[]; // TODO: Points to `D_800254C0` etc. strings above, needs .data?

    #define STR_POS_X_BASE 158
    #define STR_POS_Y_BASE 184

    s32 i;

    // Run through options.
    for (i = 0; i < MAIN_MENU_OPTION_COUNT; i++)
    {
        if (D_800A9A7C & (1 << i))
        {
            Gfx_StringSetPosition(STR_POS_X_BASE - D_800254EC[i], STR_POS_Y_BASE + (i * 20));
            Gfx_StringSetColor(ColorId_White);

            if (i == g_MainMenu_SelectedOptionIdx)
            {
                Gfx_StringDraw("[", 99);
            }
            else
            {
                Gfx_StringDraw("_", 99);
            }

            Gfx_StringDraw(D_800A9A8C[i], 99);

            if (i == g_MainMenu_SelectedOptionIdx)
            {
                Gfx_StringDraw("]", 99);
            }

            Gfx_StringDraw("\n", 99);
        }
    }
}

const char D_80025504[] = "HARD";
const char D_8002550C[] = "NORMAL";
const char D_80025514[] = "EASY";

void Gfx_MainMenu_DifficultyTextDraw(s32 arg0) // 0x8003B678
{
    static const u8 D_8002551C[] = { 0x1C, 0x2B, 0x1E, 0x4C, 0x00, 0x95, 0xAB, 0x90, 0x00, 0x00, 0x00, 0x00 }; // Only first 3 are used, what are others for?
    extern char*    D_800A9AA0[]; // TODO: points to `D_80025504` etc strings above, needs .data?

    s32 i;

    for (i = 0; i < 3; i++)
    {
        Gfx_StringSetPosition(158 - D_8002551C[i], 204 + (20 * i));
        Gfx_StringSetColor(ColorId_White);

        if (i == arg0)
        {
            Gfx_StringDraw("[", 99);
        }
        else
        {
            Gfx_StringDraw("_", 99);
        }

        Gfx_StringDraw(D_800A9AA0[i], 99);

        if (i == arg0)
        {
            Gfx_StringDraw("]", 99);
        }

        Gfx_StringDraw("\n", 99);
    }
}

void Gfx_MainMenu_BackgroundDraw() // 0x8003B758
{
    if (g_SysWork.sysState_8 == 0)
    {
        g_SysWork.sysState_8     = 1;
        g_SysWork.timer_24       = 0;
        g_SysWork.sysStateStep_C = 0;
        g_SysWork.field_28       = 0;
        g_SysWork.field_10       = 0;
        g_SysWork.timer_2C       = 0;
        g_SysWork.field_14       = 0;
        func_8003BCF4();
    }

    Gfx_BackgroundSpriteDraw(&g_TitleImg);
    Gfx_MainMenu_FogUpdate();
}

void func_8003B7BC() // 0x8003B7BC
{
    // Can't be `s32*` since 462 doesn't divide by 4, so I'm guessing it's `s8`.
    s8* s0 = 0x801E2432;

    memset(s0, 0, 462);
    D_800BCDE0 = s0;
}

u32 func_8003B7FC(s32 idx) // 0x8003B7FC
{
    u8  idx0 = D_800BCDE0[idx];
    u32 val  = D_800A9AAC[idx0];

    if (idx < 210)
    {
        return 0x3A000000;
    }

    return val;
}

PACKET* Gfx_MainMenu_FogPacketGet(GsOT* ot, PACKET* packet) // 0x8003B838
{
    s32      yOffset;
    s32      i;
    s32      j;
    s32      color0;
    s32      color2;
    s32      color3;
    s32      color1;
    POLY_G4* poly;

    for (i = 10; i < MAIN_MENU_FOG_COUNT; i++)
    {
        color1 = func_8003B7FC(MAIN_MENU_FOG_COUNT * (i - 1));
        color3 = func_8003B7FC(MAIN_MENU_FOG_COUNT * i);

        for (j = 1; j < MAIN_MENU_FOG_COUNT; j++)
        {
            color2 = color3;
            color0 = color1;

            color1 = func_8003B7FC(j + (MAIN_MENU_FOG_COUNT * (i - 1)));
            color3 = func_8003B7FC(j + (MAIN_MENU_FOG_COUNT * i));

            poly = packet;
            setPolyG4(poly);

            yOffset = (i - 1) * 24;

            setXY4(poly,
                   -176 + (16 * j), yOffset - 208,
                   -160 + (16 * j), yOffset - 208,
                   -176 + (16 * j), yOffset - 184,
                   -160 + (16 * j), yOffset - 184);

            *((u32*)&poly->r0) = color0;
            *((u32*)&poly->r1) = color1;
            *((u32*)&poly->r2) = color2;
            *((u32*)&poly->r3) = color3;

            addPrim(ot, poly);
            packet += sizeof(POLY_G4);
        }
    }

    return packet;
}

void Gfx_MainMenu_FogDraw() // 0x8003BA08
{
    PACKET*   packet;
    GsOT_TAG* tag;

    tag    = g_ObjectTable1[g_ObjectTableIdx].org;
    packet = Gfx_MainMenu_FogPacketGet(&tag[6], GsOUT_PACKET_P);
    SetDrawMode((DR_MODE*)packet, 0, 1, 0x2A, NULL);
    addPrim(&tag[6], packet);
    GsOUT_PACKET_P = packet + sizeof(DR_MODE);
}

void Gfx_MainMenu_FogRandomize() // 0x8003BAC4
{
    s32 idx;
    s32 i;
    s32 val;
    s8* ptr;
    u8* ptr1;
    s8* ptr2;

    ptr         = D_800BCDE0;
    ptr1        = ptr + 441;
    D_800A9EAC += 4 + ((s32)Rng_Rand16() & 0x7);
    val         = FP_MULTIPLY(shRsin(D_800A9EAC), 10, Q12_SHIFT) - 122;
    ptr2        = ptr + 461;

    for (i = 20; i >= 0; i--)
    {
        *ptr2-- = val;
    }

    for (i = 0; i < 16; i++)
    {
        idx       = (s32)Rng_Rand16() % MAIN_MENU_FOG_COUNT;
        ptr1[idx] = NO_VALUE;
    }

    for (i = 0; i < 9; i++)
    {
        idx       = (s32)Rng_Rand16() % MAIN_MENU_FOG_COUNT;
        ptr1[idx] = 0;
    }
}

void Gfx_MainMenu_FogScatter() // 0x8003BBF4
{
    s32 i;
    s32 j;
    s32 val;
    u8* ptr;

    Gfx_MainMenu_FogRandomize();

    for (i = 0; i < MAIN_MENU_FOG_COUNT; i++)
    {
        ptr = &D_800BCDE0[i * MAIN_MENU_FOG_COUNT];
        
        for (j = 0; j < MAIN_MENU_FOG_COUNT; j++)
        {
            val   = ptr[j + MAIN_MENU_FOG_COUNT];
            val  += ptr[j - 1];
            val  += ptr[j];
            val  += ptr[j + 1];
            val >>= 2;
            val--;
            
            if (val <= 0) 
            {
                ptr[j] = 0;
            } 
            else 
            {
                ptr[j] = val;
            }
        }
    }
}

void Gfx_MainMenu_FogUpdate() // 0x8003BC8C
{
    if (D_800A9EB0 == ((D_800A9EB0 / 5) * 5))
    {
        Gfx_MainMenu_FogScatter(D_800A9EB0);
    }

    D_800A9EB0++;
    Gfx_MainMenu_FogDraw();
}

void func_8003BCF4() // 0x8003BCF4
{
    s32 i;

    func_8003B7BC();

    for (i = 0; i < 30; i++)
    {
        Gfx_MainMenu_FogScatter();
    }
}

// ========================================
// UNKNOWN
// ========================================

// TODO: Remake this whenever we have further context of `D_8002500C`.
s32 func_8003BD2C() // 0x8003BD2C
{
    return ((s32*)D_800BCE18.field_0[0].field_0 - &D_8002500C) >> 2;
}

void func_8003BD48(s_SubCharacter* chara) // 0x8003BD48
{
    u16 var_s0;

    D_800BCE14 = func_80069810();
    var_s0     = D_800BCE14;

    switch (func_8003BD2C())
    {
        case 0:
            if (chara->position_18.vx >= FP_METER(191.6f) && chara->position_18.vx <= FP_METER(198.8f) && 
                chara->position_18.vz >= FP_METER(-96.0f) && chara->position_18.vz <= FP_METER(-90.3f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
            break;

        case 3:
        case 4:
            if(chara->position_18.vx >= FP_METER(-100.0f) && chara->position_18.vx <= FP_METER(-94.5f) && 
               chara->position_18.vz >= FP_METER(-70.3f) && chara->position_18.vz <= FP_METER(-62.0f)) 
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
    }

    func_80069820(var_s0);
}

void func_8003BE28() // 0x8003BE28
{
    func_80069820(D_800BCE14);
}

s32 func_8003BE50(s32 idx) // 0x8003BE50
{
    return &D_800BCE18.field_0[0].field_18[idx]->field_14.field_C;
}

// ========================================
// BOOT LOADING FILES
// ========================================

void GameFs_BgEtcGfxLoad() // 0x8003BE6C
{
    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &D_800A9EB4);
}

void GameFs_BgItemLoad() // 0x8003BE9C
{
    D_800BCE18.field_1BE4.queueIdx_1000 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &D_800BCE18.field_1BE4);
}

void func_8003BED0() // 0x8003BED0
{
    s_800BE9FC* D_800BE9FC = &D_800BCE18.field_1BE4;

    if (Fs_QueueIsEntryLoaded(D_800BE9FC->queueIdx_1000) == 0 || D_800BE9FC->field_2 != 0)
    {
        return;
    }

    func_800560FC(&D_800BCE18.field_1BE4);
    func_80056504(&D_800BCE18.field_1BE4, "TIM00", &D_800A9EBC, 1);
    func_80056504(&D_800BCE18.field_1BE4, "BG_ETC", &D_800A9EC4, 1);
    func_80056954(&D_800BCE18.field_1BE4);
}

// ========================================
// UNKNOWN
// ========================================

extern s_800C4168 const D_800C4168;

s32 func_8003BF60(s32 x, s32 z) // 0x8003BF60
{
    s32               ret;
    s8                val;
    s_800BCE18_0_0_C* ptr;

    ret = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == 0)
    {
        return 1;
    }

    if (D_800BCE18.field_0[0].field_0->field_C != NULL)
    {
        ptr = D_800BCE18.field_0[0].field_0->field_C;
        val = ptr->field_0;
     
        if (val != NO_VALUE)
        {
            do 
            {
                if (x >= (ptr->field_2 << 8) && (ptr->field_4 << 8) >= x &&
                    z >= (ptr->field_6 << 8) && (ptr->field_8 << 8) >= z &&
                    ret < val)
                {
                    ret = val;
                }

                ptr++;
                val = ptr->field_0;
            }
            while (val != NO_VALUE);
        }
    }

    return ret;
}

void func_8003C048() // 0x8003C048
{
    func_80055028();

    D_800BCE18.field_0[0].field_4 = 0;

    func_80041C24((s_80041CEC*)0x8016B600, 0x80175600, 0x2C000);
    func_800697EC();

    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    func_8003EBA0();
    func_8005B55C(vwGetViewCoord());
    func_8003CB3C(&D_800BCE18);
}

void func_8003C0C0() // 0x8003C0C0
{
    s_800BCE18_1BAC* ptr = &D_800BCE18.field_1BAC;

    ptr->field_0  = NO_VALUE;
    ptr->field_14 = (s_800BE9FC*)(Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FE600); // `field_14` defined as a pointer?
    ptr->field_18 = 0;
    ptr->field_1C = 0;
    ptr->field_20 = 0;
}

void func_8003C110() // 0x8003C110
{
    s32              i;
    s_800BCE18_0_CC* var_s0;

    for (i = 0; i < 45; i++)
    {
        if (i != 1)
        {
            D_800BCE18.field_0->field_18[i] = NULL;
        }
    } 

    D_800BCE18.field_0[0].field_14 = Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FEE00;

    // TODO: This part could be rewritten in a less confusing way.
    var_s0 = &D_800BCE18.field_0[0].field_CC;

    while ((u32)var_s0 < (u32)&D_800BCE18.field_164C)
    {
        func_8003C1AC((u32)var_s0);
        var_s0 = (int)var_s0 + sizeof(s_800BCE18_0); // TODO: Fake match.
    } 
}

void func_8003C1AC(s_800BCE18_0_CC* arg0) // 0x8003C1AC
{
    s_FsImageDesc sp10 = { 0 };

    //memset(&sp10, 0, 8);
    arg0->field_0 = 0;
    arg0->field_1 = 0;
    arg0->field_4 = 0;
    arg0->field_8 = (s32)(Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FEE00);
    arg0->field_C = sp10;
}

/** TODO: Remake the function with new context.
 * This function is used in `GameFs_MapStartUp`, there the values
 * passed are the pointer to `g_MapOverlayHeader` (arg0), the position
 * at X of the player (arg1) and the position at Y of the player (arg2).
 */
void func_8003C220(s_sub_800BCE18_0** arg0, s32 arg1, s32 arg2) // 0x8003C220
{
    s32               var_a2;
    u8                temp_v1;
    s_sub_800BCE18_0* ptr;

    D_800BCE18.field_0[0].field_0 = *arg0;
    temp_v1 = (*arg0)->field_6;

    if (temp_v1 & (1 << 0)) 
    {
        var_a2 = 1;
    } 
    else if (temp_v1 & (1 << 1)) 
    {
        var_a2 = 2;
    }
    else
    {
        var_a2 = 4;
    }

    ptr = *arg0;
    func_800421D8(&ptr->field_2, ptr->field_0, var_a2, ((ptr->field_6 >> 2) ^ 1) & (1 << 0), 0, 0);

    if (*arg0 == &D_8002500C) 
    {
        func_80041ED0(0x467, -1, 8);
    }
    
    func_80042C3C(arg1, arg2, arg1, arg2);
}

void func_8003C2EC() // 0x8003C2EC
{
    func_80041FF0();
}

void func_8003C30C() // 0x8003C30C
{
    u8 temp_v1;

    temp_v1 = D_800BCE18.field_0[0].field_0->field_6;
    
    if ((temp_v1 & 4) && (temp_v1 & 3)) 
    {
        func_800420C0();
        return;
    }
    func_80041FF0();
    func_8004201C();
}

void func_8003C368() // 0x8003C368
{
    D_800BCE18.field_0[0].field_4 = 1;
    D_800BCE18.field_0[0].field_8 = g_SysWork.player_4C.chara_0.position_18;
}

void func_8003C3A0() // 0x8003C3A0
{
    D_800BCE18.field_0[0].field_4 = 0;
}

void func_8003C3AC() // 0x8003C3AC
{
    VECTOR3         sp10;
    VECTOR3         sp20;
    SVECTOR         sp30;
    s32             temp_a1;
    s32             temp_a2;
    s32             temp_s0;
    s32             temp_s0_2;
    s32             temp_v0_3;
    s32             temp_v1;
    s32             temp_v1_4;
    s32             var_a0;
    s32             var_a1;
    s32             var_s1;
    u8              temp_v1_3;
    u8              temp_v1_6;
    s_SubCharacter* chara = &g_SysWork.player_4C.chara_0;

    if ((u8)D_800BCE18.field_0[0].field_4 != 0)
    {
        sp10 = D_800BCE18.field_0[0].field_8;
    }
    else
    {
        sp10 = chara->position_18;
    }

    temp_s0 = (chara->moveSpeed_38 * 0x5800) / 16015;
    temp_s0 = CLAMP(temp_s0, 0, 0x5800);

    sp10.vx += FP_MULTIPLY((s64)temp_s0, shRsin(chara->headingAngle_3C), Q12_SHIFT);
    sp10.vz += FP_MULTIPLY((s64)temp_s0, shRcos(chara->headingAngle_3C), Q12_SHIFT);

    if (D_800BCE18.field_0[0].field_0 == &D_8002500C &&
        chara->position_18.vx >= FP_METER(-40.0f) && chara->position_18.vx <= FP_METER(40.0f) &&
        chara->position_18.vz >= FP_METER(200.0f) && chara->position_18.vz <= FP_METER(240.0f))
    {

        sp10.vz = FP_METER(200.0f);
    }

    if (D_800C4169 != 0)
    {
        vwGetViewPosition(&sp20);
        vwGetViewAngle(&sp30);

        temp_v1_3 = D_800BCE18.field_0[0].field_0->field_6;
        if (!(temp_v1_3 & 0x4) || !(temp_v1_3 & 0x3))
        {
            var_s1 = FP_MULTIPLY(shRcos(sp30.vx), 0x9000, Q12_SHIFT);
        }
        else
        {
            var_s1 = 0;
        }
        
        temp_s0_2 = FP_MULTIPLY(var_s1, shRsin(sp30.vy), Q12_SHIFT);
        temp_s0_2 = CLAMP(temp_s0_2, -0x6000, 0x6000);

        temp_v1_4 = FP_MULTIPLY(var_s1, shRcos(sp30.vy), Q12_SHIFT);
        temp_v1_4 = CLAMP(temp_v1_4, -0x6000, 0x6000);

        sp20.vx += temp_s0_2;
        sp20.vz += temp_v1_4;

        if (Vc_VectorMagnitudeCalc(sp20.vx - chara->position_18.vx, 0, sp20.vz - chara->position_18.vz) > 0x10000)
        {
            var_s1  = 0xE000;
            sp20.vx = chara->position_18.vx + FP_MULTIPLY(shRsin(sp30.vy), var_s1, Q12_SHIFT);
            sp20.vz = chara->position_18.vz + FP_MULTIPLY(shRcos(sp30.vy), var_s1, Q12_SHIFT);
        }
    } 
    else
    {
        sp20     = chara->position_18;
        sp20.vx += FP_FROM(FP_TO(shRsin(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
        sp20.vz += FP_FROM(FP_TO(shRcos(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
    }

    temp_v1_6 = D_800BCE18.field_0[0].field_0->field_6;

    if ((temp_v1_6 & 0x4) && (temp_v1_6 & 0x3))
    {
        var_a1 = chara->position_18.vx / 10240;
        if (chara->position_18.vx < 0)
        {
            var_a1 -= 1;
        }

        var_a0  = chara->position_18.vz / 10240;
        temp_a1 = var_a1 * 0x2800;

        if (chara->position_18.vz < 0)
        {
            var_a0 -= 1;
        }

        temp_a2 = var_a0 * 0x2800;

        sp10.vx = CLAMP(sp10.vx, temp_a1 + 1, temp_a1 + 0x27FF);
        sp10.vz = CLAMP(sp10.vz, temp_a2 + 1, temp_a2 + 0x27FF);
        sp20.vx = CLAMP(sp20.vx, temp_a1 + 1, temp_a1 + 0x27FF);
        sp20.vz = CLAMP(sp20.vz, temp_a2 + 1, temp_a2 + 0x27FF);

    }

    func_80042C3C(sp10.vx, sp10.vz, sp20.vx, sp20.vz);
}

s32 func_8003C850() // 0x8003C850
{
    func_8003C3AC();
    func_80043740();
}

void func_8003C878(s32 arg0) // 0x8003C878
{
    func_8003CB44(&D_800BCE18);

    while (func_80043830())
    {
        func_8003C3AC();
        Fs_QueueWaitForEmpty();
    }

    func_80043A24(&g_ObjectTable0[g_ObjectTableIdx], arg0);
    func_800550D0();
}

void func_8003C8F8(s_800BCE18_2BEC_0* arg0, s8* newStr) // 0x8003C8F8
{
    arg0->field_10.field_9 = 0;
    arg0->field_0          = 0;

    func_80056D64(&arg0->field_10.field_0, newStr);

    arg0->field_10.field_8 = 0;
}

void func_8003C92C(s_800BCE18_2BEC_0* arg0, VECTOR3* pos, SVECTOR3* rot) // 0x8003C92C
{
    s32              vy;
    s32              coord1;
    s32              vx;
    s32              vz;
    s32              coord0;
    s32              coord2;
    s32              i;
    s32              ret;
    s_800BCE18_2BEC* ptr;

    if (D_800BCE18.field_2BE8 < 29)
    {
        if (arg0->field_10.field_9 == 0)
        {
            func_8003BED0();
            ret = func_8004287C(arg0, &arg0->field_10, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz);

            if (ret == 0)
            {
                if (func_80056CB4(arg0, &D_800BCE18.field_1BE4, &arg0->field_10) == 0)
                {
                    return;
                }
                else
                {
                    ret = 1;
                }
            }

            arg0->field_10.field_9 = ret;
        } 

        coord0 = FP_FROM(pos->vx, Q4_SHIFT);
        coord1 = FP_FROM(pos->vy, Q4_SHIFT);
        coord2 = FP_FROM(pos->vz, Q4_SHIFT);
        vx     = rot->vx >> 2;
        vz     = rot->vz >> 2;
        vy     = rot->vy;

        for (i = 0; i < D_800BCE18.field_2BE8; i++)
        {
            ptr = &D_800BCE18.field_2BEC[i];
    
            if (arg0 == ptr->field_0 &&
                coord0 == ptr->gsCoordinate0_4 &&
                coord2 == ptr->gsCoordinate2_8 &&
                coord1 == ptr->gsCoordinate1_4 &&
                vx == ptr->vx_C &&
                vy == ptr->vy_C &&
                vz == ptr->vz_C)
            {
                return;
            }
        }

        ptr = &D_800BCE18.field_2BEC[D_800BCE18.field_2BE8];

        ptr->vx_C = vx;
        ptr->vy_C = vy;

        // Required for match.
        if (ptr->gsCoordinate2_8) {}

        ptr->vz_C            = vz;
        ptr->field_0         = arg0;
        ptr->gsCoordinate0_4 = coord0;
        ptr->gsCoordinate1_4 = coord1;
        ptr->gsCoordinate2_8 = coord2;
        D_800BCE18.field_2BE8++;
    }
}

void func_8003CB3C(s_800BCE18* arg0) // 0x8003CB3C
{
    arg0->field_2BE8 = 0;
}

void func_8003CB44(s_800BCE18* arg0) // 0x8003CB44
{
    s_800BCE18_2BEC* ptr;

    for (ptr = &arg0->field_2BEC[0]; ptr < &arg0->field_2BEC[arg0->field_2BE8]; ptr++)
    {
        func_8003CBA4(ptr);
    }

    arg0->field_2BE8 = 0;
}

void func_8003CBA4(s_800BCE18_2BEC* arg0) // 0x8003CBA4
{
    GsCOORDINATE2 coord;
    SVECTOR       vec;
    MATRIX        mats[2];

    coord.flg   = 0;
    coord.super = 0;

    coord.coord.t[0] = arg0->gsCoordinate0_4;
    coord.coord.t[1] = arg0->gsCoordinate1_4;
    coord.coord.t[2] = arg0->gsCoordinate2_8;

    // Unpack XYZ bitfield (TODO: Was this used anywhere else?)
    vec.vx = arg0->vx_C << 2;
    vec.vy = arg0->vy_C;
    vec.vz = arg0->vz_C << 2;

    func_80096C94(&vec, &coord.coord);
    func_80049B6C(&coord, &mats[1], &mats[0]);
    func_8003CC7C(arg0->field_0, &mats[0], &mats[1]);
}

void func_8003CC7C(s_800BCE18_2BEC_0* arg0, MATRIX* arg1, MATRIX* arg2) // 0x8003CC7C
{
    s8                    temp_a0;
    s_800BCE18_2BEC_0_10* temp_s1;
    s_800BCE18_2BEC_0_10* temp_s2;

    temp_a0 = arg0->field_10.field_9;
    if (!temp_a0)
    {
        return;
    }

    temp_s2 = arg0->field_8;
    temp_s1 = &arg0->field_10;

    if (temp_a0 >= 3 && temp_a0 < 7)
    {
        if (!func_80042C04(temp_a0 - 3))
        {
            arg0->field_10.field_9 = 0;
        }
    }

    if (temp_s1->field_0 != temp_s2->field_0 || temp_s1->field_4 != temp_s2->field_4)
    {
        arg0->field_10.field_9 = 0;
        return;
    }

    func_80057090(arg0, &g_ObjectTable0[g_ObjectTableIdx], 1, arg1, arg2, 0);
}

s32 func_8003CD5C() // 0x8003CD5C
{
    return D_800BCE18.field_1BAC.field_0;
}

void func_8003CD6C(s_PlayerCombat* arg0) // 0x8003CD6C
{
    s32 var_a0;
    s8  temp_v0;

    temp_v0 = arg0->field_F;
    var_a0  = NO_VALUE;
    if (temp_v0 != NO_VALUE)
    {
        var_a0 = temp_v0 + 0x80;
    }

    func_8003CDA0(var_a0);
}

s32 func_8003CDA0(s32 itemIdx)
{
    s32              fileIdx;
    s_800BCE18_1BAC* ptr;

    ptr = &D_800BCE18.field_1BAC;

    if (ptr->field_0 == itemIdx)
    {
        return 0;
    }

    ptr->field_0 = itemIdx;

    switch (itemIdx)
    {
        default:
            fileIdx = NO_VALUE;
            break;
        case NO_VALUE:
        case 128:
        case 132:
        case 135:
        case 160:
        case 161:
        case 162:
            fileIdx      = NO_VALUE;
            ptr->field_8 = "HERO";
            break;
        case InventoryItemId_SteelPipe:
            fileIdx      = FILE_ITEM_PIPE_TIM;
            ptr->field_8 = "PIPE";
            break;
        case 164:
            fileIdx      = FILE_ITEM_PHONE_TIM;
            ptr->field_8 = "PHONE";
            break;
        case 165:
            fileIdx      = FILE_ITEM_FLAUROS_TIM;
            ptr->field_8 = "FLAUROS";
            break;
        case 166:
            fileIdx      = FILE_ITEM_AGLA_TIM;
            ptr->field_8 = "AGLA";
            break;
        case 167:
            fileIdx      = FILE_ITEM_BOTL_TIM;
            ptr->field_8 = "BOTL";
            break;
        case 168:
            fileIdx      = FILE_ITEM_BABY_TIM;
            ptr->field_8 = "BABY";
            break;
        case 169:
            fileIdx      = FILE_ITEM_BLOOD_TIM;
            ptr->field_8 = "BLOOD";
            break;
        case InventoryItemId_Chainsaw:
            fileIdx      = FILE_ITEM_CSAW_TIM;
            ptr->field_8 = "CSAW";
            break;
        case InventoryItemId_HyperBlaster:
            fileIdx      = FILE_ITEM_HPRGUN_TIM;
            ptr->field_8 = "HPRGUN";
            break;
        case InventoryItemId_RockDrill:
            fileIdx      = FILE_ITEM_DRILL_TIM;
            ptr->field_8 = "DRILL";
            break;
        case InventoryItemId_Katana:
            fileIdx      = FILE_ITEM_KATANA_TIM;
            ptr->field_8 = "KATANA";
            break;
    }

    if (fileIdx == NO_VALUE)
    {
        ptr->imageDesc_C.tPage[1] = 27;
        ptr->imageDesc_C.tPage[0] = 0;
        ptr->imageDesc_C.u        = 0;
        ptr->imageDesc_C.v        = 0;
        ptr->imageDesc_C.clutX    = 736;
        ptr->imageDesc_C.clutY    = 480;
    }
    else
    {
        ptr->imageDesc_C.tPage[1] = 27;
        ptr->imageDesc_C.tPage[0] = 0;
        ptr->imageDesc_C.u        = 48;
        ptr->imageDesc_C.v        = 224;
        ptr->imageDesc_C.clutX    = 736;
        ptr->imageDesc_C.clutY    = 498;
    }

    if (fileIdx != NO_VALUE)
    {
        ptr->field_4 = Fs_QueueStartReadTim(fileIdx, FS_BUFFER_10, &ptr->imageDesc_C);
    }

    switch (itemIdx)
    {
        case NO_VALUE:
        default:
            fileIdx = NO_VALUE;
            break;
        case InventoryItemId_KitchenKnife:
            fileIdx = FILE_ITEM_KNIFE_PLM;
            break;
        case InventoryItemId_SteelPipe:
            fileIdx = FILE_ITEM_PIPE_PLM;
            break;
        case InventoryItemId_Hammer:
            fileIdx = FILE_ITEM_HAMMER_PLM;
            break;
        case InventoryItemId_Axe:
            fileIdx = FILE_ITEM_AXE_PLM;
            break;
        case InventoryItemId_Handgun:
            fileIdx = FILE_ITEM_HANDGUN_PLM;
            break;
        case InventoryItemId_HuntingRifle:
            fileIdx = FILE_ITEM_RIFLE_PLM;
            break;
        case InventoryItemId_Shotgun:
            fileIdx = FILE_ITEM_SHOTGUN_PLM;
            break;
        case 164:
            fileIdx = FILE_ITEM_PHONE_PLM;
            break;
        case 165:
            fileIdx = FILE_ITEM_FLAUROS_PLM;
            break;
        case 166:
            fileIdx = FILE_ITEM_AGLA_PLM;
            break;
        case 167:
            fileIdx = FILE_ITEM_BOTL_PLM;
            break;
        case 168:
            fileIdx = FILE_ITEM_BABY_PLM;
            break;
        case 169:
            fileIdx = FILE_ITEM_BLOOD_PLM;
            break;
        case InventoryItemId_Chainsaw:
            fileIdx = FILE_ITEM_CSAW_PLM;
            break;
        case InventoryItemId_HyperBlaster:
            fileIdx = FILE_ITEM_HPRGUN_PLM;
            break;
        case InventoryItemId_RockDrill:
            fileIdx = FILE_ITEM_DRILL_PLM;
            break;
        case InventoryItemId_Katana:
            fileIdx = FILE_ITEM_KATANA_PLM;
            break;
    }

    if (fileIdx != NO_VALUE)
    {
        ptr->field_4 = Fs_QueueStartRead(fileIdx, ptr->field_14);
        return ptr->field_4;
    }

    return 0;
}

void func_8003D01C() // 0x8003D01C
{
    D_800BCE18.field_1BAC.field_18 &= ~(1 << 31);
}

void func_8003D03C() // 0x8003D03C
{
    D_800BCE18.field_1BAC.field_18 |= 1 << 31;
}

void func_8003D058() // 0x8003D058
{
    MATRIX           mat0;
    MATRIX           mat1;
    GsCOORDINATE2*   coord;
    s_800BCE18_1BAC* ptr0;
    s_800BE9FC*      ptr1;

    ptr0 = &D_800BCE18.field_1BAC;

    if (ptr0->field_0 != NO_VALUE) 
    {
        if (ptr0->field_0 == 164)
        {
            coord = &g_SysWork.playerBoneCoords_890[6];
        } 
        else 
        {
            coord = &g_SysWork.playerBoneCoords_890[10];
        }

        if (Fs_QueueIsEntryLoaded(ptr0->field_4) != 0) 
        {
            ptr1 = ptr0->field_14;

            if (ptr1->field_2 == 0)
            {
                func_800560FC(ptr1);
                func_80056504(ptr1, ptr0->field_8, &ptr0->imageDesc_C, 1);
                func_80056954(ptr1);
                func_80056C8C(&ptr0->field_18, ptr0->field_14, 0);
            }

            func_80049B6C(coord, &mat1, &mat0);
            func_80057090(&ptr0->field_18, &g_ObjectTable0[g_ObjectTableIdx], 1, &mat0, &mat1, 0);
        }
    }
}

void func_8003D160() // 0x8003D160
{
    s_FsImageDesc    img;
    s32              queueIdx;
    s_800BCE18*      ptr;
    s_800BCE18_0_CC* ptr2;
    void*            addr = (void*)0x800FE600;

    func_8003D3BC(&img, 1, 0);

    ptr                               = &D_800BCE18;
    ptr2                              = &ptr->field_164C;
    D_800BCE18.field_0[0].field_18[1] = ptr2;

    Fs_QueueStartRead(g_Chara_FileInfo[1].modelFileIdx, addr);
    queueIdx = Fs_QueueStartReadTim(g_Chara_FileInfo[1].textureFileIdx, FS_BUFFER_1, &img);

    D_800BCE18.field_164C.field_0 = 1;
    ptr2->field_1                 = 0;
    ptr2->field_4                 = queueIdx;
    ptr2->field_8                 = addr;
    D_800BCE18.field_164C.field_C = img;
}

s32 func_8003D21C(s_MapOverlayHeader* arg0) // 0x8003D21C
{
    s_FsImageDesc    img;
    s32              j;
    s32              var_s3;
    s32              i;
    s32              ret;
    s32              ids;
    s_800BCE18_0_CC* ptr;

    for (ret                            = 0,
         i                              = 0,
         D_800BCE18.field_0[0].field_14 = Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FEE00,
         var_s3                         = 0;
         i < 4; i++)
    {
        ids = arg0->charaGroupIds_248[i];
        ptr = &D_800BCE18.field_0[i].field_CC;

        if (ids != 0) 
        {
            if (var_s3 == 0) 
            {
                if (ids != ptr->field_0) 
                {
                    var_s3 = 1;
                    for (j = i; j < 4; j++)
                    {
                        D_800BCE18.field_0[j].field_CC.field_0 = 0;
                    }
                }
            } 

            if (var_s3 != 0) 
            {
                func_8003D3BC(&img, ids, i);
                ret = func_8003D7D4(ids, i, D_800BCE18.field_0[0].field_14, &img);
            }

            func_8003D354(&D_800BCE18.field_0[0].field_14, ids);
        }
    }

    return ret;
}

void func_8003D354(s32* arg0, s32 arg1) // 0x8003D354
{
    s16 idx;
    s32 fileSize;

    idx      = g_Chara_FileInfo[arg1].modelFileIdx;
    fileSize = Fs_GetFileSize(idx);

    Fs_GetFileSectorAlignedSize(idx);

    *arg0 += (fileSize + 3) & ~0x3;
}

/** Fixes texture UV for NPCs. */
void func_8003D3BC(s_FsImageDesc* img, s32 arg1, s32 arg2) // 0x8003D3BC
{
    s16 clutX;
    s16 clutY;
    s8  tPage;
    s8  v;
    s8  u;

    v = arg1 < 2;

    if (arg1 >= 0 && v)
    {
        tPage = 0x1B;
        v     = 0;
        u     = 0;
        clutX = 0x2E0;
        clutY = 0x1E0;
    }
    else 
    {
        clutY = 0x1D0;
        clutX = (arg2 * 0x10) + 0x2C0;

        switch (arg2)
        {
            default:
                arg2 = 0;

            case 0:
            case 1:
                tPage = 0x1C;
                u     = 0;
                v     = arg2 << 7;
                break;

            case 2:
            case 3:
                tPage = 0x1D;
                u     = 0;
                v     = (arg2 - 2) << 7;
                break;
        }
    }

    img->tPage[0] = 0;
    img->tPage[1] = tPage;
    img->u        = u;
    img->v        = v;
    img->clutX    = clutX;
    img->clutY    = clutY;
}

s32 func_8003D444(s32 idx) // 0x8003D444
{
    return D_800BCE18.field_0[0].field_18[idx] != 0;
}

void func_8003D460() {}

void func_8003D468(s32 arg0, s32 arg1) // 0x8003D468
{
    s16              data[256];
    RECT             rect;
    s32              x;
    s32              i;
    s32              y;
    s_800BCE18_0_CC* temp_s0;

    temp_s0 = D_800BCE18.field_0[0].field_18[arg0];
    func_80056244(temp_s0->field_8);

    rect.x = temp_s0->field_C.clutX;
    rect.y = temp_s0->field_C.clutY;
    rect.w = 16;
    rect.h = 16;

    DrawSync(0);
    StoreImage(&rect, &data);

    for (y = 0, i = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++, i++)
        {
            if (arg1 == 0)
            {
                data[i] &= 0x7FFF;
            }
            else
            {
                data[i] |= 1 << 15;
            }
        }
    }

    LoadImage(&rect, &data);
}

void func_8003D550(s32 arg0, s32 arg1) // 0x8003D550
{
    s_800BCE18_0_CC* ptr;

    ptr = D_800BCE18.field_0[0].field_18[arg0];
    func_80056464(ptr->field_8, g_Chara_FileInfo[arg0].textureFileIdx, &ptr->field_C, arg1);
    func_80056954(ptr->field_8);
}

void func_8003D5B4(s8 flags) // 0x8003D5B4
{
    u8               fileIdx;
    s32              i;
    u32              temp;
    s_800BCE18_0_CC* ptr;

    for (i = 0; i < 4; i++)
    {
        ptr = &D_800BCE18.field_0[i].field_CC;
        if ((flags >> i) & (1 << 0))
        {
            func_8003D6A4(ptr);
        }
    }

    i = 0; 

    D_800BCE18.field_0[0].field_14 = Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FEE00;

    for (; i < 4; i++)
    {
        ptr = &D_800BCE18.field_0[i].field_CC;

        fileIdx = ptr->field_0;
        if (fileIdx != 0)
        {
            temp = ptr->field_8 + Fs_GetFileSize(g_Chara_FileInfo[fileIdx].modelFileIdx);
            if (D_800BCE18.field_0[0].field_14 < temp)
            {
                D_800BCE18.field_0[0].field_14 = temp;
            }
        }
    }
}

void func_8003D6A4(s_800BCE18_0_CC* arg0) // 0x8003D6A4
{
    if (arg0->field_0 != 0)
    {
        D_800BCE18.field_0[0].field_18[arg0->field_0] = NULL;
        func_8003C1AC(arg0);
    }
}

void func_8003D6E0(s32 arg0, s32 arg1, void* arg2, s_FsImageDesc* arg3) // 0x8003D6E0
{
    s_FsImageDesc img;
    void*         var_s0;

    if (arg2 != NULL) 
    {
        var_s0 = arg2;
    } 
    else if (D_800BCE18.field_0[arg1].field_CC.field_0 != 0) 
    {
        var_s0 = D_800BCE18.field_0[arg1].field_CC.field_8;
    } 
    else 
    {
        var_s0 = D_800BCE18.field_0[0].field_14;
        func_8003D354(&D_800BCE18.field_0[0].field_14, arg0);
    }

    if (arg3 != NULL) 
    {
        img = *arg3;
    } 
    else 
    {
        func_8003D3BC(&img, arg0, arg1);
    }

    func_8003D7D4(arg0, arg1, var_s0, &img);
}

s32 func_8003D7D4(u32 arg0, s32 arg1, void* arg2, s_FsImageDesc* img) // 0x8003D7D4
{
    s32              queueIdx;
    s32              idx;
    s_800BCE18_0_CC* ptr;
    s_FsImageDesc*   img0;

    ptr = &D_800BCE18.field_0[arg1].field_CC;
    idx = ptr->field_0;
    img0 = &ptr->field_C;

    if (arg0 == 0) 
    {
        D_800BCE18.field_0[0].field_18[idx] = NULL;
        return 0;
    }

    if (idx != 0) 
    {
        if (arg0 == idx) 
        {
            if (arg2 == ptr->field_8 && memcmp(img, img0, sizeof(s_FsImageDesc)) == 0)
            {
                return 0;
            }
        }

        D_800BCE18.field_0[0].field_18[idx] = NULL;
    }

    D_800BCE18.field_0[0].field_18[arg0] = ptr;

    queueIdx = Fs_QueueStartRead(g_Chara_FileInfo[arg0].modelFileIdx, arg2);

    if (g_Chara_FileInfo[arg0].textureFileIdx != NO_VALUE) 
    {
        queueIdx = Fs_QueueStartReadTim(g_Chara_FileInfo[arg0].textureFileIdx, FS_BUFFER_1, img);
    }

    ptr->field_0 = arg0;
    ptr->field_1 = 0;
    ptr->field_4 = queueIdx;
    ptr->field_8 = arg2;
    ptr->field_C = *img;

    return queueIdx;
}

void func_8003D938() // 0x8003D938
{
    func_8003D9C8(&D_800BCE18.field_164C);
}

void func_8003D95C() // 0x8003D95C
{
    s32 temp_a0;
    s32 i;

    for (i = 0; i < 45; i++)
    {
        if (i != 1) 
        {
            temp_a0 = D_800BCE18.field_0[0].field_18[i];
            if (temp_a0 != 0) 
            {
                func_8003D9C8(temp_a0);
            }
        }
    }
}

void func_8003D9C8(s_800BCE18_0_CC* arg0) // 0x8003D9C8
{
    s_Skeleton* skel;

    if (arg0->field_1 == 0 && arg0->field_0 != 0 && Fs_QueueIsEntryLoaded(arg0->field_4) != 0)
    {
        arg0->field_1 = 1;

        func_800560FC(arg0->field_8);
        func_80056464(arg0->field_8, g_Chara_FileInfo[arg0->field_0].textureFileIdx, &arg0->field_C, g_Chara_FileInfo[arg0->field_0].field_6_10 & 3);

        skel = &arg0->field_14;

        func_80056954(arg0->field_8);
        func_80044FE0(skel, &arg0->field_14.field_C, 56); // TODO: Can't fit `s_Bone` at `field_C`. Check `s_Skeleton` size.
        func_8004506C(skel, arg0->field_8);
        func_800452EC(skel);
        func_800453E8(skel, 1);
    }
}

void func_8003DA9C(s32 arg0, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4) // 0x8003DA9C
{
    s_800C4168_28 sp20 = { 0 };
    u16           ret;

    if (arg0 == 0)
    {
        return;
    }

    arg3 = CLAMP(arg3, FP_FLOAT_TO(0.0f, Q12_SHIFT), FP_FLOAT_TO(1.0f, Q12_SHIFT));

    if (arg0 == 1)
    {
        func_8003D058();
    }

    ret = func_8003DD74(arg0, arg4);

    if (arg3 != 0)
    {
        sp20 = D_800C4168.field_28;

        func_80055330(D_800C4168.field_0, D_800C4168.field_20,
                      D_800C4168.field_3,
                      FP_MULTIPLY(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, (s64)D_800C4168.field_28.field_0, Q12_SHIFT) << 5,
                      FP_MULTIPLY(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, (s64)D_800C4168.field_28.field_1, Q12_SHIFT) << 5,
                      FP_MULTIPLY(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, (s64)D_800C4168.field_28.field_2, Q12_SHIFT) << 5,
                      D_800C4168.field_8);
    }

    func_80045534(&D_800BCE18.field_0[0].field_18[arg0]->field_14, &g_ObjectTable0[g_ObjectTableIdx], arg2,
                  coord, g_Chara_FileInfo[arg0].field_6 * 16, ret, g_Chara_FileInfo[arg0].field_8);

    if (arg3 != 0)
    {
        func_80055330(D_800C4168.field_0, D_800C4168.field_20, D_800C4168.field_3, sp20.field_0 << 5, sp20.field_1 << 5, sp20.field_2 << 5, D_800C4168.field_8);
    }
}

s32 func_8003DD74(s32 arg0, s32 arg1) // 0x8003DD74
{
    return (arg1 << 10) & 0xFC00;
}

void func_8003DD80(s32 idx, s32 arg1) // 0x8003DD80
{
    s_800BCE18_0_CC* temp_a2;

    temp_a2 = D_800BCE18.field_0[0].field_18[idx];

    switch (idx)
    {
        case 1:
            func_8003DE60(&temp_a2->field_14, arg1);
            break;

        case 7:
            func_8003E388(&temp_a2->field_14, arg1);
            break;

        case 26:
        case 27:
            func_8003DF84(&temp_a2->field_14, arg1);
            break;

        case 24:
            func_8003E08C(&temp_a2->field_14, arg1);
            break;

        case 30:
        case 31:
            func_8003E194(&temp_a2->field_14, arg1);
            break;

        case 38:
        case 39:
            func_8003E238(&temp_a2->field_14, arg1);
            break;

        case 14:
            func_8003E414(&temp_a2->field_14, arg1);
            break;

        case 16:
            func_8003E4A0(&temp_a2->field_14, arg1);
            break;

        case 18:
            func_8003E544(&temp_a2->field_14, arg1);
            break;

        default:
            break;
    }
}

void func_8003DE60(s_Skeleton* skel, s32 arg1) // 0x8003DE60
{
    s32 temp_s0;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9ECC, 0);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9ED0, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9ED4, 1);
                break;

            case 3:
                func_80045468(skel, &D_800A9ED8, 1);
                break;

            case 4:
                func_80045468(skel, &D_800A9EDC, 1);
                break;

            case 5:
                func_80045468(skel, &D_800A9EE0, 1);
                break;

            default:
                break;
        }
    }

    temp_s0 = arg1 & 0xF0;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9EE4, 0);

        switch (temp_s0)
        {
            case 16:
                func_80045468(skel, &D_800A9EE8, 1);
                break;

            case 32:
                func_80045468(skel, &D_800A9EEC, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003DF84(s_Skeleton* skel, s32 arg1) // 0x8003DF84
{
    s32 temp_v1;

    temp_v1 = arg1 & 0xF;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 1:
                func_80045468(skel, &D_800A9EF4, 0);
                func_80045468(skel, &D_800A9EF0, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9EF0, 0);
                func_80045468(skel, &D_800A9EF4, 1);
                break;

            default:
                break;
        }
    }

    temp_v1 = arg1 & 0xF0;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 16:
                func_80045468(skel, &D_800A9EFC, 0);
                func_80045468(skel, &D_800A9EF8, 1);
                break;

            case 32:
                func_80045468(skel, &D_800A9EF8, 0);
                func_80045468(skel, &D_800A9EFC, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E08C(s_Skeleton* skel, s32 arg1) // 0x8003E08C
{
    s32 temp_v1;

    temp_v1 = arg1 & 0xF;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 1:
                func_80045468(skel, &D_800A9F04, 0);
                func_80045468(skel, &D_800A9F00, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F00, 0);
                func_80045468(skel, &D_800A9F04, 1);
                break;

            default:
                break;
        }
    }

    temp_v1 = arg1 & 0xF0;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 16:
                func_80045468(skel, &D_800A9F0C, 0);
                func_80045468(skel, &D_800A9F08, 1);
                break;

            case 32:
                func_80045468(skel, &D_800A9F08, 0);
                func_80045468(skel, &D_800A9F0C, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E194(s_Skeleton* skel, s32 arg1) // 0x8003E194
{
    s32 temp_s0;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9F10, 0);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F14, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F18, 1);
                break;

            case 3:
                func_80045468(skel, &D_800A9F1C, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E238(s_Skeleton* skel, s32 arg1) // 0x8003E238
{
    s32 var_s0;

    var_s0 = arg1 & 0xF;
    if (var_s0 != 0)
    {
        func_80045468(skel, &D_800A9F20, 0);

        switch (var_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F28, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F2C, 1);
                break;

            case 3:
                func_80045468(skel, &D_800A9F30, 1);
                break;

            case 4:
                func_80045468(skel, &D_800A9F34, 1);
                break;

            default:
                break;
        }
    }


    var_s0 = arg1 & 0xF0;
    if (var_s0 != 0)
    {
        func_80045468(skel, &D_800A9F38, 0);

        switch (var_s0)
        {
            case 16:
                func_80045468(skel, &D_800A9F3C, 1);
                break;

            case 32:
                func_80045468(skel, &D_800A9F40, 1);
                break;

            case 48:
                func_80045468(skel, &D_800A9F44, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E388(s_Skeleton* skel, s32 arg1) // 0x8003E388
{
    s32 temp_a1;

    temp_a1 = arg1 & 0xF;
    if (temp_a1 != 0)
    {
        switch (temp_a1)
        {
            case 1:
                func_80045468(skel, &D_800A9F4C, 0);
                func_80045468(skel, &D_800A9F48, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F48, 0);
                func_80045468(skel, &D_800A9F4C, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E414(s_Skeleton* skel, s32 arg1) // 0x8003E414
{
    s32 temp_a1;

    temp_a1 = arg1 & 0x3;
    if (temp_a1 != 0)
    {
        switch (temp_a1)
        {
            case 1:
                func_80045468(skel, &D_800A9F50, 0);
                func_80045468(skel, &D_800A9F54, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F54, 0);
                func_80045468(skel, &D_800A9F50, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E4A0(s_Skeleton* skel, s32 arg1) // 0x8003E4A0
{
    s32 temp_s0;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9F58, 0);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F60, 1);
                break;

            case 2:
                func_80045468(skel, &D_800A9F64, 1);
                break;

            case 3:
                func_80045468(skel, &D_800A9F68, 1);
                break;

            default:
                break;
        }
    }
}

void func_8003E544(s_Skeleton* skel, s32 arg1) // 0x8003E544
{
    s32 temp_s0;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 == 0)
    {
        return;
    }

    func_80045468(skel, &D_800A9F6C, 0);

    switch (temp_s0)
    {
        case 1:
            func_80045468(skel, &D_800A9F74, 1);
            break;

        case 2:
            func_80045468(skel, &D_800A9F78, 1);
            break;

        case 3:
            func_80045468(skel, &D_800A9F7C, 1);
            break;

        default:
            break;
    }
}

void func_8003E5E8(s32 arg0) // 0x8003E5E8
{
    GsOT_TAG* ot;
    s32       i;
    u8        color;
    PACKET*   packet;
    LINE_G2*  line;

    packet = GsOUT_PACKET_P;
    ot     = &g_ObjectTable0[g_ObjectTableIdx].org[1];

    for (i = -10; i < 11; i++)
    {
        line = (LINE_G2*)packet;
        setLineG2(line);

        line->x1 = ((g_GameWork.gsScreenWidth_588 - 64) / 20) * i;
        line->x0 = line->x1;

        line->y0 = -16;
        line->y1 = (g_GameWork.gsScreenHeight_58A / 2) - 45;

        color = (arg0 * 8) + 4;

        line->b1 = color;
        line->g1 = color;
        line->r1 = color;

        line->b0 = color;
        line->g0 = color;
        line->r0 = color;

        AddPrim(ot, line);
        packet += sizeof(LINE_G2);
    }

    GsOUT_PACKET_P = packet;
}

void GameFs_FlameGfxLoad() // 0x8003E710
{
    Fs_QueueStartReadTim(FILE_TIM_FLAME_TIM, FS_BUFFER_1, &D_800A9FA8);
}

void func_8003E740() // 0x8003E740
{
    DVECTOR   sp10;
    MATRIX    sp18;
    SVECTOR   sp38;
    s32       sp40[4];
    SVECTOR   sp50;
    DVECTOR   sp58;
    s32       sp60;
    s32       temp_a0;
    s32       temp_s6;
    s16*      var_a0;
    s32       i;
    s32       var_s5;
    POLY_FT4* poly;
    s32       temp_s2 = 0;

    if (g_DeltaTime0 != 0)
    {
        D_800A9FB0 += 8;
        for (i = 0; i < 8; i++)
        {
            D_800BCDE8[i] = Rng_Rand16();
        }
    }

    sp38.vx = 1;
    sp38.vy = -7;
    sp38.vz = 0x21;
    sp38.vx = FP_MULTIPLY(shAngleRegulate(D_800BCDE8[temp_s2++]), 5, Q12_SHIFT) + 1;
    sp38.vz = FP_MULTIPLY(shAngleRegulate(D_800BCDE8[temp_s2++]), 5, Q12_SHIFT) + 33;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    func_80049AF8(&g_SysWork.playerBoneCoords_890[PlayerBone_RightHand], &sp18);
    SetRotMatrix(&sp18);
    SetTransMatrix(&sp18);

    var_s5 = RotTransPers(&sp38, &sp10, &sp60, &sp60);

    temp_s6  = var_s5 * 4;
    var_s5 >>= 1;
    var_s5  -= 2;

    if (var_s5 < 0)
    {
        var_s5 = 0;
    }

    if (temp_s6 >= 0x81 && var_s5 < 0x7FF)
    {
        SetPolyFT4(poly);
        setSemiTrans(poly, 1);

        temp_a0 = D_800BCDE8[temp_s2++];

        if ((temp_a0 & 0xFFF) >= 0xD9A)
        {
            D_800A9FB0 -= 0x10 + (temp_a0 & 0xF);
        }

        if (D_800A9FB0 >= 33)
        {
            D_800A9FB0 = 0;
        }

        setRGB0(poly, D_800A9FB0 + 0x30, D_800A9FB0 + 0x30, D_800A9FB0 + 0x30);
        poly->tpage = 0x2C;
        poly->clut  = 0x1032;

        var_a0 = &D_800BCDE8[temp_s2++];

        for (i = 0; i < 4; i++)
        {
            sp40[i] = (var_a0[i] & 0xF) - 8;
        }

        SetRotMatrix(&GsIDMATRIX);
        SetTransMatrix(&GsIDMATRIX);

        sp50.vz = temp_s6;
        sp50.vx = sp40[0] - 0x33;
        sp50.vy = sp40[2] - 0x33;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x0 = sp10.vx + sp58.vx;
        poly->y0 = sp10.vy + sp58.vy;
        sp50.vx  = sp40[1] + 0x33;
        sp50.vy  = sp40[3] - 0x33;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x1 = sp10.vx + sp58.vx;
        poly->y1 = sp10.vy + sp58.vy;
        sp50.vx  = -0x33 - sp40[1];
        sp50.vy  = 0x33 - sp40[3];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x2 = sp10.vx + sp58.vx;
        poly->y2 = sp10.vy + sp58.vy;
        sp50.vx  = 0x33 - sp40[0];
        sp50.vy  = 0x33 - sp40[2];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x3 = sp10.vx + sp58.vx;
        poly->y3 = sp10.vy + sp58.vy;

        poly->u0 = 0x80;
        poly->u1 = 0xBF;
        poly->u2 = 0x80;
        poly->u3 = 0xBF;

        poly->v0 = 0;
        poly->v1 = 0;
        poly->v2 = 0x3F;
        poly->v3 = 0x3F;

        AddPrim(&g_ObjectTable0[g_ObjectTableIdx].org[var_s5], poly);
        GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_FT4);
    }
}

/**
 * TODO: Please investigate me!
 */
void func_8003EB54() // 0x8003EB54
{
    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[0];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[0];

    Math_Vector3Set(&g_SysWork.field_2360, 0, -0x333, -0x2000);
    Math_SVectorSet(&g_SysWork.field_2370, 0x71, 0, 0);
}

void func_8003EBA0() // 0x8003EBA0
{
    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[1];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[0];

    Math_Vector3Set(&g_SysWork.field_2360, -0x147, -0x47A, 0x1EB);
    Math_SVectorSet(&g_SysWork.field_2370, -0xAA, 0, 0);
}

void func_8003EBF4(s_MapOverlayHeader* arg0) // 0x8003EBF4
{
    s_800A9F80* ptr;
    s32         var_v1;
    s8          temp_a0;
    u8          temp_a1;

    temp_a1 = arg0->field_0->field_6;

    var_v1 = 0;

    if (temp_a1 & 4)
    {
        var_v1 = (temp_a1 & 3) > 0;
    }

    switch (arg0->field_16)
    {
        case 1:
            if (var_v1 != 0)
            {
                ptr = &D_800A9F84;
            }
            else
            {
                ptr = &D_800A9F80;
            }
            break;

        case 2:
            if (var_v1 != 0)
            {
                ptr = &D_800A9F8C;
            }
            else
            {
                ptr = &D_800A9F88;
            }
            break;

        case 3:
            ptr = &D_800A9F98;
            break;

        default:
            ptr = &D_800A9F80;
            break;
    }

    func_8003ED74(ptr->field_0, ptr->field_1);
}

void Game_TurnFlashlightOn() // 0x8003ECBC
{
    g_SysWork.field_2388.flashlightState_15 = 1;
    g_SavegamePtr->flags_AC                &= ~(1 << 1);
}

void Game_TurnFlashlightOff() // 0x8003ECE4
{
    g_SysWork.field_2388.flashlightState_15 = 0;
    g_SavegamePtr->flags_AC                |= 1 << 1;
}

void func_8003ED08() // 0x8003ED08
{
    g_SysWork.field_2388.flashlightState_15 ^= 1;

    if (g_SysWork.field_2388.flashlightState_15 == 1)
    {
        g_SavegamePtr->flags_AC &= ~(1 << 1);
    }
    else
    {
        g_SavegamePtr->flags_AC |= 1 << 1;
    }
}

u32 func_8003ED64() // 0x8003ED64
{
    return g_SysWork.field_2388.flashlightState_15;
}

void func_8003ED74(s32 arg0, s32 arg1) // 0x8003ED74
{
    func_8003EF10(arg0, arg1, 0, 0, 0, 0);
    func_8003F170();
}

void func_8003EDA8() // 0x8003EDA8
{
    g_SysWork.field_2388.field_14 = 1;
}

void func_8003EDB8(s32* arg0, s32* arg1) // 0x8003EDB8
{
    s_SysWork_2288* ptr0;
    s_SysWork_2288* ptr1;

    memcpy(arg0, &(ptr0 = &g_SysWork.field_2388)->field_1C[g_SysWork.field_2388.flashlightState_15].field_0.field_20.vec_0[1], 4); // Is there a better solution?
    memcpy(arg1, &(ptr1 = &g_SysWork.field_2388)->field_1C[g_SysWork.field_2388.flashlightState_15].field_0.field_24.vec_0[1], 4);
}

void func_8003EE30(s32 arg0, s8* arg1, s32 arg2, s32 arg3) // 0x8003EE30
{
    g_SysWork.field_2388.field_4 = arg1;
    g_SysWork.field_2388.field_0 = 5;
    g_SysWork.field_2388.field_8 = arg2;
    g_SysWork.field_2388.field_C = arg3;

    g_SysWork.field_2388.field_EC[0] = g_SysWork.field_2388.field_1C[0];
    g_SysWork.field_2388.field_EC[1] = g_SysWork.field_2388.field_1C[1];
}

void func_8003EEDC(s32 arg0, s32 arg1) // 0x8003EEDC
{
    func_8003EF10(arg0, arg1, 0, 0, 0, 0);
    func_8003F170();
}

void func_8003EF10(s32 idx0, s32 idx1, s32 arg4, s32 arg5, s32 arg6, s32 arg7) // 0x8003EF10
{
    func_8003EF74(&D_800A93CC[idx0], &D_800A93CC[idx1], arg4, arg5, arg6, arg7);
}

void func_8003EF74(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x8003EF74
{
    if (arg0 == arg1)
    {
        g_SysWork.field_2388.field_16 = 1;
    }
    else
    {
        g_SysWork.field_2388.field_16 = 0;
    }

    g_SysWork.field_2388.field_4 = arg3;
    g_SysWork.field_2388.field_0 = arg2;
    g_SysWork.field_2388.field_8 = arg4;
    g_SysWork.field_2388.field_C = arg5;

    g_SysWork.field_2388.field_EC[0] = g_SysWork.field_2388.field_1C[0];
    g_SysWork.field_2388.field_EC[1] = g_SysWork.field_2388.field_1C[1];

    func_8003F08C(&g_SysWork.field_2388.field_84[0], arg0);
    func_8003F08C(&g_SysWork.field_2388.field_84[1], arg1);
}

void func_8003F08C(s_StructUnk3* arg0, s_sub_StructUnk3* arg1) // 0x8003F08C
{
    arg0->field_0 = *arg1;

    if (arg1->field_0.s_field_0.field_0 & (1 << 2))
    {
        arg0->field_2E = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    }
    else
    {
        arg0->field_2E = 0;
    }

    if (arg1->field_0.s_field_0.field_0 & (1 << 4))
    {
        arg0->field_2C = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    }
    else
    {
        arg0->field_2C = 0;
    }

    switch (arg1->field_E)
    {
        case 0:
        case 1:
            arg0->field_30 = arg1->field_10;
            break;

        case 2:
            arg0->field_30 = 0;
            break;

        case 3:
            arg0->field_30 = arg1->field_10;
            break;

        default:
            break;
    }
}

void func_8003F170() // 0x8003F170
{
    MATRIX          sp28;
    VECTOR          sp48;
    SVECTOR         sp58;
    GsCOORDINATE2*  sp60;
    s32             temp_v0;
    u8              temp_v1;
    s32             temp;
    s_StructUnk3*   ptr2;
    s_SysWork_2288* ptr = &g_SysWork.field_2388;

    if (g_SysWork.field_2388.flashlightState_15 != 0)
    {
        g_SysWork.field_2388.flashlightIntensity_18 += FP_MULTIPLY((s64)g_DeltaTime0, FP_FLOAT_TO(4.0f, Q12_SHIFT), Q12_SHIFT);
    }
    else
    {
        g_SysWork.field_2388.flashlightIntensity_18 -= FP_MULTIPLY((s64)g_DeltaTime0, FP_FLOAT_TO(4.0f, Q12_SHIFT), Q12_SHIFT);
    }

    g_SysWork.field_2388.flashlightIntensity_18 = CLAMP(g_SysWork.field_2388.flashlightIntensity_18, 0, FP_FLOAT_TO(1.0f, Q12_SHIFT));

    if (g_SysWork.field_2388.field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].field_0.field_E == 3)
    {
        func_80049AF8(g_SysWork.field_235C, &sp28);
        ApplyMatrixLV(&sp28, (VECTOR*)&g_SysWork.field_2360, &sp48); // Bug? `g_SysWork.field_2360` is `VECTOR3`.
        ptr->field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].field_30 = sp48.vz + (sp28.t[2] * 0x10);
    }

    if (ptr->field_0 == 0)
    {
        ptr->field_1C[0] = ptr->field_84[0];
        ptr->field_1C[1] = ptr->field_84[1];
    }
    else
    {
        temp_v0 = func_8003F6F0(func_8003F654(ptr), ptr->field_8, ptr->field_C);

        func_8003F838(&ptr->field_1C[0], &ptr->field_EC[0], &ptr->field_84[0], temp_v0);
        func_8003F838(&ptr->field_1C[1], &ptr->field_EC[1], &ptr->field_84[1], temp_v0);

        if (temp_v0 >= FP_FLOAT_TO(1.0f, Q12_SHIFT))
        {
            ptr->field_0 = 0;
        }
    }

    func_8003F838(&ptr->field_154, &ptr->field_1C[0], &ptr->field_1C[1], ptr->flashlightIntensity_18);

    ptr2 = &ptr->field_154;

    if (ptr->field_14 != 0)
    {
        temp_v1       = ptr->field_154.field_0.field_0.s_field_0.field_0;
        ptr->field_14 = 0;

        if (temp_v1 & 1)
        {
            func_8003F08C(ptr2, &D_800A952C);
        }
        else if (temp_v1 & 2)
        {
            ptr2->field_0.field_4 += 0x4CC;
        }
    }

    ptr->field_10 = func_8003FEC0(&ptr2->field_0);
    func_8003FF2C(ptr2);

    temp = FP_MULTIPLY(func_8003F4DC(&sp60, &sp58, ptr2->field_0.field_4, ptr2->field_0.field_0.s_field_0.field_2, func_80080A10(), &g_SysWork), g_SysWork.field_2378, Q12_SHIFT);

    func_800554C4(temp, ptr2->field_2C, sp60, g_SysWork.field_235C, &sp58, g_SysWork.field_2360.vx, g_SysWork.field_2360.vy, g_SysWork.field_2360.vz, D_800BCE18.field_0[0].field_0->field_8);
    func_80055814(ptr2->field_30);

    if (ptr->field_154.field_0.field_0.s_field_0.field_0 & (1 << 3))
    {
        func_8003E740();
    }
}

s32 func_8003F4DC(GsCOORDINATE2** arg0, SVECTOR* rot, s32 arg2, s32 arg3, u32 arg4, s_SysWork* sysWork) // 0x8003F4DC
{
    s32     temp;
    s32     res;
    SVECTOR vec;

    if (arg3 != 2)
    {
        arg4 = 1;
    }

    res = arg2;
    if (arg4 == 0)
    {
        res = 0;
    }

    switch (arg4)
    {
        default:
        case 1:
            *arg0 = sysWork->field_236C;
            break;

        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
            *arg0 = NULL;
            break;
    }

    switch (arg4)
    {
        default:
        case 1:
            vec = sysWork->field_2370;
            break;

        case 0:
            vec.vx = 0;
            vec.vy = 0xFC00;
            vec.vz = 0;
            break;

        case 2:
            vec.vx = 0xFF1D;
            vec.vy = 0x8AA;
            vec.vz = 0;
            break;

        case 3:
            vec.vx = 0xFF1D;
            vec.vy = 0xFCAB;
            vec.vz = 0;
            break;

        case 4:
            vec.vx = 0xFF1D;
            vec.vy = 0xAA;
            vec.vz = 0;
            break;

        case 5:
            vec.vx = 0xFF1D;
            vec.vy = 0x4AA;
            vec.vz = 0;
            break;
    }

    rot->vy = -shRsin(vec.vx);
    temp    = shRcos(vec.vx);
    rot->vz = FP_MULTIPLY(temp, shRcos(vec.vy), Q12_SHIFT);
    rot->vx = FP_MULTIPLY(temp, shRsin(vec.vy), Q12_SHIFT);
    return res;
}

u32 func_8003F654(s_func_8003F654* arg0)
{
    switch (arg0->field_0)
    {
        default:
        case PrimitiveType_None:
            break;

        case PrimitiveType_S8:
            return *arg0->field_4;

        case PrimitiveType_U8:
            return *(u8*)arg0->field_4;

        case PrimitiveType_S16:
            return *(s16*)arg0->field_4;

        case PrimitiveType_U16:
            return *(u16*)arg0->field_4;

        case PrimitiveType_S32:
            return *(s32*)arg0->field_4;
    }

    return 0;
}

s32 func_8003F6F0(s32 arg0, s32 arg1, s32 arg2) // 0x8003F6F0
{
    s32 leadingZeros;
    s32 shift;

    if (arg1 < arg2)
    {
        arg0 = CLAMP(arg0, arg1, arg2);
    }
    else if (arg2 < arg1)
    {
        arg0 = CLAMP(arg0, arg2, arg1);
    }
    else
    {
        return FP_TO(1, Q12_SHIFT);
    }

    leadingZeros = 32 - Lzc(arg2 - arg1);
    shift        = 0;

    if ((leadingZeros + 12) >= 31)
    {
        shift = leadingZeros - 19;
    }

    shift = CLAMP(shift, 0, Q12_SHIFT);

    return ((arg0 - arg1) << (Q12_SHIFT - shift)) / ((arg2 - arg1) >> shift);
}

s32 Math_GetWeightedAverage(s32 a, s32 b, s32 weight) // 0x8003F7E4
{
    return Math_MulFixed(a, FP_ALPHA(1.0f) - weight, Q12_SHIFT) + Math_MulFixed(b, weight, Q12_SHIFT);
}

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight) // 0x8003F838
{
    s32 weight0;
    s32 weight1;
    s32 weight2;
    u32 temp;

    weight0 = weight * 2;
    weight0 = CLAMP(weight0, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
    weight1 = (weight - FP_ALPHA(0.5f)) * 2;
    weight1 = CLAMP(weight1, FP_ALPHA(0.0f), FP_ALPHA(1.0f));

    if (weight < FP_ALPHA(0.5f))
    {
        arg0->field_0.field_0.s_field_0.field_0 = arg1->field_0.field_0.s_field_0.field_0;
    }
    else
    {
        arg0->field_0.field_0.s_field_0.field_0 = arg2->field_0.field_0.s_field_0.field_0;
    }

    func_8003FCB0(&arg0->field_0, &arg1->field_0, &arg2->field_0, weight);

    if (arg1->field_2C == FP_ALPHA(0.0f))
    {
        arg0->field_2C = Math_GetWeightedAverage(0, arg2->field_2C, weight1);
    }
    else
    {
        arg0->field_2C = Math_GetWeightedAverage(arg1->field_2C, arg2->field_2C, weight0);
    }

    if (arg1->field_0.field_0.s_field_0.field_0 & (1 << 0))
    {
        if (arg2->field_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_GetWeightedAverage(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight);
        }
        else
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_GetWeightedAverage(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight1);
        }
    }
    else
    {
        if (arg2->field_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_GetWeightedAverage(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight0);
        }
        else
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_GetWeightedAverage(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight);
        }
    }

    if (arg1->field_0.field_E == 0)
    {
        if (arg2->field_0.field_E != 0)
        {
            arg0->field_0.field_E = arg2->field_0.field_E;
            func_8003FD38(arg0, arg1, arg2, weight, weight0, weight1);
        }
        else
        {
            temp                  = arg2->field_0.field_E;
            arg0->field_0.field_E = temp;
            func_8003FD38(arg0, arg1, arg2, weight, weight, weight);
        }
    }
    else if (arg2->field_0.field_E == 0)
    {
        if (weight1 >= FP_ALPHA(1.0f))
        {
            arg0->field_0.field_E = arg2->field_0.field_E;
        }
        else
        {
            arg0->field_0.field_E = arg1->field_0.field_E;
        }
        func_8003FD38(arg0, arg1, arg2, weight, weight1, weight0);
    }
    else
    {
        temp                  = arg2->field_0.field_E;
        arg0->field_0.field_E = temp;
        func_8003FD38(arg0, arg1, arg2, weight, weight, weight);
    }

    arg0->field_0.field_8 = Math_GetWeightedAverage(arg1->field_0.field_8, arg2->field_0.field_8, weight);
    arg0->field_0.field_A = Math_GetWeightedAverage(arg1->field_0.field_A, arg2->field_0.field_A, weight);
    arg0->field_0.field_C = Math_GetWeightedAverage(arg1->field_0.field_C, arg2->field_0.field_C, weight);

    if (arg1->field_0.field_0.s_field_0.field_2 == 1 && arg2->field_0.field_0.s_field_0.field_2 == 2)
    {
        if (weight < FP_ALPHA(5.0f / 6.0f))
        {
            weight2                                 = FP_MULTIPLY(weight, FP_ALPHA(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_GetWeightedAverage(arg1->field_0.field_4, 0, weight2);
        }
        else
        {
            weight2                                 = (weight - FP_ALPHA(5.0f / 6.0f)) * 6;
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            weight0                                 = arg2->field_0.field_4;
            arg0->field_0.field_4                   = Math_GetWeightedAverage(FP_ALPHA(0.0f), weight0, weight2);
        }
    }
    else if (arg1->field_0.field_0.s_field_0.field_2 == 2 && arg2->field_0.field_0.s_field_0.field_2 == 1)
    {
        if (weight < FP_ALPHA(1.0f / 6.0f))
        {
            weight2                                 = weight * 6;
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_GetWeightedAverage(arg1->field_0.field_4, FP_ALPHA(0.0f), weight2);
        }
        else
        {
            weight2                                 = FP_MULTIPLY(weight - FP_ALPHA(1.0f / 6.0f), FP_ALPHA(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_GetWeightedAverage(FP_ALPHA(0.0f), arg2->field_0.field_4, weight2);
        }
    }
    else
    {
        if (arg1->field_0.field_0.s_field_0.field_2 != 0 && arg2->field_0.field_0.s_field_0.field_2 == 0)
        {
            if (weight >= FP_ALPHA(1.0f))
            {
                arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            }
            else
            {
                arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            }
        }
        else
        {
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
        }

        arg0->field_0.field_4 = Math_GetWeightedAverage(arg1->field_0.field_4, arg2->field_0.field_4, weight);
    }

    if (arg1->field_0.field_18.vec_0[0] == 0 && arg2->field_0.field_18.vec_0[0] != 0)
    {
        func_8003FE04(&arg0->field_0, &arg1->field_0, &arg2->field_0, weight1);
    }
    else
    {
        func_8003FE04(&arg0->field_0, &arg1->field_0, &arg2->field_0, weight);
    }
}

void func_8003FCB0(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 arg3) // 0x8003FCB0
{
    s32 p0;
    
    p0 = FP_ALPHA(1.0f) - arg3;
    LoadAverageCol(&arg1->field_20.vec_0[1], &arg2->field_20.vec_0[1], p0, arg3, &arg0->field_20.vec_0[1]);
    LoadAverageCol(&arg1->field_24.vec_0[1], &arg2->field_24.vec_0[1], p0, arg3, &arg0->field_24.vec_0[1]);
}

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight0, s32 weight1, s32 alphaTo) // 0x8003FD38
{
    if (arg1->field_2E != arg2->field_2E)
    {
        arg0->field_2E = Math_GetWeightedAverage(arg1->field_2E, arg2->field_2E, weight0);
    }
    else
    {
        arg0->field_2E = arg2->field_2E;
    }

    arg0->field_30         = Math_GetWeightedAverage(arg1->field_30, arg2->field_30, weight0);
    arg0->field_0.field_10 = Math_GetWeightedAverage(arg1->field_0.field_10, arg2->field_0.field_10, weight1);
    arg0->field_0.field_6  = Math_GetWeightedAverage(arg1->field_0.field_6, arg2->field_0.field_6, weight0);

    LoadAverageCol(arg1->field_0.field_14.vec_0, arg2->field_0.field_14.vec_0, FP_ALPHA(1.0f) - alphaTo, alphaTo, arg0->field_0.field_14.vec_0);
}

void func_8003FE04(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 alphaTo) // 0x8003FE04
{
    s32 alphaFrom;

    alphaFrom = FP_ALPHA(1.0f) - alphaTo;
    LoadAverageCol(&arg1->field_18.vec_0[1], &arg2->field_18.vec_0[1], alphaFrom, alphaTo, &arg0->field_18.vec_0[1]);
    LoadAverageCol(&arg1->field_1C.vec_0[1], &arg2->field_1C.vec_0[1], alphaFrom, alphaTo, &arg0->field_1C.vec_0[1]);

    if ((arg0->field_18.field_0 & ~0xFF) || (arg0->field_1C.field_0 & ~0xFF))
    {
        arg0->field_18.vec_0[0] = 1;
    }
    else
    {
        arg0->field_18.vec_0[0] = 0;
    }
}

s32 func_8003FEC0(s_sub_StructUnk3* arg0) // 0x8003FEC0
{
    if (D_800C4168.field_1 != 0)
    {
        return arg0->field_10;
    }

    if (D_800C4168.field_0 == 1)
    {
        return vwOresenHokan(D_800A9FB4, 5, arg0->field_4, 0, FP_FLOAT_TO(2.0f, Q12_SHIFT));
    }

    return FP_FLOAT_TO(20.0f, Q12_SHIFT);
}

void func_8003FF2C(s_StructUnk3* arg0) // 0x8003FF2C
{
    s32 temp_a0;
    s32 temp_v1;
    s32 var_t0;

    temp_v1 = FP_MULTIPLY(arg0->field_2E, ((g_GameWork.config_0.optBrightness_22 * 8) + 4), Q12_SHIFT);
    var_t0  = CLAMP(temp_v1, 0, 0xFF);

    func_80055330(arg0->field_0.field_0.s_field_0.field_2, arg0->field_0.field_6, arg0->field_0.field_0.s_field_0.field_1, arg0->field_0.field_8, arg0->field_0.field_A, arg0->field_0.field_C, var_t0);
    func_800553C4(arg0->field_0.field_E != 0, arg0->field_0.field_14.vec_0[0], arg0->field_0.field_14.vec_0[1], arg0->field_0.field_14.vec_0[2]);

    temp_a0 = arg0->field_0.field_10;

    func_80055840(temp_a0, temp_a0 + FP_FLOAT_TO(1.0f, Q12_SHIFT));
    func_800553E0(arg0->field_0.field_18.vec_0[0], arg0->field_0.field_18.vec_0[1], arg0->field_0.field_18.vec_0[2], arg0->field_0.field_18.vec_0[3], arg0->field_0.field_1C.vec_0[1], arg0->field_0.field_1C.vec_0[2], arg0->field_0.field_1C.vec_0[3]);
}

void func_80040004(s_800BCE18* arg0) // 0x80040004
{
    D_800BCE18.field_1BD8 = &arg0->field_0[2].field_26C;
}

void func_80040014() // 0x80040014
{
    func_80069860(g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz, D_800BCE18.field_1BD8);
};
