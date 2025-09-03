#include "game.h"
#include "inline_no_dmpsx.h"

#include <libapi.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"

// INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", D_80028B94);

// INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", D_800294F4); // Causes missmatch

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_800706E4); // 0x800706E4

void func_80070B84(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3) // 0x80070B84
{
    s16  temp_v0;
    s32  var_v0;
    s16* new_var;

    if (!D_800AF216)
    {
        var_v0 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
    }
    else
    {
        var_v0 = D_800AF216;
    }

    arg1 = arg1 + ((arg2 - arg1) * (var_v0 - 0x40) / 64);

    // HACK: Wrapping in loop required for match.
    do
    { 
        if (arg1 < g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126)
        {
            temp_v0                                                                 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 - ((Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2);
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = temp_v0;
            if (temp_v0 < arg1)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = arg1;
            }
        }
        else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < arg1)
        {
            new_var = &g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            if (chara->model_0.anim_4.keyframeIdx0_8 >= arg3)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = *new_var + Math_UnkDistTimeCalc(FP_TIME(0.4f));
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(*new_var, 0, arg1);
        }
    }
    while (false);
}

// TODO: Matched with register swap issues.
// Scratch: https://decomp.me/scratch/AItzp
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_80070CF0); // 0x80070CF0

void func_80070DF0(s_MainCharacterExtra* extra, s_SubCharacter* chara, s32 arg2, s32 animStatus)  // 0x80070DF0
{
    s16 shortestAngle;
    s16 temp_a1;

    if (extra->model_0.stateStep_3 == 0) 
    {
        extra->model_0.anim_4.status_0 = animStatus - 1;
        extra->model_0.stateStep_3++;
    }

    if (chara->model_0.stateStep_3 == 0) 
    {
        chara->model_0.anim_4.status_0 = animStatus - 1;
        chara->model_0.stateStep_3++;
    }

    temp_a1 = (ratan2((g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vx + g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_0) - g_SysWork.playerCombatInfo_38.field_0.vx, 
                      (g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vz + g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_2) - g_SysWork.playerCombatInfo_38.field_0.vz) + 0x1000) & 0xFFF;
    chara->rotation_24.pad = temp_a1;
    Math_ShortestAngleGet(chara->rotation_24.vy, temp_a1, &shortestAngle);

    if (ABS(shortestAngle) >= FP_ANGLE(8.5f)) 
    {
        if (shortestAngle < 0) 
        {
            chara->rotation_24.vy -= FP_ANGLE(8.5f);
        } 
        else 
        {
            chara->rotation_24.vy += FP_ANGLE(8.5f);
        }
    }

    if (extra->model_0.anim_4.keyframeIdx0_8 >= g_MaybePlayerAnims[animStatus].keyframeIdx0_C + D_800AD4C8[arg2].field_E && 
        g_MaybePlayerAnims[animStatus].keyframeIdx0_C + D_800AD4C8[arg2].field_E + D_800AD4C8[arg2].field_F >= extra->model_0.anim_4.keyframeIdx0_8)
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F = arg2;

        if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2)) 
        {
            chara->field_44                                             = 1;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
        }
    }

    if (animStatus == ANIM_STATUS(PlayerAnim_Unk24, true) &&
        IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        g_SysWork.player_4C.chara_0.field_D8.field_0 = FP_MULTIPLY(D_800AF014[chara->model_0.anim_4.keyframeIdx0_8 - 457], Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_2 = -FP_MULTIPLY(D_800AF014[chara->model_0.anim_4.keyframeIdx0_8 - 457], Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
    }

    if (animStatus == ANIM_STATUS(PlayerAnim_Unk25, true) &&
        IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0)) 
    {
        g_SysWork.player_4C.chara_0.field_D8.field_0 = FP_MULTIPLY(D_800AF04C[chara->model_0.anim_4.keyframeIdx0_8 - 485], Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_2 = -FP_MULTIPLY(D_800AF04C[chara->model_0.anim_4.keyframeIdx0_8 - 485], Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
    }

    if (chara->model_0.anim_4.status_0 == animStatus &&
        chara->model_0.anim_4.keyframeIdx0_8 == g_MaybePlayerAnims[animStatus].keyframeIdx1_E)
    {
        g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
        chara->model_0.stateStep_3                                  = 0;
        chara->model_0.state_2                                      = 0;
        extra->model_0.stateStep_3                                  = 0;
        extra->model_0.state_2                                      = 0;
        g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_None;
        g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_None;
        g_SysWork.player_4C.chara_0.field_D8.field_6                = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_4                = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_2                = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_0                = 0;
        g_SysWork.playerCombatInfo_38.equippedWeapon_F              = (g_SavegamePtr->equippedWeapon_AA == InventoryItemId_Unequipped) ? InventoryItemId_Empty : (g_SavegamePtr->equippedWeapon_AA + 128);
        g_SysWork.enemyTargetIdx_2353                               = NO_VALUE;
        g_SysWork.playerCombatInfo_38.isAiming_13                   = false;
    }
}

void Player_CharaTurn_0(s_SubCharacter* chara, e_PlayerLowerBodyState currentState) // 0x800711C4
{
    if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack || !g_Player_IsSteppingLeftTap || !g_Player_IsSteppingRightTap)
    {
        return;
    }

    if (g_Player_IsTurningLeft)
    {
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = currentState + PlayerLowerBodyState_QuickTurnLeft;
    }
    else
    {
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = currentState + PlayerLowerBodyState_QuickTurnRight;
    }
}

void Player_CharaTurn_1(s_SubCharacter* chara, e_PlayerLowerBodyState currentState) // 0x80071224
{
    if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack || g_Player_IsSteppingLeftTap == 0 || g_Player_IsSteppingRightTap == 0)
    {
        return;
    }

    if (g_Player_IsTurningRight)
    {
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = currentState + PlayerLowerBodyState_QuickTurnRight;
    }
    else
    {
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = currentState + PlayerLowerBodyState_QuickTurnLeft;
    }
}

void Player_CharaRotate(s32 speed) // 0x80071284
{
    if (g_GameWork.config_0.optExtraRetreatTurn_2A)
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((speed * g_DeltaTime0) * g_Player_IsTurningRight) >> 6; // Divide by `0x40 / 64`?
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((-speed * g_DeltaTime0) * g_Player_IsTurningLeft) >> 6;
        }
    }
    else if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_WalkBackward || g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_AimWalkBackward)
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((-speed * g_DeltaTime0) * g_Player_IsTurningRight) >> 6;
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((speed * g_DeltaTime0) * g_Player_IsTurningLeft) >> 6;
        }
    }
    else
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((speed * g_DeltaTime0) * g_Player_IsTurningRight) >> 6;
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((-speed * g_DeltaTime0) * g_Player_IsTurningLeft) >> 6;
        }
    }
}

void Player_MovementStateReset(s_SubCharacter* chara, e_PlayerLowerBodyState lowerBodyState) // 0x800713B4
{
    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != lowerBodyState)
    {
        chara->model_0.stateStep_3              = 0;
        chara->model_0.state_2                  = 0;
        chara->properties_E4.player.runTimer_F8 = 0;
        chara->properties_E4.player.afkTimer_E8 = 0;
        g_SysWork.field_235A                    = 0;
    }
}

bool func_800713E8(s32 animStatus, s_SubCharacter* chara, s32 keyframe0, s32 keyframe1, s32 sfx, s8 pitch)
{
    if (chara->model_0.anim_4.status_0 != animStatus) 
    {
        return false;
    }
    
    if (chara->model_0.anim_4.keyframeIdx0_8 >= keyframe1) 
    {
        if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk4)) 
        {
            if (pitch < 0x20)
            {
                switch (animStatus)
                {
                    case ANIM_STATUS(PlayerAnim_SidestepRight, true):
                    case ANIM_STATUS(PlayerAnim_SidestepLeft, true):
                    case ANIM_STATUS(PlayerAnim_TurnLeft, true):
                    case ANIM_STATUS(PlayerAnim_TurnRight, true):
                        func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.095f), pitch);
                        chara->properties_E4.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.25f), pitch);
                        chara->properties_E4.player.field_10C = pitch + 0x10;
                        break;
                }
            } 
            else 
            {
                func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.5f), pitch);
                chara->properties_E4.player.field_10C = pitch + 0x40;
            } 

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk4;
            return true;
        }
    }
    else
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk4;
    }

    if (chara->model_0.anim_4.keyframeIdx0_8 >= keyframe0) 
    {
        if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk5)) 
        {
            if (pitch < 0x20) 
            {
                switch (animStatus) 
                {
                    case ANIM_STATUS(PlayerAnim_SidestepRight, true):
                    case ANIM_STATUS(PlayerAnim_SidestepLeft, true):
                    case ANIM_STATUS(PlayerAnim_TurnLeft, true):
                    case ANIM_STATUS(PlayerAnim_TurnRight, true):
                        func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.095f), pitch);
                        chara->properties_E4.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.25f), pitch);
                        chara->properties_E4.player.field_10C = pitch + 0x10;
                        break;
                }
            } 
            else 
            {
                func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.5f), pitch);
                chara->properties_E4.player.field_10C = pitch + 0x40;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            return true;
        }
    } 
    else 
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
    }

    return false;  
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_80071620); // 0x80071620

void Player_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord) // 0x800717D0
{
    // Called by `GameState_InGame_Update`, might be player update function.
    // - `chara` always `&g_SysWork.player_4C.chara_0`.
    // - `arg1`  always `0x8010A600`/`FS_BUFFER_0` (holds anim data).
    // - `coord` always `&g_SysWork.playerBoneCoords_890`.

    s_MainCharacterExtra* extra;

    extra = &g_SysWork.player_4C.extra_128;

    if (g_DeltaTime0 != FP_TIME(0.0f))
    {
        Player_ReceiveDamage(chara, extra);

        if (g_Player_IsInWalkToRunTransition)
        {
            g_Player_ActionRunPressed      = false;
            g_Player_MovementInputDetected = false;
            g_Player_IsShooting            = false;
            g_Player_IsAttacking           = false;
            g_Player_IsHoldAttack          = false;
            g_Player_IsAiming              = false;
            g_Player_IsRunning             = false;
            g_Player_IsMovingBackward      = false;
            g_Player_IsMovingForward       = false;
            g_Player_IsSteppingRightTap    = false;
            g_Player_IsSteppingRightHold   = false;
            g_Player_IsTurningRight        = false;
            g_Player_IsSteppingLeftTap     = false;
            g_Player_IsSteppingLeftHold    = false;
            g_Player_IsTurningLeft         = false;
        }

        if (!g_Player_DisableControl)
        {
            Player_LogicUpdate(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_B8(chara, extra, coord);
        }

        if (!g_Player_DisableControl)
        {
            func_8007C0D8(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_BC(chara, extra, coord);
        }

        func_80071968(chara, extra, arg1, coord);
        func_8007D090(chara, extra, coord);
    }

    D_800C45B0.vx = 0;
    D_800C45B0.vz = 0;
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", D_800297B8);

static inline void func_80071968_Switch0()
{
    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Tap): 
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Multitap):
                func_8003DD80(1, 34); // `arg2` holds two values, split with `& 0xF0` / `& 0x0F` later on.
                break;

            case EquippedWeaponId_Handgun:
            case EquippedWeaponId_Shotgun:
            case EquippedWeaponId_HyperBlaster:
                func_8003DD80(1, 35);
                break;

            case EquippedWeaponId_HuntingRifle:
                func_8003DD80(1, 36);
                break;

            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Multitap):
            case 31:
                break;
        }
    }
    else
    {
        func_8003DD80(1, 34);
    }
}

static inline void func_80071968_Switch1()
{
    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Tap): 
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_KitchenKnife, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_SteelPipe, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_RockDrill, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Hammer, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Chainsaw, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Katana, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Axe, AttackInputType_Multitap):
                func_8003DD80(1, 18);
                break;

            case EquippedWeaponId_Handgun:
            case EquippedWeaponId_Shotgun:
            case EquippedWeaponId_HyperBlaster:
                func_8003DD80(1, 19);
                break;

            case EquippedWeaponId_HuntingRifle:
                func_8003DD80(1, 20);
                break;

            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Tap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Hold):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk3, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk8, AttackInputType_Multitap):
            case WeaponId_AttackVariantGet(EquippedWeaponId_Unk9, AttackInputType_Multitap):
            case 31:
                break;
        }
    }
    else
    {
        func_8003DD80(1, (g_SysWork.field_2358 != 0) ? 18 : 17);
    }
}

void func_80071968(s_SubCharacter* chara, s_MainCharacterExtra* extra, void* arg2, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
        case PlayerState_Unk61:
        case PlayerState_Unk62:
        case PlayerState_Unk63:
        case PlayerState_Unk64:
        case PlayerState_Unk65:
        case PlayerState_Unk66:
        case PlayerState_Unk67:
        case PlayerState_Unk68:
        case PlayerState_Unk69:
        case PlayerState_Unk76:
        case PlayerState_Unk77:
        case PlayerState_Unk78:
        case PlayerState_Unk79:
        case PlayerState_Unk80:
        case PlayerState_Unk83:
        case PlayerState_Unk84:
        case PlayerState_Unk85:
        case PlayerState_Unk86:
        case PlayerState_Unk87:
        case PlayerState_Unk88:
        case PlayerState_Unk93:
        case PlayerState_Unk94:
        case PlayerState_Unk95:
        case PlayerState_Unk97:
        case PlayerState_Unk98:
        case PlayerState_Unk99:
        case PlayerState_Unk100:
        case PlayerState_Unk102:
        case PlayerState_Unk103:
        case PlayerState_Unk104:
        case PlayerState_Unk105: // Moving an object. (Hospital Basement Otherworld and Motel)
        case PlayerState_Unk107:
        case PlayerState_Unk108:
        case PlayerState_Unk111:
        case PlayerState_Unk112:
        case PlayerState_Unk118:
        case PlayerState_Unk119:
        case PlayerState_Unk122:
        case PlayerState_Unk134:
        case PlayerState_Unk136:
        case PlayerState_Unk137:
        case PlayerState_Unk138:
        case PlayerState_Unk139:
        case PlayerState_Unk141: // Throwing the disinfective alcohol scene. (Hospital Basement Otherworld)
        case PlayerState_Unk142:
        case PlayerState_Unk143:
        case PlayerState_Unk144:
        case PlayerState_Unk145:
        case PlayerState_Unk146:
        case PlayerState_Unk147:
        case PlayerState_Unk148:
        case PlayerState_Unk152:
        case PlayerState_Unk162:
            break;

        case PlayerState_Unk54:
            func_80071968_Switch0();
            break;

        case PlayerState_None: 
            switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
            {
                case PlayerUpperBodyState_RunForward:
                case PlayerUpperBodyState_RunRight:
                case PlayerUpperBodyState_RunLeft:
                    func_80071968_Switch0();
                    break;
                
                default:
                    func_80071968_Switch1();
                    break;
            }
            break;

        default:  
        case PlayerState_Combat: 
        case PlayerState_Idle: 
        case PlayerState_FallForward: 
        case PlayerState_FallBackward: 
        case PlayerState_KickEnemy: 
        case PlayerState_StompEnemy: 
        case PlayerState_Unk7: 
        case PlayerState_Death: 
        case PlayerState_InstantDeath: 
        case PlayerState_EnemyGrabTorsoFront: 
        case PlayerState_Unk11: 
        case PlayerState_Unk12: 
        case PlayerState_EnemyGrabTorsoBack: 
        case PlayerState_EnemyGrabLegsFront: 
        case PlayerState_EnemyGrabLegsBack: 
        case PlayerState_EnemyReleaseUpperFront:
        case PlayerState_Unk17:
        case PlayerState_Unk18:
        case PlayerState_DamageHead:
        case PlayerState_EnemyReleaseUpperBack:
        case PlayerState_EnemyReleaseLowerFront:
        case PlayerState_EnemyReleaseLowerBack:
        case PlayerState_DamageTorsoBack:
        case PlayerState_DamageTorsoFront:
        case PlayerState_DamageTorsoRight:
        case PlayerState_DamageTorsoLeft:
        case PlayerState_DamageFeetFront:
        case PlayerState_DamageFeetBack:
        case PlayerState_DamagePushBack:
        case PlayerState_DamagePushFront:
        case PlayerState_Unk31:
        case PlayerState_EnemyGrabNeckFront:
        case PlayerState_EnemyGrabNeckBack:
        case PlayerState_Unk34:
        case PlayerState_Unk35:
        case PlayerState_Unk36:
        case PlayerState_EnemyGrabPinnedFrontStart:
        case PlayerState_EnemyGrabPinnedBackStart:
        case PlayerState_EnemyGrabPinnedFront:
        case PlayerState_EnemyGrabPinnedBack:
        case PlayerState_EnemyReleasePinnedFront:
        case PlayerState_EnemyReleasePinnedBack:
        case PlayerState_Unk43:
        case PlayerState_Unk44:
        case PlayerState_DamageThrownFront:
        case PlayerState_DamageThrownBack:
        case PlayerState_OnFloorFront:
        case PlayerState_OnFloorBehind:
        case PlayerState_GetUpFront:
        case PlayerState_GetUpBack:
        case PlayerState_Unk51:
        case PlayerState_Unk52:
        case PlayerState_Unk53:
        case PlayerState_Unk55:
        case PlayerState_Unk56:
        case PlayerState_Unk57:
        case PlayerState_Unk58:
        case PlayerState_Unk59: // Interacting with vines. (Hospital Basement Otherworld)
        case PlayerState_Unk60: // Interacting with vines without disinfective alcohol applied. (Hospital Basement Otherworld)
        case PlayerState_Unk70:
        case PlayerState_Unk71:
        case PlayerState_Unk72:
        case PlayerState_Unk73:
        case PlayerState_Unk74:
        case PlayerState_Unk75:
        case PlayerState_Unk81: // Burning vines scene. (Hospital Basement Otherworld)
        case PlayerState_Unk82:
        case PlayerState_Unk89:
        case PlayerState_Unk90:
        case PlayerState_Unk91:
        case PlayerState_Unk92:
        case PlayerState_Unk96:
        case PlayerState_Unk101:
        case PlayerState_Unk106:
        case PlayerState_Unk109:
        case PlayerState_Unk110:
        case PlayerState_Unk113:
        case PlayerState_Unk114:
        case PlayerState_Unk115:
        case PlayerState_Unk116:
        case PlayerState_Unk117:
        case PlayerState_Unk120:
        case PlayerState_Unk121:
        case PlayerState_Unk123:
        case PlayerState_Unk124:
        case PlayerState_Unk125:
        case PlayerState_Unk126:
        case PlayerState_Unk127:
        case PlayerState_Unk128:
        case PlayerState_Unk129:
        case PlayerState_Unk130:
        case PlayerState_Unk131:
        case PlayerState_Unk132:
        case PlayerState_Unk133:
        case PlayerState_Unk135:
        case PlayerState_Unk140:
        case PlayerState_Unk149:
        case PlayerState_Unk150:
        case PlayerState_Unk151:
        case PlayerState_Unk153:
        case PlayerState_Unk154:
        case PlayerState_Unk155:
        case PlayerState_Unk156:
        case PlayerState_Unk157:
        case PlayerState_Unk158:
        case PlayerState_Unk159:
        case PlayerState_Unk160:
        case PlayerState_Unk161:
            func_80071968_Switch1();
            break;
    }

    if (!g_Player_IsInWalkToRunTransition)
    {
        g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(0.5f, Q12_SHIFT) - 1;
        animInfo                               = &g_MaybePlayerAnims[chara->model_0.anim_4.status_0];
        animInfo->funcPtr_0(&chara->model_0, (s32)arg2, coord, animInfo);

        g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(63.5f, Q12_SHIFT);
        animInfo                               = &g_MaybePlayerAnims[extra->model_0.anim_4.status_0];
        animInfo->funcPtr_0(&extra->model_0, (s32)arg2, coord, animInfo);
        return;
    }

    g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(0.5f, Q12_SHIFT) - 1;
    chara->model_0.anim_4.status_0        = ANIM_STATUS(PlayerAnim_Unk0, false);
    animInfo                               = &g_MaybePlayerAnims[0];
    animInfo->funcPtr_0(chara, (s32)arg2, coord, animInfo);

    g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(63.5f, Q12_SHIFT);
    animInfo                               = &g_MaybePlayerAnims[extra->model_0.anim_4.status_0];
    animInfo->funcPtr_0(&extra->model_0, (s32)arg2, coord, animInfo);

    if (chara->model_0.anim_4.status_0 == g_MaybePlayerAnims[0].status_6)
    {
        g_Player_IsInWalkToRunTransition = false;
    }
}

