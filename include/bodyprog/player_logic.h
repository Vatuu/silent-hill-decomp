#ifndef _PLAYER_LOGIC_H
#define _PLAYER_LOGIC_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the player logic.
 */

/** @note The game handles the upper and lower part of the player's body independently.
 *
 * SH2 symbols indicate a similar system with 4 enums used depending on the controls cheme:
 * `lower_*_2D`
 * `lower_*_3D`
 * `upper_*_2D`
 * `upper_*_3D`
 */

// ======
// ENUMS
// ======
 
/** @brief Player states. */
typedef enum _PlayerState
{
    PlayerState_None                      = 0,
    PlayerState_Combat                    = 1,
    PlayerState_Idle                      = 2,
    PlayerState_FallForward               = 3,
    PlayerState_FallBackward              = 4,
    PlayerState_KickEnemy                 = 5,
    PlayerState_StompEnemy                = 6,
    PlayerState_Unk7                      = 7, // Lighting bolts at the end of the game?
    PlayerState_Death                     = 8,
    PlayerState_InstantDeath              = 9, // Split Head boss.
    PlayerState_EnemyGrabTorsoFront       = 10,
    PlayerState_Unk11                     = 11,
    PlayerState_Unk12                     = 12,
    PlayerState_EnemyGrabTorsoBack        = 13,
    PlayerState_EnemyGrabLegsFront        = 14,
    PlayerState_EnemyGrabLegsBack         = 15,
    PlayerState_EnemyReleaseUpperFront    = 16,
    PlayerState_Unk17                     = 17,
    PlayerState_Unk18                     = 18,
    PlayerState_DamageHead                = 19,
    PlayerState_EnemyReleaseUpperBack     = 20,
    PlayerState_EnemyReleaseLowerFront    = 21,
    PlayerState_EnemyReleaseLowerBack     = 22,
    PlayerState_DamageTorsoBack           = 23,
    PlayerState_DamageTorsoFront          = 24,
    PlayerState_DamageTorsoRight          = 25,
    PlayerState_DamageTorsoLeft           = 26,
    PlayerState_DamageFeetFront           = 27, // Creeper attack.
    PlayerState_DamageFeetBack            = 28, // Creeper attack.
    PlayerState_DamagePushBack            = 29, // Split Head boss.
    PlayerState_DamagePushFront           = 30, // Split Head boss.
    PlayerState_Unk31                     = 31,
    PlayerState_EnemyGrabNeckFront        = 32, // Cybil boss.
    PlayerState_EnemyGrabNeckBack         = 33, // Cybil boss.
    PlayerState_Unk34                     = 34,
    PlayerState_Unk35                     = 35,
    PlayerState_Unk36                     = 36,
    PlayerState_EnemyGrabPinnedFrontStart = 37, // Romper attack.
    PlayerState_EnemyGrabPinnedBackStart  = 38, // Romper attack.
    PlayerState_EnemyGrabPinnedFront      = 39, // Romper attack.
    PlayerState_EnemyGrabPinnedBack       = 40, // Romper attack.
    PlayerState_EnemyReleasePinnedFront   = 41, // Romper attack.
    PlayerState_EnemyReleasePinnedBack    = 42, // Romper attack.
    PlayerState_Unk43                     = 43,
    PlayerState_Unk44                     = 44,
    PlayerState_DamageThrownFront         = 45,
    PlayerState_DamageThrownBack          = 46,
    PlayerState_OnFloorFront              = 47, // Counts as grab anim.
    PlayerState_OnFloorBehind             = 48, // Counts as grab anim.
    PlayerState_GetUpFront                = 49,
    PlayerState_GetUpBack                 = 50,
    PlayerState_Unk51                     = 51, // Cutscenes
    PlayerState_Unk52                     = 52, // Standing during interacting with something/cutscenes?
    PlayerState_Unk53                     = 53, // Moving in cutscene?
    PlayerState_Unk54                     = 54, // Running in cutscene?
    PlayerState_Unk55                     = 55,
    PlayerState_Unk56                     = 56,
    PlayerState_Unk57                     = 57,
    PlayerState_Unk58                     = 58,
    PlayerState_Unk59                     = 59, // Crouching in cutscenes/interactions?
    PlayerState_Unk60                     = 60, // Get up from crouching in cutscenes/interactions?
    PlayerState_Unk61                     = 61,
    PlayerState_Unk62                     = 62,
    PlayerState_Unk63                     = 63,
    PlayerState_Unk64                     = 64,
    PlayerState_Unk65                     = 65,
    PlayerState_Unk66                     = 66,
    PlayerState_Unk67                     = 67,
    PlayerState_Unk68                     = 68,
    PlayerState_Unk69                     = 69,
    PlayerState_Unk70                     = 70,
    PlayerState_Unk71                     = 71,
    PlayerState_Unk72                     = 72,
    PlayerState_Unk73                     = 73,
    PlayerState_Unk74                     = 74,
    PlayerState_Unk75                     = 75,
    PlayerState_Unk76                     = 76,
    PlayerState_Unk77                     = 77,
    PlayerState_Unk78                     = 78,
    PlayerState_Unk79                     = 79,
    PlayerState_Unk80                     = 80,
    PlayerState_Unk81                     = 81,
    PlayerState_Unk82                     = 82,
    PlayerState_Unk83                     = 83,
    PlayerState_Unk84                     = 84,
    PlayerState_Unk85                     = 85,
    PlayerState_Unk86                     = 86,
    PlayerState_Unk87                     = 87,
    PlayerState_Unk88                     = 88,
    PlayerState_Unk89                     = 89,
    PlayerState_Unk90                     = 90,
    PlayerState_Unk91                     = 91,
    PlayerState_Unk92                     = 92,
    PlayerState_Unk93                     = 93,
    PlayerState_Unk94                     = 94,
    PlayerState_Unk95                     = 95,
    PlayerState_Unk96                     = 96,
    PlayerState_Unk97                     = 97,
    PlayerState_Unk98                     = 98,
    PlayerState_Unk99                     = 99,
    PlayerState_Unk100                    = 100,
    PlayerState_Unk101                    = 101,
    PlayerState_Unk102                    = 102,
    PlayerState_Unk103                    = 103,
    PlayerState_Unk104                    = 104,
    PlayerState_Unk105                    = 105,
    PlayerState_Unk106                    = 106,
    PlayerState_Unk107                    = 107,
    PlayerState_Unk108                    = 108,
    PlayerState_Unk109                    = 109,
    PlayerState_Unk110                    = 110,
    PlayerState_Unk111                    = 111,
    PlayerState_Unk112                    = 112,
    PlayerState_Unk113                    = 113,
    PlayerState_Unk114                    = 114,
    PlayerState_Unk115                    = 115,
    PlayerState_Unk116                    = 116,
    PlayerState_Unk117                    = 117,
    PlayerState_Unk118                    = 118,
    PlayerState_Unk119                    = 119,
    PlayerState_Unk120                    = 120,
    PlayerState_Unk121                    = 121,
    PlayerState_Unk122                    = 122,
    PlayerState_Unk123                    = 123,
    PlayerState_Unk124                    = 124,
    PlayerState_Unk125                    = 125,
    PlayerState_Unk126                    = 126,
    PlayerState_Unk127                    = 127,
    PlayerState_Unk128                    = 128,
    PlayerState_Unk129                    = 129,
    PlayerState_Unk130                    = 130,
    PlayerState_Unk131                    = 131,
    PlayerState_Unk132                    = 132,
    PlayerState_Unk133                    = 133,
    PlayerState_Unk134                    = 134,
    PlayerState_Unk135                    = 135,
    PlayerState_Unk136                    = 136,
    PlayerState_Unk137                    = 137,
    PlayerState_Unk138                    = 138,
    PlayerState_Unk139                    = 139,
    PlayerState_Unk140                    = 140,
    PlayerState_Unk141                    = 141,
    PlayerState_Unk142                    = 142,
    PlayerState_Unk143                    = 143,
    PlayerState_Unk144                    = 144,
    PlayerState_Unk145                    = 145,
    PlayerState_Unk146                    = 146,
    PlayerState_Unk147                    = 147,
    PlayerState_Unk148                    = 148,
    PlayerState_Unk149                    = 149,
    PlayerState_Unk150                    = 150,
    PlayerState_Unk151                    = 151,
    PlayerState_Unk152                    = 152,
    PlayerState_Unk153                    = 153,
    PlayerState_Unk154                    = 154,
    PlayerState_Unk155                    = 155,
    PlayerState_Unk156                    = 156,
    PlayerState_Unk157                    = 157,
    PlayerState_Unk158                    = 158,
    PlayerState_Unk159                    = 159,
    PlayerState_Unk160                    = 160,
    PlayerState_Unk161                    = 161,
    PlayerState_Unk162                    = 162,
    PlayerState_Unk163                    = 163,
    PlayerState_Unk164                    = 164,
    PlayerState_Unk165                    = 165,
    PlayerState_Unk166                    = 166,
    PlayerState_Unk167                    = 167,
    PlayerState_Unk168                    = 168,
    PlayerState_Unk169                    = 169,
    PlayerState_Unk170                    = 170,
    PlayerState_Unk171                    = 171,
    PlayerState_Unk172                    = 172,
    PlayerState_Unk173                    = 173,
    PlayerState_Unk174                    = 174,
    PlayerState_Unk175                    = 175,
    PlayerState_Unk176                    = 176,
    PlayerState_Unk177                    = 177,
    PlayerState_Unk178                    = 178,
    PlayerState_Unk179                    = 179,
    PlayerState_Unk180                    = 180
} e_PlayerState;

