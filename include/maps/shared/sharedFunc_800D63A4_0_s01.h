void sharedFunc_800D63A4_0_s01(s_SubCharacter* airScreamer)
{
    q3_12  headingAngle;
    q19_12 moveSpeed;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;
    s32    temp_s0;
    s32    magSqr;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800D6EC4_0_s01(airScreamer);

    headingAngle                 = airScreamer->rotation_24.vy;
    moveSpeed                    = airScreamer->moveSpeed_38;
    posY                         = airScreamer->field_34;
    airScreamer->headingAngle_3C = headingAngle;

    sharedData_800DE1F0_0_s01.vx = Q12_MULT_PRECISE(moveSpeed, Math_Sin(headingAngle));
    sharedData_800DE1F0_0_s01.vy = posY;
    sharedData_800DE1F0_0_s01.vz = Q12_MULT_PRECISE(moveSpeed, Math_Cos(headingAngle));

    sharedData_800DE1E0_0_s01.vx = Q12_MULT_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vx);
    sharedData_800DE1E0_0_s01.vy = Q12_MULT_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vy);
    sharedData_800DE1E0_0_s01.vz = Q12_MULT_PRECISE(g_DeltaTime0, sharedData_800DE1F0_0_s01.vz);

    temp_s0 = sharedFunc_800D6A60_0_s01(&sharedData_800E2350_0_s01.offset_0,
                                        &sharedData_800DE1F0_0_s01,
                                        airScreamer,
                                        sharedFunc_800D7440_0_s01(&sharedData_800E2350_0_s01, &sharedData_800DE1E0_0_s01, airScreamer),
                                        &sharedData_800E21D0_0_s01.field_11C);

    airScreamerProps.flags_11C &= ~PlayerFlag_Unk29;

    // @hack Permuter find.
    temp_s0++;
    temp_s0--;

    if (sharedFunc_800D4A80_0_s01(airScreamer) == 3)
    {
        posX = sharedData_800E21D0_0_s01.field_11C.vx;
        posZ = sharedData_800E21D0_0_s01.field_11C.vz;

        magSqr = Q12_MULT_PRECISE(posX, posX) + Q12_MULT_PRECISE(posZ, posZ);
        if (magSqr < Q12(0.49f))
        {
            airScreamerProps.flags_11C |= PlayerFlag_Unk29;
        }
    }

    airScreamer->field_34 = sharedData_800E21D0_0_s01.field_B4[6][3];
    sharedFunc_800D6C7C_0_s01(&sharedData_800DE1E0_0_s01, airScreamer, temp_s0, &sharedData_800E21D0_0_s01.field_134);

    #undef airScreamerProps
}
