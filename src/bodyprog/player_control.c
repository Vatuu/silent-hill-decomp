#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/sys/joy.h"
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
u8         __pad_bss_800C4563[13];
s_800AFBF4 g_Player_EquippedWeaponInfo;
u8         D_800C457C;
u8         __pad_bss_800C457D;
u16        g_Player_IsAiming;
u16        g_Player_IsSteppingLeftTap;
u16        g_Player_IsSteppingRightTap;
u16        g_Player_IsTurningLeft;
u16        g_Player_IsTurningRight;
u8         D_800C4588;
s8         __pad_bss_800C4589[7];
s_CollisionResult D_800C4590;
u16        g_Player_IsSteppingLeftHold;
u16        g_Player_IsSteppingRightHold;
VECTOR3    D_800C45B0;
u16        g_Player_IsHoldAttack;
u16        g_Player_IsAttacking;
u16        g_Player_IsShooting;
s8         __pad_bss_800C45C2[6];
s_800C45C8 D_800C45C8;
s8         __pad_bss_800C45E0[8];
u16        g_Player_IsMovingForward;
s8         __pad_bss_800C45EA[2];
s32        D_800C45EC;
u16        g_Player_IsMovingBackward;
s8         __pad_bss_800C45F2[6];
VECTOR3    g_Player_PrevPosition;
u16        g_Player_IsRunning;
s16        __pad_bss_800C4606;
q19_12     g_Player_HeadingAngle;
s32        __pad_bss_800C460C;
VECTOR3    D_800C4610;

#define playerProps g_SysWork.playerWork.player.properties.player

q19_12 Player_VariableAnimDurationGet(s_Model* model) // 0x800706E4
{
    q19_12 duration;

    #define playerChara g_SysWork.playerWork.player
    #define playerExtra g_SysWork.playerWork.extra.state

    duration = Q12(0.0f);

    switch (playerExtra)
    {
        case PlayerState_EnemyGrabPinnedFront:
        case PlayerState_EnemyGrabPinnedBack:
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapIdx_MAP2_S00:
                case MapIdx_MAP2_S02:
                case MapIdx_MAP4_S02:
                case MapIdx_MAP5_S01:
                case MapIdx_MAP6_S00:
                case MapIdx_MAP6_S02:
                    if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(128, false) ||
                        g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(129, false))
                    {
                        if (playerChara.health <= Q12(0.0f))
                        {
                            playerProps.afkTimer_E8 -= g_DeltaTime;
                            if (playerProps.afkTimer_E8 >= Q12(0.0f))
                            {
                                playerProps.afkTimer_E8 -= g_DeltaTime;
                                duration = playerProps.afkTimer_E8;
                            }
                            else
                            {
                                duration = Q12(0.0f);
                            }
                            break;
                        }
                    }

                    duration = Q12(15.0f);
            }
            break;

        case PlayerState_OnFloorFront:
        case PlayerState_OnFloorBehind:
            if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP6_S04)
            {
                if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(132, true) ||
                    g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(133, false))
                {
                    if (playerChara.health <= Q12(0.0f))
                    {
                        playerProps.afkTimer_E8 -= g_DeltaTime * 2;
                        if (playerProps.afkTimer_E8 >= Q12(0.0f))
                        {
                            playerProps.afkTimer_E8 -= g_DeltaTime * 2;

                            duration = playerProps.afkTimer_E8;
                        }
                        else
                        {
                            duration = Q12(0.0f);
                        }
                        break;
                    }
                }

                duration = Q12(10.0f);
            }
            break;

        default:
            switch (model->anim.status)
            {
                case ANIM_STATUS(HarryAnim_WalkForward, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        duration = (ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.65f) / 64) * 16 + Q12(12.0f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        duration = ((ABS(D_800AF216 - 64) * Q12(0.65f) / 64) * 16) + Q12(12.0f);
                    }
                    else
                    {
                        duration = Q12(22.0f);
                    }
                    break;

                case ANIM_STATUS(HarryAnim_RunForward, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        if ((model->anim.keyframeIdx >= 40 && model->anim.keyframeIdx < 46) ||
                            (model->anim.keyframeIdx >= 30 && model->anim.keyframeIdx < 36))
                        {
                            duration = ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.25f) + Q12(16.0f);
                        }
                        else
                        {
                            duration = Q12(32.0f);
                        }
                    }
                    else if (D_800AF216 != 0)
                    {
                        duration = ABS(D_800AF216 - 64) * Q12(0.25f) + Q12(16.0f);
                    }
                    else
                    {
                        duration = Q12(30.0f);
                    }
                    break;

                case ANIM_STATUS(HarryAnim_WalkBackward, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY >= 64)
                    {
                        duration = ((ABS(g_Controller0->sticks_20.sticks_0.leftY - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        duration = ((ABS(D_800AF216 - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else
                    {
                        duration = Q12(23.0f);
                    }
                    break;

                case ANIM_STATUS(HarryAnim_IdleExhausted, true):
                    if (playerChara.health < Q12(30.0f))
                    {
                        duration = Q12(40.0f) - playerChara.health;
                    }
                    else
                    {
                        duration = Q12(FP_FROM(playerProps.exhaustionTimer_FC, Q12_SHIFT));
                    }
                    break;
            }
    }

    return duration;

    #undef playerChara
    #undef playerExtra
}

const s_AnimInfo* const D_800297B8 = HARRY_BASE_ANIM_INFOS;

void func_80070B84(s_SubCharacter* player, q19_12 moveDistMax, q19_12 arg2, s32 keyframeIdx) // 0x80070B84
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
        if (moveDistMax < playerProps.moveDistance_126)
        {
            unkMoveDist                  = playerProps.moveDistance_126 - ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
            playerProps.moveDistance_126 = unkMoveDist;
            if (unkMoveDist < moveDistMax)
            {
                playerProps.moveDistance_126 = moveDistMax;
            }
        }
        else if (playerProps.moveDistance_126 < moveDistMax)
        {
            moveDist = &playerProps.moveDistance_126;
            if (player->model.anim.keyframeIdx >= keyframeIdx)
            {
                playerProps.moveDistance_126 = *moveDist + TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
            }

            playerProps.moveDistance_126 = CLAMP(*moveDist, Q12(0.0f), moveDistMax);
        }
    }
    while (false); // @hack Required for match.
}

void func_80070CF0(s_SubCharacter* player, q19_12 arg1, q19_12 moveDistMax, q19_12 moveDistForward, q19_12 modeDistBack) // 0x80070CF0
{
    s32    stickY;
    q3_12* moveDist;

    do
    {
        if ((player->model.anim.keyframeIdx >= 40 && player->model.anim.keyframeIdx < 46) ||
            (player->model.anim.keyframeIdx >= 30 && player->model.anim.keyframeIdx < 36))
        {
            stickY      = D_800AF216 ? D_800AF216 : ABS(g_Controller0->sticks_20.sticks_0.leftY);
            moveDistMax = arg1 + ((moveDistMax - arg1) * (stickY - 64) / 64);
        }
    }
    while (false); // @hack Required for match.

    if (moveDistMax < playerProps.moveDistance_126)
    {
        playerProps.moveDistance_126 -= modeDistBack;
        if (playerProps.moveDistance_126 < moveDistMax)
        {
            playerProps.moveDistance_126 = moveDistMax;
        }
    }
    else
    {
        moveDist = &playerProps.moveDistance_126;
        if (playerProps.moveDistance_126 < moveDistMax)
        {
            playerProps.moveDistance_126 += moveDistForward;
            playerProps.moveDistance_126  = CLAMP(*moveDist, Q12(0.0f), moveDistMax);
        }
    }
}

void func_80070DF0(s_PlayerExtra* extra, s_SubCharacter* player, s32 weaponAttack, s32 animStatus)  // 0x80070DF0
{
    q3_12 shortestAngle;
    q3_12 angleTo;

    if (extra->model.stateStep == 0)
    {
        extra->model.anim.status = animStatus - 1;
        extra->model.stateStep++;
    }

    if (player->model.stateStep == 0)
    {
        player->model.anim.status = animStatus - 1;
        player->model.stateStep++;
    }

    angleTo = Q12_FRACT(ratan2((g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vx + g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetX_0) - g_SysWork.playerCombat.field_0.vx,
                               (g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vz + g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetZ_2) - g_SysWork.playerCombat.field_0.vz) +
                          Q12_ANGLE(360.0f));
    player->field_2A = angleTo;
    Math_ShortestAngleGet(player->rotation.vy, angleTo, &shortestAngle);

    if (ABS(shortestAngle) >= Q12_ANGLE(8.5f))
    {
        if (shortestAngle < 0)
        {
            player->rotation.vy -= Q12_ANGLE(8.5f);
        }
        else
        {
            player->rotation.vy += Q12_ANGLE(8.5f);
        }
    }

    if (extra->model.anim.keyframeIdx >= (HARRY_BASE_ANIM_INFOS[animStatus].startKeyframeIdx + D_800AD4C8[weaponAttack].field_E) &&
        ((HARRY_BASE_ANIM_INFOS[animStatus].startKeyframeIdx + D_800AD4C8[weaponAttack].field_E) + D_800AD4C8[weaponAttack].field_F) >= extra->model.anim.keyframeIdx)
    {
        g_SysWork.playerCombat.weaponAttack = weaponAttack;

        if (!(playerProps.flags_11C & PlayerFlag_Unk2))
        {
            player->field_44.field_0                                     = 1;
            playerProps.flags_11C |= PlayerFlag_Unk2;
        }
    }

    if (animStatus == ANIM_STATUS(HarryAnim_Kick, true) && ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
    {
        g_SysWork.playerWork.player.field_D8.offsetX_0 =  Q12_MULT(D_800AF014[player->model.anim.keyframeIdx - 457], Math_Cos(player->rotation.vy));
        g_SysWork.playerWork.player.field_D8.offsetZ_2 = -Q12_MULT(D_800AF014[player->model.anim.keyframeIdx - 457], Math_Sin(player->rotation.vy));
        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
    }

    if (animStatus == ANIM_STATUS(HarryAnim_Stomp, true) && ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
    {
        g_SysWork.playerWork.player.field_D8.offsetX_0 =  Q12_MULT(D_800AF04C[player->model.anim.keyframeIdx - 485], Math_Cos(player->rotation.vy));
        g_SysWork.playerWork.player.field_D8.offsetZ_2 = -Q12_MULT(D_800AF04C[player->model.anim.keyframeIdx - 485], Math_Sin(player->rotation.vy));
        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
    }

    if (player->model.anim.status == animStatus &&
        player->model.anim.keyframeIdx == HARRY_BASE_ANIM_INFOS[animStatus].endKeyframeIdx)
    {
        playerProps.flags_11C &= ~PlayerFlag_Unk2;

        Player_ExtraStateSet(player, extra, PlayerState_None);

        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
        g_SysWork.playerCombat.weaponAttack            = (g_SavegamePtr->equippedWeapon_AA == InvItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA + InvItemId_KitchenKnife);
        g_SysWork.targetNpcIdx                         = NO_VALUE;
        g_SysWork.playerCombat.isAiming               = false;
    }
}

void Player_CharaTurn_0(s_SubCharacter* player, e_PlayerLowerBodyState curState) // 0x800711C4
{
    if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_Attack ||
        !g_Player_IsSteppingLeftTap || !g_Player_IsSteppingRightTap)
    {
        return;
    }

    if (g_Player_IsTurningLeft)
    {
        g_SysWork.playerWork.extra.lowerBodyState = curState + PlayerLowerBodyState_QuickTurnLeft;
    }
    else
    {
        g_SysWork.playerWork.extra.lowerBodyState = curState + PlayerLowerBodyState_QuickTurnRight;
    }
}

void Player_CharaTurn_1(s_SubCharacter* player, e_PlayerLowerBodyState curState) // 0x80071224
{
    if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_Attack ||
        !g_Player_IsSteppingLeftTap || !g_Player_IsSteppingRightTap)
    {
        return;
    }

    if (g_Player_IsTurningRight)
    {
        g_SysWork.playerWork.extra.lowerBodyState = curState + PlayerLowerBodyState_QuickTurnRight;
    }
    else
    {
        g_SysWork.playerWork.extra.lowerBodyState = curState + PlayerLowerBodyState_QuickTurnLeft;
    }
}

void Player_CharaRotate(s32 speed) // 0x80071284
{
    if (g_GameWork.config.optExtraRetreatTurn_2A)
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
    else if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_WalkBackward ||
             g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_AimWalkBackward)
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

void Player_MovementStateReset(s_SubCharacter* player, e_PlayerLowerBodyState lowerBodyState) // 0x800713B4
{
    if (g_SysWork.playerWork.extra.lowerBodyState != lowerBodyState)
    {
        player->model.stateStep              = 0;
        player->model.controlState           = 0;
        player->properties.player.runTimer_F8 = Q12(0.0f);
        player->properties.player.afkTimer_E8 = Q12(0.0f);
        g_SysWork.playerStopFlags          = PlayerStopFlag_None;
    }
}

bool Player_FootstepSfxPlay(s32 animStatus, s_SubCharacter* player, s32 keyframe0, s32 keyframe1, s32 sfx, s8 pitch)
{
    if (player->model.anim.status != animStatus)
    {
        return false;
    }

    if (player->model.anim.keyframeIdx >= keyframe1)
    {
        if (!(playerProps.flags_11C & PlayerFlag_Unk4))
        {
            if (pitch < 0x20)
            {
                switch (animStatus)
                {
                    case ANIM_STATUS(HarryAnim_SidestepRight, true):
                    case ANIM_STATUS(HarryAnim_SidestepLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnRight, true):
                        func_8005DD44(sfx, &player->position, Q8_CLAMPED(0.095f), pitch);
                        player->properties.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &player->position, Q8(0.25f), pitch);
                        player->properties.player.field_10C = pitch + 0x10;
                        break;
                }
            }
            else
            {
                func_8005DD44(sfx, &player->position, Q8(0.5f), pitch);
                player->properties.player.field_10C = pitch + 0x40;
            }

            playerProps.flags_11C |= PlayerFlag_Unk4;
            return true;
        }
    }
    else
    {
        playerProps.flags_11C &= ~PlayerFlag_Unk4;
    }

    if (player->model.anim.keyframeIdx >= keyframe0)
    {
        if (!(playerProps.flags_11C & PlayerFlag_Unk5))
        {
            if (pitch < 32)
            {
                switch (animStatus)
                {
                    case ANIM_STATUS(HarryAnim_SidestepRight, true):
                    case ANIM_STATUS(HarryAnim_SidestepLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnLeft, true):
                    case ANIM_STATUS(HarryAnim_TurnRight, true):
                        func_8005DD44(sfx, &player->position, Q8_CLAMPED(0.095f), pitch);
                        player->properties.player.field_10C = pitch;
                        break;

                    default:
                        func_8005DD44(sfx, &player->position, Q8(0.25f), pitch);
                        player->properties.player.field_10C = pitch + 16;
                        break;
                }
            }
            else
            {
                func_8005DD44(sfx, &player->position, Q8(0.5f), pitch);
                player->properties.player.field_10C = pitch + 64;
            }

            playerProps.flags_11C |= PlayerFlag_Unk5;
            return true;
        }
    }
    else
    {
        playerProps.flags_11C &= ~PlayerFlag_Unk5;
    }

    return false;
}

bool func_80071620(u32 animStatus, s_SubCharacter* player, s32 keyframeIdx, e_SfxId sfxId) // 0x80071620
{
    if (player->model.anim.status != animStatus)
    {
        return false;
    }

    if (player->model.anim.keyframeIdx >= keyframeIdx)
    {
        if (playerProps.flags_11C & PlayerFlag_SfxActive)
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
                func_8005DC1C(sfxId, &player->position, 0x80, 0);
                player->properties.player.field_10C = 0x40;
                break;

            case Sfx_Unk1283:
                func_8005DC1C(sfxId, &player->position, 0xC8, 2);
                player->properties.player.field_10C = 0;
                break;

            case Sfx_Unk1628:
                func_8005DC1C(sfxId, &player->position, 0x40, 1);
                break;

            case Sfx_Unk1626:
                func_8005DC1C(sfxId, &player->position, 0xFF, 1);
                break;

            case Sfx_Unk1638:
                func_8005DC1C(sfxId, &player->position, 0xFF, 2);
                break;

            default:
            case Sfx_HarryHeavyBreath:
            case Sfx_DoorJammed:
                func_8005DC1C(sfxId, &player->position, 0x40, 2);
                player->properties.player.field_10C = 0;
                break;
        }

        playerProps.flags_11C |= PlayerFlag_SfxActive;
        return true;
    }
    else
    {
        playerProps.flags_11C &= ~PlayerFlag_SfxActive;

        do {} while (false); // @hack Required for match.

        return false;
    }
}

void Player_Update(s_SubCharacter* player, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800717D0
{
    s_PlayerExtra* extra;

    extra = &g_SysWork.playerWork.extra;

    if (g_DeltaTime != Q12(0.0f))
    {
        Player_ReceiveDamage(player, extra);

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
            Player_LogicUpdate(player, extra, coords);
        }
        else
        {
            g_MapOverlayHeader.func_B8(player, extra, coords);
        }

        if (!g_Player_DisableControl)
        {
            func_8007C0D8(player, extra, coords);
        }
        else
        {
            g_MapOverlayHeader.func_BC(player, extra, coords);
        }

        Player_AnimUpdate(player, extra, anmHdr, coords);
        func_8007D090(player, extra, coords);
    }

    D_800C45B0.vx = 0;
    D_800C45B0.vz = 0;
}

static inline void func_80071968_Switch0(void)
{
    if (g_SysWork.playerCombat.weaponAttack != NO_VALUE)
    {
        switch (g_SysWork.playerCombat.weaponAttack)
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
            case WEAPON_ATTACK(EquippedWeaponId_Kick, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Kick, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Kick, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp, AttackInputType_Multitap):
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
    if (g_SysWork.playerCombat.weaponAttack != NO_VALUE)
    {
        switch (g_SysWork.playerCombat.weaponAttack)
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
            case WEAPON_ATTACK(EquippedWeaponId_Kick,  AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp,  AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Kick,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp,  AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Unk3,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Kick,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Stomp,  AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Unk31, AttackInputType_Tap):
                break;
        }
    }
    else
    {
        WorldGfx_HeldItemAttach(Chara_Harry, g_SysWork.enablePlayerMatchAnim ? MODEL_BONE(2, 1) : MODEL_BONE(1, 1));
    }
}

void Player_AnimUpdate(s_SubCharacter* player, s_PlayerExtra* extra, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x80071968
{
    s_AnimInfo* animInfo;

    switch (g_SysWork.playerWork.extra.state)
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
            switch (g_SysWork.playerWork.extra.upperBodyState)
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
        g_SysWork.playerWork.extra.disabledAnimBones = HARRY_UPPER_BODY_BONE_MASK;

        animInfo = &HARRY_BASE_ANIM_INFOS[player->model.anim.status];
        animInfo->playbackFunc(&player->model, anmHdr, coords, animInfo);

        // Re-enable upper body bones, disable lower body bones.
        g_SysWork.playerWork.extra.disabledAnimBones = HARRY_LOWER_BODY_BONE_MASK;

        animInfo = &HARRY_BASE_ANIM_INFOS[extra->model.anim.status];
        animInfo->playbackFunc(&extra->model, anmHdr, coords, animInfo);
        return;
    }

    // Disable upper body bones before playing anim.
    g_SysWork.playerWork.extra.disabledAnimBones = HARRY_UPPER_BODY_BONE_MASK;
    player->model.anim.status                     = ANIM_STATUS(HarryAnim_Still, false);

    animInfo = &HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)];
    animInfo->playbackFunc(&player->model, anmHdr, coords, animInfo);

    // Re-enable upper body bones, disable lower body bones.
    g_SysWork.playerWork.extra.disabledAnimBones = HARRY_LOWER_BODY_BONE_MASK;

    animInfo = &HARRY_BASE_ANIM_INFOS[extra->model.anim.status];
    animInfo->playbackFunc(&extra->model, anmHdr, coords, animInfo);

    if (player->model.anim.status == HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus)
    {
        g_Player_IsInWalkToRunTransition = false;
    }
}