/** @brief Upper body player states. */
typedef enum _PlayerUpperBodyState
{
    PlayerUpperBodyState_None                 = 0,
    PlayerUpperBodyState_WalkForward          = 1,
    PlayerUpperBodyState_RunForward           = 2,
    PlayerUpperBodyState_RunWallStop          = 3,
    PlayerUpperBodyState_SidestepRight        = 4,
    PlayerUpperBodyState_SidestepLeft         = 5,
    PlayerUpperBodyState_RunRight             = 6,
    PlayerUpperBodyState_RunLeft              = 7,
    PlayerUpperBodyState_WalkBackward         = 8,
    PlayerUpperBodyState_QuickTurnRight       = 9,
    PlayerUpperBodyState_QuickTurnLeft        = 10,
    PlayerUpperBodyState_TurnRight            = 11,
    PlayerUpperBodyState_TurnLeft             = 12,
    PlayerUpperBodyState_RunJumpBackward      = 13,
    PlayerUpperBodyState_LowerBodyStumble     = 14,
    PlayerUpperBodyState_RunLeftWallStop      = 15,
    PlayerUpperBodyState_RunRightWallStop     = 16,
    PlayerUpperBodyState_RunLeftStumble       = 17,
    PlayerUpperBodyState_SidestepRightStumble = 18,
    PlayerUpperBodyState_Aim                  = 19,
    PlayerUpperBodyState_AimTargetLock        = 20,
    PlayerUpperBodyState_AimStart             = 21,
    PlayerUpperBodyState_AimStartTargetLock   = 22,
    PlayerUpperBodyState_AimTargetLockSwitch  = 23,
    PlayerUpperBodyState_AimStop              = 24,
    PlayerUpperBodyState_Attack               = 25,
    PlayerUpperBodyState_Reload               = 26
} e_PlayerUpperBodyState;

