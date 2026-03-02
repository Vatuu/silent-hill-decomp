#include "bodyprog/bodyprog.h"

/** @brief Relative paper map TIM file indices. */
s8 g_PaperMapFileIdxs[] = {
    0, 0, 1, 1, 9, 12, 10, 11,
    13, 12, 10, 11, 13, 2, 3, 4,
    8, 5, 6, 7, 8, 5, 6, 7
};

/** @brief Relative paper map marking TIM file indices. */
s8 g_PaperMapMarkingFileIdxs[] = {
    255, 0, 1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3
};

s_800A99E4 D_800A99E4 = {
    0,           &D_80025368, &D_8002535C, &D_80025350,
    &D_80025344, &D_80025338, &D_8002532C, &D_80025320
};

/** @note Related to images display. */
s_FsImageDesc D_800A9A04 = { .tPage = { 1, 21 }, .clutX = 224, .clutY = 13 };

s32 D_800A9A0C = 0;

s32 g_MapEventSysState = SysState_Gameplay;

u32 g_MapEventParam = 0;

s32 g_MapEventLastUsedItem = 0;

s32 g_RadioPitchState = 0;

