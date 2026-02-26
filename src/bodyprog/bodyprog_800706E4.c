#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/joy.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

s_800C44F0 D_800C44F0[10];
VECTOR3    g_TargetEnemyPosition;
q19_12     D_800C454C;
q19_12     D_800C4550;
s16        D_800C4554;
s16        D_800C4556;
s32        g_Player_HasMoveInput;
s32        g_Player_HasActionInput;
s8         D_800C4560;
u8         g_Player_IsDead;
u8         g_Player_DisableDamage;
u8         pad_bss_800C4563[13];
s_800AFBF4 g_Player_EquippedWeaponInfo;
u8         D_800C457C;
u8         pad_bss_800C457D;
u16        g_Player_IsAiming;
u16        g_Player_IsSteppingLeftTap;
u16        g_Player_IsSteppingRightTap;
u16        g_Player_IsTurningLeft;
u16        g_Player_IsTurningRight;
u8         D_800C4588;
s8         pad_bss_800C4589[7];
s_800C4590 D_800C4590;
u16        g_Player_IsSteppingLeftHold;
u16        g_Player_IsSteppingRightHold;
VECTOR3    D_800C45B0;
u16        g_Player_IsHoldAttack;
u16        g_Player_IsAttacking;
u16        g_Player_IsShooting;
s8         pad_bss_800C45C2[6];
s_800C45C8 D_800C45C8;
s8         pad_bss_800C45E0[8];
u16        g_Player_IsMovingForward;
s8         pad_bss_800C45EA[2];
s32        D_800C45EC;
u16        g_Player_IsMovingBackward;
s8         pad_bss_800C45F2[6];
VECTOR3    g_Player_PrevPosition;
u16        g_Player_IsRunning;
s16        pad_bss_800C4606;
q19_12     g_Player_HeadingAngle;
s32        pad_bss_800C460C;
VECTOR3    D_800C4610;

// Some kind of `Anim_UpdateX` function, included in some `s_AnimInfo` array which also had pointers to `Anim_Update1`/`Anim_Update2`.

s32 func_800706E4(s_Model* model) // 0x800706E4
{
    s32 result;

    result = 0;

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
    {
        case 39:
        case 40:
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP2_S00:
                case MapOverlayId_MAP2_S02:
                case MapOverlayId_MAP4_S02:
                case MapOverlayId_MAP5_S01:
                case MapOverlayId_MAP6_S00:
                case MapOverlayId_MAP6_S02:
                    if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(128, false) ||
                        g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(129, false))
                    {
                        if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime;
                            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 >= Q12(0.0f))
                            {
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime;
                                result = g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8;
                            }
                            else
                            {
                                result = Q12(0.0f);
                            }
                            break;
                        }
                    }

                    result = Q12(15.0f);
            }
            break;

        case 47:
        case 48:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
            {
                if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(132, true) ||
                    g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(133, false))
                {
                    if (g_SysWork.playerWork_4C.player_0.health_B0 <= 0)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime * 2;
                        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 >= Q12(0.0f))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime * 2;

                            result = g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8;
                        }
                        else
                        {
                            result = Q12(0.0f);
                        }
                        break;
                    }
                }

                result = Q12(10.0f);
            }
            break;

        default:
            switch (model->anim_4.status_0)
            {
                case ANIM_STATUS(2, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        result = (ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.65f) / 64) * 16 + Q12(12.0f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ((ABS(D_800AF216 - 64) * Q12(0.65f) / 64) * 16) + Q12(12.0f);
                    }
                    else
                    {
                        result = Q12(22.0f);
                    }
                    break;

                case ANIM_STATUS(3, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        if ((model->anim_4.keyframeIdx_8 >= 40 && model->anim_4.keyframeIdx_8 < 46) ||
                            (model->anim_4.keyframeIdx_8 >= 30 && model->anim_4.keyframeIdx_8 < 36))
                        {
                            result = ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.25f) + Q12(16.0f);
                        }
                        else
                        {
                            result = Q12(32.0f);
                        }
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ABS(D_800AF216 - 64) * Q12(0.25f) + Q12(16.0f);
                    }
                    else
                    {
                        result = Q12(30.0f);
                    }
                    break;

                case ANIM_STATUS(4, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY >= 64)
                    {
                        result = ((ABS(g_Controller0->sticks_20.sticks_0.leftY - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ((ABS(D_800AF216 - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else
                    {
                        result = Q12(23.0f);
                    }
                    break;

                case ANIM_STATUS(27, true):
                    if (g_SysWork.playerWork_4C.player_0.health_B0 < Q12(30.0f))
                    {
                        result = Q12(40.0f) - g_SysWork.playerWork_4C.player_0.health_B0;
                    }
                    else
                    {
                        result = Q12(FP_FROM(g_SysWork.playerWork_4C.player_0.properties_E4.player.exhaustionTimer_FC, Q12_SHIFT));
                    }
                    break;
            }
    }

    return result;
}

const s_AnimInfo* const D_800297B8 = HARRY_BASE_ANIM_INFOS;

void func_80070B84(s_SubCharacter* chara, q19_12 moveDistMax, q19_12 arg2, s32 keyframeIdx) // 0x80070B84
{
    q3_12  unkMoveDist;
    s32    stickY;
    q3_12* moveDist;

    if (!D_800AF216)
    {
        stickY = ABS(g_Controller0->sticks_20.sticks_0.leftY);
    }
    else
    {
        stickY = D_800AF216;
    }

    moveDistMax = moveDistMax + ((arg2 - moveDistMax) * (stickY - 64) / 64);

    // @hack Wrapping in loop required for match.
    do
    {
        if (moveDistMax < g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126)
        {
            unkMoveDist                                                            = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 - ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = unkMoveDist;
            if (unkMoveDist < moveDistMax)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = moveDistMax;
            }
        }
        else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < moveDistMax)
        {
            moveDist = &g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = *moveDist + TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(*moveDist, Q12(0.0f), moveDistMax);
        }
    }
    while (false); // @hack Required for match.
}

void func_80070CF0(s_SubCharacter* chara, q19_12 arg1, q19_12 moveDistMax, q19_12 moveDistForward, q19_12 modeDistBack) // 0x80070CF0
{
    s32    stickY;
    q3_12* moveDist;

    do
    {
        if ((chara->model_0.anim_4.keyframeIdx_8 >= 40 && chara->model_0.anim_4.keyframeIdx_8 < 46) ||
            (chara->model_0.anim_4.keyframeIdx_8 >= 30 && chara->model_0.anim_4.keyframeIdx_8 < 36))
        {
            stickY      = D_800AF216 ? D_800AF216 : ABS(g_Controller0->sticks_20.sticks_0.leftY);
            moveDistMax = arg1 + ((moveDistMax - arg1) * (stickY - 64) / 64);
        }
    }
    while (false); // @hack Required for match.

    if (moveDistMax < g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126)
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= modeDistBack;
        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < moveDistMax)
        {
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = moveDistMax;
        }
    }
    else
    {
        moveDist = &g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < moveDistMax)
        {
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += moveDistForward;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126  = CLAMP(*moveDist, Q12(0.0f), moveDistMax);
        }
    }
}

void func_80070DF0(s_PlayerExtra* extra, s_SubCharacter* chara, s32 weaponAttack, s32 animStatus)  // 0x80070DF0
{
    q3_12 shortestAngle;
    q3_12 angleTo;

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

    angleTo = Q12_FRACT(ratan2((g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vx + g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetX_0) - g_SysWork.playerCombat_38.field_0.vx,
                               (g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vz + g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetZ_2) - g_SysWork.playerCombat_38.field_0.vz) +
                          Q12_ANGLE(360.0f));
    chara->field_2A = angleTo;
    Math_ShortestAngleGet(chara->rotation_24.vy, angleTo, &shortestAngle);

    if (ABS(shortestAngle) >= Q12_ANGLE(8.5f))
    {
        if (shortestAngle < 0)
        {
            chara->rotation_24.vy -= Q12_ANGLE(8.5f);
        }
        else
        {
            chara->rotation_24.vy += Q12_ANGLE(8.5f);
        }
    }

    if (extra->model_0.anim_4.keyframeIdx_8 >= (HARRY_BASE_ANIM_INFOS[animStatus].startKeyframeIdx_C + D_800AD4C8[weaponAttack].field_E) &&
        ((HARRY_BASE_ANIM_INFOS[animStatus].startKeyframeIdx_C + D_800AD4C8[weaponAttack].field_E) + D_800AD4C8[weaponAttack].field_F) >= extra->model_0.anim_4.keyframeIdx_8)
    {
        g_SysWork.playerCombat_38.weaponAttack_F = weaponAttack;

        if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
        {
            chara->field_44.field_0                                     = 1;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
        }
    }

    if (animStatus == ANIM_STATUS(HarryAnim_Kick, true) && ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 =  Q12_MULT(D_800AF014[chara->model_0.anim_4.keyframeIdx_8 - 457], Math_Cos(chara->rotation_24.vy));
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = -Q12_MULT(D_800AF014[chara->model_0.anim_4.keyframeIdx_8 - 457], Math_Sin(chara->rotation_24.vy));
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
    }

    if (animStatus == ANIM_STATUS(HarryAnim_Stomp, true) && ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 =  Q12_MULT(D_800AF04C[chara->model_0.anim_4.keyframeIdx_8 - 485], Math_Cos(chara->rotation_24.vy));
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = -Q12_MULT(D_800AF04C[chara->model_0.anim_4.keyframeIdx_8 - 485], Math_Sin(chara->rotation_24.vy));
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
    }

    if (chara->model_0.anim_4.status_0 == animStatus &&
        chara->model_0.anim_4.keyframeIdx_8 == HARRY_BASE_ANIM_INFOS[animStatus].endKeyframeIdx_E)
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

        Player_ExtraStateSet(chara, extra, PlayerState_None);

        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
        g_SysWork.playerCombat_38.weaponAttack_F            = (g_SavegamePtr->equippedWeapon_AA == InventoryItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA + InventoryItemId_KitchenKnife);
        g_SysWork.targetNpcIdx_2353                         = NO_VALUE;
        g_SysWork.playerCombat_38.isAiming_13               = false;
    }
}

void Player_CharaTurn_0(s_SubCharacter* chara, e_PlayerLowerBodyState curState) // 0x800711C4
{
    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack ||
        !g_Player_IsSteppingLeftTap || !g_Player_IsSteppingRightTap)
    {
        return;
    }

    if (g_Player_IsTurningLeft)
    {
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = curState + PlayerLowerBodyState_QuickTurnLeft;
    }
    else
    {
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = curState + PlayerLowerBodyState_QuickTurnRight;
    }
}

void Player_CharaTurn_1(s_SubCharacter* chara, e_PlayerLowerBodyState curState) // 0x80071224
{
    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack ||
        !g_Player_IsSteppingLeftTap || !g_Player_IsSteppingRightTap)
    {
        return;
    }

    if (g_Player_IsTurningRight)
    {
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = curState + PlayerLowerBodyState_QuickTurnRight;
    }
    else
    {
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = curState + PlayerLowerBodyState_QuickTurnLeft;
    }
}

void Player_CharaRotate(s32 speed) // 0x80071284
{
    if (g_GameWork.config_0.optExtraRetreatTurn_2A)
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((speed * g_DeltaTime) * g_Player_IsTurningRight) >> 6; // Divide by `0x40 / 64`?
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((-speed * g_DeltaTime) * g_Player_IsTurningLeft) >> 6;
        }
    }
    else if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_WalkBackward ||
             g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_AimWalkBackward)
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((-speed * g_DeltaTime) * g_Player_IsTurningRight) >> 6;
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((speed * g_DeltaTime) * g_Player_IsTurningLeft) >> 6;
        }
    }
    else
    {
        if (g_Player_IsTurningRight)
        {
            D_800C454C = ((speed * g_DeltaTime) * g_Player_IsTurningRight) >> 6;
        }
        else if (g_Player_IsTurningLeft)
        {
            D_800C454C = ((-speed * g_DeltaTime) * g_Player_IsTurningLeft) >> 6;
        }
    }
}

void Player_MovementStateReset(s_SubCharacter* chara, e_PlayerLowerBodyState lowerBodyState) // 0x800713B4
{
    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != lowerBodyState)
    {
        chara->model_0.stateStep_3              = 0;
        chara->model_0.controlState_2           = ModelState_Uninitialized;
        chara->properties_E4.player.runTimer_F8 = Q12(0.0f);
        chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
        g_SysWork.playerStopFlags_235A          = PlayerStopFlag_None;
    }
}

bool Player_FootstepSfxPlay(s32 animStatus, s_SubCharacter* chara, s32 keyframe0, s32 keyframe1, s32 sfx, s8 pitch)
{
    if (chara->model_0.anim_4.status_0 != animStatus)
    {
        return false;
    }

    if (chara->model_0.anim_4.keyframeIdx_8 >= keyframe1)
    {
        if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk4))
        {
            if (pitch < 0x20)
            {
                switch (animStatus)
                {
                    case ANIM_STATUS(HarryAnim_SidestepRight, true):
                    case ANIM_STATUS(HarryAnim_SidestepLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnRight, true):
                        func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.095f), pitch);
                        chara->properties_E4.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.25f), pitch);
                        chara->properties_E4.player.field_10C = pitch + 0x10;
                        break;
                }
            }
            else
            {
                func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.5f), pitch);
                chara->properties_E4.player.field_10C = pitch + 0x40;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk4;
            return true;
        }
    }
    else
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk4;
    }

    if (chara->model_0.anim_4.keyframeIdx_8 >= keyframe0)
    {
        if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk5))
        {
            if (pitch < 32)
            {
                switch (animStatus)
                {
                    case ANIM_STATUS(HarryAnim_SidestepRight, true):
                    case ANIM_STATUS(HarryAnim_SidestepLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnRight, true):
                        func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.095f), pitch);
                        chara->properties_E4.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.25f), pitch);
                        chara->properties_E4.player.field_10C = pitch + 16;
                        break;
                }
            }
            else
            {
                func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.5f), pitch);
                chara->properties_E4.player.field_10C = pitch + 64;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            return true;
        }
    }
    else
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
    }

    return false;
}

bool func_80071620(u32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, e_SfxId sfxId) // 0x80071620
{
    if (chara->model_0.anim_4.status_0 != animStatus)
    {
        return false;
    }

    if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx)
    {
        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk13)
        {
            return false;
        }

        switch (sfxId)
        {
            case Sfx_Stumble0:
            case Sfx_Unk1316:
            case Sfx_Unk1318:
            case Sfx_Unk1319:
            case Sfx_Stumble1:
                func_8005DC1C(sfxId, &chara->position_18, 0x80, 0);
                chara->properties_E4.player.field_10C = 0x40;
                break;

            case Sfx_Unk1283:
                func_8005DC1C(sfxId, &chara->position_18, 0xC8, 2);
                chara->properties_E4.player.field_10C = 0;
                break;

            case Sfx_Unk1628:
                func_8005DC1C(sfxId, &chara->position_18, 0x40, 1);
                break;

            case Sfx_Unk1626:
                func_8005DC1C(sfxId, &chara->position_18, 0xFF, 1);
                break;

            case Sfx_Unk1638:
                func_8005DC1C(sfxId, &chara->position_18, 0xFF, 2);
                break;

            default:
            case Sfx_HarryHeavyBreath:
            case Sfx_DoorJammed:
                func_8005DC1C(sfxId, &chara->position_18, 0x40, 2);
                chara->properties_E4.player.field_10C = 0;
                break;
        }

        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk13;
        return true;
    }
    else
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk13;

        do {} while (false); // @hack Required for match.

        return false;
    }
}

void Player_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800717D0
{
    // Called by `GameState_InGame_Update`, might be player update function.
    // - `chara` always `&g_SysWork.playerWork_4C.player_0`.
    // - `arg1`  always `0x8010A600`/`FS_BUFFER_0` (holds anim data).
    // - `coord` always `&g_SysWork.playerBoneCoords_890`.

    s_PlayerExtra* extra;

    extra = &g_SysWork.playerWork_4C.extra_128;

    if (g_DeltaTime != Q12(0.0f))
    {
        Player_ReceiveDamage(chara, extra);

        if (g_Player_IsInWalkToRunTransition)
        {
            g_Player_HasActionInput      = false;
            g_Player_HasMoveInput        = false;
            g_Player_IsShooting          = false;
            g_Player_IsAttacking         = false;
            g_Player_IsHoldAttack        = false;
            g_Player_IsAiming            = false;
            g_Player_IsRunning           = false;
            g_Player_IsMovingBackward    = false;
            g_Player_IsMovingForward     = false;
            g_Player_IsSteppingRightTap  = false;
            g_Player_IsSteppingRightHold = false;
            g_Player_IsTurningRight      = false;
            g_Player_IsSteppingLeftTap   = false;
            g_Player_IsSteppingLeftHold  = false;
            g_Player_IsTurningLeft       = false;
        }

        if (!g_Player_DisableControl)
        {
            Player_LogicUpdate(chara, extra, coords);
        }
        else
        {
            g_MapOverlayHeader.func_B8(chara, extra, coords);
        }

        if (!g_Player_DisableControl)
        {
            func_8007C0D8(chara, extra, coords);
        }
        else
        {
            g_MapOverlayHeader.func_BC(chara, extra, coords);
        }

        Player_AnimUpdate(chara, extra, anmHdr, coords);
        func_8007D090(chara, extra, coords);
    }

    D_800C45B0.vx = 0;
    D_800C45B0.vz = 0;
}

static inline void func_80071968_Switch0(void)
{
    if (g_SysWork.playerCombat_38.weaponAttack_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Multitap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(2, 2));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Handgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(3, 2));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(4, 2));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Unk3, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk31,AttackInputType_Tap):
                break;
        }
    }
    else
    {
        WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(2, 2));
    }
}

static inline void func_80071968_Switch1(void)
{
    if (g_SysWork.playerCombat_38.weaponAttack_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Multitap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(2, 1));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Handgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(3, 1));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(4, 1));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Unk3,  AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8,  AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9,  AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk8,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk9,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk31, AttackInputType_Tap):
                break;
        }
    }
    else
    {
        WorldGfx_HeldItemAttach(Chara_Harry, g_SysWork.enablePlayerMatchAnim_2358 ? MODEL_BONE(2, 1) : MODEL_BONE(1, 1));
    }
}

void Player_AnimUpdate(s_SubCharacter* chara, s_PlayerExtra* extra, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x80071968
{
    s_AnimInfo* animInfo;

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
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
        case PlayerState_Unk141: // Throwing disinfective alcohol scene. (Hospital Basement Otherworld)
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
            switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
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
        // Disable upper body bones before playing anim.
        g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_UPPER_BODY_BONE_MASK;

        animInfo = &HARRY_BASE_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

        // Re-enable upper body bones, disable lower body bones.
        g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_LOWER_BODY_BONE_MASK;

        animInfo = &HARRY_BASE_ANIM_INFOS[extra->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&extra->model_0, anmHdr, coords, animInfo);
        return;
    }

    // Disable upper body bones before playing anim.
    g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_UPPER_BODY_BONE_MASK;
    chara->model_0.anim_4.status_0                     = ANIM_STATUS(HarryAnim_Still, false);

    animInfo = &HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    // Re-enable upper body bones, disable lower body bones.
    g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_LOWER_BODY_BONE_MASK;

    animInfo = &HARRY_BASE_ANIM_INFOS[extra->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&extra->model_0, anmHdr, coords, animInfo);

    if (chara->model_0.anim_4.status_0 == HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6)
    {
        g_Player_IsInWalkToRunTransition = false;
    }
}

