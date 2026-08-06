#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/bgm.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "bodyprog/text/text_draw.h"
#include "main/fsqueue.h"

extern const s8 D_80025234[];

// ========================================
// GLOBAL VARIABLES
// ========================================

u32 D_800A999C = &D_80025234;

// ========================================
// STATIC VARIABLES
// ========================================

static s32 g_Bgm_LayersUpdated;
static s32 g_Bgm_ChannelSetProcessState = 0;
static u8  g_Bgm_LayerLimits[8] = { 128, 128, 128, 128, 128, 128, 128, 128 };

// ========================================
// MUSIC UPDATE
// ========================================

void Bgm_Update(bool updateTrack) // 0x80035DB4
{
    g_Bgm_LayersUpdated = false;

    if (g_MapOverlayHdr.bgmEvent != NULL) // Checks if function exists.
    {
        g_MapOverlayHdr.bgmEvent(updateTrack);
        if (updateTrack == false && g_Bgm_LayersUpdated == false)
        {
            Bgm_LayersUpdate(BgmFlag_Layer1, Q12(240.0f), 0);
        }
    }
}

void Bgm_AllLayersMute(void) // 0x80035E1C
{
    s32 i;

    // Reset all BGM layer volumes.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.bgmLayerVolumes); i++)
    {
        g_SysWork.bgmLayerVolumes[i] = Q12(0.0f);
    }
}

bool Bgm_LayerOnCheck(void) // 0x80035E44
{
    s32 i;
    u16 val;

    for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1); i++)
    {
        if (g_SysWork.bgmLayerVolumes[i] != Q12(0.0f))
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

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1); i++)
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

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1); i++)
    {
        g_SysWork.bgmLayerVolumes[i] = Sd_BgmLayerVolumeGet(i) << 5; // Conversion to Q12.
    }

    if (func_80045BC8() == 0)
    {
        g_SysWork.bgmLayerVolumes[0] = Q12(1.0f);
    }

    g_SysWork.bgmLayerVolumes[ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1] = Q12(0.0f);
}

