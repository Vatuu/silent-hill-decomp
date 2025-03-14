#ifndef _LIBSD_H
#define _LIBSD_H

/**
 * libsd: konami-customized version of libsnd?
 * Majority of functions match up with libsnd Ss versions.
 * libref.pdf v4.4 may be useful, though was likely based on earlier SDK.
 */

// MIDI related header magic.
#define SD_MAGIC_SEQp 0x53455170
#define SD_MAGIC_MThd 0x6468544D
#define SD_MAGIC_KDT  0x2054444B
#define SD_MAGIC_KDT1 0x3154444B

extern s32 sd_reverb_mode;
extern s16 sd_keyoff_mode;
extern s32 sd_interrupt_start_flag;
extern s32 sd_tick_mode;
extern u8  sd_vb_malloc_rec[];
extern s32 sd_reserved_voice;
extern s32 sd_mono_st_flag;
extern s32 sd_int_flag;
extern s32 sd_int_flag2;
extern s32 sd_timer_sync;
extern s32 smf_start_flag;
extern u32 sd_vab_transfer_offset;
extern s16 sd_seq_loop_mode;
extern s32 sd_timer_event;
extern s32 smf_file_no;

extern u32 spu_ch_tbl[24];

typedef struct _VAB_S // Pachinko Dream uses similar VAB_S struct
{
    s16            vab_id_0;
    struct VabHdr* vab_header_4; // libsnd.h
    s32            vab_prog_size_8;
    s32            vab_addr_C;
    s32            vab_start_10;
    s32            vab_total_14;
    s8             master_vol_18;
    char           field_19; // lvol? Read by some funcs but haven't seen it written to.
    char           field_1A; // rvol? ^
    s8             master_pan_1B;
} s_VAB_S;
STATIC_ASSERT_SIZEOF(s_VAB_S, 0x1C);

extern s_VAB_S vab_h[0x10];

typedef struct _SMF_TRACK_S
{
    u32 dword0;
    u32 dword4;
    u32 dword8;
    u32 dwordC;
    u32 dword10;
    u16 tempo_14;
    u16 tempo_16;
    u16 word18;
    u16 field_1A;
    u16 word1C;
    u16 field_1E;
    u8  byte20;
    u8  byte21;
    u8  byte22;
    u8  byte23;
    u8  byte24;
    u8  byte25;
    u8  byte26;
    u8  byte27;
} s_SMF_TRACK_S;
STATIC_ASSERT_SIZEOF(s_SMF_TRACK_S, 0x28);

typedef struct _SMF_S // Standard MIDI File
{
    s_SMF_TRACK_S tracks_0[32];
    s8            unk_500[4];
    void*         play_ptr_504;
    s16           vab_id_508;
    s16           play_status_50A;
    s16           vol_left_50C;
    s16           vol_right_50E;
    u32           muted_channels_510;
    void*         seq_data_ptr_514;
    s32           field_518;
    u32           beat_51C;
    s32           field_520;
    u16           field_524;
    u16           num_tracks_526;
    u16           field_528;
    u16           field_52A;
    u8            field_52C;
    u8            field_52D;
    u8            beat2_52E;
    u8            control_status_52F;
    u16           field_530;
    u16           field_532;
    u16           seq_wide_534;
    u16           field_536;
    u16           field_538;
    u8            unk_53A[2];
} s_SMF_S;
STATIC_ASSERT_SIZEOF(s_SMF_S, 0x53C);

/** s_SMF_MIDI fields are mainly changed by control_change(), which takes in a MIDI control change ID and adjusts appropriate field
 * Seems that func accepts some change IDs that are undefined in MIDI specs though... */
