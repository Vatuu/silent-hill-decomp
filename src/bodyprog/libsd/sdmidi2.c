#include "common.h"

#include <libapi.h>

#include "bodyprog/libsd.h"

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
        if (!MemCmp(D_8002E538, smf_song[smf_file_no].mf_data_ptr_504 + offset, 4))
        {
            return offset + 4;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++offset)
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
        if (!MemCmp(D_8002E540, smf_song[smf_file_no].mf_data_ptr_504 + offset, 4))
        {
            return offset + 4;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++offset)
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
        if (!MemCmp(&D_800B25C4, smf_song[smf_file_no].mf_data_ptr_504 + offset, 3))
        {
            return offset + 3;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++offset)
        {
            return -1;
        }
    }

    return offset;
}

s32 egetc(SMF* track) // 0x800A723C
{
    u32 ret = smf_song[smf_file_no].mf_data_ptr_504[track->mf_data_loc_0];

    track->mf_data_loc_0++;

    if (smf_song[smf_file_no].mf_data_size_518 < track->mf_data_loc_0)
    {
        track->mf_eof_flag_20 = 1;
        return -1;
    }

    return ret;
}

s32 readvarinum(SMF* track) // 0x800A72B4
{
    s32 curByte;
    s32 num;

    curByte = egetc(track);

    if (curByte == 0)
    {
        return 0;
    }

    if (curByte == -1)
    {
        track->mf_eof_flag_20 = 1;
        return 0;
    }

    num = curByte;

    if (curByte & 0x80)
    {
        num = curByte & 0x7F;
        do
        {
            curByte = egetc(track);
            num     = (num << 7) + (curByte & 0x7F);
        }
        while (curByte & 0x80);
    }

    return num;
}

s32 to32bit(char arg0, char arg1, char arg2, char arg3) // 0x800A733C
{
    return (((((arg0 << 8) + arg1) << 8) + arg2) << 8) | arg3;
}

s32 to16bit(char arg0, char arg1) // 0x800A7368
{
    return (arg0 << 8) | arg1;
}

s32 read32bit(SMF* track) // 0x800A737C
{
    s8 b0 = egetc(track);
    s8 b1 = egetc(track);
    s8 b2 = egetc(track);
    s8 b3 = egetc(track);
    return to32bit(b0, b1, b2, b3);
}

s32 read16bit(SMF* track) // 0x800A73E8
{
    s8 b0 = egetc(track);
    s8 b1 = egetc(track);
    return to16bit(b0, b1) & 0xFFFF;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readheader);

void len_add(s32* ptr, s32 val) // 0x800A7814
{
    *ptr += val;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", metaevent);

void sysex(SMF* track) // 0x800A7AEC
{
    u32 i     = 0;
    u32 count = readvarinum(track);

    do
    {
        i++;
        if ((egetc(track) & 0xFF) == 0xF7)
        {
            break;
        }
    }
    while (i < count);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", chanmessage);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readtrack);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readtrack2);

s32 track_head_read(SMF* track)
{
    track->mf_data_loc_0 = readMTrk(track->mf_data_loc_0);
    if (track->mf_data_loc_0 == NO_VALUE)
    {
        return 1;
    }

    track->mf_track_length_8 = read32bit(track);
    track->mf_repeat_ptr_10  = track->mf_data_loc_0;
    track->mf_track_size_C   = track->mf_data_loc_0 + track->mf_track_length_8;
    return 0;
}

void delta_time_conv(SMF* track) // 0x800A84B0
{
    switch (smf_song[smf_file_no].mf_division_528)
    {
        case 48:
            track->mf_delta_time_1C *= 10;
            track->mf_delta_time_1C += track->time_hosei_18;
            track->time_hosei_18 = track->mf_delta_time_1C & 3;
            track->mf_delta_time_1C /= 4;
            break;

        case 96:
            track->mf_delta_time_1C *= 5;
            track->mf_delta_time_1C += track->time_hosei_18;
            track->time_hosei_18 = track->mf_delta_time_1C & 3;
            track->mf_delta_time_1C /= 4;
            break;

        case 192:
        case 240:
            track->mf_delta_time_1C += track->time_hosei_18;
            track->time_hosei_18 = track->mf_delta_time_1C & 1;
            track->mf_delta_time_1C /= 2;
            break;

        case 288:
        case 360:
            track->mf_delta_time_1C /= 3;
            break;

        case 480:
        case 384:
            track->mf_delta_time_1C += track->time_hosei_18;
            track->time_hosei_18 = track->mf_delta_time_1C & 3;
            track->mf_delta_time_1C /= 4;
            break;

        case 768:
        case 960:
            track->mf_delta_time_1C += track->time_hosei_18;
            track->time_hosei_18 = track->mf_delta_time_1C & 7;
            track->mf_delta_time_1C /= 8;
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_file_out);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", midi_smf_main);

void midi_smf_stop(s32 seq_access_num) // 0x800A8C74
{
    s32 i;

    for (i = 0; i < smf_song[seq_access_num].mf_tracks_526; i++)
    {
        smf_song[seq_access_num].tracks_0[i].mf_eof_flag_20 = 1;
        smf_song[seq_access_num].tracks_0[i].mf_data_loc_0  = 0;
    }
}

s16 midi_smf_stat(s32 seq_access_num) // 0x800A8D00
{
    s32 i;

    for (i = 0; i < smf_song[seq_access_num].mf_tracks_526; i++)
    {
        if (smf_song[seq_access_num].tracks_0[i].mf_eof_flag_20 != 1)
        {
            return 1;
        }
    }

    return 3;
}
