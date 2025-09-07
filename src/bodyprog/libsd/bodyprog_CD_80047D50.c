#include "game.h"

#include <libcd.h>
#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

#define CD_ERROR_LIMIT 600 // Matches value used in beatmania `FSCD.C`.

/**
* Either this file contain more file to split
* Or this file is related to audio load from CD.
* It is more probable to be the second option.
*/

static u8* D_800A9FC8[4] =
{
    (u8*)0x801FE460,
    (u8*)0x801FD840,
    (u8*)0x801FC220,
    (u8*)0x801FA600
};

static u8* D_800A9FD8[1] =
{
    (u8*)0x801F5600,
};

static s32 D_800A9FDC[166] =
{
    0x00001010, 0x00021490, 0x00027630, 0x00058F50, 0x10200000, 0x00021410, 0x0000008C, 0x0C200002,
    0x00035B80, 0x0000021B, 0x0C200002, 0x00020FA0, 0x00006295, 0x0C200001, 0x00006BF0, 0x000061D5,
    0x0C200001, 0x00005690, 0x000062D7, 0x0C200001, 0x00005ED0, 0x0000639C, 0x0C200001, 0x00004450,
    0x0000725B, 0x0C200001, 0x00006A20, 0x000072AE, 0x0C200001, 0x00006B20, 0x00007310, 0x0C200001,
    0x00006860, 0x00007302, 0x12200002, 0x00021EB0, 0x00006FB1, 0x10200002, 0x00031910, 0x00006584,
    0x14200002, 0x00029290, 0x00006FF5, 0x14200002, 0x0002F370, 0x00007048, 0x16200002, 0x00029860,
    0x000070A7, 0x16200002, 0x0002DD80, 0x000070FB, 0x0C200002, 0x0002D060, 0x000067BF, 0x12200002,
    0x0001C430, 0x0000681A, 0x12200002, 0x00032970, 0x00006853, 0x12200002, 0x0002DF90, 0x000068B9,
    0x0C200002, 0x000031C0, 0x00006915, 0x14200002, 0x0002E9E0, 0x0000691C, 0x14200002, 0x00032310,
    0x0000697A, 0x14200002, 0x000303B0, 0x000069DF, 0x14200002, 0x000325E0, 0x00006A40, 0x14200002,
    0x00032CF0, 0x00006AA5, 0x0C200002, 0x00017750, 0x00006B0B, 0x0C200002, 0x00016750, 0x00006B3A,
    0x12200002, 0x000259C0, 0x00006B67, 0x0C200002, 0x000284A0, 0x00006BB3, 0x12200002, 0x00032B40,
    0x00006C04, 0x14200002, 0x000254C0, 0x00006C6A, 0x12200002, 0x00021340, 0x00006CB5, 0x12200002,
    0x0000A510, 0x00007157, 0x0C200002, 0x00007BB0, 0x00006D12, 0x12200002, 0x00032510, 0x00006D22,
    0x0E200002, 0x0000C640, 0x00006D87, 0x0E200002, 0x00010760, 0x00006DA0, 0x12200002, 0x00027580,
    0x00006DC1, 0x14200002, 0x000305F0, 0x0000716C, 0x0C200002, 0x00006230, 0x00006E76, 0x12200002,
    0x000328B0, 0x00006E83, 0x14200002, 0x00032420, 0x00006EE9, 0x10200002, 0x00031030, 0x00006F4E,
    0x12200002, 0x000311F0, 0x000065E8, 0x18200003, 0x0001CC20, 0x0000603A, 0x1C200003, 0x0001CB90,
    0x0000607E, 0x18200003, 0x00023060, 0x000060BD, 0x14200003, 0x00018090, 0x00006106, 0x16200003,
    0x00021740, 0x00006138, 0x10200003, 0x00021D80, 0x0000617C, 0x0C200003, 0x00009FE0, 0x000061C1,
    0x14200003, 0x0000A410, 0x000061E6, 0x10200003, 0x000144C0, 0x000061FC
};

