#include "bodyprog/bodyprog.h"

/** @brief Relative paper map TIM file indices. */
s8 g_PaperMapFileIdxs[24] = {
    0, 0, 1, 1, 9, 12, 10, 11,
    13, 12, 10, 11, 13, 2, 3, 4,
    8, 5, 6, 7, 8, 5, 6, 7
};

/** @brief Relative paper map marking TIM file indices. */
s8 g_PaperMapMarkingFileIdxs[56] = {
    255, 0, 1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 104, 83, 2, 128,
    92, 83, 2, 128, 80, 83, 2, 128,
    68, 83, 2, 128, 56, 83, 2, 128,
    44, 83, 2, 128, 32, 83, 2, 128
};

/** @note Related to images display. */
s_FsImageDesc D_800A9A04 = { .tPage = { 1, 21 }, .clutX = 224, .clutY = 13 };

s32 D_800A9A0C = 0;

s32 g_MapEventSysState = SysState_Gameplay;

u32 g_MapEventIdx = 0;

s32 g_MapEventLastUsedItem = 0;

s32 g_RadioPitchState = 0;

