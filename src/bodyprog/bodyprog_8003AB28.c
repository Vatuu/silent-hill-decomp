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

    bool        playIntroFmv;
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
        
        if (playIntroFmv)
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
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks    = 1;
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep = Q12(2.0f);
            g_MainMenuState++;

        case MenuState_Main:
            if (playIntroFmv)
            {
                GameFs_MapStartup();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == Q12(0.0f))
                {
                    g_Demo_ReproducedCount++;
                }

                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    g_Demo_ReproducedCount++;
                }
            }

            g_MainMenu_VisibleEntryFlags = (1 << MainMenuEntry_Start) | (1 << MainMenuEntry_Option);

            if (g_GameWork.autosave_90.playerHealth_240 > Q12(0.0f))
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
                Sd_EngineCmd(Sfx_Ui_Move);
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

                ScreenFade_Start(true, false, false);
                g_MainMenuState++;

                if (g_MainMenu_SelectedEntry < (u32)MainMenuEntry_Start) // TODO: Odd cast.
                {
                    Sd_EngineCmd(Sfx_StartGame);
                }
                else
                {
                    Sd_EngineCmd(Sfx_Ui_Confirm);
                }

                switch (g_MainMenu_SelectedEntry)
                {
                    case MainMenuEntry_Continue:
                        if (g_GameWork.autosave_90.playerHealth_240 > Q12(0.0f))
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
                        ScreenFade_Reset();
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
            if (playIntroFmv)
            {
                GameFs_MapStartup();

                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == Q12(0.0f))
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
                Sd_EngineCmd(Sfx_Ui_Move);
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

                ScreenFade_Start(true, false, false);
                g_MainMenuState     = 4;
            }
            // Cancel.
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(Sfx_Ui_Cancel);
                g_MainMenuState = 1;
            }
            break;

        case MenuState_LoadGame:
        case MenuState_NewGameStart:
            if (ScreenFade_IsFinished())
            {
                Screen_Refresh(SCREEN_WIDTH, 0);
                Fs_QueueWaitForEmpty();

                if (g_GameWork.autosave_90.playerHealth_240 > Q12(0.0f))
                {
                    NEXT_GAME_STATES[1] = 10;
                }

                if (g_MainMenu_SelectedEntry == MainMenuEntry_Start)
                {
                    Chara_PositionUpdateFromParams(&g_MapOverlayHeader.mapPointsOfInterest_1C[0]);
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

    if (!playIntroFmv)
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
    Screen_Init(SCREEN_WIDTH, false);
}

void MainMenu_SelectedOptionIdxReset() // 0x8003B550
{
    g_MainMenu_SelectedEntry = MainMenuEntry_Continue;
}

void func_8003B560() {}

static const char* MAIN_MENU_ENTRY_STRINGS[] = {
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
            Gfx_StringDraw("[", DEFAULT_MAP_MESSAGE_LENGTH);
        }
        else
        {
            Gfx_StringDraw("_", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw(MAIN_MENU_ENTRY_STRINGS[i], DEFAULT_MAP_MESSAGE_LENGTH);

        if (i == g_MainMenu_SelectedEntry)
        {
            Gfx_StringDraw("]", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw("\n", DEFAULT_MAP_MESSAGE_LENGTH);
    }
}

static const char* DIFFICULTY_MENU_ENTRY_STRINGS[] = {
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

    static const u8 STR_OFFSETS_X[] = { 28, 43, 30, 76 };               // @unused Last element may have been for a 4th selectable difficulty. "INTENSE" fits this offset.
    static const u8 UNUSED[]        = { 0, 149, 171, 144, 0, 0, 0, 0 }; // @unused Unknown purpose.

    s32 i;

    // Draw selection strings.
    for (i = 0; i < DIFFICULTY_MENU_SELECTION_COUNT; i++)
    {
        Gfx_StringSetPosition(COLUMN_POS_X - STR_OFFSETS_X[i], COLUMN_POS_Y + (i * STR_OFFSET_Y));
        Gfx_StringSetColor(StringColorId_White);

        if (i == arg0)
        {
            Gfx_StringDraw("[", DEFAULT_MAP_MESSAGE_LENGTH);
        }
        else
        {
            Gfx_StringDraw("_", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw(DIFFICULTY_MENU_ENTRY_STRINGS[i], DEFAULT_MAP_MESSAGE_LENGTH);

        if (i == arg0)
        {
            Gfx_StringDraw("]", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw("\n", DEFAULT_MAP_MESSAGE_LENGTH);
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

u32 D_800A9AAC[256] = {
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
    return g_WorldGfx.type_0 - MAP_TYPES;
}

void func_8003BD48(s_SubCharacter* chara) // 0x8003BD48
{
    u16 var_s0;

    D_800BCE14 = func_80069810();
    var_s0     = D_800BCE14;

    switch (Map_TypeGet())
    {
        case 0:
            if (chara->position_18.vx >= Q12(191.6f) && chara->position_18.vx <= Q12(198.8f) && 
                chara->position_18.vz >= Q12(-96.0f) && chara->position_18.vz <= Q12(-90.3f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
            break;

        case 3:
        case 4:
            if (chara->position_18.vx >= Q12(-100.0f) && chara->position_18.vx <= Q12(-94.5f) && 
                chara->position_18.vz >= Q12(-70.3f) && chara->position_18.vz <= Q12(-62.0f)) 
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

s_Bone* WorldGfx_CharaModelBonesGet(e_CharacterId charaId) // 0x8003BE50
{
    return g_WorldGfx.registeredCharaModels_18[charaId]->skeleton_14.bones_C;
}

// ========================================
// BOOT LOADING FILES
// ========================================

void GameFs_BgEtcGfxLoad() // 0x8003BE6C
{
    static s_FsImageDesc IMAGE = { .tPage = { 0, 12 }, .clutX = 192 };

    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &IMAGE);
}

void GameFs_BgItemLoad() // 0x8003BE9C
{
    g_WorldGfx.itemLmQueueIdx_2BE4 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &g_WorldGfx.itemLmHdr_1BE4);
}

void func_8003BED0() // 0x8003BED0
{
    static s_FsImageDesc IMAGE_TIM = {
        .tPage = { 0, 15 },
        .u     = 0,
        .v     = 0,
        .clutX = 176,
        .clutY = 0
    };

    static s_FsImageDesc IMAGE_ETC = {
        .tPage = { 0, 12 },
        .u     = 0,
        .v     = 192,
        .clutX = 192,
        .clutY = 0
    };

    s_LmHeader* itemLmHdr;

    itemLmHdr = &g_WorldGfx.itemLmHdr_1BE4;

    if (!Fs_QueueIsEntryLoaded(g_WorldGfx.itemLmQueueIdx_2BE4) || itemLmHdr->isLoaded_2)
    {
        return;
    }

    LmHeader_FixOffsets(&g_WorldGfx.itemLmHdr_1BE4);
    func_80056504(&g_WorldGfx.itemLmHdr_1BE4, "TIM00", &IMAGE_TIM, 1);
    func_80056504(&g_WorldGfx.itemLmHdr_1BE4, "BG_ETC", &IMAGE_ETC, 1);
    Lm_MaterialFlagsApply(&g_WorldGfx.itemLmHdr_1BE4);
}

// ========================================
// UNKNOWN
// ========================================

extern s_800C4168 const D_800C4168;

s32 Map_SpeedZoneTypeGet(q19_12 posX, q19_12 posZ) // 0x8003BF60
{
    s32                zoneType;
    const s_SpeedZone* curZone;

    zoneType = SpeedZoneType_Slow;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
    {
        return SpeedZoneType_Normal;
    }

    if (g_WorldGfx.type_0->speedZones_C != NULL)
    {
        curZone = g_WorldGfx.type_0->speedZones_C;
        while (curZone->type_0 != NO_VALUE)
        {
            if (posX >= Q4_TO_Q12(curZone->minX_2) && Q4_TO_Q12(curZone->maxX_4) >= posX &&
                posZ >= Q4_TO_Q12(curZone->minZ_6) && Q4_TO_Q12(curZone->maxZ_8) >= posZ &&
                zoneType < curZone->type_0)
            {
                zoneType = curZone->type_0;
            }

            curZone++;
        }
    }

    return zoneType;
}

void func_8003C048() // 0x8003C048
{
    func_80055028();

    g_WorldGfx.useStoredPoint_4 = false;

    Map_Init(GLOBAL_LM_BUFFER, IPD_BUFFER, 0x2C000);
    func_800697EC();

    g_SysWork.field_2378 = Q12(1.0f);

    func_8003EBA0();
    func_8005B55C(vwGetViewCoord());
    func_8003CB3C(&g_WorldGfx);
}

void func_8003C0C0() // 0x8003C0C0
{
    s_HeldItem* heldItem;

    heldItem = &g_WorldGfx.heldItem_1BAC;

    heldItem->itemId_0 = NO_VALUE;
    heldItem->lmHdr_14 = HELD_ITEM_LM_BUFFER;
    heldItem->bone_18.modelInfo_0.field_0 = 0;
    heldItem->bone_18.modelInfo_0.field_4 = NULL;
    heldItem->bone_18.modelInfo_0.modelHdr_8 = NULL;
}

void func_8003C110() // 0x8003C110
{
    s32           i;
    s_CharaModel* curModel;

    for (i = 0; i < Chara_Count; i++)
    {
        if (i != Chara_Harry)
        {
            g_WorldGfx.registeredCharaModels_18[i] = NULL;
        }
    } 

    g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER;
    for (curModel = &g_WorldGfx.charaModels_CC[0]; curModel < &g_WorldGfx.charaModels_CC[4]; curModel++)
    {
        CharaModel_Free(curModel);
    }
}

void CharaModel_Free(s_CharaModel* model) // 0x8003C1AC
{
    s_FsImageDesc image = { 0 };

    //memset(&image, 0, 8);
    model->charaId_0  = Chara_None;
    model->isLoaded_1 = false;
    model->queueIdx_4 = 0;
    model->lmHdr_8    = MAP_CHARA_LM_BUFFER;
    model->texture_C  = image;
}

void func_8003C220(s_MapOverlayHeader* mapHdr, s32 playerPosX, s32 playerPosZ) // 0x8003C220
{
    s32        activeIpdCount;
    u8         flags;
    s_MapType* mapType;

    g_WorldGfx.type_0 = mapHdr->type_0;

    flags = mapHdr->type_0->flags_6;
    if (flags & MapTypeFlag_OneActiveChunk)
    {
        activeIpdCount = 1;
    } 
    else if (flags & MapTypeFlag_TwoActiveChunks)
    {
        activeIpdCount = 2;
    }
    else
    {
        activeIpdCount = 4;
    }

    mapType = mapHdr->type_0;
    func_800421D8(mapType->tag_2, mapType->plmFileIdx_0, activeIpdCount, CHECK_FLAG(mapType->flags_6, MapTypeFlag_Interior, false), 0, 0);

    if (mapHdr->type_0 == &MAP_TYPES[0])
    {
        Map_PlaceIpdAtGridPos(FILE_BG_THR05FD_IPD, -1, 8);
    }

    func_80042C3C(playerPosX, playerPosZ, playerPosX, playerPosZ);
}

void Ipd_ActiveChunksClear1() // 0x8003C2EC
{
    Ipd_ActiveChunksClear0();
}

void func_8003C30C() // 0x8003C30C
{
    u8 flags;

    flags = g_WorldGfx.type_0->flags_6;
    if ((flags & MapTypeFlag_Interior) && (flags & (MapTypeFlag_OneActiveChunk | MapTypeFlag_TwoActiveChunks))) 
    {
        func_800420C0();
        return;
    }

    Ipd_ActiveChunksClear0();
    Ipd_TexturesInit0();
}

void WorldGfx_IpdSamplePointStore() // 0x8003C368
{
    g_WorldGfx.useStoredPoint_4 = true;
    g_WorldGfx.ipdSamplePoint_8 = g_SysWork.player_4C.chara_0.position_18;
}

void WorldGfx_IpdSamplePointReset() // 0x8003C3A0
{
    g_WorldGfx.useStoredPoint_4 = false;
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
    u8              flags0;
    u8              flags1;
    s_SubCharacter* chara;

    chara = &g_SysWork.player_4C.chara_0;

    if (g_WorldGfx.useStoredPoint_4)
    {
        pos0 = g_WorldGfx.ipdSamplePoint_8;
    }
    else
    {
        pos0 = chara->position_18;
    }

    moveAmt = (chara->moveSpeed_38 * Q12(5.5f)) / 16015; // TODO: `Q12(3.91f)`? What's this doing?
    moveAmt = CLAMP(moveAmt, Q12(0.0f), Q12(5.5f));

    pos0.vx += FP_MULTIPLY_PRECISE(moveAmt, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
    pos0.vz += FP_MULTIPLY_PRECISE(moveAmt, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

    if (g_WorldGfx.type_0 == &MAP_TYPES[0] &&
        chara->position_18.vx >= Q12(-40.0f) && chara->position_18.vx <= Q12(40.0f) &&
        chara->position_18.vz >= Q12(200.0f) && chara->position_18.vz <= Q12(240.0f))
    {

        pos0.vz = Q12(200.0f);
    }

    if (D_800C4168.isFogEnabled_1)
    {
        vwGetViewPosition(&pos1);
        vwGetViewAngle(&pos2);

        flags1 = g_WorldGfx.type_0->flags_6;
        if (!(flags1 & MapTypeFlag_Interior) || !(flags1 & (MapTypeFlag_OneActiveChunk | MapTypeFlag_TwoActiveChunks)))
        {
            var_s1 = FP_MULTIPLY(Math_Cos(pos2.vx), Q12(9.0f), Q12_SHIFT);
        }
        else
        {
            var_s1 = Q12(0.0f);
        }
        
        temp_s0_2 = FP_MULTIPLY(var_s1, Math_Sin(pos2.vy), Q12_SHIFT);
        temp_s0_2 = CLAMP(temp_s0_2, Q12(-6.0f), Q12(6.0f));

        temp_v1_4 = FP_MULTIPLY(var_s1, Math_Cos(pos2.vy), Q12_SHIFT);
        temp_v1_4 = CLAMP(temp_v1_4, Q12(-6.0f), Q12(6.0f));

        pos1.vx += temp_s0_2;
        pos1.vz += temp_v1_4;

        if (Vc_VectorMagnitudeCalc(pos1.vx - chara->position_18.vx, 0, pos1.vz - chara->position_18.vz) > 0x10000)
        {
            var_s1  = Q12(14.0f);
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

    flags0 = g_WorldGfx.type_0->flags_6;
    if ((flags0 & MapTypeFlag_Interior) && (flags0 & (MapTypeFlag_OneActiveChunk | MapTypeFlag_TwoActiveChunks)))
    {
        var_a1 = chara->position_18.vx / Q12(2.5f);
        if (chara->position_18.vx < Q12(0.0f))
        {
            var_a1--;
        }

        var_a0  = chara->position_18.vz / Q12(2.5f);
        temp_a1 = var_a1 * Q12(2.5f);

        if (chara->position_18.vz < Q12(0.0f))
        {
            var_a0--;
        }

        temp_a2 = var_a0 * Q12(2.5f);

        pos0.vx = CLAMP(pos0.vx, temp_a1 + 1, temp_a1 + (Q12(2.5f) - 1));
        pos0.vz = CLAMP(pos0.vz, temp_a2 + 1, temp_a2 + (Q12(2.5f) - 1));
        pos1.vx = CLAMP(pos1.vx, temp_a1 + 1, temp_a1 + (Q12(2.5f) - 1));
        pos1.vz = CLAMP(pos1.vz, temp_a2 + 1, temp_a2 + (Q12(2.5f) - 1));
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
    func_8003CB44(&g_WorldGfx);

    while (func_80043830())
    {
        func_8003C3AC();
        Fs_QueueWaitForEmpty();
    }

    func_80043A24(&g_OrderingTable0[g_ActiveBufferIdx], arg0);
    func_800550D0();
}

void WorldObject_ModelNameSet(s_WorldObject_0* arg0, char* newStr) // 0x8003C8F8
{
    arg0->field_10.lmIdx_9 = 0;
    arg0->modelInfo_0.field_0  = 0;

    StringCopy(arg0->field_10.name_0.str, newStr);

    arg0->field_10.field_8 = 0;
}

void g_WorldGfx_ObjectAdd(s_WorldObject_0* arg0, const VECTOR3* pos, const SVECTOR3* rot) // 0x8003C92C
{
    s32            vy;
    s32            vx;
    s32            vz;
    q23_8          coordX; // Q23.8
    q23_8          coordY; // Q23.8
    q23_8          coordZ; // Q23.8
    s32            i;
    s32            lmIdx;
    s_WorldObject* obj;

    if (g_WorldGfx.objectCount_2BE8 < 29)
    {
        if (arg0->field_10.lmIdx_9 == 0)
        {
            func_8003BED0();
            lmIdx = func_8004287C(arg0, &arg0->field_10, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz);

            if (lmIdx == 0)
            {
                if (!Lm_ModelFind(arg0, &g_WorldGfx.itemLmHdr_1BE4, &arg0->field_10))
                {
                    return;
                }
                else
                {
                    lmIdx = 1;
                }
            }

            arg0->field_10.lmIdx_9 = lmIdx;
        } 

        coordX = Q12_TO_Q8(pos->vx);
        coordY = Q12_TO_Q8(pos->vy);
        coordZ = Q12_TO_Q8(pos->vz);
        vx     = rot->vx >> 2;
        vz     = rot->vz >> 2;
        vy     = rot->vy;

        for (i = 0; i < g_WorldGfx.objectCount_2BE8; i++)
        {
            obj = &g_WorldGfx.objects_2BEC[i];
    
            if (arg0 == obj->field_0 &&
                coordX == obj->gsCoordinate0_4 &&
                coordZ == obj->gsCoordinate2_8 &&
                coordY == obj->gsCoordinate1_4 &&
                vx == obj->vx_C &&
                vy == obj->vy_C &&
                vz == obj->vz_C)
            {
                return;
            }
        }

        obj = &g_WorldGfx.objects_2BEC[g_WorldGfx.objectCount_2BE8];

        obj->vx_C = vx;
        obj->vy_C = vy;

        // TODO: Required for match.
        if (obj->gsCoordinate2_8) {}

        obj->vz_C            = vz;
        obj->field_0         = arg0;
        obj->gsCoordinate0_4 = coordX;
        obj->gsCoordinate1_4 = coordY;
        obj->gsCoordinate2_8 = coordZ;
        g_WorldGfx.objectCount_2BE8++;
    }
}

void func_8003CB3C(s_WorldGfx* worldGfx) // 0x8003CB3C
{
    worldGfx->objectCount_2BE8 = 0;
}

void func_8003CB44(s_WorldGfx* worldGfx) // 0x8003CB44
{
    s_WorldObject* curObj;

    for (curObj = &worldGfx->objects_2BEC[0]; curObj < &worldGfx->objects_2BEC[worldGfx->objectCount_2BE8]; curObj++)
    {
        func_8003CBA4(curObj);
    }

    worldGfx->objectCount_2BE8 = 0;
}

void func_8003CBA4(s_WorldObject* obj) // 0x8003CBA4
{
    GsCOORDINATE2 coord;
    SVECTOR       vec;
    MATRIX        mats[2];

    coord.flg   = false;
    coord.super = NULL;

    coord.coord.t[0] = obj->gsCoordinate0_4;
    coord.coord.t[1] = obj->gsCoordinate1_4;
    coord.coord.t[2] = obj->gsCoordinate2_8;

    // Unpack XYZ bitfield (TODO: Was this used anywhere else?)
    vec.vx = obj->vx_C << 2;
    vec.vy = obj->vy_C;
    vec.vz = obj->vz_C << 2;

    Math_MatrixRotate0(&vec, &coord.coord);
    func_80049B6C(&coord, &mats[1], &mats[0]);
    func_8003CC7C(obj->field_0, &mats[0], &mats[1]);
}

void func_8003CC7C(s_WorldObject_0* arg0, MATRIX* arg1, MATRIX* arg2) // 0x8003CC7C
{
    s8                  lmIdx;
    s_WorldObject_0_10* temp_s1;
    s_ModelHeader*      modelHdr;

    lmIdx = arg0->field_10.lmIdx_9;
    if (!lmIdx)
    {
        return;
    }

    modelHdr = arg0->modelInfo_0.modelHdr_8;
    temp_s1 = &arg0->field_10;

    if (lmIdx >= 3 && lmIdx < 7)
    {
        if (!IpdHeader_IsLoaded(lmIdx - 3))
        {
            arg0->field_10.lmIdx_9 = 0;
        }
    }

    if (COMPARE_FILENAMES(&temp_s1->name_0, &modelHdr->name_0))
    {
        arg0->field_10.lmIdx_9 = 0;
        return;
    }

    func_80057090(&arg0->modelInfo_0, &g_OrderingTable0[g_ActiveBufferIdx], 1, arg1, arg2, 0);
}

s32 func_8003CD5C() // 0x8003CD5C
{
    return g_WorldGfx.heldItem_1BAC.itemId_0;
}

void func_8003CD6C(s_PlayerCombat* combat) // 0x8003CD6C
{
    s32 itemId;
    s8  weaponAttack;

    weaponAttack = combat->weaponAttack_F;
    itemId       = NO_VALUE;
    if (weaponAttack != NO_VALUE)
    {
        itemId = weaponAttack + InventoryItemId_KitchenKnife;
    }

    WorldGfx_PlayerHeldItemSet(itemId);
}

s32 WorldGfx_PlayerHeldItemSet(e_InventoryItemId itemId) // 0x8003CDA0
{
    s32         fileIdx;
    s_HeldItem* heldItem;

    // Check if requested item is already being held.
    heldItem = &g_WorldGfx.heldItem_1BAC;
    if (heldItem->itemId_0 == itemId)
    {
        return 0;
    }

    // Define texture files to load.
    heldItem->itemId_0 = itemId;
    switch (itemId)
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
            fileIdx               = NO_VALUE;
            heldItem->textureName_8 = "HERO";
            break;

        case InventoryItemId_SteelPipe:
            fileIdx               = FILE_ITEM_PIPE_TIM;
            heldItem->textureName_8 = "PIPE";
            break;

        case InventoryItemId_CutscenePhone:
            fileIdx               = FILE_ITEM_PHONE_TIM;
            heldItem->textureName_8 = "PHONE";
            break;

        case InventoryItemId_CutsceneFlauros:
            fileIdx               = FILE_ITEM_FLAUROS_TIM;
            heldItem->textureName_8 = "FLAUROS";
            break;

        case InventoryItemId_CutsceneAglaophotis:
            fileIdx               = FILE_ITEM_AGLA_TIM;
            heldItem->textureName_8 = "AGLA";
            break;

        case InventoryItemId_CutscenePlasticBottle:
            fileIdx               = FILE_ITEM_BOTL_TIM;
            heldItem->textureName_8 = "BOTL";
            break;

        case InventoryItemId_CutsceneBaby:
            fileIdx               = FILE_ITEM_BABY_TIM;
            heldItem->textureName_8 = "BABY";
            break;

        case InventoryItemId_CutsceneBloodPack:
            fileIdx               = FILE_ITEM_BLOOD_TIM;
            heldItem->textureName_8 = "BLOOD";
            break;

        case InventoryItemId_Chainsaw:
            fileIdx               = FILE_ITEM_CSAW_TIM;
            heldItem->textureName_8 = "CSAW";
            break;

        case InventoryItemId_HyperBlaster:
            fileIdx               = FILE_ITEM_HPRGUN_TIM;
            heldItem->textureName_8 = "HPRGUN";
            break;

        case InventoryItemId_RockDrill:
            fileIdx               = FILE_ITEM_DRILL_TIM;
            heldItem->textureName_8 = "DRILL";
            break;

        case InventoryItemId_Katana:
            fileIdx               = FILE_ITEM_KATANA_TIM;
            heldItem->textureName_8 = "KATANA";
            break;
    }

    // Set texture UVs.
    if (fileIdx == NO_VALUE)
    {
        heldItem->imageDesc_C.tPage[1] = 27;
        heldItem->imageDesc_C.tPage[0] = 0;
        heldItem->imageDesc_C.u        = 0;
        heldItem->imageDesc_C.v        = 0;
        heldItem->imageDesc_C.clutX    = 736;
        heldItem->imageDesc_C.clutY    = 480;
    }
    else
    {
        heldItem->imageDesc_C.tPage[1] = 27;
        heldItem->imageDesc_C.tPage[0] = 0;
        heldItem->imageDesc_C.u        = 48;
        heldItem->imageDesc_C.v        = 224;
        heldItem->imageDesc_C.clutX    = 736;
        heldItem->imageDesc_C.clutY    = 498;
    }

    // Load texture.
    if (fileIdx != NO_VALUE)
    {
        heldItem->queueIdx_4 = Fs_QueueStartReadTim(fileIdx, FS_BUFFER_10, &heldItem->imageDesc_C);
    }

    // Define index of model file to lead.
    switch (itemId)
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

    // Load model.
    if (fileIdx != NO_VALUE)
    {
        heldItem->queueIdx_4 = Fs_QueueStartRead(fileIdx, heldItem->lmHdr_14);
        return heldItem->queueIdx_4;
    }

    return 0;
}

void func_8003D01C() // 0x8003D01C
{
    g_WorldGfx.heldItem_1BAC.bone_18.modelInfo_0.field_0 &= ~(1 << 31);
}

void func_8003D03C() // 0x8003D03C
{
    g_WorldGfx.heldItem_1BAC.bone_18.modelInfo_0.field_0 |= 1 << 31;
}

void func_8003D058() // 0x8003D058
{
    MATRIX         mat0;
    MATRIX         mat1;
    GsCOORDINATE2* coord;
    s_HeldItem*    heldItem;
    s_LmHeader*    lmHdr;

    // Check if held item is valid.
    heldItem = &g_WorldGfx.heldItem_1BAC;
    if (heldItem->itemId_0 == NO_VALUE)
    {
        return;
    }

    // Distinguish between left-handed and right-handed items.
    if (heldItem->itemId_0 == InventoryItemId_CutscenePhone)
    {
        coord = &g_SysWork.playerBoneCoords_890[HarryBone_LeftHand];
    } 
    else 
    {
        coord = &g_SysWork.playerBoneCoords_890[HarryBone_RightHand];
    }

    if (Fs_QueueIsEntryLoaded(heldItem->queueIdx_4)) 
    {
        lmHdr = heldItem->lmHdr_14;
        if (!lmHdr->isLoaded_2)
        {
            LmHeader_FixOffsets(lmHdr);
            func_80056504(lmHdr, heldItem->textureName_8, &heldItem->imageDesc_C, BlendMode_Additive);
            Lm_MaterialFlagsApply(lmHdr);
            Bone_ModelAssign(&heldItem->bone_18, heldItem->lmHdr_14, 0);
        }

        func_80049B6C(coord, &mat1, &mat0);
        func_80057090(&heldItem->bone_18.modelInfo_0, &g_OrderingTable0[g_ActiveBufferIdx], 1, &mat0, &mat1, 0);
    }
}

void WorldGfx_HarryCharaLoad() // 0x8003D160
{
    s_FsImageDesc image;
    s32           queueIdx;
    s_WorldGfx*   worldGfx;
    s_CharaModel* harryModel;
    s_LmHeader*   harryLmHdr;

    harryLmHdr = HARRY_LM_BUFFER;

    Chara_FsImageCalc(&image, Chara_Harry, 0);

    worldGfx                                         = &g_WorldGfx;
    harryModel                                       = &worldGfx->harryModel_164C;
    g_WorldGfx.registeredCharaModels_18[Chara_Harry] = harryModel;

    Fs_QueueStartRead(CHARA_FILE_INFOS[Chara_Harry].modelFileIdx, harryLmHdr);
    queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[Chara_Harry].textureFileIdx, FS_BUFFER_1, &image);

    g_WorldGfx.harryModel_164C.charaId_0 = Chara_Harry;
    harryModel->isLoaded_1               = false;
    harryModel->queueIdx_4               = queueIdx;
    harryModel->lmHdr_8                  = harryLmHdr;
    g_WorldGfx.harryModel_164C.texture_C = image;
}

s32 func_8003D21C(s_MapOverlayHeader* mapHdr) // 0x8003D21C
{
    s_FsImageDesc image;
    bool          cond;
    s32           i;
    s32           j;
    s32           queueIdx;
    s32           curCharaId;
    s_CharaModel* curModel;

    for (queueIdx = 0, i = 0, g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER, cond = false;
         i < GROUP_CHARA_COUNT;
         i++)
    {
        curCharaId = mapHdr->charaGroupIds_248[i];
        curModel   = &g_WorldGfx.charaModels_CC[i];

        if (curCharaId != Chara_None) 
        {
            if (!cond) 
            {
                if (curCharaId != curModel->charaId_0) 
                {
                    cond = true;
                    for (j = i; j < ARRAY_SIZE(g_WorldGfx.charaModels_CC); j++)
                    {
                        g_WorldGfx.charaModels_CC[j].charaId_0 = Chara_None;
                    }
                }
            } 

            if (cond) 
            {
                Chara_FsImageCalc(&image, curCharaId, i);
                queueIdx = WorldGfx_CharaModelLoad(curCharaId, i, (s_LmHeader*)g_WorldGfx.charaLmBuffer_14, &image);
            }

            WorldGfx_CharaLmBufferAdvance(&g_WorldGfx.charaLmBuffer_14, curCharaId);
        }
    }

    return queueIdx;
}

void WorldGfx_CharaLmBufferAdvance(u8** buf, e_CharacterId charaId) // 0x8003D354
{
    s16 modelFileIdx;
    s32 fileSize;

    modelFileIdx = CHARA_FILE_INFOS[charaId].modelFileIdx;
    fileSize     = Fs_GetFileSize(modelFileIdx);

    Fs_GetFileSectorAlignedSize(modelFileIdx);
    *buf += (fileSize + 3) & ~0x3;
}

void Chara_FsImageCalc(s_FsImageDesc* image, s32 charaId, s32 modelIdx) // 0x8003D3BC
{
    s16 clutX;
    s16 clutY;
    s8  tPage;
    s8  v;
    s8  u;

    // TODO: Deoptimise.
    v = charaId < Chara_AirScreamer;
    if (charaId >= Chara_None && v)
    {
        tPage = 27;
        v     = 0;
        u     = 0;
        clutX = 736;
        clutY = 480;
    }
    else 
    {
        clutY = 464;
        clutX = (modelIdx * 16) + 704;

        switch (modelIdx)
        {
            default:
                modelIdx = 0;

            case 0:
            case 1:
                tPage = 28;
                u     = 0;
                v     = modelIdx << 7;
                break;

            case 2:
            case 3:
                tPage = 29;
                u     = 0;
                v     = (modelIdx - 2) << 7;
                break;
        }
    }

    image->tPage[0] = 0;
    image->tPage[1] = tPage;
    image->u        = u;
    image->v        = v;
    image->clutX    = clutX;
    image->clutY    = clutY;
}

bool WorldGfx_IsCharaModelPresent(e_CharacterId charaId) // 0x8003D444
{
    return g_WorldGfx.registeredCharaModels_18[charaId] != NULL;
}

void func_8003D460() {}

void func_8003D468(e_CharacterId charaId, bool flag) // 0x8003D468
{
    s16           data[256];
    RECT          rect;
    s32           x;
    s32           i;
    s32           y;
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];
    func_80056244(model->lmHdr_8, flag);

    rect.x = model->texture_C.clutX;
    rect.y = model->texture_C.clutY;
    rect.w = 16;
    rect.h = 16;

    DrawSync(SyncMode_Wait);
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

void WorldGfx_CharaModelMaterialSet(s32 charaId, s32 blendMode) // 0x8003D550
{
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];
    Lm_MaterialFileIdxApply(model->lmHdr_8, CHARA_FILE_INFOS[charaId].textureFileIdx, &model->texture_C, blendMode);
    Lm_MaterialFlagsApply(model->lmHdr_8);
}

void WorldGfx_CharaLmBufferAssign(s8 forceFree) // 0x8003D5B4
{
    u8            charaId;
    s32           i;
    u32           lmData;
    s_CharaModel* curModel;

    for (i = 0; i < ARRAY_SIZE(g_WorldGfx.charaModels_CC); i++)
    {
        curModel = &g_WorldGfx.charaModels_CC[i];
        if ((forceFree >> i) & (1 << 0))
        {
            WorldGfx_CharaFree(curModel);
        }
    }

    i = 0; 
    g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER;
    for (; i < ARRAY_SIZE(g_WorldGfx.charaModels_CC); i++)
    {
        curModel = &g_WorldGfx.charaModels_CC[i];

        charaId = curModel->charaId_0;
        if (charaId != Chara_None)
        {
            lmData = (s32)curModel->lmHdr_8 + Fs_GetFileSize(CHARA_FILE_INFOS[charaId].modelFileIdx);
            if (g_WorldGfx.charaLmBuffer_14 < lmData)
            {
                g_WorldGfx.charaLmBuffer_14 = lmData;
            }
        }
    }
}

void WorldGfx_CharaFree(s_CharaModel* model) // 0x8003D6A4
{
    if (model->charaId_0 != Chara_None)
    {
        g_WorldGfx.registeredCharaModels_18[model->charaId_0] = NULL;
        CharaModel_Free(model);
    }
}

void WorldGfx_CharaLoad(e_CharacterId charaId, s32 modeIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x8003D6E0
{
    s_FsImageDesc image;
    s_LmHeader*   lmHdrBuf;

    // Set LM header.
    if (lmHdr != NULL)
    {
        lmHdrBuf = lmHdr;
    } 
    else if (g_WorldGfx.charaModels_CC[modeIdx].charaId_0 != Chara_None) 
    {
        lmHdrBuf = g_WorldGfx.charaModels_CC[modeIdx].lmHdr_8;
    } 
    else 
    {
        lmHdrBuf = (s_LmHeader*)g_WorldGfx.charaLmBuffer_14;
        WorldGfx_CharaLmBufferAdvance(&g_WorldGfx.charaLmBuffer_14, charaId);
    }

    // Set texture UVs.
    if (tex != NULL)
    {
        image = *tex;
    } 
    else 
    {
        Chara_FsImageCalc(&image, charaId, modeIdx);
    }

    WorldGfx_CharaModelLoad(charaId, modeIdx, lmHdrBuf, &image);
}

s32 WorldGfx_CharaModelLoad(e_CharacterId charaId, s32 modelIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x8003D7D4
{
    s32            queueIdx;
    s32            modelCharaId; // `e_CharacterId`
    s_CharaModel*  model;
    s_FsImageDesc* modelTex;

    model        = &g_WorldGfx.charaModels_CC[modelIdx];
    modelCharaId = model->charaId_0;
    modelTex     = &model->texture_C;

    // If character is invalid, set model as unused.
    if (charaId == Chara_None) 
    {
        g_WorldGfx.registeredCharaModels_18[modelCharaId] = NULL;
        return 0;
    }

    // Register character model.
    if (modelCharaId != Chara_None) 
    {
        if (charaId == modelCharaId) 
        {
            if (lmHdr == model->lmHdr_8 && memcmp(tex, modelTex, sizeof(s_FsImageDesc)) == 0)
            {
                return 0;
            }
        }

        g_WorldGfx.registeredCharaModels_18[modelCharaId] = NULL;
    }
    g_WorldGfx.registeredCharaModels_18[charaId] = model;

    // Load model and texture files.
    queueIdx = Fs_QueueStartRead(CHARA_FILE_INFOS[charaId].modelFileIdx, lmHdr);
    if (CHARA_FILE_INFOS[charaId].textureFileIdx != NO_VALUE) 
    {
        queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[charaId].textureFileIdx, FS_BUFFER_1, tex);
    }

    // Set loaded model data.
    model->charaId_0  = charaId;
    model->isLoaded_1 = false;
    model->queueIdx_4 = queueIdx;
    model->lmHdr_8    = lmHdr;
    model->texture_C  = *tex;
    return queueIdx;
}

void func_8003D938() // 0x8003D938
{
    func_8003D9C8(&g_WorldGfx.harryModel_164C);
}

void func_8003D95C() // 0x8003D95C
{
    s32           i;
    s_CharaModel* model;

    for (i = 0; i < Chara_Count; i++)
    {
        if (i != Chara_Harry) 
        {
            model = g_WorldGfx.registeredCharaModels_18[i];
            if (model != NULL) 
            {
                func_8003D9C8(model);
            }
        }
    }
}

void func_8003D9C8(s_CharaModel* model) // 0x8003D9C8
{
    s_Skeleton* skel;

    if (!model->isLoaded_1 && model->charaId_0 != Chara_None && Fs_QueueIsEntryLoaded(model->queueIdx_4))
    {
        model->isLoaded_1 = true;

        LmHeader_FixOffsets(model->lmHdr_8);
        Lm_MaterialFileIdxApply(model->lmHdr_8, CHARA_FILE_INFOS[model->charaId_0].textureFileIdx, &model->texture_C, CHARA_FILE_INFOS[model->charaId_0].materialBlendMode_6_10 % 4);

        skel = &model->skeleton_14;

        Lm_MaterialFlagsApply(model->lmHdr_8);
        Skeleton_Init(skel, model->skeleton_14.bones_C, 56);
        func_8004506C(skel, model->lmHdr_8);
        func_800452EC(skel);
        func_800453E8(skel, true);
    }
}

void func_8003DA9C(e_CharacterId charaId, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4) // 0x8003DA9C
{
    CVECTOR tintColor = { 0 };
    s16     ret;

    // Check if character is valid.
    if (charaId == Chara_None)
    {
        return;
    }

    arg3 = CLAMP(arg3, Q12(0.0f), Q12(1.0f));

    // Something to do with items held by player.
    if (charaId == Chara_Harry)
    {
        func_8003D058();
    }

    ret = func_8003DD74(charaId, arg4);

    if (arg3 != 0)
    {
        tintColor = D_800C4168.worldTintColor_28;

        func_80055330(D_800C4168.field_0, D_800C4168.field_20, D_800C4168.field_3,
                      FP_MULTIPLY_PRECISE(Q12(1.0f) - arg3, D_800C4168.worldTintColor_28.r, Q12_SHIFT) << 5,
                      FP_MULTIPLY_PRECISE(Q12(1.0f) - arg3, D_800C4168.worldTintColor_28.g, Q12_SHIFT) << 5,
                      FP_MULTIPLY_PRECISE(Q12(1.0f) - arg3, D_800C4168.worldTintColor_28.b, Q12_SHIFT) << 5,
                      D_800C4168.screenBrightness_8);
    }

    func_80045534(&g_WorldGfx.registeredCharaModels_18[charaId]->skeleton_14, &g_OrderingTable0[g_ActiveBufferIdx], arg2,
                  coord, Q8_TO_Q12(CHARA_FILE_INFOS[charaId].field_6), ret, CHARA_FILE_INFOS[charaId].field_8);

    if (arg3 != 0)
    {
        func_80055330(D_800C4168.field_0, D_800C4168.field_20, D_800C4168.field_3, tintColor.r << 5, tintColor.g << 5, tintColor.b << 5, D_800C4168.screenBrightness_8);
    }
}

s32 func_8003DD74(e_CharacterId charaId, s32 arg1) // 0x8003DD74
{
    return ((s32)arg1 << 10) & 0xFC00;
}

void func_8003DD80(e_CharacterId charaId, s32 arg1) // 0x8003DD80
{
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];

    switch (charaId)
    {
        case Chara_Harry:
            func_8003DE60(&model->skeleton_14, arg1);
            break;

        case Chara_Stalker:
            func_8003E388(&model->skeleton_14, arg1);
            break;

        case Chara_Cybil:
        case Chara_EndingCybil:
            func_8003DF84(&model->skeleton_14, arg1);
            break;

        case Chara_MonsterCybil:
            func_8003E08C(&model->skeleton_14, arg1);
            break;

        case Chara_Dahlia:
        case Chara_EndingDahlia:
            func_8003E194(&model->skeleton_14, arg1);
            break;

        case Chara_Kaufmann:
        case Chara_EndingKaufmann:
            func_8003E238(&model->skeleton_14, arg1);
            break;

        case Chara_Splithead:
            func_8003E414(&model->skeleton_14, arg1);
            break;

        case Chara_PuppetNurse:
            func_8003E4A0(&model->skeleton_14, arg1);
            break;

        case Chara_PuppetDoctor:
            func_8003E544(&model->skeleton_14, arg1);
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
    s32 val;

    static s32 D_800A9F48 = 0x0000FE05;
    static s32 D_800A9F4C = 0x0000FE06;

    val = arg1 & 0xF;
    if (val != 0)
    {
        switch (val)
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
    s32 val;

    static s32 D_800A9F50 = 0xFE19FD11;
    static s32 D_800A9F54 = 0xFE22FD1A;

    val = arg1 & 0x3;
    if (val == 0)
    {
        return;
    }

    switch (val)
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
    s32       i;
    u8        color;
    GsOT_TAG* ot;
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
    static s_FsImageDesc IMG_FLAME = {
        .tPage = { 0, 12 },
        .u     = 32,
        .v     = 0,
        .clutX = 800,
        .clutY = 64
    };

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

    if (g_DeltaTime0 != Q12(0.0))
    {
        D_800A9FB0 += 8;
        for (i = 0; i < 8; i++)
        {
            D_800BCDE8[i] = Rng_Rand16();
        }
    }

    sp38.vx = 1;
    sp38.vy = -7;
    sp38.vz = 33;
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

    if (temp_s6 >= 129 && var_s5 < 2047)
    {
        SetPolyFT4(poly);
        setSemiTrans(poly, 1);

        temp_a0 = D_800BCDE8[temp_s2++];

        if ((temp_a0 & 0xFFF) >= 3482)
        {
            D_800A9FB0 -= 16 + (temp_a0 & 0xF);
        }

        if (D_800A9FB0 >= 33)
        {
            D_800A9FB0 = 0;
        }

        setRGB0(poly, D_800A9FB0 + 48, D_800A9FB0 + 48, D_800A9FB0 + 48);
        poly->tpage = 44;
        poly->clut  = 4146;

        var_a0 = &D_800BCDE8[temp_s2++];

        for (i = 0; i < 4; i++)
        {
            sp40[i] = (var_a0[i] & 0xF) - 8;
        }

        SetRotMatrix(&GsIDMATRIX);
        SetTransMatrix(&GsIDMATRIX);

        sp50.vz = temp_s6;
        sp50.vx = sp40[0] - 51;
        sp50.vy = sp40[2] - 51;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x0 = sp10.vx + sp58.vx;
        poly->y0 = sp10.vy + sp58.vy;
        sp50.vx  = sp40[1] + 51;
        sp50.vy  = sp40[3] - 51;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x1 = sp10.vx + sp58.vx;
        poly->y1 = sp10.vy + sp58.vy;
        sp50.vx  = -51 - sp40[1];
        sp50.vy  = 51 - sp40[3];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x2 = sp10.vx + sp58.vx;
        poly->y2 = sp10.vy + sp58.vy;
        sp50.vx  = 51 - sp40[0];
        sp50.vy  = 51 - sp40[2];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x3 = sp10.vx + sp58.vx;
        poly->y3 = sp10.vy + sp58.vy;

        poly->u0 = 128;
        poly->u1 = 191;
        poly->u2 = 128;
        poly->u3 = 191;

        poly->v0 = 0;
        poly->v1 = 0;
        poly->v2 = 63;
        poly->v3 = 63;

        AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[var_s5], poly);
        GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_FT4);
    }
}

/**
 * TODO: Please investigate me!
 */
void func_8003EB54() // 0x8003EB54
{
    g_SysWork.field_2378 = Q12(1.0f);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.field_2360, Q12(0.0f), Q12(-0.2f), Q12(-2.0f));
    Math_SVectorSet(&g_SysWork.field_2370, FP_ANGLE(10.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void func_8003EBA0() // 0x8003EBA0
{
    g_SysWork.field_2378 = Q12(1.0f);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Torso];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.field_2360, Q12(-0.08f), Q12(-0.28f), Q12(0.12f));
    Math_SVectorSet(&g_SysWork.field_2370, FP_ANGLE(-15.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void func_8003EBF4(s_MapOverlayHeader* mapHdr) // 0x8003EBF4
{
    bool        hasActiveChunk;
    u8          flags;
    s_800A9F80* ptr;

    flags          = mapHdr->type_0->flags_6;
    hasActiveChunk = false;
    if (flags & MapTypeFlag_Interior)
    {
        hasActiveChunk = (flags & (MapTypeFlag_OneActiveChunk | MapTypeFlag_TwoActiveChunks)) > 0;
    }

    switch (mapHdr->field_16)
    {
        case 1:
            if (hasActiveChunk)
            {
                ptr = &D_800A9F84;
            }
            else
            {
                ptr = &D_800A9F80;
            }
            break;

        case 2:
            if (hasActiveChunk)
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

void Game_TurnFlashlightOn(void) // 0x8003ECBC
{
    g_SysWork.field_2388.isFlashlightOn_15 = true;
    g_SavegamePtr->itemToggleFlags_AC     &= ~ItemToggleFlag_FlashlightOff;
}

void Game_TurnFlashlightOff(void) // 0x8003ECE4
{
    g_SysWork.field_2388.isFlashlightOn_15 = false;
    g_SavegamePtr->itemToggleFlags_AC     |= ItemToggleFlag_FlashlightOff;
}

void Game_FlashlightToggle(void) // 0x8003ED08
{
    // Awkward `isFlashlightOn_15` toggle.
    g_SysWork.field_2388.isFlashlightOn_15 ^= true;
    if (g_SysWork.field_2388.isFlashlightOn_15 == true)
    {
        g_SavegamePtr->itemToggleFlags_AC &= ~ItemToggleFlag_FlashlightOff;
    }
    else
    {
        g_SavegamePtr->itemToggleFlags_AC |= ItemToggleFlag_FlashlightOff;
    }
}

bool Game_FlashlightIsOn() // 0x8003ED64
{
    return g_SysWork.field_2388.isFlashlightOn_15;
}

void func_8003ED74(s32 arg0, s32 arg1) // 0x8003ED74
{
    func_8003EF10(arg0, arg1, PrimitiveType_None, NULL, 0, 0);
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

void func_8003EE30(s32 arg0, s32* arg1, s32 arg2, s32 arg3) // 0x8003EE30
{
    g_SysWork.field_2388.field_4 = (s8*)arg1;
    g_SysWork.field_2388.field_0 = PrimitiveType_S32;
    g_SysWork.field_2388.field_8 = arg2;
    g_SysWork.field_2388.field_C = arg3;

    g_SysWork.field_2388.field_EC[0] = g_SysWork.field_2388.field_1C[0];
    g_SysWork.field_2388.field_EC[1] = g_SysWork.field_2388.field_1C[1];
}

void func_8003EEDC(s32 arg0, s32 arg1) // 0x8003EEDC
{
    func_8003EF10(arg0, arg1, PrimitiveType_None, NULL, 0, 0);
    func_8003F170();
}

void func_8003EF10(s32 idx0, s32 idx1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5) // 0x8003EF10
{
    func_8003EF74(&D_800A93CC[idx0], &D_800A93CC[idx1], primType, primData, arg4, arg5);
}

void func_8003EF74(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5) // 0x8003EF74
{
    if (arg0 == arg1)
    {
        g_SysWork.field_2388.field_16 = true;
    }
    else
    {
        g_SysWork.field_2388.field_16 = false;
    }

    g_SysWork.field_2388.field_4 = primData;
    g_SysWork.field_2388.field_0 = primType;
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
        arg0->field_2E = Q12(1.0f);
        arg0->field_2E = Q12(1.0f);
    }
    else
    {
        arg0->field_2E = Q12(0.0f);
    }

    if (arg1->field_0.s_field_0.field_0 & (1 << 4))
    {
        arg0->field_2C = Q12(1.0f);
    }
    else
    {
        arg0->field_2C = Q12(0.0f);
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
    MATRIX          mat;
    VECTOR          sp48;
    SVECTOR         rot;
    s32             temp_v0;
    u8              temp_v1;
    s32             temp;
    GsCOORDINATE2*  sp60;
    s_StructUnk3*   ptr2;
    s_SysWork_2288* ptr;

    ptr = &g_SysWork.field_2388;

    if (g_SysWork.field_2388.isFlashlightOn_15)
    {
        g_SysWork.field_2388.flashlightIntensity_18 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
    }
    else
    {
        g_SysWork.field_2388.flashlightIntensity_18 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
    }

    g_SysWork.field_2388.flashlightIntensity_18 = CLAMP(g_SysWork.field_2388.flashlightIntensity_18, Q12(0.0f), Q12(1.0f));

    if (g_SysWork.field_2388.field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].field_0.field_E == 3)
    {
        func_80049AF8(g_SysWork.field_235C, &mat);
        ApplyMatrixLV(&mat, (VECTOR*)&g_SysWork.field_2360, &sp48); // Bug? `g_SysWork.field_2360` is `VECTOR3`.
        ptr->field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].field_30 = sp48.vz + (mat.t[2] * 16);
    }

    if (ptr->field_0 == PrimitiveType_None)
    {
        ptr->field_1C[0] = ptr->field_84[0];
        ptr->field_1C[1] = ptr->field_84[1];
    }
    else
    {
        temp_v0 = func_8003F6F0(func_8003F654(ptr), ptr->field_8, ptr->field_C);

        func_8003F838(&ptr->field_1C[0], &ptr->field_EC[0], &ptr->field_84[0], temp_v0);
        func_8003F838(&ptr->field_1C[1], &ptr->field_EC[1], &ptr->field_84[1], temp_v0);

        if (temp_v0 >= Q12(1.0f))
        {
            ptr->field_0 = PrimitiveType_None;
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
            ptr2->field_0.field_4 += Q12(0.3f);
        }
    }

    ptr->field_10 = func_8003FEC0(&ptr2->field_0);
    func_8003FF2C(ptr2);

    temp = FP_MULTIPLY(func_8003F4DC(&sp60, &rot, ptr2->field_0.field_4, ptr2->field_0.field_0.s_field_0.field_2, func_80080A10(), &g_SysWork), g_SysWork.field_2378, Q12_SHIFT);

    func_800554C4(temp, ptr2->field_2C, sp60, g_SysWork.field_235C, &rot, 
                  g_SysWork.field_2360.vx, g_SysWork.field_2360.vy, g_SysWork.field_2360.vz,
                  g_WorldGfx.type_0->waterZones_8);
    func_80055814(ptr2->field_30);

    if (ptr->field_154.field_0.field_0.s_field_0.field_0 & (1 << 3))
    {
        func_8003E740();
    }
}

q19_12 func_8003F4DC(GsCOORDINATE2** arg0, SVECTOR* rot, q19_12 alpha, s32 arg3, u32 arg4, s_SysWork* sysWork) // 0x8003F4DC
{
    s32     temp;
    q19_12  alphaCpy;
    SVECTOR rot0;

    if (arg3 != 2)
    {
        arg4 = 1;
    }

    alphaCpy = alpha;
    if (arg4 == 0)
    {
        alphaCpy = Q12(0.0f);
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
            rot0 = sysWork->field_2370;
            break;

        case 0:
            rot0.vx = FP_ANGLE(0.0f);
            rot0.vy = FP_ANGLE(-90.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 2:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(195.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 3:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(-75.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 4:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(15.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 5:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(105.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;
    }

    rot->vy = -Math_Sin(rot0.vx);
    temp    = Math_Cos(rot0.vx);
    rot->vz = FP_MULTIPLY(temp, Math_Cos(rot0.vy), Q12_SHIFT);
    rot->vx = FP_MULTIPLY(temp, Math_Sin(rot0.vy), Q12_SHIFT);
    return alphaCpy;
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
        return Q12(1.0f);
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

q19_12 Math_WeightedAverageGet(s32 a, s32 b, q19_12 weight) // 0x8003F7E4
{
    return Math_MulFixed(a, Q12(1.0f) - weight, Q12_SHIFT) + Math_MulFixed(b, weight, Q12_SHIFT);
}

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight) // 0x8003F838
{
    q19_12 weight0;
    q19_12 weight1;
    q19_12 weight2;
    u32    temp;

    weight0 = weight * 2;
    weight0 = CLAMP(weight0, Q12(0.0f), Q12(1.0f));
    weight1 = (weight - Q12(0.5f)) * 2;
    weight1 = CLAMP(weight1, Q12(0.0f), Q12(1.0f));

    if (weight < Q12(0.5f))
    {
        arg0->field_0.field_0.s_field_0.field_0 = arg1->field_0.field_0.s_field_0.field_0;
    }
    else
    {
        arg0->field_0.field_0.s_field_0.field_0 = arg2->field_0.field_0.s_field_0.field_0;
    }

    func_8003FCB0(&arg0->field_0, &arg1->field_0, &arg2->field_0, weight);

    if (arg1->field_2C == Q12(0.0f))
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
        if (weight1 >= Q12(1.0f))
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
        if (weight < Q12(5.0f / 6.0f))
        {
            weight2                                 = FP_MULTIPLY(weight, Q12(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(arg1->field_0.field_4, 0, weight2);
        }
        else
        {
            weight2                                 = (weight - Q12(5.0f / 6.0f)) * 6;
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            weight0                                 = arg2->field_0.field_4;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(Q12(0.0f), weight0, weight2);
        }
    }
    else if (arg1->field_0.field_0.s_field_0.field_2 == 2 && arg2->field_0.field_0.s_field_0.field_2 == 1)
    {
        if (weight < Q12(1.0f / 6.0f))
        {
            weight2                                 = weight * 6;
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg1->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(arg1->field_0.field_4, Q12(0.0f), weight2);
        }
        else
        {
            weight2                                 = FP_MULTIPLY(weight - Q12(1.0f / 6.0f), Q12(1.2f), Q12_SHIFT);
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->field_0.field_0.s_field_0.field_2 = arg2->field_0.field_0.s_field_0.field_2;
            arg0->field_0.field_4                   = Math_WeightedAverageGet(Q12(0.0f), arg2->field_0.field_4, weight2);
        }
    }
    else
    {
        if (arg1->field_0.field_0.s_field_0.field_2 != 0 && arg2->field_0.field_0.s_field_0.field_2 == 0)
        {
            if (weight >= Q12(1.0f))
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

void func_8003FCB0(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, q19_12 alphaTo) // 0x8003FCB0
{
    q19_12 alphaFrom;
    
    alphaFrom = Q12(1.0f) - alphaTo;
    LoadAverageCol(&arg1->field_21.r, &arg2->field_21.r, alphaFrom, alphaTo, &arg0->field_21.r);
    LoadAverageCol(&arg1->field_25.r, &arg2->field_25.r, alphaFrom, alphaTo, &arg0->field_25.r);
}

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight0, q19_12 weight1, q19_12 alphaTo) // 0x8003FD38
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

    LoadAverageCol(&arg1->field_0.fogColor_14.r, &arg2->field_0.fogColor_14.r, Q12(1.0f) - alphaTo, alphaTo, &arg0->field_0.fogColor_14.r);
}

void func_8003FE04(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, q19_12 alphaTo) // 0x8003FE04
{
    q19_12 alphaFrom;

    alphaFrom = Q12(1.0f) - alphaTo;
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
    static q19_12 Y_ARRAY[5] = {
        Q12(1.75f),
        Q12(6.0f),
        Q12(9.5f),
        Q12(12.5f),
        Q12(15.0f)
    };

    if (D_800C4168.isFogEnabled_1)
    {
        return arg0->field_10;
    }

    if (D_800C4168.field_0 == 1)
    {
        return vwOresenHokan(Y_ARRAY, ARRAY_SIZE(Y_ARRAY), arg0->field_4, 0, Q12(2.0f));
    }

    return Q12(20.0f);
}

void func_8003FF2C(s_StructUnk3* arg0) // 0x8003FF2C
{
    s32   temp_a0;
    s32   temp_v1;
    q23_8 brightness;

    temp_v1    = FP_MULTIPLY(arg0->field_2E, (g_GameWork.config_0.optBrightness_22 * 8) + 4, Q12_SHIFT);
    brightness = CLAMP(temp_v1, Q8_CLAMPED(0.0f), Q8_CLAMPED(1.0f));

    func_80055330(arg0->field_0.field_0.s_field_0.field_2, arg0->field_0.field_6, arg0->field_0.field_0.s_field_0.field_1, arg0->field_0.field_8, arg0->field_0.field_A, arg0->field_0.field_C, brightness);
    Gfx_FogParamsSet(arg0->field_0.field_E != 0, arg0->field_0.fogColor_14.r, arg0->field_0.fogColor_14.g, arg0->field_0.fogColor_14.b);

    temp_a0 = arg0->field_0.field_10;

    func_80055840(temp_a0, temp_a0 + Q12(1.0f));
    func_800553E0(arg0->field_0.field_18, arg0->field_0.field_19.r, arg0->field_0.field_19.g, arg0->field_0.field_19.b, arg0->field_0.field_1D.r, arg0->field_0.field_1D.g, arg0->field_0.field_1D.b);
}

void func_80040004(s_WorldGfx* worldGfx) // 0x80040004
{
    g_WorldGfx.heldItem_1BAC.bone_18.next_14 = &worldGfx->charaModels_CC[2].skeleton_14.bones_C[16];
}

void func_80040014() // 0x80040014
{
    func_80069860(g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz, g_WorldGfx.heldItem_1BAC.bone_18.next_14);
};

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_8003AB28", D_80025BE4);
