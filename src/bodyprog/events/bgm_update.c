#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "main/fsqueue.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/sound_system.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

/** @note This file should contain up to three or two splits,
 * Those being among `Bgm_TrackUpdate`, `Savegame_MapRoomIdxUpdate`
 * and `func_800364BC`, however, bss data heavily leans that all this
 * functions belongs to one same split as `bgmLayerVolumes` (0x800BCD50)
 * and `D_800BCD58` (0x800BCD58) should be static variables nested inside
 * the functions that exclusively uses it, and then `D_800BCD5C` (0x800BCD5C) should
 * be a global variable which is used in functions related to BGM handling.
 * The situation is that `D_800BCD58` is only ever used within
 * `func_800364BC` meaning that `D_800BCD5C` is either declared in a
 * different file, or `func_800364BC` is actually part of the same split
 * which contain all "CURRENT ROOM INFO GET" and "UNKNOWN" functions
 *
 * @note OPM16 and the November 24, 98 preview builds further confirm that this
 * functions belong to a same file.
 */

extern const char D_80025234[];

// ========================================
// STATIC VARIABLES
// ========================================

static s32 D_800BCD5C;

static u32 D_800A999C = &D_80025234;
static s32 D_800A99A0 = 0;
static u8  g_Bgm_LayerLimits[8] = { 128, 128, 128, 128, 128, 128, 128, 128 };

// ========================================
// MUSIC UPDATE
// ========================================

void Bgm_TrackUpdate(bool arg0) // 0x80035DB4
{
    D_800BCD5C = false;

    if (g_MapOverlayHeader.bgmEvent_10 != NULL) // Checks if function exists.
    {
        g_MapOverlayHeader.bgmEvent_10(arg0);
        if (arg0 == false && D_800BCD5C == false)
        {
            Bgm_Update(BgmFlag_Unk0, Q12(240.0f), 0);
        }
    }
}

void Bgm_AllLayersMute(void) // 0x80035E1C
{
    s32 i;

    // Reset all BGM layer volumes.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748); i++)
    {
        g_SysWork.bgmLayerVolumes_2748[i] = Q12(0.0f);
    }
}

bool Bgm_LayerOnCheck(void) // 0x80035E44
{
    s32 i;
    u16 val;

    for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        if (g_SysWork.bgmLayerVolumes_2748[i] != Q12(0.0f))
        {
            return false;
        }
    }

    val = func_80045BC8();
    if (val == 0)
    {
        return true;
    }
    else if (val == 0xFFFF)
    {
        return false;
    }

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        if (Sd_BgmLayerVolumeGet(i) != 0)
        {
            return false;
        }
    }

    return true;
}

void Bgm_GlobalLayerVariablesUpdate(void) // 0x80035ED0
{
    s32 i;

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        g_SysWork.bgmLayerVolumes_2748[i] = Sd_BgmLayerVolumeGet(i) << 5; // Conversion to Q12.
    }

    if (func_80045BC8() == 0)
    {
        g_SysWork.bgmLayerVolumes_2748[0] = Q12(1.0f);
    }

    g_SysWork.bgmLayerVolumes_2748[ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1] = Q12(0.0f);
}

