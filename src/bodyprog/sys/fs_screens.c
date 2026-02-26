#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "main/fsqueue.h"
#include "bodyprog/text/text_draw.h"

void GameFs_TitleGfxSeek(void) // 0x80032bd0
{
    Fs_QueueStartSeek(FILE_TIM_TITLE_E_TIM);
}

void GameFs_TitleGfxLoad(void) // 0x80032bf0
{
    Fs_QueueStartReadTim(FILE_TIM_TITLE_E_TIM, FS_BUFFER_3, &g_TitleImg);
}

void GameFs_StreamBinSeek(void) // 0x80032C20
{
    Fs_QueueStartSeek(FILE_VIN_STREAM_BIN);
}

void GameFs_StreamBinLoad(void) // 0x80032C40
{
    Fs_QueueStartRead(FILE_VIN_STREAM_BIN, FS_BUFFER_1);
}

void GameFs_OptionBinLoad(void) // 0x80032C68
{
    Fs_QueueStartReadTim(FILE_TIM_OPTION_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
    Fs_QueueStartRead(FILE_VIN_OPTION_BIN, FS_BUFFER_1);
}

void GameFs_SaveLoadBinLoad(void) // 0x80032CA8
{
    Fs_QueueStartReadTim(FILE_TIM_SAVELOAD_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
    Fs_QueueStartRead(FILE_VIN_SAVELOAD_BIN, FS_BUFFER_1);
}

void func_80032CE8(void) // 0x80032CE8
{
    Gfx_StringSetPosition(SCREEN_POSITION_X(33.75f), SCREEN_POSITION_Y(43.5f));
    Gfx_StringDraw("\x7Now_loading.", 100);
}