void Player_LogicUpdate(s_SubCharacter* player, s_PlayerExtra* extra, GsCOORDINATE2* coords) // 0x80071CE8
{
    SVECTOR       playerAngles;
    q3_12         headingAngle0;
    q3_12         headingAngle1;
    q3_12         angle;
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
    s32           grabFreeInputCount;
    e_PlayerState romperAttackState;
    e_PlayerState enemyGrabReleaseState;
    q3_12         unkDistThreshold;
    q3_12         npcDist;
    s32           npcIdx;
    s32           animStatus;
    s32           temp;
    s_Model**     models; // Maybe model pointer array?
    s_Model*      model;

    #define playerExtra g_SysWork.playerWork.extra

    animStatus = ANIM_STATUS(HarryAnim_Still, false);

    Game_TimerUpdate();

    D_800C4550                              = 0;
    D_800C454C                              = 0;
    player->properties.player.field_10C >>= 1;

    if (player->flags & CharaFlag_Unk4)
    {
        player->properties.player.timer_110 += g_DeltaTime;
    }

    if (player->properties.player.timer_110 > D_800C45EC)
    {
        player->properties.player.timer_110 = Q12(0.0f);
        player->flags &= ~CharaFlag_Unk4;
    }

    if (playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
    {
        playerProps.gasWeaponPowerTimer_114 -= g_DeltaTime;
    }

    playerProps.gasWeaponPowerTimer_114 = CLAMP(playerProps.gasWeaponPowerTimer_114, Q12(0.0f), Q12(60.0f));

    if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
        g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
    {
        func_8004C564(g_SysWork.playerCombat.weaponAttack, (playerProps.gasWeaponPowerTimer_114 != 0) ? 4 : 2);
    }

    g_SavegamePtr->healthSaturation_238 -= g_DeltaTime;
    g_SavegamePtr->healthSaturation_238 = CLAMP(g_SavegamePtr->healthSaturation_238, Q12(0.0f), Q12(300.0f));

    if (g_SavegamePtr->healthSaturation_238 != Q12(0.0f))
    {
        g_SysWork.playerWork.player.health += g_DeltaTime;
        g_SysWork.playerWork.player.health  = CLAMP(g_SysWork.playerWork.player.health, Q12(0.0f), Q12(100.0f));
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP2_S00)
    {
        g_MapOverlayHeader.func_108();
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        Player_Controller();
    }

    switch (playerExtra.state)
    {
        case PlayerState_Idle:
            playerProps.moveDistance_126 = Q12(0.0f);
            func_8005545C(&playerAngles);
            playerProps.quickTurnHeadingAngle_120 = playerAngles.vy;

            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_LookAround, false);
                extra->model.stateStep++;
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_LookAround, false);
                player->model.stateStep++;
            }

            // If player is not performing a movement.
            if (!(g_Player_HasMoveInput | g_Player_HasActionInput))
            {
                break;
            }

            Player_ExtraStateSet(player, extra, PlayerState_None);

        case PlayerState_None:
        case PlayerState_Combat:
            Player_LowerBodyUpdate(player, extra);

            if (playerExtra.state < (u32)PlayerState_Idle)
            {
                Player_UpperBodyUpdate(player, extra);
            }
            break;

        case PlayerState_Unk7:
            func_8007FB94(player, extra, ANIM_STATUS(100, false));

            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));

                if (playerProps.moveDistance_126 < Q12(0.0f))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (!(player->attackReceived >= 68 && player->attackReceived < 70))
            {
                g_Player_HeadingAngle                                                  = ratan2(player->damage.position.vx, player->damage.position.vz) - player->rotation.vy;
                playerProps.moveDistance_126 = SQUARE(player->damage.position.vx) + SQUARE(player->damage.position.vz) + SQUARE(player->damage.position.vy);
            }

            if (extra->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                player->attackReceived = NO_VALUE;

                g_SysWork.targetNpcIdx                                      = NO_VALUE;
                playerProps.flags_11C &= ~PlayerFlag_DamageReceived;

                Player_ExtraStateSet(player, extra, PlayerState_None);

                playerProps.moveDistance_126 = Q12(0.0f);
            }

            D_800C4550               = playerProps.moveDistance_126;
            player->flags         |= CharaFlag_Unk4;
            player->attackReceived = NO_VALUE;
            break;

        case PlayerState_DamageThrownFront:
        case PlayerState_DamageThrownBack:
            thrownState = PlayerState_None;

            switch (playerExtra.state)
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

            func_8007FB94(player, extra, animStatus);

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(player, extra, thrownState);
                player->properties.player.afkTimer_E8 = Q12(10.0f);
            }

            if (playerProps.moveDistance_126 != 0)
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f)) >> 3;

                if ((playerProps.moveDistance_126) < 0)
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800C4550 = playerProps.moveDistance_126;
            break;

        case PlayerState_EnemyGrabPinnedFrontStart:
        case PlayerState_EnemyGrabPinnedBackStart:
            romperAttackState = PlayerState_None;
            npcIdx            = 0;

            switch (playerExtra.state)
            {
                case PlayerState_EnemyGrabPinnedFrontStart:
                    animStatus        = ANIM_STATUS(HarryAnim_Unk127, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedFront;
                    npcIdx            = g_SysWork.npcIdxs[0];
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[npcIdx].rotation.vy + Q12_ANGLE(180.0f)), &headingAngle0);
                    break;

                case PlayerState_EnemyGrabPinnedBackStart:
                    animStatus        = ANIM_STATUS(HarryAnim_Unk128, true);
                    romperAttackState = PlayerState_EnemyGrabPinnedBack;
                    npcIdx            = g_SysWork.npcIdxs[1];
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[npcIdx].rotation.vy + Q12_ANGLE(360.0f)), &headingAngle0);
                    break;
            }

            playerProps.moveDistance_126 = Q12(0.0f);
            func_8007FB94(player, extra, animStatus);
            player->field_D4.radius_0 = Q12(0.25f);
            player->field_D4.field_2 = Q12(0.0f);

            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
            {
                temp_s0 = -D_800AF1FC[player->model.anim.keyframeIdx - g_MapOverlayHeader.field_38[D_800AF220].time];
                g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12_MULT(temp_s0, Math_Sin(player->rotation.vy));
                g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12_MULT(temp_s0, Math_Cos(player->rotation.vy));
            }

            if (ABS(headingAngle0) < Q12_ANGLE(11.25f))
            {
                if (playerExtra.state == PlayerState_EnemyGrabPinnedFrontStart)
                {
                    player->rotation.vy = g_SysWork.npcs[npcIdx].rotation.vy + Q12_ANGLE(180.0f);
                }
                else
                {
                    player->rotation.vy = g_SysWork.npcs[npcIdx].rotation.vy;
                }
            }
            else
            {
                if (headingAngle0 > Q12_ANGLE(0.0f))
                {
                    player->rotation.vy += Q12_ANGLE(11.25f);
                }
                else
                {
                    player->rotation.vy -= Q12_ANGLE(11.25f);
                }
            }

            Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[npcIdx].rotation.vy + Q12_ANGLE(360.0f)), &headingAngle0);

            model = &g_SysWork.npcs[npcIdx].model;

            do {} while(false); // @hack Required for match.

            g_Player_HeadingAngle =
            temp                  = headingAngle0;

            if ((*models) != NULL) // @hack Required for match.
            {
                g_Player_HeadingAngle += Q12_ANGLE(0.0f);
            }

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(player, extra, romperAttackState);
                player->properties.player.afkTimer_E8 = Q12(15.0f);
            }

            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
            {
                if (playerExtra.state >= PlayerState_EnemyGrabPinnedFrontStart &&
                    playerExtra.state <  PlayerState_EnemyGrabPinnedFront)
                {
                    temp = Q12(-8.0f);
                    extra->model.anim.time = (Q12(g_MapOverlayHeader.harryMapAnimInfos_34[player->model.anim.status - 76].startKeyframeIdx) + model->anim.time) + temp;
                    player->model.anim.time = (Q12(g_MapOverlayHeader.harryMapAnimInfos_34[player->model.anim.status - 76].startKeyframeIdx) + model->anim.time) + temp;
                    player->model.anim.keyframeIdx = FP_FROM(player->model.anim.time, Q12_SHIFT);
                    extra->model.anim.keyframeIdx = FP_FROM(extra->model.anim.time, Q12_SHIFT);
                }
            }

            if (ABS(player->position.vx - D_800C4610.vx) <= Q12(0.05f))
            {
                player->position.vx = D_800C4610.vx;
            }
            else
            {
                if (player->position.vx >= D_800C4610.vx)
                {
                    player->position.vx -= Q12(0.05f) + 1;
                }
                else
                {
                    player->position.vx += Q12(0.05f) + 1;
                }
            }

            if (ABS(player->position.vz - D_800C4610.vz) <= Q12(0.05f))
            {
                player->position.vz = D_800C4610.vz;
            }
            else
            {
                if (player->position.vz < D_800C4610.vz)
                {
                    player->position.vz += Q12(0.05f) + 1;
                }
                else
                {
                    player->position.vz -= Q12(0.05f) + 1;
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
            grabFreeInputCount                              = 0;
            enemyGrabReleaseState                                          = PlayerState_None;
            unkDistThreshold                                               = Q12(0.0f);
            playerProps.moveDistance_126 = Q12(0.0f);
            npcDist                                                        = Q12(0.0f);

            // Accommodates player position (for pinned enemy gram and Romper attack) and establishes required input count to get free.
            switch (playerExtra.state)
            {
                case PlayerState_OnFloorFront:
                case PlayerState_OnFloorBehind:
                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 1600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 4800;
                    }
                    else
                    {
                        grabFreeInputCount = 3200;
                    }

                    switch (playerExtra.state)
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

                    player->field_D4.field_2 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.27f));
                    player->field_C8.field_0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(1.2f));
                    player->field_C8.field_6 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.9f));

                    player->field_D4.field_2 = CLAMP(player->field_D4.field_2, Q12(0.23f), Q12(0.5f));
                    player->field_C8.field_0 = CLAMP(player->field_C8.field_0, Q12(-1.6f), Q12(-0.4));
                    player->field_C8.field_6 = CLAMP(player->field_C8.field_6, Q12(-1.1f), Q12(-0.2f));

                    if (player->health <= Q12(0.0f) && player->properties.player.afkTimer_E8 <= Q12(0.0f))
                    {
                        g_MapOverlayHeader.playerAnimLock_DC();
                        SysWork_StateSetNext(SysState_GameOver);

                        player->health                                                         = Q12(100.0f);
                        playerProps.gasWeaponPowerTimer_114 = Q12(0.0f);
                        return;
                    }
                    break;

                case PlayerState_EnemyGrabPinnedFront:
                case PlayerState_EnemyGrabPinnedBack:
                    unkDistThreshold = Q12(0.65f);

                    switch (playerExtra.state)
                    {
                        case PlayerState_EnemyGrabPinnedFront:
                            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                            {
                                grabFreeInputCount = 800;
                            }
                            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                            {
                                grabFreeInputCount = 2400;
                            }
                            else
                            {
                                grabFreeInputCount = 1600;
                            }

                            animStatus          = ANIM_STATUS(HarryAnim_Unk128, false);
                            enemyGrabReleaseState = PlayerState_EnemyReleasePinnedFront;
                            break;

                        case PlayerState_EnemyGrabPinnedBack:
                            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                            {
                                grabFreeInputCount = 1200;
                            }
                            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                            {
                                grabFreeInputCount = 3600;
                            }
                            else
                            {
                                grabFreeInputCount = 2400;
                            }

                            animStatus          = ANIM_STATUS(HarryAnim_Unk129, false);
                            enemyGrabReleaseState = PlayerState_EnemyReleasePinnedBack;
                            break;
                    }

                    player->field_D4.radius_0                        = 0;
                    g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);

                    if (ABS(player->position.vx - D_800C4610.vx) <= Q12(0.05f))
                    {
                        player->position.vx = D_800C4610.vx;
                    }
                    else
                    {
                        if (player->position.vx >= D_800C4610.vx)
                        {
                            player->position.vx -= (Q12(0.05f) + 1);
                        }
                        else
                        {
                            player->position.vx += (Q12(0.05f) + 1);
                        }
                    }

                    if (ABS(player->position.vz - D_800C4610.vz) <= Q12(0.05f))
                    {
                        player->position.vz = D_800C4610.vz;
                    }
                    else
                    {
                        if (player->position.vz >= D_800C4610.vz)
                        {
                            player->position.vz -= (Q12(0.05f) + 1);
                        }
                        else
                        {
                            player->position.vz += (Q12(0.05f) + 1);
                        }
                    }

                    if (player->health <= Q12(0.0f) && player->properties.player.afkTimer_E8 <= Q12(0.0f))
                    {
                        g_MapOverlayHeader.playerAnimLock_DC();

                        SysWork_StateSetNext(SysState_GameOver);

                        player->health                                                         = Q12(100.0f);
                        playerProps.gasWeaponPowerTimer_114 = Q12(0.0f);
                        return;
                    }
                    break;

                case PlayerState_EnemyGrabTorsoFront:
                    unkDistThreshold = Q12(1.0f);

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 800;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 2400;
                    }
                    else
                    {
                        grabFreeInputCount = 1600;
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
                        grabFreeInputCount = 1000;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 3000;
                    }
                    else
                    {
                        grabFreeInputCount = 2000;
                    }

                    animStatus            = ANIM_STATUS(HarryAnim_Unk117, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;

                case PlayerState_EnemyGrabLegsFront:
                    unkDistThreshold = Q12(0.8f);

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 700;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 2100;
                    }
                    else
                    {
                        grabFreeInputCount = 1400;
                    }

                    animStatus            = ANIM_STATUS(HarryAnim_Unk117, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerFront;
                    break;

                case PlayerState_EnemyGrabLegsBack:
                    unkDistThreshold = Q12(0.8f);

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 800;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 2400;
                    }
                    else
                    {
                        grabFreeInputCount = 1600;
                    }

                    animStatus            = ANIM_STATUS(HarryAnim_Unk118, false);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseLowerBack;
                    break;

                case PlayerState_EnemyGrabNeckFront:
                    unkDistThreshold = Q12(1.5f);

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 3600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 10800;
                    }
                    else
                    {
                        grabFreeInputCount = 7200;
                    }

                    animStatus            = ANIM_STATUS(HarryAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperFront;
                    break;

                case PlayerState_EnemyGrabNeckBack:
                    unkDistThreshold = Q12(1.5f);

                    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
                    {
                        grabFreeInputCount = 3600;
                    }
                    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                    {
                        grabFreeInputCount = 10800;
                    }
                    else
                    {
                        grabFreeInputCount = 7200;
                    }

                    animStatus            = ANIM_STATUS(HarryAnim_Unk125, true);
                    enemyGrabReleaseState = PlayerState_EnemyReleaseUpperBack;
                    break;
            }

            // Accommodates position of player and enemy?
            switch (playerExtra.state)
            {
                case PlayerState_EnemyGrabTorsoFront:
                case PlayerState_EnemyGrabLegsFront:
                case PlayerState_EnemyGrabNeckFront:
                case PlayerState_EnemyGrabPinnedFront:
                    deltaPosX = player->position.vx - g_SysWork.npcs[g_SysWork.npcIdxs[0]].position.vx;
                    deltaPosZ = player->position.vz - g_SysWork.npcs[g_SysWork.npcIdxs[0]].position.vz;
                    npcDist   = SquareRoot0(SQUARE(deltaPosX) + SQUARE(deltaPosZ));
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[g_SysWork.npcIdxs[0]].rotation.vy + Q12_ANGLE(180.0f)), &headingAngle1);

                    if (ABS(headingAngle1) < Q12_ANGLE(11.25f))
                    {
                        player->rotation.vy = g_SysWork.npcs[g_SysWork.npcIdxs[0]].rotation.vy + Q12_ANGLE(180.0f);
                    }
                    else
                    {
                        if (headingAngle1 > Q12_ANGLE(0.0f))
                        {
                            player->rotation.vy += Q12_ANGLE(11.25f);
                        }
                        else
                        {
                            player->rotation.vy -= Q12_ANGLE(11.25f);
                        }
                    }
                    break;

                case PlayerState_EnemyGrabTorsoBack:
                case PlayerState_EnemyGrabLegsBack:
                case PlayerState_EnemyGrabNeckBack:
                case PlayerState_EnemyGrabPinnedBack:
                    temp_v1_12 = player->position.vx - g_SysWork.npcs[g_SysWork.npcIdxs[1]].position.vx;
                    temp_v1_13 = player->position.vz - g_SysWork.npcs[g_SysWork.npcIdxs[1]].position.vz;
                    npcDist     = SquareRoot0(SQUARE(temp_v1_12) + SQUARE(temp_v1_13));
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[g_SysWork.npcIdxs[1]].rotation.vy + Q12_ANGLE(360.0f)), &headingAngle1);

                    if (ABS(headingAngle1) < Q12_ANGLE(11.25f))
                    {
                        player->rotation.vy = g_SysWork.npcs[g_SysWork.npcIdxs[1]].rotation.vy;
                    }
                    else
                    {
                        if (headingAngle1 > Q12_ANGLE(0.0f))
                        {
                            player->rotation.vy += Q12_ANGLE(11.25f);
                        }
                        else
                        {
                            player->rotation.vy -= Q12_ANGLE(11.25f);
                        }
                    }
                    break;
            }

            switch (playerExtra.state)
            {
                case PlayerState_EnemyGrabPinnedFront:
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[g_SysWork.npcIdxs[0]].rotation.vy + Q12_ANGLE(360.0f)), &headingAngle1);

                case PlayerState_EnemyGrabPinnedBack:
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE_NORM_U(g_SysWork.npcs[g_SysWork.npcIdxs[1]].rotation.vy + Q12_ANGLE(360.0f)), &headingAngle1);
                    break;
            }

            g_Player_HeadingAngle = headingAngle1;
            func_8007FB94(player, extra, animStatus);

            if (player->health > Q12(0.0f) && (g_Player_HasMoveInput | g_Player_HasActionInput))
            {
                g_Player_GrabReleaseInputTimer += g_DeltaTime;
            }

            // If player isn't thrown to floor (Cybil shoot attack).
            if (!(playerExtra.state >= PlayerState_OnFloorFront &&
                  playerExtra.state <  PlayerState_GetUpFront))
            {
                if (unkDistThreshold < npcDist)
                {
                    g_Player_GrabReleaseInputTimer = grabFreeInputCount;
                    if (playerExtra.state == PlayerState_EnemyGrabPinnedFront)
                    {
                        g_SysWork.npcs[g_SysWork.npcIdxs[0]].moveSpeed = Q12(0.0f);
                    }

                    if (playerExtra.state == PlayerState_EnemyGrabPinnedBack)
                    {
                        g_SysWork.npcs[g_SysWork.npcIdxs[1]].moveSpeed = Q12(0.0f);
                    }
                }
            }

            if (g_Player_GrabReleaseInputTimer >= grabFreeInputCount)
            {
                func_8007FD4C(false);

                Player_ExtraStateSet(player, extra, enemyGrabReleaseState);

                player->flags |= CharaFlag_Unk4;
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
            if (playerExtra.state != PlayerState_FallBackward)
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) >> 1; // `/ 2`.
                    if ((playerProps.moveDistance_126 >> 16) & 1)
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) >> 2; // `/ 4`.

                if ((playerProps.moveDistance_126 >> 16) & 1)
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            switch (playerExtra.state)
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

            if (!(playerExtra.state >= PlayerState_FallForward && playerExtra.state < PlayerState_KickEnemy))
            {
                func_8007FB94(player, extra, animStatus);
            }

            D_800C4550 = playerProps.moveDistance_126;
            player->flags |= CharaFlag_Unk4;

            switch (playerExtra.state)
            {
                case PlayerState_GetUpFront:
                case PlayerState_GetUpBack:
                    player->damage.amount                  = Q12(0.0f);
                    player->properties.player.afkTimer_E8 = Q12(0.0f);

                    if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        playerProps.flags_11C &= ~PlayerFlag_DamageReceived;

                        Player_ExtraStateSet(player, extra, PlayerState_None);

                        g_SysWork.playerWork.player.field_D4.radius_0  = Q12(0.3f);
                        g_SysWork.playerWork.player.field_D4.field_2   = Q12(0.23f);
                        g_SysWork.playerWork.player.field_C8.field_0   = Q12(-1.6f);
                        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_C8.field_2   = Q12(0.0f);
                        g_SysWork.playerWork.player.field_C8.field_6   = Q12(-1.1f);
                    }

                    player->attackReceived = NO_VALUE;

                default:
                    break;

                case PlayerState_EnemyReleasePinnedFront:
                case PlayerState_EnemyReleasePinnedBack:
                    player->properties.player.afkTimer_E8        = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                    g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);

                    if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
                    {
                        player->field_D4.radius_0 = ((player->model.anim.keyframeIdx - g_MapOverlayHeader.field_38[D_800AF220].time) * Q12(0.3f)) / 21;
                    }
                    else
                    {
                        player->field_D4.radius_0 = Q12(0.0f);
                    }

                    if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        playerProps.flags_11C &= ~PlayerFlag_DamageReceived;
                        switch (playerExtra.state)
                        {
                            case PlayerState_EnemyReleasePinnedFront:
                                Player_ExtraStateSet(player, extra, PlayerState_Unk43);
                                break;

                            case PlayerState_EnemyReleasePinnedBack:
                                Player_ExtraStateSet(player, extra, PlayerState_Unk44);
                                break;
                        }

                        g_SysWork.playerWork.player.field_D4.radius_0  = Q12(0.3f);
                        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);

                        player->attackReceived = NO_VALUE;
                    }
                    break;

                case PlayerState_EnemyReleaseUpperFront:
                case PlayerState_Unk17:
                case PlayerState_Unk18:
                case PlayerState_DamageHead:
                case PlayerState_EnemyReleaseUpperBack:
                case PlayerState_EnemyReleaseLowerFront:
                case PlayerState_EnemyReleaseLowerBack:
                    if (player->model.anim.keyframeIdx == (g_MapOverlayHeader.field_38[D_800AF220].time + 4))
                    {
                        player->attackReceived = NO_VALUE;
                    }

                    if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                    {
                        playerProps.flags_11C &= ~PlayerFlag_DamageReceived;

                        Player_ExtraStateSet(player, extra, PlayerState_None);

                        player->field_D4.radius_0 = Q12(0.3f);

                        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                        g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
                    }
                    break;

                case PlayerState_FallForward:
                case PlayerState_FallBackward:
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = animStatus;
                        extra->model.stateStep++;
                    }

                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = animStatus;
                        player->model.stateStep++;
                    }

                    if (extra->model.controlState == 0 && player->position.vy >= player->properties.player.positionY_EC)
                    {
                        extra->model.controlState++;
                        func_8005DC1C(Sfx_Unk1317, &player->position, Q8(1.0f / 8.0f), 0);
                        player->properties.player.field_10C = 128;
                        func_80089470();
                    }

                    if (playerExtra.state == PlayerState_FallForward)
                    {
                        player->properties.player.field_10D = 0;
                        if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
                        {
                            g_SysWork.playerWork.player.field_C8.field_0 = D_800AEEDC[player->model.anim.keyframeIdx - 379][0];
                            g_SysWork.playerWork.player.field_C8.field_6 = D_800AEEDC[player->model.anim.keyframeIdx - 379][1];
                        }

                        if (player->model.anim.keyframeIdx == HARRY_BASE_ANIM_INFOS[45].endKeyframeIdx)
                        {
                            if (player->position.vy > Q12(6.5f))
                            {
                                Player_ExtraStateSet(player, extra, PlayerState_Death);
                            }
                            else
                            {
                                Player_ExtraStateSet(player, extra, PlayerState_None);
                            }

                            g_SysWork.playerWork.player.field_C8.field_0 = Q12(-1.6f);
                            g_SysWork.playerWork.player.field_C8.field_2 = Q12(0.0f);
                            g_SysWork.playerWork.player.field_C8.field_6 = Q12(-1.1f);

                            player->field_D4.radius_0 = Q12(0.3f);
                        }
                    }
                    else
                    {
                        player->properties.player.field_10D = 1;

                        if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
                        {
                            g_SysWork.playerWork.player.field_C8.field_0 = D_800AEF78[player->model.anim.keyframeIdx - 418][0];
                            g_SysWork.playerWork.player.field_C8.field_6 = D_800AEF78[player->model.anim.keyframeIdx - 418][1];
                        }

                        if (player->model.anim.keyframeIdx == HARRY_BASE_ANIM_INFOS[47].endKeyframeIdx)
                        {
                            if (player->position.vy > Q12(6.5f))
                            {
                                Player_ExtraStateSet(player, extra, PlayerState_Death);
                            }
                            else
                            {
                                Player_ExtraStateSet(player, extra, PlayerState_None);
                            }

                            g_SysWork.playerWork.player.field_C8.field_0 = Q12(-1.6f);
                            g_SysWork.playerWork.player.field_C8.field_2 = Q12(0.0f);
                            g_SysWork.playerWork.player.field_C8.field_6 = Q12(-1.1f);

                            player->field_D4.radius_0 = Q12(0.3f);
                        }
                    }
                    break;
            }

            player->attackReceived = NO_VALUE;
            break;

        case PlayerState_Unk43:
            func_8007FB94(player, extra, ANIM_STATUS(130, true));

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(player, extra, PlayerState_None);

                player->field_D4.field_2 = Q12(0.23f);
            }
            break;

        case PlayerState_Unk44:
            func_8007FB94(player, extra, ANIM_STATUS(131, false));

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                Player_ExtraStateSet(player, extra, PlayerState_None);

                player->field_D4.field_2 = Q12(0.23f);
            }
            break;

        case PlayerState_Unk36:
            player->attackReceived = NO_VALUE;
            func_8007FB94(player, extra, ANIM_STATUS(126, false));

            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time + 12) >= player->model.anim.keyframeIdx)
                {
                    func_80071620(player->model.anim.status, player, g_MapOverlayHeader.field_38[D_800AF220].time + 12, Sfx_Unk1318);
                }
                else
                {
                    func_80071620(player->model.anim.status, player, g_MapOverlayHeader.field_38[D_800AF220].time + 30, Sfx_Unk1319);
                }
            }

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model.controlState++;
                player->health = Q12(100.0f);
                player->model.controlState++;
                playerProps.gasWeaponPowerTimer_114 = Q12(0.0f);
                return;
            }
            break;

        case PlayerState_Death:
            player->attackReceived = NO_VALUE;
            func_8007FB94(player, extra, ANIM_STATUS(101, false));
            player->field_D4.field_2 = Q12(0.0f);

            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status))
            {
                if ((g_MapOverlayHeader.field_38[D_800AF220].time + 12) >= player->model.anim.keyframeIdx)
                {
                    func_80071620(player->model.anim.status, player, g_MapOverlayHeader.field_38[D_800AF220].time + 12, Sfx_Unk1318);
                }
                else
                {
                    func_80071620(player->model.anim.status, player, g_MapOverlayHeader.field_38[D_800AF220].time + 32, Sfx_Unk1319);
                }

                temp_a2 = D_800AF070[player->model.anim.keyframeIdx - g_MapOverlayHeader.field_38[D_800AF220].time];

                if (player->model.anim.keyframeIdx != g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
                {
                    var_v1_5 = D_800AF070[(player->model.anim.keyframeIdx + 1) - g_MapOverlayHeader.field_38[D_800AF220].time];
                }
                else
                {
                    var_v1_5 = temp_a2;
                }

                temp_s0_3                                    = temp_a2 + Q12_MULT(var_v1_5 - temp_a2, Q12_FRACT(player->model.anim.time));
                g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12_MULT(temp_s0_3, Math_Sin(player->rotation.vy));
                g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12_MULT(temp_s0_3, Math_Cos(player->rotation.vy));
                player->field_D4.radius_0                        = Q12(0.3f);
            }

            if (player->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP0_S00)
                {
                    g_MapOverlayHeader.playerAnimLock_DC();
                    Savegame_EventFlagSet(EventFlag_25);

                    func_8007E9C4();

                    extra->model.controlState++;
                    player->health = Q12(100.0f);
                    player->model.controlState++;
                    playerProps.gasWeaponPowerTimer_114 = Q12(0.0f);
                    return;
                }

                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model.controlState++;
                player->health = Q12(100.0f);
                player->model.controlState++;
                playerProps.gasWeaponPowerTimer_114 = Q12(0.0f);
                return;
            }
            break;

        case PlayerState_InstantDeath:
            if (extra->model.controlState == 0)
            {
                SD_Call(4731);
            }

            func_8007FB94(player, extra, ANIM_STATUS(101, true));
            player->field_D4.field_2 = Q12(0.0f);

            if (player->model.anim.keyframeIdx == (g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6 - 25))
            {
                g_MapOverlayHeader.playerAnimLock_DC();

                SysWork_StateSetNext(SysState_GameOver);

                func_8007E9C4();

                extra->model.controlState++;
                player->health = Q12(100.0f);
                player->model.controlState++;
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
            switch (g_SysWork.playerWork.extra.state)
            {
                case PlayerState_DamageTorsoBack:
                    func_8007FB94(player, extra, ANIM_STATUS(105, true));
                    break;

                case PlayerState_DamageTorsoFront:
                    func_8007FB94(player, extra, ANIM_STATUS(105, false));
                    break;

                case PlayerState_DamageTorsoRight:
                    func_8007FB94(player, extra, ANIM_STATUS(106, false));
                    break;

                case PlayerState_DamageTorsoLeft:
                    func_8007FB94(player, extra, ANIM_STATUS(106, true));
                    break;

                case PlayerState_DamageFeetFront:
                    func_8007FB94(player, extra, ANIM_STATUS(107, true));
                    break;

                case PlayerState_DamageFeetBack:
                    func_8007FB94(player, extra, ANIM_STATUS(107, false));
                    break;

                case PlayerState_DamagePushBack:
                    func_8007FB94(player, extra, ANIM_STATUS(123, true));
                    break;

                case PlayerState_DamagePushFront:
                    func_8007FB94(player, extra, ANIM_STATUS(124, false));
                    break;
            }

            switch (playerExtra.state)
            {
                case PlayerState_DamagePushBack:
                    Math_ShortestAngleGet(player->rotation.vy, playerProps.field_118, &angle);

                    if (ABS(angle) >= Q12_ANGLE(90.0f))
                    {
                        break;
                    }

                    if (ABS(angle) < Q12_ANGLE(5.7f))
                    {
                        player->rotation.vy = playerProps.field_118;
                    }
                    else
                    {
                        player->rotation.vy += (angle / ABS(angle)) << 6;
                    }
                    break;

                case PlayerState_DamagePushFront:
                    Math_ShortestAngleGet(player->rotation.vy, playerProps.field_118, &sp1E);

                    if (ABS(sp1E) < Q12_ANGLE(90.0f))
                    {
                        break;
                    }

                    if (ABS(sp1E) >= Q12_ANGLE(174.4f))
                    {
                        player->rotation.vy = Q12_ANGLE_NORM_U(playerProps.field_118 + Q12_ANGLE(180.0f));
                    }
                    else
                    {
                        player->rotation.vy -= (sp1E / ABS(sp1E)) << 6;
                    }
                    break;
            }

            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f)) >> 2;

                if ((playerProps.moveDistance_126 >> 16) & 0x1)
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (!(player->attackReceived >= 68 && player->attackReceived < 70)) // TODO: Demagic.
            {
                g_Player_HeadingAngle                                                   = ratan2(player->damage.position.vx, player->damage.position.vz) - player->rotation.vy;
                playerProps.moveDistance_126 = SQUARE(player->damage.position.vx) + SQUARE(player->damage.position.vz) + SQUARE(player->damage.position.vy);
            }

            if (extra->model.anim.keyframeIdx == g_MapOverlayHeader.field_38[D_800AF220].keyframeIdx_6)
            {
                player->attackReceived                                    = NO_VALUE;
                g_SysWork.targetNpcIdx                                   = NO_VALUE;
                playerProps.flags_11C &= ~PlayerFlag_DamageReceived;

                Player_ExtraStateSet(player, extra, PlayerState_None);

                playerProps.moveDistance_126 = Q12(0.0f);
            }

            D_800C4550       = playerProps.moveDistance_126;
            player->flags |= CharaFlag_Unk4;
            break;

        case PlayerState_KickEnemy:
            func_80070DF0(extra, player, WEAPON_ATTACK(EquippedWeaponId_Kick, AttackInputType_Tap), ANIM_STATUS(24, true));
            break;

        case PlayerState_StompEnemy:
            func_80070DF0(extra, player, WEAPON_ATTACK(EquippedWeaponId_Stomp, AttackInputType_Tap), ANIM_STATUS(25, true));
            break;
    }

    player->rotation.vy      = Q12_ANGLE_NORM_U(player->rotation.vy + (D_800C454C >> 4) + Q12_ANGLE(360.0f));
    player->headingAngle     = Q12_ANGLE_NORM_U((player->rotation.vy + g_Player_HeadingAngle) + Q12_ANGLE(360.0f));
    player->moveSpeed        = D_800C4550;
    player->fallSpeed       += g_GravitySpeed;
    player->rotationSpeed.vy = (D_800C454C << 8) / g_DeltaTime;
    coords->flg             = false;

    Math_RotMatrixZxyNegGte(&player->rotation, &coords->coord);

    #undef playerExtra
}

