s32 sharedFunc_800E939C_2_s02(s_SubCharacter* romper)
{
    s32    i;
    q19_12 relAnimTime;
    u32    var_a3;

    #define romperProps romper->properties_E4.romper

    if (romper->model_0.anim_4.time_4 <  Q12(147.0f) ||
        romper->model_0.anim_4.time_4 >= Q12(163.0f))
    {
        return 0;
    }

    relAnimTime = romper->model_0.anim_4.time_4 - Q12(147.0f);
    if (relAnimTime < romperProps.field_F4)
    {
        romperProps.field_F0 = 6;
        romperProps.field_F4 = Q12(0.0f);
        romper->moveSpeed_38 = 89; // TODO: Clean float. Maybe it was a fraction?
    }

    var_a3 = 0;
    for (i = 0; i < 7; i++)
    {
        if (sharedData_800ED2D4_2_s02[i].field_0 > romperProps.field_F4 ||
            romperProps.field_F4 >= sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            continue;
        }

        if (relAnimTime < sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            var_a3 += Q12_MULT_PRECISE(relAnimTime - romperProps.field_F4, sharedData_800ED2D4_2_s02[i].field_4);
            break;
        }

        var_a3 += Q12_MULT_PRECISE(sharedData_800ED2D4_2_s02[i + 1].field_0 - romperProps.field_F4, sharedData_800ED2D4_2_s02[i].field_4);
        romperProps.field_F4 = sharedData_800ED2D4_2_s02[i + 1].field_0;
    }

    romperProps.field_F4 = relAnimTime;
    return (var_a3 >> 31) + var_a3;

    #undef romperProps
}
