void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer)
{
    s32 tmp0;
    s32 tmp1;
    s32 element1;
    s32 element2;
    s32 moveSpeed;

    sharedData_800E21D0_0_s01.flags_0 &= ~0x2B;

    element1 = sharedData_800E21D0_0_s01.field_B4[0][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[0][2];
    moveSpeed = airScreamer->moveSpeed_38;
    if (sharedData_800E21D0_0_s01.field_B4[0][0])
    {
        sharedData_800E21D0_0_s01.field_B4[0][0] = 0;
        moveSpeed = sharedFunc_800D71F0_0_s01(moveSpeed, element1, element2, sharedData_800E21D0_0_s01.field_B4[0][3]);
    }
    else
    {
        moveSpeed = sharedFunc_800D7120_0_s01(moveSpeed, element1, element2);
    }
    airScreamer->moveSpeed_38 = moveSpeed;

    moveSpeed = airScreamer->field_34;
    element1 = sharedData_800E21D0_0_s01.field_B4[1][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[1][2];
    if (sharedData_800E21D0_0_s01.field_B4[1][0])
    {
        sharedData_800E21D0_0_s01.field_B4[1][0] = 0;
        moveSpeed = sharedFunc_800D71F0_0_s01(moveSpeed, element1, element2, sharedData_800E21D0_0_s01.field_B4[1][3]);
    }
    else
    {
        moveSpeed = sharedFunc_800D7120_0_s01(moveSpeed, element1, element2);
    }
    airScreamer->field_34 = moveSpeed;

    moveSpeed = airScreamer->rotationSpeed_2C.vy;
    element1 = sharedData_800E21D0_0_s01.field_B4[3][1];
    element2 = sharedData_800E21D0_0_s01.field_B4[3][2];
    if (sharedData_800E21D0_0_s01.field_B4[3][0])
    {

        moveSpeed = sharedFunc_800D71F0_0_s01(moveSpeed, element1, element2, sharedData_800E21D0_0_s01.field_B4[3][3]);
    }
    else
    {
        moveSpeed = sharedFunc_800D7120_0_s01(moveSpeed, element1, element2);
    }
    airScreamer->rotationSpeed_2C.vy = moveSpeed;

    airScreamer->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, moveSpeed); 
    if (sharedFunc_800D4A80_0_s01(airScreamer) == 3) 
    {
        sharedFunc_800D72E8_0_s01(airScreamer, airScreamer->field_34, airScreamer->rotationSpeed_2C.vy);
    }
    else
    {
        sharedFunc_800D72E8_0_s01(airScreamer, 0, FP_ANGLE(0.0f));
    }

    tmp0 = sharedFunc_800D71F0_0_s01(airScreamer->rotationSpeed_2C.vx, sharedData_800E21D0_0_s01.field_B4[2][1], sharedData_800E21D0_0_s01.field_B4[2][2], sharedData_800E21D0_0_s01.field_B4[2][3]);
    moveSpeed = tmp0;
    airScreamer->rotationSpeed_2C.vx = tmp0;
    airScreamer->rotation_24.vx += Q12_MULT_PRECISE(g_DeltaTime0, moveSpeed);
    element1 = sharedFunc_800D71F0_0_s01(airScreamer->rotationSpeed_2C.vz, sharedData_800E21D0_0_s01.field_B4[4][1], sharedData_800E21D0_0_s01.field_B4[4][2], sharedData_800E21D0_0_s01.field_B4[4][3]);
    moveSpeed = element1;
    airScreamer->rotationSpeed_2C.vz = moveSpeed;

    airScreamer->rotation_24.vz += Q12_MULT_PRECISE(g_DeltaTime0, moveSpeed);
    moveSpeed                  = sharedFunc_800D71F0_0_s01(airScreamer->field_32, sharedData_800E21D0_0_s01.field_B4[5][1], sharedData_800E21D0_0_s01.field_B4[5][2], sharedData_800E21D0_0_s01.field_B4[5][3]);
    tmp1 = moveSpeed;
    airScreamer->field_32        = tmp1;
    airScreamer->field_2A       += Q12_MULT_PRECISE(g_DeltaTime0, tmp1);
}
