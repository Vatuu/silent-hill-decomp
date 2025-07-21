#include "game.h"

s_GameWork* const       g_GameWorkConst      = &g_GameWork;
s_ShSavegame* const     g_SavegamePtr        = &g_GameWork.savegame_30C;
s_ControllerData* const g_ControllerPtrConst = &g_GameWork.controllers_38[0];
s_ControllerData* const g_ControllerPtr      = &g_GameWork.controllers_38[1];
s_GameWork* const       g_GameWorkPtr        = &g_GameWork;

// TODO: bunch of .rodata related to stage/map data?
