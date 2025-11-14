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
    u16 timer_0; // A timer related to audio command processes.
    u16 field_2;
    u16 field_4;
    u16 field_6;
    u16 field_8[1]; // Unknown size.
    s16 field_A;
    s16 field_C;
    u16 field_E;
    u16 field_10;
    u8  isStereoEnabled_12; // `bool`
    s8  field_13;
    u8  bgmFadeSpeed_14; /** Value to get rested in order to speed the music fade. Range: [0, 2], default: 0. */
    u8  field_15;
    u8  field_16;    // `bool` | XA streaming related. If a voiceline audio is playing, this is set to `false`, otherwise `true`.
    u8  muteGame_17; // `bool` | Mutes the game. If the value is `true`, the whole game audio will progressively lower
	                 // in volume until mute. The sounds will keep playing, but muted.
} s_800C1658;

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} s_800C1670;

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

// ========
// GLOBALS
// ========

// Only used in `sd_work_init` as iterator variable.
extern s32 D_800C15B8;

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15D8;

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15DC;

// Only used in `func_80047A70` as iterator variable.
extern s32 D_800C15E0;

// Very likely to be related to music.
extern s_800C1658 D_800C1658;

extern s_800C1670 D_800C1670;

extern s_800C1678 D_800C1678;

extern u8 g_Sound_ReverbDepth;

// Command pool related to audio and streaming.
extern u8 D_800C16A8[32];

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

/** @brief Sets the volume for the global channels of the music, sound effects, and voices. */
void Sd_SetVolume(u8 xaVol, s16 bgmVol, u8 seVol);

#endif
