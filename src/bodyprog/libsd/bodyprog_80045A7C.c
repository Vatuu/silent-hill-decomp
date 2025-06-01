#include "game.h"

#include <libcd.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

/** This file could possibly be `sdmgr.c` or
* at least starting from `sd_init` function it
* could be.
*/

void Sd_EngineCmd(u32 cmd) // 0x80045A7C
{
    switch ((cmd >> 8) & 0xFF)
    {
        case 0:
            func_80045BD8(cmd);
            return;

        case 3:
        case 4:
            func_80046A24(cmd);
            return;

        case 5:
        case 6:
            func_80046048(cmd, 0, 0);
            return;

        case 7:
        case 8:
            func_8004692C((cmd - 0x200));
            return;

        case 11:
        case 12:
            func_800468EC();
            return;

        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            func_80046D3C(cmd);

        default:
            return;
    }
}

u8 func_80045B28() // 0x80045B28
{
    u8 var;

    var = 1;
    if (D_800C1658.field_4 != 0)
    {
        return var;
    }

    var = 2;
    if (D_800C1658.field_15 == 0)
    {
        if (D_800C1673 != 0)
        {
            D_800C1688.field_8 = VSync(-1);
            D_800C1688.field_4 = 0;
            return 3;
        }

        if (D_800C37DC == 0)
        {
            if (D_800C37DD == 0)
            {
                return 0;
            }

            var = 5;
            return var;
        }

        var = 4;
        return var;
    }

    return var;
}

u16 func_80045BC8() // 0x80045BC8
{
    return D_800C1666;
}

void func_80045BD8(u16 caseArg) // 0x80045BD8
{
    switch (caseArg)
    {
        case 1:
            func_80045D28(0);
            break;

        case 2:
            func_80045D28(1);
            break;

        case 16:
            func_800469AC();
            func_800468EC();
            break;

        case 17:
            func_800469E8();
            func_800468EC();
            break;

        case 18:
            func_80046AD8();
            break;

        case 21:
            func_800469E8();

        case 20:
            func_800469AC();
            func_800468EC();
            func_80046AD8();

        case 19:
            func_8004760C();
            break;

        case 22:
            D_800C166C = 1;

        default:
            break;

        case 23:
            D_800C166C = 2;
            break;

        case 3:
            D_800C166F = 1;
            break;

        case 4:
            D_800C166F = 0;
            break;
    }

    if (caseArg >= 160 && caseArg < 245)
    {
        func_80047B24(caseArg);
    }

    if (caseArg >= 32 && caseArg < 72)
    {
        func_80048244(caseArg);
    }
}

void func_80045D28(s32 caseArg) // 0x80045D28
{
    CdlATV vol;

    switch (caseArg & 0xFF)
    {
        case 0:
            SdSetMono();

            vol.val0 = vol.val2 = 0x4F; // spu (L)
            vol.val1 = vol.val3 = 0x4F; // spu (R)
            CdMix(&vol);

            D_800C167C = 0x7F;
            D_800C166A = 0;
            return;

        case 1:
            SdSetStereo();

            vol.val0 = vol.val2 = 0x7F; // spu (L)
            vol.val1 = vol.val3 = 0;    // spu (R)
            CdMix(&vol);

            D_800C167C = 0x7F;
            D_800C166A = 1;
            return;

        default:
            break;
    }
}

void sd_init() // 0x80045DD4
{
    SdInit();
    SdSetTickMode(1);
    func_80045D28(1);
    SdSetReservedVoice(24);
    SdStart();
    SdSetTableSize(&D_800C16C8, 16, 3);

    D_800C1678.field_C = OPT_SOUND_VOLUME_MAX - 1;
    D_800C1678.field_D = OPT_SOUND_VOLUME_MAX - 1;
    D_800C1678.field_E = OPT_SOUND_VOLUME_MAX - 1;

    sd_work_init();
}