void Player_UpperBodyStateUpdate(s_PlayerExtra* extra, e_PlayerUpperBodyState upperState, s32 unused, s32 arg3) // 0x80073FC0
{
    e_PlayerUpperBodyState prevState;
    s_Model*               charaModel;

    prevState  = g_SysWork.playerWork.extra.upperBodyState;
    charaModel = &g_SysWork.playerWork.player.model;

    switch (g_SysWork.playerWork.extra.lowerBodyState)
    {
        case PlayerLowerBodyState_WalkForward:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_WalkForward;

        default:
            break;

        case PlayerLowerBodyState_RunForward:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunForward;
            break;

        case PlayerLowerBodyState_WalkBackward:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_WalkBackward;
            break;

        case PlayerLowerBodyState_SidestepRight:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_SidestepRight;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_SidestepLeft;
            break;

        case PlayerLowerBodyState_RunRight:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunRight;
            break;

        case PlayerLowerBodyState_RunLeft:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunLeft;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_QuickTurnRight;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_QuickTurnLeft;
            break;

        case PlayerLowerBodyState_JumpBackward:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunJumpBackward;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunWallStop;
            break;

        case PlayerLowerBodyState_Stumble:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_LowerBodyStumble;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunLeftWallStop;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunRightWallStop;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunLeftStumble;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_SidestepRightStumble;
            break;

        case PlayerLowerBodyState_None:
            switch (arg3)
            {
                case 0:
                case 2:
                    g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_None;
                    break;

                case 1:
                    if (!g_Player_IsTurningRight)
                    {
                        if (g_Player_IsTurningLeft)
                        {
                            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_TurnLeft;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_TurnRight;
                    }
                    break;

                case 3:
                    if (g_Player_IsTurningLeft)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_TurnLeft;
                        break;
                    }

                    if (!g_Player_IsTurningRight)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_None;
                    }
                    break;

                case 4:
                    if (g_Player_IsTurningRight)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_TurnRight;
                        break;
                    }

                    if (!g_Player_IsTurningLeft)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_None;
                    }
                    break;
            }
            break;
    }

    if (g_SysWork.playerWork.extra.upperBodyState != upperState)
    {
        extra->model.stateStep = 0;
        extra->model.controlState     = 0;
    }

    switch (prevState)
    {
        case PlayerUpperBodyState_WalkForward:
            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_RunForward)
            {
                break;
            }

            extra->model.anim.status      = charaModel->anim.status;
            extra->model.anim.keyframeIdx = charaModel->anim.keyframeIdx;
            extra->model.anim.time         = charaModel->anim.time;
            extra->model.stateStep++;
            break;

        case PlayerUpperBodyState_RunForward:
            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_WalkForward)
            {
                break;
            }

            extra->model.anim.status      = charaModel->anim.status;
            extra->model.anim.keyframeIdx = charaModel->anim.keyframeIdx;
            extra->model.anim.time         = charaModel->anim.time;
            extra->model.stateStep++;
            break;
    }
}

void Player_UpperBodyUpdate(s_SubCharacter* player, s_PlayerExtra* extra) // 0x80074254
{
    s32 stumbleSfxId;

    if (Player_UpperBodyMainUpdate(player, extra))
    {
        return;
    }

    stumbleSfxId = (D_800C45C8.field_1 == 10) ? Sfx_Stumble1 : Sfx_Stumble0;

    switch (g_SysWork.playerWork.extra.upperBodyState)
    {
        case PlayerUpperBodyState_None:
            func_80071620(55, player, 551, Sfx_HarryHeavyBreath);
            break;

        case PlayerUpperBodyState_LowerBodyStumble:
            if (func_80071620(23, player, 173, stumbleSfxId))
            {
                func_8008944C();
            }
            break;

        case PlayerUpperBodyState_RunLeftStumble:
            if (func_80071620(39, player, 340, stumbleSfxId))
            {
                func_8008944C();
            }
            break;

        case PlayerUpperBodyState_SidestepRightStumble:
            if (func_80071620(43, player, 369, stumbleSfxId))
            {
                func_8008944C();
            }
            break;
    }

    Player_CombatStateUpdate(player, extra);
}

bool Player_UpperBodyMainUpdate(s_SubCharacter* player, s_PlayerExtra* extra) // 0x80075504
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

        weaponAttack = g_SysWork.playerCombat.weaponAttack;

        switch (g_SysWork.playerCombat.weaponAttack)
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

        if (g_SysWork.playerWork.extra.state == PlayerState_Combat)
        {
            playerProps.field_104 += g_DeltaTime;

            if (!g_GameWork.config.optExtraWeaponCtrl_23)
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
        if (extra->model.controlState == 0)
        {
            g_Player_MeleeAttackType  = 0;
            g_Player_IsMultiTapAttack = 0;

            playerProps.flags_11C &= ~PlayerFlag_Shooting;
            playerProps.flags_11C &= ~PlayerFlag_Unk6;

            if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_Player_MeleeAttackType    = 0;
                g_Player_AttackAnimIdx = g_Player_EquippedWeaponInfo.animAttackHold_8;
                D_800AF220                  = g_Player_EquippedWeaponInfo.field_A >> 4;
            }
            else if (g_Player_IsAttacking && g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                g_Player_MeleeAttackType = 1;
                g_Player_AttackAnimIdx   = g_Player_EquippedWeaponInfo.animAttackHold_8 - 4;
                D_800AF220               = (g_Player_EquippedWeaponInfo.field_A >> 4) - 2;
            }
            else
            {
                g_Player_MeleeAttackType = 0;

                // Handle Rock Drill animation.
                if (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) ||
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

            extra->model.controlState++;

            if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_SysWork.playerCombat.weaponAttack = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack), AttackInputType_Tap);
            }

            g_SysWork.playerCombat.weaponAttack += g_Player_MeleeAttackType * 10; // TODO: Macro for this?

            D_800C44D0 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx + D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_E;
            D_800C44D4 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx + D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_E +
                         D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_F;
        }

        // Used for make continuos/hold shooting smoother?
        if (g_SysWork.targetNpcIdx != NO_VALUE &&
            g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (!g_GameWork.config.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(10.0f), 0);
                    func_8005D50C(&g_Player_TargetNpcIdx, &D_800C4554, &D_800C4556, &g_SysWork.playerCombat, enemyAttackedIdx, Q12_ANGLE(20.0f));
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(3.0f), 0);
                    func_8005D50C(&g_Player_TargetNpcIdx, &D_800C4554, &D_800C4556, &g_SysWork.playerCombat, enemyAttackedIdx, Q12_ANGLE(20.0f));
                }
            }
            else
            {
                enemyAttackedIdx = g_SysWork.targetNpcIdx;
            }

            if (enemyAttackedIdx == NO_VALUE && enemyAttackedIdx == g_Player_TargetNpcIdx)
            {
                D_800C4556 = NO_VALUE;
                D_800C4554 = NO_VALUE;
            }

            if (enemyAttackedIdx == g_SysWork.targetNpcIdx)
            {
                player->field_2A = Q12_FRACT(ratan2((g_SysWork.npcs[enemyAttackedIdx].position.vx + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork.player.position.vx,
                                                   (g_SysWork.npcs[enemyAttackedIdx].position.vz + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork.player.position.vz) +
                                            Q12_ANGLE(360.0f));
            }
            else
            {
                player->field_2A = player->rotation.vy;
            }

            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk30, false);
                extra->model.stateStep++;
            }
        }
        else
        {
            if (g_SysWork.targetNpcIdx != NO_VALUE && !g_GameWork.config.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(3.0f), Q12(3.0f), 5);
                }
                else
                {
                    func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(1.0f), Q12(1.0f), 5);
                }

                if (enemyAttackedIdx == g_SysWork.targetNpcIdx)
                {
                    temp_a1 = Q12_FRACT(ratan2((g_SysWork.npcs[enemyAttackedIdx].position.vx + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork.player.position.vx,
                                               (g_SysWork.npcs[enemyAttackedIdx].position.vz + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork.player.position.vz) + Q12(1.0f));

                    Math_ShortestAngleGet(player->rotation.vy, temp_a1, &ssp20);
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
                        player->field_2A = player->rotation.vy = temp_a1;
                        D_800C454C             = 0;
                    }
                }
            }
            else
            {
                enemyAttackedIdx                                           = NO_VALUE;
                playerProps.field_122 = Q12_ANGLE(90.0f);
                player->field_2A                                            = player->rotation.vy;
            }

            if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (playerProps.flags_11C & PlayerFlag_Unk11)
                {
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 - 12;
                        extra->model.stateStep++;
                    }
                }
                else
                {
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                        extra->model.stateStep++;
                    }
                }
            }
            else if (g_Player_IsAttacking && g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                    extra->model.stateStep++;
                }
            }
            else if (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) ||
                     g_Player_RockDrill_DirectionAttack == 0)
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                    extra->model.stateStep++;
                }
            }
            else if (g_Player_RockDrill_DirectionAttack == NO_VALUE)
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 + 4;
                    extra->model.stateStep++;
                }
            }
            else
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 + 2;
                    extra->model.stateStep++;
                }
            }
        }

        // Audio effects for attack animations, no ammo audio and removes ammo value.
        // Additionally trigger some special state for the Rock Drill.
        if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model.anim.keyframeIdx >= D_800C44D0 && D_800C44D4 >= extra->model.anim.keyframeIdx)
                {
                    if (!(playerProps.flags_11C & PlayerFlag_Unk2))
                    {
                        player->field_44.field_0 = 1;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &player->position, Q8(0.5f), 0);

                        player->properties.player.field_10C                       = 0x40;
                        playerProps.flags_11C |= PlayerFlag_Unk2;
                    }
                }
                else if (D_800C44D4 < extra->model.anim.keyframeIdx)
                {
                    playerProps.flags_11C &= ~PlayerFlag_Unk2;
                }
            }
            else if (playerProps.gasWeaponPowerTimer_114 == Q12(0.0f))
            {
                if (extra->model.anim.keyframeIdx >= D_800C44D0 && D_800C44D4 >= extra->model.anim.keyframeIdx &&
                    !(playerProps.flags_11C & PlayerFlag_Unk2))
                {
                    player->field_44.field_0                                     = 1;
                    playerProps.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else
            {
                if (player->field_44.field_0 <= 0)
                {
                    player->field_44.field_0 = 1;
                }

                player->properties.player.field_10C = 0x40;
            }
        }
        else
        {
            if (extra->model.anim.keyframeIdx >= D_800C44D0 && D_800C44D4 >= extra->model.anim.keyframeIdx &&
                !(playerProps.flags_11C & PlayerFlag_Shooting))
            {
                playerProps.flags_11C |= PlayerFlag_Shooting;

                if (g_SysWork.playerCombat.currentWeaponAmmo != 0)
                {
                    player->field_44.field_0 = 1;

                    if (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                    {
                        g_SysWork.playerCombat.currentWeaponAmmo--;
                        g_SavegamePtr->items_0[g_SysWork.playerCombat.weaponInventoryIdx].count_1--;

                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &player->position, Q8(0.5f), 0);
                    }
                    else
                    {
                        func_8005DC1C(g_Player_EquippedWeaponInfo.attackSfx_0, &player->position, Q8_CLAMPED(0.19f), 0);
                    }

                    player->properties.player.field_10C = 0xC8;
                }
                else
                {
                    func_8005DC1C(g_Player_EquippedWeaponInfo.outOfAmmoSfx_4, &player->position, Q8(0.5f), 0);

                    player->properties.player.field_10C = 32;
                    extra->model.anim.keyframeIdx  = D_800C44F0[D_800AF220].field_6 - 3;
                    extra->model.anim.time          = Q12(D_800C44F0[D_800AF220].field_6 - 3);

                    if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                    {
                        player->model.anim.keyframeIdx = D_800C44F0[D_800AF220].field_6 - 3;
                        player->model.anim.time         = Q12(D_800C44F0[D_800AF220].field_6 - 3);
                    }
                }
            }
        }

        // Finish attack animation.
        // Though more context about `D_800AF220` and `D_800C44F0` is required,
        // they likely indicate if an attack animation has finished.
        if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            // Attack anim.
            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true) ||
                extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
            {
                if (extra->model.anim.keyframeIdx == D_800C44F0[D_800AF220].field_6)
                {
                    extra->model.anim.status      = ANIM_STATUS(HarryAnim_HandgunAim, true);
                    extra->model.anim.keyframeIdx = D_800C44F0[0].field_6;
                    extra->model.anim.time         = Q12(extra->model.anim.keyframeIdx);

                    if (playerProps.flags_11C & PlayerFlag_Unk0)
                    {
                        g_SysWork.playerWork.extra.state          = PlayerState_Combat;
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimTargetLock;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.state          = PlayerState_None;
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Aim;
                        extra->model.controlState                          = extra->model.stateStep = 0;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Aim;
                            playerProps.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }

                    playerProps.field_104  = 0;
                    playerProps.flags_11C &= ~PlayerFlag_Unk2;
                    playerProps.flags_11C &= ~PlayerFlag_Shooting;
                    g_SysWork.playerCombat.weaponAttack                = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack), AttackInputType_Tap);
                    return true;
                }
            }
        }
        // Attack anim.
        else if ((extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true) ||
                  extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk36, true)) &&
                 extra->model.anim.keyframeIdx == D_800C44F0[D_800AF220].field_6)
        {
            if (playerProps.flags_11C & PlayerFlag_Unk0)
            {
                g_SysWork.playerWork.extra.state          = PlayerState_Combat;
                g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimTargetLock;

                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                }
            }
            else
            {
                g_SysWork.playerWork.extra.state          = PlayerState_None;
                g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Aim;
                extra->model.controlState                          = extra->model.stateStep = 0;

                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Aim;
                    playerProps.flags_11C &= ~PlayerFlag_Unk10;
                    player->model.controlState                                      =
                    player->model.stateStep                                  = 0;
                }
            }

            D_800C4556                                                  = NO_VALUE;
            D_800C4554                                                  = NO_VALUE;
            playerProps.field_104  = 0;
            playerProps.flags_11C &= ~PlayerFlag_Shooting;
            return true;
        }

        playerProps.flags_11C |= PlayerFlag_Unk6;

        // Handles multitap attack.
        if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
        {
            if (g_Player_MeleeAttackType == 0 && g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model.anim.keyframeIdx >= keyframeIdx1 &&
                    extra->model.anim.keyframeIdx < keyframeIdx0 &&
                    extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true) &&
                    (g_Player_IsAttacking || g_Player_IsShooting))
                {
                    g_Player_IsMultiTapAttack = true;
                }
            }
        }

        if (g_Player_IsMultiTapAttack)
        {
            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true) &&
                extra->model.anim.keyframeIdx >= keyframeIdx0)
            {
                extra->model.stateStep = 0;

                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                {
                    player->model.stateStep = 0;
                }

                g_Player_AttackAnimIdx                       = g_Player_EquippedWeaponInfo.animAttackHold_8 - 2;
                D_800AF220                                   = (g_Player_EquippedWeaponInfo.field_A >> 4) - 1;
                g_Player_MeleeAttackType                     = 2;
                g_SysWork.playerCombat.weaponAttack = WEAPON_ATTACK(WEAPON_ATTACK_ID_GET(weaponAttack), AttackInputType_Multitap);

                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 - 2;
                    extra->model.stateStep++;
                }

                D_800C44D0 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx + D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_E;
                D_800C44D4 = HARRY_BASE_ANIM_INFOS[g_Player_AttackAnimIdx].startKeyframeIdx + D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_E +
                             D_800AD4C8[g_SysWork.playerCombat.weaponAttack].field_F;
                g_Player_IsMultiTapAttack = 0;

                playerProps.flags_11C &= ~PlayerFlag_Unk2;
            }
        }

        return false;
    }

    enemyAttackedIdx = NO_VALUE;

    if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimTargetLock && g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_Attack)
    {
        playerProps.field_104 = 0;
    }

    switch (g_SysWork.playerWork.extra.upperBodyState)
    {
        case PlayerUpperBodyState_None:
            if ((extra->model.anim.status == ANIM_STATUS(HarryAnim_WalkForward, true) ||
                 extra->model.anim.status == ANIM_STATUS(HarryAnim_RunForward, true)) &&
                extra->model.stateStep != 0)
            {
                extra->model.stateStep = 0;
            }

            // Set idle animation.
            if (player->properties.player.exhaustionTimer_FC < Q12(10.0f) && player->health >= Q12(30.0f))
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_Idle, false);
                    extra->model.stateStep++;
                }

                Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 53, 1);
            }
            else
            {
                player->properties.player.afkTimer_E8 = Q12(0.0f);

                // If not normal idle anim, set it and update `upperBodyState`.
                if (extra->model.anim.status != ANIM_STATUS(HarryAnim_Idle, true))
                {
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = ANIM_STATUS(HarryAnim_Idle, false);
                        extra->model.stateStep++;
                    }

                    Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_None, 55, 1);
                }
                else
                {
                    extra->model.stateStep = 0;
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = ANIM_STATUS(HarryAnim_IdleExhausted, false);
                        extra->model.stateStep++;
                    }
                }
            }

            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_None)
            {
                player->properties.player.afkTimer_E8 = Q12(0.0f);
            }

            player->field_2A = player->rotation.vy;

            if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_None)
            {
                player->properties.player.afkTimer_E8++;

                if (player->properties.player.afkTimer_E8 >= 300)
                {
                    if (player->health >= Q12(60.0f))
                    {
                        player->properties.player.afkTimer_E8             = Q12(0.0f);
                        // TODO: `Player_ExtraStateSet` doesn't match?
                        g_SysWork.playerWork.extra.state              = PlayerState_Idle;
                        player->model.controlState = player->model.stateStep = 0;
                        extra->model.controlState = extra->model.stateStep = 0;
                        g_SysWork.playerWork.extra.upperBodyState     = PlayerUpperBodyState_None;
                        g_SysWork.playerWork.extra.lowerBodyState     = PlayerLowerBodyState_None;
                        return true;
                    }
                }
            }
            break;

        default:
            break;

        case PlayerUpperBodyState_WalkForward:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_WalkForward, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_WalkForward, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkForward, 5, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunForward:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunForward, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunForward, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunForward, 7, 2);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunWallStop:
            if (playerProps.flags_11C & PlayerFlag_WallStopRight)
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardWallStopRight, false);
                    extra->model.stateStep++;
                }
            }
            else if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 19, 0);
            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunWallStop, 21, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_SidestepRight:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_SidestepRight, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRight, 13, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_SidestepLeft:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_SidestepLeft, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepLeft, 11, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunRight:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunRight, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRight, 17, 0);
            player->field_2A = player->rotation.vy;

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunRight, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }
            break;

        case PlayerUpperBodyState_RunLeft:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunLeft, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeft, 15, 0);
            player->field_2A = player->rotation.vy;

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunLeft, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }
            break;

        case PlayerUpperBodyState_WalkBackward:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_WalkBackward, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_WalkBackward, 9, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_QuickTurnRight:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_QuickTurnRight, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnRight, 29, 0);

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_QuickTurnRight, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_QuickTurnLeft:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_QuickTurnLeft, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_QuickTurnLeft, 31, 0);

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_QuickTurnLeft, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_TurnRight:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_TurnRight, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnRight, 27, 3);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_TurnLeft:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_TurnLeft, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_TurnLeft, 25, 4);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunJumpBackward:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_JumpBackward, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_JumpBackward, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunJumpBackward, 33, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_LowerBodyStumble:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardStumble, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunForwardStumble, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_LowerBodyStumble, 23, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunLeftWallStop:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunLeftWallStop, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftWallStop, 0x25, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunRightWallStop:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunRightWallStop, false);
                extra->model.stateStep++;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunRightWallStop, 41, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_RunLeftStumble:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunLeftStumble, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunLeftStumble, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_RunLeftStumble, 39, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_SidestepRightStumble:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_RunRightStumble, false);
                extra->model.stateStep++;
            }

            if (extra->model.anim.status == ANIM_STATUS(HarryAnim_RunRightStumble, true))
            {
                extra->model.anim.time = player->model.anim.time;
            }

            Player_UpperBodyStateUpdate(extra, PlayerUpperBodyState_SidestepRightStumble, 43, 0);
            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_Aim:
            g_SysWork.targetNpcIdx = NO_VALUE;

            if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
                {
                    if (player->field_44.field_0 <= 0)
                    {
                        player->field_44.field_0 = 1;
                    }

                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk34, false);
                        extra->model.stateStep++;
                    }
                }
                else
                {
                    extra->model.anim.status      = ANIM_STATUS(HarryAnim_HandgunAim, true);
                    extra->model.anim.keyframeIdx = D_800AF5C6;
                    extra->model.anim.time         = D_800AF5C6 << 12;
                }
            }

            playerProps.flags_11C &= ~PlayerFlag_Unk6;
            player->field_2A                                             = player->rotation.vy;

            if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                // Aim.
                if (extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                    extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk34, true))
                {
                    if (g_Player_IsAttacking || g_Player_IsShooting)
                    {
                        playerProps.flags_11C |= PlayerFlag_Unk11;
                    }
                    else
                    {
                        playerProps.flags_11C &= ~PlayerFlag_Unk11;

                        if (extra->model.stateStep == 0)
                        {
                            extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk34, false);
                            extra->model.stateStep++;
                        }
                    }
                }
                else
                {
                    playerProps.flags_11C &= ~PlayerFlag_Unk11;
                }
            }
            break;

        case PlayerUpperBodyState_AimTargetLock:
            playerProps.field_104 += g_DeltaTime;
            playerProps.flags_11C &= ~PlayerFlag_Unk6;

            if (g_Player_IsTurningRight)
            {
                playerTurn = 1;
            }
            else
            {
                playerTurn = (g_Player_IsTurningLeft != false) * 2;
            }

            if ((extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk29, true) || extra->model.anim.keyframeIdx != D_800C44F0[1].field_6) &&
                (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk30, true) || extra->model.anim.keyframeIdx != D_800C44F0[2].field_6) &&
                (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk32, true) || extra->model.anim.keyframeIdx != D_800C44F0[4].field_6))
            {
                playerTurn = 0;
                player->properties.player.field_100++;
            }
            else
            {
                player->properties.player.field_100 = 0;
            }

            if (playerTurn != 0)
            {
                playerProps.flags_11C &= ~PlayerFlag_Unk9;
                player->properties.player.field_F4                 = g_Player_FlexRotationX;

                if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(2.0f / 3.0f), Q12(10.0f), playerTurn);
                }
                else
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(1.0f / 3.0f), Q12(3.0f), playerTurn);
                }

                if (g_Player_TargetNpcIdx == NO_VALUE)
                {
                    playerProps.flags_11C &= ~PlayerFlag_Unk12;
                    player->model.stateStep                                  = 0;
                    playerProps.field_122  = Q12_ANGLE(90.0f);
                    g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Aim;
                    g_Player_IsShooting                                         = false;
                    g_SysWork.playerWork.extra.state                      = PlayerState_None;
                    g_Player_IsAttacking                                        = false;
                    extra->model.controlState                                      = extra->model.stateStep = 0;

                    if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                        player->model.controlState                          = player->model.stateStep = 0;
                    }
                }
                else
                {
                    g_SysWork.playerWork.extra.upperBodyState         = PlayerUpperBodyState_AimTargetLockSwitch;
                    playerProps.flags_11C |= PlayerFlag_Unk12;
                    extra->model.controlState                                      = extra->model.stateStep = 0;
                }

                g_SysWork.targetNpcIdx = g_Player_TargetNpcIdx;
            }
            else
            {
                if (extra->model.controlState != 0)
                {
                    if (g_TargetEnemyPosition.vx != g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vx ||
                        g_TargetEnemyPosition.vy != g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vy ||
                        g_TargetEnemyPosition.vz != g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vz ||
                        g_Player_PrevPosition.vx != g_SysWork.playerWork.player.position.vx ||
                        g_Player_PrevPosition.vy != g_SysWork.playerWork.player.position.vy ||
                        g_Player_PrevPosition.vz != g_SysWork.playerWork.player.position.vz)
                    {
                        if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                        {
                            func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(10.0f), 0);
                        }
                        else
                        {
                            func_8005CD38(&enemyAttackedIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x11C, Q12(3.0f), 0);
                        }

                        g_TargetEnemyPosition = g_SysWork.npcs[g_SysWork.targetNpcIdx].position;
                    }
                    else
                    {
                        enemyAttackedIdx = g_SysWork.targetNpcIdx;
                    }
                }
                else
                {
                    enemyAttackedIdx      = g_SysWork.targetNpcIdx;
                    g_TargetEnemyPosition = g_SysWork.npcs[g_SysWork.targetNpcIdx].position;
                }

                if (enemyAttackedIdx == g_SysWork.targetNpcIdx && enemyAttackedIdx != NO_VALUE)
                {
                    player->field_2A = Q12_FRACT(ratan2((g_SysWork.npcs[enemyAttackedIdx].position.vx + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetX_0) - g_SysWork.playerWork.player.position.vx,
                                                       (g_SysWork.npcs[enemyAttackedIdx].position.vz + g_SysWork.npcs[enemyAttackedIdx].field_D8.offsetZ_2) - g_SysWork.playerWork.player.position.vz) +
                                                Q12_ANGLE(360.0f));
                }
                else
                {
                    playerProps.flags_11C &= ~PlayerFlag_Unk12;
                    player->model.stateStep                                  = 0;
                    playerProps.field_122  = Q12_ANGLE(90.0f);
                    g_SysWork.targetNpcIdx                                 = NO_VALUE;
                    g_SysWork.playerWork.extra.state                      = PlayerState_None;
                    g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Aim;
                    extra->model.controlState                                      = extra->model.stateStep = 0;
                }
            }

            if (extra->model.controlState == 0)
            {
                extra->model.controlState++;
            }
            break;

        case PlayerUpperBodyState_AimStart:
            player->field_2A = player->rotation.vy;

            if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
                {
                    if (extra->model.stateStep == 0)
                    {
                        extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk33, false);
                        extra->model.stateStep++;
                    }
                }
                else if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_HandgunAim, false);
                    extra->model.stateStep++;
                }

                if (((g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) &&
                      extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                      extra->model.anim.keyframeIdx >= (D_800C44F0[0].field_4 + 5)) ||
                     (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) &&
                      extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunAim, true) &&
                      extra->model.anim.keyframeIdx >= (D_800C44F0[0].field_4 + 9))) &&
                    !(playerProps.flags_11C & PlayerFlag_Unk2))
                {
                    playerProps.gasWeaponPowerTimer_114 = Q12(60.0f);

                    func_8004C564(g_SysWork.playerCombat.weaponAttack, 0);

                    player->properties.player.field_10C                       = 0x40;
                    playerProps.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap))
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk29, false);
                    extra->model.stateStep++;
                }
            }
            else
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_HandgunAim, false);
                    extra->model.stateStep++;
                }
            }

            if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                if (extra->model.anim.keyframeIdx == D_800C44F0[0].field_6 ||
                    extra->model.anim.keyframeIdx == D_800C44F0[5].field_6)
                {
                    if (extra->model.anim.keyframeIdx == D_800C44F0[0].field_6)
                    {
                        func_8004C564(g_SysWork.playerCombat.weaponAttack, 1);
                    }

                    g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Aim;
                    extra->model.controlState                                      = extra->model.stateStep = 0;
                    playerProps.flags_11C &= ~PlayerFlag_Unk2;

                    if (playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
                    {
                        player->field_44.field_0 = 1;
                    }
                }
            }
            else
            {
                if (extra->model.anim.keyframeIdx == D_800C44F0[0].field_6 ||
                    extra->model.anim.keyframeIdx == D_800C44F0[1].field_6)
                {
                    g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Aim;
                }
            }
            break;

        case PlayerUpperBodyState_AimStartTargetLock:
        case PlayerUpperBodyState_AimTargetLockSwitch:
            sp22 = 0;

            if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (g_GameWork.config.optExtraAutoAiming_2C)
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(10.0f), 0);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(3.0f), 0);
                    }
                }
                else if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(3.0f), Q12(7.0f), 4);
                }
                else
                {
                    func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(0.9f), Q12(2.1f), 4);
                }

                g_SysWork.targetNpcIdx = g_Player_TargetNpcIdx;
            }

            D_800AF220 = 1;
            player->properties.player.field_100++;

            if (!g_GameWork.config.optExtraWeaponCtrl_23)
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

            extra->model.controlState++;

            if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock)
            {
                if (extra->model.stateStep == 0)
                {
                    extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk32, false);
                    extra->model.stateStep++;
                }
            }
            else if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_Unk29, false);
                extra->model.stateStep++;
            }

            if (g_SysWork.targetNpcIdx == NO_VALUE)
            {
                playerProps.field_122  = Q12_ANGLE(90.0f);
                g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Aim;
                g_SysWork.playerWork.extra.state                      = PlayerState_None;
                playerProps.flags_11C &= ~PlayerFlag_Unk12;
                extra->model.controlState                                      = extra->model.stateStep = 0;
                break;
            }

            if (!g_GameWork.config.optExtraAutoAiming_2C)
            {
                temp_v0_3 = ratan2((g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vx + g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetX_0) - g_SysWork.playerWork.player.position.vx,
                                   (g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vz + g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetZ_2) - g_SysWork.playerWork.player.position.vz);

                temp_s1_2 = Q12_ANGLE_NORM_U(temp_v0_3 + Q12_ANGLE(360.0f));

                switch (extra->model.anim.status)
                {
                    case ANIM_STATUS(HarryAnim_Unk29, true):
                    case ANIM_STATUS(HarryAnim_Unk32, true):
                        if (extra->model.anim.keyframeIdx == D_800C44F0[D_800AF220].field_6)
                        {
                            player->rotation.vy = temp_s1_2;
                        }
                        break;
                }

                Math_ShortestAngleGet(player->rotation.vy, temp_s1_2, &sp20);

                D_800C454C = ((extra->model.controlState * 3) + 12) * g_DeltaTime;
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
                    player->rotation.vy  = temp_s1_2;
                    D_800C454C             = 0;
                    player->field_2A        = temp_s1_2;

                    if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock)
                    {
                        playerProps.flags_11C &= ~PlayerFlag_Unk8;
                    }
                    else
                    {
                        playerProps.flags_11C |= PlayerFlag_Unk8;
                    }

                    if (playerProps.flags_11C & PlayerFlag_Unk9)
                    {
                        if (extra->model.anim.keyframeIdx == D_800C44F0[4].field_6)
                        {
                            g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Attack;

                            if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                                player->model.controlState                          =
                                player->model.stateStep                      = 0;
                            }

                            playerProps.flags_11C &= ~PlayerFlag_Unk9;
                            extra->model.controlState                                      =
                            extra->model.stateStep                                  = 0;
                        }
                    }
                    else if (extra->model.anim.keyframeIdx == D_800C44F0[4].field_6)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimTargetLock;
                        extra->model.controlState                          =
                        extra->model.stateStep                      = 0;
                    }
                }

                player->field_2A = player->rotation.vy;
                break;
            }

            temp_v0_3 = ratan2((g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vx +
                                g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetX_0) -
                               g_SysWork.playerWork.player.position.vx,
                                (g_SysWork.npcs[g_SysWork.targetNpcIdx].position.vz +
                                 g_SysWork.npcs[g_SysWork.targetNpcIdx].field_D8.offsetZ_2) -
                                g_SysWork.playerWork.player.position.vz);

            temp_s1_2 = Q12_ANGLE_NORM_U(temp_v0_3 + Q12_ANGLE(360.0f));

            Math_ShortestAngleGet(player->rotation.vy, temp_s1_2, &sp20);

            sp20      = CLAMP(sp20, -0x180, 0x180);

            temp_v1_3 = g_DeltaTime * 0xF;
            temp_v1_3 = CLAMP(temp_v1_3, 0, 0xFFF);
            var_s0    = temp_v1_3;

            Math_ShortestAngleGet(player->field_2A, temp_s1_2, &sp22);

            if (ABS(sp22) > Q12_ANGLE(11.25f))
            {
                if (sp22 < Q12_ANGLE(0.0f))
                {
                    var_s0 = -var_s0;
                }

                player->field_2A = Q12_ANGLE_NORM_U((player->field_2A + (var_s0 >> 4)) + Q12_ANGLE(360.0f));
            }
            else
            {
                player->field_2A = player->rotation.vy + sp20;

                if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock)
                {
                    playerProps.flags_11C &= ~PlayerFlag_Unk8;
                }
                else
                {
                    playerProps.flags_11C |= PlayerFlag_Unk8;
                }

                if (playerProps.flags_11C & PlayerFlag_Unk9)
                {
                    if (extra->model.anim.keyframeIdx == D_800C44F0[4].field_6)
                    {
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Attack;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                            player->model.controlState                          = player->model.stateStep = 0;
                        }

                        playerProps.flags_11C &= ~PlayerFlag_Unk9;
                        extra->model.controlState                                      = extra->model.stateStep = 0;
                    }
                }
                else if (extra->model.anim.keyframeIdx == D_800C44F0[4].field_6)
                {
                    g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimTargetLock;
                    extra->model.controlState = extra->model.stateStep = 0;
                }
            }
            break;

        case PlayerUpperBodyState_AimStop:
            D_800AF220 = g_Player_EquippedWeaponInfo.field_A & 0xF;

            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = g_Player_EquippedWeaponInfo.animStopAiming_6;
                extra->model.stateStep++;
            }

            if (extra->model.anim.keyframeIdx == D_800C44F0[D_800AF220].field_4 ||
                ((g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_RunForward || g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_RunRight ||
                  g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_RunLeft) &&
                 (extra->model.anim.keyframeIdx <= D_800C44F0[D_800AF220].field_6)))
            {
                switch (g_SysWork.playerWork.extra.lowerBodyState)
                {
                    case PlayerLowerBodyState_RunForward:
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunForward;
                        break;

                    case PlayerLowerBodyState_RunRight:
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunRight;
                        break;

                    case PlayerLowerBodyState_AimRunLeft:
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunLeft;
                        break;

                    default:
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_None;
                        break;
                }

                extra->model.controlState = extra->model.stateStep = 0;
                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_None)
                {
                    player->model.controlState = player->model.stateStep = 0;
                }

                g_SysWork.targetNpcIdx = NO_VALUE;
            }

            player->field_2A = player->rotation.vy;
            break;

        case PlayerUpperBodyState_Attack:
            if (Player_CombatAnimUpdate())
            {
                return true;
            }
            break;

        case PlayerUpperBodyState_Reload:
            if (extra->model.stateStep == 0)
            {
                extra->model.anim.status = ANIM_STATUS(HarryAnim_HandgunRecoil, false);
                extra->model.stateStep++;
            }

            if ((D_800AF624 + g_Player_EquippedWeaponInfo.field_9) <= extra->model.anim.keyframeIdx &&
                !(playerProps.flags_11C & PlayerFlag_Unk2))
            {
                func_8005DC1C(g_Player_EquippedWeaponInfo.reloadSfx_2, &player->position, Q8(0.5f), 0);

                player->properties.player.field_10C                       = 0x20;
                playerProps.flags_11C |= PlayerFlag_Unk2;
            }

            if (extra->model.anim.keyframeIdx == D_800AF626)
            {
                g_Player_TargetNpcIdx                                       = NO_VALUE;
                g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Aim;
                g_SysWork.targetNpcIdx                                 = NO_VALUE;
                g_SysWork.playerWork.extra.state                      = PlayerState_None;
                playerProps.flags_11C &= ~PlayerFlag_Unk2;
                extra->model.anim.status                              = ANIM_STATUS(HarryAnim_HandgunAim, true);
                extra->model.anim.keyframeIdx                         = 588;
                extra->model.anim.time                                = Q12(588.0f);

                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Reload)
                {
                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                }

                if (g_SysWork.playerCombat.totalWeaponAmmo != 0)
                {
                    currentAmmoVar = g_SysWork.playerCombat.currentWeaponAmmo;
                    totalAmmoVar   = g_SysWork.playerCombat.totalWeaponAmmo;

                    Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombat.weaponAttack);

                    g_SysWork.playerCombat.currentWeaponAmmo = currentAmmoVar;
                    g_SysWork.playerCombat.totalWeaponAmmo   = totalAmmoVar;

                    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                    {
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat.weaponAttack + InvItemId_KitchenKnife))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat.currentWeaponAmmo;
                        }
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat.weaponAttack + InvItemId_Handgun))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat.totalWeaponAmmo;
                        }
                    }
                }
            }
            break;
    }

    return false;
}