void Player_LogicUpdate(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords)
{
    SVECTOR       playerAngles;
    q3_12         headingAngle0;
    q3_12         headingAngle1;
    s16           sp1C;
    s16           sp1E;
    s32           temp_a2;
    s32           temp_s0;
    s32           var_v1_5;
    s32           temp_s0_3;
    q19_12        deltaPosX;
    q19_12        deltaPosZ;
    s32           temp_v1_12;
    s32           temp_v1_13;
    e_PlayerState thrownState;
    s32           playeGrabFree_RequiredInputCount;
    e_PlayerState romperAttackState;
    e_PlayerState enemyGrabReleaseState;
    q3_12         unkDistThreshold;
    q3_12         npcDist;
    s32           npcIdx;
    s32           animStatus;
    s32           temp;
    s_Model**     models; // Maybe model pointer array?
    s_Model*      model;

    animStatus = ANIM_STATUS(HarryAnim_Still, false);

    Game_TimerUpdate();

    D_800C4550                              = 0;
    D_800C454C                              = 0;
    chara->properties_E4.player.field_10C >>= 1;

    if (chara->flags_3E & CharaFlag_Unk4)
    {
        chara->properties_E4.player.timer_110 += g_DeltaTime;
    }

    if (chara->properties_E4.player.timer_110 > D_800C45EC)
    {
        chara->properties_E4.player.timer_110 = Q12(0.0f);
        chara->flags_3E &= ~CharaFlag_Unk4;
    }

    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 -= g_DeltaTime;
    }

    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114, Q12(0.0f), Q12(60.0f));

    if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
        g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
    {
        func_8004C564(g_SysWork.playerCombat_38.weaponAttack_F, (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != 0) ? 4 : 2);
    }

    g_SavegamePtr->healthSaturation_238 -= g_DeltaTime;
    g_SavegamePtr->healthSaturation_238 = CLAMP(g_SavegamePtr->healthSaturation_238, Q12(0.0f), Q12(300.0f));

    if (g_SavegamePtr->healthSaturation_238 != Q12(0.0f))
    {
        g_SysWork.playerWork_4C.player_0.health_B0 += g_DeltaTime;
        g_SysWork.playerWork_4C.player_0.health_B0  = CLAMP(g_SysWork.playerWork_4C.player_0.health_B0, Q12(0.0f), Q12(100.0f));
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S00)
    {
        g_MapOverlayHeader.func_108();
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        Player_Controller();
    }

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
    {
        case PlayerState_Idle:
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            func_8005545C(&playerAngles);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120 = playerAngles.vy;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_LookAround, false);
                extra->model_0.stateStep_3++;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_LookAround, false);
                chara->model_0.stateStep_3++;
            }

            // If player is not performing a movement.
            if (!(g_Player_HasMoveInput | g_Player_HasActionInput))
            {
                break;
            }

            Player_ExtraStateSet(chara, extra, PlayerState_None);

        case PlayerState_None:
        case PlayerState_Combat:
            Player_LowerBodyUpdate(chara, extra);

            if (g_SysWork.playerWork_4C.extra_128.state_1C < (u32)PlayerState_Idle)
            {
                Player_UpperBodyUpdate(chara, extra);
            }
            break;

        case PlayerState_Unk7:
            func_8007FB94(chara, extra, ANIM_STATUS(100, false));

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));

                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (!(chara->attackReceived_41 >= 68 && chara->attackReceived_41 < 70))
            {
                g_Player_HeadingAngle                                                  = ratan2(chara->damage_B4.position_0.vx, chara->damage_B4.position_0.vz) - chara->rotation_24.vy;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = SQUARE(chara->damage_B4.position_0.vx) + SQUARE(chara->damage_B4.position_0.vz) + SQUARE(chara->damage_B4.position_0.vy);
            }

            if (extra->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                chara->attackReceived_41 = NO_VALUE;

                g_SysWork.targetNpcIdx_2353                                      = NO_VALUE;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

                Player_ExtraStateSet(chara, extra, PlayerState_None);

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            }

            D_800C4550               = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            chara->flags_3E         |= CharaFlag_Unk4;
            chara->attackReceived_41 = NO_VALUE;
            break;

        case PlayerState_DamageThrownFront:
        case PlayerState_DamageThrownBack:
            thrownState = PlayerState_None;

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_DamageThrownFront:
                    animStatus  = ANIM_STATUS(HarryAnim_Unk131, true);
                    thrownState = PlayerState_OnFloorFront;
                    break;

                case PlayerState_DamageThrownBack:
                    animStatus  = ANIM_STATUS(HarryAnim_Unk132, false);
                    thrownState = PlayerState_OnFloorBehind;
                    break;
            }

            func_8007FB94(chara, extra, animStatus);

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(chara, extra, thrownState);
                chara->properties_E4.player.afkTimer_E8 = Q12(10.0f);
            }

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != 0)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f)) >> 3;

                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126) < 0)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800C4550 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            break;

        case PlayerState_EnemyGrabPinnedFrontStart:
        case PlayerState_EnemyGrabPinnedBackStart:
            romperAttackState = PlayerState_None;
            npcIdx            = 0;

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabPinnedFrontStart:
                    animStatus        = ANIM_STATUS(HarryAnim_Unk127, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedFront;
                    npcIdx            = g_SysWork.npcIdxs_2354[0];
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + Q12_ANGLE(180.0f)), &headingAngle0);
                    break;

                case PlayerState_EnemyGrabPinnedBackStart:
                    animStatus        = ANIM_STATUS(HarryAnim_Unk128, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedBack;
                    npcIdx            = g_SysWork.npcIdxs_2354[1];
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + Q12_ANGLE(360.0f)), &headingAngle0);
                    break;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            func_8007FB94(chara, extra, animStatus);
            chara->field_D4.radius_0 = Q12(0.25f);
            chara->field_D4.field_2 = Q12(0.0f);

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                temp_s0 = -D_800AF1FC[chara->model_0.anim_4.keyframeIdx_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4];
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12_MULT(temp_s0, Math_Sin(chara->rotation_24.vy));
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12_MULT(temp_s0, Math_Cos(chara->rotation_24.vy));
            }

            if (ABS(headingAngle0) < Q12_ANGLE(11.25f))
            {
                if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedFrontStart)
                {
                    chara->rotation_24.vy = g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + Q12_ANGLE(180.0f);
                }
                else
                {
                    chara->rotation_24.vy = g_SysWork.npcs_1A0[npcIdx].rotation_24.vy;
                }
            }
            else
            {
                if (headingAngle0 > Q12_ANGLE(0.0f))
                {
                    chara->rotation_24.vy += Q12_ANGLE(11.25f);
                }
                else
                {
                    chara->rotation_24.vy -= Q12_ANGLE(11.25f);
                }
            }

            Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[npcIdx].rotation_24.vy + Q12_ANGLE(360.0f)), &headingAngle0);

            model = &g_SysWork.npcs_1A0[npcIdx].model_0;

            do {} while(false); // @hack Required for match.

            g_Player_HeadingAngle =
            temp                  = headingAngle0;

            if ((*models) != NULL) // @hack Required for match.
            {
                g_Player_HeadingAngle += Q12_ANGLE(0.0f);
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(chara, extra, romperAttackState);
                chara->properties_E4.player.afkTimer_E8 = Q12(15.0f);
            }

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if (g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_EnemyGrabPinnedFrontStart &&
                    g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_EnemyGrabPinnedFront)
                {
                    temp = -0x8000;
                    extra->model_0.anim_4.time_4 = (Q12(g_MapOverlayHeader.animInfos_34[chara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C) + model->anim_4.time_4) + temp;
                    chara->model_0.anim_4.time_4 = (Q12(g_MapOverlayHeader.animInfos_34[chara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C) + model->anim_4.time_4) + temp;
                    chara->model_0.anim_4.keyframeIdx_8 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                    extra->model_0.anim_4.keyframeIdx_8 = FP_FROM(extra->model_0.anim_4.time_4, Q12_SHIFT);
                }
            }

            if (ABS(chara->position_18.vx - D_800C4610.vx) <= Q12(0.05f))
            {
                chara->position_18.vx = D_800C4610.vx;
            }
            else
            {
                if (chara->position_18.vx >= D_800C4610.vx)
                {
                    chara->position_18.vx -= (Q12(0.05f) + 1);
                }
                else
                {
                    chara->position_18.vx += (Q12(0.05f) + 1);
                }
            }

            if (ABS(chara->position_18.vz - D_800C4610.vz) <= Q12(0.05f))
            {
                chara->position_18.vz = D_800C4610.vz;
            }
            else
            {
                if (chara->position_18.vz < D_800C4610.vz)
                {
                    chara->position_18.vz += (Q12(0.05f) + 1);
                }
                else
                {
                    chara->position_18.vz -= (Q12(0.05f) + 1);
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
            enemyGrabReleaseState                                                   = PlayerState_None;
            unkDistThreshold                                                        = Q12(0.0f);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126  = Q12(0.0f);
            npcDist                                                                 = Q12(0.0f);

            // Accommodates player position (for pinned enemy gram and Romper attack) and establishes required input count to get free.
            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
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

                    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
                    {
                        case PlayerState_OnFloorFront:
                            animStatus            = ANIM_STATUS(HarryAnim_Unk132, true);
                            enemyGrabReleaseState = PlayerState_GetUpFront;
                            break;

                        case PlayerState_OnFloorBehind:
                            animStatus            = ANIM_STATUS(HarryAnim_Unk133, false);
                            enemyGrabReleaseState = PlayerState_GetUpBack;
                            break;
                    }

                    chara->field_D4.field_2 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.27f));
                    chara->field_C8.field_0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(1.2f));
                    chara->field_C8.field_6 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.9f));

                    chara->field_D4.field_2 = CLAMP(chara->field_D4.field_2, Q12(0.23f), Q12(0.5f));
                    chara->field_C8.field_0 = CLAMP(chara->field_C8.field_0, Q12(-1.6f), Q12(-0.4));
                    chara->field_C8.field_6 = CLAMP(chara->field_C8.field_6, Q12(-1.1f), Q12(-0.2f));

                    if (chara->health_B0 <= Q12(0.0f) && chara->properties_E4.player.afkTimer_E8 <= Q12(0.0f))
                    {
                        g_MapOverlayHeader.playerAnimLock_DC();
                        SysWork_StateSetNext(SysState_GameOver);

                        chara->health_B0                                                         = Q12(100.0f);
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                        return;
                    }
                    break;

                case PlayerState_EnemyGrabPinnedFront:
                case PlayerState_EnemyGrabPinnedBack:
                    unkDistThreshold = Q12(0.65f);

                    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
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

                            animStatus          = ANIM_STATUS(HarryAnim_Unk128, false);
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

                            animStatus          = ANIM_STATUS(HarryAnim_Unk129, false);
                            enemyGrabReleaseState = PlayerState_EnemyReleasePinnedBack;
                            break;
                    }

                    chara->field_D4.radius_0                        = 0;
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);

                    if (ABS(chara->position_18.vx - D_800C4610.vx) <= Q12(0.05f))
                    {
                        chara->position_18.vx = D_800C4610.vx;
                    }
                    else
                    {
                        if (chara->position_18.vx >= D_800C4610.vx)
                        {
                            chara->position_18.vx -= (Q12(0.05f) + 1);
                        }
                        else
                        {
                            chara->position_18.vx += (Q12(0.05f) + 1);
                        }
                    }

                    if (ABS(chara->position_18.vz - D_800C4610.vz) <= Q12(0.05f))
                    {
                        chara->position_18.vz = D_800C4610.vz;
                    }
                    else
                    {
                        if (chara->position_18.vz >= D_800C4610.vz)
                        {
                            chara->position_18.vz -= (Q12(0.05f) + 1);
                        }
                        else
                        {
                            chara->position_18.vz += (Q12(0.05f) + 1);
                        }
                    }

                    if (chara->health_B0 <= Q12(0.0f) && chara->properties_E4.player.afkTimer_E8 <= Q12(0.0f))
                    {
                        g_MapOverlayHeader.playerAnimLock_DC();

                        SysWork_StateSetNext(SysState_GameOver);

                        chara->health_B0                                                         = Q12(100.0f);
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                        return;
                    }
                    break;

                case PlayerState_EnemyGrabTorsoFront:
                    unkDistThreshold = Q12(1.0f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk115, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperFront;
                    break;

                default:
                    break;

                case PlayerState_EnemyGrabTorsoBack:
                    unkDistThreshold = Q12(1.0f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk117, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;

                case PlayerState_EnemyGrabLegsFront:
                    unkDistThreshold = Q12(0.8f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk117, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerFront;
                    break;

                case PlayerState_EnemyGrabLegsBack:
                    unkDistThreshold = Q12(0.8f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk118, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerBack;
                    break;

                case PlayerState_EnemyGrabNeckFront:
                    unkDistThreshold = Q12(1.5f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperFront;
                    break;

                case PlayerState_EnemyGrabNeckBack:
                    unkDistThreshold = Q12(1.5f);

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

                    animStatus            = ANIM_STATUS(HarryAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;
            }

            // Accommodates position of player and enemy?
            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabTorsoFront:
                case PlayerState_EnemyGrabLegsFront:
                case PlayerState_EnemyGrabNeckFront:
                case PlayerState_EnemyGrabPinnedFront:
                    deltaPosX = chara->position_18.vx - g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].position_18.vx;
                    deltaPosZ = chara->position_18.vz - g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].position_18.vz;
                    npcDist   = SquareRoot0(SQUARE(deltaPosX) + SQUARE(deltaPosZ));
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].rotation_24.vy + Q12_ANGLE(180.0f)), &headingAngle1);

                    if (ABS(headingAngle1) < Q12_ANGLE(11.25f))
                    {
                        chara->rotation_24.vy = g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].rotation_24.vy + Q12_ANGLE(180.0f);
                    }
                    else
                    {
                        if (headingAngle1 > Q12_ANGLE(0.0f))
                        {
                            chara->rotation_24.vy += Q12_ANGLE(11.25f);
                        }
                        else
                        {
                            chara->rotation_24.vy -= Q12_ANGLE(11.25f);
                        }
                    }
                    break;

                case PlayerState_EnemyGrabTorsoBack:
                case PlayerState_EnemyGrabLegsBack:
                case PlayerState_EnemyGrabNeckBack:
                case PlayerState_EnemyGrabPinnedBack:
                    temp_v1_12 = chara->position_18.vx - g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].position_18.vx;
                    temp_v1_13 = chara->position_18.vz - g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].position_18.vz;
                    npcDist     = SquareRoot0(SQUARE(temp_v1_12) + SQUARE(temp_v1_13));
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].rotation_24.vy + Q12_ANGLE(360.0f)), &headingAngle1);

                    if (ABS(headingAngle1) < Q12_ANGLE(11.25f))
                    {
                        chara->rotation_24.vy = g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].rotation_24.vy;
                    }
                    else
                    {
                        if (headingAngle1 > Q12_ANGLE(0.0f))
                        {
                            chara->rotation_24.vy += Q12_ANGLE(11.25f);
                        }
                        else
                        {
                            chara->rotation_24.vy -= Q12_ANGLE(11.25f);
                        }
                    }
                    break;
            }

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_EnemyGrabPinnedFront:
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].rotation_24.vy + Q12_ANGLE(360.0f)), &headingAngle1);

                case PlayerState_EnemyGrabPinnedBack:
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].rotation_24.vy + Q12_ANGLE(360.0f)), &headingAngle1);
                    break;
            }

            g_Player_HeadingAngle = headingAngle1;
            func_8007FB94(chara, extra, animStatus);

            if (chara->health_B0 > Q12(0.0f) && (g_Player_HasMoveInput | g_Player_HasActionInput))
            {
                g_Player_GrabReleaseInputTimer += g_DeltaTime;
            }

            // If player isn't thrown to floor (Cybil shoot attack).
            if (!(g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_OnFloorFront &&
                  g_SysWork.playerWork_4C.extra_128.state_1C <  PlayerState_GetUpFront))
            {
                if (unkDistThreshold < npcDist)
                {
                    g_Player_GrabReleaseInputTimer = playeGrabFree_RequiredInputCount;
                    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedFront)
                    {
                        g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[0]].moveSpeed_38 = Q12(0.0f);
                    }

                    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_EnemyGrabPinnedBack)
                    {
                        g_SysWork.npcs_1A0[g_SysWork.npcIdxs_2354[1]].moveSpeed_38 = Q12(0.0f);
                    }
                }
            }

            if (g_Player_GrabReleaseInputTimer >= playeGrabFree_RequiredInputCount)
            {
                func_8007FD4C(false);

                Player_ExtraStateSet(chara, extra, enemyGrabReleaseState);

                chara->flags_3E |= CharaFlag_Unk4;
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
            if (g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_FallBackward)
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) >> 1; // `/ 2`.
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & 1)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) >> 2; // `/ 4`.

                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & 1)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_GetUpFront:
                    animStatus = ANIM_STATUS(HarryAnim_Unk133, true);
                    break;

                case PlayerState_GetUpBack:
                    animStatus = ANIM_STATUS(HarryAnim_Unk134, false);
                    break;

                case PlayerState_EnemyReleasePinnedFront:
                    animStatus = ANIM_STATUS(HarryAnim_Unk129, true);
                    break;

                case PlayerState_EnemyReleasePinnedBack:
                    animStatus = ANIM_STATUS(HarryAnim_Unk130, false);
                    break;

                case PlayerState_EnemyReleaseUpperFront:
                    animStatus = ANIM_STATUS(HarryAnim_Unk120, false);
                    break;

                case PlayerState_EnemyReleaseUpperBack:
                    animStatus = ANIM_STATUS(HarryAnim_Unk122, false);
                    break;

                case PlayerState_Unk17:
                    animStatus = ANIM_STATUS(HarryAnim_Unk120, true);
                    break;

                case PlayerState_Unk18:
                    animStatus = ANIM_STATUS(HarryAnim_Unk121, true);
                    break;

                case PlayerState_EnemyReleaseLowerFront:
                    animStatus = ANIM_STATUS(HarryAnim_Unk122, true);
                    break;

                case PlayerState_EnemyReleaseLowerBack:
                    animStatus = ANIM_STATUS(HarryAnim_Unk123, false);
                    break;

                case PlayerState_DamageHead:
                    animStatus = ANIM_STATUS(HarryAnim_Unk121, false);
                    break;

                case PlayerState_FallForward:
                    animStatus = ANIM_STATUS(HarryAnim_FallForward, false);
                    break;

                case PlayerState_FallBackward:
                    animStatus = ANIM_STATUS(HarryAnim_FallBackward, false);
                    break;
            }

            if (!(g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_FallForward && g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_KickEnemy))
            {
                func_8007FB94(chara, extra, animStatus);
            }

            D_800C4550 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            chara->flags_3E |= CharaFlag_Unk4;

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_GetUpFront:
                case PlayerState_GetUpBack:
                    chara->damage_B4.amount_C                  = Q12(0.0f);
                    chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);

                    if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

                        Player_ExtraStateSet(chara, extra, PlayerState_None);

                        g_SysWork.playerWork_4C.player_0.field_D4.radius_0  = Q12(0.3f);
                        g_SysWork.playerWork_4C.player_0.field_D4.field_2   = Q12(0.23f);
                        g_SysWork.playerWork_4C.player_0.field_C8.field_0   = Q12(-1.6f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_C8.field_2   = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_C8.field_6   = Q12(-1.1f);
                    }

                    chara->attackReceived_41 = NO_VALUE;

                default:
                    break;

                case PlayerState_EnemyReleasePinnedFront:
                case PlayerState_EnemyReleasePinnedBack:
                    chara->properties_E4.player.afkTimer_E8        = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);

                    if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
                    {
                        chara->field_D4.radius_0 = ((chara->model_0.anim_4.keyframeIdx_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4) * 0x4CC) / 21;
                    }
                    else
                    {
                        chara->field_D4.radius_0 = 0;
                    }

                    if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
                        switch (g_SysWork.playerWork_4C.extra_128.state_1C)
                        {
                            case PlayerState_EnemyReleasePinnedFront:
                                Player_ExtraStateSet(chara, extra, PlayerState_Unk43);
                                break;

                            case PlayerState_EnemyReleasePinnedBack:
                                Player_ExtraStateSet(chara, extra, PlayerState_Unk44);
                                break;
                        }

                        g_SysWork.playerWork_4C.player_0.field_D4.radius_0  = Q12(0.3f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);

                        chara->attackReceived_41 = NO_VALUE;
                    }
                    break;

                case PlayerState_EnemyReleaseUpperFront:
                case PlayerState_Unk17:
                case PlayerState_Unk18:
                case PlayerState_DamageHead:
                case PlayerState_EnemyReleaseUpperBack:
                case PlayerState_EnemyReleaseLowerFront:
                case PlayerState_EnemyReleaseLowerBack:
                    if (chara->model_0.anim_4.keyframeIdx_8 == (g_MapOverlayHeader.field_38[D_800AF220].time_4 + 4))
                    {
                        chara->attackReceived_41 = NO_VALUE;
                    }

                    if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

                        Player_ExtraStateSet(chara, extra, PlayerState_None);

                        chara->field_D4.radius_0 = Q12(0.3f);

                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
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

                    if (extra->model_0.controlState_2 == ModelState_Uninitialized && chara->position_18.vy >= chara->properties_E4.player.positionY_EC)
                    {
                        extra->model_0.controlState_2++;
                        func_8005DC1C(Sfx_Unk1317, &chara->position_18, Q8_CLAMPED(0.125f), 0);
                        chara->properties_E4.player.field_10C = 128;
                        func_80089470();
                    }

                    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_FallForward)
                    {
                        chara->properties_E4.player.field_10D = 0;
                        if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
                        {
                            g_SysWork.playerWork_4C.player_0.field_C8.field_0 = D_800AEEDC[chara->model_0.anim_4.keyframeIdx_8 - 379][0];
                            g_SysWork.playerWork_4C.player_0.field_C8.field_6 = D_800AEEDC[chara->model_0.anim_4.keyframeIdx_8 - 379][1];
                        }

                        if (chara->model_0.anim_4.keyframeIdx_8 == HARRY_BASE_ANIM_INFOS[45].endKeyframeIdx_E)
                        {
                            if (chara->position_18.vy > Q12(6.5f))
                            {
                                Player_ExtraStateSet(chara, extra, PlayerState_Death);
                            }
                            else
                            {
                                Player_ExtraStateSet(chara, extra, PlayerState_None);
                            }

                            g_SysWork.playerWork_4C.player_0.field_C8.field_0 = Q12(-1.6f);
                            g_SysWork.playerWork_4C.player_0.field_C8.field_2 = Q12(0.0f);
                            g_SysWork.playerWork_4C.player_0.field_C8.field_6 = Q12(-1.1f);

                            chara->field_D4.radius_0 = Q12(0.3f);
                        }
                    }
                    else
                    {
                        chara->properties_E4.player.field_10D = 1;

                        if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
                        {
                            g_SysWork.playerWork_4C.player_0.field_C8.field_0 = D_800AEF78[chara->model_0.anim_4.keyframeIdx_8 - 418][0];
                            g_SysWork.playerWork_4C.player_0.field_C8.field_6 = D_800AEF78[chara->model_0.anim_4.keyframeIdx_8 - 418][1];
                        }

                        if (chara->model_0.anim_4.keyframeIdx_8 == HARRY_BASE_ANIM_INFOS[47].endKeyframeIdx_E)
                        {
                            if (chara->position_18.vy > Q12(6.5f))
                            {
                                Player_ExtraStateSet(chara, extra, PlayerState_Death);
                            }
                            else
                            {
                                Player_ExtraStateSet(chara, extra, PlayerState_None);
                            }

                            g_SysWork.playerWork_4C.player_0.field_C8.field_0 = Q12(-1.6f);
                            g_SysWork.playerWork_4C.player_0.field_C8.field_2 = Q12(0.0f);
                            g_SysWork.playerWork_4C.player_0.field_C8.field_6 = Q12(-1.1f);

                            chara->field_D4.radius_0 = Q12(0.3f);
                        }
                    }
                    break;
            }

            chara->attackReceived_41 = NO_VALUE;
            break;

        case PlayerState_Unk43:
            func_8007FB94(chara, extra, ANIM_STATUS(130, true));

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(chara, extra, PlayerState_None);

                chara->field_D4.field_2 = Q12(0.23f);
            }
            break;

        case PlayerState_Unk44:
            func_8007FB94(chara, extra, ANIM_STATUS(131, false));

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(chara, extra, PlayerState_None);

                chara->field_D4.field_2 = Q12(0.23f);
            }
            break;

        case PlayerState_Unk36:
            chara->attackReceived_41 = NO_VALUE;
            func_8007FB94(chara, extra, ANIM_STATUS(126, false));

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12) >= chara->model_0.anim_4.keyframeIdx_8)
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12, Sfx_Unk1318);
                }
                else
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 30, Sfx_Unk1319);
                }
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model_0.controlState_2++;
                chara->health_B0 = Q12(100.0f);
                chara->model_0.controlState_2++;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                return;
            }
            break;

        case PlayerState_Death:
            chara->attackReceived_41 = NO_VALUE;
            func_8007FB94(chara, extra, ANIM_STATUS(101, false));
            chara->field_D4.field_2 = Q12(0.0f);

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12) >= chara->model_0.anim_4.keyframeIdx_8)
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 12, Sfx_Unk1318);
                }
                else
                {
                    func_80071620(chara->model_0.anim_4.status_0, chara, g_MapOverlayHeader.field_38[D_800AF220].time_4 + 32, Sfx_Unk1319);
                }

                temp_a2 = D_800AF070[chara->model_0.anim_4.keyframeIdx_8 - g_MapOverlayHeader.field_38[D_800AF220].time_4];

                if (chara->model_0.anim_4.keyframeIdx_8 != g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                {
                    var_v1_5 = D_800AF070[(chara->model_0.anim_4.keyframeIdx_8 + 1) - g_MapOverlayHeader.field_38[D_800AF220].time_4];
                }
                else
                {
                    var_v1_5 = temp_a2;
                }

                temp_s0_3                                    = temp_a2 + Q12_MULT(var_v1_5 - temp_a2, Q12_FRACT(chara->model_0.anim_4.time_4));
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12_MULT(temp_s0_3, Math_Sin(chara->rotation_24.vy));
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12_MULT(temp_s0_3, Math_Cos(chara->rotation_24.vy));
                chara->field_D4.radius_0                        = Q12(0.3f);
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
                {
                    g_MapOverlayHeader.playerAnimLock_DC();
                    Savegame_EventFlagSet(EventFlag_25);

                    func_8007E9C4();

                    extra->model_0.controlState_2++;
                    chara->health_B0 = Q12(100.0f);
                    chara->model_0.controlState_2++;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                    return;
                }

                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model_0.controlState_2++;
                chara->health_B0 = Q12(100.0f);
                chara->model_0.controlState_2++;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                return;
            }
            break;

        case PlayerState_InstantDeath:
            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                SD_Call(4731);
            }

            func_8007FB94(chara, extra, ANIM_STATUS(101, true));
            chara->field_D4.field_2 = Q12(0.0f);

            if (chara->model_0.anim_4.keyframeIdx_8 == (g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6 - 25))
            {
                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model_0.controlState_2++;
                chara->health_B0 = Q12(100.0f);
                chara->model_0.controlState_2++;
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
            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_DamageTorsoBack:
                    func_8007FB94(chara, extra, ANIM_STATUS(105, true));
                    break;

                case PlayerState_DamageTorsoFront:
                    func_8007FB94(chara, extra, ANIM_STATUS(105, false));
                    break;

                case PlayerState_DamageTorsoRight:
                    func_8007FB94(chara, extra, ANIM_STATUS(106, false));
                    break;

                case PlayerState_DamageTorsoLeft:
                    func_8007FB94(chara, extra, ANIM_STATUS(106, true));
                    break;

                case PlayerState_DamageFeetFront:
                    func_8007FB94(chara, extra, ANIM_STATUS(107, true));
                    break;

                case PlayerState_DamageFeetBack:
                    func_8007FB94(chara, extra, ANIM_STATUS(107, false));
                    break;

                case PlayerState_DamagePushBack:
                    func_8007FB94(chara, extra, ANIM_STATUS(123, true));
                    break;

                case PlayerState_DamagePushFront:
                    func_8007FB94(chara, extra, ANIM_STATUS(124, false));
                    break;
            }

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case PlayerState_DamagePushBack:
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.playerWork_4C.player_0.properties_E4.player.field_118, &sp1C);

                    if (ABS(sp1C) >= Q12_ANGLE(90.0f))
                    {
                        break;
                    }

                    if (ABS(sp1C) < Q12_ANGLE(5.7f))
                    {
                        chara->rotation_24.vy = g_SysWork.playerWork_4C.player_0.properties_E4.player.field_118;
                    }
                    else
                    {
                        chara->rotation_24.vy += (sp1C / ABS(sp1C)) << 6;
                    }
                    break;

                case PlayerState_DamagePushFront:
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.playerWork_4C.player_0.properties_E4.player.field_118, &sp1E);

                    if (ABS(sp1E) < Q12_ANGLE(90.0f))
                    {
                        break;
                    }

                    if (ABS(sp1E) >= Q12_ANGLE(174.4f))
                    {
                        chara->rotation_24.vy = Q12_ANGLE_NORM_U(g_SysWork.playerWork_4C.player_0.properties_E4.player.field_118 + Q12_ANGLE(180.0f));
                    }
                    else
                    {
                        chara->rotation_24.vy -= (sp1E / ABS(sp1E)) << 6;
                    }
                    break;
            }

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != 0)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f)) >> 2;

                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & 1)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (!(chara->attackReceived_41 >= 68 && chara->attackReceived_41 < 70))
            {
                g_Player_HeadingAngle                                                   = ratan2(chara->damage_B4.position_0.vx, chara->damage_B4.position_0.vz) - chara->rotation_24.vy;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = SQUARE(chara->damage_B4.position_0.vx) + SQUARE(chara->damage_B4.position_0.vz) + SQUARE(chara->damage_B4.position_0.vy);
            }

            if (extra->model_0.anim_4.keyframeIdx_8 == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                chara->attackReceived_41                                         = NO_VALUE;
                g_SysWork.targetNpcIdx_2353                                      = NO_VALUE;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

                Player_ExtraStateSet(chara, extra, PlayerState_None);

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            }

            D_800C4550       = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            chara->flags_3E |= CharaFlag_Unk4;
            break;

        case PlayerState_KickEnemy:
            func_80070DF0(extra, chara, WEAPON_ATTACK(EquippedWeaponId_Unk8, AttackInputType_Tap), ANIM_STATUS(24, true));
            break;

        case PlayerState_StompEnemy:
            func_80070DF0(extra, chara, WEAPON_ATTACK(EquippedWeaponId_Unk9, AttackInputType_Tap), ANIM_STATUS(25, true));
            break;
    }

    chara->rotation_24.vy       = Q12_ANGLE_NORM_U(chara->rotation_24.vy + (D_800C454C >> 4) + Q12_ANGLE(360.0f));
    chara->headingAngle_3C      = Q12_ANGLE_NORM_U((chara->rotation_24.vy + g_Player_HeadingAngle) + Q12_ANGLE(360.0f));
    chara->moveSpeed_38        = D_800C4550;
    chara->fallSpeed_34        += g_GravitySpeed;
    chara->rotationSpeed_2C.vy  = (D_800C454C << 8) / g_DeltaTime;
    coords->flg                 = false;

    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

