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
    SpuInitMalloc(16, &sd_vb_malloc_rec);
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
        else // SS_REV
        {
            spu_attr.mask      = SPU_COMMON_CDREV;
            spu_attr.cd.reverb = mode;
        }
    }
    else // SS_SERIAL_B
    {
        if (attr == SS_MIX)
        {
            spu_attr.mask    = SPU_COMMON_EXTMIX;
            spu_attr.ext.mix = mode;
        }
        else // SS_REV
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
        attr.mask            = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
        attr.cd.volume.left  = v_left;
        attr.cd.volume.right = v_right;
    }
    else // SS_SERIAL_B
    {
        attr.mask             = SPU_COMMON_EXTVOLL | SPU_COMMON_EXTVOLR;
        attr.ext.volume.left  = v_left;
        attr.ext.volume.right = v_right;
    }

    SpuSetCommonAttr(&attr);
}

void SdSetMVol(s16 left, s16 right) // 0x8009F75C
{
    SpuCommonAttr attr;

    attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_MVOLMODEL | SPU_COMMON_MVOLMODER;
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

s16 SdVabTransBody(u8* addr, s16 vabid) // 0x8009FD38
{
    s32 vab_h_id;

    if (vabid < 0)
    {
        return -1;
    }

    vab_h_id = vab_h[vabid].vab_id_0;
    if (vab_h_id >= 0 && vab_h_id == vabid)
    {
        SpuSetTransferStartAddr(vab_h[vabid].vab_start_10);
        if (SpuWrite(addr, vab_h[vabid].vab_total_14) == vab_h[vabid].vab_total_14)
        {
            vab_h[vabid].vab_addr_C = addr;
            return vab_h_id;
        }
    }

    return -1;
}

s16 SdVabTransBodyPartly(u8* addr, u32 bufsize, s16 vabid) // 0x8009FDDC
{
    s16 vab_h_id;
    s32 retval;

    if (vabid < 0)
    {
        return -1;
    }

    vab_h_id = vab_h[vabid].vab_id_0;
    retval   = -1;
    if (vab_h_id >= 0 && vab_h_id == vabid)
    {
        SpuSetTransferStartAddr(vab_h[vabid].vab_start_10 + sd_vab_transfer_offset);
        if (vab_h[vabid].vab_total_14 - sd_vab_transfer_offset < bufsize)
        {
            bufsize = vab_h[vabid].vab_total_14 - sd_vab_transfer_offset;
        }
        if (SpuWrite(addr, bufsize) != bufsize)
        {
            return -1;
        }

        sd_vab_transfer_offset += bufsize;
        retval = vab_h_id;

        if (sd_vab_transfer_offset < vab_h[vabid].vab_total_14)
        {
            return -2;
        }

        return vab_h_id; // Maybe was meant to be return retval but devs just returned vab_h_id?
    }
    return retval;
}

s16 SdVabTransCompleted(s16 immediateFlag) // 0x8009FEC4
{
    if (!immediateFlag)
    {
        return SpuIsTransferCompleted(0);
    }
    else
    {
        return SpuIsTransferCompleted(1);
    }
}

void SdVabClose(s16 vab_id) // 0x8009FF00
{
    if (vab_h[vab_id].vab_id_0 != -1)
    {
        SdSpuFree(vab_h[vab_id].vab_start_10);
        vab_h[vab_id].vab_id_0 = -1;
    }
}

void SdSetAutoKeyOffMode(s16 mode) // 0x8009FF64
{
    sd_keyoff_mode = mode;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdAutoKeyOffCheck);

s16 SdSeqOpen(s32* addr, s16 vab_id) // 0x800A00A4
{
    s32 i;

    sd_int_flag = 1;
    if (*addr != SD_MAGIC_SEQp && *addr != SD_MAGIC_MThd && *addr != SD_MAGIC_KDT && *addr != SD_MAGIC_KDT1)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        if (smf_song[i].vab_id_508 == -1)
        {
            smf_song[i].play_status_50A  = 2;
            smf_song[i].seq_data_ptr_514 = addr;
            smf_song[i].vab_id_508       = vab_id;
            sd_int_flag                  = 0;
            return i;
        }
    }

    sd_int_flag = 0;
    return -1;
}

s16 SdSeqOpenWithAccNum(s32* addr, s16 vab_id, s16 seq_access_num) // 0x800A0154
{
    sd_int_flag = 1;
    if (*addr != SD_MAGIC_SEQp && *addr != SD_MAGIC_MThd && *addr != SD_MAGIC_KDT && *addr != SD_MAGIC_KDT1)
    {
        return -1;
    }

    if (smf_song[seq_access_num].vab_id_508 == -1)
    {
        smf_song[seq_access_num].play_status_50A  = 2;
        smf_song[seq_access_num].seq_data_ptr_514 = addr;
        smf_song[seq_access_num].vab_id_508       = vab_id;
        sd_int_flag                               = 0;
        return seq_access_num;
    }

    sd_int_flag = 0;
    return -1;
}

void SdSeqPlay(s16 seq_access_num, u8 play_mode, s16 l_count) // 0x800A0210
{
    if (seq_access_num == -1)
    {
        return;
    }

    sd_int_flag = 1;

    if (smf_song[seq_access_num].vab_id_508 == -1)
    {
        sd_int_flag = 0;
        return;
    }

    sd_seq_loop_mode = l_count;

    smf_song[seq_access_num].field_518    = 0x10000;
    smf_song[seq_access_num].play_ptr_504 = smf_song[seq_access_num].seq_data_ptr_514;

    midi_file_out(seq_access_num);

    if (!play_mode)
    {
        smf_song[seq_access_num].play_status_50A = 4;
    }
    else
    {
        smf_start_flag                           = 1;
        smf_song[seq_access_num].play_status_50A = 1;
    }

    sd_int_flag = 0;
}

