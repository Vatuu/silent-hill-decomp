#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

/** @brief Addresses where loaded VAB files are stored in memory.
 * 0 = Music VAB.
 * 1 = Weapon VAB.
 * 2 = Unk.
 * 3 = Unk.
 *
 * @note Deobfuscated symbols from other games may also share this system.
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

/** @note Strange data access.
 * Splat's generated assembly points to data from 0x800A9FDC to 0x800AA274 to be all from the same 
 * array, however, `Sd_VabLoad` accesses this data in a strange way.
 *
 * `Sd_VabLoad` is used to switch the audio bank of the currently selected weapon
 * (change the weapon in the inventory and then leave it to triger this function).
 * The way this function triggers is by adding a command to `g_Sd_CmdPool` which goes from 164 to 168
 * depending on the weapon (the code allows it to go down to 160, but it's impossible to get a
 * command with that value naturally). The value of this command goes through many functions until it reaches
 * `func_8007F14C`, where it's used to get the index of the audio bank to be loaded. The strange
 * thing starts here, as the same value of the command assigned is used to get inside a specific element from
 * a variable that uses struct `s_VabItemData`: `D_800A986C`, which only has 5 elements. However, the
 * elements being accessed have index 164 to 168. So instead the code uses `D_800A986C` as a pointer
 * to jump all the way up to 0x800A9FEC where the table is actually used for switching the audio bank of the
 * currently selected weapon. This is over-engineered and it would be interesting to investigate how this
 * works in other versions.
 *
 * With the previously said this means that this data is actually a `s_VabItemData` struct array that begins
 * at 0x800A9FEC, and since it's not being directly or indirectly (in a normal way) called by a function,
 * Splat mixes it up with `D_800A9FDC`, which is actually being called directly by `func_80047E3C`. Looking at
 * the code indicates that the data between 0x800A9FDC to 0x800A9FEC are actually 4 `int` values.
 */
static s32 D_800A9FDC[4] = {
    0x00001010, 0x00021490, 0x00027630, 0x00058F50
};

static s_VabItemData D_800A9FEC[54] = {
    { VabAudioType_MusicKey, 0, 4128, 136208, 140   },
    { VabAudioType_Ambient,  0, 3104, 220032, 539   },
    { VabAudioType_Ambient,  0, 3104, 135072, 25237 },
    { VabAudioType_Weapon,   0, 3104,  27632, 25045 },
    { VabAudioType_Weapon,   0, 3104,  22160, 25303 },
    { VabAudioType_Weapon,   0, 3104,  24272, 25500 },
    { VabAudioType_Weapon,   0, 3104,  17488, 29275 },
    { VabAudioType_Weapon,   0, 3104,  27168, 29358 },
    { VabAudioType_Weapon,   0, 3104,  27424, 29456 },
    { VabAudioType_Weapon,   0, 3104,  26720, 29442 },
    { VabAudioType_Ambient,  0, 4640, 138928, 28593 },
    { VabAudioType_Ambient,  0, 4128, 203024, 25988 },
    { VabAudioType_Ambient,  0, 5152, 168592, 28661 },
    { VabAudioType_Ambient,  0, 5152, 193392, 28744 },
    { VabAudioType_Ambient,  0, 5664, 170080, 28839 },
    { VabAudioType_Ambient,  0, 5664, 187776, 28923 },
    { VabAudioType_Ambient,  0, 3104, 184416, 26559 },
    { VabAudioType_Ambient,  0, 4640, 115760, 26650 },
    { VabAudioType_Ambient,  0, 4640, 207216, 26707 },
    { VabAudioType_Ambient,  0, 4640, 188304, 26809 },
    { VabAudioType_Ambient,  0, 3104,  12736, 26901 },
    { VabAudioType_Ambient,  0, 5152, 190944, 26908 },
    { VabAudioType_Ambient,  0, 5152, 205584, 27002 },
    { VabAudioType_Ambient,  0, 5152, 197552, 27103 },
    { VabAudioType_Ambient,  0, 5152, 206304, 27200 },
    { VabAudioType_Ambient,  0, 5152, 208112, 27301 },
    { VabAudioType_Ambient,  0, 3104,  96080, 27403 },
    { VabAudioType_Ambient,  0, 3104,  91984, 27450 },
    { VabAudioType_Ambient,  0, 4640, 154048, 27495 },
    { VabAudioType_Ambient,  0, 3104, 165024, 27571 },
    { VabAudioType_Ambient,  0, 4640, 207680, 27652 },
    { VabAudioType_Ambient,  0, 5152, 152768, 27754 },
    { VabAudioType_Ambient,  0, 4640, 136000, 27829 },
    { VabAudioType_Ambient,  0, 4640,  42256, 29015 },
    { VabAudioType_Ambient,  0, 3104,  31664, 27922 },
    { VabAudioType_Ambient,  0, 4640, 206096, 27938 },
    { VabAudioType_Ambient,  0, 3616,  50752, 28039 },
    { VabAudioType_Ambient,  0, 3616,  67424, 28064 },
    { VabAudioType_Ambient,  0, 4640, 161152, 28097 },
    { VabAudioType_Ambient,  0, 5152, 198128, 29036 },
    { VabAudioType_Ambient,  0, 3104,  25136, 28278 },
    { VabAudioType_Ambient,  0, 4640, 207024, 28291 },
    { VabAudioType_Ambient,  0, 5152, 205856, 28393 },
    { VabAudioType_Ambient,  0, 4128, 200752, 28494 },
    { VabAudioType_Ambient,  0, 4640, 201200, 26088 },
    { VabAudioType_Unk3,     0, 6176, 117792, 24634 },
    { VabAudioType_Unk3,     0, 7200, 117648, 24702 },
    { VabAudioType_Unk3,     0, 6176, 143456, 24765 },
    { VabAudioType_Unk3,     0, 5152,  98448, 24838 },
    { VabAudioType_Unk3,     0, 5664, 137024, 24888 },
    { VabAudioType_Unk3,     0, 4128, 138624, 24956 },
    { VabAudioType_Unk3,     0, 3104,  40928, 25025 },
    { VabAudioType_Unk3,     0, 5152,  42000, 25062 },
    { VabAudioType_Unk3,     0, 4128,  83136, 25084 }
};

