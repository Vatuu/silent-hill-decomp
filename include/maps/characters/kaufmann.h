#ifndef _MAPS_CHARACTERS_CHARA_KAUFMANN_H
#define _MAPS_CHARACTERS_CHARA_KAUFMANN_H

/** @brief Kaufmann character animation indices. */
typedef enum _KaufmannAnim
{
    KaufmannAnim_Still = 0,
    KaufmannAnim_1     = 1,
    KaufmannAnim_2     = 2,
    KaufmannAnim_3     = 3,
    KaufmannAnim_4     = 4,
    KaufmannAnim_5     = 5,
    KaufmannAnim_6     = 6,
    KaufmannAnim_7     = 7,
    KaufmannAnim_8     = 8,
    KaufmannAnim_9     = 9,
    KaufmannAnim_10    = 10,
    KaufmannAnim_11    = 11,
    KaufmannAnim_12    = 12,
    KaufmannAnim_13    = 13,
    KaufmannAnim_14    = 14,
    KaufmannAnim_15    = 15,
    KaufmannAnim_16    = 16,
    KaufmannAnim_17    = 17,
    KaufmannAnim_18    = 18,
    KaufmannAnim_19    = 19,
    KaufmannAnim_20    = 20,
    KaufmannAnim_21    = 21
} e_KaufmannAnim;

/** @brief Kaufmann character control states. */
typedef enum _KaufmannControl
{
    KaufmannControl_0  = 0,
    KaufmannControl_1  = 1,
    KaufmannControl_2  = 2,
    KaufmannControl_3  = 3,
    KaufmannControl_4  = 4,
    KaufmannControl_5  = 5,
    KaufmannControl_6  = 6,
    KaufmannControl_7  = 7,
    KaufmannControl_8  = 8,
    KaufmannControl_9  = 9,
    KaufmannControl_10 = 10,
    KaufmannControl_11 = 11,
    KaufmannControl_12 = 12,
    KaufmannControl_13 = 13,
    KaufmannControl_14 = 14,
    KaufmannControl_15 = 15,
    KaufmannControl_16 = 16,
    KaufmannControl_17 = 17,
    KaufmannControl_18 = 18,
    KaufmannControl_19 = 19,
    KaufmannControl_20 = 20,
    KaufmannControl_21 = 21,
    KaufmannControl_22 = 22,
    KaufmannControl_23 = 23,
    KaufmannControl_24 = 24,
    KaufmannControl_25 = 25
} e_KaufmannControl;

/** @brief Kaufmann character anim infos. */
extern s_AnimInfo KAUFMANN_ANIM_INFOS[];

// TODO: Not Kaufmann anims.
/*s_AnimInfo KAUFMANN_ANIM_INFOS[] = {
    { Anim_BlendLinear, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0.0f)  }, NO_VALUE, 0 },
    { Anim_PlaybackLoop, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30.0f) }, NO_VALUE, 1 },
    { Anim_BlendLinear, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(5.0f)  }, NO_VALUE, 0 },
    { Anim_PlaybackLoop, ANIM_STATUS(1, true),  false, NO_VALUE,              { Q12(5.0f)  }, 0,        5 },
    { Anim_BlendLinear, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(5.0f)  }, NO_VALUE, 6 }
};*/

extern s32 sharedData_800D5CF4_3_s00; // Used by `Kaufmann_Init`.

void Kaufmann_Update(s_SubCharacter* kaufmann, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void Kaufmann_AnimUpdate(s_SubCharacter* kaufmann, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void Kaufmann_MovementUpdate(s_SubCharacter* kaufmann, GsCOORDINATE2* boneCoords);

void Kaufmann_ControlUpdate(s_SubCharacter* kaufmann, GsCOORDINATE2* boneCoords);

void Kaufmann_Init(s_SubCharacter* kaufmann);

#endif
