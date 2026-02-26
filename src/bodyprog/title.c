#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

static s32 g_MainMenuState = 0;

static s32 g_MainMenu_SelectedEntry = MainMenuEntry_Start;

static u32 g_MainMenu_VisibleEntryFlags = (1 << MainMenuEntry_Start) | (1 << MainMenuEntry_Option);

s8 g_Demo_ReproducedCount = 0;

// ========================================
// MAIN MENU
// ========================================

s8* D_800BCDE0;

#define MAIN_MENU_OPTION_COUNT 5
#define MAIN_MENU_FOG_COUNT    21

static const s32 rodataPad_8002547C = 0;

void GameState_MainMenu_Update(void) // 0x8003AB28
{
    #define MAIN_MENU_GAME_STATE_COUNT 5

    s32 NEXT_GAME_STATES[MAIN_MENU_GAME_STATE_COUNT] =
    {
        GameState_LoadSavegameScreen,
        GameState_AutoLoadSavegame,
        GameState_MovieOpening,
        GameState_OptionScreen,
        GameState_MovieIntro
    };

    bool        playInGameDemo;
    s32         prevGameDifficultyIdx;
    s32         nextGameDifficultyIdx;
    e_GameState prevState;
    static s32  newGameSelectedDifficultyIdx = 1;
    static s32  prevSavegameCount            = 0;

    func_80033548();

    // After staying idle in the title screen for some time, this checks if the intro FMV or a
    // demo gameplay segment should be played. If the next value from `g_Demo_ReproducedCount`
    // is a value divisible by 3, the intro FMV will play. Otherwise, it defaults to a gameplay demo.
    playInGameDemo = ((g_Demo_ReproducedCount + 1) % 3) != 0;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_MainMenuState = 0;

        if (playInGameDemo)
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
            g_GameWork.background2dColor_58C.r = 0;
            g_GameWork.background2dColor_58C.g = 0;
            g_GameWork.background2dColor_58C.b = 0;

            Screen_RectInterlacedClear(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks    = 1;
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep = Q12(2.0f);
            g_MainMenuState++;

        case MenuState_Main:
            if (playInGameDemo)
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
            if (g_MemCard_SavegameCount > 0)
            {
                g_MainMenu_VisibleEntryFlags |= (1 << MainMenuEntry_Load) | (1 << MainMenuEntry_Continue);

                if (prevSavegameCount < g_MemCard_SavegameCount && g_MainMenu_SelectedEntry != MainMenuEntry_Load)
                {
                    g_MainMenu_SelectedEntry = MainMenuEntry_Continue;
                }
            }
            // No savegames exist, but did previously (e.g. memory card removed before player death).
            else if (prevSavegameCount > 0)
            {
                while(!(g_MainMenu_VisibleEntryFlags & (1 << g_MainMenu_SelectedEntry)))
                {
                    g_MainMenu_SelectedEntry++;
                }
            }

            g_MainMenu_VisibleEntryFlags |= g_MainMenu_VisibleEntryFlags << MAIN_MENU_OPTION_COUNT;

            if (g_Controller0->btnsPulsed_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                SD_Call(Sfx_MenuMove);
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
                while(!(g_MainMenu_VisibleEntryFlags & (1 << --g_MainMenu_SelectedEntry)));
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                while(!(g_MainMenu_VisibleEntryFlags & (1 << ++g_MainMenu_SelectedEntry)));
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
                    SD_Call(Sfx_MenuStartGame);
                }
                else
                {
                    SD_Call(Sfx_MenuConfirm);
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
                        g_MainMenuState = MenuState_DifficultySelector;
                        break;

                    case MainMenuEntry_Option:
                        GameFs_OptionBinLoad();
                        break;

                    case MainMenuEntry_Extra: // @unused See `e_MainMenuEntry`.
                        break;
                }
            }

            prevSavegameCount = g_MemCard_SavegameCount;

        default:
            break;

        case MenuState_DifficultySelector:
            if (playInGameDemo)
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
                if (newGameSelectedDifficultyIdx > 0)
                {
                    prevGameDifficultyIdx = newGameSelectedDifficultyIdx - 1;
                }
                newGameSelectedDifficultyIdx = prevGameDifficultyIdx;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                nextGameDifficultyIdx = 0;
                if (newGameSelectedDifficultyIdx < 2)
                {
                    nextGameDifficultyIdx = newGameSelectedDifficultyIdx + 1;
                }
                newGameSelectedDifficultyIdx = nextGameDifficultyIdx;
            }

            // Play scroll sound.
            if (g_Controller0->btnsPulsed_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                SD_Call(Sfx_MenuMove);
            }

            // Select game difficulty.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Game_SavegameInitialize(0, newGameSelectedDifficultyIdx - 1);
                Game_PlayerInit();

                g_SysWork.processFlags_2298 = SysWorkProcessFlag_NewGame;

                GameFs_MapLoad(MapOverlayId_MAP0_S00);
                GameFs_StreamBinLoad();
                SD_Call(Sfx_MenuStartGame);

                ScreenFade_Start(true, false, false);
                g_MainMenuState     = 4;
            }
            // Cancel.
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SD_Call(Sfx_MenuCancel);
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
                    NEXT_GAME_STATES[1] = GameState_MainLoadScreen;
                }

                if (g_MainMenu_SelectedEntry == MainMenuEntry_Start)
                {
                    Chara_PositionSet(&g_MapOverlayHeader.mapPointsOfInterest_1C[0]);
                }

                MemCard_Disable();

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

    if (!playInGameDemo)
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

                    g_GameWork.background2dColor_58C.r = 0;
                    g_GameWork.background2dColor_58C.g = 0;
                    g_GameWork.background2dColor_58C.b = 0;

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

        Gfx_MainMenu_DifficultyTextDraw(newGameSelectedDifficultyIdx);
        return;
    }
    else
    {
        *(s32*)0x1F800000 = 0x200000;
        *(s32*)0x1F800004 = 0x01C00140;
        ClearImage2((RECT*)0x1F800000, 0u, 0u, 0u);
        Screen_Init(SCREEN_WIDTH, false);
        return;
    }

    #undef MAIN_MENU_GAME_STATE_COUNT
}

