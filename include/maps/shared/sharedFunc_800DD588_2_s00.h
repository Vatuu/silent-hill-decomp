void sharedFunc_800DD588_2_s00(s_SubCharacter* chara)
{
    #define ANGLE_STEP_COUNT 16

    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;
    q19_12 rotY;
    q19_12 curPosX;
    q19_12 curPosY;
    q19_12 curPosZ;
    q19_12 curAngle;
    q19_12 newAngle;
    q19_12 angleStep;
    q19_12 sinRotY;
    s32    i;

    posX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    posY = g_SysWork.playerWork_4C.player_0.position_18.vy;
    posZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    rotY = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    
    if (Rng_RandQ12() < FP_ANGLE(180.0f))
    {
        angleStep = FP_ANGLE(360.0f / ANGLE_STEP_COUNT);
    }
    else
    {
        angleStep = FP_ANGLE(-(360.0f / ANGLE_STEP_COUNT));
    }

    newAngle = Rng_RandQ12() - FP_ANGLE(180.0f);
    newAngle >>= 5;
    newAngle += FP_ANGLE(180.0f);

    // Probe points around position.
    curAngle = rotY + newAngle;
    for (i = 0; i < ANGLE_STEP_COUNT; i++, curAngle += angleStep)
    {
        if (FP_ANGLE_NORM_S(rotY - curAngle) >= FP_ANGLE(-90.0f) &&
            FP_ANGLE_NORM_S(rotY - curAngle) <  FP_ANGLE(90.0f))
        {
            continue;
        }

        curPosX = posX + FP_MULTIPLY_PRECISE(Math_Sin(curAngle), Q12(20.0f), Q12_SHIFT);
        curPosZ = posZ + FP_MULTIPLY_PRECISE(Math_Cos(curAngle), Q12(20.0f), Q12_SHIFT);
        curPosY = func_80080884(curPosX, curPosZ) - Q12(2.0f);

        if (curPosY < (posY - Q12(2.0f)) || posY < curPosY || curPosY < sharedFunc_800D5274_0_s01() ||
            !func_8008F914(curPosX, curPosZ) || !func_800808AC(curPosX, curPosZ))
        {
            continue;
        }

        chara->position_18.vx = curPosX;
        chara->position_18.vy = curPosY;
        chara->position_18.vz = curPosZ;

        newAngle = ((Rng_RandQ12() - FP_ANGLE(180.0f)) >> 4) + FP_ANGLE(180.0f);
        chara->rotation_24.vy = curAngle + newAngle;
        sinRotY = Math_Sin(chara->rotation_24.vy);

        chara->properties_E4.unk0.field_F8.vy = curPosY;
        chara->properties_E4.unk0.field_F8.vx = curPosX + FP_MULTIPLY_PRECISE(sinRotY, Q12(30.0f), Q12_SHIFT);
        chara->properties_E4.unk0.field_F8.vz = curPosX + FP_MULTIPLY_PRECISE(Math_Cos(chara->rotation_24.vy), Q12(30.0f), Q12_SHIFT);

        if (sharedFunc_800D4AEC_0_s01(chara, NULL, &chara->properties_E4.unk0.field_F8, NULL))
        {
            break;
        }
    }

    if (i == ANGLE_STEP_COUNT)
    {
        chara->position_18.vx = posX + Q12(50.0f);
        chara->position_18.vy = sharedFunc_800D5274_0_s01() * 2;
        chara->position_18.vz = posZ + Q12(50.0f);
        return;
    }

    chara->moveSpeed_38 = sharedData_800CAA98_0_s01.unk_380[9][0];
    chara->properties_E4.dummy.properties_E8[14].val32 = Q12(10.0f);    
}
