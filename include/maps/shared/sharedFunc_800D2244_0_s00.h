#include <bodyprog/player_logic.h>

void sharedFunc_800D2244_0_s00(s32 arg0)
{
    s_MainCharacterExtra* extra;
    s_SubCharacter*       player;

    g_Player_DisableControl = false;

    extra  = &g_SysWork.player_4C.extra_128;
    player = &g_SysWork.player_4C.chara_0;

    if (arg0 != 0)
    {
        g_SysWork.player_4C.extra_128.state_1C          = PlayerState_None;
        g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
        g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;

        player->model_0.anim_4.status_0      = ANIM_STATUS(26, true);
        player->model_0.anim_4.keyframeIdx_8 = 503;
        extra->model_0.anim_4.status_0       = ANIM_STATUS(26, true);
        extra->model_0.anim_4.keyframeIdx_8  = 503;

        player->model_0.anim_4.time_4         = FP_TO(503, Q12_SHIFT);
        player->model_0.anim_4.alpha_A = FP_ALPHA(1.0f);
        extra->model_0.anim_4.time_4          = FP_TO(503, Q12_SHIFT);
        extra->model_0.anim_4.alpha_A  = FP_ALPHA(1.0f);
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

    player->field_D6 = 942;

    g_SysWork.player_4C.chara_0.field_C8                        = FP_FLOAT_TO(-1.6f, Q12_SHIFT);
    g_SysWork.player_4C.chara_0.field_CE                        = FP_FLOAT_TO(-1.1f, Q12_SHIFT);
    g_SysWork.player_4C.chara_0.field_CA                        = 0;
    g_SysWork.player_4C.chara_0.field_D8.field_6                = 0;
    g_SysWork.player_4C.chara_0.field_D8.field_4                = 0;
    g_SysWork.player_4C.chara_0.field_D8.field_2                = 0;
    g_SysWork.player_4C.chara_0.field_D8.field_0                = 0;
    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~(PlayerFlag_Unk2 |
                                                                    PlayerFlag_Unk13 |
                                                                    PlayerFlag_DamageReceived |
                                                                    PlayerFlag_Moving);

    player->flags_3E &= ~CharaFlag_Unk4;
    player->field_E0_8 = 3;

    Player_AnimFlagsSet(AnimFlag_Unlocked);

    D_800C45F8.vx = player->position_18.vx;
    D_800C45F8.vz = player->position_18.vz;

#if !defined(MAP0_S00)
    D_800AF210 = 0;
    D_800AF212 = 0;
#endif
}
