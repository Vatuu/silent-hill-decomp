void sharedFunc_800D5098_0_s00(s_SubCharacter* chara)
{
    s16 temp_3;
    s32 temp_s5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 newMoveSpeed0;
    s32 i;
    s32 var_v1;

    #define SPEED_0_9 Q12(0.9f)
    #define SPEED_0_7 Q12(0.7f)

    // TODO: `chara->model_0.anim_4.status_0 == ANIM_STATUS(30, false)` doesn't match?
    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 30)
    {
        chara->model_0.state_2   = 4;
        g_SysWork.field_2284[3] &= ~(1 << 1);
        return;
    }

    temp_v1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
    if (temp_v1 >= 62 && temp_v1 < 65)
    {
        chara->moveSpeed_38 = Q12(0.0f);
    }
    else if (temp_v1 >= 50 && temp_v1 < 62)
    {
        temp_s5 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                      g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

        for (i = 0; i < 6; i++)
        {
            temp_3    = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                              g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                      chara->rotation_24.vy));
            temp_v1_2 = ((g_DeltaTime0 / 3) >> 3) + 1; // @hack `(g_DeltaTime0 / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?

            if ((temp_3 >= 0 && temp_v1_2 < temp_3) || (temp_3 < 0 && temp_v1_2 < -temp_3))
            {
                if (temp_3 > 0)
                {
                    chara->rotation_24.vy = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.0833f, Q12_SHIFT) + chara->rotation_24.vy;
                }
                else
                {
                    chara->rotation_24.vy = chara->rotation_24.vy - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.0833f, Q12_SHIFT);
                }
            }
        }

        if (!((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 13)))
        {
            if (temp_s5 > SPEED_0_9)
            {
                if (chara->moveSpeed_38 > SPEED_0_7)
                {
                    newMoveSpeed0 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < SPEED_0_7)
                    {
                        newMoveSpeed0 = SPEED_0_7;
                    }
                }
                else
                {
                    newMoveSpeed0 = SPEED_0_7;
                    var_v1        = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (var_v1 <= SPEED_0_7)
                    {
                        newMoveSpeed0 = var_v1;
                    }
                }

                chara->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            if (temp_s5 < SPEED_0_7)
            {
                if (chara->moveSpeed_38 > -SPEED_0_7)
                {
                    newMoveSpeed0 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < -SPEED_0_7)
                    {
                        newMoveSpeed0 = -SPEED_0_7;
                    }
                }
                else
                {
                    newMoveSpeed0 = -SPEED_0_7;
                    var_v1        = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (var_v1 <= -SPEED_0_7)
                    {
                        newMoveSpeed0 = var_v1;
                    }
                }

                chara->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            Chara_MoveSpeedUpdate(chara, Q12(6.0f));
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(chara, Q12(6.0f));
    }
}
