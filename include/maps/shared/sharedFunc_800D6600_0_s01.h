void sharedFunc_800D6600_0_s01(s_SubCharacter* arg0)
{
    s32 sp18;
    s32 sp1C;
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0_3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    u32 temp_v0_9;
    s32 temp;

    sp18      = FP_MULTIPLY_PRECISE(arg0->damage_B4.position_0.vx, 0x3000, Q12_SHIFT);
    temp_fp   = FP_MULTIPLY_PRECISE(arg0->damage_B4.position_0.vy, 0x3000, Q12_SHIFT);
    temp_v0_3 = FP_MULTIPLY_PRECISE(arg0->damage_B4.position_0.vz, 0x3000, Q12_SHIFT);

    arg0->damage_B4.position_0.vx = 0;
    arg0->damage_B4.position_0.vy = 0;
    arg0->damage_B4.position_0.vz = 0;

    sp1C = SquareRoot12(FP_SQUARE_PRECISE(sp18, Q12_SHIFT) + FP_SQUARE_PRECISE(temp_fp, Q12_SHIFT) + FP_SQUARE_PRECISE(temp_v0_3, Q12_SHIFT));

    temp_s1 = arg0->properties_E4.dummy.properties_E8[1].val32;
    temp_s0 = arg0->properties_E4.dummy.properties_E8[2].val16[0];
    temp_s2 = arg0->properties_E4.dummy.properties_E8[2].val16[1];

    if (temp_s1 == 0)
    {
        var_s4 = 0;
        var_s6 = 0;
        var_s5 = 0;
    }
    else
    {
        var_s6  = FP_MULTIPLY_PRECISE(temp_s1, Math_Sin(temp_s0), Q12_SHIFT);
        temp_s0 = FP_MULTIPLY_PRECISE(temp_s1, Math_Cos(temp_s0), Q12_SHIFT);

        if (temp_s0 < 0)
        {
            temp_s0  = -temp_s0;
            temp_s2 ^= 0x800;
        }

        var_s5 = FP_MULTIPLY_PRECISE(temp_s0, Math_Sin(temp_s2), Q12_SHIFT);
        var_s4 = FP_MULTIPLY_PRECISE(temp_s0, Math_Cos(temp_s2), Q12_SHIFT);
    }

    if (sp1C > 0)
    {
        var_s5 += sp18;
        var_s6 += temp_fp;
        var_s4 += temp_v0_3;
    }

    if (!(var_s5 | var_s6 | var_s4))
    {
        arg0->properties_E4.dummy.properties_E8[1].val32    = 0;
        arg0->properties_E4.dummy.properties_E8[2].val16[0] = 0;
        arg0->properties_E4.dummy.properties_E8[2].val16[1] = arg0->rotation_24.vy;
        return;
    }

    sharedData_800DE210_0_s01.vx = var_s5;
    sharedData_800DE210_0_s01.vy = var_s6;
    sharedData_800DE210_0_s01.vz = var_s4;

    sharedData_800DE200_0_s01.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, var_s5, Q12_SHIFT);
    sharedData_800DE200_0_s01.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, var_s6, Q12_SHIFT);
    sharedData_800DE200_0_s01.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, var_s4, Q12_SHIFT);

    temp = sharedFunc_800D7440_0_s01(&sharedData_800E2350_0_s01, &sharedData_800DE200_0_s01, arg0);
    temp = sharedFunc_800D6A60_0_s01(&sharedData_800E2350_0_s01.offset_0, &sharedData_800DE210_0_s01, arg0, temp, &sharedData_800E21D0_0_s01.field_128);

    sharedFunc_800D6C7C_0_s01(&sharedData_800DE200_0_s01, arg0, temp, &sharedData_800E21D0_0_s01.unk_140);

    temp_s2   = ratan2(var_s5, var_s4);
    temp_s0   = FP_SQUARE_PRECISE(var_s5, Q12_SHIFT) + FP_SQUARE_PRECISE(var_s4, Q12_SHIFT);
    temp_s1   = temp_s0 + FP_SQUARE_PRECISE(var_s6, Q12_SHIFT);
    temp_s0   = SquareRoot12(temp_s0);
    temp_s1   = SquareRoot12(temp_s1);
    temp_s0   = ratan2(var_s6, temp_s0);
    temp_v0_9 = FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x6000, Q12_SHIFT);

    if (temp_s1 < temp_v0_9)
    {
        temp_s1 = 0;
    }
    else
    {
        temp_s1 = temp_s1 - temp_v0_9;
    }

    arg0->properties_E4.dummy.properties_E8[1].val32    = temp_s1;
    arg0->properties_E4.dummy.properties_E8[2].val16[0] = temp_s0;
    arg0->properties_E4.dummy.properties_E8[2].val16[1] = temp_s2;
}