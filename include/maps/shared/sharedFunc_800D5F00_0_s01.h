extern VECTOR3 sharedData_800DE1D0_0_s01;

bool sharedFunc_800D5F00_0_s01(s_SubCharacter* const airScreamer)
{
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;
    q19_12 groundHeight;
    s32    temp_s0;
    s32    temp_v0_3;
    s32    var_fp;
    s32    i;
    s32    var_s3;
    s32    var_s4;
    s32    var_s5;
    s32    var_s6;
    s32    var_s7;
    s32    var_v1;
    s32    temp;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    posX = airScreamer->position_18.vx;
    posY = airScreamer->position_18.vy;
    posZ = airScreamer->position_18.vz;

    groundHeight = Collision_GroundHeightGet(posX, posZ);

    if (airScreamer->moveSpeed_38 != Q12(0.0f))
    {
        return false;
    }

    if (posY < groundHeight)
    {
        return false;
    }

    if (airScreamer->field_34 < 0)
    {
        return false;
    }

    if (airScreamer->rotationSpeed_2C.vx != 0)
    {
        return false;
    }

    if (airScreamer->rotationSpeed_2C.vy != 0)
    {
        return false;
    }

    if (airScreamer->rotationSpeed_2C.vz != 0)
    {
        return false;
    }

    if (airScreamer->field_32 != 0)
    {
        return false;
    }

    if (airScreamer->properties_E4.player.positionY_EC != 0)
    {
        return false;
    }

    var_s7 = 0;
    var_s6 = 0;
    var_fp = 1;

    for (var_s4 = 0x200; var_s4 <= 0x800; var_s4 += 0x800, var_fp++)
    {
        var_s5 = groundHeight + (var_fp << 7);

        for (i = 0, var_s3 = 0; i < 8; i++, var_s3 += 0x200)
        {
            temp_s0   = posX + FP_MULTIPLY_PRECISE(var_s4, Math_Sin(var_s3), Q12_SHIFT);
            temp_v0_3 = Collision_GroundHeightGet(temp_s0, FP_MULTIPLY_PRECISE(var_s4, Math_Cos(var_s3), Q12_SHIFT) + posZ);

            if (var_s5 < temp_v0_3)
            {
                var_s7 = (1 << i);
                var_s6 = 1;
                var_s5 = temp_v0_3;
            }
            else if (temp_v0_3 == var_s5)
            {
                var_s7 |= (1 << i);
                var_s6 += 1;
            }
        }

        if (var_s6)
        {
            var_v1 = FP_MULTIPLY(Rng_RandQ12(), var_s6, Q12_SHIFT);

            for (i = 0; i < 8; i++)
            {
                temp = 1 << i;
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

            var_s3 = i << 9;
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

    sharedFunc_800D81D0_0_s01(airScreamer);

    airScreamer->field_D4.radius_0 = 0;

    func_80069B24(&sharedData_800E2350_0_s01, &sharedData_800DE1D0_0_s01, airScreamer);

    sharedFunc_800D8244_0_s01(airScreamer);

    posX += sharedData_800E2350_0_s01.offset_0.vx;
    posY += sharedData_800E2350_0_s01.offset_0.vy;
    posZ += sharedData_800E2350_0_s01.offset_0.vz;

    groundHeight = Collision_GroundHeightGet(posX, posZ);

    posY = MIN(groundHeight, posY);

    airScreamer->position_18.vx = posX;
    airScreamer->position_18.vy = posY;
    airScreamer->position_18.vz = posZ;

    return false;

    #undef airScreamerProps
}