void Bgm_LayersUpdate(s32 bgmFlags, q19_12 fadeSpeed, s_BgmLayerLimits* layerLimits) // 0x80035F4C
{
    s16       temp_v0;
    s32       ducking;
    s32       targetVol;
    q19_12    curLayerVol;
    q19_12    curLayerVol1;
    s32       activeSetChannelTask;
    s32       i;
    s32       flagsCpy;
    bool      isBgmLayerActive;
    bool      isMusicPlaying;
    q19_12    adjustLayerValue;
    bool      areChannelsActive;
    s32       lastLayerIdx;
    q3_12*    layersVol;
    u8*       layerLimitsCpy;
    static s8 bgmChannelsVol[8];

    // Setup.
    flagsCpy       = bgmFlags;
    layerLimitsCpy = layerLimits;
    layersVol      = g_SysWork.bgmLayerVolumes;

    // Ensure layer limits are valid.
    if (layerLimitsCpy == NULL)
    {
        layerLimitsCpy = g_Bgm_LayerLimits;
    }

    // Continue music at reduced volume if player is dead.
    if (g_SysWork.playerWork.player.health <= Q12(0.0f) || g_SysWork.sysState == SysState_GameOver)
    {
        flagsCpy &= BgmFlag_KeepAlive;
        flagsCpy |= BgmFlag_Layer1;
        fadeSpeed = Q12(0.2f);
    }

    // If player is not dead and the radio is active this set the
    // BGM status flag for radio active.
    if (!(flagsCpy & BgmFlag_KeepAlive) && g_RadioPitchState > 0 &&
        (g_SavegamePtr->itemToggleFlags & ItemToggleFlag_RadioOn))
    {
        g_SysWork.bgmStatusFlags |= BgmStatusFlag_RadioActive;
    }

    // Mute layers.
    if (g_SysWork.bgmStatusFlags & BgmStatusFlag_RequestMute)
    {
        flagsCpy                  = BgmFlag_Layer1 | BgmFlag_MuteAll;
        g_SysWork.bgmStatusFlags |= BgmStatusFlag_ApplyMute;
    }

    if (flagsCpy & BgmFlag_Layer1)
    {
        flagsCpy &= BgmFlag_KeepAlive | BgmFlag_MuteAll;
    }
    else
    {
        flagsCpy ^= BgmFlag_Layer1;
    }

    // Updates music layers volume.
    for (i = 0, lastLayerIdx = (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1);
         i < ARRAY_SIZE(g_SysWork.bgmLayerVolumes);
         i++)
    {
        curLayerVol = layersVol[i];

        if (i == lastLayerIdx)
        {
            adjustLayerValue = Q12_MULT_FLOAT_PRECISE(g_DeltaTimeRaw, 0.25f);
            if (g_SysWork.bgmStatusFlags & BgmStatusFlag_ApplyMute)
            {
                ducking = Q12(1.0f);
            }
            else if (g_SysWork.bgmStatusFlags & BgmStatusFlag_RadioActive)
            {
                ducking = Q12(0.75f);
            }
            else
            {
                ducking = (g_SysWork.bgmStatusFlags & BgmStatusFlag_Duck) ? Q12(0.5f) : Q12(0.0f);
            }
        }
        else
        {
            if ((flagsCpy >> i) & 1) // Turn on music layer.
            {
                adjustLayerValue = FP_MULTIPLY(g_DeltaTimeRaw, fadeSpeed, Q12_SHIFT - 1); // @hack Should be multiplied by 2 but doesn't match.
                ducking          = Q12(1.0f);
            }
            else // Turn off music larper.
            {
                adjustLayerValue = Q12_MULT(g_DeltaTimeRaw, fadeSpeed);
                ducking          = Q12(0.0f);
            }
        }

        targetVol = ducking - curLayerVol;
        if (curLayerVol != ducking)
        {
            if (adjustLayerValue < targetVol)
            {
                curLayerVol += adjustLayerValue;
            }
            else if (targetVol >= -adjustLayerValue)
            {
                curLayerVol = ducking;
            }
            else
            {
                curLayerVol -= adjustLayerValue;
            }
        }

        layersVol[i] = curLayerVol;
    }

    isBgmLayerActive = false;
    temp_v0          = Q12(1.0f) - layersVol[8];
    
    /* @todo Figure out this weird FP math.
       @note This extremely small values are likely related to delta timer as `layersVol[8]` is set
       by doing some stuff with the delta timer and as the previous variable shows it is used to
       define a variable which is used for adjusting the first channel volume on certain circumstances
       (for example during the inventory).
    */
    // Updates console's music channel volume.
    for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1); i++)
    {
        curLayerVol1      = layersVol[i];
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

        curLayerVol1 = (curLayerVol1 * layerLimitsCpy[i]) >> 7; // This is the equivalent of `/ Q12(0.0312f)` but causes missmatch.
        if (curLayerVol1 > Q12(0.0312f))
        {
            curLayerVol1 = Q12(0.0312f);
        }

        bgmChannelsVol[i] = curLayerVol1;
    }

    isMusicPlaying    = false;
    areChannelsActive = activeSetChannelTask = func_80045BC8();

    areChannelsActive = activeSetChannelTask != 0 && areChannelsActive != 0xFFFF;

    if (isBgmLayerActive)
    {
        switch (g_Bgm_ChannelSetProcessState)
        {
            case 3:
                Bgm_AllLayersMute();

                if (areChannelsActive)
                {
                    g_Bgm_ChannelSetProcessState = 0;
                }
                else
                {
                    Bgm_ChannelSet();
                    g_Bgm_ChannelSetProcessState = 2;
                }
                break;

            case 2:
                Bgm_AllLayersMute();
                g_Bgm_ChannelSetProcessState = 1;
                break;

            case 1:
                if (areChannelsActive)
                {
                    Bgm_GlobalLayerVariablesUpdate();
                }
                else
                {
                    Bgm_AllLayersMute();
                }

                g_Bgm_ChannelSetProcessState = 0;
                break;

            case 0:
                isMusicPlaying = true;
                break;
        }
    }
    else if (flagsCpy & BgmFlag_MuteAll)
    {
        if (g_Bgm_ChannelSetProcessState != 3)
        {
            g_Bgm_ChannelSetProcessState = 3;
            SD_Call(18);
        }
    }
    else if (g_Bgm_ChannelSetProcessState == 0)
    {
        isMusicPlaying = true;
    }

    if (isMusicPlaying)
    {
        if (areChannelsActive)
        {
            for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes) - 1); i++)
            {
                Sd_ChannelsVolumeSet(i, bgmChannelsVol[i]);
            }
        }
        else
        {
            Bgm_AllLayersMute();
            g_Bgm_ChannelSetProcessState = 3;
        }
    }

    g_Bgm_LayersUpdated = true;
}

void Bgm_MenuUpdate(void) // 0x800363D0
{
    g_RadioPitchState         = 0;
    g_SysWork.bgmStatusFlags |= BgmStatusFlag_Duck;
    Bgm_Update(false);
}

void Bgm_TrackChange(s32 bgmIdx) // 0x8003640C
{
    if (bgmIdx != BgmCmd_UpdateLayers)
    {
        g_MapOverlayHdr.bgmCmd = bgmIdx;
    }
}

// ========================================
// PLAYER ROOM INFORMATION
// ========================================

void Game_MapRoomIdxUpdate(void) // 0x80036420
{
    q19_12 posX;
    q19_12 posZ;
    s8     newMapRoomIdx;

    #define playerChara g_SysWork.playerWork.player

    posX = playerChara.position.vx;
    posZ = playerChara.position.vz;

    // Set map room index based on current player position.
    if (g_MapOverlayHdr.mapRoomIdxGet == NULL)
    {
        newMapRoomIdx = 0;
    }
    else
    {
        newMapRoomIdx = g_MapOverlayHdr.mapRoomIdxGet(posX, posZ);
    }
    g_SavegamePtr->mapRoomIdx = newMapRoomIdx;

    #undef playerChara
}

s32 func_8003647C(void) // 0x8003647C
{
    return g_SavegamePtr->mapRoomIdx > g_MapOverlayHdr.unused_8;
}

s32 func_80036498(void) // 80036498
{
    return !(g_SavegamePtr->mapRoomIdx > g_MapOverlayHdr.unused_8);
}

// ========================================
// UNKNOWN UNUSED MATH
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
