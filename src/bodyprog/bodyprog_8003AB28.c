#include "game.h"

#include <libetc.h>
#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/math/math.h"
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
    #define MAIN_MENU_GAME_STATE_COUNT 5

    s32 NEXT_GAME_STATES[MAIN_MENU_GAME_STATE_COUNT] = // 0x80025480
    {
        GameState_SaveScreen, 
        GameState_DeathLoadScreen,
        GameState_MovieOpening,
        GameState_OptionScreen,
        GameState_MovieIntro
    };

    s32         playIntroFmv;
    s32         prevGameDifficultyIdx;
    s32         nextGameDifficultyIdx;
    e_GameState prevState;

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
            g_SysWork.processFlags_2298 = SysWorkProcessFlag_BootDemo;
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

            Screen_RectInterlacedClear(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Screen_Init(SCREEN_WIDTH, 1);

            g_IntervalVBlanks    = 1;
            g_Screen_FadeStatus  = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);
            g_ScreenFadeTimestep = FP_TIME(2.0f);
            g_MainMenuState++;

        case MenuState_Main:
            if (playIntroFmv != 0)
            {
                GameFs_MapStartup();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == FP_TIME(0.0f))
                {
                    g_Demo_ReproducedCount++;
                }

                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    g_Demo_ReproducedCount++;
                }
            }

            g_MainMenu_VisibleEntryFlags = (1 << MainMenuEntry_Start) | (1 << MainMenuEntry_Option);

            if (g_GameWork.autosave_90.playerHealth_240 > FP_HEALTH(0.0f))
            {
                g_MainMenu_VisibleEntryFlags = (1 << MainMenuEntry_Continue) | (1 << MainMenuEntry_Start) | (1 << MainMenuEntry_Option);
            }

            // Memory card present and savegames exist.
            if (g_SavegameCount > 0)
            {
                g_MainMenu_VisibleEntryFlags |= (1 << MainMenuEntry_Load) | (1 << MainMenuEntry_Continue);
                
                if (g_PrevSavegameCount < g_SavegameCount && g_MainMenu_SelectedEntry != MainMenuEntry_Load)
                {
                    g_MainMenu_SelectedEntry = MainMenuEntry_Continue;
                }
            }
            // Mo savegames exist but did previously (e.g. memory card removed before player death).
            else if (g_PrevSavegameCount > 0)
            {
                while(!(g_MainMenu_VisibleEntryFlags & (1 << g_MainMenu_SelectedEntry)))
                {
                    g_MainMenu_SelectedEntry++;
                }
            }

            g_MainMenu_VisibleEntryFlags |= g_MainMenu_VisibleEntryFlags << MAIN_MENU_OPTION_COUNT;

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
                g_MainMenu_SelectedEntry += MAIN_MENU_OPTION_COUNT;
                while(!(g_MainMenu_VisibleEntryFlags & (1 << --g_MainMenu_SelectedEntry)))
                {
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {                
                while(!(g_MainMenu_VisibleEntryFlags & (1 << ++g_MainMenu_SelectedEntry)))
                {
                }
            }

            // Wrap selection.
            g_MainMenu_SelectedEntry %= MAIN_MENU_OPTION_COUNT;

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_GameWork.gameState_594 = GameState_MainMenu;

                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }

                g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_MainMenuState++;

                if (g_MainMenu_SelectedEntry < (u32)MainMenuEntry_Start) // TODO: Odd cast.
                {
                    Sd_EngineCmd(Sfx_StartGame);
                }
                else
                {
                    Sd_EngineCmd(Sfx_Confirm);
                }

                switch (g_MainMenu_SelectedEntry)
                {
                    case MainMenuEntry_Continue:
                        if (g_GameWork.autosave_90.playerHealth_240 > FP_HEALTH(0.0f))
                        {
                            g_GameWork.savegame_30C = g_GameWork.autosave_90;
                        }
                        else
                        {
                            GameFs_SaveLoadBinLoad();
                        }

                        Game_PlayerInit();
                        g_SysWork.processFlags_2298 = SysWorkProcessFlag_Continue;
                        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
                        break;

                    case MainMenuEntry_Load:
                        GameFs_SaveLoadBinLoad();
                        break;

                    case MainMenuEntry_Start:
                        g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_Reset, false);
                        g_MainMenuState     = MenuState_DifficultySelector;
                        break;

                    case MainMenuEntry_Option:
                        GameFs_OptionBinLoad();
                        break;

                    case MainMenuEntry_Extra: // @unused See `e_MainMenuEntry`.
                        break;
                }
            }

            g_PrevSavegameCount = g_SavegameCount;

        default:
            break;

        case MenuState_DifficultySelector:
            if (playIntroFmv != 0)
            {
                GameFs_MapStartup();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == FP_TIME(0.0f))
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
                Game_PlayerInit();

                g_SysWork.processFlags_2298 = SysWorkProcessFlag_NewGame;

                GameFs_MapLoad(MapOverlayId_MAP0_S00);
                GameFs_StreamBinLoad();
                Sd_EngineCmd(Sfx_StartGame);

                g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
                g_MainMenuState     = 4;
            }
            // Cancel.
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(Sfx_Cancel);
                g_MainMenuState = 1;
            }
            break;

        case MenuState_LoadGame:
        case MenuState_NewGameStart:
            if (SCREEN_FADE_STATE_GET(g_Screen_FadeStatus) == ScreenFadeState_FadeOutComplete)
            {
                Screen_Refresh(SCREEN_WIDTH, 0);
                Fs_QueueWaitForEmpty();

                if (g_GameWork.autosave_90.playerHealth_240 > FP_HEALTH(0.0f))
                {
                    NEXT_GAME_STATES[1] = 10;
                }

                if (g_MainMenu_SelectedEntry == MainMenuEntry_Start)
                {
                    Chara_PositionUpdateFromParams(g_MapOverlayHeader.mapAreaLoadParams_1C);
                }

                func_8002E830();

                prevState                       = g_GameWork.gameState_594;
                g_GameWork.gameStateStep_598[0] = prevState;
                g_GameWork.gameState_594        = NEXT_GAME_STATES[g_MainMenu_SelectedEntry];
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
    Screen_Init(SCREEN_WIDTH, 0);
}

void MainMenu_SelectedOptionIdxReset() // 0x8003B550
{
    g_MainMenu_SelectedEntry = MainMenuEntry_Continue;
}

void func_8003B560() {}

static const char* MAIN_MENU_ENTRY_STRINGS[] =
{
    "LOAD",
    "CONTINUE",
    "START",
    "OPTION",
    "EXTRA" /** @unused See `e_MainMenuEntry`. */
};

void Gfx_MainMenu_MainTextDraw() // 0x8003B568
{
    #define COLUMN_POS_X 158
    #define COLUMN_POS_Y 184
    #define STR_OFFSET_Y 20

    static const u8 STR_OFFSETS_X[] = { 29, 50, 32, 39, 33 }; // @unused Element at index 4. See `g_MainMenu_VisibleEntryFlags`.

    s32 i;

    // Draw selection strings.
    for (i = 0; i < MAIN_MENU_OPTION_COUNT; i++)
    {
        // Check entry visibility flag.
        if (!(g_MainMenu_VisibleEntryFlags & (1 << i)))
        {
            continue;
        }

        Gfx_StringSetPosition(COLUMN_POS_X - STR_OFFSETS_X[i], COLUMN_POS_Y + (i * STR_OFFSET_Y));
        Gfx_StringSetColor(StringColorId_White);

        if (i == g_MainMenu_SelectedEntry)
        {
            Gfx_StringDraw("[", 99);
        }
        else
        {
            Gfx_StringDraw("_", 99);
        }

        Gfx_StringDraw(MAIN_MENU_ENTRY_STRINGS[i], 99);

        if (i == g_MainMenu_SelectedEntry)
        {
            Gfx_StringDraw("]", 99);
        }

        Gfx_StringDraw("\n", 99);
    }
}