void func_80047D50() // 0x80047D50
{
    CdlLOC sp10;

    if (!func_80048954(CdlSetloc, (u8*)CdIntToPos(D_800C37D4->field_8 + (D_800C37CC >> 11), &sp10), 0))
    {
        D_800C1670.field_0 = 3;
    }
}

void func_80047DB0() // 0x80047DB0
{
    if (CdSync(1, 0) == 2)
    {
        if (D_800C37D4->field_4 < 51200)
        {
            CdRead((D_800C37D4->field_4 + 2047) / 2048, CD_ADDR_0, 128);
        }
        else
        {
            CdRead(25, CD_ADDR_0, 128);
        }

        if (D_800C1670.field_0)
        {
            char unk = -unk;
        }

        D_800C1670.field_0 = 4;
        D_800C1658.field_0 = 0;
    }

    D_800C1658.field_0++;
}

void func_80047E3C() // 0x80047E3C
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)CD_ADDR_0;
        ptr0 = D_800A9FC8[D_800C37C8];

        for (i = 0; i < D_800C37D4->field_2; i++) 
        {
            *ptr0++ = *ptr1++;
        }

        SdVabOpenHeadSticky(D_800A9FC8[D_800C37C8], D_800C37C8, D_800A9FDC[D_800C37C8]);
        D_800C1670.field_0 = 5;
    }

    D_800C1658.field_0++;
}

void func_80047F18() // 0x80047F18
{
    s32 var;
    s32* ptr;

    if (D_800C37D4->field_4 < 51200)
    {
        var = SdVabTransBody((u8*)CD_ADDR_0 + D_800C37D4->field_2, D_800C37C8);
        ptr = &D_800C37D4->field_4;

        D_800C37CC = *ptr;
        D_800C1670.field_0 = 9;
    }
    else
    {
        var = SdVabTransBodyPartly((u8*)CD_ADDR_0 + D_800C37D4->field_2, 0xC800 - D_800C37D4->field_2, D_800C37C8);

        D_800C37CC = 0xC800;
        D_800C1670.field_0 = 6;
    }
    
    if (var == NO_VALUE && D_800C37D0 < 16)
    {
        D_800C37D0++;
        D_800C1670.field_0 = 1;
    }
}

void func_80048000() // 0x80048000
{
    s32 i;
    CdlLOC  cdLocArg;
    CdlLOC* cdLocRes;

    if (SdVabTransCompleted(0) == 1)
    {
        i = D_800C37D4->field_8 + ((D_800C37CC + 0x7FF) >> 11);
        cdLocRes = CdIntToPos(i, &cdLocArg);

        if (!func_80048954(CdlSetloc, (u8*)cdLocRes, 0))
        {
            D_800C1670.field_0 = 7;
        }
    }
}

void func_8004807C() // 0x8004807C
{
    u32 var;

    if (CdSync(1, 0) != 2)
    {
        return;
    }
    
    var = D_800C37D4->field_4 - D_800C37CC;
    if (var < 51200)
    {
        CdRead(((var + 2047) / 2048), CD_ADDR_0, 128);
    }
    else
    {
        CdRead(25, CD_ADDR_0, 128);
    }
    
    D_800C1670.field_0 = 8;
}

void func_800480FC() // 0x800480FC
{
    s32 var0;
    u32 var1;

    if (CdReadSync(1, 0) != 0)
    {
        return;
    }

    var1 = D_800C37D4->field_4 - D_800C37CC;
    if (var1 < 51200)
    {
        var0 = SdVabTransBodyPartly((u8*)CD_ADDR_0, var1, D_800C37C8);
        D_800C37CC = D_800C37D4->field_4;
        D_800C1670.field_0 = 9;
    }
    else
    {
        var0 = SdVabTransBodyPartly((u8*)CD_ADDR_0, 0xC800u, D_800C37C8);
        D_800C37CC += 0xC800;
        D_800C1670.field_0 = 6;
    }

    if (var0 == NO_VALUE && D_800C37D0 < 16)
    {
        D_800C37D0++;
        D_800C1670.field_0 = 1;
    }
}

