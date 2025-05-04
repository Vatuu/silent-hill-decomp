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

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", Note2Pitch);

void tre_calc(PORT* midiPort) // 0x800A3B20
{
    s32 vol;
    s32 var0;
    s8  var1;

    if (midiPort->tredm_36 == 0)
    {
        return;
    }

    if (midiPort->trehc_32 != midiPort->trehs_39)
    {
        midiPort->trehc_32++;
    }
    else
    {
        if (midiPort->trecc_38 >= midiPort->trecs_3A)
        {
            midiPort->tred_34 = midiPort->tredm_36;
        }
        else
        {
            if (midiPort->trecc_38 != 0)
            {
                midiPort->tred_34 += midiPort->tread_3C;
            }
            else
            {
                midiPort->tred_34 = midiPort->tread_3C;
            }
            midiPort->trecc_38++;
        }

        midiPort->trec_33 += midiPort->trecad_3B;
        midiPort->trecadw2_31 = 0;
        if (midiPort->trec_33 < 0)
        {
            var1 = -midiPort->trec_33 * 2;
            if (var1 < 0)
            {
                var1 = -var1;
            }

            var0 = midiPort->tred_34 * var1;
            if (var0 > 0)
            {
                var0 = -var0;
            }
        }
        else
        {
            var1 = midiPort->trec_33 * 2;
            if (var1 < 0)
            {
                var1 = -var1;
            }

            var0 = midiPort->tred_34 * var1;
            if (var0 < 0)
            {
                var0 = -var0;
            }
        }

        if (var0 != 0)
        {
            if (var0 < 0)
            {
                var0 += 0xFF;
            }
            midiPort->tre_data_3E = var0 >> 8;
        }
        else
        {
            midiPort->tre_data_3E = 0;
        }
    }

    if (midiPort->tremoro_wk_4C == midiPort->tre_data_3E)
    {
        return;
    }

    midiPort->tremoro_wk_4C = midiPort->tre_data_3E;

    s_attr.mask  = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER;
    s_attr.voice = spu_ch_tbl[midiPort->vc_0];

    vol = midiPort->l_vol_C + midiPort->tre_data_3E;
    if (vol < 0)
    {
        vol = 0;
    }
    else if (vol > 0x3FFF)
    {
        vol = 0x3FFF;
    }
    s_attr.volume.left = vol;

    vol = midiPort->r_vol_E + midiPort->tre_data_3E;
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

void vib_calc(PORT* midiPort) // 0x800A3D30
{
    s32 var0;
    s8  var1;

    if (midiPort->vibdm_26 != 0)
    {
        if (midiPort->vibhc_22 != midiPort->vibhs_29)
        {
            midiPort->vibhc_22++;
            return;
        }

        if (midiPort->vibcc_28 >= midiPort->vibcs_2A)
        {
            midiPort->vibd_24 = midiPort->vibdm_26;
        }
        else
        {
            if (midiPort->vibcc_28 != 0)
            {
                midiPort->vibd_24 += midiPort->vibad_2C;
            }
            else
            {
                midiPort->vibd_24 = midiPort->vibad_2C;
            }
            midiPort->vibcc_28++;
        }

        midiPort->vibc_23 += midiPort->vibcad_2B;
        midiPort->vibcadw2_21 = 0;

        if (midiPort->vibc_23 < 0)
        {
            var1 = -midiPort->vibc_23 * 2;
            if (var1 < 0)
            {
                var1 = -var1;
            }

            var0 = midiPort->vibd_24 * var1;
            if (var0 > 0)
            {
                var0 = -var0;
            }
        }
        else
        {
            var1 = midiPort->vibc_23 * 2;
            if (var1 < 0)
            {
                var1 = -var1;
            }

            var0 = midiPort->vibd_24 * var1;
            if (var0 < 0)
            {
                var0 = -var0;
            }
        }

        if (var0 != 0)
        {
            if (var0 < 0)
            {
                var0 += 0x3FF;
            }

            midiPort->vib_data_2E = var0 >> 10;
            return;
        }

        midiPort->vib_data_2E = 0;
    }
}

void random_calc(PORT* midiPort) // 0x800A3E70
{
    extern u8 random_tbl[];

    s32 var0;
    s8  randValue;

    if (!midiPort->rdms_43)
    {
        return;
    }

    midiPort->rdmc_44 += midiPort->rdms_43;

    if (midiPort->rdmc_44 < 0x7F && midiPort->rdms_43 != 127)
    {
        return;
    }

    midiPort->rdmc_44 = midiPort->rdmc_44 & 0x7F;

    randValue = random_tbl[midiPort->rdmo_42];
    midiPort->rdmo_42++;

    if (randValue)
    {
        var0 = randValue * midiPort->rdmdm_45;
        if (var0 < 0)
        {
            var0 += 3;
        }

        midiPort->rdmd_40 = (var0 >> 2);
    }
    else
    {
        midiPort->rdmd_40 = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", volume_calc);

void smf_vol_set(s32 midiChannel, s32 voice, s32 volLeft, s32 volRight) // 0x800A4150
{
    s_attr.mask  = (SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER);
    s_attr.voice = spu_ch_tbl[voice];

    if (volLeft | volRight)
    {
        s_attr.volume.left  = (volLeft * smf_song[midiChannel >> 4].sd_seq_mvoll_50C) >> 7;
        s_attr.volume.right = (volRight * smf_song[midiChannel >> 4].sd_seq_mvolr_50E) >> 7;
        if (smf_midi[midiChannel].wide_flag_21 || smf_song[midiChannel >> 4].seq_wide_flag_534)
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

void seq_master_vol_set(s32 seq_access_num) // 0x800A4314
{
    s32 i;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        if ((smf_port[i].midi_ch_3 >> 4) == seq_access_num)
        {
            smf_vol_set(smf_port[i].midi_ch_3, i, smf_port[i].l_vol_C, smf_port[i].r_vol_E);
        }
    }
}

void toremoro_set() // 0x800A439C
{
    s16 temp_v1;
    s32 i;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        temp_v1 = smf_port[i].tre_data_3E;
        if (smf_port[i].tremoro_wk_4C != temp_v1)
        {
            smf_vol_set(smf_port[i].midi_ch_3, i, smf_port[i].l_vol_C + temp_v1, smf_port[i].r_vol_E + temp_v1);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_bend_calc);

void pitch_calc(PORT* midiPort, s32 forceSpuUpdate) // 0x800A4494
{
    MIDI*       midi;
    s32         temp_s0;
    s32         temp_a0;

    midi = &smf_midi[midiPort->midi_ch_3];
    if (midiPort->vibdm_26 != 0 || midi->mod_2 != 0 || midi->porta_28 != 0 || midiPort->rdms_43 != 0 || midi->pbend_7 != midiPort->pbend_wk_4E || forceSpuUpdate)
    {
        midiPort->pbend_wk_4E = midi->pbend_7;

        temp_s0 = midiPort->rdmd_40 + (midiPort->vib_data_2E + ((u16)midi->mod_depth_1C + (u16)midi->porta_depth_2A));
        temp_s0 += (midiPort->note_wk_8 << 7) + pitch_bend_calc(midiPort, midi->pbend_7, midi);
        temp_a0 = temp_s0 << 16;

        s_attr.mask  = SPU_VOICE_PITCH;
        s_attr.voice = spu_ch_tbl[midiPort->vc_0];
        s_attr.pitch = Note2Pitch(temp_a0 >> 23, temp_s0 & 0x7F, midiPort->center_1E, midiPort->shift_1F);
        SpuSetVoiceAttr(&s_attr);
    }

    if (midiPort->vibdm_26 != 0 && !SpuGetKeyStatus(spu_ch_tbl[midiPort->vc_0]))
    {
        midiPort->vibdm_26    = 0;
        midiPort->vib_data_2E = 0;
    }
}

void midi_mod(MIDI* midiTrack) // 0x800A4608
{
    if (midiTrack->mod_2 != 0)
    {
        if (midiTrack->mod_w_14 != 0)
        {
            if ((midiTrack->mod_depth_1C + midiTrack->mod_add_1A) < midiTrack->mod_limit_1E)
            {
                midiTrack->mod_depth_1C += midiTrack->mod_add_1A;
            }
            else
            {
                midiTrack->mod_w_14     = 0;
                midiTrack->mod_depth_1C = midiTrack->mod_limit_1E;
            }
        }
        else if ((midiTrack->mod_depth_1C - midiTrack->mod_add_1A) > -midiTrack->mod_limit_1E)
        {
            midiTrack->mod_depth_1C -= midiTrack->mod_add_1A;
        }
        else
        {
            midiTrack->mod_w_14     = 1;
            midiTrack->mod_depth_1C = -midiTrack->mod_limit_1E;
        }
    }
    else
    {
        midiTrack->mod_depth_1C = 0;
    }
}

void midi_porta(MIDI* midiTrack) // 0x800A46B8
{
    if (midiTrack->porta_28 != 0)
    {
        if (midiTrack->porta_wk_30 != 0)
        {
            if ((midiTrack->porta_depth_2A + midiTrack->porta_add_2C) < midiTrack->porta_limit_2E)
            {
                midiTrack->porta_depth_2A += midiTrack->porta_add_2C;
            }
            else
            {
                midiTrack->porta_depth_2A = midiTrack->porta_limit_2E;
            }
        }
        else
        {
            if ((midiTrack->porta_add_2C - midiTrack->porta_depth_2A) < midiTrack->porta_limit_2E)
            {
                midiTrack->porta_depth_2A -= midiTrack->porta_add_2C;
            }
            else
            {
                midiTrack->porta_depth_2A = -midiTrack->porta_limit_2E;
            }
        }
    }
}

void replay_reverb_set(s16 seq_access_num) // 0x800A4748
{
    SpuReverbAttr reverb;

    if (smf_song[seq_access_num].seq_rev_set_flag_532 != 0)
    {
        if (smf_song[seq_access_num].seq_rev_set_flag_532 & 1)
        {
            reverb.mask = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
            if (smf_song[seq_access_num].seq_rev_set_flag_532 << 8 < smf_song[seq_access_num].seq_reverb_depth_536)
            {
                reverb.depth.left = reverb.depth.right = smf_song[seq_access_num].seq_rev_set_flag_532 << 8;
            }
            else
            {
                reverb.depth.left = reverb.depth.right        = smf_song[seq_access_num].seq_reverb_depth_536;
                smf_song[seq_access_num].seq_rev_set_flag_532 = 0;
                return; // BUG: Returns before setting seq_reverb_depth_536 as reverb? (fixed in soundcd.irx)
            }

            SpuSetReverbModeParam(&reverb);
            SpuSetReverb(1);
        }
        smf_song[seq_access_num].seq_rev_set_flag_532 += 2;
    }
}

void midi_vsync() // 0x800A4838
{
    s32 device;
    s32 channel;

    for (device = 0; device < 2; device++)
    {
        if (smf_song[device].sd_seq_stat_50A == SEQ_PLAY)
        {
            for (channel = 0; channel < 16; channel++)
            {
                midi_mod(&smf_midi[channel + (device * 16)]);
                midi_porta(&smf_midi[channel + (device * 16)]);
            }
        }
    }

    for (channel = 0; channel < sd_reserved_voice; channel++)
    {
        u8 midi_num = smf_port[channel].midi_ch_3;
        if (midi_num < 32 && smf_song[midi_num >> 4].sd_seq_stat_50A == SEQ_PLAY)
        {
            vib_calc(&smf_port[channel]);
            tre_calc(&smf_port[channel]);
            random_calc(&smf_port[channel]);
            pitch_calc(&smf_port[channel], 0);

            if (smf_song[(u8)smf_port[channel].midi_ch_3 >> 4].seq_vol_set_flag_530 != 0)
            {
                smf_vol_set(smf_port[channel].midi_ch_3, channel, smf_port[channel].l_vol_C, smf_port[channel].r_vol_E);
            }
        }
    }

    for (device = 0; device < 2; device++)
    {
        if (smf_song[device].sd_seq_stat_50A == SEQ_PLAY)
        {
            replay_reverb_set(device);
            if (smf_song[device].seq_vol_set_flag_530 != 0)
            {
                smf_song[device].seq_vol_set_flag_530 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", sound_seq_off);

void sound_off() // 0x800A4D20
{
    u32 voice;
    s32 keyStatus;
    s32 i;
    u32 voices;

    voices = 0;

    for (i = 0; i < 2; i++)
    {
        sound_seq_off(i);
    }

    for (i = 0; i < sd_reserved_voice; i++)
    {
        smf_vol_set(0, i, 0, 0);
        smf_port[i].vc_0        = i;
        smf_port[i].stat_16     = 0;
        smf_port[i].pan_14      = 0x40;
        smf_port[i].pbend_wk_4E = 0x40;
        smf_port[i].pbend_50    = 0x40;

        voice = spu_ch_tbl[i];
        voices |= voice;
        rr_off(i);

        do
        {
            SpuSetKey(0, voice);
            keyStatus = SpuGetKeyStatus(voice);
        }
        while (keyStatus != 2 && keyStatus != 0);
    }

    smf_midi_sound_off.mvol_3               = 0x7F;
    smf_midi_sound_off.pan_1                = 0x40;
    smf_midi_sound_off.pbend_7              = 0x40;
    smf_midi_sound_off.pedal_6              = 0;
    smf_midi_sound_off.express_5            = 0x7F;
    smf_midi_sound_off.l_vol_8              = 0x7F;
    smf_midi_sound_off.r_vol_C              = 0x7F;
    smf_midi_sound_off.mod_2                = 0;
    smf_midi_sound_off.pitch_32             = 0;
    smf_midi_sound_off.porta_28             = 0;

    do
    {
        SpuSetKey(0, voices);
        keyStatus = SpuGetKeyStatus(voices);
    }
    while (keyStatus != 2 && keyStatus != 0);
}

void func_800A4E90() {} // 0x800A4E90

void adsr_set(s32 voice, PORT* midiPort) // 0x800A4E98
{
    s_attr.mask   = SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    s_attr.voice  = spu_ch_tbl[voice];
    s_attr.adsr1  = midiPort->adsr1_46;
    s_attr.adsr2  = midiPort->adsr2_48;
    s_attr.a_mode = midiPort->a_mode_4A;
    SpuSetVoiceAttr(&s_attr);
}

void rr_off(s32 voice) // 0x800A4F08
{
    s_attr.mask   = SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    s_attr.voice  = spu_ch_tbl[voice];
    s_attr.adsr1  = 0;
    s_attr.adsr2  = 0;
    s_attr.a_mode = 5;
    SpuSetVoiceAttr(&s_attr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", voice_check);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", key_on);

void key_off(u8 midiNum, u8 keyNum)
{
    s32 keyStatus;
    s32 i;
    u32 voices;

    voices = 0;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        if (midiNum == smf_port[i].midi_ch_3 && keyNum == smf_port[i].note_6)
        {
            if (smf_port[i].pedal_1B == 0)
            {
                adsr_set(i, &smf_port[i]);
                voices |= spu_ch_tbl[i];

                do
                {
                    SpuSetKey(0, spu_ch_tbl[i]);
                    keyStatus = SpuGetKeyStatus(spu_ch_tbl[i]);
                }
                while (keyStatus != 2 && keyStatus != 0);

                smf_port[i].stat_16 = 0;
            }
            else
            {
                smf_port[i].velo_1A |= 1 << 7;
            }
        }
    }

    if (voices != 0)
    {
        do
        {
            SpuSetKey(0, voices);
            keyStatus = SpuGetKeyStatus(voices);
        }
        while (keyStatus != 2 && keyStatus != 0);
    }
}

void key_press() {} // 0x800A5DCC

VagAtr* get_vab_tone(MIDI* midiTrack, u16 tone, u8 midiChannel) // 0x800A5DD4
{
    SD_VAB_H* vab;

    if (midiTrack->bank_change_5A > 16)
    {
        vab = vab_h[smf_song[midiChannel >> 4].sd_seq_vab_id_508].vh_addr_4;
    }
    else
    {
        vab = vab_h[midiTrack->bank_change_5A].vh_addr_4;
    }

    return &vab->vag_atr[(midiTrack->prog_no_0 * 16) + tone];
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", smf_data_entry);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", control_change);

void program_change(u8 midiChannel, u8 progNum) // 0x800A6C2C
{
    smf_midi[midiChannel].prog_no_0 = progNum;
}

void chan_press() {} // 0x800A6C58

void pitch_bend(u8 midiChannel, s32 unused, u8 pitchBend)
{
    smf_midi[midiChannel].pbend_7 = pitchBend & 0x7F;
    set_midi_info(1, midiChannel, pitchBend);
}

void control_code_set(s32 seq_access_num) {} // 0x800A6CB0