void Player_LogicUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    SVECTOR       playerAngles;
    s16           headingAngle0;
    s16           headingAngle1;
    s16           sp1C;
    s16           sp1E;
    s32           temp_a2;
    s_Model**     new_var;
    s32           temp_s0;
    s16           temp_v0;
    s32           var_v1_5;
    s32           temp_s0_3;
    s32           temp_v1_10;
    s32           temp_v1_11;
    s32           temp_v1_12;
    s32           temp_v1_13;
    e_PlayerState thrownState;
    s32           playeGrabFree_RequiredInputCount;
    e_PlayerState romperAttackState;
    e_PlayerState enemyGrabReleaseState;
    s32           var_s6;
    s16           var_s7;
    s32           npcIdx;
    s32           animStatus;
    s_Model*      model;
    s32           temp;

    animStatus = ANIM_STATUS(PlayerAnim_Unk0, false);
    
    Game_TimerUpdate();
    
    D_800C4550                              = 0;
    D_800C454C                              = 0;
    chara->properties_E4.player.field_10C >>= 1;
    
    if (chara->flags_3E & (1 << 3))
    {
        chara->properties_E4.larvalStalker.properties_E8[10].val32 += g_DeltaTime0;
    }
    
    if (chara->properties_E4.larvalStalker.properties_E8[10].val32 > D_800C45EC)
    {
        chara->properties_E4.larvalStalker.properties_E8[10].val32 = 0;
        chara->flags_3E &= ~(1 << 3);
    }
    
    if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 -= g_DeltaTime0;
    }
    
    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114, FP_FLOAT_TO(0.0f, Q12_SHIFT), FP_FLOAT_TO(60.0f, Q12_SHIFT));
    
    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw || g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
    {
        func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != 0) ? 4 : 2);
    }
    
    g_SavegamePtr->healthSaturation_238 -= g_DeltaTime0;
    
    g_SavegamePtr->healthSaturation_238 = CLAMP(g_SavegamePtr->healthSaturation_238, FP_HEALTH(0.0f), FP_HEALTH(300.0f));
    
    if (g_SavegamePtr->healthSaturation_238 != FP_HEALTH(0.0f))
    {
        g_SysWork.player_4C.chara_0.health_B0 += g_DeltaTime0;
        g_SysWork.player_4C.chara_0.health_B0  = CLAMP(g_SysWork.player_4C.chara_0.health_B0, FP_HEALTH(0.0f), FP_HEALTH(100.0f));
    }
    
    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S00)
    {
        g_MapOverlayHeader.func_108();
    }
    
    if (g_DeltaTime0 != FP_TIME(0.0f))
    if (g_DeltaTime0 != FP_TIME(0.0f))
    {
        Player_Controller();
    }
    
    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
        case PlayerState_Idle:
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
            func_8005545C(&playerAngles);
            g_SysWork.player_4C.chara_0.properties_E4.player.field_120 = playerAngles.vy;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk17, false);
                extra->model_0.stateStep_3++;
            }
            
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk17, false);
                chara->model_0.stateStep_3++;
            }
            
			// If player is not performing a movement.
            if (!(g_Player_MovementInputDetected | g_Player_ActionRunPressed))
            {
                break;
            }
            
            g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
            chara->model_0.stateStep_3                      = 0;
            chara->model_0.state_2                          = 0;
            extra->model_0.stateStep_3                      = 0;
            extra->model_0.state_2                          = 0;
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;

        case PlayerState_None:
        case PlayerState_Combat:
            Player_LowerBodyUpdate(chara, extra);
                
            if (g_SysWork.player_4C.extra_128.state_1C < (u32)PlayerState_Idle)
            {
                Player_UpperBodyUpdate(chara, extra);
            }
            break;
            
        case PlayerState_Unk7:
            func_8007FB94(chara, extra, 200);
            
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 << 11) / 136);
                
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (!(chara->attackReceived_41 >= 68 && chara->attackReceived_41 < 70))
            {
                g_Player_HeadingAngle                                                   = ratan2(chara->field_B4, chara->field_BC) - chara->rotation_24.vy;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = SQUARE(chara->field_B4) + SQUARE(chara->field_BC) + SQUARE(chara->field_B8);
            }
            
            if (extra->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                chara->attackReceived_41                                                = NO_VALUE;
                g_SysWork.enemyTargetIdx_2353                                           = NO_VALUE;
                g_SysWork.player_4C.extra_128.state_1C                                  = PlayerState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C             &= ~PlayerFlag_DamageReceived;
                chara->model_0.stateStep_3                                              = 0;
                chara->model_0.state_2                                                  = 0;
                extra->model_0.stateStep_3                                              = 0;
                extra->model_0.state_2                                                  = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20                         = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24                         = PlayerLowerBodyState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            }
            
            D_800C4550               = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            chara->flags_3E         |= 1 << 3;
            chara->attackReceived_41 = NO_VALUE;
            break;
        
        case PlayerState_DamageThrownFront:
        case PlayerState_DamageThrownBack:
            thrownState = PlayerState_None;
            
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_DamageThrownFront:
                    animStatus  = ANIM_STATUS(PlayerAnim_Unk131, true);
                    thrownState = PlayerState_OnFloorFront;
                    break;
                    
                case PlayerState_DamageThrownBack:
                    animStatus  = ANIM_STATUS(PlayerAnim_Unk132, false);
                    thrownState = PlayerState_OnFloorBehind;
                    break;
            }
            
            func_8007FB94(chara, extra, animStatus);
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                g_SysWork.player_4C.extra_128.state_1C          = thrownState;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                chara->properties_E4.player.afkTimer_E8         = FP_TIME(10.0f);
            }
            
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 << 11) / 136) >> 3;
                
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126) < 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }
            
            D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            
            break;
        
        case PlayerState_EnemyGrabPinnedFrontStart:
        case PlayerState_EnemyGrabPinnedBackStart:
            romperAttackState = PlayerState_None;
            npcIdx            = 0;
            
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabPinnedFrontStart:
                    animStatus        = ANIM_STATUS(PlayerAnim_Unk127, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedFront;
                    npcIdx            = g_SysWork.field_2354[0];
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + FP_ANGLE(180.0f)), &headingAngle0);
                    break;
                    
                case PlayerState_EnemyGrabPinnedBackStart:
                    animStatus        = ANIM_STATUS(PlayerAnim_Unk128, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedBack;
                    npcIdx            = g_SysWork.field_2354[1];
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + FP_ANGLE(360.0f)), &headingAngle0);
                    break;
            }
            
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
            func_8007FB94(chara, extra, animStatus);
            chara->field_D4 = 0x400;
            chara->field_D6 = 0;
            
            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                temp_s0 = -D_800AF1FC[chara->model_0.anim_4.keyframeIdx0_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4];
                g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_4 = FP_MULTIPLY(temp_s0, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
                g_SysWork.player_4C.chara_0.field_D8.field_6 = FP_MULTIPLY(temp_s0, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
            }
            
            if (ABS(headingAngle0) < FP_ANGLE(11.25f))
            {
                if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedFrontStart)
                {
                    chara->rotation_24.vy = g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + FP_ANGLE(180.0f);
                }
                else
                {
                    chara->rotation_24.vy = g_SysWork.npcs_1A0[npcIdx].rotation_24.vy;
                }
            }
            else
            {
                if (headingAngle0 > FP_ANGLE(0.0f))
                {
                    chara->rotation_24.vy += FP_ANGLE(11.25f);
                }
                else
                {
                    chara->rotation_24.vy -= FP_ANGLE(11.25f);
                }
            }

            Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + FP_ANGLE(360.0f)), &headingAngle0);
            
            model = &g_SysWork.npcs_1A0[npcIdx].model_0;
            
            do { } while(false); // @hack Required for match.
            
            g_Player_HeadingAngle =
            temp                  = headingAngle0;

            if ((*new_var) != NULL) // @hack Required for match.
            {
                g_Player_HeadingAngle += FP_ANGLE(0.0f);
            }
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                g_SysWork.player_4C.extra_128.state_1C          = romperAttackState;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                chara->properties_E4.player.afkTimer_E8         = FP_TIME(15.0f);
            }

            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if (g_SysWork.player_4C.extra_128.state_1C >= PlayerState_EnemyGrabPinnedFrontStart &&
				    g_SysWork.player_4C.extra_128.state_1C < PlayerState_EnemyGrabPinnedFront)
                {
                    temp = -0x8000;
                    extra->model_0.anim_4.time_4 = (FP_TO(g_MapOverlayHeader.animInfos_34[chara->model_0.anim_4.status_0 - 76].keyframeIdx0_C, Q12_SHIFT) + model->anim_4.time_4) + temp;
                    chara->model_0.anim_4.time_4 = (FP_TO(g_MapOverlayHeader.animInfos_34[chara->model_0.anim_4.status_0 - 76].keyframeIdx0_C, Q12_SHIFT) + model->anim_4.time_4) + temp;
                    chara->model_0.anim_4.keyframeIdx0_8 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                    extra->model_0.anim_4.keyframeIdx0_8 = FP_FROM(extra->model_0.anim_4.time_4, Q12_SHIFT);
                }
            }
            

            if (ABS(chara->position_18.vx - D_800C4610) < 0xCD)
            {
                chara->position_18.vx = D_800C4610;
            }
            else
            {
                if (chara->position_18.vx >= D_800C4610)
                {
                    chara->position_18.vx -= 0xCD;
                }
                else
                {
                    chara->position_18.vx += 0xCD;
                }
            }
            
            if (ABS(chara->position_18.vz - D_800C4618) < 0xCD)
            {
                chara->position_18.vz = D_800C4618;
            }
            else
            {
                if (chara->position_18.vz < D_800C4618)
                {
                    chara->position_18.vz += 0xCD;
                }
                else
                {
                    chara->position_18.vz -= 0xCD;
                }
            }
            
            break;
        
        case PlayerState_EnemyGrabTorsoFront:
        case PlayerState_EnemyGrabTorsoBack:
        case PlayerState_EnemyGrabLegsFront:
        case PlayerState_EnemyGrabLegsBack:
        case PlayerState_EnemyGrabNeckFront:
        case PlayerState_EnemyGrabNeckBack:
        case PlayerState_EnemyGrabPinnedFront:
        case PlayerState_EnemyGrabPinnedBack:
        case PlayerState_OnFloorFront:
        case PlayerState_OnFloorBehind:
            playeGrabFree_RequiredInputCount                                        = 0;
            enemyGrabReleaseState                                                     = PlayerState_None;
            var_s6                                                                  = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
            var_s7                                                                  = 0;
            
			// Accommodates player position (for pinned enemy gram and Romper attack) and establishes required input count to get free.
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_OnFloorFront:
                case PlayerState_OnFloorBehind:
                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 1600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 4800;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 3200;
                    }
                    
                    switch (g_SysWork.player_4C.extra_128.state_1C)
                    {
                        case PlayerState_OnFloorFront:
                            animStatus            = ANIM_STATUS(PlayerAnim_Unk132, true);
                            enemyGrabReleaseState = PlayerState_GetUpFront;
                            break;
                        
                        case PlayerState_OnFloorBehind:
                            animStatus            = ANIM_STATUS(PlayerAnim_Unk133, false);
                            enemyGrabReleaseState = PlayerState_GetUpBack;
                            break;
                    }
                    
                    chara->field_D6 += FP_MULTIPLY((s64)g_DeltaTime0, (s64)FP_FLOAT_TO(0.27f, Q12_SHIFT), Q12_SHIFT);
                    chara->field_C8 += FP_MULTIPLY((s64)g_DeltaTime0, (s64)FP_FLOAT_TO(1.2f, Q12_SHIFT), Q12_SHIFT);
                    chara->field_CE += FP_MULTIPLY((s64)g_DeltaTime0, (s64)FP_FLOAT_TO(0.9f, Q12_SHIFT), Q12_SHIFT);
                    
                    chara->field_D6 = CLAMP(chara->field_D6, 0x3AE, 0x800);
                    chara->field_C8 = CLAMP(chara->field_C8, -0x1999, -0x666);
                    chara->field_CE = CLAMP(chara->field_CE, -0x1199, -0x333);
                    
                    if (chara->health_B0 <= FP_HEALTH(0.0f) && chara->properties_E4.player.afkTimer_E8 <= FP_TIME(0.0f))
                    {
                        g_MapOverlayHeader.func_DC();
                        //SysWork_StateSetNext(GameState_ExitMovie); // TODO: Doesn't match.
                        g_SysWork.sysState_8        = GameState_ExitMovie;
                        g_SysWork.timer_24          = 0;
                        g_SysWork.sysStateStep_C[0] = 0;
                        g_SysWork.field_28          = 0;
                        g_SysWork.sysStateStep_C[1] = 0;
                        g_SysWork.timer_2C          = 0;
                        g_SysWork.sysStateStep_C[2] = 0;

                        chara->health_B0                                                         = FP_HEALTH(100.0f);
                        g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(0.0f);
                        return;
                    }
                    break;

                case PlayerState_EnemyGrabPinnedFront:
                case PlayerState_EnemyGrabPinnedBack:
                    var_s6 = 0xA66;
                    
                    switch (g_SysWork.player_4C.extra_128.state_1C)
                    {
                        case PlayerState_EnemyGrabPinnedFront:
                            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                            {
                                playeGrabFree_RequiredInputCount = 800;
                            }
                            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                            {
                                playeGrabFree_RequiredInputCount = 2400;
                            }
                            else
                            {
                                playeGrabFree_RequiredInputCount = 1600;
                            }
                            
                            animStatus          = ANIM_STATUS(PlayerAnim_Unk128, false);
                            enemyGrabReleaseState = PlayerState_EnemyReleasePinnedFront;
                            break;
                        
                        case PlayerState_EnemyGrabPinnedBack:
                            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                            {
                                playeGrabFree_RequiredInputCount = 1200;
                            }
                            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                            {
                                playeGrabFree_RequiredInputCount = 3600;
                            }
                            else
                            {
                                playeGrabFree_RequiredInputCount = 2400;
                            }
                            
                            animStatus          = ANIM_STATUS(PlayerAnim_Unk129, false);
                            enemyGrabReleaseState = PlayerState_EnemyReleasePinnedBack;
                            break;
                    }
                    
                    chara->field_D4                              = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
                    
                    if (ABS(chara->position_18.vx - D_800C4610) < 0xCD)
                    {
                        chara->position_18.vx = D_800C4610;
                    }
                    else
                    {
                        if (chara->position_18.vx >= D_800C4610)
                        {
                            chara->position_18.vx -= 0xCD;
                        }
                        else
                        {
                            chara->position_18.vx += 0xCD;
                        }
                    }
                    
                    if (ABS(chara->position_18.vz - D_800C4618) < 0xCD)
                    {
                        chara->position_18.vz = D_800C4618;
                    }
                    else
                    {
                        if (chara->position_18.vz >= D_800C4618)
                        {
                            chara->position_18.vz -= 0xCD;
                        }
                        else
                        {
                            chara->position_18.vz += 0xCD;
                        }
                    }
                    
                    if (chara->health_B0 <= FP_FLOAT_TO(0.0f, Q12_SHIFT) && chara->properties_E4.player.afkTimer_E8 <= FP_TIME(0.0f))
                    {
                        g_MapOverlayHeader.func_DC();

                        //SysWork_StateSetNext(GameState_ExitMovie); // TODO: Doesn't match.
                        g_SysWork.sysState_8        = GameState_ExitMovie;
                        g_SysWork.timer_24          = 0;
                        g_SysWork.sysStateStep_C[0] = 0;
                        g_SysWork.field_28          = 0;
                        g_SysWork.sysStateStep_C[1] = 0;
                        g_SysWork.timer_2C          = 0;
                        g_SysWork.sysStateStep_C[2] = 0;

                        chara->health_B0                                                         = FP_HEALTH(100.0f);
                        g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(0.0f);
                        return;
                    }
                    break;
                
                case PlayerState_EnemyGrabTorsoFront:
                    var_s6 = 0x1000;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 800;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 2400;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 1600;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk115, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperFront;
                    break;
                
                default:
                    break;
                
                case PlayerState_EnemyGrabTorsoBack:
                    var_s6 = 0x1000;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 1000;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 3000;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 2000;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk117, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;
                
                case PlayerState_EnemyGrabLegsFront:
                    var_s6 = 0xCCC;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 700;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 2100;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 1400;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk117, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerFront;
                    break;
                
                case PlayerState_EnemyGrabLegsBack:
                    var_s6 = 0xCCC;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 800;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 2400;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 1600;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk118, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerBack;
                    break;
                
                case PlayerState_EnemyGrabNeckFront:
                    var_s6 = 0x1800;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 3600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 10800;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 7200;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperFront;
                    break;
                
                case PlayerState_EnemyGrabNeckBack:
                    var_s6 = 0x1800;

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        playeGrabFree_RequiredInputCount = 3600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        playeGrabFree_RequiredInputCount = 10800;
                    }
                    else
                    {
                        playeGrabFree_RequiredInputCount = 7200;
                    }
                    
                    animStatus            = ANIM_STATUS(PlayerAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;
            }
            
			// Accommodates position of player and enemy?
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabTorsoFront:
                case PlayerState_EnemyGrabLegsFront:
                case PlayerState_EnemyGrabNeckFront:
                case PlayerState_EnemyGrabPinnedFront:
                    temp_v1_10 = chara->position_18.vx - g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].position_18.vx;
                    temp_v1_11 = chara->position_18.vz - g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].position_18.vz;
                    var_s7     = SquareRoot0(SQUARE(temp_v1_10) + SQUARE(temp_v1_11));
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].rotation_24.vy + FP_ANGLE(180.0f)), &headingAngle1);
                            
                    if (ABS(headingAngle1) < FP_ANGLE(11.25f))
                    {
                        chara->rotation_24.vy = g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].rotation_24.vy + FP_ANGLE(180.0f);
                    }
                    else
                    {
                        if (headingAngle1 > FP_ANGLE(0.0f))
                        {
                            chara->rotation_24.vy += FP_ANGLE(11.25f);
                        }
                        else
                        {
                            chara->rotation_24.vy -= FP_ANGLE(11.25f);
                        }
                    }
                    break;
                        
                case PlayerState_EnemyGrabTorsoBack:
                case PlayerState_EnemyGrabLegsBack:
                case PlayerState_EnemyGrabNeckBack:
                case PlayerState_EnemyGrabPinnedBack:
                    temp_v1_12 = chara->position_18.vx - g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].position_18.vx;
                    temp_v1_13 = chara->position_18.vz - g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].position_18.vz;
                    var_s7     = SquareRoot0(SQUARE(temp_v1_12) + SQUARE(temp_v1_13));
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].rotation_24.vy + FP_ANGLE(360.0f)), &headingAngle1);

                    if (ABS(headingAngle1) < FP_ANGLE(11.25f))
                    {
                        chara->rotation_24.vy = g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].rotation_24.vy;
                    }
                    else
                    {
                        if (headingAngle1 > FP_ANGLE(0.0f))
                        {
                            chara->rotation_24.vy += FP_ANGLE(11.25f);
                        }
                        else
                        {
                            chara->rotation_24.vy -= FP_ANGLE(11.25f);
                        }
                    }
                    break;
            }
                    
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabPinnedFront:
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].rotation_24.vy + FP_ANGLE(360.0f)), &headingAngle1);
                        
                case PlayerState_EnemyGrabPinnedBack:
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].rotation_24.vy + FP_ANGLE(360.0f)), &headingAngle1);
                    break;
            }
                    
            g_Player_HeadingAngle = headingAngle1;
            func_8007FB94(chara, extra, animStatus);
                    
            if (chara->health_B0 > FP_HEALTH(0.0f) && (g_Player_MovementInputDetected | g_Player_ActionRunPressed))
            {
                g_Player_GrabFree_InputCount += g_DeltaTime0;
            }

			// If player isn't thrown on the floor (Cybil shoot attack).
            if (!(g_SysWork.player_4C.extra_128.state_1C >= PlayerState_OnFloorFront &&
			     g_SysWork.player_4C.extra_128.state_1C < PlayerState_GetUpFront))
            {
                if (var_s6 < var_s7)
                {
                    g_Player_GrabFree_InputCount = playeGrabFree_RequiredInputCount;
                    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedFront)
                    {
                        g_SysWork.npcs_1A0[g_SysWork.field_2354[0]].moveSpeed_38 = 0;
                    }
                            
                    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedBack)
                    {
                        g_SysWork.npcs_1A0[g_SysWork.field_2354[1]].moveSpeed_38 = 0;
                    }
                }
            }
                    
            if (g_Player_GrabFree_InputCount >= playeGrabFree_RequiredInputCount)
            {
                func_8007FD4C(0);
                        
                g_SysWork.player_4C.extra_128.state_1C          = enemyGrabReleaseState;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                chara->flags_3E                                |= 1 << 3;
            }
            break;
        
        case PlayerState_FallForward: 
        case PlayerState_FallBackward: 
        case PlayerState_EnemyReleaseUpperFront:
        case PlayerState_Unk17:
        case PlayerState_Unk18:
        case PlayerState_DamageHead:
        case PlayerState_EnemyReleaseUpperBack:
        case PlayerState_EnemyReleaseLowerFront:
        case PlayerState_EnemyReleaseLowerBack:
        case PlayerState_EnemyReleasePinnedFront:
        case PlayerState_EnemyReleasePinnedBack:
        case PlayerState_GetUpFront:
        case PlayerState_GetUpBack:
            if (g_SysWork.player_4C.extra_128.state_1C != PlayerState_FallBackward)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f)) >> 1;
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16 & 1)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                    }
                }
                
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f)) >> 2;

                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16 & 1)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }
            
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_GetUpFront:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk133, true);
                    break;
                    
                case PlayerState_GetUpBack:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk134, false);
                    break;
                    
                case PlayerState_EnemyReleasePinnedFront:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk129, true);
                    break;
                    
                case PlayerState_EnemyReleasePinnedBack:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk130, false);
                    break;
                    
                case PlayerState_EnemyReleaseUpperFront:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk120, false);
                    break;
                    
                case PlayerState_EnemyReleaseUpperBack:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk122, false);
                    break;
                    
                case PlayerState_Unk17:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk120, true);
                    break;
                    
                case PlayerState_Unk18:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk121, true);
                    break;
                    
                case PlayerState_EnemyReleaseLowerFront:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk122, true);
                    break;
                    
                case PlayerState_EnemyReleaseLowerBack:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk123, false);
                    break;
                    
                case PlayerState_DamageHead:
                    animStatus = ANIM_STATUS(PlayerAnim_Unk121, false);
                    break;
                    
                case PlayerState_FallForward: 
                    animStatus = ANIM_STATUS(PlayerAnim_FallForward, false);
                    break;
                    
                case PlayerState_FallBackward: 
                    animStatus = ANIM_STATUS(PlayerAnim_FallBackward, false);
                    break;
            }

            if (!(g_SysWork.player_4C.extra_128.state_1C >= PlayerState_FallForward && g_SysWork.player_4C.extra_128.state_1C < PlayerState_KickEnemy))
            {
                func_8007FB94(chara, extra, animStatus);
            }
            
            D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            chara->flags_3E |= 1 << 3;
            
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_GetUpFront:
                case PlayerState_GetUpBack:
                    chara->damageReceived_C0                = FP_HEALTH(0.0f);
                    chara->properties_E4.player.afkTimer_E8 = FP_TIME(0.0f);
					
                    if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
                    {
                        g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
                        chara->model_0.stateStep_3                                  = 0;
                        chara->model_0.state_2                                      = 0;
                        extra->model_0.stateStep_3                                  = 0;
                        extra->model_0.state_2                                      = 0;
                        g_SysWork.player_4C.chara_0.field_D4                        = 0x4CC;
                        g_SysWork.player_4C.chara_0.field_D6                        = 0x3AE;
                        g_SysWork.player_4C.chara_0.field_C8                        = -0x1999;
                        g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_None;
                        g_SysWork.player_4C.chara_0.field_D8.field_6                = 0; 
                        g_SysWork.player_4C.chara_0.field_D8.field_4                = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_2                = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_0                = 0;
                        g_SysWork.player_4C.chara_0.field_CA                        = 0;
                        g_SysWork.player_4C.chara_0.field_CE                        = -0x1199;
                    }
                    
                    chara->attackReceived_41 = NO_VALUE;
                    
                default:
                    break;
                    
                case PlayerState_EnemyReleasePinnedFront:
                case PlayerState_EnemyReleasePinnedBack:
                    chara->properties_E4.player.afkTimer_E8      = FP_TIME(0.0f);
                    g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                    g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
                    
                    if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
                    {
                        chara->field_D4 = ((chara->model_0.anim_4.keyframeIdx0_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4) * 0x4CC) / 21;
                    }
                    else
                    {
                        chara->field_D4 = 0;
                    }
                    
                    if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
                        switch (g_SysWork.player_4C.extra_128.state_1C)
                        {
                            case PlayerState_EnemyReleasePinnedFront:
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk43;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;
                                
                            case PlayerState_EnemyReleasePinnedBack:
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk44;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;
                        }
                        
                        g_SysWork.player_4C.chara_0.field_D4         = 0x4CC;
                        g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
                        chara->attackReceived_41                     = NO_VALUE;
                    }
                    break;
                    
                case PlayerState_EnemyReleaseUpperFront:
                case PlayerState_Unk17:
                case PlayerState_Unk18:
                case PlayerState_DamageHead:
                case PlayerState_EnemyReleaseUpperBack:
                case PlayerState_EnemyReleaseLowerFront:
                case PlayerState_EnemyReleaseLowerBack:
                    if (chara->model_0.anim_4.keyframeIdx0_8 == (g_MapOverlayHeader.field_38[D_800AF220].time_4 + 4))
                    {
                        chara->attackReceived_41 = NO_VALUE;
                    }
                    
                    if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
                    {
                        g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
                        chara->model_0.stateStep_3                                  = 0;
                        chara->model_0.state_2                                      = 0;
                        extra->model_0.stateStep_3                                  = 0;
                        extra->model_0.state_2                                      = 0;
                        g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_None;
                        chara->field_D4                                             = 0x4CC;
                        g_SysWork.player_4C.chara_0.field_D8.field_6                = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_4                = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_2                = 0;
                        g_SysWork.player_4C.chara_0.field_D8.field_0                = 0;
                    }
                    break;
                    
                case PlayerState_FallForward:
                case PlayerState_FallBackward:
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = animStatus;
                        extra->model_0.stateStep_3++;
                    }
                    
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = animStatus;
                        chara->model_0.stateStep_3++;
                    }
                    
                    if (extra->model_0.state_2 == 0 && chara->position_18.vy >= chara->properties_E4.player.positionY_EC)
                    {
                        extra->model_0.state_2++;
                        func_8005DC1C(Sfx_Unk1317, &chara->position_18, FP_VOLUME(0.125f), 0);
                        chara->properties_E4.player.field_10C = 128;
                        func_80089470();
                    }
                    
                    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_FallForward)
                    {
                        chara->properties_E4.player.field_10D = 0;
                        if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
                        {
                            g_SysWork.player_4C.chara_0.field_C8 = D_800AEEDC[chara->model_0.anim_4.keyframeIdx0_8 - 379][0];
                            g_SysWork.player_4C.chara_0.field_CE = D_800AEEDC[chara->model_0.anim_4.keyframeIdx0_8 - 379][1];
                        }
                        
                        if (chara->model_0.anim_4.keyframeIdx0_8 == D_800AF506)
                        {
                            if (chara->position_18.vy > FP_METER(6.5f))
                            {
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Death;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                            
                            g_SysWork.player_4C.chara_0.field_C8 = -0x1999;
                            g_SysWork.player_4C.chara_0.field_CA = 0;
                            g_SysWork.player_4C.chara_0.field_CE = -0x1199;
                            chara->field_D4                      = 0x4CC;
                        }
                    }
                    else
                    {
                        chara->properties_E4.player.field_10D = 1;
                        
                        if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
                        {
                            g_SysWork.player_4C.chara_0.field_C8 = D_800AEF78[chara->model_0.anim_4.keyframeIdx0_8 - 0x1A2][0];
                            g_SysWork.player_4C.chara_0.field_CE = D_800AEF78[chara->model_0.anim_4.keyframeIdx0_8 - 0x1A2][1];
                        }
                        
                        if (chara->model_0.anim_4.keyframeIdx0_8 == D_800AF526)
                        {
                            if (chara->position_18.vy > FP_METER(6.5f))
                            {
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Death;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                                chara->model_0.stateStep_3                      = 0;
                                chara->model_0.state_2                          = 0;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }

                            g_SysWork.player_4C.chara_0.field_C8 = -0x1999;
                            g_SysWork.player_4C.chara_0.field_CA = 0;
                            g_SysWork.player_4C.chara_0.field_CE = -0x1199;
                            chara->field_D4                      = 0x4CC;
                        }
                    }
                    break;
            }
            
            chara->attackReceived_41 = NO_VALUE;
            break;
        
        case PlayerState_Unk43:
            func_8007FB94(chara, extra, 0x105);
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                chara->field_D6                                 = 0x3AE;
            }
            break;
        
        case PlayerState_Unk44:
            func_8007FB94(chara, extra, 0x106);
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                chara->field_D6                                 = 0x3AE;
            }
            break;
        
        case PlayerState_Unk36:
            chara->attackReceived_41 = NO_VALUE;
            func_8007FB94(chara, extra, 0xFC);
            
            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12) >= chara->model_0.anim_4.keyframeIdx0_8)
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 0xC, 0x526);
                }
                else
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 0x1E, 0x527);
                }
            }
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                g_MapOverlayHeader.func_DC();
                
                //SysWork_StateSetNext(GameState_ExitMovie); // TODO: Doesn't match.
                g_SysWork.sysState_8        = GameState_ExitMovie;
                g_SysWork.timer_24          = 0;
                g_SysWork.sysStateStep_C[0] = 0;
                g_SysWork.field_28          = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                
                func_8007E9C4();
                
                extra->model_0.state_2++;
                chara->health_B0 = FP_HEALTH(100.0f);
                chara->model_0.state_2++;
                g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(0.0f);
                return;
            }
            break;
        
        case PlayerState_Death: 
            chara->attackReceived_41 = NO_VALUE;
            func_8007FB94(chara, extra, 0xCA);
            chara->field_D6 = 0;
            
            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12) >= chara->model_0.anim_4.keyframeIdx0_8)
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 0xC, 0x526);
                }
                else
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 0x20, 0x527);
                }
                
                temp_a2 = D_800AF070[chara->model_0.anim_4.keyframeIdx0_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4];
                
                if (chara->model_0.anim_4.keyframeIdx0_8 != g_MapOverlayHeader.field_38[D_800AF220].field_6)
                {
                    var_v1_5 = D_800AF070[(chara->model_0.anim_4.keyframeIdx0_8 + 1) - g_MapOverlayHeader.field_38[D_800AF220].time_4];
                }
                else
                {
                    var_v1_5 = temp_a2;
                }
                
                temp_s0_3                                    = temp_a2 + FP_MULTIPLY(var_v1_5 - temp_a2, chara->model_0.anim_4.time_4 & 0xFFF, Q12_SHIFT);
                g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_4 = FP_MULTIPLY(temp_s0_3, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
                g_SysWork.player_4C.chara_0.field_D8.field_6 = FP_MULTIPLY(temp_s0_3, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
                chara->field_D4                              = 0x4CC;
            }
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
                {
                    g_MapOverlayHeader.func_DC();
                    g_SavegamePtr->eventFlags_168[0] |= 1 << 25;
                    
                    func_8007E9C4();
                    
                    extra->model_0.state_2++;
                    chara->health_B0 = FP_HEALTH(100.0f);
                    chara->model_0.state_2++;
                    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(0.0f);
                    return;
                }
                
                g_MapOverlayHeader.func_DC();
                
                //SysWork_StateSetNext(GameState_ExitMovie); // TODO: Doesn't match.
                g_SysWork.sysState_8        = GameState_ExitMovie;
                g_SysWork.timer_24          = 0;
                g_SysWork.sysStateStep_C[0] = 0;
                g_SysWork.field_28          = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                
                func_8007E9C4();
                
                extra->model_0.state_2++;
                chara->health_B0 = FP_HEALTH(100.0f);
                chara->model_0.state_2++;
                g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(0.0f);
                return;
            }
            break;
        
        case PlayerState_InstantDeath:
            if (extra->model_0.state_2 == 0)
            {
                Sd_EngineCmd(4731);
            }
            
            func_8007FB94(chara, extra, 0xCB);
            chara->field_D6 = 0;
            
            if (chara->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6 - 0x19)
            {
                g_MapOverlayHeader.func_DC();
                
                //SysWork_StateSetNext(GameState_ExitMovie); // TODO: Doesn't match.
                g_SysWork.sysState_8        = GameState_ExitMovie;
                g_SysWork.timer_24          = 0;
                g_SysWork.sysStateStep_C[0] = 0;
                g_SysWork.field_28          = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                
                func_8007E9C4();
                
                extra->model_0.state_2++;
                chara->health_B0 = FP_HEALTH(100.0f);
                chara->model_0.state_2++;
                return;
            }
            break;
        
        case PlayerState_DamageTorsoBack:
        case PlayerState_DamageTorsoFront:
        case PlayerState_DamageTorsoRight:
        case PlayerState_DamageTorsoLeft:
        case PlayerState_DamageFeetFront:
        case PlayerState_DamageFeetBack:
        case PlayerState_DamagePushBack:
        case PlayerState_DamagePushFront:
            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_DamageTorsoBack:
                    func_8007FB94(chara, extra, 0xD3);
                    break;
                    
                case PlayerState_DamageTorsoFront:
                    func_8007FB94(chara, extra, 0xD2);
                    break;
                    
                case PlayerState_DamageTorsoRight:
                    func_8007FB94(chara, extra, 0xD4);
                    break;
                    
                case PlayerState_DamageTorsoLeft:
                    func_8007FB94(chara, extra, 0xD5);
                    break;
                    
                case PlayerState_DamageFeetFront:
                    func_8007FB94(chara, extra, 0xD7);
                    break;
                    
                case PlayerState_DamageFeetBack:
                    func_8007FB94(chara, extra, 0xD6);
                    break;
                    
                case PlayerState_DamagePushBack:
                    func_8007FB94(chara, extra, 0xF7);
                    break;
                    
                case PlayerState_DamagePushFront:
                    func_8007FB94(chara, extra, 0xF8);
                    break;
            }

            switch (g_SysWork.player_4C.extra_128.state_1C)
            {
                case PlayerState_DamagePushBack:
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.player_4C.chara_0.properties_E4.larvalStalker.properties_E8[0xC].val16[0], &sp1C);
                    
                    if (ABS(sp1C) >= 0x400)
                    {
                        break;
                    }
                    
                    if (ABS(sp1C) < 0x40)
                    {
                        chara->rotation_24.vy = g_SysWork.player_4C.chara_0.properties_E4.player.field_118;
                    }
                    else
                    {
                        chara->rotation_24.vy += (sp1C / ABS(sp1C)) << 6;
                    }
                    break;
                
                case PlayerState_DamagePushFront:
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.player_4C.chara_0.properties_E4.larvalStalker.properties_E8[12].val16[0], &sp1E);
                    
                    if (ABS(sp1E) < 0x400)
                    {
                        break;
                    }
                        
                    if (ABS(sp1E) >= 0x7C0)
                    {
                        chara->rotation_24.vy = FP_ANGLE_NORM_U(g_SysWork.player_4C.chara_0.properties_E4.player.field_118 + FP_ANGLE(180.0f));
                    }
                    else
                    {
                        chara->rotation_24.vy -= (sp1E / ABS(sp1E)) << 6;
                    }
                    break;
            }
            
            
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 << 11) / 136) >> 2;
                
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & 1)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }

            if (!(chara->attackReceived_41 >= 68 && chara->attackReceived_41 < 70))
            {
                g_Player_HeadingAngle                                                   = ratan2(chara->field_B4, chara->field_BC) - chara->rotation_24.vy;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = SQUARE(chara->field_B4) + SQUARE(chara->field_BC) + SQUARE(chara->field_B8);
            }
            
            if (extra->model_0.anim_4.keyframeIdx0_8 == g_MapOverlayHeader.field_38[D_800AF220].field_6)
            {
                chara->attackReceived_41                                                = NO_VALUE;
                g_SysWork.enemyTargetIdx_2353                                           = NO_VALUE;
                g_SysWork.player_4C.extra_128.state_1C                                  = PlayerState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C             &= ~PlayerFlag_DamageReceived;
                chara->model_0.stateStep_3                                              = 0;
                chara->model_0.state_2                                                  = 0;
                extra->model_0.stateStep_3                                              = 0;
                extra->model_0.state_2                                                  = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20                         = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24                         = PlayerLowerBodyState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
            }
            
            D_800C4550       = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            chara->flags_3E |= 8;
            break;
        
        case PlayerState_KickEnemy:
            func_80070DF0(extra, chara, 8, 0x31);
            break;
        
        case PlayerState_StompEnemy:
            func_80070DF0(extra, chara, 9, 0x33);
            break;
    }

    temp_v0                    = FP_ANGLE_NORM_U(chara->rotation_24.vy + (D_800C454C >> 4) + FP_ANGLE(360.0f));
    chara->rotation_24.vy      = temp_v0;
    chara->headingAngle_3C     = FP_ANGLE_NORM_U((temp_v0 + g_Player_HeadingAngle) + FP_ANGLE(360.0f));
    chara->moveSpeed_38        = D_800C4550;
    chara->field_34           += g_DeltaTime2;
    chara->rotationSpeed_2C.vy = (D_800C454C << 8) / g_DeltaTime0;
    coord->flg                 = false;
                
    func_80096E78(&chara->rotation_24, &coord->coord);
}

