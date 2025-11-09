void sharedFunc_800D6EC4_0_s01(s_SubCharacter* chara)
{
    s32 tmp0;
    s32 tmp1;
    s32 element1;
    s32 element2;
    s32 speed;

    sharedData_800E21D0_0_s01.flags_0 &= ~0x2B;

    element1 = sharedData_800E21D0_0_s01.field_B4[0][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[0][2];
    speed = chara->moveSpeed_38;
    if (sharedData_800E21D0_0_s01.field_B4[0][0])
    {
        sharedData_800E21D0_0_s01.field_B4[0][0] = 0;
        speed = sharedFunc_800D71F0_0_s01(speed, element1, element2, sharedData_800E21D0_0_s01.field_B4[0][3]);
    }
    else
    {
        speed = sharedFunc_800D7120_0_s01(speed, element1, element2);
    }
    chara->moveSpeed_38 = speed;

    speed = chara->field_34;
    element1 = sharedData_800E21D0_0_s01.field_B4[1][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[1][2];
    if (sharedData_800E21D0_0_s01.field_B4[1][0])
    {
        sharedData_800E21D0_0_s01.field_B4[1][0] = 0;
        speed = sharedFunc_800D71F0_0_s01(speed, element1, element2, sharedData_800E21D0_0_s01.field_B4[1][3]);
    }
    else
    {
        speed = sharedFunc_800D7120_0_s01(speed, element1, element2);
    }
    chara->field_34 = speed;

    speed = chara->rotationSpeed_2C.vy;
    element1 = sharedData_800E21D0_0_s01.field_B4[3][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[3][2];
    if (sharedData_800E21D0_0_s01.field_B4[3][0])
    {

        speed = sharedFunc_800D71F0_0_s01(speed, element1, element2, sharedData_800E21D0_0_s01.field_B4[3][3]);
    }
    else
    {
        speed = sharedFunc_800D7120_0_s01(speed, element1, element2);
    }
    chara->rotationSpeed_2C.vy = speed;

    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT); 
    if (sharedFunc_800D4A80_0_s01(chara) == 3) 
    {
        sharedFunc_800D72E8_0_s01(chara, chara->field_34, chara->rotationSpeed_2C.vy);
    }
    else
    {
        sharedFunc_800D72E8_0_s01(chara, 0, 0);
    }

    tmp0 = sharedFunc_800D71F0_0_s01(chara->rotationSpeed_2C.vx, sharedData_800E21D0_0_s01.field_B4[2][1], sharedData_800E21D0_0_s01.field_B4[2][2], sharedData_800E21D0_0_s01.field_B4[2][3]);
    speed = tmp0;
    chara->rotationSpeed_2C.vx = tmp0;
    chara->rotation_24.vx += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);
    element1 = sharedFunc_800D71F0_0_s01(chara->rotationSpeed_2C.vz, sharedData_800E21D0_0_s01.field_B4[4][1], sharedData_800E21D0_0_s01.field_B4[4][2], sharedData_800E21D0_0_s01.field_B4[4][3]);
    speed = element1;
    chara->rotationSpeed_2C.vz = speed;

    chara->rotation_24.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);
    speed = sharedFunc_800D71F0_0_s01(chara->rotationSpeed_2C.pad, sharedData_800E21D0_0_s01.field_B4[5][1], sharedData_800E21D0_0_s01.field_B4[5][2], sharedData_800E21D0_0_s01.field_B4[5][3]);
    tmp1 = speed;
    chara->rotationSpeed_2C.pad = tmp1;
    chara->rotation_24.pad += FP_MULTIPLY_PRECISE(g_DeltaTime0, tmp1, Q12_SHIFT);
}
