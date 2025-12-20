void sharedFunc_800D6600_0_s01(s_SubCharacter* chara)
{
    q19_12 newPosX;
    q19_12 sp1C;
    q19_12 newPosY;
    q19_12 angle0;
    q19_12 angle2;
    q19_12 angle1;
    q19_12 newPosZ;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;
    q20_12 angle3;
    s32    temp;

    newPosX = FP_MULTIPLY_PRECISE(chara->damage_B4.position_0.vx, Q12(3.0f), Q12_SHIFT);
    newPosY = FP_MULTIPLY_PRECISE(chara->damage_B4.position_0.vy, Q12(3.0f), Q12_SHIFT);
    newPosZ = FP_MULTIPLY_PRECISE(chara->damage_B4.position_0.vz, Q12(3.0f), Q12_SHIFT);

    chara->damage_B4.position_0.vx = Q12(0.0f);
    chara->damage_B4.position_0.vy = Q12(0.0f);
    chara->damage_B4.position_0.vz = Q12(0.0f);

    sp1C = SquareRoot12(FP_SQUARE_PRECISE(newPosX, Q12_SHIFT) +
                        FP_SQUARE_PRECISE(newPosY, Q12_SHIFT) +
                        FP_SQUARE_PRECISE(newPosZ, Q12_SHIFT));

    angle2 = chara->properties_E4.dummy.properties_E8[1].val32;
    angle0 = chara->properties_E4.dummy.properties_E8[2].val16[0];
    angle1 = chara->properties_E4.dummy.properties_E8[2].val16[1];

    if (angle2 == FP_ANGLE(0.0f))
    {
        posZ = Q12(0.0f);
        posY = Q12(0.0f);
        posX = Q12(0.0f);
    }
    else
    {
        posY   = FP_MULTIPLY_PRECISE(angle2, Math_Sin(angle0), Q12_SHIFT);
        angle0 = FP_MULTIPLY_PRECISE(angle2, Math_Cos(angle0), Q12_SHIFT);

        if (angle0 < FP_ANGLE(0.0f))
        {
            angle0  = -angle0;
            angle1 ^= 0x800;
        }

        posX = FP_MULTIPLY_PRECISE(angle0, Math_Sin(angle1), Q12_SHIFT);
        posZ = FP_MULTIPLY_PRECISE(angle0, Math_Cos(angle1), Q12_SHIFT);
    }

    if (sp1C > 0)
    {
        posX += newPosX;
        posY += newPosY;
        posZ += newPosZ;
    }

    if (!(posX | posY | posZ))
    {
        chara->properties_E4.dummy.properties_E8[1].val32    = FP_ANGLE(0.0f); // } Presumably angles.
        chara->properties_E4.dummy.properties_E8[2].val16[0] = FP_ANGLE(0.0f); // }
        chara->properties_E4.dummy.properties_E8[2].val16[1] = chara->rotation_24.vy;
        return;
    }

    sharedData_800DE210_0_s01.vx = posX;
    sharedData_800DE210_0_s01.vy = posY;
    sharedData_800DE210_0_s01.vz = posZ;

    sharedData_800DE200_0_s01.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, posX, Q12_SHIFT);
    sharedData_800DE200_0_s01.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, posY, Q12_SHIFT);
    sharedData_800DE200_0_s01.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, posZ, Q12_SHIFT);

    temp = sharedFunc_800D7440_0_s01(&sharedData_800E2350_0_s01, &sharedData_800DE200_0_s01, chara);
    temp = sharedFunc_800D6A60_0_s01(&sharedData_800E2350_0_s01.offset_0, &sharedData_800DE210_0_s01, chara, temp, &sharedData_800E21D0_0_s01.field_128);

    sharedFunc_800D6C7C_0_s01(&sharedData_800DE200_0_s01, chara, temp, &sharedData_800E21D0_0_s01.unk_140);

    angle1 = ratan2(posX, posZ);
    angle0 = FP_SQUARE_PRECISE(posX, Q12_SHIFT) + FP_SQUARE_PRECISE(posZ, Q12_SHIFT);
    angle2 = angle0 + FP_SQUARE_PRECISE(posY, Q12_SHIFT);
    angle0 = SquareRoot12(angle0);
    angle2 = SquareRoot12(angle2);
    angle0 = ratan2(posY, angle0);
    angle3 = FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT);

    if (angle2 < angle3)
    {
        angle2 = FP_ANGLE(0.0f);
    }
    else
    {
        angle2 = angle2 - angle3;
    }

    chara->properties_E4.dummy.properties_E8[1].val32    = angle2;
    chara->properties_E4.dummy.properties_E8[2].val16[0] = angle0;
    chara->properties_E4.dummy.properties_E8[2].val16[1] = angle1;
}
