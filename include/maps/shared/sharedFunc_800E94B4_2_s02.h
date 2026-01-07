s32 sharedFunc_800E94B4_2_s02(s_SubCharacter* romper)
{
    s32 i;
    s32 temp_a0;
    u32 var_t4;

    if (romper->model_0.anim_4.time_4 < 0x6D000 || romper->model_0.anim_4.time_4 > 0x82FFF)
    {
        return 0;
    }

    temp_a0 = romper->model_0.anim_4.time_4 - 0x6D000;

    if (temp_a0 < romper->properties_E4.romper.field_F4)
    {
        romper->properties_E4.romper.field_F0 = -0x194;
        romper->properties_E4.romper.field_F4 = 0;
        romper->moveSpeed_38                  = -0x418;
    }

    var_t4 = 0;

    for (i = 0; i < 22; i++)
    {
        if (romper->properties_E4.romper.field_F4 < FP_TO(i, Q12_SHIFT) ||
            romper->properties_E4.romper.field_F4 >= FP_TO(i + 1, Q12_SHIFT))
        {
            continue;
        }

        if (temp_a0 >= FP_TO(i + 1, Q12_SHIFT))
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
                    romper->moveSpeed_38                  = 0x1449;
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
            var_t4               += Q12_MULT_PRECISE(temp_a0 - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_0);
            romper->moveSpeed_38 += Q12_MULT_PRECISE(temp_a0 - romper->properties_E4.romper.field_F4, sharedData_800ED314_2_s02[i].field_4);
            break;
        }
    }

    romper->properties_E4.romper.field_F4 = temp_a0;

    if ((temp_a0 > 0xFFF && temp_a0 < 0x7000) || (temp_a0 > 0xAFFF && temp_a0 < 0x12000))
    {
        sharedData_800EC950_2_s02 = 0xC000;
    }
    else
    {
        sharedData_800EC950_2_s02 = 0x18000;
    }

    return (var_t4 >> 0x1F) + var_t4;
}