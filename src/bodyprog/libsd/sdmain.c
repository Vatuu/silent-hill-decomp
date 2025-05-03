#include "common.h"

#include <libspu.h>

#include "bodyprog/libsd.h"

void tone_adsr_mem(s16 vabid) // 0x8009EDA4
{
    s_VabHeader* vabData;
    VagAtr*      vagAtr;
    VabHdr*      vabHdr;
    s32          vagNum;
    s32          progNum;

    vabData = vab_h[vabid].vab_header_4;
    vabHdr  = &vabData->header;

    for (progNum = 0; progNum < vabHdr->ps; progNum++)
    {
        for (vagNum = 0; vagNum < 0x10; vagNum++)
        {
            vagAtr = &vabData->vag[(progNum * 0x10) + vagNum];

            vagAtr->reserved[0] = vagAtr->adsr1;
            vagAtr->reserved[1] = vagAtr->adsr2;
        }
    }
}

void tone_adsr_back(s16 vabid) // 0x8009EE30
{
    s_VabHeader* vabData;
    VagAtr*      vagAtr;
    VabHdr*      vabHdr;
    s32          vagNum;
    s32          progNum;

    vabData = vab_h[vabid].vab_header_4;
    vabHdr  = &vabData->header;

    for (progNum = 0; progNum < vabHdr->ps; progNum++)
    {
        for (vagNum = 0; vagNum < 0x10; vagNum++)
        {
            vagAtr = &vabData->vag[(progNum * 0x10) + vagNum];

            vagAtr->adsr1 = vagAtr->reserved[0];
            vagAtr->adsr2 = vagAtr->reserved[1];
        }
    }
}