void Player_UpperBodyStateUpdate(s_MainCharacterExtra* extra, e_PlayerUpperBodyState upperState, s32 unused, s32 arg3) // 0x80073FC0
{
    e_PlayerUpperBodyState prevState;
    s_Model*         charaModel;

    prevState  = g_SysWork.player_4C.extra_128.upperBodyState_20;
    charaModel = &g_SysWork.player_4C.chara_0.model_0;

    switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_WalkForward:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_WalkForward;

        default:
            break;

        case PlayerLowerBodyState_RunForward:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunForward;
            break;

        case PlayerLowerBodyState_WalkBackward:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_WalkBackward;
            break;

        case PlayerLowerBodyState_SidestepRight:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepRight;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepLeft;
            break;

        case PlayerLowerBodyState_RunRight:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRight;
            break;

        case PlayerLowerBodyState_RunLeft:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeft;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_QuickTurnRight;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_QuickTurnLeft;
            break;

        case PlayerLowerBodyState_JumpBackward:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunWallStop;
            break;

        case PlayerLowerBodyState_Stumble:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_LowerBodyStumble;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeftWallStop;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRightWallStop;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeftStumble;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepRightStumble;
            break;

        case PlayerLowerBodyState_None:
            switch (arg3)
            {
                case 0:
                case 2:
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    break;

                case 1:
                    if (!g_Player_IsTurningRight)
                    {
                        if (g_Player_IsTurningLeft)
                        {
                            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnLeft;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnRight;
                    }
                    break;

                case 3:
                    if (g_Player_IsTurningLeft)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnLeft;
                        break;
                    }

                    if (!g_Player_IsTurningRight)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    }
                    break;

                case 4:
                    if (g_Player_IsTurningRight)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnRight;
                        break;
                    }

                    if (!g_Player_IsTurningLeft)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    }
                    break;
            }
            break;
    }

    if (g_SysWork.player_4C.extra_128.upperBodyState_20 != upperState)
    {
        extra->model_0.stateStep_3 = 0;
        extra->model_0.state_2     = 0;
    }

    switch (prevState)
    {
        case PlayerUpperBodyState_WalkForward:
            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_RunForward)
            {
                break;
            }

            extra->model_0.anim_4.status_0      = charaModel->anim_4.status_0;
            extra->model_0.anim_4.keyframeIdx0_8 = charaModel->anim_4.keyframeIdx0_8;
            extra->model_0.anim_4.time_4         = charaModel->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;

        case PlayerUpperBodyState_RunForward:
            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_WalkForward)
            {
                break;
            }

            extra->model_0.anim_4.status_0      = charaModel->anim_4.status_0;
            extra->model_0.anim_4.keyframeIdx0_8 = charaModel->anim_4.keyframeIdx0_8;
            extra->model_0.anim_4.time_4         = charaModel->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;
    }
}

void Player_UpperBodyUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80074254
{
    s32 stumbleSfx;

    if (Player_UpperBodyMainUpdate(chara, extra))
    {
        return;
    }

    stumbleSfx = (D_800C45C8.field_1 == 10) ? Sfx_Stumble1 : Sfx_Stumble0;

    switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
            func_80071620(55, chara, 551, Sfx_HeavyBreath);
            break;

        case PlayerUpperBodyState_LowerBodyStumble:
            if (func_80071620(23, chara, 173, stumbleSfx))
            {
                func_8008944C();
            }
            break;

        case PlayerUpperBodyState_RunLeftStumble:
            if (func_80071620(39, chara, 340, stumbleSfx))
            {
                func_8008944C();
            }
            break;

        case PlayerUpperBodyState_SidestepRightStumble:
            if (func_80071620(43, chara, 369, stumbleSfx))
            {
                func_8008944C();
            }
            break;
    }

    Player_CombatStateUpdate(chara, extra);
}

bool Player_UpperBodyMainUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80075504
{
    s32 enemyAttackedIdx;
    s16 sp20;
    s16 sp22;
    s32 currentAmmoVar;
    s32 totalAmmoVar;
    s32 temp_s1_2;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s32 i;
    s16 var_s0;
    s32 playerTurn;

    bool Player_CombatAnimUpdate() // 0x80074350
    {
        s16 ssp20;
        s16 temp_a1;
        s32 keyframeIdx0;
        s32 keyframeIdx1;
        u8  equippedWeaponId;

        equippedWeaponId = g_SysWork.playerCombatInfo_38.equippedWeapon_F;

        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case EquippedWeaponId_KitchenKnife:
                keyframeIdx0 = 619;
                keyframeIdx1 = 613;
                break;

            case EquippedWeaponId_Chainsaw:
                keyframeIdx0 = 630;
                keyframeIdx1 = 624;
                break;

            case EquippedWeaponId_RockDrill:
                keyframeIdx0 = 568;
                keyframeIdx1 = 568;
                break;

            case EquippedWeaponId_Axe:
                keyframeIdx0 = 625;
                keyframeIdx1 = 618;
                break;

            case EquippedWeaponId_SteelPipe:
            case EquippedWeaponId_Hammer:
                keyframeIdx0 = 648;
                keyframeIdx1 = 642;
                break;

            case EquippedWeaponId_Katana:
                keyframeIdx0 = 619;
                keyframeIdx1 = 612;
                break;

            default:
                keyframeIdx1 = 0;
                keyframeIdx0 = 0;
                break;
        }

        if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat)
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.field_104 += g_DeltaTime0;

            if (g_GameWork.config_0.optExtraWeaponCtrl_23 == 0)
            {
                g_Player_ActionRunPressed      = false;
                g_Player_MovementInputDetected = false;
                g_Player_IsShooting            = false;
                g_Player_IsAttacking           = false;
                g_Player_IsHoldAttack          = false;
                g_Player_IsAiming              = false;
                g_Player_IsRunning             = false;
                g_Player_IsMovingBackward      = false;
                g_Player_IsMovingForward       = false;
                g_Player_IsSteppingRightTap    = false;
                g_Player_IsSteppingRightHold   = false;
                g_Player_IsTurningRight        = false;
                g_Player_IsSteppingLeftTap     = false;
                g_Player_IsSteppingLeftHold    = false;
                g_Player_IsTurningLeft         = false;
            }
        }

		// Attack type (except melee multitap) and animation.
        if (extra->model_0.state_2 == 0)
        {
            g_Player_MeleeAttackType  = 0;
            g_Player_IsMultiTapAttack = 0;

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                g_Player_MeleeAttackType    = 0;
                g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8;
                D_800AF220                  = g_Player_EquippedWeaponInfo.field_A >> 4;
            }
            else if (g_Player_IsAttacking && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                g_Player_MeleeAttackType = 1;
                g_Player_AttackAnimIdx   = g_Player_EquippedWeaponInfo.animAttackHold_8 - 4;
                D_800AF220               = (g_Player_EquippedWeaponInfo.field_A >> 4) - 2;
            }
            else
            {
                g_Player_MeleeAttackType = 0;
				
				// Handle Rock Drill animation.
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill || g_Player_RockDrill_DirectionAttack == 0)
                {
                    g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8;
                    D_800AF220                  = g_Player_EquippedWeaponInfo.field_A >> 4;
                }
                else if (g_Player_RockDrill_DirectionAttack == NO_VALUE)
                {
                    g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8 + 4;
                    D_800AF220                  = (g_Player_EquippedWeaponInfo.field_A >> 4) + 2;
                }
                else
                {
                    g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8 + 2;
                    D_800AF220                  = (g_Player_EquippedWeaponInfo.field_A >> 4) + 1;
                }
            }

            extra->model_0.state_2++;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                g_SysWork.playerCombatInfo_38.equippedWeapon_F %= 10;
            }

            g_SysWork.playerCombatInfo_38.equippedWeapon_F += g_Player_MeleeAttackType * 10;

            D_800C44D0 = g_MaybePlayerAnims[g_Player_AttackAnimIdx].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E;
            D_800C44D4 = g_MaybePlayerAnims[g_Player_AttackAnimIdx].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E +
                         D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_F;
        }

		// Used for make continuos/hold shooting smoother?
        if (g_SysWork.enemyTargetIdx_2353 != NO_VALUE && g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
        {
            if (!g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                    func_8005D50C(&D_800AF21C, &D_800C4554, &D_800C4556, &g_SysWork.playerCombatInfo_38, enemyAttackedIdx, 0xE3);
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                    func_8005D50C(&D_800AF21C, &D_800C4554, &D_800C4556, &g_SysWork.playerCombatInfo_38, enemyAttackedIdx, 0xE3);
                }
            }
            else
            {
                enemyAttackedIdx = g_SysWork.enemyTargetIdx_2353;
            }

            if (enemyAttackedIdx == NO_VALUE && enemyAttackedIdx == D_800AF21C)
            {
                D_800C4556 = NO_VALUE;
                D_800C4554 = NO_VALUE;
            }

            if (enemyAttackedIdx == g_SysWork.enemyTargetIdx_2353)
            {
                chara->rotation_24.pad = (ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                                (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) + 0x1000) & 0xFFF;
            }
            else
            {
                chara->rotation_24.pad = chara->rotation_24.vy;
            }

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk30, false);
                extra->model_0.stateStep_3++;
            }
        }
        else
        {
            if (g_SysWork.enemyTargetIdx_2353 != NO_VALUE && !g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x3000, 5);
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x1000, 0x1000, 5);
                }

                if (enemyAttackedIdx == g_SysWork.enemyTargetIdx_2353)
                {
                    temp_a1 = (ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                      (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) + 0x1000) & 0xFFF;

                    Math_ShortestAngleGet(chara->rotation_24.vy, temp_a1, &ssp20);
                    D_800C454C = g_DeltaTime0 * 0xF;

                    if (ABS(ssp20) >= 0x80)
                    {
                        if (ssp20 < 0)
                        {
                            D_800C454C = -D_800C454C;
                        }
                    }
                    else
                    {
                        chara->rotation_24.pad = chara->rotation_24.vy = temp_a1;
                        D_800C454C             = 0;
                    }
                }
            }
            else
            {
                enemyAttackedIdx                                           = NO_VALUE;
                g_SysWork.player_4C.chara_0.properties_E4.player.field_122 = 0x400;
                chara->rotation_24.pad                                     = chara->rotation_24.vy;
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 12;
                        extra->model_0.stateStep_3++;
                    }
                }
                else
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                        extra->model_0.stateStep_3++;
                    }
                }
            }
            else if (g_Player_IsAttacking && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill || g_Player_RockDrill_DirectionAttack == 0)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (g_Player_RockDrill_DirectionAttack == NO_VALUE)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 + 4;
                    extra->model_0.stateStep_3++;
                }
            }
            else
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 + 2;
                    extra->model_0.stateStep_3++;
                }
            }
        }

		// Audio effects for attack animations, no ammo audio and removes ammo value.
		// Additionally trigger some special state for the Rock Drill.
        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_Chainsaw &&
                (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8)
                {
                    if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                    {
                        chara->field_44 = 1;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, FP_VOLUME(0.5f), 0);

                        chara->properties_E4.player.field_10C                       = 0x40;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                    }
                }
                else if (D_800C44D4 < extra->model_0.anim_4.keyframeIdx0_8)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 == FP_TIME(0.0f))
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8 &&
                    !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                {
                    chara->field_44                                             = 1;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else
            {
                if (chara->field_44 <= 0)
                {
                    chara->field_44 = 1;
                }

                chara->properties_E4.player.field_10C = 0x40;
            }
        }
        else
        {
            if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Shooting))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Shooting;

                if (g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 != 0)
                {
                    chara->field_44 = 1;

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                    {
                        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10--;
                        g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].count_1--;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, FP_VOLUME(0.5f), 0);
                    }
                    else
                    {
                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, FP_VOLUME(0.19f), 0);
                    }

                    chara->properties_E4.player.field_10C = 0xC8;
                }
                else
                {
                    func_8005DC1C(g_Player_EquippedWeaponInfo.outOfAmmoSfx_4, &chara->position_18, FP_VOLUME(0.5f), 0);

                    chara->properties_E4.player.field_10C = 32;
                    extra->model_0.anim_4.keyframeIdx0_8  = D_800C44F0[D_800AF220].field_6 - 3;
                    extra->model_0.anim_4.time_4          = FP_TO(D_800C44F0[D_800AF220].field_6 - 3, Q12_SHIFT);

                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                    {
                        chara->model_0.anim_4.keyframeIdx0_8 = D_800C44F0[D_800AF220].field_6 - 3;
                        chara->model_0.anim_4.time_4         = FP_TO(D_800C44F0[D_800AF220].field_6 - 3, Q12_SHIFT);
                    }
                }
            }
        }

        // Finish attack animation.
		// Though more context about `D_800AF220` and `D_800C44F0` is required,
		// they likely indicate if an attack animation has finished.
        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            // Attack anim.
            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
                {
                    extra->model_0.anim_4.status_0      = ANIM_STATUS(PlayerAnim_IdleAim, true);
                    extra->model_0.anim_4.keyframeIdx0_8 = D_800C44F0[0].field_6;
                    extra->model_0.anim_4.time_4         = FP_TO(extra->model_0.anim_4.keyframeIdx0_8, Q12_SHIFT);

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Combat;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                        extra->model_0.state_2                          = extra->model_0.stateStep_3 = 0;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Aim;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }

                    g_SysWork.player_4C.chara_0.properties_E4.player.field_104  = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
                    g_SysWork.playerCombatInfo_38.equippedWeapon_F             %= 10;
                    return true;
                }
            }
        }
        // Attack anim.
        else if ((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true) ||
                  extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk36, true)) &&
                 extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
        {
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
            {
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Combat;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                }
            }
            else
            {
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                extra->model_0.state_2                          = extra->model_0.stateStep_3 = 0;

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Aim;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    chara->model_0.state_2                                      =
                    chara->model_0.stateStep_3                                  = 0;
                }
            }

            D_800C4556                                                  = NO_VALUE;
            D_800C4554                                                  = NO_VALUE;
            g_SysWork.player_4C.chara_0.properties_E4.player.field_104  = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
            return true;
        }

        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;

        // Handles multitap attack.
        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            if (g_Player_MeleeAttackType == 0 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= keyframeIdx1 &&
                    extra->model_0.anim_4.keyframeIdx0_8 < keyframeIdx0 &&
                    extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true) &&
                    (g_Player_IsAttacking || g_Player_IsShooting))
                {
                    g_Player_IsMultiTapAttack = true;
                }
            }
        }

        if (g_Player_IsMultiTapAttack)
        {
            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true) &&
                extra->model_0.anim_4.keyframeIdx0_8 >= keyframeIdx0)
            {
                extra->model_0.stateStep_3 = 0;

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    chara->model_0.stateStep_3 = 0;
                }

                g_Player_AttackAnimIdx                         = g_Player_EquippedWeaponInfo.animAttackHold_8 - 2;
                D_800AF220                                     = (g_Player_EquippedWeaponInfo.field_A >> 4) - 1;
                g_Player_MeleeAttackType                       = 2;
                g_SysWork.playerCombatInfo_38.equippedWeapon_F = (equippedWeaponId % 10) + 20;

                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 2;
                    extra->model_0.stateStep_3++;
                }

                D_800C44D0 = g_MaybePlayerAnims[g_Player_AttackAnimIdx].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E;
                D_800C44D4 = g_MaybePlayerAnims[g_Player_AttackAnimIdx].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E +
                             D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_F;
                g_Player_IsMultiTapAttack = 0;

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
            }
        }

        return false;
    }

    enemyAttackedIdx = NO_VALUE;

    if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimTargetLock && g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_Attack)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.field_104 = 0;
    }

    switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
            if ((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_WalkForward, true) ||
                 extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForward, true)) &&
                extra->model_0.stateStep_3 != 0)
            {
                extra->model_0.stateStep_3 = 0;
            }

			// Set idle animation.
            if (chara->properties_E4.player.exertionTimer_FC < FP_TIME(10.0f) && chara->health_B0 >= FP_HEALTH(30.0f))
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Idle, false);
                    extra->model_0.stateStep_3++;
                }

                Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 53, 1);
            }
            else
            {
                chara->properties_E4.player.afkTimer_E8 = FP_TIME(0.0f);
				
                // If not normal idle anim, set it and update `upperBodyState_20`.
                if (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Idle, true))
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Idle, false);
                        extra->model_0.stateStep_3++;
                    }

                    Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 55, 1);
                }
                else
                {
                    extra->model_0.stateStep_3 = 0;
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleTired, false);
                        extra->model_0.stateStep_3++;
                    }
                }
            }

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_None)
            {
                chara->properties_E4.player.afkTimer_E8 = 0;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_None)
            {
                chara->properties_E4.player.afkTimer_E8++;

                if (chara->properties_E4.player.afkTimer_E8 >= 300)
                {
                    if (chara->health_B0 >= FP_HEALTH(60.0f))
                    {
                        chara->properties_E4.player.afkTimer_E8             = 0;
                        g_SysWork.player_4C.extra_128.state_1C              = PlayerState_Idle;
                        chara->model_0.state_2 = chara->model_0.stateStep_3 = 0;
                        extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                        g_SysWork.player_4C.extra_128.upperBodyState_20     = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24     = PlayerLowerBodyState_None;
                        return true;
                    }
                }
            }
            break;

        default:
            break;

        case PlayerUpperBodyState_WalkForward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_WalkForward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_WalkForward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkForward, 5, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunForward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunForward, 7, 2);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunWallStop:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 19, 0);
            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 21, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_SidestepRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRight, 13, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_SidestepLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepLeft, 11, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRight, 17, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRight, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case PlayerUpperBodyState_RunLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeft, 15, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeft, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case PlayerUpperBodyState_WalkBackward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_WalkBackward, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkBackward, 9, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_QuickTurnRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_QuickTurnRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnRight, 29, 0);

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_QuickTurnRight, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_QuickTurnLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_QuickTurnLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnLeft, 31, 0);

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_QuickTurnLeft, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_TurnRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_TurnRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnRight, 27, 3);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_TurnLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_TurnLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnLeft, 25, 4);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunJumpBackward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_JumpBackward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_JumpBackward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunJumpBackward, 33, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_LowerBodyStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForwardStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_LowerBodyStumble, 23, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunLeftWallStop:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunLeftWallStop, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftWallStop, 0x25, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunRightWallStop:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunRightWallStop, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRightWallStop, 41, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunLeftStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunLeftStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeftStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftStumble, 39, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepRightStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunRightStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRightStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRightStumble, 43, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_Aim:
            g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
                {
                    if (chara->field_44 <= 0)
                    {
                        chara->field_44 = 1;
                    }

                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk34, false);
                        extra->model_0.stateStep_3++;
                    }
                }
                else
                {
                    extra->model_0.anim_4.status_0      = ANIM_STATUS(PlayerAnim_IdleAim, true);
                    extra->model_0.anim_4.keyframeIdx0_8 = D_800AF5C6;
                    extra->model_0.anim_4.time_4         = D_800AF5C6 << 12;
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            chara->rotation_24.pad                                      = chara->rotation_24.vy;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
				// Aim.
                if (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_IdleAim, true) &&
                    extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk34, true))
                {
                    if (g_Player_IsAttacking || g_Player_IsShooting)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk11;
                    }
                    else
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;

                        if (extra->model_0.stateStep_3 == 0)
                        {
                            extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk34, false);
                            extra->model_0.stateStep_3++;
                        }
                    }
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;
                }
            }
            break;

        case PlayerUpperBodyState_AimTargetLock:
            g_SysWork.player_4C.chara_0.properties_E4.player.field_104 += g_DeltaTime0;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;

            if (g_Player_IsTurningRight)
            {
                playerTurn = 1;
            }
            else
            {
                playerTurn = (g_Player_IsTurningLeft != false) * 2;
            }

            if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk29, true) ||
                 extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk30, true) ||
                 extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk32, true) ||
                 extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[4].field_6))
            {
                playerTurn = 0;
                chara->properties_E4.player.field_100++;
            }
            else
            {
                chara->properties_E4.player.field_100 = 0;
            }

            if (playerTurn != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->properties_E4.player.field_F4                 = D_800AF212;

                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xAAA, 0xA000, playerTurn);
                }
                else
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x555, 0x3000, playerTurn);
                }

                if (D_800AF21C == NO_VALUE)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                    g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    g_Player_IsShooting                                         = false;
                    g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                    g_Player_IsAttacking                                        = false;
                    extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;

                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        chara->model_0.state_2                          = chara->model_0.stateStep_3 = 0;
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.upperBodyState_20         = PlayerUpperBodyState_AimTargetLockSwitch;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk12;
                    extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;
                }

                g_SysWork.enemyTargetIdx_2353 = D_800AF21C;
            }
            else
            {
                if (extra->model_0.state_2 != 0)
                {
                    if (g_TargetEnemyPosition.vx != g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vx || g_TargetEnemyPosition.vy != g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vy || g_TargetEnemyPosition.vz != g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vz ||
						D_800C45F8.vx != g_SysWork.player_4C.chara_0.position_18.vx || D_800C45F8.vy != g_SysWork.player_4C.chara_0.position_18.vy || D_800C45F8.vz != g_SysWork.player_4C.chara_0.position_18.vz)
                    {
                        if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                        {
                            func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                        }
                        else
                        {
                            func_8005CD38(&enemyAttackedIdx, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x11C, 0x3000, 0);
                        }

                        g_TargetEnemyPosition = g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18;
                    }
                    else
                    {
                        enemyAttackedIdx = g_SysWork.enemyTargetIdx_2353;
                    }
                }
                else
                {
                    enemyAttackedIdx      = g_SysWork.enemyTargetIdx_2353;
                    g_TargetEnemyPosition = g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18;
                }

                if (enemyAttackedIdx == g_SysWork.enemyTargetIdx_2353 && enemyAttackedIdx != NO_VALUE)
                {
                    chara->rotation_24.pad = (ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                                    (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) + 0x1000) & 0xFFF;
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                    g_SysWork.enemyTargetIdx_2353                               = NO_VALUE;
                    g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                    g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;
                }
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }
            break;

        case PlayerUpperBodyState_AimStart:
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk33, false);
                        extra->model_0.stateStep_3++;
                    }
                }
                else if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleAim, false);
                    extra->model_0.stateStep_3++;
                }

                if (((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw &&
                      extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleAim, true) &&
                      extra->model_0.anim_4.keyframeIdx0_8 >= (D_800C44F0[0].field_4 + 5)) ||
                     (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill &&
                      extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleAim, true) &&
                      extra->model_0.anim_4.keyframeIdx0_8 >= (D_800C44F0[0].field_4 + 9))) &&
                    !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & 4))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_TIME(60.0f);

                    func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, 0);

                    chara->properties_E4.player.field_10C                       = 0x40;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HuntingRifle)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk29, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleAim, false);
                    extra->model_0.stateStep_3++;
                }
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                {
                    if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6)
                    {
                        func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, 1);
                    }

                    g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
                    {
                        chara->field_44 = 1;
                    }
                }
            }
            else
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[1].field_6)
                {
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                }
            }
            break;

        case PlayerUpperBodyState_AimStartTargetLock:
        case PlayerUpperBodyState_AimTargetLockSwitch:
            sp22 = 0;

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (g_GameWork.config_0.optExtraAutoAiming_2C != 0)
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xa000, 0);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                    }
                }
                else if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x7000, 4);
                }
                else
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xE66, 0x2199, 4);
                }

                g_SysWork.enemyTargetIdx_2353 = D_800AF21C;
            }

            D_800AF220 = 1;
            chara->properties_E4.player.field_100++;

            if (!g_GameWork.config_0.optExtraWeaponCtrl_23)
            {
                g_Player_ActionRunPressed      = false;
                g_Player_MovementInputDetected = false;
                g_Player_IsShooting            = false;
                g_Player_IsAttacking           = false;
                g_Player_IsHoldAttack          = false;
                g_Player_IsAiming              = false;
                g_Player_IsRunning             = false;
                g_Player_IsMovingBackward      = false;
                g_Player_IsMovingForward       = false;
                g_Player_IsSteppingRightTap    = false;
                g_Player_IsSteppingRightHold   = false;
                g_Player_IsTurningRight        = false;
                g_Player_IsSteppingLeftTap     = false;
                g_Player_IsSteppingLeftHold    = false;
                g_Player_IsTurningLeft         = false;
            }

            extra->model_0.state_2++;

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk32, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk29, false);
                extra->model_0.stateStep_3++;
            }

            if (g_SysWork.enemyTargetIdx_2353 == NO_VALUE)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;
                break;
            }

            if (g_GameWork.config_0.optExtraAutoAiming_2C == 0)
            {
                temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vx + g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                   (g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vz + g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz);

                temp_s1_2 = FP_ANGLE_NORM_U(temp_v0_3 + FP_ANGLE(360.0f));

                switch (extra->model_0.anim_4.status_0)
                {
                    case ANIM_STATUS(PlayerAnim_Unk29, true):
                    case ANIM_STATUS(PlayerAnim_Unk32, true):
                        if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
                        {
                            chara->rotation_24.vy = temp_s1_2;
                        }
                        break;
                }

                Math_ShortestAngleGet(chara->rotation_24.vy, temp_s1_2, &sp20);

                D_800C454C = ((extra->model_0.state_2 * 3) + 12) * g_DeltaTime0;
                D_800C454C = CLAMP(D_800C454C, 0, 0xFFF);

                if (ABS(sp20) >= FP_ANGLE(11.25f))
                {
                    if (sp20 < FP_ANGLE(0.0f))
                    {
                        D_800C454C = -D_800C454C;
                    }
                }
                else
                {
                    chara->rotation_24.vy  = temp_s1_2;
                    D_800C454C             = 0;
                    chara->rotation_24.pad = temp_s1_2;

                    if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                    }
                    else
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                    }

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                    {
                        if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                        {
                            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                                chara->model_0.state_2                          =
                                chara->model_0.stateStep_3                      = 0;
                            }

                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                            extra->model_0.state_2                                      =
                            extra->model_0.stateStep_3                                  = 0;
                        }
                    }
                    else if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;
                        extra->model_0.state_2                          =
                        extra->model_0.stateStep_3                      = 0;
                    }
                }

                chara->rotation_24.pad = chara->rotation_24.vy;
                break;
            }

            temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vx +
                                g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_0) -
                               g_SysWork.player_4C.chara_0.position_18.vx,
                                (g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].position_18.vz +
                                 g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353].field_D8.field_2) -
                                g_SysWork.player_4C.chara_0.position_18.vz);

            temp_s1_2 = FP_ANGLE_NORM_U(temp_v0_3 + FP_ANGLE(360.0f));

            Math_ShortestAngleGet(chara->rotation_24.vy, temp_s1_2, &sp20);

            sp20      = CLAMP(sp20, -0x180, 0x180);

            temp_v1_3 = g_DeltaTime0 * 0xF;
            temp_v1_3 = CLAMP(temp_v1_3, 0, 0xFFF);
            var_s0    = temp_v1_3;

            Math_ShortestAngleGet(chara->rotation_24.pad, temp_s1_2, &sp22);

            if (ABS(sp22) > FP_ANGLE(11.25f))
            {
                if (sp22 < FP_ANGLE(0.0f))
                {
                    var_s0 = -var_s0;
                }

                chara->rotation_24.pad = FP_ANGLE_NORM_U((chara->rotation_24.pad + (var_s0 >> 4)) + FP_ANGLE(360.0f));
            }
            else
            {
                chara->rotation_24.pad = chara->rotation_24.vy + sp20;

                if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                }

                if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                {
                    if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.state_2                          = chara->model_0.stateStep_3 = 0;
                        }

                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                        extra->model_0.state_2                                      = extra->model_0.stateStep_3 = 0;
                    }
                }
                else if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                {
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;
                    extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                }
            }
            break;

        case PlayerUpperBodyState_AimStop:
            D_800AF220 = g_Player_EquippedWeaponInfo.field_A & 0xF;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animStopAiming_6;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_4 ||
                ((g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunForward || g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunRight ||
                  g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunLeft) &&
                 (extra->model_0.anim_4.keyframeIdx0_8 <= D_800C44F0[D_800AF220].field_6)))
            {
                switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
                {
                    case PlayerLowerBodyState_RunForward:
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunForward;
                        break;

                    case PlayerLowerBodyState_RunRight:
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRight;
                        break;

                    case PlayerLowerBodyState_AimRunLeft:
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeft;
                        break;

                    default:
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                        break;
                }

                extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
                {
                    chara->model_0.state_2 = chara->model_0.stateStep_3 = 0;
                }

                g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_Attack:
            if (Player_CombatAnimUpdate())
            {
                return true;
            }
            break;

        case PlayerUpperBodyState_Reload:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk31, false);
                extra->model_0.stateStep_3++;
            }

            if ((D_800AF624 + g_Player_EquippedWeaponInfo.field_9) <= extra->model_0.anim_4.keyframeIdx0_8 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
            {
                func_8005DC1C(g_Player_EquippedWeaponInfo.reloadSfx_2, &chara->position_18, FP_VOLUME(0.5f), 0);

                chara->properties_E4.player.field_10C                       = 0x20;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
            }

            if (extra->model_0.anim_4.keyframeIdx0_8 == D_800AF626)
            {
                D_800AF21C                                                  = NO_VALUE;
                g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                g_SysWork.enemyTargetIdx_2353                               = NO_VALUE;
                g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                extra->model_0.anim_4.status_0                             = ANIM_STATUS(PlayerAnim_IdleAim, true);
                extra->model_0.anim_4.keyframeIdx0_8                        = 588;
                extra->model_0.anim_4.time_4                                = 0x24C000;

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Reload)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                }

                if (g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                {
                    currentAmmoVar = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                    totalAmmoVar   = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

                    Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombatInfo_38.equippedWeapon_F);

                    g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = currentAmmoVar;
                    g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = totalAmmoVar;

                    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                    {
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_KitchenKnife))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                        }
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_Handgun))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;
                        }
                    }
                }
            }
            break;
    }

    return false;
}

