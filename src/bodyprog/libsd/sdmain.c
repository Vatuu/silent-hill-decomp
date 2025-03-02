#include "common.h"
#include "bodyprog/libsd.h"

#include <libspu.h>
#include <libsnd.h>

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", tone_adsr_mem);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", tone_adsr_back);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", sd_alloc_sort);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSpuMalloc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSpuMallocWithStartAddr);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSpuFree);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdWorkInit);

void SdInit(void) // 0x8009F490
{
    SsUtReverbOff();
    sound_off();
    SdWorkInit();
    SpuInitMalloc(0x10, &sd_vb_malloc_rec);
}

void SdStart(void) // 0x8009F4D0
{
    if (sd_tick_mode > 0)
    {
        if (sd_tick_mode < 4)
        {
            smf_timer_set();
        }
    }
    sd_interrupt_start_flag = 1;
}

void SdStart2(void) // 0x8009F510
{
    SdStart();
}

void SdSetTickMode(s32 tick_mode) // 0x8009F530
{
    sd_tick_mode = tick_mode;
}

void SdSeqCalledTbyT(void) // 0x8009F53C
{
    if (sd_interrupt_start_flag != 0)
    {
        smf_vsync();
    }
}

void SdSetStereo(void) // 0x8009F568
{
    sd_mono_st_flag = 0;
}

void SdSetMono(void) // 0x8009F574
{
    sd_mono_st_flag = 1;
}

char SdSetReservedVoice(char voices) // 0x8009F584
{
    if (voices >= 0x19)
    {
        return -1;
    }
    if (voices == 0)
    {
        return -1;
    }

    sd_reserved_voice = voices;
    return voices;
}

void SdSetTableSize(void) {} // 0x8009F5B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdEnd);

void SdQuit(void) // 0x8009F64C
{
    sound_off();
    SdWorkInit();
    SpuQuit();
}

void SdSetSerialAttr(char s_num, char attr, char mode) // 0x8009F67C
{
    SpuCommonAttr spu_attr;

    if (s_num == SS_SERIAL_A)
    {
        if (attr == SS_MIX)
        {
            spu_attr.mask   = SPU_COMMON_CDMIX;
            spu_attr.cd.mix = mode;
        }
        else /* SS_REV */
        {
            spu_attr.mask      = SPU_COMMON_CDREV;
            spu_attr.cd.reverb = mode;
        }
    }
    else /* SS_SERIAL_B */
    {
        if (attr == SS_MIX)
        {
            spu_attr.mask    = SPU_COMMON_EXTMIX;
            spu_attr.ext.mix = mode;
        }
        else /* SS_REV */
        {
            spu_attr.mask       = SPU_COMMON_EXTREV;
            spu_attr.ext.reverb = mode;
        }
    }
    SpuSetCommonAttr(&spu_attr);
}

void SdSetSerialVol(s16 s_num, s16 voll, s16 volr) // 0x8009F700
{
    // TODO: libsnd SsSetSerialVol uses char for s_num, callers also seem to
    // pass char but only matches with s16 right now?

    SpuCommonAttr attr;

    s32 v_left  = voll << 8;
    s32 v_right = volr << 8;

    if (s_num == SS_SERIAL_A)
    {
        attr.mask            = (SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR);
        attr.cd.volume.left  = v_left;
        attr.cd.volume.right = v_right;
    }
    else /* SS_SERIAL_B */
    {
        attr.mask             = (SPU_COMMON_EXTVOLL | SPU_COMMON_EXTVOLR);
        attr.ext.volume.left  = v_left;
        attr.ext.volume.right = v_right;
    }

    SpuSetCommonAttr(&attr);
}

void SdSetMVol(s16 left, s16 right) // 0x8009F75C
{
    SpuCommonAttr attr;

    attr.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_MVOLMODEL |
                 SPU_COMMON_MVOLMODER);
    attr.mvol.left      = left << 7;
    attr.mvol.right     = right << 7;
    attr.mvolmode.left  = 0;
    attr.mvolmode.right = 0;

    SpuSetCommonAttr(&attr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabOpenHead);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabOpenHeadSticky);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabFakeHead);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVbOpenOne);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabTransBody);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabTransBodyPartly);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabTransCompleted);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVabClose);

void SdSetAutoKeyOffMode(s16 mode) // 0x8009FF64
{
    sd_keyoff_mode = mode;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdAutoKeyOffCheck);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqOpen);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqOpenWithAccNum);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqPlay);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqStop);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqClose);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqPause);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqReplay);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqSetVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqGetVol);

void SdUtFlush(void) // 0x800A0794
{
    SdAutoKeyOffCheck();
}

void SdUtReverbOn(void) // 0x800A07B4
{
    SpuReserveReverbWorkArea(SPU_ON);
    SpuSetReverb(SPU_ON);
}

void SdUtReverbOff(void) // 0x800A07DC
{
    sd_reverb_mode = 0;
    SpuSetReverb(SPU_OFF);
    SpuReserveReverbWorkArea(SPU_OFF);
}

s16 SdUtSetReverbType(s16 type) // 0x800A080C
{
    SpuReverbAttr attr;

    attr.mask = SPU_REV_MODE;
    attr.mode = type;

    if (SpuSetReverbModeParam(&attr))
    {
        return -1;
    }

    sd_reverb_mode = type;
    return type;
}

void SdUtSetReverbDepth(s16 left, s16 right) // 0x800A085C
{
    SpuReverbAttr attr;

    attr.mask        = (SPU_REV_DEPTHL | SPU_REV_DEPTHR);
    attr.depth.left  = (left << 0x10) >> 8;
    attr.depth.right = (right << 0x10) >> 8;

    SpuSetReverbModeParam(&attr);
}

void SdSetRVol(s16 left, s16 right) // 0x800A089C
{
    SpuReverbAttr attr;

    attr.mask        = (SPU_REV_DEPTHL | SPU_REV_DEPTHR);
    attr.depth.left  = (left << 0x10) >> 8;
    attr.depth.right = (right << 0x10) >> 8;

    SpuSetReverbModeParam(&attr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtSEAllKeyOff);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtAllKeyOff);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtGetVabHdr);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVoKeyOn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVoKeyOff);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVoKeyOffWithRROff);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtKeyOnV);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtKeyOn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVbKeyOn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtKeyOffV);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtKeyOffVWithRROff);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetSeqStatus);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtSetDetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtSetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtGetDetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtGetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetTempo);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetTempo);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetSeqWide);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiExpress);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiExpress);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiPan);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiPan);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiPitchBendFine);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiPitchBendFine);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetTrackTranspause);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetTrackTranspause);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetTrackMute);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetTrackMute);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetSeqControlStatus);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetSeqPlayStatus);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetSeqBeat);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetSeqBeat2);