void Player_CombatStateUpdate(s_SubCharacter* player, s_PlayerExtra* extra) // 0x800771BC
{
    s32 currentAmmoVar;
    s32 totalAmmoVar;
    s32 i;

    // Lock player view onto enemy.
    switch (g_SysWork.playerWork.extra.upperBodyState)
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
                if ((g_Player_IsAiming && g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap)) ||
                    g_SysWork.playerCombat.isAiming)
                {
                    g_SysWork.playerCombat.isAiming = true;

                    if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                    {
                        g_Player_TargetNpcIdx = NO_VALUE;
                    }
                    else
                    {
                        if (g_GameWork.config.optExtraAutoAiming_2C)
                        {
                            if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                            {
                                func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(10.0f), 0);
                            }
                            else
                            {
                                func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, 0x238, Q12(3.0f), 0);
                            }
                        }
                        else if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 1))
                        {
                            func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(3.0f), Q12(7.0f), 4);
                        }
                        else
                        {
                            func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(0.9f), Q12(2.1f), 4);
                        }
                    }

                    g_SysWork.targetNpcIdx = g_Player_TargetNpcIdx;
                    if (g_SysWork.targetNpcIdx == NO_VALUE)
                    {
                        g_SysWork.playerWork.extra.upperBodyState            = PlayerUpperBodyState_AimStart;
                        playerProps.field_122 = Q12_ANGLE(90.0f);
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.state          = PlayerState_Combat;
                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimStartTargetLock;
                    }

                    if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_None)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                        player->model.stateStep                      = 0;
                        player->model.controlState                          = 0;
                    }
                    else if (g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState += PlayerLowerBodyState_Aim;
                    }

                    extra->model.stateStep            = 0;
                    extra->model.controlState                = 0;
                    player->properties.player.field_100 = 0;

                    if (g_SysWork.playerCombat.totalWeaponAmmo != 0)
                    {
                        if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                        {
                            currentAmmoVar = g_SysWork.playerCombat.currentWeaponAmmo;
                            totalAmmoVar   = g_SysWork.playerCombat.totalWeaponAmmo;

                            Items_AmmoReloadCalculation(&currentAmmoVar, &totalAmmoVar, g_SysWork.playerCombat.weaponAttack);

                            g_SysWork.playerCombat.currentWeaponAmmo = currentAmmoVar;
                            g_SysWork.playerCombat.totalWeaponAmmo   = totalAmmoVar;
                        }
                    }

                    if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                    {
                        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                        {
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat.weaponAttack + InvItemId_KitchenKnife))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat.currentWeaponAmmo;
                            }
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombat.weaponAttack + InvItemId_Handgun))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombat.totalWeaponAmmo;
                            }
                        }
                    }
                }
            }
            break;
    }

    // Execute finishing move on knocked enemies.
    switch (g_SysWork.playerWork.extra.upperBodyState)
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
                    Player_ExtraStateSet(player, extra, PlayerState_StompEnemy);
                    return;
                }

                if (g_Player_IsShooting)
                {
                    Player_ExtraStateSet(player, extra, PlayerState_KickEnemy);
                    return;
                }
            }
            break;
    }

    // Handle aim state.
    switch (g_SysWork.playerWork.extra.upperBodyState)
    {
        case PlayerUpperBodyState_Aim:
        case PlayerUpperBodyState_AimTargetLock:
            // Stop aiming.
            if (( g_GameWork.config.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                (!g_GameWork.config.optExtraWeaponCtrl_23 &&  g_Player_IsAiming))
            {
                player->properties.player.field_F4                        = 0;
                g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_AimStop;
                g_SysWork.targetNpcIdx                                 = NO_VALUE;
                playerProps.flags_11C &= ~PlayerFlag_Unk0;
                g_SysWork.playerWork.extra.state                      = PlayerState_None;
                g_SysWork.playerCombat.isAiming                   = false;
                playerProps.flags_11C &= ~PlayerFlag_Unk9;

                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim ||
                    g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                {
                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                    player->model.stateStep                      = 0;
                    player->model.controlState                          = 0;
                    extra->model.stateStep                      = 0;
                    extra->model.controlState                          = 0;
                    break;
                }

                if (g_SysWork.playerWork.extra.lowerBodyState >= PlayerLowerBodyState_AimWalkForward)
                {
                    g_SysWork.playerWork.extra.lowerBodyState -= PlayerLowerBodyState_Aim;
                }

                extra->model.stateStep = 0;
                extra->model.controlState     = 0;
                break;
            }

            if ((g_Player_IsAttacking || g_Player_IsShooting) &&
                g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_AimQuickTurnRight &&
                g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_AimQuickTurnLeft)
            {
                if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                        g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
                    {
                        if ((extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[0].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk29, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[1].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk34, true) ||
                             extra->model.anim.keyframeIdx < D_800C44F0[6].field_4 ||
                             D_800C44F0[6].field_6 < extra->model.anim.keyframeIdx) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk30, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[2].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[3].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk33, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[5].field_6))
                        {
                            break;
                        }
                    }
                    else
                    {
                        if ((extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[0].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk29, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[1].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk30, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[2].field_6) &&
                            (extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                             extra->model.anim.keyframeIdx != D_800C44F0[3].field_6))
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if ((extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunAim, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[0].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk29, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[1].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk30, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[2].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_HandgunRecoil, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[3].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk32, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[4].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk36, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[8].field_6) &&
                        (extra->model.anim.status != ANIM_STATUS(HarryAnim_Unk34, true) ||
                         extra->model.anim.keyframeIdx != D_800C44F0[6].field_4))
                    {
                        break;
                    }
                }

                playerProps.flags_11C &= ~PlayerFlag_Unk0;

                if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(3.0f), Q12(3.0f), 5);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(1.0f), Q12(1.0f), 5);
                    }

                    g_SysWork.targetNpcIdx = g_Player_TargetNpcIdx;
                }
                else
                {
                    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & PlayerFlag_Unk0))
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(7.0f), Q12(7.0f), 5);
                    }
                    else
                    {
                        func_8005CD38(&g_Player_TargetNpcIdx, &playerProps.field_122, &g_SysWork.playerCombat, Q12(2.1f), Q12(2.1f), 5);
                    }
                }

                switch (g_Player_TargetNpcIdx)
                {
                    default:
                        if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                        {
                            g_SysWork.playerWork.extra.state                      = PlayerState_Combat;
                            playerProps.flags_11C |= PlayerFlag_Unk0 | PlayerFlag_Unk9;

                            if (g_SysWork.targetNpcIdx != g_Player_TargetNpcIdx)
                            {
                                g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_AimTargetLockSwitch;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Attack;

                                if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                                    player->model.stateStep                      = 0;
                                    player->model.controlState                          = 0;
                                }
                            }

                            g_SysWork.targetNpcIdx = g_Player_TargetNpcIdx;
                            break;
                        }

                        g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Attack;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                            player->model.stateStep                      = 0;
                            player->model.controlState                          = 0;
                        }

                    case NO_VALUE:
                        playerProps.field_122  = Q12_ANGLE(90.0f);
                        g_SysWork.playerWork.extra.upperBodyState             = PlayerUpperBodyState_Attack;
                        playerProps.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                            player->model.stateStep                      = 0;
                            player->model.controlState                          = 0;
                        }
                        break;
                }

                if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (g_SysWork.playerCombat.currentWeaponAmmo == 0 &&
                        INVENTORY_ITEM_GROUP(g_SavegamePtr->equippedWeapon_AA) == InvItemGroup_GunWeapons &&
                        g_SysWork.playerCombat.totalWeaponAmmo != 0)
                    {
                        g_SysWork.playerWork.extra.upperBodyState              = PlayerUpperBodyState_Reload;
                        playerProps.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim ||
                            g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Attack)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Reload;
                            player->model.stateStep                          = 0;
                            player->model.controlState                       = 0;
                        }
                    }
                }
                else
                {
                    g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_Attack;

                    if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_Aim ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_SteelPipe ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Hammer    ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_RockDrill ||
                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Katana)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Attack;
                        player->model.stateStep                      = 0;
                        player->model.controlState                          = 0;
                    }
                }

                extra->model.stateStep = 0;
                extra->model.controlState     = 0;
            }
            else
            {
                playerProps.flags_11C &= ~PlayerFlag_Unk9;
            }
            break;
    }
}

void Player_StepWallStop_MovementCancel(s_SubCharacter* player, s32 animStatus0, s32 animStatus1, s32 keyframeIdx, e_PlayerLowerBodyState lowerBodyState, s32 headingAngle, s32 aimState) // 0x80077BB8
{
    q3_12 headingAngleCpy;

    if (playerProps.moveDistance_126 != Q12(0.0f))
    {
        playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 1;
        if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
        {
            playerProps.moveDistance_126 = Q12(0.0f);
        }
    }

    if (player->model.stateStep == 0)
    {
        player->model.anim.status = animStatus0;
        player->model.stateStep++;
    }

    if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStartTargetLock)
    {
        if (player->model.anim.status == animStatus1 && player->model.anim.keyframeIdx >= keyframeIdx)
        {
            g_SysWork.playerWork.extra.lowerBodyState = aimState;
            Player_MovementStateReset(player, lowerBodyState);
        }

        Player_CharaRotate(2);
    }

    if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_None)
    {
        playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
        g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
    }
    else
    {
        headingAngleCpy                                                   = headingAngle;
        playerProps.headingAngle_124 = headingAngleCpy;
        g_Player_HeadingAngle                                             = headingAngleCpy;
    }
}

