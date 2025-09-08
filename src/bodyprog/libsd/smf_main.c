#include "common.h"

#include <libapi.h>

#include "bodyprog/libsd.h"

s32 sd_interrupt_start_flag = 0;
s16 sd_keyoff_mode = 0;
// 2 bytes of padding.
s32 sd_mono_st_flag = 0;
s32 sd_reverb_mode = 0;
u32 body_partly_size = 0;

#include "smf_tables.h"

s32 sd_reserved_voice = 0x18;
u32 spu_reverb_sw = 0;
u32 spu_ch_tbl[24] =
{
    0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
    0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
};
s32 sd_int_flag = 0;
s32 sd_int_flag2 = 0;
s32 smf_start_flag = 0;
s32 sd_timer_sync = 0;
u32 timer_count[5] = { 0x1999, 0x2000, 0x4000, 0xFFFF, 0x1A80 };
s32 sd_timer_flag = 0;
s32 time_flag = 0xC0;
s32 smf_file_no = 0;
u32 print_start = 0;
char eof_char[3] = { 0xFF, 0x2F, 0x00 };
// 1 byte padding.
s32 chantype[18] = {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 0, 0, 0 };


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
