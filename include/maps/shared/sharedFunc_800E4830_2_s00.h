void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner)
{
    VECTOR3 sp20;
    q3_12   angleDeltaToPlayer0;
    q3_12   angleDeltaToPlayer1;
    s32     temp_a2;
    q19_12  distToPlayer;
    q19_12  deltaX;
    q19_12  deltaZ;
    q19_12  deltaY;
    s32     temp_v1;
    q19_12  rotMax;
    s32     var_v0;
    s32     temp1;
    s32     temp2;

    #define groanerProps groaner->properties_E4.groaner

    // TODO: Use macro.
    deltaX       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx);
    deltaZ       = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz);
    distToPlayer = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angleDeltaToPlayer0 = func_8005BF38(Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                        groaner->rotation_24.vy);

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_15 ||
        ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 214) < 9u)
    {
        temp_v1 = TIMESTEP_ANGLE_4;

        if ((angleDeltaToPlayer0 >= FP_ANGLE(0.0f) && temp_v1 <  angleDeltaToPlayer0) ||
            (angleDeltaToPlayer0 <  FP_ANGLE(0.0f) && temp_v1 < -angleDeltaToPlayer0))
        {
            if (angleDeltaToPlayer0 > FP_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
            }

            angleDeltaToPlayer1 = func_8005BF38(Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                                groaner->rotation_24.vy);

            rotMax = TIMESTEP_ANGLE_4;
            if ((angleDeltaToPlayer1 >= FP_ANGLE(0.0f) && rotMax <  angleDeltaToPlayer1) ||
                (angleDeltaToPlayer1 <  FP_ANGLE(0.0f) && rotMax < -angleDeltaToPlayer1))
            {
                if (angleDeltaToPlayer1 > FP_ANGLE(0.0f))
                {
                    groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
                }
                else
                {
                    groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
                }
            }
            else
            {
                groaner->rotation_24.vy = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
            }
        }
        else
        {
            groaner->rotation_24.vy = Math_AngleBetweenPositionsGet(groaner->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
        groaner->headingAngle_3C = groaner->rotation_24.vy;
    }
    else
    {
        // TODO: Convert 771. Maybe some fraction?
        temp1 = groaner->rotation_24.vy + Q12(0.125f);
        temp2 = groaner->headingAngle_3C + Q12_MULT_PRECISE(g_DeltaTime0, 771);

        if (temp2 < temp1)
        {
            groaner->headingAngle_3C += Q12_MULT_PRECISE(g_DeltaTime0, 771);
        }
        else
        {
            groaner->headingAngle_3C = groaner->rotation_24.vy + Q12(0.125f);
        }
    }

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_15)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(9.5f), Q12(0.0f));
    }
    else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_10)
    {
        if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_9))
        {
            groanerProps.flags_E8.val16[0]                         |= GroanerFlag_9;
            var_v0                                                = g_SysWork.playerWork_4C.player_0.field_D4.field_2 + 573;
            var_v0                                                = (distToPlayer - var_v0) << 1;
            groaner->moveSpeed_38                                   = MIN(var_v0, Q12(4.5f));

            deltaY                                           = g_SysWork.playerWork_4C.player_0.position_18.vy - groaner->position_18.vy;
            groaner->field_44.field_0                             = 1;
            groanerProps.field_10C[3] = 2;
            groaner->field_34                                     = Q12_MULT_PRECISE(deltaY - Q12(1.4f), Q12(2.35f));
        }
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 222)) < 2u)
    {
        sp20.vx = groaner->position_18.vx + groaner->field_D8.offsetX_4;
        sp20.vy = groaner->position_18.vy - Q12(0.8f);
        sp20.vz = groaner->position_18.vz + groaner->field_D8.offsetZ_6;
        func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Hold), groaner, &sp20, &g_SysWork.playerWork_4C.player_0, groaner->rotation_24.vy, FP_ANGLE(90.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 222)) < 14u)
    {
        groaner->field_34 += g_DeltaTime2;

        Chara_MoveSpeedUpdate3(groaner, Q12(0.3f), Q12(0.0f));
    }

    if ((ANIM_TIME_REL_KEYFRAME_IDX_GET(groaner->model_0.anim_4.time_4, 236)) < 7u)
    {
        Chara_MoveSpeedUpdate3(groaner, Q12(1.2f), Q12(0.0f));
    }

    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_16)
    {
        groaner->model_0.controlState_2                         = GroanerControl_4;
        groaner->rotation_24.vy                                += Q12(0.125f);
        groanerProps.angle_EC += Q12(0.125f);
        g_SysWork.field_2284[3]                              &= ~(1 << 1);
        groaner->model_0.anim_4.status_0                        = ANIM_STATUS(GroanerAnim_16, true);
        groaner->model_0.anim_4.time_4                          = Q12(363.0f);
        groaner->model_0.anim_4.keyframeIdx_8                   = 363;
        groanerProps.flags_E8.val16[0]                         &= ~GroanerFlag_9;
    }

    #undef groanerProps
}