void func_800481F8() // 0x800481F8
{
    if (SdVabTransCompleted(0) != 1)
    {
        return;
    }

    D_800C1670.field_0 = 0;
    D_800C1658.field_0 = 0;
    D_800C1658.field_15 = 0;
    func_80047A70();
}

void func_80048244(u16 cmd) // 0x80048244
{
    if (D_800C1658.field_6 == cmd)
    {
        return;
    }

    if (D_800C1658.field_4 != 0)
    {
        func_800478DC(2);
    }

    func_80046AD8();
    Sd_EngineCmd((u16)(cmd + 173)); // 173 must be some base value for a command category.
    func_800478DC(cmd);

    D_800C37D0          = 0;
    D_800C1658.field_6  = cmd;
    D_800C1658.field_15 = 1;
}

static s_800C37D4 D_800AA274[73] =
{
    { 3, 0, 4640, 86848,  25126 },
    { 3, 0, 6176, 133680, 25171 },
    { 3, 0, 5664, 141408, 25318 },
    { 3, 0, 4640, 122704, 25389 },
    { 3, 0, 4128, 60192,  25450 },
    { 3, 0, 3616, 37712,  25481 },
    { 3, 0, 5664, 97392,  25513 },
    { 3, 0, 5152, 114992, 25562 },
    { 3, 0, 5664, 128256, 25621 },
    { 3, 0, 4128, 73648,  25685 },
    { 3, 0, 6176, 137600, 25722 },
    { 3, 0, 4640, 139712, 25791 },
    { 3, 0, 4640, 106288, 25863 },
    { 3, 0, 5152, 140400, 29136 },
    { 3, 0, 4128, 80144,  29207 },
    { 3, 0, 4128, 54336,  29248 },
    { 3, 0, 4640, 129968, 29285 },
    { 3, 0, 3104, 15168,  29350 },
    { 3, 0, 5152, 140672, 29373 },
    { 3, 0, 5152, 61344,  29475 },
    { 3, 0, 5152, 61344,  29507 },
    { 3, 0, 4128, 90096,  29538 },
    { 3, 0, 4128, 134656, 29583 },
    { 3, 0, 4640, 63376,  29651 },
    { 3, 0, 5152, 109056, 29683 },
    { 3, 0, 5152, 97840,  29739 },
    { 3, 0, 5152, 137568, 29788 },
    { 3, 0, 5152, 147936, 29858 },
    { 3, 0, 4640, 94400,  29934 },
    { 3, 0, 5152, 137296, 29983 },
    { 3, 0, 6688, 153152, 30057 },
    {}, // Might be a new table but I don't see a reference to this address anywhere.
    { 0, 0, 0,    3236,   24632 },
    { 0, 0, 0,    19340,  24692 },
    { 0, 0, 0,    9576,   24760 },
    { 0, 0, 0,    4040,   24836 },
    { 0, 0, 0,    1776,   24887 },
    { 0, 0, 0,    1304,   24955 },
    { 0, 0, 0,    596,    25024 },
    { 0, 0, 0,    4500,   25059 },
    { 0, 0, 0,    300,    25083 },
    { 0, 0, 0,    532,    25125 },
    { 0, 0, 0,    3728,   25169 },
    { 0, 0, 0,    6492,   25314 },
    { 0, 0, 0,    1344,   25388 },
    { 0, 0, 0,    896,    25449 },
    { 0, 0, 0,    196,    25480 },
    { 0, 0, 0,    1256,   25512 },
    { 0, 0, 0,    1892,   25561 },
    { 0, 0, 0,    2560,   25619 },
    { 0, 0, 0,    732,    25684 },
    { 0, 0, 0,    1860,   25721 },
    { 0, 0, 0,    1176,   25790 },
    { 0, 0, 0,    6000,   25860 },
    { 0, 0, 0,    5476,   29133 },
    { 0, 0, 0,    3952,   29205 },
    { 0, 0, 0,    808,    29247 },
    { 0, 0, 0,    1820,   29284 },
    { 0, 0, 0,    676,    29349 },
    { 0, 0, 0,    716,    29372 },
    { 0, 0, 0,    8220,   29470 },
    { 0, 0, 0,    2448,   29505 },
    { 0, 0, 0,    832,    29537 },
    { 0, 0, 0,    172,    29582 },
    { 0, 0, 0,    2720,   29649 },
    { 0, 0, 0,    1688,   29682 },
    { 0, 0, 0,    3128,   29737 },
    { 0, 0, 0,    1348,   29787 },
    { 0, 0, 0,    2324,   29856 },
    { 0, 0, 0,    4436,   29931 },
    { 0, 0, 0,    2496,   29981 },
    { 0, 0, 0,    11372,  30051 },
    {}
};
void func_800482D8() // 0x800482D8
{
    switch (D_800C1670.field_0)
    {
        case 0:
            D_800C37D8 = &D_800AA274[D_800C16A8[0]];
            D_800C37C8 = D_800C37D8->field_0;
            D_800C1670.field_0 = 1;
            break;
        
        case 1:
            Sd_StopSeq();
            break;
        
        case 2:
            func_800483D4();
            break;
        
        case 3:
            func_80048424();
            break;
        
        case 4:
            func_80048498();
            break;
        
        default:
            break;
    }
}