void sd_alloc_sort() // 0x8009EEBC
{
    s32 lastSlotIdx;
    s32 frontIdx;
    s32 backIdx;

    for (lastSlotIdx = 0; lastSlotIdx < SD_ALLOC_SLOTS; lastSlotIdx++)
    {
        if (sd_spu_alloc[lastSlotIdx].addr_0 == 0)
        {
            break;
        }
    }

    for (frontIdx = 0; frontIdx < lastSlotIdx; frontIdx++)
    {
        for (backIdx = lastSlotIdx - 1; frontIdx < backIdx; backIdx--)
        {
            if (sd_spu_alloc[frontIdx].addr_0 > sd_spu_alloc[backIdx].addr_0)
            {
                s_SD_ALLOC temp;
                temp.size_4 = sd_spu_alloc[frontIdx].size_4;
                temp.addr_0 = sd_spu_alloc[frontIdx].addr_0;

                sd_spu_alloc[frontIdx].size_4 = sd_spu_alloc[backIdx].size_4;
                sd_spu_alloc[frontIdx].addr_0 = sd_spu_alloc[backIdx].addr_0;

                sd_spu_alloc[backIdx].size_4 = temp.size_4;
                sd_spu_alloc[backIdx].addr_0 = temp.addr_0;
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSpuMalloc);

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdSpuMallocWithStartAddr);

void SdSpuFree(u32 addr) // 0x8009F364
{
    s32 i;

    for (i = 0; i < SD_ALLOC_SLOTS; i++)
    {
        if (sd_spu_alloc[i].addr_0 != addr)
        {
            continue;
        }

        // TODO: could this be moved out of the for loop above?
        for (; i < SD_ALLOC_SLOTS; i++)
        {
            sd_spu_alloc[i].size_4 = sd_spu_alloc[i + 1].size_4;
            sd_spu_alloc[i].addr_0 = sd_spu_alloc[i + 1].addr_0;
            if (!sd_spu_alloc[i].addr_0)
                break;
        }
        sd_alloc_sort();
        return;
    }
}

void SdWorkInit() // 0x8009F400
{
    s32 i;

    STATIC_ASSERT(SD_VAB_SLOTS == SD_ALLOC_SLOTS, SD_VAB_SLOTS_must_equal_SD_ALLOC_SLOTS);

    for (i = 0; i < SD_VAB_SLOTS; i++)
    {
        vab_h[i].vab_id_0      = -1;
        vab_h[i].field_19      = 0x7F;
        vab_h[i].field_1A      = 0x7F;
        vab_h[i].master_pan_1B = 0x40;
        sd_spu_alloc[i].size_4 = 0;
        sd_spu_alloc[i].addr_0 = 0;
    }

    for (i = 0; i < 2; i++)
    {
        smf_song[i].vab_id_508      = -1;
        smf_song[i].play_status_50A = 0;
        smf_song[i].vol_right_50E   = 0x7F;
        smf_song[i].vol_left_50C    = 0x7F;
    }

    sd_tick_mode = 4096;
}

void SdInit() // 0x8009F490
{
    SsUtReverbOff();
    sound_off();
    SdWorkInit();
    SpuInitMalloc(16, &sd_vb_malloc_rec);
}

void SdStart() // 0x8009F4D0
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

void SdStart2() // 0x8009F510
{
    SdStart();
}

void SdSetTickMode(s32 tick_mode) // 0x8009F530
{
    sd_tick_mode = tick_mode;
}

void SdSeqCalledTbyT() // 0x8009F53C
{
    if (sd_interrupt_start_flag != 0)
    {
        smf_vsync();
    }
}

void SdSetStereo() // 0x8009F568
{
    sd_mono_st_flag = 0;
}

void SdSetMono() // 0x8009F574
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

void SdSetTableSize() {} // 0x8009F5B8

void SdEnd() // 0x8009F5C0
{
    s32 i;

    sound_off();

    if (sd_tick_mode > 0)
    {
        if (sd_tick_mode < 4)
        {
            smf_timer_end();
        }
    }

    for (i = 0; i < SD_VAB_SLOTS; i++)
    {
        if (vab_h[i].vab_id_0 >= 0)
        {
            SdSpuFree(vab_h[i].vab_start_10);
        }
    }

    SdWorkInit();
}

void SdQuit() // 0x8009F64C
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

    return SpuIsTransferCompleted(1);
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

void SdAutoKeyOffCheck() // 0x8009FF70
{
    s32 keyStatus;
    s32 voiceIdx;
    u32 voices;

    voices = 0;

    if (sd_keyoff_mode == 0)
    {
        for (voiceIdx = 0; voiceIdx < sd_reserved_voice; voiceIdx++)
        {
            if (smf_port[voiceIdx].field_16 != 0 && SpuGetKeyStatus(spu_ch_tbl[voiceIdx]) == 3)
            {
                if (smf_port[voiceIdx].field_16 >= 2U)
                {
                    voices |= spu_ch_tbl[voiceIdx];

                    do
                    {
                        SpuSetKey(0, spu_ch_tbl[voiceIdx]);
                        keyStatus = SpuGetKeyStatus(spu_ch_tbl[voiceIdx]);
                    } while (keyStatus != 2 && keyStatus != 0);

                    smf_port[voiceIdx].field_16 = 0;

                    func_800485C0(voiceIdx);
                }
                else
                {
                    smf_port[voiceIdx].field_16++;
                }
            }
        }
    }

    if (voices != 0)
    {
        SpuSetKey(0, voices);
    }
}

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

void SdSeqPause(s16 seq_access_num) // 0x800A0418
{
    SpuVoiceAttr voice;
    s32          i;

    if (seq_access_num == -1)
    {
        return;
    }

    sd_int_flag = 1;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        if ((smf_port[i].smf_midi_num_3 >> 4) == seq_access_num && smf_port[i].field_16 != 0)
        {
            voice.mask         = (SPU_VOICE_VOLL | SPU_VOICE_VOLR);
            voice.voice        = spu_ch_tbl[i];
            voice.volume.left  = 0;
            voice.volume.right = 0;
            SpuSetVoiceAttr(&voice);
        }
    }

    smf_song[seq_access_num].play_status_50A = 4;

    sd_int_flag = 0;
}

void SdSeqReplay(s16 seq_access_num) // 0x800A0534
{
    SpuVoiceAttr  voice;
    SpuReverbAttr reverb;
    s32           i;
    u32           temp_v1;

    if (seq_access_num == -1)
    {
        return;
    }

    sd_int_flag = 1;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        temp_v1 = (smf_port[i].smf_midi_num_3 >> 4);
        if (temp_v1 == seq_access_num && smf_port[i].field_16 != 0)
        {
            voice.mask         = (SPU_VOICE_VOLL | SPU_VOICE_VOLR);
            voice.voice        = spu_ch_tbl[i];
            voice.volume.left  = ((smf_port[i].vol_left_C * smf_song[temp_v1].vol_left_50C) >> 7);
            voice.volume.right = ((smf_port[i].vol_right_E * smf_song[temp_v1].vol_right_50E) >> 7);
            SpuSetVoiceAttr(&voice);
        }
    }

    if (smf_song[seq_access_num].field_536 != 0)
    {
        reverb.mask        = (SPU_REV_DEPTHL | SPU_REV_DEPTHR);
        reverb.depth.right = 0;
        reverb.depth.left  = 0;
        SpuSetReverbModeParam(&reverb);
        SpuSetReverb(1);
        smf_song[seq_access_num].field_532 = 1;
    }

    smf_song[seq_access_num].play_status_50A = 1;
    control_code_set(seq_access_num);

    sd_int_flag = 0;
}

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

