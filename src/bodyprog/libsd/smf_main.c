#include "common.h"

#include <libapi.h>

#include "bodyprog/libsd.h"

s32 sd_interrupt_start_flag = 0;
s16 sd_keyoff_mode = 0;
// 2 bytes of padding.
s32 sd_mono_st_flag = 0;
s32 sd_reverb_mode = 0;
u32 body_partly_size = 0;
s32 sd_reverb_area_size[10] =
{
    0x00000080, 0x000026C0, 0x00001F40, 0x00004840, 0x00006FE0,
    0x0000ADE0, 0x0000F6C0, 0x00018040, 0x00018040, 0x00003C00
};

u32 _spu_rev_param[172] =
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x005B007D, 0x54B86D80, 0x0000BED0, 0xBA800000, 0x53005800, 0x033304D6,
    0x022703F0, 0x01EF0374, 0x01B50334, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x013601B4,
    0x005C00B8, 0x80008000, 0x00000000, 0x00250033, 0x4FA870F0, 0x4410BCE0, 0x9C00C0F0, 0x4EC05280,
    0x031B03E4, 0x02AF03A4, 0x02660372, 0x025D031C, 0x018E025C, 0x0135022F, 0x00B701D2, 0x00B5018F,
    0x008000B4, 0x0026004C, 0x80008000, 0x00000000, 0x007F00B1, 0x4FA870F0, 0x4510BCE0, 0xB4C0BEF0,
    0x4EC05280, 0x076B0904, 0x065F0824, 0x061607A2, 0x05ED076C, 0x042E05EC, 0x0305050F, 0x02B70462,
    0x0265042F, 0x01B20264, 0x00800100, 0x80008000, 0x00000000, 0x00A900E3, 0x4FA86F60, 0x4510BCE0,
    0xA680BEF0, 0x52C05680, 0x0B580DFB, 0x0A3C0D09, 0x09730BD9, 0x08DA0B59, 0x05E908D9, 0x04B007EC,
    0x03D206EF, 0x031D05EA, 0x0238031C, 0x00AA0154, 0x80008000, 0x00000000, 0x013901A5, 0x50006000,
    0xB8004C00, 0xC000BC00, 0x5C006000, 0x11BB15BA, 0x10BD14C2, 0x0DC111BC, 0x0DC311C0, 0x09C10DC0,
    0x07C10BC4, 0x06CD0A00, 0x05C109C2, 0x041A05C0, 0x013A0274, 0x80008000, 0x00000000, 0x0231033D,
    0x50007E00, 0xB000B400, 0xB0004C00, 0x54006000, 0x1A311ED6, 0x183B1D14, 0x16B21BC2, 0x15EF1A32,
    0x105515EE, 0x0F2D1334, 0x0C5D11F6, 0x0AE11056, 0x07A20AE0, 0x02320464, 0x80008000, 0x00000000,
    0x00010001, 0x7FFF7FFF, 0x00000000, 0x81000000, 0x00000000, 0x0FFF1FFF, 0x00051005, 0x00000000,
    0x00051005, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x10021004, 0x00020004, 0x80008000,
    0x00000000, 0x00010001, 0x7FFF7FFF, 0x00000000, 0x00000000, 0x00000000, 0x0FFF1FFF, 0x00051005,
    0x00000000, 0x00051005, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x10021004, 0x00020004,
    0x80008000, 0x00000000, 0x00130017, 0x4FA870F0, 0x4510BCE0, 0x8500BEF0, 0x54C05F80, 0x02AF0371,
    0x01DF02E5, 0x01D702B0, 0x026A0358, 0x011E01D6, 0x00B1012D, 0x0059011F, 0x00E301A0, 0x00400058,
    0x00140028, 0x80008000, 0x00000000, 0x00000000
};


extern s32 sd_timer_flag; // Only used in this file

s32 smf_timer() // 0x800A6D18
{
    if (sd_interrupt_start_flag == 0 || sd_int_flag != 0)
    {
        return 1;
    }

    if (sd_int_flag2 == 0)
    {
        sd_int_flag2 = 1;
        midi_smf_main();

        if (sd_timer_sync >= 11)
        {
            midi_vsync();
            SdAutoKeyOffCheck();
            sd_timer_sync = 0;
        }

        sd_int_flag2 = 0;
        sd_timer_sync++;
    }

    return 0;
}

void smf_timer_set() // 0x800A6DC0
{
    if (sd_timer_flag == 0)
    {
        sd_timer_flag = 1;

        EnterCriticalSection();
        sd_timer_event = OpenEvent(RCntCNT2, EvSpINT, EvMdINTR, smf_timer);
        EnableEvent(sd_timer_event);
        SetRCnt(RCntCNT2, 7328, RCntMdINTR); // ~30Hz?
        StartRCnt(RCntCNT2);
        ExitCriticalSection();

        sd_int_flag   = 0;
        sd_timer_flag = 0;
    }
}

void smf_timer_end() // 0x800A6E58
{
    sd_timer_flag = 1;

    EnterCriticalSection();
    StopRCnt(RCntCNT2);
    DisableEvent(sd_timer_event);
    CloseEvent(sd_timer_event);
    ExitCriticalSection();

    sd_timer_flag = 0;
    sd_int_flag   = 0;
}

void smf_timer_stop() // 0x800A6EC8
{
    sd_timer_flag = 1;

    EnterCriticalSection();
    StopRCnt(RCntCNT2);
    ExitCriticalSection();

    sd_timer_flag = 0;
    sd_int_flag   = 0;
}

void smf_vsync() // 0x800A6F14
{
    if (sd_int_flag2 != 0)
        return;

    sd_int_flag2 = 1;

    if (smf_start_flag != 0)
    {
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
        midi_smf_main();
    }

    midi_vsync();
    SdAutoKeyOffCheck();
    sd_int_flag2 = 0;
}