void Player_LowerBodyUpdate(s_SubCharacter* player, s_PlayerExtra* extra) // 0x80077D00
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

    if (g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim)
    {
        aimState = 0;
    }
    else
    {
        aimState = 20;
    }

    // Compute move distance step.
    temp_s3        = func_8007D6F0(player, &D_800C45C8);
    speedZoneType  = Map_SpeedZoneTypeGet(player->position.vx, player->position.vz);
    speedX         = SQUARE(player->position.vx - g_Player_PrevPosition.vx);
    speedZ         = SQUARE(player->position.vz - g_Player_PrevPosition.vz);
    travelDistStep = SquareRoot0(speedX + speedZ);

    switch (g_SysWork.playerWork.extra.lowerBodyState)
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

    switch (g_SysWork.playerWork.extra.lowerBodyState)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            if (player->model.anim.status == ANIM_STATUS(HarryAnim_WalkForward, true))
            {
                player->model.stateStep = 0;
            }

            // Check if player is aiming.
            if (aimState != 0)
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if ((playerProps.moveDistance_126 >> 16) & 1)
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                if ((playerProps.moveDistance_126 >> 16) & 1)
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            // Sets animations during specific idle states while aiming or standing.
            if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_None)
            {
                // Aim to idle.
                if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombat.isAiming && player->model.stateStep == 0)
                    {
                        player->model.anim.status = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        player->model.stateStep++;
                    }
                }
                // Check if player has >= 30% or < 10% health to determine level of exertion.
                else if (player->properties.player.exhaustionTimer_FC < Q12(10.0f) && player->health >= Q12(30.0f))
                {
                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_Idle, false);
                        player->model.stateStep++;
                    }
                }
                else if (player->model.stateStep == 0)
                {
                    player->model.anim.status = ANIM_STATUS(HarryAnim_IdleExhausted, false);
                    player->model.stateStep++;
                }
            }
            else
            {
                if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStop)
                {
                    if (!g_SysWork.playerCombat.isAiming && player->model.stateStep == 0)
                    {
                        player->model.anim.status = g_Player_EquippedWeaponInfo.animStopAiming_6;
                        player->model.stateStep++;
                    }
                }
                // Melee weapon.
                else if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if ((g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) ||
                         g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap)) &&
                        playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = ANIM_STATUS(HarryAnim_Unk33, false);
                            player->model.stateStep++;
                        }
                    }
                    else if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        player->model.stateStep++;
                    }
                }
                else if (playerProps.flags_11C & PlayerFlag_Unk6)
                {
                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_Unk34, false);
                        player->model.stateStep++;
                    }
                }
                else if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock)
                {
                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_Unk32, false);
                        player->model.stateStep++;
                    }
                }
                else if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap))
                {
                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_Unk29, false);
                        player->model.stateStep++;
                    }
                }
                else
                {
                    if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        player->model.stateStep++;
                    }
                }

                playerProps.flags_11C &= ~PlayerFlag_Unk6;
            }

            // Set idle to move depending on user input.
            if (g_SysWork.playerWork.extra.state == PlayerState_Combat) // Aiming at or shooting enemy.
            {
                if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status) &&
                    ANIM_STATUS_IS_ACTIVE(extra->model.anim.status))
                {
                    if (player->model.anim.status >= ANIM_STATUS(HarryAnim_Unk29, false) ||
                        player->model.anim.keyframeIdx == D_800C44F0[0].field_6 ||
                        player->model.anim.keyframeIdx == D_800C44F0[5].field_6)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkForward;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkBackward;
                        }
                    }
                }

                Player_MovementStateReset(player, aimState);
            }
            // Aiming at nothing, or shooting at nothing, or idle.
            else
            {
                if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status) &&
                    ANIM_STATUS_IS_ACTIVE(extra->model.anim.status))
                {
                    if ((aimState == 0 && playerProps.moveDistance_126 == Q12(0.0f))||
                        player->model.anim.status >= ANIM_STATUS(HarryAnim_Unk29, false) ||
                        player->model.anim.keyframeIdx == D_800C44F0[0].field_6)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            // Restrict aiming when going from idle to run.
                            if ((g_Player_IsRunning && temp_s3 == PlayerLowerBodyState_None) &&
                                (aimState == 0 || (( g_GameWork.config.optExtraWeaponCtrl_23 && !g_Player_IsAiming) ||
                                                   (!g_GameWork.config.optExtraWeaponCtrl_23 &&  g_Player_IsAiming)) &&
                                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_SteelPipe))
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkForward;
                            }
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkBackward;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            player->headingAngle = player->headingAngle + Q12_ANGLE(90.0f);
                            temp_s3                = func_8007D6F0(player, &D_800C45C8);

                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepRight;
                            }
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            player->headingAngle -= Q12_ANGLE(90.0f);
                            temp_s3                 = func_8007D6F0(player, &D_800C45C8);

                            if (g_Player_IsRunning && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepLeft;
                            }
                        }

                        if (aimState == 0 && !g_SysWork.playerCombat.isAiming)
                        {
                            if (( g_GameWork.config.optExtraWalkRunCtrl_2B && !g_Player_IsRunning) ||
                                (!g_GameWork.config.optExtraWalkRunCtrl_2B &&  g_Player_IsRunning))
                            {
                                if (g_Player_IsMovingBackward)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_JumpBackward;
                                    g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunJumpBackward;
                                    extra->model.stateStep                      = 0;
                                    extra->model.controlState                          = 0;
                                }
                            }
                        }

                        if (g_SysWork.playerWork.extra.lowerBodyState == aimState && !g_Player_IsInWalkToRunTransition)
                        {
                            Player_CharaTurn_0(player, aimState);
                        }
                    }
                }

                Player_MovementStateReset(player, aimState);

                if (g_Player_IsRunning)
                {
                    Player_CharaRotate(10);
                }
                else
                {
                    Player_CharaRotate(7);
                }

                if (aimState != 0 && g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_Aim)
                {
                    if (D_800C454C != Q12(0.0f))
                    {
                        // TODO: Convert hex to clean floats.
                        // Determine speed if using certain weapons while moving?
                        switch (g_SysWork.playerCombat.weaponAttack)
                        {
                            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
                                playerProps.moveDistance_126 = (u32)(D_800C454C * 0x465) >> 9;
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Katana,   AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Axe,      AttackInputType_Tap):
                                playerProps.moveDistance_126 = (u32)(D_800C454C * 0x15F9) >> 11;
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Hammer,    AttackInputType_Tap):
                                playerProps.moveDistance_126 = ((u32)(D_800C454C * 0xD2F) >> 10);
                                break;

                            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Handgun,      AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
                            case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                                playerProps.moveDistance_126 = (-(D_800C454C * 0x87F0) >> 14);
                                break;
                        }

                        if (g_DeltaTime != Q12(0.0f))
                        {
                            playerProps.moveDistance_126 = ((playerProps.moveDistance_126 * 0x88) / g_DeltaTime);
                        }

                        // Restart timer for idle animation.
                        if (D_800C454C != Q12(0.0f))
                        {
                            player->properties.player.afkTimer_E8 = Q12(0.0f);
                        }
                    }
                }
                // Move without aiming.
                else if (D_800C454C != Q12(0.0f))
                {
                    player->properties.player.afkTimer_E8 = Q12(0.0f);
                }

                // Turn if idle.
                if (g_Player_IsTurningLeft && player->model.stateStep == 1 &&
                    (player->model.anim.status == ANIM_STATUS(HarryAnim_Idle, true) ||
                     player->model.anim.status == ANIM_STATUS(HarryAnim_IdleExhausted, true)))
                {
                    player->model.stateStep      = 2;
                    player->model.anim.status = ANIM_STATUS(HarryAnim_TurnLeft, false);
                }
                else if (g_Player_IsTurningRight && player->model.stateStep == 1 &&
                         (player->model.anim.status == ANIM_STATUS(HarryAnim_Idle, true) ||
                          player->model.anim.status == ANIM_STATUS(HarryAnim_IdleExhausted, true)))
                {
                    player->model.stateStep      = 2;
                    player->model.anim.status = ANIM_STATUS(HarryAnim_TurnRight, false);
                }

                if (!g_Player_IsTurningLeft && !g_Player_IsTurningRight && player->model.stateStep == 2 &&
                    (player->model.anim.status == ANIM_STATUS(HarryAnim_TurnRight, true) ||
                     player->model.anim.status == ANIM_STATUS(HarryAnim_TurnLeft, true)))
                {
                    player->model.anim.status = ANIM_STATUS(HarryAnim_Idle, false);
                    player->model.stateStep      = 0;
                }
            }

            if (playerProps.moveDistance_126 == Q12(0.0f) ||
                 g_Player_IsTurningLeft || g_Player_IsTurningRight)
            {
                playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            }
            break;

        case PlayerLowerBodyState_WalkForward:
        case PlayerLowerBodyState_AimWalkForward:
            if (!g_Player_IsMovingForward)
            {
                g_SysWork.playerStopFlags |= PlayerStopFlag_StopWalking;
            }

            if ((g_SysWork.playerStopFlags & PlayerStopFlag_StopWalking) &&
                g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop)
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;

                    if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            // Walking.
            else
            {
                if (g_Controller0->sticks_20.sticks_0.leftY <= -STICK_THRESHOLD)
                {
                    D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                    func_80070B84(player, Q12(0.75f), Q12(1.4f), 2);
                }
                // Stopped walking.
                else
                {
                    if (D_800AF216 != 0)
                    {
                        func_80070B84(player, Q12(0.75f), Q12(1.4f), 2);
                    }
                    // Reduce speed if going too fast while walking.
                    else if (playerProps.moveDistance_126 > Q12(1.4f))
                    {
                        playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                        if (playerProps.moveDistance_126 < Q12(1.4f))
                        {
                            playerProps.moveDistance_126 = Q12(1.4f);
                        }
                    }
                    else if (playerProps.moveDistance_126 < Q12(1.4f))
                    {
                        if (player->model.anim.keyframeIdx >= 2)
                        {
                            playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                        }

                        playerProps.moveDistance_126 = CLAMP(playerProps.moveDistance_126,
                                                                                                        Q12(0.0f),
                                                                                                        Q12(1.4f));
                    }

                    if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                    {
                        D_800AF216 = 0;
                    }
                }
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_WalkForward, false);
                player->model.stateStep++;
            }

            // Something related to anim and states when aiming or attacking while moving.
            if (g_SysWork.playerWork.extra.state == PlayerState_Combat)
            {
                if (g_SysWork.playerStopFlags & PlayerStopFlag_StopWalking)
                {
                    if ((g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                         g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop) ||
                         (player->model.anim.keyframeIdx >= 10 && player->model.anim.keyframeIdx <= 11) ||
                          player->model.anim.keyframeIdx == 22 || player->model.anim.keyframeIdx == 21)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(player, aimState | (1 << 0));

                if (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.playerStopFlags & PlayerStopFlag_StopWalking))
                {
                    // Code to change the player's state to running.
                    if (g_Player_IsRunning)
                    {
                        if (aimState == 0 && temp_s3 == PlayerLowerBodyState_None &&
                            (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_WalkForward ||
                             g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStop))
                        {
                            if (player->model.anim.keyframeIdx >= 10 && player->model.anim.keyframeIdx <= 11)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForward;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 36;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_RunForward, true);
                                playerProps.flags_11C |= PlayerFlag_Unk5;
                            }
                            else if (player->model.anim.keyframeIdx >= 21 && player->model.anim.keyframeIdx <= 22)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForward;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 26;
                                HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_RunForward, true);
                            }
                        }
                    }
                }
                else if ((g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                          g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop) ||
                         (player->model.anim.keyframeIdx >= 10 && player->model.anim.keyframeIdx <= 11) ||
                          player->model.anim.keyframeIdx == 22 || player->model.anim.keyframeIdx == 21)
                {
                    // Aparently, code intended to change player's state if the player stop walking while either aiming or attacking.
                    if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                            (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                             g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                            extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            playerProps.flags_11C |= PlayerFlag_Unk10;
                            player->model.stateStep                                  = 0;
                            player->model.controlState                                      = 0;
                            g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork.extra.lowerBodyState             = aimState;
                            playerProps.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.lowerBodyState             = aimState;
                        playerProps.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.playerWork.extra.lowerBodyState == (aimState + PlayerLowerBodyState_WalkForward) && !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(player, aimState);
                }

                Player_MovementStateReset(player, aimState | (1 << 0));
                Player_CharaRotate(5);
            }

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_RunForward)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_Still, false);
                player->model.stateStep++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForward:
            player->properties.player.exhaustionTimer_FC += g_DeltaTime;

            if (g_Controller0->sticks_20.sticks_0.leftY <= -STICK_THRESHOLD)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);

                speedX = GET_MOVE_SPEED(speedZoneType);

                if (playerProps.moveDistance_126 < Q12(3.5f))
                {
                    var_a3 = TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                }
                else
                {
                    speedZ   = g_DeltaTime;
                    speedZ  += (speedZ < 0) ? 3 : 0;
                    var_a3 = speedZ >> 2;
                }

                func_80070CF0(player, Q12(2.0f), speedX, var_a3, TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
            }
            // Stopped running.
            else
            {
                if (D_800AF216 != 0)
                {
                    speedX = GET_MOVE_SPEED(speedZoneType);

                    if (playerProps.moveDistance_126 < Q12(3.5f))
                    {
                        var_a3 = TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                    }
                    else
                    {
                        speedZ   = g_DeltaTime;
                        speedZ  += (speedZ < Q12(0.0f)) ? 3 : Q12(0.0f);
                        var_a3 = speedZ >> 2;
                    }

                    func_80070CF0(player, Q12(2.0f), speedX, var_a3, TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
                }
                else if (playerProps.moveDistance_126 > GET_MOVE_SPEED(speedZoneType))
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if (playerProps.moveDistance_126 < GET_MOVE_SPEED(speedZoneType))
                    {
                        playerProps.moveDistance_126 = GET_MOVE_SPEED(speedZoneType);
                    }
                }
                else
                {
                    if (playerProps.moveDistance_126 < GET_MOVE_SPEED(speedZoneType))
                    {
                        playerProps.moveDistance_126 += GET_VAL(playerProps.moveDistance_126);
                        playerProps.moveDistance_126  = CLAMP(playerProps.moveDistance_126, 0, GET_MOVE_SPEED(speedZoneType));
                    }
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                {
                    D_800AF216 = 0;
                }
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunForward, false);
                player->model.stateStep++;
            }

            if ((player->model.anim.keyframeIdx == 43 || player->model.anim.keyframeIdx == 33) &&
                player->position.vy == player->properties.player.positionY_EC)
            {
                player->fallSpeed = Q12(-1.25f);
            }

            // Running.
            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStartTargetLock &&
                player->model.anim.status == ANIM_STATUS(HarryAnim_RunForward, true))
            {
                // TODO: What does `func_8007D6F0` do?
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Stumble;
                        }
                        else if (player->model.anim.keyframeIdx >= 30 &&
                                 player->model.anim.keyframeIdx <= 31)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = temp_s3;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 8;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        else if (player->model.anim.keyframeIdx >= 41 &&
                                 player->model.anim.keyframeIdx <= 42)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = temp_s3;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 20;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForwardWallStop;
                        }
                        else if (player->model.anim.keyframeIdx >= 30 &&
                                 player->model.anim.keyframeIdx <= 31)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 8;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        else if (player->model.anim.keyframeIdx >= 41 &&
                                 player->model.anim.keyframeIdx <= 42)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 20;
                            HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                        }
                        break;

                    default:
                        if (!g_Player_IsRunning || !g_Player_IsMovingForward)
                        {
                            // Change state from running to walking.
                            if (g_Player_IsMovingForward)
                            {
                                if (player->model.anim.keyframeIdx >= 30 &&
                                    player->model.anim.keyframeIdx <= 31)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 8;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                                else if (player->model.anim.keyframeIdx >= 41 &&
                                         player->model.anim.keyframeIdx <= 42)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 20;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                            }
                            // Set stumble anim if crashed into a wall.
                            else if (player->properties.player.runTimer_F8 >= 5 &&
                                     playerProps.moveDistance_126 >= Q12(3.125f))
                            {
                                if (player->model.anim.keyframeIdx >= 33 &&
                                    player->model.anim.keyframeIdx <= 34)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_RunForwardWallStop;
                                    playerProps.flags_11C &= ~PlayerFlag_WallStopRight;
                                }
                                else if (player->model.anim.keyframeIdx >= 43 &&
                                         player->model.anim.keyframeIdx <= 44)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_RunForwardWallStop;
                                    playerProps.flags_11C |= PlayerFlag_WallStopRight;
                                }
                            }
                            // Change state from running to walking. Difference with first conditional is this only triggers if
                            // walking is abruptly stopped wall crash anim was not triggered.
                            // In-game, appears as though player goes directly to idle. Mechanically, it goes through this state, then to idle.
                            else
                            {
                                if (player->model.anim.keyframeIdx >= 30 &&
                                    player->model.anim.keyframeIdx <= 31)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 8;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                                else if (player->model.anim.keyframeIdx >= 41 &&
                                         player->model.anim.keyframeIdx <= 42)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_WalkForward;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].endKeyframeIdx = 20;
                                    HARRY_BASE_ANIM_INFOS[ANIM_STATUS(HarryAnim_Still, false)].linkStatus         = ANIM_STATUS(HarryAnim_WalkForward, true);
                                }
                            }
                        }
                        break;
                }
            }

            if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_RunForward)
            {
                Player_MovementStateReset(player, PlayerLowerBodyState_RunForward);
            }

            Player_CharaRotate(4);

            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);

            if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_WalkForward)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_Still, false);
                player->model.stateStep++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 1;
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            // Depending on frame of gait cycle, set left or right wall stop anim variant.
            if (playerProps.flags_11C & PlayerFlag_WallStopRight)
            {
                if (player->model.stateStep == 0)
                {
                    player->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardWallStopRight, false);
                    player->model.stateStep++;
                }
            }
            else if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false);
                player->model.stateStep++;
            }

            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStartTargetLock)
            {
                if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true) &&
                    player->model.anim.keyframeIdx >= 168 ||
                    player->model.anim.status == ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true) &&
                    player->model.anim.keyframeIdx >= 158)
                {
                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                    Player_MovementStateReset(player, PlayerLowerBodyState_RunForwardWallStop);
                }

                Player_CharaRotate(4);
            }
            break;

        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            if (!g_Player_IsMovingBackward)
            {
                g_SysWork.playerStopFlags |= PlayerStopFlag_StopRunning;
            }

            if ((g_SysWork.playerStopFlags & PlayerStopFlag_StopRunning) &&
                g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop)
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
                    if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            // Walking backward.
            else if (g_Controller0->sticks_20.sticks_0.leftY >= STICK_THRESHOLD)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                func_80070B84(player, Q12(0.75f), Q12(1.15f), 2);
            }
            // Stop walking backward.
            else
            {
                if (D_800AF216 != 0)
                {
                    func_80070B84(player, Q12(0.75f), Q12(1.15f), 2);
                }
                else if (playerProps.moveDistance_126 > Q12(1.15f))
                {
                    playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2;
                    if (playerProps.moveDistance_126 < Q12(1.15f))
                    {
                        playerProps.moveDistance_126 = Q12(1.15f);
                    }
                }
                else if (playerProps.moveDistance_126 < Q12(1.15f))
                {
                    if (player->model.anim.keyframeIdx >= 2)
                    {
                        playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    }

                    playerProps.moveDistance_126 = CLAMP(playerProps.moveDistance_126,
                                                                                                    Q12(0.0f),
                                                                                                    Q12(1.15f));
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickDown)
                {
                    D_800AF216 = 0;
                }
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_WalkBackward, false);
                player->model.stateStep++;
            }

            if (g_SysWork.playerWork.extra.state == PlayerState_Combat)
            {
                if (g_SysWork.playerStopFlags & PlayerStopFlag_StopRunning)
                {
                    if ((g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                         g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop) ||
                         (player->model.anim.keyframeIdx >= 56 &&
                          player->model.anim.keyframeIdx <= 57) ||
                         player->model.anim.keyframeIdx == 67 ||
                         player->model.anim.keyframeIdx == 66)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_Aim;
                    }
                }

                Player_MovementStateReset(player, aimState + PlayerLowerBodyState_WalkBackward);

                if (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
                {
                    Player_CharaRotate(5);
                }
            }
            else
            {
                if (!(g_SysWork.playerStopFlags & PlayerStopFlag_StopRunning))
                {
                    if (((player->model.anim.keyframeIdx >= 66 &&
                          player->model.anim.keyframeIdx <= 67) ||
                         player->model.anim.keyframeIdx == 46 ||
                         player->model.anim.keyframeIdx == 47) &&
                        aimState == 0 && g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop)
                    {
                        if (( g_GameWork.config.optExtraWalkRunCtrl_2B && !g_Player_IsRunning) ||
                            (!g_GameWork.config.optExtraWalkRunCtrl_2B &&  g_Player_IsRunning))
                        {
                            if (g_Player_IsMovingBackward)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_JumpBackward;
                                g_SysWork.playerWork.extra.upperBodyState = PlayerUpperBodyState_RunJumpBackward;
                                extra->model.stateStep                      = 0;
                                extra->model.controlState                          = 0;
                            }
                        }
                    }
                }
                else if ((g_SysWork.playerWork.extra.lowerBodyState < PlayerLowerBodyState_Aim &&
                          g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop) ||
                         (player->model.anim.keyframeIdx >= 56 && player->model.anim.keyframeIdx <= 57) ||
                          player->model.anim.keyframeIdx == 67 || player->model.anim.keyframeIdx == 66)
                {
                    if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                            extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            playerProps.flags_11C |= PlayerFlag_Unk10;
                            player->model.stateStep                                  = 0;
                            player->model.controlState                                      = 0;
                            g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork.extra.lowerBodyState             = aimState;
                            playerProps.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.lowerBodyState             = aimState;
                        playerProps.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.playerWork.extra.lowerBodyState == (aimState + PlayerLowerBodyState_WalkBackward) &&
                    !g_Player_IsInWalkToRunTransition)
                {
                    Player_CharaTurn_0(player, aimState);
                }

                Player_MovementStateReset(player, aimState + PlayerLowerBodyState_WalkBackward);
                Player_CharaRotate(4);
            }

            playerProps.headingAngle_124 = Q12_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_SidestepRight:
        case PlayerLowerBodyState_AimSidestepRight:
            if (playerProps.moveDistance_126 > Q12(1.25f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)));
                if (playerProps.moveDistance_126 < Q12(1.25f))
                {
                    playerProps.moveDistance_126 = Q12(1.25f);
                }
            }
            else
            {
                if (player->model.anim.keyframeIdx >= 100 &&
                    player->model.anim.keyframeIdx <= 111)
                {
                    playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }
                else if (player->model.anim.keyframeIdx >= 112)
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }

                playerProps.moveDistance_126 = CLAMP(playerProps.moveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.25f));
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_SidestepRight, false);
                player->model.stateStep++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_SidestepRight, true) &&
                player->model.anim.keyframeIdx >= 117)
            {
                // Stopped sidestepping while attacking.
                // If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingRightHold)
                {
                    if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        // Some melee weapons allow attack while sidestepping.
                        if (((extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                              extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            playerProps.flags_11C |= PlayerFlag_Unk10;
                            player->model.stateStep                                  = 0;
                            player->model.controlState                                      = 0;
                            g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRight;
                    }
                }
            }

            Player_CharaTurn_0(player, aimState);
            Player_MovementStateReset(player, aimState + PlayerLowerBodyState_SidestepRight);
            Player_CharaRotate(3);

            playerProps.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_SidestepLeft:
        case PlayerLowerBodyState_AimSidestepLeft:
            if (playerProps.moveDistance_126 > Q12(1.25f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (playerProps.moveDistance_126 < Q12(1.25f))
                {
                    playerProps.moveDistance_126 = Q12(1.25f);
                }
            }
            else
            {
                if (player->model.anim.keyframeIdx >= 75 &&
                    player->model.anim.keyframeIdx <= 86)
                {
                    playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }
                else if (player->model.anim.keyframeIdx >= 87)
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }

                playerProps.moveDistance_126 = CLAMP(playerProps.moveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.25f));
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_SidestepLeft, false);
                player->model.stateStep++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_SidestepLeft, true) &&
                player->model.anim.keyframeIdx >= 92)
            {
                // Stopped stepping while attacking.
                // If attacking with gun, dispatches to idle aim state instead of attack state.
                if (!g_Player_IsSteppingLeftHold)
                {
                    if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                        aimState != 0)
                    {
                        if (((extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true) ||
                              extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true)) &&
                             (g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap) &&
                              g_SysWork.playerCombat.weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))) ||
                             extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                        {
                            playerProps.flags_11C |= PlayerFlag_Unk10;
                            player->model.stateStep                                  = 0;
                            player->model.controlState                                      = 0;
                            g_SysWork.playerWork.extra.lowerBodyState             = PlayerLowerBodyState_Attack;
                        }
                        else
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = aimState;
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = aimState;
                    }
                }
                else if (g_Player_IsRunning != 0 && aimState == 0 && temp_s3 == PlayerLowerBodyState_None)
                {
                    if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStop)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeft;
                    }
                }
            }

            Player_CharaTurn_1(player, aimState);
            Player_MovementStateReset(player, aimState + PlayerLowerBodyState_SidestepLeft);
            Player_CharaRotate(3);

            playerProps.headingAngle_124 = Q12_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_RunRight:
            player->properties.player.exhaustionTimer_FC += g_DeltaTime;
            if (playerProps.moveDistance_126 > Q12(3.1739f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (playerProps.moveDistance_126 < Q12(3.1739f))
                {
                    playerProps.moveDistance_126 = Q12(3.1739f);
                }
            }
            else if (playerProps.moveDistance_126 < Q12(3.1739f))
            {
                playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                playerProps.moveDistance_126  = CLAMP(playerProps.moveDistance_126,
                                                                                                 Q12(0.0f),
                                                                                                 Q12(3.1739f));
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunRight, false);
                player->model.stateStep++;
            }

            if ((player->model.anim.keyframeIdx == 139 ||
                 player->model.anim.keyframeIdx == 145) &&
                player->position.vy == player->properties.player.positionY_EC)
            {
                player->fallSpeed = Q12(-1.0f);
            }

            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRightStumble;
                        }
                        else
                        {
                            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                player->model.anim.keyframeIdx >= 147)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRightWallStop;
                        }
                        else
                        {
                            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                player->model.anim.keyframeIdx >= 147)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (player->properties.player.runTimer_F8 >= 5 &&
                            playerProps.moveDistance_126 >= Q12(3.125f))
                        {
                            if (player->model.anim.keyframeIdx >= 144 && (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRightWallStop;
                            }
                        }
                        else if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunRight, true) &&
                                 player->model.anim.keyframeIdx >= 147 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingRightHold))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(player, PlayerLowerBodyState_RunRight);
            Player_CharaRotate(4);

            playerProps.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_RunLeft:
            player->properties.player.exhaustionTimer_FC += g_DeltaTime;
            if (playerProps.moveDistance_126 > Q12(3.1739f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (playerProps.moveDistance_126 < Q12(3.1739f))
                {
                    playerProps.moveDistance_126 = Q12(3.1739f);
                }
            }
            else if (playerProps.moveDistance_126 < Q12(3.1739f))
            {
                playerProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                playerProps.moveDistance_126  = CLAMP(playerProps.moveDistance_126,
                                                                                                 Q12(0.0f),
                                                                                                 Q12(3.1739f));
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunLeft, false);
                player->model.stateStep++;
            }

            if ((player->model.anim.keyframeIdx == 125 || player->model.anim.keyframeIdx == 132) &&
                player->position.vy == player->properties.player.positionY_EC)
            {
                player->fallSpeed = Q12(-1.0f);
            }

            if (g_SysWork.playerWork.extra.upperBodyState != PlayerUpperBodyState_AimStartTargetLock)
            {
                switch (temp_s3)
                {
                    case PlayerLowerBodyState_WalkForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeftStumble;
                        }
                        else
                        {
                            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunLeft, true) &&
                                player->model.anim.keyframeIdx >= 132)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    case PlayerLowerBodyState_RunForward:
                        if (player->properties.player.runTimer_108 >= (u32)Q12(10.0f))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeftWallStop;
                        }
                        else
                        {
                            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunLeft, true) &&
                                player->model.anim.keyframeIdx >= 132)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                            }
                        }
                        break;

                    default:
                        if (player->properties.player.runTimer_F8 >= 5 &&
                            playerProps.moveDistance_126 >= Q12(3.125f))
                        {
                            if (player->model.anim.keyframeIdx > 128 && (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeftWallStop;
                            }
                        }
                        else if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunLeft, true) && player->model.anim.keyframeIdx >= 132 &&
                                 (!g_Player_IsRunning || !g_Player_IsSteppingLeftHold))
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                        }
                        break;
                }
            }

            Player_MovementStateReset(player, PlayerLowerBodyState_RunLeft);
            Player_CharaRotate(4);

            playerProps.headingAngle_124 = Q12_ANGLE(-90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            g_Player_HeadingAngle = Q12_ANGLE(0.0f);

            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (player->model.controlState == 0)
            {
                playerProps.quickTurnHeadingAngle_120 = player->rotation.vy;
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_QuickTurnRight, false);
                player->model.stateStep++;
            }

            if (player->model.controlState == 0)
            {
                player->model.controlState++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_QuickTurnRight, true) && player->model.anim.keyframeIdx >= 206)
            {
                D_800C454C = g_DeltaTime * 24;
            }
            else
            {
                D_800C454C = Q12(0.0f);
            }

            if (ABS_DIFF(playerProps.quickTurnHeadingAngle_120, player->rotation.vy) > (Q12_ANGLE(180.0f) - ((s32)(g_DeltaTime * 24) >> 4)))
            {
                if (ABS_DIFF(playerProps.quickTurnHeadingAngle_120, player->rotation.vy) < (((g_DeltaTime * 24) >> 4) + Q12_ANGLE(180.0f)))
                {
                    player->rotation.vy                                                   = playerProps.quickTurnHeadingAngle_120 + Q12_ANGLE(180.0f);
                    playerProps.moveDistance_126 = Q12(1.4f);
                    D_800C454C                                                              = Q12(0.0f);

                    // State change.
                    if (player->model.anim.keyframeIdx >= 213)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            player->headingAngle += Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            player->headingAngle -= Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (player->model.anim.keyframeIdx >= 216)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = aimState;
                            player->model.stateStep                      = 0;
                            player->model.controlState                          = 0;
                        }
                    }
                }
            }

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            g_Player_HeadingAngle = Q12_ANGLE(0.0f);

            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (player->model.controlState == 0)
            {
                playerProps.quickTurnHeadingAngle_120 = player->rotation.vy;
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_QuickTurnLeft, false);
                player->model.stateStep++;
            }

            if (player->model.controlState == 0)
            {
                player->model.controlState++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_QuickTurnLeft, true) && player->model.anim.keyframeIdx >= 219)
            {
                D_800C454C = -(g_DeltaTime * 24);
            }
            else
            {
                D_800C454C = Q12(0.0f);
            }

            if (ABS_DIFF(playerProps.quickTurnHeadingAngle_120, player->rotation.vy) > (Q12_ANGLE(180.0f) - ((g_DeltaTime * 24) >> 4)))
            {
                if (ABS_DIFF(playerProps.quickTurnHeadingAngle_120, player->rotation.vy) < (((g_DeltaTime * 24) >> 4) + Q12_ANGLE(180.0f)))
                {
                    player->rotation.vy                                                   = playerProps.quickTurnHeadingAngle_120 + Q12_ANGLE(180.0f);
                    playerProps.moveDistance_126 = Q12(1.4f);
                    D_800C454C                                                              = Q12(0.0f);

                    // State change.
                    if (player->model.anim.keyframeIdx >= 226)
                    {
                        if (g_Player_IsMovingForward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunForward;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkForward;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsMovingBackward)
                        {
                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_JumpBackward;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_WalkBackward;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsSteppingRightHold)
                        {
                            player->headingAngle += Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunRight;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepRight;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (g_Player_IsSteppingLeftHold)
                        {
                            player->headingAngle -= Q12_ANGLE(90.0f);

                            if (g_Player_IsRunning && aimState == 0)
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_RunLeft;
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = aimState + PlayerLowerBodyState_SidestepLeft;
                            }

                            player->model.stateStep = 0;
                            player->model.controlState     = 0;
                        }
                        else if (player->model.anim.keyframeIdx >= 229)
                        {
                            g_SysWork.playerWork.extra.lowerBodyState = aimState;
                            player->model.stateStep                      = 0;
                            player->model.controlState                          = 0;
                        }
                    }
                }
            }

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_JumpBackward:
            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_JumpBackward, false);
                player->model.stateStep++;
            }

            // Jump backward.
            if ((player->model.anim.status >= ANIM_STATUS(HarryAnim_JumpBackward, false) &&
                 player->model.anim.status <= ANIM_STATUS(HarryAnim_JumpBackward, true)) &&
                player->model.anim.keyframeIdx < 245)
            {
                if (player->model.controlState == 0)
                {
                    player->fallSpeed = Q12(-2.0f);
                }

                player->model.controlState++;
                playerProps.moveDistance_126 = Q12(2.25f);
                D_800C4550                                                              = Q12(2.25f);
            }
            else
            {
                if (playerProps.moveDistance_126 != 0)
                {
                    playerProps.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2);
                    if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }

                D_800C4550 = playerProps.moveDistance_126;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_JumpBackward, true) && player->model.anim.keyframeIdx == 246)
            {
                if (player->position.vy < player->properties.player.positionY_EC)
                {
                    Player_ExtraStateSet(player, extra, PlayerState_FallBackward);

                    playerProps.moveDistance_126 = Q12(1.25f);
                }
                else
                {
                    g_SysWork.playerWork.extra.lowerBodyState = aimState;
                    player->model.stateStep                      = 0;
                    player->model.controlState                   = 0;
                    player->fallSpeed                                 = Q12(0.0f);
                }
            }

            playerProps.headingAngle_124 = Q12_ANGLE(180.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(180.0f);
            break;

        case PlayerLowerBodyState_Stumble:
            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= ((TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 2) / 3;
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 <= Q12(0.5f) &&
                playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) * 4;
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunForwardStumble, false);
                player->model.stateStep++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunForwardStumble, true) && player->model.anim.keyframeIdx == 179)
            {
                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                Player_MovementStateReset(player, PlayerLowerBodyState_Stumble);
            }
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            Player_StepWallStop_MovementCancel(player, 36, 37, 335, PlayerLowerBodyState_RunLeftWallStop, Q12_ANGLE(-90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            Player_StepWallStop_MovementCancel(player, 40, 41, 364, PlayerLowerBodyState_RunRightWallStop, Q12_ANGLE(90.0f), aimState);
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 2;
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 < Q12(0.3401f))
            {
                playerProps.moveDistance_126 = Q12(0.0f);
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunLeftStumble, false);
                player->model.stateStep++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunLeftStumble, true) && player->model.anim.keyframeIdx == 349)
            {
                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                Player_MovementStateReset(player, 15);
            }

            if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_None)
            {
                playerProps.headingAngle_124 = Q12_ANGLE(-90.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(-90.0f);
                break;
            }

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (playerProps.moveDistance_126 != Q12(0.0f))
            {
                playerProps.moveDistance_126 -= (TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f))) >> 2;
                if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                {
                    playerProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (D_800C45C8.field_14 < Q12(0.3401f))
            {
                playerProps.moveDistance_126 = Q12(0.0f);
            }

            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_RunRightStumble, false);
                player->model.stateStep++;
            }

            if (player->model.anim.status == ANIM_STATUS(HarryAnim_RunRightStumble, true) && player->model.anim.keyframeIdx == 378)
            {
                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_None;
                Player_MovementStateReset(player, 16);
            }

            if (g_SysWork.playerWork.extra.lowerBodyState == PlayerLowerBodyState_None)
            {
                playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
                g_Player_HeadingAngle                                             = Q12_ANGLE(0.0f);
                break;
            }

            playerProps.headingAngle_124 = Q12_ANGLE(90.0f);
            g_Player_HeadingAngle                                             = Q12_ANGLE(90.0f);
            break;

        case PlayerLowerBodyState_Attack:
            // If weapon is katana.
            if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Katana)
            {
                if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Katana, AttackInputType_Hold))
                {
                    if (playerProps.moveDistance_126 == Q12(0.0f) &&
                        (extra->model.anim.keyframeIdx >= D_800C44F0[D_800AF220].field_4 + 7))
                    {
                        playerProps.moveDistance_126 = Q12(5.0f);
                        g_Player_HeadingAngle                                                   = Q12_ANGLE(0.0f);
                    }
                }
                else if (player->model.stateStep == 0 && !g_Player_IsAttacking)
                {
                    playerProps.moveDistance_126 = Q12(5.0f);
                    g_Player_HeadingAngle                                                   = Q12_ANGLE(0.0f);
                }
            }

            if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Katana)
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, 0x444);
                    if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }
            else
            {
                if (playerProps.moveDistance_126 != Q12(0.0f))
                {
                    playerProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                    if ((playerProps.moveDistance_126 >> 16) & (1 << 0))
                    {
                        playerProps.moveDistance_126 = Q12(0.0f);
                    }
                }
            }

            if (g_SysWork.targetNpcIdx == NO_VALUE ||
                g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
                {
                    if (playerProps.flags_11C & PlayerFlag_Unk11)
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 - 12;
                            player->model.stateStep++;
                        }
                    }
                    else
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                            player->model.stateStep++;
                        }
                    }
                }
                else if (playerProps.flags_11C & PlayerFlag_Unk10)
                {
                    if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) ||
                        g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                            player->model.stateStep++;
                        }
                    }
                    else if (player->model.stateStep == 0)
                    {
                        player->model.anim.status = ANIM_STATUS(HarryAnim_HandgunAim, false);
                        player->model.stateStep++;
                    }

                    if (player->model.anim.keyframeIdx == D_800C44F0[0].field_6 || player->model.anim.keyframeIdx == D_800C44F0[5].field_6)
                    {
                        player->model.anim.status      = extra->model.anim.status;
                        player->model.anim.keyframeIdx = extra->model.anim.keyframeIdx;
                        player->model.anim.time         = extra->model.anim.time;
                        player->model.stateStep++;
                    }
                }
                else if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
                {
                    if (g_Player_RockDrill_DirectionAttack == 1)
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 + 2;
                            player->model.stateStep++;
                        }
                    }
                    else if (g_Player_RockDrill_DirectionAttack == NO_VALUE)
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 + 4;
                            player->model.stateStep++;
                        }
                    }
                    else
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                            player->model.stateStep++;
                        }
                    }
                }
                else
                {
                    if (extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk30, true))
                    {
                        player->model.anim.status      = extra->model.anim.status;
                        player->model.anim.keyframeIdx = extra->model.anim.keyframeIdx;
                        player->model.anim.time         = extra->model.anim.time;
                        player->model.stateStep++;
                    }
                    else if (g_Player_IsAttacking || extra->model.anim.status == ANIM_STATUS(HarryAnim_Unk29, true))
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7 - 4;
                            player->model.stateStep++;
                        }
                    }
                    else if (g_Player_IsShooting || extra->model.anim.status == ANIM_STATUS(HarryAnim_HandgunRecoil, true))
                    {
                        if (player->model.stateStep == 0)
                        {
                            player->model.anim.status = g_Player_EquippedWeaponInfo.animAttack_7;
                            player->model.stateStep++;
                        }
                    }
                }
            }
            else if (player->model.stateStep == 0)
            {
                player->model.anim.status = g_Player_EquippedWeaponInfo.animAttackHold_8 - 1;
                player->model.stateStep++;
            }

            if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) ||
                (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != EquippedWeaponId_SteelPipe &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != EquippedWeaponId_Hammer    &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != EquippedWeaponId_RockDrill &&
                 WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) != EquippedWeaponId_Katana))
            {
                if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status) && ANIM_STATUS_IS_ACTIVE(extra->model.anim.status) &&
                    (player->model.anim.status >= ANIM_STATUS(HarryAnim_Unk29, false) || player->model.anim.keyframeIdx == D_800C44F0[0].field_6))
                {
                    if (!g_Player_IsMovingForward)
                    {
                        if (g_Player_IsMovingBackward)
                        {
                            if (playerProps.moveDistance_126 == Q12(0.0f))
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkBackward;
                            }
                        }
                        else if (g_SysWork.playerWork.extra.state != PlayerState_Combat)
                        {
                            if (!g_Player_IsSteppingRightHold)
                            {
                                if (g_Player_IsSteppingLeftHold)
                                {
                                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimSidestepLeft;
                                }
                            }
                            else
                            {
                                g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimSidestepRight;
                            }
                        }
                    }
                    else
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkForward;
                    }

                    if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_Attack)
                    {
                        Player_MovementStateReset(player, PlayerLowerBodyState_Aim);
                        break;
                    }
                }
            }
            break;

        case PlayerLowerBodyState_Reload:
            if (player->model.stateStep == 0)
            {
                player->model.anim.status = ANIM_STATUS(HarryAnim_HandgunRecoil, false);
                player->model.stateStep++;
            }

            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status) && ANIM_STATUS_IS_ACTIVE(extra->model.anim.status) &&
                (player->model.anim.status >= ANIM_STATUS(HarryAnim_Unk29, false) || player->model.anim.keyframeIdx == D_800C44F0[0].field_6))
            {
                if (g_Player_IsMovingForward)
                {
                    g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkForward;
                }
                else if (g_Player_IsMovingBackward)
                {
                    if (playerProps.moveDistance_126 == Q12(0.0f))
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimWalkBackward;
                    }
                }
                else if (g_SysWork.playerWork.extra.state != PlayerState_Combat)
                {
                    if (g_Player_IsSteppingRightHold)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimSidestepRight;
                    }
                    else if (g_Player_IsSteppingLeftHold)
                    {
                        g_SysWork.playerWork.extra.lowerBodyState = PlayerLowerBodyState_AimSidestepLeft;
                    }
                }

                if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_Reload)
                {
                    Player_MovementStateReset(player, PlayerLowerBodyState_Aim);
                }
            }
            break;
    }

    func_8007B924(player, extra);
}