typedef struct _SMF_MIDI
{
    u8  vabProgNum_0;
    u8  pan_1;
    u8  field_2;
    u8  vol_3;
    u8  field_4;
    u8  expression_5;
    u8  damperPedalEnabled_6;
    u8  pitchBendFine_7;
    u32 field_8;
    u32 field_C;
    u8  footPedal_10;
    u8  effect1Controller_11;
    u8  monoMode_12;
    u8  field_13;
    u16 field_14;
    u8  unk_16[2];
    u16 field_18;
    s16 field_1A;
    s16 field_1C;
    s16 field_1E;
    u8  field_20;
    u8  field_21;
    u16 field_22;
    u8  effect1Depth_24;
    u8  nrpnLsb_25;
    u8  nrpnMsb_26;
    u8  nrpnData_27;
    s16 portamentoTime_28;
    s16 field_2A;
    s16 field_2C;
    u16 field_2E;
    u16 field_30;
    u16 field_32;
    u8  field_34;
    u8  unk_35[1];
    u8  field_36;
    u8  field_37;
    u8  field_38;
    u8  field_39;
    u8  field_3A;
    u8  field_3B;
    u16 field_3C;
    u16 field_3E;
    u16 field_40;
    u8  unk_42[2];
    u8  field_44;
    u8  field_45;
    u8  field_46;
    u8  field_47;
    u16 field_48;
    u16 field_4A;
    u16 field_4C;
    u8  unk_4E[2];
    u8  field_50;
    u8  field_51;
    u8  field_52;
    u8  field_53;
    u16 field_54;
    u8  field_56;
    u8  effect2Controller_57;
    u8  field_58;
    u8  field_59;
    u8  bank_idx_5A;
    u8  unk_5B[1];
} s_SMF_MIDI;
STATIC_ASSERT_SIZEOF(s_SMF_MIDI, 0x5C);

typedef struct _SMF_PORT
{
    u8  field_0;
    u8  unk_1[1];
    u8  midiProgramNum_2;
    u8  smf_midi_num_3;
    u16 field_4;
    u16 midiKeyNum_6;
    u16 field_8;
    u8  unk_A[2];
    u16 vol_left_C;
    u16 vol_right_E;
    u8  field_10;
    u8  field_11;
    u8  field_12;
    u8  field_13;
    u16 field_14;
    u16 field_16;
    u8  unk_18[2];
    u8  field_1A;
    u8  field_1B;
    u8  field_1C;
    u8  field_1D;
    u8  field_1E;
    u8  field_1F;
    u8  field_20;
    u8  field_21[1];
    u8  field_22;
    u8  field_23;
    u16 field_24;
    u16 field_26;
    u8  field_28;
    u8  field_29;
    u8  field_2A;
    u8  field_2B;
    u16 field_2C;
    u16 field_2E;
    u8  field_30;
    u8  unk_31[1];
    u8  field_32;
    u8  field_33;
    u16 field_34;
    u16 field_36;
    u8  field_38;
    u8  field_39;
    u8  field_3A;
    u8  field_3B;
    u16 field_3C;
    s16 field_3E;
    u16 field_40;
    u8  randomTblIndex_42;
    u8  field_43;
    u8  field_44;
    u8  field_45;
    u16 field_46;
    u16 field_48;
    u16 field_4A;
    s16 field_4C;
    u16 field_4E;
    u16 field_50;
    u8  vabId_52;
    u8  unk_53[1];
} s_SMF_PORT;
STATIC_ASSERT_SIZEOF(s_SMF_PORT, 0x54);

extern s_SMF_MIDI smf_midi[2 * 16]; // 2 devices with 16 channels each?
extern s_SMF_MIDI D_800C82B8;       // smf_midi[32] ? used in sound_off
extern s_SMF_PORT smf_port[24];
extern s_SMF_S smf_song[2];

// sdmain.c

void tone_adsr_back(s16);

void SdWorkInit();
void SdInit(void);
void SdStart(void);
void SdStart2(void);
void SdSetTickMode(s32 tick_mode);
void SdSeqCalledTbyT(void);
void SdSetStereo(void);
void SdSetMono(void);
char SdSetReservedVoice(char voices);
void SdSetTableSize(void);

void SdEnd();
void SdQuit(void);
void SdSetSerialAttr(char s_num, char attr, char mode);
void SdSetSerialVol(s16 s_num, s16 voll, s16 volr);
void SdSetMVol(s16 left, s16 right);

