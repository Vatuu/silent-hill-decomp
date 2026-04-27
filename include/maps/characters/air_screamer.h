#ifndef _MAPS_CHARACTERS_AIRSCREAMER_H
#define _MAPS_CHARACTERS_AIRSCREAMER_H

/** @brief Air Screamer or Night Flutter character flags. */
typedef enum _AirScreamerFlags
{
    AirScreamerFlag_None = 0,
    AirScreamerFlag_0    = 1 << 0,
    AirScreamerFlag_1    = 1 << 1,
    AirScreamerFlag_2    = 1 << 2,
    AirScreamerFlag_3    = 1 << 3,
    AirScreamerFlag_4    = 1 << 4,
    AirScreamerFlag_5    = 1 << 5,
    AirScreamerFlag_6    = 1 << 6,
    AirScreamerFlag_7    = 1 << 7,
    AirScreamerFlag_8    = 1 << 8,
    AirScreamerFlag_9    = 1 << 9,
    AirScreamerFlag_10   = 1 << 10,
    AirScreamerFlag_11   = 1 << 11,
    AirScreamerFlag_12   = 1 << 12,
    AirScreamerFlag_13   = 1 << 13, // SFX active? Mirrors similar player flag?
    AirScreamerFlag_14   = 1 << 14,
    AirScreamerFlag_15   = 1 << 15,
    AirScreamerFlag_16   = 1 << 16,
    AirScreamerFlag_17   = 1 << 17,
    AirScreamerFlag_18   = 1 << 18,
    AirScreamerFlag_19   = 1 << 19,
    AirScreamerFlag_20   = 1 << 20,
    AirScreamerFlag_21   = 1 << 21,
    AirScreamerFlag_22   = 1 << 22,
    AirScreamerFlag_23   = 1 << 23,
    AirScreamerFlag_24   = 1 << 24,
    AirScreamerFlag_25   = 1 << 25,
    AirScreamerFlag_26   = 1 << 26,
    AirScreamerFlag_27   = 1 << 27,
    AirScreamerFlag_28   = 1 << 28,
    AirScreamerFlag_29   = 1 << 29,

    AirScreamerFlag_31   = 1 << 31
} e_AirScreamerFlags;

/** @brief Air Screamer character animation indices. */
typedef enum _AirScreamerAnim
{
    AirScreamerAnim_Still                  = 0,
    AirScreamerAnim_StandBiteAttack        = 1,
    AirScreamerAnim_HoverBiteAttack        = 2,
    AirScreamerAnim_GlideScratchAttack     = 3,
    AirScreamerAnim_StandToStun            = 4,
    AirScreamerAnim_Death                  = 5,
    AirScreamerAnim_StandRecoil            = 6,
    AirScreamerAnim_HoverRecoil            = 7,
    AirScreamerAnim_GlideRecoil            = 8,
    AirScreamerAnim_HoverInjuredBiteAttack = 9,
    AirScreamerAnim_HoverToStun            = 10,
    AirScreamerAnim_GlideToStun            = 11,
    AirScreamerAnim_DeathThroes            = 12,
    AirScreamerAnim_StandBiteAttackStart   = 13,
    AirScreamerAnim_StandBiteAttackEnd     = 14,
    AirScreamerAnim_GlideToHover           = 15,
    AirScreamerAnim_GlideToWalkForward     = 16,
    AirScreamerAnim_Glide                  = 17,
    AirScreamerAnim_HoverToGlide           = 18,
    AirScreamerAnim_HoverVariable          = 19,
    AirScreamerAnim_HoverInjuredToStun     = 20,
    AirScreamerAnim_HoverInjured           = 21,
    AirScreamerAnim_StandIdleToHover       = 22,
    AirScreamerAnim_StandIdle              = 23,
    AirScreamerAnim_StandIdleToGlide       = 24,
    AirScreamerAnim_WalkForward            = 25,
    AirScreamerAnim_Stun                   = 26,
    AirScreamerAnim_HoverConstant          = 27
} e_AirScreamerAnim;