void sd_work_init() // 0x80045E44
{
    SdSetAutoKeyOffMode(0);
    SdUtSetReverbType(1);
    SpuClearReverbWorkArea(1);
    SdUtReverbOn();
    SpuSetTransferMode(0);

    g_Sd_ReverbDepth = 20;

    SdUtSetReverbDepth(20, 20);
    Sd_SetReverbEnable(0);
    SdSetSerialAttr(0, 0, 0);
    Sd_SetVolXa(0, 0);

    D_800C15F0 = 128;
    func_80048954(14, &D_800C15F0, NULL);

    for(D_800C15B8 = 0; D_800C15B8 < 31; D_800C15B8++)
    {
        D_800C16A8[D_800C15B8] = 0;
    }

    for(D_800C15B8 = 0; D_800C15B8 < 24; D_800C15B8++)
    {
        D_800C15F8[D_800C15B8] = 0;
    }

    D_800C1658.field_6            = 0;
    D_800C1658.field_8            = 0;
    D_800C1658.field_A            = 0;
    D_800C1658.field_C            = 0;
    D_800C1658.field_4            = 0;
    D_800C1658.field_F.field_0[3] = 0;
    D_800C1658.field_0            = 0;
    D_800C1658.field_14           = 0;
    D_800C1658.field_15           = 0;
    D_800C1658.field_16           = 0;
    D_800C1658.field_17           = 0;
    D_800C1678.field_A            = 127;

    SdSetMVol(127, 127);

    D_800C37DC                  = 0;
    D_800C1658.field_E          = 0;
    D_800C1658.field_F.field_01 = 0;
    D_800C1670.field_0          = 0;
    D_800C1670.field_1          = 0;
    D_800C1670.field_2          = 0;
    D_800C1670.field_3          = 0;
    D_800C1678.volumeXa_0       = 84;
    D_800C1678.volumeBgm_8      = 40;
    D_800C1678.field_6          = 40;

    Sd_SetVolBgm(40, 40);
}

void func_80045FF8() // 0x80045FF8
{
    s32 i;
    
    SdSeqClose(0);
    
    for (i = 4; i >= 0; i--)
    {
        SdVabClose(i);
    }
    
    SdEnd();
    SdQuit();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_800463C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046620);

void func_800468EC() // 0x800468EC
{
    SdUtKeyOffV(23);
}

void func_8004690C(s32 arg0) // 0x8004690C
{
    func_8004692C(arg0);
}

void func_8004692C(u16 arg0) // 0x8004692C
{
    if (arg0 == 0x500)
    {
        return;
    }

    D_800C15C4 = arg0 - 0x500;
    D_800C15C6 = D_800ACAA8[D_800C15C4].field_2;
    D_800C15C8 = (D_800ACAA8[D_800C15C4].field_4 & 0xFF) << 8;
    SdVoKeyOff(D_800C15C6, D_800C15C8);
}

void func_800469AC() // 0x800469AC
{
    s32 i;

    for (i = 0; i < 24; i++)
    {
        SdUtKeyOffV(i);
    }
}

void func_800469E8() // 0x800469E8
{
    s32 i;

    for (i = 0; i < 24; i++)
    {
        SdUtKeyOffVWithRROff(i);
    }
}

void func_80046A24(u16 arg0) // 0x80046A24
{
    s32 temp = arg0 & 0xFFFF;

    if (D_800C1658.field_F.field_01 != temp && D_800C1658.field_E != temp)
    {
        D_800C1658.field_F.field_01 = arg0;
        func_800478DC(7);
    }
}

void func_80046A70() // 0x80046A70
{
    u16 prevVal;

    prevVal                     = D_800C1658.field_F.field_01;
    D_800C1658.field_14         = 0;
    D_800C1658.field_F.field_01 = 0;
    D_800C1658.field_E          = prevVal;

    SdSeqPlay(0, 1, 0);

    D_800C1678.field_6     = 40;
    D_800C1678.volumeBgm_8 = 40;

    Sd_SetVolBgm(40, 40);
    func_80047A70();
}

