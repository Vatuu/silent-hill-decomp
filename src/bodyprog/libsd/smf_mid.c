#include "common.h"

#include <libapi.h>

#include "bodyprog/libsd.h"

extern s32 time_flag; // Only used in this file.

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
        }
        while (c & 0x80);
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

void metaevent(SMF* p, u8 type)
{
    u32 tempo;
    u32 len;
    u32 a;

    switch (type)
    {
        case 0x2F:
            p->mf_eof_flag_20 = 1;
            egetc(p);
            break;

        case 0x51:
            if (smf_song[smf_file_no].smf_seq_flag_52C == 1)
            {
                tempo = read32bit(p) & 0xFFFFFF;
            }
            else
            {
                tempo = egetc(p) << 0x10;
                tempo = tempo | (egetc(p) << 8);
                tempo = tempo | egetc(p);
            }

            tempo = 60000000 / tempo;
            tempo = (100 * tempo) / 115;

            if (tempo > 255)
            {
                tempo = 255;
            }

            switch (smf_song[smf_file_no].mf_division_528)
            {
                case 60:
                case 24:
                    tempo = tempo / 2;
                    break;

                case 30:
                    tempo = tempo / 4;
                    break;
            }

            for (a = 0; a < smf_song[smf_file_no].mf_tracks_526; a++)
            {
                smf_song[smf_file_no].tracks_0[a].mf_tempo2_16 = tempo;
                smf_song[smf_file_no].tracks_0[a].mf_tempo_14  = tempo;
            }
            break;

        case 0x54:
            egetc(p);
            egetc(p);
            egetc(p);
            egetc(p);
            egetc(p);
            egetc(p);
            break;

        case 0x58:
            egetc(p);
            read32bit(p);
            break;

        case 0x59:
            egetc(p);
            egetc(p);
            egetc(p);
            break;

        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
        default:
            len = readvarinum(p);
            len_add(p, len);
            break;
    }
}

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
    }
    while (cou < len);
}

void chanmessage(SMF* p, u8 status, u8 c1, u8 c2) // 0x800A7B54
{
    SMF* pp;
    s32  i;
    u8   chan;

    chan = (status & 0xF) | ((u8)smf_file_no * 0x10);
    switch (status & 0xF0)
    {
        case 0x80:
            key_off(chan, c1, c2);
            break;
        case 0x90:
            if ((c2 & 0xFF) != 0)
            {
                key_on(chan, c1, c2);
            }
            else
            {
                key_off(chan, c1, 0);
            }
            break;
        case 0xA0:
            key_press(chan, c1, c2);
            break;
        case 0xB0:
            if (c1 == 0x63)
            {
                if (c2 == 0x14)
                {
                    if (smf_song[smf_file_no].smf_seq_flag_52C == 2)
                    {
                        smf_song[smf_file_no].loop_start_flag_52D = smf_song[smf_file_no].smf_seq_flag_52C;
                    }
                    else if (smf_song[smf_file_no].mf_format_524 != 0)
                    {
                        for (i = 0; i < smf_song[smf_file_no].mf_tracks_526; i++)
                        {
                            pp = &smf_song[smf_file_no].tracks_0[i];

                            pp->mf_loop_count_22    = c2;
                            pp->mf_eof_flag_wk_21   = pp->mf_eof_flag_20;
                            pp->status_value_wk_26  = pp->status_value_25;
                            pp->mf_loop_point_4     = pp->mf_data_loc_0;
                            pp->mf_delta_time_wk_1E = pp->mf_delta_time_1C;
                            pp->time_hosei_wk_1A    = pp->time_hosei_18;
                        }

                        smf_song[smf_file_no].mf_seq_beat_wk_520 = smf_song[smf_file_no].mf_seq_beat_51C;
                    }
                    else
                    {
                        p->mf_loop_count_22 = 0x7F;
                        p->mf_loop_point_4  = p->mf_data_loc_0;
                    }
                }
                else
                {
                    if (c2 == 0x1E)
                    {
                        if (smf_song[smf_file_no].smf_seq_flag_52C == 2)
                        {
                            smf_song[smf_file_no].loop_start_flag_52D = 1;
                        }
                        else
                        {
                            if (p->mf_loop_count_22 != 0)
                            {
                                if (p->mf_loop_count_22 < 0x7F)
                                {
                                    p->mf_loop_count_22 = p->mf_loop_count_22 - 1;
                                }

                                if (smf_song[smf_file_no].mf_format_524 != 0)
                                {
                                    for (i = 0; i < smf_song[smf_file_no].mf_tracks_526; i++)
                                    {
                                        pp = &smf_song[smf_file_no].tracks_0[i];

                                        pp->mf_eof_flag_20   = pp->mf_eof_flag_wk_21;
                                        pp->status_value_25  = pp->status_value_wk_26;
                                        pp->mf_data_loc_0    = pp->mf_loop_point_4;
                                        pp->mf_delta_time_1C = pp->mf_delta_time_wk_1E;
                                        pp->time_hosei_18    = pp->time_hosei_wk_1A;
                                    }

                                    smf_song[smf_file_no].mf_seq_beat_51C = smf_song[smf_file_no].mf_seq_beat_wk_520;
                                }
                                else
                                {
                                    p->mf_data_loc_0 = p->mf_loop_point_4;
                                }
                            }
                        }
                    }
                }
            }

            if (c1 == 6)
            {
                if (smf_midi[chan & 0xFF].nrpn_msb_26 == 0x14)
                {
                    if (smf_song[smf_file_no].mf_format_524 != 0)
                    {
                        for (i = 0; i < smf_song[smf_file_no].mf_tracks_526; i++)
                        {
                            smf_song[smf_file_no].tracks_0[i].mf_loop_count_22 = c2;
                        }
                    }
                    else
                    {
                        p->mf_loop_count_22 = c2;
                        break;
                    }
                }
            }
            control_change(chan, c1, c2);
            break;
        case 0xE0:
            pitch_bend(chan, c1, c2);
            break;
        case 0xC0:
            program_change(chan, c1);
            break;
        case 0xD0:
            chan_press(chan, c1);
            break;
    }
}

