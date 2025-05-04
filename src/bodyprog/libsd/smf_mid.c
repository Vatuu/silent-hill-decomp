#include "common.h"

#include <libapi.h>

#include "bodyprog/libsd.h"

s32 MemCmp(u8* src, u8* des, s32 num) // 0x800A6FB8
{
    if (!num)
    {
        return -1;
    }

    while (--num)
    {
        if (*src != *des)
        {
            break;
        }

        src += 1;
        des += 1;
    }

    return *src - *des;
}

s32 readMThd(u32 loc) // 0x800A6FFC
{
    extern char D_8002E538[4]; // "MThd"
    while (true)
    {
        if (!MemCmp(D_8002E538, smf_song[smf_file_no].mf_data_ptr_504 + loc, 4))
        {
            return loc + 4;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++loc)
        {
            return -1;
        }
    }

    return loc;
}

s32 readMTrk(u32 loc) // 0x800A70BC
{
    extern char D_8002E540[4]; // "MTrk"

    while (true)
    {
        if (!MemCmp(D_8002E540, smf_song[smf_file_no].mf_data_ptr_504 + loc, 4))
        {
            return loc + 4;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++loc)
        {
            return -1;
        }
    }

    return loc;
}

s32 readEOF(u32 loc) // 0x800A717C
{
    extern char eof_char[3]; // 0x00002FFF

    while (true)
    {
        if (!MemCmp(&eof_char, smf_song[smf_file_no].mf_data_ptr_504 + loc, 3))
        {
            return loc + 3;
        }

        if (smf_song[smf_file_no].mf_data_size_518 < ++loc)
        {
            return -1;
        }
    }

    return loc;
}

s32 egetc(SMF* p) // 0x800A723C
{
    u32 data;

    data = smf_song[smf_file_no].mf_data_ptr_504[p->mf_data_loc_0];

    p->mf_data_loc_0++;

    if (smf_song[smf_file_no].mf_data_size_518 < p->mf_data_loc_0)
    {
        p->mf_eof_flag_20 = 1;
        return -1;
    }

    return data;
}

s32 readvarinum(SMF* p) // 0x800A72B4
{
    s32 c;
    s32 value;

    c = egetc(p);

    if (c == 0)
    {
        return 0;
    }

    if (c == -1)
    {
        p->mf_eof_flag_20 = 1;
        return 0;
    }

    value = c;

    if (c & 0x80)
    {
        value = c & 0x7F;
        do
        {
            c     = egetc(p);
            value = (value << 7) + (c & 0x7F);
        } while (c & 0x80);
    }

    return value;
}

s32 to32bit(char c1, char c2, char c3, char c4) // 0x800A733C
{
    return (((((c1 << 8) + c2) << 8) + c3) << 8) | c4;
}

s32 to16bit(char c1, char c2) // 0x800A7368
{
    return (c1 << 8) | c2;
}

s32 read32bit(SMF* p) // 0x800A737C
{
    s8 c1 = egetc(p);
    s8 c2 = egetc(p);
    s8 c3 = egetc(p);
    s8 c4 = egetc(p);
    return to32bit(c1, c2, c3, c4);
}

s32 read16bit(SMF* p) // 0x800A73E8
{
    s8 c1 = egetc(p);
    s8 c2 = egetc(p);
    return to16bit(c1, c2) & 0xFFFF;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", readheader);

void len_add(SMF* p, s32 len) // 0x800A7814
{
    p->mf_data_loc_0 += len;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", metaevent);

void sysex(SMF* p) // 0x800A7AEC
{
    u32 cou = 0;
    u32 len = readvarinum(p);

    do
    {
        cou++;
        if ((egetc(p) & 0xFF) == 0xF7)
        {
            break;
        }
    } while (cou < len);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", chanmessage);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", readtrack);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", readtrack2);

s32 track_head_read(SMF* p)
{
    p->mf_data_loc_0 = readMTrk(p->mf_data_loc_0);
    if (p->mf_data_loc_0 == NO_VALUE)
    {
        return 1;
    }

    p->mf_track_length_8 = read32bit(p);
    p->mf_repeat_ptr_10  = p->mf_data_loc_0;
    p->mf_track_size_C   = p->mf_data_loc_0 + p->mf_track_length_8;
    return 0;
}

void delta_time_conv(SMF* p) // 0x800A84B0
{
    switch (smf_song[smf_file_no].mf_division_528)
    {
        case 48:
            p->mf_delta_time_1C *= 10;
            p->mf_delta_time_1C += p->time_hosei_18;
            p->time_hosei_18 = p->mf_delta_time_1C & 3;
            p->mf_delta_time_1C /= 4;
            break;

        case 96:
            p->mf_delta_time_1C *= 5;
            p->mf_delta_time_1C += p->time_hosei_18;
            p->time_hosei_18 = p->mf_delta_time_1C & 3;
            p->mf_delta_time_1C /= 4;
            break;

        case 192:
        case 240:
            p->mf_delta_time_1C += p->time_hosei_18;
            p->time_hosei_18 = p->mf_delta_time_1C & 1;
            p->mf_delta_time_1C /= 2;
            break;

        case 288:
        case 360:
            p->mf_delta_time_1C /= 3;
            break;

        case 480:
        case 384:
            p->mf_delta_time_1C += p->time_hosei_18;
            p->time_hosei_18 = p->mf_delta_time_1C & 3;
            p->mf_delta_time_1C /= 4;
            break;

        case 768:
        case 960:
            p->mf_delta_time_1C += p->time_hosei_18;
            p->time_hosei_18 = p->mf_delta_time_1C & 7;
            p->mf_delta_time_1C /= 8;
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", midi_file_out);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_mid", midi_smf_main);

void midi_smf_stop(s32 access_value) // 0x800A8C74
{
    s32 tr;

    for (tr = 0; tr < smf_song[access_value].mf_tracks_526; tr++)
    {
        smf_song[access_value].tracks_0[tr].mf_eof_flag_20 = 1;
        smf_song[access_value].tracks_0[tr].mf_data_loc_0  = 0;
    }
}

s16 midi_smf_stat(s32 access_no) // 0x800A8D00
{
    s32 tr;

    for (tr = 0; tr < smf_song[access_no].mf_tracks_526; tr++)
    {
        if (smf_song[access_no].tracks_0[tr].mf_eof_flag_20 != 1)
        {
            return SEQ_PLAY;
        }
    }

    return SEQ_END;
}