void MainMenu_SelectedOptionIdxReset(void) // 0x8003B550
{
    g_MainMenu_SelectedEntry = MainMenuEntry_Continue;
}

void func_8003B560(void) {} // 0x8003B560

void Gfx_MainMenu_MainTextDraw(void) // 0x8003B568
{
    #define COLUMN_POS_X 158
    #define COLUMN_POS_Y 184
    #define STR_OFFSET_Y 20

    static const char* MAIN_MENU_ENTRY_STRINGS[] = {
        "LOAD",
        "CONTINUE",
        "START",
        "OPTION",
        "EXTRA" /** @unused See `e_MainMenuEntry`. */
    };
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

void Gfx_MainMenu_DifficultyTextDraw(s32 idx) // 0x8003B678
{
    #define DIFFICULTY_MENU_SELECTION_COUNT 3
    #define COLUMN_POS_X                    158
    #define COLUMN_POS_Y                    204
    #define STR_OFFSET_Y                    20

    static const char* DIFFICULTY_MENU_ENTRY_STRINGS[] = {
        "EASY",
        "NORMAL",
        "HARD"
    };
    static const u8 STR_OFFSETS_X[] = { 28, 43, 30 };

    s32 i;

    // Draw selection strings.
    for (i = 0; i < DIFFICULTY_MENU_SELECTION_COUNT; i++)
    {
        Gfx_StringSetPosition(COLUMN_POS_X - STR_OFFSETS_X[i], COLUMN_POS_Y + (i * STR_OFFSET_Y));
        Gfx_StringSetColor(StringColorId_White);

        if (i == idx)
        {
            Gfx_StringDraw("[", DEFAULT_MAP_MESSAGE_LENGTH);
        }
        else
        {
            Gfx_StringDraw("_", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw(DIFFICULTY_MENU_ENTRY_STRINGS[i], DEFAULT_MAP_MESSAGE_LENGTH);

        if (i == idx)
        {
            Gfx_StringDraw("]", DEFAULT_MAP_MESSAGE_LENGTH);
        }

        Gfx_StringDraw("\n", DEFAULT_MAP_MESSAGE_LENGTH);
    }
}

void Gfx_MainMenu_BackgroundDraw(void) // 0x8003B758
{
    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
        func_8003BCF4();
    }

    Gfx_BackgroundSpriteDraw(&g_TitleImg);
    Gfx_MainMenu_FogUpdate();
}

void func_8003B7BC(void) // 0x8003B7BC
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

void Gfx_MainMenu_FogDraw(void) // 0x8003BA08
{
    PACKET*   packet;
    GsOT_TAG* tag;

    tag    = g_OrderingTable2[g_ActiveBufferIdx].org;
    packet = Gfx_MainMenu_FogPacketGet(&tag[6], GsOUT_PACKET_P);
    SetDrawMode((DR_MODE*)packet, 0, 1, 42, NULL);
    addPrim(&tag[6], packet);
    GsOUT_PACKET_P = packet + sizeof(DR_MODE);
}

void Gfx_MainMenu_FogRandomize(void) // 0x8003BAC4
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
    RAND += Rng_GenerateInt(4, 11u);
    val   = Q12_MULT(Math_Sin(RAND), 10) - 122;
    ptr2  = ptr + 461;

    for (i = 20; i >= 0; i--)
    {
        *ptr2-- = val;
    }

    for (i = 0; i < 16; i++)
    {
        idx       = Rng_GenerateInt(0, MAIN_MENU_FOG_COUNT - 1);
        ptr1[idx] = NO_VALUE;
    }

    for (i = 0; i < 9; i++)
    {
        idx       = Rng_GenerateInt(0, MAIN_MENU_FOG_COUNT - 1);
        ptr1[idx] = 0;
    }
}

void Gfx_MainMenu_FogScatter(void) // 0x8003BBF4
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

void Gfx_MainMenu_FogUpdate(void) // 0x8003BC8C
{
    static s32 fogCount = 0;

    if (fogCount == ((fogCount / 5) * 5))
    {
        Gfx_MainMenu_FogScatter();
    }

    fogCount++;
    Gfx_MainMenu_FogDraw();
}

void func_8003BCF4(void) // 0x8003BCF4
{
    s32 i;

    func_8003B7BC();

    for (i = 0; i < 30; i++)
    {
        Gfx_MainMenu_FogScatter();
    }
}

static const s8  pad_rodata_8002551F = 0x4C;
static const s32 pad_rodata_80025520 = 0x90AB9500;

#undef MAIN_MENU_OPTION_COUNT
#undef MAIN_MENU_FOG_COUNT
