#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

#define CD_ERROR_LIMIT 600 // Matches value used in beatmania `FSCD.C`.

void Sd_TaskPoolExecute(void) // 0x800485D8
{
    g_Sd_CurrentTask = g_Sd_TaskPool[0];
    switch (g_Sd_CurrentTask)
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
            Sd_XaPreLoadAudio();
            break;

        case 7:
            func_80046A70();
            break;

        case 8:
            Sd_StopBgm();
            break;

        default:
            if (g_Sd_CurrentTask >= 160)
            {
                Sd_VabLoad();
            }
            else if (g_Sd_CurrentTask >= 32)
            {
                Sd_KdtLoad();
            }
            else
            {
                Sd_TaskPoolUpdate();
            }
            break;
    }

    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        D_800C1688.field_4 = VSync(SyncMode_Count) - D_800C1688.field_8;
    }

    // Fade out background music.
    if (g_Sd_AudioWork.bgmFadeSpeed_14 != 0)
    {
        g_Sd_AudioWork.field_E = NO_VALUE;

        if (gSDVolConfig.volumeBgm_8 <= 0)
        {
            gSDVolConfig.volumeBgm_8 = 0;
            Sd_StopBgmStep();
        }
        else
        {
            gSDVolConfig.volumeBgm_8 -= g_Sd_AudioWork.bgmFadeSpeed_14;

            if ((gSDVolConfig.volumeBgm_8 << 16) <= 0)
            {
                gSDVolConfig.volumeBgm_8 = 0;
                Sd_StopBgmStep();
            }
        }

        gSDVolConfig.volumeBgm_6 = gSDVolConfig.volumeBgm_8;
        
        Sd_SetVolBgm(gSDVolConfig.volumeBgm_8, gSDVolConfig.volumeBgm_8);
    }
    else if (gSDVolConfig.volumeBgm_6 != gSDVolConfig.volumeBgm_8)
    {
        if (gSDVolConfig.volumeBgm_8 < gSDVolConfig.volumeBgm_6)
        {
            gSDVolConfig.volumeBgm_8++;
            if (ABS(gSDVolConfig.volumeBgm_8 - gSDVolConfig.volumeBgm_6) < 2) 
            {
                gSDVolConfig.volumeBgm_8 = gSDVolConfig.volumeBgm_6;
            }
        }
        else
        {
            gSDVolConfig.volumeBgm_8--;
            if (ABS(gSDVolConfig.volumeBgm_8 - gSDVolConfig.volumeBgm_6) < 2) 
            {
                gSDVolConfig.volumeBgm_8 = gSDVolConfig.volumeBgm_6;
            }
        }

        Sd_SetVolBgm(gSDVolConfig.volumeBgm_8, gSDVolConfig.volumeBgm_8);
    }

    if ((u32)D_800C1688.field_4 > (u32)D_800C1688.field_0)
    {
        if (g_Sd_CurrentTask == 0)
        {
            if (g_Sd_AudioWork.isXaLoading_16 == false)
            {
                Sd_TaskPoolAdd(2);
            }

            D_800C1688.field_8 = VSync(SyncMode_Count);
            D_800C1688.field_4 = 0;
        }
    }

    // Slowly fade in/out game audio based if `g_Sd_AudioWork.muteGame_17` enabled.
    if (g_Sd_AudioWork.muteGame_17 == true)
    {
        if (gSDVolConfig.volumeGlobal_A > 0)
        {
            gSDVolConfig.volumeGlobal_A -= 8;
            if ((gSDVolConfig.volumeGlobal_A << 16) <= 0)
            {
                gSDVolConfig.volumeGlobal_A = 0;
            }
            
            SdSetMVol(gSDVolConfig.volumeGlobal_A, gSDVolConfig.volumeGlobal_A);
        }
    }
    else
    {
        if (gSDVolConfig.volumeGlobal_A < (OPT_SOUND_VOLUME_MAX - 1))
        {
            gSDVolConfig.volumeGlobal_A += 4;
            if (gSDVolConfig.volumeGlobal_A >= (OPT_SOUND_VOLUME_MAX - 1))
            {
                gSDVolConfig.volumeGlobal_A = OPT_SOUND_VOLUME_MAX - 1;
            }
            
            SdSetMVol(gSDVolConfig.volumeGlobal_A, gSDVolConfig.volumeGlobal_A);
        }
    }

    // Reset audio streaming system if failed.
    if (g_Sd_AudioWork.cdErrorCount_0 > CD_ERROR_LIMIT)
    {
        CdReset(0);
        CdControlB(CdlNop, NULL, NULL);
        if (g_Sd_AudioStreamingStates.audioLoadState_0 != 0)
        {
            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
        }
        
        g_Sd_AudioStreamingStates.xaLoadState_1    = 0;
        g_Sd_AudioStreamingStates.xaStopState_2    = 0;
        g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
        g_Sd_AudioWork.cdErrorCount_0              = 0;
    }
}

u8 Sd_CdPrimitiveCmdTry(s32 com, u8* param, u8* res) // 0x80048954
{
    u8 syncRes;
    u8 comCopy;
    
    comCopy = com;

    if (CdSync(1, &syncRes) == CdlComplete && CdControl(comCopy, param, res))
    {
        g_Sd_AudioWork.cdErrorCount_0 = 0;
        return false;
    }

    g_Sd_AudioWork.cdErrorCount_0++;

    if (g_Sd_AudioWork.cdErrorCount_0 > CD_ERROR_LIMIT)
    {
        CdReset(0);
        CdControlB(CdlNop, NULL, NULL);
        VSync(SyncMode_Wait3);
        
        if (g_Sd_AudioStreamingStates.audioLoadState_0 != 0)
        {
            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
        }
        
        g_Sd_AudioStreamingStates.xaLoadState_1    = 0;
        g_Sd_AudioStreamingStates.xaStopState_2    = 0;
        g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
        g_Sd_AudioWork.cdErrorCount_0              = 0;
    }

    return true;
}

const s32 rodataPad_80025D60[2] = { 0x6A375A00, 0x892FBD00 }; // Unused. Likely linker generated garbage.