void Bgm_Update(s32 flags, q19_12 arg1, s_Bgm_Update* bgmLayerLimitPtr) // 0x80035F4C
{
    s16       temp_v0;
    s32       var_a0;
    s32       var_a2;
    q19_12    curLayerVol;
    q19_12    curLayerVol1;
    s32       temp_s2;
    s32       i;
    s32       flagsCpy;
    bool      isBgmLayerActive;
    bool      isMusicPlayer;
    q19_12    var_t0;
    bool      cond0;
    s32       endLayerIdx;
    q3_12*    bgmLayerVols;
    u8*       bgmLayerLimitCpy;
    static s8 bgmLayerVolumes[8];

    flagsCpy           = flags;
    bgmLayerLimitCpy   = bgmLayerLimitPtr;
    bgmLayerVols = g_SysWork.bgmLayerVolumes_2748;

    if (bgmLayerLimitCpy == NULL)
    {
        bgmLayerLimitCpy = g_Bgm_LayerLimits;
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) || g_SysWork.sysState_8 == SysState_GameOver)
    {
        flagsCpy &= BgmFlag_Unk8;
        flagsCpy |= BgmFlag_Unk0;
        arg1      = Q12(0.2f);
    }

    if (!(flagsCpy & BgmFlag_Unk8))
    {
        if (g_RadioPitchState > 0 && g_SavegamePtr->itemToggleFlags_AC & ItemToggleFlag_RadioOn)
        {
            g_SysWork.sysFlags_22A0 |= SysFlag_2;
        }
    }

    if (g_SysWork.sysFlags_22A0 & SysFlag_7)
    {
        flagsCpy                 = BgmFlag_Unk0 | BgmFlag_Unk9;
        g_SysWork.sysFlags_22A0 |= SysFlag_1;
    }

    if (flagsCpy & BgmFlag_Unk0)
    {
        flagsCpy &= BgmFlag_Unk8 | BgmFlag_Unk9;
    }
    else
    {
        flagsCpy ^= BgmFlag_Unk0;
    }

    for (i = 0, endLayerIdx = (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1);
         i < ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748);
         i++)
    {
        curLayerVol = bgmLayerVols[i];

        if (i == endLayerIdx)
        {
            var_t0 = Q12_MULT_FLOAT_PRECISE(g_DeltaTimeRaw, 0.25f);
            if (g_SysWork.sysFlags_22A0 & SysFlag_1)
            {
                var_a0 = Q12(1.0f);
            }
            else if (g_SysWork.sysFlags_22A0 & SysFlag_2)
            {
                var_a0 = Q12(0.75f);
            }
            else
            {
                var_a0 = (g_SysWork.sysFlags_22A0 & SysFlag_3) ? Q12(0.5f) : 0;
            }
        }
        else
        {
            if ((flagsCpy >> i) & BgmFlag_Unk0)
            {
                var_t0 = FP_MULTIPLY(g_DeltaTimeRaw, arg1, Q12_SHIFT - 1); // @hack Should be multiplied by 2 but doesn't match.
                var_a0 = Q12(1.0f);
            }
            else
            {
                var_t0 = Q12_MULT(g_DeltaTimeRaw, arg1);
                var_a0 = Q12(0.0f);
            }
        }

        var_a2 = var_a0 - curLayerVol;
        if (curLayerVol != var_a0)
        {
            if (var_t0 < var_a2)
            {
                curLayerVol += var_t0;
            }
            else if (var_a2 >= -var_t0)
            {
                curLayerVol = var_a0;
            }
            else
            {
                curLayerVol -= var_t0;
            }
        }

        bgmLayerVols[i] = curLayerVol;
    }

    isBgmLayerActive = false;
    temp_v0          = Q12(1.0f) - bgmLayerVols[8];

    for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        curLayerVol1        = bgmLayerVols[i];
        isBgmLayerActive |= curLayerVol1 != Q12(0.0f);

        if (i == 0)
        {
            curLayerVol1 = Q12_MULT_PRECISE(curLayerVol1, temp_v0);
        }

        curLayerVol1 = Q12_MULT_PRECISE(curLayerVol1, Q12(0.0312f));
        if (curLayerVol1 > Q12(0.0312f))
        {
            curLayerVol1 = Q12(0.0312f);
        }

        curLayerVol1 = (curLayerVol1 * bgmLayerLimitCpy[i]) >> 7;
        if (curLayerVol1 > Q12(0.0312f))
        {
            curLayerVol1 = Q12(0.0312f);
        }

        bgmLayerVolumes[i] = curLayerVol1;
    }

    isMusicPlayer = false;
    temp_s2        = func_80045BC8();

    cond0 = temp_s2;
    cond0 = temp_s2 != 0 && cond0 != 0xFFFF;

    if (isBgmLayerActive)
    {
        switch (D_800A99A0)
        {
            case 3:
                Bgm_AllLayersMute();

                if (cond0)
                {
                    D_800A99A0 = 0;
                }
                else
                {
                    Bgm_BgmChannelSet();
                    D_800A99A0 = 2;
                }
                break;

            case 2:
                Bgm_AllLayersMute();
                D_800A99A0 = 1;
                break;

            case 1:
                if (cond0)
                {
                    Bgm_GlobalLayerVariablesUpdate();
                }
                else
                {
                    Bgm_AllLayersMute();
                }

                D_800A99A0 = 0;
                break;

            case 0:
                isMusicPlayer = true;
                break;
        }
    }
    else if (flagsCpy & BgmFlag_Unk9)
    {
        if (D_800A99A0 != 3)
        {
            D_800A99A0 = 3;
            SD_Call(18);
        }
    }
    else if (D_800A99A0 == 0)
    {
        isMusicPlayer = true;
    }

    if (isMusicPlayer)
    {
        if (cond0)
        {
            for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
            {
                Sd_BgmLayerVolumeSet(i, bgmLayerVolumes[i]);
            }
        }
        else
        {
            Bgm_AllLayersMute();
            D_800A99A0 = 3;
        }
    }

    D_800BCD5C = true;
}

