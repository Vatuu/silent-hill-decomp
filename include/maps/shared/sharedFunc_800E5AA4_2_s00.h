void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner)
{
    s_800C4590 sp10;
    q3_12      angleDeltaToHeading;

    #define groanerProps groaner->properties_E4.groaner

    if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->field_34 += g_DeltaTime2;
    }
    else
    {
        groaner->field_34 += g_DeltaTime2 >> 1;
    }

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_1)
    {
        if (!(groanerProps.flags_E8.val16[0] & GroanerFlag_2))
        {
            if (groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_16, true))
            {
                Chara_MoveSpeedUpdate(groaner, Q12(7.2f) - 3);
            }
            else
            {
                Chara_MoveSpeedUpdate(groaner, Q12(1.8f));
            }
        }

        if (groanerProps.field_FE > Q12(0.0f))
        {
            angleDeltaToHeading = func_8005BF38((groaner->headingAngle_3C - groaner->rotation_24.vy) + FP_ANGLE(180.0f));
            if (ABS(angleDeltaToHeading) < FP_ANGLE(45.0f))
            {
                angleDeltaToHeading = FP_ANGLE(-180.0f);
            }
            else if (angleDeltaToHeading > FP_ANGLE(0.0f))
            {
                angleDeltaToHeading = FP_ANGLE(-90.0f);
            }
            else
            {
                angleDeltaToHeading = FP_ANGLE(90.0f);
            }

            if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) > FP_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, groanerProps.field_FE);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) <= FP_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - angleDeltaToHeading;
                }
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, groanerProps.field_FE);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + angleDeltaToHeading)) >= FP_ANGLE(0.0f))
                {
                    groanerProps.field_FE = Q12(0.0f);
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - angleDeltaToHeading;
                }
            }

            groanerProps.field_FE = CLAMP_LOW(groanerProps.field_FE - FP_MULTIPLY_PRECISE(g_DeltaTime0,
                                                                                          Q12(1.0f / 3.0f),
                                                                                          Q12_SHIFT),
                                              Q12(0.0f));
        }
        else if (groaner->moveSpeed_38 < Q12(0.225f))
        {
            groanerProps.flags_E8.val16[0] &= ~GroanerFlag_1;
        }
    }
    else if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(GroanerAnim_10, true))
    {
        groaner->headingAngle_3C = groaner->rotation_24.vy;
    }

    func_8005CB20(groaner, &sp10, groanerProps.field_F0, groanerProps.field_F2);

    groanerProps.field_F2 = Q12(0.0f);
    groanerProps.field_F0 = Q12(0.0f);

    if (groaner->position_18.vy == sp10.field_C)
    {
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_2;
    }
    else
    {
        groanerProps.flags_E8.val16[0] |= GroanerFlag_2;
    }

    #undef groanerProps
}
