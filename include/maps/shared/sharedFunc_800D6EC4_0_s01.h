void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer)
{
    s32 tmp0;
    s32 tmp1;
    s32 element1;
    s32 element2;
    s32 speed;

    sharedData_800E21D0_0_s01.flags_0 &= ~0x2B;

    element1 = sharedData_800E21D0_0_s01.field_B4[0][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[0][2];
    speed = airScreamer->moveSpeed_38;
    if (sharedData_800E21D0_0_s01.field_B4[0][0])
    {
        sharedData_800E21D0_0_s01.field_B4[0][0] = 0;
        speed = sharedFunc_800D71F0_0_s01(speed, element1, element2, sharedData_800E21D0_0_s01.field_B4[0][3]);
    }
    else
    {
        speed = sharedFunc_800D7120_0_s01(speed, element1, element2);
    }
    airScreamer->moveSpeed_38 = speed;

    speed = airScreamer->field_34;
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
    airScreamer->field_34 = speed;

    speed = airScreamer->rotationSpeed_2C.vy;
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
    airScreamer->rotationSpeed_2C.vy = speed;

    airScreamer->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT); 
    if (sharedFunc_800D4A80_0_s01(airScreamer) == 3) 
    {
        sharedFunc_800D72E8_0_s01(airScreamer, airScreamer->field_34, airScreamer->rotationSpeed_2C.vy);
    }
    else
    {
        sharedFunc_800D72E8_0_s01(airScreamer, 0, FP_ANGLE(0.0f));
    }

    tmp0 = sharedFunc_800D71F0_0_s01(airScreamer->rotationSpeed_2C.vx, sharedData_800E21D0_0_s01.field_B4[2][1], sharedData_800E21D0_0_s01.field_B4[2][2], sharedData_800E21D0_0_s01.field_B4[2][3]);
    speed = tmp0;
    airScreamer->rotationSpeed_2C.vx = tmp0;
    airScreamer->rotation_24.vx += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);
    element1 = sharedFunc_800D71F0_0_s01(airScreamer->rotationSpeed_2C.vz, sharedData_800E21D0_0_s01.field_B4[4][1], sharedData_800E21D0_0_s01.field_B4[4][2], sharedData_800E21D0_0_s01.field_B4[4][3]);
    speed = element1;
    airScreamer->rotationSpeed_2C.vz = speed;

    airScreamer->rotation_24.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);
    speed                  = sharedFunc_800D71F0_0_s01(airScreamer->field_32, sharedData_800E21D0_0_s01.field_B4[5][1], sharedData_800E21D0_0_s01.field_B4[5][2], sharedData_800E21D0_0_s01.field_B4[5][3]);
    tmp1 = speed;
    airScreamer->field_32        = tmp1;
    airScreamer->field_2A       += FP_MULTIPLY_PRECISE(g_DeltaTime0, tmp1, Q12_SHIFT);
}
