s32 sharedFunc_800D4AEC_0_s01(s_SubCharacter* arg0, VECTOR3* arg1, VECTOR3* arg2, VECTOR3* arg3)
{
    s32      sp18;
    VECTOR3* var_s0;
    s32      temp_v1;
    s32      temp_s0;
    s32      temp_s0_3;
    s32      temp_s3;
    s32      temp_s4;
    s32      var_a0;
    s32      var_s5;
    s32      var_v1;
    s32      temp_v0;
    s32      temp_v0_2;
    s32      vx0;
    s32      vy0;
    s32      vz0;
    s32      temp;
    s32      temp2;
    s32      temp3;

    if (arg1 == NULL)
    {
        var_s0 = &arg0->position_18;
    }
    else
    {
        var_s0 = arg1;
    }

    vx0 = var_s0->vx;
    vy0 = var_s0->vy;
    vz0 = var_s0->vz;

    temp_s3 = arg2->vx - vx0;
    temp_s4 = arg2->vz - vz0;

    sharedData_800DE1A0_0_s01.vx = temp_s3;
    sharedData_800DE1A0_0_s01.vz = temp_s4;

    if (sharedFunc_800D4A80_0_s01(arg0) == 1)
    {
        var_s5                       = 0;
        sharedData_800DE1A0_0_s01.vy = 0;
    }
    else
    {
        var_s5                       = arg2->vy - vy0;
        sharedData_800DE1A0_0_s01.vy = var_s5;
    }

    temp_s0 = g_SysWork.player_4C.chara_0.field_E1_0;

    g_SysWork.player_4C.chara_0.field_E1_0 = 0;

    sp18 = func_8006DB3C(&sharedData_800E2330_0_s01, var_s0, &sharedData_800DE1A0_0_s01, arg0);

    g_SysWork.player_4C.chara_0.field_E1_0 = temp_s0;
    temp_s3                                = sharedData_800E2330_0_s01.field_4.vx - vx0;
    temp_s4                                = sharedData_800E2330_0_s01.field_4.vz - vz0;

    func_8006F250(sharedData_800E2370_0_s01, vx0, vz0, temp_s3, temp_s4);

    var_a0    = sharedData_800E2370_0_s01[1];
    temp_v1   = arg0->field_C8.field_0;
    temp_v0_2 = 1;

    if (var_s5 < 0 && var_a0 < (vy0 + temp_v1))
    {
        if ((sharedData_800E2330_0_s01.field_4.vy + temp_v1) < var_a0)
        {
            sharedData_800E2330_0_s01.field_4.vy = var_a0 - temp_v1;
        }
    }
    else if (sharedData_800E2330_0_s01.field_4.vy + temp_v1 < var_a0)
    {
        temp = sharedData_800E2370_0_s01[0];

        if (temp < sharedData_800E2330_0_s01.field_14)
        {
            if (sharedData_800E2330_0_s01.field_14 == 0)
            {
                var_v1 = 0;
            }
            else
            {
                var_v1 = FP_TO(temp, 0xC) / sharedData_800E2330_0_s01.field_14;
            }

            sp18  = true;
            temp3 = FP_MULTIPLY_PRECISE(temp_s3, var_v1, Q12_SHIFT);
            temp2 = FP_MULTIPLY_PRECISE(var_s5, var_v1, Q12_SHIFT);

            sharedData_800E2330_0_s01.field_14   = temp;
            sharedData_800E2330_0_s01.field_0    = temp_v0_2;
            sharedData_800E2330_0_s01.field_4.vx = temp3 + vx0;
            sharedData_800E2330_0_s01.field_4.vy = temp2 + vy0;
            sharedData_800E2330_0_s01.field_18   = sharedData_800E2330_0_s01.field_4.vy;

            temp2                                 = FP_MULTIPLY_PRECISE(temp_s4, var_v1, Q12_SHIFT);
            sharedData_800E2330_0_s01.field_4.vz  = temp2 + vz0;
            sharedData_800E2330_0_s01.field_4.vy += 0; // @hack
        }
    }

    if (arg3 != NULL)
    {
        *arg3 = sharedData_800E2330_0_s01.field_4;

        if (sp18 != false)
        {
            if (sharedFunc_800D5274_0_s01() < sharedData_800E2330_0_s01.field_18)
            {
                temp_v0                              = Rng_RandQ12() / 2 + 0x1800;
                sharedData_800E2330_0_s01.field_4.vy = sharedData_800E2330_0_s01.field_18 - temp_v0;
            }
            else
            {
                temp_s0_3  = func_80080884(arg0->position_18.vx, arg0->position_18.vz);
                temp_v0    = Rng_RandQ12() / 2 + 0x1800;
                temp_s0_3 -= temp_v0;

                temp_v0                              = Rng_RandQ12() / 2 - 0x400;
                sharedData_800E2330_0_s01.field_4.vy = arg0->position_18.vy - temp_v0;

                if (temp_s0_3 < sharedData_800E2330_0_s01.field_4.vy)
                {
                    sharedData_800E2330_0_s01.field_4.vy = temp_s0_3;
                }
            }
        }
    }
    return !sp18;
}