u8 readtrack(SMF* p) // 0x800A80C4
{
    extern s32 chantype[]; // static

    u8  c1;
    u8  c2;
    u8  c;
    u8  type;
    u8  stat;
    s32 needed;

    c2 = 0;

    type = egetc(p);

    if ((type & 0x80) == 0)
    {
        stat                      = p->status_value_25;
        p->running_status_flag_24 = 1;
    }
    else
    {
        if (type != 0xFF)
        {
            p->status_value_25 = type;
        }

        stat                      = type;
        p->running_status_flag_24 = 0;
    }

    needed = chantype[(stat >> 4) & 0xF];

    if (needed != 0)
    {
        if (p->running_status_flag_24 != 0)
        {
            c1 = type;
        }
        else
        {
            c1 = egetc(p);
        }

        if (needed == 2)
        {
            c2 = egetc(p);
        }

        chanmessage(p, stat, c1, c2);
        return 0;
    }

    if (type != 0xF0)
    {
        if (type == 0xFF)
        {
            c = egetc(p);
            metaevent(p, c);
        }
        return 0;
    }

    sysex(p);
    return 0;
}

u8 readtrack2(SMF* p) // 0x800A81F4
{
    u8  c;
    s8  c1;
    s32 tempo;
    s32 tr;

    c = egetc(p);
    if (!(c & 0x80))
    {
        c1 = egetc(p);
        if ((c1 & 0x7F) != 0)
        {
            key_on(p->midi_ch_27, c & 0x7F, c1 & 0x7F);
        }
        else
        {
            key_off(p->midi_ch_27, c & 0x7F, 0);
        }
        p->status_value_25 = c;
    }
    else
    {
        switch (c & 0x7F)
        {
            case 0x4A:
                key_off(p->midi_ch_27, p->status_value_25, 0);
                return 0;

            case 0x4B:
                key_off(p->midi_ch_27, p->status_value_25, 0);
                return 1;

            case 0x47:
                c1 = egetc(p);
                for (tr = 0; tr < smf_song[smf_file_no].mf_tracks_526; tr++)
                {
                    tempo = (((c1 & 0x7F) * 2) + 2);
                    smf_song[(p->midi_ch_27 >> 4)].tracks_0[tr].mf_tempo2_16 = tempo;
                }
                break;

            case 0x48:
                c1 = egetc(p);
                pitch_bend(p->midi_ch_27, 0, c1 & 0x7F);
                break;

            case 0x49:
                c1 = egetc(p);
                program_change(p->midi_ch_27, c1 & 0x7F);
                break;

            case 0x46:
                c1 = egetc(p);
                p->midi_ch_27 = (c1 & 0xF) + ((u8)smf_file_no * 0x10);
                break;

            case 0x7F:
                c1 = egetc(p);
                p->mf_eof_flag_20 = 1;
                break;

            default:
                c1 = egetc(p);
                chanmessage(p, (p->midi_ch_27 & 0xF) | 0xB0, c & 0x7F, c1 & 0x7F);
                break;
        }
    }

    return (c1 & 0x80) > 0;
}

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