void Player_CombatStateUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x800771BC
{
    s32 currentAmmoVar;
    s32 totalAmmoVar;
    s32 i;

	// Lock player view onto enemy.
    switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
        case PlayerUpperBodyState_WalkForward:
        case PlayerUpperBodyState_SidestepRight:
        case PlayerUpperBodyState_SidestepLeft:
        case PlayerUpperBodyState_WalkBackward:
        case PlayerUpperBodyState_TurnRight:
        case PlayerUpperBodyState_TurnLeft:
            if (!g_Player_IsInWalkToRunTransition)
            {
                if ((g_Player_IsAiming && g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_KitchenKnife) ||
                    g_SysWork.playerCombatInfo_38.isAiming_13)
                {
                    g_SysWork.playerCombatInfo_38.isAiming_13 = true;

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                    {
                        D_800AF21C = NO_VALUE;
                    }
                    else
                    {
                        if (g_GameWork.config_0.optExtraAutoAiming_2C)
                        {
                            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                            {
                                func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                            }
                            else
                            {
                                func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                            }
                        }
                        else if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                        {
                            func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x7000, 4);
                        }
                        else
                        {
                            func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xE66, 0x2199, 4);
                        }
                    }

                    g_SysWork.enemyTargetIdx_2353 = D_800AF21C;
                    if (g_SysWork.enemyTargetIdx_2353 == NO_VALUE)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20            = PlayerUpperBodyState_AimStart;
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_122 = 0x400;
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Combat;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimStartTargetLock;
                    }

                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.state_2                          = 0;
                    }
                    else if (g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 += PlayerLowerBodyState_Aim;
                    }

                    extra->model_0.stateStep_3                   = 0;
                    extra->model_0.state_2                       = 0;
                    chara->properties_E4.player.field_100 = 0;

                    if (g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                    {
                        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                        {
                            currentAmmoVar = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                            totalAmmoVar   = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;
							
                            Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombatInfo_38.equippedWeapon_F);

                            g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = currentAmmoVar;
                            g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = totalAmmoVar;
                        }
                    }

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                    {
                        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                        {
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_KitchenKnife))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                            }
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_Handgun))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;
                            }
                        }
                    }
                }
            }
            break;
    }

    // Execute finishing move on knocked enemies.
    switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
        case PlayerUpperBodyState_WalkForward:
        case PlayerUpperBodyState_SidestepRight:
        case PlayerUpperBodyState_SidestepLeft:
        case PlayerUpperBodyState_WalkBackward:
        case PlayerUpperBodyState_TurnRight:
        case PlayerUpperBodyState_TurnLeft:
        case PlayerUpperBodyState_Aim:
            if (func_8007F95C())
            {
                if (g_Player_IsAttacking)
                {
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_StompEnemy;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    return;
                }

                if (g_Player_IsShooting)
                {
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_KickEnemy;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    return;
                }
            }
            break;
    }

    // Handle aim state.
    switch (g_SysWork.player_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_Aim:
        case PlayerUpperBodyState_AimTargetLock:
		    // Stop aiming.
            if ((g_GameWork.config_0.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                (!g_GameWork.config_0.optExtraWeaponCtrl_23 && g_Player_IsAiming))
            {
                chara->properties_E4.player.field_F4                        = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_AimStop;
                g_SysWork.enemyTargetIdx_2353                               = NO_VALUE;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;
                g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.playerCombatInfo_38.isAiming_13                   = false;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    break;
                }

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_AimWalkForward)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 -= PlayerLowerBodyState_Aim;
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.state_2     = 0;
                break;
            }

            if ((g_Player_IsAttacking || g_Player_IsShooting) &&
                g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_AimQuickTurnRight &&
                g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_AimQuickTurnLeft)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                        g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                    {
                        if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_IdleAim, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk29, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk34, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 < D_800C44F0[6].field_4 ||
                             D_800C44F0[6].field_6 < extra->model_0.anim_4.keyframeIdx0_8) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk30, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk31, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk33, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[5].field_6))
                        {
                            break;
                        }
                    }
                    else
                    {
                        if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_IdleAim, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk29, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk30, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk31, true) ||
                             extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6))
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_IdleAim, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk29, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk30, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk31, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk32, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[4].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk36, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[8].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(PlayerAnim_Unk34, true) ||
                         extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[6].field_4))
                    {
                        break;
                    }
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x3000, 5);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x1000, 0x1000, 5);
                    }

                    g_SysWork.enemyTargetIdx_2353 = D_800AF21C;
                }
                else
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & PlayerFlag_Unk0))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x7000, 0x7000, 5);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x2199, 0x2199, 5);
                    }
                }

                switch (D_800AF21C)
                {
                    default:
                        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                        {
                            g_SysWork.player_4C.extra_128.state_1C                      = PlayerState_Combat;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk0 | PlayerFlag_Unk9;

                            if (g_SysWork.enemyTargetIdx_2353 != D_800AF21C)
                            {
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLockSwitch;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                                    chara->model_0.stateStep_3                      = 0;
                                    chara->model_0.state_2                          = 0;
                                }
                            }

                            g_SysWork.enemyTargetIdx_2353 = D_800AF21C;
                            break;
                        }

                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.state_2                          = 0;
                        }

                    case NO_VALUE:
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                        g_SysWork.player_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Attack;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.state_2                          = 0;
                        }
                        break;
                }

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 == 0 &&
                        (g_SavegamePtr->equippedWeapon_AA >> 5) == 5 &&
                        g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                    {
                        g_SysWork.player_4C.extra_128.upperBodyState_20       = PlayerUpperBodyState_Reload;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Reload;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.state_2                          = 0;
                        }
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_SteelPipe ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Hammer    ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_RockDrill ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Katana)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.state_2                          = 0;
                    }
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.state_2     = 0;
            }
            else
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
            }
            break;
    }
}

void Player_StepWallStop_MovementCancel(s_SubCharacter* chara, s32 animStatus0, s32 animStatus1, s32 keyframeIdx, e_PlayerLowerBodyState lowerBodyState, s32 headingAngle, s32 aimState) // 0x80077BB8
{
    s16 headingAngleCpy;

    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) >> 1;
        if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
        }
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.status_0 = animStatus0;
        chara->model_0.stateStep_3++;
    }

    if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
    {
        if (chara->model_0.anim_4.status_0 == animStatus1 && chara->model_0.anim_4.keyframeIdx0_8 >= keyframeIdx)
        {
            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
            Player_MovementStateReset(chara, lowerBodyState);
        }

        Player_CharaRotate(2);
    }

    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
        g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
    }
    else
    {
        headingAngleCpy                                                   = headingAngle;
        g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = headingAngleCpy;
        g_Player_HeadingAngle                                             = headingAngleCpy;
    }
}

