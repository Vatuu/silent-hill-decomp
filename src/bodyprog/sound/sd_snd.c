#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

#define VAB_BUFFER_LIMIT 0xC800u

u8 g_Sd_AudioType;

char pad_bss_800C37C9[3];

u32 g_Sd_DataMoved;

u8 g_Sd_VabLoadAttemps;

char pad_bss_800C37D1[3];

s_AudioItemData* g_Sd_VabTargetLoad;

s_AudioItemData* g_Sd_KdTargetLoad;

// ========================================
// LOAD VAB FILE
// ========================================

void Sd_VabLoad_TaskAdd(s32 cmd) // 0x80047B24
{
    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_TaskPoolAdd(2);
    }

    g_Sd_VabLoadAttemps = 0;
    Sd_TaskPoolAdd(cmd);
    g_Sd_AudioWork.isAudioLoading_15 = true;
}

void Sd_VabLoad(void) // 0x80047B80
{
    u8 depth;
    u8 cmd;

    switch (g_Sd_AudioStreamingStates.audioLoadState_0)
    {
        case 0:
            cmd                = g_Sd_TaskPool[0];
            g_Sd_VabTargetLoad = &g_AudioData[cmd-160];
            g_Sd_AudioType     = g_Sd_VabTargetLoad->typeIdx_0;

            // If audio being loaded isn't BASE.VAB or KDT file.
            if (g_Sd_AudioType != 0)
            {
                if (g_Sd_AudioWork.lastVabAudioLoadedIdx_8[g_Sd_AudioType - 1] == cmd)
                {
                    g_Sd_AudioStreamingStates.audioLoadState_0 = 0;
                    g_Sd_AudioWork.isAudioLoading_15           = false;
                    Sd_TaskPoolUpdate();
                    break;
                }

                g_Sd_AudioWork.lastVabAudioLoadedIdx_8[g_Sd_AudioType - 1] = cmd;
            }

            // Ambient sounds.
            if (cmd >= 170 && cmd <= 204)
            {
                depth = g_Sd_ReverbDepths[cmd - 170];
                if (depth != gSDVolConfig.reverbDepth_F)
                {
                    Sd_SetReverbDepth(depth);
                }
            }

            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
            break;

        case 1:
            Sd_VabLoad_TypeClear();
            break;

        case 2:
            Sd_VabLoad_OffSet();
            break;

        case 3:
            Sd_VabLoad_FileLoad();
            break;

        case 4:
            Sd_VabLoad_OffVagDataSet();
            break;

        case 5:
            Sd_VabLoad_VagDataMove();
            break;

        case 6:
            Sd_VabLoad_OffVagNextDataSet();
            break;

        case 7:
            Sd_VabLoad_NextVagDataMove();
            break;

        case 8:
            Sd_VabLoad_LastVagDataMove();
            break;

        case 9:
            Sd_VabLoad_Finalization();
            break;

        default:
            break;
    }
}

void Sd_VabLoad_TypeClear(void) // 0x80047D1C
{
    g_Sd_DataMoved = 0;
    SdVabClose(g_Sd_AudioType);
    g_Sd_AudioStreamingStates.audioLoadState_0 = 2;
}

void Sd_VabLoad_OffSet(void) // 0x80047D50
{
    CdlLOC sp10;

    if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)CdIntToPos(g_Sd_VabTargetLoad->fileOffset_8 + (g_Sd_DataMoved  / 2048), &sp10), 0))
    {
        g_Sd_AudioStreamingStates.audioLoadState_0 = 3;
    }
}

void Sd_VabLoad_FileLoad(void) // 0x80047DB0
{
    if (CdSync(1, 0) == CdlComplete)
    {
        if (g_Sd_VabTargetLoad->fileSize_4 < VAB_BUFFER_LIMIT)
        {
            CdRead((g_Sd_VabTargetLoad->fileSize_4 + 2047) / 2048, CD_ADDR_0, 128);
        }
        else
        {
            CdRead(25, CD_ADDR_0, 128);
        }

        // @hack
        if (g_Sd_AudioStreamingStates.audioLoadState_0)
        {
            char unk = -unk;
        }

        g_Sd_AudioStreamingStates.audioLoadState_0 = 4;
        g_Sd_AudioWork.cdErrorCount_0              = 0;
    }

    g_Sd_AudioWork.cdErrorCount_0++;
}

