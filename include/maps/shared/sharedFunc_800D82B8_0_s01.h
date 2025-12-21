void sharedFunc_800D82B8_0_s01(s_SubCharacter* airScreamer)
{
    s32            sp10;
    GsCOORDINATE2* coord;
    SVECTOR*       temp_a0;
    SVECTOR*       temp_s5;
    s32            var_t0;
    s32            temp_a0_2;
    s32            temp_v1;
    s32            var_a3;
    s32            var_s0;
    s32            i;
    s32            var_s2_2;
    s32            var_s3;
    s32            var_t1;
    VECTOR3*       var_t0_2;
    s16            new_var;
    s16            new_var2;
    s16            new_var3;
    s16            new_var4;
    s32            temp;
    s32            temp2;
    s32            vx;
    s32            vy;
    s32            vz;

    sp10 = sharedFunc_800D4A80_0_s01(airScreamer);
    if (sp10 != 0)
    {
        var_a3 = 0;
        var_s3 = 1;

        temp_s5 = sharedData_800CAA98_0_s01.ptr_D48[4];
        coord   = sharedData_800E21D0_0_s01.coords_8;

        temp_a0  = &temp_s5[1];
        var_s0   = temp_a0->pad;
        var_t0   = temp_s5->pad;
        var_t0_2 = &sharedData_800E21D0_0_s01.matrices_C;

        for (i = 1; var_s0 != NO_VALUE; i++)
        {
            if (var_s0 != var_t0)
            {
                func_800805BC(&var_t0_2[var_a3], &temp_s5[var_a3], &coord[var_t0], var_s3 - var_a3);
                var_t0 = var_s0;
                var_a3 = var_s3;
            }

            var_s3++;
            var_s0 = temp_s5[var_s3].pad;
        }

        func_800805BC(&var_t0_2[var_a3], &temp_s5[var_a3], &coord[var_t0], var_s3 - var_a3);

        var_t1   = 0;
        var_s0   = INT_MAX + 1;
        var_s2_2 = INT_MAX;

        vx = airScreamer->position_18.vx;
        vy = airScreamer->position_18.vy;
        vz = airScreamer->position_18.vz;

        for (i = i - 1; i >= 0; i--)
        {
            temp   = var_t0_2[i].vx - vx;
            var_a3 = var_t0_2[i].vy - vy;
            temp2  = var_t0_2[i].vz - vz;

            temp_a0_2 = FP_SQUARE_PRECISE(temp, Q12_SHIFT) + FP_SQUARE_PRECISE(temp2, Q12_SHIFT);
            if (var_t1 < temp_a0_2)
            {
                var_t1 = temp_a0_2;
            }

            if (var_s0 < var_a3)
            {
                var_s0 = var_a3;
            }

            if (var_a3 < var_s2_2)
            {
                var_s2_2 = var_a3;
            }
        }

        var_t1  = SquareRoot12(var_t1) >> 1;
        temp_v1 = (var_s0 + var_s2_2) / 2;

        airScreamer->field_D4.field_2 = var_t1;

        var_s0   += (var_s0 - temp_v1) >> 2;
        var_s2_2 += (var_s2_2 - temp_v1) >> 2;

        airScreamer->field_C8.field_6 = temp_v1;
        airScreamer->field_C8.field_8 = temp_v1;

        airScreamer->field_C8.field_4 = var_s0;
        airScreamer->field_C8.field_0 = var_s2_2;

        new_var  = sharedData_800CAA98_0_s01.field_D70[sp10][0];
        new_var2 = sharedData_800CAA98_0_s01.field_D70[sp10][1];

        airScreamer->field_E1_0       = 3;
        airScreamer->field_C8.field_2 = new_var;
        airScreamer->field_D4.field_0 = new_var2;
    }
    else
    {
        new_var3 = sharedData_800CAA98_0_s01.field_D70[0][0];
        new_var4 = sharedData_800CAA98_0_s01.field_D70[0][1];

        airScreamer->field_D4.field_0 = new_var4;
        airScreamer->field_D4.field_2 = 0;

        airScreamer->field_C8.field_4 = Q12(0.0f);
        airScreamer->field_C8.field_0 = Q12(0.0f);
        airScreamer->field_C8.field_6 = Q12(0.0f);
        airScreamer->field_C8.field_8 = Q12(0.0f);
        airScreamer->field_C8.field_2 = new_var3;
        airScreamer->field_E1_0       = 0;
    }

    if ((airScreamer->properties_E4.player.afkTimer_E8 & 0xF) == 3)
    {
        airScreamer->field_C8.field_2 = FP_MULTIPLY_PRECISE(airScreamer->field_C8.field_2, Q12(1.125f), Q12_SHIFT);
        airScreamer->field_D4.field_2 = FP_MULTIPLY_PRECISE(airScreamer->field_D4.field_2, Q12(1.125f), Q12_SHIFT);
    }

    if (airScreamer->properties_E4.player.flags_11C & PlayerFlag_Unk12)
    {
        airScreamer->field_C8.field_2 = FP_MULTIPLY_PRECISE(airScreamer->field_C8.field_2, Q12(0.875f), Q12_SHIFT);
        airScreamer->field_D4.field_2 = FP_MULTIPLY_PRECISE(airScreamer->field_D4.field_2, Q12(0.875f), Q12_SHIFT);
    }

    airScreamer->field_D8.offsetX_0 = Q12(0.0f);
    airScreamer->field_D8.offsetZ_2 = Q12(0.0f);
    airScreamer->field_D8.offsetX_4 = Q12(0.0f);
    airScreamer->field_D8.offsetZ_6 = Q12(0.0f);
}
