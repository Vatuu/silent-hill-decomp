#ifndef _PLAYER_LOGIC_H
#define _PLAYER_LOGIC_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the player logic.
 */

// ======
// ENUMS
// ======

/** @note The game handles the upper and lower part of Harry with different states.
 * Curiously by SH2 symbols indicate that the player is handle in a similar way, by
 * separating them between 4 types (based on the part and control scheme):
 * lower_*_2D
 * lower_*_3D
 * upper_*_2D
 * upper_*_3D
 *
 * For the first two enums here, in SH2 there are two enums named as `_JAMES_UPPER_STATUS`
 * and `_JAMES_LOWER_STATUS` that could likely hint this tecnique was carry over to the
 * sequel their real names of the enums with some differences as for example: Stepping
 * in a enemy has a specific value in the SH2's enums while in SH1 stepping is part of
 * `g_SysWork.player_4C.extra_128.field_1C`.
 */
 
typedef enum _PlayerSubMovement
{
    PlayerSubMovement_None                   = 0,
    PlayerSubMovement_Walk_Forward           = 1,
    PlayerSubMovement_Run_Forward            = 2,
    PlayerSubMovement_Run_AbruptStop         = 3,
    PlayerSubMovement_Walk_RStep             = 4,
    PlayerSubMovement_Walk_LStep             = 5,
    PlayerSubMovement_Run_RStep              = 6,
    PlayerSubMovement_Run_LStep              = 7,
    PlayerSubMovement_Walk_Backward          = 8,
    PlayerSubMovement_QuickTurn_Right        = 9,
    PlayerSubMovement_QuickTurn_Left         = 10,
    PlayerSubMovement_RRotation              = 11,
    PlayerSubMovement_LRotation              = 12,
    PlayerSubMovement_Run_BackwardJump       = 13,
    PlayerSubMovement_PlayerMovement_Stumble = 14,
    PlayerSubMovement_Run_LStep_AbruptStop   = 15,
    PlayerSubMovement_Run_RStep_AbruptStop   = 16,
    PlayerSubMovement_Run_LStep_Stumble      = 17,
    PlayerSubMovement_RStep_Stumble          = 18,
    PlayerSubMovement_Aim                    = 19,
    PlayerSubMovement_Aim_TargetLock         = 20,
    PlayerSubMovement_Aim_Start              = 21,
    PlayerSubMovement_Aim_Start_TargetLock   = 22,
    PlayerSubMovement_Aim_TargetLock_Switch  = 23,
    PlayerSubMovement_Aim_Stop               = 24,
    PlayerSubMovement_Attack                 = 25,
    PlayerSubMovement_Reload                 = 26
} e_PlayerSubMovement;

typedef enum _PlayerMovement
{
    PlayerMovement_None                 = 0,
    PlayerMovement_Walk_Forward         = 1,
    PlayerMovement_Run_Forward          = 2,
    PlayerMovement_Run_AbruptStop       = 3,
    PlayerMovement_Walk_Backward        = 4,
    PlayerMovement_Walk_RStep           = 5,
    PlayerMovement_Walk_LStep           = 6,
    PlayerMovement_Run_RStep            = 7,
    PlayerMovement_Run_LStep            = 8,
    PlayerMovement_QuickTurn_Right      = 9,
    PlayerMovement_QuickTurn_Left       = 10,
    PlayerMovement_Run_BackwardJump     = 11,
    PlayerMovement_Stumble              = 12,
    PlayerMovement_Run_LStep_AbruptStop = 13,
    PlayerMovement_Run_RStep_AbruptStop = 14,
    PlayerMovement_Run_RStep_Stumble    = 16,
    PlayerMovement_Run_LStep_Stumble    = 15,
    PlayerMovement_Unk17                = 17,
    PlayerMovement_Unk18                = 18,
    PlayerMovement_Unk19                = 19,
    PlayerMovement_Aim                  = 20,
    PlayerMovement_Aim_Walk_Forward     = 21,
    PlayerMovement_Unk22                = 22, // Unused PlayerMovement_Aim_Run_Forward?
    PlayerMovement_Unk23                = 23, // Unused PlayerMovement_Aim_Run_AbruptStop?
    PlayerMovement_Aim_Walk_Backward    = 24,
    PlayerMovement_Aim_RStep            = 25,
    PlayerMovement_Aim_LStep            = 26,
    PlayerMovement_Aim_Run_RStep        = 27, // Unused.
    PlayerMovement_Aim_Run_LStep        = 28, // Unused.
    PlayerMovement_Aim_QuickTurn_Right  = 29,
    PlayerMovement_Aim_QuickTurn_Left   = 30,
    PlayerMovement_Unk31                = 31,
    PlayerMovement_Unk32                = 32,
    PlayerMovement_Unk33                = 33,
    PlayerMovement_Attack               = 34,
    PlayerMovement_Reload               = 35
} e_PlayerMovement;

// ========
// STRUCTS
// ========

typedef struct _800AFBF4
{
    s16 attackSfx_0;
    s16 reloadSfx_2;
    s16 outOfAmmoSfx_4;
    u8  animStopAiming_6;
    u8  animAttack_7;
    u8  animAttackHold_8;
    u8  field_9;
    u8  field_A; // Attack type?
    u8  unk_B;
} s_800AFBF4;
STATIC_ASSERT_SIZEOF(s_800AFBF4, 12);

// ========
// GLOBALS
// ========

/** @brief Boolean. Defines if the player is transitioning from walking to running and vice-versa. */
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

/** @brief Attack animation currently playing. */
extern s32 g_Player_AttackAnimationIdx; // 0x800AFBE8

/** @brief Indicates if a multiple button taps attack is being perfomed. */
extern s32 g_Player_IsMultiTapAttack; // 0x800AFBF0