void Player_UpperBodyStateUpdate(s_PlayerExtra* extra, e_PlayerUpperBodyState upperState, s32 unused, s32 arg3) // 0x80073FC0
{
    e_PlayerUpperBodyState prevState;
    s_Model*         charaModel;

    prevState  = g_SysWork.playerWork_4C.extra_128.upperBodyState_20;
    charaModel = &g_SysWork.playerWork_4C.player_0.model_0;

    switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_WalkForward:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_WalkForward;

        default:
            break;

        case PlayerLowerBodyState_RunForward:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunForward;
            break;

        case PlayerLowerBodyState_WalkBackward:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_WalkBackward;
            break;

        case PlayerLowerBodyState_SidestepRight:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepRight;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepLeft;
            break;

        case PlayerLowerBodyState_RunRight:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRight;
            break;

        case PlayerLowerBodyState_RunLeft:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeft;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_QuickTurnRight;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_QuickTurnLeft;
            break;

        case PlayerLowerBodyState_JumpBackward:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunWallStop;
            break;

        case PlayerLowerBodyState_Stumble:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_LowerBodyStumble;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeftWallStop;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRightWallStop;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeftStumble;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_SidestepRightStumble;
            break;

        case PlayerLowerBodyState_None:
            switch (arg3)
            {
                case 0:
                case 2:
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    break;

                case 1:
                    if (!g_Player_IsTurningRight)
                    {
                        if (g_Player_IsTurningLeft)
                        {
                            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnLeft;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnRight;
                    }
                    break;

                case 3:
                    if (g_Player_IsTurningLeft)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnLeft;
                        break;
                    }

                    if (!g_Player_IsTurningRight)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    }
                    break;

                case 4:
                    if (g_Player_IsTurningRight)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_TurnRight;
                        break;
                    }

                    if (!g_Player_IsTurningLeft)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                    }
                    break;
            }
            break;
    }

    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != upperState)
    {
        extra->model_0.stateStep_3 = 0;
        extra->model_0.controlState_2     = ModelState_Uninitialized;
    }

    switch (prevState)
    {
        case PlayerUpperBodyState_WalkForward:
            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_RunForward)
            {
                break;
            }

            extra->model_0.anim_4.status_0      = charaModel->anim_4.status_0;
            extra->model_0.anim_4.keyframeIdx_8 = charaModel->anim_4.keyframeIdx_8;
            extra->model_0.anim_4.time_4         = charaModel->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;

        case PlayerUpperBodyState_RunForward:
            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_WalkForward)
            {
                break;
            }

            extra->model_0.anim_4.status_0      = charaModel->anim_4.status_0;
            extra->model_0.anim_4.keyframeIdx_8 = charaModel->anim_4.keyframeIdx_8;
            extra->model_0.anim_4.time_4         = charaModel->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;
    }
}

void Player_UpperBodyUpdate(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x80074254
{
    s32 stumbleSfx;

    if (Player_UpperBodyMainUpdate(chara, extra))
    {
        return;
    }

    stumbleSfx = (D_800C45C8.field_1 == 10) ? Sfx_Stumble1 : Sfx_Stumble0;

    switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
            func_80071620(55, chara, 551, Sfx_HarryHeavyBreath);
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

bool Player_UpperBodyMainUpdate(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x80075504
{
    s32        enemyAttackedIdx;
    s16        sp20;
    s16        sp22;
    s32        currentAmmoVar;
    s32        totalAmmoVar;
    s32        temp_s1_2;
    s16        temp_v0_3;
    s16        temp_v1_3;
    s32        i;
    s16        var_s0;
    s32        playerTurn;
    static s32 D_800C44D0;
    static s32 D_800C44D4;

    bool Player_CombatAnimUpdate(void) // 0x80074350
    {
        s16 ssp20;
        s16 temp_a1;
        s32 keyframeIdx0;
        s32 keyframeIdx1;
        u8  weaponAttack;

        weaponAttack = g_SysWork.playerCombat_38.weaponAttack_F;

        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
                keyframeIdx0 = 619;
                keyframeIdx1 = 613;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
                keyframeIdx0 = 630;
                keyframeIdx1 = 624;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap):
                keyframeIdx0 = 568;
                keyframeIdx1 = 568;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Axe, AttackInputType_Tap):
                keyframeIdx0 = 625;
                keyframeIdx1 = 618;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,    AttackInputType_Tap):
                keyframeIdx0 = 648;
                keyframeIdx1 = 642;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Katana, AttackInputType_Tap):
                keyframeIdx0 = 619;
                keyframeIdx1 = 612;
                break;

            default:
                keyframeIdx1 = 0;
                keyframeIdx0 = 0;
                break;
        }

        if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat)
        {
            g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104 += g_DeltaTime;

            if (!g_GameWork.config_0.optExtraWeaponCtrl_23)
            {
                g_Player_HasActionInput      = false;
                g_Player_HasMoveInput        = false;
                g_Player_IsShooting          = false;
                g_Player_IsAttacking         = false;
                g_Player_IsHoldAttack        = false;
                g_Player_IsAiming            = false;
                g_Player_IsRunning           = false;
                g_Player_IsMovingBackward    = false;
                g_Player_IsMovingForward     = false;
                g_Player_IsSteppingRightTap  = false;
                g_Player_IsSteppingRightHold = false;
                g_Player_IsTurningRight      = false;
                g_Player_IsSteppingLeftTap   = false;
                g_Player_IsSteppingLeftHold  = false;
                g_Player_IsTurningLeft       = false;
            }
        }

        // Attack type (except melee multitap) and animation.
        if (extra->model_0.controlState_2 == ModelState_Uninitialized)
        {
            g_Player_MeleeAttackType  = 0;
            g_Player_IsMultiTapAttack = 0;

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;

            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_Player_MeleeAttackType    = 0;
                g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8;
                D_800AF220                  = g_Player_EquippedWeaponInfo.field_A >> 4;
            }
            else if (g_Player_IsAttacking && g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                g_Player_MeleeAttackType = 1;
                g_Player_AttackAnimIdx   = g_Player_EquippedWeaponInfo.animAttackHold_8 - 4;
                D_800AF220               = (g_Player_EquippedWeaponInfo.field_A >> 4) - 2;
            }
            else
            {
                g_Player_MeleeAttackType = 0;

                // Handle Rock Drill animation.
                if (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) ||
                    g_Player_RockDrill_DirectionAttack == 0)
                {
                    g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8;
                    D_800AF220             = g_Player_EquippedWeaponInfo.field_A >> 4;
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

            extra->model_0.controlState_2++;

            if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_SysWork.playerCombat_38.weaponAttack_F = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F), AttackInputType_Tap);
            }

            g_SysWork.playerCombat_38.weaponAttack_F += g_Player_MeleeAttackType * 10; // TODO: Macro for this?

            D_800C44D0 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx_C + D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_E;
            D_800C44D4 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx_C + D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_E +
                         D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_F;
        }

        // Used for make continuos/hold shooting smoother?
        if (g_SysWork.targetNpcIdx_2353 != NO_VALUE &&
            g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (!g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(10.0f), 0);
                    func_8005D50C(&g_Player_TargetNpcIdx, &D_800C4554, &D_800C4556, &g_SysWork.playerCombat_38, enemyAttackedIdx, Q12_ANGLE(20.0f));
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(3.0f), 0);
                    func_8005D50C(&g_Player_TargetNpcIdx, &D_800C4554, &D_800C4556, &g_SysWork.playerCombat_38, enemyAttackedIdx, Q12_ANGLE(20.0f));
                }
            }
            else
            {
                enemyAttackedIdx = g_SysWork.targetNpcIdx_2353;
            }

            if (enemyAttackedIdx == NO_VALUE && enemyAttackedIdx == g_Player_TargetNpcIdx)
            {
                D_800C4556 = NO_VALUE;
                D_800C4554 = NO_VALUE;
            }

            if (enemyAttackedIdx == g_SysWork.targetNpcIdx_2353)
            {
                chara->field_2A = Q12_FRACT(ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                   (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork_4C.player_0.position_18.vz) +
                                            Q12_ANGLE(360.0f));
            }
            else
            {
                chara->field_2A = chara->rotation_24.vy;
            }

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk30, false);
                extra->model_0.stateStep_3++;
            }
        }
        else
        {
            if (g_SysWork.targetNpcIdx_2353 != NO_VALUE && !g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(3.0f), Q12(3.0f), 5);
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(1.0f), Q12(1.0f), 5);
                }

                if (enemyAttackedIdx == g_SysWork.targetNpcIdx_2353)
                {
                    temp_a1 = Q12_FRACT(ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                               (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork_4C.player_0.position_18.vz) + Q12(1.0f));

                    Math_ShortestAngleGet(chara->rotation_24.vy, temp_a1, &ssp20);
                    D_800C454C = g_DeltaTime * 0xF;

                    if (ABS(ssp20) >= 0x80)
                    {
                        if (ssp20 < 0)
                        {
                            D_800C454C = -D_800C454C;
                        }
                    }
                    else
                    {
                        chara->field_2A = chara->rotation_24.vy = temp_a1;
                        D_800C454C             = 0;
                    }
                }
            }
            else
            {
                enemyAttackedIdx                                           = NO_VALUE;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122 = Q12_ANGLE(90.0f);
                chara->field_2A                                            = chara->rotation_24.vy;
            }

            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
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
            else if (g_Player_IsAttacking && g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) ||
                     g_Player_RockDrill_DirectionAttack == 0)
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
        if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model_0.anim_4.keyframeIdx_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx_8)
                {
                    if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                    {
                        chara->field_44.field_0 = 1;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, Q8_CLAMPED(0.5f), 0);

                        chara->properties_E4.player.field_10C                       = 0x40;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                    }
                }
                else if (D_800C44D4 < extra->model_0.anim_4.keyframeIdx_8)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 == Q12(0.0f))
            {
                if (extra->model_0.anim_4.keyframeIdx_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx_8 &&
                    !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                {
                    chara->field_44.field_0                                     = 1;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else
            {
                if (chara->field_44.field_0 <= 0)
                {
                    chara->field_44.field_0 = 1;
                }

                chara->properties_E4.player.field_10C = 0x40;
            }
        }
        else
        {
            if (extra->model_0.anim_4.keyframeIdx_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx_8 &&
                !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Shooting))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Shooting;

                if (g_SysWork.playerCombat_38.currentWeaponAmmo_10 != 0)
                {
                    chara->field_44.field_0 = 1;

                    if (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                    {
                        g_SysWork.playerCombat_38.currentWeaponAmmo_10--;
                        g_SavegamePtr->items_0[g_SysWork.playerCombat_38.weaponInventoryIdx_12].count_1--;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                    }
                    else
                    {
                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &chara->position_18, Q8_CLAMPED(0.19f), 0);
                    }

                    chara->properties_E4.player.field_10C = 0xC8;
                }
                else
                {
                    func_8005DC1C(g_Player_EquippedWeaponInfo.outOfAmmoSfx_4, &chara->position_18, Q8_CLAMPED(0.5f), 0);

                    chara->properties_E4.player.field_10C = 32;
                    extra->model_0.anim_4.keyframeIdx_8  = D_800C44F0[D_800AF220].field_6 - 3;
                    extra->model_0.anim_4.time_4          = Q12(D_800C44F0[D_800AF220].field_6 - 3);

                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                    {
                        chara->model_0.anim_4.keyframeIdx_8 = D_800C44F0[D_800AF220].field_6 - 3;
                        chara->model_0.anim_4.time_4         = Q12(D_800C44F0[D_800AF220].field_6 - 3);
                    }
                }
            }
        }

        // Finish attack animation.
        // Though more context about `D_800AF220` and `D_800C44F0` is required,
        // they likely indicate if an attack animation has finished.
        if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            // Attack anim.
            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
            {
                if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[D_800AF220].field_6)
                {
                    extra->model_0.anim_4.status_0      = ANIM_STATUS(HarryAnim_HandgunAim, true);
                    extra->model_0.anim_4.keyframeIdx_8 = D_800C44F0[0].field_6;
                    extra->model_0.anim_4.time_4         = Q12(extra->model_0.anim_4.keyframeIdx_8);

                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
                    {
                        g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_Combat;
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_None;
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                        extra->model_0.controlState_2                          = extra->model_0.stateStep_3 = 0;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Aim;
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }

                    g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104  = 0;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
                    g_SysWork.playerCombat_38.weaponAttack_F                = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F), AttackInputType_Tap);
                    return true;
                }
            }
        }
        // Attack anim.
        else if ((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true) ||
                  extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk36, true)) &&
                 extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[D_800AF220].field_6)
        {
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
            {
                g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_Combat;
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                }
            }
            else
            {
                g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_None;
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                extra->model_0.controlState_2                          = extra->model_0.stateStep_3 = 0;

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Aim;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    chara->model_0.controlState_2                                      =
                    chara->model_0.stateStep_3                                  = 0;
                }
            }

            D_800C4556                                                  = NO_VALUE;
            D_800C4554                                                  = NO_VALUE;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104  = 0;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Shooting;
            return true;
        }

        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;

        // Handles multitap attack.
        if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (g_Player_MeleeAttackType == 0 && g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model_0.anim_4.keyframeIdx_8 >= keyframeIdx1 &&
                    extra->model_0.anim_4.keyframeIdx_8 < keyframeIdx0 &&
                    extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true) &&
                    (g_Player_IsAttacking || g_Player_IsShooting))
                {
                    g_Player_IsMultiTapAttack = true;
                }
            }
        }

        if (g_Player_IsMultiTapAttack)
        {
            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true) &&
                extra->model_0.anim_4.keyframeIdx_8 >= keyframeIdx0)
            {
                extra->model_0.stateStep_3 = 0;

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    chara->model_0.stateStep_3 = 0;
                }

                g_Player_AttackAnimIdx                       = g_Player_EquippedWeaponInfo.animAttackHold_8 - 2;
                D_800AF220                                   = (g_Player_EquippedWeaponInfo.field_A >> 4) - 1;
                g_Player_MeleeAttackType                     = 2;
                g_SysWork.playerCombat_38.weaponAttack_F = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(weaponAttack), AttackInputType_Multitap);

                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 2;
                    extra->model_0.stateStep_3++;
                }

                D_800C44D0 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx_C + D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_E;
                D_800C44D4 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx_C + D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_E +
                             D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_F;
                g_Player_IsMultiTapAttack = 0;

                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
            }
        }

        return false;
    }

    enemyAttackedIdx = NO_VALUE;

    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimTargetLock && g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_Attack)
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104 = 0;
    }

    switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_None:
            if ((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_WalkForward, true) ||
                 extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForward, true)) &&
                extra->model_0.stateStep_3 != 0)
            {
                extra->model_0.stateStep_3 = 0;
            }

            // Set idle animation.
            if (chara->properties_E4.player.exhaustionTimer_FC < Q12(10.0f) && chara->health_B0 >= Q12(30.0f))
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                    extra->model_0.stateStep_3++;
                }

                Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 53, 1);
            }
            else
            {
                chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);

                // If not normal idle anim, set it and update `upperBodyState_20`.
                if (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Idle, true))
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                        extra->model_0.stateStep_3++;
                    }

                    Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 55, 1);
                }
                else
                {
                    extra->model_0.stateStep_3 = 0;
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_IdleExhausted, false);
                        extra->model_0.stateStep_3++;
                    }
                }
            }

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_None)
            {
                chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
            }

            chara->field_2A = chara->rotation_24.vy;

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_None)
            {
                chara->properties_E4.player.afkTimer_E8++;

                if (chara->properties_E4.player.afkTimer_E8 >= 300)
                {
                    if (chara->health_B0 >= Q12(60.0f))
                    {
                        chara->properties_E4.player.afkTimer_E8             = Q12(0.0f);
                        // TODO: `Player_ExtraStateSet` doesn't match?
                        g_SysWork.playerWork_4C.extra_128.state_1C              = PlayerState_Idle;
                        chara->model_0.controlState_2 = chara->model_0.stateStep_3 = 0;
                        extra->model_0.controlState_2 = extra->model_0.stateStep_3 = 0;
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20     = PlayerUpperBodyState_None;
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24     = PlayerLowerBodyState_None;
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
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_WalkForward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_WalkForward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkForward, 5, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunForward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunForward, 7, 2);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunWallStop:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardWallStopRight, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 19, 0);
            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 21, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_SidestepRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRight, 13, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_SidestepLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepLeft, 11, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRight, 17, 0);
            chara->field_2A = chara->rotation_24.vy;

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRight, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case PlayerUpperBodyState_RunLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeft, 15, 0);
            chara->field_2A = chara->rotation_24.vy;

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeft, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case PlayerUpperBodyState_WalkBackward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_WalkBackward, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkBackward, 9, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_QuickTurnRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_QuickTurnRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnRight, 29, 0);

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_QuickTurnRight, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_QuickTurnLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_QuickTurnLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnLeft, 31, 0);

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_QuickTurnLeft, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_TurnRight:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_TurnRight, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnRight, 27, 3);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_TurnLeft:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_TurnLeft, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnLeft, 25, 4);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunJumpBackward:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_JumpBackward, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_JumpBackward, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunJumpBackward, 33, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_LowerBodyStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForwardStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_LowerBodyStumble, 23, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunLeftWallStop:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunLeftWallStop, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftWallStop, 0x25, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunRightWallStop:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRightWallStop, false);
                extra->model_0.stateStep_3++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRightWallStop, 41, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_RunLeftStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunLeftStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeftStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftStumble, 39, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_SidestepRightStumble:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRightStumble, false);
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRightStumble, true))
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRightStumble, 43, 0);
            chara->field_2A = chara->rotation_24.vy;
            break;

        case PlayerUpperBodyState_Aim:
            g_SysWork.targetNpcIdx_2353 = NO_VALUE;

            if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
                {
                    if (chara->field_44.field_0 <= 0)
                    {
                        chara->field_44.field_0 = 1;
                    }

                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk34, false);
                        extra->model_0.stateStep_3++;
                    }
                }
                else
                {
                    extra->model_0.anim_4.status_0      = ANIM_STATUS(HarryAnim_HandgunAim, true);
                    extra->model_0.anim_4.keyframeIdx_8 = D_800AF5C6;
                    extra->model_0.anim_4.time_4         = D_800AF5C6 << 12;
                }
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            chara->field_2A                                             = chara->rotation_24.vy;

            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                // Aim.
                if (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                    extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk34, true))
                {
                    if (g_Player_IsAttacking || g_Player_IsShooting)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk11;
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;

                        if (extra->model_0.stateStep_3 == 0)
                        {
                            extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk34, false);
                            extra->model_0.stateStep_3++;
                        }
                    }
                }
                else
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;
                }
            }
            break;

        case PlayerUpperBodyState_AimTargetLock:
            g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104 += g_DeltaTime;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;

            if (g_Player_IsTurningRight)
            {
                playerTurn = 1;
            }
            else
            {
                playerTurn = (g_Player_IsTurningLeft != false) * 2;
            }

            if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk29, true) || extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[1].field_6) &&
                (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk30, true) || extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[2].field_6) &&
                (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk32, true) || extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[4].field_6))
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
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->properties_E4.player.field_F4                 = g_Player_FlexRotationX;

                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(2.0f / 3.0f), Q12(10.0f), playerTurn);
                }
                else
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(1.0f / 3.0f), Q12(3.0f), playerTurn);
                }

                if (g_Player_TargetNpcIdx == NO_VALUE)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122  = Q12_ANGLE(90.0f);
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    g_Player_IsShooting                                         = false;
                    g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_None;
                    g_Player_IsAttacking                                        = false;
                    extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;

                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        chara->model_0.controlState_2                          = chara->model_0.stateStep_3 = 0;
                    }
                }
                else
                {
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20         = PlayerUpperBodyState_AimTargetLockSwitch;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk12;
                    extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;
                }

                g_SysWork.targetNpcIdx_2353 = g_Player_TargetNpcIdx;
            }
            else
            {
                if (extra->model_0.controlState_2 != ModelState_Uninitialized)
                {
                    if (g_TargetEnemyPosition.vx != g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vx ||
                        g_TargetEnemyPosition.vy != g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vy ||
                        g_TargetEnemyPosition.vz != g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vz ||
                        g_Player_PrevPosition.vx != g_SysWork.playerWork_4C.player_0.position_18.vx ||
                        g_Player_PrevPosition.vy != g_SysWork.playerWork_4C.player_0.position_18.vy ||
                        g_Player_PrevPosition.vz != g_SysWork.playerWork_4C.player_0.position_18.vz)
                    {
                        if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                        {
                            func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(10.0f), 0);
                        }
                        else
                        {
                            func_8005CD38(&enemyAttackedIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x11C, Q12(3.0f), 0);
                        }

                        g_TargetEnemyPosition = g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18;
                    }
                    else
                    {
                        enemyAttackedIdx = g_SysWork.targetNpcIdx_2353;
                    }
                }
                else
                {
                    enemyAttackedIdx      = g_SysWork.targetNpcIdx_2353;
                    g_TargetEnemyPosition = g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18;
                }

                if (enemyAttackedIdx == g_SysWork.targetNpcIdx_2353 && enemyAttackedIdx != NO_VALUE)
                {
                    chara->field_2A = Q12_FRACT(ratan2((g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vx + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                       (g_SysWork.npcs_1A0[enemyAttackedIdx].position_18.vz + g_SysWork.npcs_1A0[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork_4C.player_0.position_18.vz) +
                                                Q12_ANGLE(360.0f));
                }
                else
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122  = Q12_ANGLE(90.0f);
                    g_SysWork.targetNpcIdx_2353                                 = NO_VALUE;
                    g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_None;
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;
                }
            }

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }
            break;

        case PlayerUpperBodyState_AimStart:
            chara->field_2A = chara->rotation_24.vy;

            if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk33, false);
                        extra->model_0.stateStep_3++;
                    }
                }
                else if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunAim, false);
                    extra->model_0.stateStep_3++;
                }

                if (((g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) &&
                      extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                      extra->model_0.anim_4.keyframeIdx_8 >= (D_800C44F0[0].field_4 + 5)) ||
                     (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) &&
                      extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                      extra->model_0.anim_4.keyframeIdx_8 >= (D_800C44F0[0].field_4 + 9))) &&
                    !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(60.0f);

                    func_8004C564(g_SysWork.playerCombat_38.weaponAttack_F, 0);

                    chara->properties_E4.player.field_10C                       = 0x40;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap))
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk29, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunAim, false);
                    extra->model_0.stateStep_3++;
                }
            }

            if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[5].field_6)
                {
                    if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6)
                    {
                        func_8004C564(g_SysWork.playerCombat_38.weaponAttack_F, 1);
                    }

                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                    extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
                    {
                        chara->field_44.field_0 = 1;
                    }
                }
            }
            else
            {
                if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[1].field_6)
                {
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Aim;
                }
            }
            break;

        case PlayerUpperBodyState_AimStartTargetLock:
        case PlayerUpperBodyState_AimTargetLockSwitch:
            sp22 = 0;

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (g_GameWork.config_0.optExtraAutoAiming_2C)
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(10.0f), 0);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(3.0f), 0);
                    }
                }
                else if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(3.0f), Q12(7.0f), 4);
                }
                else
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(0.9f), Q12(2.1f), 4);
                }

                g_SysWork.targetNpcIdx_2353 = g_Player_TargetNpcIdx;
            }

            D_800AF220 = 1;
            chara->properties_E4.player.field_100++;

            if (!g_GameWork.config_0.optExtraWeaponCtrl_23)
            {
                g_Player_HasActionInput      = false;
                g_Player_HasMoveInput        = false;
                g_Player_IsShooting          = false;
                g_Player_IsAttacking         = false;
                g_Player_IsHoldAttack        = false;
                g_Player_IsAiming            = false;
                g_Player_IsRunning           = false;
                g_Player_IsMovingBackward    = false;
                g_Player_IsMovingForward     = false;
                g_Player_IsSteppingRightTap  = false;
                g_Player_IsSteppingRightHold = false;
                g_Player_IsTurningRight      = false;
                g_Player_IsSteppingLeftTap   = false;
                g_Player_IsSteppingLeftHold  = false;
                g_Player_IsTurningLeft       = false;
            }

            extra->model_0.controlState_2++;

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk32, false);
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk29, false);
                extra->model_0.stateStep_3++;
            }

            if (g_SysWork.targetNpcIdx_2353 == NO_VALUE)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122  = Q12_ANGLE(90.0f);
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;
                break;
            }

            if (!g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vx + g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetX_0) - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                   (g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vz + g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetZ_2) - g_SysWork.playerWork_4C.player_0.position_18.vz);

                temp_s1_2 = Q12_ANGLE_NORM_U(temp_v0_3 + Q12_ANGLE(360.0f));

                switch (extra->model_0.anim_4.status_0)
                {
                    case ANIM_STATUS(HarryAnim_Unk29, true):
                    case ANIM_STATUS(HarryAnim_Unk32, true):
                        if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[D_800AF220].field_6)
                        {
                            chara->rotation_24.vy = temp_s1_2;
                        }
                        break;
                }

                Math_ShortestAngleGet(chara->rotation_24.vy, temp_s1_2, &sp20);

                D_800C454C = ((extra->model_0.controlState_2 * 3) + 12) * g_DeltaTime;
                D_800C454C = CLAMP(D_800C454C, 0, 0xFFF);

                if (ABS(sp20) >= Q12_ANGLE(11.25f))
                {
                    if (sp20 < Q12_ANGLE(0.0f))
                    {
                        D_800C454C = -D_800C454C;
                    }
                }
                else
                {
                    chara->rotation_24.vy  = temp_s1_2;
                    D_800C454C             = 0;
                    chara->field_2A        = temp_s1_2;

                    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                    }

                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                    {
                        if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[4].field_6)
                        {
                            g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                                chara->model_0.controlState_2                          =
                                chara->model_0.stateStep_3                      = 0;
                            }

                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                            extra->model_0.controlState_2                                      =
                            extra->model_0.stateStep_3                                  = 0;
                        }
                    }
                    else if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;
                        extra->model_0.controlState_2                          =
                        extra->model_0.stateStep_3                      = 0;
                    }
                }

                chara->field_2A = chara->rotation_24.vy;
                break;
            }

            temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vx +
                                g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetX_0) -
                               g_SysWork.playerWork_4C.player_0.position_18.vx,
                                (g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].position_18.vz +
                                 g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353].field_D8.offsetZ_2) -
                                g_SysWork.playerWork_4C.player_0.position_18.vz);

            temp_s1_2 = Q12_ANGLE_NORM_U(temp_v0_3 + Q12_ANGLE(360.0f));

            Math_ShortestAngleGet(chara->rotation_24.vy, temp_s1_2, &sp20);

            sp20      = CLAMP(sp20, -0x180, 0x180);

            temp_v1_3 = g_DeltaTime * 0xF;
            temp_v1_3 = CLAMP(temp_v1_3, 0, 0xFFF);
            var_s0    = temp_v1_3;

            Math_ShortestAngleGet(chara->field_2A, temp_s1_2, &sp22);

            if (ABS(sp22) > Q12_ANGLE(11.25f))
            {
                if (sp22 < Q12_ANGLE(0.0f))
                {
                    var_s0 = -var_s0;
                }

                chara->field_2A = Q12_ANGLE_NORM_U((chara->field_2A + (var_s0 >> 4)) + Q12_ANGLE(360.0f));
            }
            else
            {
                chara->field_2A = chara->rotation_24.vy + sp20;

                if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                }
                else
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                }

                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                {
                    if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.controlState_2                          = chara->model_0.stateStep_3 = 0;
                        }

                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                        extra->model_0.controlState_2                                      = extra->model_0.stateStep_3 = 0;
                    }
                }
                else if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[4].field_6)
                {
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLock;
                    extra->model_0.controlState_2 = extra->model_0.stateStep_3 = 0;
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

            if (extra->model_0.anim_4.keyframeIdx_8 == D_800C44F0[D_800AF220].field_4 ||
                ((g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunForward || g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunRight ||
                  g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunLeft) &&
                 (extra->model_0.anim_4.keyframeIdx_8 <= D_800C44F0[D_800AF220].field_6)))
            {
                switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
                {
                    case PlayerLowerBodyState_RunForward:
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunForward;
                        break;

                    case PlayerLowerBodyState_RunRight:
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunRight;
                        break;

                    case PlayerLowerBodyState_AimRunLeft:
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunLeft;
                        break;

                    default:
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
                        break;
                }

                extra->model_0.controlState_2 = extra->model_0.stateStep_3 = 0;
                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
                {
                    chara->model_0.controlState_2 = chara->model_0.stateStep_3 = 0;
                }

                g_SysWork.targetNpcIdx_2353 = NO_VALUE;
            }

            chara->field_2A = chara->rotation_24.vy;
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
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunRecoil, false);
                extra->model_0.stateStep_3++;
            }

            if ((D_800AF624 + g_Player_EquippedWeaponInfo.field_9) <= extra->model_0.anim_4.keyframeIdx_8 &&
                !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
            {
                func_8005DC1C(g_Player_EquippedWeaponInfo.reloadSfx_2, &chara->position_18, Q8_CLAMPED(0.5f), 0);

                chara->properties_E4.player.field_10C                       = 0x20;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
            }

            if (extra->model_0.anim_4.keyframeIdx_8 == D_800AF626)
            {
                g_Player_TargetNpcIdx                                       = NO_VALUE;
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Aim;
                g_SysWork.targetNpcIdx_2353                                 = NO_VALUE;
                g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                extra->model_0.anim_4.status_0                              = ANIM_STATUS(HarryAnim_HandgunAim, true);
                extra->model_0.anim_4.keyframeIdx_8                         = 588;
                extra->model_0.anim_4.time_4                                = Q12(588.0f);

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Reload)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                }

                if (g_SysWork.playerCombat_38.totalWeaponAmmo_11 != 0)
                {
                    currentAmmoVar = g_SysWork.playerCombat_38.currentWeaponAmmo_10;
                    totalAmmoVar   = g_SysWork.playerCombat_38.totalWeaponAmmo_11;

                    Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombat_38.weaponAttack_F);

                    g_SysWork.playerCombat_38.currentWeaponAmmo_10 = currentAmmoVar;
                    g_SysWork.playerCombat_38.totalWeaponAmmo_11   = totalAmmoVar;

                    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                    {
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat_38.weaponAttack_F + InventoryItemId_KitchenKnife))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat_38.currentWeaponAmmo_10;
                        }
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat_38.weaponAttack_F + InventoryItemId_Handgun))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat_38.totalWeaponAmmo_11;
                        }
                    }
                }
            }
            break;
    }

    return false;
}

