#include "bodyprog/player_logic.h"

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    s_func_800699F8 sp10;
    s32             sfx;
    s8              pitch;
    s8              sp25;
    s32             unused; // @unused Unknown purpose.
    s32             newMoveSpeed;

    unused                    = 0;
    sharedData_800D32A0_0_s02 = 0;
    sharedData_800E39D8_0_s00 = 0;

    playerChara->properties_E4.player.field_10C = (playerChara->properties_E4.player.field_10C >> 1);
    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = 0;

    func_8004C564(0, -1);

    playerChara->properties_E4.player.afkTimer_E8      = 0;
    playerChara->properties_E4.player.exertionTimer_FC = 0;

    if (g_SysWork.player_4C.extra_128.playerState_1C == 52)
    {
        if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * FP_TIME(0.4f)) / FP_TIME(0.1f / 3.0f)) * 2;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
            }
        }

        sharedData_800E39D8_0_s00 = 0;
        sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

        if (extra->model_0.stateStep_3 == 0)
        {
            extra->model_0.anim_4.animIdx_0 = 52;
            extra->model_0.stateStep_3++;
        }

        if (playerChara->model_0.stateStep_3 == 0)
        {
            playerChara->model_0.anim_4.animIdx_0 = 52;
            playerChara->model_0.stateStep_3++;
        }

        if (extra->model_0.state_2 == 0)
        {
            extra->model_0.state_2++;
        }

        switch (D_800C457C)
        {
            case 3:
                g_SysWork.player_4C.extra_128.playerState_1C         = PlayerState_Unk56;
				playerChara->model_0.stateStep_3                     = 0;
				playerChara->model_0.state_2                         = 0;
				extra->model_0.stateStep_3                           = 0;
				extra->model_0.state_2                               = 0;
				g_SysWork.player_4C.extra_128.playerUpperMovement_20 = PlayerUpperMovement_None;
				g_SysWork.player_4C.extra_128.playerLowerMovement_24 = PlayerLowerMovement_None;
                break;

            case 4:
                g_SysWork.player_4C.extra_128.playerState_1C         = PlayerState_Unk57;
				playerChara->model_0.stateStep_3                     = 0;
				playerChara->model_0.state_2                         = 0;
				extra->model_0.stateStep_3                           = 0;
				extra->model_0.state_2                               = 0;
				g_SysWork.player_4C.extra_128.playerUpperMovement_20 = PlayerUpperMovement_None;
				g_SysWork.player_4C.extra_128.playerLowerMovement_24 = PlayerLowerMovement_None;
                break;
        }

        if (D_800C4606 != 0)
        {
            g_SysWork.player_4C.extra_128.playerState_1C         = PlayerState_Unk52;
            playerChara->model_0.stateStep_3                     = 0;
            playerChara->model_0.state_2                         = 0;
            extra->model_0.stateStep_3                           = 0;
            extra->model_0.state_2                               = 0;
            g_SysWork.player_4C.extra_128.playerUpperMovement_20 = PlayerUpperMovement_None;
            g_SysWork.player_4C.extra_128.playerLowerMovement_24 = PlayerLowerMovement_None;
            D_800C4606                                           = 0;
        }

        g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
        unused                                                     = 0;
    }

    func_800699F8(&sp10, playerChara->position_18.vx, playerChara->position_18.vz);
    func_8007FDE0(sp10.field_8, &sfx, &pitch, &sp25);

    if (g_SysWork.player_4C.extra_128.playerState_1C == 52)
    {
        if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Moving)
        {
            if (playerChara->model_0.anim_4.animIdx_0 == g_SysWork.player_4C.extra_128.playerState_1C)
            {
                func_8005DD44(sfx, &playerChara->position_18, 64, pitch);

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
    playerChara->headingAngle_3C = FP_ANGLE_NORM_U(playerChara->rotation_24.vy + unused);
    playerChara->moveSpeed_38    = newMoveSpeed;
    playerChara->field_34       += g_DeltaTime2;

    coord->flg = 0;
    func_80096E78(&playerChara->rotation_24, &coord->coord);
}