void Sd_StopSeq() // 0x8004839C
{
    func_80046B78();
    SdSeqClose(D_800C37C8);

    D_800C1670.field_0 = 2;
}

void func_800483D4() // 0x800483D4
{
    CdlLOC cdLoc;

    if (!func_80048954(CdlSetloc, (u8*)CdIntToPos(D_800C37D8->field_8, &cdLoc), 0))
    {
        D_800C1670.field_0 = 3;
    }
}

void func_80048424() // 0x80048424
{
    if (CdSync(1, 0) == 2)
    {
        CdRead((D_800C37D8->field_4 + 2047) / 2048, FS_BUFFER_1, 128);
        
        D_800C1670.field_0 = 4;
        D_800C1658.field_0 = 0;
    }

    D_800C1658.field_0++;
}

void func_80048498() // 0x80048498
{
    s32 i;
    u8* ptr0;
    u8* ptr1;

    if (CdReadSync(1, NULL) == 0)
    {
        ptr1 = (u8*)FS_BUFFER_1;
        ptr0 = D_800A9FD8[D_800C37C8];
        
        for (i = 0; i < D_800C37D8->field_4; i++)
        {
            *ptr0++ = *ptr1++;
        }

        i = SdSeqOpen(D_800A9FD8[D_800C37C8], 3);
        
        if (i == NO_VALUE && D_800C37D0 < 16)
        {
            D_800C37D0++;
            D_800C1670.field_0 = 1;
        }
        else
        {
            D_800C1670.field_0 = 0;
            D_800C166D         = 0;

            func_80047A70();
        }

        D_800C1658.field_0 = 0;
    }

    D_800C1658.field_0++;
}

void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4) {}

void func_800485B8(s32 arg0, u8 arg1, u32 arg2) {}

void func_800485C0(s32 idx) // 0x800485C0
{
    D_800C15F8[idx] = 0;
}

const s32 g_rodataPad_80025D38 = 0;

