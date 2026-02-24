void sharedFunc_800D03E4_3_s03(s_SubCharacter* nurse)
{
    s_800C4590 sp10;
    VECTOR     damagePos; // Q19.12
    VECTOR     dir;       // Q19.12
    VECTOR     unkPos;
    q19_12     moveSpeed;
    q19_12     damagePosComp;
    q19_12     temp_s1;
    q19_12     unkPosX;
    q19_12     unkPosY;
    q19_12     unkPosZ;

    temp_s1 = nurse->properties_E4.puppetNurse.field_124->field_2C;

    damagePos.vx = nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    damagePos.vz = nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;
    damagePos.vy = nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;

    moveSpeed                                  = nurse->moveSpeed_38;
    nurse->properties_E4.puppetNurse.moveSpeed_110 = moveSpeed;

    dir.vx = Math_Sin(nurse->rotation_24.vy);
    dir.vz = Math_Cos(nurse->rotation_24.vy);
    dir.vy = Q12(0.0f);

    unkPosX = Q12_MULT_PRECISE(temp_s1, damagePos.vx) + Q12_MULT_PRECISE(moveSpeed, dir.vx);
    unkPosY = Q12_MULT_PRECISE(temp_s1, damagePos.vy);
    unkPosZ = Q12_MULT_PRECISE(temp_s1, damagePos.vz) + Q12_MULT_PRECISE(moveSpeed, dir.vz);

    unkPos.vx = unkPosX;
    unkPos.vy = unkPosY;
    unkPos.vz = unkPosZ;

    nurse->moveSpeed_38    = SquareRoot12(Q12_MULT_PRECISE(unkPosX, unkPosX) + Q12_MULT_PRECISE(unkPosZ, unkPosZ));
    nurse->headingAngle_3C = ratan2(unkPosX, unkPosZ);
    nurse->fallSpeed_34   += g_GravitySpeed;

    func_8005C944(nurse, &sp10);

    damagePosComp                                                = nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    nurse->moveSpeed_38                                      = nurse->properties_E4.puppetNurse.moveSpeed_110;
    nurse->properties_E4.puppetNurse.damage_F4.position_0.vx = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);

    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vx = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    }

    damagePosComp                                                = nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;
    nurse->properties_E4.puppetNurse.damage_F4.position_0.vy = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);

    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vy = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;
    }

    damagePosComp = nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;

    nurse->properties_E4.puppetNurse.damage_F4.position_0.vz = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);
    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vz = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;
    }

    nurse->rotation_24.vy = func_8005BF38(nurse->rotation_24.vy);
}