static const char* DIFFICULTY_MENU_ENTRY_STRINGS[] =
{
    "EASY",
    "NORMAL",
    "HARD"
};

void Gfx_MainMenu_DifficultyTextDraw(s32 arg0) // 0x8003B678
{
    #define DIFFICULTY_MENU_SELECTION_COUNT 3
    #define COLUMN_POS_X                    158
    #define COLUMN_POS_Y                    204
    #define STR_OFFSET_Y                    20

    static const u8 STR_OFFSETS_X[] = { 28, 43, 30, 76 };               // @unused Element at index 3 may have been a 4th selectable difficulty.
    static const u8 UNUSED[]        = { 0, 149, 171, 144, 0, 0, 0, 0 }; // @unused Unknown purpose.

    s32 i;

    // Draw selection strings.
    for (i = 0; i < DIFFICULTY_MENU_SELECTION_COUNT; i++)
    {
        Gfx_StringSetPosition(COLUMN_POS_X - STR_OFFSETS_X[i], COLUMN_POS_Y + (i * STR_OFFSET_Y));
        Gfx_StringSetColor(StringColorId_White);

        if (i == arg0)
        {
            Gfx_StringDraw("[", 99);
        }
        else
        {
            Gfx_StringDraw("_", 99);
        }

        Gfx_StringDraw(DIFFICULTY_MENU_ENTRY_STRINGS[i], 99);

        if (i == arg0)
        {
            Gfx_StringDraw("]", 99);
        }

        Gfx_StringDraw("\n", 99);
    }
}

void Gfx_MainMenu_BackgroundDraw() // 0x8003B758
{
    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
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

u32 D_800A9AAC[256] =
{
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000,
    0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A000000, 0x3A010101,
    0x3A020202, 0x3A040403, 0x3A050505, 0x3A070706, 0x3A080807, 0x3A0A0A09, 0x3A0C0B0A, 0x3A0D0D0B,
    0x3A0F0E0D, 0x3A10100E, 0x3A12120F, 0x3A131311, 0x3A151512, 0x3A171613, 0x3A181815, 0x3A1A1916,
    0x3A1B1B17, 0x3A1D1C19, 0x3A1E1E1A, 0x3A20201C, 0x3A22211D, 0x3A23231E, 0x3A252420, 0x3A262621,
    0x3A282722, 0x3A292924, 0x3A2B2A25, 0x3A2D2C26, 0x3A2E2D28, 0x3A302F29, 0x3A31312A, 0x3A33322C,
    0x3A34342D, 0x3A36352E, 0x3A383730, 0x3A393831, 0x3A3B3A32, 0x3A3C3B34, 0x3A3E3D35, 0x3A403F37,
    0x3A413F37, 0x3A424038, 0x3A434139, 0x3A444139, 0x3A45423A, 0x3A46433B, 0x3A47443B, 0x3A48443C,
    0x3A49453D, 0x3A4A463D, 0x3A4B463E, 0x3A4C473F, 0x3A4D483F, 0x3A4E4940, 0x3A504941, 0x3A514A42,
    0x3A524B42, 0x3A534C43, 0x3A544C44, 0x3A554D44, 0x3A564E45, 0x3A574E46, 0x3A584F46, 0x3A595047,
    0x3A5A5148, 0x3A5B5148, 0x3A5C5249, 0x3A5D534A, 0x3A5F544B, 0x3A60544C, 0x3A61554D, 0x3A62564D,
    0x3A63574E, 0x3A64574F, 0x3A655850, 0x3A665950, 0x3A685951, 0x3A695A52, 0x3A6A5B53, 0x3A6B5C53,
    0x3A6C5C54, 0x3A6D5D55, 0x3A6E5E56, 0x3A6F5E56, 0x3A705F57, 0x3A716058, 0x3A726059, 0x3A736159,
    0x3A74625A, 0x3A75635B, 0x3A77635C, 0x3A78645C, 0x3A79655D, 0x3A7A655E, 0x3A7B665F, 0x3A7C675F,
    0x3A7D6860, 0x3A7E6861, 0x3A7F6962, 0x3A806A62, 0x3A816A63, 0x3A826B64, 0x3A836C65, 0x3A856D66,
    0x3A806D67, 0x3A806E68, 0x3A816F68, 0x3A827069, 0x3A83706A, 0x3A84716B, 0x3A85726C, 0x3A86736D,
    0x3A87746E, 0x3A88756E, 0x3A89766F, 0x3A897770, 0x3A8A7871, 0x3A8B7872, 0x3A8C7973, 0x3A8D7A74,
    0x3A8E7B74, 0x3A8F7C75, 0x3A907D76, 0x3A917E77, 0x3A927F78, 0x3A928079, 0x3A93807A, 0x3A94817A,
    0x3A95827B, 0x3A96837C, 0x3A97847D, 0x3A98857E, 0x3A99867F, 0x3A9A8780, 0x3A9B8881, 0x3A9C8982,
    0x3A9C8A83, 0x3A9D8B84, 0x3A9E8C85, 0x3A9F8D86, 0x3AA08E87, 0x3AA08F88, 0x3AA18F89, 0x3AA2908A,
    0x3AA3918B, 0x3AA4928C, 0x3AA4938D, 0x3AA5948E, 0x3AA6958F, 0x3AA7968F, 0x3AA79790, 0x3AA89891,
    0x3AA99892, 0x3AAA9993, 0x3AAB9A94, 0x3AAB9B95, 0x3AAC9C96, 0x3AAD9D97, 0x3AAE9E98, 0x3AAF9F99,
    0x3AAFA09A, 0x3AB0A19B, 0x3AB1A29C, 0x3AB2A29D, 0x3AB3A39E, 0x3AB3A49F, 0x3AB4A59F, 0x3AB5A6A0,
    0x3AB6A7A1, 0x3AB6A8A2, 0x3AB7A9A3, 0x3AB8AAA4, 0x3AB9ABA5, 0x3ABAABA6, 0x3ABAACA7, 0x3ABBADA8,
    0x3ABCAEA9, 0x3ABDAFAA, 0x3ABEB0AB, 0x3ABEB1AC, 0x3ABFB2AD, 0x3AC0B3AE, 0x3AC1B4AF, 0x3AC2B5B0
};

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

    tag    = g_OrderingTable2[g_ActiveBufferIdx].org;
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

    static s32 RAND = 0;

    ptr   = D_800BCDE0;
    ptr1  = ptr + 441;
    RAND += Rng_GenerateInt(Rng_Rand16(), 4, 11u);
    val   = FP_MULTIPLY(Math_Sin(RAND), 10, Q12_SHIFT) - 122;
    ptr2  = ptr + 461;

    for (i = 20; i >= 0; i--)
    {
        *ptr2-- = val;
    }

    for (i = 0; i < 16; i++)
    {
        idx       = Rng_GenerateInt(Rng_Rand16(), 0, MAIN_MENU_FOG_COUNT - 1);
        ptr1[idx] = NO_VALUE;
    }

    for (i = 0; i < 9; i++)
    {
        idx       = Rng_GenerateInt(Rng_Rand16(), 0, MAIN_MENU_FOG_COUNT - 1);
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
    static s32 FOG_COUNT = 0;

    if (FOG_COUNT == ((FOG_COUNT / 5) * 5))
    {
        Gfx_MainMenu_FogScatter(FOG_COUNT);
    }

    FOG_COUNT++;
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
// UNKNOWN - IN-GAME LOOP RELATED
// ========================================

s32 Map_TypeGet() // 0x8003BD2C
{
    return D_800BCE18.field_0[0].type_0 - g_MapTypes;
}

void func_8003BD48(s_SubCharacter* chara) // 0x8003BD48
{
    u16 var_s0;

    D_800BCE14 = func_80069810();
    var_s0     = D_800BCE14;

    switch (Map_TypeGet())
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
    static s_FsImageDesc IMG = { .tPage = { 0, 12 }, .clutX = 192 };

    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &IMG);
}

void GameFs_BgItemLoad() // 0x8003BE9C
{
    D_800BCE18.field_1BE4.queueIdx_1000 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &D_800BCE18.field_1BE4);
}