/** @brief Air Screamer or Night Flutter character control states. */
typedef enum _AirScreamerControl
{
    AirScreamerControl_None  = 0,
    AirScreamerControl_1     = 1,
    AirScreamerControl_2     = 2,
    AirScreamerControl_3     = 3,
    AirScreamerControl_4     = 4, // } Walk
    AirScreamerControl_5     = 5, // }
    AirScreamerControl_6     = 6,
    AirScreamerControl_7     = 7,
    AirScreamerControl_8     = 8,
    AirScreamerControl_9     = 9,
    AirScreamerControl_10    = 10,
    AirScreamerControl_11    = 11,
    AirScreamerControl_12    = 12,
    AirScreamerControl_13    = 13,
    AirScreamerControl_14    = 14,
    AirScreamerControl_15    = 15,
    AirScreamerControl_16    = 16,
    AirScreamerControl_17    = 17,
    AirScreamerControl_18    = 18, // } Variable duration hover?
    AirScreamerControl_19    = 19, // }
    AirScreamerControl_20    = 20,
    AirScreamerControl_21    = 21,
    AirScreamerControl_22    = 22,
    AirScreamerControl_23    = 23,
    AirScreamerControl_24    = 24,
    AirScreamerControl_25    = 25,
    AirScreamerControl_26    = 26,
    AirScreamerControl_27    = 27,
    AirScreamerControl_28    = 28,
    AirScreamerControl_29    = 29,
    AirScreamerControl_30    = 30,
    AirScreamerControl_31    = 31,
    AirScreamerControl_32    = 32,
    AirScreamerControl_33    = 33,
    AirScreamerControl_34    = 34,
    AirScreamerControl_35    = 35,
    AirScreamerControl_36    = 36,
    AirScreamerControl_37    = 37,
    AirScreamerControl_38    = 38,
    AirScreamerControl_39    = 39,
    AirScreamerControl_40    = 40,
    AirScreamerControl_41    = 41,
    AirScreamerControl_42    = 42,
    AirScreamerControl_43    = 43,
    AirScreamerControl_44    = 44,
    AirScreamerControl_45    = 45,
    AirScreamerControl_46    = 46,
    AirScreamerControl_47    = 47,
    AirScreamerControl_48    = 48,
    AirScreamerControl_49    = 49,
    AirScreamerControl_50    = 50,
    AirScreamerControl_51    = 51,

    AirScreamerControl_Count = 52
} e_AirScreamerControl;

/** @brief Air Screamer or Night Flutter character state steps. */
typedef enum _AirScreamerStateStep
{
    AirScreamerStateStep_0  = 0,
    AirScreamerStateStep_1  = 1,
    AirScreamerStateStep_2  = 2,
    AirScreamerStateStep_3  = 3,
    AirScreamerStateStep_4  = 4,
    AirScreamerStateStep_5  = 5,
    AirScreamerStateStep_6  = 6,
    AirScreamerStateStep_7  = 7,
    AirScreamerStateStep_8  = 8,
    AirScreamerStateStep_9  = 9,
    AirScreamerStateStep_10 = 10,
    AirScreamerStateStep_11 = 11,
    AirScreamerStateStep_12 = 12,
    AirScreamerStateStep_13 = 13,

    AirScreamerStateStep_64 = 64,
    AirScreamerStateStep_65 = 65,
    AirScreamerStateStep_66 = 66,
    AirScreamerStateStep_67 = 67
} e_AirScreamerStateStep;

/** @brief Air Screamer or Night Flutter character damage types. */
typedef enum _AirScreamerDamage
{
    AirScreamerDamage_None = 0,
    AirScreamerDamage_1    = 1,
    AirScreamerDamage_2    = 2,
    AirScreamerDamage_3    = 3,
    AirScreamerDamage_4    = 4
} e_AirScreamerDamage;

/** @brief Updates an active Air Screamer or Night Flutter character.
 *
 * @param airScreamer Air Screamer or Night Flutter character to update.
 * @param animHdr Animation header.
 * @param boneCoords Model bone coordinates.
 */