void Player_CombatStateUpdate(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x800771BC
{
    s32 currentAmmoVar;
    s32 totalAmmoVar;
    s32 i;

    // Lock player view onto enemy.
    switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
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
                if ((g_Player_IsAiming && g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap)) ||
                    g_SysWork.playerCombat_38.isAiming_13)
                {
                    g_SysWork.playerCombat_38.isAiming_13 = true;

                    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                    {
                        g_Player_TargetNpcIdx = NO_VALUE;
                    }
                    else
                    {
                        if (g_GameWork.config_0.optExtraAutoAiming_2C)
                        {
                            if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                            {
                                func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(10.0f), 0);
                            }
                            else
                            {
                                func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, 0x238, Q12(3.0f), 0);
                            }
                        }
                        else if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                        {
                            func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(3.0f), Q12(7.0f), 4);
                        }
                        else
                        {
                            func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(0.9f), Q12(2.1f), 4);
                        }
                    }

                    g_SysWork.targetNpcIdx_2353 = g_Player_TargetNpcIdx;
                    if (g_SysWork.targetNpcIdx_2353 == NO_VALUE)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20            = PlayerUpperBodyState_AimStart;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122 = Q12_ANGLE(90.0f);
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_Combat;
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimStartTargetLock;
                    }

                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.controlState_2                          = ModelState_Uninitialized;
                    }
                    else if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 += PlayerLowerBodyState_Aim;
                    }

                    extra->model_0.stateStep_3            = 0;
                    extra->model_0.controlState_2                = ModelState_Uninitialized;
                    chara->properties_E4.player.field_100 = 0;

                    if (g_SysWork.playerCombat_38.totalWeaponAmmo_11 != 0)
                    {
                        if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                        {
                            currentAmmoVar = g_SysWork.playerCombat_38.currentWeaponAmmo_10;
                            totalAmmoVar   = g_SysWork.playerCombat_38.totalWeaponAmmo_11;

                            Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombat_38.weaponAttack_F);

                            g_SysWork.playerCombat_38.currentWeaponAmmo_10 = currentAmmoVar;
                            g_SysWork.playerCombat_38.totalWeaponAmmo_11   = totalAmmoVar;
                        }
                    }

                    if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                    {
                        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                        {
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat_38.weaponAttack_F + InventoryItemId_KitchenKnife))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat_38.currentWeaponAmmo_10;
                            }
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat_38.weaponAttack_F + InventoryItemId_Handgun))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat_38.totalWeaponAmmo_11;
                            }
                        }
                    }
                }
            }
            break;
    }

    // Execute finishing move on knocked enemies.
    switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
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
                    Player_ExtraStateSet(chara, extra, PlayerState_StompEnemy);
                    return;
                }

                if (g_Player_IsShooting)
                {
                    Player_ExtraStateSet(chara, extra, PlayerState_KickEnemy);
                    return;
                }
            }
            break;
    }

    // Handle aim state.
    switch (g_SysWork.playerWork_4C.extra_128.upperBodyState_20)
    {
        case PlayerUpperBodyState_Aim:
        case PlayerUpperBodyState_AimTargetLock:
            // Stop aiming.
            if (( g_GameWork.config_0.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                (!g_GameWork.config_0.optExtraWeaponCtrl_23 &&  g_Player_IsAiming))
            {
                chara->properties_E4.player.field_F4                        = 0;
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_AimStop;
                g_SysWork.targetNpcIdx_2353                                 = NO_VALUE;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;
                g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_None;
                g_SysWork.playerCombat_38.isAiming_13                   = false;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.controlState_2                          = ModelState_Uninitialized;
                    extra->model_0.stateStep_3                      = 0;
                    extra->model_0.controlState_2                          = ModelState_Uninitialized;
                    break;
                }

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_AimWalkForward)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 -= PlayerLowerBodyState_Aim;
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.controlState_2     = ModelState_Uninitialized;
                break;
            }

            if ((g_Player_IsAttacking || g_Player_IsShooting) &&
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_AimQuickTurnRight &&
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_AimQuickTurnLeft)
            {
                if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                        g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
                    {
                        if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk29, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk34, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 < D_800C44F0[6].field_4 ||
                             D_800C44F0[6].field_6 < extra->model_0.anim_4.keyframeIdx_8) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk30, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[3].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk33, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[5].field_6))
                        {
                            break;
                        }
                    }
                    else
                    {
                        if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk29, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk30, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                             extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[3].field_6))
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if ((extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[0].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk29, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[1].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk30, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[2].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[3].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk32, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[4].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk36, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[8].field_6) &&
                        (extra->model_0.anim_4.status_0 != ANIM_STATUS(HarryAnim_Unk34, true) ||
                         extra->model_0.anim_4.keyframeIdx_8 != D_800C44F0[6].field_4))
                    {
                        break;
                    }
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;

                if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(3.0f), Q12(3.0f), 5);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(1.0f), Q12(1.0f), 5);
                    }

                    g_SysWork.targetNpcIdx_2353 = g_Player_TargetNpcIdx;
                }
                else
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & PlayerFlag_Unk0))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(7.0f), Q12(7.0f), 5);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122, &g_SysWork.playerCombat_38, Q12(2.1f), Q12(2.1f), 5);
                    }
                }

                switch (g_Player_TargetNpcIdx)
                {
                    default:
                        if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                        {
                            g_SysWork.playerWork_4C.extra_128.state_1C                      = PlayerState_Combat;
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk0 | PlayerFlag_Unk9;

                            if (g_SysWork.targetNpcIdx_2353 != g_Player_TargetNpcIdx)
                            {
                                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_AimTargetLockSwitch;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                                    chara->model_0.stateStep_3                      = 0;
                                    chara->model_0.controlState_2                          = ModelState_Uninitialized;
                                }
                            }

                            g_SysWork.targetNpcIdx_2353 = g_Player_TargetNpcIdx;
                            break;
                        }

                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.controlState_2                          = ModelState_Uninitialized;
                        }

                    case NO_VALUE:
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122  = Q12_ANGLE(90.0f);
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Attack;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.controlState_2                          = ModelState_Uninitialized;
                        }
                        break;
                }

                if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (g_SysWork.playerCombat_38.currentWeaponAmmo_10 == 0 &&
                        (g_SavegamePtr->equippedWeapon_AA >> 5) == 5 &&
                        g_SysWork.playerCombat_38.totalWeaponAmmo_11 != 0)
                    {
                        g_SysWork.playerWork_4C.extra_128.upperBodyState_20             = PlayerUpperBodyState_Reload;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Reload;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.controlState_2                          = ModelState_Uninitialized;
                        }
                    }
                }
                else
                {
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_Attack;

                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_Aim ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_SteelPipe ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Hammer    ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_RockDrill ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Katana)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Attack;
                        chara->model_0.stateStep_3                      = 0;
                        chara->model_0.controlState_2                          = ModelState_Uninitialized;
                    }
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.controlState_2     = ModelState_Uninitialized;
            }
            else
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
            }
            break;
    }
}

void Player_StepWallStop_MovementCancel(s_SubCharacter* chara, s32 animStatus0, s32 animStatus1, s32 keyframeIdx, e_PlayerLowerBodyState lowerBodyState, s32 headingAngle, s32 aimState) // 0x80077BB8
{
    s16 headingAngleCpy;

    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 1;
        if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
        {
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
        }
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.status_0 = animStatus0;
        chara->model_0.stateStep_3++;
    }

    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
    {
        if (chara->model_0.anim_4.status_0 == animStatus1 && chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx)
        {
            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
            Player_MovementStateReset(chara, lowerBodyState);
        }

        Player_CharaRotate(2);
    }

    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
        g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
    }
    else
    {
        headingAngleCpy                                                   = headingAngle;
        g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = headingAngleCpy;
        g_Player_HeadingAngle                                             = headingAngleCpy;
    }
}