/** @brief Lower body player states. */
typedef enum _PlayerLowerBodyState
{
    PlayerLowerBodyState_None               = 0,
    PlayerLowerBodyState_WalkForward        = 1,
    PlayerLowerBodyState_RunForward         = 2,
    PlayerLowerBodyState_RunForwardWallStop = 3,
    PlayerLowerBodyState_WalkBackward       = 4,
    PlayerLowerBodyState_SidestepRight      = 5,
    PlayerLowerBodyState_SidestepLeft       = 6,
    PlayerLowerBodyState_RunRight           = 7, // } TODO: Check. Could be swapped.
    PlayerLowerBodyState_RunLeft            = 8, // }
    PlayerLowerBodyState_QuickTurnRight     = 9,
    PlayerLowerBodyState_QuickTurnLeft      = 10,
    PlayerLowerBodyState_JumpBackward       = 11,
    PlayerLowerBodyState_Stumble            = 12,
    PlayerLowerBodyState_RunLeftWallStop    = 13,
    PlayerLowerBodyState_RunRightWallStop   = 14,
    PlayerLowerBodyState_RunRightStumble    = 16,
    PlayerLowerBodyState_RunLeftStumble     = 15,
    PlayerLowerBodyState_Unk17              = 17,
    PlayerLowerBodyState_Unk18              = 18,
    PlayerLowerBodyState_Unk19              = 19,
    PlayerLowerBodyState_Aim                = 20,
    PlayerLowerBodyState_AimWalkForward     = 21,
    PlayerLowerBodyState_Unk22              = 22, // @unused `PlayerLowerBodyState_AimRunForward`?
    PlayerLowerBodyState_Unk23              = 23, // @unused `PlayerLowerBodyState_AimRunWallStop`?
    PlayerLowerBodyState_AimWalkBackward    = 24,
    PlayerLowerBodyState_AimSidestepRight   = 25,
    PlayerLowerBodyState_AimSidestepLeft    = 26,
    PlayerLowerBodyState_AimRunRight        = 27, // @unused
    PlayerLowerBodyState_AimRunLeft         = 28, // @unused
    PlayerLowerBodyState_AimQuickTurnRight  = 29,
    PlayerLowerBodyState_AimQuickTurnLeft   = 30,
    PlayerLowerBodyState_Unk31              = 31, // Something backward?
    PlayerLowerBodyState_Unk32              = 32,
    PlayerLowerBodyState_Unk33              = 33,
    PlayerLowerBodyState_Attack             = 34,
    PlayerLowerBodyState_Reload             = 35
} e_PlayerLowerBodyState;

