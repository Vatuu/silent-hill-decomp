#ifndef _BODYPROG_SOUNDSYSTEM_H
#define _BODYPROG_SOUNDSYSTEM_H

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

// Used for loading XA files. `field_0` holds commands for `Sd_CdPrimitiveCmdTry`
typedef struct
{
    u8 field_0;
    u8 field_1;
} s_800C15F0;

// TODO: Field with `_24` seems to be part of a thing related to how XA files works.
typedef struct
{
    u8  xaFileIdx_0;
    u8  unk_1; // } Padding?
    u8  unk_2; // }
    u8  unk_3; // }
    u32 sector_4      : 24;
    u8  field_4_24    : 8; // Index. Indicates the element of the group index defined at `field_8_24`.
    u32 audioLength_8 : 24;
    u8  field_8_24    : 8; // Index. Indicate some sort of group.
} s_XaItemData;
STATIC_ASSERT_SIZEOF(s_XaItemData, 12);

typedef struct
{
    u16 cdErrorCount_0;    /** Counter for failed attempts at the moment of process a primite command. */
    u16 xaAudioIdxCheck_2; /** XA Audio index. Used for check if the file exist. */
    u16 xaAudioIdx_4;      /** XA Audio index. Used for playing the audio. */
    u16 field_6;
    u16 field_8[1]; // Unknown size.
    s16 field_A;
    s16 field_C;
    u16 field_E; // Related to the handling of music layers.
    u16 field_10;
    u8  isStereoEnabled_12; // `bool`
    s8  isXaStopping_13; /** `bool` | It stop any play from a XA file in memory from playing, when doing it this is
                          * set to `true`, otherwise it keep in `false`. */
    u8  bgmFadeSpeed_14; /** Value to get rested in order to speed the music fade. Range: [0, 2], default: 0. */
    u8  isVabLoading_15; /** `bool` | Loading: `true`, Nothing loading: `false`, default: Nothing loading. */
    u8  isXaLoading_16;  /** `bool` | Loading: `true`, Nothing loading: `false`, default: Nothing loading. */
    u8  muteGame_17;     /** `bool` | Mutes the game. If the value is `true`, the whole game audio will progressively get lower
	                      * in volume until mute. The sounds will keep playing, but muted.
						  */
} s_800C1658;

typedef struct
{
    u8 vabLoadState_0;   /** Load VAB audio state. */
    u8 xaLoadState_1;    /** Load XA audio state. */
    u8 xaStopState_2;    /** Stop XA audio streaming state. */
    u8 xaPreLoadState_3; /** Prepare Load XA audio state. Positions the current read point to the one where the XA audio to load resides.
                          * This is arbitrary as `xaLoadState_1` is already used for that.
                          */
} s_AudioStreamingStates;

// Game audio channels volume configuration struct.
// @note Could the values of the fields be some sort of fractional value?
typedef struct
{
    s16 volumeXa_0; /** This and the second field are volume controllers for XA audio files. This field is used more generally while the
                     * second field is used by `Sd_XaAudioPlay` in order to set the audio volume.
                     */
    s16 volumeXa_2;
    u16 volumeSe_4;
    s16 volumeBgm_6; /** This and the fifth field are volume controllers for music.
                      * This field is like the "parent" that ensures `volumeBgm_8` is at the same volume.
                      */
    s16 volumeBgm_8;
    s16 volumeGlobal_A;
	
	/** As main difference with previous volume controlers, this seems to influence the behavior of the game.
	 * When reducing `globalVolumeXa_E`, the current voice line continues playing at the same
	 * volume while the next plays at the volume set here. Other volume controllers don't do this and instantly adjust audio volume.
	 *
	 * This are also the values modified by the game configuration menu.
	 */
    u8  globalVolumeSe_C;  // Global SE volume channel.
    u8  globalVolumeBgm_D; // Global BGM volume channel.
    u8  globalVolumeXa_E;  // Global Voice volume channel (not configurable).
} s_ChannelsVolumeController;

// Used for the load of XA audios and related to VSync values???
typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8; // Somebody defined this as an individual global variable in the symbol file as `g_Game_VSyncTimeSinceBoot`.
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

extern s_800C37D4 D_800A986C[];

extern u8 g_Sd_ReverbDepths[];

extern s_XaItemData g_XaItemData[];

/** Values capped at 127. */
extern s8 g_Sd_BgmLayers[8];

// Likely declared as `static` as this is only used in `Sd_XaAudioPlay`.
// `Sd_XaPreLoadAudioInit` (similar to `Sd_XaAudioPlay`) has a
// variable that works the same and is only used there.
extern u16 D_800C15CA;