/** @brief Used to asign the type of attack performed based on the .
 *
 * 0: Tap
 * 1: Hold
 * 2: Multiple taps
 */
extern s32 g_Player_MeleeAttackType; // 0x800AFBEC

extern s_800AFBF4 D_800AFBF4[10]; // 0x800AFBF4

/** @brief Used to indicate player rotation speed.
 * More context is required for asign it a name.
 */
extern q19_12 D_800C454C;

/** @brief Used to indicate player movement speed.
 * More context is required for asign it a name.
 */
extern q19_12 D_800C4550; // 0x800C4550

/** @brief Used to cancel idle state in case of tapping the action or run button. */
extern s32 g_Player_ActionRunPressed; // 0x800C455C

/** @brief Defines if the player is pressing a movement button or the right analog stick. */
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

extern u16 g_Player_IsStepping_Left_Tap; // 0x800C4580

extern u16 g_Player_IsStepping_Right_Tap; // 0x800C4582

extern u16 g_Player_IsTurning_Left; // 0x800C4584

extern u16 g_Player_IsTurning_Right; // 0x800C4586

extern u16 g_Player_IsStepping_Left_Hold; // 0x800C45AC

extern u16 g_Player_IsStepping_Right_Hold; // 0x800C45AE

extern u16 g_Player_IsHoldAttack; // 0x800C45BC

extern u16 g_Player_IsAttacking; // 0x800C45BE

extern u16 g_Player_IsShooting; // 0x800C45C0

extern u16 g_Player_IsMovingForward; // 0x800C45E8

extern u16 g_Player_IsMovingBackward; // 0x800C45F0

/** @brief Defines if the player is triggering the running action. */
extern u16 g_Player_IsRunning; // 0x800C4604

/** Boolean.
 * @note Possibly inaccurrate name or buggy functionality. If enemies grab the
 * player with this set to `true`, the user will be unable to interact with anything.
 */
extern u8 g_Player_DisableDamage; // 0x800C4562

extern q19_12 D_800C45DC;

extern VECTOR3 D_800C45F8;

// ==========
// FUNCTIONS
// ==========

/** Used for running displacement. */
void func_80070CF0(s_SubCharacter* chara, q19_12 arg1, s32 arg2, q19_12 arg3, s32 arg4); // 0x80070CF0

void Player_CharaTurn_0(s_SubCharacter* chara, e_PlayerMovement currentState); // 0x800711C4

void Player_CharaTurn_1(s_SubCharacter* chara, e_PlayerMovement currentState); // 0x80071224

void Player_CharaRotate(s32 speed); // 0x80071284

/** @brief Clears movement variables and reset Harry's lower body part animation states in case
 * of switching the player state.
 */
void Player_MovementStateReset(s_SubCharacter* chara, e_PlayerMovement state); // 0x800713B4

/** Audio related. */
s32 func_800713E8(s32 animIdx, s_SubCharacter* chara, s32 arg2, s32 arg3, s32 arg4, s8 arg5);

/** @brief Main update function for player logic.
 *
 * @note SH2 symbols have a similar function named `PlayerFunction`, but code-wise they
 * doesn't share many similarities.
 */
void Player_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord); // 0x800717D0

void func_80071968(s_SubCharacter* chara, s_MainCharacterExtra* extra, void* arg2, GsCOORDINATE2* coord); // 0x80071968

/** @brief Updates `g_SysWork.player_4C.extra_128.playerSubMovement_20` and prepares
 * transitions between running to and from walking animation.
 *
 * @param `extra` Pointer to `s_MainCharacterExtra` struct.
 * @param `state` Checks if `g_SysWork.player_4C.extra_128.playerSubMovement_20` is not
 * the same being input in order to clear animation status.
 * @param `unused` Possibly intented to pass animation index.
 * @param `arg3` Indicates the player rotation state. This states will only affect the rotation animations.
 * * 0 and 2: The player will be at idle state.
 * *       1: The player can be at any of the rotation state.
 * *       3: The player can be only at the left rotation state.
 * *       4: The player can be only at the right rotation state.
 */
void Player_MovementsSub_StateUpdate(s_MainCharacterExtra* extra, e_PlayerSubMovement state, s32 unused, s32 arg3); // 0x80073FC0

/** @brief Trigger animations and actions done in the upper half part of Harry's body (arms, torso and head). */
void Player_MovementsSub(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80074254

/** @note Important for handling `g_SysWork.player_4C.extra_128.field_20`.
 * Also Important for handling animations.
 */
bool func_80075504(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80075504

void func_800771BC(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x800771BC

/** @brief Cancels movement when the player abruptly stop the running while stepping movement. */
void Player_StepAbruptStop_MovementCancel(s_SubCharacter* chara, s32 arg1, s32 animIdx, s32 keyframeIdx, e_PlayerMovement playerState, q19_12 arg5, s32 aimingState); // 0x80077BB8

/** @brief Main player movement function. */
void Player_MovementsMain(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x80077D00

/** @brief Function with multiple purposes.
 * This function does:
 * * Asign the value used by a global that handles player movement.
 * * Deals with the exhaustion variable (When Harry has been running for too long).
 * * Restart the animation state in case of the player no longer being with low health
 *   and exhausted.
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

// Removing this function makes impossible to run.
s32 func_8007D6F0(s_SubCharacter* chara, s_800C45C8* arg1); // 0x8007D6F0

void func_8007EBBC(); // 0x8007EBBC

void Game_PlayerMovementsReset(); // 0x8007F1CC

void Player_Controller(); // 0x8007F32C

/** Player func. */
bool func_8007F95C(); // 0x8007F95C

#endif
