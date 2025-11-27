void sharedFunc_800D7B14_0_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s32 bendAngle;
    s16 axisBlend;
    s32 cosVal;
    s32 sinVal;
    s32 scaledAngle;

    if (chara->model_0.anim_4.flags_2 & 1)
    {
        bendAngle = chara->field_2A;

        PushMatrix();
        sharedData_800DE220_0_s01.vx = 0;
        sharedData_800DE220_0_s01.vz = 0;
        sharedData_800DE220_0_s01.vy = FP_MULTIPLY_FLOAT_PRECISE(bendAngle, 0.3f, Q12_SHIFT);
        Math_RotMatrixXyxGte(&sharedData_800DE220_0_s01, &sharedData_800DE230_0_s01);
        MulMatrix(&coords[10].coord, &sharedData_800DE230_0_s01);

        scaledAngle = FP_MULTIPLY_FLOAT_PRECISE(bendAngle, 0.5f, Q12_SHIFT);

        cosVal                            = Math_Cos(scaledAngle);
        sinVal                            = Math_Sin(scaledAngle);
        sharedData_800DE230_0_s01.m[0][0] = cosVal;

        // axisBlend = sin(theta) * 1/sqrt(2) -> off-diagonal axis contribution
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(sinVal, 0.7071f, Q12_SHIFT); // 1/sqrt(2)
        sharedData_800DE230_0_s01.m[1][0] = axisBlend;
        sharedData_800DE230_0_s01.m[0][2] = axisBlend;
        sharedData_800DE230_0_s01.m[2][0] = -axisBlend;
        sharedData_800DE230_0_s01.m[0][1] = -axisBlend;
        // axisBlend = (cos(theta) + 1) * 0.5 -> positive diagonal blend
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(cosVal + Q12(1.0f), 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][2] = axisBlend;
        sharedData_800DE230_0_s01.m[1][1] = axisBlend;
        // axisBlend = (1 - cos(theta)) * 0.5 -> complementary diagonal blend
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(Q12(1.0f) - cosVal, 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][1] = axisBlend;
        sharedData_800DE230_0_s01.m[1][2] = axisBlend;
        MulMatrix(&coords[9].coord, &sharedData_800DE230_0_s01);

        scaledAngle = FP_MULTIPLY_FLOAT_PRECISE(bendAngle, 0.2f, Q12_SHIFT);

        cosVal                            = Math_Cos(scaledAngle);
        sinVal                            = Math_Sin(scaledAngle);
        sharedData_800DE230_0_s01.m[0][0] = cosVal;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(sinVal, 0.7071f, Q12_SHIFT); // 1 / sqrt(2)
        sharedData_800DE230_0_s01.m[1][0] = axisBlend;
        sharedData_800DE230_0_s01.m[0][2] = axisBlend;
        sharedData_800DE230_0_s01.m[2][0] = -axisBlend;
        sharedData_800DE230_0_s01.m[0][1] = -axisBlend;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(cosVal + Q12(1.0f), 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][2] = axisBlend;
        sharedData_800DE230_0_s01.m[1][1] = axisBlend;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(Q12(1.0f) - cosVal, 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][1] = axisBlend;
        sharedData_800DE230_0_s01.m[1][2] = axisBlend;
        MulMatrix(&coords[1].coord, &sharedData_800DE230_0_s01);

        scaledAngle = FP_MULTIPLY_FLOAT_PRECISE(bendAngle, 0.2f, Q12_SHIFT);

        cosVal                            = Math_Cos(scaledAngle);
        sinVal                            = Math_Sin(scaledAngle);
        sharedData_800DE230_0_s01.m[0][0] = cosVal;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(sinVal, 0.7071f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][0] = axisBlend;
        sharedData_800DE230_0_s01.m[0][1] = axisBlend;
        sharedData_800DE230_0_s01.m[1][0] = -axisBlend;
        sharedData_800DE230_0_s01.m[0][2] = -axisBlend;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(cosVal + Q12(1.0f), 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][2] = axisBlend;
        sharedData_800DE230_0_s01.m[1][1] = axisBlend;
        axisBlend                         = FP_MULTIPLY_FLOAT_PRECISE(Q12(1.0f) - cosVal, 0.5f, Q12_SHIFT);
        sharedData_800DE230_0_s01.m[2][1] = axisBlend;
        sharedData_800DE230_0_s01.m[1][2] = axisBlend;
        MulMatrix(&coords[2].coord, &sharedData_800DE230_0_s01);
        PopMatrix();
    }
}
