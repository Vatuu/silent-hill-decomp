#include "game.h"

s_GameWork* const       g_GameWorkConst = &g_GameWork;
s_Savegame* const       g_SavegamePtr   = &g_GameWork.savegame_30C;
s_ControllerData* const g_Controller0   = &g_GameWork.controllers_38[0];
s_ControllerData* const g_Controller1   = &g_GameWork.controllers_38[1];
s_GameWork* const       g_GameWorkPtr   = &g_GameWork;

// TODO: Bunch of .rodata related to stage/map data?
u32 D_80024D58 = 0;
u32 D_80024D5C[] = 
{
    /* 1FC 80024D5C 01000800 */ 0x00080001,
    /* 200 80024D60 80F80005 */ 0x0500F880,
    /* 204 80024D64 80F88002 */ 0x0280F880,
    /* 208 80024D68 01000800 */ 0x00080001,
    /* 20C 80024D6C 00008002 */ 0x02800000,
    /* 210 80024D70 00000005 */ 0x05000000,
    /* 214 80024D74 00000000 */ 0x00000000,
    /* 218 80024D78 00000000 */ 0x00000000,
    /* 21C 80024D7C 00000000 */ 0x00000000,
};
