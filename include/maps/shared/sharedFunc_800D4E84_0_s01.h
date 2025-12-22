void sharedFunc_800D4E84_0_s01(s_SubCharacter* chara)
{
    q19_12   dist0;
    q19_12   posX;
    q19_12   posY;
    q19_12   posZ;
    s32      vecF8Y;
    q19_12   dist2;
    s32      new_var;
    VECTOR3* pos;
    s32      rotY;
    q19_12   temp_a0;
    q19_12   dist5;
    s32      temp_hi;
    q19_12   dist1;
    q19_12   angle;
    q19_12   temp_v0;
    q19_12   dist3;
    s32      temp_v0_3;
    s32      temp_v0_4;
    s32      dist4;
    s32      dist2_1_2;
    q19_12   curAngle;
    s32      i;
    s32      var_s5;
    s32      var_s7;

    dist3 = Q12(8.0f);

    pos = &chara->position_18;

    dist0   = Math_Distance2dGet(pos, &chara->properties_E4.unk0.field_F8);
    temp_v0 = func_80080478(pos, &chara->properties_E4.unk0.field_F8);

    rotY = chara->rotation_24.vy;

    posX = chara->position_18.vx;
    posY = chara->position_18.vy;
    posZ = chara->position_18.vz;

    angle = FP_ANGLE_NORM_S(temp_v0 - rotY);
    vecF8Y  = chara->properties_E4.unk0.field_F8.vy;

    if (sharedFunc_800D4AEC_0_s01(chara, NULL, &chara->properties_E4.unk0.field_F8, &sharedData_800DE1B0_0_s01))
    {
        chara->properties_E4.unk0.pos_110 = sharedData_800DE1B0_0_s01;
        return;
    }

    sharedData_800E21D0_0_s01.flags_0 |= 0x08000000;

    if (angle > FP_ANGLE(-11.34f) && angle < FP_ANGLE(11.34f))
    {
        sharedData_800DE1C0_0_s01.vx = Math_Sin(rotY) * 2;
        sharedData_800DE1C0_0_s01.vy = Q12(0.0f);
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
    var_s7 = Q12(1.0f);

    for (i = 0, curAngle = (rotY + angle / 2) - FP_ANGLE(90.0f); i < 9; i++, curAngle += FP_ANGLE(22.5f))
    {
        sharedData_800DE1B0_0_s01.vx = posX + FP_MULTIPLY_PRECISE(Math_Sin(curAngle), Q12(8.0f), Q12_SHIFT);
        sharedData_800DE1B0_0_s01.vy = vecF8Y;
        sharedData_800DE1B0_0_s01.vz = posZ + FP_MULTIPLY_PRECISE(Math_Cos(curAngle), Q12(8.0f), Q12_SHIFT);

        new_var = dist2;
        if (!sharedFunc_800D4AEC_0_s01(chara, NULL, &sharedData_800DE1B0_0_s01, &sharedData_800DE1B0_0_s01))
        {
            dist1 = Math_Distance2dGet(&chara->position_18, &sharedData_800DE1B0_0_s01);
        }
        else
        {
            dist1 = Q12(8.0f);
        }

        dist3   = Math_Distance2dGet(&sharedData_800DE1B0_0_s01, &chara->properties_E4.unk0.field_F8);
        temp_a0 = FP_MULTIPLY_PRECISE(new_var - dist1, dist3, Q12_SHIFT);

        temp_v0_3 = FP_ANGLE_NORM_S(curAngle - rotY);

        temp_v0_4 = temp_v0_3 >> 31;
        temp_hi   = (temp_v0_3 ^ temp_v0_4) - temp_v0_4;
        dist2_1_2 = temp_hi;

        if (temp_a0 < var_s5 || (temp_a0 == var_s5 && dist2_1_2 < var_s7))
        {
            var_s5                            = temp_a0;
            var_s7                            = dist2_1_2;
            chara->properties_E4.unk0.pos_110 = sharedData_800DE1B0_0_s01;
        }
    }

    dist1 = Math_Distance2dGet(&chara->properties_E4.unk0.pos_110, &chara->position_18);
    dist4 = Math_Distance2dGet(&chara->properties_E4.unk0.pos_110, &chara->properties_E4.unk0.field_F8);

    dist5 = dist1 + dist4;
    if (dist5 == Q12(0.0f))
    {
        chara->properties_E4.unk0.pos_110.vy = vecF8Y;
        return;
    }

    chara->properties_E4.unk0.pos_110.vy = FP_TO(FP_MULTIPLY_PRECISE(vecF8Y, dist1, Q12_SHIFT) +
                                                 FP_MULTIPLY_PRECISE(posY, dist4, Q12_SHIFT),
                                                 Q12_SHIFT) /
                                           dist5;

    sharedFunc_800D4AEC_0_s01(chara, NULL, &sharedData_800DE1B0_0_s01, &sharedData_800DE1B0_0_s01);
}