void func_80046AD8() // 0x80046AD8
{
    D_800C1666 = 0xFFFF;
    func_800478DC(8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046B04);

void func_80046B78() // 0x80046B78
{
    Sd_SetVolBgm(0, 0);
    SdSeqStop(0);

    D_800C1658.field_14 = 0;
    D_800C1658.field_E = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046BB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046C54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046D3C);

s32 func_80046DCC(s32 idx) // 0x80046DCC
{
    return (D_800AA894[idx & 0xFFF].field_8 & 0xFFFFFF) + 32;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80046E00);

void func_8004729C(u16 arg0) // 0x8004729C
{
    func_800472BC(arg0 & 0xFFFF);
}

void func_800472BC(s32 arg0) // 0x800472BC
{
    D_800C1658.field_2 = arg0 & 0xFFF;
    D_800C37DC = 1;

    if (D_800C1658.field_4 != 0)
    {
        func_800478DC(2);
    }

    func_800478DC(6);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80047308);

void func_8004760C() // 0x8004760C
{
    func_800478DC(2);
    D_800C166E = 1;
}

void func_80047634() // 0x80047634
{
    D_800C1658.field_F.field_0[3] = 1;

    switch ((u8)D_800C1670.field_2)
    {
        case 0:
            Sd_SetVolXa(D_800C1678.volumeXa_0, D_800C1678.volumeXa_0);
            D_800C1678.volumeXa_0 = D_800C1678.volumeXa_0 - 24;
            D_800C1678.field_2    = D_800C1678.volumeXa_0;

            if (D_800C1678.volumeXa_0 < 2)
            {
                D_800C1670.field_2 = 1;
            }
            break;

        case 1:
            D_800C1678.volumeXa_0 = 0;
            D_800C1678.field_2 = 0;

            Sd_SetVolXa(0, 0);
            SdSetSerialAttr(0, 0, 0);

            D_800C1670.field_2 = 2;
            break;

        case 2:
            if (!(func_80048954(9, NULL, NULL) & 0xFF))
            {
                D_800C1658.field_0 = 0;
                D_800C1670.field_2 = 3;
            }

            D_800C1658.field_0++;
            break;

        case 3:
            D_800C1658.field_F.field_0[3] = 0;
            D_800C1658.field_4            = 0;
            D_800C1670.field_2            = 0;

            if ((u8)D_800C1658.field_14 == 0)
            {
                D_800C167E = 0x28;
            }

            func_80047A70(&D_800C1658);
            D_800C1658.field_0 = 0;
            break;

        default:
            break;
    }
}

void Sd_SetVolume(u8 arg0, s16 arg1, u8 arg2) // 0x80047798
{
    D_800C1678.field_E = arg0;
    D_800C1678.field_D = arg1;
    D_800C1678.field_C = arg2;
    
    if (D_800C1658.field_E != 0)
    {
        Sd_SetVolBgm(D_800C1678.volumeBgm_8, D_800C1678.volumeBgm_8);
    }
    
    if (D_800C1658.field_4 != 0)
    {
        Sd_SetVolXa(D_800C1678.volumeXa_0, D_800C1678.volumeXa_0);
    }
}

void Sd_SetVolBgm(s16 volLeft, s16 volRight) // 0x80047808
{
    SdSeqSetVol(0, (volLeft * g_Sd_VolumeBgm) >> 7, (volRight * g_Sd_VolumeBgm) >> 7);
}

void Sd_SetVolXa(s16 volLeft, s16 volRight) // 0x80047860
{
    SdSetSerialVol(0, (volLeft * g_Sd_VolumeXa) >> 7, (volRight * g_Sd_VolumeXa) >> 7);
}

s16 Sd_GetVolSe(s16 arg0) // 0x800478B8
{
    return (arg0 * g_Sd_VolumeSe) >> 7;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_800478DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80047A70);

void Sd_SetReverbDepth(s8 depth)
{
    s32 left;

    g_Sd_ReverbDepth = depth;

    left = depth & 0xFF;
    SdUtSetReverbDepth(left, left);
}

void Sd_SetReverbEnable(s32 mode)
{
    SdSetSerialAttr(0, 1, mode & 0xFF);
}

void func_80047B24(s32 arg0) // 0x80047B24
{
    if (D_800C1658.field_4 != 0)
    {
        func_800478DC(2);
    }

    D_800C37D0 = 0;
    func_800478DC(arg0 & 0xFF);
    D_800C1658.field_15 = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/bodyprog_80045A7C", func_80047B80);

void func_80047D1C() // 0x80047D1C
{
    D_800C37CC = 0;
    SdVabClose(D_800C37C8);
    D_800C1670.field_0 = 2;
}