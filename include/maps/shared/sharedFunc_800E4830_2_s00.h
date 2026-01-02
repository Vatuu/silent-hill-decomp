void sharedFunc_800E4830_2_s00(s_SubCharacter* chara)
{
    VECTOR3 sp20;
    q3_12   angleDeltaToPlayer0;
    q3_12   angleDeltaToPlayer1;
    s32     temp_a2;
    s32     distToPlayer;
    q19_12  deltaX;
    q19_12  deltaZ;
    s32     temp_v0_4;
    s32     temp_v1;
    s32     temp_v1_2;
    s32     var_v0;
    s32     temp1;
    s32     temp2;

    // TODO: Use macro.
    deltaX       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx);
    deltaZ       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    distToPlayer = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angleDeltaToPlayer0 = func_8005BF38(Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                        chara->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 15 ||
        ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 214) < 9u)
    {
        temp_v1 = TIMESTEP_ANGLE_4;

        if ((angleDeltaToPlayer0 >= FP_ANGLE(0.0f) && temp_v1 <  angleDeltaToPlayer0) ||
            (angleDeltaToPlayer0 <  FP_ANGLE(0.0f) && temp_v1 < -angleDeltaToPlayer0))
        {
            if (angleDeltaToPlayer0 > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
            }

            angleDeltaToPlayer1 = func_8005BF38(Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                                chara->rotation_24.vy);

            temp_v1_2 = TIMESTEP_ANGLE_4;
            if ((angleDeltaToPlayer1 >= FP_ANGLE(0.0f) && temp_v1_2 <  angleDeltaToPlayer1) ||
                (angleDeltaToPlayer1 <  FP_ANGLE(0.0f) && temp_v1_2 < -angleDeltaToPlayer1))
            {
                if (angleDeltaToPlayer1 > FP_ANGLE(0.0f))
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
                }
            }
            else
            {
                chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
        chara->headingAngle_3C = chara->rotation_24.vy;
    }
    else
    {
        // TODO: Convert 771. Maybe some fraction?
        temp1 = chara->rotation_24.vy + Q12(0.125f);
        temp2 = chara->headingAngle_3C + FP_MULTIPLY_PRECISE(g_DeltaTime0, 771, Q12_SHIFT);

        if (temp2 < temp1)
        {
            chara->headingAngle_3C += FP_MULTIPLY_PRECISE(g_DeltaTime0, 771, Q12_SHIFT);
        }
        else
        {
            chara->headingAngle_3C = chara->rotation_24.vy + Q12(0.125f);
        }
    }

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 15)
    {
        Chara_MoveSpeedUpdate3(chara, Q12(9.5f), Q12(0.0f));
    }
    else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 10)
    {
        if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 9)))
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 9);
            var_v0                                                = g_SysWork.playerWork_4C.player_0.field_D4.field_2 + 573;
            var_v0                                                = (distToPlayer - var_v0) << 1;
            chara->moveSpeed_38                                   = MIN(var_v0, Q12(4.5f));

            temp_v0_4                                           = g_SysWork.playerWork_4C.player_0.position_18.vy - chara->position_18.vy;
            chara->field_44.field_0                             = 1;
            chara->properties_E4.dummy.properties_E8[9].val8[3] = 2;
            chara->field_34                                     = FP_MULTIPLY_PRECISE(temp_v0_4 - Q12(1.4f), Q12(2.35f), Q12_SHIFT);
        }
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 222)) < 2u)
    {
        sp20.vx = chara->position_18.vx + chara->field_D8.offsetX_4;
        sp20.vy = chara->position_18.vy - Q12(0.8f);
        sp20.vz = chara->position_18.vz + chara->field_D8.offsetZ_6;
        func_8008A0E4(1, 0x2B, chara, &sp20, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, Q12(0.25f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 222)) < 14u)
    {
        chara->field_34 += g_DeltaTime2;

        Chara_MoveSpeedUpdate3(chara, Q12(0.3f), Q12(0.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 236)) < 7u)
    {
        Chara_MoveSpeedUpdate3(chara, Q12(1.2f), Q12(0.0f));
    }

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 16)
    {
        chara->model_0.controlState_2                         = 4;
        chara->rotation_24.vy                                += Q12(0.125f);
        chara->properties_E4.dummy.properties_E8[1].val16[0] += Q12(0.125f);
        g_SysWork.field_2284[3]                              &= ~(1 << 1);
        chara->model_0.anim_4.status_0                        = ANIM_STATUS(16, true);
        chara->model_0.anim_4.time_4                          = Q12(363.0f);
        chara->model_0.anim_4.keyframeIdx_8                   = 363;
        chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 9);
    }
}
