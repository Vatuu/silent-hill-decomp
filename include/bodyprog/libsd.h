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
extern u32 sd_reserved_voice;
extern s32 sd_mono_st_flag;
extern s32 sd_int_flag;
extern s32 sd_int_flag2;
extern s32 sd_timer_sync;
extern s32 smf_start_flag;
extern u32 sd_vab_transfer_offset;
extern s16 sd_seq_loop_mode;

extern s32 spu_ch_tbl[24];

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
    s16           field_530;
    u16           field_532;
    s16           seq_wide_534;
    u16           field_536;
    u16           field_538;
    u8            unk_53A[2];
} s_SMF_S;

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

void SdSeqSetVol(s16 seq_access_num, s16 voll, s16 volr);
void SdSeqGetVol(s16 seq_access_num, s16* voll, s16* volr);
void SdUtFlush(void);
void SdUtReverbOn(void);
void SdUtReverbOff(void);
s16  SdUtSetReverbType(s16 type);
void SdUtSetReverbDepth(s16 left, s16 right);
void SdSetRVol(s16 left, s16 right);

void SdUtAllKeyOff(s16 mode);

s16 SdGetSeqStatus(s16 seq_access_num);

u16  SdGetTempo(s16 seq_access_num);
void SdSetTempo(s16 seq_access_num, s16 tempo);
void SdSetSeqWide(s16 seq_access_num, s16 seq_wide);

s32 SdGetTrackTranspause();
s32 SdSetTrackTranspause();
s32 SdGetTrackMute(s16 seq_access_num, s32 channel);
s32 SdSetTrackMute(s16 seq_access_num, s32 channel);
s32 SdGetSeqControlStatus(s16 seq_access_num);
s16 SdGetSeqPlayStatus(s32 seq_access_num);
u32 SdGetSeqBeat(s16 seq_access_num);
s32 SdGetSeqBeat2(s16 seq_access_num);

// sdmidi.c

void midi_vsync();

void sound_off();
void set_note_on_mb(void);

void key_press(void);

void chan_press(void);

void control_code_set(void);

// sdmidi2.c

s32  smf_timer(void);
void smf_timer_set();

void smf_vsync(void);

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