// TODO: goto jumps below which I'm not sure how to remove yet, maybe code actually included them.
u8 midi_smf_main()
{
    SMF_SONG* s;
    SMF*      p;
    s32       wk;
    s32       tr;

    wk = smf_file_no;

    for (smf_file_no = 0; smf_file_no < 2; smf_file_no++)
    {
        s = &smf_song[smf_file_no];

        if (s->sd_seq_stat_50A == 1)
        {
            for (tr = 0; tr < s->mf_tracks_526; tr++)
            {
                p = &s->tracks_0[tr];

                if (p->mf_eof_flag_20 == 0)
                {
                    p->mf_tempo_14 += p->mf_tempo2_16;

                    if (p->mf_tempo_14 > 0xFF)
                    {
                        p->mf_tempo_14 = p->mf_tempo_14 & 0xFF;

                        if (tr == s->mf_format_524)
                        {
                            s->mf_seq_beat_51C++;
                        }

                        if (p->mf_delta_time_1C != 0)
                        {
                            p->mf_delta_time_1C--;
                        }
                        else
                        {
                            while (true)
                            {
                                if (s->smf_seq_flag_52C != 2)
                                {
                                    readtrack(p);
                                    goto block_12;
                                }
                                if (!readtrack2(p))
                                {
                                block_12:
                                    if (p->mf_eof_flag_20 == 0)
                                    {
                                        p->mf_delta_time_1C = readvarinum(p);
                                        goto block_15;
                                    }
                                }
                                else if (p->mf_eof_flag_20 == 0)
                                {
                                block_15:
                                    if (p->mf_delta_time_1C != 0 && time_flag != 0)
                                    {
                                        delta_time_conv(p);
                                    }

                                    if (p->mf_delta_time_1C == 0)
                                    {
                                        continue;
                                    }
                                }

                                if (p->mf_delta_time_1C != 0)
                                {
                                    p->mf_delta_time_1C--;
                                }

                                break;
                            }
                        }
                    }
                }
            }

            if (s->smf_seq_flag_52C == 2 && s->loop_start_flag_52D != 0)
            {
                for (tr = 0; tr < s->mf_tracks_526; tr++)
                {
                    p = &s->tracks_0[tr];

                    if (s->loop_start_flag_52D == 2)
                    {
                        p->mf_loop_count_22    = 127;
                        p->mf_loop_point_4     = p->mf_data_loc_0;
                        p->mf_delta_time_wk_1E = p->mf_delta_time_1C;
                        p->time_hosei_wk_1A    = p->time_hosei_18;
                        p->mf_eof_flag_wk_21   = p->mf_eof_flag_20;
                        p->status_value_wk_26  = p->status_value_25;
                    }
                    else if (s->loop_start_flag_52D == 1)
                    {
                        if (p->mf_loop_count_22 != 0)
                        {
                            if (p->mf_loop_count_22 < 127)
                            {
                                p->mf_loop_count_22 = p->mf_loop_count_22 - 1;
                            }
                            p->mf_data_loc_0    = p->mf_loop_point_4;
                            p->mf_delta_time_1C = p->mf_delta_time_wk_1E;
                            p->time_hosei_18    = p->time_hosei_wk_1A;
                            p->mf_eof_flag_20   = p->mf_eof_flag_wk_21;
                            p->status_value_25  = p->status_value_wk_26;
                        }
                    }
                }

                if (s->loop_start_flag_52D == 2)
                {
                    s->mf_seq_beat_wk_520 = s->mf_seq_beat_51C;
                }
                else if (s->loop_start_flag_52D == 1)
                {
                    s->mf_seq_beat_51C = s->mf_seq_beat_wk_520;
                }

                s->loop_start_flag_52D = 0;
            }
        }
    }
    smf_file_no = wk;

    return 0;
}

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
