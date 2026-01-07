s32 sharedFunc_800E939C_2_s02(s_SubCharacter* romper)
{
    s32 i;
    s32 temp_v1;
    u32 var_a3;

    if (romper->model_0.anim_4.time_4 < 0x93000 || romper->model_0.anim_4.time_4 > 0xA2FFF)
    {
        return 0;
    }

    temp_v1 = romper->model_0.anim_4.time_4 - 0x93000;

    if (temp_v1 < romper->properties_E4.romper.field_F4)
    {
        romper->properties_E4.romper.field_F0 = 6;
        romper->properties_E4.romper.field_F4 = 0;
        romper->moveSpeed_38                  = 0x59;
    }

    var_a3 = 0;

    for (i = 0; i < 7; i++)
    {
        if (sharedData_800ED2D4_2_s02[i].field_0 > romper->properties_E4.romper.field_F4 ||
            romper->properties_E4.romper.field_F4 >= sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            continue;
        }

        if (temp_v1 < sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            var_a3 += Q12_MULT_PRECISE(temp_v1 - romper->properties_E4.romper.field_F4, sharedData_800ED2D4_2_s02[i].field_4);
            break;
        }

        var_a3 += Q12_MULT_PRECISE(sharedData_800ED2D4_2_s02[i + 1].field_0 - romper->properties_E4.romper.field_F4, sharedData_800ED2D4_2_s02[i].field_4);

        romper->properties_E4.romper.field_F4 = sharedData_800ED2D4_2_s02[i + 1].field_0;
    }

    romper->properties_E4.romper.field_F4 = temp_v1;

    return (var_a3 >> 0x1F) + var_a3;
}