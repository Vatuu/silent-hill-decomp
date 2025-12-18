void sharedFunc_800D4E84_0_s01(s_SubCharacter* chara)
{
    s32      dist0;
    s32      posX;
    s32      posY;
    s32      posZ;
    s32      vecF8Y;
    s32      dist2;
    s32      new_var;
    VECTOR3* pos;
    s32      rotY;
    s32      temp_a0;
    s32      temp_a3;
    s32      temp_hi;
    s32      temp_s1;
    s32      temp_s6;
    s32      temp_v0;
    s32      dist3;
    s32      temp_v0_3;
    s32      temp_v0_4;
    s32      temp_v0_5;
    s32      dist2_1_2;
    s32      var_s2;
    s32      var_s4;
    s32      var_s5;
    s32      var_s7;

    dist3 = 0x8000;

    pos = &chara->position_18;

    dist0   = Math_Distance2dGet(pos, &chara->properties_E4.unk0.field_F8);
    temp_v0 = func_80080478(pos, &chara->properties_E4.unk0.field_F8);

    rotY = chara->rotation_24.vy;

    posX = chara->position_18.vx;
    posY = chara->position_18.vy;
    posZ = chara->position_18.vz;

    temp_s6 = FP_ANGLE_NORM_S(temp_v0 - rotY);
    vecF8Y  = chara->properties_E4.unk0.field_F8.vy;

    if (sharedFunc_800D4AEC_0_s01(chara, NULL, &chara->properties_E4.unk0.field_F8, &sharedData_800DE1B0_0_s01))
    {
        chara->properties_E4.unk0.pos_110 = sharedData_800DE1B0_0_s01;
        return;
    }

    sharedData_800E21D0_0_s01.flags_0 |= 0x08000000;

    if (temp_s6 > -0x81 && temp_s6 < 0x81)
    {
        sharedData_800DE1C0_0_s01.vx = Math_Sin(rotY) * 2;
        sharedData_800DE1C0_0_s01.vy = 0;
        sharedData_800DE1C0_0_s01.vz = Math_Cos(rotY) * 2;

        if (func_8006DB3C(&sharedData_800E2330_0_s01, pos, &sharedData_800DE1C0_0_s01, chara) && sharedFunc_800D5274_0_s01() < sharedData_800E2330_0_s01.field_18)
        {
            chara->properties_E4.unk0.pos_110.vx = sharedData_800E2330_0_s01.field_4.vx;
            chara->properties_E4.unk0.pos_110.vy = sharedData_800E2330_0_s01.field_18 - Q12(1.5f);
            chara->properties_E4.unk0.pos_110.vz = sharedData_800E2330_0_s01.field_4.vz;
            return;
        }
    }

    dist2 = dist0 - Math_Distance2dGet(&chara->position_18, &sharedData_800DE1B0_0_s01) + dist3;

    var_s5 = INT_MAX;
    var_s7 = 0x1000;

    for (var_s4 = 0, var_s2 = (rotY + temp_s6 / 2) - 0x400; var_s4 < 9; var_s4++, var_s2 += 0x100)
    {
        sharedData_800DE1B0_0_s01.vx = posX + FP_MULTIPLY_PRECISE(Math_Sin(var_s2), 0x8000, Q12_SHIFT);
        sharedData_800DE1B0_0_s01.vy = vecF8Y;
        sharedData_800DE1B0_0_s01.vz = posZ + FP_MULTIPLY_PRECISE(Math_Cos(var_s2), 0x8000, Q12_SHIFT);

        new_var = dist2;
        if (!sharedFunc_800D4AEC_0_s01(chara, NULL, &sharedData_800DE1B0_0_s01, &sharedData_800DE1B0_0_s01))
        {
            temp_s1 = Math_Distance2dGet(&chara->position_18, &sharedData_800DE1B0_0_s01);
        }
        else
        {
            temp_s1 = 0x8000;
        }

        dist3   = Math_Distance2dGet(&sharedData_800DE1B0_0_s01, &chara->properties_E4.unk0.field_F8);
        temp_a0 = FP_MULTIPLY_PRECISE(new_var - temp_s1, dist3, Q12_SHIFT);

        temp_v0_3 = FP_ANGLE_NORM_S(var_s2 - rotY);

        temp_v0_4 = temp_v0_3 >> 0x1F;
        temp_hi   = (temp_v0_3 ^ temp_v0_4) - temp_v0_4;
        dist2_1_2 = temp_hi;

        if (temp_a0 < var_s5 || (temp_a0 == var_s5 && dist2_1_2 < var_s7))
        {
            var_s5                            = temp_a0;
            var_s7                            = dist2_1_2;
            chara->properties_E4.unk0.pos_110 = sharedData_800DE1B0_0_s01;
        }
    }

    temp_s1   = Math_Distance2dGet(&chara->properties_E4.unk0.pos_110, &chara->position_18);
    temp_v0_5 = Math_Distance2dGet(&chara->properties_E4.unk0.pos_110, &chara->properties_E4.unk0.field_F8);

    temp_a3 = temp_s1 + temp_v0_5;

    if (temp_a3 == 0)
    {
        chara->properties_E4.unk0.pos_110.vy = vecF8Y;
        return;
    }

    chara->properties_E4.unk0.pos_110.vy = FP_TO(FP_MULTIPLY_PRECISE(vecF8Y, temp_s1, Q12_SHIFT) +
                                                     FP_MULTIPLY_PRECISE(posY, temp_v0_5, Q12_SHIFT),
                                                 Q12_SHIFT) /
                                           temp_a3;

    sharedFunc_800D4AEC_0_s01(chara, NULL, &sharedData_800DE1B0_0_s01, &sharedData_800DE1B0_0_s01);
}