void func_8007B924(s_SubCharacter* player, s_PlayerExtra* extra) // 0x8007B924
{
    e_SfxId sfxId;
    s8      pitch0;
    s8      pitch1;

    func_8007FDE0(D_800C4590.field_14, &sfxId, &pitch0, &pitch1);

    // This entire conditional is the reason why movement stop working when removing this function call.
    if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_JumpBackward &&
        g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_Reload)
    {
        D_800C4550 = playerProps.moveDistance_126;
    }

    switch (g_SysWork.playerWork.extra.lowerBodyState)
    {
        case PlayerLowerBodyState_RunForward:
        case PlayerLowerBodyState_RunRight:
        case PlayerLowerBodyState_RunLeft:
            if (ANIM_STATUS_IS_ACTIVE(player->model.anim.status) && player->model.anim.status >= ANIM_STATUS(HarryAnim_RunForward, true))
            {
                player->properties.player.exhaustionTimer_FC += g_DeltaTime;
            }
            break;

        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_RunForwardWallStop:
        case PlayerLowerBodyState_Stumble:
        case PlayerLowerBodyState_RunLeftStumble:
        case PlayerLowerBodyState_RunRightStumble:
        case PlayerLowerBodyState_Aim:
            player->properties.player.exhaustionTimer_FC -= g_DeltaTime * 2;
            break;

        default:
            player->properties.player.exhaustionTimer_FC -= g_DeltaTime;
            break;
    }

    player->properties.player.exhaustionTimer_FC = CLAMP(player->properties.player.exhaustionTimer_FC, Q12(0.0f), Q12(35.0f));

    // Check if player has >=30% or <10% of health to determine exertion level.
    if (player->model.anim.status == ANIM_STATUS(HarryAnim_IdleExhausted, true))
    {
        if (player->properties.player.exhaustionTimer_FC < Q12(10.0f) &&
            player->health >= Q12(30.0f))
        {
            player->model.stateStep = 0;
            player->model.controlState     = 0;
            extra->model.stateStep = 0;
            extra->model.controlState     = 0;
        }
    }

    // Plays movement sounds.
    switch (g_SysWork.playerWork.extra.lowerBodyState)
    {
        case PlayerLowerBodyState_None:
        case PlayerLowerBodyState_Aim:
            // Turn right.
            if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_TurnRight)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_TurnRight, true), player, 204, 200, sfxId, pitch0);
            }
            // Turn left.
            else if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_TurnLeft)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_TurnLeft, true), player, 187, 191, sfxId, pitch0);
            }

            if ((playerProps.flags_11C & PlayerFlag_Moving) &&
                ((player->model.anim.status >= ANIM_STATUS(HarryAnim_Idle, true) &&
                  player->model.anim.status <= ANIM_STATUS(HarryAnim_IdleExhausted, false)) ||
                 player->model.anim.status == ANIM_STATUS(HarryAnim_HandgunAim, true)))
            {
                func_8005DD44(sfxId, &player->position, Q8_CLAMPED(0.095f), pitch0);

                player->properties.player.field_10C                        = pitch0 + 0x10;
                playerProps.flags_11C &= ~PlayerFlag_Moving;
            }

            if (player->model.anim.keyframeIdx == 246 &&
                !(playerProps.flags_11C & PlayerFlag_Unk5))
            {
                func_8005DD44(sfxId, &player->position, Q8(0.5f), pitch1);

                player->properties.player.field_10C                       = pitch1 + 0x20;
                playerProps.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        default:
            break;

        case PlayerLowerBodyState_WalkBackward:
        case PlayerLowerBodyState_AimWalkBackward:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_WalkBackward, true), player, 52, 63, sfxId, pitch0);
            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_AimWalkForward:
        case PlayerLowerBodyState_WalkForward:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_WalkForward, true), player, 18, 6, sfxId, pitch0);
            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForward:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForward, true), player, 31, 41, sfxId, pitch1))
            {
                player->properties.player.runTimer_F8++;
            }

            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepRight:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_SidestepRight, true), player, 118, 108, sfxId, pitch0);
            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_SidestepLeft:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_SidestepLeft, true), player, 93, 83, sfxId, pitch0);
            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRight:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRight, true), player, 145, 139, sfxId, pitch1))
            {
                player->properties.player.runTimer_F8++;
            }

            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeft:
            if (Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeft, true), player, 131, 125, sfxId, pitch1))
            {
                player->properties.player.runTimer_F8++;
            }

            playerProps.flags_11C |= PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunForwardWallStop:
            if (playerProps.flags_11C & PlayerFlag_WallStopRight)
            {
                if (player->model.anim.keyframeIdx < 152)
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true), player, 151, 154, sfxId, pitch1);
                }
                else
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true), player, 156, 154, sfxId, pitch1);
                }
            }
            else
            {
                if (player->model.anim.keyframeIdx < 162)
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true), player, 164, 161, sfxId, pitch1);
                }
                else
                {
                    Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true), player, 164, 166, sfxId, pitch1);
                }
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftWallStop:
            if (player->model.anim.keyframeIdx < 323)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftWallStop, true), player, 322, 324, sfxId, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftWallStop, true), player, 327, 324, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightWallStop:
            if (player->model.anim.keyframeIdx < 352)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightWallStop, true), player, 353, 351, sfxId, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightWallStop, true), player, 353, 356, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_Stumble:
            if (player->model.anim.keyframeIdx < 172)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardStumble, true), player, 171, 174, sfxId, pitch1);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunForwardStumble, true), player, 176, 174, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunLeftStumble:
            if (player->model.anim.keyframeIdx < 338)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), player, 337, 341, sfxId, pitch0);
            }
            else if (player->model.anim.keyframeIdx < 344)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), player, 343, 341, sfxId, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunLeftStumble, true), player, 356, 346, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_RunRightStumble:
            if (player->model.anim.keyframeIdx < 367)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), player, 366, 370, sfxId, pitch0);
            }
            else if (player->model.anim.keyframeIdx < 373)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), player, 372, 370, sfxId, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_RunRightStumble, true), player, 385, 375, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnLeft:
        case PlayerLowerBodyState_AimQuickTurnLeft:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_QuickTurnLeft, true), player, 222, 224, sfxId, pitch0);
            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_QuickTurnRight:
        case PlayerLowerBodyState_AimQuickTurnRight:
            Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_QuickTurnRight, true), player, 209, 211, sfxId, pitch0);
            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;

        case PlayerLowerBodyState_JumpBackward:
        case PlayerLowerBodyState_Unk31:
            if (player->model.anim.keyframeIdx < 243)
            {
                playerProps.flags_11C &= ~PlayerFlag_Unk5;
            }

            if (player->position.vy == D_800C4590.field_C)
            {
                Player_FootstepSfxPlay(ANIM_STATUS(HarryAnim_JumpBackward, true), player, 243, 245, sfxId, pitch1);
            }

            playerProps.flags_11C &= ~PlayerFlag_Moving;
            break;
    }
}

void func_8007C0D8(s_SubCharacter* player, s_PlayerExtra* extra, GsCOORDINATE2* coords) // 0x8007C0D8
{
    s_Collision coll;
    VECTOR3     offset;
    VECTOR3     sp30; // Q19.12
    VECTOR3     sp40; // Q19.12
    s16         temp_v0;
    q3_12       someAngle;
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

    g_Player_PrevPosition = player->position;

    Collision_Get(&coll, player->position.vx, player->position.vz);

    temp_s3 = Q12_MULT(player->moveSpeed, Math_Sin(player->headingAngle));
    temp_s2 = Q12_MULT(player->moveSpeed, Math_Cos(player->headingAngle));

    temp_s0 = Math_Cos(ABS(coll.field_4) >> 3);
    temp_v0 = Math_Cos(ABS(coll.field_6) >> 3);

    temp_v1 = Q12_MULT(Q12_MULT(temp_s3, temp_s0), temp_s0);
    someAngle = Q12_MULT(Q12_MULT(temp_s2, temp_v0), temp_v0);

    if (player->moveSpeed >= Q12(0.0f))
    {
        player->moveSpeed = SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }
    else
    {
        player->moveSpeed = -SquareRoot0(SQUARE(temp_v1) + SQUARE(someAngle));
    }

    temp_s0_2 = Q12_MULT_PRECISE(player->moveSpeed, g_DeltaTime);

    temp_v0_3 = player->headingAngle;
    temp      = temp_s0_2 + SHRT_MAX;
    temp_s2_2 = (temp > (SHRT_MAX * 2)) * 4;
    temp_s3_2 = temp_s2_2 >> 1;

    offset.vx = Q12_MULT_PRECISE((temp_s0_2 >> temp_s3_2), Math_Sin(temp_v0_3) >> temp_s3_2);
    offset.vx <<= temp_s2_2;

    offset.vz = Q12_MULT_PRECISE((temp_s0_2 >> temp_s3_2), Math_Cos(temp_v0_3) >> temp_s3_2);
    offset.vz <<= temp_s2_2;

    offset.vy = Q12_MULT_PRECISE(player->fallSpeed, g_DeltaTime);

    if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP1_S05)
    {
        offset.vx = offset.vx + D_800C45B0.vx;
        sp30.vx = offset.vx;
        offset.vz = offset.vz + D_800C45B0.vz;
        sp30.vz = offset.vz;
    }

    Collision_WallDetect(&D_800C4590, &offset, player);

    if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP1_S05)
    {
        if (D_800C45B0.vx != 0 && (DIFF_SIGN(sp30.vx, D_800C4590.offset_0.vx) || abs(sp30.vx) >= ABS(D_800C4590.offset_0.vx)))
        {
            sp40.vx = sp30.vx - D_800C4590.offset_0.vx;
        }
        else
        {
            sp40.vx = Q12(0.0f);
        }

        if (D_800C45B0.vz != 0 && (DIFF_SIGN(sp30.vz, D_800C4590.offset_0.vz) || abs(sp30.vz) >= ABS(D_800C4590.offset_0.vz)))
        {
            sp40.vz = sp30.vz - D_800C4590.offset_0.vz;
        }
        else
        {
            sp40.vz = Q12(0.0f);
        }

        g_MapOverlayHeader.func_158(-sp40.vx, -sp40.vz);
    }

    player->position.vx += D_800C4590.offset_0.vx;
    player->position.vy += D_800C4590.offset_0.vy;
    player->position.vz += D_800C4590.offset_0.vz;

    if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_RunForward ||
        g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_RunRight ||
        g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_RunLeft)
    {
        player->properties.player.runTimer_108 += SquareRoot0(SQUARE(D_800C4590.offset_0.vx) +
                                                                SQUARE(D_800C4590.offset_0.vy) +
                                                                SQUARE(D_800C4590.offset_0.vz));
    }
    else
    {
        player->properties.player.runTimer_108 = 0;
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP1_S00 && g_SavegamePtr->mapRoomIdx_A5 == 13)
    {
        D_800C4590.field_C = 0;
    }

    if (D_800C4590.field_14 == 0)
    {
        D_800C4590.field_C = player->properties.player.positionY_EC;
    }

    if (player->position.vy > D_800C4590.field_C)
    {
        player->position.vy = D_800C4590.field_C;
        player->fallSpeed   = Q12(0.0f);
    }

    someAngle = Q12_ANGLE_NORM_U(ratan2(player->position.vx - g_Player_PrevPosition.vx, player->position.vz - g_Player_PrevPosition.vz) + Q12_ANGLE(360.0f));

    if (!(g_SysWork.playerWork.extra.state >= PlayerState_FallForward && g_SysWork.playerWork.extra.state < PlayerState_KickEnemy))
    {
        if (!g_Player_IsInWalkToRunTransition)
        {
            posY = player->position.vy;
            if ((D_800C4590.field_C - posY) >= Q12(0.65f))
            {
                if (ABS_DIFF(player->rotation.vy, someAngle) >= Q12_ANGLE(90.0f) &&
                    ABS_DIFF(player->rotation.vy, someAngle) <  Q12_ANGLE(270.0f))
                {
                    if (g_SysWork.playerWork.extra.lowerBodyState != PlayerLowerBodyState_JumpBackward)
                    {
                        Player_ExtraStateSet(player, extra, PlayerState_FallBackward);
                    }
                }
                else
                {
                    Player_ExtraStateSet(player, extra, PlayerState_FallForward);
                }

                g_SysWork.playerCombat.isAiming = false;
            }
        }
    }

    player->properties.player.positionY_EC = D_800C4590.field_C;
    coords->coord.t[0]                        = Q12_TO_Q8(player->position.vx);
    coords->coord.t[1]                        = Q12_TO_Q8(player->position.vy);
    coords->coord.t[2]                        = Q12_TO_Q8(player->position.vz);
}

