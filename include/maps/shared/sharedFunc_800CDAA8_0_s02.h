#include "bodyprog/player_logic.h"

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    s_func_800699F8 sp10;
    s32             sfx;
    s8              pitch;
    s8              sp25;
    s32             headingAngle; // Serves no meaaningful purpose as it's always `FP_ANGLE(0.0f)`.
    s32             newMoveSpeed;

    headingAngle              = FP_ANGLE(0.0f);
    sharedData_800D32A0_0_s02 = 0;
    sharedData_800E39D8_0_s00 = 0;

    playerChara->properties_E4.player.field_10C = (playerChara->properties_E4.player.field_10C >> 1);
    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = 0;

    func_8004C564(0, -1);

    playerChara->properties_E4.player.afkTimer_E8      = FP_TIME(0.0f);
    playerChara->properties_E4.player.exertionTimer_FC = FP_TIME(0.0f);

    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk52)
    {
        if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != FP_METER(0.0f))
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * FP_METER(0.4f)) / FP_METER(0.1f / 3.0f)) * 2;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < FP_METER(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(0.0f);
            }
        }

        sharedData_800E39D8_0_s00 = 0;
        sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

        if (extra->model_0.stateStep_3 == 0)
        {
            extra->model_0.anim_4.status_0 = ANIM_STATUS(26, false);
            extra->model_0.stateStep_3++;
        }

        if (playerChara->model_0.stateStep_3 == 0)
        {
            playerChara->model_0.anim_4.status_0 = ANIM_STATUS(26, false);
            playerChara->model_0.stateStep_3++;
        }

        if (extra->model_0.state_2 == 0)
        {
            extra->model_0.state_2++;
        }

        switch (D_800C457C)
        {
            case 3:
                g_SysWork.player_4C.extra_128.state_1C         = PlayerState_Unk56;
				playerChara->model_0.stateStep_3               = 0;
				playerChara->model_0.state_2                   = 0;
				extra->model_0.stateStep_3                     = 0;
				extra->model_0.state_2                         = 0;
				g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
				g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                break;

            case 4:
                g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk57;
				playerChara->model_0.stateStep_3                = 0;
				playerChara->model_0.state_2                    = 0;
				extra->model_0.stateStep_3                      = 0;
				extra->model_0.state_2                          = 0;
				g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
				g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
                break;
        }

        if (D_800C4606 != 0)
        {
            g_SysWork.player_4C.extra_128.state_1C          = PlayerState_Unk52;
            playerChara->model_0.stateStep_3                = 0;
            playerChara->model_0.state_2                    = 0;
            extra->model_0.stateStep_3                      = 0;
            extra->model_0.state_2                          = 0;
            g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
            g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
            D_800C4606                                      = 0;
        }

        g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
        headingAngle                                                      = FP_ANGLE(0.0f);
    }

    func_800699F8(&sp10, playerChara->position_18.vx, playerChara->position_18.vz);
    func_8007FDE0(sp10.field_8, &sfx, &pitch, &sp25);

    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk52)
    {
        if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Moving)
        {
            // TODO: State used as anim status??
            if (playerChara->model_0.anim_4.status_0 == g_SysWork.player_4C.extra_128.state_1C)
            {
                func_8005DD44(sfx, &playerChara->position_18, FP_VOLUME(0.25f), pitch);

                playerChara->properties_E4.player.field_10C                 = pitch + 16;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }
        }
    }
    else
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
    }

    newMoveSpeed = sharedData_800D32A0_0_s02;

    playerChara->rotation_24.vy  = FP_ANGLE_NORM_U((playerChara->rotation_24.vy + (sharedData_800E39D8_0_s00 >> 4)) + FP_ANGLE(360.0f));
    playerChara->headingAngle_3C = FP_ANGLE_NORM_U(playerChara->rotation_24.vy + headingAngle);
    playerChara->moveSpeed_38    = newMoveSpeed;
    playerChara->field_34       += g_DeltaTime2;

    coord->flg = false;
    func_80096E78(&playerChara->rotation_24, &coord->coord);
}