void func_8003BED0() // 0x8003BED0
{
    static s_FsImageDesc IMG_TIM = { .tPage = { 0, 15 }, .clutX = 176 };
    static s_FsImageDesc IMG_ETC = { .tPage = { 0, 12 }, .v = 192, .clutX = 192 };

    s_LmHeader* D_800BE9FC = &D_800BCE18.field_1BE4;

    if (Fs_QueueIsEntryLoaded(D_800BE9FC->queueIdx_1000) == 0 || D_800BE9FC->isLoaded_2)
    {
        return;
    }

    LmHeader_FixOffsets(&D_800BCE18.field_1BE4);
    func_80056504(&D_800BCE18.field_1BE4, "TIM00", &IMG_TIM, 1);
    func_80056504(&D_800BCE18.field_1BE4, "BG_ETC", &IMG_ETC, 1);
    func_80056954(&D_800BCE18.field_1BE4);
}

// ========================================
// UNKNOWN
// ========================================

extern s_800C4168 const D_800C4168;

s32 Map_SpeedZoneGet(s32 x, s32 z) // 0x8003BF60
{
    s32          ret;
    s_SpeedZone* ptr;

    ret = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
    {
        return SpeedZoneType_Normal;
    }

    if (D_800BCE18.field_0[0].type_0->speedZones_C != NULL)
    {
        ptr = D_800BCE18.field_0[0].type_0->speedZones_C;

        while (ptr->speedIdx_0 != NO_VALUE)
        {
            if (x >= (ptr->minX_2 << 8) && (ptr->maxX_4 << 8) >= x &&
                z >= (ptr->minZ_6 << 8) && (ptr->maxZ_8 << 8) >= z &&
                ret < ptr->speedIdx_0)
            {
                ret = ptr->speedIdx_0;
            }

            ptr++;
        }
    }

    return ret;
}

void func_8003C048() // 0x8003C048
{
    func_80055028();

    D_800BCE18.field_0[0].field_4 = 0;

    func_80041C24((s_LmHeader*)0x8016B600, 0x80175600, 0x2C000);
    func_800697EC();

    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    func_8003EBA0();
    func_8005B55C(vwGetViewCoord());
    func_8003CB3C(&D_800BCE18);
}

void func_8003C0C0() // 0x8003C0C0
{
    s_800BCE18_1BAC* ptr = &D_800BCE18.field_1BAC;

    ptr->itemId_0 = NO_VALUE;
    ptr->field_14 = (s_LmHeader*)(Fs_GetFileSize(FILE_CHARA_HERO_ILM) + 0x800FE600); // `field_14` defined as a pointer?
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
    arg0->lmHeader_8 = (s_LmHeader*)((void*)0x800FEE00 + Fs_GetFileSize(FILE_CHARA_HERO_ILM));
    arg0->texture_C   = sp10;
}

void func_8003C220(s_MapOverlayHeader* mapHeader, s32 playerPosX, s32 playerPosZ) // 0x8003C220
{
    s32        var_a2;
    u8         temp_v1;
    s_MapType* ptr;

    D_800BCE18.field_0[0].type_0 = mapHeader->type_0;
    temp_v1 = mapHeader->type_0->flags_6;

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

    ptr = mapHeader->type_0;
    func_800421D8(ptr->tag_2, ptr->plmFileIdx_0, var_a2, ((ptr->flags_6 >> 2) ^ 1) & (1 << 0), 0, 0);

    if (mapHeader->type_0 == &g_MapTypes[0])
    {
        Map_PlaceIpdAtGridPos(FILE_BG_THR05FD_IPD, -1, 8);
    }

    func_80042C3C(playerPosX, playerPosZ, playerPosX, playerPosZ);
}

void func_8003C2EC() // 0x8003C2EC
{
    func_80041FF0();
}