/** @brief Player animation indices. */
typedef enum _PlayerAnim
{
    PlayerAnim_Unk0                    = 0,
    PlayerAnim_Unk1                    = 1, // Start walk forward?
    PlayerAnim_WalkForward             = 2,
    PlayerAnim_RunForward              = 3,
    PlayerAnim_WalkBackward            = 4,
    PlayerAnim_SidestepLeft            = 5,
    PlayerAnim_SidestepRight           = 6,
    PlayerAnim_RunLeft                 = 7,
    PlayerAnim_RunRight                = 8,
    PlayerAnim_RunForwardWallStopRight = 9,
    PlayerAnim_RunForwardWallStopLeft  = 10,
    PlayerAnim_RunForwardStumble       = 11,
    PlayerAnim_TurnLeft                = 12,
    PlayerAnim_TurnRight               = 13,
    PlayerAnim_QuickTurnRight          = 14,
    PlayerAnim_QuickTurnLeft           = 15,
    PlayerAnim_JumpBackward            = 16,
    PlayerAnim_LookAround              = 17,
    PlayerAnim_RunLeftWallStop         = 18,
    PlayerAnim_RunLeftStumble          = 19,
    PlayerAnim_RunRightWallStop        = 20,
    PlayerAnim_RunRightStumble         = 21,
    PlayerAnim_FallForward             = 22,
    PlayerAnim_FallBackward            = 23,
    PlayerAnim_Kick                    = 24,
    PlayerAnim_Stomp                   = 25,
    PlayerAnim_Idle                    = 26,
    PlayerAnim_IdleTired               = 27,
    PlayerAnim_HandgunAim              = 28,
    PlayerAnim_Unk29                   = 29, // } Handgun.
    PlayerAnim_Unk30                   = 30, // }
    PlayerAnim_HandgunRecoil           = 31,
    PlayerAnim_Unk32                   = 32,
    PlayerAnim_Unk33                   = 33,
    PlayerAnim_Unk34                   = 34,
    PlayerAnim_Unk35                   = 35,
    PlayerAnim_Unk36                   = 36,
    PlayerAnim_Unk37                   = 37,

    // NOTE: Anims 28 and above are per-map. Will need separate enums or could do `#ifdef` magic here if it works.

    PlayerAnim_Death                   = 40,

    // 56 - duplicate stomp?

    // Probably combat anims and many cutscene anims here.

    // TODO: Anims ahead not entirely clear. Need to confirm before naming definitively. Some grab/release anims might be split in two, hence the gaps.

    PlayerAnim_Unk115                  = 115, // Enemy grab torso front?

    PlayerAnim_Unk117                  = 117, // Enemy grab torso back?
    PlayerAnim_Unk118                  = 118, // Enemy grab legs back?

    PlayerAnim_Unk120                  = 120, // Enemy release upper front?
    PlayerAnim_Unk121                  = 121, // Damage head?
    PlayerAnim_Unk122                  = 122, // Enemy release upper front?
    PlayerAnim_Unk123                  = 123, // Enemy release lower back?

    PlayerAnim_Unk125                  = 125, // Enemy grab neck front and back?

    PlayerAnim_Unk127                  = 127, // Enemy grab pinned front?
    PlayerAnim_Unk128                  = 128, // Enemy grab pinned back?
    PlayerAnim_Unk129                  = 129, // Enemy release pinned front?
    PlayerAnim_Unk130                  = 130, // Enemy release pinned back?
    PlayerAnim_Unk131                  = 131, // Damage thrown front? Also used to recover from pinned grab.
    PlayerAnim_Unk132                  = 132, // Damage thrown back? Also used to recover from pinned grab.
    PlayerAnim_Unk133                  = 133, // Get up front?
    PlayerAnim_Unk134                  = 134  // Get up back?
} s_PlayerAnim;

