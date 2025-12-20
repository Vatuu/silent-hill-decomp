void sharedFunc_800D63A4_0_s01(s_SubCharacter* chara)
{
    q3_12  rot;
    q19_12 speed;
    s32    field34;
    s32    temp_s0;
    s32    x;
    s32    z;
    s32    magSqr;

    sharedFunc_800D6EC4_0_s01(chara);

    rot     = chara->rotation_24.vy;
    speed   = chara->moveSpeed_38;
    field34 = chara->field_34;

    chara->headingAngle_3C = rot;

    sharedData_800DE1F0_0_s01.vx = FP_MULTIPLY_PRECISE(speed, Math_Sin(rot), Q12_SHIFT);
    sharedData_800DE1F0_0_s01.vy = field34;
    sharedData_800DE1F0_0_s01.vz = FP_MULTIPLY_PRECISE(speed, Math_Cos(rot), Q12_SHIFT);

    sharedData_800DE1E0_0_s01.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vx, Q12_SHIFT);
    sharedData_800DE1E0_0_s01.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vy, Q12_SHIFT);
    sharedData_800DE1E0_0_s01.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vz, Q12_SHIFT);

    temp_s0 = sharedFunc_800D6A60_0_s01(&sharedData_800E2350_0_s01.offset_0,
                                        &sharedData_800DE1F0_0_s01,
                                        chara,
                                        sharedFunc_800D7440_0_s01(&sharedData_800E2350_0_s01, &sharedData_800DE1E0_0_s01, chara),
                                        &sharedData_800E21D0_0_s01.field_11C);

    chara->properties_E4.player.flags_11C &= ~PlayerFlag_Unk29;

    // @hack Permuter find.
    temp_s0++;
    temp_s0--;

    if (sharedFunc_800D4A80_0_s01(chara) == 3)
    {
        x = sharedData_800E21D0_0_s01.field_11C.vx;
        z = sharedData_800E21D0_0_s01.field_11C.vz;

        magSqr = FP_MULTIPLY_PRECISE(x, x, Q12_SHIFT) + FP_MULTIPLY_PRECISE(z, z, Q12_SHIFT);
        if (magSqr < Q12(0.49f))
        {
            chara->properties_E4.player.flags_11C |= PlayerFlag_Unk29;
        }
    }

    chara->field_34 = sharedData_800E21D0_0_s01.field_B4[6][3];
    sharedFunc_800D6C7C_0_s01(&sharedData_800DE1E0_0_s01, chara, temp_s0, &sharedData_800E21D0_0_s01.field_134);
}
