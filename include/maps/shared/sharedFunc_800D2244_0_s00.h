#include <bodyprog/player_logic.h>

void sharedFunc_800D2244_0_s00(bool arg0)
{
    s_SubCharacter*       player;
    s_MainCharacterExtra* extra;

    g_Player_DisableControl = false;

    extra  = &g_SysWork.player_4C.extra_128;
    player = &g_SysWork.player_4C.chara_0;

    if (arg0)
    {
        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;

        // TODO: Will `Character_AnimSet` work here?
        player->model_0.anim_4.status_0      = ANIM_STATUS(26, true);
        player->model_0.anim_4.keyframeIdx_8 = 503;
        extra->model_0.anim_4.status_0       = ANIM_STATUS(26, true);
        extra->model_0.anim_4.keyframeIdx_8  = 503;
        player->model_0.anim_4.time_4        = Q12(503);
        player->model_0.anim_4.alpha_A       = Q12(1.0f);
        extra->model_0.anim_4.time_4         = Q12(503);
        extra->model_0.anim_4.alpha_A        = Q12(1.0f);
    }
    else
    {
        g_SysWork.player_4C.extra_128.state_1C = PlayerState_None;
        player->model_0.stateStep_3 = 0;
        player->model_0.state_2     = 0;
        extra->model_0.stateStep_3  = 0;
        extra->model_0.state_2      = 0;
        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
    }

    player->attackReceived_41 = NO_VALUE;
    player->field_40          = NO_VALUE;
    g_SysWork.field_2354[1]   = NO_VALUE;
    g_SysWork.field_2354[0]   = NO_VALUE;

#if !defined(MAP0_S00) && !defined(MAP0_S01)
    func_8003D01C();
#endif

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

    g_SysWork.playerCombatInfo_38.isAiming_13 = false;

    player->field_D6                                            = Q12(0.23f);
    g_SysWork.player_4C.chara_0.field_C8                        = Q12(-1.6f);
    g_SysWork.player_4C.chara_0.field_CE                        = Q12(-1.1f);
    g_SysWork.player_4C.chara_0.field_CA                        = Q12(0.0f);
    g_SysWork.player_4C.chara_0.field_D8.offsetZ_6              = Q12(0.0f);
    g_SysWork.player_4C.chara_0.field_D8.offsetX_4              = Q12(0.0f);
    g_SysWork.player_4C.chara_0.field_D8.offsetZ_2              = Q12(0.0f);
    g_SysWork.player_4C.chara_0.field_D8.offsetX_0              = Q12(0.0f);
    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~(PlayerFlag_Unk2           |
                                                                    PlayerFlag_Unk13          |
                                                                    PlayerFlag_DamageReceived |
                                                                    PlayerFlag_Moving);

    player->flags_3E &= ~CharaFlag_Unk4;
    player->field_E1_0 = 3;

    Player_AnimFlagsSet(AnimFlag_Unlocked);

    g_Player_PrevPosition.vx = player->position_18.vx;
    g_Player_PrevPosition.vz = player->position_18.vz;

#if !defined(MAP0_S00)
    g_Player_FlexRotationY = FP_ANGLE(0.0f);
    g_Player_FlexRotationX = FP_ANGLE(0.0f);
#endif
}
