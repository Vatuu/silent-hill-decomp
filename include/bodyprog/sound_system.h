#ifndef _BODYPROG_SOUNDSYSTEM_H
#define _BODYPROG_SOUNDSYSTEM_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` that has been identified to be
 * related the audio system of the game, but haven't been recognized
 * to be a function from the Konami's LIBSD system.
 *
 * This code is game-specific and not part of the library itself.
 * This code specifically handle file streaming and some general
 * sound game effects.
 *
 * @note Name recognition.
 * `Tokimeki Memorial ~Forever With You~` and `Konami International Rally Championship` symbols
 * indicate that what are named `commands` in the decomp are actually named as `tasks`. TM
 * suggests that at some point, they were called `events`.
 */

// ==========
// CONSTANTS
// ==========

// TODO: Part of an enum?
#define AUDIO_TYPE_MONO   1
#define AUDIO_TYPE_STEREO 2

// ==============
// HELPER MACROS
// ==============

/** @brief Packs an audio type and program index into a single  value.
 *
 * The third field from `s_VabInfo` is obfuscated.
 * The value get pass to `SdVoKeyOn` through the first argument (`vab_pro`) where it is used to give a
 * value to the variables `prog` (by doing the equivalent of `vab_progIdx_2 & 0x7F`) and `vabid`
 * (by doing the equivalent of `vab_progIdx_2 >> 8`).
 * This indicates from the values that are 516 (0x204), `prog` receives the value of
 * 2 while `vabid` would receive 4. This also fits with other values like 256 (0x100) and 514 (0x202).
 *
 * The first argument is related to `e_AudioType` and `g_Sd_AudioType`, used to
 * access the index of `vab_h`, which apparently allocates VAG data in memory.
 *
 * The second value is the index for a VAB-specific attribute named `program`.
 */
#define TYPE_AND_PROG_SFX(audioType, progIdx) \
    (audioType << 8) + progIdx

// ======
// ENUMS
// ======

/** @brief Audio types. */
typedef enum _AudioType
{
    AudioType_MusicKey      = 0,
    AudioType_BaseAudio     = 0,
    AudioType_Weapon        = 1,
    AudioType_Ambient       = 2,
    AudioType_SpecialScreen = 2,
    AudioType_MusicBank     = 3
} e_AudioType;

// ========
// STRUCTS
// ========

// Used for loading XA files. `field_0` holds commands for `Sd_CdPrimitiveCmdTry`
typedef struct
{
    u8 field_0;
    u8 field_1;
} s_800C15F0;

typedef struct
{
    u16 cdErrorCount_0;             /** Counter for failed attempts when processing a primitive command. */
    u16 xaAudioIdxCheck_2;          /** XA Audio index. Used to check if the file exists. */
    u16 xaAudioIdx_4;               /** XA Audio index. Used to play the audio. */
    u16 bgmLoadedSongIdx_6;         /** Index of the currently loaded music. */
    u16 lastVabAudioLoadedIdx_8[3]; /** Stores the index of the last loaded VAB audio that's not a music note. */
    u16 field_E;                    /** MIDI channel assignment for BGM layers.
                                     * Used to assign the corresponding MIDI channel for BGM layers.
                                     *
                                     * This requires further investigation for a proper explanation. This is used
                                     * to access values from `D_800AA604` columns in an odd way, as the values assigned
                                     * are from `g_UnknownBgmTable1`, which range from 769 to 808 (including 0).
                                     * However, the variables are cast as `u8`, which removes
                                     * the second byte (range in hexadecimal: 0x1003 to 0x2803), leaving only the first byte
                                     * ranging from 1 to 40 (also including 0).
                                     */
    u16 field_10;                   /** Temporarily stores a value intended for `field_E` so it can be assigned when the function
                                     * that assigns it is executed. Part of a rule for `SD_Call`.
                                     */
    u8  isStereoEnabled_12;         /** `bool` */
    s8  isXaStopping_13;            /** `bool` | Set to `true` to stop an XA file in memory from playing, otherwise `false`.
                                     */
    u8  bgmFadeSpeed_14;            /** Music fade speed. Range: `[0, 2]`, default: 0. */
    u8  isAudioLoading_15;          /** `bool` | If a KDT or VAB file is being loaded. | Loading: `true`, Nothing loading: `false`, default: Nothing loading. */
    u8  isXaNotPlaying_16;          /** `bool` | Playing: `false`, Nothing playing: `true`, default: Nothing playing. */
    u8  muteGame_17;                /** `bool` | Mutes the game. If the value is `true`, the whole game audio will progressively get lower
                                     * in volume until mute (the sounds will keep playing, but muted).
                                     */
} s_Sd_AudioWork;