void Ai_AirScreamer_Update(s_SubCharacter* airScreamer, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

bool sharedFunc_800D21E4_0_s01(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

/** Probes collision and sets `airScreamerProps.groundHeight_124`. */
void sharedFunc_800D2200_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D2274_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2364_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D2390_0_s01(s_SubCharacter* airScreamer);

/** @brief Initializes an Air Screamer or Night Flutter character.
 *
 * @param airScreamer Air Screamer or Night Flutter character to initialize.
 */
bool Ai_AirScreamer_Init(s_SubCharacter* airScreamer);

void sharedFunc_800D2B00_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2B10_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2B28_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2B4C_0_s01(s_SubCharacter* airScreamer);

/** @brief Warps an Air Screamer or Night Flutter character to the ground.
 *
 * @param airScreamer Air Screamer or Night Flutter character to warp.
 */
void Ai_AirScreamer_GroundWarp(s_SubCharacter* airScreamer);

void sharedFunc_800D2BE4_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* airScreamer);

s32 Ai_AirScreamer_DamageTake(s_SubCharacter* airScreamer, q19_12 mult);

bool sharedFunc_800D2E04_0_s01(s_SubCharacter* airScreamer, VECTOR3* inVec, s32* outDist, s32* outAngle);

bool sharedFunc_800D3430_0_s01(s_SubCharacter* airScreamer, q19_12* dist, q19_12* angle);

/** Pecking distance getter? */
s32 sharedFunc_800D3814_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D31D0_0_s01(s_SubCharacter* airScreamer, const VECTOR3* pos, s32 arg2);

bool Ai_AirScreamer_Control(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_0(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_1(s_SubCharacter* airScreamer);

/** Probability query. */
void sharedFunc_800D3DFC_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D62D8_0_s01(s_SubCharacter* airScreamer);

/** Returns anim-related index. */
s32 sharedFunc_800D4A80_0_s01(s_SubCharacter* airScreamer);

/** Gets player Y position with an offset. */
q19_12 sharedFunc_800D5274_0_s01(void);

void sharedFunc_800D633C_0_s01(s_SubCharacter* airScreamer);
void sharedFunc_800D63A4_0_s01(s_SubCharacter* airScreamer);
void sharedFunc_800D6600_0_s01(s_SubCharacter* airScreamer);

q19_12 sharedFunc_800D7120_0_s01(q19_12 moveSpeed, s32 arg1, s32 arg2);
q19_12 sharedFunc_800D71F0_0_s01(q19_12 moveSpeed, s32 arg1, s32 arg2, s32 arg3);

s32 sharedFunc_800D7440_0_s01(s_CollisionResult* arg0, VECTOR* vec1, s_SubCharacter* airScreamer);

void sharedFunc_800D7560_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D76A0_0_s01(s_SubCharacter* airScreamer);

q19_12 sharedFunc_800D77D0_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D7AB0_0_s01(s_SubCharacter* airScreamer);

/** @brief Applies a multi-stage bend deformation to several model coordinates.
 * Builds three rotation matrices using scaled fractions of `chara->field_2A` and
 * multiplies them into `boneCoords[10]`, `boneCoords[9]`, `boneCoords[1]`, and `boneCoords[2]`.
 * Used when the animation flag bit 0 is active to drive a chained bending motion.
 */
void sharedFunc_800D7B14_0_s01(s_SubCharacter* airScreamer, GsCOORDINATE2* boneCoords);

q19_12 Model_AnimDurationGet(s_Model* model);

bool sharedFunc_800D7EBC_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D81B0_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D81D0_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D8244_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D82B8_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D8714_0_s01(s_SubCharacter* airScreamer, q19_12 moveSpeed, q19_12 headingAngle);

void sharedFunc_800D87FC_0_s01(s_SubCharacter* airScreamer);

// NOTE: Following are only present in M0S01
void func_800D39F4(s_SubCharacter* airScreamer);

void func_800D3A3C(s_SubCharacter* airScreamer);

void func_800D3AC0(s_SubCharacter* airScreamer);

#endif
