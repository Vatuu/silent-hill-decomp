s32 sharedFunc_800DE250_2_s00(s_SubCharacter* arg0)
{
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s6;
    u32 temp_v1;
    s32 var_fp;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s3;
    s32 var_s5;
    s32 var_s7;
    s32 temp;
    s32 temp2;

    sp1C   = 0;
    var_fp = 0;
    sp20   = 0;
    sp2C   = 0;
    var_s7 = -1;

    sp10 = arg0->position_18.vx;
    sp14 = arg0->position_18.vz;
    sp18 = arg0->properties_E4.airScreamer.groundHeight_124;

    var_s0  = arg0->properties_E4.airScreamer.position_104.vx;
    temp_s1 = arg0->properties_E4.airScreamer.position_104.vz;

    sp34 = sharedFunc_800D4A80_0_s01(arg0) == 1;

    temp_s2  = sp10 - var_s0;
    var_s0_3 = sp14 - temp_s1;

    sp24    = ratan2(temp_s2, var_s0_3);
    sp28    = SquareRoot12(FP_SQUARE_PRECISE(temp_s2, Q12_SHIFT) + FP_SQUARE_PRECISE(var_s0_3, Q12_SHIFT));
    temp_s6 = (Rng_RandQ12() * 4) + 0x4000;

    if (Rng_RandQ12() < 0x800)
    {
        sp30 = 0x100;
    }
    else
    {
        sp30 = -0x100;
    }

    for (var_s5 = 0, var_s3 = sp24; var_s5 < 0x10; var_s5++, var_s3 += sp30)
    {
        // same as
        // if (FP_ANGLE_NORM_S(var_s3 - sp24) >= 0x6AA || FP_ANGLE_NORM_S(var_s3 - sp24) < -0x6AA)
        // but that uses sltiu instead of sltu..
        temp_v1 = 0xD54;
        temp_v1 = temp_v1 < FP_ANGLE_NORM_S(var_s3 - sp24) + 0x6AA;

        if (!temp_v1)
        {
            temp_s2 = FP_MULTIPLY_PRECISE(temp_s6, Math_Sin(var_s3), Q12_SHIFT);
            temp_a1 = FP_MULTIPLY_PRECISE(temp_s6, Math_Cos(var_s3), Q12_SHIFT);

            temp_a2                      = sp10 + temp_s2;
            sharedData_800F21CC_2_s00.vx = temp_a2;

            temp_a1                     += sp14;
            sharedData_800F21CC_2_s00.vz = temp_a1;

            if (sp34 == 0)
            {
                var_s0_2 = Collision_GroundHeightGet(temp_a2, temp_a1);

                if (sp18 < var_s0_2)
                {
                    var_s0_2 = sp18;
                }

                var_s0_2 -= 0x1800 + (Rng_RandQ12() / 2);

                if (var_s0_2 < sharedFunc_800D5274_0_s01())
                {
                    var_s0_2 = sharedFunc_800D5274_0_s01();
                }
                sharedData_800F21CC_2_s00.vy = var_s0_2;
            }

            sharedFunc_800D4AEC_0_s01(arg0, NULL, &sharedData_800F21CC_2_s00, &sharedData_800F21CC_2_s00);

            temp  = Math_Distance2dGet(&arg0->properties_E4.airScreamer.position_104, &sharedData_800F21CC_2_s00);
            temp2 = temp + (Math_Distance2dGet(&arg0->position_18, &sharedData_800F21CC_2_s00) * 2);

            if (var_s7 < temp2)
            {
                var_s0_3 = temp;
                sp2C     = var_s0_3 < sp28;
                var_s7   = temp2 + 0x199;

                sp1C   = sharedData_800F21CC_2_s00.vx;
                sp20   = sharedData_800F21CC_2_s00.vy;
                var_fp = sharedData_800F21CC_2_s00.vz;
            }
        }
    }

    arg0->properties_E4.airScreamer.targetPosition_F8.vx = sp1C;
    arg0->properties_E4.airScreamer.targetPosition_F8.vz = var_fp;

    if (sp34 != 0)
    {
        arg0->properties_E4.airScreamer.targetPosition_F8.vy = Collision_GroundHeightGet(sp1C, var_fp);
    }
    else
    {
        arg0->properties_E4.airScreamer.targetPosition_F8.vy = sp20;
    }

    sharedFunc_800D4E84_0_s01(arg0);

    return sp2C;
}