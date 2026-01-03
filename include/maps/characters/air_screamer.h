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
    AirScreamerFlag_13   = 1 << 13,
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
    AirScreamerAnim_Still = 0,
    AirScreamerAnim_1     = 1, // StandAttack
    AirScreamerAnim_2     = 2, // FlyAttack
    AirScreamerAnim_3     = 3, // GlideAttack
    AirScreamerAnim_4     = 4, // StandKnockout
    AirScreamerAnim_5     = 5, // Death
    AirScreamerAnim_6     = 6, // StandDamageRecoil
    AirScreamerAnim_7     = 7, // FlyDamageRecoil
    AirScreamerAnim_8     = 8, // GlideDamageRecoil
    AirScreamerAnim_9     = 9, // FlyPeckAttack 2?
    AirScreamerAnim_10    = 10, // FlyKnockout
    AirScreamerAnim_11    = 11, // GlideKnockout
    AirScreamerAnim_12    = 12, // Knockout crawl/attack?
    AirScreamerAnim_13    = 13, // Stand eat look up?
    AirScreamerAnim_14    = 14, // Stand eat?
    AirScreamerAnim_15    = 15, // Glide attack start?
    AirScreamerAnim_16    = 16, // Glide to stand
    AirScreamerAnim_17    = 17, // Glide flap
    AirScreamerAnim_18    = 18, // Fly to glide
    AirScreamerAnim_19    = 19, // FlyIdle
    AirScreamerAnim_20    = 20, // Near death die
    AirScreamerAnim_21    = 21, // near death?
    AirScreamerAnim_22    = 22,
    AirScreamerAnim_23    = 23, // StandIdle
    AirScreamerAnim_24    = 24, // TakeOff
    AirScreamerAnim_25    = 25, // WalkForward
    AirScreamerAnim_26    = 26, // Death end?
    AirScreamerAnim_27    = 27 // FlyIdle duplicate
} e_AirScreamerAnim;

/** @brief Air Screamer or Night Flutter character control states. */
typedef enum _AirScreamerControl
{
    AirScreamerControl_None  = 0,
    AirScreamerControl_1     = 1,
    AirScreamerControl_2     = 2,
    AirScreamerControl_3     = 3,
    AirScreamerControl_4     = 4,
    AirScreamerControl_5     = 5,
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
    AirScreamerControl_18    = 18,
    AirScreamerControl_19    = 19,
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

/*s_AnimInfo AIR_SCREAMER_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, NO_VALUE, { Q12(10) }, NO_VALUE, NO_VALUE },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(10) }, NO_VALUE, NO_VALUE },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(10) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(23, false), { Q12(20) }, 0, 11 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(15) }, NO_VALUE, 12 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(19, false), { Q12(15) }, 12, 25 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(30) }, NO_VALUE, 26 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(17, false), { Q12(25) }, 26, 55 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(15) }, NO_VALUE, 56 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(26, false), { Q12(15) }, 56, 80 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(10) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(26, false), { Q12(10) }, 81, 99 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(30) }, NO_VALUE, 100 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(23, false), { Q12(20) }, 100, 114 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(30) }, NO_VALUE, 115 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(19, false), { Q12(20) }, 115, 129 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(30) }, NO_VALUE, 130 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(17, false), { Q12(25) }, 130, 153 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(30) }, NO_VALUE, 154 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(21, false), { Q12(24) }, 154, 171 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(10) }, NO_VALUE, 172 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(26, false), sharedFunc_800D77D0_0_s01, 172, 189 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(10) }, NO_VALUE, 190 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(26, false), sharedFunc_800D77D0_0_s01, 190, 230 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(10) }, NO_VALUE, 231 },
    { Anim_Update0, ANIM_STATUS(12, true), false, ANIM_STATUS(26, false), { Q12(10) }, 231, 242 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(5) }, NO_VALUE, 243 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(14, false), { Q12(10) }, 243, 272 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(1.5) }, NO_VALUE, 273 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(10) }, 273, 302 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), func_800E21C8, NO_VALUE, 303 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(19, false), func_800E21C8, 303, 314 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(30) }, NO_VALUE, 315 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(25, false), sharedFunc_800D77D0_0_s01, 315, 339 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), func_800E21C8, NO_VALUE, 340 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 340, 352 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(30) }, NO_VALUE, 353 },
    { Anim_Update0, ANIM_STATUS(18, true), false, ANIM_STATUS(17, false), { Q12(20) }, 353, 364 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), func_800E21C8, NO_VALUE, 365 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 365, 376 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(10) }, NO_VALUE, 377 },
    { Anim_Update0, ANIM_STATUS(20, true), false, ANIM_STATUS(26, false), { Q12(10) }, 377, 383 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(15) }, NO_VALUE, 384 },
    { Anim_Update1, ANIM_STATUS(21, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 384, 407 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(30) }, NO_VALUE, 408 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(19, false), { Q12(20) }, 408, 432 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(10) }, NO_VALUE, 433 },
    { Anim_Update1, ANIM_STATUS(23, true), false, NO_VALUE, func_800E21C8, 433, 447 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), func_800E21C8, NO_VALUE, 448 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(17, false), func_800E21C8, 448, 482 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(30) }, NO_VALUE, 483 },
    { Anim_Update1, ANIM_STATUS(25, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 483, 523 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true), { Q12(1.5) }, NO_VALUE, 96 },
    { Anim_Update1, ANIM_STATUS(26, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 96, 99 },
    { Anim_Update2, ANIM_STATUS(27, false), false, ANIM_STATUS(27, true), { Q12(30) }, NO_VALUE, 365 },
    { Anim_Update1, ANIM_STATUS(27, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 365, 376 }
};*/

/** @brief Updates an active Air Screamer or Night Flutter character.
 *
 * @param airScreamer Air Screamer or Night Flutter character to update.
 * @param animHdr Animation header.
 * @param coords TODO
 */
void Ai_AirScreamer_Update(s_SubCharacter* airScreamer, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

bool sharedFunc_800D21E4_0_s01(s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

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

void Ai_AirScreamerControl_0(s_SubCharacter* airScreamer);

void Ai_AirScreamerControl_1(s_SubCharacter* airScreamer);

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

s32 sharedFunc_800D7440_0_s01(s_800C4590* arg0, VECTOR* vec1, s_SubCharacter* airScreamer);

void sharedFunc_800D7560_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D76A0_0_s01(s_SubCharacter* airScreamer);

q19_12 sharedFunc_800D77D0_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D7AB0_0_s01(s_SubCharacter* airScreamer);

/** @brief Applies a multi-stage bend deformation to several model coordinates.
 * Builds three rotation matrices using scaled fractions of `chara->field_2A` and
 * multiplies them into `coords[10]`, `coords[9]`, `coords[1]`, and `coords[2]`.
 * Used when the animation flag bit 0 is active to drive a chained bending motion.
 */
void sharedFunc_800D7B14_0_s01(s_SubCharacter* airScreamer, GsCOORDINATE2* coords);

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
