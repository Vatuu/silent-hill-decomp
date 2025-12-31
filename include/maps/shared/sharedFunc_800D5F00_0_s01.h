extern VECTOR3 sharedData_800DE1D0_0_s01;

bool sharedFunc_800D5F00_0_s01(s_SubCharacter* const chara)
{
    s32 x;
    s32 y;
    s32 z;
    s32 posY;
    s32 temp_s0;
    s32 temp_v0_3;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1;
    s32 temp;

    x = chara->position_18.vx;
    y = chara->position_18.vy;
    z = chara->position_18.vz;

    posY = Collision_GroundHeightGet(x, z);

    if (chara->moveSpeed_38 != Q12(0.0f))
    {
        return false;
    }

    if (y < posY)
    {
        return false;
    }

    if (chara->field_34 < 0)
    {
        return false;
    }

    if (chara->rotationSpeed_2C.vx != 0)
    {
        return false;
    }

    if (chara->rotationSpeed_2C.vy != 0)
    {
        return false;
    }

    if (chara->rotationSpeed_2C.vz != 0)
    {
        return false;
    }

    if (chara->field_32 != 0)
    {
        return false;
    }

    if (chara->properties_E4.player.positionY_EC != 0)
    {
        return false;
    }

    var_s7 = 0;
    var_s6 = 0;
    var_fp = 1;

    for (var_s4 = 0x200; var_s4 <= 0x800; var_s4 += 0x800, var_fp++)
    {
        var_s5 = posY + (var_fp << 7);

        for (var_s2 = 0, var_s3 = 0; var_s2 < 8; var_s2++, var_s3 += 0x200)
        {
            temp_s0   = x + FP_MULTIPLY_PRECISE(var_s4, Math_Sin(var_s3), Q12_SHIFT);
            temp_v0_3 = Collision_GroundHeightGet(temp_s0, FP_MULTIPLY_PRECISE(var_s4, Math_Cos(var_s3), Q12_SHIFT) + z);

            if (var_s5 < temp_v0_3)
            {
                var_s7 = (1 << var_s2);
                var_s6 = 1;
                var_s5 = temp_v0_3;
            }
            else if (temp_v0_3 == var_s5)
            {
                var_s7 |= (1 << var_s2);
                var_s6 += 1;
            }
        }

        if (var_s6)
        {
            var_v1 = FP_MULTIPLY(Rng_RandQ12(), var_s6, Q12_SHIFT);

            for (var_s2 = 0; var_s2 < 8; var_s2++)
            {
                temp = (1 << var_s2);

                if (!(var_s7 & temp))
                {
                    continue;
                }

                if (!var_v1)
                {
                    break;
                }

                var_v1--;
            }

            var_s3 = var_s2 << 9;
            break;
        }
    }

    if (var_s6 == 0)
    {
        return true;
    }

    sharedData_800E21D0_0_s01.flags_0 |= 0x20000000;
    var_s4                             = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);

    sharedData_800DE1D0_0_s01.vx = FP_MULTIPLY_PRECISE(var_s4, Math_Sin(var_s3), Q12_SHIFT);
    sharedData_800DE1D0_0_s01.vy = var_s4;
    sharedData_800DE1D0_0_s01.vz = FP_MULTIPLY_PRECISE(var_s4, Math_Cos(var_s3), Q12_SHIFT);

    sharedFunc_800D81D0_0_s01(chara);

    chara->field_D4.radius_0 = 0;

    func_80069B24(&sharedData_800E2350_0_s01, &sharedData_800DE1D0_0_s01, chara);

    sharedFunc_800D8244_0_s01(chara);

    x += sharedData_800E2350_0_s01.offset_0.vx;
    y += sharedData_800E2350_0_s01.offset_0.vy;
    z += sharedData_800E2350_0_s01.offset_0.vz;

    posY = Collision_GroundHeightGet(x, z);

    y = MIN(posY, y);

    chara->position_18.vx = x;
    chara->position_18.vy = y;
    chara->position_18.vz = z;

    return false;
}