void Player_LowerBodyUpdate(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x80077D00
{
    #define MOVE_DIST_MAX Q12(1000000.0f)
    #define MOVE_DIST_MIN 1

    // Used for `player.moveDistance_126`.
    #define GET_MOVE_SPEED(zoneType)                      \
        (((zoneType) == SpeedZoneType_Fast) ? Q12(5.0f) : \
                                              (((zoneType) == SpeedZoneType_Slow) ? Q12(3.5f) : Q12(4.0f)))

    // Used for `player.moveDistance_126`.
#define GET_VAL(val) \
    (((val) < Q12(3.5f)) ? (((g_DeltaTime) * Q12(0.75f)) / TIMESTEP_30_FPS) : (((g_DeltaTime) + (((g_DeltaTime) < 0) ? 3 : 0)) >> 2))

    q19_12                 speedX;
    q19_12                 speedZ;
    s32                    travelDistStep;
    s32                    speedZoneType; // `e_SpeedZoneType`
    e_PlayerLowerBodyState temp_s3;       // runningState?
    s32                    var_a3;
    s32                    aimState;

    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
    {
        aimState = 0;
    }
    else
    {
        aimState = 20;
    }

    // Compute move distance step.
    temp_s3        = func_8007D6F0(chara, &D_800C45C8);
    speedZoneType  = Map_SpeedZoneTypeGet(chara->position_18.vx, chara->position_18.vz);
    speedX         = SQUARE(chara->position_18.vx - g_Player_PrevPosition.vx);
    speedZ         = SQUARE(chara->position_18.vz - g_Player_PrevPosition.vz);
    travelDistStep = SquareRoot0(speedX + speedZ);

    switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
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
            g_SavegamePtr->walkDistance_258  = CLAMP(g_SavegamePtr->walkDistance_258, MOVE_DIST_MIN, MOVE_DIST_MAX);
            break;

        default:
            g_SavegamePtr->runDistance_254 += travelDistStep;
            g_SavegamePtr->runDistance_254  = CLAMP(g_SavegamePtr->runDistance_254, MOVE_DIST_MIN, MOVE_DIST_MAX);
            break;
    }

    switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_WalkForward, true))
            {
                chara->model_0.stateStep_3 = 0;
            }

            // Check if player is aiming.
            if (aimState != 0)
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & 1)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & 1)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            // Sets animations during specific idle states while aiming or standing.
            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
            {
                // Aim to idle.
                if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombat_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        chara->model_0.stateStep_3++;
                    }
                }
                // Check if player has >= 30% or < 10% health to determine level of exertion.
                else if (chara->properties_E4.player.exhaustionTimer_FC < Q12(10.0f) && chara->health_B0 >= Q12(30.0f))
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_IdleExhausted, false);
                    chara->model_0.stateStep_3++;
                }
            }
            else
            {
                if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombat_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        chara->model_0.stateStep_3++;
                    }
                }
                // Melee weapon.
                else if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if ((g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                         g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap)) &&
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk33, false);
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk6)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk34, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk32, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap))
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Unk29, false);
                        chara->model_0.stateStep_3++;
                    }
                }
                else
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        chara->model_0.stateStep_3++;
                    }
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            }

            // Set idle to move depending on user input.
            if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat) // Aiming at or shooting enemy.
            {
                if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) &&
                    ANIM_STATUS_IS_ACTIVE(extra->model_0.anim_4.status_0))
                {
                    if (chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_Unk29, false) ||
                        chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6 ||
                        chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[5].field_6)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                        }
                    }
                }

                Player_MovementStateReset(chara, aimState);
            }
            // Aiming at nothing, or shooting at nothing, or idle.
            else
            {
                if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) &&
                    ANIM_STATUS_IS_ACTIVE(extra->model_0.anim_4.status_0))
                {
                    if ((aimState == 0 && g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f))||
                        chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_Unk29, false) ||
                        chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            // Restrict aiming when going from idle to run.
                            if ((g_Player_IsRunning && temp_s3 == PlayerLowerBodyState_None) &&
                                (aimState == 0 || (( g_GameWork.config_0.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                                                   (!g_GameWork.config_0.optExtraWeaponCtrl_23 &&  g_Player_IsAiming)) &&
                                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_SteelPipe))
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C = chara->headingAngle_3C + Q12_ANGLE(90.0f);
                            temp_s3                = func_8007D6F0(chara, &D_800C45C8);

                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= Q12_ANGLE(90.0f);
                            temp_s3                 = func_8007D6F0(chara, &D_800C45C8);

                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }
                        }

                        if (aimState == 0 && !g_SysWork.playerCombat_38.isAiming_13)
                        {
                            if (( g_GameWork.config_0.optExtraWalkRunCtrl_2B && !g_Player_IsRunning) ||
                                (!g_GameWork.config_0.optExtraWalkRunCtrl_2B &&  g_Player_IsRunning))
                            {
                                if (g_Player_IsMovingBackward)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
                                    extra->model_0.stateStep_3                      = 0;
                                    extra->model_0.controlState_2                          = ModelState_Uninitialized;
                                }
                            }
                        }

                        if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == aimState && !g_Player_IsInWalkToRunTransition)
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

                if (aimState != 0 && g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Aim)
                {
                    if (D_800C454C != Q12(0.0f))
                    {
                        // TODO: Convert hex to clean floats.
                        // Determine speed if using certain weapons while moving?
                        switch (g_SysWork.playerCombat_38.weaponAttack_F)
                        {
                            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = (u32)(D_800C454C * 0x465) >> 9;
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Katana,   AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Axe,      AttackInputType_Tap):
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = (u32)(D_800C454C * 0x15F9) >> 11;
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Hammer,    AttackInputType_Tap):
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = ((u32)(D_800C454C * 0xD2F) >> 10);
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Handgun,      AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = (-(D_800C454C * 0x87F0) >> 14);
                                break;
                        }

                        if (g_DeltaTime != Q12(0.0f))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 * 0x88) / g_DeltaTime);
                        }

                        // Restart timer for idle animation.
                        if (D_800C454C != Q12(0.0f))
                        {
                            chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
                        }
                    }
                }
                // Move without aiming.
                else if (D_800C454C != Q12(0.0f))
                {
                    chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
                }

                // Turn if idle.
                if (g_Player_IsTurningLeft && chara->model_0.stateStep_3 == 1 &&
                    (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Idle, true) ||
                     chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_IdleExhausted, true)))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_TurnLeft, false);
                }
                else if (g_Player_IsTurningRight && chara->model_0.stateStep_3 == 1 &&
                         (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Idle, true) ||
                          chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_IdleExhausted, true)))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_TurnRight, false);
                }

                if (!g_Player_IsTurningLeft && !g_Player_IsTurningRight && chara->model_0.stateStep_3 == 2 &&
                    (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_TurnRight, true) ||
                     chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_TurnLeft, true)))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                    chara->model_0.stateStep_3      = 0;
                }
            }

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f) ||
                 g_Player_IsTurningLeft || g_Player_IsTurningRight)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            }
            break;

        case PlayerLowerBodyState_WalkForward:
        case PlayerLowerBodyState_AimWalkForward:
            if (!g_Player_IsMovingForward)
            {
                g_SysWork.playerStopFlags_235A |= PlayerStopFlag_StopWalking;
            }

            if ((g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopWalking) &&
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;

                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            // Walking.
            else
            {
                if (g_Controller0->sticks_20.sticks_0.leftY <= -STICK_THRESHOLD)
                {
                    D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                    func_80070B84(chara, Q12(0.75f), Q12(1.4f), 2);
                }
                // Stopped walking.
                else
                {
                    if (D_800AF216 != 0)
                    {
                        func_80070B84(chara, Q12(0.75f), Q12(1.4f), 2);
                    }
                    // Reduce speed if going too fast while walking.
                    else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(1.4f))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.4f))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.4f);
                        }
                    }
                    else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.4f))
                    {
                        if (chara->model_0.anim_4.keyframeIdx_8 >= 2)
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                        }

                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                        Q12(0.0f),
                                                                                                        Q12(1.4f));
                    }

                    if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                    {
                        D_800AF216 = 0;
                    }
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_WalkForward, false);
                chara->model_0.stateStep_3++;
            }

            // Something related to anim and states when aiming or attacking while moving.
            if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat)
            {
                if (g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopWalking)
                {
                    if ((g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                         g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx_8 >= 10 && chara->model_0.anim_4.keyframeIdx_8 <= 11) ||
                          chara->model_0.anim_4.keyframeIdx_8 == 22 || chara->model_0.anim_4.keyframeIdx_8 == 21)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(chara, aimState | (1 << 0));

                if (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopWalking))
                {
                    // Code to change the player's state to running.
                    if (g_Player_IsRunning)
                    {
                        if (aimState == 0 && temp_s3 == PlayerLowerBodyState_None &&
                            (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_WalkForward ||
                             g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStop))
                        {
                            if (chara->model_0.anim_4.keyframeIdx_8 >= 10 && chara->model_0.anim_4.keyframeIdx_8 <= 11)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 36;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_RunForward, true);
                                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
                            }
                            else if (chara->model_0.anim_4.keyframeIdx_8 >= 21 && chara->model_0.anim_4.keyframeIdx_8 <= 22)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 26;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_RunForward, true);
                            }
                        }
                    }
                }
                else if ((g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                          g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx_8 >= 10 && chara->model_0.anim_4.keyframeIdx_8 <= 11) ||
                          chara->model_0.anim_4.keyframeIdx_8 == 22 || chara->model_0.anim_4.keyframeIdx_8 == 21)
                {
                    // Aparently, code intended to change player's state if the player stop walking while either aiming or attacking.
                    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                            (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                             g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                            extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.controlState_2                                      = ModelState_Uninitialized;
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = aimState;
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = aimState;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == (aimState + PlayerLowerBodyState_WalkForward) && !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(chara, aimState);
                }

                Player_MovementStateReset(chara, aimState | (1 << 0));
                Player_CharaRotate(5);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_RunForward)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Still, false);
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForward:
            chara->properties_E4.player.exhaustionTimer_FC += g_DeltaTime;

            if (g_Controller0->sticks_20.sticks_0.leftY <= -STICK_THRESHOLD)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);

                speedX = GET_MOVE_SPEED(speedZoneType);

                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.5f))
                {
                    var_a3 = TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                }
                else
                {
                    speedZ   = g_DeltaTime;
                    speedZ  += (speedZ < 0) ? 3 : 0;
                    var_a3 = speedZ >> 2;
                }

                func_80070CF0(chara, Q12(2.0f), speedX, var_a3, TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
            }
            // Stopped running.
            else
            {
                if (D_800AF216 != 0)
                {
                    speedX = GET_MOVE_SPEED(speedZoneType);

                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.5f))
                    {
                        var_a3 = TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                    }
                    else
                    {
                        speedZ   = g_DeltaTime;
                        speedZ  += (speedZ < Q12(0.0f)) ? 3 : Q12(0.0f);
                        var_a3 = speedZ >> 2;
                    }

                    func_80070CF0(chara, Q12(2.0f), speedX, var_a3, TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
                }
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > GET_MOVE_SPEED(speedZoneType))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < GET_MOVE_SPEED(speedZoneType))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = GET_MOVE_SPEED(speedZoneType);
                    }
                }
                else
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < GET_MOVE_SPEED(speedZoneType))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += GET_VAL(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126);
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126  = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126, 0, GET_MOVE_SPEED(speedZoneType));
                    }
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForward, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx_8 == 43 || chara->model_0.anim_4.keyframeIdx_8 == 33) &&
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->fallSpeed_34 = Q12(-1.25f);
            }

            // Running.
            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock &&
                chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForward, true))
            {
                // TODO: What does `func_8007D6F0` do?
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Stumble;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx_8 <= 31)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = temp_s3;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 8;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx_8 <= 42)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = temp_s3;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 20;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForwardWallStop;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx_8 <= 31)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 8;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx_8 <= 42)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 20;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        break;

                    default:
                        if (!g_Player_IsRunning || !g_Player_IsMovingForward)
                        {
                            // Change state from running to walking.
                            if (g_Player_IsMovingForward)
                            {
                                if (chara->model_0.anim_4.keyframeIdx_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx_8 <= 31)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 8;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                                else if (chara->model_0.anim_4.keyframeIdx_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx_8 <= 42)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 20;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                            }
                            // Set stumble anim if crashed into a wall.
                            else if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                                     g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >= Q12(3.125f))
                            {
                                if (chara->model_0.anim_4.keyframeIdx_8 >= 33 &&
                                    chara->model_0.anim_4.keyframeIdx_8 <= 34)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_RunForwardWallStop;
                                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_WallStopRight;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx_8 >= 43 &&
                                         chara->model_0.anim_4.keyframeIdx_8 <= 44)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_RunForwardWallStop;
                                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                                }
                            }
                            // Change state from running to walking. Difference with first conditional is this only triggers if
                            // walking is abruptly stopped wall crash anim was not triggered.
                            // In-game, appears as though player goes directly to idle. Mechanically, it goes through this state, then to idle.
                            else
                            {
                                if (chara->model_0.anim_4.keyframeIdx_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx_8 <= 31)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 8;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                                else if (chara->model_0.anim_4.keyframeIdx_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx_8 <= 42)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx_E = 20;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].status_6         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                            }
                        }
                        break;
                }
            }

            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_RunForward)
            {
                Player_MovementStateReset(chara, PlayerLowerBodyState_RunForward);
            }

            Player_CharaRotate(4);

            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_WalkForward)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Still, false);
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 1;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            // Depending on frame of gait cycle, set left or right wall stop anim variant.
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardWallStopRight, false);
                    chara->model_0.stateStep_3++;
                }
            }
            else if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true) &&
                    chara->model_0.anim_4.keyframeIdx_8 >= 168 ||
                    chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true) &&
                    chara->model_0.anim_4.keyframeIdx_8 >= 158)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                    Player_MovementStateReset(chara, PlayerLowerBodyState_RunForwardWallStop);
                }

                Player_CharaRotate(4);
            }
            break;

        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            if (!g_Player_IsMovingBackward)
            {
                g_SysWork.playerStopFlags_235A |= PlayerStopFlag_StopRunning;
            }

            if ((g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopRunning) &&
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            // Walking backward.
            else if (g_Controller0->sticks_20.sticks_0.leftY >= STICK_THRESHOLD)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                func_80070B84(chara, Q12(0.75f), Q12(1.15f), 2);
            }
            // Stop walking backward.
            else
            {
                if (D_800AF216 != 0)
                {
                    func_80070B84(chara, Q12(0.75f), Q12(1.15f), 2);
                }
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(1.15f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.15f))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.15f);
                    }
                }
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.15f))
                {
                    if (chara->model_0.anim_4.keyframeIdx_8 >= 2)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    }

                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                    Q12(0.0f),
                                                                                                    Q12(1.15f));
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickDown)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_WalkBackward, false);
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat)
            {
                if (g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopRunning)
                {
                    if ((g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                         g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx_8 >= 56 &&
                          chara->model_0.anim_4.keyframeIdx_8 <= 57) ||
                         chara->model_0.anim_4.keyframeIdx_8 == 67 ||
                         chara->model_0.anim_4.keyframeIdx_8 == 66)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_WalkBackward);

                if (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.playerStopFlags_235A & PlayerStopFlag_StopRunning))
                {
                    if (((chara->model_0.anim_4.keyframeIdx_8 >= 66 &&
                          chara->model_0.anim_4.keyframeIdx_8 <= 67) ||
                         chara->model_0.anim_4.keyframeIdx_8 == 46 ||
                         chara->model_0.anim_4.keyframeIdx_8 == 47) &&
                        aimState == 0 && g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        if (( g_GameWork.config_0.optExtraWalkRunCtrl_2B && !g_Player_IsRunning) ||
                            (!g_GameWork.config_0.optExtraWalkRunCtrl_2B &&  g_Player_IsRunning))
                        {
                            if (g_Player_IsMovingBackward)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                                g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_RunJumpBackward;
                                extra->model_0.stateStep_3                      = 0;
                                extra->model_0.controlState_2                          = ModelState_Uninitialized;
                            }
                        }
                    }
                }
                else if ((g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim &&
                          g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop) ||
                         (chara->model_0.anim_4.keyframeIdx_8 >= 56 && chara->model_0.anim_4.keyframeIdx_8 <= 57) ||
                          chara->model_0.anim_4.keyframeIdx_8 == 67 || chara->model_0.anim_4.keyframeIdx_8 == 66)
                {
                    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                            extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.controlState_2                                      = ModelState_Uninitialized;
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = aimState;
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = aimState;
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == (aimState + PlayerLowerBodyState_WalkBackward) &&
                    !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(chara, aimState);
                }

                Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_WalkBackward);
                Player_CharaRotate(4);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_SidestepRight:
        case PlayerLowerBodyState_AimSidestepRight:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(1.25f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.25f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.25f);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx_8 >= 100 &&
                    chara->model_0.anim_4.keyframeIdx_8 <= 111)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }
                else if (chara->model_0.anim_4.keyframeIdx_8 >= 112)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.25f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_SidestepRight, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_SidestepRight, true) &&
                chara->model_0.anim_4.keyframeIdx_8 >= 117)
            {
                // Stopped sidestepping while attacking.
                // If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingRightHold)
                {
                    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        // Some melee weapons allow attack while sidestepping.
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.controlState_2                                      = ModelState_Uninitialized;
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                    }
                }
            }

            Player_CharaTurn_0(chara, aimState);
            Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_SidestepRight);
            Player_CharaRotate(3);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_SidestepLeft:
        case PlayerLowerBodyState_AimSidestepLeft:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(1.25f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.25f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.25f);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx_8 >= 75 &&
                    chara->model_0.anim_4.keyframeIdx_8 <= 86)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }
                else if (chara->model_0.anim_4.keyframeIdx_8 >= 87)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.25f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_SidestepLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_SidestepLeft, true) &&
                chara->model_0.anim_4.keyframeIdx_8 >= 92)
            {
                // Stopped stepping while attacking.
                // If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingLeftHold)
                {
                    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                             extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.controlState_2                                      = ModelState_Uninitialized;
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                    }
                }
            }

            Player_CharaTurn_1(chara, aimState);
            Player_MovementStateReset(chara, aimState + PlayerLowerBodyState_SidestepLeft);
            Player_CharaRotate(3);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_RunRight:
            chara->properties_E4.player.exhaustionTimer_FC += g_DeltaTime;
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(3.1739f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.1739f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(3.1739f);
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.1739f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126  = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                 Q12(0.0f),
                                                                                                 Q12(3.1739f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRight, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx_8 == 139 ||
                 chara->model_0.anim_4.keyframeIdx_8 == 145) &&
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->fallSpeed_34 = Q12(-1.0f);
            }

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightStumble;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                chara->model_0.anim_4.keyframeIdx_8 >= 147)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightWallStop;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                chara->model_0.anim_4.keyframeIdx_8 >= 147)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >= Q12(3.125f))
                        {
                            if (chara->model_0.anim_4.keyframeIdx_8 >= 144 && (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRightWallStop;
                            }
                        }
                        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                 chara->model_0.anim_4.keyframeIdx_8 >= 147 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(chara, PlayerLowerBodyState_RunRight);
            Player_CharaRotate(4);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_RunLeft:
            chara->properties_E4.player.exhaustionTimer_FC += g_DeltaTime;
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(3.1739f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.1739f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(3.1739f);
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(3.1739f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126  = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                 Q12(0.0f),
                                                                                                 Q12(3.1739f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunLeft, false);
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx_8 == 125 || chara->model_0.anim_4.keyframeIdx_8 == 132) &&
                chara->position_18.vy == chara->properties_E4.player.positionY_EC)
            {
                chara->fallSpeed_34 = Q12(-1.0f);
            }

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftStumble;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeft, true) &&
                                chara->model_0.anim_4.keyframeIdx_8 >= 132)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (chara->properties_E4.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftWallStop;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeft, true) &&
                                chara->model_0.anim_4.keyframeIdx_8 >= 132)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.runTimer_F8 >= 5 &&
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >= Q12(3.125f))
                        {
                            if (chara->model_0.anim_4.keyframeIdx_8 > 128 && (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeftWallStop;
                            }
                        }
                        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeft, true) && chara->model_0.anim_4.keyframeIdx_8 >= 132 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(chara, PlayerLowerBodyState_RunLeft);
            Player_CharaRotate(4);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            g_Player_HeadingAngle = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (chara->model_0.controlState_2 == ModelState_Uninitialized)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_QuickTurnRight, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.controlState_2 == ModelState_Uninitialized)
            {
                chara->model_0.controlState_2++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_QuickTurnRight, true) && chara->model_0.anim_4.keyframeIdx_8 >= 206)
            {
                D_800C454C = g_DeltaTime * 24;
            }
            else
            {
                D_800C454C = Q12(0.0f);
            }

            if (ABS_DIFF(g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120, chara->rotation_24.vy) > (Q12_ANGLE(180.0f) - ((s32)(g_DeltaTime * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120, chara->rotation_24.vy) < (((g_DeltaTime * 24) >> 4) + Q12_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                                   = g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120 + Q12_ANGLE(180.0f);
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.4f);
                    D_800C454C                                                              = Q12(0.0f);

                    // State change.
                    if (chara->model_0.anim_4.keyframeIdx_8 >= 213)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C += Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 216)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.controlState_2                          = ModelState_Uninitialized;
                        }
                    }
                }
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            g_Player_HeadingAngle = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (chara->model_0.controlState_2 == ModelState_Uninitialized)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_QuickTurnLeft, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.controlState_2 == ModelState_Uninitialized)
            {
                chara->model_0.controlState_2++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_QuickTurnLeft, true) && chara->model_0.anim_4.keyframeIdx_8 >= 219)
            {
                D_800C454C = -(g_DeltaTime * 24);
            }
            else
            {
                D_800C454C = Q12(0.0f);
            }

            if (ABS_DIFF(g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120, chara->rotation_24.vy) > (Q12_ANGLE(180.0f) - ((g_DeltaTime * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120, chara->rotation_24.vy) < (((g_DeltaTime * 24) >> 4) + Q12_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                                   = g_SysWork.playerWork_4C.player_0.properties_E4.player.quickTurnHeadingAngle_120 + Q12_ANGLE(180.0f);
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.4f);
                    D_800C454C                                                              = Q12(0.0f);

                    // State change.
                    if (chara->model_0.anim_4.keyframeIdx_8 >= 226)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            chara->headingAngle_3C += Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            chara->headingAngle_3C -= Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.controlState_2     = ModelState_Uninitialized;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx_8 >= 229)
                        {
                            g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                            chara->model_0.stateStep_3                      = 0;
                            chara->model_0.controlState_2                          = ModelState_Uninitialized;
                        }
                    }
                }
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_JumpBackward:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_JumpBackward, false);
                chara->model_0.stateStep_3++;
            }

            // Jump backward.
            if ((chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_JumpBackward, false) &&
                 chara->model_0.anim_4.status_0 <= ANIM_STATUS(HarryAnim_JumpBackward, true)) &&
                chara->model_0.anim_4.keyframeIdx_8 < 245)
            {
                if (chara->model_0.controlState_2 == ModelState_Uninitialized)
                {
                    chara->fallSpeed_34 = Q12(-2.0f);
                }

                chara->model_0.controlState_2++;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(2.25f);
                D_800C4550                                                              = Q12(2.25f);
            }
            else
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != 0)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }

                D_800C4550 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_JumpBackward, true) && chara->model_0.anim_4.keyframeIdx_8 == 246)
            {
                if (chara->position_18.vy < chara->properties_E4.player.positionY_EC)
                {
                    Player_ExtraStateSet(chara, extra, PlayerState_FallBackward);

                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.25f);
                }
                else
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = aimState;
                    chara->model_0.stateStep_3                      = 0;
                    chara->model_0.controlState_2                   = ModelState_Uninitialized;
                    chara->fallSpeed_34                                 = Q12(0.0f);
                }
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_Stumble:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2) / 3;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 <= Q12(0.5f) &&
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 4;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunForwardStumble, true) && chara->model_0.anim_4.keyframeIdx_8 == 179)
            {
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, PlayerLowerBodyState_Stumble);
            }
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            Player_StepWallStop_MovementCancel(chara, 36, 37, 335, PlayerLowerBodyState_RunLeftWallStop, Q12_ANGLE(-90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            Player_StepWallStop_MovementCancel(chara, 40, 41, 364, PlayerLowerBodyState_RunRightWallStop, Q12_ANGLE(90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 2;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 < Q12(0.3401f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunLeftStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunLeftStumble, true) && chara->model_0.anim_4.keyframeIdx_8 == 349)
            {
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, 15);
            }

            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_None)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(-90.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
                break;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 2;
                if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 < Q12(0.3401f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRightStumble, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_RunRightStumble, true) && chara->model_0.anim_4.keyframeIdx_8 == 378)
            {
                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                Player_MovementStateReset(chara, 16);
            }

            if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 == PlayerLowerBodyState_None)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
                break;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_Attack:
            // If weapon is katana.
            if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Katana)
            {
                if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Katana, AttackInputType_Hold))
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f) &&
                        (extra->model_0.anim_4.keyframeIdx_8 >= D_800C44F0[D_800AF220].field_4 + 7))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(5.0f);
                        g_Player_HeadingAngle                                                   = Q12_ANGLE(0.0f);
                    }
                }
                else if (chara->model_0.stateStep_3 == 0 && !g_Player_IsAttacking)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(5.0f);
                    g_Player_HeadingAngle                                                   = Q12_ANGLE(0.0f);
                }
            }

            if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Katana)
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, 0x444);
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else
            {
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }

            if (g_SysWork.targetNpcIdx_2353 == NO_VALUE ||
                g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
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
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk10)
                {
                    if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) ||
                        g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        chara->model_0.stateStep_3++;
                    }

                    if (chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6 || chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[5].field_6)
                    {
                        chara->model_0.anim_4.status_0      = extra->model_0.anim_4.status_0;
                        chara->model_0.anim_4.keyframeIdx_8 = extra->model_0.anim_4.keyframeIdx_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
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
                    if (extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk30, true))
                    {
                        chara->model_0.anim_4.status_0      = extra->model_0.anim_4.status_0;
                        chara->model_0.anim_4.keyframeIdx_8 = extra->model_0.anim_4.keyframeIdx_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                    else if (g_Player_IsAttacking || extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Unk29, true))
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.status_0 = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (g_Player_IsShooting || extra->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
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

            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) ||
                (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != EquippedWeaponId_SteelPipe &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != EquippedWeaponId_Hammer    &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != EquippedWeaponId_RockDrill &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) != EquippedWeaponId_Katana))
            {
                if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) && ANIM_STATUS_IS_ACTIVE(extra->model_0.anim_4.status_0) &&
                    (chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_Unk29, false) || chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6))
                {
                    if (!g_Player_IsMovingForward)
                    {
                        if (g_Player_IsMovingBackward)
                        {
                            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f))
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                            }
                        }
                        else if (g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_Combat)
                        {
                            if (!g_Player_IsSteppingRightHold)
                            {
                                if (g_Player_IsSteppingLeftHold)
                                {
                                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepLeft;
                                }
                            }
                            else
                            {
                                g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepRight;
                            }
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                    }

                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Attack)
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
                chara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_HandgunRecoil, false);
                chara->model_0.stateStep_3++;
            }

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) && ANIM_STATUS_IS_ACTIVE(extra->model_0.anim_4.status_0) &&
                (chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_Unk29, false) || chara->model_0.anim_4.keyframeIdx_8 == D_800C44F0[0].field_6))
            {
                if (g_Player_IsMovingForward)
                {
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkForward;
                }
                else if (g_Player_IsMovingBackward)
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f))
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimWalkBackward;
                    }
                }
                else if (g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_Combat)
                {
                    if (g_Player_IsSteppingRightHold)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepRight;
                    }
                    else if (g_Player_IsSteppingLeftHold)
                    {
                        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_AimSidestepLeft;
                    }
                }

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Reload)
                {
                    Player_MovementStateReset(chara, PlayerLowerBodyState_Aim);
                }
            }
            break;
    }

    func_8007B924(chara, extra);
}

void func_8007B924(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x8007B924
{
    e_SfxId sfx;
    s8    pitch0;
    s8    pitch1;

    func_8007FDE0(D_800C4590.field_14, &sfx, &pitch0, &pitch1);

    // This entire conditional is the reason why movement stop working when removing this function call.
    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_JumpBackward &&
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_Reload)
    {
        D_800C4550 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
    }

    switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_RunForward:
        case PlayerLowerBodyState_RunRight:
        case PlayerLowerBodyState_RunLeft:
            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) && chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_RunForward, true))
            {
                chara->properties_E4.player.exhaustionTimer_FC += g_DeltaTime;
            }
            break;

        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_RunForwardWallStop:
        case PlayerLowerBodyState_Stumble:
        case PlayerLowerBodyState_RunLeftStumble:
        case PlayerLowerBodyState_RunRightStumble:
        case PlayerLowerBodyState_Aim:
            chara->properties_E4.player.exhaustionTimer_FC -= g_DeltaTime * 2;
            break;

        default:
            chara->properties_E4.player.exhaustionTimer_FC -= g_DeltaTime;
            break;
    }

    chara->properties_E4.player.exhaustionTimer_FC = CLAMP(chara->properties_E4.player.exhaustionTimer_FC, Q12(0.0f), Q12(35.0f));

    // Check if player has >=30% or <10% of health to determine exertion level.
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_IdleExhausted, true))
    {
        if (chara->properties_E4.player.exhaustionTimer_FC < Q12(10.0f) &&
            chara->health_B0 >= Q12(30.0f))
        {
            chara->model_0.stateStep_3 = 0;
            chara->model_0.controlState_2     = ModelState_Uninitialized;
            extra->model_0.stateStep_3 = 0;
            extra->model_0.controlState_2     = ModelState_Uninitialized;
        }
    }

    // Plays movement sounds.
    switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            // Turn right.
            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_TurnRight)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_TurnRight, true), chara, 204, 200, sfx, pitch0);
            }
            // Turn left.
            else if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_TurnLeft)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_TurnLeft, true), chara, 187, 191, sfx, pitch0);
            }

            if ((g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Moving) &&
                ((chara->model_0.anim_4.status_0 >= ANIM_STATUS(HarryAnim_Idle, true) &&
                  chara->model_0.anim_4.status_0 <= ANIM_STATUS(HarryAnim_IdleExhausted, false)) ||
                 chara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_HandgunAim, true)))
            {
                func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.095f), pitch0);

                chara->properties_E4.player.field_10C                        = pitch0 + 0x10;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == 246 &&
                !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk5))
            {
                func_8005DD44(sfx, &chara->position_18, Q8_CLAMPED(0.5f), pitch1);

                chara->properties_E4.player.field_10C                       = pitch1 + 0x20;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        default:
            break;

        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_WalkBackward, true), chara, 52, 63, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_AimWalkForward:
        case PlayerLowerBodyState_WalkForward:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_WalkForward, true), chara, 18, 6, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForward:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForward, true), chara, 31, 41, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepRight:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_SidestepRight, true), chara, 118, 108, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_SidestepLeft, true), chara, 93, 83, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRight:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRight, true), chara, 145, 139, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeft:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeft, true), chara, 131, 125, sfx, pitch1))
            {
                chara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_WallStopRight)
            {
                if (chara->model_0.anim_4.keyframeIdx_8 < 152)
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true), chara, 151, 154, sfx, pitch1);
                }
                else
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true), chara, 156, 154, sfx, pitch1);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx_8 < 162)
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true), chara, 164, 161, sfx, pitch1);
                }
                else
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true), chara, 164, 166, sfx, pitch1);
                }
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            if (chara->model_0.anim_4.keyframeIdx_8 < 323)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftWallStop, true), chara, 322, 324, sfx, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftWallStop, true), chara, 327, 324, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            if (chara->model_0.anim_4.keyframeIdx_8 < 352)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightWallStop, true), chara, 353, 351, sfx, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightWallStop, true), chara, 353, 356, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_Stumble:
            if (chara->model_0.anim_4.keyframeIdx_8 < 172)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardStumble, true), chara, 171, 174, sfx, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardStumble, true), chara, 176, 174, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (chara->model_0.anim_4.keyframeIdx_8 < 338)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), chara, 337, 341, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 < 344)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), chara, 343, 341, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), chara, 356, 346, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (chara->model_0.anim_4.keyframeIdx_8 < 367)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), chara, 366, 370, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 < 373)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), chara, 372, 370, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), chara, 385, 375, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_QuickTurnLeft, true), chara, 222, 224, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_QuickTurnRight, true), chara, 209, 211, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_JumpBackward:
        case PlayerLowerBodyState_Unk31:
            if (chara->model_0.anim_4.keyframeIdx_8 < 243)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
            }

            if (chara->position_18.vy == D_800C4590.field_C)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_JumpBackward, true), chara, 243, 245, sfx, pitch1);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
    }
}

