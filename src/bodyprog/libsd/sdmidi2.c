#include "common.h"
#include "bodyprog/libsd.h"

#include <libapi.h>

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

s32 MemCmp(u8* str1, u8* str2, s32 count) // 0x800A6FB8
{
    if (!count)
    {
        return -1;
    }

    while (--count)
    {
        if (*str1 != *str2)
        {
            break;
        }

        str1 += 1;
        str2 += 1;
    }

    return *str1 - *str2;
}

s32 readMThd(u32 offset) // 0x800A6FFC
{
    extern char D_8002E538[4]; // "MThd"
    while (true)
    {
        if (!MemCmp(D_8002E538, smf_song[smf_file_no].play_ptr_504 + offset, 4))
        {
            return offset + 4;
        }

        if (smf_song[smf_file_no].field_518 < ++offset)
        {
            return -1;
        }
    }

    return offset;
}

s32 readMTrk(u32 offset) // 0x800A70BC
{
    extern char D_8002E540[4]; // "MTrk"

    while (true)
    {
        if (!MemCmp(D_8002E540, smf_song[smf_file_no].play_ptr_504 + offset, 4))
        {
            return offset + 4;
        }

        if (smf_song[smf_file_no].field_518 < ++offset)
        {
            return -1;
        }
    }

    return offset;
}

s32 readEOF(u32 offset) // 0x800A717C
{
    extern char D_800B25C4[3]; // 0x00002FFF

    while (true)
    {
        if (!MemCmp(&D_800B25C4, smf_song[smf_file_no].play_ptr_504 + offset, 3))
        {
            return offset + 3;
        }

        if (smf_song[smf_file_no].field_518 < ++offset)
        {
            return -1;
        }
    }

    return offset;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", egetc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readvarinum);

s32 to32bit(char arg0, char arg1, char arg2, char arg3) // 0x800A733C
{
    return (((((arg0 << 8) + arg1) << 8) + arg2) << 8) | arg3;
}

s32 to16bit(char arg0, char arg1) // 0x800A7368
{
    return (arg0 << 8) | arg1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", read32bit);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", read16bit);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readheader);

void len_add(s32* ptr, s32 val) // 0x800A7814
{
    *ptr += val;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", metaevent);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", sysex);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", chanmessage);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readtrack);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readtrack2);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", track_head_read);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", delta_time_conv);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_file_out);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_smf_main);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_smf_stop);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_smf_stat);
