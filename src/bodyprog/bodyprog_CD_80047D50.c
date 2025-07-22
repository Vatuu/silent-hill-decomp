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
    Sd_EngineCmd((u16)(cmd + 0xAD));
    func_800478DC(cmd);

    D_800C37D0 = 0;
    D_800C1658.field_6 = cmd;
    D_800C1658.field_15 = 1;
}

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

// TODO: .rodata migration.
#ifdef NON_MATCHING
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

    D_800C37DD = D_800C16A8;
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
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_CD_80047D50", func_800485D8);
#endif

u8 func_80048954(s32 com, u8* param, u8* res) // 0x80048954
{
    u8 syncRes;
    u8 comCopy;
    
    comCopy = com;

    if (CdSync(1, &syncRes) == CdlComplete && CdControl(comCopy, param, res) != 0)
    {
        D_800C1658.field_0 = 0;
        return 0;
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

    return 1;
}