// ========
// STRUCTS
// ========

/** TODO: Maybe `s_PlayerAttack` fits. */
typedef struct _800AFBF4
{
    s16 attackSfx_0;
    s16 reloadSfx_2;
    s16 outOfAmmoSfx_4;
    u8  animStopAiming_6; /** Packed anim status. See `s_ModelAnim::status_0`. */
    u8  animAttack_7;     /** Packed anim status. See `s_ModelAnim::status_0`. */
    u8  animAttackHold_8;
    u8  field_9;
    u8  field_A; // Attack type?
    u8  unk_B;
} s_800AFBF4;
STATIC_ASSERT_SIZEOF(s_800AFBF4, 12);

// ========
// GLOBALS
// ========

/** @brief `bool` | Determines if the player is transitioning from a walk to a run and vice-versa. */
extern u8 g_Player_IsInWalkToRunTransition; // 0x800AF214

/** Boolean. */
extern u8 g_Player_DisableControl; // 0x800AF215

extern u8 D_800AF216; // 0x800AF216

/** @brief Indicates the direction which the Rock Drill will attack based on the press of
 * the movement directions.
 *
 * -1: Backward move - Pointing down.
 *  0: No input      - Pointing at the center.
 *  1: Forward move  - Pointing up.
 */
extern s8 g_Player_RockDrill_DirectionAttack; // 0x800AF217

/** Another variable that saves the index of the enemy being attacked. */
extern s32 D_800AF21C; // 0x800AF21C

/** @brief Counts the amount inputs the player has pressed in order to free himselft from a grab. */
extern s32 g_Player_GrabFree_InputCount; // 0x800AF20C