void func_8003C30C() // 0x8003C30C
{
    u8 temp_v1;

    temp_v1 = D_800BCE18.field_0[0].type_0->flags_6;
    
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
    VECTOR3         pos0;
    VECTOR3         pos1;
    SVECTOR         pos2;
    s32             temp_a1;
    s32             temp_a2;
    s32             moveAmt;
    s32             temp_s0_2;
    s32             temp_v1_4;
    s32             var_a0;
    s32             var_a1;
    s32             var_s1;
    u8              flags1;
    u8              flags0;
    s_SubCharacter* chara = &g_SysWork.player_4C.chara_0;

    if ((u8)D_800BCE18.field_0[0].field_4 != 0)
    {
        pos0 = D_800BCE18.field_0[0].field_8;
    }
    else
    {
        pos0 = chara->position_18;
    }

    moveAmt = (chara->moveSpeed_38 * FP_METER(5.5f)) / 16015; // TODO: `FP_METER(3.91f)`? What's this doing?
    moveAmt = CLAMP(moveAmt, FP_METER(0.0f), FP_METER(5.5f));

    pos0.vx += FP_MULTIPLY_PRECISE(moveAmt, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
    pos0.vz += FP_MULTIPLY_PRECISE(moveAmt, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

    if (D_800BCE18.field_0[0].type_0 == &g_MapTypes[0] &&
        chara->position_18.vx >= FP_METER(-40.0f) && chara->position_18.vx <= FP_METER(40.0f) &&
        chara->position_18.vz >= FP_METER(200.0f) && chara->position_18.vz <= FP_METER(240.0f))
    {

        pos0.vz = FP_METER(200.0f);
    }

    if (D_800C4168.fogEnabled_1)
    {
        vwGetViewPosition(&pos1);
        vwGetViewAngle(&pos2);

        flags1 = D_800BCE18.field_0[0].type_0->flags_6;
        if (!(flags1 & 0x4) || !(flags1 & 0x3))
        {
            var_s1 = FP_MULTIPLY(Math_Cos(pos2.vx), FP_METER(9.0f), Q12_SHIFT);
        }
        else
        {
            var_s1 = FP_METER(0.0f);
        }
        
        temp_s0_2 = FP_MULTIPLY(var_s1, Math_Sin(pos2.vy), Q12_SHIFT);
        temp_s0_2 = CLAMP(temp_s0_2, FP_METER(-6.0f), FP_METER(6.0f));

        temp_v1_4 = FP_MULTIPLY(var_s1, Math_Cos(pos2.vy), Q12_SHIFT);
        temp_v1_4 = CLAMP(temp_v1_4, FP_METER(-6.0f), FP_METER(6.0f));

        pos1.vx += temp_s0_2;
        pos1.vz += temp_v1_4;

        if (Vc_VectorMagnitudeCalc(pos1.vx - chara->position_18.vx, 0, pos1.vz - chara->position_18.vz) > 0x10000)
        {
            var_s1  = FP_METER(14.0f);
            pos1.vx = chara->position_18.vx + FP_MULTIPLY(Math_Sin(pos2.vy), var_s1, Q12_SHIFT);
            pos1.vz = chara->position_18.vz + FP_MULTIPLY(Math_Cos(pos2.vy), var_s1, Q12_SHIFT);
        }
    } 
    else
    {
        pos1     = chara->position_18;
        pos1.vx += FP_FROM(FP_TO(Math_Sin(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
        pos1.vz += FP_FROM(FP_TO(Math_Cos(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
    }

    flags0 = D_800BCE18.field_0[0].type_0->flags_6;
    if ((flags0 & 0x4) && (flags0 & 0x3))
    {
        var_a1 = chara->position_18.vx / FP_METER(2.5f);
        if (chara->position_18.vx < FP_METER(0.0f))
        {
            var_a1--;
        }

        var_a0  = chara->position_18.vz / FP_METER(2.5f);
        temp_a1 = var_a1 * FP_METER(2.5f);

        if (chara->position_18.vz < FP_METER(0.0f))
        {
            var_a0--;
        }

        temp_a2 = var_a0 * FP_METER(2.5f);

        pos0.vx = CLAMP(pos0.vx, temp_a1 + 1, temp_a1 + (FP_METER(2.5f) - 1));
        pos0.vz = CLAMP(pos0.vz, temp_a2 + 1, temp_a2 + (FP_METER(2.5f) - 1));
        pos1.vx = CLAMP(pos1.vx, temp_a1 + 1, temp_a1 + (FP_METER(2.5f) - 1));
        pos1.vz = CLAMP(pos1.vz, temp_a2 + 1, temp_a2 + (FP_METER(2.5f) - 1));
    }

    func_80042C3C(pos0.vx, pos0.vz, pos1.vx, pos1.vz);
}

s32 func_8003C850() // 0x8003C850
{
    func_8003C3AC();
    return func_80043740();
}

void func_8003C878(s32 arg0) // 0x8003C878
{
    func_8003CB44(&D_800BCE18);

    while (func_80043830())
    {
        func_8003C3AC();
        Fs_QueueWaitForEmpty();
    }

    func_80043A24(&g_OrderingTable0[g_ActiveBufferIdx], arg0);
    func_800550D0();
}

void func_8003C8F8(s_800BCE18_2BEC_0* arg0, char* newStr) // 0x8003C8F8
{
    arg0->field_10.field_9 = 0;
    arg0->field_0.field_0  = 0;

    StringCopy(arg0->field_10.string_0, newStr);

    arg0->field_10.field_8 = 0;
}

void func_8003C92C(s_800BCE18_2BEC_0* arg0, const VECTOR3* pos, const SVECTOR3* rot) // 0x8003C92C
{
    s32              vy;
    s32              vx;
    s32              vz;
    s32              coord0; // Q23.8
    s32              coord1; // Q23.8
    s32              coord2; // Q23.8
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
                if (!func_80056CB4(arg0, &D_800BCE18.field_1BE4, &arg0->field_10))
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

        coord0 = FP_METER_TO_GEO(pos->vx);
        coord1 = FP_METER_TO_GEO(pos->vy);
        coord2 = FP_METER_TO_GEO(pos->vz);
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

    coord.flg   = false;
    coord.super = NULL;

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

    temp_s2 = arg0->field_0.field_8;
    temp_s1 = &arg0->field_10;

    if (temp_a0 >= 3 && temp_a0 < 7)
    {
        if (!IpdHeader_IsLoaded(temp_a0 - 3))
        {
            arg0->field_10.field_9 = 0;
        }
    }

    // TODO: Some kind of 8-byte string compare inline/macro?
    if (*(u32*)&temp_s1->string_0[0] != *(u32*)&temp_s2->string_0[0] || *(u32*)&temp_s1->string_0[4] != *(u32*)&temp_s2->string_0[4])
    {
        arg0->field_10.field_9 = 0;
        return;
    }

    func_80057090(arg0, &g_OrderingTable0[g_ActiveBufferIdx], 1, arg1, arg2, 0);
}

s32 func_8003CD5C() // 0x8003CD5C
{
    return D_800BCE18.field_1BAC.itemId_0;
}

void func_8003CD6C(s_PlayerCombat* combat) // 0x8003CD6C
{
	#define INVENTORY_WEAPONS_ID_BASE InventoryItemId_KitchenKnife

    s32 itemId;
    s8  equippedWeaponId;

    equippedWeaponId = combat->equippedWeapon_F;
    itemId           = NO_VALUE;
    if (equippedWeaponId != NO_VALUE)
    {
        itemId = equippedWeaponId + INVENTORY_WEAPONS_ID_BASE;
    }

    func_8003CDA0(itemId);
}

s32 func_8003CDA0(s32 itemIdx) // 0x8003CDA0
{
    s32              fileIdx;
    s_800BCE18_1BAC* ptr;

    ptr = &D_800BCE18.field_1BAC;

    if (ptr->itemId_0 == itemIdx)
    {
        return 0;
    }

    ptr->itemId_0 = itemIdx;

    switch (itemIdx)
    {
        default:
            fileIdx = NO_VALUE;
            break;

        case NO_VALUE:
        case InventoryItemId_KitchenKnife:
        case InventoryItemId_Hammer:
        case InventoryItemId_Axe:
        case InventoryItemId_Handgun:
        case InventoryItemId_HuntingRifle:
        case InventoryItemId_Shotgun:
            fileIdx      = NO_VALUE;
            ptr->textureName_8 = "HERO";
            break;

        case InventoryItemId_SteelPipe:
            fileIdx      = FILE_ITEM_PIPE_TIM;
            ptr->textureName_8 = "PIPE";
            break;

        case InventoryItemId_CutscenePhone:
            fileIdx      = FILE_ITEM_PHONE_TIM;
            ptr->textureName_8 = "PHONE";
            break;

        case InventoryItemId_CutsceneFlauros:
            fileIdx      = FILE_ITEM_FLAUROS_TIM;
            ptr->textureName_8 = "FLAUROS";
            break;

        case InventoryItemId_CutsceneAglaophotis:
            fileIdx      = FILE_ITEM_AGLA_TIM;
            ptr->textureName_8 = "AGLA";
            break;

        case InventoryItemId_CutscenePlasticBottle:
            fileIdx      = FILE_ITEM_BOTL_TIM;
            ptr->textureName_8 = "BOTL";
            break;

        case InventoryItemId_CutsceneBaby:
            fileIdx      = FILE_ITEM_BABY_TIM;
            ptr->textureName_8 = "BABY";
            break;

        case InventoryItemId_CutsceneBloodPack:
            fileIdx      = FILE_ITEM_BLOOD_TIM;
            ptr->textureName_8 = "BLOOD";
            break;

        case InventoryItemId_Chainsaw:
            fileIdx      = FILE_ITEM_CSAW_TIM;
            ptr->textureName_8 = "CSAW";
            break;

        case InventoryItemId_HyperBlaster:
            fileIdx      = FILE_ITEM_HPRGUN_TIM;
            ptr->textureName_8 = "HPRGUN";
            break;

        case InventoryItemId_RockDrill:
            fileIdx      = FILE_ITEM_DRILL_TIM;
            ptr->textureName_8 = "DRILL";
            break;

        case InventoryItemId_Katana:
            fileIdx      = FILE_ITEM_KATANA_TIM;
            ptr->textureName_8 = "KATANA";
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

        case InventoryItemId_CutscenePhone:
            fileIdx = FILE_ITEM_PHONE_PLM;
            break;

        case InventoryItemId_CutsceneFlauros:
            fileIdx = FILE_ITEM_FLAUROS_PLM;
            break;

        case InventoryItemId_CutsceneAglaophotis:
            fileIdx = FILE_ITEM_AGLA_PLM;
            break;

        case InventoryItemId_CutscenePlasticBottle:
            fileIdx = FILE_ITEM_BOTL_PLM;
            break;

        case InventoryItemId_CutsceneBaby:
            fileIdx = FILE_ITEM_BABY_PLM;
            break;

        case InventoryItemId_CutsceneBloodPack:
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
    s_LmHeader*      lmHeader;

    ptr0 = &D_800BCE18.field_1BAC;

    if (ptr0->itemId_0 != NO_VALUE)
    {
        if (ptr0->itemId_0 == InventoryItemId_CutscenePhone)
        {
            coord = &g_SysWork.playerBoneCoords_890[HarryBone_LeftHand];
        } 
        else 
        {
            coord = &g_SysWork.playerBoneCoords_890[HarryBone_RightHand];
        }

        if (Fs_QueueIsEntryLoaded(ptr0->field_4)) 
        {
            lmHeader = ptr0->field_14;

            if (!lmHeader->isLoaded_2)
            {
                LmHeader_FixOffsets(lmHeader);
                func_80056504(lmHeader, ptr0->textureName_8, &ptr0->imageDesc_C, 1);
                func_80056954(lmHeader);
                func_80056C8C(&ptr0->field_18, ptr0->field_14, 0);
            }

            func_80049B6C(coord, &mat1, &mat0);
            func_80057090(&ptr0->field_18, &g_OrderingTable0[g_ActiveBufferIdx], 1, &mat0, &mat1, 0);
        }
    }
}

void func_8003D160() // 0x8003D160
{
    s_FsImageDesc    img;
    s32              queueIdx;
    s_800BCE18*      ptr;
    s_800BCE18_0_CC* ptr2;
    s_LmHeader*      addr = (void*)0x800FE600;

    func_8003D3BC(&img, 1, 0);

    ptr                               = &D_800BCE18;
    ptr2                              = &ptr->field_164C;
    D_800BCE18.field_0[0].field_18[1] = ptr2;

    Fs_QueueStartRead(CHARA_FILE_INFOS[1].modelFileIdx, addr);
    queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[1].textureFileIdx, FS_BUFFER_1, &img);

    D_800BCE18.field_164C.field_0   = 1;
    ptr2->field_1                   = 0;
    ptr2->field_4                   = queueIdx;
    ptr2->lmHeader_8                = addr;
    D_800BCE18.field_164C.texture_C = img;
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
                ret = func_8003D7D4(ids, i, (s_LmHeader*)D_800BCE18.field_0[0].field_14, &img);
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

    idx      = CHARA_FILE_INFOS[arg1].modelFileIdx;
    fileSize = Fs_GetFileSize(idx);

    Fs_GetFileSectorAlignedSize(idx);

    *arg0 += (fileSize + 3) & ~0x3;
}

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

void func_8003D468(s32 arg0, bool flag) // 0x8003D468
{
    s16              data[256];
    RECT             rect;
    s32              x;
    s32              i;
    s32              y;
    s_800BCE18_0_CC* temp_s0;

    temp_s0 = D_800BCE18.field_0[0].field_18[arg0];
    func_80056244(temp_s0->lmHeader_8, flag);

    rect.x = temp_s0->texture_C.clutX;
    rect.y = temp_s0->texture_C.clutY;
    rect.w = 16;
    rect.h = 16;

    DrawSync(0);
    StoreImage(&rect, &data);

    for (y = 0, i = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++, i++)
        {
            if (!flag)
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
    func_80056464(ptr->lmHeader_8, CHARA_FILE_INFOS[arg0].textureFileIdx, &ptr->texture_C, arg1);
    func_80056954(ptr->lmHeader_8);
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
            temp = (s32)ptr->lmHeader_8 + Fs_GetFileSize(CHARA_FILE_INFOS[fileIdx].modelFileIdx);
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

void func_8003D6E0(s32 arg0, s32 arg1, s_LmHeader* lmHeader, s_FsImageDesc* tex) // 0x8003D6E0
{
    s_FsImageDesc img;
    s_LmHeader*  plmHeaderPtr;

    if (lmHeader != NULL)
    {
        plmHeaderPtr = lmHeader;
    } 
    else if (D_800BCE18.field_0[arg1].field_CC.field_0 != 0) 
    {
        plmHeaderPtr = D_800BCE18.field_0[arg1].field_CC.lmHeader_8;
    } 
    else 
    {
        plmHeaderPtr = (s_LmHeader*)D_800BCE18.field_0[0].field_14;
        func_8003D354(&D_800BCE18.field_0[0].field_14, arg0); // Increments `field_14`?
    }

    if (tex != NULL)
    {
        img = *tex;
    } 
    else 
    {
        func_8003D3BC(&img, arg0, arg1);
    }

    func_8003D7D4(arg0, arg1, plmHeaderPtr, &img);
}

s32 func_8003D7D4(u32 arg0, s32 arg1, s_LmHeader* lmHeader, s_FsImageDesc* tex) // 0x8003D7D4
{
    s32              queueIdx;
    s32              idx;
    s_800BCE18_0_CC* ptr;
    s_FsImageDesc*   img;

    ptr = &D_800BCE18.field_0[arg1].field_CC;
    idx = ptr->field_0;
    img = &ptr->texture_C;

    if (arg0 == 0) 
    {
        D_800BCE18.field_0[0].field_18[idx] = NULL;
        return 0;
    }

    if (idx != 0) 
    {
        if (arg0 == idx) 
        {
            if (lmHeader == ptr->lmHeader_8 && memcmp(tex, img, sizeof(s_FsImageDesc)) == 0)
            {
                return 0;
            }
        }

        D_800BCE18.field_0[0].field_18[idx] = NULL;
    }

    D_800BCE18.field_0[0].field_18[arg0] = ptr;

    queueIdx = Fs_QueueStartRead(CHARA_FILE_INFOS[arg0].modelFileIdx, lmHeader);

    if (CHARA_FILE_INFOS[arg0].textureFileIdx != NO_VALUE) 
    {
        queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[arg0].textureFileIdx, FS_BUFFER_1, tex);
    }

    ptr->field_0    = arg0;
    ptr->field_1    = 0;
    ptr->field_4    = queueIdx;
    ptr->lmHeader_8 = lmHeader;
    ptr->texture_C  = *tex;

    return queueIdx;
}

void func_8003D938() // 0x8003D938
{
    func_8003D9C8(&D_800BCE18.field_164C);
}

void func_8003D95C() // 0x8003D95C
{
    s_800BCE18_0_CC* temp_a0;
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

        LmHeader_FixOffsets(arg0->lmHeader_8);
        func_80056464(arg0->lmHeader_8, CHARA_FILE_INFOS[arg0->field_0].textureFileIdx, &arg0->texture_C, CHARA_FILE_INFOS[arg0->field_0].field_6_10 % 4);

        skel = &arg0->field_14;

        func_80056954(arg0->lmHeader_8);
        func_80044FE0(skel, &arg0->field_14.field_C, 56); // TODO: Can't fit `s_Bone` at `field_C`. Check `s_Skeleton` size.
        func_8004506C(skel, arg0->lmHeader_8);
        func_800452EC(skel);
        func_800453E8(skel, true);
    }
}

void func_8003DA9C(s32 arg0, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4) // 0x8003DA9C
{
    CVECTOR sp20 = { 0 };
    s16     ret;

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
        sp20 = D_800C4168.worldTintColor_28;

        func_80055330(D_800C4168.field_0, D_800C4168.field_20,
                      D_800C4168.field_3,
                      FP_MULTIPLY_PRECISE(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, D_800C4168.worldTintColor_28.r, Q12_SHIFT) << 5,
                      FP_MULTIPLY_PRECISE(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, D_800C4168.worldTintColor_28.g, Q12_SHIFT) << 5,
                      FP_MULTIPLY_PRECISE(FP_FLOAT_TO(1.0f, Q12_SHIFT) - arg3, D_800C4168.worldTintColor_28.b, Q12_SHIFT) << 5,
                      D_800C4168.screenBrightness_8);
    }

    func_80045534(&D_800BCE18.field_0[0].field_18[arg0]->field_14, &g_OrderingTable0[g_ActiveBufferIdx], arg2,
                  coord, CHARA_FILE_INFOS[arg0].field_6 * 16, ret, CHARA_FILE_INFOS[arg0].field_8);

    if (arg3 != 0)
    {
        func_80055330(D_800C4168.field_0, D_800C4168.field_20, D_800C4168.field_3, sp20.r << 5, sp20.g << 5, sp20.b << 5, D_800C4168.screenBrightness_8);
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
    }
}

void func_8003DE60(s_Skeleton* skel, s32 arg1) // 0x8003DE60
{
    s32 temp_s0;

    static s32 D_800A9ECC = 0xFE16FD13;
    static s32 D_800A9ED0 = 0x0000FE13;
    static s32 D_800A9ED4 = 0x0000FE14;
    static s32 D_800A9ED8 = 0x0000FE15;
    static s32 D_800A9EDC = 0x0000FE16;
    static s32 D_800A9EE0 = 0x000000FE;
    static s32 D_800A9EE4 = 0x00FE1211;
    static s32 D_800A9EE8 = 0x0000FE11;
    static s32 D_800A9EEC = 0x0000FE12;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9ECC, false);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9ED0, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9ED4, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9ED8, true);
                break;

            case 4:
                func_80045468(skel, &D_800A9EDC, true);
                break;

            case 5:
                func_80045468(skel, &D_800A9EE0, true);
                break;
        }
    }

    temp_s0 = arg1 & 0xF0;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9EE4, false);

        switch (temp_s0)
        {
            case 16:
                func_80045468(skel, &D_800A9EE8, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9EEC, true);
                break;
        }
    }
}

void func_8003DF84(s_Skeleton* skel, s32 arg1) // 0x8003DF84
{
    s32 temp_v1;

    static s32 D_800A9EF0 = 0x0000FE14;
    static s32 D_800A9EF4 = 0x00FE1514;
    static s32 D_800A9EF8 = 0x0000FE12;
    static s32 D_800A9EFC = 0x00FE1312;

    temp_v1 = arg1 & 0xF;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 1:
                func_80045468(skel, &D_800A9EF4, false);
                func_80045468(skel, &D_800A9EF0, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9EF0, false);
                func_80045468(skel, &D_800A9EF4, true);
                break;
        }
    }

    temp_v1 = arg1 & 0xF0;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 16:
                func_80045468(skel, &D_800A9EFC, false);
                func_80045468(skel, &D_800A9EF8, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9EF8, false);
                func_80045468(skel, &D_800A9EFC, true);
                break;
        }
    }
}

