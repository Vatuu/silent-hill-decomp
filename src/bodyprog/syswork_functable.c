#include "game.h"
#include "bodyprog/bodyprog.h"

void (*g_SysStateFuncTable[])() = {
    SysState_Gameplay_Update,
    SysState_OptionsMenu_Update,
    SysState_StatusMenu_Update,
    SysState_Unk3_Update,
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
    SysState_GamePaused_Update,
};