typedef struct
{
    u8 audioLoadState_0; /** Load VAB audio and KDT music key notes state. */
    u8 xaLoadState_1;    /** Load XA audio state. */
    u8 xaStopState_2;    /** Stop XA audio streaming state. */
    u8 xaPreLoadState_3; /** Prepare Load XA audio state. Positions the current read point to the one where the XA audio to load resides. */
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
     * These are also the values modified in the configuration menu.
     */
    u8  globalVolumeSe_C;  // Global SE volume channel.
    u8  globalVolumeBgm_D; // Global BGM volume channel.
    u8  globalVolumeXa_E;  // Global Voice volume channel (not configurable).
    u8  reverbDepth_F;
} s_ChannelsVolumeController;

// Used for the load of XA audios and related to VSync values???
typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8; // Somebody defined this as an individual global variable in the symbol file as `g_Game_VSyncTimeSinceBoot`.
} s_800C1688;

/** Sound struct for currently used SFX.
 * @note It is recomended to read VAB file format documentation to fully understand this struct.
 */
typedef struct
{
    u8  audioVabIdx_0;
    u8  pad_1;
    s16 typeIdx_2; /** `e_AudioType` */
    s16 progIdx_4;
    s16 toneIdx_6;
    s16 noteIdx_8;
    s16 pitch_A;
    s16 volumeLeft_C;
    s16 volumeRight_E;
} s_VabPlayingInfo;

/** @note It is recomended to read VAB file format documentation to fully understand this struct. */
typedef struct
{
    u8  audioVabIdx_0; /** Index of audio inside VAB files. */
    u8  pad_1;
    u16 vab_progIdx_2; /** See `TYPE_AND_PROG_SFX`. */
    u8  noteIdx_4;
    s8  field_5;       // Volume??? (Tested In-game indeed changes the volume)
} s_VabInfo;

// TODO: Field with `_24` seems to be part of a thing related to how XA files work.
typedef struct
{
    u8  xaFileIdx_0;
    u8  pad_1[3];
    u32 sector_4      : 24;
    u8  field_4_24    : 8; // Index. Element of the group index defined at `field_8_24`.
    u32 audioLength_8 : 24;
    u8  field_8_24    : 8; // Index. Indicate some sort of group.
} s_XaItemData;
STATIC_ASSERT_SIZEOF(s_XaItemData, 12);

// Used to store KDT and VAB data access.
typedef struct
{
    s8  typeIdx_0;       /** See `e_AudioType`. */
    s8  pad_1;
    u16 vagDataOffset_2; /** Offset of VAG data in VAB files. */
    u32 fileSize_4;      /** VAB file size. */
    s32 fileOffset_8;    /** VAB audio offset in the file container. */
} s_AudioItemData;

// ========
// GLOBALS
// ========

extern s32 D_800A9FDC[];

extern s_AudioItemData g_AudioData[];

extern u8 g_Sd_ReverbDepths[];

extern u8 D_800AA604[][];

extern s_XaItemData g_XaItemData[];

extern s_VabInfo g_Vab_InfoTable[420];

extern u8* g_Sd_KdtBuffer[];

extern s_AudioItemData g_AudioData[];

extern s32 D_800A9FDC[];

extern u8* g_Sd_KdtBuffer[];

extern u8* g_Sd_VabBuffers[];

extern s_800C15F0 D_800C15F0[4];

/** @brief `e_SfxId` | Stores the index of the currently playing SFX . */
extern u16 g_AudioPlayingIdxList[24];

/** @brief Stores the pitch of currently playing SFX.
 * Shares the same index where the SFX is stored in `g_AudioPlayingIdxList`.
 */
extern s16 g_AudioPlayingPitchList[24];

extern s_Sd_AudioWork g_Sd_AudioWork;

/** @brief Hold states for different audio types streaming. */
extern s_AudioStreamingStates g_Sd_AudioStreamingStates;

extern s32 pad_bss_800C1674;

/** @note Name from retrieved debug symbols.
 * Debug symbols from: `Konami International Rally Championship`
 *
 * Symbol don't indicate the struct name. The size may not
 * contradict this definition as it seems the variable is intended
 * to have a size of 48/0x30 bytes, while this has a size of 16/0x10
 * bytes. They serve the same purpose of adjusting the volume
 * channels.
 */
