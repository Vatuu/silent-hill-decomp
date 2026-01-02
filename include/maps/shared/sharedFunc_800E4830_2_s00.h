void sharedFunc_800E4830_2_s00(s_SubCharacter* chara)
{
    VECTOR3 sp20;
    s16     angle;
    s16     angle1;
    s32     temp_a2;
    s32     dist;
    s32     deltaX;
    s32     deltaZ;
    s32     temp_v0_4;
    s32     temp_v1;
    s32     temp_v1_2;
    s32     var_v0;
    s32     temp1, temp2;

    deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angle = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                  g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                           chara->rotation_24.vy));

    if ((ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 0xF) || (ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 0xD6) < 9U))
    {
        temp_v1 = TIMESTEP_ANGLE_4;

        if ((angle >= 0 && temp_v1 < angle) || (angle < 0 && temp_v1 < -angle))
        {
            if (angle > 0)
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
            }

            angle1 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                           g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy));

            temp_v1_2 = TIMESTEP_ANGLE_4;
            if ((angle1 >= 0 && temp_v1_2 < angle1) || (angle1 < 0 && temp_v1_2 < -angle1))
            {
                if (angle1 > 0)
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
                chara->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
            }
        }
        else
        {
            chara->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                           g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
        }
        chara->headingAngle_3C = chara->rotation_24.vy;
    }
    else
    {
        temp1 = chara->rotation_24.vy + Q12(0.125f);
        temp2 = chara->headingAngle_3C + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x303, Q12_SHIFT);

        if (temp2 < temp1)
        {
            chara->headingAngle_3C += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x303, Q12_SHIFT);
        }
        else
        {
            chara->headingAngle_3C = chara->rotation_24.vy + Q12(0.125f);
        }
    }

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 0xF)
    {
        Chara_MoveSpeedUpdate3(chara, Q12(9.5f), Q12(0.0f));
    }
    else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 0xA)
    {
        if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x200))
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] |= 0x200;
            var_v0                                                = g_SysWork.playerWork_4C.player_0.field_D4.field_2 + 0x23D;
            var_v0                                                = (dist - var_v0) << 1;
            chara->moveSpeed_38                                   = MIN(var_v0, Q12(4.5f));

            temp_v0_4                                           = g_SysWork.playerWork_4C.player_0.position_18.vy - chara->position_18.vy;
            chara->field_44.field_0                             = 1;
            chara->properties_E4.dummy.properties_E8[9].val8[3] = 2;
            chara->field_34                                     = FP_MULTIPLY_PRECISE(temp_v0_4 - Q12(1.4f), Q12(2.35f), Q12_SHIFT);
        }
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 0xDE)) < 2U)
    {
        sp20.vx = chara->position_18.vx + chara->field_D8.offsetX_4;
        sp20.vy = chara->position_18.vy - Q12(0.8f);
        sp20.vz = chara->position_18.vz + chara->field_D8.offsetZ_6;
        func_8008A0E4(1, 0x2B, chara, &sp20, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, Q12(0.25f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 0xDE)) < 0xEU)
    {
        chara->field_34 += g_DeltaTime2;

        Chara_MoveSpeedUpdate3(chara, Q12(0.3f), Q12(0.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(chara->model_0.anim_4.time_4, 0xEC)) < 7U)
    {
        Chara_MoveSpeedUpdate3(chara, Q12(1.2f), Q12(0.0f));
    }

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 0x10)
    {
        chara->model_0.controlState_2                         = 4;
        chara->rotation_24.vy                                += Q12(0.125f);
        chara->properties_E4.dummy.properties_E8[1].val16[0] += Q12(0.125f);
        g_SysWork.field_2284[3]                              &= 0xFFFD;
        chara->model_0.anim_4.status_0                        = 0x21;
        chara->model_0.anim_4.time_4                          = 0x16B000;
        chara->model_0.anim_4.keyframeIdx_8                   = 0x16B;
        chara->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFDFF;
    }
}