void func_8003E08C(s_Skeleton* skel, s32 arg1) // 0x8003E08C
{
    s32 temp_v1;

    static s32 D_800A9F00 = 0x0000FE02;
    static s32 D_800A9F04 = 0x0000FE03;
    static s32 D_800A9F08 = 0x0000FE00;
    static s32 D_800A9F0C = 0x00FE0100;

    temp_v1 = arg1 & 0xF;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 1:
                func_80045468(skel, &D_800A9F04, false);
                func_80045468(skel, &D_800A9F00, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F00, false);
                func_80045468(skel, &D_800A9F04, true);
                break;
        }
    }

    temp_v1 = arg1 & 0xF0;
    if (temp_v1 != 0)
    {
        switch (temp_v1)
        {
            case 16:
                func_80045468(skel, &D_800A9F0C, false);
                func_80045468(skel, &D_800A9F08, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9F08, false);
                func_80045468(skel, &D_800A9F0C, true);
                break;
        }
    }
}

void func_8003E194(s_Skeleton* skel, s32 arg1) // 0x8003E194
{
    s32 temp_s0;

    static s32 D_800A9F10 = 0xFE03FD00;
    static s32 D_800A9F14 = 0x0000FE00;
    static s32 D_800A9F18 = 0x00FE0201;
    static s32 D_800A9F1C = 0x0000FE03;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9F10, false);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F14, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F18, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F1C, true);
                break;
        }
    }
}