extern s_ChannelsVolumeController gSDVolConfig;

extern s_800C1688 D_800C1688;

extern s32 pad_bss_800C1694;

extern s_VabPlayingInfo g_Sd_VabPlayingInfo;

/** @brief Task pool related to audio and audio data streaming.
 * `Sd_TaskPoolExecute` is the main function responsible for executing tasks.
 *
 * @note Possible name retrieved from debug symbols.
 * `Tokimeki Memorial ~Forever With You~` symbols have a global variable named
 * `gSDEvt`. This function can't be restored, but the name would fit for
 * this purpose. This game also features a similar command pool system
 * to the one in SH1.
 */
extern u8 g_Sd_TaskPool[32];

extern s32 D_800C16C8[0x840];

/** @brief The type of audio file being loaded. See `e_AudioType`. */
extern u8 g_Sd_AudioType;

extern char pad_bss_800C37C9[3];

/** @brief Amount of data moved when loading KDT/VAB files. */
extern u32 g_Sd_DataMoved;

extern u8 g_Sd_VabLoadAttemps;

extern char pad_bss_800C37D1[3];

extern s_AudioItemData* g_Sd_VabTargetLoad;

// Pointer to the data of the VAB loading to be used for music.
extern s_AudioItemData* g_Sd_KdTargetLoad;

extern u8 D_800C37DC; // Boolean.

extern u8 g_Sd_CurrentTask;

// ==========
// FUNCTIONS
// ==========

/** @brief Passes a task to the sound driver.
 * Plays SFX among other things.
 *
 * @note Name from retrieved debug symbols.
 * KCET games using LIBSD and SH2 feature a function with this name
 * differing in case between each game.
 * * `Tokimeki Memorial ~Forever With You~` and `International Rally Championship` call it `SD_Call`.
 * * `Winning Eleven 6` calls it `SD_call`.
 * * `Silent Scope 3` and `Silent Hill 2` call it `sd_call`.
 *
 * Each game varies the functionallity mainly based on its requirements,
 * but in all instances, it's used to pass a command/task to the
 * audio streaming system. The most similar are IRC and SH2.
 */
void SD_Call(u32 cmd);

/** @brief Checks if an audio file is loading, is going to be loaded, or an XA file is playing.
 * Depending of the audio file, it marks different numbers.
 *
 * 0 = Nothing currently loading.
 * 1 = XA file playing.
 * 2 = VAB file loading.
 * 3 = XA file loading.
 * 4 and 5 = TODO: Unknown. Requires further investigation about `D_800C37DC` functionallity.
 */
u8 Sd_AudioStreamingCheck(void);

u16 func_80045BC8(void);

/** @brief Sound effect management and VAB + KDT file load.
 * Scratch: https://decomp.me/scratch/AA6ui
 *
 * @note Name from retrieved debug symbols.
 * `Tokimeki Memorial ~Forever With You~` and `International Rally Championship`
 * have a function with a similar purpose as this for handling
 * the loading of VAB files and some other audio system features.
 * Both cases are different. Notably in TM, it's used
 * to also handle XA files and more low-level features related the audio system
 * that neither SH1 nor IRC have.
 */
void SD_BranchCTRL(u16 task);

/** @brief Sets the audio system to stereo or mono.
 * Scratch: https://decomp.me/scratch/jtrpu
 */
void Sd_AudioSystemSet(u8 isStereo);

/** @note Name from retrieved debug symbols.
 * The function can be found in many Konami games with the LIBSD library,
 * but `International Rally Championship` (name as `SD_Call`) and
 * Winning Eleven 5 (Inside `SOUNDCD.IRX`; Name as `sd_call`) have more
 * similarity to SH1. Additionally, SH2 has a similarly named function
 * (`shSdInit`) which is completely different.
 */
void SD_Init(void);

/** @note Name from retrieved debug symbols.
 * See `SD_Init`.
 *
 * As noted above, IRC and WE5 are games with the most similarities to SH1, where a similar function that
 * handles more of the initalization process for the audio system is found.
 * Each game has a slightly different name.
 * IRC calls it `SD_InitMyself`, while WE5 calls it `sd_work_init`. It's probable
 * that WE5 is the name SH1 used, as the its variant contains similar loops and function calls to SH1.
 */
void sd_work_init(void);

