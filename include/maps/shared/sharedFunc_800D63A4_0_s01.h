void sharedFunc_800D63A4_0_s01(s_SubCharacter* chara)
{
    s16 rot;
    s32 speed;
    s32 field34;
    s32 sinVal;
    s32 cosVal;
    s32 temp_s0;
    s32 v0_4;
    s32 v0_5;
    s32 magSq;
    u8* base;

    sharedFunc_800D6EC4_0_s01(chara);

    rot     = chara->rotation_24.vy;
    speed   = chara->moveSpeed_38;
    field34 = chara->field_34;

    chara->headingAngle_3C = rot;

    sharedData_800DE1F0_0_s01.vx = FP_MULTIPLY_PRECISE(speed, Math_Sin(rot), 12);
    sharedData_800DE1F0_0_s01.vy = field34;
    sharedData_800DE1F0_0_s01.vz = FP_MULTIPLY_PRECISE(speed, Math_Cos(rot), 12);

    sharedData_800DE1E0_0_s01.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vx, 12);
    sharedData_800DE1E0_0_s01.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vy, 12);
    sharedData_800DE1E0_0_s01.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vz, 12);

    temp_s0 = sharedFunc_800D6A60_0_s01(
        &sharedData_800E2350_0_s01,
        &sharedData_800DE1F0_0_s01,
        chara,
        sharedFunc_800D7440_0_s01(&sharedData_800E2350_0_s01, &sharedData_800DE1E0_0_s01, chara),
        &sharedData_800E21D0_0_s01.field_11C
    );

    chara->properties_E4.player.flags_11C &= 0xDFFFFFFF;

    // @hack permuter find.
    temp_s0++;
    temp_s0--;

    if (sharedFunc_800D4A80_0_s01(chara) == 3)
    {
        //base = (u8*)&D_800E22EC - 0x11C;
        v0_4 = sharedData_800E21D0_0_s01.field_11C.vx;
        v0_5 = sharedData_800E21D0_0_s01.field_11C.vz;

        magSq = FP_MULTIPLY_PRECISE(v0_4, v0_4, 12)
              + FP_MULTIPLY_PRECISE(v0_5, v0_5, 12);

        if (magSq < 0x7D7)
        {
            chara->properties_E4.player.flags_11C |= 0x20000000;
        }
    }

    chara->field_34 = sharedData_800E21D0_0_s01.field_B4[6][3];

    sharedFunc_800D6C7C_0_s01(&sharedData_800DE1E0_0_s01, chara, temp_s0, &sharedData_800E21D0_0_s01.field_134);
}
