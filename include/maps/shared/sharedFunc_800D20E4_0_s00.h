#include <bodyprog/player_logic.h>

void sharedFunc_800D20E4_0_s00()
{
    // TODO: Pointers here are odd, might be full of inlines.

    s_MainCharacterExtra* extra;
    s_SubCharacter*       chara;
    s_SysWork*            sysWork;

    sharedData_800DD59C_0_s00 = NO_VALUE;

    D_800C457C                       = 0;
    D_800C4588                       = 0;
    g_Player_DisableControl          = true;
    g_Player_IsInWalkToRunTransition = false;

    extra   = &g_SysWork.player_4C.extra_128;
    chara   = &g_SysWork.player_4C.chara_0;
    sysWork = &g_SysWork;

    D_800AF216 = 0;

    chara->properties_E4.player.properties_E4[PlayerProperty_AfkTimer]      = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_RunTimer0]     = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_ExertionTimer] = 0;

    sysWork->player_4C.extra_128.playerState_1C = PlayerState_Unk52;
    chara->model_0.stateStep_3                  = 0;
    chara->model_0.state_2                      = 0;
    extra->model_0.stateStep_3                  = 0;
    extra->model_0.state_2                      = 0;

    g_Player_IsShooting            = 0;
    g_Player_IsAttacking           = 0;
    g_Player_IsHoldAttack          = 0;
    g_Player_IsAiming              = 0;
    g_Player_IsRunning             = 0;
    g_Player_IsMovingBackward      = 0;
    g_Player_IsMovingForward       = 0;
    g_Player_IsStepping_Right_Tap  = 0;
    g_Player_IsStepping_Right_Hold = 0;
    g_Player_IsTurning_Right       = 0;
    g_Player_IsStepping_Left_Tap   = 0;
    g_Player_IsStepping_Left_Hold  = 0;
    g_Player_IsTurning_Left        = 0;

    sysWork->player_4C.extra_128.playerUpperMovement_20 = 0;
    sysWork->player_4C.extra_128.playerLowerMovement_24 = 0;

    sharedData_800E39D8_0_s00 = 0;

    chara->field_D6                                            = 0;
    sysWork->player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk4 | PlayerFlag_Unk5;
    chara->flags_3E                                           |= CharaFlag_Unk4;
    chara->field_E0_8                                          = 4;

    if (sysWork->playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
    {
        sysWork->playerCombatInfo_38.equippedWeapon_F %= 10;
    }
}
