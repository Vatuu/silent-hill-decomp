#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libgs.h>

#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

void Screen_RectInterlacedClear(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b) // 0x80032358
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(SyncMode_Wait);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(SyncMode_Wait);
}

void Screen_Refresh(s32 screenWidth, bool isInterlaced) // 0x800323C8
{
    DrawSync(SyncMode_Wait);
    Screen_RectInterlacedClear(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
    Screen_Init(screenWidth, isInterlaced);
}

void Screen_Init(s32 screenWidth, bool isInterlaced) // 0x80032428
{
    g_GameWork.gsScreenWidth_588  = screenWidth;
    g_GameWork.gsScreenHeight_58A = !isInterlaced ? FRAMEBUFFER_HEIGHT_PROGRESSIVE : FRAMEBUFFER_HEIGHT_INTERLACED;

    DrawSync(SyncMode_Wait);
    GsInitGraph2(g_GameWork.gsScreenWidth_588, g_GameWork.gsScreenHeight_58A, isInterlaced | (1 << 2), 1, 0);
    GsDefDispBuff2(0, 32, 0, isInterlaced ? 32 : 256);

    GsDISPENV.screen.h =
    GsDRAWENV.clip.h   = FRAMEBUFFER_HEIGHT_PROGRESSIVE;

    GsInit3D();
    Screen_XyPositionSet(g_GameWorkConst->config_0.optScreenPosX_1C, g_GameWorkConst->config_0.optScreenPosY_1D);
    GsSwapDispBuff();
    GsSwapDispBuff();
}

void Screen_XyPositionSet(s32 x, s32 y) // 0x800324F4
{
    Screen_DisplayEnvXySet(&GsDISPENV, x, y);
}

void Screen_DisplayEnvXySet(DISPENV* displayEnv, s32 x, s32 y) // 0x80032524
{
    #define RANGE_X 11
    #define RANGE_Y 8

    x = CLAMP(x, -RANGE_X, RANGE_X);
    y = CLAMP(y, -RANGE_Y, RANGE_Y);

    g_GameWorkConst->config_0.optScreenPosX_1C = x;
    g_GameWorkConst->config_0.optScreenPosY_1D = y;

    displayEnv->screen.x = g_GameWorkConst->config_0.optScreenPosX_1C;
    displayEnv->screen.y = g_GameWorkConst->config_0.optScreenPosY_1D + RANGE_Y;
}
