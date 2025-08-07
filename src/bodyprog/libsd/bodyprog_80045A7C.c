#include "game.h"

#include <libcd.h>
#include <libetc.h>
#include <libspu.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

extern CdlLOC D_800C15E8;

/** This file could possibly be `sdmgr.c`, or
* at least starting from `sd_init` function it
* could be.
*/

void Sd_EngineCmd(u32 cmd) // 0x80045A7C
{
    // Execute sound command based on category.
    switch ((cmd >> 8) & 0xFF)
    {
        // Unknown. Range [0, 255].
        case 0:
            func_80045BD8(cmd);
            return;

        // Unknown. Range [300, 1279].
        case 3:
        case 4:
            func_80046A24(cmd);
            return;

        // Play SFX. Range [1280, 1791]. 511 possible values.
        case 5:
        case 6:
            Sd_PlaySfx(cmd, 0, 0);
            return;

        // Unknown. Range [1792, 2303].
        case 7:
        case 8:
            func_8004692C(cmd - 0x200);
            return;

        // Unknown. Range [2816, 3327].
        case 11:
        case 12:
            func_800468EC();
            return;

        // Unknown. Range [4096, 5887].
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

void func_80045BD8(u16 cmd) // 0x80045BD8
{
    switch (cmd)
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

    if (cmd >= 160 && cmd < 245)
    {
        func_80047B24(cmd);
    }

    if (cmd >= 32 && cmd < 72)
    {
        func_80048244(cmd);
    }
}

void func_80045D28(u8 caseArg) // 0x80045D28
{
    CdlATV vol;

    switch (caseArg)
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

    D_800C15F0.field_0 = CdlModeSpeed;
    func_80048954(CdlSetmode, &D_800C15F0.field_0, NULL);

    for(D_800C15B8 = 0; D_800C15B8 < 31; D_800C15B8++)
    {
        D_800C16A8[D_800C15B8] = 0;
    }

    for(D_800C15B8 = 0; D_800C15B8 < 24; D_800C15B8++)
    {
        D_800C15F8[D_800C15B8] = 0;
    }

    D_800C1658.field_6            = 0;
    D_800C1658.field_8[0]         = 0;
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

static inline void WriteVolume(s16* left, s16* right, s16 vol)
{
    *left  = vol;
    *right = vol;
}

u8 Sd_PlaySfx(u16 sfx, s8 arg1, u8 vol) // 0x80046048
{
    SpuVoiceAttr attr;
    s16          convertedVol;
    s16          volCpy;
    s32          i;

    if (sfx == Sfx_Base)
    {
        return NO_VALUE;
    }

    D_800C15BC = sfx - Sfx_Base;
    volCpy     = vol;

    // Copy key SFX data.
    D_800C1698.field_2 = D_800ACAA8[D_800C15BC].field_2 >> 8;
    D_800C1698.field_4 = D_800ACAA8[D_800C15BC].field_2 & 0xFF;
    D_800C1698.field_8 = D_800ACAA8[D_800C15BC].field_4;

    convertedVol = D_800C167C + D_800ACAA8[D_800C15BC].field_5;
    convertedVol = convertedVol - (convertedVol * volCpy) / 255;

    WriteVolume(&D_800C1698.volumeLeft_C, &D_800C1698.volumeRight_E, convertedVol);

    if (D_800C166A == 1)
    {
        if (arg1 < 0)
        {
            D_800C1698.volumeRight_E -= (D_800C1698.volumeLeft_C * ABS(arg1)) >> 7;
        }
        else
        {
            D_800C1698.volumeLeft_C -= (D_800C1698.volumeLeft_C * arg1) >> 7;
        }
    }

    if (D_800C1698.volumeLeft_C < 0)
    {
        D_800C1698.volumeLeft_C = 0;
    }

    if (D_800C1698.volumeRight_E < 0)
    {
        D_800C1698.volumeRight_E = 0;
    }

    if (sfx == Sfx_Unk1321)
    {
        D_800C1698.field_6 = D_800ACAA8[D_800C15BC].field_0;
        SdUtKeyOnV(22, D_800C1698.field_2, D_800C1698.field_4, D_800C1698.field_6, D_800C1698.field_8, 0,
                   Sd_GetVolSe(D_800C1698.volumeLeft_C), Sd_GetVolSe(D_800C1698.volumeRight_E));
        D_800C1698.field_0 = 22;
    }
    else if (sfx == Sfx_Unk1322)
    {
        D_800C1698.field_6 = D_800ACAA8[D_800C15BC].field_0;
        SdUtKeyOnV(23, D_800C1698.field_2, D_800C1698.field_4, D_800C1698.field_6, D_800C1698.field_8, 120,
                   Sd_GetVolSe(D_800C1698.volumeLeft_C), Sd_GetVolSe(D_800C1698.volumeRight_E));
        D_800C1698.field_0 = 23;
    }
    else
    {
        D_800C1698.field_0 = SdVoKeyOn(D_800ACAA8[D_800C15BC].field_2, D_800C1698.field_8 * 256,
                                       Sd_GetVolSe(D_800C1698.volumeLeft_C), Sd_GetVolSe(D_800C1698.volumeRight_E));
    }

    for (i = 0; i < 24; i++)
    {
        if (D_800C15F8[i] == sfx)
        {
            D_800C15F8[i] = 0;
        }
    }

    if (D_800C1698.field_0 < 24)
    {
        D_800C15F8[D_800C1698.field_0] = sfx;
        attr.voice = 1 << D_800C1698.field_0;

        SpuGetVoiceAttr(&attr);

        D_800C1628[D_800C1698.field_0] = attr.pitch;
        return D_800C1698.field_0;
    }

    return NO_VALUE;
}

void func_800463C0(u16 sfx, s8 arg1, u8 vol, s8 arg3) // 0x800463C0
{
    SpuVoiceAttr attr;
    s16          convertedVol;
    s32          temp;
    s32          i;

    if (sfx == Sfx_Base)
    {
        return;
    }

    D_800C15BE = sfx - Sfx_Base;
    D_800C16A4 = D_800C167C + D_800ACAA8[D_800C15BE].field_5;

    if (sfx == Sfx_Unk1321)
    {
        temp       = 22;
        attr.voice = 0x400000;
    }
    else if (sfx == Sfx_Unk1322)
    {
        temp       = 23;
        attr.voice = 0x800000;
    }
    else
    {
        temp = NO_VALUE;

        for (i = 0; i < 24; i++)
        {
            if (D_800C15F8[i] == sfx)
            {
                temp = i;
            }
        }

        if (temp < 0)
        {
            return;
        }

        attr.voice = 1 << temp;
    }

    D_800C1698.field_A = 0;
    D_800C1698.field_8 = D_800ACAA8[D_800C15BE].field_4;
    D_800C15C0         = D_800C1628[temp] + (arg3 * 2);
    convertedVol       = vol;
    convertedVol       = D_800C1698.volumeLeft_C - ((D_800C1698.volumeLeft_C * (convertedVol)) / 255);

    WriteVolume(&D_800C1698.volumeLeft_C, &D_800C1698.volumeRight_E, convertedVol);

    if (D_800C166A == 1)
    {
        if (arg1 < 0)
        {
            D_800C1698.volumeRight_E -= (convertedVol * ABS(arg1)) >> 7;
        }
        else
        {
            D_800C1698.volumeLeft_C -= (convertedVol * arg1) >> 7;
        }
    }

    SpuGetVoiceAttr(&attr);

    attr.mask          = 0x1F;
    attr.volmode.left  = 0;
    attr.volmode.right = 0;
    attr.volmode.left  = 0;
    attr.volmode.right = 0;

    if (D_800C1698.volumeLeft_C < 0)
    {
        D_800C1698.volumeLeft_C = 0;
    }

    if (D_800C1698.volumeRight_E < 0)
    {
        D_800C1698.volumeRight_E = 0;
    }

    attr.volume.right = Sd_GetVolSe(D_800C1698.volumeRight_E << 7);
    attr.volume.left  = Sd_GetVolSe(D_800C1698.volumeLeft_C << 7);
    attr.pitch        = D_800C15C0;

    SpuSetVoiceAttr(&attr);
}

void func_80046620(u16 sfx, s8 arg1, u8 vol, s8 arg3) // 0x80046620
{
    s16 temp;
    s16 convertedVol;

    if (sfx == Sfx_Base)
    {
        return;
    }

    D_800C15C2         = sfx - Sfx_Base;
    D_800C1698.field_2 = D_800ACAA8[D_800C15C2].field_2 >> 8;
    D_800C1698.field_4 = D_800ACAA8[D_800C15C2].field_2 & 0xFF;
    D_800C1698.field_6 = D_800ACAA8[D_800C15C2].field_0;
    D_800C1698.field_8 = D_800ACAA8[D_800C15C2].field_4 + (s8)(arg3 * 5 / 127);

    if (arg3 > 0)
    {
        D_800C1698.field_A = ABS(arg3 * 5) % 127;
    }
    else
    {
        D_800C1698.field_A = 0x7F - ABS(arg3 * 5) % 127;
    }

    temp                    = D_800C167C + D_800ACAA8[D_800C15C2].field_5;
    convertedVol            = vol;
    D_800C1698.volumeLeft_C = temp - (temp * convertedVol) / 255;

    WriteVolume(&D_800C1698.volumeLeft_C, &D_800C1698.volumeRight_E, D_800C1698.volumeLeft_C);

    if (D_800C166A == 1)
    {
        if (arg1 < 0)
        {
            D_800C1698.volumeRight_E -= (D_800C1698.volumeRight_E * ABS(arg1)) >> 7;
        }
        else
        {
            D_800C1698.volumeLeft_C -= (D_800C1698.volumeLeft_C * arg1) >> 7;
        }
    }

    if (D_800C1698.volumeLeft_C < 0)
    {
        D_800C1698.volumeLeft_C = 0;
    }

    if (D_800C1698.volumeRight_E < 0)
    {
        D_800C1698.volumeRight_E = 0;
    }

    D_800C1698.field_0 = SdUtKeyOn(D_800C1698.field_2, D_800C1698.field_4, D_800C1698.field_6, D_800C1698.field_8, D_800C1698.field_A,
                                   Sd_GetVolSe(D_800C1698.volumeLeft_C), Sd_GetVolSe(D_800C1698.volumeRight_E));
}

void func_800468EC() // 0x800468EC
{
    SdUtKeyOffV(23);
}

void func_8004690C(u16 sfx) // 0x8004690C
{
    func_8004692C(sfx);
}

void func_8004692C(u16 cmd) // 0x8004692C
{
    if (cmd == 0x500)
    {
        return;
    }

    D_800C15C4 = cmd - 0x500;
    D_800C15C6 = D_800ACAA8[D_800C15C4].field_2;
    D_800C15C8 = D_800ACAA8[D_800C15C4].field_4 << 8;
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

void func_80046A24(u16 cmd) // 0x80046A24
{
    if (D_800C1658.field_F.field_01 != cmd && D_800C1658.field_E != cmd)
    {
        D_800C1658.field_F.field_01 = cmd;
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

void func_80046B04() // 0x80046B04
{
    if (D_800C1678.volumeBgm_8 > 0)
    {
        D_800C1678.volumeBgm_8 -= 4;
    }

    if (D_800C1678.volumeBgm_8 <= 0)
    {
        D_800C1678.volumeBgm_8 = 0;
        func_80046B78();
        func_80047A70();
    }

    D_800C1678.field_6 = D_800C1678.volumeBgm_8;
    Sd_SetVolBgm(D_800C1678.field_6, D_800C1678.field_6);
}

void func_80046B78() // 0x80046B78
{
    Sd_SetVolBgm(0, 0);
    SdSeqStop(0);

    D_800C1658.field_14 = 0;
    D_800C1658.field_E = 0;
}

u8 func_80046BB4(u8 arg0) // 0x80046BB4
{
    u32 i;
    u8  ret;

    if (arg0 == 0)
    {
        return 0;
    }

    if (D_800C1658.field_E >= 809)
    {
        return 0;
    }

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        if (D_800AA604[(u8)D_800C1658.field_E][i] == arg0)
        {
            ret = SdGetMidiVol(0, i);
            break;
        }
    }

    return ret;
}

void func_80046C54(u8 arg0, u8 arg1) // 0x80046C54
{
    u32 i;
    s16 var0;
    u8  var1;
    u8  idx;

    if (arg0 == 0)
    {
        D_800C167E = (arg1 * 40) / 127;
    }
    else if (D_800C1658.field_E < 809)
    {
        idx = D_800C1658.field_E;

        for (i = 0; i < 15; i++)
        {
            var1 = D_800AA604[idx][i];
            var0  = arg1;

            if (var1 == arg0)
            {
                SdSetMidiVol(0, i, var0);
            }
        }
    }
}

void func_80046D3C(u16 cmd) // 0x80046D3C
{
    D_800C1658.field_2 = cmd & 0xFFF;

    if (D_800AA894[D_800C1658.field_2].field_0 != 0)
    {
        D_800C37DC         = 1;
        D_800C1688.field_8 = VSync(-1);
        D_800C1688.field_4 = 0;

        func_800478DC(2);

        D_800C1658.field_4 = D_800C1658.field_2;

        func_800478DC(1);
    }
}

s32 func_80046DCC(s32 idx) // 0x80046DCC
{
    return (D_800AA894[idx & 0xFFF].field_8 & 0xFFFFFF) + 32;
}

void func_80046E00() // 0x80046E00
{
    u32* temp_a1;
    u32* temp_v0;

    D_800C1658.field_0++;

    switch (D_800C1671)
    {
        case 0:
            if (D_800C1658.field_14 == 0)
            {
                D_800C167E = 24;
            }

            D_800C15CA = D_800C1658.field_2;
            switch (D_800C15CA)
            {
                case 0x35:
                case 0x38:
                case 0x254:
                case 0x255:
                case 0x256:
                case 0x258:
                case 0x25A:
                case 0x264:
                case 0x266:
                case 0x26C:
                case 0x291:
                case 0x25E:
                    D_800C167A = Sd_GetVolSe(84);
                    break;

                case 0x2D3:
                case 0x2D5:
                    D_800C167A = 50;
                    break;

                case 0x2D4:
                    D_800C167A = 40;
                    break;

                default:
                    D_800C167A = 84;
                    break;
            }

            D_800C1678.volumeXa_0 = D_800C1678.field_2;
            Sd_SetVolXa(D_800C1678.field_2, D_800C1678.field_2);
            D_800C15F0.field_0 = CdlModeSF | CdlModeRT | CdlModeSpeed;
            D_800C1671         = 1;
            break;

        case 1:
            if (!func_80048954(CdlSetmode, &D_800C15F0.field_0, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1671         = 2;
            }
            break;

        default:
            break;

        case 2:
            D_800C15F0.field_0 = D_800AA894[D_800C15CA].field_8_24;
            D_800C15F0.field_1 = D_800AA894[D_800C15CA].field_4_24;
            D_800C1671         = 3;
            break;

        case 3:
            if (!func_80048954(CdlSetfilter, &D_800C15F0.field_0, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1671         = 4;
            }
            break;

        case 4:
            // HACK: Needed for match, weird code.
            temp_a1     = g_FileXaLoc;
            temp_v0     = &temp_a1[D_800AA894[D_800C15CA].field_0];
            D_800C15CC  = *temp_v0;
            D_800C15CC += 0x96 + D_800AA894[D_800C15CA].field_4;

            D_800C1688.field_0 = D_800AA894[D_800C15CA].field_8 + 32;

            D_800C1671        = 5;
            D_800C15E8.sector = itob(D_800C15CC % 75);
            D_800C15CC       /= 75;
            D_800C15E8.second = itob(D_800C15CC % 60);
            D_800C15CC       /= 60;
            D_800C15E8.minute = itob(D_800C15CC);
            break;

        case 5:
            if (!func_80048954(CdlSeekL, (u8*)&D_800C15E8, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1671         = 6;
            }
            break;

        case 6:
            if (!func_80048954(CdlReadN, NULL, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C37DC         = 0;
                D_800C1671         = 7;
            }
            break;

        case 7:
            D_800C1658.field_4 = D_800C15CA;

            SdSetSerialAttr(0, 0, 1);
            D_800C1688.field_8 = VSync(-1);
            D_800C1688.field_4 = 0;
            D_800C1671         = 0;

            func_80047A70();
            D_800C1658.field_0  = 0;
            D_800C1658.field_16 = 0;
            break;
    }
}

void func_8004729C(u16 arg0) // 0x8004729C
{
    func_800472BC(arg0);
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

void func_80047308() // 0x80047308
{
    u32* temp_a1;
    u32* temp_v0;

    D_800C1658.field_0++;

    switch (D_800C1673)
    {
        case 0:
            D_800C15D0 = D_800C165A;
            Sd_SetVolXa(0, 0);
            D_800C15F0.field_0 = CdlModeSF | CdlModeRT | CdlModeSpeed;
            D_800C1673         = 1;
            break;

        case 1:
            if (!func_80048954(CdlSetmode, &D_800C15F0.field_0, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1673         = 2;
            }
            break;

        case 2:
            D_800C15F0.field_0 = D_800AA894[D_800C15D0].field_8_24;
            D_800C15F0.field_1 = D_800AA894[D_800C15D0].field_4_24;
            D_800C1673         = 3;
            return;

        case 3:
            if (!func_80048954(CdlSetfilter, &D_800C15F0.field_0, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1673         = 4;
            }
            break;

        case 4:
            // HACK: Needed for match, weird code.
            temp_a1     = g_FileXaLoc;
            temp_v0     = &temp_a1[D_800AA894[D_800C15D0].field_0];
            D_800C15D4  = *temp_v0;
            D_800C15D4 += 0x96 + D_800AA894[D_800C15D0].field_4;

            D_800C1688.field_0 = D_800AA894[D_800C15D0].field_8 + 0x20;

            D_800C1673        = 5;
            D_800C15E8.sector = itob(D_800C15D4 % 75);
            D_800C15D4       /= 75;
            D_800C15E8.second = itob(D_800C15D4 % 60);
            D_800C15D4       /= 60;
            D_800C15E8.minute = itob(D_800C15D4);
            break;

        case 5:
            if (!func_80048954(CdlSeekL, &D_800C15E8, NULL))
            {
                D_800C1658.field_0 = 0;
                D_800C1673         = 6;
            }
            break;

        case 6:
            if (!func_80048954(CdlPause, NULL, NULL))
            {
                D_800C1673 = 0;
                D_800C37DC = 0;
                func_80047A70();
                D_800C1658.field_0 = 0;
            }
            break;

        default:
            break;
    }
}

void func_8004760C() // 0x8004760C
{
    func_800478DC(2);
    D_800C166E = 1;
}

void func_80047634() // 0x80047634
{
    D_800C1658.field_F.field_0[3] = 1;

    switch (D_800C1670.field_2)
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
            if (!func_80048954(CdlPause, NULL, NULL))
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

            if (D_800C1658.field_14 == 0)
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

void func_800478DC(u8 cmd) // 0x800478DC
{
    if (cmd == 2)
    {
        for (D_800C15D8 = 1; D_800C15D8 < 30; D_800C15D8++)
        {
            if (D_800C16A8[D_800C15D8] == 1)
            {
                for (D_800C15DC = D_800C15D8; D_800C15DC < 30; D_800C15DC++)
                {
                    D_800C16A8[D_800C15DC] = D_800C16A8[D_800C15DC + 1];
                }

                D_800C16A8[31] = 0;
                D_800C37DC     = 0;
            }
        }
    }

    for (D_800C15D8 = 1; D_800C15D8 < 30; D_800C15D8++)
    {
        if (D_800C16A8[D_800C15D8] == cmd)
        {
            for (D_800C15DC = D_800C15D8; D_800C15DC < 30; D_800C15DC++)
            {
                D_800C16A8[D_800C15DC] = D_800C16A8[D_800C15DC + 1];
            }

            D_800C16A8[31] = 0;
        }
    }

    for (D_800C15D8 = 0; D_800C15D8 < 31; D_800C15D8++)
    {
        if (D_800C16A8[D_800C15D8] == 0)
        {
            D_800C16A8[D_800C15D8] = cmd;
            break;
        }
    }

    D_800C37DD = D_800C16A8[0];
}

void func_80047A70() // 0x80047A70
{
    if (D_800C16A8[0] != 0)
    {
        for (D_800C15E0 = 0; D_800C15E0 < 0x1F; D_800C15E0++)
        {
            D_800C16A8[D_800C15E0] = D_800C16A8[D_800C15E0 + 1];
        }

        D_800C16A8[0x1F] = 0;
    }
}

void Sd_SetReverbDepth(u8 depth) // 0x80047AD0
{
    s32 left;

    g_Sd_ReverbDepth = depth;

    left = depth;
    SdUtSetReverbDepth(left, left);
}

void Sd_SetReverbEnable(s32 mode) // 0x80047AFC
{
    SdSetSerialAttr(0, 1, mode);
}

void func_80047B24(s32 arg0) // 0x80047B24
{
    if (D_800C1658.field_4 != 0)
    {
        func_800478DC(2);
    }

    D_800C37D0 = 0;
    func_800478DC(arg0);
    D_800C1658.field_15 = 1;
}

void func_80047B80() // 0x80047B80
{
    u8 temp_a0;
    u8 var_a1;

    switch (D_800C1670.field_0)
    {
        case 0:
            var_a1     = D_800C16A8[0];
            D_800C37D4 = &D_800A986C[var_a1];
            D_800C37C8 = D_800C37D4->field_0;

            if (D_800C37C8)
            {
                if (D_800C1658.field_8[D_800C37C8 - 1] == var_a1)
                {
                    D_800C1670.field_0  = 0;
                    D_800C1658.field_15 = 0;
                    func_80047A70();
                    break;
                }

                D_800C1658.field_8[D_800C37C8 - 1] = var_a1;
            }

            if (var_a1 >= 170 && var_a1 <= 204)
            {
                temp_a0 = D_800AA5E0[var_a1 - 170];
                if (temp_a0 != g_Sd_ReverbDepth)
                {
                    Sd_SetReverbDepth(temp_a0);
                }
            }

            D_800C1670.field_0 = 1;
            break;

        case 1:
            func_80047D1C();
            break;

        case 2:
            func_80047D50();
            break;

        case 3:
            func_80047DB0();
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
            func_800481F8();
            break;

        default:
            break;
    }
}

void func_80047D1C() // 0x80047D1C
{
    D_800C37CC = 0;
    SdVabClose(D_800C37C8);
    D_800C1670.field_0 = 2;
}