void Player_LowerBodyUpdate(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80077D00
{
	#define PLAYER_FLAG_STOP_WALKING (1 << 0)
	#define PLAYER_FLAG_STOP_RUNNING (1 << 1)
    #define TRAVEL_DIST_MAX          FP_METER(1000000.0f)
    #define TRAVEL_DIST_MIN          1

    // Used for `player.playerMoveDistance_126`.
    #define GET_REAL_SPEED(x)         \
        (((x) == SpeedZoneType_Fast) ? 0x5000 : (((x) == SpeedZoneType_Slow) ? 0x3800 : 0x4000))

    // Used for `player.playerMoveDistance_126`.
    #define GET_VAL(val, delta)     \
        (((val) < 0x3800) ?         \
        (((delta) * 0xC00) / 136) : \
        (((delta) + (((delta) < 0) ? 3 : 0)) >> 2))

    s32                    var_a2;
    s32                    travelDistStep;
    s32                    speedId;
    e_PlayerLowerBodyState temp_s3; // runningState?
    s32                    var_a3;
    s32                    aimState;
    s32                    temp;

    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
    {
        aimState = 0;
    }
    else
    {
        aimState = 20;
    }

    // Compute move distance step.
    temp_s3        = func_8007D6F0(chara, &D_800C45C8);
    speedId        = Map_GetSpeedZone(chara->position_18.vx, chara->position_18.vz);
    var_a2         = SQUARE(chara->position_18.vx - D_800C45F8.vx);
    temp           = SQUARE(chara->position_18.vz - D_800C45F8.vz);
    travelDistStep = SquareRoot0(var_a2 + temp);

    switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
        case PlayerLowerBodyState_Attack:
            break;

        case PlayerLowerBodyState_WalkForward:
        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_SidestepRight:
        case PlayerLowerBodyState_SidestepLeft:
        case PlayerLowerBodyState_AimWalkForward:
        case PlayerLowerBodyState_AimWalkBackward:
        case PlayerLowerBodyState_AimSidestepRight:
        case PlayerLowerBodyState_AimSidestepLeft:
            g_SavegamePtr->walkDistance_258 += travelDistStep;
            g_SavegamePtr->walkDistance_258  = CLAMP(g_SavegamePtr->walkDistance_258, TRAVEL_DIST_MIN, TRAVEL_DIST_MAX);
            break;

        default:
            g_SavegamePtr->runDistance_254 += travelDistStep;
            g_SavegamePtr->runDistance_254  = CLAMP(g_SavegamePtr->runDistance_254, TRAVEL_DIST_MIN, TRAVEL_DIST_MAX);
            break;
    }

    switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_WalkForward, true))
            {
                chara->model_0.stateStep_3 = 0;
            }

            if (aimState != 0) // If player is aiming.
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & 1)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                    }
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & 1)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }

            // Sets animations during specific idle states while aiming or standing.
            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
            {
                // Aim to idle.
                if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombatInfo_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        chara->model_0.stateStep_3++;
                    }
                }
	           // Checks if player has >=30% or <10% health to determine level of exertion.
                else if (chara->properties_E4.player.exertionTimer_FC < FP_TIME(10.0f) && chara->health_B0 >= FP_HEALTH(30.0f))
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Idle, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleTired, false);
                    chara->model_0.stateStep_3++;
                }
            }
            else
            {
                if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombatInfo_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        chara->model_0.stateStep_3++;
                    }
                }
                // Non-gun weapon.
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                         g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill) &&
                        g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk33, false);
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleAim, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk6)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk34, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk32, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HuntingRifle)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk29, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleAim, false);
                        chara->model_0.stateStep_3++;
                    }
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            }

            // Set idle to move depending on user input.
            if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat) // Aiming at or shooting enemy.
            {
                if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0) &&
                    IS_ANIM_STATUS_ACTIVE(extra->model_0.anim_4.status_0))
                {
                    if (chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_Unk29, false) ||
                        chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 || 
                        chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                    {
                        if (g_Player_IsMovingForward != 0)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                        }
                        else if (g_Player_IsMovingBackward != 0)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                        }
                    }
                }

                Player_MovementStateReset(chara, aimState);
            }
            // Aiming at nothing, or shooting at nothing, or idle.
            else
            {
                if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0) &&
                    IS_ANIM_STATUS_ACTIVE(extra->model_0.anim_4.status_0))
                {
                    if ((aimState == 0 && g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 == FP_METER(0.0f))||
                        chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_Unk29, false) ||
						chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6)
                    {
                        if (g_Player_IsMovingForward)
                        {
							// Restrict aiming when going from idle to run.
                            if ((g_Player_IsRunning && temp_s3 == PlayerLowerBodyState_None) &&
                                (aimState == 0 || ((g_GameWork.config_0.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                                                   (!g_GameWork.config_0.optExtraWeaponCtrl_23 && g_Player_IsAiming)) && 
                                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_SteelPipe))
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C = chara->headingAngle_3C + FP_ANGLE(90.0f);
                            temp_s3                = func_8007D6F0(chara, &D_800C45C8);

                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);
                            temp_s3                 = func_8007D6F0(chara, &D_800C45C8);
 
                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }
                        }

                        if (aimState == 0 && g_SysWork.playerCombatInfo_38.isAiming_13 == false)
                        {
                            if ((g_GameWork.config_0.optExtraWalkRunCtrl_2B && !g_Player_IsRunning) ||
                                (!g_GameWork.config_0.optExtraWalkRunCtrl_2B && g_Player_IsRunning))
                            {
                                if (g_Player_IsMovingBackward)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
                                    extra->model_0.stateStep_3                      = 0;
                                    extra->model_0.state_2                          = 0;
                                }
                            }
                        }

                        if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == aimState && !g_Player_IsInWalkToRunTransition)
                        {
                            Player_CharaTurn_0(chara, aimState);
                        }
                    }
                }

                Player_MovementStateReset(chara, aimState);

                if (g_Player_IsRunning)
                {
                    Player_CharaRotate(10);
                }
                else
                {
                    Player_CharaRotate(7);
                }

                if (aimState != 0 && g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Aim)
                {
                    if (D_800C454C != FP_METER(0.0f))
                    {
						// Determine speed if using certain weapons while moving?
                        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
                        {
                            case EquippedWeaponId_KitchenKnife:
                                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = (u32)(D_800C454C * 0x465) >> 9;
                                break;

                            case EquippedWeaponId_Chainsaw:
                            case EquippedWeaponId_Katana:
                            case EquippedWeaponId_Axe:
                                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = (u32)(D_800C454C * 0x15F9) >> 11;
                                break;

                            case EquippedWeaponId_SteelPipe:
                            case EquippedWeaponId_Hammer:
                                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = ((u32)(D_800C454C * 0xD2F) >> 10);
                                break;

                            case EquippedWeaponId_RockDrill:
                            case EquippedWeaponId_Handgun:
                            case EquippedWeaponId_HuntingRifle:
                            case EquippedWeaponId_Shotgun:
                            case EquippedWeaponId_HyperBlaster:
                                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = (-(D_800C454C * 0x87F0) >> 14);
                                break;
                        }

                        if (g_DeltaTime0 != FP_METER(0.0f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 * 0x88) / g_DeltaTime0);
                        }
						
						// Restart timer for idle animation.
                        if (D_800C454C != FP_METER(0.0f))
                        {
                            chara->properties_E4.player.afkTimer_E8 = 0;
                        }
                    }
                }
                // Move without aiming.
                else if (D_800C454C != FP_METER(0.0f))
                {
                    chara->properties_E4.player.afkTimer_E8 = 0;
                }
				
				// Turn if idle.
                if (g_Player_IsTurningLeft && chara->model_0.stateStep_3 == 1 &&
                    (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Idle, true) ||
                     chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleTired, true)))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_TurnLeft, false);
                }
                else if (g_Player_IsTurningRight && chara->model_0.stateStep_3 == 1 && 
                         (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Idle, true) ||
                          chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleTired, true)))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_TurnRight, false);
                }

                if (!g_Player_IsTurningLeft && !g_Player_IsTurningRight && chara->model_0.stateStep_3 == 2 &&
                    (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_TurnRight, true) ||
                     chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_TurnLeft, true)))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Idle, false);
                    chara->model_0.stateStep_3      = 0;
                }
            }

            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 == FP_METER(0.0f) ||
                 g_Player_IsTurningLeft || g_Player_IsTurningRight)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
            }
            break;

        case PlayerLowerBodyState_WalkForward:
        case PlayerLowerBodyState_AimWalkForward:
            if (!g_Player_IsMovingForward)
            {
                g_SysWork.field_235A |= PLAYER_FLAG_STOP_WALKING;
            }

            if (g_SysWork.field_235A & PLAYER_FLAG_STOP_WALKING && g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim && 
                g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2;

                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                    }
                }
            }
            // Walking.
            else
            {
                if (g_Controller0->sticks_20.sticks_0.leftY < -0x3F)
                {
                    D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                    func_80070B84(chara, FP_METER(0.75f), FP_METER(1.4f), 2);
                }
                // Stopped walking.
                else
                {
                    if (D_800AF216 != 0)
                    {
                        func_80070B84(chara, FP_METER(0.75f), FP_METER(1.4f), 2);
                    }
                    // Reduce speed if going too fast while walking.
                    else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(1.4f))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2;
                        if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.4f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.4f);
                        }
                    }
                    else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.4f))
                    {
                        if (chara->model_0.anim_4.keyframeIdx0_8 >= 2)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.4f));
                        }
                        
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                        FP_METER(0.0f),
                                                                                                        FP_METER(1.4f));
                    }

                    if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                    {
                        D_800AF216 = 0;
                    }
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_WalkForward, false);
                chara->model_0.stateStep_3++;
            }

            // Something related to anim and states when aiming or attacking while moving.
            if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat)
            {
                if (g_SysWork.field_235A & PLAYER_FLAG_STOP_WALKING)
                {
                    if ((g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                         g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 10 && chara->model_0.anim_4.keyframeIdx0_8 <= 11) || 
                          chara->model_0.anim_4.keyframeIdx0_8 == 22 || chara->model_0.anim_4.keyframeIdx0_8 == 21)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(chara, aimState | (1 << 0));

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.field_235A & PLAYER_FLAG_STOP_WALKING))
                {
					// Code to change the player's state to running.
                    if (g_Player_IsRunning)
                    {
                        if (aimState == 0 && temp_s3 == PlayerLowerBodyState_None &&
                            (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_WalkForward ||
                             g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 >= 10 && chara->model_0.anim_4.keyframeIdx0_8 <= 11)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_RunForward;
                                g_MaybePlayerAnims[0].keyframeIdx1_E                        = 36;
                                g_MaybePlayerAnims[0].status_6                             = 7;
                                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
                            }
                            else if (chara->model_0.anim_4.keyframeIdx0_8 >= 21 && chara->model_0.anim_4.keyframeIdx0_8 <= 22)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                                g_MaybePlayerAnims[0].keyframeIdx1_E            = 26;
                                g_MaybePlayerAnims[0].status_6                 = 7;
                            }
                        }
                    }
                }
                else if ((g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                          g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 10 && chara->model_0.anim_4.keyframeIdx0_8 <= 11) ||
                          chara->model_0.anim_4.keyframeIdx0_8 == 22 || chara->model_0.anim_4.keyframeIdx0_8 == 21)
                {
					// Aparently, code intended to change player's state if the player stop walking while either aiming or attacking.
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true)) && 
                            (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                             g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                            extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = aimState;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24             = aimState;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == (aimState + PlayerLowerBodyState_WalkForward) && !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(chara, aimState);
                }

                Player_MovementStateReset(chara, aimState | (1 << 0));
                Player_CharaRotate(5);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);

            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunForward)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk0, false);
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForward:
            chara->properties_E4.player.exertionTimer_FC += g_DeltaTime0;

            if (g_Controller0->sticks_20.sticks_0.leftY < -0x3F)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);

                var_a2 = GET_REAL_SPEED(speedId);

                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.5f)) 
                {
                    var_a3 = Math_UnkDistTimeCalc(FP_METER(0.75f));
                } 
                else 
                {
                    temp   = g_DeltaTime0;
                    temp  += (temp < 0) ? 3 : 0;
                    var_a3 = temp >> 2;
                }

                func_80070CF0(chara, FP_FLOAT_TO(2.0f, Q12_SHIFT), var_a2, var_a3, Math_UnkDistTimeCalc(FP_METER(0.4f)));
            }
            // Stopped running.
            else
            {
                if (D_800AF216 != 0)
                {
                    var_a2 = GET_REAL_SPEED(speedId);

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.5f)) 
                    {
                        var_a3 = Math_UnkDistTimeCalc(FP_METER(0.75f));
                    } 
                    else 
                    {
                        temp   = g_DeltaTime0;
                        temp  += (temp < 0) ? 3 : 0;
                        var_a3 = temp >> 2;
                    }

                    func_80070CF0(chara, FP_FLOAT_TO(2.0f, Q12_SHIFT), var_a2, var_a3, Math_UnkDistTimeCalc(FP_METER(0.4f)));
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > GET_REAL_SPEED(speedId))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < GET_REAL_SPEED(speedId))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = GET_REAL_SPEED(speedId);
                    }
                }
                else
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < GET_REAL_SPEED(speedId))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += GET_VAL(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126, g_DeltaTime0);
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126, 0, GET_REAL_SPEED(speedId));
                    }
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForward, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 43 || chara->model_0.anim_4.keyframeIdx0_8 == 33) && 
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->field_34 = FP_FLOAT_TO(-1.25f, Q12_SHIFT);
            }

            // Running.
            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock &&
                chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForward, true))
            {
				// TODO: What does `func_8007D6F0` do?
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Stumble;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = temp_s3;
                            g_MaybePlayerAnims[0].keyframeIdx1_E            = 8;
                            g_MaybePlayerAnims[0].status_6                 = 5;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = temp_s3;
                            g_MaybePlayerAnims[0].keyframeIdx1_E            = 20;
                            g_MaybePlayerAnims[0].status_6                 = 5;
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForwardWallStop;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                            g_MaybePlayerAnims[0].keyframeIdx1_E            = 8;
                            g_MaybePlayerAnims[0].status_6                 = 5;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                            g_MaybePlayerAnims[0].keyframeIdx1_E            = 20;
                            g_MaybePlayerAnims[0].status_6                 = 5;
                        }
                        break;

                    default:
                        if (g_Player_IsRunning == 0 || g_Player_IsMovingForward == 0)
                        {
                            // Change state from running to walking.
                            if (g_Player_IsMovingForward)
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E            = 8;
                                    g_MaybePlayerAnims[0].status_6                 = 5;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E            = 20;
                                    g_MaybePlayerAnims[0].status_6                 = 5;
                                }
                            }
                            // Set stumble anim if crashed into a wall.
                            else if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                                     g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >= FP_METER(3.125f))
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 33 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 34)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_RunForwardWallStop;
                                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_WallStopRight;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 43 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 44)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_RunForwardWallStop;
                                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                                }
                            }
                            // Change state from running to walking. Difference with first conditional is this only triggers if
                            // walking is abruptly stopped wall crash anim was not triggered.
                            // In-game, appears as though player goes directly to idle. Mechanically, it goes through this state, then to idle.
                            else
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E            = 8;
                                    g_MaybePlayerAnims[0].status_6                 = 5;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E            = 20;
                                    g_MaybePlayerAnims[0].status_6                 = 5;
                                }
                            }
                        }
                        break;
                }
            }

            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_RunForward)
            {
                Player_MovementStateReset(chara, PlayerLowerBodyState_RunForward);
            }

            Player_CharaRotate(4);

            g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);

            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_WalkForward)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk0, false);
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) >> 1;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }
			
            // Depending on frame of gait cycle, set left or right wall stop anim variant.
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, false);
                    chara->model_0.stateStep_3++;
                }
            }
            else if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft, true) &&
                    chara->model_0.anim_4.keyframeIdx0_8 >= 168 ||
                    chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true) &&
                    chara->model_0.anim_4.keyframeIdx0_8 >= 158)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    Player_MovementStateReset(chara, PlayerLowerBodyState_RunForwardWallStop);
                }

                Player_CharaRotate(4);
            }
            break;

        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            if (g_Player_IsMovingBackward == 0)
            {
                g_SysWork.field_235A |= PLAYER_FLAG_STOP_RUNNING;
            }

            if (g_SysWork.field_235A & PLAYER_FLAG_STOP_RUNNING && g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
			g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2);
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                    }
                }
            }
            // Walking backward.
            else if (g_Controller0->sticks_20.sticks_0.leftY >= (1 << 6))
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                func_80070B84(chara, FP_METER(0.75f), FP_METER(1.15f), 2);
            }
            // Stop walking backward.
            else
            {
                if (D_800AF216 != 0)
                {
                    func_80070B84(chara, FP_METER(0.75f), FP_METER(1.15f), 2);
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(1.15f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2;
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.15f))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.15f);
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.15f))
                {
                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 2)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.4f));
                    }
                        
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                    FP_METER(0.0f),
                                                                                                    FP_METER(1.15f));
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickDown)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_WalkBackward, false);
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat)
            {
                if (g_SysWork.field_235A & PLAYER_FLAG_STOP_RUNNING)
                {
                    if ((g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim && g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 56 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 57) ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 67 ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 66)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_WalkBackward);

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.field_235A & PLAYER_FLAG_STOP_RUNNING))
                {
                    if (((chara->model_0.anim_4.keyframeIdx0_8 >= 66 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 67) ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 46 ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 47) && 
                        aimState == 0 && g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        if ((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0 && g_Player_IsRunning == 0) ||
                            (g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0 && g_Player_IsRunning != 0))
                        {
                            if (g_Player_IsMovingBackward != 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.state_2                          = 0;
                            }
                        }
                    }
                }
                else if ((g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim && g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 56 && chara->model_0.anim_4.keyframeIdx0_8 <= 57) ||
                          chara->model_0.anim_4.keyframeIdx0_8 == 67 || chara->model_0.anim_4.keyframeIdx0_8 == 66)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true)) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                            extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = aimState;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24             = aimState;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == (aimState + PlayerLowerBodyState_WalkBackward) && !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(chara, aimState);
                }

                Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_WalkBackward);
                Player_CharaRotate(4);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_SidestepRight:
        case PlayerLowerBodyState_AimSidestepRight:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(1.25f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f)));
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.25f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.25f);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 >= 100 &&
                    chara->model_0.anim_4.keyframeIdx0_8 <= 111)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.4f));
                }
                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 112)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                FP_METER(0.0f),   
                                                                                                FP_METER(1.25f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_SidestepRight, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_SidestepRight, true) &&
                chara->model_0.anim_4.keyframeIdx0_8 >= 117)
            {
				// Stopped sidestepping while attacking.
				// If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingRightHold)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && aimState != 0)
                    {
						// Some melee weapons allow attack while sidestepping.
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true)) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                    }
                }
            }

            Player_CharaTurn_0(chara, aimState);
            Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_SidestepRight);
            Player_CharaRotate(3);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_SidestepLeft:
        case PlayerLowerBodyState_AimSidestepLeft:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(1.25f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(1.25f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.25f);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 >= 75 &&
                    chara->model_0.anim_4.keyframeIdx0_8 <= 86)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.4f));
                }
                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 87)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                FP_METER(0.0f),
                                                                                                FP_METER(1.25f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_SidestepLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_SidestepLeft, true) &&
                chara->model_0.anim_4.keyframeIdx0_8 >= 92)
            {
				// Stopped stepping while attacking.
				// If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingLeftHold)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true)) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                             extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                    }
                }
            }

            Player_CharaTurn_1(chara, aimState);
            Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_SidestepLeft);
            Player_CharaRotate(3);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_RunRight:
            chara->properties_E4.player.exertionTimer_FC += g_DeltaTime0;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(3.1739))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.1739))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(3.1739);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.1739))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.75f));
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                 FP_METER(0.0f),
                                                                                                 FP_METER(3.1739));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunRight, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 139 ||
                 chara->model_0.anim_4.keyframeIdx0_8 == 145) &&
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->field_34 = FP_FLOAT_TO(-1.0f, Q12_SHIFT);
            }

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightStumble;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRight, true) &&
                                chara->model_0.anim_4.keyframeIdx0_8 >= 147)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightWallStop;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRight, true) &&
                                chara->model_0.anim_4.keyframeIdx0_8 >= 147)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >= FP_METER(3.125f))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 >= 144 && (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightWallStop;
                            }
                        }
                        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRight, true) &&
                                 chara->model_0.anim_4.keyframeIdx0_8 >= 147 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(chara, PlayerLowerBodyState_RunRight);
            Player_CharaRotate(4);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_RunLeft:
            chara->properties_E4.player.exertionTimer_FC += g_DeltaTime0;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > FP_METER(3.1739))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.1739))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(3.1739);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(3.1739))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += Math_UnkDistTimeCalc(FP_METER(0.75f));
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                 FP_METER(0.0f),
                                                                                                 FP_METER(3.1739));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunLeft, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 125 || chara->model_0.anim_4.keyframeIdx0_8 == 132) &&
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->field_34 = FP_FLOAT_TO(-1.0f, Q12_SHIFT);
            }

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftStumble;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeft, true) &&
                                chara->model_0.anim_4.keyframeIdx0_8 >= 132)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)FP_METER(10.0f))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftWallStop;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeft, true) &&
                                chara->model_0.anim_4.keyframeIdx0_8 >= 132)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >= FP_METER(3.125f))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 > 128 && (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftWallStop;
                            }
                        }
                        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeft, true) && chara->model_0.anim_4.keyframeIdx0_8 >= 132 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(chara, PlayerLowerBodyState_RunLeft);
            Player_CharaRotate(4);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            g_Player_HeadingAngle = FP_ANGLE(0.0f);

            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (g_DeltaTime0 << 11) / 136;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (chara->model_0.state_2 == 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_QuickTurnRight, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.state_2 == 0)
            {
                chara->model_0.state_2++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_QuickTurnRight, true) && chara->model_0.anim_4.keyframeIdx0_8 >= 206)
            {
                D_800C454C = g_DeltaTime0 * 24;
            }
            else
            {
                D_800C454C = FP_TIME(0.0f);
            }

            if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) > (FP_ANGLE(180.0f) - ((s32)(g_DeltaTime0 * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) < (((g_DeltaTime0 * 24) >> 4) + FP_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                                   = g_SysWork.player_4C.chara_0.properties_E4.npc.field_120 +
                                                                                              FP_ANGLE(180.0f);
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.4f);
                    D_800C454C                                                              = FP_TIME(0.0f);

                    // State change.
                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 213)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C += FP_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 216)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.state_2                          = 0;
                        }
                    }
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            g_Player_HeadingAngle = FP_ANGLE(0.0f);

            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (g_DeltaTime0 << 11) / 136;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (chara->model_0.state_2 == 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_QuickTurnLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.state_2 == 0)
            {
                chara->model_0.state_2++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_QuickTurnLeft, true) && chara->model_0.anim_4.keyframeIdx0_8 >= 219)
            {
                D_800C454C = -(g_DeltaTime0 * 24);
            }
            else
            {
                D_800C454C = FP_TIME(0.0f);
            }

            if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) > (FP_ANGLE(180.0f) - ((g_DeltaTime0 * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) < (((g_DeltaTime0 * 24) >> 4) + FP_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                                   = g_SysWork.player_4C.chara_0.properties_E4.npc.field_120 + FP_ANGLE(180.0f);
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.4f);
                    D_800C454C                                                              = FP_TIME(0.0f);

                    // State change.
                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 226)
                    {
                        if (g_Player_IsMovingForward != 0)
                        {
                            if (g_Player_IsRunning != 0 && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C += FP_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 229)
                        {
                            g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.state_2                          = 0;
                        }
                    }
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
            break;
            
        case PlayerLowerBodyState_JumpBackward:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_JumpBackward, false);
                chara->model_0.stateStep_3++;
            }
            
            // Jump backward.
            if ((chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_JumpBackward, false) &&
                 chara->model_0.anim_4.status_0 <= ANIM_STATUS(PlayerAnim_JumpBackward, true)) &&
                chara->model_0.anim_4.keyframeIdx0_8 < 245)
            {
                if (chara->model_0.state_2 == 0)
                {
                    chara->field_34 = FP_FLOAT_TO(-2.0f, Q12_SHIFT);
                }

                chara->model_0.state_2++;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(2.25f);
                D_800C4550                                                              = FP_METER(2.25f);
            }
            else
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2);
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                    }
                }

                D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_JumpBackward, true) && chara->model_0.anim_4.keyframeIdx0_8 == 246)
            {
                if (chara->position_18.vy < chara->properties_E4.player.positionY_EC)
                {
                    g_SysWork.player_4C.extra_128.state_1C = PlayerState_FallBackward;

                    chara->model_0.stateStep_3 = 0;
                    chara->model_0.state_2     = 0;
                    extra->model_0.stateStep_3 = 0;
                    extra->model_0.state_2     = 0;

                    g_SysWork.player_4C.extra_128.upperBodyState_20                         = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24                         = PlayerLowerBodyState_None;
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(1.25f);
                }
                else 
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = aimState;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    chara->field_34                                 = FP_METER(0.0f);
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_Stumble:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((Math_UnkDistTimeCalc(FP_METER(0.4f))) * 2) / 3;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (D_800C45DC <= FP_FLOAT_TO(0.5f, Q12_SHIFT) && g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) * 4;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunForwardStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunForwardStumble, true) && chara->model_0.anim_4.keyframeIdx0_8 == 179)
            {
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, PlayerLowerBodyState_Stumble);
            }
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            Player_StepWallStop_MovementCancel(chara, 36, 37, 335, PlayerLowerBodyState_RunLeftWallStop, FP_ANGLE(-90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            Player_StepWallStop_MovementCancel(chara, 40, 41, 364, PlayerLowerBodyState_RunRightWallStop, FP_ANGLE(90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) >> 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (D_800C45DC < FP_FLOAT_TO(0.3401f, Q12_SHIFT))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunLeftStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunLeftStumble, true) && chara->model_0.anim_4.keyframeIdx0_8 == 349)
            {
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, 15);
            }

            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_None)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(-90.0f);
                g_Player_HeadingAngle                                             = FP_ANGLE(-90.0f);
                break;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (Math_UnkDistTimeCalc(FP_METER(0.4f))) >> 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                }
            }

            if (D_800C45DC < FP_FLOAT_TO(0.3401f, Q12_SHIFT))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_RunRightStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_RunRightStumble, true) && chara->model_0.anim_4.keyframeIdx0_8 == 378)
            {
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, 16);
            }

            if (g_SysWork.player_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = FP_ANGLE(0.0f);
                break;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = FP_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_Attack:
		    // If weapon is katana.
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Katana)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == 16)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 == FP_METER(0.0f) && 
                        (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44F0[D_800AF220].field_4 + 7))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(5.0f);
                        g_Player_HeadingAngle                                                   = FP_ANGLE(0.0f);
                    }
                }
                else if (chara->model_0.stateStep_3 == 0 && !g_Player_IsAttacking)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(5.0f);
                    g_Player_HeadingAngle                                                   = FP_ANGLE(0.0f);
                }
            }
			
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Katana)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (g_DeltaTime0 * 0x444) / 136;
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                    }
                }
            }
            else
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= Math_UnkDistTimeCalc(FP_METER(0.4f));
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
                    }
                }
            }

            if (g_SysWork.enemyTargetIdx_2353 == NO_VALUE || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 12;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk10)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw || g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_IdleAim, false);
                        chara->model_0.stateStep_3++;
                    }

                    if (chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                    {
                        chara->model_0.anim_4.status_0      = extra->model_0.anim_4.status_0;
                        chara->model_0.anim_4.keyframeIdx0_8 = extra->model_0.anim_4.keyframeIdx0_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                {
                    if (g_Player_RockDrill_DirectionAttack == 1)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 + 2;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (g_Player_RockDrill_DirectionAttack == NO_VALUE)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 + 4;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
                else
                {
                    if (extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk30, true))
                    {
                        chara->model_0.anim_4.status_0      = extra->model_0.anim_4.status_0;
                        chara->model_0.anim_4.keyframeIdx0_8 = extra->model_0.anim_4.keyframeIdx0_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                    else if (g_Player_IsAttacking || extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk29, true))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (g_Player_IsShooting || extra->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_Unk31, true))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
            }
            else if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttackHold_8 - 1;
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun ||
                ((g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_SteelPipe &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_Hammer    &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_RockDrill &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != EquippedWeaponId_Katana))
            {
                if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0) && IS_ANIM_STATUS_ACTIVE(extra->model_0.anim_4.status_0) &&
                    (chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_Unk29, false) || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6))
                {
                    if (!g_Player_IsMovingForward)
                    {
                        if (g_Player_IsMovingBackward)
                        {
                            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 == FP_METER(0.0f))
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                            }
                        }
                        else if (g_SysWork.player_4C.extra_128.state_1C != PlayerState_Combat)
                        {
                            if (!g_Player_IsSteppingRightHold)
                            {
                                if (g_Player_IsSteppingLeftHold)
                                {
                                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepLeft;
                                }
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepRight;
                            }
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                    }
                    
                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Attack)
                    {
                        Player_MovementStateReset(chara, PlayerLowerBodyState_Aim);
                        break;
                    }
                }
            }
            break;

        case PlayerLowerBodyState_Reload:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(PlayerAnim_Unk31, false);
                chara->model_0.stateStep_3++;
            }

            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0) && IS_ANIM_STATUS_ACTIVE(extra->model_0.anim_4.status_0) &&
                (chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_Unk29, false) || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6))
            {
                if (g_Player_IsMovingForward)
                {
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                }
                else if (g_Player_IsMovingBackward)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 == FP_METER(0.0f))
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                    }
                }
                else if (g_SysWork.player_4C.extra_128.state_1C != PlayerState_Combat)
                {
                    if (g_Player_IsSteppingRightHold)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepRight;
                    }
                    else if (g_Player_IsSteppingLeftHold)
                    {
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepLeft;
                    }
                }

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Reload)
                {
                    Player_MovementStateReset(chara, PlayerLowerBodyState_Aim);
                }
            }
            break;
    }

    func_8007B924(chara, extra);
}