/** @brief current attack animation. */
extern s32 g_Player_AttackAnimIdx; // 0x800AFBE8

/** @brief Indicates if a multiple button taps attack is being perfomed. */
extern s32 g_Player_IsMultiTapAttack; // 0x800AFBF0

/** @brief `e_AttackInputType` | Attack type performed by the player. */
extern s32 g_Player_MeleeAttackType; // 0x800AFBEC

extern s_800AFBF4 D_800AFBF4[11]; // 0x800AFBF4

/** @brief Player rotation speed.
 * More context is required for a name.
 */
extern q19_12 D_800C454C;

/** @brief Player movement speed.
 * More context is required for a name.
 */
extern q19_12 D_800C4550; // 0x800C4550

/** @brief Used to cancel the idle state if the Action or Run button is tapped. */
extern s32 g_Player_ActionRunPressed; // 0x800C455C

/** @brief Determines if the player is pressing a movement button or the right analog stick. */
extern s32 g_Player_MovementInputDetected; // 0x800C4558

extern s_800AFBF4 g_Player_EquippedWeaponInfo; // 0x800C4570

/** `D_800C457C` could be related to animations that play during cutscenes.
 * 
 * Called by:
 * - 'func_800D2C7C' in map0_s00.c
 * - 'func_800D2D2C' in map0_s00.c
 * 
 * The value changes during cutscenes when the player does any of the following
 * actions:
 * * 0 - Nothing
 * * 1 - Walking
 * * 3 - Moves to the right?
 * * 4 - Moves to the left
 * 
 * This behaviour is irregular. After the first in-game dialogue
 * with Harry, the value is kept as 1 (even when he is not walking or in
 * a cutscene) until the next dialogue triggers (when Harry sees
 * Cheryl and the second FMV plays). Something similar happens on the
 * next overlay where the value is 1 during the first
 * cutscene and doesn't change until the player makes an input.
 */
extern u8 D_800C457C; // 0x800C457C

/** @brief Defines if the player is triggering the aiming action. */
extern u16 g_Player_IsAiming; // 0x800C457E

extern u16 g_Player_IsSteppingLeftTap; // 0x800C4580

extern u16 g_Player_IsSteppingRightTap; // 0x800C4582

extern u16 g_Player_IsTurningLeft; // 0x800C4584

extern u16 g_Player_IsTurningRight; // 0x800C4586

extern u16 g_Player_IsSteppingLeftHold; // 0x800C45AC

extern u16 g_Player_IsSteppingRightHold; // 0x800C45AE

extern u16 g_Player_IsHoldAttack; // 0x800C45BC

extern u16 g_Player_IsAttacking; // 0x800C45BE

extern u16 g_Player_IsShooting; // 0x800C45C0

extern u16 g_Player_IsMovingForward; // 0x800C45E8

extern u16 g_Player_IsMovingBackward; // 0x800C45F0

/** @brief Defines if the player is triggering the running action. */
extern u16 g_Player_IsRunning; // 0x800C4604

extern s32 g_Player_HeadingAngle;

/** `bool`
 *
 * @note Possibly inaccurrate name or buggy functionality. If enemies grab the
 * player with this set to `true`, the user will be unable to interact with anything.
 */
extern u8 g_Player_DisableDamage; // 0x800C4562

extern q19_12 D_800C45DC;

extern VECTOR3 D_800C45F8;

// ==========
// FUNCTIONS
// ==========

/** Used for enemy target locking. */
void func_8005CD38(s32*, s32*, s_PlayerCombat*, s32, s32, s32);

/** Used for running displacement. */
void func_80070CF0(s_SubCharacter* chara, q19_12 arg1, s32 arg2, q19_12 arg3, s32 arg4); // 0x80070CF0

void Player_CharaTurn_0(s_SubCharacter* chara, e_PlayerLowerBodyState currentState); // 0x800711C4

