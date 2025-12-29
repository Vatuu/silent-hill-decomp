#ifndef _MAPS_CHARACTERS_LARVALSTALKER_H
#define _MAPS_CHARACTERS_LARVALSTALKER_H

/** @brief Larval Stalker character flags. */
typedef enum _LarvalStalkerFlags
{
    LarvalStalkerFlag_None = 0,
    LarvalStalkerFlag_1    = 1 << 1,
    LarvalStalkerFlag_2    = 1 << 2,
    LarvalStalkerFlag_3    = 1 << 3,
    LarvalStalkerFlag_4    = 1 << 4,
    LarvalStalkerFlag_5    = 1 << 5,
    LarvalStalkerFlag_6    = 1 << 6,
    LarvalStalkerFlag_7    = 1 << 7
} e_LarvalStalkerFlags;

/** @brief Larval Stalker character animation incides. */
typedef enum _LarvalStalkerAnim
{
    LarvalStalkerAnim_Still = 0,
    LarvalStalkerAnim_1     = 1,
    LarvalStalkerAnim_2     = 2,
    LarvalStalkerAnim_3     = 3,
    LarvalStalkerAnim_4     = 4,
    LarvalStalkerAnim_5     = 5,
    LarvalStalkerAnim_6     = 6,
    LarvalStalkerAnim_7     = 7,
    LarvalStalkerAnim_8     = 8,
    LarvalStalkerAnim_9     = 9,
    LarvalStalkerAnim_10    = 10,
    LarvalStalkerAnim_11    = 11,
    LarvalStalkerAnim_12    = 12,
    LarvalStalkerAnim_13    = 13,
    LarvalStalkerAnim_14    = 14,
    LarvalStalkerAnim_15    = 15,
    LarvalStalkerAnim_16    = 16,
    LarvalStalkerAnim_17    = 17,
    LarvalStalkerAnim_18    = 18
} e_LarvalStalkerAnim;

/** @brief Larval Stalker character control states. */
typedef enum _LarvalStalkerControl
{
    LarvalStalkerControl_None = 0,
    LarvalStalkerControl_1    = 1,
    LarvalStalkerControl_2    = 2,
    LarvalStalkerControl_3    = 3,
    LarvalStalkerControl_4    = 4,
    LarvalStalkerControl_5    = 5,
    LarvalStalkerControl_6    = 6,
    LarvalStalkerControl_7    = 7,
    LarvalStalkerControl_8    = 8,
    LarvalStalkerControl_9    = 9,
    LarvalStalkerControl_10   = 10,
    LarvalStalkerControl_11   = 11,
    LarvalStalkerControl_12   = 12,
    LarvalStalkerControl_13   = 13
} e_LarvalStalkerControl;

void Ai_LarvalStalker_Update(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800CF168_1_s00(s_SubCharacter* larvalStalker);

void sharedFunc_800D140C_1_s00(s_SubCharacter* larvalStalker, GsCOORDINATE2* coords);

void sharedFunc_800D1524_1_s00(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_LarvalStalker_Init(s_SubCharacter* larvalStalker);

void sharedFunc_800D17BC_1_s00(s_SubCharacter* larvalStalker);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter* larvalStalker);

#endif
