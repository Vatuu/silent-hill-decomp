void sharedFunc_800E39D8_2_s00(s_SubCharacter* arg0)
{
    s16 temp_v0;
    s32 temp_a0_2;
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_s0_2;
    s32 temp_t0_2;
    s32 temp_t1;

    Chara_MoveSpeedUpdate5(arg0, 0x6000, FP_MULTIPLY_PRECISE(arg0->properties_E4.groaner.field_114, 0x800, Q12_SHIFT));

    if (arg0->properties_E4.groaner.flags_E8.val16[0] & 1)
    {
        temp_v0 = func_8005BF38(arg0->properties_E4.groaner.field_FC - arg0->rotation_24.vy);

        if (((g_DeltaTime0 / 3) >> 2) + 1 < ABS(temp_v0))
        {
            if (temp_v0 > 0)
            {
                arg0->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x2AA, Q12_SHIFT);
            }
            else
            {
                arg0->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x2AA, Q12_SHIFT);
            }
        }
        else
        {
            arg0->rotation_24.vy                           = arg0->properties_E4.groaner.field_FC;
            arg0->properties_E4.groaner.flags_E8.val16[0] &= 0xFFFE;
        }
    }
    else
    {
        if (func_8007029C(arg0, 0xD99, arg0->rotation_24.vy))
        {
            arg0->properties_E4.groaner.field_FC = func_8006F99C(arg0, 0xD99, arg0->rotation_24.vy);

            if (arg0->properties_E4.groaner.field_FC == 0x1000)
            {
                arg0->properties_E4.groaner.field_FC = -arg0->rotation_24.vy;
            }
            arg0->properties_E4.groaner.flags_E8.val16[0] |= 1;
        }
        else
        {
            temp_a2_2 = Rng_GenerateInt(0x2000, 0x5FFF);
            temp_t1   = arg0->position_18.vx;
            temp_a3   = arg0->properties_E4.groaner.targetPositionX_F4;
            temp_t0_2 = arg0->position_18.vz;
            temp_a0_2 = arg0->properties_E4.groaner.targetPositionZ_F8;

            if (temp_a2_2 < (temp_t1 - temp_a3 > temp_t0_2 - temp_a0_2 ? ABS(temp_t1 - temp_a3) + ABS((temp_t0_2 - temp_a0_2) >> 1) : ABS((temp_t1 - temp_a3) >> 1) + ABS(temp_t0_2 - temp_a0_2)))
            {
                if (ABS(func_8005BF38(arg0->rotation_24.vy - ratan2(arg0->position_18.vx - arg0->properties_E4.groaner.targetPositionX_F4,
                                                                    arg0->position_18.vz - arg0->properties_E4.groaner.targetPositionZ_F8))) < Rng_TestProbabilityBits(6) + 0x200)
                {
                    temp_s0_2 = arg0->properties_E4.groaner.targetPositionX_F4 + Rng_GenerateInt(-0x800, 0x7FF);

                    arg0->properties_E4.groaner.field_FC = Chara_HeadingAngleGet(arg0, 0xD99, temp_s0_2,
                                                                                 arg0->properties_E4.groaner.targetPositionZ_F8 + Rng_GenerateInt(-0x800, 0x7FF), 0x1000, 1);

                    if (arg0->properties_E4.groaner.field_FC == 0x1000)
                    {
                        arg0->properties_E4.groaner.field_FC = -arg0->rotation_24.vy;
                    }

                    arg0->properties_E4.groaner.flags_E8.val16[0] |= 1;
                }
            }
        }
    }

    if (arg0->model_0.anim_4.status_0 == 0x23 && (arg0->properties_E4.groaner.flags_E8.val32 & 0xA0) == 0xA0)
    {
        arg0->model_0.controlState_2                   = 2;
        arg0->model_0.anim_4.status_0                  = 0x20;
        arg0->properties_E4.groaner.flags_E8.val16[0] &= 0xFFFE;
        arg0->properties_E4.groaner.flags_E8.val16[0] |= 0x400;
    }
}