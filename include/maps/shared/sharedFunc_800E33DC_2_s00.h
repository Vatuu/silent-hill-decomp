void sharedFunc_800E33DC_2_s00(s_SubCharacter* groaner)
{
    s_Collision coll;
    q3_12       newHeadingAngle;
    q3_12       unkAngle;
    q19_12      unkDist;
    s32         temp_v0;
    s32         prevControlState;

    if (groaner->health_B0 > Q12(0.0f))
    {
        Collision_Get(&coll, groaner->position_18.vx, groaner->position_18.vz);

        if (coll.field_8 == 12 && Rng_GenerateInt(Q12(4.0f), Q12(7.0f) - 1) < groaner->position_18.vy)
        {
            groaner->damage_B4.amount_C = Q12(1000.0f);
        }
    }

    if (groaner->damage_B4.amount_C == Q12(0.0f))
    {
        return;
    }

    if (groaner->health_B0 < Q12(0.0f))
    {
        return;
    }

    prevControlState = groaner->model_0.controlState_2;

    if (groaner->health_B0 > Q12(0.0f))
    {
        groaner->properties_E4.dummy.properties_E8[9].val8[3] = 4;
    }

    groaner->properties_E4.dummy.properties_E8[3].val32     = g_SysWork.playerWork_4C.player_0.position_18.vx;
    groaner->properties_E4.dummy.properties_E8[4].val32     = g_SysWork.playerWork_4C.player_0.position_18.vz;
    groaner->properties_E4.groaner.flags_E8 |= GroanerFlag_7;

    groaner->health_B0 = MAX(groaner->health_B0 - groaner->damage_B4.amount_C, Q12(0.0f));
    unkDist         = Math_Vector2MagCalc(groaner->damage_B4.position_0.vx, groaner->damage_B4.position_0.vz);

    // Set new heading angle.
    if (groaner->damage_B4.position_0.vx != Q12(0.0f) ||
        groaner->damage_B4.position_0.vz != Q12(0.0f))
    {
        newHeadingAngle = ratan2(groaner->damage_B4.position_0.vx, groaner->damage_B4.position_0.vz);
    }
    else
    {
        newHeadingAngle = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    }

    unkAngle = func_8005BF38((newHeadingAngle - groaner->rotation_24.vy) + FP_ANGLE(180.0f));

    groaner->properties_E4.dummy.properties_E8[5].val16[1] = CLAMP_LOW(unkDist >> 2, FP_ANGLE(90.0f));

    temp_v0 = FP_TO(groaner->damage_B4.position_0.vy, Q12_SHIFT);

    groaner->headingAngle_3C = newHeadingAngle;
    groaner->damage_B4.amount_C                             = Q12(0.0f);
    groaner->damage_B4.position_0.vz                        = Q12(0.0f);
    groaner->damage_B4.position_0.vy                        = Q12(0.0f);
    groaner->damage_B4.position_0.vx                        = Q12(0.0f);
    groaner->properties_E4.groaner.flags_E8 |= GroanerFlag_1;
    groaner->moveSpeed_38                                   = FP_TO(unkDist, Q12_SHIFT) / Q12(1.2f);
    groaner->field_34                                      += temp_v0 / Q12(1.2f);

    if (groaner->properties_E4.groaner.flags_E8 & GroanerFlag_3)
    {
        groaner->properties_E4.dummy.properties_E8[5].val16[1] = 0;

        if (groaner->health_B0 != Q12(0.0f))
        {
            if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == ANIM_STATUS(GroanerAnim_2, false))
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_4, true))
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 78;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_21, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_8)
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_8, true))
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 165;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_22, false);
            }
            else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) == GroanerAnim_14)
            {
                if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_14, true))
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    groaner->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 319;
                }

                groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_23, false);
            }
        }
    }
    else if (groaner->health_B0 > Q12(100.0f))
    {
        if (!(groaner->properties_E4.groaner.flags_E8 & GroanerFlag_10))
        {
            if (ABS(unkAngle) < FP_ANGLE(45.0f))
            {
                if ((ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0)) != GroanerAnim_2)
                {
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_2, false);
                }
            }
            else
            {
                if (unkAngle > FP_ANGLE(0.0f))
                {
                    if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_6)
                    {
                        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_6, false);
                    }
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_12)
                {
                    groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_12, false);
                }
            }

            groaner->model_0.controlState_2 = GroanerControl_5;
        }
    }
    else
    {
        func_80037DC4(groaner);

        groaner->flags_3E                                      |= CharaFlag_Unk2;
        groaner->properties_E4.groaner.flags_E8 |= GroanerFlag_3 | GroanerFlag_12;

        if (ABS(unkAngle) < FP_ANGLE(45.0f))
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_3, false);
            groaner->model_0.controlState_2  = GroanerControl_6;
        }
        else if (unkAngle > 0)
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_7, false);
            groaner->model_0.controlState_2  = GroanerControl_7;
        }
        else
        {
            groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_13, false);
            groaner->model_0.controlState_2  = GroanerControl_8;
        }
    }

    if (prevControlState != groaner->model_0.controlState_2 && prevControlState == GroanerControl_3)
    {
        g_SysWork.field_2284[3] &= ~(1 << 1);
    }
}
