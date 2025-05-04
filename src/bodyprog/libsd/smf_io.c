#include "game.h"

#include <libspu.h>

#include "bodyprog/libsd.h"

extern SpuVoiceAttr s_attr;

void set_note_on(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4) // 0x800A397C
{
    func_800485B0(arg0, arg1, arg2, arg3, arg4); // Nullsub
}

void set_midi_info(s32 type, u8 midiChannel, u32 value) // 0x800A39B8
{
    func_800485B8(type, midiChannel, value); // Nullsub
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", Note2Pitch);

void tre_calc(PORT* p) // 0x800A3B20
{
    s32 vol;
    s32 tre_data;
    s8  tre_char;

    if (p->tredm_36 == 0)
    {
        return;
    }

    if (p->trehc_32 != p->trehs_39)
    {
        p->trehc_32++;
    }
    else
    {
        if (p->trecc_38 >= p->trecs_3A)
        {
            p->tred_34 = p->tredm_36;
        }
        else
        {
            if (p->trecc_38 != 0)
            {
                p->tred_34 += p->tread_3C;
            }
            else
            {
                p->tred_34 = p->tread_3C;
            }
            p->trecc_38++;
        }

        p->trec_33 += p->trecad_3B;
        p->trecadw2_31 = 0;

        if (p->trec_33 < 0)
        {
            tre_char = -p->trec_33 * 2;
            if (tre_char < 0)
            {
                tre_char = -tre_char;
            }

            tre_data = p->tred_34 * tre_char;
            if (tre_data > 0)
            {
                tre_data = -tre_data;
            }
        }
        else
        {
            tre_char = p->trec_33 * 2;
            if (tre_char < 0)
            {
                tre_char = -tre_char;
            }

            tre_data = p->tred_34 * tre_char;
            if (tre_data < 0)
            {
                tre_data = -tre_data;
            }
        }

        if (tre_data != 0)
        {
            if (tre_data < 0)
            {
                tre_data += 0xFF;
            }
            p->tre_data_3E = tre_data >> 8;
        }
        else
        {
            p->tre_data_3E = 0;
        }
    }

    if (p->tremoro_wk_4C == p->tre_data_3E)
    {
        return;
    }

    p->tremoro_wk_4C = p->tre_data_3E;

    s_attr.mask  = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER;
    s_attr.voice = spu_ch_tbl[p->vc_0];

    vol = p->l_vol_C + p->tre_data_3E;
    if (vol < 0)
    {
        vol = 0;
    }
    else if (vol > 0x3FFF)
    {
        vol = 0x3FFF;
    }
    s_attr.volume.left = vol;

    vol = p->r_vol_E + p->tre_data_3E;
    if (vol < 0)
    {
        vol = 0;
    }
    else if (vol > 0x3FFF)
    {
        vol = 0x3FFF;
    }
    s_attr.volume.right = vol;

    s_attr.volmode.left  = 0;
    s_attr.volmode.right = 0;
    SpuSetVoiceAttr(&s_attr);
}

void vib_calc(PORT* p) // 0x800A3D30
{
    s32 vib_data;
    s8  vib_char;

    if (p->vibdm_26 != 0)
    {
        if (p->vibhc_22 != p->vibhs_29)
        {
            p->vibhc_22++;
            return;
        }

        if (p->vibcc_28 >= p->vibcs_2A)
        {
            p->vibd_24 = p->vibdm_26;
        }
        else
        {
            if (p->vibcc_28 != 0)
            {
                p->vibd_24 += p->vibad_2C;
            }
            else
            {
                p->vibd_24 = p->vibad_2C;
            }
            p->vibcc_28++;
        }

        p->vibc_23 += p->vibcad_2B;
        p->vibcadw2_21 = 0;

        if (p->vibc_23 < 0)
        {
            vib_char = -p->vibc_23 * 2;
            if (vib_char < 0)
            {
                vib_char = -vib_char;
            }

            vib_data = p->vibd_24 * vib_char;
            if (vib_data > 0)
            {
                vib_data = -vib_data;
            }
        }
        else
        {
            vib_char = p->vibc_23 * 2;
            if (vib_char < 0)
            {
                vib_char = -vib_char;
            }

            vib_data = p->vibd_24 * vib_char;
            if (vib_data < 0)
            {
                vib_data = -vib_data;
            }
        }

        if (vib_data != 0)
        {
            if (vib_data < 0)
            {
                vib_data += 0x3FF;
            }

            p->vib_data_2E = vib_data >> 10;
            return;
        }

        p->vib_data_2E = 0;
    }
}

void random_calc(PORT* p) // 0x800A3E70
{
    extern u8 random_tbl[];

    s32 rd_data;
    s8  c_data;

    if (!p->rdms_43)
    {
        return;
    }

    p->rdmc_44 += p->rdms_43;

    if (p->rdmc_44 < 0x7F && p->rdms_43 != 127)
    {
        return;
    }

    p->rdmc_44 = p->rdmc_44 & 0x7F;

    c_data = random_tbl[p->rdmo_42];
    p->rdmo_42++;

    if (c_data)
    {
        rd_data = c_data * p->rdmdm_45;
        if (rd_data < 0)
        {
            rd_data += 3;
        }

        p->rdmd_40 = (rd_data >> 2);
    }
    else
    {
        p->rdmd_40 = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", volume_calc);

void smf_vol_set(s32 ch, s32 vc, s32 l_vol, s32 r_vol) // 0x800A4150
{
    s_attr.mask  = (SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER);
    s_attr.voice = spu_ch_tbl[vc];

    if (l_vol | r_vol)
    {
        s_attr.volume.left  = (l_vol * smf_song[ch >> 4].sd_seq_mvoll_50C) >> 7;
        s_attr.volume.right = (r_vol * smf_song[ch >> 4].sd_seq_mvolr_50E) >> 7;
        if (smf_midi[ch].wide_flag_21 || smf_song[ch >> 4].seq_wide_flag_534)
        {
            s_attr.volume.right = -s_attr.volume.right;
        }
    }
    else
    {
        s_attr.volume.right = 0;
        s_attr.volume.left  = 0;
    }

    s_attr.volmode.left  = 0;
    s_attr.volmode.right = 0;

    SpuSetVoiceAttr(&s_attr);
}

void master_vol_set() // 0x800A4260
{
    s32 i;

    sd_int_flag = 1;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        volume_calc(&smf_port[i], &smf_midi[smf_port[i].midi_ch_3]);
        smf_vol_set(smf_port[i].midi_ch_3, i, smf_port[i].l_vol_C, smf_port[i].r_vol_E);
    }

    sd_int_flag = 0;
}

void seq_master_vol_set(s32 access_num) // 0x800A4314
{
    s32 vc;

    for (vc = 0; vc < sd_reserved_voice; vc++)
    {
        if ((smf_port[vc].midi_ch_3 >> 4) == access_num)
        {
            smf_vol_set(smf_port[vc].midi_ch_3, vc, smf_port[vc].l_vol_C, smf_port[vc].r_vol_E);
        }
    }
}

void toremoro_set() // 0x800A439C
{
    s16 tre_data;
    s32 vc;

    for (vc = 0; vc < sd_reserved_voice; vc++)
    {
        tre_data = smf_port[vc].tre_data_3E;
        if (smf_port[vc].tremoro_wk_4C != tre_data)
        {
            smf_vol_set(smf_port[vc].midi_ch_3, vc, smf_port[vc].l_vol_C + tre_data, smf_port[vc].r_vol_E + tre_data);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", pitch_bend_calc);

void pitch_calc(PORT* p, s32 forceSpuUpdate) // 0x800A4494
{
    MIDI* m;
    s32   pitch;
    s32   note;

    m = &smf_midi[p->midi_ch_3];
    if (p->vibdm_26 != 0 || m->mod_2 != 0 || m->porta_28 != 0 || p->rdms_43 != 0 || m->pbend_7 != p->pbend_wk_4E || forceSpuUpdate)
    {
        p->pbend_wk_4E = m->pbend_7;

        pitch = p->rdmd_40 + (p->vib_data_2E + ((u16)m->mod_depth_1C + (u16)m->porta_depth_2A));
        pitch += (p->note_wk_8 << 7) + pitch_bend_calc(p, m->pbend_7, m);
        note = pitch << 16;

        s_attr.mask  = SPU_VOICE_PITCH;
        s_attr.voice = spu_ch_tbl[p->vc_0];
        s_attr.pitch = Note2Pitch(note >> 23, pitch & 0x7F, p->center_1E, p->shift_1F);
        SpuSetVoiceAttr(&s_attr);
    }

    if (p->vibdm_26 != 0 && !SpuGetKeyStatus(spu_ch_tbl[p->vc_0]))
    {
        p->vibdm_26    = 0;
        p->vib_data_2E = 0;
    }
}

void midi_mod(MIDI* p) // 0x800A4608
{
    if (p->mod_2 != 0)
    {
        if (p->mod_w_14 != 0)
        {
            if ((p->mod_depth_1C + p->mod_add_1A) < p->mod_limit_1E)
            {
                p->mod_depth_1C += p->mod_add_1A;
            }
            else
            {
                p->mod_w_14     = 0;
                p->mod_depth_1C = p->mod_limit_1E;
            }
        }
        else if ((p->mod_depth_1C - p->mod_add_1A) > -p->mod_limit_1E)
        {
            p->mod_depth_1C -= p->mod_add_1A;
        }
        else
        {
            p->mod_w_14     = 1;
            p->mod_depth_1C = -p->mod_limit_1E;
        }
    }
    else
    {
        p->mod_depth_1C = 0;
    }
}

void midi_porta(MIDI* p) // 0x800A46B8
{
    if (p->porta_28 != 0)
    {
        if (p->porta_wk_30 != 0)
        {
            if ((p->porta_depth_2A + p->porta_add_2C) < p->porta_limit_2E)
            {
                p->porta_depth_2A += p->porta_add_2C;
            }
            else
            {
                p->porta_depth_2A = p->porta_limit_2E;
            }
        }
        else
        {
            if ((p->porta_add_2C - p->porta_depth_2A) < p->porta_limit_2E)
            {
                p->porta_depth_2A -= p->porta_add_2C;
            }
            else
            {
                p->porta_depth_2A = -p->porta_limit_2E;
            }
        }
    }
}

void replay_reverb_set(s16 acc) // 0x800A4748
{
    SpuReverbAttr reverb;

    if (smf_song[acc].seq_rev_set_flag_532 != 0)
    {
        if (smf_song[acc].seq_rev_set_flag_532 & 1)
        {
            reverb.mask = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
            if (smf_song[acc].seq_rev_set_flag_532 << 8 < smf_song[acc].seq_reverb_depth_536)
            {
                reverb.depth.left = reverb.depth.right = smf_song[acc].seq_rev_set_flag_532 << 8;
            }
            else
            {
                reverb.depth.left = reverb.depth.right = smf_song[acc].seq_reverb_depth_536;
                smf_song[acc].seq_rev_set_flag_532     = 0;
                return; // BUG: Returns before setting seq_reverb_depth_536 as reverb? (fixed in soundcd.irx)
            }

            SpuSetReverbModeParam(&reverb);
            SpuSetReverb(1);
        }
        smf_song[acc].seq_rev_set_flag_532 += 2;
    }
}

void midi_vsync() // 0x800A4838
{
    s32 i;
    s32 ch;

    for (i = 0; i < 2; i++)
    {
        if (smf_song[i].sd_seq_stat_50A == SEQ_PLAY)
        {
            for (ch = 0; ch < 16; ch++)
            {
                midi_mod(&smf_midi[ch + (i * 16)]);
                midi_porta(&smf_midi[ch + (i * 16)]);
            }
        }
    }

    for (ch = 0; ch < sd_reserved_voice; ch++)
    {
        u8 midi_num = smf_port[ch].midi_ch_3;
        if (midi_num < 32 && smf_song[midi_num >> 4].sd_seq_stat_50A == SEQ_PLAY)
        {
            vib_calc(&smf_port[ch]);
            tre_calc(&smf_port[ch]);
            random_calc(&smf_port[ch]);
            pitch_calc(&smf_port[ch], 0);

            if (smf_song[(u8)smf_port[ch].midi_ch_3 >> 4].seq_vol_set_flag_530 != 0)
            {
                smf_vol_set(smf_port[ch].midi_ch_3, ch, smf_port[ch].l_vol_C, smf_port[ch].r_vol_E);
            }
        }
    }

    for (i = 0; i < 2; i++)
    {
        if (smf_song[i].sd_seq_stat_50A == SEQ_PLAY)
        {
            replay_reverb_set(i);
            if (smf_song[i].seq_vol_set_flag_530 != 0)
            {
                smf_song[i].seq_vol_set_flag_530 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", sound_seq_off);

void sound_off() // 0x800A4D20
{
    u32 voice;
    s32 keyStatus;
    s32 vo;
    u32 voices;

    voices = 0;

    for (vo = 0; vo < 2; vo++)
    {
        sound_seq_off(vo);
    }

    for (vo = 0; vo < sd_reserved_voice; vo++)
    {
        smf_vol_set(0, vo, 0, 0);
        smf_port[vo].vc_0        = vo;
        smf_port[vo].stat_16     = 0;
        smf_port[vo].pan_14      = 0x40;
        smf_port[vo].pbend_wk_4E = 0x40;
        smf_port[vo].pbend_50    = 0x40;

        voice = spu_ch_tbl[vo];
        voices |= voice;
        rr_off(vo);

        do
        {
            SpuSetKey(0, voice);
            keyStatus = SpuGetKeyStatus(voice);
        } while (keyStatus != 2 && keyStatus != 0);
    }

    smf_midi_sound_off.mvol_3    = 0x7F;
    smf_midi_sound_off.pan_1     = 0x40;
    smf_midi_sound_off.pbend_7   = 0x40;
    smf_midi_sound_off.pedal_6   = 0;
    smf_midi_sound_off.express_5 = 0x7F;
    smf_midi_sound_off.l_vol_8   = 0x7F;
    smf_midi_sound_off.r_vol_C   = 0x7F;
    smf_midi_sound_off.mod_2     = 0;
    smf_midi_sound_off.pitch_32  = 0;
    smf_midi_sound_off.porta_28  = 0;

    do
    {
        SpuSetKey(0, voices);
        keyStatus = SpuGetKeyStatus(voices);
    } while (keyStatus != 2 && keyStatus != 0);
}

void vol_calc() {} // 0x800A4E90

void adsr_set(s32 vo, PORT* p) // 0x800A4E98
{
    s_attr.mask   = SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    s_attr.voice  = spu_ch_tbl[vo];
    s_attr.adsr1  = p->adsr1_46;
    s_attr.adsr2  = p->adsr2_48;
    s_attr.a_mode = p->a_mode_4A;
    SpuSetVoiceAttr(&s_attr);
}

void rr_off(s32 vo) // 0x800A4F08
{
    s_attr.mask   = SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    s_attr.voice  = spu_ch_tbl[vo];
    s_attr.adsr1  = 0;
    s_attr.adsr2  = 0;
    s_attr.a_mode = 5;
    SpuSetVoiceAttr(&s_attr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", voice_check);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", key_on);

void key_off(u8 chan, u8 c1, u8 c2)
{
    s32 keyStatus;
    s32 vo;
    u32 voices;

    voices = 0;

    for (vo = 0; vo < sd_reserved_voice; vo++)
    {
        if (chan == smf_port[vo].midi_ch_3 && c1 == smf_port[vo].note_6)
        {
            if (smf_port[vo].pedal_1B == 0)
            {
                adsr_set(vo, &smf_port[vo]);
                voices |= spu_ch_tbl[vo];

                do
                {
                    SpuSetKey(0, spu_ch_tbl[vo]);
                    keyStatus = SpuGetKeyStatus(spu_ch_tbl[vo]);
                } while (keyStatus != 2 && keyStatus != 0);

                smf_port[vo].stat_16 = 0;
            }
            else
            {
                smf_port[vo].velo_1A |= 1 << 7;
            }
        }
    }

    if (voices != 0)
    {
        do
        {
            SpuSetKey(0, voices);
            keyStatus = SpuGetKeyStatus(voices);
        } while (keyStatus != 2 && keyStatus != 0);
    }
}

void key_press() {} // 0x800A5DCC

VagAtr* get_vab_tone(MIDI* p, u16 tone, u8 chan) // 0x800A5DD4
{
    SD_VAB_H* vab;

    if (p->bank_change_5A > 16)
    {
        vab = vab_h[smf_song[chan >> 4].sd_seq_vab_id_508].vh_addr_4;
    }
    else
    {
        vab = vab_h[p->bank_change_5A].vh_addr_4;
    }

    return &vab->vag_atr[(p->prog_no_0 * 16) + tone];
}

void smf_data_entry(MIDI* p, u8 chan)
{
    SpuReverbAttr rev_attr; // used in AUDIO.IRX but unused here
    VagAtr*       vp;
    s32           i;

    if (p->nrpn_msb_26 == 0x10 && p->nrpn_lsb_25 < 0xE)
    {
        for (i = 0; i < 16; i++)
        {
            vp = get_vab_tone(p, i, chan);
            switch (p->nrpn_lsb_25)
            {
                case 0:
                    break;
                case 1:
                    vp->mode = p->data_entry_27;
                    break;
                case 2:
                    vp->min = p->data_entry_27;
                    break;
                case 3:
                    vp->max = p->data_entry_27;
                    break;
                case 4:
                    vp->adsr1 = (vp->adsr1 & 0xFF) | ((0x7F - p->data_entry_27) << 8);
                    break;
                case 5:
                    vp->adsr1 = (vp->adsr1 & 0xFF) | ((0x7F - p->data_entry_27) << 8) | 0x8000;
                    break;
                case 6:
                    vp->adsr1 = (vp->adsr1 & 0xFF0F) | ((p->data_entry_27 * 2) & 0xF0);
                    break;
                case 7:
                    vp->adsr1 = (vp->adsr1 & 0xFFF0) | ((p->data_entry_27 >> 3));
                    break;
                case 8:
                    vp->adsr2 = (vp->adsr2 & 0x603F) | ((0x7F - p->data_entry_27) << 6);
                    break;
                case 9:
                    vp->adsr2 = (vp->adsr2 & 0x603F) | ((0x7F - p->data_entry_27) << 6) | 0x8000;
                    break;
                case 10:
                    vp->adsr2 = (vp->adsr2 & 0xFFC0) | ((0x7F - p->data_entry_27) >> 3);
                    break;
                case 11:
                    vp->adsr2 = (vp->adsr2 & 0xFFC0) | ((0x7F - p->data_entry_27) >> 3) | 0x20;
                    break;
                case 12:
                    if (p->data_entry_27 <= 0x40)
                    {
                        vp->adsr2 |= 0x4000;
                    }
                    else
                    {
                        vp->adsr2 &= 0xBFFF;
                    }
                    break;
                case 13:
                    vp->adsr1 = vp->reserved[0];
                    vp->adsr2 = vp->reserved[1];
                    break;
            }
        }
    }
    else
    {
        vp = get_vab_tone(p, p->nrpn_msb_26 & 0xF, chan);

        switch (p->nrpn_lsb_25)
        {
            case 0:
                break;
            case 1:
                vp->mode = p->data_entry_27;
                break;
            case 2:
                vp->min = p->data_entry_27;
                break;
            case 3:
                vp->max = p->data_entry_27;
                break;
            case 4:
                vp->adsr1 = (vp->adsr1 & 0xFF) | ((0x7F - p->data_entry_27) << 8);
                break;
            case 5:
                vp->adsr1 = (vp->adsr1 & 0xFF) | ((0x7F - p->data_entry_27) << 8) | 0x8000;
                break;
            case 6:
                vp->adsr1 = (vp->adsr1 & 0xFF0F) | ((p->data_entry_27 * 2) & 0xF0);
                break;
            case 7:
                vp->adsr1 = (vp->adsr1 & 0xFFF0) | (p->data_entry_27 >> 3);
                break;
            case 8:
                vp->adsr2 = (vp->adsr2 & 0x603F) | ((0x7F - p->data_entry_27) << 6);
                break;
            case 9:
                vp->adsr2 = (vp->adsr2 & 0x603F) | ((0x7F - p->data_entry_27) << 6) | 0x8000;
                break;
            case 10:
                vp->adsr2 = (vp->adsr2 & 0xFFC0) | ((0x7F - p->data_entry_27) >> 3);
                break;
            case 11:
                vp->adsr2 = (vp->adsr2 & 0xFFC0) | ((0x7F - p->data_entry_27) >> 3) | 0x20;
                break;
            case 12:
                if (p->data_entry_27 <= 0x40)
                {
                    vp->adsr2 |= 0x4000;
                }
                else
                {
                    vp->adsr2 &= 0xBFFF;
                }
                break;
            case 13:
                vp->adsr1 = vp->reserved[0];
                vp->adsr2 = vp->reserved[1];
                return;
            case 23:
                p->before_note_13 = p->data_entry_27;
                break;
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/smf_io", control_change);

void program_change(u8 chan, u8 c1) // 0x800A6C2C
{
    smf_midi[chan].prog_no_0 = c1;
}

void chan_press() {} // 0x800A6C58

void pitch_bend(u8 chan, s32 c1, u8 c2)
{
    smf_midi[chan].pbend_7 = c2 & 0x7F;
    set_midi_info(1, chan, c2);
}

void control_code_set(s32 seq_access_num) {} // 0x800A6CB0
