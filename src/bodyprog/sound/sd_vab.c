#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

#define VAB_BUFFER_LIMIT 0xC800u

/** @brief Addresses where loaded VAB files are stored in memory.
 * 0 = Generic game sound file (BASE.VAB).
 * 1 = Weapon VAB.
 * 2 = Ambient VAB and new game / load menu sound (FIRST.VAB).
 * 3 = Music VAB.
 *
 * @note These types are irregular as the first 3 defined files ain `g_AudioData` don't correspond to their
 * categories. Of the last two, maybe one is unused, and the other is the sound that plays when starting
 * a save. However, the first file has a value of 0, suggesting it's a KDT file, but it's actually a VAB file
 * containing generic sound effects.
 * Deobfuscated symbols from other games may also share this system.
 */
static u8* g_Sd_VabBuffers[4] = {
    (u8*)0x801FE460,
    (u8*)0x801FD840,
    (u8*)0x801FC220,
    (u8*)0x801FA600
};

/** @brief Stores the currently loaded KDT file.
 * Declared as an array because of the way the code handles VAB file loading, as it expect to have a position.
 */
static u8* g_Sd_KdtBuffer[1] = {
    (u8*)0x801F5600
};

static s32 D_800A9FDC[4] = {
    0x00001010, 0x00021490, 0x00027630, 0x00058F50
};

