#include "common.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", func_800A397C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", func_800A39B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", Note2Pitch);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", tre_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", vib_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", random_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", volume_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", smf_vol_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", master_vol_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", seq_master_vol_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", toremoro_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_bend_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_calc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", midi_mod);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", midi_porta);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", replay_reverb_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", midi_vsync);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", sound_seq_off);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", sound_off);

void set_note_on_mb(void) {} // 0x800A4E90

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", adsr_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", rr_off);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", voice_check);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", key_on);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", key_off);

void key_press(void) {} // 0x800A5DCC

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", get_vab_tone);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", smf_data_entry);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", control_change);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", program_change);

void chan_press(void) {} // 0x800A6C58

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi", pitch_bend);

void control_code_set(void) {} // 0x800A6CB0
