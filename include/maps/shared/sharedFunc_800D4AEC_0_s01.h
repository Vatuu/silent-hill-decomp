bool sharedFunc_800D4AEC_0_s01(s_SubCharacter* chara, VECTOR3* arg1, VECTOR3* arg2, VECTOR3* arg3)
{
    s32      sp18;
    VECTOR3* var_s0;
    s32      temp_v1;
    s32      temp_s0;
    q19_12   unkY;
    q19_12   offsetX;
    q19_12   offsetZ;
    s32      var_a0;
    s32      i;
    s32      var_v1;
    s32      temp_v0;
    s32      temp_v0_2;
    q19_12   posX;
    q19_12   posY;
    q19_12   posZ;
    s32      temp;
    s32      temp2;
    s32      temp3;

    if (arg1 == NULL)
    {
        var_s0 = &chara->position_18;
    }
    else
    {
        var_s0 = arg1;
    }

    posX = var_s0->vx;
    posY = var_s0->vy;
    posZ = var_s0->vz;

    offsetX = arg2->vx - posX;
    offsetZ = arg2->vz - posZ;

    sharedData_800DE1A0_0_s01.vx = offsetX;
    sharedData_800DE1A0_0_s01.vz = offsetZ;

    if (sharedFunc_800D4A80_0_s01(chara) == 1)
    {
        i                            = 0;
        sharedData_800DE1A0_0_s01.vy = 0;
    }
    else
    {
        i                            = arg2->vy - posY;
        sharedData_800DE1A0_0_s01.vy = i;
    }

    temp_s0 = g_SysWork.player_4C.chara_0.field_E1_0;

    g_SysWork.player_4C.chara_0.field_E1_0 = 0;

    sp18 = func_8006DB3C(&sharedData_800E2330_0_s01, var_s0, &sharedData_800DE1A0_0_s01, chara);

    g_SysWork.player_4C.chara_0.field_E1_0 = temp_s0;
    offsetX                                = sharedData_800E2330_0_s01.field_4.vx - posX;
    offsetZ                                = sharedData_800E2330_0_s01.field_4.vz - posZ;

    func_8006F250(sharedData_800E2370_0_s01, posX, posZ, offsetX, offsetZ);

    var_a0    = sharedData_800E2370_0_s01[1];
    temp_v1   = chara->field_C8.field_0;
    temp_v0_2 = 1;

    if (i < 0 && var_a0 < (posY + temp_v1))
    {
        if ((sharedData_800E2330_0_s01.field_4.vy + temp_v1) < var_a0)
        {
            sharedData_800E2330_0_s01.field_4.vy = var_a0 - temp_v1;
        }
    }
    else if ((sharedData_800E2330_0_s01.field_4.vy + temp_v1) < var_a0)
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
                var_v1 = FP_TO(temp, Q12_SHIFT) / sharedData_800E2330_0_s01.field_14;
            }

            sp18  = true;
            temp3 = FP_MULTIPLY_PRECISE(offsetX, var_v1, Q12_SHIFT);
            temp2 = FP_MULTIPLY_PRECISE(i, var_v1, Q12_SHIFT);

            sharedData_800E2330_0_s01.field_14   = temp;
            sharedData_800E2330_0_s01.field_0    = temp_v0_2;
            sharedData_800E2330_0_s01.field_4.vx = temp3 + posX;
            sharedData_800E2330_0_s01.field_4.vy = temp2 + posY;
            sharedData_800E2330_0_s01.field_18   = sharedData_800E2330_0_s01.field_4.vy;

            temp2                                 = FP_MULTIPLY_PRECISE(offsetZ, var_v1, Q12_SHIFT);
            sharedData_800E2330_0_s01.field_4.vz  = temp2 + posZ;
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
                temp_v0                              = (Rng_RandQ12() / 2) + Q12(1.5f);
                sharedData_800E2330_0_s01.field_4.vy = sharedData_800E2330_0_s01.field_18 - temp_v0;
            }
            else
            {
                unkY  = func_80080884(chara->position_18.vx, chara->position_18.vz);
                temp_v0    = Rng_RandQ12() / 2 + Q12(1.5f);
                unkY -= temp_v0;

                temp_v0                              = (Rng_RandQ12() / 2) - Q12(0.25f);
                sharedData_800E2330_0_s01.field_4.vy = chara->position_18.vy - temp_v0;

                if (unkY < sharedData_800E2330_0_s01.field_4.vy)
                {
                    sharedData_800E2330_0_s01.field_4.vy = unkY;
                }
            }
        }
    }

    return !sp18;
}