void func_8007C0D8(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords) // 0x8007C0D8
{
    s_Collision coll;
    VECTOR3     offset;
    VECTOR3     sp30;
    VECTOR3     sp40;
    s16         temp_v0;
    s16         someAngle;
    s16         temp_s0;
    s32         temp_s0_2;
    s32         temp_s2;
    s32         temp_s2_2;
    s32         temp_s3;
    s32         temp_s3_2;
    s32         temp_v0_3;
    s16         temp_v1;
    s32         posY;
    u32         temp;

    g_Player_PrevPosition = chara->position_18;

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

    temp_s3 = Q12_MULT(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C));
    temp_s2 = Q12_MULT(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C));

    temp_s0 = Math_Cos(ABS(coll.field_4) >> 3);
    temp_v0 = Math_Cos(ABS(coll.field_6) >> 3);

    temp_v1 = Q12_MULT(Q12_MULT(temp_s3, temp_s0), temp_s0);
    someAngle = Q12_MULT(Q12_MULT(temp_s2, temp_v0), temp_v0);

    if (chara->moveSpeed_38 >= Q12(0.0f))
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }

    temp_s0_2 = Q12_MULT_PRECISE(chara->moveSpeed_38, g_DeltaTime);

    temp_v0_3 = chara->headingAngle_3C;
    temp      = temp_s0_2 + SHRT_MAX;
    temp_s2_2 = (temp > (SHRT_MAX * 2)) * 4;
    temp_s3_2 = temp_s2_2 >> 1;

    offset.vx = Q12_MULT_PRECISE((temp_s0_2 >> temp_s3_2), Math_Sin(temp_v0_3) >> temp_s3_2);
    offset.vx <<= temp_s2_2;

    offset.vz = Q12_MULT_PRECISE((temp_s0_2 >> temp_s3_2), Math_Cos(temp_v0_3) >> temp_s3_2);
    offset.vz <<= temp_s2_2;

    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        offset.vx = offset.vx + D_800C45B0.vx;
        sp30.vx = offset.vx;
        offset.vz = offset.vz + D_800C45B0.vz;
        sp30.vz = offset.vz;
    }

    func_80069B24(&D_800C4590, &offset, chara);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        if (D_800C45B0.vx != 0 && (DIFF_SIGN(sp30.vx, D_800C4590.offset_0.vx) || abs(sp30.vx) >= ABS(D_800C4590.offset_0.vx)))
        {
            sp40.vx = sp30.vx - D_800C4590.offset_0.vx;
        }
        else
        {
            sp40.vx = 0;
        }

        if (D_800C45B0.vz != 0 && (DIFF_SIGN(sp30.vz, D_800C4590.offset_0.vz) || abs(sp30.vz) >= ABS(D_800C4590.offset_0.vz)))
        {
            sp40.vz = sp30.vz - D_800C4590.offset_0.vz;
        }
        else
        {
            sp40.vz = 0;
        }

        g_MapOverlayHeader.func_158(-sp40.vx, -sp40.vz);
    }

    chara->position_18.vx += D_800C4590.offset_0.vx;
    chara->position_18.vy += D_800C4590.offset_0.vy;
    chara->position_18.vz += D_800C4590.offset_0.vz;

    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunForward ||
        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunRight ||
        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_RunLeft)
    {
        chara->properties_E4.player.runTimer_108 += SquareRoot0(SQUARE(D_800C4590.offset_0.vx) +
                                                                SQUARE(D_800C4590.offset_0.vy) +
                                                                SQUARE(D_800C4590.offset_0.vz));
    }
    else
    {
        chara->properties_E4.player.runTimer_108 = 0;
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S00 && g_SavegamePtr->mapRoomIdx_A5 == 13)
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
        chara->fallSpeed_34   = Q12(0.0f);
    }

    someAngle = Q12_ANGLE_NORM_U(ratan2(chara->position_18.vx - g_Player_PrevPosition.vx, chara->position_18.vz - g_Player_PrevPosition.vz) + Q12_ANGLE(360.0f));

    if (!(g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_FallForward && g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_KickEnemy))
    {
        if (!g_Player_IsInWalkToRunTransition)
        {
            posY = chara->position_18.vy;
            if ((D_800C4590.field_C - posY) >= Q12(0.65f))
            {
                if (ABS_DIFF(chara->rotation_24.vy, someAngle) >= Q12_ANGLE(90.0f) &&
                    ABS_DIFF(chara->rotation_24.vy, someAngle) <  Q12_ANGLE(270.0f))
                {
                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 != PlayerLowerBodyState_JumpBackward)
                    {
                        Player_ExtraStateSet(chara, extra, PlayerState_FallBackward);
                    }
                }
                else
                {
                    Player_ExtraStateSet(chara, extra, PlayerState_FallForward);
                }

                g_SysWork.playerCombat_38.isAiming_13 = false;
            }
        }
    }

    chara->properties_E4.player.positionY_EC = D_800C4590.field_C;
    coords->coord.t[0]                        = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1]                        = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2]                        = Q12_TO_Q8(chara->position_18.vz);
}

void Player_ReceiveDamage(s_SubCharacter* chara, s_PlayerExtra* extra) // 0x8007C800
{
    s16 headingAngle;
    u16 enemyRotY;
    s32 i;
    s32 sfx;
    s32 angleState;

    // Set damage SFX according to something.
    sfx = Sfx_Unk1326;
    if (chara->attackReceived_41 != NO_VALUE)
    {
        switch (D_800AD4C8[chara->attackReceived_41].field_11)
        {
            case 2:
                sfx = Sfx_Unk1327;
                break;

            case 4:
                sfx = Sfx_Unk1328;
                break;

            case 5:
                sfx = Sfx_Unk1329;
                break;

            case 0:
                break;
        }
    }

    if (g_Player_DisableControl || g_Player_DisableDamage)
    {
        chara->damage_B4.amount_C = Q12(0.0f);
        return;
    }

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
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
            // Related to enemy grabbing.
            if (chara->damage_B4.amount_C != Q12(0.0f) && !(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
                func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.125f), 0);
                chara->properties_E4.player.field_10C = 64;
            }

            if (chara->damage_B4.amount_C == Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;
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
            chara->damage_B4.position_0.vz = Q12(0.0f);
            chara->damage_B4.position_0.vy = Q12(0.0f);
            chara->damage_B4.position_0.vx = Q12(0.0f);

            if (chara->attackReceived_41 == 47)
            {
                g_SysWork.playerWork_4C.player_0.field_D4.field_2 = Q12(0.0f);
                Player_ExtraStateSet(chara, extra, PlayerState_InstantDeath);
                return;
            }

            if (chara->attackReceived_41 >= 68 &&
                chara->attackReceived_41 <  70)
            {
                chara->damage_B4.amount_C = Q12(0.0f);
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
                D_800C4560 = NO_VALUE;
            }

            if (chara->attackReceived_41 <= 0)
            {
                break;
            }

            g_SysWork.targetNpcIdx_2353                  = NO_VALUE;
            g_SysWork.playerCombat_38.weaponAttack_F = (g_SavegamePtr->equippedWeapon_AA == InventoryItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA - InventoryItemId_KitchenKnife);

            if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                func_8004C564(2, 3);
            }

            if (g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_FallForward &&
                g_SysWork.playerWork_4C.extra_128.state_1C <  PlayerState_Unk7)
            {
                g_SysWork.playerWork_4C.player_0.field_C8.field_0   = Q12(-1.6f);
                g_SysWork.playerWork_4C.player_0.field_C8.field_2   = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_C8.field_6   = Q12(-1.1f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
            }

            enemyRotY = g_SysWork.npcs_1A0[chara->field_40].rotation_24.vy;
            if (chara->attackReceived_41 >= 64 && chara->attackReceived_41 < 66)
            {
                enemyRotY -= Q12_ANGLE(90.0f);
            }
            else if (chara->attackReceived_41 == 69)
            {
                enemyRotY = Q12_ANGLE(90.0f);
            }
            else if (chara->attackReceived_41 == 68)
            {
                enemyRotY = chara->damage_B4.position_0.vy;
            }

            enemyRotY = Q12_ANGLE_NORM_U((enemyRotY - chara->rotation_24.vy) + Q12_ANGLE(360.0f));

            switch (chara->attackReceived_41)
            {
                case 67:
                    Player_ExtraStateSet(chara, extra, PlayerState_Unk7);
                    break;

                case 63:
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.5f);
                    Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.npcs_1A0[0].rotation_24.vy, &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                    if (enemyRotY >= Q12_ANGLE(90.0f) && enemyRotY < Q12_ANGLE(270.0f))
                    {
                        Player_ExtraStateSet(chara, extra, PlayerState_DamageThrownFront);
                    }
                    else
                    {
                        Player_ExtraStateSet(chara, extra, PlayerState_DamageThrownBack);
                    }
                    break;

                case 60:
                case 62:
                    chara->damage_B4.amount_C = Q12(10.0f);
                    Player_ExtraStateSet(chara, extra, PlayerState_DamageHead);
                    break;

                case 41:
                case 42:
                    Player_ExtraStateSet(chara, extra, PlayerState_DamageHead);
                    break;

                case 49: // Leg grab.
                case 54: // Romper grab.
                case 56: // Torso grab.
                case 66:
                    if (enemyRotY >= Q12_ANGLE(90.0f) &&
                        enemyRotY <  Q12_ANGLE(270.0f))
                    {
                        g_SysWork.npcIdxs_2354[0] = chara->field_40;

                        switch (chara->attackReceived_41)
                        {
                            case 54:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabPinnedFrontStart);
                                break;

                            case 45:
                            case 56:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabTorsoFront);
                                break;

                            case 49:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabLegsFront);
                                break;

                            case 66:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabNeckFront);
                                break;

                        }
                    }
                    else
                    {
                        g_SysWork.npcIdxs_2354[1] = chara->field_40;

                        switch (chara->attackReceived_41)
                        {
                            case 54:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabPinnedBackStart);
                                break;

                            case 45:
                            case 56:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabTorsoBack);
                                break;

                            case 49:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabLegsBack);
                                break;

                            case 66:
                                Player_ExtraStateSet(chara, extra, PlayerState_EnemyGrabNeckBack);
                                break;
                        }
                    }
                    break;

                case 47:
                    chara->health_B0        = NO_VALUE;
                    chara->field_D4.field_2 = Q12(0.0f);
                    Player_ExtraStateSet(chara, extra, PlayerState_InstantDeath);
                    return;

                case 69:
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.6f);
                    Math_ShortestAngleGet(chara->rotation_24.vy, Q12_ANGLE(90.0f), &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                case 68:
                    if (chara->attackReceived_41 != 69)
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(4.0f);
                        Math_ShortestAngleGet(chara->rotation_24.vy, (s16)chara->damage_B4.position_0.vy, &headingAngle);
                        g_Player_HeadingAngle = headingAngle;
                    }

                case 40:
                case 43:
                case 44:
                case 45:
                case 46:
                case 48:
                case 50:
                case 52:
                case 57:
                case 58:
                case 59:
                case 61:
                case 64:
                case 65:
                    // Left harm animation.
                    if (enemyRotY >= Q12_ANGLE(45.0f) && enemyRotY < Q12_ANGLE(135.0f))
                    {
                        angleState = PlayerState_DamageTorsoLeft;
                    }
                    // Front harm animation.
                    else if (enemyRotY >= Q12_ANGLE(135.0f) && enemyRotY < Q12_ANGLE(225.0f))
                    {
                        angleState = PlayerState_DamageTorsoFront;
                    }
                    // Right harm animation.
                    else if (enemyRotY >= Q12_ANGLE(225.0f) && enemyRotY < Q12_ANGLE(315.0f))
                    {
                        angleState = PlayerState_DamageTorsoRight;
                    }
                    // Back harm animation.
                    else
                    {
                        angleState = PlayerState_DamageTorsoBack;
                    }

                    Player_ExtraStateSet(chara, extra, angleState);
                    break;

                case 53:
                    if (enemyRotY < Q12_ANGLE(179.95f))
                    {
                        angleState = PlayerState_DamageFeetFront;
                    }
                    else
                    {
                        angleState = PlayerState_DamageFeetBack;
                    }

                    Player_ExtraStateSet(chara, extra, angleState);
                    break;
            }

            if ((u32)g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_FallForward)
            {
                chara->properties_E4.player.afkTimer_E8                     = Q12(0.0f);
                chara->properties_E4.player.field_F4                        = 0;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                g_SysWork.playerCombat_38.isAiming_13                   = false;
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->field_44.field_0                                     = NO_VALUE;
            }
            break;
    }

    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Death)
    {
        Chara_DamageClear(chara);
        return;
    }

    if (chara->damage_B4.amount_C != Q12(0.0f))
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
        if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived))
        {
            func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.125f), 0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
            chara->properties_E4.player.field_10C = 0x40;
        }

        if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
        {
            chara->health_B0 -= chara->damage_B4.amount_C * 2;
        }
        else
        {
            switch (g_SavegamePtr->gameDifficulty_260)
            {
                case GameDifficulty_Easy:
                    chara->damage_B4.amount_C = (chara->damage_B4.amount_C * 3) >> 2; // `/ 4`.
                    break;

                case GameDifficulty_Hard:
                    chara->damage_B4.amount_C = (chara->damage_B4.amount_C * 6) >> 2; // `/ 4`.
                    break;
            }

            chara->health_B0 -= chara->damage_B4.amount_C;
        }

        if (chara->health_B0 < Q12(0.0f))
        {
            chara->health_B0 = NO_VALUE;
            g_Player_IsDead  = true;
        }

        func_800893D0(chara->damage_B4.amount_C);
        chara->damage_B4.amount_C = Q12(0.0f);
    }

    if (chara->health_B0 <= Q12(0.0f) && g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_Death &&
        g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_Unk36 && g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_EnemyGrabPinnedFront &&
        g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_EnemyGrabPinnedBack && g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_OnFloorFront &&
        g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_OnFloorBehind && !g_Player_IsInWalkToRunTransition)
    {
        chara->field_40                     = NO_VALUE;
        g_SavegamePtr->healthSaturation_238 = Q12(0.0f);

        for (i = 0; i < 4; i++)
        {
            g_SysWork.npcIdxs_2354[i] = NO_VALUE;
        }

        if (chara->attackReceived_41 == 66)
        {
            Player_ExtraStateSet(chara, extra, PlayerState_Unk36);
        }
        else
        {
            Player_ExtraStateSet(chara, extra, PlayerState_Death);
        }
    }
}

void func_8007D090(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords) // 0x8007D090
{
    #define FLEX_ROT_X_RANGE Q12_ANGLE(56.25f)
    #define FLEX_ROT_Y_RANGE Q12_ANGLE(33.75f)

    q19_12 flexRotStep;
    s32    temp_v0;
    q19_12 flexRotMax;
    q19_12 var_a2;
    s32    var_a3;
    q19_12 var_v1;

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
    {
        case PlayerState_Combat:
            switch (g_SysWork.playerCombat_38.weaponAttack_F)
            {
                case WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap):
                    var_a2 = 20;
                    var_a3 = 2;
                    break;

                case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                    var_a2 = 18;
                    var_a3 = 6;
                    break;

                case WEAPON_ATTACK(EquippedWeaponId_Shotgun, AttackInputType_Tap):
                    var_a2 = 26;
                    var_a3 = 3;
                    break;

                case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                    var_a2 = 30;
                    var_a3 = 0;
                    break;

                default:
                    var_a2 = 12;
                    var_a3 = 6;
                    break;
            }

            if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Reload ||
                g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                g_Player_FlexRotationY = Q12_ANGLE(0.0f);
            }
            else
            {
                g_Player_FlexRotationX = g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122 - Q12_ANGLE(90.0f);

                if (ABS(chara->field_2A - chara->rotation_24.vy) > Q12_ANGLE(180.0f))
                {
                    if (chara->field_2A > chara->rotation_24.vy)
                    {
                        g_Player_FlexRotationY = -Q12_ANGLE_NORM_U((chara->rotation_24.vy + Q12_ANGLE(360.0f)) - chara->field_2A);
                    }
                    else
                    {
                        g_Player_FlexRotationY = Q12_ANGLE_NORM_U((chara->field_2A + Q12_ANGLE(360.0f)) - chara->rotation_24.vy);
                    }
                }
                else
                {
                    g_Player_FlexRotationY = chara->field_2A - chara->rotation_24.vy;
                }

                if (chara->properties_E4.player.field_100 != 0 || g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimStartTargetLock ||
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_AimTargetLockSwitch)
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk8)
                    {
                        var_v1 = Q12_ANGLE(0.0f);
                    }
                    else
                    {
                        var_v1 = var_a3;
                    }

                    if (chara->properties_E4.player.field_F4 != 0)
                    {
                        flexRotStep = chara->properties_E4.player.field_F4 - g_Player_FlexRotationX;
                        if (g_Player_FlexRotationX < chara->properties_E4.player.field_F4)
                        {
                            flexRotMax = chara->properties_E4.player.field_100 * TIMESTEP_SCALE_30_FPS(g_DeltaTime, var_a2 + chara->properties_E4.player.field_100);
                            if (flexRotMax < flexRotStep)
                            {
                                g_Player_FlexRotationX = chara->properties_E4.player.field_F4 - flexRotMax;
                            }
                        }
                        else
                        {
                            flexRotMax = -(chara->properties_E4.player.field_100 * TIMESTEP_SCALE_30_FPS(g_DeltaTime, var_a2 + chara->properties_E4.player.field_100));
                            if (flexRotStep < flexRotMax)
                            {
                                g_Player_FlexRotationX = chara->properties_E4.player.field_F4 - flexRotMax;
                            }
                        }
                    }
                    else
                    {
                        if (chara->properties_E4.player.field_100 < var_v1)
                        {
                            g_Player_FlexRotationY = Q12_ANGLE(0.0f);
                            g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                        }
                        else
                        {
                            temp_v0     = chara->properties_E4.player.field_100 + 1;
                            flexRotStep = temp_v0 - var_v1;
                            flexRotMax  = Q12_ANGLE(0.4f);
                            flexRotMax  = flexRotStep * TIMESTEP_SCALE_30_FPS(g_DeltaTime, var_a2 + ((flexRotStep * 2) + flexRotMax));

                            // Clamp X-axis flex angle.
                            if (g_Player_FlexRotationX > Q12_ANGLE(0.0f))
                            {
                                if (flexRotMax < g_Player_FlexRotationX)
                                {
                                    g_Player_FlexRotationX = flexRotMax;
                                }
                            }
                            else if (g_Player_FlexRotationX < Q12_ANGLE(0.0f))
                            {
                                if (g_Player_FlexRotationX < -flexRotMax)
                                {
                                    g_Player_FlexRotationX = -flexRotMax;
                                }
                            }

                            // Clamp Y-axis flex angle.
                            if (g_Player_FlexRotationY > Q12_ANGLE(0.0f))
                            {
                                if (flexRotMax < g_Player_FlexRotationY)
                                {
                                    g_Player_FlexRotationY = flexRotMax;
                                }
                            }
                            else if (g_Player_FlexRotationY < Q12_ANGLE(0.0f))
                            {
                                if (g_Player_FlexRotationY < -flexRotMax)
                                {
                                    g_Player_FlexRotationY = -flexRotMax;
                                }
                            }
                        }
                    }
                }

                g_Player_FlexRotationX = CLAMP(g_Player_FlexRotationX, -FLEX_ROT_X_RANGE, FLEX_ROT_X_RANGE);
                g_Player_FlexRotationY = CLAMP(g_Player_FlexRotationY, -FLEX_ROT_Y_RANGE, FLEX_ROT_Y_RANGE);

                // Apply flex rotation to torso and arms.
                func_80044F14(&coords[HarryBone_Torso], Q12_ANGLE(0.0f), g_Player_FlexRotationX >> 1, g_Player_FlexRotationY);
                Math_RotMatrixZ(g_Player_FlexRotationX >> 1, &coords[HarryBone_LeftUpperArm].coord);
                Math_RotMatrixZ(g_Player_FlexRotationX >> 1, &coords[HarryBone_RightUpperArm].coord);
            }
            break;

        case PlayerState_None:
            // Pre-modulate X-axis flex angle.
            if (g_Player_FlexRotationX > Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationX -= Q12_ANGLE(2.9f);
            }
            else if (g_Player_FlexRotationX < Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationX += Q12_ANGLE(2.9f);
            }

            flexRotStep = TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12_ANGLE(2.15f));

            // Modulate X-axis flex angle.
            if (g_Player_FlexRotationX > Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationX -= flexRotStep;
                if (g_Player_FlexRotationX < Q12_ANGLE(0.0f))
                {
                    g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                }
            }
            else if (g_Player_FlexRotationX < Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationX += flexRotStep;
                if (g_Player_FlexRotationX > Q12_ANGLE(0.0f))
                {
                    g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                }
            }

            // Modulate Y-axis flex angle.
            if (g_Player_FlexRotationY > Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationY -= flexRotStep;
                if (g_Player_FlexRotationY < Q12_ANGLE(0.0f))
                {
                    g_Player_FlexRotationY = Q12_ANGLE(0.0f);
                }
            }
            else if (g_Player_FlexRotationY < Q12_ANGLE(0.0f))
            {
                g_Player_FlexRotationY += flexRotStep;
                if (g_Player_FlexRotationY > Q12_ANGLE(0.0f))
                {
                    g_Player_FlexRotationY = Q12_ANGLE(0.0f);
                }
            }

            // Apply flex rotation to torso and arms.
            func_80044F14(&coords[HarryBone_Torso], Q12_ANGLE(0.0f), g_Player_FlexRotationX >> 1, g_Player_FlexRotationY);
            Math_RotMatrixZ(g_Player_FlexRotationX >> 1, &coords[HarryBone_LeftUpperArm].coord);
            Math_RotMatrixZ(g_Player_FlexRotationX >> 1, &coords[HarryBone_RightUpperArm].coord);
            break;

        case PlayerState_Unk180:
            if (g_Player_FlexRotationY != Q12_ANGLE(0.0f))
            {
                func_80044F14(&coords[HarryBone_Torso], Q12_ANGLE(0.0f), Q12_ANGLE(0.0f),  Q12_ANGLE(16.9f));
                func_80044F14(&coords[HarryBone_Head],  Q12_ANGLE(0.0f), Q12_ANGLE(28.2f), Q12_ANGLE(19.7f));
            }
            break;

        default:
            if (g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_Unk52 &&
                g_SysWork.playerWork_4C.extra_128.state_1C <  PlayerState_Unk59)
            {
                func_80044F14(&coords[HarryBone_Head], Q12_ANGLE(0.0f), Q12_ANGLE(0.0f), g_Player_FlexRotationY);
            }
            else
            {
                g_Player_FlexRotationY = Q12_ANGLE(0.0f);
                g_Player_FlexRotationX = Q12_ANGLE(0.0f);
            }
            break;
    }

    if (g_SysWork.enablePlayerMatchAnim_2358 && g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Unk58)
    {
        func_80044F14(&g_SysWork.playerBoneCoords_890[HarryBone_RightUpperArm], Q12_ANGLE(0.0f),   Q12_ANGLE(63.3f), Q12_ANGLE(-8.8f));
        func_80044F14(&g_SysWork.playerBoneCoords_890[HarryBone_RightForearm],  Q12_ANGLE(-14.1f), Q12_ANGLE(22.5f), Q12_ANGLE(-30.8f));
        func_80044F14(&g_SysWork.playerBoneCoords_890[HarryBone_RightHand],     Q12_ANGLE(13.2f),  Q12_ANGLE(0.0f),  Q12_ANGLE(0.0f));
    }
}