static s_VabItemData D_800AA274[73] = {
    { VabAudioType_Unk3,     0, 4640, 86848,  25126 },
    { VabAudioType_Unk3,     0, 6176, 133680, 25171 },
    { VabAudioType_Unk3,     0, 5664, 141408, 25318 },
    { VabAudioType_Unk3,     0, 4640, 122704, 25389 },
    { VabAudioType_Unk3,     0, 4128, 60192,  25450 },
    { VabAudioType_Unk3,     0, 3616, 37712,  25481 },
    { VabAudioType_Unk3,     0, 5664, 97392,  25513 },
    { VabAudioType_Unk3,     0, 5152, 114992, 25562 },
    { VabAudioType_Unk3,     0, 5664, 128256, 25621 },
    { VabAudioType_Unk3,     0, 4128, 73648,  25685 },
    { VabAudioType_Unk3,     0, 6176, 137600, 25722 },
    { VabAudioType_Unk3,     0, 4640, 139712, 25791 },
    { VabAudioType_Unk3,     0, 4640, 106288, 25863 },
    { VabAudioType_Unk3,     0, 5152, 140400, 29136 },
    { VabAudioType_Unk3,     0, 4128, 80144,  29207 },
    { VabAudioType_Unk3,     0, 4128, 54336,  29248 },
    { VabAudioType_Unk3,     0, 4640, 129968, 29285 },
    { VabAudioType_Unk3,     0, 3104, 15168,  29350 },
    { VabAudioType_Unk3,     0, 5152, 140672, 29373 },
    { VabAudioType_Unk3,     0, 5152, 61344,  29475 },
    { VabAudioType_Unk3,     0, 5152, 61344,  29507 },
    { VabAudioType_Unk3,     0, 4128, 90096,  29538 },
    { VabAudioType_Unk3,     0, 4128, 134656, 29583 },
    { VabAudioType_Unk3,     0, 4640, 63376,  29651 },
    { VabAudioType_Unk3,     0, 5152, 109056, 29683 },
    { VabAudioType_Unk3,     0, 5152, 97840,  29739 },
    { VabAudioType_Unk3,     0, 5152, 137568, 29788 },
    { VabAudioType_Unk3,     0, 5152, 147936, 29858 },
    { VabAudioType_Unk3,     0, 4640, 94400,  29934 },
    { VabAudioType_Unk3,     0, 5152, 137296, 29983 },
    { VabAudioType_Unk3,     0, 6688, 153152, 30057 },
    {},
    { VabAudioType_MusicKey, 0, 0,    3236,   24632 },
    { VabAudioType_MusicKey, 0, 0,    19340,  24692 },
    { VabAudioType_MusicKey, 0, 0,    9576,   24760 },
    { VabAudioType_MusicKey, 0, 0,    4040,   24836 },
    { VabAudioType_MusicKey, 0, 0,    1776,   24887 },
    { VabAudioType_MusicKey, 0, 0,    1304,   24955 },
    { VabAudioType_MusicKey, 0, 0,    596,    25024 },
    { VabAudioType_MusicKey, 0, 0,    4500,   25059 },
    { VabAudioType_MusicKey, 0, 0,    300,    25083 },
    { VabAudioType_MusicKey, 0, 0,    532,    25125 },
    { VabAudioType_MusicKey, 0, 0,    3728,   25169 },
    { VabAudioType_MusicKey, 0, 0,    6492,   25314 },
    { VabAudioType_MusicKey, 0, 0,    1344,   25388 },
    { VabAudioType_MusicKey, 0, 0,    896,    25449 },
    { VabAudioType_MusicKey, 0, 0,    196,    25480 },
    { VabAudioType_MusicKey, 0, 0,    1256,   25512 },
    { VabAudioType_MusicKey, 0, 0,    1892,   25561 },
    { VabAudioType_MusicKey, 0, 0,    2560,   25619 },
    { VabAudioType_MusicKey, 0, 0,    732,    25684 },
    { VabAudioType_MusicKey, 0, 0,    1860,   25721 },
    { VabAudioType_MusicKey, 0, 0,    1176,   25790 },
    { VabAudioType_MusicKey, 0, 0,    6000,   25860 },
    { VabAudioType_MusicKey, 0, 0,    5476,   29133 },
    { VabAudioType_MusicKey, 0, 0,    3952,   29205 },
    { VabAudioType_MusicKey, 0, 0,    808,    29247 },
    { VabAudioType_MusicKey, 0, 0,    1820,   29284 },
    { VabAudioType_MusicKey, 0, 0,    676,    29349 },
    { VabAudioType_MusicKey, 0, 0,    716,    29372 },
    { VabAudioType_MusicKey, 0, 0,    8220,   29470 },
    { VabAudioType_MusicKey, 0, 0,    2448,   29505 },
    { VabAudioType_MusicKey, 0, 0,    832,    29537 },
    { VabAudioType_MusicKey, 0, 0,    172,    29582 },
    { VabAudioType_MusicKey, 0, 0,    2720,   29649 },
    { VabAudioType_MusicKey, 0, 0,    1688,   29682 },
    { VabAudioType_MusicKey, 0, 0,    3128,   29737 },
    { VabAudioType_MusicKey, 0, 0,    1348,   29787 },
    { VabAudioType_MusicKey, 0, 0,    2324,   29856 },
    { VabAudioType_MusicKey, 0, 0,    4436,   29931 },
    { VabAudioType_MusicKey, 0, 0,    2496,   29981 },
    { VabAudioType_MusicKey, 0, 0,    11372,  30051 },
    {}
};