void Sd_VabLoad_OffVagDataSet(void) // 0x80047E3C
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)CD_ADDR_0;
        ptr0 = g_Sd_VabBuffers[g_Sd_AudioType];

        for (i = 0; i < g_Sd_VabTargetLoad->vagDataOffset_2; i++)
        {
            *ptr0++ = *ptr1++;
        }

        SdVabOpenHeadSticky(g_Sd_VabBuffers[g_Sd_AudioType], g_Sd_AudioType, D_800A9FDC[g_Sd_AudioType]);
        g_Sd_AudioStreamingStates.audioLoadState_0 = 5;
    }

    g_Sd_AudioWork.cdErrorCount_0++;
}

void Sd_VabLoad_VagDataMove(void) // 0x80047F18
{
    s32  dataMoveCheck;
    s32* ptr;

    if (g_Sd_VabTargetLoad->fileSize_4 < VAB_BUFFER_LIMIT)
    {
        dataMoveCheck = SdVabTransBody((u8*)CD_ADDR_0 + g_Sd_VabTargetLoad->vagDataOffset_2, g_Sd_AudioType);
        ptr           = &g_Sd_VabTargetLoad->fileSize_4;

        g_Sd_DataMoved                             = *ptr;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 9;
    }
    else
    {
        dataMoveCheck = SdVabTransBodyPartly((u8*)CD_ADDR_0 + g_Sd_VabTargetLoad->vagDataOffset_2, VAB_BUFFER_LIMIT - g_Sd_VabTargetLoad->vagDataOffset_2, g_Sd_AudioType);

        g_Sd_DataMoved                             = VAB_BUFFER_LIMIT;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 6;
    }

    if (dataMoveCheck == NO_VALUE && g_Sd_VabLoadAttemps < 16)
    {
        g_Sd_VabLoadAttemps++;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
    }
}

void Sd_VabLoad_OffVagNextDataSet(void) // 0x80048000
{
    s32 i;
    CdlLOC  cdLocArg;
    CdlLOC* cdLocRes;

    if (SdVabTransCompleted(0) == 1)
    {
        i        = g_Sd_VabTargetLoad->fileOffset_8 + ((g_Sd_DataMoved + 2047) / 2048);
        cdLocRes = CdIntToPos(i, &cdLocArg);

        if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)cdLocRes, 0))
        {
            g_Sd_AudioStreamingStates.audioLoadState_0 = 7;
        }
    }
}

void Sd_VabLoad_NextVagDataMove(void) // 0x8004807C
{
    u32 remainingData;

    if (CdSync(1, 0) != CdlComplete)
    {
        return;
    }

    remainingData = g_Sd_VabTargetLoad->fileSize_4 - g_Sd_DataMoved;
    if (remainingData < VAB_BUFFER_LIMIT)
    {
        CdRead(((remainingData + 2047) / 2048), CD_ADDR_0, 128);
    }
    else
    {
        CdRead(25, CD_ADDR_0, 128);
    }

    g_Sd_AudioStreamingStates.audioLoadState_0 = 8;
}

void Sd_VabLoad_LastVagDataMove(void) // 0x800480FC
{
    s32 dataMoveCheck;
    u32 remainingData;

    if (CdReadSync(1, 0) != 0)
    {
        return;
    }

    remainingData = g_Sd_VabTargetLoad->fileSize_4 - g_Sd_DataMoved;
    if (remainingData < VAB_BUFFER_LIMIT)
    {
        dataMoveCheck                              = SdVabTransBodyPartly((u8*)CD_ADDR_0, remainingData, g_Sd_AudioType);
        g_Sd_DataMoved                             = g_Sd_VabTargetLoad->fileSize_4;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 9;
    }
    else
    {
        dataMoveCheck                              = SdVabTransBodyPartly((u8*)CD_ADDR_0, VAB_BUFFER_LIMIT, g_Sd_AudioType);
        g_Sd_DataMoved                            += VAB_BUFFER_LIMIT;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 6;
    }

    if (dataMoveCheck == NO_VALUE && g_Sd_VabLoadAttemps < 16)
    {
        g_Sd_VabLoadAttemps++;
        g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
    }
}

