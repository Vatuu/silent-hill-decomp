#ifndef _MAPS_CHARACTERS_GROANER_H
#define _MAPS_CHARACTERS_GROANER_H

/** @brief Groaner character flags. */
typedef enum _GroanerFlags
{
    GroanerFlag_None = 0,
    GroanerFlag_0    = 1 << 0,
    GroanerFlag_1    = 1 << 1,
    GroanerFlag_2    = 1 << 2,
    GroanerFlag_3    = 1 << 3,
    GroanerFlag_4    = 1 << 4,
    GroanerFlag_5    = 1 << 5,
    GroanerFlag_6    = 1 << 6,
    GroanerFlag_7    = 1 << 7,
    GroanerFlag_8    = 1 << 8,
    GroanerFlag_9    = 1 << 9,
    GroanerFlag_10   = 1 << 10,
    GroanerFlag_11   = 1 << 11,
    GroanerFlag_12   = 1 << 12
} e_GroanerFlags;

/** @brief Groaner character animation indices. */
typedef enum _GroanerAnim
{
    GroanerAnim_Still = 0,
    GroanerAnim_1     = 1,
    GroanerAnim_2     = 2,
    GroanerAnim_3     = 3,
    GroanerAnim_4     = 4,
    GroanerAnim_5     = 5,
    GroanerAnim_6     = 6,
    GroanerAnim_7     = 7,
    GroanerAnim_8     = 8,
    GroanerAnim_9     = 9,
    GroanerAnim_10    = 10,
    GroanerAnim_11    = 11,
    GroanerAnim_12    = 12,
    GroanerAnim_13    = 13,
    GroanerAnim_14    = 14,
    GroanerAnim_15    = 15,
    GroanerAnim_16    = 16,
    GroanerAnim_17    = 17,
    GroanerAnim_18    = 18,
    GroanerAnim_19    = 19,
    GroanerAnim_20    = 20,
    GroanerAnim_21    = 21,
    GroanerAnim_22    = 22,
    GroanerAnim_23    = 23
} e_GroanerAnim;

/** @brief Groaner character control states. */
typedef enum _GroanerControl
{
    GroanerControl_0 = 0,
    GroanerControl_1 = 1,
    GroanerControl_2 = 2,
    GroanerControl_3 = 3,
    GroanerControl_4 = 4,
    GroanerControl_5 = 5,
    GroanerControl_6 = 6,
    GroanerControl_7 = 7,
    GroanerControl_8 = 8,
    GroanerControl_9 = 9
} e_GroanerControl;

/** @brief Groaner character state steps. */
typedef enum _GroanerStateStep
{
    GroanerStateStep_0 = 0,
    GroanerStateStep_1 = 1,
    GroanerStateStep_2 = 2,
    GroanerStateStep_3 = 3
} e_GroanerStateStep;

void Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void Groaner_Init(s_SubCharacter* groaner); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E33DC_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E39D8_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5930_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner);

// Plays SFX.
void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner);