// ========================================
// LOAD VAB FILE
// ========================================

void Sd_VabLoad_CmdSet(s32 cmd) // 0x80047B24
{
    if (D_800C1658.xaAudioIdx_4 != 0)
    {
        Sd_CmdPoolAdd(2);
    }

    g_Sd_VabLoadAttemps = 0;
    Sd_CmdPoolAdd(cmd);
    D_800C1658.isVabLoading_15 = true;
}

void Sd_VabLoad(void) // 0x80047B80
{
    u8 depth;
    u8 cmd;

    switch (g_Sd_AudioStreamingStates.vabLoadState_0)
    {
        case 0:
            // Strange access of data. See `D_800A9FDC`.
            cmd                    = g_Sd_CmdPool[0];
            g_Sd_VabLoad_TargetVab = &D_800A986C[cmd];
            g_Sd_VabType           = g_Sd_VabLoad_TargetVab->vabTypeIdx_0;

            if (g_Sd_VabType != VabAudioType_MusicKey)
            {
                if (D_800C1658.vabAudioIdx_8[g_Sd_VabType - 1] == cmd)
                {
                    g_Sd_AudioStreamingStates.vabLoadState_0 = 0;
                    D_800C1658.isVabLoading_15               = false;
                    Sd_CmdPoolUpdate();
                    break;
                }

                D_800C1658.vabAudioIdx_8[g_Sd_VabType - 1] = cmd;
            }

            if (cmd >= 170 && cmd <= 204)
            {
                depth = g_Sd_ReverbDepths[cmd - 170];
                if (depth != g_Sd_ReverbDepth)
                {
                    Sd_SetReverbDepth(depth);
                }
            }

            g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
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
            func_80047E3C();
            break;

        case 5:
            func_80047F18();
            break;

        case 6:
            func_80048000();
            break;

        case 7:
            func_8004807C();
            break;

        case 8:
            func_800480FC();
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
    D_800C37CC = 0;
    SdVabClose(g_Sd_VabType);
    g_Sd_AudioStreamingStates.vabLoadState_0 = 2;
}

void Sd_VabLoad_OffSet(void) // 0x80047D50
{
    CdlLOC sp10;

    if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)CdIntToPos(g_Sd_VabLoad_TargetVab->vabFileOffset_8 + (D_800C37CC >> 11), &sp10), 0))
    {
        g_Sd_AudioStreamingStates.vabLoadState_0 = 3;
    }
}

