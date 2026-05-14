#ifndef _BODYPROG_SOUND_SOUND_H
#define _BODYPROG_SOUND_SOUND_H

/** @brief SFX pair indices. Used for `SFX_PAIRS`. */
typedef enum _SfxPairIdx
{
    SfxPairIdx_0  = 0,
    SfxPairIdx_1  = 1,
    SfxPairIdx_2  = 2,
    SfxPairIdx_3  = 3,
    SfxPairIdx_4  = 4,
    SfxPairIdx_5  = 5,
    SfxPairIdx_6  = 6,
    SfxPairIdx_7  = 7,
    SfxPairIdx_8  = 8,
    SfxPairIdx_9  = 9,
    SfxPairIdx_10 = 10,
    SfxPairIdx_11 = 11,
    SfxPairIdx_12 = 12,
    SfxPairIdx_13 = 13,
    SfxPairIdx_14 = 14,
    SfxPairIdx_15 = 15,
    SfxPairIdx_16 = 16,
    SfxPairIdx_17 = 17,
    SfxPairIdx_18 = 18,
    SfxPairIdx_19 = 19,
    SfxPairIdx_20 = 20,
    SfxPairIdx_21 = 21,
    SfxPairIdx_22 = 22,
    SfxPairIdx_23 = 23,
    SfxPairIdx_24 = 24
} e_SfxPairIdx;

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

/** @brief SFX pair used for area transitions (e.g. door opening and closing). */
typedef struct _AreaLoadSfx
{
    u16 sfx_0;
    u16 sfx_2;
} s_AreaLoadSfx;

#endif
