void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner)
{
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s2;
    s32 temp_a0;

    if (groaner->properties_E4.groaner.field_10C > 0)
    {
        groaner->properties_E4.groaner.field_10C -= g_DeltaTime0;
        if (groaner->properties_E4.groaner.field_10C <= 0)
        {
            groaner->properties_E4.groaner.field_10C = 0;
            groaner->properties_E4.groaner.field_10E = 0;
        }
    }
    else if (groaner->properties_E4.groaner.field_10C < 0)
    {
        groaner->properties_E4.groaner.field_10C += g_DeltaTime0;
        if (groaner->properties_E4.groaner.field_10C >= 0)
        {
            func_8005DC1C(0x583, &groaner->position_18, 0x80, 0);
            groaner->properties_E4.groaner.field_10C = 0x2000;
        }
    }

    switch (groaner->properties_E4.groaner.field_10E)
    {
        default:
            temp_a0 = groaner->properties_E4.groaner.field_10F;
            if (temp_a0 == 4)
            {
                groaner->properties_E4.groaner.field_10C = 0x1000;
                groaner->properties_E4.groaner.field_10E = temp_a0;

                if (groaner->health_B0 > 0 && (groaner->properties_E4.groaner.flags_E8.val32 & 0x1008) == 8)
                {
                    func_8005DC1C(0x581, &groaner->position_18, 0x80, 0);
                }
                else
                {
                    func_8005DC1C(0x586, &groaner->position_18, 0x80, 0);
                }
                groaner->properties_E4.groaner.flags_E8.val16[0] &= 0xEFFF;
                break;
            }
            else if (groaner->properties_E4.groaner.field_10E != 2 && temp_a0 == 2)
            {
                groaner->properties_E4.groaner.field_10C = -0x4CC;
                groaner->properties_E4.groaner.field_10E = temp_a0;
                break;
            }

        case 4:
            // these 10E/10F checks load word from 0x10C and ANDs the upper 16 bits, not even a bitfield, weird
            if (groaner->properties_E4.groaner.field_10E == 0 && groaner->properties_E4.groaner.field_10F == 0 &&
                (groaner->health_B0 > 0))
            {
                if (groaner->model_0.anim_4.status_0 == 0x21)
                {
                    func_8005DC1C(0x582, &groaner->position_18, 0x40, 0);
                    groaner->properties_E4.groaner.field_10C = Rng_GenerateInt(0x800, 0x998);
                    groaner->properties_E4.groaner.field_10E = 3;
                }
                else if (groaner->model_0.anim_4.status_0 >> 1 != 0xA && groaner->model_0.anim_4.status_0 >> 1 != 0xF && !Rng_TestProbabilityBits(4))
                {
                    func_8005DC1C(0x57E, &groaner->position_18, ((FP_TO(groaner->health_B0, Q12_SHIFT) / 0x118000) >> 7) + 0x20, 0);
                    groaner->properties_E4.groaner.field_10C = Rng_GenerateInt(0x4CCC, 0x7FFE);
                    groaner->properties_E4.groaner.field_10E = 1;
                }
            }
            break;
    }

    groaner->properties_E4.groaner.field_10F = 0;

    temp_s1 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
    temp_s3 = (FP_TO(groaner->moveSpeed_38, Q12_SHIFT) / FP_MULTIPLY_PRECISE(groaner->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT) >> 6) + 0x40;
    temp_s2 = (FP_TO(groaner->moveSpeed_38, Q12_SHIFT) / FP_MULTIPLY_PRECISE(groaner->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT) >> 7) + Rng_TestProbabilityBits(3);

    if ((temp_s1 > 0x16D && temp_s1 < 0x172) || (temp_s1 > 0x176 && temp_s1 < 0x17E))
    {
        if (groaner->properties_E4.groaner.field_110 == 0)
        {
            func_8005DD44(0x585, &groaner->position_18, temp_s3, temp_s2);
            groaner->properties_E4.groaner.field_110 += 1;
        }
    }
    else
    {
        groaner->properties_E4.groaner.field_110 = 0;
    }

    if ((temp_s1 > 0x16F && temp_s1 < 0x175) || (temp_s1 > 0x186 && temp_s1 < 0x18D))
    {
        if (groaner->properties_E4.groaner.field_111 == 0)
        {
            func_8005DD44(0x585, &groaner->position_18, temp_s3, temp_s2);
            groaner->properties_E4.groaner.field_111 += 1;
        }
    }
    else
    {
        groaner->properties_E4.groaner.field_111 = 0;
    }
}