void func_8003E238(s_Skeleton* skel, s32 arg1) // 0x8003E238
{
    s32 var_s0;

    static s32 D_800A9F20 = 0x06050403;
    static s32 D_800A9F24 = 0x000000FE; // @unused
    static s32 D_800A9F28 = 0x0000FE03;
    static s32 D_800A9F2C = 0x0000FE04;
    static s32 D_800A9F30 = 0x00FE0504;
    static s32 D_800A9F34 = 0x00FE0603;
    static s32 D_800A9F38 = 0xFE020100;
    static s32 D_800A9F3C = 0x0000FE00;
    static s32 D_800A9F40 = 0x0000FE01;
    static s32 D_800A9F44 = 0x00FE0201;

    var_s0 = arg1 & 0xF;
    if (var_s0 != 0)
    {
        func_80045468(skel, &D_800A9F20, false);

        switch (var_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F28, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F2C, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F30, true);
                break;

            case 4:
                func_80045468(skel, &D_800A9F34, true);
                break;
        }
    }


    var_s0 = arg1 & 0xF0;
    if (var_s0 != 0)
    {
        func_80045468(skel, &D_800A9F38, false);

        switch (var_s0)
        {
            case 16:
                func_80045468(skel, &D_800A9F3C, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9F40, true);
                break;

            case 48:
                func_80045468(skel, &D_800A9F44, true);
                break;
        }
    }
}