void Player_ReceiveDamage(s_SubCharacter* player, s_PlayerExtra* extra) // 0x8007C800
{
    q3_12 headingAngle;
    q4_12 enemyRotY;
    s32   i;
    s32   sfxId;
    s32   angleState;

    // Set damage SFX according to something.
    sfxId = Sfx_Unk1326;
    if (player->attackReceived != NO_VALUE)
    {
        switch (D_800AD4C8[player->attackReceived].field_11)
        {
            case 2:
                sfxId = Sfx_Unk1327;
                break;

            case 4:
                sfxId = Sfx_Unk1328;
                break;

            case 5:
                sfxId = Sfx_Unk1329;
                break;

            case 0:
                break;
        }
    }

    if (g_Player_DisableControl || g_Player_DisableDamage)
    {
        player->damage.amount = Q12(0.0f);
        return;
    }

    switch (g_SysWork.playerWork.extra.state)
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
            if (player->damage.amount != Q12(0.0f) && !(playerProps.flags_11C & PlayerFlag_DamageReceived))
            {
                playerProps.flags_11C |= PlayerFlag_DamageReceived;
                func_8005DC1C(sfxId, &player->position, Q8(1.0f / 8.0f), 0);
                player->properties.player.field_10C = 64;
            }

            if (player->damage.amount == Q12(0.0f))
            {
                playerProps.flags_11C &= ~PlayerFlag_DamageReceived;
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
            player->damage.position.vz = Q12(0.0f);
            player->damage.position.vy = Q12(0.0f);
            player->damage.position.vx = Q12(0.0f);

            if (player->attackReceived == 47)
            {
                g_SysWork.playerWork.player.field_D4.field_2 = Q12(0.0f);
                Player_ExtraStateSet(player, extra, PlayerState_InstantDeath);
                return;
            }

            if (player->attackReceived >= 68 &&
                player->attackReceived <  70)
            {
                player->damage.amount = Q12(0.0f);
            }
            break;

        default:
            if (g_Player_IsInWalkToRunTransition)
            {
                D_800C4560 = player->attackReceived;
                return;
            }

            if (D_800C4560 != NO_VALUE)
            {
                player->attackReceived = D_800C4560;
                D_800C4560 = NO_VALUE;
            }

            if (player->attackReceived <= 0)
            {
                break;
            }

            g_SysWork.targetNpcIdx                  = NO_VALUE;
            g_SysWork.playerCombat.weaponAttack = (g_SavegamePtr->equippedWeapon_AA == InvItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA - InvItemId_KitchenKnife);

            if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
            {
                func_8004C564(2, 3);
            }

            if (g_SysWork.playerWork.extra.state >= PlayerState_FallForward &&
                g_SysWork.playerWork.extra.state <  PlayerState_Unk7)
            {
                g_SysWork.playerWork.player.field_C8.field_0   = Q12(-1.6f);
                g_SysWork.playerWork.player.field_C8.field_2   = Q12(0.0f);
                g_SysWork.playerWork.player.field_C8.field_6   = Q12(-1.1f);
                g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
                g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
            }

            enemyRotY = g_SysWork.npcs[player->field_40].rotation.vy;
            if (player->attackReceived >= 64 && player->attackReceived < 66)
            {
                enemyRotY -= Q12_ANGLE(90.0f);
            }
            else if (player->attackReceived == 69)
            {
                enemyRotY = Q12_ANGLE(90.0f);
            }
            else if (player->attackReceived == 68)
            {
                enemyRotY = player->damage.position.vy;
            }

            enemyRotY = Q12_ANGLE_NORM_U((enemyRotY - player->rotation.vy) + Q12_ANGLE(360.0f));

            switch (player->attackReceived)
            {
                case 67:
                    Player_ExtraStateSet(player, extra, PlayerState_Unk7);
                    break;

                case 63:
                    playerProps.moveDistance_126 = Q12(1.5f);
                    Math_ShortestAngleGet(player->rotation.vy, g_SysWork.npcs[0].rotation.vy, &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                    if (enemyRotY >= Q12_ANGLE(90.0f) && enemyRotY < Q12_ANGLE(270.0f))
                    {
                        Player_ExtraStateSet(player, extra, PlayerState_DamageThrownFront);
                    }
                    else
                    {
                        Player_ExtraStateSet(player, extra, PlayerState_DamageThrownBack);
                    }
                    break;

                case 60:
                case 62:
                    player->damage.amount = Q12(10.0f);
                    Player_ExtraStateSet(player, extra, PlayerState_DamageHead);
                    break;

                case 41:
                case 42:
                    Player_ExtraStateSet(player, extra, PlayerState_DamageHead);
                    break;

                case 49: // Leg grab.
                case 54: // Romper grab.
                case 56: // Torso grab.
                case 66:
                    if (enemyRotY >= Q12_ANGLE(90.0f) &&
                        enemyRotY <  Q12_ANGLE(270.0f))
                    {
                        g_SysWork.npcIdxs[0] = player->field_40;

                        switch (player->attackReceived)
                        {
                            case 54:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabPinnedFrontStart);
                                break;

                            case 45:
                            case 56:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabTorsoFront);
                                break;

                            case 49:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabLegsFront);
                                break;

                            case 66:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabNeckFront);
                                break;

                        }
                    }
                    else
                    {
                        g_SysWork.npcIdxs[1] = player->field_40;

                        switch (player->attackReceived)
                        {
                            case 54:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabPinnedBackStart);
                                break;

                            case 45:
                            case 56:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabTorsoBack);
                                break;

                            case 49:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabLegsBack);
                                break;

                            case 66:
                                Player_ExtraStateSet(player, extra, PlayerState_EnemyGrabNeckBack);
                                break;
                        }
                    }
                    break;

                case 47:
                    player->health        = NO_VALUE;
                    player->field_D4.field_2 = Q12(0.0f);
                    Player_ExtraStateSet(player, extra, PlayerState_InstantDeath);
                    return;

                case 69:
                    playerProps.moveDistance_126 = Q12(1.6f);
                    Math_ShortestAngleGet(player->rotation.vy, Q12_ANGLE(90.0f), &headingAngle);
                    g_Player_HeadingAngle = headingAngle;

                case 68:
                    if (player->attackReceived != 69)
                    {
                        playerProps.moveDistance_126 = Q12(4.0f);
                        Math_ShortestAngleGet(player->rotation.vy, (s16)player->damage.position.vy, &headingAngle);
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

                    Player_ExtraStateSet(player, extra, angleState);
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

                    Player_ExtraStateSet(player, extra, angleState);
                    break;
            }

            if ((u32)g_SysWork.playerWork.extra.state >= PlayerState_FallForward)
            {
                player->properties.player.afkTimer_E8                     = Q12(0.0f);
                player->properties.player.field_F4                        = 0;
                playerProps.flags_11C &= ~PlayerFlag_Unk12;
                g_SysWork.playerCombat.isAiming                   = false;
                playerProps.flags_11C &= ~PlayerFlag_Unk9;
                player->field_44.field_0                                     = NO_VALUE;
            }
            break;
    }

    if (g_SysWork.playerWork.extra.state == PlayerState_Death)
    {
        Chara_DamageClear(player);
        return;
    }

    if (player->damage.amount != Q12(0.0f))
    {
        playerProps.flags_11C &= ~PlayerFlag_Unk2;
        if (!(playerProps.flags_11C & PlayerFlag_DamageReceived))
        {
            func_8005DC1C(sfxId, &player->position, Q8(1.0f / 8.0f), 0);
            playerProps.flags_11C |= PlayerFlag_DamageReceived;
            player->properties.player.field_10C = 0x40;
        }

        if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP0_S00)
        {
            player->health -= player->damage.amount * 2;
        }
        else
        {
            switch (g_SavegamePtr->gameDifficulty_260)
            {
                case GameDifficulty_Easy:
                    player->damage.amount = (player->damage.amount * 3) >> 2; // `/ 4`.
                    break;

                case GameDifficulty_Hard:
                    player->damage.amount = (player->damage.amount * 6) >> 2; // `/ 4`.
                    break;
            }

            player->health -= player->damage.amount;
        }

        if (player->health < Q12(0.0f))
        {
            player->health = NO_VALUE;
            g_Player_IsDead  = true;
        }

        func_800893D0(player->damage.amount);
        player->damage.amount = Q12(0.0f);
    }

    if (player->health <= Q12(0.0f) && g_SysWork.playerWork.extra.state != PlayerState_Death &&
        g_SysWork.playerWork.extra.state != PlayerState_Unk36 && g_SysWork.playerWork.extra.state != PlayerState_EnemyGrabPinnedFront &&
        g_SysWork.playerWork.extra.state != PlayerState_EnemyGrabPinnedBack && g_SysWork.playerWork.extra.state != PlayerState_OnFloorFront &&
        g_SysWork.playerWork.extra.state != PlayerState_OnFloorBehind && !g_Player_IsInWalkToRunTransition)
    {
        player->field_40                     = NO_VALUE;
        g_SavegamePtr->healthSaturation_238 = Q12(0.0f);

        for (i = 0; i < 4; i++)
        {
            g_SysWork.npcIdxs[i] = NO_VALUE;
        }

        if (player->attackReceived == 66)
        {
            Player_ExtraStateSet(player, extra, PlayerState_Unk36);
        }
        else
        {
            Player_ExtraStateSet(player, extra, PlayerState_Death);
        }
    }
}

void func_8007D090(s_SubCharacter* player, s_PlayerExtra* extra, GsCOORDINATE2* coords) // 0x8007D090
{
    #define FLEX_ROT_X_RANGE Q12_ANGLE(56.25f)
    #define FLEX_ROT_Y_RANGE Q12_ANGLE(33.75f)

    q19_12 flexRotStep;
    s32    temp_v0;
    q19_12 flexRotMax;
    q19_12 var_a2;
    s32    var_a3;
    q19_12 var_v1;

    switch (g_SysWork.playerWork.extra.state)
    {
        case PlayerState_Combat:
            switch (g_SysWork.playerCombat.weaponAttack)
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

            if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_Reload ||
                g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                g_Player_FlexRotationY = Q12_ANGLE(0.0f);
            }
            else
            {
                g_Player_FlexRotationX = playerProps.field_122 - Q12_ANGLE(90.0f);

                if (ABS(player->field_2A - player->rotation.vy) > Q12_ANGLE(180.0f))
                {
                    if (player->field_2A > player->rotation.vy)
                    {
                        g_Player_FlexRotationY = -Q12_ANGLE_NORM_U((player->rotation.vy + Q12_ANGLE(360.0f)) - player->field_2A);
                    }
                    else
                    {
                        g_Player_FlexRotationY = Q12_ANGLE_NORM_U((player->field_2A + Q12_ANGLE(360.0f)) - player->rotation.vy);
                    }
                }
                else
                {
                    g_Player_FlexRotationY = player->field_2A - player->rotation.vy;
                }

                if (player->properties.player.field_100 != 0 || g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimStartTargetLock ||
                    g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_AimTargetLockSwitch)
                {
                    if (playerProps.flags_11C & PlayerFlag_Unk8)
                    {
                        var_v1 = Q12_ANGLE(0.0f);
                    }
                    else
                    {
                        var_v1 = var_a3;
                    }

                    if (player->properties.player.field_F4 != 0)
                    {
                        flexRotStep = player->properties.player.field_F4 - g_Player_FlexRotationX;
                        if (g_Player_FlexRotationX < player->properties.player.field_F4)
                        {
                            flexRotMax = player->properties.player.field_100 * TIMESTEP_SCALE_30_FPS(g_DeltaTime, var_a2 + player->properties.player.field_100);
                            if (flexRotMax < flexRotStep)
                            {
                                g_Player_FlexRotationX = player->properties.player.field_F4 - flexRotMax;
                            }
                        }
                        else
                        {
                            flexRotMax = -(player->properties.player.field_100 * TIMESTEP_SCALE_30_FPS(g_DeltaTime, var_a2 + player->properties.player.field_100));
                            if (flexRotStep < flexRotMax)
                            {
                                g_Player_FlexRotationX = player->properties.player.field_F4 - flexRotMax;
                            }
                        }
                    }
                    else
                    {
                        if (player->properties.player.field_100 < var_v1)
                        {
                            g_Player_FlexRotationY = Q12_ANGLE(0.0f);
                            g_Player_FlexRotationX = Q12_ANGLE(0.0f);
                        }
                        else
                        {
                            temp_v0     = player->properties.player.field_100 + 1;
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
            if (g_SysWork.playerWork.extra.state >= PlayerState_Unk52 &&
                g_SysWork.playerWork.extra.state <  PlayerState_Unk59)
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

    if (g_SysWork.enablePlayerMatchAnim && g_SysWork.playerWork.extra.state < PlayerState_Unk58)
    {
        func_80044F14(&g_SysWork.playerBoneCoords[HarryBone_RightUpperArm], Q12_ANGLE(0.0f),   Q12_ANGLE(63.3f), Q12_ANGLE(-8.8f));
        func_80044F14(&g_SysWork.playerBoneCoords[HarryBone_RightForearm],  Q12_ANGLE(-14.1f), Q12_ANGLE(22.5f), Q12_ANGLE(-30.8f));
        func_80044F14(&g_SysWork.playerBoneCoords[HarryBone_RightHand],     Q12_ANGLE(13.2f),  Q12_ANGLE(0.0f),  Q12_ANGLE(0.0f));
    }
}

void Player_FlexRotationYReset(void) // 0x8007D6E0
{
    g_Player_FlexRotationY = Q12_ANGLE(0.1f);
}

s32 func_8007D6F0(s_SubCharacter* player, s_800C45C8* arg1) // 0x8007D6F0
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

    temp_s0  = playerProps.moveDistance_126 >> 3;
    temp_s0 += Q12(0.75f);
    temp_s1  = Q12(-0.6f);
    temp_s1 -= playerProps.moveDistance_126 >> 4;

    temp_s4 = Q12_MULT(Math_Cos(player->headingAngle), Q12(0.2f)); // Maybe meters?
    temp_s3 = Q12_MULT(Math_Sin(player->headingAngle), Q12(0.2f)); // Maybe meters?
    temp_s5 = Q12_MULT(temp_s0, Math_Sin(player->headingAngle));
    temp_lo = Q12_MULT(temp_s0, Math_Cos(player->headingAngle));

    temp_s1 -= Q12(0.4f);

    vecs[0].vy = player->position.vy + temp_s1;
    vecs[0].vx = (player->position.vx + temp_s4) + temp_s5;

    vecs[0].vz = (player->position.vz - temp_s3) + temp_lo;
    vecs[2].vy = player->position.vy - Q12(0.4f);
    vecs[2].vx = player->position.vx + temp_s4;
    vecs[2].vz = player->position.vz - temp_s3;

    ret[0] = Ray_LineCheck(&rays[0], &vecs[2], &vecs[0]);

    if (ret[0])
    {
        vecs[1].vy = vecs[0].vy;
        vecs[1].vx = (player->position.vx - temp_s4) + temp_s5;
        vecs[1].vz = (player->position.vz + temp_s3) + temp_lo;
        vecs[3].vy = vecs[2].vy;
        vecs[3].vx = player->position.vx - temp_s4;
        vecs[3].vz = player->position.vz + temp_s3;

        ret[1] = Ray_LineCheck(&rays[1], &vecs[3], &vecs[1]);

        if (ret[1])
        {
            arg1->field_14 = (rays[0].field_14 + rays[1].field_14) >> 1;
            arg1->field_1  = rays[0].field_1;

            angle      = Q12_ANGLE_NORM_U(((rays[0].field_1C + rays[1].field_1C) >> 1) + Q12_ANGLE(360.0f));
            angleDelta = ABS_DIFF(angle, player->headingAngle);

            if (angleDelta > Q12_ANGLE(160.0f) && angleDelta < Q12_ANGLE(200.0f))
            {
                if ((player->position.vy - Q12(1.3f)) < rays[0].field_18 || rays[0].field_1 == 0 || rays[0].field_1 == 12)
                {
                    if ((player->position.vy - Q12(0.3f)) >= rays[0].field_18)
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

void Player_CombatUpdate(s_SubCharacter* player, GsCOORDINATE2* coord) // 0x8007D970
{
    VECTOR                sp20; // Q19.12
    VECTOR                sp30; // Q19.12
    VECTOR                sp40; // Q19.12
    MATRIX                sp50;
    VECTOR                sp70; // Q23.8
    VECTOR                sp80; // Q23.8
    SVECTOR               sp90;
    DVECTOR               unkRot;
    s32                   temp_s0;
    q23_8                 temp_v0_5;
    q23_8                 temp_v0_6;
    q3_12                 unkAngle;
    VECTOR*               vec;  // Q19.12
    VECTOR*               vec2; // Q19.12
    VECTOR*               vec3; // Q19.12
    s_Model*              model;
    static s32            __pad_bss_800C44D8[2];
    static VECTOR3        D_800C44E0;
    static s32            __pad_bss_800C44EC;

    #define playerExtra  g_SysWork.playerWork.extra
    #define playerCombat g_SysWork.playerCombat

    model = &playerExtra.model;

    if (playerExtra.lowerBodyState < PlayerLowerBodyState_Aim)
    {
        vec     = &playerCombat.field_0;
        vec->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[0]);
        vec->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[1]);
        vec->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[2]);
    }
    else
    {
        switch (playerCombat.weaponAttack)
        {
            case NO_VALUE:
            case 8:
            case 9:
                vec2     = &playerCombat.field_0;
                vec2->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[0]);
                vec2->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[1]);
                vec2->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightFoot].workm.t[2]);
                break;

            default:
                vec3     = &playerCombat.field_0;
                vec3->vx = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightHand].workm.t[0]);
                vec3->vy = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightHand].workm.t[1]);
                vec3->vz = Q8_TO_Q12(g_SysWork.playerBoneCoords[HarryBone_RightHand].workm.t[2]);
                break;
        }
    }

    if (playerProps.gasWeaponPowerTimer_114 != Q12(0.0f))
    {
        g_SysWork.timer_2C++;

        if (playerProps.moveDistance_126 >= Q12(3.1739f) ||
            (g_SysWork.timer_2C & (1 << 0)))
        {
            func_8006342C(g_SavegamePtr->equippedWeapon_AA - InvItemId_KitchenKnife,
                          Q12_ANGLE(0.0f), Q12_ANGLE(0.0f), coord);
        }
    }

    if (!(playerExtra.state >= PlayerState_Unk7 && playerExtra.state < PlayerState_Unk51) &&
        ((playerExtra.state >= PlayerState_None && playerExtra.state < PlayerState_Idle) ||
        playerExtra.state == PlayerState_KickEnemy ||
        playerExtra.state == PlayerState_StompEnemy))
    {
        if (playerCombat.weaponAttack >= EquippedWeaponId_Handgun &&
            playerExtra.lowerBodyState >= PlayerLowerBodyState_Aim)
        {
            if (playerExtra.state == PlayerState_Combat && g_Player_TargetNpcIdx != NO_VALUE)
            {
                unkRot.vx = ratan2((g_SysWork.npcs[g_Player_TargetNpcIdx].position.vx + g_SysWork.npcs[g_Player_TargetNpcIdx].field_D8.offsetX_0) - playerCombat.field_0.vx,
                                 (g_SysWork.npcs[g_Player_TargetNpcIdx].position.vz + g_SysWork.npcs[g_Player_TargetNpcIdx].field_D8.offsetZ_2) - playerCombat.field_0.vz);
            }
            else
            {
                // @hack Required for match.
                do { player->field_2A = player->rotation.vy; } while (false);

                unkRot.vx = player->field_2A;
            }

            unkRot.vy  = playerProps.field_122;
            unkAngle = unkRot.vy;
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

            if (player->field_44.field_0 > 0)
            {
                func_8006342C(playerCombat.weaponAttack, unkAngle, unkRot.vx, coord);
            }
        }
        else
        {
            switch (playerCombat.weaponAttack)
            {
                case NO_VALUE:
                case EquippedWeaponId_Kick:
                case EquippedWeaponId_Stomp:
                    Math_SetSVectorFast(&sp90, 0, 60, 134);
                    Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    break;

                default:
                    if (playerExtra.lowerBodyState < PlayerLowerBodyState_Aim)
                    {
                        Math_SetSVectorFast(&sp90, 0, 60, 134);
                        Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    }
                    else
                    {
                        switch (WEAPON_ATTACK_ID_GET(playerCombat.weaponAttack))
                        {
                            case EquippedWeaponId_KitchenKnife:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF),
                                                        -FP_MULTIPLY(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x4B, Q12_SHIFT - 1),
                                                         Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x4B) >> 1);
                                break;

                            case EquippedWeaponId_SteelPipe:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF),
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xE1) >> 1),
                                                         FP_MULTIPLY(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x2D, Q12_SHIFT - 2));
                                break;

                            case EquippedWeaponId_Chainsaw:
                                Math_SetSVectorFastSum(&sp90, Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF) >> 1,
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x87) >> 1),
                                                         (Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x1EF) >> 1));
                                break;

                            case EquippedWeaponId_RockDrill:
                                Math_SetSVectorFastSum(&sp90, 0,
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x2D)),
                                                         FP_MULTIPLY(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x2D, Q12_SHIFT - 2));
                                break;

                            case EquippedWeaponId_Axe:
                                Math_SetSVectorFastSum(&sp90, 0,
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x2C1) >> 1),
                                                         Q12_MULT((u32)D_800AD4C8[playerCombat.weaponAttack].field_0, 0xC3));
                                break;

                            case EquippedWeaponId_Hammer:
                                Math_SetSVectorFastSum(&sp90, (Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF) >> 1),
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x69)),
                                                         Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x13B) >> 1);
                                break;

                            case EquippedWeaponId_Katana:
                                Math_SetSVectorFastSum(&sp90, (Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF) >> 1),
                                                        -(Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0x13B) >> 1),
                                                         Q12_MULT(D_800AD4C8[playerCombat.weaponAttack].field_0, 0xF));
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

            temp_v0_5 = Q12_TO_Q8(playerCombat.field_0.vx) - sp70.vx;
            temp_v0_6 = Q12_TO_Q8(playerCombat.field_0.vz) - sp70.vz;
            temp_s0   = SquareRoot0(SQUARE(temp_v0_5) + SQUARE(temp_v0_6));

            unkRot.vx = ratan2(sp70.vx - Q12_TO_Q8(playerCombat.field_0.vx),
                               sp70.vz - Q12_TO_Q8(playerCombat.field_0.vz));
            unkRot.vy = ratan2(temp_s0, sp70.vy - Q12_TO_Q8(playerCombat.field_0.vy));
        }

        if (playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap) &&
            playerCombat.isAiming &&
            model->anim.status >= ANIM_STATUS(HarryAnim_HandgunAim, true) && model->anim.keyframeIdx >= 574)
        {
            if (playerExtra.state < PlayerState_Idle)
            {
                if (playerExtra.state == PlayerState_None && g_SysWork.targetNpcIdx != NO_VALUE)
                {
                    g_SysWork.targetNpcIdx = NO_VALUE;
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

                if (g_GameWork.config.optExtraAutoAiming_2C)
                {
                    unkRot.vx = player->field_2A;
                }

                g_MapOverlayHeader.particleHyperBlasterBeamDraw_178(&sp20, &unkRot.vx, &unkRot.vy);
            }
        }

        if (playerExtra.state < PlayerState_Idle)
        {
            if ((playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) &&
                 model->anim.keyframeIdx >= 572 && model->anim.keyframeIdx < 584) ||
                (playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) &&
                 player->model.anim.keyframeIdx >= 577 && model->anim.keyframeIdx < 583))
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

        if (playerExtra.upperBodyState != PlayerUpperBodyState_AimStop)
        {
            if (playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                if (D_800C4554 != NO_VALUE || D_800C4556 != D_800C4554)
                {
                    func_8008A0E4(player->field_44.field_0, playerCombat.weaponAttack, player, &D_800C44E0, &g_SysWork.npcs[0], D_800C4556, D_800C4554);
                }
                else
                {
                    func_8008A0E4(player->field_44.field_0, playerCombat.weaponAttack, player, &D_800C44E0, &g_SysWork.npcs[0], unkRot.vx, unkRot.vy);
                }
            }
            else
            {
                func_8008A0E4(player->field_44.field_0, playerCombat.weaponAttack, player, &playerCombat.field_0, &g_SysWork.npcs[0], unkRot.vx, unkRot.vy);
            }

            D_800C42D2 = unkRot.vx;
            D_800C42D0 = unkRot.vy;
        }
    }

    D_800C44E0 = playerCombat.field_0;

    #undef playerExtra
    #undef playerCombat
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
    g_SavegamePtr->equippedWeapon_AA     = InvItemId_Unequipped;
    g_SavegamePtr->healthSaturation_238  = Q12(0.0f);
    g_SavegamePtr->gameplayTimer_250     = Q12(0.0f);
    g_SavegamePtr->runDistance_254       = Q12(0.0f);
    g_SavegamePtr->walkDistance_258      = Q12(0.0f);
    g_SavegamePtr->pickedUpItemCount_23C = 0;
    g_SavegamePtr->clearGameCount_24A    = 0;
    g_SavegamePtr->add290Hours_25C_1     = 0;

    #undef DEFAULT_INV_SLOT_COUNT
}

