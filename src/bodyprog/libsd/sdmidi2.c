#include "common.h"
#include "bodyprog/libsd.h"

s32 smf_timer(void) // 0x800A6D18
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", smf_timer_set);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", smf_timer_end);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", smf_timer_stop);

void smf_vsync(void) // 0x800A6F14
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", MemCmp);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readMThd);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readMTrk);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmidi2", readEOF);

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
