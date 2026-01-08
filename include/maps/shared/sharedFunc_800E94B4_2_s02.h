s32 sharedFunc_800E94B4_2_s02(s_SubCharacter* romper)
{
    s32 i;
    s32 relAnimTime;
    u32 var_t4;

    if (romper->model_0.anim_4.time_4 <  Q12(109.0f) ||
        romper->model_0.anim_4.time_4 >= Q12(131.0f))
    {
        return 0;
    }

    relAnimTime = romper->model_0.anim_4.time_4 - Q12(109.0f);
    if (relAnimTime < romper->properties_E4.romper.field_F4)
    {
        romper->properties_E4.romper.field_F0 = -0x194;
        romper->properties_E4.romper.field_F4 = Q12(0.0f);
        romper->moveSpeed_38                  = Q12(-0.256f);
    }

    var_t4 = 0;
    for (i = 0; i < 22; i++)
    {
        if (romper->properties_E4.romper.field_F4 < FP_TO(i, Q12_SHIFT) ||
            romper->properties_E4.romper.field_F4 >= FP_TO(i + 1, Q12_SHIFT))
        {
            continue;
        }

        if (relAnimTime >= FP_TO(i + 1, Q12_SHIFT))
        {
            switch (i + 1)
            {
                case 1:
                    if (romper->field_34 == 0)
                    {
                        romper->field_34 = -0x2A77;
                    }
                    break;

                case 11:
                    if (romper->field_34 == 0)
                    {
                        romper->field_34 = -0x30FF;
                    }
                    break;

                case 7:
                    var_t4                                = 0;
                    romper->properties_E4.romper.field_F0 = 0x112;
                    romper->moveSpeed_38                  = Q12(1.268f);
                    break;

                case 18:
                    var_t4                                = 0;
                    romper->properties_E4.romper.field_F0 = 0x3F;
                    romper->moveSpeed_38                  = 0xBF0;
                    break;

                default:
                    var_t4               += Q12_MULT_PRECISE(FP_TO(i + 1, Q12_SHIFT) - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_0);
                    romper->moveSpeed_38 += Q12_MULT_PRECISE(FP_TO(i + 1, Q12_SHIFT) - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_4);
                    break;
            }
            romper->properties_E4.romper.field_F4 = FP_TO(i + 1, Q12_SHIFT);
        }
        else
        {
            var_t4               += Q12_MULT_PRECISE(relAnimTime - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_0);
            romper->moveSpeed_38 += Q12_MULT_PRECISE(relAnimTime - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_4);
            break;
        }
    }

    romper->properties_E4.romper.field_F4 = relAnimTime;

    if ((relAnimTime >= Q12(1.0f) && relAnimTime < Q12(7.0f)) ||
        (relAnimTime >= Q12(11.0f) && relAnimTime < Q12(18.0f)))
    {
        sharedData_800EC950_2_s02 = Q12(12.0f);
    }
    else
    {
        sharedData_800EC950_2_s02 = Q12(24.0f);
    }

    return (var_t4 >> 31) + var_t4;
}