void Sd_VabLoad_FileLoad(void) // 0x80047DB0
{
    if (CdSync(1, 0) == CdlComplete)
    {
        if (g_Sd_VabLoad_TargetVab->vabFileSize_4 < 0xC800)
        {
            CdRead((g_Sd_VabLoad_TargetVab->vabFileSize_4 + 2047) / 2048, CD_ADDR_0, 128);
        }
        else
        {
            CdRead(25, CD_ADDR_0, 128);
        }

        // @hack
        if (g_Sd_AudioStreamingStates.vabLoadState_0)
        {
            char unk = -unk;
        }

        g_Sd_AudioStreamingStates.vabLoadState_0 = 4;
        D_800C1658.cdErrorCount_0                = 0;
    }

    D_800C1658.cdErrorCount_0++;
}

void func_80047E3C(void) // 0x80047E3C
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)CD_ADDR_0;
        ptr0 = g_Sd_VabBuffers[g_Sd_VabType];

        for (i = 0; i < g_Sd_VabLoad_TargetVab->field_2; i++) 
        {
            *ptr0++ = *ptr1++;
        }

        SdVabOpenHeadSticky(g_Sd_VabBuffers[g_Sd_VabType], g_Sd_VabType, D_800A9FDC[g_Sd_VabType]);
        g_Sd_AudioStreamingStates.vabLoadState_0 = 5;
    }

    D_800C1658.cdErrorCount_0++;
}

void func_80047F18(void) // 0x80047F18
{
    s32 var;
    s32* ptr;

    if (g_Sd_VabLoad_TargetVab->vabFileSize_4 < 0xC800)
    {
        var = SdVabTransBody((u8*)CD_ADDR_0 + g_Sd_VabLoad_TargetVab->field_2, g_Sd_VabType);
        ptr = &g_Sd_VabLoad_TargetVab->vabFileSize_4;

        D_800C37CC                               = *ptr;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 9;
    }
    else
    {
        var = SdVabTransBodyPartly((u8*)CD_ADDR_0 + g_Sd_VabLoad_TargetVab->field_2, 0xC800 - g_Sd_VabLoad_TargetVab->field_2, g_Sd_VabType);

        D_800C37CC                               = 0xC800;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 6;
    }
    
    if (var == NO_VALUE && g_Sd_VabLoadAttemps < 16)
    {
        g_Sd_VabLoadAttemps++;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
    }
}

void func_80048000(void) // 0x80048000
{
    s32 i;
    CdlLOC  cdLocArg;
    CdlLOC* cdLocRes;

    if (SdVabTransCompleted(0) == 1)
    {
        i        = g_Sd_VabLoad_TargetVab->vabFileOffset_8 + ((D_800C37CC + 0x7FF) >> 11);
        cdLocRes = CdIntToPos(i, &cdLocArg);

        if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)cdLocRes, 0))
        {
            g_Sd_AudioStreamingStates.vabLoadState_0 = 7;
        }
    }
}

void func_8004807C(void) // 0x8004807C
{
    u32 var;

    if (CdSync(1, 0) != CdlComplete)
    {
        return;
    }
    
    var = g_Sd_VabLoad_TargetVab->vabFileSize_4 - D_800C37CC;
    if (var < 0xC800)
    {
        CdRead(((var + 2047) / 2048), CD_ADDR_0, 128);
    }
    else
    {
        CdRead(25, CD_ADDR_0, 128);
    }
    
    g_Sd_AudioStreamingStates.vabLoadState_0 = 8;
}

void func_800480FC(void) // 0x800480FC
{
    s32 var0;
    u32 var1;

    if (CdReadSync(1, 0) != 0)
    {
        return;
    }

    var1 = g_Sd_VabLoad_TargetVab->vabFileSize_4 - D_800C37CC;
    if (var1 < 51200)
    {
        var0                                     = SdVabTransBodyPartly((u8*)CD_ADDR_0, var1, g_Sd_VabType);
        D_800C37CC                               = g_Sd_VabLoad_TargetVab->vabFileSize_4;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 9;
    }
    else
    {
        var0                                     = SdVabTransBodyPartly((u8*)CD_ADDR_0, 0xC800u, g_Sd_VabType);
        D_800C37CC                              += 0xC800;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 6;
    }

    if (var0 == NO_VALUE && g_Sd_VabLoadAttemps < 16)
    {
        g_Sd_VabLoadAttemps++;
        g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
    }
}