void func_8007B924(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x8007B924
{
    s32 sfx;
    s8  pitch0;
    s8  pitch1;

    func_8007FDE0(D_800C4590.field_14, &sfx, &pitch0, &pitch1);

	// This entire conditional is the reason why movement stop working when removing this function call.
    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_JumpBackward && g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Reload)
    {
        D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
    }
	
    switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_RunForward:
        case PlayerLowerBodyState_RunRight:
        case PlayerLowerBodyState_RunLeft:
            if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0) && chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_RunForward, true))
            {
                chara->properties_E4.player.exertionTimer_FC += g_DeltaTime0;
            }
            break;

        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_RunForwardWallStop:
        case PlayerLowerBodyState_Stumble:
        case PlayerLowerBodyState_RunLeftStumble:
        case PlayerLowerBodyState_RunRightStumble:
        case PlayerLowerBodyState_Aim:
            chara->properties_E4.player.exertionTimer_FC -= g_DeltaTime0 * 2;
            break;

        default:
            chara->properties_E4.player.exertionTimer_FC -= g_DeltaTime0;
            break;
    }

    chara->properties_E4.player.exertionTimer_FC = CLAMP(chara->properties_E4.player.exertionTimer_FC, FP_TIME(0.0f), FP_TIME(35.0f));

    // Check if player has >=30% or <10% of health to determine exertion level.
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleTired, true))
    {
        if (chara->properties_E4.player.exertionTimer_FC < FP_TIME(10.0f) &&
            chara->health_B0 >= FP_HEALTH(30.0f))
        {
            chara->model_0.stateStep_3 = 0;
            chara->model_0.state_2     = 0;
            extra->model_0.stateStep_3 = 0;
            extra->model_0.state_2     = 0;
        }
    }
	
	// Plays movement sounds.
    switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            // Turn right.
            if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_TurnRight)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_TurnRight, true), chara, 204, 200, sfx, pitch0);
            }
            // Turn left.
            else if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_TurnLeft)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_TurnLeft, true), chara, 187, 191, sfx, pitch0);
            }

            if ((g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Moving) &&
                ((chara->model_0.anim_4.status_0 >= ANIM_STATUS(PlayerAnim_Idle, true) &&
                  chara->model_0.anim_4.status_0 <= ANIM_STATUS(PlayerAnim_IdleTired, false)) ||
                 chara->model_0.anim_4.status_0 == ANIM_STATUS(PlayerAnim_IdleAim, true)))
            {
                func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.095f), pitch0);

                chara->properties_E4.player.field_10C                        = pitch0 + 0x10;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }

            if (chara->model_0.anim_4.keyframeIdx0_8 == 246 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk5))
            {
                func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.5f), pitch1);

                chara->properties_E4.player.field_10C                       = pitch1 + 0x20;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        default:
            break;
			
        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            func_800713E8(ANIM_STATUS(PlayerAnim_WalkBackward, true), chara, 52, 63, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_AimWalkForward:
        case PlayerLowerBodyState_WalkForward:
            func_800713E8(ANIM_STATUS(PlayerAnim_WalkForward, true), chara, 18, 6, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForward:
            if (func_800713E8(ANIM_STATUS(PlayerAnim_RunForward, true), chara, 31, 41, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepRight:
            func_800713E8(ANIM_STATUS(PlayerAnim_SidestepRight, true), chara, 118, 108, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            func_800713E8(ANIM_STATUS(PlayerAnim_SidestepLeft, true), chara, 93, 83, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRight:
            if (func_800713E8(ANIM_STATUS(PlayerAnim_RunRight, true), chara, 145, 139, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeft:
            if (func_800713E8(ANIM_STATUS(PlayerAnim_RunLeft, true), chara, 131, 125, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 < 152)
                {
                    func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true), chara, 151, 154, sfx, pitch1);
                }
                else
                {
                    func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true), chara, 156, 154, sfx, pitch1);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 < 162)
                {
                    func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft, true), chara, 164, 161, sfx, pitch1);
                }
                else
                {
                    func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft, true), chara, 164, 166, sfx, pitch1);
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 323)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunLeftWallStop, true), chara, 322, 324, sfx, pitch1);
            }
            else
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunLeftWallStop, true), chara, 327, 324, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 352)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunRightWallStop, true), chara, 353, 351, sfx, pitch1);
            }
            else
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunRightWallStop, true), chara, 353, 356, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_Stumble:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 172)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardStumble, true), chara, 171, 174, sfx, pitch1);
            }
            else
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunForwardStumble, true), chara, 176, 174, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 338)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunLeftStumble, true), chara, 337, 341, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx0_8 < 344)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunLeftStumble, true), chara, 343, 341, sfx, pitch0);
            }
            else
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunLeftStumble, true), chara, 356, 346, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 367)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunRightStumble, true), chara, 366, 370, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx0_8 < 373)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunRightStumble, true), chara, 372, 370, sfx, pitch0);
            }
            else
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_RunRightStumble, true), chara, 385, 375, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            func_800713E8(ANIM_STATUS(PlayerAnim_QuickTurnLeft, true), chara, 222, 224, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            func_800713E8(ANIM_STATUS(PlayerAnim_QuickTurnRight, true), chara, 209, 211, sfx, pitch0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_JumpBackward:
        case PlayerLowerBodyState_Unk31:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 243)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
            }

            if (chara->position_18.vy == D_800C4590.field_C)
            {
                func_800713E8(ANIM_STATUS(PlayerAnim_JumpBackward, true), chara, 243, 245, sfx, pitch1);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
    }
}

void func_8007C0D8(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord) // 0x8007C0D8
{
    s_func_800699F8 sp10;
    VECTOR3         sp20;
    VECTOR3         sp30;
    VECTOR3         sp40;
    s16             temp_v0;
    s16             someAngle;
    s16             temp_s0;
    s32             temp_s0_2;
    s32             temp_s2;
    s32             temp_s2_2;
    s32             temp_s3;
    s32             temp_s3_2;
    s32             temp_v0_3;
    s16             temp_v1;
    s32             posY;
    u32             temp;

    D_800C45F8 = chara->position_18;

    func_800699F8(&sp10, chara->position_18.vx, chara->position_18.vz);

    temp_s3 = FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
    temp_s2 = FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

    temp_s0 = Math_Cos(ABS(sp10.field_4) >> 3);

    temp_v0 = Math_Cos(ABS(sp10.field_6) >> 3);

    temp_v1 = FP_MULTIPLY(FP_MULTIPLY(temp_s3, temp_s0, Q12_SHIFT), temp_s0, Q12_SHIFT);
    someAngle = FP_MULTIPLY(FP_MULTIPLY(temp_s2, temp_v0, Q12_SHIFT), temp_v0, Q12_SHIFT);

    if (chara->moveSpeed_38 >= 0)
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }

    temp_s0_2 = FP_MULTIPLY_PRECISE(chara->moveSpeed_38, g_DeltaTime0, Q12_SHIFT);

    temp_v0_3 = chara->headingAngle_3C;
    temp      = temp_s0_2 + 0x7FFF;
    temp_s2_2 = (temp > 0xFFFE) * 4;
    temp_s3_2 = temp_s2_2 >> 1;

    sp20.vx = FP_MULTIPLY_PRECISE((temp_s0_2 >> temp_s3_2), Math_Sin(temp_v0_3) >> temp_s3_2, Q12_SHIFT);
    sp20.vx <<= temp_s2_2;

    sp20.vz = FP_MULTIPLY_PRECISE((temp_s0_2 >> temp_s3_2), Math_Cos(temp_v0_3) >> temp_s3_2, Q12_SHIFT);
    sp20.vz <<= temp_s2_2;

    sp20.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        sp20.vx = sp20.vx + D_800C45B0.vx;
        sp30.vx = sp20.vx;
        sp20.vz = sp20.vz + D_800C45B0.vz;
        sp30.vz = sp20.vz;
    }

    func_80069B24(&D_800C4590, &sp20, chara);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        if (D_800C45B0.vx != 0 && (DIFF_SIGN(sp30.vx, D_800C4590.field_0.vx) || abs(sp30.vx) >= ABS(D_800C4590.field_0.vx)))
        {
            sp40.vx = sp30.vx - D_800C4590.field_0.vx;
        }
        else
        {
            sp40.vx = 0;
        }

        if (D_800C45B0.vz != 0 && (DIFF_SIGN(sp30.vz, D_800C4590.field_0.vz) || abs(sp30.vz) >= ABS(D_800C4590.field_0.vz)))
        {
            sp40.vz = sp30.vz - D_800C4590.field_0.vz;
        }
        else
        {
            sp40.vz = 0;
        }

        g_MapOverlayHeader.func_158(-sp40.vx, -sp40.vz);
    }

    chara->position_18.vx += D_800C4590.field_0.vx;
    chara->position_18.vy += D_800C4590.field_0.vy;
    chara->position_18.vz += D_800C4590.field_0.vz;

    if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunForward ||
        g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunRight ||
        g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunLeft)
    {
        chara->properties_E4.player.runTimer_108 += SquareRoot0(SQUARE(D_800C4590.field_0.vx) +
                                                                SQUARE(D_800C4590.field_0.vy) +
                                                                SQUARE(D_800C4590.field_0.vz));
    }
    else
    {
        chara->properties_E4.player.runTimer_108 = 0;
    }

    if (*(u16*)&g_SavegamePtr->mapOverlayId_A4 == 3331)
    {
        D_800C4590.field_C = 0;
    }

    if (D_800C4590.field_14 == 0)
    {
        D_800C4590.field_C = chara->properties_E4.player.positionY_EC;
    }

    if (chara->position_18.vy > D_800C4590.field_C)
    {
        chara->position_18.vy = D_800C4590.field_C;
        chara->field_34       = 0;
    }

    someAngle = FP_ANGLE_NORM_U(ratan2(chara->position_18.vx - D_800C45F8.vx, chara->position_18.vz - D_800C45F8.vz) + FP_ANGLE(360.0f));

    if (!(g_SysWork.player_4C.extra_128.state_1C >= PlayerState_FallForward && g_SysWork.player_4C.extra_128.state_1C < PlayerState_KickEnemy))
    {
        if (!g_Player_IsInWalkToRunTransition)
        {
            posY = chara->position_18.vy;
            if ((D_800C4590.field_C - posY) >= FP_METER(0.65f))
            {
                if (ABS_DIFF(chara->rotation_24.vy, someAngle) >= FP_ANGLE(90.0f) &&
                    ABS_DIFF(chara->rotation_24.vy, someAngle) <  FP_ANGLE(270.0f))
                {
                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_JumpBackward)
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_FallBackward;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.state_2                          = 0;
                        extra->model_0.stateStep_3                      = 0;
                        extra->model_0.state_2                          = 0;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_FallForward;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                }

                g_SysWork.playerCombatInfo_38.isAiming_13 = false;
            }
        }
    }

    chara->properties_E4.player.positionY_EC = D_800C4590.field_C;
    coord->coord.t[0]                        = FP_METER_TO_GEO(chara->position_18.vx);
    coord->coord.t[1]                        = FP_METER_TO_GEO(chara->position_18.vy);
    coord->coord.t[2]                        = FP_METER_TO_GEO(chara->position_18.vz);
}

void Player_ReceiveDamage(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x8007C800
{
    s16 headingAngle;
    u16 enemyRotY;
    s32 i;
    s32 sfx;
    s32 angleState;
    s8  temp_v0_3;

    // Set damage SFX according to something.
    sfx = 1326;
    if (chara->attackReceived_41 != NO_VALUE)
    {
        switch (D_800AD4C8[chara->attackReceived_41].field_11)
        {
            case 2:
                sfx = 1327;
                break;

            case 4:
                sfx = 1328;
                break;

            case 5:
                sfx = 1329;
                break;

            case 0:
                break;
        }
    }

    if (g_Player_DisableControl || g_Player_DisableDamage)
    {
        chara->damageReceived_C0 = FP_HEALTH(0.0f);
        return;
    }

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
        case PlayerState_FallForward:
        case PlayerState_FallBackward:
        case PlayerState_EnemyReleasePinnedFront:
        case PlayerState_EnemyReleasePinnedBack:
        case PlayerState_DamageThrownFront:
        case PlayerState_DamageThrownBack:
        case PlayerState_GetUpFront:
        case PlayerState_GetUpBack:
            break;

        case PlayerState_Death:
        case PlayerState_InstantDeath:
            return;

        // Grab states.
        case PlayerState_EnemyGrabTorsoFront:
        case PlayerState_EnemyGrabTorsoBack:
        case PlayerState_EnemyGrabLegsFront:
        case PlayerState_EnemyGrabLegsBack:
        case PlayerState_EnemyGrabNeckFront:
        case PlayerState_EnemyGrabNeckBack:
        case PlayerState_EnemyGrabPinnedFront:
        case PlayerState_EnemyGrabPinnedBack:
        case PlayerState_OnFloorFront:
        case PlayerState_OnFloorBehind:
            // related to enemy grabbing.
            if (chara->damageReceived_C0 != FP_HEALTH(0.0f) && !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
                func_8005DC1C(sfx, &chara->position_18, FP_VOLUME(0.125f), 0);
                chara->properties_E4.player.field_10C = 0x40;
            }

            if (chara->damageReceived_C0 == FP_HEALTH(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
            }

            func_80089494();
            break;

        case PlayerState_Unk7:
        case PlayerState_EnemyReleaseUpperFront:
        case PlayerState_Unk17:
        case PlayerState_Unk18:
        case PlayerState_DamageHead:
        case PlayerState_EnemyReleaseUpperBack:
        case PlayerState_EnemyReleaseLowerFront:
        case PlayerState_EnemyReleaseLowerBack:
        case PlayerState_DamageTorsoBack:
        case PlayerState_DamageTorsoFront:
        case PlayerState_DamageTorsoRight:
        case PlayerState_DamageTorsoLeft:
        case PlayerState_DamageFeetFront:
        case PlayerState_DamageFeetBack:
        case PlayerState_Unk35:
        case PlayerState_EnemyGrabPinnedFrontStart:
        case PlayerState_EnemyGrabPinnedBackStart:
            chara->field_BC = 0;
            chara->field_B8 = 0;
            chara->field_B4 = 0;

            if (chara->attackReceived_41 == 47)
            {
                g_SysWork.player_4C.chara_0.field_D6            = 0;
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_InstantDeath;
                chara->model_0.stateStep_3                      = 0;
                chara->model_0.state_2                          = 0;
                extra->model_0.stateStep_3                      = 0;
                extra->model_0.state_2                          = 0;
                g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                return;
            }

            if (chara->attackReceived_41 >= 68 &&
                chara->attackReceived_41 <  70)
            {
                chara->damageReceived_C0 = FP_HEALTH(0.0f);
            }
            break;

        default:
            if (g_Player_IsInWalkToRunTransition)
            {
                D_800C4560 = chara->attackReceived_41;
                return;
            }

            if (D_800C4560 != NO_VALUE)
            {
                chara->attackReceived_41 = D_800C4560;
                D_800C4560      = NO_VALUE;
            }

            if (chara->attackReceived_41 <= 0)
            {
                break;
            }

            g_SysWork.enemyTargetIdx_2353                  = NO_VALUE;
            g_SysWork.playerCombatInfo_38.equippedWeapon_F = (g_SavegamePtr->equippedWeapon_AA == InventoryItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA - 0x80);

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                func_8004C564(2, 3);
            }

            if (g_SysWork.player_4C.extra_128.state_1C >= PlayerState_FallForward &&
                g_SysWork.player_4C.extra_128.state_1C <  PlayerState_Unk7)
            {
                g_SysWork.player_4C.chara_0.field_C8         = FP_FLOAT_TO(-25.6f, Q8_SHIFT);
                g_SysWork.player_4C.chara_0.field_CA         = 0;
                g_SysWork.player_4C.chara_0.field_CE         = FP_FLOAT_TO(-17.6f, Q8_SHIFT);
                g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
            }

            enemyRotY = g_SysWork.npcs_1A0[chara->field_40].rotation_24.vy;
            if (chara->attackReceived_41 >= 64 && chara->attackReceived_41 < 66)
            {
                enemyRotY -= FP_FLOAT_TO(4.0f, Q8_SHIFT);
            }
            else if (chara->attackReceived_41 == 69)
            {
                enemyRotY = FP_FLOAT_TO(4.0f, Q8_SHIFT);
            }
            else if (chara->attackReceived_41 == 68)
            {
                enemyRotY = chara->field_B8;
            }

            enemyRotY = FP_ANGLE_NORM_U((enemyRotY - chara->rotation_24.vy) + FP_ANGLE(360.0f));
            temp_v0_3 = chara->attackReceived_41 - 40;
            switch (temp_v0_3)
            {
                case 27:
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk7;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    break;

                case 23:
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0x1800;
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.npcs_1A0[0].rotation_24.vy, &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                    if (enemyRotY >= FP_ANGLE(90.0f) && enemyRotY < FP_ANGLE(270.0f))
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_DamageThrownFront;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.state_2                          = 0;
                        extra->model_0.stateStep_3                      = 0;
                        extra->model_0.state_2                          = 0;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_DamageThrownBack;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.state_2                          = 0;
                        extra->model_0.stateStep_3                      = 0;
                        extra->model_0.state_2                          = 0;
                        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    }
                    break;

                case 20:
                case 22:
                    chara->damageReceived_C0                        = FP_HEALTH(10.0f);
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_DamageHead;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    break;

                case 1:
                case 2:
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_DamageHead;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    break;

                case 9:  // Leg grab.
                case 14: // Romper grab.
                case 16: // Torso grab.
                case 26:
                    if (enemyRotY >= FP_ANGLE(90.0f) &&
                        enemyRotY <  FP_ANGLE(270.0f))
                    {
                        g_SysWork.field_2354[0] = chara->field_40;

                        temp_v0_3 = chara->attackReceived_41 - 45;
                        switch (temp_v0_3)
                        {
                            case 9:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabPinnedFrontStart;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 0:
                            case 11:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabTorsoFront;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 4:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabLegsFront;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 21:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabNeckFront;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                        }
                    }
                    else
                    {
                        g_SysWork.field_2354[1] = chara->field_40;

                        temp_v0_3 = chara->attackReceived_41 - 45;
                        switch (temp_v0_3)
                        {
                            case 9:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabPinnedBackStart;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 0:
                            case 11:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabTorsoBack;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 4:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabLegsBack;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;

                            case 21:
								g_SysWork.player_4C.extra_128.state_1C          = PlayerState_EnemyGrabNeckBack;
								chara->model_0.stateStep_3                      = 0;
								chara->model_0.state_2                          = 0;
								extra->model_0.stateStep_3                      = 0;
								extra->model_0.state_2                          = 0;
								g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
								g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                                break;
                        }
                    }
                    break;

                case 7:
                    chara->health_B0                                = NO_VALUE;
                    chara->field_D6                                 = 0;
                    g_SysWork.player_4C.extra_128.state_1C          = PlayerState_InstantDeath;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    return;

                case 29:
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_FLOAT_TO(1.6f, Q12_SHIFT);
                    Math_ShortestAngleGet(chara->rotation_24.vy, FP_ANGLE(90.0f), &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                case 28:
                    if (chara->attackReceived_41 != 69)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_FLOAT_TO(4.0f, Q12_SHIFT);
                        Math_ShortestAngleGet(chara->rotation_24.vy, (s16)chara->field_B8, &headingAngle);
                        g_Player_HeadingAngle = headingAngle;
                    }

                case 0:
                case 3:
                case 4:
                case 5:
                case 6:
                case 8:
                case 10:
                case 12:
                case 17:
                case 18:
                case 19:
                case 21:
                case 24:
                case 25:
                    // Harm animations.
                    if (enemyRotY >= FP_ANGLE(45.0f) && enemyRotY < FP_ANGLE(135.0f))
                    {
                        angleState = PlayerState_DamageTorsoLeft; // Left harm animation.
                    }
                    else if (enemyRotY >= FP_ANGLE(135.0f) && enemyRotY < FP_ANGLE(225.0f))
                    {
                        angleState = PlayerState_DamageTorsoFront; // Front harm animation.
                    }
                    else if (enemyRotY >= FP_ANGLE(225.0f) && enemyRotY < FP_ANGLE(315.0f))
                    {
                        angleState = PlayerState_DamageTorsoRight; // Right harm animation.
                    }
                    else
                    {
                        angleState = PlayerState_DamageTorsoBack; // Back harm animation.
                    }

                    g_SysWork.player_4C.extra_128.state_1C          = angleState;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    break;

                case 13:
                    if (enemyRotY < FP_ANGLE(179.95f))
                    {
                        angleState = PlayerState_DamageFeetFront;
                    }
                    else
                    {
                        angleState = PlayerState_DamageFeetBack;
                    }

                    g_SysWork.player_4C.extra_128.state_1C          = angleState;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.state_2                          = 0;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.state_2                          = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    break;
            }

            if ((u32)g_SysWork.player_4C.extra_128.state_1C >= PlayerState_FallForward)
            {
                chara->properties_E4.player.afkTimer_E8                     = 0;
                chara->properties_E4.player.field_F4                        = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                g_SysWork.playerCombatInfo_38.isAiming_13                   = false;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->field_44                                             = NO_VALUE;
            }
            break;
    }

    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Death)
    {
        chara->damageReceived_C0 = FP_HEALTH(0.0f);
        chara->field_BC          = 0;
        chara->field_B8          = 0;
        chara->field_B4          = 0;
        return;
    }

    if (chara->damageReceived_C0 != FP_HEALTH(0.0f))
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
        if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived))
        {
            func_8005DC1C(sfx, &chara->position_18, FP_VOLUME(0.125f), 0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
            chara->properties_E4.player.field_10C = 0x40;
        }

        if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
        {
            chara->health_B0 -= chara->damageReceived_C0 * 2;
        }
        else
        {
            switch (g_SavegamePtr->gameDifficulty_260)
            {
                case GameDifficulty_Easy:
                    chara->damageReceived_C0 = (chara->damageReceived_C0 * 3) >> 2;
                    break;

                case GameDifficulty_Hard:
                    chara->damageReceived_C0 = (chara->damageReceived_C0 * 6) >> 2;
                    break;
            }

            chara->health_B0 -= chara->damageReceived_C0;
        }

        if (chara->health_B0 < FP_HEALTH(0.0f))
        {
            chara->health_B0 = NO_VALUE;
            D_800C4561       = 1;
        }

        func_800893D0(chara->damageReceived_C0);
        chara->damageReceived_C0 = FP_HEALTH(0.0f);
    }

    if (chara->health_B0 <= FP_HEALTH(0.0f) && g_SysWork.player_4C.extra_128.state_1C != PlayerState_Death &&
        g_SysWork.player_4C.extra_128.state_1C != PlayerState_Unk36 && g_SysWork.player_4C.extra_128.state_1C != PlayerState_EnemyGrabPinnedFront &&
        g_SysWork.player_4C.extra_128.state_1C != PlayerState_EnemyGrabPinnedBack && g_SysWork.player_4C.extra_128.state_1C != PlayerState_OnFloorFront &&
        g_SysWork.player_4C.extra_128.state_1C != PlayerState_OnFloorBehind && !g_Player_IsInWalkToRunTransition)
    {
        chara->field_40                     = NO_VALUE;
        g_SavegamePtr->healthSaturation_238 = FP_HEALTH(0.0f);

        for (i = 0; i < 4; i++)
        {
            g_SysWork.field_2354[i] = NO_VALUE;
        }

        if (chara->attackReceived_41 == 66)
        {
            g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk36;
            chara->model_0.stateStep_3                      = 0;
            chara->model_0.state_2                          = 0;
            extra->model_0.stateStep_3                      = 0;
            extra->model_0.state_2                          = 0;
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
        }
        else
        {
            g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Death;
            chara->model_0.stateStep_3                      = 0;
            chara->model_0.state_2                          = 0;
            extra->model_0.stateStep_3                      = 0;
            extra->model_0.state_2                          = 0;
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
        }
    }
}