void Player_FlexRotationYReset(void) // 0x8007D6E0
{
    g_Player_FlexRotationY = Q12_ANGLE(0.1f);
}

s32 func_8007D6F0(s_SubCharacter* chara, s_800C45C8* arg1) // 0x8007D6F0
{
    s_RayData rays[2];
    VECTOR3   vecs[4];
    bool      ret[2];
    s32       temp_lo;
    s32       temp_s0;
    s32       temp_s1;
    s32       temp_s3;
    s32       temp_s4;
    s32       temp_s5;
    q3_12     angle;
    q4_12     angleDelta;

    temp_s0  = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 3;
    temp_s0 += Q12(0.75f);
    temp_s1  = Q12(-0.6f);
    temp_s1 -= g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >> 4;

    temp_s4 = Q12_MULT(Math_Cos(chara->headingAngle_3C), Q12(0.2f)); // Maybe meters?
    temp_s3 = Q12_MULT(Math_Sin(chara->headingAngle_3C), Q12(0.2f)); // Maybe meters?
    temp_s5 = Q12_MULT(temp_s0, Math_Sin(chara->headingAngle_3C));
    temp_lo = Q12_MULT(temp_s0, Math_Cos(chara->headingAngle_3C));

    temp_s1 -= Q12(0.4f);

    vecs[0].vy = chara->position_18.vy + temp_s1;
    vecs[0].vx = (chara->position_18.vx + temp_s4) + temp_s5;

    vecs[0].vz = (chara->position_18.vz - temp_s3) + temp_lo;
    vecs[2].vy = chara->position_18.vy - Q12(0.4f);
    vecs[2].vx = chara->position_18.vx + temp_s4;
    vecs[2].vz = chara->position_18.vz - temp_s3;

    ret[0] = Ray_LineCheck(&rays[0], &vecs[2], &vecs[0]);

    if (ret[0])
    {
        vecs[1].vy = vecs[0].vy;
        vecs[1].vx = (chara->position_18.vx - temp_s4) + temp_s5;
        vecs[1].vz = (chara->position_18.vz + temp_s3) + temp_lo;
        vecs[3].vy = vecs[2].vy;
        vecs[3].vx = chara->position_18.vx - temp_s4;
        vecs[3].vz = chara->position_18.vz + temp_s3;

        ret[1] = Ray_LineCheck(&rays[1], &vecs[3], &vecs[1]);

        if (ret[1])
        {
            arg1->field_14 = (rays[0].field_14 + rays[1].field_14) >> 1;
            arg1->field_1  = rays[0].field_1;

            angle      = Q12_ANGLE_NORM_U(((rays[0].field_1C + rays[1].field_1C) >> 1) + Q12_ANGLE(360.0f));
            angleDelta = ABS_DIFF(angle, chara->headingAngle_3C);

            if (angleDelta > Q12_ANGLE(160.0f) && angleDelta < Q12_ANGLE(200.0f))
            {
                if ((chara->position_18.vy - Q12(1.3f)) < rays[0].field_18 || rays[0].field_1 == 0 || rays[0].field_1 == 12)
                {
                    if ((chara->position_18.vy - Q12(0.3f)) >= rays[0].field_18)
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

void Player_CombatUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x8007D970
{
    VECTOR                sp20; // Q19.12
    VECTOR                sp30; // Q19.12
    VECTOR                sp40; // Q19.12
    MATRIX                sp50;
    VECTOR                sp70; // Q23.8
    VECTOR                sp80; // Q23.8
    SVECTOR               sp90;
    DVECTOR               sp98;
    s32                   temp_s0;
    q23_8                 temp_v0_5;
    q23_8                 temp_v0_6;
    q3_12                 unkAngle;
    VECTOR*               vec;  // Q19.12
    VECTOR*               vec2; // Q19.12
    VECTOR*               vec3; // Q19.12
    s_Model*              model;
    static s32            pad_bss_800C44D8[2];
    static VECTOR3        D_800C44E0;
    static s32            pad_bss_800C44EC;

    model = &g_SysWork.playerWork_4C.extra_128.model_0;

    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
    {
        vec     = &g_SysWork.playerCombat_38.field_0;
        vec->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[0]);
        vec->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[1]);
        vec->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[2]);
    }
    else
    {
        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case NO_VALUE:
            case 8:
            case 9:
                vec2     = &g_SysWork.playerCombat_38.field_0;
                vec2->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[0]);
                vec2->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[1]);
                vec2->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightFoot].workm.t[2]);
                break;

            default:
                vec3     = &g_SysWork.playerCombat_38.field_0;
                vec3->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[0]);
                vec3->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[1]);
                vec3->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords_890[HarryBone_RightHand].workm.t[2]);
                break;
        }
    }

    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 != Q12(0.0f))
    {
        g_SysWork.timer_2C++;

        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 >= Q12(3.1739f) || (g_SysWork.timer_2C & (1 << 0)))
        {
            func_8006342C(g_SavegamePtr->equippedWeapon_AA - InventoryItemId_KitchenKnife, 0, 0, coord);
        }
    }

    if (!(g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_Unk7 && g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Unk51) &&
        ((g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_None && g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Idle) || g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_KickEnemy || g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_StompEnemy))
    {
        if (g_SysWork.playerCombat_38.weaponAttack_F >= EquippedWeaponId_Handgun && g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim)
        {
            if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat && g_Player_TargetNpcIdx != NO_VALUE)
            {
                sp98.vx = ratan2((g_SysWork.npcs_1A0[g_Player_TargetNpcIdx].position_18.vx + g_SysWork.npcs_1A0[g_Player_TargetNpcIdx].field_D8.offsetX_0) - g_SysWork.playerCombat_38.field_0.vx,
                                 (g_SysWork.npcs_1A0[g_Player_TargetNpcIdx].position_18.vz + g_SysWork.npcs_1A0[g_Player_TargetNpcIdx].field_D8.offsetZ_2) - g_SysWork.playerCombat_38.field_0.vz);
            }
            else
            {
                // @hack Required for match.
                do
                {
                    chara->field_2A = chara->rotation_24.vy;
                } while (0);

                sp98.vx = chara->field_2A;
            }

            sp98.vy  = g_SysWork.playerWork_4C.player_0.properties_E4.player.field_122;
            unkAngle = sp98.vy;
            if (unkAngle >= Q12_ANGLE(33.75f))
            {
                if (unkAngle > Q12_ANGLE(146.25f))
                {
                    unkAngle = Q12_ANGLE(146.25f);
                }
            }
            else
            {
                unkAngle = Q12_ANGLE(33.75f);
            }

            if (chara->field_44.field_0 > 0)
            {
                func_8006342C(g_SysWork.playerCombat_38.weaponAttack_F, unkAngle, sp98.vx, coord);
            }
        }
        else
        {
            switch (g_SysWork.playerCombat_38.weaponAttack_F)
            {
                case NO_VALUE:
                case EquippedWeaponId_Unk8:
                case EquippedWeaponId_Unk9:
                    Math_SetSVectorFast(&sp90, 0, 60, 134);
                    Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    break;

                default:
                    if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 < PlayerLowerBodyState_Aim)
                    {
                        Math_SetSVectorFast(&sp90, 0, 60, 134);
                        Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    }
                    else
                    {
                        switch (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F))
                        {
                            case EquippedWeaponId_KitchenKnife:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF),
                                                        -FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x4B, Q12_SHIFT - 1),
                                                         Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x4B) >> 1);
                                break;

                            case EquippedWeaponId_SteelPipe:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF),
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xE1) >> 1),
                                                         FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x2D, Q12_SHIFT - 2));
                                break;

                            case EquippedWeaponId_Chainsaw:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF) >> 1,
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x87) >> 1),
                                                         (Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x1EF) >> 1));
                                break;

                            case EquippedWeaponId_RockDrill:
                                Math_SetSVectorFastSum(&sp90, 0,
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x2D)),
                                                         FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x2D, Q12_SHIFT - 2));
                                break;

                            case EquippedWeaponId_Axe:
                                Math_SetSVectorFastSum(&sp90, 0,
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x2C1) >> 1),
                                                         Q12_MULT((u32)D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xC3));
                                break;

                            case EquippedWeaponId_Hammer:
                                Math_SetSVectorFastSum(&sp90, (Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF) >> 1),
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x69)),
                                                         Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x13B) >> 1);
                                break;

                            case EquippedWeaponId_Katana:
                                Math_SetSVectorFastSum(&sp90, (Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF) >> 1),
                                                        -(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0x13B) >> 1),
                                                         Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, 0xF));
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

            temp_v0_5 = Q12_TO_Q8(g_SysWork.playerCombat_38.field_0.vx) - sp70.vx;
            temp_v0_6 = Q12_TO_Q8(g_SysWork.playerCombat_38.field_0.vz) - sp70.vz;
            temp_s0   = SquareRoot0(SQUARE(temp_v0_5) + SQUARE(temp_v0_6));

            sp98.vx = ratan2(sp70.vx - Q12_TO_Q8(g_SysWork.playerCombat_38.field_0.vx),
                             sp70.vz - Q12_TO_Q8(g_SysWork.playerCombat_38.field_0.vz));
            sp98.vy = ratan2(temp_s0, sp70.vy - Q12_TO_Q8(g_SysWork.playerCombat_38.field_0.vy));
        }

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap) &&
            g_SysWork.playerCombat_38.isAiming_13 &&
            model->anim_4.status_0 >= ANIM_STATUS(HarryAnim_HandgunAim, true) && model->anim_4.keyframeIdx_8 >= 574)
        {
            if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Idle)
            {
                if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_None && g_SysWork.targetNpcIdx_2353 != NO_VALUE)
                {
                    g_SysWork.targetNpcIdx_2353 = NO_VALUE;
                }

                Math_SetSVectorFast(&sp90, 0, -39, 87);
                sp90.vz = 87;

                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp20.vx = Q8_TO_Q12(sp80.vx);
                sp20.vy = Q8_TO_Q12(sp80.vy);
                sp20.vz = Q8_TO_Q12(sp80.vz);

                if (g_GameWork.config_0.optExtraAutoAiming_2C)
                {
                    sp98.vx = chara->field_2A;
                }

                g_MapOverlayHeader.particleHyperBlasterBeamDraw_178(&sp20, &sp98.vx, &sp98.vy);
            }
        }

        if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Idle)
        {
            if ((g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) &&
                 model->anim_4.keyframeIdx_8 >= 572 && model->anim_4.keyframeIdx_8 < 584) ||
                (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) &&
                 chara->model_0.anim_4.keyframeIdx_8 >= 577 && model->anim_4.keyframeIdx_8 <  583))
            {
                Math_SetSVectorFast(&sp90, 0, 0, 0);
                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                Math_SetSVectorFast(&sp90, 0, 0, 0);
                sp30.vx = Q8_TO_Q12(sp80.vx);
                sp30.vy = Q8_TO_Q12(sp80.vy);
                sp30.vz = Q8_TO_Q12(sp80.vz);

                Vw_CoordHierarchyMatrixCompute(&coord[6], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp40.vx = Q8_TO_Q12(sp80.vx);
                sp40.vy = Q8_TO_Q12(sp80.vy);
                sp40.vz = Q8_TO_Q12(sp80.vz);
                g_MapOverlayHeader.particleBeamDraw_17C(&sp30, &sp40);
            }
        }

        if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 != PlayerUpperBodyState_AimStop)
        {
            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (D_800C4554 != NO_VALUE || D_800C4556 != D_800C4554)
                {
                    func_8008A0E4(chara->field_44.field_0, g_SysWork.playerCombat_38.weaponAttack_F, chara, &D_800C44E0, &g_SysWork.npcs_1A0[0], D_800C4556, D_800C4554);
                }
                else
                {
                    func_8008A0E4(chara->field_44.field_0, g_SysWork.playerCombat_38.weaponAttack_F, chara, &D_800C44E0, &g_SysWork.npcs_1A0[0], sp98.vx, sp98.vy);
                }
            }
            else
            {
                func_8008A0E4(chara->field_44.field_0, g_SysWork.playerCombat_38.weaponAttack_F, chara, &g_SysWork.playerCombat_38.field_0, &g_SysWork.npcs_1A0[0], sp98.vx, sp98.vy);
            }

            D_800C42D2 = sp98.vx;
            D_800C42D0 = sp98.vy;
        }
    }

    D_800C44E0 = g_SysWork.playerCombat_38.field_0;
}

void Game_SavegameResetPlayer(void) // 0x8007E530
{
    #define DEFAULT_INV_SLOT_COUNT 8

    s32 i;

    g_SavegamePtr->inventorySlotCount_AB = DEFAULT_INV_SLOT_COUNT;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        g_SavegamePtr->items_0[i].id_0    = NO_VALUE;
        g_SavegamePtr->items_0[i].count_1 = 0;
    }

    g_SavegamePtr->playerHealth_240      = Q12(100.0f);
    g_SavegamePtr->field_A0              = 0;
    g_SavegamePtr->equippedWeapon_AA     = InventoryItemId_Unequipped;
    g_SavegamePtr->healthSaturation_238  = Q12(0.0f);
    g_SavegamePtr->gameplayTimer_250     = Q12(0.0f);
    g_SavegamePtr->runDistance_254       = Q12(0.0f);
    g_SavegamePtr->walkDistance_258      = Q12(0.0f);
    g_SavegamePtr->pickedUpItemCount_23C = 0;
    g_SavegamePtr->clearGameCount_24A    = 0;
    g_SavegamePtr->add290Hours_25C_1     = 0;
}

void Game_PlayerInfoInit(void) // 0x8007E5AC
{
    s32      i;
    u32      temp_t0;
    s_Model* model;
    s_Model* extraModel;

    SysWork_SavegameReadPlayer();

    g_SysWork.playerWork_4C.player_0.model_0.charaId_0  = Chara_Harry;
    g_SysWork.playerWork_4C.extra_128.model_0.charaId_0 = Chara_Harry;
    g_SysWork.playerWork_4C.player_0.field_D4.radius_0  = Q12(0.3f);
    g_SysWork.playerWork_4C.player_0.field_D4.field_2   = Q12(0.23f);

    extraModel = &g_SysWork.playerWork_4C.player_0.model_0;
    model      = &g_SysWork.playerWork_4C.extra_128.model_0;

    g_SysWork.enablePlayerMatchAnim_2358 = false;

    extraModel->anim_4.flags_2 |= AnimFlag_Unlocked | AnimFlag_Visible;
    model->anim_4.flags_2      |= AnimFlag_Unlocked | AnimFlag_Visible;

    g_SysWork.playerWork_4C.player_0.field_E1_0 = 3;
    g_Inventory_EquippedItem                    = g_SavegamePtr->equippedWeapon_AA;

    // Should be `g_SavegamePtr->equippedWeapon_AA / 32`, but causes swap register missmatch.
    temp_t0 = g_SavegamePtr->equippedWeapon_AA >> 5;

    // Assign weapon which the player was holding when saving.
    // `temp_t0` == 4 means melee weapon, 5 means gun weapon.
    // Other values are non-equipable items.
    if (temp_t0 >= 4 && temp_t0 < 6)
    {
        for (i = 0; g_SavegamePtr->items_0[i].id_0 != g_SavegamePtr->equippedWeapon_AA && i < INVENTORY_ITEM_COUNT_MAX; i++);

        g_SysWork.playerCombat_38.weaponAttack_F        = g_SavegamePtr->equippedWeapon_AA + InventoryItemId_KitchenKnife;
        g_SysWork.playerCombat_38.currentWeaponAmmo_10  = g_SavegamePtr->items_0[i].count_1;
        g_SysWork.playerCombat_38.weaponInventoryIdx_12 = i;

        if (temp_t0 == 4)
        {
            g_SysWork.playerCombat_38.totalWeaponAmmo_11 = 0;
        }
        else
        {
            for (i = 0;
                 g_SavegamePtr->items_0[i].id_0 != (g_SavegamePtr->equippedWeapon_AA + InventoryItemId_HealthDrink) && i < INVENTORY_ITEM_COUNT_MAX;
                 i++);

            if (i == INVENTORY_ITEM_COUNT_MAX)
            {
                g_SysWork.playerCombat_38.totalWeaponAmmo_11 = 0;
            }
            else
            {
                g_SysWork.playerCombat_38.totalWeaponAmmo_11 = (s8)g_SavegamePtr->items_0[i].count_1;
            }
        }
    }
    else
    {
        g_SysWork.playerCombat_38.weaponAttack_F        = NO_VALUE;
        g_SysWork.playerCombat_38.currentWeaponAmmo_10  = 0;
        g_SysWork.playerCombat_38.totalWeaponAmmo_11    = 0;
        g_SysWork.playerCombat_38.weaponInventoryIdx_12 = NO_VALUE;
    }

    g_SysWork.playerCombat_38.isAiming_13 = false;
    g_Player_GrabReleaseInputTimer        = Q12(0.0f);
    D_800C4588                            = 0;
    D_800C457C                            = 0;
    g_Player_DisableControl               = false;

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            D_800C45EC = Q12(5.0f);
            break;

        case GameDifficulty_Normal:
            D_800C45EC = Q12(2.5f);
            break;

        case GameDifficulty_Hard:
            D_800C45EC = Q12(1.8f);
            break;
    }

    g_Player_LastWeaponSelected = NO_VALUE;
    g_GameWork.mapAnimIdx_5B1   = NO_VALUE;

    g_SavegamePtr->inventorySlotCount_AB       = CLAMP(g_SavegamePtr->inventorySlotCount_AB, INVENTORY_ITEM_COUNT_MAX / 5, INVENTORY_ITEM_COUNT_MAX);
    g_SysWork.playerWork_4C.player_0.health_B0 = CLAMP(g_SysWork.playerWork_4C.player_0.health_B0, 1, Q12(100.0f));
}

void func_8007E860(void) // 0x8007E860
{
    s32 i;
    s32 startIdx;

    for (i = 0; i < 8; i++)
    {
        startIdx                            = 92;
        HARRY_BASE_ANIM_INFOS[startIdx + i] = g_MapOverlayHeader.animInfos_34[i + 16];
    }
}

void func_8007E8C0(void) // 0x8007E8C0
{
    s32             i;
    s_AnimInfo*     animInfos;
    s_SubCharacter* chara;

    chara     = &g_SysWork.playerWork_4C.player_0;
    animInfos = g_MapOverlayHeader.animInfos_34;

    for (i = 76; animInfos->updateFunc_0 != NULL; i++, animInfos++)
    {
        HARRY_BASE_ANIM_INFOS[i] = g_MapOverlayHeader.animInfos_34[i - 76];
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S01)
    {
        g_SysWork.enablePlayerMatchAnim_2358 = false;
    }

    chara->properties_E4.player.exhaustionTimer_FC      = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_0   = Q12(-1.6f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_2   = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_6   = Q12(-1.1f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
    chara->field_D4.radius_0                            = Q12(0.3f);
    chara->field_D4.field_2                             = Q12(0.23f);
    g_GameWork.mapAnimIdx_5B1                           = NO_VALUE;

    func_8007E9C4();
}

void func_8007E9C4(void) // 0x8007E9C4
{
    s_SubCharacter* chara;

    chara = &g_SysWork.playerWork_4C.player_0;

    g_Player_IsInWalkToRunTransition                         = false;
    g_SysWork.playerWork_4C.extra_128.state_1C               = PlayerState_None;
    g_SysWork.playerWork_4C.extra_128.upperBodyState_20      = PlayerUpperBodyState_None;
    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24      = PlayerLowerBodyState_None;
    g_SysWork.playerWork_4C.extra_128.model_0.stateStep_3    = 0;
    g_SysWork.playerWork_4C.extra_128.model_0.controlState_2 = ModelState_Uninitialized;

    chara->model_0.stateStep_3            = 0;
    chara->model_0.controlState_2         = ModelState_Uninitialized;
    g_SysWork.playerStopFlags_235A        = PlayerStopFlag_None;
    g_Player_FlexRotationY                = Q12_ANGLE(0.0f);
    g_Player_FlexRotationX                = Q12_ANGLE(0.0f);
    D_800C4560                            = NO_VALUE;
    g_SysWork.playerCombat_38.isAiming_13 = false;

    func_8004C564(0, NO_VALUE);

    chara->field_2A         = Q12_ANGLE(90.0f);
    g_Player_IsDead         = false;
    g_Player_DisableDamage  = false;
    g_Player_HasActionInput = false;
    g_Player_HasMoveInput   = false;
    g_Player_IsShooting     = false;
    g_Player_IsAttacking    = false;

    chara->properties_E4.player.afkTimer_E8      = Q12(0.0f);
    chara->properties_E4.player.field_F4         = 0;
    chara->properties_E4.player.runTimer_F8      = Q12(0.0f);
    chara->properties_E4.player.field_100        = 0;
    chara->properties_E4.player.field_104        = 0;
    chara->properties_E4.player.runTimer_108     = Q12(0.0f);
    chara->properties_E4.player.timer_110        = 0;
    chara->properties_E4.player.flags_11C        = 0;
    chara->properties_E4.player.moveDistance_126 = 0;

    Chara_DamageClear(chara);

    g_Player_IsHoldAttack       = false;
    chara->flags_3E            &= ~CharaFlag_Unk4;
    g_Player_PrevPosition       = chara->position_18;
    g_SysWork.targetNpcIdx_2353 = NO_VALUE;
    chara->field_40             = NO_VALUE;
    chara->attackReceived_41    = NO_VALUE;

    g_SysWork.npcIdxs_2354[3] = NO_VALUE;
    g_SysWork.npcIdxs_2354[2] = NO_VALUE;
    g_SysWork.npcIdxs_2354[1] = NO_VALUE;
    g_SysWork.npcIdxs_2354[0] = NO_VALUE;
    chara->field_D4.field_2   = Q12(0.23f);

    g_Player_IsAiming            = false;
    g_Player_IsRunning           = false;
    g_Player_IsMovingBackward    = false;
    g_Player_IsMovingForward     = false;
    g_Player_IsSteppingRightTap  = false;
    g_Player_IsSteppingRightHold = false;
    g_Player_IsTurningRight      = false;
    g_Player_IsSteppingLeftTap   = false;
    g_Player_IsSteppingLeftHold  = false;
    g_Player_IsTurningLeft       = false;
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

void GameFs_WeaponInfoUpdate(void) // 0x8007EBBC
{
    s32 relAnimInfoIdx;
    s32 relKeyframeIdx;
    s32 i;

    relAnimInfoIdx = 0;
    relKeyframeIdx = 0;

    g_SysWork.targetNpcIdx_2353 = NO_VALUE;

    switch (g_SysWork.playerCombat_38.weaponAttack_F)
    {
        case NO_VALUE:
            g_Player_EquippedWeaponInfo = D_800AFBF4[0];
            return;

        case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
            relAnimInfoIdx                                    = 30;
            relKeyframeIdx                                    = 15;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[1];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x1030;
            break;

        default:
            return;

        case WEAPON_ATTACK(EquippedWeaponId_Axe, AttackInputType_Tap):
            relAnimInfoIdx                                    = 0;
            relKeyframeIdx                                    = 0;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[3];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0xFD0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_Hammer, AttackInputType_Tap):
            g_Player_EquippedWeaponInfo = D_800AFBF4[2];
            switch (g_SysWork.playerCombat_38.weaponAttack_F)
            {
                case WEAPON_ATTACK(EquippedWeaponId_Hammer, AttackInputType_Tap):
                    relAnimInfoIdx = 10;
                    relKeyframeIdx = 5;
                    break;

                case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
                    relAnimInfoIdx = 20;
                    relKeyframeIdx = 10;
                    break;
            }

            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0xEC0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
            relAnimInfoIdx                                    = 50;
            relKeyframeIdx                                    = 25;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[4];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0xE90;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap):
            relAnimInfoIdx                                    = 64;
            relKeyframeIdx                                    = 32;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[5];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x12E0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Katana, AttackInputType_Tap):
            relAnimInfoIdx                                    = 40;
            relKeyframeIdx                                    = 20;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[10];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0xF20;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap):
            relAnimInfoIdx                                    = 78;
            relKeyframeIdx                                    = 39;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[6];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x1600;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
            relAnimInfoIdx                                    = 96;
            relKeyframeIdx                                    = 48;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[7];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x1180;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Shotgun, AttackInputType_Tap):
            relAnimInfoIdx                                    = 114;
            relKeyframeIdx                                    = 57;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[8];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x1600;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
            relAnimInfoIdx                                    = 132;
            relKeyframeIdx                                    = 66;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[9];
            g_SysWork.playerWork_4C.player_0.field_C8.field_8 = -0x1610;
            break;
    }

    for (i = 56; i < 76; i++)
    {
        HARRY_BASE_ANIM_INFOS[i] = D_80028B94[(i - 56) + relAnimInfoIdx];
    }

    for (i = 0; i < 10; i++)
    {
        D_800C44F0[i] = D_800294F4[i + relKeyframeIdx];
    }

    if (g_SysWork.playerCombat_38.weaponAttack_F != NO_VALUE && g_Player_LastWeaponSelected != g_SysWork.playerCombat_38.weaponAttack_F)
    {
        g_Player_LastWeaponSelected = g_SysWork.playerCombat_38.weaponAttack_F;
        func_8007F14C(g_SysWork.playerCombat_38.weaponAttack_F);

        switch (g_SysWork.playerCombat_38.weaponAttack_F)
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

void func_8007F14C(u8 weaponAttack) // 0x8007F14C
{
    switch (weaponAttack)
    {
        case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Tap):
            SD_Call(164);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
            SD_Call(169);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap):
            SD_Call(163);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap):
            SD_Call(166);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
            SD_Call(167);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Shotgun, AttackInputType_Tap):
            SD_Call(168);
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
            SD_Call(165);
            break;
    }
}

