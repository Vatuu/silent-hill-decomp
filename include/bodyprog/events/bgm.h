#ifndef _BODYPROG_EVENTS_BGM_H
#define _BODYPROG_EVENTS_BGM_H

#define BGM_LAYER_COUNT 9

/** @brief Background music status flags. */
typedef enum _BgmStatusFlags
{
    BgmStatusFlag_None        = 0,
    BgmStatusFlag_Pause       = 1 << 0,
    BgmStatusFlag_ApplyMute   = 1 << 1,
    BgmStatusFlag_RadioActive = 1 << 2,
    BgmStatusFlag_Duck        = 1 << 3,
    BgmStatusFlag_4           = 1 << 4,
    BgmStatusFlag_VoiceDialog = 1 << 5,
    BgmStatusFlag_6           = 1 << 6, // Something to do with the radio?
    BgmStatusFlag_RequestMute = 1 << 7
} e_BgmStatusFlags;

/** @brief Background music flags. */
typedef enum _BgmFlags
{
    BgmFlag_Layer0    = 1 << 0,
    BgmFlag_Layer1    = 1 << 1,
    BgmFlag_Layer2    = 1 << 2,
    BgmFlag_Layer3    = 1 << 3,
    BgmFlag_Layer4    = 1 << 4,
    BgmFlag_Layer5    = 1 << 5,
    BgmFlag_Layer6    = 1 << 6,
    BgmFlag_Layer7    = 1 << 7,
    BgmFlag_KeepAlive = 1 << 8,
    BgmFlag_MuteAll   = 1 << 9
} e_BgmFlags;

/** @brief Background music track indices. */
typedef enum _BgmTrackIdx
{
    BgmTrackIdx_None = 0,
    BgmTrackIdx_1    = 1,
    BgmTrackIdx_2    = 2,
    BgmTrackIdx_3    = 3,
    BgmTrackIdx_4    = 4,
    BgmTrackIdx_5    = 5,
    BgmTrackIdx_6    = 6,
    BgmTrackIdx_7    = 7,
    BgmTrackIdx_8    = 8,
    BgmTrackIdx_9    = 9,
    BgmTrackIdx_10   = 10,
    BgmTrackIdx_11   = 11,
    BgmTrackIdx_12   = 12,
    BgmTrackIdx_13   = 13,
    BgmTrackIdx_14   = 14,
    BgmTrackIdx_15   = 15,
    BgmTrackIdx_16   = 16,
    BgmTrackIdx_17   = 17,
    BgmTrackIdx_18   = 18,
    BgmTrackIdx_19   = 19,
    BgmTrackIdx_20   = 20,
    BgmTrackIdx_21   = 21,
    BgmTrackIdx_22   = 22,
    BgmTrackIdx_23   = 23,
    BgmTrackIdx_24   = 24,
    BgmTrackIdx_25   = 25,
    BgmTrackIdx_26   = 26,
    BgmTrackIdx_27   = 27,
    BgmTrackIdx_28   = 28,
    BgmTrackIdx_29   = 29,
    BgmTrackIdx_30   = 30,
    BgmTrackIdx_31   = 31,
    BgmTrackIdx_32   = 32,
    BgmTrackIdx_33   = 33,
    BgmTrackIdx_34   = 34,
    BgmTrackIdx_35   = 35,
    BgmTrackIdx_36   = 36,
    BgmTrackIdx_37   = 37,
    BgmTrackIdx_38   = 38,
    BgmTrackIdx_39   = 39,
    BgmTrackIdx_40   = 40,
    BgmTrackIdx_41   = 41
} e_BgmTrackIds;

// ========
// STRUCTS
// ========

typedef struct _BgmLayerLimits
{
    /* 0x0 */ u8 limits[8];
} s_BgmLayerLimits;

// ==========
// FUNCTIONS
// ==========

void Bgm_TrackUpdate(bool arg0);

void Bgm_AllLayersMute(void);

/** @unused. */
bool Bgm_LayerOnCheck(void);

void Bgm_GlobalLayerVariablesUpdate(void);

/** @brief Undates background music.
 *
 * @param bgmFlags BGM layer flags.
 * @param fadeSpeed Volume fade speed.
 * @param layerLimits BGM layer limits.
 */
void Bgm_Update(s32 bgmFlags, q19_12 fadeSpeed, s_BgmLayerLimits* layerLimits);

/** @brief Updates the track index and disables radio effects. */
void func_800363D0(void);

void Bgm_TrackChange(s32 bgmIdx);

void Game_MapRoomIdxUpdate(void);

/** @unused */
s32 func_8003647C(void);

/** @unused */
s32 func_80036498(void);

// Used in some RoomBgmInit funcs.
u32 func_800364BC(void);

#endif
