#include <bodyprog/player_logic.h>

void sharedFunc_800D20E4_0_s00()
{
    // TODO: Pointers here are odd, might be full of inlines.

    s_MainCharacterExtra* extra;
    s_SubCharacter*       chara;

    sharedData_800DD59C_0_s00 = NO_VALUE;

    D_800C457C                       = 0;
    D_800C4588                       = 0;
    g_Player_DisableControl          = true;
    g_Player_IsInWalkToRunTransition = false;

    extra   = &g_SysWork.player_4C.extra_128;
    chara   = &g_SysWork.player_4C.chara_0;

    D_800AF216 = 0;

    chara->properties_E4.player.afkTimer_E8      = 0;
    chara->properties_E4.player.runTimer_F8      = 0;
    chara->properties_E4.player.exhaustionTimer_FC = 0;

    g_SysWork.player_4C.extra_128.state_1C = PlayerState_Unk52;
    chara->model_0.stateStep_3             = 0;
    chara->model_0.state_2                 = 0;
    extra->model_0.stateStep_3             = 0;
    extra->model_0.state_2                 = 0;

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

    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;

    sharedData_800E39D8_0_s00 = 0;

    chara->field_D6                                             = 0;
    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk4 | PlayerFlag_Unk5;
    chara->flags_3E                                            |= CharaFlag_Unk4;
    chara->field_E1_0                                           = 4;

    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F %= 10;
    }
}