void Game_PlayerMovementsReset(void) // 0x8007F1CC
{
    g_Player_HasActionInput          = false;
    g_Player_HasMoveInput            = false;
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

void Player_DisableDamage(u8* playerIsDead, u8 disableDamage) // 0x8007F250
{
    *playerIsDead          = g_Player_IsDead;
    g_Player_DisableDamage = disableDamage;
}

bool Player_IsAttacking(void) // 0x8007F26C
{
    if (g_SysWork.playerWork_4C.extra_128.upperBodyState_20 == PlayerUpperBodyState_Attack ||
        g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_KickEnemy ||
        g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_StompEnemy)
    {
        return true;
    }

    return false;
}

bool Player_IsBusy(void) // 0x8007F2AC
{
    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) ||
        g_SysWork.playerCombat_38.isAiming_13 ||
        g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_KickEnemy ||
        g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_StompEnemy ||
        (g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_Unk7 &&
         g_SysWork.playerWork_4C.extra_128.state_1C <= PlayerState_GetUpBack))
    {
        return true;
    }

    return false;
}

s16 Player_AnimGetSomething(void) // 0x8007F308
{
    return HARRY_BASE_ANIM_INFOS[g_SysWork.playerWork_4C.player_0.model_0.anim_4.status_0].startKeyframeIdx_C;
}

void Player_Controller(void) // 0x8007F32C
{
    s32 attackBtnInput;

    g_Player_IsMovingForward    = (g_Player_IsMovingForward * 2) & 0x3;
    g_Player_IsSteppingLeftTap  = (g_Player_IsSteppingLeftTap * 2) & 0x3F;
    g_Player_IsSteppingRightTap = (g_Player_IsSteppingRightTap * 2) & 0x3F;

    if (g_Controller0->sticks_20.sticks_0.leftY < -STICK_THRESHOLD || g_Controller0->sticks_20.sticks_0.leftY >= STICK_THRESHOLD ||
        g_Controller0->sticks_20.sticks_0.leftX < -STICK_THRESHOLD || g_Controller0->sticks_20.sticks_0.leftX >= STICK_THRESHOLD)
    {
        g_Player_IsTurningLeft    = g_Controller0->sticks_20.sticks_0.leftX < -STICK_THRESHOLD ? ABS(g_Controller0->sticks_20.sticks_0.leftX + STICK_THRESHOLD) : 0;
        g_Player_IsTurningRight   = g_Controller0->sticks_20.sticks_0.leftX >= STICK_THRESHOLD ? (g_Controller0->sticks_20.sticks_0.leftX - (STICK_THRESHOLD - 1)) : 0;
        g_Player_IsMovingForward |= g_Controller0->sticks_20.sticks_0.leftY < -STICK_THRESHOLD;
        g_Player_IsMovingBackward = g_Controller0->sticks_20.sticks_0.leftY >= STICK_THRESHOLD;
        g_Player_HasMoveInput     = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10 |
                                                                              (ControllerFlag_LStickUp2 | ControllerFlag_LStickRight2 | ControllerFlag_LStickDown2 | ControllerFlag_LStickLeft2) |
                                                                              g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12 | g_GameWorkPtr->config_0.controllerConfig_0.aim_8);
    }
    else
    {
        g_Player_IsTurningLeft    = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickLeft) << 6;
        g_Player_IsTurningRight   = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickRight) << 6;
        g_Player_IsMovingForward |= (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickUp;
        g_Player_IsMovingBackward = (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickDown;
        g_Player_HasMoveInput     = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10 |
                                                                              (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft) |
                                                                              g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12 | g_GameWorkPtr->config_0.controllerConfig_0.aim_8);
    }

    g_Player_IsSteppingLeftHold  = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10) &&
                                  !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12);

    g_Player_IsSteppingRightHold = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepRight_12) &&
                                  !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10);

    g_Player_IsSteppingLeftTap  |= (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.stepLeft_10)  != 0;
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

    if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim)
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

    g_Player_HasActionInput = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.run_C | g_GameWorkPtr->config_0.controllerConfig_0.action_6);

    if (g_SysWork.sysState_8 != SysState_Gameplay)
    {
        g_Player_IsShooting   = false;
        g_Player_IsAttacking  = false;
        g_Player_IsHoldAttack = false;
    }

    if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
    {
        switch (Inventory_HyperBlasterFunctionalTest())
        {
            case 0: // Player has weapon (not unlocked).
                g_Player_IsAiming = false;
                break;

            case 1: // Konami gun controller.
                g_Player_IsAiming    = g_Controller1->btnsHeld_C & ControllerFlag_Cross;
                g_Player_IsShooting  = g_Controller1->btnsHeld_C & ControllerFlag_Square;
                g_Player_IsAttacking = g_Player_IsShooting;
                break;

            case 2: // Player has weapon (unlocked).
                break;
        }
    }

    // This is the conditional that makes impossible to move when aiming with specific weapons.
    if (g_SysWork.playerCombat_38.isAiming_13 && (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap) ||
                                                      (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                                                       (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Hammer ||
                                                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_RockDrill ||
                                                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_Katana))))
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

bool func_8007F95C(void) // 0x8007F95C
{
    VECTOR3         pos0;
    VECTOR3         pos1;
    u16             sp30;
    s32             i;
    u16             temp;
    q19_12          radius;
    s_SubCharacter* curNpc1;
    s_SubCharacter* curNpc0;

    if (g_Player_IsInWalkToRunTransition)
    {
        return false;
    }

    pos0.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
    pos0.vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
    pos0.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (!g_SysWork.playerCombat_38.isAiming_13 ||
        g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
    {
        for (i = 0, curNpc0 = g_SysWork.npcs_1A0, curNpc1 = g_SysWork.npcs_1A0;
             i < ARRAY_SIZE(g_SysWork.npcs_1A0);
             i++, curNpc0++, curNpc1++)
        {
            if (curNpc1->model_0.charaId_0 != Chara_None)
            {
                if (curNpc1->model_0.charaId_0 == Chara_AirScreamer ||
                    curNpc1->model_0.charaId_0 == Chara_NightFlutter)
                {
                    radius = Q12(1.2f);
                }
                else
                {
                    if (curNpc1->model_0.charaId_0 == Chara_Creeper)
                    {
                        radius = Q12(0.65f);
                    }
                    else
                    {
                        radius = Q12(0.85f);
                    }
                }

                pos1.vx = curNpc0->position_18.vx + curNpc0->field_D8.offsetX_0;
                pos1.vy = curNpc0->position_18.vy;
                pos1.vz = curNpc0->position_18.vz + curNpc0->field_D8.offsetZ_2;

                if (!Math_Distance2dCheck(&pos0, &pos1, radius) && ABS(pos1.vy - pos0.vy) < Q12(0.3f) &&
                    curNpc0->health_B0 > Q12(0.0f) && (curNpc0->flags_3E & CharaFlag_Unk2))
                {
                    Math_ShortestAngleGet(g_SysWork.playerWork_4C.player_0.rotation_24.vy,
                                          Q12_ANGLE_NORM_U(ratan2(pos1.vx - pos0.vx, pos1.vz - pos0.vz) + Q12_ANGLE(360.0f)),
                                          &sp30);

                    temp = sp30 + Q12_ANGLE(89.98f);
                    if (temp < Q12_ANGLE(202.49f))
                    {
                        g_SysWork.targetNpcIdx_2353 = i;
                        return true;
                    }
                }
            }
        }
    }

    g_SysWork.targetNpcIdx_2353 = NO_VALUE;
    return false;
}

void Math_ShortestAngleGet(q3_12 angleFrom, q3_12 angleTo, q3_12* shortestAngle) // 0x8007FB34
{
    q3_12 adjAngle;

    if (angleTo > angleFrom)
    {
        if ((angleTo - angleFrom) < Q12_ANGLE(180.0f))
        {
            *shortestAngle = angleTo - angleFrom;
        }
        else
        {
            adjAngle       = angleTo  - Q12_ANGLE(360.0f);
            *shortestAngle = adjAngle - angleFrom;
        }
    }
    else
    {
        if ((angleFrom - angleTo) < Q12_ANGLE(180.0f))
        {
            *shortestAngle = angleTo - angleFrom;
        }
        else
        {
            adjAngle       = angleFrom - Q12_ANGLE(360.0f);
            *shortestAngle = angleTo   - adjAngle;
        }
    }
}

void func_8007FB94(s_SubCharacter* chara, s_PlayerExtra* extra, s32 animStatus) // 0x8007FB94
{
    s32 i;

    if (extra->model_0.controlState_2 != 0)
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

        extra->model_0.controlState_2++;
    }
}

void func_8007FC48(s_SubCharacter* chara, s_PlayerExtra* extra, s32 animStatus) // 0x8007FC48
{
    s32 i;

    if (extra->model_0.controlState_2 != 0)
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
        extra->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0 + 1; // TODO: There's a macro for anim status++.
        chara->model_0.anim_4.status_0 = g_MapOverlayHeader.field_38[i].status_0 + 1;

        // Increment state step.
        extra->model_0.stateStep_3++;
        chara->model_0.stateStep_3++;

        // Set anim time.
        extra->model_0.anim_4.time_4 = Q12(g_MapOverlayHeader.field_38[i].time_4);
        D_800AF220                   = i;
        chara->model_0.anim_4.time_4 = Q12(g_MapOverlayHeader.field_38[i].time_4);
        i                            = 41;

        // Increment state.
        extra->model_0.controlState_2++;
    }
}

s32 func_8007FD2C(void) // 0x8007FD2C
{
    return g_SysWork.playerWork_4C.player_0.properties_E4.player.field_104;
}

q19_12 Game_GasWeaponPowerTimerValue(void) // 0x8007FD3C
{
    return g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114;
}

void func_8007FD4C(bool cond) // 0x8007FD4C
{
    s32             i;
    s_SubCharacter* chara;

    chara = &g_SysWork.playerWork_4C.player_0;

    g_Player_GrabReleaseInputTimer = Q12(0.0f);
    chara->field_40                = NO_VALUE;

    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_DamageReceived;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcIdxs_2354); i++)
    {
        g_SysWork.npcIdxs_2354[i] = NO_VALUE;
    }

    if (cond)
    {
        g_SysWork.playerWork_4C.player_0.field_D4.radius_0   = Q12(0.3f);
        g_SysWork.playerWork_4C.player_0.field_D4.field_2   = Q12(0.23f);
        g_SysWork.playerWork_4C.player_0.field_C8.field_0   = Q12(-1.6f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0 = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_C8.field_2   = Q12(0.0f);
        g_SysWork.playerWork_4C.player_0.field_C8.field_6   = Q12(-1.1f);
    }
}

void func_8007FDE0(s8 arg0, e_SfxId* sfxId, s8* pitch0, s8* pitch1) // 0x8007FDE0
{
    // `arg0` usually comes from `s_Collision::field_8`, maybe floor type?
    s32 mapOverlayId;

    switch (arg0)
    {
        case 8:
            mapOverlayId = g_SavegamePtr->mapOverlayId_A4;
            *sfxId       = Sfx_Unk1330;

            // @hack Odd redundant load of `mapOverlayId_A4`, likely there was some optimized-out code above that left side-effects?
            // This just sets `mapOverlayId` to `g_SavegamePtr->mapOverlayId_A4` (again).
            asm volatile(
                "lui   $2, %%hi(g_SavegamePtr)\n"
                "lw    $2, %%lo(g_SavegamePtr)($2)\n"
                "nop\n"
                "lb    $3, 164($2)\n"
                :
                :
                : "memory");

            if (mapOverlayId == MapOverlayId_MAP2_S00)
            {
                if (g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(95.0f)  && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(105.0f) &&
                    g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(-33.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(-28.0f))
                {
                    *sfxId = Sfx_Unk1389;
                }
            }
            break;

        case 3:
            *sfxId = Sfx_FootstepGrass;
            break;

        case 4:
            *sfxId = Sfx_Unk1313;
            break;

        case 5:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP4_S02)
            {
                *sfxId = Sfx_Unk1543;
            }
            else
            {
                *sfxId = Sfx_Unk1557;
            }
            break;

        case 6:
        case 10:
        case 11:
            *sfxId = Sfx_FootstepMetal;
            break;

        case 9:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S02)
            {
                *sfxId = Sfx_Unk1388;
            }
            else
            {
                *sfxId = Sfx_Unk1331;
            }
            break;

        case 2:
            *sfxId = Sfx_Unk1389;
            break;

        default:
        case 0:
        case 1:
        case 7:
            *sfxId = Sfx_FootstepConcrete;
            break;
    }

    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP6_S02:
            switch (g_SavegamePtr->mapRoomIdx_A5)
            {
                case 20:
                    if (g_SysWork.playerWork_4C.player_0.position_18.vy > Q12(0.0f))
                    {
                        *sfxId = Sfx_Unk1346;
                    }
                    break;

                case 21:
                    if (arg0 != 1)
                    {
                        *sfxId = Sfx_Unk1346;
                    }
                    break;
            }
            break;

        case MapOverlayId_MAP4_S03:
            if ((g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(165.0f)   &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(58.5f)    && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(61.5f)) ||
                (g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(112.1f)   &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(-101.45f) && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(-98.5f)))
            {
                *sfxId = Sfx_Unk1565;
            }

        case MapOverlayId_MAP6_S00:
            if ((g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(-160.1f)  && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-158.5f)  &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(26.8f)    && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(27.4f))   ||
                (g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(-160.1f)  && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-158.5f)  &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(16.8f)    && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(17.5f))   ||
                (g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(-170.0f)  && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-165.8f)  &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(-16.4f)   && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(-14.35f)) ||
                (g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(-172.7f)  && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-170.9f)  &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(-24.9f)   && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(-21.25f)) ||
                (g_SysWork.playerWork_4C.player_0.position_18.vx >= Q12(-170.28f) && g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-165.85f) &&
                 g_SysWork.playerWork_4C.player_0.position_18.vz >= Q12(-35.4f)   && g_SysWork.playerWork_4C.player_0.position_18.vz <= Q12(-34.35f)))
            {
                *sfxId = Sfx_Unk1600;
            }
            break;

        case MapOverlayId_MAP6_S01:
            if (g_SavegamePtr->mapRoomIdx_A5 == 18)
            {
                *sfxId = Sfx_Unk1608;
            }
            break;

        case MapOverlayId_MAP6_S04:
            *sfxId = Sfx_FootstepMetal;
            break;
    }

    switch (arg0)
    {
        case 5:
        case 6:
        case 10:
        case 11:
            *pitch0 = (Rng_Rand16() % 8) - 4;
            *pitch1 = (Rng_Rand16() % 16) + 56;
            break;

        default:
            *pitch0 = (Rng_Rand16() % 32) - 16;
            *pitch1 = (Rng_Rand16() % 64) + 32;
            break;
    }
}

q19_12 Math_DistanceGet(const VECTOR3* from, const VECTOR3* to) // 0x800802CC
{
    q19_12 deltaX;
    q19_12 deltaY;
    q19_12 deltaZ;

    deltaX = to->vx - from->vx;
    deltaY = to->vy - from->vy;
    deltaZ = to->vz - from->vz;
    return SquareRoot12(Q12_MULT_PRECISE(deltaX, deltaX) +
                        Q12_MULT_PRECISE(deltaY, deltaY) +
                        Q12_MULT_PRECISE(deltaZ, deltaZ));
}

q19_12 Math_Distance2dGet(const VECTOR3* from, const VECTOR3* to) // 0x8008037C
{
    q19_12 deltaX;
    q19_12 deltaZ;

    deltaX = to->vx - from->vx;
    deltaZ = to->vz - from->vz;
    return SquareRoot12(Q12_MULT_PRECISE(deltaX, deltaX) +
                        Q12_MULT_PRECISE(deltaZ, deltaZ));
}

void func_800803FC(VECTOR3* pos, s32 idx) // 0x800803FC
{
    q19_12 posX;
    q19_12 posZ;

    posX = g_MapOverlayHeader.charaSpawns_24C[0][idx].positionX_0;
    posZ = g_MapOverlayHeader.charaSpawns_24C[0][idx].positionZ_8;

    pos->vx = posX;
    pos->vy = Collision_GroundHeightGet(posX, posZ);
    pos->vz = posZ;
}

void Input_SelectClickSet(void) // 0x80080458
{
    g_Controller1->btnsClicked_10 |= ControllerFlag_Select;
}

q19_12 func_80080478(const VECTOR3* pos0, const VECTOR3* pos1) // 0x80080478
{
    q19_12 x0;
    q19_12 x1;
    q19_12 y1;
    q19_12 y0;
    q19_12 z0;
    q19_12 z1;
    q19_12 deltaX;
    q19_12 deltaZ;
    u16    atan2Delta;
    s32    unk;

    x0 = pos0->vx;
    x1 = pos1->vx;
    y0 = pos0->vy;
    y1 = pos1->vy;
    z0 = pos0->vz;
    z1 = pos1->vz;

    deltaX     = x1 - x0;
    deltaZ     = z1 - z0;
    atan2Delta = ratan2(deltaX, deltaZ);

    unk = func_8008A058(func_80080540(deltaX, Q12(0.0f), deltaZ));
    return (ratan2(unk, y1 - y0) << 16) | atan2Delta;
}

q19_12 Rng_RandQ12(void) // 0x80080514
{
    s32 rand16;

    rand16 = Rng_Rand16();
    return Q12_ANGLE_NORM_U(((rand16 * 2) ^ rand16) >> 3);
}

s32 func_80080540(s32 arg0, s32 arg1, s32 arg2) // 0x80080540
{
    s32 v0;

    __asm__ volatile(
        "mult %0, %0\n"
        "mflo $4\n"
        "mfhi $3\n"
        "srl  $4, $4, 0xc\n"
        "sll  $3, $3, 0x14\n"

        "mult %1, %1\n"
        "or   %3, $3, %0\n"
        "mflo $4\n"
        "mfhi $3\n"
        "srl  $4, $4, 0xc\n"
        "sll  $3, $3, 0x14\n"

        "mult %2, %2\n"
        "or   %1, $3, %0\n"
        "mflo $4\n"
        "mfhi $3\n"
        "srl  $4, $4, 0xc\n"
        "sll  $3, $3, 0x14\n"
        "or   %2, $3, $4\n"

        : "r="(arg0), "r="(arg1), "r="(arg2), "r="(v0)
        : "r"(arg0), "r"(arg1), "r"(arg2));

    return v0 + arg1 + arg2;
}

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

        pos->vx = Q8_TO_Q12(vec.vx);
        pos->vy = Q8_TO_Q12(vec.vy);
        pos->vz = Q8_TO_Q12(vec.vz);

        arg3--;
        rot++;
        pos++;
    }
}

bool func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800806AC
{
    bool result;
    //static s_Collision D_800C4620;

    result = arg0 != 0;
    if (!result)
    {
        return result;
    }

    result = arg0 == NO_VALUE;
    if (result)
    {
        return result;
    }

    Collision_Get(&D_800C4620, arg1, arg3);

    result = arg2 < D_800C4620.groundHeight_0;
    if (result)
    {
        result = D_800C4620.field_8 != NO_VALUE;
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

void Collision_Fill(q19_12 posX, q19_12 posZ) // 0x8008076C
{
    q19_12       groundHeight;
    s32          count;
    q19_12       collX;
    q19_12       collZ;
    s_Collision* coll;

    coll = &g_CollisionPoint.collision_C;

    collX = g_CollisionPoint.position_0.vx;
    collZ = g_CollisionPoint.position_0.vz;
    if (g_CollisionPoint.field_18 != NO_VALUE && collX == posX && collZ == posZ)
    {
        return;
    }

    Collision_Get(coll, posX, posZ);
    g_CollisionPoint.position_0.vx = posX;
    g_CollisionPoint.position_0.vz = posZ;

    count = coll->field_8;
    switch (coll->field_8)
    {
        case 0:
            groundHeight = Q12(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP5_S01:
                    if (posZ <= Q12(0.0f))
                    {
                        groundHeight = Q12(4.0f);
                        count        = 7;
                    }
                    break;

                case MapOverlayId_MAP6_S00:
                    groundHeight = Q12(4.0f);
                    count      = 7;
                    break;
            }
            break;

        case 12:
            groundHeight = Q12(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP6_S00:
                    groundHeight = Q12(4.0f);
                    count      = 7;
                    break;
            }
            break;

        default:
            groundHeight = coll->groundHeight_0;
            break;
    }

    g_CollisionPoint.position_0.vy = groundHeight;
    g_CollisionPoint.field_18      = count;
}

q19_12 Collision_GroundHeightGet(q19_12 posX, q19_12 posZ) // 0x80080884
{
    Collision_Fill(posX, posZ);
    return g_CollisionPoint.position_0.vy;
}

s32 func_800808AC(q19_12 posX, q19_12 posZ) // 0x800808AC
{
    Collision_Fill(posX, posZ);
    return g_CollisionPoint.field_18;
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

INCLUDE_RODATA("bodyprog/nonmatchings/bodyprog_800706E4", hack_D_8002A844_fix);

