#ifndef _SOUND_SYSTEM_H
#define _SOUND_SYSTEM_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` that has been identified to be
 * related the audio system of the game, but haven't been recognized
 * to be a function from the Konami's LIBSD system.
 *
 * Code here can still be refered as part of the SD system, but no
 * function with symbols recognized from the SD system should be here.
 */

// ==========
// CONSTANTS
// ==========

// TODO: Part of an enum?
#define AUDIO_TYPE_MONO   1
#define AUDIO_TYPE_STEREO 2

// ========
// STRUCTS
// ========

typedef struct
{
    u8  xaFileIdx_0;
    u8  unk_1; // } Padding?
    u8  unk_2; // }
    u8  unk_3; // }
    u32 sector_4      : 24;
    u8  field_4_24    : 8; // Index. This indicate the element of the group idx defined at `field_8_24`.
    u32 audioLength_8 : 24;
    u8  field_8_24    : 8; // Index. This indicate some sort of group.
} s_XaItemData;
STATIC_ASSERT_SIZEOF(s_XaItemData, 12);

typedef struct
{
    u16 timer_0; // A timer related to audio command processes.
    u16 xaAudioIdxCheck_2; // XA Audio index. Used for check if the file exist.
    u16 xaAudioIdx_4;      // XA Audio index. Used for playing the audio.
    u16 field_6;
    u16 field_8[1]; // Unknown size.
    s16 field_A;
    s16 field_C;
    u16 field_E;
    u16 field_10;
    u8  isStereoEnabled_12; // `bool`
    s8  field_13;
    u8  bgmFadeSpeed_14; /** Value to get rested in order to speed the music fade. Range: [0, 2], default: 0. */
    u8  isVabLoading_15; /** `bool` | Loading: `true`, Nothing loading: `false`, default: Nothing loading. */
    u8  field_16;        /** `bool` | XA streaming related. If a voiceline audio is playing, this is set to `false`, otherwise `true`. */
    u8  muteGame_17;     /** `bool` | Mutes the game. If the value is `true`, the whole game audio will progressively lower
	                      * in volume until mute. The sounds will keep playing, but muted.
						  */
} s_800C1658;

typedef struct
{
    u8 vabLoadState_0; // States related to audio streaming. VAB Audio.
    u8 field_1;        // States related to audio streaming.
    u8 field_2;        // States related to audio streaming.
    u8 field_3;
} s_Sd_AudioLoadStates;

// Game current volume configuration struct?
typedef struct
{
    s16 volumeXa_0; // Could also be event timer? Most values are shared with `field_2`.
    s16 field_2;    // `volumeVoice_2`?
    u16 volumeSE_4;
    s16 field_6;     // Related to the BGM volume.
    s16 field_8;     // Related to the BGM volume.
    s16 volumeGlobal_A;
	
	// As main difference with previous volume controlers, this seems to influence the behaviour of the game.
	// When reducing `globalVolumeXa_E`, the current voice line will continue playing at the same
	// volume while the next will be play at the volume set here. Other volume controllers don't do this and instantly adjust audio volume.
    u8  globalVolumeSe_C;  // Global SE volume channel.
    u8  globalVolumeBgm_D; // Global BGM volume channel.
    u8  globalVolumeXa_E;  // Global Voice volume channel (not configurable).
} s_800C1678;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
} s_800C1688;

/** Sound struct for currently used SFX? */
typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A; // Pitch?
    s16 volumeLeft_C;
    s16 volumeRight_E;
} s_800C1698;

typedef struct
{
    s8  field_0;
    s8  unk_1;
    u16 field_2;
    u32 field_4; // VA Sound Sector count?
    s32 field_8;
} s_800C37D4;

// ========
// GLOBALS
// ========

extern u8 g_Sd_ReverbDepthsList[]; // 0x800AA5E0

extern s_800C37D4 D_800A986C[];

extern s_XaItemData g_XaItemData[]; // 0x800AA894

// Only used in `sd_work_init` as iterator variable.
extern s32 D_800C15B8;

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15D8;

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15DC;

// Only used in `func_80047A70` as iterator variable.
extern s32 D_800C15E0;

extern s_800C1658 D_800C1658;

extern s_Sd_AudioLoadStates g_Sd_AudioLoadState; // 0x800C1670

extern s_800C1678 D_800C1678;

extern u8 g_Sd_ReverbDepth; // 0x800C1687;

extern s_800C1688 D_800C1688;

extern s_800C1698 D_800C1698;

extern u8 D_800C37C8;

extern u32 D_800C37CC;

/** Command pool related to audio and streaming.
 * Seems like `func_800485D8` is the main function on charge of executing commands,
 * as this function is part of the mainloop function.
 */
extern u8 D_800C16A8[32];

extern s_800C37D4* D_800C37D4;

extern s_800C37D4* D_800C37D8;

extern u8 D_800C37DD;

// ==========
// FUNCTIONS
// ==========

/** @brief Passes a command to the sound driver.
 * Plays SFX among other things.
 */
void Sd_EngineCmd(u32 cmd);

u16 func_80045BC8(void);

/** @brief Sets the audio system to stereo or mono. */
void Sd_AudioSystemSet(u8 isStereo);

/** @brief Executes `SdUtKeyOffV` and runs through the element 23 of `smf_port`. */
void Sd_LastVoiceKeyOff(void);

/** @brief Executes `SdUtKeyOffV` and runs through all elements of `smf_port`. */
void Sd_AllVoicesKeyOff(void);

/** @brief Executes `SdUtKeyOffVWithRROff` and runs through all elements of `smf_port`. */
void Sd_AllVoicesKeyOffVWithRROff(void);

/** @brief Plays XA audios defined at `g_XaItemData`. */
void Sd_XaAudioPlay(u16 sfx); // 0x80046D3C

/** @unused Gets the length of XA audios defined at `g_XaItemData`. */
s32 Sd_XaAudioLengthGet(s32 idx); // 0x80046DCC

/** @brief Sets the volume for the global channels of the music, sound effects, and voices. */
void Sd_SetVolume(u8 xaVol, s16 bgmVol, u8 seVol);

void Sd_SetVolBgm(s16 volLeft, s16 volRight); // 0x80047808

void Sd_SetVolXa(s16 volLeft, s16 volRight); // 0x80047860

s16 Sd_GetVolSe(s16 arg0); // 0x800478B8

/** Updates and add commands to a command pool. */
void func_800478DC(u8 cmd); // 0x800478DC

/** Updates a command pool by shifting a field. */
void func_80047A70(void); // 0x80047A70

void func_80047B80(void); // 0x80047B80

void Sd_SetReverbDepth(u8 depth); // 0x80047AD0

void Sd_SetReverbEnable(s32 mode); // 0x80047AFC

void func_80047B24(s32 arg0); // 0x80047B24

void func_80047D1C(void); // 0x80047D1C

void func_80047D50(void); // 0x80047D50

void func_80047DB0(void); // 0x80047DB0

void func_80047E3C(void); // 0x80047E3C

void func_80047F18(void); // 0x80047F18

void func_800485D8(void); // 0x800485D8


#endif
