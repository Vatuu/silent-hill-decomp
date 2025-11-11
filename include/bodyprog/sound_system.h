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
    union
    {
        s8  field_0[3];
        u16 field_01;
    } field_F;
    u8  field_14;
    u8  field_15;
    u8  field_16;
    u8  muteGame_17; // Boolean. Mutes the game.
	                 // If the value is 1 the whole game audio will progressively start lowering
				     // it's volume until it becomes mute. The sounds will still be playing, but muted.
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
    s16 volumeXa_0; // Might be wrong, but it's used in a `Sd_SetVolBXa` call. Could also be event timer? Most values are shared with `field_2`.
    s16 field_2;    // `volumeVoice_2`?
    u16 volumeSE_4;
    s16 field_6;     // Related to the Bgm volume
    s16 field_8;     // Related to the Bgm volume
    s16 volumeGlobal_A;
	
	// As main difference with previous volume controlers, this seems to influenciate the behaviour of the game.
	// For example: when reducing `globalVolumeXA_E` the current voice line will still play while at the same
	// volume while the next will be play with the volume stablished here. The other volume controlers doesn't
	// that and they instantly adjust the audio volume.
    u8  globalVolumeSE_C;  // Global SE volume channel
    u8  globalVolumeBGM_D; // Global BGM volume channel
    u8  globalVolumeXA_E;  // Global Voice volume channel (Not configurable)
} s_800C1678;

// ========
// GLOBALS
// ========

extern u8 g_Sound_ReverbDepth; // 0x800C1687;

/** `bool` */
extern u8 g_Sound_IsStereoEnabled; // 0x800C166A

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15D8;

// Only used in `func_800478DC` as iterator variable.
extern s32 D_800C15DC; // Index.

// Only used in `func_80047A70` as iterator variable.
extern s32 D_800C15E0;

// Very likely to be related to music.
extern s_800C1658 D_800C1658;

extern s_800C1670 D_800C1670;

extern s_800C1678 D_800C1678;

// ==========
// FUNCTIONS
// ==========

/** @brief Passes a command to the sound driver.
 * Plays SFX among other things.
 */
void Sd_EngineCmd(u32 cmd);

u16 func_80045BC8(void);

/** @brief Sets the audio system to stereo or mono. */
void Sd_AudioSystemSet(u8 isStereo); // 0x80045D28

/** @brief Executes `SdUtKeyOffV` and runs through the element 23 of `smf_port`. */
void Sd_LastVoiceKeyOff(void); // 0x800468EC

/** @brief Executes `SdUtKeyOffV` and runs through all elements of `smf_port`. */
void Sd_AllVoicesKeyOff(void); // 0x800469AC

/** @brief Executes `SdUtKeyOffVWithRROff` and runs through all elements of `smf_port`. */
void Sd_AllVoicesKeyOffVWithRROff(void); // 0x800469E8

/** @brief Sets the volume for the global channels of the music, sound effects, and voices. */
void Sd_SetVolume(u8 xaVol, s16 bgmVol, u8 seVol); // 0x80047798

#endif
