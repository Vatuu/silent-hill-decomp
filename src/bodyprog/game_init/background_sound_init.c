#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

/** @brief Task commands for `SD_Call` to load BGM KDT and VAB files. */
u16 g_BgmTaskLoadCmds[] = {
    0,
    0,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    64,
    65,
    66,
    67,
    68,
    69,
    45,
    70,
    71,
    63
};

/** @brief Task commands for `SD_Call` to set current BGM channels to be used. */
u16 g_BgmChannelSetTaskCmds[] = {
    0,
    0,
    769,
    770,
    771,
    772,
    773,
    774,
    775,
    776,
    777,
    778,
    779,
    780,
    781,
    783,
    784,
    785,
    786,
    787,
    788,
    789,
    790,
    791,
    792,
    793,
    794,
    795,
    796,
    797,
    798,
    799,
    801,
    802,
    803,
    804,
    805,
    806,
    782,
    807,
    808,
    800
};

/** @brief Task commands for `SD_Call` to load ambient VAB files. */
u16 g_AmbientVabTaskLoadCmds[] = {
    0,
    162,
    170,
    171,
    204,
    172,
    173,
    174,
    175,
    176,
    177,
    178,
    179,
    179,
    179,
    180,
    181,
    182,
    183,
    184,
    185,
    186,
    187,
    188,
    189,
    184,
    190,
    191,
    192,
    193,
    194,
    195,
    196,
    197,
    198,
    199,
    200,
    201,
    202,
    203
};

// ========================================
// BACKGROUND MUSIC INIT & SET
// ========================================

s32 Bgm_Init(void) // 0x80035780
{
    if (Sd_AudioStreamingCheck())
    {
        return NO_VALUE;
    }

    if (Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            func_8003596C();
            g_GameWork.gameStateStep_598[1]++;

        case 1:
            if (Bgm_IsCurrentBgmTargetCheck(g_MapOverlayHeader.bgmIdx_14) == false)
            {
                g_GameWork.gameStateStep_598[1] += 2;
            }
            else
            {
                SD_Call(18);
                Bgm_AllLayersMute();

                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case 2:
            if (func_80045BC8() == 0)
            {
                Bgm_TrackSet(g_MapOverlayHeader.bgmIdx_14);
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        default:
            return 0;
    }

    return 1;
}

bool Bgm_IsCurrentBgmTargetCheck(s32 bgmIdx) // 0x800358A8
{
    if (bgmIdx == 0)
    {
        return false;
    }

    if (bgmIdx == 1)
    {
        return false;
    }

    return g_GameWork.bgmIdx_5B2 != bgmIdx;
}

void Bgm_TrackSet(s32 bgmIdx) // 0x800358DC
{
    if (bgmIdx == 0)
    {
        return;
    }

    if (bgmIdx == 1)
    {
        return;
    }

    g_GameWork.bgmIdx_5B2 = bgmIdx;
    SD_Call(g_BgmTaskLoadCmds[bgmIdx]);
}

void Bgm_BgmChannelSet(void) // 0x80035924
{
    if (g_GameWork.bgmIdx_5B2 == 0)
    {
        return;
    }

    if (g_GameWork.bgmIdx_5B2 == 1)
    {
        return;
    }

    SD_Call(g_BgmChannelSetTaskCmds[g_GameWork.bgmIdx_5B2]);
}

void func_8003596C(void) // 0x8003596C
{
    if (g_MapOverlayHeader.bgmIdx_14 == 1)
    {
        Bgm_TrackUpdate(true);
    }
}

// ========================================
// AMBIENT SOUND INIT & SET
// ========================================

s32 Sd_AmbientSfxInit(void) // 0x8003599C
{
    if (Sd_AudioStreamingCheck() || Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S00)
            {
                if (Savegame_EventFlagGet(EventFlag_133) || Savegame_EventFlagGet(EventFlag_181))
                {
                    g_MapOverlayHeader.ambientAudioIdx_15 = 11;
                }
                else
                {
                    g_MapOverlayHeader.ambientAudioIdx_15 = 4;
                }
            }

            if (Sd_IsCurrentAmbientTargetCheck((s8)g_MapOverlayHeader.ambientAudioIdx_15) != false)
            {
                SD_Call(17);
                g_GameWork.gameStateStep_598[1]++;
                return 1;
            }
            break;

        case 1:
            Sd_AmbientSfxSet((s8)g_MapOverlayHeader.ambientAudioIdx_15);
            g_GameWork.gameStateStep_598[1]++;
            return 1;

        default:
           break;
    }

    return 0;
}

bool Sd_IsCurrentAmbientTargetCheck(s32 ambIdx) // 0x80035AB0
{
    return g_GameWork.ambientIdx_5B4 != ambIdx;
}

void Sd_AmbientSfxSet(s32 idx) // 0x80035AC8
{
    g_GameWork.ambientIdx_5B4 = idx;
    SD_Call(g_AmbientVabTaskLoadCmds[idx]);
}
