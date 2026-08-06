#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/game_boot/game_boot.h"
#include "bodyprog/sound/sound_system.h"

// ========================================
// STATIC VARIABLES
// ========================================

/** @brief Task commands for `SD_Call` to load BGM KDT and VAB files. */
static u16 g_BgmTaskLoadCmds[42] = {
    0,  0,  32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 64, 65, 66, 67, 68, 69, 45, 70,
    71, 63
};

/** @brief Task commands for `SD_Call` to set current BGM channels to be used. */
static u16 g_BgmChannelSetTaskCmds[42] = {
    0, 0,
    SD_TASK_CHANNELSET(1),  SD_TASK_CHANNELSET(2),  SD_TASK_CHANNELSET(3),
    SD_TASK_CHANNELSET(4),  SD_TASK_CHANNELSET(5),  SD_TASK_CHANNELSET(6),
    SD_TASK_CHANNELSET(7),  SD_TASK_CHANNELSET(8),  SD_TASK_CHANNELSET(9),
    SD_TASK_CHANNELSET(10), SD_TASK_CHANNELSET(11), SD_TASK_CHANNELSET(12),
    SD_TASK_CHANNELSET(13), SD_TASK_CHANNELSET(15), SD_TASK_CHANNELSET(16),
    SD_TASK_CHANNELSET(17), SD_TASK_CHANNELSET(18), SD_TASK_CHANNELSET(19),
    SD_TASK_CHANNELSET(20), SD_TASK_CHANNELSET(21), SD_TASK_CHANNELSET(22),
    SD_TASK_CHANNELSET(23), SD_TASK_CHANNELSET(24), SD_TASK_CHANNELSET(25),
    SD_TASK_CHANNELSET(26), SD_TASK_CHANNELSET(27), SD_TASK_CHANNELSET(28),
    SD_TASK_CHANNELSET(29), SD_TASK_CHANNELSET(30), SD_TASK_CHANNELSET(31),
    SD_TASK_CHANNELSET(33), SD_TASK_CHANNELSET(34), SD_TASK_CHANNELSET(35),
    SD_TASK_CHANNELSET(36), SD_TASK_CHANNELSET(37), SD_TASK_CHANNELSET(38),
    SD_TASK_CHANNELSET(14), SD_TASK_CHANNELSET(39), SD_TASK_CHANNELSET(40),
    SD_TASK_CHANNELSET(32)
};

/** @brief Task commands for `SD_Call` to load ambient VAB files. */
static u16 g_AmbientVabTaskLoadCmds[40] = {
    0,   162, 170, 171, 204, 172, 173, 174,
    175, 176, 177, 178, 179, 179, 179, 180,
    181, 182, 183, 184, 185, 186, 187, 188,
    189, 184, 190, 191, 192, 193, 194, 195,
    196, 197, 198, 199, 200, 201, 202, 203
};

// ========================================
// MUSIC INIT AND SET
// ========================================

bool Bgm_Init(void) // 0x80035780
{
    if (Sd_AudioStreamingCheck() != AudioStreamingState_None)
    {
        return NO_VALUE;
    }

    if (Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    // Handle background music initialization step.
    switch (g_GameWork.gameStateSteps[1])
    {
        case 0:
            Bgm_UpdateTrack();
            g_GameWork.gameStateSteps[1]++;

        case 1:
            if (Bgm_ActiveTrackCheck(g_MapOverlayHdr.bgmCmd) == false)
            {
                g_GameWork.gameStateSteps[1] += 2;
            }
            else
            {
                SD_Call(18);
                Bgm_AllLayersMute();

                g_GameWork.gameStateSteps[1]++;
            }
            break;

        case 2:
            // Checks if no BGM channel is being used.
            if (func_80045BC8() == 0)
            {
                Bgm_TrackSet(g_MapOverlayHdr.bgmCmd);
                g_GameWork.gameStateSteps[1]++;
            }
            break;

        default:
            return false;
    }

    return true;
}

bool Bgm_ActiveTrackCheck(s32 bgmIdx) // 0x800358A8
{
    if (bgmIdx == BgmCmd_UpdateLayers)
    {
        return false;
    }

    if (bgmIdx == BgmCmd_UpdateTrack)
    {
        return false;
    }

    return g_GameWork.bgmIdx != bgmIdx;
}

void Bgm_TrackSet(s32 bgmIdx) // 0x800358DC
{
    if (bgmIdx == BgmCmd_UpdateLayers)
    {
        return;
    }

    if (bgmIdx == BgmCmd_UpdateTrack)
    {
        return;
    }

    g_GameWork.bgmIdx = bgmIdx;
    SD_Call(g_BgmTaskLoadCmds[bgmIdx]);
}

void Bgm_ChannelSet(void) // 0x80035924
{
    if (g_GameWork.bgmIdx == BgmCmd_UpdateLayers)
    {
        return;
    }

    if (g_GameWork.bgmIdx == BgmCmd_UpdateTrack)
    {
        return;
    }

    SD_Call(g_BgmChannelSetTaskCmds[g_GameWork.bgmIdx]);
}

void Bgm_UpdateTrack(void)
{
    if (g_MapOverlayHdr.bgmCmd == BgmCmd_UpdateTrack)
    {
        Bgm_Update(true);
    }
}

// ========================================
// AMBIENT SOUND INIT & SET
// ========================================

bool Sd_AmbientSfxInit(void) // 0x8003599C
{
    if (Sd_AudioStreamingCheck() != AudioStreamingState_None || Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateSteps[1])
    {
        case 0:
            if (g_SavegamePtr->mapIdx == MapIdx_MAP2_S00)
            {
                if (Savegame_EventFlagGet(EventFlag_133) || Savegame_EventFlagGet(EventFlag_181))
                {
                    g_MapOverlayHdr.ambientAudioIdx = 11;
                }
                else
                {
                    g_MapOverlayHdr.ambientAudioIdx = 4;
                }
            }

            if (Sd_ActiveAmbientCheck((s8)g_MapOverlayHdr.ambientAudioIdx) != false)
            {
                SD_Call(17);
                g_GameWork.gameStateSteps[1]++;
                return true;
            }
            break;

        case 1:
            Sd_AmbientSfxSet((s8)g_MapOverlayHdr.ambientAudioIdx);
            g_GameWork.gameStateSteps[1]++;
            return true;

        default:
           break;
    }

    return false;
}

bool Sd_ActiveAmbientCheck(s32 ambientIdx) // 0x80035AB0
{
    return g_GameWork.ambientIdx != ambientIdx;
}

void Sd_AmbientSfxSet(s32 idx) // 0x80035AC8
{
    g_GameWork.ambientIdx = idx;
    SD_Call(g_AmbientVabTaskLoadCmds[idx]);
}