/** @brief Data used to access to VAB and KDT files. */
static s_AudioItemData g_AudioData[127] = {
    { AudioType_BaseAudio,     0, 4128, 136208, 140   }, // BASE.VAB
    { AudioType_SpecialScreen, 0, 3104, 220032, 539   }, // COATION.VAB (@unused)
    { AudioType_SpecialScreen, 0, 3104, 135072, 25237 }, // FIRST.VAB
    { AudioType_Weapon,        0, 3104, 27632,  25045 },
    { AudioType_Weapon,        0, 3104, 22160,  25303 },
    { AudioType_Weapon,        0, 3104, 24272,  25500 },
    { AudioType_Weapon,        0, 3104, 17488,  29275 },
    { AudioType_Weapon,        0, 3104, 27168,  29358 },
    { AudioType_Weapon,        0, 3104, 27424,  29456 },
    { AudioType_Weapon,        0, 3104, 26720,  29442 },
    { AudioType_Ambient,       0, 4640, 138928, 28593 },
    { AudioType_Ambient,       0, 4128, 203024, 25988 },
    { AudioType_Ambient,       0, 5152, 168592, 28661 },
    { AudioType_Ambient,       0, 5152, 193392, 28744 },
    { AudioType_Ambient,       0, 5664, 170080, 28839 },
    { AudioType_Ambient,       0, 5664, 187776, 28923 },
    { AudioType_Ambient,       0, 3104, 184416, 26559 },
    { AudioType_Ambient,       0, 4640, 115760, 26650 },
    { AudioType_Ambient,       0, 4640, 207216, 26707 },
    { AudioType_Ambient,       0, 4640, 188304, 26809 },
    { AudioType_Ambient,       0, 3104, 12736,  26901 },
    { AudioType_Ambient,       0, 5152, 190944, 26908 },
    { AudioType_Ambient,       0, 5152, 205584, 27002 },
    { AudioType_Ambient,       0, 5152, 197552, 27103 },
    { AudioType_Ambient,       0, 5152, 206304, 27200 },
    { AudioType_Ambient,       0, 5152, 208112, 27301 },
    { AudioType_Ambient,       0, 3104, 96080,  27403 },
    { AudioType_Ambient,       0, 3104, 91984,  27450 },
    { AudioType_Ambient,       0, 4640, 154048, 27495 },
    { AudioType_Ambient,       0, 3104, 165024, 27571 },
    { AudioType_Ambient,       0, 4640, 207680, 27652 },
    { AudioType_Ambient,       0, 5152, 152768, 27754 },
    { AudioType_Ambient,       0, 4640, 136000, 27829 },
    { AudioType_Ambient,       0, 4640, 42256,  29015 },
    { AudioType_Ambient,       0, 3104, 31664,  27922 },
    { AudioType_Ambient,       0, 4640, 206096, 27938 },
    { AudioType_Ambient,       0, 3616, 50752,  28039 },
    { AudioType_Ambient,       0, 3616, 67424,  28064 },
    { AudioType_Ambient,       0, 4640, 161152, 28097 },
    { AudioType_Ambient,       0, 5152, 198128, 29036 },
    { AudioType_Ambient,       0, 3104, 25136,  28278 },
    { AudioType_Ambient,       0, 4640, 207024, 28291 },
    { AudioType_Ambient,       0, 5152, 205856, 28393 },
    { AudioType_Ambient,       0, 4128, 200752, 28494 },
    { AudioType_Ambient,       0, 4640, 201200, 26088 },
    { AudioType_MusicBank,     0, 6176, 117792, 24634 },
    { AudioType_MusicBank,     0, 7200, 117648, 24702 },
    { AudioType_MusicBank,     0, 6176, 143456, 24765 },
    { AudioType_MusicBank,     0, 5152, 98448,  24838 },
    { AudioType_MusicBank,     0, 5664, 137024, 24888 },
    { AudioType_MusicBank,     0, 4128, 138624, 24956 },
    { AudioType_MusicBank,     0, 3104, 40928,  25025 },
    { AudioType_MusicBank,     0, 5152, 42000,  25062 },
    { AudioType_MusicBank,     0, 4128, 83136,  25084 },
    { AudioType_MusicBank,     0, 4640, 86848,  25126 },
    { AudioType_MusicBank,     0, 6176, 133680, 25171 },
    { AudioType_MusicBank,     0, 5664, 141408, 25318 },
    { AudioType_MusicBank,     0, 4640, 122704, 25389 },
    { AudioType_MusicBank,     0, 4128, 60192,  25450 },
    { AudioType_MusicBank,     0, 3616, 37712,  25481 },
    { AudioType_MusicBank,     0, 5664, 97392,  25513 },
    { AudioType_MusicBank,     0, 5152, 114992, 25562 },
    { AudioType_MusicBank,     0, 5664, 128256, 25621 },
    { AudioType_MusicBank,     0, 4128, 73648,  25685 },
    { AudioType_MusicBank,     0, 6176, 137600, 25722 },
    { AudioType_MusicBank,     0, 4640, 139712, 25791 },
    { AudioType_MusicBank,     0, 4640, 106288, 25863 },
    { AudioType_MusicBank,     0, 5152, 140400, 29136 },
    { AudioType_MusicBank,     0, 4128, 80144,  29207 },
    { AudioType_MusicBank,     0, 4128, 54336,  29248 },
    { AudioType_MusicBank,     0, 4640, 129968, 29285 },
    { AudioType_MusicBank,     0, 3104, 15168,  29350 },
    { AudioType_MusicBank,     0, 5152, 140672, 29373 },
    { AudioType_MusicBank,     0, 5152, 61344,  29475 },
    { AudioType_MusicBank,     0, 5152, 61344,  29507 },
    { AudioType_MusicBank,     0, 4128, 90096,  29538 },
    { AudioType_MusicBank,     0, 4128, 134656, 29583 },
    { AudioType_MusicBank,     0, 4640, 63376,  29651 },
    { AudioType_MusicBank,     0, 5152, 109056, 29683 },
    { AudioType_MusicBank,     0, 5152, 97840,  29739 },
    { AudioType_MusicBank,     0, 5152, 137568, 29788 },
    { AudioType_MusicBank,     0, 5152, 147936, 29858 },
    { AudioType_MusicBank,     0, 4640, 94400,  29934 },
    { AudioType_MusicBank,     0, 5152, 137296, 29983 },
    { AudioType_MusicBank,     0, 6688, 153152, 30057 },
    { 0,                       0, 0,    0,      0     },
    { AudioType_MusicKey,      0, 0,    3236,   24632 },
    { AudioType_MusicKey,      0, 0,    19340,  24692 },
    { AudioType_MusicKey,      0, 0,    9576,   24760 },
    { AudioType_MusicKey,      0, 0,    4040,   24836 },
    { AudioType_MusicKey,      0, 0,    1776,   24887 },
    { AudioType_MusicKey,      0, 0,    1304,   24955 },
    { AudioType_MusicKey,      0, 0,    596,    25024 },
    { AudioType_MusicKey,      0, 0,    4500,   25059 },
    { AudioType_MusicKey,      0, 0,    300,    25083 },
    { AudioType_MusicKey,      0, 0,    532,    25125 },
    { AudioType_MusicKey,      0, 0,    3728,   25169 },
    { AudioType_MusicKey,      0, 0,    6492,   25314 },
    { AudioType_MusicKey,      0, 0,    1344,   25388 },
    { AudioType_MusicKey,      0, 0,    896,    25449 },
    { AudioType_MusicKey,      0, 0,    196,    25480 },
    { AudioType_MusicKey,      0, 0,    1256,   25512 },
    { AudioType_MusicKey,      0, 0,    1892,   25561 },
    { AudioType_MusicKey,      0, 0,    2560,   25619 },
    { AudioType_MusicKey,      0, 0,    732,    25684 },
    { AudioType_MusicKey,      0, 0,    1860,   25721 },
    { AudioType_MusicKey,      0, 0,    1176,   25790 },
    { AudioType_MusicKey,      0, 0,    6000,   25860 },
    { AudioType_MusicKey,      0, 0,    5476,   29133 },
    { AudioType_MusicKey,      0, 0,    3952,   29205 },
    { AudioType_MusicKey,      0, 0,    808,    29247 },
    { AudioType_MusicKey,      0, 0,    1820,   29284 },
    { AudioType_MusicKey,      0, 0,    676,    29349 },
    { AudioType_MusicKey,      0, 0,    716,    29372 },
    { AudioType_MusicKey,      0, 0,    8220,   29470 },
    { AudioType_MusicKey,      0, 0,    2448,   29505 },
    { AudioType_MusicKey,      0, 0,    832,    29537 },
    { AudioType_MusicKey,      0, 0,    172,    29582 },
    { AudioType_MusicKey,      0, 0,    2720,   29649 },
    { AudioType_MusicKey,      0, 0,    1688,   29682 },
    { AudioType_MusicKey,      0, 0,    3128,   29737 },
    { AudioType_MusicKey,      0, 0,    1348,   29787 },
    { AudioType_MusicKey,      0, 0,    2324,   29856 },
    { AudioType_MusicKey,      0, 0,    4436,   29931 },
    { AudioType_MusicKey,      0, 0,    2496,   29981 },
    { AudioType_MusicKey,      0, 0,    11372,  30051 },
    { 0,                       0, 0,    0,      0     }
};