void func_8003E388(s_Skeleton* skel, s32 arg1) // 0x8003E388
{
    s32 temp_a1;

    static s32 D_800A9F48 = 0x0000FE05;
    static s32 D_800A9F4C = 0x0000FE06;

    temp_a1 = arg1 & 0xF;
    if (temp_a1 != 0)
    {
        switch (temp_a1)
        {
            case 1:
                func_80045468(skel, &D_800A9F4C, false);
                func_80045468(skel, &D_800A9F48, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F48, false);
                func_80045468(skel, &D_800A9F4C, true);
                break;
        }
    }
}

void func_8003E414(s_Skeleton* skel, s32 arg1) // 0x8003E414
{
    s32 temp_a1;

    static s32 D_800A9F50 = 0xFE19FD11;
    static s32 D_800A9F54 = 0xFE22FD1A;

    temp_a1 = arg1 & 0x3;
    if (temp_a1 != 0)
    {
        switch (temp_a1)
        {
            case 1:
                func_80045468(skel, &D_800A9F50, false);
                func_80045468(skel, &D_800A9F54, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F54, false);
                func_80045468(skel, &D_800A9F50, true);
                break;
        }
    }
}

void func_8003E4A0(s_Skeleton* skel, s32 arg1) // 0x8003E4A0
{
    s32 temp_s0;

    static s32 D_800A9F58 = 0x05040302;
    static s32 D_800A9F5C = 0x00FE0706; // @unused
    static s32 D_800A9F60 = 0x00FE0502;
    static s32 D_800A9F64 = 0x00FE0603;
    static s32 D_800A9F68 = 0x00FE0704;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 != 0)
    {
        func_80045468(skel, &D_800A9F58, false);

        switch (temp_s0)
        {
            case 1:
                func_80045468(skel, &D_800A9F60, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F64, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F68, true);
                break;
        }
    }
}

void func_8003E544(s_Skeleton* skel, s32 arg1) // 0x8003E544
{
    s32 temp_s0;

    static s32 D_800A9F6C = 0x05040302;
    static s32 D_800A9F70 = 0x00FE0706; // @unused
    static s32 D_800A9F74 = 0x00FE0502;
    static s32 D_800A9F78 = 0x00FE0603;
    static s32 D_800A9F7C = 0x00FE0704;

    temp_s0 = arg1 & 0xF;
    if (temp_s0 == 0)
    {
        return;
    }

    func_80045468(skel, &D_800A9F6C, false);

    switch (temp_s0)
    {
        case 1:
            func_80045468(skel, &D_800A9F74, true);
            break;

        case 2:
            func_80045468(skel, &D_800A9F78, true);
            break;

        case 3:
            func_80045468(skel, &D_800A9F7C, true);
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
    ot     = &g_OrderingTable0[g_ActiveBufferIdx].org[1];

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

static s_800A9F80 D_800A9F80 = { 1, 1  };
static s_800A9F80 D_800A9F84 = { 2, 2  };
static s_800A9F80 D_800A9F88 = { 6, 3  };
static s_800A9F80 D_800A9F8C = { 7, 4  };
static s_800A9F80 D_800A9F90 = { 6, 10 }; // @unused
static s_800A9F80 D_800A9F94 = { 6, 5  }; // @unused
static s_800A9F80 D_800A9F98 = { 9, 9  };
static s_800A9F80 D_800A9F9C = { 6, 6  }; // @unused
static s_800A9F80 D_800A9FA0 = { 3, 3  }; // @unused
static s_800A9F80 D_800A9FA4 = { 5, 5  }; // @unused

void GameFs_FlameGfxLoad() // 0x8003E710
{
    static s_FsImageDesc IMG_FLAME = { .tPage = { 0, 12 }, .u = 32, .v = 0, .clutX = 800, .clutY = 64 };

    Fs_QueueStartReadTim(FILE_TIM_FLAME_TIM, FS_BUFFER_1, &IMG_FLAME);
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

    static u32 D_800A9FB0 = 0;

    if (g_DeltaTime0 != FP_TIME(0.0))
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
    sp38.vx = FP_MULTIPLY(Math_AngleNormalize(D_800BCDE8[temp_s2++]), 5, Q12_SHIFT) + 1;
    sp38.vz = FP_MULTIPLY(Math_AngleNormalize(D_800BCDE8[temp_s2++]), 5, Q12_SHIFT) + 33;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    func_80049AF8(&g_SysWork.playerBoneCoords_890[HarryBone_RightHand], &sp18);
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

        setRGB0(poly, D_800A9FB0 + FP_COLOR(0.1875f), D_800A9FB0 + FP_COLOR(0.1875f), D_800A9FB0 + FP_COLOR(0.1875f));
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

        AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[var_s5], poly);
        GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_FT4);
    }
}

/**
 * TODO: Please investigate me!
 */