void SdSeqStop(s16 seq_access_num) // 0x800A02D8
{
    if (seq_access_num == -1)
    {
        return;
    }

    if (smf_song[seq_access_num].vab_id_508 != -1)
    {
        sd_int_flag = 1;

        midi_smf_stop(seq_access_num);
        sound_seq_off(seq_access_num);
        smf_song[seq_access_num].vol_right_50E   = 127;
        smf_song[seq_access_num].vol_left_50C    = 127;
        smf_song[seq_access_num].play_status_50A = 2;

        sd_int_flag = 0;
    }
}

void SdSeqClose(s16 seq_access_num) // 0x800A037C
{
    if (seq_access_num == -1)
    {
        return;
    }

    if (smf_song[seq_access_num].vab_id_508 != -1)
    {
        sd_int_flag = 1;

        tone_adsr_back(smf_song[seq_access_num].vab_id_508);
        smf_song[seq_access_num].vab_id_508      = -1;
        smf_song[seq_access_num].play_status_50A = 0;
        smf_song[seq_access_num].vol_right_50E   = 127;
        smf_song[seq_access_num].vol_left_50C    = 127;

        sd_int_flag = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqPause);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSeqReplay);

void SdSeqSetVol(s16 seq_access_num, s16 voll, s16 volr) // 0x800A06F0
{
    smf_song[seq_access_num].vol_left_50C  = voll & 0x7F;
    smf_song[seq_access_num].vol_right_50E = volr & 0x7F;
    if (smf_song[seq_access_num].play_status_50A != 2)
    {
        smf_song[seq_access_num].field_530 = 1;
    }
}

void SdSeqGetVol(s16 seq_access_num, s16* voll, s16* volr) // 0x800A074C
{
    *voll = smf_song[seq_access_num].vol_left_50C;
    *volr = smf_song[seq_access_num].vol_right_50E;
}

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

    attr.mask        = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
    attr.depth.left  = (left << 0x10) >> 8;
    attr.depth.right = (right << 0x10) >> 8;

    SpuSetReverbModeParam(&attr);
}

void SdSetRVol(s16 left, s16 right) // 0x800A089C
{
    SpuReverbAttr attr;

    attr.mask        = SPU_REV_DEPTHL | SPU_REV_DEPTHR;
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

s16 SdGetSeqStatus(s16 seq_access_num) // 0x800A1B14
{
    if (smf_song[seq_access_num].play_status_50A == 1 && midi_smf_stat(seq_access_num) == 3)
    {
        smf_song[seq_access_num].play_status_50A = 3;
    }

    return smf_song[seq_access_num].play_status_50A;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtSetDetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtSetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtGetDetVVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdUtGetVVol);

u16 SdGetTempo(s16 seq_access_num) // 0x800A1D68
{
    return smf_song[seq_access_num].tracks_0[0].tempo_16;
}

void SdSetTempo(s16 seq_access_num, s16 tempo) // 0x800A1DA4
{
    s32 i;

    for (i = 0; i < smf_song[seq_access_num].num_tracks_526; i++)
    {
        smf_song[seq_access_num].tracks_0[i].tempo_16 = tempo;
        smf_song[seq_access_num].tracks_0[i].tempo_14 = tempo;
    }
}

void SdSetSeqWide(s16 seq_access_num, s16 seq_wide) // 0x800A1E18
{
    smf_song[seq_access_num].seq_wide_534 = seq_wide;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiVol);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiExpress);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiExpress);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiPan);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiPan);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdGetMidiPitchBendFine);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSetMidiPitchBendFine);

s32 SdGetTrackTranspause() // 0x800A2030
{
    return 0;
}

s32 SdSetTrackTranspause() // 0x800A2038
{
    return 0;
}

s32 SdGetTrackMute(s16 seq_access_num, s32 channel) // 0x800A2040
{
    return smf_song[seq_access_num].muted_channels_510 & spu_ch_tbl[channel];
}

s32 SdSetTrackMute(s16 seq_access_num, s32 channel) // 0x800A2090
{
    smf_song[seq_access_num].muted_channels_510 |= spu_ch_tbl[channel];
    return 0;
}

s32 SdGetSeqControlStatus(s16 seq_access_num) // 0x800A20EC
{
    if (seq_access_num >= 0)
    {
        return smf_song[seq_access_num].control_status_52F;
    }
    return -1;
}

s16 SdGetSeqPlayStatus(s32 seq_access_num) // 0x800A2134
{
    if (smf_song[seq_access_num].play_status_50A == 1 && midi_smf_stat(seq_access_num) == 3)
    {
        smf_song[seq_access_num].play_status_50A = 3;
    }

    return smf_song[seq_access_num].play_status_50A;
}

u32 SdGetSeqBeat(s16 seq_access_num) // 0x800A21E0
{
    if (seq_access_num >= 0)
    {
        if (smf_song[seq_access_num].beat_51C == 0)
        {
            return 0;
        }
        return smf_song[seq_access_num].beat_51C / 60;
    }
    return -1;
}

s32 SdGetSeqBeat2(s16 seq_access_num) // 0x800A224C
{
    if (seq_access_num >= 0)
    {
        return smf_song[seq_access_num].beat2_52E;
    }
    return -1;
}