void Game_PlayerInfoInit(void) // 0x8007E5AC
{
    s32      i;
    u32      itemGroupId;
    s_Model* model;
    s_Model* extraModel;

    SysWork_SavegameReadPlayer();

    g_SysWork.playerWork.player.model.charaId  = Chara_Harry;
    g_SysWork.playerWork.extra.model.charaId = Chara_Harry;
    g_SysWork.playerWork.player.field_D4.radius_0  = Q12(0.3f);
    g_SysWork.playerWork.player.field_D4.field_2   = Q12(0.23f);

    extraModel = &g_SysWork.playerWork.player.model;
    model      = &g_SysWork.playerWork.extra.model;

    g_SysWork.enablePlayerMatchAnim = false;

    extraModel->anim.flags |= AnimFlag_Unlocked | AnimFlag_Visible;
    model->anim.flags      |= AnimFlag_Unlocked | AnimFlag_Visible;

    g_SysWork.playerWork.player.field_E1_0 = 3;
    g_Inventory_EquippedItem                    = g_SavegamePtr->equippedWeapon_AA;

    itemGroupId = INVENTORY_ITEM_GROUP(g_SavegamePtr->equippedWeapon_AA);

    // Assign weapon that the player was holding when saving.
    if (itemGroupId == InvItemGroup_MeleeWeapons || itemGroupId == InvItemGroup_GunWeapons)
    {
        for (i = 0; g_SavegamePtr->items_0[i].id_0 != g_SavegamePtr->equippedWeapon_AA && i < INVENTORY_ITEM_COUNT_MAX; i++);

        g_SysWork.playerCombat.weaponAttack        = g_SavegamePtr->equippedWeapon_AA + InvItemId_KitchenKnife;
        g_SysWork.playerCombat.currentWeaponAmmo  = g_SavegamePtr->items_0[i].count_1;
        g_SysWork.playerCombat.weaponInventoryIdx = i;

        if (itemGroupId == InvItemGroup_MeleeWeapons)
        {
            g_SysWork.playerCombat.totalWeaponAmmo = 0;
        }
        else
        {
            for (i = 0;
                 g_SavegamePtr->items_0[i].id_0 != (g_SavegamePtr->equippedWeapon_AA + InvItemId_HealthDrink) && i < INVENTORY_ITEM_COUNT_MAX;
                 i++);

            if (i == INVENTORY_ITEM_COUNT_MAX)
            {
                g_SysWork.playerCombat.totalWeaponAmmo = 0;
            }
            else
            {
                g_SysWork.playerCombat.totalWeaponAmmo = (s8)g_SavegamePtr->items_0[i].count_1;
            }
        }
    }
    else
    {
        g_SysWork.playerCombat.weaponAttack        = NO_VALUE;
        g_SysWork.playerCombat.currentWeaponAmmo  = 0;
        g_SysWork.playerCombat.totalWeaponAmmo    = 0;
        g_SysWork.playerCombat.weaponInventoryIdx = NO_VALUE;
    }

    g_SysWork.playerCombat.isAiming = false;
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
    g_GameWork.mapAnimIdx   = NO_VALUE;

    g_SavegamePtr->inventorySlotCount_AB       = CLAMP(g_SavegamePtr->inventorySlotCount_AB, INVENTORY_ITEM_COUNT_MAX / 5, INVENTORY_ITEM_COUNT_MAX);
    g_SysWork.playerWork.player.health = CLAMP(g_SysWork.playerWork.player.health, 1, Q12(100.0f));
}

void func_8007E860(void) // 0x8007E860
{
    s32 i;
    s32 startIdx;

    for (i = 0; i < 8; i++)
    {
        startIdx                            = 92;
        HARRY_BASE_ANIM_INFOS[startIdx + i] = g_MapOverlayHeader.harryMapAnimInfos_34[i + 16];
    }
}

void func_8007E8C0(void) // 0x8007E8C0
{
    s32             i;
    s_AnimInfo*     animInfos;
    s_SubCharacter* chara;

    chara     = &g_SysWork.playerWork.player;
    animInfos = g_MapOverlayHeader.harryMapAnimInfos_34;

    for (i = 76; animInfos->playbackFunc != NULL; i++, animInfos++)
    {
        HARRY_BASE_ANIM_INFOS[i] = g_MapOverlayHeader.harryMapAnimInfos_34[i - 76];
    }

    if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP0_S01)
    {
        g_SysWork.enablePlayerMatchAnim = false;
    }

    chara->properties.player.exhaustionTimer_FC      = Q12(0.0f);
    g_SysWork.playerWork.player.field_C8.field_0   = Q12(-1.6f);
    g_SysWork.playerWork.player.field_C8.field_2   = Q12(0.0f);
    g_SysWork.playerWork.player.field_C8.field_6   = Q12(-1.1f);
    g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
    g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
    g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
    g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
    chara->field_D4.radius_0                            = Q12(0.3f);
    chara->field_D4.field_2                             = Q12(0.23f);
    g_GameWork.mapAnimIdx                           = NO_VALUE;

    func_8007E9C4();
}

void func_8007E9C4(void) // 0x8007E9C4
{
    s_SubCharacter* chara;

    chara = &g_SysWork.playerWork.player;

    g_Player_IsInWalkToRunTransition                         = false;
    g_SysWork.playerWork.extra.state               = PlayerState_None;
    g_SysWork.playerWork.extra.upperBodyState      = PlayerUpperBodyState_None;
    g_SysWork.playerWork.extra.lowerBodyState      = PlayerLowerBodyState_None;
    g_SysWork.playerWork.extra.model.stateStep    = 0;
    g_SysWork.playerWork.extra.model.controlState = 0;

    chara->model.stateStep            = 0;
    chara->model.controlState         = 0;
    g_SysWork.playerStopFlags        = PlayerStopFlag_None;
    g_Player_FlexRotationY                = Q12_ANGLE(0.0f);
    g_Player_FlexRotationX                = Q12_ANGLE(0.0f);
    D_800C4560                            = NO_VALUE;
    g_SysWork.playerCombat.isAiming = false;

    func_8004C564(0, NO_VALUE);

    chara->field_2A         = Q12_ANGLE(90.0f);
    g_Player_IsDead         = false;
    g_Player_DisableDamage  = false;
    g_Player_HasActionInput = false;
    g_Player_HasMoveInput   = false;
    g_Player_IsShooting     = false;
    g_Player_IsAttacking    = false;

    chara->properties.player.afkTimer_E8      = Q12(0.0f);
    chara->properties.player.field_F4         = 0;
    chara->properties.player.runTimer_F8      = Q12(0.0f);
    chara->properties.player.field_100        = 0;
    chara->properties.player.field_104        = 0;
    chara->properties.player.runTimer_108     = Q12(0.0f);
    chara->properties.player.timer_110        = 0;
    chara->properties.player.flags_11C        = 0;
    chara->properties.player.moveDistance_126 = 0;

    Chara_DamageClear(chara);

    g_Player_IsHoldAttack       = false;
    chara->flags            &= ~CharaFlag_Unk4;
    g_Player_PrevPosition       = chara->position;
    g_SysWork.targetNpcIdx = NO_VALUE;
    chara->field_40             = NO_VALUE;
    chara->attackReceived    = NO_VALUE;

    g_SysWork.npcIdxs[3] = NO_VALUE;
    g_SysWork.npcIdxs[2] = NO_VALUE;
    g_SysWork.npcIdxs[1] = NO_VALUE;
    g_SysWork.npcIdxs[0] = NO_VALUE;
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

    if (g_GameWork.mapAnimIdx != mapIdx ||
        mapIdx == (FILE_ANIM_HB_M6S04_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S01_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S02_ANM - BASE_FILE_IDX))
    {
        g_GameWork.mapAnimIdx = mapIdx;
        Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, FS_BUFFER_4);
    }

    #undef BASE_FILE_IDX
}

void GameFs_WeaponInfoUpdate(void) // 0x8007EBBC
{
    s32 relAnimInfoIdx;
    s32 relKeyframeIdx;
    s32 i;

    relAnimInfoIdx = 0;
    relKeyframeIdx = 0;

    g_SysWork.targetNpcIdx = NO_VALUE;

    switch (g_SysWork.playerCombat.weaponAttack)
    {
        case NO_VALUE:
            g_Player_EquippedWeaponInfo = D_800AFBF4[0];
            return;

        case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
            relAnimInfoIdx                                    = 30;
            relKeyframeIdx                                    = 15;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[1];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x1030;
            break;

        default:
            return;

        case WEAPON_ATTACK(EquippedWeaponId_Axe, AttackInputType_Tap):
            relAnimInfoIdx                                    = 0;
            relKeyframeIdx                                    = 0;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[3];
            g_SysWork.playerWork.player.field_C8.field_8 = -0xFD0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
        case WEAPON_ATTACK(EquippedWeaponId_Hammer, AttackInputType_Tap):
            g_Player_EquippedWeaponInfo = D_800AFBF4[2];
            switch (g_SysWork.playerCombat.weaponAttack)
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

            g_SysWork.playerWork.player.field_C8.field_8 = -0xEC0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap):
            relAnimInfoIdx                                    = 50;
            relKeyframeIdx                                    = 25;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[4];
            g_SysWork.playerWork.player.field_C8.field_8 = -0xE90;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap):
            relAnimInfoIdx                                    = 64;
            relKeyframeIdx                                    = 32;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[5];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x12E0;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Katana, AttackInputType_Tap):
            relAnimInfoIdx                                    = 40;
            relKeyframeIdx                                    = 20;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[10];
            g_SysWork.playerWork.player.field_C8.field_8 = -0xF20;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap):
            relAnimInfoIdx                                    = 78;
            relKeyframeIdx                                    = 39;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[6];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x1600;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
            relAnimInfoIdx                                    = 96;
            relKeyframeIdx                                    = 48;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[7];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x1180;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_Shotgun, AttackInputType_Tap):
            relAnimInfoIdx                                    = 114;
            relKeyframeIdx                                    = 57;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[8];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x1600;
            break;

        case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
            relAnimInfoIdx                                    = 132;
            relKeyframeIdx                                    = 66;
            g_Player_EquippedWeaponInfo                       = D_800AFBF4[9];
            g_SysWork.playerWork.player.field_C8.field_8 = -0x1610;
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

    if (g_SysWork.playerCombat.weaponAttack != NO_VALUE && g_Player_LastWeaponSelected != g_SysWork.playerCombat.weaponAttack)
    {
        g_Player_LastWeaponSelected = g_SysWork.playerCombat.weaponAttack;
        func_8007F14C(g_SysWork.playerCombat.weaponAttack);

        switch (g_SysWork.playerCombat.weaponAttack)
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
    if (g_SysWork.playerWork.extra.upperBodyState == PlayerUpperBodyState_Attack ||
        g_SysWork.playerWork.extra.state == PlayerState_KickEnemy ||
        g_SysWork.playerWork.extra.state == PlayerState_StompEnemy)
    {
        return true;
    }

    return false;
}

bool Player_IsBusy(void) // 0x8007F2AC
{
    if (g_SysWork.playerWork.player.health <= Q12(0.0f) ||
        g_SysWork.playerCombat.isAiming ||
        g_SysWork.playerWork.extra.state == PlayerState_KickEnemy ||
        g_SysWork.playerWork.extra.state == PlayerState_StompEnemy ||
        (g_SysWork.playerWork.extra.state >= PlayerState_Unk7 &&
         g_SysWork.playerWork.extra.state <= PlayerState_GetUpBack))
    {
        return true;
    }

    return false;
}

s16 Player_AnimGetSomething(void) // 0x8007F308
{
    return HARRY_BASE_ANIM_INFOS[g_SysWork.playerWork.player.model.anim.status].startKeyframeIdx;
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
        g_Player_HasMoveInput     = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.stepLeft |
                                                                              (ControllerFlag_LStickUp2 | ControllerFlag_LStickRight2 | ControllerFlag_LStickDown2 | ControllerFlag_LStickLeft2) |
                                                                              g_GameWorkPtr->config.controllerConfig.stepRight | g_GameWorkPtr->config.controllerConfig.aim);
    }
    else
    {
        g_Player_IsTurningLeft    = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickLeft) << 6;
        g_Player_IsTurningRight   = ((g_Controller0->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == ControllerFlag_LStickRight) << 6;
        g_Player_IsMovingForward |= (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickUp;
        g_Player_IsMovingBackward = (g_Controller0->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == ControllerFlag_LStickDown;
        g_Player_HasMoveInput     = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.stepLeft |
                                                                              (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft) |
                                                                              g_GameWorkPtr->config.controllerConfig.stepRight | g_GameWorkPtr->config.controllerConfig.aim);
    }

    g_Player_IsSteppingLeftHold  = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.stepLeft) &&
                                  !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.stepRight);

    g_Player_IsSteppingRightHold = (g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.stepRight) &&
                                  !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.stepLeft);

    g_Player_IsSteppingLeftTap  |= (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.stepLeft)  != 0;
    g_Player_IsSteppingRightTap |= (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.stepRight) != 0;

    if (g_GameWork.config.optExtraWalkRunCtrl_2B)
    {
        g_Player_IsRunning = !(g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.run);
    }
    else
    {
        g_Player_IsRunning = g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.run;
    }

    if (g_GameWork.config.optExtraWeaponCtrl_23)
    {
        g_Player_IsAiming = g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.aim;
    }
    else
    {
        g_Player_IsAiming = g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.aim;
    }

    if (g_SysWork.playerCombat.weaponAttack >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
        g_SysWork.playerWork.extra.lowerBodyState >= PlayerLowerBodyState_Aim)
    {
        g_Player_IsShooting  = g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.action;
        g_Player_IsAttacking = g_Player_IsShooting;
    }
    else
    {
        attackBtnInput = g_Controller0->btnsHeld_C & g_GameWorkPtr->config.controllerConfig.action;

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

    g_Player_HasActionInput = g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.run | g_GameWorkPtr->config.controllerConfig.action);

    if (g_SysWork.sysState != SysState_Gameplay)
    {
        g_Player_IsShooting   = false;
        g_Player_IsAttacking  = false;
        g_Player_IsHoldAttack = false;
    }

    if (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap))
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
    if (g_SysWork.playerCombat.isAiming && (g_SysWork.playerCombat.weaponAttack == WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap) ||
                                                      (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap) &&
                                                       (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Hammer ||
                                                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_RockDrill ||
                                                        WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack) == EquippedWeaponId_Katana))))
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

    pos0.vx = g_SysWork.playerWork.player.position.vx;
    pos0.vy = g_SysWork.playerWork.player.position.vy;
    pos0.vz = g_SysWork.playerWork.player.position.vz;

    if (!g_SysWork.playerCombat.isAiming ||
        g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
    {
        for (i = 0, curNpc0 = g_SysWork.npcs, curNpc1 = g_SysWork.npcs;
             i < ARRAY_SIZE(g_SysWork.npcs);
             i++, curNpc0++, curNpc1++)
        {
            if (curNpc1->model.charaId != Chara_None)
            {
                if (curNpc1->model.charaId == Chara_AirScreamer ||
                    curNpc1->model.charaId == Chara_NightFlutter)
                {
                    radius = Q12(1.2f);
                }
                else
                {
                    if (curNpc1->model.charaId == Chara_Creeper)
                    {
                        radius = Q12(0.65f);
                    }
                    else
                    {
                        radius = Q12(0.85f);
                    }
                }

                pos1.vx = curNpc0->position.vx + curNpc0->field_D8.offsetX_0;
                pos1.vy = curNpc0->position.vy;
                pos1.vz = curNpc0->position.vz + curNpc0->field_D8.offsetZ_2;

                if (!Math_Distance2dCheck(&pos0, &pos1, radius) && ABS(pos1.vy - pos0.vy) < Q12(0.3f) &&
                    curNpc0->health > Q12(0.0f) && (curNpc0->flags & CharaFlag_Unk2))
                {
                    Math_ShortestAngleGet(g_SysWork.playerWork.player.rotation.vy,
                                          Q12_ANGLE_NORM_U(ratan2(pos1.vx - pos0.vx, pos1.vz - pos0.vz) + Q12_ANGLE(360.0f)),
                                          &sp30);

                    temp = sp30 + Q12_ANGLE(89.98f);
                    if (temp < Q12_ANGLE(202.49f))
                    {
                        g_SysWork.targetNpcIdx = i;
                        return true;
                    }
                }
            }
        }
    }

    g_SysWork.targetNpcIdx = NO_VALUE;
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

    if (extra->model.controlState != 0)
    {
        return;
    }

    for (i = 0; i < 40; i++)
    {
        if (g_MapOverlayHeader.field_38[i].status_2 != animStatus)
        {
            continue;
        }

        if (extra->model.stateStep == 0)
        {
            extra->model.anim.status = g_MapOverlayHeader.field_38[i].status;
            extra->model.stateStep++;
        }

        if (chara->model.stateStep == 0)
        {
            chara->model.anim.status = g_MapOverlayHeader.field_38[i].status;
            chara->model.stateStep++;
        }

        D_800AF220 = i;
        i          = 41;

        extra->model.controlState++;
    }
}

void func_8007FC48(s_SubCharacter* chara, s_PlayerExtra* extra, s32 animStatus) // 0x8007FC48
{
    s32 i;

    if (extra->model.controlState != 0)
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
        extra->model.anim.status = g_MapOverlayHeader.field_38[i].status + 1; // TODO: There's a macro for anim status++.
        chara->model.anim.status = g_MapOverlayHeader.field_38[i].status + 1;

        // Increment state step.
        extra->model.stateStep++;
        chara->model.stateStep++;

        // Set anim time.
        extra->model.anim.time = Q12(g_MapOverlayHeader.field_38[i].time);
        D_800AF220                   = i;
        chara->model.anim.time = Q12(g_MapOverlayHeader.field_38[i].time);
        i                            = 41;

        // Increment state.
        extra->model.controlState++;
    }
}

s32 func_8007FD2C(void) // 0x8007FD2C
{
    return playerProps.field_104;
}

q19_12 Game_GasWeaponPowerTimerValue(void) // 0x8007FD3C
{
    return playerProps.gasWeaponPowerTimer_114;
}

void func_8007FD4C(bool cond) // 0x8007FD4C
{
    s32             i;
    s_SubCharacter* chara;

    chara = &g_SysWork.playerWork.player;

    g_Player_GrabReleaseInputTimer = Q12(0.0f);
    chara->field_40                = NO_VALUE;

    playerProps.flags_11C &= ~PlayerFlag_DamageReceived;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcIdxs); i++)
    {
        g_SysWork.npcIdxs[i] = NO_VALUE;
    }

    if (cond)
    {
        g_SysWork.playerWork.player.field_D4.radius_0   = Q12(0.3f);
        g_SysWork.playerWork.player.field_D4.field_2   = Q12(0.23f);
        g_SysWork.playerWork.player.field_C8.field_0   = Q12(-1.6f);
        g_SysWork.playerWork.player.field_D8.offsetZ_6 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetX_4 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetZ_2 = Q12(0.0f);
        g_SysWork.playerWork.player.field_D8.offsetX_0 = Q12(0.0f);
        g_SysWork.playerWork.player.field_C8.field_2   = Q12(0.0f);
        g_SysWork.playerWork.player.field_C8.field_6   = Q12(-1.1f);
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

            if (mapOverlayId == MapIdx_MAP2_S00)
            {
                if (g_SysWork.playerWork.player.position.vx >= Q12(95.0f)  && g_SysWork.playerWork.player.position.vx <= Q12(105.0f) &&
                    g_SysWork.playerWork.player.position.vz >= Q12(-33.0f) && g_SysWork.playerWork.player.position.vz <= Q12(-28.0f))
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
            if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP4_S02)
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
            if (g_SavegamePtr->mapOverlayId_A4 == MapIdx_MAP0_S02)
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
        case MapIdx_MAP6_S02:
            switch (g_SavegamePtr->mapRoomIdx_A5)
            {
                case 20:
                    if (g_SysWork.playerWork.player.position.vy > Q12(0.0f))
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

        case MapIdx_MAP4_S03:
            if ((g_SysWork.playerWork.player.position.vx >= Q12(165.0f)   &&
                 g_SysWork.playerWork.player.position.vz >= Q12(58.5f)    && g_SysWork.playerWork.player.position.vz <= Q12(61.5f)) ||
                (g_SysWork.playerWork.player.position.vx <= Q12(112.1f)   &&
                 g_SysWork.playerWork.player.position.vz >= Q12(-101.45f) && g_SysWork.playerWork.player.position.vz <= Q12(-98.5f)))
            {
                *sfxId = Sfx_Unk1565;
            }

        case MapIdx_MAP6_S00:
            if ((g_SysWork.playerWork.player.position.vx >= Q12(-160.1f)  && g_SysWork.playerWork.player.position.vx <= Q12(-158.5f)  &&
                 g_SysWork.playerWork.player.position.vz >= Q12(26.8f)    && g_SysWork.playerWork.player.position.vz <= Q12(27.4f))   ||
                (g_SysWork.playerWork.player.position.vx >= Q12(-160.1f)  && g_SysWork.playerWork.player.position.vx <= Q12(-158.5f)  &&
                 g_SysWork.playerWork.player.position.vz >= Q12(16.8f)    && g_SysWork.playerWork.player.position.vz <= Q12(17.5f))   ||
                (g_SysWork.playerWork.player.position.vx >= Q12(-170.0f)  && g_SysWork.playerWork.player.position.vx <= Q12(-165.8f)  &&
                 g_SysWork.playerWork.player.position.vz >= Q12(-16.4f)   && g_SysWork.playerWork.player.position.vz <= Q12(-14.35f)) ||
                (g_SysWork.playerWork.player.position.vx >= Q12(-172.7f)  && g_SysWork.playerWork.player.position.vx <= Q12(-170.9f)  &&
                 g_SysWork.playerWork.player.position.vz >= Q12(-24.9f)   && g_SysWork.playerWork.player.position.vz <= Q12(-21.25f)) ||
                (g_SysWork.playerWork.player.position.vx >= Q12(-170.28f) && g_SysWork.playerWork.player.position.vx <= Q12(-165.85f) &&
                 g_SysWork.playerWork.player.position.vz >= Q12(-35.4f)   && g_SysWork.playerWork.player.position.vz <= Q12(-34.35f)))
            {
                *sfxId = Sfx_Unk1600;
            }
            break;

        case MapIdx_MAP6_S01:
            if (g_SavegamePtr->mapRoomIdx_A5 == 18)
            {
                *sfxId = Sfx_Unk1608;
            }
            break;

        case MapIdx_MAP6_S04:
            *sfxId = Sfx_FootstepMetal;
            break;
    }

    // TODO: Use range-based rand macro.
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

    coll = &g_CollisionPointCache.collision_C;

    collX = g_CollisionPointCache.position.vx;
    collZ = g_CollisionPointCache.position.vz;
    if (g_CollisionPointCache.field_18 != NO_VALUE && collX == posX && collZ == posZ)
    {
        return;
    }

    Collision_Get(coll, posX, posZ);
    g_CollisionPointCache.position.vx = posX;
    g_CollisionPointCache.position.vz = posZ;

    count = coll->field_8;
    switch (coll->field_8)
    {
        case 0:
            groundHeight = Q12(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapIdx_MAP5_S01:
#if VERSION_EQUAL_OR_NEWER(USA)
                    if (posZ <= Q12(0.0f))
#endif
                    {
                        groundHeight = Q12(4.0f);
#if VERSION_EQUAL_OR_NEWER(USA)
                        count = 7;
#else
                        coll->field_8 = 7;
#endif
                    }
                    break;

                case MapIdx_MAP6_S00:
                    groundHeight = Q12(4.0f);
#if VERSION_EQUAL_OR_NEWER(USA)
                    count = 7;
#else
                    coll->field_8 = 7;
#endif
                    break;
            }
            break;

        case 12:
            groundHeight = Q12(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapIdx_MAP6_S00:
                    groundHeight = Q12(4.0f);
#if VERSION_EQUAL_OR_NEWER(USA)
                    count = 7;
#else
                    coll->field_8 = 7;
#endif
                    break;
            }
            break;

        default:
            groundHeight = coll->groundHeight_0;
            break;
    }

    g_CollisionPointCache.position.vy = groundHeight;
    g_CollisionPointCache.field_18      = count;
}

q19_12 Collision_GroundHeightGet(q19_12 posX, q19_12 posZ) // 0x80080884
{
    Collision_Fill(posX, posZ);
    return g_CollisionPointCache.position.vy;
}

s32 func_800808AC(q19_12 posX, q19_12 posZ) // 0x800808AC
{
    Collision_Fill(posX, posZ);
    return g_CollisionPointCache.field_18;
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

INCLUDE_RODATA("bodyprog/nonmatchings/player_control", hack_D_8002A844_fix);

#undef playerProps