void SdUtFlush() // 0x800A0794
{
    SdAutoKeyOffCheck();
}

void SdUtReverbOn() // 0x800A07B4
{
    SpuReserveReverbWorkArea(SPU_ON);
    SpuSetReverb(SPU_ON);
}

void SdUtReverbOff() // 0x800A07DC
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

void SdUtSEAllKeyOff() // 0x800A08DC
{
    s32 i;
    s32 keyStatus = 0;
    u32 voices    = 0;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        if (smf_port[i].smf_midi_num_3 == 0x20)
        {
            voices |= spu_ch_tbl[i];
            smf_port[i].field_16     = 0;
            smf_port[i].midiKeyNum_6 = 0;
            SpuSetKey(0, spu_ch_tbl[i]);
            adsr_set(i, &smf_port[i]);
            rr_off(i);
            do
            {
                SpuSetKey(0, spu_ch_tbl[i]);
                keyStatus = SpuGetKeyStatus(spu_ch_tbl[i]);
            } while (keyStatus != 2 && keyStatus != 0);
        }
    }

    if (keyStatus != 0)
    {
        SpuSetKey(0, voices);
    }
}

void SdUtAllKeyOff(s16 mode) // 0x800A09E8
{
    s32 i;
    u32 voices = 0;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        voices |= spu_ch_tbl[i];
    }

    SpuSetKey(0, voices);
}

