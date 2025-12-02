#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

#define CD_ERROR_LIMIT 600 // Matches value used in beatmania `FSCD.C`.

void Sd_CmdPoolExecute(void) // 0x800485D8
{
    g_Sd_CurrentCmd = g_Sd_CmdPool[0];
    switch (g_Sd_CurrentCmd)
    {
        case 0:
            break;

        case 1:
            Sd_XaAudioPlay();
            break;

        case 2:
            Sd_XaAudioStop();
            break;

        case 6:
            Sd_XaPreLoadAudioInit();
            break;

        case 7:
            func_80046A70();
            break;

        case 8:
            Sd_StopBgm();
            break;

        default:
            if (g_Sd_CurrentCmd >= 160)
            {
                func_80047B80();
            }
            else if (g_Sd_CurrentCmd >= 32)
            {
                func_800482D8();
            }
            else
            {
                Sd_CmdPoolUpdate();
            }
            break;
    }

    if (D_800C1658.xaAudioIdx_4 != 0)
    {
        D_800C1688.field_4 = VSync(SyncMode_Count) - D_800C1688.field_8;
    }

	// Fade out background music.
    if (D_800C1658.bgmFadeSpeed_14 != 0)
    {
        D_800C1658.field_E = NO_VALUE;

        if (g_Sd_ChannelsVolume.volumeBgm_8 <= 0)
        {
            g_Sd_ChannelsVolume.volumeBgm_8 = 0;
            Sd_StopBgmStep();
        }
        else
        {
            g_Sd_ChannelsVolume.volumeBgm_8 -= D_800C1658.bgmFadeSpeed_14;

            if ((g_Sd_ChannelsVolume.volumeBgm_8 << 16) <= 0)
            {
                g_Sd_ChannelsVolume.volumeBgm_8 = 0;
                Sd_StopBgmStep();
            }
        }

        g_Sd_ChannelsVolume.volumeBgm_6 = g_Sd_ChannelsVolume.volumeBgm_8;
        
        Sd_SetVolBgm(g_Sd_ChannelsVolume.volumeBgm_8, g_Sd_ChannelsVolume.volumeBgm_8);
    }
    else if (g_Sd_ChannelsVolume.volumeBgm_6 != g_Sd_ChannelsVolume.volumeBgm_8)
    {
        if (g_Sd_ChannelsVolume.volumeBgm_8 < g_Sd_ChannelsVolume.volumeBgm_6)
        {
            g_Sd_ChannelsVolume.volumeBgm_8++;
            if (ABS(g_Sd_ChannelsVolume.volumeBgm_8 - g_Sd_ChannelsVolume.volumeBgm_6) < 2) 
            {
                g_Sd_ChannelsVolume.volumeBgm_8 = g_Sd_ChannelsVolume.volumeBgm_6;
            }
        }
        else
        {
            g_Sd_ChannelsVolume.volumeBgm_8--;
            if (ABS(g_Sd_ChannelsVolume.volumeBgm_8 - g_Sd_ChannelsVolume.volumeBgm_6) < 2) 
            {
                g_Sd_ChannelsVolume.volumeBgm_8 = g_Sd_ChannelsVolume.volumeBgm_6;
            }
        }

        Sd_SetVolBgm(g_Sd_ChannelsVolume.volumeBgm_8, g_Sd_ChannelsVolume.volumeBgm_8);
    }

    if ((u32)D_800C1688.field_4 > (u32)D_800C1688.field_0)
    {
        if (g_Sd_CurrentCmd == 0)
        {
            if (D_800C1658.isXaLoading_16 == false)
            {
                Sd_CmdPoolAdd(2);
            }

            D_800C1688.field_8 = VSync(SyncMode_Count);
            D_800C1688.field_4 = 0;
        }
    }

	// Slowly fade in/out game audio based if `D_800C1658.muteGame_17` enabled.
    if (D_800C1658.muteGame_17 == true)
    {
        if (g_Sd_ChannelsVolume.volumeGlobal_A > 0)
        {
            g_Sd_ChannelsVolume.volumeGlobal_A -= 8;
            if ((g_Sd_ChannelsVolume.volumeGlobal_A << 16) <= 0)
            {
                g_Sd_ChannelsVolume.volumeGlobal_A = 0;
            }
            
            SdSetMVol(g_Sd_ChannelsVolume.volumeGlobal_A, g_Sd_ChannelsVolume.volumeGlobal_A);
        }
    }
    else
    {
        if (g_Sd_ChannelsVolume.volumeGlobal_A < (OPT_SOUND_VOLUME_MAX - 1))
        {
            g_Sd_ChannelsVolume.volumeGlobal_A += 4;
            if (g_Sd_ChannelsVolume.volumeGlobal_A >= (OPT_SOUND_VOLUME_MAX - 1))
            {
                g_Sd_ChannelsVolume.volumeGlobal_A = OPT_SOUND_VOLUME_MAX - 1;
            }
            
            SdSetMVol(g_Sd_ChannelsVolume.volumeGlobal_A, g_Sd_ChannelsVolume.volumeGlobal_A);
        }
    }

	// Reset audio streaming system if failed.
    if (D_800C1658.cdErrorCount_0 > CD_ERROR_LIMIT)
    {
        CdReset(0);
        CdControlB(CdlNop, NULL, NULL);
        if (g_Sd_AudioStreamingStates.vabLoadState_0 != 0)
        {
            g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
        }
        
        g_Sd_AudioStreamingStates.xaLoadState_1    = 0;
        g_Sd_AudioStreamingStates.xaStopState_2    = 0;
        g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
        D_800C1658.cdErrorCount_0                  = 0;
    }
}

u8 Sd_CdPrimitiveCmdTry(s32 com, u8* param, u8* res) // 0x80048954
{
    u8 syncRes;
    u8 comCopy;
    
    comCopy = com;

    if (CdSync(1, &syncRes) == CdlComplete && CdControl(comCopy, param, res))
    {
        D_800C1658.cdErrorCount_0 = 0;
        return false;
    }

    D_800C1658.cdErrorCount_0++;

    if (D_800C1658.cdErrorCount_0 > CD_ERROR_LIMIT)
    {
        CdReset(0);
        CdControlB(CdlNop, NULL, NULL);
        VSync(SyncMode_Wait3);
        
        if (g_Sd_AudioStreamingStates.vabLoadState_0 != 0)
        {
            g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
        }
        
        g_Sd_AudioStreamingStates.xaLoadState_1    = 0;
        g_Sd_AudioStreamingStates.xaStopState_2    = 0;
        g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
        D_800C1658.cdErrorCount_0                  = 0;
    }

    return true;
}

const s32 unused_Rodata_80025D60[2] = { 0x6A375A00, 0x892FBD00 }; // Unused.
