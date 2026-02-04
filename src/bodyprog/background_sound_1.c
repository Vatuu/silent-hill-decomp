#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/credits.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// AUDIO HANDLING
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

s32 Sd_IsCurrentAmbientTargetCheck(s32 ambIdx) // 0x80035AB0
{
    return g_GameWork.ambientIdx_5B4 != ambIdx;
}

void Sd_AmbientSfxSet(s32 idx) // 0x80035AC8
{
    g_GameWork.ambientIdx_5B4 = idx;
    SD_Call(g_AmbientVabTaskLoadCmds[idx]);
}