// Likely declared as `static` as this is only used in `Sd_XaAudioPlay`
extern u16 D_800C15D0;

// Likely declared as `static` inside the function that uses it.
extern u32 D_800C15CC;

// Likely declared as `static` inside the function that uses it.
extern u32 D_800C15D4;

// Likely declared as `static` inside the function that uses it.
extern s16 D_800C15C4;

// Likely declared as `static` inside the function that uses it.
extern s16 D_800C15C6;

// Likely declared as `static` inside the function that uses it.
extern s16 D_800C15C8;

// Likely declared as `static` inside the function that uses it.
extern u16 D_800C15D0;

// Only used in `sd_work_init` as iterator variable.
extern s32 D_800C15B8;

// Only used in `Sd_CmdPoolAdd` as iterator variable.
extern s32 D_800C15D8;

// Only used in `Sd_CmdPoolAdd` as iterator variable.
extern s32 D_800C15DC;

// Only used in `Sd_CmdPoolUpdate` as iterator variable.
extern s32 D_800C15E0;

extern s_800C15F0 D_800C15F0;

extern s_800C1658 D_800C1658;

/** @brief Hold states for different audio types streaming. */
extern s_AudioStreamingStates g_Sd_AudioStreamingStates;

extern s_ChannelsVolumeController g_Sd_ChannelsVolume;

extern u8 g_Sd_ReverbDepth;

extern s_800C1688 D_800C1688;

extern s_800C1698 D_800C1698;

/** Command pool related to audio and streaming.
 * Seems like `Sd_CmdPoolExecute` is the main function on charge of executing commands,
 * as this function is part of the mainloop function.
 */
extern u8 g_Sd_CmdPool[32];

extern u8 D_800C37C8;

extern u32 D_800C37CC;

extern s_800C37D4* D_800C37D4;

extern s_800C37D4* D_800C37D8;

extern u8 D_800C37DC; // Boolean.

extern u8 g_Sd_CurrentCmd;

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

/** Manipulate the BGM audio layers. Can't be determined if this function
 * is fully in charge of that as `func_80035F4C` (not directly related to the SD audio system)
 * triggers and handles in-game music.
 */
void func_80046C54(u8 arg0, u8 vol);

/** @brief Loads and plays XA audio defined at `g_XaItemData`. */
void Sd_XaAudioPlay(void);

/** @brief Initializes the process to play an XA audios defined at `g_XaItemData`. */
void Sd_XaAudioPlayCmdAdd(u16 sfx);

/** @unused Gets the length of XA audios defined at `g_XaItemData`. */
s32 Sd_XaAudioLengthGet(s32 idx);

void Sd_XaAudioStopCmdAdd(void);

void Sd_XaPreLoadAudio(u16 xaIdx);

void Sd_XaPreLoadAudioCmdAdd(s32 xaIdx);

/** @brief Stops the streaming of the currently loaded XA audio in memory. */
void Sd_XaAudioStop(void);

/** @brief Sets the volume for the global channels of the music, sound effects, and voices. */
void Sd_SetVolume(u8 xaVol, s16 bgmVol, u8 seVol);

/** @brief Sets the volume for the channels of music. */
void Sd_SetVolBgm(s16 volLeft, s16 volRight);

/** @brief Sets the volume for the channels of voices. */
void Sd_SetVolXa(s16 volLeft, s16 volRight);

/** @brief Sets the volume for the channels of sound effects. */
s16 Sd_GetVolSe(s16 arg0);

/** Updates and add commands to a command pool. */
void Sd_CmdPoolAdd(u8 cmd);

/** Updates a command pool by shifting a field. */
void Sd_CmdPoolUpdate(void);

void func_80047B80(void);

void Sd_SetReverbDepth(u8 depth);

void Sd_SetReverbEnable(s32 mode);

void func_80047B24(s32 arg0);

void func_80047D1C(void);

void func_80047D50(void);

void func_80047DB0(void);

void func_80047E3C(void);

void func_80047F18(void);

void Sd_StopSeq(void);

void Sd_CmdPoolExecute(void);

/** @brief Executes a new primitive command and checks the status against the previous.
 * If the previous primitive commands haven't completed, it starts
 * adding to `D_800C1658.cdErrorCount_0` each time the process fails. When it
 * reaches 600 failed attemps, it restarts the CD-ROM system.
 */
u8 Sd_CdPrimitiveCmdTry(s32 com, u8* param, u8* res);

#endif