/** @unused Stop main audio system. */
void Sd_AudioStop(void);

u8 Sd_PlaySfx(u16 sfxId, q0_7 balance, u8 vol);

/** Updates attributes from currently playing specified audio. */
void Sd_SfxAttributesUpdate(u16 sfxId, q0_7 balance, u8 vol, s8 pitch);

/** SFX func. */
void func_80046620(u16 sfxId, q0_7 balance, u8 vol, s8 pitch);

/** @brief Stops the last VAB audio data playback. */
void Sd_LastSfxStop(void);

/** @brief Stops specified VAB audio data playback. */
void Sd_SfxStop(u16 sfxId);

/** @brief Stops specified VAB audio data playback according to an SFX ID. */
void Sd_SfxStopStep(u16 sfxId);

/** @brief Stops all VAB audio data playback. */
void Sd_AllSfxStop(void);

/** @brief Stops all VAB audio data playback with `Release Rate` mode enabled. */
void Sd_AllSfxWithRRStop(void);

/** Sound command func. Unknown category. */
void func_80046A24(u16 cmd);

void func_80046A70(void);

void Sd_StopBgmTaskAdd(void);

void Sd_StopBgm(void);

void Sd_StopBgmStep(void);

/** Returns the current BGM audio layer volume based on the PSX's MIDI channel. Returns Q7 value?? */
u8 Sd_BgmLayerVolumeGet(u8 layerIdx);

/** Manipulates the BGM audio layer volume. */
void Sd_BgmLayerVolumeSet(u8 layerIdx, u8 vol);

/** @brief Loads and plays XA audio in `g_XaItemData`. */
void Sd_XaAudioPlay(void);

/** @brief Initializes the process to play XA audios in `g_XaItemData`. */
void Sd_XaAudioPlayTaskAdd(u16 sfx);

/** @unused Gets the length of XA audios in `g_XaItemData`. */
s32 Sd_XaAudioLengthGet(s32 idx);

void Sd_XaAudioStopTaskAdd(void);

void Sd_XaPreLoadAudioPreTaskAdd(u16 xaIdx);

void Sd_XaPreLoadAudioTaskAdd(s32 xaIdx);

/** @brief Prepares the audio load of the XA set in `g_XaItemData`. */
void Sd_XaPreLoadAudio(void);

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

/** Updates and add tasks to a task pool. */
void Sd_TaskPoolAdd(u8 task);

/** Updates a task pool by shifting a field. */
void Sd_TaskPoolUpdate(void);

void Sd_VabLoad(void);

void Sd_SetReverbDepth(u8 depth);

void Sd_SetReverbEnable(s32 mode);

void Sd_VabLoad_TaskAdd(s32 cmd);

void Sd_VabLoad_TypeClear(void);

/** @brief Sets the reader offset to the target VAB position. */
void Sd_VabLoad_OffSet(void);

void Sd_VabLoad_FileLoad(void);

/** @brief Sets the reader offset to the VAG data position. */
void Sd_VabLoad_OffVagDataSet(void);

/** @brief Moves VAG data from the temporary file location to the indicated `g_Sd_VabBuffers` buffer.
 * If the file is larger than `VAB_BUFFER_LIMIT`, it loops to move remaining beyond this size.
 */
void Sd_VabLoad_VagDataMove(void);

void Sd_VabLoad_OffVagNextDataSet(void);

void Sd_VabLoad_NextVagDataMove(void);

void Sd_VabLoad_LastVagDataMove(void);

void Sd_VabLoad_Finalization(void);

/** Nullsub */
void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4);

/** Nullsub */
void func_800485B8(s32 arg0, u8 arg1, u32 arg2);

void Sd_KdtLoad_TaskAdd(u16 songIdx);

void Sd_KdtLoad(void);

void Sd_KdtLoad_StopSeq(void);

void Sd_KdtLoad_OffSet(void);

void Sd_KdtLoad_FileLoad(void);

void Sd_KdtLoad_LoadCheck(void);

void Sd_TaskPoolExecute(void);

void func_800485C0(s32 idx);

/** @brief Executes a new primitive command and checks the status against the previous.
 * If the previous primitive commands haven't completed, it starts
 * adding to `g_Sd_AudioWork.cdErrorCount_0` each time the process fails. When it
 * reaches 600 failed attemps, it restarts the CD-ROM system.
 */
u8 Sd_CdPrimitiveCmdTry(s32 com, u8* param, u8* res);

#endif