s16  SdVabTransBody(u8* addr, s16 vabid);
s16  SdVabTransBodyPartly(u8* addr, u32 bufsize, s16 vabid);
s16  SdVabTransCompleted(s16 immediateFlag);
void SdVabClose(s16 vab_id);
void SdSetAutoKeyOffMode(s16 mode);
void SdAutoKeyOffCheck();
s16  SdSeqOpen(s32* addr, s16 vab_id);
s16  SdSeqOpenWithAccNum(s32* addr, s16 vab_id, s16 seq_access_num);
void SdSeqPlay(s16 seq_access_num, u8 play_mode, s16 l_count);
void SdSeqStop(s16 seq_access_num);
void SdSeqClose(s16 seq_access_num);
void SdSeqPause(s16 seq_access_num);
void SdSeqReplay(s16 seq_access_num);
void SdSeqSetVol(s16 seq_access_num, s16 voll, s16 volr);
void SdSeqGetVol(s16 seq_access_num, s16* voll, s16* volr);
void SdUtFlush(void);
void SdUtReverbOn(void);
void SdUtReverbOff(void);
s16  SdUtSetReverbType(s16 type);
void SdUtSetReverbDepth(s16 left, s16 right);
void SdSetRVol(s16 left, s16 right);
void SdUtSEAllKeyOff();
void SdUtAllKeyOff(s16 mode);

void SdVoKeyOff(s32 vab_pro, s32 pitch);
void SdVoKeyOffWithRROff(s32 vab_pro, s32 pitch);

s16 SdGetSeqStatus(s16 seq_access_num);

u16  SdGetTempo(s16 seq_access_num);
void SdSetTempo(s16 seq_access_num, s16 tempo);
void SdSetSeqWide(s16 seq_access_num, u16 seq_wide);
u8   SdGetMidiVol(s16 device, s16 channel);
void SdSetMidiVol(s16 device, s16 channel, s32 vol);
void SdSetMidiExpress(s16 device, s16 channel, s32 expression);
u8   SdGetMidiExpress(s16 device, s16 channel);
u8   SdGetMidiPan(s16 device, s16 channel);
void SdSetMidiPan(s16 device, s16 channel, s32 pan);
u8   SdGetMidiPitchBendFine(s16 device, s16 channel);
s32  SdSetMidiPitchBendFine(s16 device, s16 channel, u8 pitchBendFine);
s32 SdGetTrackTranspause();
s32 SdSetTrackTranspause();
s32 SdGetTrackMute(s16 seq_access_num, s32 channel);
s32 SdSetTrackMute(s16 seq_access_num, s32 channel);
s32 SdGetSeqControlStatus(s16 seq_access_num);
s16 SdGetSeqPlayStatus(s32 seq_access_num);
u32 SdGetSeqBeat(s16 seq_access_num);
s32 SdGetSeqBeat2(s16 seq_access_num);

// sdmidi.c

void tre_calc(s_SMF_PORT*);
void vib_calc(s_SMF_PORT*);
void random_calc(s_SMF_PORT* midiPort);
void volume_calc(s_SMF_PORT*, s_SMF_MIDI*);
void smf_vol_set(s32 midiChannel, s32 voice, s32 volLeft, s32 volRight);
void master_vol_set();
void seq_master_vol_set(s32 seq_access_num);
void toremoro_set();

void pitch_calc(s_SMF_PORT*, s32);
void midi_mod(s_SMF_MIDI* midiTrack);
void midi_porta(s_SMF_MIDI* midiTrack);
void replay_reverb_set(s16 seq_access_num);
void midi_vsync();
void sound_seq_off(s32);
void sound_off();
void set_note_on_mb(void);
void adsr_set(s32 voice, s_SMF_PORT* midiPort);
void rr_off(s32 voice);

void key_off(u8 midiNum, u8 keyNum);
void key_press(void);

void control_change(u8, s32, s32);
void program_change(u8 midiChannel, u8 progNum);
void chan_press(void);

void control_code_set(s32 seq_access_num);

// sdmidi2.c

s32  smf_timer();
void smf_timer_set();
void smf_timer_end();
void smf_timer_stop();
void smf_vsync(void);
s32  MemCmp(u8* str1, u8* str2, s32 count);
s32  readMThd(u32 offset);
s32  readMTrk(u32 offset);
s32  readEOF(u32 offset);

// to32bit/to16bit/len_add only seem used inside sdmidi2.c, can probably be removed from header.
s32  to32bit(char arg0, char arg1, char arg2, char arg3);
s32  to16bit(char arg0, char arg1);
void len_add(s32* ptr, s32 val);

void midi_file_out(s16);
void midi_smf_main();

s16 midi_smf_stat(s32);

// ssmain.c
void SsSetMVol(s16 left, s16 right);
void SsEnd(void);
void SsSetSerialAttr(char s_num, char attr, char mode);
void SsSetSerialVol(char s_num, s16 voll, s16 volr);
void SsUtAllKeyOff(s16 mode);

#endif /* _LIBSD_H */