void Player_CharaTurn_1(s_SubCharacter* chara, e_PlayerLowerBodyState currentState); // 0x80071224

void Player_CharaRotate(s32 speed); // 0x80071284

/** @brief Clears movement variables and reset Harry's lower body part animation states in case
 * of switching the player state.
 */
void Player_MovementStateReset(s_SubCharacter* chara, e_PlayerLowerBodyState lowerBodyState); // 0x800713B4

/** Audio-related. */
bool func_800713E8(s32 animStatus, s_SubCharacter* chara, s32 keyframe0, s32 keyframe1, s32 sfx, s8 pitch);

/** @brief Main update function for player functionality.
 *
 * @note SH2 symbols have a similar function named `PlayerFunction`, but code-wise they
 * doesn't share many similarities.
 */
void Player_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord); // 0x800717D0

void func_80071968(s_SubCharacter* chara, s_MainCharacterExtra* extra, void* arg2, GsCOORDINATE2* coord); // 0x80071968

/** @brief Main update function for player logic. */
void Player_LogicUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord); // 0x80071CE8

/** @brief Updates `g_SysWork.player_4C.extra_128.upperBodyState_20` and prepares
 * transitions between running to and from walking animations.
 *
 * @param extra Pointer to `s_MainCharacterExtra` struct.
 * @param upperState Check if `g_SysWork.player_4C.extra_128.upperBodyState_20` is not the same being input in order to clear animation status.
 * @param unused @unused Possibly animation index.
 * @param arg3 Player turn state. Only affects turn animations.
 * * 0 and 2: Idle state.
 * *       1: Any turn state.
 * *       3: Left turn state.
 * *       4: Right turn state.
 */
void Player_UpperBodyStateUpdate(s_MainCharacterExtra* extra, e_PlayerUpperBodyState upperState, s32 unused, s32 arg3); // 0x80073FC0

/** @brief Triggers animations and actions performed by the player's upper body. */
void Player_UpperBodyUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80074254

/** @brief Updates animations and status related to player attacks.
 * Returns `true` if animations where succefully finished and if performing a multitap attack.
 */
bool Player_CombatAnimUpdate();

/** @brief Main animation and state handler for the player's upper body.
 * Returns `true` if combat animations where completed or if the player's health is >60%.
 */
bool Player_UpperBodyMainUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80075504

/** @brief Updates upper body states related to combat. */
void Player_CombatStateUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x800771BC

/** @brief Cancels movement when the player abruptly stops running sideways. */
void Player_StepWallStop_MovementCancel(s_SubCharacter* chara, s32 arg1, s32 animStatus, s32 keyframeIdx, e_PlayerLowerBodyState lowerBodyState, s32 headingAngle, s32 aimState); // 0x80077BB8

/** @brief Main player movement function. */
void Player_LowerBodyUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80077D00

/** @brief Multiple purposes.
 * * Assigns the value used by a global that handles player movement.
 * * Deals with the exhaustion variable (When Harry has been running for too long).
 * * Restarts the animation state if the player is not longer exhausted or has recovered health.
 * * Handles audio related to Harry's movements.
 */
void func_8007B924(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x8007B924

/** @brief Checks for damage received by the player and handles the animations
 * for getting hurt or grabbed by monsters.
 *
 * @note SH2 symbols have a similar function named `PlayerCheckDamage`, but code-wise it has
 * no similarities.
 */
void Player_ReceiveDamage(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x8007C800

// Removing this function makes it impossible to run.
s32 func_8007D6F0(s_SubCharacter* chara, s_800C45C8* arg1); // 0x8007D6F0

void func_8007EBBC(); // 0x8007EBBC

void Game_PlayerMovementsReset(); // 0x8007F1CC

void Player_Controller(); // 0x8007F32C

/** @brief Determines if the player can stomp or kick a knocked enemy. */
bool func_8007F95C(); // 0x8007F95C

#endif