s32 SdUtGetVabHdr(s16 vabId, VabHdr* vabhdrptr) // 0x800A0A40
{
    u8* dest;
    u8* src;
    u32 i;

    if (vab_h[vabId].vab_id_0 == -1)
    {
        return -1;
    }

    dest = (u8*)vabhdrptr;
    src  = (u8*)vab_h[vabId].vab_header_4;

    for (i = 0; i < sizeof(VabHdr); i++)
    {
        *dest++ = *src++;
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/libsd/sdmain", SdVoKeyOn);

void SdVoKeyOff(s32 vab_pro, s32 pitch) // 0x800A0CFC
{
    s32 i;
    u32 voices = 0;

    sd_int_flag = 1;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        // Of the lower 16 bits of vab_pro, the upper 8 bits are used for VAB id, and the lower 8 bits specify a program number
        // Of the lower 16 bits of pitch, the upper 8 bits specify a key number in MIDI standard.
        // To specify a finer pitch, specify a key number in the lower 8 bits of pitch in 1/128 semitones.
        if (smf_port[i].field_16 != 0 &&
            smf_port[i].smf_midi_num_3 == 0x20 &&
            smf_port[i].midiKeyNum_6 == (pitch >> 8) &&
            smf_port[i].vabId_52 == (vab_pro >> 8) &&
            smf_port[i].midiProgramNum_2 == (vab_pro & 0x7F))
        {
            voices |= spu_ch_tbl[i];

            smf_port[i].field_16     = 0;
            smf_port[i].midiKeyNum_6 = 0;

            adsr_set(i, &smf_port[i]);
            SpuSetKey(0, spu_ch_tbl[i]);
            adsr_set(i, &smf_port[i]);
            SpuSetKey(0, spu_ch_tbl[i]);

            voices |= spu_ch_tbl[i];
        }
    }

    SpuSetKey(0, voices);

    sd_int_flag = 0;
}

void SdVoKeyOffWithRROff(s32 vab_pro, s32 pitch) // 0x800A0E40
{
    s32 i;
    u32 voices = 0;

    sd_int_flag = 1;

    for (i = 0; i < sd_reserved_voice; i++)
    {
        // Of the lower 16 bits of vab_pro, the upper 8 bits are used for VAB id, and the lower 8 bits specify a program number
        // Of the lower 16 bits of pitch, the upper 8 bits specify a key number in MIDI standard.
        // To specify a finer pitch, specify a key number in the lower 8 bits of pitch in 1/128 semitones.
        if (smf_port[i].field_16 != 0 &&
            smf_port[i].smf_midi_num_3 == 0x20 &&
            smf_port[i].midiKeyNum_6 == (pitch >> 8) &&
            smf_port[i].vabId_52 == (vab_pro >> 8) &&
            smf_port[i].midiProgramNum_2 == (vab_pro & 0x7F))
        {
            voices |= spu_ch_tbl[i];

            smf_port[i].field_16     = 0;
            smf_port[i].midiKeyNum_6 = 0;

            adsr_set(i, &smf_port[i]);
            rr_off(i);
            SpuSetKey(0, spu_ch_tbl[i]);
            SpuSetKey(0, spu_ch_tbl[i]);

            voices |= spu_ch_tbl[i];
        }
    }

    SpuSetKey(0, voices);

    sd_int_flag = 0;
}

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

s32 SdUtSetDetVVol(s16 voice, s16 volLeft, s16 volRight) // 0x800A1BD0
{
    SpuVoiceAttr voiceAttr;
    voiceAttr.mask         = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    voiceAttr.voice        = spu_ch_tbl[voice];
    voiceAttr.volume.left  = volLeft;
    voiceAttr.volume.right = volRight;

    SpuSetVoiceAttr(&voiceAttr);
    return 0;
}

s32 SdUtSetVVol(s16 voice, s16 volLeft, s16 volRight) // 0x800A1C1C
{
    SpuVoiceAttr voiceAttr;

    voiceAttr.mask         = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    voiceAttr.voice        = spu_ch_tbl[voice];
    voiceAttr.volume.left  = (volLeft & 0x7F) << 7;
    voiceAttr.volume.right = (volRight & 0x7F) << 7;

    SpuSetVoiceAttr(&voiceAttr);
    return 0;
}

s32 SdUtGetDetVVol(s16 voice, u16* volLeft, u16* volRight) // 0x800A1C78
{
    SpuVoiceAttr voiceAttr;
    voiceAttr.mask  = 0;
    voiceAttr.voice = spu_ch_tbl[voice];

    SpuGetVoiceAttr(&voiceAttr);

    *volLeft  = voiceAttr.volume.left;
    *volRight = voiceAttr.volume.right;
    return 0;
}

s32 SdUtGetVVol(s16 voice, u16* volLeft, u16* volRight) // 0x800A1CE8
{
    SpuVoiceAttr voiceAttr;
    voiceAttr.mask  = 0;
    voiceAttr.voice = spu_ch_tbl[voice];

    SpuGetVoiceAttr(&voiceAttr);

    *volLeft  = voiceAttr.volume.left >> 7;
    *volRight = voiceAttr.volume.right >> 7;
    return 0;
}

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

void SdSetSeqWide(s16 seq_access_num, u16 seq_wide) // 0x800A1E18
{
    smf_song[seq_access_num].seq_wide_534 = seq_wide;
}

u8 SdGetMidiVol(s16 device, s16 channel) // 0x800A1E50
{
    return smf_midi[channel + (device * 0x10)].vol_3;
}

void SdSetMidiVol(s16 device, s16 channel, s32 vol) // 0x800A1E90
{
    control_change(channel + (device * 0x10), 7, vol & 0x7F);
}

void SdSetMidiExpress(s16 device, s16 channel, s32 expression) // 0x800A1EC4
{
    control_change(channel + (device * 0x10), 11, expression & 0x7F);
}

u8 SdGetMidiExpress(s16 device, s16 channel) // 0x800A1EF8
{
    return smf_midi[channel + (device * 0x10)].expression_5;
}

u8 SdGetMidiPan(s16 device, s16 channel) // 0x800A1F38
{
    return smf_midi[channel + (device * 0x10)].pan_1;
}

void SdSetMidiPan(s16 device, s16 channel, s32 pan) // 0x800A1F78
{
    control_change(channel + (device * 0x10), 10, pan & 0x7F);
}

u8 SdGetMidiPitchBendFine(s16 device, s16 channel) // 0x800A1FAC
{
    return smf_midi[channel + (device * 0x10)].pitchBendFine_7;
}

s32 SdSetMidiPitchBendFine(s16 device, s16 channel, u8 pitchBendFine) // 0x800A1FEC
{
    smf_midi[channel + (device * 0x10)].pitchBendFine_7 = pitchBendFine & 0x7F;
    return 0;
}

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