void Sd_VabLoad_Finalization(void) // 0x800481F8
{
    if (SdVabTransCompleted(0) != 1)
    {
        return;
    }

    g_Sd_AudioStreamingStates.audioLoadState_0 = 0;
    g_Sd_AudioWork.cdErrorCount_0              = 0;
    g_Sd_AudioWork.isAudioLoading_15           = false;
    Sd_TaskPoolUpdate();
}

// ========================================
// LOAD KDT FILE FOR MUSIC
// ========================================

void Sd_KdtLoad_TaskAdd(u16 songIdx) // 0x80048244
{
    if (g_Sd_AudioWork.bgmLoadedSongIdx_6 == songIdx)
    {
        return;
    }

    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_TaskPoolAdd(2);
    }

    Sd_StopBgmTaskAdd();
    SD_Call((u16)(songIdx + 173));
    Sd_TaskPoolAdd(songIdx);

    g_Sd_VabLoadAttemps               = 0;
    g_Sd_AudioWork.bgmLoadedSongIdx_6 = songIdx;
    g_Sd_AudioWork.isAudioLoading_15  = true;
}

void Sd_KdtLoad(void) // 0x800482D8
{
    switch (g_Sd_AudioStreamingStates.audioLoadState_0)
    {
        case 0:
            g_Sd_KdTargetLoad                          = &g_AudioData[54+g_Sd_TaskPool[0]];
            g_Sd_AudioType                             = g_Sd_KdTargetLoad->typeIdx_0;
            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
            break;

        case 1:
            Sd_KdtLoad_StopSeq();
            break;

        case 2:
            Sd_KdtLoad_OffSet();
            break;

        case 3:
            Sd_KdtLoad_FileLoad();
            break;

        case 4:
            Sd_KdtLoad_LoadCheck();
            break;

        default:
            break;
    }
}

void Sd_KdtLoad_StopSeq(void) // 0x8004839C
{
    Sd_StopBgmStep();
    SdSeqClose(g_Sd_AudioType);

    g_Sd_AudioStreamingStates.audioLoadState_0 = 2;
}

void Sd_KdtLoad_OffSet(void) // 0x800483D4
{
    CdlLOC cdLoc;

    if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)CdIntToPos(g_Sd_KdTargetLoad->fileOffset_8, &cdLoc), 0))
    {
        g_Sd_AudioStreamingStates.audioLoadState_0 = 3;
    }
}

void Sd_KdtLoad_FileLoad(void) // 0x80048424
{
    if (CdSync(1, 0) == 2)
    {
        CdRead((g_Sd_KdTargetLoad->fileSize_4 + 2047) / 2048, FS_BUFFER_1, 128);

        g_Sd_AudioStreamingStates.audioLoadState_0 = 4;
        g_Sd_AudioWork.cdErrorCount_0              = 0;
    }

    g_Sd_AudioWork.cdErrorCount_0++;
}

void Sd_KdtLoad_LoadCheck(void) // 0x80048498
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)FS_BUFFER_1;
        ptr0 = g_Sd_KdtBuffer[g_Sd_AudioType];

        for (i = 0; i < g_Sd_KdTargetLoad->fileSize_4; i++)
        {
            *ptr0++ = *ptr1++;
        }

        i = SdSeqOpen(g_Sd_KdtBuffer[g_Sd_AudioType], 3);

        if (i == NO_VALUE && g_Sd_VabLoadAttemps < 16)
        {
            g_Sd_VabLoadAttemps++;
            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
        }
        else
        {
            g_Sd_AudioStreamingStates.audioLoadState_0 = 0;
            g_Sd_AudioWork.isAudioLoading_15           = false;

            Sd_TaskPoolUpdate();
        }

        g_Sd_AudioWork.cdErrorCount_0 = 0;
    }

    g_Sd_AudioWork.cdErrorCount_0++;
}

const s32 g_rodataPad_80025D38 = 0;