void func_8007D090(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord) // 0x8007D090
{
    s32 temp_a1_3;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
        case PlayerState_Combat:
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case EquippedWeaponId_Handgun:
                    var_a2 = 20;
                    var_a3 = 2;
                    break;

                case EquippedWeaponId_HuntingRifle:
                    var_a2 = 18;
                    var_a3 = 6;
                    break;

                case EquippedWeaponId_Shotgun:
                    var_a2 = 26;
                    var_a3 = 3;
                    break;

                case EquippedWeaponId_HyperBlaster:
                    var_a2 = 30;
                    var_a3 = 0;
                    break;

                default:
                    var_a2 = 12;
                    var_a3 = 6;
                    break;
            }

            if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Reload || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                D_800AF212 = 0;
                D_800AF210 = 0;
            }
            else
            {
                D_800AF212 = g_SysWork.player_4C.chara_0.properties_E4.npc.field_122 - (1 << 10);

                if (ABS(chara->rotation_24.pad - chara->rotation_24.vy) > FP_ANGLE(180.0f))
                {
                    if (chara->rotation_24.pad > chara->rotation_24.vy)
                    {
                        D_800AF210 = -FP_ANGLE_NORM_U((chara->rotation_24.vy + FP_ANGLE(360.0f)) - chara->rotation_24.pad);
                    }
                    else
                    {
                        D_800AF210 = FP_ANGLE_NORM_U((chara->rotation_24.pad + FP_ANGLE(360.0f)) - chara->rotation_24.vy);
                    }
                }
                else
                {
                    D_800AF210 = chara->rotation_24.pad - chara->rotation_24.vy;
                }

                if (chara->properties_E4.player.field_100 != 0 || g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock ||
                    g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimTargetLockSwitch)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & (1 << 8))
                    {
                        var_v1 = 0;
                    }
                    else
                    {
                        var_v1 = var_a3;
                    }

                    if (chara->properties_E4.player.field_F4 != 0)
                    {
                        temp_a1_3 = chara->properties_E4.player.field_F4 - D_800AF212;
                        if (D_800AF212 < chara->properties_E4.player.field_F4)
                        {
                            var_a0 = chara->properties_E4.player.field_100 * (((var_a2 + chara->properties_E4.player.field_100) * g_DeltaTime0) / 136);
                            if (var_a0 < temp_a1_3)
                            {
                                D_800AF212 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0] - var_a0;
                            }
                        }
                        else
                        {
                            var_a0 = -(chara->properties_E4.player.field_100 * (((var_a2 + chara->properties_E4.player.field_100) * g_DeltaTime0) / 136));
                            if (temp_a1_3 < var_a0)
                            {
                                D_800AF212 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0] - var_a0;
                            }
                        }
                    }
                    else
                    {
                        if (chara->properties_E4.player.field_100 < var_v1)
                        {
                            D_800AF210 = 0;
                            D_800AF212 = 0;
                        }
                        else
                        {
                            temp_v0   = chara->properties_E4.player.field_100 + 1;
                            temp_a1_3 = temp_v0 - var_v1;
                            var_a0    = 4;
                            var_a0    = temp_a1_3 * (((var_a2 + ((temp_a1_3 * 2) + var_a0)) * g_DeltaTime0) / 136);

                            if (D_800AF212 > 0)
                            {
                                if (var_a0 < D_800AF212)
                                {
                                    D_800AF212 = var_a0;
                                }
                            }
                            else if (D_800AF212 < 0)
                            {
                                if (D_800AF212 < -var_a0)
                                {
                                    D_800AF212 = -var_a0;
                                }
                            }

                            if (D_800AF210 > 0)
                            {
                                if (var_a0 < D_800AF210)
                                {
                                    D_800AF210 = var_a0;
                                }
                            }
                            else if (D_800AF210 < 0)
                            {
                                if (D_800AF210 < -var_a0)
                                {
                                    D_800AF210 = -var_a0;
                                }
                            }
                        }
                    }
                }

                D_800AF212 = CLAMP(D_800AF212, FP_ANGLE(-56.25), FP_ANGLE(56.25));
                D_800AF210 = CLAMP(D_800AF210, FP_ANGLE(-33.75f), FP_ANGLE(33.75f));

                func_80044F14(&coord[1], 0, D_800AF212 >> 1, D_800AF210);
                shRotMatrixZ(D_800AF212 >> 1, &coord[4].coord);
                shRotMatrixZ(D_800AF212 >> 1, &coord[8].coord);
            }
            break;

        case PlayerState_None:
            if (D_800AF212 > 0)
            {
                D_800AF212 -= 0x20;
            }
            else if (D_800AF212 < 0)
            {
                D_800AF212 += 0x20;
            }

            temp_a1_3 = Math_UnkDistTimeCalc(24);

            if (D_800AF212 > 0)
            {
                D_800AF212 -= temp_a1_3;
                if (D_800AF212 < 0)
                {
                    D_800AF212 = 0;
                }
            }
            else if (D_800AF212 < 0)
            {
                D_800AF212 += temp_a1_3;
                if (D_800AF212 > 0)
                {
                    D_800AF212 = 0;
                }
            }

            if (D_800AF210 > 0)
            {
                D_800AF210 -= temp_a1_3;
                if (D_800AF210 < 0)
                {
                    D_800AF210 = 0;
                }
            }
            else if (D_800AF210 < 0)
            {
                D_800AF210 += temp_a1_3;
                if (D_800AF210 > 0)
                {
                    D_800AF210 = 0;
                }
            }

            func_80044F14(&coord[1], 0, D_800AF212 >> 1, D_800AF210);
            shRotMatrixZ(D_800AF212 >> 1, &coord[4].coord);
            shRotMatrixZ(D_800AF212 >> 1, &coord[8].coord);
            break;

        case PlayerState_Unk180:
            if (D_800AF210 != 0)
            {
                func_80044F14(&coord[1], 0, 0,     0xC0);
                func_80044F14(&coord[2], 0, 0x140, 0xE0);
            }
            break;

        default:
            if (g_SysWork.player_4C.extra_128.state_1C >= PlayerState_Unk52 &&
                g_SysWork.player_4C.extra_128.state_1C <  PlayerState_Unk59)
            {
                func_80044F14(&coord[2], 0, 0, D_800AF210);
            }
            else
            {
                D_800AF210 = 0;
                D_800AF212 = 0;
            }
            break;
    }

    if (g_SysWork.field_2358 != 0 && g_SysWork.player_4C.extra_128.state_1C < PlayerState_Unk58)
    {
        func_80044F14(&g_SysWork.playerBoneCoords_890[PlayerBone_RightUpperArm], 0, 0x2D0, -0x64);
        func_80044F14(&g_SysWork.playerBoneCoords_890[PlayerBone_RightForearm], -0xA0, 0x100, -0x15E);
        func_80044F14(&g_SysWork.playerBoneCoords_890[PlayerBone_RightHand], 0x96, 0, 0);
    }
}

void func_8007D6E0() // 0x8007D6E0
{
    D_800AF210 = 1;
}

s32 func_8007D6F0(s_SubCharacter* chara, s_800C45C8* arg1) // 0x8007D6F0
{
    s_func_800700F8_2 sp10[2];
    VECTOR3           vecs[4];
    bool              ret[2];
    s32               temp_lo;
    s32               temp_s0;
    s32               temp_s1;
    s32               temp_s3;
    s32               temp_s4;
    s32               temp_s5;
    s16               angle;
    u16               angleDelta;

    temp_s0  = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 3;
    temp_s0 += FP_METER(0.75f);
    temp_s1  = FP_METER(-0.6f);
    temp_s1 -= g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >> 4;

    temp_s4 = FP_MULTIPLY(Math_Cos(chara->headingAngle_3C), FP_METER(0.2f), Q12_SHIFT); // Maybe meters?
    temp_s3 = FP_MULTIPLY(Math_Sin(chara->headingAngle_3C), FP_METER(0.2f), Q12_SHIFT); // Maybe meters?
    temp_s5 = FP_MULTIPLY(temp_s0, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
    temp_lo = FP_MULTIPLY(temp_s0, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

    temp_s1 -= FP_METER(0.4f);

    vecs[0].vy = chara->position_18.vy + temp_s1;
    vecs[0].vx = (chara->position_18.vx + temp_s4) + temp_s5;

    vecs[0].vz = (chara->position_18.vz - temp_s3) + temp_lo;
    vecs[2].vy = chara->position_18.vy - FP_METER(0.4f);
    vecs[2].vx = chara->position_18.vx + temp_s4;
    vecs[2].vz = chara->position_18.vz - temp_s3;

    ret[0] = func_8006D90C(&sp10[0], &vecs[2], &vecs[0]);

    if (ret[0])
    {
        vecs[1].vy = vecs[0].vy;
        vecs[1].vx = (chara->position_18.vx - temp_s4) + temp_s5;
        vecs[1].vz = (chara->position_18.vz + temp_s3) + temp_lo;
        vecs[3].vy = vecs[2].vy;
        vecs[3].vx = chara->position_18.vx - temp_s4;
        vecs[3].vz = chara->position_18.vz + temp_s3;

        ret[1] = func_8006D90C(&sp10[1], &vecs[3], &vecs[1]);

        if (ret[1])
        {
            arg1->field_14 = (sp10[0].field_14 + sp10[1].field_14) >> 1;
            arg1->field_1  = sp10[0].field_1;

            angle      = FP_ANGLE_NORM_U(((sp10[0].field_1C + sp10[1].field_1C) >> 1) + FP_ANGLE(360.0f));
            angleDelta = ABS_DIFF(angle, chara->headingAngle_3C);

            if (angleDelta > FP_ANGLE(160.0f) && angleDelta < FP_ANGLE(200.0f))
            {
                if ((chara->position_18.vy - FP_METER(1.3f)) < sp10[0].field_18 || sp10[0].field_1 == 0 || sp10[0].field_1 == 12)
                {
                    if ((chara->position_18.vy - FP_METER(0.3f)) >= sp10[0].field_18)
                    {
                        return PlayerLowerBodyState_RunForward;
                    }
                }
                else
                {
                    return PlayerLowerBodyState_WalkForward;
                }
            }
        }
    }

    return PlayerLowerBodyState_None;
}

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x8007D970
{
    VECTOR  sp20;
    VECTOR  sp30;
    VECTOR  sp40;
    MATRIX  sp50;
    VECTOR  sp70;
    VECTOR  sp80;
    SVECTOR sp90;
    DVECTOR sp98;
    s32      temp_s0;
    s32      temp_v0_5;
    s32      temp_v0_6;
    s16      var_a1;
    VECTOR*  vec;
    VECTOR*  vec2;
    VECTOR*  vec3;
    s_Model* model;

    model = &g_SysWork.player_4C.extra_128.model_0;

    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
    {
        vec     = &g_SysWork.playerCombatInfo_38.field_0;
        vec->vx = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[0] * 16;
        vec->vy = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[1] * 16;
        vec->vz = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[2] * 16;
    }
    else
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case NO_VALUE:
            case 8:
            case 9:
                vec2     = &g_SysWork.playerCombatInfo_38.field_0;
                vec2->vx = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[0] * 16;
                vec2->vy = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[1] * 16;
                vec2->vz = g_SysWork.playerBoneCoords_890[PlayerBone_RightFoot].workm.t[2] * 16;
                break;

            default:
                vec3     = &g_SysWork.playerCombatInfo_38.field_0;
                vec3->vx = g_SysWork.playerBoneCoords_890[PlayerBone_RightHand].workm.t[0] * 16;
                vec3->vy = g_SysWork.playerBoneCoords_890[PlayerBone_RightHand].workm.t[1] * 16;
                vec3->vz = g_SysWork.playerBoneCoords_890[PlayerBone_RightHand].workm.t[2] * 16;
                break;
        }
    }

    if (g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 != FP_TIME(0.0f))
    {
        g_SysWork.timer_2C++;

        if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 >= FP_METER(3.1739) || (g_SysWork.timer_2C & (1 << 0)))
        {
            func_8006342C(g_SavegamePtr->equippedWeapon_AA - InventoryItemId_KitchenKnife, 0, 0, coord);
        }
    }

    if (!(g_SysWork.player_4C.extra_128.state_1C >= PlayerState_Unk7 && g_SysWork.player_4C.extra_128.state_1C < PlayerState_Unk51) &&
        ((u32)g_SysWork.player_4C.extra_128.state_1C < PlayerState_Idle || g_SysWork.player_4C.extra_128.state_1C == PlayerState_KickEnemy || g_SysWork.player_4C.extra_128.state_1C == PlayerState_StompEnemy))
    {
        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun && g_SysWork.player_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim)
        {
            if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat && D_800AF21C != NO_VALUE)
            {
                sp98.vx = ratan2((g_SysWork.npcs_1A0[D_800AF21C].position_18.vx + g_SysWork.npcs_1A0[D_800AF21C].field_D8.field_0) - g_SysWork.playerCombatInfo_38.field_0.vx,
                                 (g_SysWork.npcs_1A0[D_800AF21C].position_18.vz + g_SysWork.npcs_1A0[D_800AF21C].field_D8.field_2) - g_SysWork.playerCombatInfo_38.field_0.vz);
            }
            else
            {
                // HACK: Required for match.
                do { chara->rotation_24.pad = chara->rotation_24.vy; } while (0);

                sp98.vx = chara->rotation_24.pad;
            }

            sp98.vy = g_SysWork.player_4C.chara_0.properties_E4.player.field_122;
            var_a1  = sp98.vy;

            if (var_a1 >= 0x180)
            {
                if (var_a1 > 0x680)
                {
                    var_a1 = 0x680;
                }
            }
            else
            {
                var_a1 = 0x180;
            }

            if (chara->field_44 > 0)
            {
                func_8006342C(g_SysWork.playerCombatInfo_38.equippedWeapon_F, var_a1, sp98.vx, coord);
            }
        }
        else
        {
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case NO_VALUE:
                case EquippedWeaponId_Unk8:
                case EquippedWeaponId_Unk9:
                    *(u32*)&sp90 = 0x3C0000;
                    sp90.vz      = 0x86;
                    Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    break;

                default:
                    if (g_SysWork.player_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
                    {
                        *(u32*)&sp90 = 0x3C0000;
                        sp90.vz      = 0x86;
                        Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    }
                    else
                    {
                        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10)
                        {
                            case EquippedWeaponId_KitchenKnife:
                                *(u32*)&sp90 = (FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x4B, Q12_SHIFT - 1)) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x4B, Q12_SHIFT) >> 1;
                                break;

                            case EquippedWeaponId_SteelPipe:
                                *(u32*)&sp90 = (FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xE1, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT - 2);
                                break;

                            case EquippedWeaponId_Chainsaw:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x87, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x1EF, Q12_SHIFT) >> 1;
                                break;

                            case EquippedWeaponId_RockDrill:
                                *(u32*)&sp90 = (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT)) << 16);
                                sp90.vz          = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT - 2);
                                break;

                            case EquippedWeaponId_Axe:
                                *(u32*)&sp90 = (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2C1, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY((u32)D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xC3, Q12_SHIFT);
                                break;

                            case EquippedWeaponId_Hammer:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x69, Q12_SHIFT)) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x13B, Q12_SHIFT) >> 1;
                                break;

                            case EquippedWeaponId_Katana:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x13B, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT);
                                break;
                        }

                        Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                    }
                    break;
            }

            gte_SetRotMatrix(&sp50);
            gte_SetTransMatrix(&sp50);
            gte_ldv0(&sp90);
            gte_rt();
            gte_stlvnl(&sp70);

            temp_v0_5 = FP_METER_TO_GEO(g_SysWork.playerCombatInfo_38.field_0.vx) - sp70.vx;
            temp_v0_6 = FP_METER_TO_GEO(g_SysWork.playerCombatInfo_38.field_0.vz) - sp70.vz;
            temp_s0   = SquareRoot0(SQUARE(temp_v0_5) + SQUARE(temp_v0_6));

            sp98.vx = ratan2(sp70.vx - FP_METER_TO_GEO(g_SysWork.playerCombatInfo_38.field_0.vx),
                             sp70.vz - FP_METER_TO_GEO(g_SysWork.playerCombatInfo_38.field_0.vz));
            sp98.vy = ratan2(temp_s0, sp70.vy - FP_METER_TO_GEO(g_SysWork.playerCombatInfo_38.field_0.vy));
        }

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HyperBlaster &&
            g_SysWork.playerCombatInfo_38.isAiming_13 &&
            model->anim_4.status_0 >= ANIM_STATUS(PlayerAnim_IdleAim, true) && model->anim_4.keyframeIdx0_8 >= 574)
        {
            if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_Idle)
            {
                if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_None && g_SysWork.enemyTargetIdx_2353 != NO_VALUE)
                {
                    g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
                }

                *(u32*)&sp90 = 0xFFD90000;
                sp90.vz      = 87;

                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp20.vx = sp80.vx * 16;
                sp20.vy = sp80.vy * 16;
                sp20.vz = sp80.vz * 16;

                if (g_GameWork.config_0.optExtraAutoAiming_2C != 0)
                {
                    sp98.vx = chara->rotation_24.pad;
                }

                g_MapOverlayHeader.func_178(&sp20.vx, &sp98.vx, &sp98.vy);
            }
        }

        if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_Idle)
        {
            if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw &&
                 model->anim_4.keyframeIdx0_8 >= 572 && model->anim_4.keyframeIdx0_8 <  584) ||
                (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill &&
                 chara->model_0.anim_4.keyframeIdx0_8 >= 577 && model->anim_4.keyframeIdx0_8 <  583))
            {
                *(u32*)&sp90 = 0;
                sp90.vz      = 0;

                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                *(u32*)&sp90 = 0;
                sp90.vz      = 0;
                sp30.vx      = sp80.vx * 16;
                sp30.vy      = sp80.vy * 16;
                sp30.vz      = sp80.vz * 16;

                Vw_CoordHierarchyMatrixCompute(&coord[6], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp40.vx = sp80.vx * 16;
                sp40.vy = sp80.vy * 16;
                sp40.vz = sp80.vz * 16;
                g_MapOverlayHeader.func_17C(&sp30.vx, &sp40.vx);
            }
        }

        if (g_SysWork.player_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
        {
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                if (D_800C4554 != NO_VALUE || D_800C4556 != D_800C4554)
                {
                    func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &D_800C44E0, g_SysWork.npcs_1A0, D_800C4556, D_800C4554);
                }
                else
                {
                    func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &D_800C44E0, g_SysWork.npcs_1A0, sp98.vx, sp98.vy);
                }
            }
            else
            {
                func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &g_SysWork.playerCombatInfo_38, g_SysWork.npcs_1A0, sp98.vx, sp98.vy);
            }

            D_800C42D2 = sp98.vx;
            D_800C42D0 = sp98.vy;
        }
    }

    D_800C44E0.field_0 = g_SysWork.playerCombatInfo_38.field_0;
}

void Game_SavegameResetPlayer() // 0x8007E530
{
    #define DEFAULT_INV_SLOT_COUNT 8

    s32 i;

    g_SavegamePtr->inventorySlotCount_AB = DEFAULT_INV_SLOT_COUNT;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        g_SavegamePtr->items_0[i].id_0    = NO_VALUE;
        g_SavegamePtr->items_0[i].count_1 = 0;
    }

    g_SavegamePtr->playerHealth_240      = FP_HEALTH(100.0f);
    g_SavegamePtr->field_A0              = 0;
    g_SavegamePtr->equippedWeapon_AA     = InventoryItemId_Unequipped;
    g_SavegamePtr->healthSaturation_238  = FP_HEALTH(0.0f);
    g_SavegamePtr->gameplayTimer_250     = 0;
    g_SavegamePtr->runDistance_254       = 0;
    g_SavegamePtr->walkDistance_258      = 0;
    g_SavegamePtr->pickedUpItemCount_23C = 0;
    g_SavegamePtr->clearGameCount_24A    = 0;
    g_SavegamePtr->add290Hours_25C_1     = 0;
}

void func_8007E5AC() // 0x8007E5AC
{
    s32      i;
    u32      temp_t0;
    s_Model* model;
    s_Model* extraModel;

    SysWork_SavegameReadPlayer();

    g_SysWork.player_4C.chara_0.model_0.charaId_0   = Chara_Hero;
    g_SysWork.player_4C.extra_128.model_0.charaId_0 = Chara_Hero;
    g_SysWork.player_4C.chara_0.field_D4            = 0x4CC;
    g_SysWork.player_4C.chara_0.field_D6            = 0x3AE;

    extraModel = &g_SysWork.player_4C.chara_0.model_0;
    model      = &g_SysWork.player_4C.extra_128.model_0;

    g_SysWork.field_2358 = 0;

    extraModel->anim_4.flags_2 |= AnimFlag_Unk1 | AnimFlag_Visible;
    model->anim_4.flags_2      |= AnimFlag_Unk1 | AnimFlag_Visible;

    g_SysWork.player_4C.chara_0.field_E0_8 = 3;
    g_Inventory_EquippedItem               = g_SavegamePtr->equippedWeapon_AA;

    temp_t0 = g_SavegamePtr->equippedWeapon_AA >> 5;

    if (temp_t0 >= 4 && temp_t0 < 6)
    {
        for (i = 0; g_SavegamePtr->items_0[i].id_0 != g_SavegamePtr->equippedWeapon_AA && i < INVENTORY_ITEM_COUNT_MAX; i++);

        g_SysWork.playerCombatInfo_38.equippedWeapon_F     = g_SavegamePtr->equippedWeapon_AA + InventoryItemId_KitchenKnife;
        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = g_SavegamePtr->items_0[i].count_1;
        g_SysWork.playerCombatInfo_38.field_12             = i;

        if (temp_t0 == 4)
        {
            g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = 0;
        }
        else
        {
            for (i = 0; g_SavegamePtr->items_0[i].id_0 != (g_SavegamePtr->equippedWeapon_AA + InventoryItemId_HealthDrink) && i < INVENTORY_ITEM_COUNT_MAX; i++);

            if (i == INVENTORY_ITEM_COUNT_MAX)
            {
                g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = 0;
            }
            else
            {
                g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = (s8)g_SavegamePtr->items_0[i].count_1;
            }
        }
    }
    else
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F     = NO_VALUE;
        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = 0;
        g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = 0;
        g_SysWork.playerCombatInfo_38.field_12             = NO_VALUE;
    }

    g_SysWork.playerCombatInfo_38.isAiming_13 = false;
    g_Player_GrabFree_InputCount              = 0;
    D_800C4588                                = 0;
    D_800C457C                                = 0;
    g_Player_DisableControl                   = false;

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            D_800C45EC = FP_FLOAT_TO(5.0f, Q12_SHIFT);
            break;

        case GameDifficulty_Normal:
            D_800C45EC = FP_FLOAT_TO(2.5f, Q12_SHIFT);
            break;

        case GameDifficulty_Hard:
            D_800C45EC = FP_FLOAT_TO(1.8f, Q12_SHIFT);
            break;
    }

    D_800AF224                = NO_VALUE;
    g_GameWork.mapAnimIdx_5B1 = NO_VALUE;

    g_SavegamePtr->inventorySlotCount_AB  = CLAMP(g_SavegamePtr->inventorySlotCount_AB, INVENTORY_ITEM_COUNT_MAX / 5, INVENTORY_ITEM_COUNT_MAX);
    g_SysWork.player_4C.chara_0.health_B0 = CLAMP(g_SysWork.player_4C.chara_0.health_B0, 1, FP_HEALTH(100.0f));
}

void func_8007E860() // 0x8007E860
{
    s32 i;
    s32 startIdx;

    for (i = 0; i < 8; i++)
    {
        startIdx                         = 92;
        g_MaybePlayerAnims[startIdx + i] = g_MapOverlayHeader.animInfos_34[i + 16];
    }
}

// TODO: Matched with displaced instruction.
// Scratch: https://decomp.me/scratch/uu71G
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_8007E8C0); // 0x8007E8C0

void func_8007E9C4() // 0x8007E9C4
{
    s_SubCharacter* chara;

    chara = &g_SysWork.player_4C.chara_0;

    g_Player_IsInWalkToRunTransition                  = false;
    g_SysWork.player_4C.extra_128.state_1C            = PlayerState_None;
    g_SysWork.player_4C.extra_128.upperBodyState_20   = PlayerUpperBodyState_None;
	g_SysWork.player_4C.extra_128.lowerBodyState_24   = PlayerLowerBodyState_None;
    g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
    g_SysWork.player_4C.extra_128.model_0.state_2     = 0;

    chara->model_0.stateStep_3                = 0;
    chara->model_0.state_2                    = 0;
    g_SysWork.field_235A                      = 0;
    D_800AF210                                = 0;
    D_800AF212                                = 0;
    D_800C4560                                = NO_VALUE;
    g_SysWork.playerCombatInfo_38.isAiming_13 = false;

    func_8004C564(0, NO_VALUE);

    chara->rotation_24.pad         = FP_ANGLE(90.0f);
    D_800C4561                     = 0;
    g_Player_DisableDamage         = false;
    g_Player_ActionRunPressed      = false;
    g_Player_MovementInputDetected = false;
    g_Player_IsShooting            = false;
    g_Player_IsAttacking           = false;

    chara->properties_E4.player.afkTimer_E8                    = FP_TIME(0.0f);
    chara->properties_E4.player.field_F4                       = 0;
    chara->properties_E4.player.runTimer_F8                    = 0;
    chara->properties_E4.player.field_100                      = 0;
    chara->properties_E4.player.field_104                      = 0;
    chara->properties_E4.player.runTimer_108                   = 0;
    chara->properties_E4.larvalStalker.properties_E8[10].val32 = 0;
    chara->properties_E4.player.flags_11C                      = 0;
    chara->properties_E4.player.playerMoveDistance_126         = 0;

    chara->damageReceived_C0 = FP_HEALTH(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    g_Player_IsHoldAttack         = false;
    chara->flags_3E              &= ~(1 << 3);
    D_800C45F8                    = chara->position_18;
    g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
    chara->field_40               = NO_VALUE;
    chara->attackReceived_41      = NO_VALUE;

    g_SysWork.field_2354[3] = NO_VALUE;
    g_SysWork.field_2354[2] = NO_VALUE;
    g_SysWork.field_2354[1] = NO_VALUE;
    g_SysWork.field_2354[0] = NO_VALUE;
    chara->field_D6         = 0x3AE;

    g_Player_IsAiming              = false;
    g_Player_IsRunning             = false;
    g_Player_IsMovingBackward      = false;
    g_Player_IsMovingForward       = false;
    g_Player_IsSteppingRightTap    = false;
    g_Player_IsSteppingRightHold   = false;
    g_Player_IsTurningRight        = false;
    g_Player_IsSteppingLeftTap     = false;
    g_Player_IsSteppingLeftHold    = false;
    g_Player_IsTurningLeft         = false;
}

void GameFs_PlayerMapAnimLoad(s32 mapIdx) // 0x8007EB64
{
    #define BASE_FILE_IDX FILE_ANIM_HB_M0S00_ANM

    if (g_GameWork.mapAnimIdx_5B1 != mapIdx ||
        mapIdx == (FILE_ANIM_HB_M6S04_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S01_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S02_ANM - BASE_FILE_IDX))
    {
        g_GameWork.mapAnimIdx_5B1 = mapIdx;
        Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, FS_BUFFER_4);
    }
}