/*s_AnimInfo GROANER_ANIM_INFOS[] = {
    { Anim_BlendLinear, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_BlendLinear, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(2) }, NO_VALUE, 0 },
    { Anim_PlaybackOnce, ANIM_STATUS(1, true), false, ANIM_STATUS(18, false), { Q12(3) }, 0, 15 },
    { Anim_BlendLinear, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(16) }, NO_VALUE, 19 },
    { Anim_PlaybackOnce, ANIM_STATUS(2, true), false, ANIM_STATUS(9, false), { Q12(24.8f) }, 19, 36 },
    { Anim_BlendLinear, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(16) }, NO_VALUE, 39 },
    { Anim_PlaybackOnce, ANIM_STATUS(3, true), false, ANIM_STATUS(4, false), { Q12(0) }, 39, 77 },
    { Anim_BlendLinear, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(1) }, NO_VALUE, 78 },
    { Anim_PlaybackLoop, ANIM_STATUS(4, true), false, NO_VALUE, { Q12(4) }, 78, 93 },
    { Anim_BlendLinear, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(2) }, NO_VALUE, 94 },
    { Anim_PlaybackOnce, ANIM_STATUS(5, true), false, ANIM_STATUS(19, false), { Q12(3.5f) }, 94, 110 },
    { Anim_BlendLinear, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(16) }, NO_VALUE, 114 },
    { Anim_PlaybackOnce, ANIM_STATUS(6, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 114, 130 },
    { Anim_BlendLinear, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(16) }, NO_VALUE, 134 },
    { Anim_PlaybackOnce, ANIM_STATUS(7, true), false, ANIM_STATUS(8, false), { Q12(0) }, 134, 164 },
    { Anim_BlendLinear, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(1) }, NO_VALUE, 165 },
    { Anim_PlaybackLoop, ANIM_STATUS(8, true), false, NO_VALUE, { Q12(6) }, 165, 190 },
    { Anim_BlendLinear, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(2) }, NO_VALUE, 191 },
    { Anim_PlaybackLoop, ANIM_STATUS(9, true), false, NO_VALUE, { Q12(7) }, 191, 206 },
    { Anim_BlendLinear, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(20) }, NO_VALUE, 214 },
    { Anim_PlaybackOnce, ANIM_STATUS(10, true), false, ANIM_STATUS(16, false), { Q12(0) }, 214, 243 },
    { Anim_BlendLinear, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(2) }, NO_VALUE, 244 },
    { Anim_PlaybackOnce, ANIM_STATUS(11, true), false, ANIM_STATUS(20, false), { Q12(3.5f) }, 244, 264 },
    { Anim_BlendLinear, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(16) }, NO_VALUE, 268 },
    { Anim_PlaybackOnce, ANIM_STATUS(12, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 268, 284 },
    { Anim_BlendLinear, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(32) }, NO_VALUE, 288 },
    { Anim_PlaybackOnce, ANIM_STATUS(13, true), false, ANIM_STATUS(14, false), { Q12(0) }, 288, 318 },
    { Anim_BlendLinear, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(1) }, NO_VALUE, 319 },
    { Anim_PlaybackLoop, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(6) }, 319, 345 },
    { Anim_BlendLinear, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(32) }, NO_VALUE, 346 },
    { Anim_PlaybackOnce, ANIM_STATUS(15, true), false, ANIM_STATUS(10, false), { Q12(54) }, 346, 362 },
    { Anim_BlendLinear, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 363 },
    { Anim_PlaybackLoop, ANIM_STATUS(16, true), false, NO_VALUE, { Q12(0) }, 363, 370 },
    { Anim_BlendLinear, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(2) }, NO_VALUE, 371 },
    { Anim_PlaybackLoop, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(11.5f) }, 371, 396 },
    { Anim_BlendLinear, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(16) }, NO_VALUE, 15 },
    { Anim_PlaybackLoop, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(0) }, 15, 16 },
    { Anim_BlendLinear, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(16) }, NO_VALUE, 110 },
    { Anim_PlaybackLoop, ANIM_STATUS(19, true), false, NO_VALUE, { Q12(0) }, 110, 111 },
    { Anim_BlendLinear, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(16) }, NO_VALUE, 264 },
    { Anim_PlaybackLoop, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(0) }, 264, 265 },
    { Anim_BlendLinear, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(16) }, NO_VALUE, 0 },
    { Anim_PlaybackOnce, ANIM_STATUS(21, true), false, ANIM_STATUS(4, false), { Q12(12) }, 0, 15 },
    { Anim_BlendLinear, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 94 },
    { Anim_PlaybackOnce, ANIM_STATUS(22, true), false, ANIM_STATUS(8, false), { Q12(12) }, 94, 110 },
    { Anim_BlendLinear, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(16) }, NO_VALUE, 244 },
    { Anim_PlaybackOnce, ANIM_STATUS(23, true), false, ANIM_STATUS(14, false), { Q12(12) }, 244, 264 }
};*/

extern s_AnimInfo GROANER_ANIM_INFOS[];

#endif
