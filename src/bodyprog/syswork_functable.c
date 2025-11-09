#include "game.h"
#include "bodyprog/bodyprog.h"

void (*g_SysStateFuncs[])(void) = {
    SysState_Gameplay_Update,
    SysState_OptionsMenu_Update,
    SysState_StatusMenu_Update,
    SysState_MapScreen_Update,
    SysState_Fmv_Update,
    SysState_LoadArea_Update,
    SysState_LoadArea_Update,
    SysState_ReadMessage_Update,
    SysState_SaveMenu_Update,
    SysState_SaveMenu_Update,
    SysState_EventCallFunc_Update,
    SysState_EventSetFlag_Update,
    SysState_EventPlaySound_Update,
    SysState_GameOver_Update,
    SysState_GamePaused_Update
};
// temporary data move to this file. After all sections are in C
// we can find a better file for them.
s32 D_800A9A68 = 0;
RECT D_800A9A6C = { 320, 256, 160, 240 };
s32 g_MainMenuState = 0;
s32 g_MainMenu_SelectedEntry = 2;
u32 g_MainMenu_VisibleEntryFlags = (1 << MainMenuEntry_Start) | (1 << MainMenuEntry_Option);
s8 g_Demo_ReproducedCount = 0;
// 3 bytes of padding.
s32 g_MainMenu_NewGameSelectedDifficultyIdx = 1;
s32 g_PrevSavegameCount = 0;