void func_8007EBBC() // 0x8007EBBC
{
    s32 var_a1;
    s32 var_a2;
    s32 i;
    s8  temp_v1;

    var_a1 = 0;
    var_a2 = 0;

    g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
    temp_v1                       = g_SysWork.playerCombatInfo_38.equippedWeapon_F + 1;

    switch (temp_v1)
    {
        case 0:
            g_Player_EquippedWeaponInfo = D_800AFBF4[0];
            return;

        case 1:
            var_a1                               = 30;
            var_a2                               = 15;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[1];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1030;
            break;

        default:
            return;

        case 8:
            var_a1                               = 0;
            var_a2                               = 0;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[3];
            g_SysWork.player_4C.chara_0.field_D0 = -0xFD0;
            break;

        case 2:
        case 5:
            g_Player_EquippedWeaponInfo = D_800AFBF4[2];
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case EquippedWeaponId_Hammer:
                    var_a1 = 10;
                    var_a2 = 5;
                    break;

                case EquippedWeaponId_SteelPipe:
                    var_a1 = 20;
                    var_a2 = 10;
                    break;
            }

            g_SysWork.player_4C.chara_0.field_D0 = -0xEC0;
            break;

        case 6:
            var_a1                               = 50;
            var_a2                               = 25;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[4];
            g_SysWork.player_4C.chara_0.field_D0 = -0xE90;
            break;

        case 3:
            var_a1                               = 64;
            var_a2                               = 32;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[5];
            g_SysWork.player_4C.chara_0.field_D0 = -0x12E0;
            break;

        case 7:
            var_a1                               = 40;
            var_a2                               = 20;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[10];
            g_SysWork.player_4C.chara_0.field_D0 = -0xF20;
            break;

        case 33:
            var_a1                               = 78;
            var_a2                               = 39;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[6];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1600;
            break;

        case 34:
            var_a1                               = 96;
            var_a2                               = 48;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[7];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1180;
            break;

        case 35:
            var_a1                               = 114;
            var_a2                               = 57;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[8];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1600;
            break;

        case 36:
            var_a1                               = 132;
            var_a2                               = 66;
            g_Player_EquippedWeaponInfo          = D_800AFBF4[9];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1610;
            break;
    }

    for (i = 56; i < 76; i++)
    {
        g_MaybePlayerAnims[i] = D_80028B94[(i - 56) + var_a1];
    }

    for (i = 0; i < 10; i++)
    {
        D_800C44F0[i] = D_800294F4[i + var_a2];
    }

    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE && D_800AF224 != g_SysWork.playerCombatInfo_38.equippedWeapon_F)
    {
        D_800AF224 = g_SysWork.playerCombatInfo_38.equippedWeapon_F;
        func_8007F14C(g_SysWork.playerCombatInfo_38.equippedWeapon_F);

        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case EquippedWeaponId_KitchenKnife:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP3_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_Axe:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP1_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_SteelPipe:
            case EquippedWeaponId_Hammer:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP2_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_Chainsaw:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP6_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_RockDrill:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP8_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_Katana:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP9_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_Handgun:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP4_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_HuntingRifle:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP51_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_Shotgun:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP52_ANM, FS_BUFFER_12);
                break;

            case EquippedWeaponId_HyperBlaster:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP53_ANM, FS_BUFFER_12);
                break;
        }
    }
}

void func_8007F14C(u8 arg0) // 0x8007F14C
{
    switch (arg0)
    {
        case 0:
        case 1:
        case 4:
        case 6:
        case 7:
            Sd_EngineCmd(164);
            break;

        case 5:
            Sd_EngineCmd(169);
            break;

        case 2:
            Sd_EngineCmd(163);
            break;

        case 32:
            Sd_EngineCmd(166);
            break;

        case 33:
            Sd_EngineCmd(167);
            break;

        case 34:
            Sd_EngineCmd(168);
            break;

        case 35:
            Sd_EngineCmd(165);
            break;
    }
}

void Game_PlayerMovementsReset() // 0x8007F1CC
{
    g_Player_ActionRunPressed        = false;
    g_Player_MovementInputDetected   = false;
    g_Player_IsShooting              = false;
    g_Player_IsAttacking             = false;
    g_Player_IsHoldAttack            = false;
    g_Player_IsAiming                = false;
    g_Player_IsRunning               = false;
    g_Player_IsMovingBackward        = false;
    g_Player_IsMovingForward         = false;
    g_Player_IsSteppingRightTap      = false;
    g_Player_IsSteppingRightHold     = false;
    g_Player_IsTurningRight          = false;
    g_Player_IsSteppingLeftTap       = false;
    g_Player_IsSteppingLeftHold      = false;
    g_Player_IsTurningLeft           = false;
    g_Player_IsInWalkToRunTransition = false;
}

void func_8007F250(u8* ptr, s8 disableDamage) // 0x8007F250
{
    *ptr                   = D_800C4561;
    g_Player_DisableDamage = disableDamage;
}

bool func_8007F26C() // 0x8007F26C
{
    if (g_SysWork.player_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack ||
        g_SysWork.player_4C.extra_128.state_1C == PlayerState_KickEnemy ||
        g_SysWork.player_4C.extra_128.state_1C == PlayerState_StompEnemy)
    {
        return true;
    }

    return false;
}

bool func_8007F2AC() // 0x8007F2AC
{
    if (g_SysWork.player_4C.chara_0.health_B0 <= FP_HEALTH(0.0f) ||
        g_SysWork.playerCombatInfo_38.isAiming_13 ||
        g_SysWork.player_4C.extra_128.state_1C == PlayerState_KickEnemy ||
        g_SysWork.player_4C.extra_128.state_1C == PlayerState_StompEnemy ||
        (g_SysWork.player_4C.extra_128.state_1C >= PlayerState_Unk7 &&
         g_SysWork.player_4C.extra_128.state_1C <= PlayerState_GetUpBack))
    {
        return true;
    }

    return false;
}

s16 Player_AnimGetSomething() // 0x8007F308
{
    return g_MaybePlayerAnims[g_SysWork.player_4C.chara_0.model_0.anim_4.status_0].keyframeIdx0_C;
}

void Player_Controller() // 0x8007F32C
{
    s32 attackBtnInput;

    g_Player_IsMovingForward    = (g_Player_IsMovingForward * 2) & 0x3;
    g_Player_IsSteppingLeftTap  = (g_Player_IsSteppingLeftTap * 2) & 0x3F;
    g_Player_IsSteppingRightTap = (g_Player_IsSteppingRightTap * 2) & 0x3F;

    if (g_Controller0->sticks_20.sticks_0.leftY < -0x40 || g_Controller0->sticks_20.sticks_0.leftY >= 0x40 ||
        g_Controller0->sticks_20.sticks_0.leftX < -0x40 || g_Controller0->sticks_20.sticks_0.leftX >= 0x40)
    {
        g_Player_IsTurningLeft        = g_Controller0->sticks_20.sticks_0.leftX < -0x40 ? ABS(g_Controller0->sticks_20.sticks_0.leftX + 0x40) : 0;
        g_Player_IsTurningRight       = g_Controller0->sticks_20.sticks_0.leftX >= 0x40 ? g_Controller0->sticks_20.sticks_0.leftX - 0x3F : 0;
        g_Player_IsMovingForward      |= g_Controller0->sticks_20.sticks_0.leftY < -0x40;
        g_Player_IsMovingBackward      = (g_Controller0->sticks_20.sticks_0.leftY < 0x40) ^ 1;
        g_Player_MovementInputDetected = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10 |
                                          (ControllerFlag_LStickUp2 | ControllerFlag_LStickRight2 | ControllerFlag_LStickDown2 | ControllerFlag_LStickLeft2) |
                                          g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12 | g_GameWorkPtr->config_0.controllerConfig_0.aim_8);
    }
    else
    {
        g_Player_IsTurningLeft        = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickLeft) << 6;
        g_Player_IsTurningRight       = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickRight) << 6;
        g_Player_IsMovingForward      |= (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickUp;
        g_Player_IsMovingBackward      = (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickDown;
        g_Player_MovementInputDetected = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10 |
                                          (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft) |
                                          g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12 | g_GameWorkPtr->config_0.controllerConfig_0.aim_8);
    }

    g_Player_IsSteppingLeftHold  = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10) &&
                                     !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12);

    g_Player_IsSteppingRightHold = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12) &&
                                     !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10);

    g_Player_IsSteppingLeftTap  |= (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10) != 0;
    g_Player_IsSteppingRightTap |= (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12) != 0;

    if (g_GameWork.config_0.optExtraWalkRunCtrl_2B)
    {
        g_Player_IsRunning = !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.run_C);
    }
    else
    {
        g_Player_IsRunning = g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.run_C;
    }

    if (g_GameWork.config_0.optExtraWeaponCtrl_23)
    {
        g_Player_IsAiming = g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.aim_8;
    }
    else
    {
        g_Player_IsAiming = g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.aim_8;
    }

    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun // If weapon is a gun.
	    && g_SysWork.player_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim)
    {
        g_Player_IsShooting  = g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.action_6;
        g_Player_IsAttacking = g_Player_IsShooting;
    }
    else
    {
        attackBtnInput = g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.action_6;

        g_Player_IsHoldAttack = (g_Player_IsHoldAttack * 2) & 0x1F;
        g_Player_IsAttacking  = (g_Player_IsAttacking * 2) & 0x3;
        g_Player_IsShooting   = (g_Player_IsShooting * 2) & 0x3;

        g_Player_IsHoldAttack |= (attackBtnInput & 0xFFFF) != false;
        g_Player_IsAttacking  |= (g_Player_IsHoldAttack & 0xF) == 0xF;

        g_Player_IsShooting |= g_Player_IsHoldAttack != false && !(g_Player_IsHoldAttack & 0x11);

        if (g_Player_IsShooting)
        {
            g_Player_IsHoldAttack = false;
        }
    }

    g_Player_ActionRunPressed = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.run_C | g_GameWorkPtr->config_0.controllerConfig_0.action_6);

    if (g_SysWork.sysState_8 != SysState_Gameplay)
    {
        g_Player_IsShooting   = false;
        g_Player_IsAttacking  = false;
        g_Player_IsHoldAttack = false;
    }

    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HyperBlaster)
    {
        switch (Inventory_HyperBlasterFunctionalTest())
        {
            case 0: // If player has the weapon, but it's not unlocked.
                g_Player_IsAiming = false;
                break;

            case 1: // This is the code for the Konami gun controller.
                g_Player_IsAiming    = g_Controller1->btnsHeld_C & ControllerFlag_Cross;
                g_Player_IsShooting  = g_Controller1->btnsHeld_C & ControllerFlag_Square;
                g_Player_IsAttacking = g_Player_IsShooting;
                break;

            case 2: // If player has the weapon and is unlocked.
                break;
        }
    }

	// This is the conditional that makes impossible to move when aiming with specific weapons.
    if (g_SysWork.playerCombatInfo_38.isAiming_13 && (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HuntingRifle ||
                                                      (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun &&
                                                       ((g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Hammer ||
                                                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_RockDrill ||
                                                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == EquippedWeaponId_Katana))))
    {
        if (g_Player_IsMovingForward)
        {
            g_Player_RockDrill_DirectionAttack = 1;
        }
        else if (g_Player_IsMovingBackward)
        {
            g_Player_RockDrill_DirectionAttack = NO_VALUE;
        }
        else
        {
            g_Player_RockDrill_DirectionAttack = 0;
        }

        g_Player_IsRunning           = false;
        g_Player_IsSteppingRightTap  = false;
        g_Player_IsSteppingRightHold = false;
        g_Player_IsSteppingLeftTap   = false;
        g_Player_IsSteppingLeftHold  = false;
        g_Player_IsMovingBackward    = false;
        g_Player_IsMovingForward     = false;
    }
}

bool func_8007F95C() // 0x8007F95C
{
    VECTOR3         pos0;
    VECTOR3         pos1;
    u16             sp30;
    s32             i;
    s_SubCharacter* ptr0;
    s_SubCharacter* ptr1;
    u16             temp;
    s32             radius;

    if (g_Player_IsInWalkToRunTransition)
    {
        return false;
    }

    pos0.vx = g_SysWork.player_4C.chara_0.position_18.vx;
    pos0.vy = g_SysWork.player_4C.chara_0.position_18.vy;
    pos0.vz = g_SysWork.player_4C.chara_0.position_18.vz;

    if (!g_SysWork.playerCombatInfo_38.isAiming_13 || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
    {
        for (i = 0, ptr1 = g_SysWork.npcs_1A0, ptr0 = g_SysWork.npcs_1A0; i < 6; i++, ptr1++, ptr0++)
        {
            if (ptr0->model_0.charaId_0 != Chara_None)
            {
                if (ptr0->model_0.charaId_0 != Chara_AirScreamer && ptr0->model_0.charaId_0 != Chara_NightFlutter)
                {
                    if (ptr0->model_0.charaId_0 == Chara_Creaper)
                    {
                        radius = FP_METER(0.65f);
                    }
                    else
                    {
                        radius = FP_METER(0.85f);
                    }
                }
                else
                {
                    radius = FP_METER(1.2f);
                }

                pos1.vx = ptr1->position_18.vx + ptr1->field_D8.field_0;
                pos1.vy = ptr1->position_18.vy;
                pos1.vz = ptr1->position_18.vz + ptr1->field_D8.field_2;

                if (!Math_Distance2dCheck(&pos0, &pos1, radius) && ABS(pos1.vy - pos0.vy) < FP_METER(0.3f) &&
                    ptr1->health_B0 > FP_HEALTH(0.0f) && (ptr1->flags_3E & (1 << 1)))
                {
                    Math_ShortestAngleGet(g_SysWork.player_4C.chara_0.rotation_24.vy,
                                       FP_ANGLE_NORM_U(ratan2(pos1.vx - pos0.vx, pos1.vz - pos0.vz) + FP_ANGLE(360.0f)),
                                       &sp30);

                    temp = sp30 + FP_ANGLE(89.98f);
                    if (temp < FP_ANGLE(202.49f))
                    {
                        g_SysWork.enemyTargetIdx_2353 = i;
                        return true;
                    }
                }
            }
        }
    }

    g_SysWork.enemyTargetIdx_2353 = NO_VALUE;
    return false;
}

void Math_ShortestAngleGet(s16 angleFrom, s16 angleTo, s16* shortestAngle) // 0x8007FB34
{
    s16 adjAngle;

    if (angleTo > angleFrom)
    {
        if ((angleTo - angleFrom) < FP_ANGLE(180.0f)) 
        {
            *shortestAngle = angleTo - angleFrom;
        }
        else
        {
            adjAngle       = angleTo  - FP_ANGLE(360.0f);
            *shortestAngle = adjAngle - angleFrom;
        }
    }
    else
    {
        if ((angleFrom - angleTo) < FP_ANGLE(180.0f))
        {
            *shortestAngle = angleTo - angleFrom;
        }
        else
        {
            adjAngle       = angleFrom - FP_ANGLE(360.0f);
            *shortestAngle = angleTo   - adjAngle;
        }
    }
}

void func_8007FB94(s_SubCharacter* chara, s_MainCharacterExtra* extra, s32 animStatus) // 0x8007FB94
{
    s32 i;

    if (extra->model_0.state_2 != 0)
    {
        return;
    }

    for (i = 0; i < 40; i++)
    {
        if (g_MapOverlayHeader.field_38[i].status_2 != animStatus)
        {
            continue;
        }

        if (extra->model_0.stateStep_3 == 0)
        {
            extra->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0;
            extra->model_0.stateStep_3++;
        }

        if (chara->model_0.stateStep_3 == 0)
        {
            chara->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0;
            chara->model_0.stateStep_3++;
        }

        D_800AF220 = i;
        i          = 41;

        extra->model_0.state_2++;
    }
}

void func_8007FC48(s_SubCharacter* chara, s_MainCharacterExtra* extra, s32 animStatus) // 0x8007FC48
{
    s32 i;

    if (extra->model_0.state_2 != 0)
    {
        return;
    }

    // TODO: 40 of what?
    for (i = 0; i < 40; i++)
    {
        if (g_MapOverlayHeader.field_38[i].status_2 != animStatus)
        {
            continue;
        }

        // Set active anim index.
        extra->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0 + 1;
        chara->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0 + 1;

        // Increment state step.
        extra->model_0.stateStep_3++;
        chara->model_0.stateStep_3++;

        // Set anim time.
        extra->model_0.anim_4.time_4 = FP_TIME(g_MapOverlayHeader.field_38[i].time_4);
        D_800AF220                   = i;
        chara->model_0.anim_4.time_4 = FP_TIME(g_MapOverlayHeader.field_38[i].time_4);
        i                            = 41;

        // Increment state.
        extra->model_0.state_2++;
    }
}

s32 func_8007FD2C() // 0x8007FD2C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.field_104;
}

q19_12 Game_GasWeaponPowerTimerValue() // 0x8007FD3C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114;
}

void func_8007FD4C(s32 arg0) // 0x8007FD4C
{
    s32             i;
    s_SubCharacter* chara;

    chara = &g_SysWork.player_4C.chara_0;

    g_Player_GrabFree_InputCount = 0;
    chara->field_40              = NO_VALUE;

    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

    for (i = 0; i < 4; i++)
    {
        g_SysWork.field_2354[i] = NO_VALUE;
    }

    if (arg0 != 0) 
    {
        g_SysWork.player_4C.chara_0.field_D4         = 0x4CC;
        g_SysWork.player_4C.chara_0.field_D6         = 0x3AE;
        g_SysWork.player_4C.chara_0.field_C8         = FP_FLOAT_TO(-1.6f, Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
        g_SysWork.player_4C.chara_0.field_CA         = 0;
        g_SysWork.player_4C.chara_0.field_CE         = FP_FLOAT_TO(-1.1f, Q12_SHIFT);
    }
}

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_8007FDE0); // 0x8007FDE0

s32 Math_DistanceGet(const VECTOR3* pos0, const VECTOR3* pos1) // 0x800802CC
{
    s32 deltaX = pos1->vx - pos0->vx;
    s32 deltaY = pos1->vy - pos0->vy;
    s32 deltaZ = pos1->vz - pos0->vz;
    return SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) +
                        FP_MULTIPLY_PRECISE(deltaY, deltaY, Q12_SHIFT) +
                        FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT));
}

s32 Math_Distance2dGet(const VECTOR3* pos0, const VECTOR3* pos1) // 0x8008037C
{
    s32 deltaX = pos1->vx - pos0->vx;
    s32 deltaZ = pos1->vz - pos0->vz;
    return SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) +
                        FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_800803FC); // 0x800803FC

void Input_SelectClickSet() // 0x80080458
{
    g_Controller1->btnsClicked_10 |= ControllerFlag_Select;
}

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1) // 0x80080478
{
    s32 x0;
    s32 x1;
    s32 y1;
    s32 y0;
    s32 z0;
    s32 z1;
    s32 deltaX;
    s32 deltaZ;
    u16 atan2Delta;
    s32 unk;

    x0 = pos0->vx;
    x1 = pos1->vx;
    y0 = pos0->vy;
    y1 = pos1->vy;
    z0 = pos0->vz;
    z1 = pos1->vz;

    deltaX     = x1 - x0;
    deltaZ     = z1 - z0;
    atan2Delta = ratan2(deltaX, deltaZ);

    unk = func_8008A058(func_80080540(deltaX, 0, deltaZ));
    return (ratan2(unk, y1 - y0) << 16) | atan2Delta;
}

s32 func_80080514(void) // 0x80080514
{
    s32 rand16;

    rand16 = Rng_Rand16();
    return FP_ANGLE_NORM_U(((rand16 * 2) ^ rand16) >> 3);
}

// TODO: Try decomping by hand. -- Sezz
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_80080540); // 0x80080540

s32 Math_PreservedSignSubtract(s32 val, s32 subtractor) // 0x80080594
{
    s32 signBit;
    s32 absDiff;

    signBit = val >> 31;  
    absDiff = ((val ^ signBit) - signBit) - subtractor;  
    return ((absDiff & ~(absDiff >> 31)) ^ signBit) - signBit; 
}

void func_800805BC(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* rootCoord, s32 arg3) // 0x800805BC
{
    MATRIX mat;
    VECTOR vec;

    Vw_CoordHierarchyMatrixCompute(rootCoord, &mat);
    gte_SetRotMatrix(&mat);
    gte_SetTransMatrix(&mat);

    while (arg3 > 0)
    {
        gte_ldv0(rot);
        gte_rt();
        gte_stlvnl(&vec);

        pos->vx = vec.vx * 16;
        pos->vy = vec.vy * 16;
        pos->vz = vec.vz * 16;

        arg3--;
        rot++;
        pos++;
    }
}

bool func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800806AC
{
    bool result;

    result = arg0 != 0;
    if (!result)
    {
        return result;
    }

    result = ~arg0 == 0;
    if (result)
    {
        return result;
    }

    func_800699F8(&D_800C4620, arg1, arg3);

    result = arg2 < D_800C4620.groundHeight_0;
    if (result)
    {
        result = ~D_800C4620.field_8 != 0;
        if (result)
        {
            result = (arg0 & (1 << D_800C4620.field_8));
            return result != false; 
        }
    }

    return result;
}

bool func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x8008074C
{
    return func_800806AC(arg0, arg1, 1 << 31, arg3);
}

void func_8008076C(s32 posX, s32 posZ) // 0x8008076C
{
    s32              groundHeight;
    s32              caseVar;
    s32              x;
    s32              z;
    s_func_800699F8* coll;

    coll = &D_800AFC78.field_C;

    x = D_800AFC78.position_0.vx;
    z = D_800AFC78.position_0.vz;
    if (D_800AFC78.field_18 != NO_VALUE && x == posX && z == posZ)
    {
        return;
    }

    func_800699F8(coll, posX, posZ);
    D_800AFC78.position_0.vx = posX;
    D_800AFC78.position_0.vz = posZ;

    caseVar = coll->field_8;
    switch (coll->field_8)
    {
        case 0:
            groundHeight = FP_METER(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP5_S01:
                    if (posZ <= 0)
                    {
                        groundHeight = FP_METER(4.0f);
                        caseVar      = 7;
                    }
                    break;

                case MapOverlayId_MAP6_S00:
                    groundHeight = FP_METER(4.0f);
                    caseVar      = 7;
                    break;
            }
            break;

        case 12:
            groundHeight = FP_METER(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP6_S00:
                    groundHeight = FP_METER(4.0f);
                    caseVar      = 7;
                    break;
            }
            break;

        default:
            groundHeight = coll->groundHeight_0;
            break;
    }
    
    D_800AFC78.position_0.vy = groundHeight;
    D_800AFC78.field_18      = caseVar;
}

s32 func_80080884(s32 posX, s32 posZ) // 0x80080884
{
    func_8008076C(posX, posZ);
    return D_800AFC78.position_0.vy;
}

s32 func_800808AC(s32 posX, s32 posZ) // 0x800808AC
{
    func_8008076C(posX, posZ);
    return D_800AFC78.field_18;
}

s32 Math_MulFixed(s32 val0, s32 val1, s32 shift) // 0x800808D4
{
    u32 lo;

    // Use inline asm to fetch high/low parts of mult.
    // Only method found to allow C to keep same insn/reg order so far.
    __asm__ volatile(
        "mult %0, %1\n" // Multiply `val0` and `val1`.
        "mfhi %0\n"     // Move high result back into `val0`?
        "mflo %2\n"     // Move low result to lo.
        : "=r"(val0), "=r"(val1), "=r"(lo)
        : "0"(val0), "1"(val1));

#if 0
    // Equivalent C version of above (non-matching).
    s64 res = (s64)val0 * (s64)val1;
    val0    = (u32)(res >> 32);
    lo      = (u32)res;
#endif

    return (val0 << (32 - shift)) | (lo >> shift);
}

s32 Math_MagnitudeShiftGet(s32 mag) // 0x800808F8
{
    #define THRESHOLD_0 (1 << 14)
    #define THRESHOLD_1 ((1 << 18) - 1)
    #define THRESHOLD_2 ((1 << 22) - 1)

    s32 shift;

    if (mag < THRESHOLD_0)
    {
        return 0;
    }

    if (mag > THRESHOLD_1)
    {
        if (mag > THRESHOLD_2)
        {
            return Q12_SHIFT;
        }

        shift = Q8_SHIFT;
        return shift;
    }

    shift = Q4_SHIFT;
    return shift;
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", hack_D_8002A844_fix);
