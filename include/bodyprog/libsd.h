#ifndef _LIBSD_H
#define _LIBSD_H

/*
   libsd: konami-customized version of libsnd?
   Majority of functions match up with the libsnd Ss versions
   libref.pdf v4.4 may be useful, though was likely based on earlier SDK
*/

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

/* sdmain.c */
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

void SdSetAutoKeyOffMode(s16 mode);
void SdAutoKeyOffCheck();

void SdUtFlush(void);
void SdUtReverbOn(void);
void SdUtReverbOff(void);
s16  SdUtSetReverbType(s16 type);
void SdUtSetReverbDepth(s16 left, s16 right);
void SdSetRVol(s16 left, s16 right);

void SdUtAllKeyOff(s16 mode);

/* sdmidi.c */
void midi_vsync();

void sound_off();
void set_note_on_mb(void);

void key_press(void);

void chan_press(void);

void control_code_set(void);

/* sdmidi2.c */
s32  smf_timer(void);
void smf_timer_set();

void smf_vsync(void);

// to32bit/to16bit/len_add only seem used inside sdmidi2.c, can probably be
// removed from header
s32  to32bit(char arg0, char arg1, char arg2, char arg3);
s32  to16bit(char arg0, char arg1);
void len_add(s32 *ptr, s32 val);

void midi_smf_main();

/* ssmain.c */
void SsSetMVol(s16 left, s16 right);
void SsEnd(void);
void SsSetSerialAttr(char s_num, char attr, char mode);
void SsSetSerialVol(char s_num, s16 voll, s16 volr);
void SsUtAllKeyOff(s16 mode);

#endif /* _LIBSD_H */