// ========================================
// LOAD VAB FILE
// ========================================

void Sd_VabLoad_CmdSet(s32 cmd) // 0x80047B24
{
    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_CmdPoolAdd(2);
    }

    g_Sd_VabLoadAttemps = 0;
    Sd_CmdPoolAdd(cmd);
    g_Sd_AudioWork.isAudioLoading_15 = true;
}

void Sd_VabLoad(void) // 0x80047B80
{
    u8 depth;
    u8 cmd;

    switch (g_Sd_AudioStreamingStates.audioLoadState_0)
    {
        case 0:
            cmd                = g_Sd_CmdPool[0];
            g_Sd_VabTargetLoad = &g_AudioData[cmd-160];
            g_Sd_AudioType     = g_Sd_VabTargetLoad->typeIdx_0;
			
            // If audio being loaded isn't BASE.VAB or KDT file.
            if (g_Sd_AudioType != 0)
            {
                if (g_Sd_AudioWork.lastVabAudioLoadedIdx_8[g_Sd_AudioType - 1] == cmd)
                {
                    g_Sd_AudioStreamingStates.audioLoadState_0 = 0;
                    g_Sd_AudioWork.isAudioLoading_15           = false;
                    Sd_CmdPoolUpdate();
                    break;
                }

                g_Sd_AudioWork.lastVabAudioLoadedIdx_8[g_Sd_AudioType - 1] = cmd;
            }
			
            // Ambient sounds.
            if (cmd >= 170 && cmd <= 204)
            {
                depth = g_Sd_ReverbDepths[cmd - 170];
                if (depth != g_Sd_ReverbDepth)
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
    Sd_CmdPoolUpdate();
}

// ========================================
// LOAD KDT FILE FOR MUSIC
// ========================================

void Sd_KdtLoad_CmdSet(u16 songIdx) // 0x80048244
{
    if (g_Sd_AudioWork.bgmLoadedSongIdx_6 == songIdx)
    {
        return;
    }

    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_CmdPoolAdd(2);
    }

    Sd_StopBgmCmd();
    Sd_EngineCmd((u16)(songIdx + 173));
    Sd_CmdPoolAdd(songIdx);

    g_Sd_VabLoadAttemps               = 0;
    g_Sd_AudioWork.bgmLoadedSongIdx_6 = songIdx;
    g_Sd_AudioWork.isAudioLoading_15  = true;
}

void Sd_KdtLoad(void) // 0x800482D8
{
    switch (g_Sd_AudioStreamingStates.audioLoadState_0)
    {
        case 0:
            g_Sd_KdTargetLoad                          = &g_AudioData[54+g_Sd_CmdPool[0]];
            g_Sd_AudioType                             = g_Sd_KdTargetLoad->typeIdx_0;
            g_Sd_AudioStreamingStates.audioLoadState_0 = 1;
            break;
        
        case 1:
            Sd_StopSeq();
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

void Sd_StopSeq(void) // 0x8004839C
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

            Sd_CmdPoolUpdate();
        }

        g_Sd_AudioWork.cdErrorCount_0 = 0;
    }

    g_Sd_AudioWork.cdErrorCount_0++;
}

const s32 g_rodataPad_80025D38 = 0;