void func_8003EB54() // 0x8003EB54
{
    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.field_2360, FP_METER(0.0f), FP_METER(-0.2f), FP_METER(-2.0f));
    Math_SVectorSet(&g_SysWork.field_2370, FP_ANGLE(10.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void func_8003EBA0() // 0x8003EBA0
{
    g_SysWork.field_2378 = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Torso];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.field_2360, FP_METER(-0.08f), FP_METER(-0.28f), FP_METER(0.12f));
    Math_SVectorSet(&g_SysWork.field_2370, FP_ANGLE(-15.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void func_8003EBF4(s_MapOverlayHeader* arg0) // 0x8003EBF4
{
    s32         var_v1;
    u8          temp_a1;
    s_800A9F80* ptr;

    temp_a1 = arg0->type_0->flags_6;

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
    g_SysWork.field_2388.isFlashlightOn_15 = true;
    g_SavegamePtr->flags_AC               &= ~(1 << 1);
}

void Game_TurnFlashlightOff() // 0x8003ECE4
{
    g_SysWork.field_2388.isFlashlightOn_15 = false;
    g_SavegamePtr->flags_AC               |= 1 << 1;
}

void func_8003ED08() // 0x8003ED08
{
    // Awkward `isFlashlightOn_15` toggle.
    g_SysWork.field_2388.isFlashlightOn_15 ^= true;
    if (g_SysWork.field_2388.isFlashlightOn_15 == true)
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
    return g_SysWork.field_2388.isFlashlightOn_15;
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

void func_8003EDB8(CVECTOR* color0, CVECTOR* color1) // 0x8003EDB8
{
    *color0 = g_SysWork.field_2388.field_1C[g_SysWork.field_2388.isFlashlightOn_15].field_0.field_21;
    *color1 = g_SysWork.field_2388.field_1C[g_SysWork.field_2388.isFlashlightOn_15].field_0.field_25;
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
        g_SysWork.field_2388.field_16 = true;
    }
    else
    {
        g_SysWork.field_2388.field_16 = false;
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
    s_SysWork_2288* ptr;

    ptr = &g_SysWork.field_2388;

    if (g_SysWork.field_2388.isFlashlightOn_15)
    {
        g_SysWork.field_2388.flashlightIntensity_18 += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_FLOAT_TO(4.0f, Q12_SHIFT), Q12_SHIFT);
    }
    else
    {
        g_SysWork.field_2388.flashlightIntensity_18 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_FLOAT_TO(4.0f, Q12_SHIFT), Q12_SHIFT);
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

        if (temp_v1 & (1 << 0))
        {
            func_8003F08C(ptr2, &D_800A952C.field_0);
        }
        else if (temp_v1 & 2)
        {
            ptr2->field_0.field_4 += 0x4CC;
        }
    }

    ptr->field_10 = func_8003FEC0(&ptr2->field_0);
    func_8003FF2C(ptr2);

    temp = FP_MULTIPLY(func_8003F4DC(&sp60, &sp58, ptr2->field_0.field_4, ptr2->field_0.field_0.s_field_0.field_2, func_80080A10(), &g_SysWork), g_SysWork.field_2378, Q12_SHIFT);

    func_800554C4(temp, ptr2->field_2C, sp60, g_SysWork.field_235C, &sp58, 
                  g_SysWork.field_2360.vx, g_SysWork.field_2360.vy, g_SysWork.field_2360.vz,
                  D_800BCE18.field_0[0].type_0->waterZones_8);
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

    rot->vy = -Math_Sin(vec.vx);
    temp    = Math_Cos(vec.vx);
    rot->vz = FP_MULTIPLY(temp, Math_Cos(vec.vy), Q12_SHIFT);
    rot->vx = FP_MULTIPLY(temp, Math_Sin(vec.vy), Q12_SHIFT);
    return res;
}

u32 func_8003F654(s_SysWork_2288* arg0)
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

s32 Math_WeightedAverageGet(s32 a, s32 b, s32 weight) // 0x8003F7E4
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
        arg0->field_2C = Math_WeightedAverageGet(0, arg2->field_2C, weight1);
    }
    else
    {
        arg0->field_2C = Math_WeightedAverageGet(arg1->field_2C, arg2->field_2C, weight0);
    }

    if (arg1->field_0.field_0.s_field_0.field_0 & (1 << 0))
    {
        if (arg2->field_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight);
        }
        else
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight1);
        }
    }
    else
    {
        if (arg2->field_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight0);
        }
        else
        {
            arg0->field_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->field_0.field_0.s_field_0.field_1, arg2->field_0.field_0.s_field_0.field_1, weight);
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

    arg0->field_0.field_8 = Math_WeightedAverageGet(arg1->field_0.field_8, arg2->field_0.field_8, weight);
    arg0->field_0.field_A = Math_WeightedAverageGet(arg1->field_0.field_A, arg2->field_0.field_A, weight);
    arg0->field_0.field_C = Math_WeightedAverageGet(arg1->field_0.field_C, arg2->field_0.field_C, weight);

    if (arg1->field_0.field_0.s_field_0.field_2 == 1 && arg2->field_0.field_0.s_field_0.field_2 == 2)
    {
        if (weight < FP_ALPHA(5.0f / 6.0f))
        {
            weight2                                 = FP_MULTIPLY(weight, FP_ALPHA(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(arg1->field_0.field_4, 0, weight2);
        }
        else
        {
            weight2                                 = (weight - FP_ALPHA(5.0f / 6.0f)) * 6;
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            weight0                                 = arg2->field_0.field_4;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(FP_ALPHA(0.0f), weight0, weight2);
        }
    }
    else if (arg1->field_0.field_0.s_field_0.field_2 == 2 && arg2->field_0.field_0.s_field_0.field_2 == 1)
    {
        if (weight < FP_ALPHA(1.0f / 6.0f))
        {
            weight2                                 = weight * 6;
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(arg1->field_0.field_4, FP_ALPHA(0.0f), weight2);
        }
        else
        {
            weight2                                 = FP_MULTIPLY(weight - FP_ALPHA(1.0f / 6.0f), FP_ALPHA(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, FP_ALPHA(0.0f), FP_ALPHA(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(FP_ALPHA(0.0f), arg2->field_0.field_4, weight2);
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

        arg0->field_0.field_4 = Math_WeightedAverageGet(arg1->field_0.field_4, arg2->field_0.field_4, weight);
    }

    if (arg1->field_0.field_18 == 0 && arg2->field_0.field_18 != 0)
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
    LoadAverageCol(&arg1->field_21.r, &arg2->field_21.r, p0, arg3, &arg0->field_21.r);
    LoadAverageCol(&arg1->field_25.r, &arg2->field_25.r, p0, arg3, &arg0->field_25.r);
}

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight0, s32 weight1, s32 alphaTo) // 0x8003FD38
{
    if (arg1->field_2E != arg2->field_2E)
    {
        arg0->field_2E = Math_WeightedAverageGet(arg1->field_2E, arg2->field_2E, weight0);
    }
    else
    {
        arg0->field_2E = arg2->field_2E;
    }

    arg0->field_30         = Math_WeightedAverageGet(arg1->field_30, arg2->field_30, weight0);
    arg0->field_0.field_10 = Math_WeightedAverageGet(arg1->field_0.field_10, arg2->field_0.field_10, weight1);
    arg0->field_0.field_6  = Math_WeightedAverageGet(arg1->field_0.field_6, arg2->field_0.field_6, weight0);

    LoadAverageCol(&arg1->field_0.fogColor_14.r, &arg2->field_0.fogColor_14.r, FP_ALPHA(1.0f) - alphaTo, alphaTo, &arg0->field_0.fogColor_14.r);
}

void func_8003FE04(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 alphaTo) // 0x8003FE04
{
    s32 alphaFrom;

    alphaFrom = FP_ALPHA(1.0f) - alphaTo;
    LoadAverageCol(&arg1->field_19.r, &arg2->field_19.r, alphaFrom, alphaTo, &arg0->field_19.r);
    LoadAverageCol(&arg1->field_1D.r, &arg2->field_1D.r, alphaFrom, alphaTo, &arg0->field_1D.r);

    if ((arg0->field_19.r || arg0->field_19.g || arg0->field_19.b) ||
        (arg0->field_1D.r || arg0->field_1D.g || arg0->field_1D.b))
    {
        arg0->field_18 = 1;
    }
    else
    {
        arg0->field_18 = 0;
    }
}

s32 func_8003FEC0(s_sub_StructUnk3* arg0) // 0x8003FEC0
{
    static q19_12 Y_ARRAY[5] =
    {
        FP_METER(1.75f),
        FP_METER(6.0f),
        FP_METER(9.5f),
        FP_METER(12.5f),
        FP_METER(15.0f)
    };

    if (D_800C4168.fogEnabled_1)
    {
        return arg0->field_10;
    }

    if (D_800C4168.field_0 == 1)
    {
        return vwOresenHokan(Y_ARRAY, ARRAY_SIZE(Y_ARRAY), arg0->field_4, 0, FP_FLOAT_TO(2.0f, Q12_SHIFT));
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
    Gfx_FogParamsSet(arg0->field_0.field_E != 0, arg0->field_0.fogColor_14.r, arg0->field_0.fogColor_14.g, arg0->field_0.fogColor_14.b);

    temp_a0 = arg0->field_0.field_10;

    func_80055840(temp_a0, temp_a0 + FP_FLOAT_TO(1.0f, Q12_SHIFT));
    func_800553E0(arg0->field_0.field_18, arg0->field_0.field_19.r, arg0->field_0.field_19.g, arg0->field_0.field_19.b, arg0->field_0.field_1D.r, arg0->field_0.field_1D.g, arg0->field_0.field_1D.b);
}

void func_80040004(s_800BCE18* arg0) // 0x80040004
{
    D_800BCE18.field_1BD8 = &arg0->field_0[2].field_26C;
}

void func_80040014() // 0x80040014
{
    func_80069860(g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz, D_800BCE18.field_1BD8);
};

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_8003AB28", D_80025BE4);