void func_800485D8() // 0x800485D8
{
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 var_a0;
    s16 var_a1;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v1;

    D_800C37DD = D_800C16A8[0];
    switch (D_800C37DD)
    {
        case 0:
            break;

        case 1:
            func_80046E00();
            break;

        case 2:
            func_80047634();
            break;

        case 6:
            func_80047308();
            break;

        case 7:
            func_80046A70();
            break;

        case 8:
            func_80046B04();
            break;

        default:
            if (D_800C37DD >= 160)
            {
                func_80047B80();
            }
            else if (D_800C37DD >= 32)
            {
                func_800482D8();
            }
            else
            {
                func_80047A70();
            }
            break;
    }

    if (D_800C1658.field_4 != 0)
    {
        D_800C1688.field_4 = VSync(-1) - D_800C1688.field_8;
    }

    if (D_800C1658.field_14 != 0)
    {
        D_800C1658.field_E = 0xFFFF;

        if (D_800C1678.volumeBgm_8 <= 0)
        {
            D_800C1678.volumeBgm_8 = 0;
            func_80046B78(&D_800C1678);
        }
        else
        {
            D_800C1678.volumeBgm_8 -= D_800C1658.field_14;

            if ((D_800C1678.volumeBgm_8 << 16) <= 0)
            {
                D_800C1678.volumeBgm_8 = 0;
                func_80046B78(&D_800C1678);
            }
        }

        D_800C1678.field_6 = D_800C1678.volumeBgm_8;
        
        Sd_SetVolBgm(D_800C1678.volumeBgm_8, D_800C1678.volumeBgm_8);
    }
    else if (D_800C1678.field_6 != D_800C1678.volumeBgm_8)
    {
        if (D_800C1678.volumeBgm_8 < D_800C1678.field_6)
        {
            D_800C1678.volumeBgm_8++;
            if (ABS(D_800C1678.volumeBgm_8 - D_800C1678.field_6) < 2) 
            {
                D_800C1678.volumeBgm_8 = D_800C1678.field_6;
            }
        }
        else
        {
            D_800C1678.volumeBgm_8--;
            if (ABS(D_800C1678.volumeBgm_8 - D_800C1678.field_6) < 2) 
            {
                D_800C1678.volumeBgm_8 = D_800C1678.field_6;
            }
        }

        Sd_SetVolBgm(D_800C1680, D_800C1680);
    }

    if ((u32)D_800C1688.field_4 > (u32)D_800C1688.field_0)
    {
        if (D_800C37DD == 0)
        {
            if (D_800C166E == 0)
            {
                func_800478DC(2);
            }

            D_800C1688.field_8 = VSync(-1);
            D_800C1688.field_4 = 0;
        }
    }

    if (D_800C166F == 1)
    {
        if (D_800C1678.field_A > 0)
        {
            D_800C1678.field_A -= 8;
            if ((D_800C1678.field_A << 16) <= 0)
            {
                D_800C1678.field_A = 0;
            }
            
            SdSetMVol(D_800C1678.field_A, D_800C1678.field_A);
        }
    }
    else
    {
        if (D_800C1678.field_A < (OPT_SOUND_VOLUME_MAX - 1))
        {
            D_800C1678.field_A += 4;
            if (D_800C1678.field_A >= (OPT_SOUND_VOLUME_MAX - 1))
            {
                D_800C1678.field_A = OPT_SOUND_VOLUME_MAX - 1;
            }
            
            SdSetMVol(D_800C1678.field_A, D_800C1678.field_A);
        }
    }

    if (D_800C1658.field_0 > 600)
    {
        CdReset(0);
        CdControlB(1, 0, 0);
        if (D_800C1670.field_0 != 0)
        {
            D_800C1670.field_0 = 1;
        }
        
        D_800C1670.field_1 = 0;
        D_800C1670.field_2 = 0;
        D_800C1670.field_3 = 0;
        D_800C1658.field_0 = 0;
    }
}

u8 func_80048954(s32 com, u8* param, u8* res) // 0x80048954
{
    u8 syncRes;
    u8 comCopy;
    
    comCopy = com;

    if (CdSync(1, &syncRes) == CdlComplete && CdControl(comCopy, param, res) != 0)
    {
        D_800C1658.field_0 = 0;
        return false;
    }

    D_800C1658.field_0++;

    if (D_800C1658.field_0 > CD_ERROR_LIMIT)
    {
        CdReset(0);
        CdControlB(1, 0, 0);
        VSync(3);
        
        if (D_800C1670.field_0 != 0)
        {
            D_800C1670.field_0 = 1;
        }
        
        D_800C1670.field_1 = 0;
        D_800C1670.field_2 = 0;
        D_800C1670.field_3 = 0;
        D_800C1658.field_0 = 0;
    }

    return true;
}

const s32 unused_Rodata_80025D60[2] = { 0x6A375A00, 0x892FBD00 }; // Unused.
