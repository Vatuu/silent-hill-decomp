#include "common.h"
#include "bodyprog/libsd.h"

#include <libspu.h>

extern SpuVoiceAttr s_attr;

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", func_800A397C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", func_800A39B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", Note2Pitch);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", tre_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", vib_calc);

void random_calc(s_SMF_PORT* midiPort) // 0x800A3E70
{
    extern u8 random_tbl[];

    s32 var_v0;
    s8  randValue;

    if (!midiPort->field_43)
        return;

    midiPort->field_44 += midiPort->field_43;

    if (midiPort->field_44 < 0x7F && midiPort->field_43 != 127)
        return;

    midiPort->field_44 = midiPort->field_44 & 0x7F;

    randValue = random_tbl[midiPort->randomTblIndex_42];
    midiPort->randomTblIndex_42++;

    if (randValue)
    {
        var_v0 = randValue * midiPort->field_45;
        if (var_v0 < 0)
        {
            var_v0 += 3;
        }
        midiPort->field_40 = (var_v0 >> 2);
    }
    else
    {
        midiPort->field_40 = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", volume_calc);

void smf_vol_set(s32 midiChannel, s32 voice, s32 volLeft, s32 volRight) // 0x800A4150
{
    s_attr.mask  = (SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_VOLMODEL | SPU_VOICE_VOLMODER);
    s_attr.voice = spu_ch_tbl[voice];

    if (volLeft | volRight)
    {
        s_attr.volume.left  = (volLeft * smf_song[midiChannel >> 4].vol_left_50C) >> 7;
        s_attr.volume.right = (volRight * smf_song[midiChannel >> 4].vol_right_50E) >> 7;
        if (smf_midi[midiChannel].field_21 || smf_song[midiChannel >> 4].seq_wide_534) // seq_wide s16 -> u16
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
        volume_calc(&smf_port[i], &smf_midi[smf_port[i].smf_midi_num_3]);
        smf_vol_set(smf_port[i].smf_midi_num_3, i, smf_port[i].vol_left_C, smf_port[i].vol_right_E);
    }

    sd_int_flag = 0;
}

void seq_master_vol_set(s32 seq_access_num) // 0x800A4314
{
    s32 i;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        if ((smf_port[i].smf_midi_num_3 >> 4) == seq_access_num)
        {
            smf_vol_set(smf_port[i].smf_midi_num_3, i, smf_port[i].vol_left_C, smf_port[i].vol_right_E);
        }
    }
}

void toremoro_set() // 0x800A439C
{
    s16 temp_v1;
    s32 i;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        temp_v1 = smf_port[i].field_3E;
        if (smf_port[i].field_4C != temp_v1)
        {
            smf_vol_set(smf_port[i].smf_midi_num_3, i, smf_port[i].vol_left_C + temp_v1, smf_port[i].vol_right_E + temp_v1);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_bend_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_calc);

void midi_mod(s_SMF_MIDI* midiTrack) // 0x800A4608
{
    if (midiTrack->field_2 != 0)
    {
        if (midiTrack->field_14 != 0)
        {
            if ((midiTrack->field_1C + midiTrack->field_1A) < midiTrack->field_1E)
            {
                midiTrack->field_1C = midiTrack->field_1C + midiTrack->field_1A;
            }
            else
            {
                midiTrack->field_14 = 0;
                midiTrack->field_1C = midiTrack->field_1E;
            }
        }
        else if ((midiTrack->field_1C - midiTrack->field_1A) > -midiTrack->field_1E)
        {
            midiTrack->field_1C = midiTrack->field_1C - midiTrack->field_1A;
        }
        else
        {
            midiTrack->field_14 = 1;
            midiTrack->field_1C = -midiTrack->field_1E;
        }
    }
    else
    {
        midiTrack->field_1C = 0;
    }
}

void midi_porta(s_SMF_MIDI* midiTrack) // 0x800A46B8
{
    if (midiTrack->portamentoTime_28 != 0)
    {
        if (midiTrack->field_30 != 0)
        {
            if ((midiTrack->field_2A + midiTrack->field_2C) < midiTrack->field_2E)
            {
                midiTrack->field_2A = midiTrack->field_2A + midiTrack->field_2C;
            }
            else
            {
                midiTrack->field_2A = midiTrack->field_2E;
            }
        }
        else
        {
            if ((midiTrack->field_2C - midiTrack->field_2A) < midiTrack->field_2E)
            {
                midiTrack->field_2A = midiTrack->field_2A - midiTrack->field_2C;
            }
            else
            {
                midiTrack->field_2A = -midiTrack->field_2E;
            }
        }
    }
}

void replay_reverb_set(s16 seq_access_num) // 0x800A4748
{
    SpuReverbAttr reverb;

    if (smf_song[seq_access_num].field_532 != 0)
    {
        if (smf_song[seq_access_num].field_532 & 1)
        {
            reverb.mask = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
            if (smf_song[seq_access_num].field_532 << 8 < smf_song[seq_access_num].field_536)
            {
                reverb.depth.left = reverb.depth.right = smf_song[seq_access_num].field_532 << 8;
            }
            else
            {
                reverb.depth.left = reverb.depth.right = smf_song[seq_access_num].field_536;
                smf_song[seq_access_num].field_532     = 0;
                return; // BUG: returns before it sets field_536 as reverb?
            }
            SpuSetReverbModeParam(&reverb);
            SpuSetReverb(1);
        }
        smf_song[seq_access_num].field_532 += 2;
    }
}

void midi_vsync() // 0x800A4838
{
    s32 device;
    s32 channel;

    for (device = 0; device < 2; device++)
    {
        if (smf_song[device].play_status_50A == 1)
        {
            for (channel = 0; channel < 0x10; channel++)
            {
                midi_mod(&smf_midi[channel + (device * 0x10)]);
                midi_porta(&smf_midi[channel + (device * 0x10)]);
            }
        }
    }

    for (channel = 0; channel < sd_reserved_voice; channel++)
    {
        u8 midi_num = smf_port[channel].smf_midi_num_3;
        if (midi_num < 32 && smf_song[midi_num >> 4].play_status_50A == 1)
        {
            vib_calc(&smf_port[channel]);
            tre_calc(&smf_port[channel]);
            random_calc(&smf_port[channel]);
            pitch_calc(&smf_port[channel], 0);
            if (smf_song[(u8)smf_port[channel].smf_midi_num_3 >> 4].field_530 != 0)
            {
                smf_vol_set(smf_port[channel].smf_midi_num_3, channel, smf_port[channel].vol_left_C, smf_port[channel].vol_right_E);
            }
        }
    }

    for (device = 0; device < 2; device++)
    {
        if (smf_song[device].play_status_50A == 1)
        {
            replay_reverb_set(device);
            if (smf_song[device].field_530 != 0)
            {
                smf_song[device].field_530 = 0;
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
        smf_port[i].field_0  = i;
        smf_port[i].field_16 = 0;
        smf_port[i].field_14 = 0x40;
        smf_port[i].field_4E = 0x40;
        smf_port[i].field_50 = 0x40;
        voice                = spu_ch_tbl[i];
        voices |= voice;
        rr_off(i);
        do
        {
            SpuSetKey(0, voice);
            keyStatus = SpuGetKeyStatus(voice);
        } while (keyStatus != 2 && keyStatus != 0);
    }

    D_800C82B8.vol_3                = 0x7F;
    D_800C82B8.pan_1                = 0x40;
    D_800C82B8.pitchBendFine_7      = 0x40;
    D_800C82B8.damperPedalEnabled_6 = 0;
    D_800C82B8.expression_5         = 0x7F;
    D_800C82B8.field_8              = 0x7F;
    D_800C82B8.field_C              = 0x7F;
    D_800C82B8.field_2              = 0;
    D_800C82B8.field_32             = 0;
    D_800C82B8.portamentoTime_28    = 0;

    do
    {
        SpuSetKey(0, voices);
        keyStatus = SpuGetKeyStatus(voices);
    } while (keyStatus != 2 && keyStatus != 0);
}

void set_note_on_mb(void) {} // 0x800A4E90

void adsr_set(s32 voice, s_SMF_PORT* midiPort) // 0x800A4E98
{
    s_attr.mask   = SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    s_attr.voice  = spu_ch_tbl[voice];
    s_attr.adsr1  = midiPort->field_46;
    s_attr.adsr2  = midiPort->field_48;
    s_attr.a_mode = midiPort->field_4A;
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
        if (midiNum == smf_port[i].smf_midi_num_3 && keyNum == smf_port[i].midiKeyNum_6)
        {
            if (smf_port[i].field_1B == 0)
            {
                adsr_set(i, &smf_port[i]);
                voices |= spu_ch_tbl[i];
                do
                {
                    SpuSetKey(0, spu_ch_tbl[i]);
                    keyStatus = SpuGetKeyStatus(spu_ch_tbl[i]);
                } while (keyStatus != 2 && keyStatus != 0);
                smf_port[i].field_16 = 0;
            }
            else
            {
                smf_port[i].field_1A |= 0x80;
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

void key_press(void) {} // 0x800A5DCC

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", get_vab_tone);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", smf_data_entry);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", control_change);

void program_change(u8 midiChannel, u8 progNum) // 0x800A6C2C
{
    smf_midi[midiChannel].vabProgNum_0 = progNum;
}

void chan_press(void) {} // 0x800A6C58

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_bend);

void control_code_set(s32 seq_access_num) {} // 0x800A6CB0