void func_800363D0(void) // 0x800363D0
{
    g_RadioPitchState        = 0;
    g_SysWork.sysFlags_22A0 |= SysFlag_3;
    Bgm_TrackUpdate(false);
}

void Bgm_TrackChange(s32 idx) // 0x8003640C
{
    if (idx != 0)
    {
        g_MapOverlayHeader.bgmIdx_14 = idx;
    }
}

// ========================================
// CURRENT ROOM INFO GET
// ========================================

void Savegame_MapRoomIdxUpdate(void) // 0x80036420
{
    s32 x;
    s32 z;
    s8  newMapRoomIdx;

    x = g_SysWork.playerWork_4C.player_0.position_18.vx;
    z = g_SysWork.playerWork_4C.player_0.position_18.vz;

    // Set map room index based on current player position.
    if (g_MapOverlayHeader.getMapRoomIdxFunc_4 == NULL)
    {
        newMapRoomIdx = 0;
    }
    else
    {
        newMapRoomIdx = g_MapOverlayHeader.getMapRoomIdxFunc_4(x, z);
    }
    g_SavegamePtr->mapRoomIdx_A5 = newMapRoomIdx;
}

s32 func_8003647C(void) // 0x8003647C
{
    return g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8;
}

s32 func_80036498(void) // 80036498
{
    return !(g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8);
}

// ========================================
// UNKNOWN
// ========================================

u32 func_800364BC(void) // 0x800364BC
{
    u32        var0;
    u32        var1;
    static u32 D_800BCD58;

    D_800BCD58 += g_DeltaTimeRaw * (Q12(64.0f) + 1);

    var0  = Q12(64.0f);
    var0 += Math_Sin(D_800BCD58 >> 18) * 8;
    var1  = Math_Sin((D_800BCD58 & 0xFFFF) / 16) * 32;
    return FP_FROM(var0 + var1, Q12_SHIFT);
}

// `RECT`s?
const char D_80025234[] = { 0, 177, 58, 204, 0 }; // Could this indicate file split nearby?

void func_8003652C(void) // 0x8003652C
{
    RECT rect;

    u32 VALS[] = {
        0xFFFF0000, 0xBBEEE318, 0xFFEC9304, 0x83FFE30C,
        0x1F8318,   0x90840018, 0x90808080, 0x80048084
    };

    rect.x = 304;
    rect.y = 510;
    rect.w = 16;
    rect.h = 1;

    LoadImage(&rect, VALS);
}

const s32 pad_rodata_8002525C = 0;