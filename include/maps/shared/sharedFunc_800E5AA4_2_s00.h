void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner)
{
    s_800C4590 sp10;
    s16        var_s1;

    if (groaner->model_0.anim_4.status_0 != 0x15)
    {
        groaner->field_34 += g_DeltaTime2;
    }
    else
    {
        groaner->field_34 += g_DeltaTime2 >> 1;
    }

    if (groaner->properties_E4.groaner.flags_E8.val16[0] & 2)
    {
        if (!(groaner->properties_E4.groaner.flags_E8.val16[0] & 4))
        {
            if (groaner->model_0.anim_4.status_0 == 0x21)
            {
                Chara_MoveSpeedUpdate(groaner, 0x7330);
            }
            else
            {
                Chara_MoveSpeedUpdate(groaner, 0x1CCC);
            }
        }

        if (groaner->properties_E4.groaner.field_FE > 0)
        {
            var_s1 = func_8005BF38((groaner->headingAngle_3C - groaner->rotation_24.vy) + 0x800);

            if (ABS(var_s1) < 0x200)
            {
                var_s1 = -0x800;
            }
            else if (var_s1 > 0)
            {
                var_s1 = -0x400;
            }
            else
            {
                var_s1 = 0x400;
            }

            if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + var_s1)) > 0)
            {
                groaner->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, groaner->properties_E4.groaner.field_FE, Q12_SHIFT);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + var_s1)) <= 0)
                {
                    groaner->properties_E4.groaner.field_FE = 0;
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - var_s1;
                }
            }
            else
            {
                groaner->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, groaner->properties_E4.groaner.field_FE, Q12_SHIFT);

                if (func_8005BF38(groaner->headingAngle_3C - (groaner->rotation_24.vy + var_s1)) >= 0)
                {
                    groaner->properties_E4.groaner.field_FE = 0;
                    groaner->rotation_24.vy                 = groaner->headingAngle_3C - var_s1;
                }
            }

            groaner->properties_E4.groaner.field_FE = CLAMP_LOW(groaner->properties_E4.groaner.field_FE -
                                                                    FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x555, Q12_SHIFT),
                                                                0);
        }
        else if (groaner->moveSpeed_38 < 0x399)
        {
            groaner->properties_E4.groaner.flags_E8.val16[0] &= 0xFFFD;
        }
    }
    else if (groaner->model_0.anim_4.status_0 != 0x15)
    {
        groaner->headingAngle_3C = groaner->rotation_24.vy;
    }

    func_8005CB20(groaner, &sp10, groaner->properties_E4.groaner.field_F0, groaner->properties_E4.groaner.field_F2);

    groaner->properties_E4.groaner.field_F2 = 0;
    groaner->properties_E4.groaner.field_F0 = 0;

    if (groaner->position_18.vy == sp10.field_C)
    {
        groaner->properties_E4.groaner.flags_E8.val16[0] &= 0xFFFB;
    }
    else
    {
        groaner->properties_E4.groaner.flags_E8.val16[0] |= 4;
    }
}