void sharedFunc_800D5098_0_s00(s_SubCharacter* chara)
{
    s16 temp_3;
    s32 temp_s5;
    s32 deltaX;
    s32 deltaZ;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 newMoveSpeed0;
    s32 i;
    s32 newMoveSpeed1;
    s32 var_v1;

    #define SPEED_0_9 (FP_FLOAT_TO(0.9f, Q12_SHIFT))
    #define SPEED_0_7 (FP_FLOAT_TO(0.7f, Q12_SHIFT))

    if ((chara->model_0.anim_4.animIdx_0 >> 1) == 0x1E)
    {
        chara->model_0.state_2 = 4;
        g_SysWork.field_228A &= ~(1 << 1);
        return;
    }

    temp_v1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
    if ((temp_v1 - 62) < 3u)
    {
        chara->moveSpeed_38 = 0;
        return;
    }

    if ((temp_v1 - 50) < 12u)
    {
        deltaX  = (g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx) >> 6;
        deltaZ  = (g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) >> 6;
        temp_s5 = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) << 6;

        for (i = 0; i < 6; i++)
        {
            temp_3    = func_8005BF38((ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                              g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                                      chara->rotation_24.vy));
            temp_v1_2 = ((g_DeltaTime0 / 3) >> 3) + 1;

            if ((temp_3 >= 0 && temp_v1_2 < temp_3) || (temp_3 < 0 && temp_v1_2 < -temp_3))
            {
                if (temp_3 > 0)
                {
                    chara->rotation_24.vy = FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 0.0833f, Q12_SHIFT) + chara->rotation_24.vy;
                }
                else
                {
                    chara->rotation_24.vy = chara->rotation_24.vy - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 0.0833f, Q12_SHIFT);
                }
            }
        }

        if (!((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 13)))
        {
            if (temp_s5 > SPEED_0_9)
            {
                if (chara->moveSpeed_38 > SPEED_0_7)
                {
                    newMoveSpeed0 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < SPEED_0_7)
                    {
                        newMoveSpeed0 = SPEED_0_7;
                    }
                }
                else
                {
                    newMoveSpeed0 = SPEED_0_7;
                    var_v1        = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.0f, Q12_SHIFT);
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
                    newMoveSpeed0 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < -SPEED_0_7)
                    {
                        newMoveSpeed0 = -SPEED_0_7;
                    }
                }
                else
                {
                    newMoveSpeed0 = -SPEED_0_7;
                    var_v1        = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (var_v1 <= -SPEED_0_7)
                    {
                        newMoveSpeed0 = var_v1;
                    }
                }

                chara->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            // TODO: This code is duplicated in block below, can it be shared somehow?
            if (chara->moveSpeed_38 > 0)
            {
                newMoveSpeed1 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 6.0f, Q12_SHIFT);
                if (newMoveSpeed1 < 0)
                {
                    newMoveSpeed1 = 0;
                }
            }
            else
            {
                newMoveSpeed1 = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 6.0f, Q12_SHIFT);
                if (newMoveSpeed1 > 0)
                {
                    newMoveSpeed1 = 0;
                }
            }

            chara->moveSpeed_38 = newMoveSpeed1;
        }
    }
    else
    {
        if (chara->moveSpeed_38 > 0)
        {
            newMoveSpeed1 = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 6.0f, Q12_SHIFT);
            if (newMoveSpeed1 < 0)
            {
                newMoveSpeed1 = 0;
            }
        }
        else
        {
            newMoveSpeed1 = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 6.0f, Q12_SHIFT);
            if (newMoveSpeed1 > 0)
            {
                newMoveSpeed1 = 0;
            }
        }

        chara->moveSpeed_38 = newMoveSpeed1;
    }
}