void Sd_VabLoad_Finalization(void) // 0x800481F8
{
    if (SdVabTransCompleted(0) != 1)
    {
        return;
    }

    g_Sd_AudioStreamingStates.vabLoadState_0 = 0;
    D_800C1658.cdErrorCount_0                = 0;
    D_800C1658.isVabLoading_15               = false;
    Sd_CmdPoolUpdate();
}

// ========================================
// LOAD VAB FILE FOR MUSIC
// ========================================

void Sd_BgmLoad_CmdSet(u16 songIdx) // 0x80048244
{
    if (D_800C1658.bgmLoadedSongIdx_6 == songIdx)
    {
        return;
    }

    if (D_800C1658.xaAudioIdx_4 != 0)
    {
        Sd_CmdPoolAdd(2);
    }

    Sd_StopBgmCmd();
    Sd_EngineCmd((u16)(songIdx + 173));
    Sd_CmdPoolAdd(songIdx);

    g_Sd_VabLoadAttemps           = 0;
    D_800C1658.bgmLoadedSongIdx_6 = songIdx;
    D_800C1658.isVabLoading_15    = true;
}

void Sd_BgmLoad(void) // 0x800482D8
{
    switch (g_Sd_AudioStreamingStates.vabLoadState_0)
    {
        case 0:
            g_Sd_BgmLoad_TargetVab                   = &D_800AA274[g_Sd_CmdPool[0]];
            g_Sd_VabType                             = g_Sd_BgmLoad_TargetVab->vabTypeIdx_0;
            g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
            break;
        
        case 1:
            Sd_StopSeq();
            break;
        
        case 2:
            Sd_BgmLoad_OffSet();
            break;
        
        case 3:
            Sd_BgmLoad_FileLoad();
            break;
        
        case 4:
            Sd_BgmLoad_LoadCheck();
            break;
        
        default:
            break;
    }
}

void Sd_StopSeq(void) // 0x8004839C
{
    Sd_StopBgmStep();
    SdSeqClose(g_Sd_VabType);

    g_Sd_AudioStreamingStates.vabLoadState_0 = 2;
}

void Sd_BgmLoad_OffSet(void) // 0x800483D4
{
    CdlLOC cdLoc;

    if (!Sd_CdPrimitiveCmdTry(CdlSetloc, (u8*)CdIntToPos(g_Sd_BgmLoad_TargetVab->vabFileOffset_8, &cdLoc), 0))
    {
        g_Sd_AudioStreamingStates.vabLoadState_0 = 3;
    }
}

void Sd_BgmLoad_FileLoad(void) // 0x80048424
{
    if (CdSync(1, 0) == 2)
    {
        CdRead((g_Sd_BgmLoad_TargetVab->vabFileSize_4 + 2047) / 2048, FS_BUFFER_1, 128);
        
        g_Sd_AudioStreamingStates.vabLoadState_0 = 4;
        D_800C1658.cdErrorCount_0                = 0;
    }

    D_800C1658.cdErrorCount_0++;
}

void Sd_BgmLoad_LoadCheck(void) // 0x80048498
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)FS_BUFFER_1;
        ptr0 = g_Sd_KdtBuffer[g_Sd_VabType];
        
        for (i = 0; i < g_Sd_BgmLoad_TargetVab->vabFileSize_4; i++)
        {
            *ptr0++ = *ptr1++;
        }

        i = SdSeqOpen(g_Sd_KdtBuffer[g_Sd_VabType], 3);
        
        if (i == NO_VALUE && g_Sd_VabLoadAttemps < 16)
        {
            g_Sd_VabLoadAttemps++;
            g_Sd_AudioStreamingStates.vabLoadState_0 = 1;
        }
        else
        {
            g_Sd_AudioStreamingStates.vabLoadState_0 = 0;
            D_800C1658.isVabLoading_15               = false;

            Sd_CmdPoolUpdate();
        }

        D_800C1658.cdErrorCount_0 = 0;
    }

    D_800C1658.cdErrorCount_0++;
}

void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4) {}

void func_800485B8(s32 arg0, u8 arg1, u32 arg2) {}

void func_800485C0(s32 idx) // 0x800485C0
{
    D_800C15F8[idx] = 0;
}

const s32 g_rodataPad_80025D38 = 0;