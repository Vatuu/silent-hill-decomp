void sharedFunc_800D03E4_3_s03(s_SubCharacter* nurse)
{
    s_800C4590 sp10;
    VECTOR     sp30;
    VECTOR     sp40;
    VECTOR     sp50;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s0_3;
    s32        temp_s1;
    s32        temp_s2;
    s32        temp5;

    temp_s1 = nurse->properties_E4.puppetNurse.field_124->field_2C;

    sp30.vx = nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    sp30.vz = nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;
    sp30.vy = nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;

    temp_s0                                    = nurse->moveSpeed_38;
    nurse->properties_E4.puppetNurse.field_110 = temp_s0;

    sp40.vx = Math_Sin(nurse->rotation_24.vy);
    sp40.vz = Math_Cos(nurse->rotation_24.vy);
    sp40.vy = 0;

    temp_s2   = Q12_MULT_PRECISE(temp_s1, sp30.vx) + Q12_MULT_PRECISE(temp_s0, sp40.vx);
    temp5     = Q12_MULT_PRECISE(temp_s1, sp30.vy);
    temp_s0_2 = Q12_MULT_PRECISE(temp_s1, sp30.vz) + Q12_MULT_PRECISE(temp_s0, sp40.vz);

    sp50.vx = temp_s2;
    sp50.vy = temp5;
    sp50.vz = temp_s0_2;

    nurse->moveSpeed_38    = SquareRoot12(Q12_MULT_PRECISE(temp_s2, temp_s2) + Q12_MULT_PRECISE(temp_s0_2, temp_s0_2));
    nurse->headingAngle_3C = ratan2(temp_s2, temp_s0_2);
    nurse->field_34       += g_DeltaTime2;

    func_8005C944(nurse, &sp10);

    temp_s0_3                                                = nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    nurse->moveSpeed_38                                      = nurse->properties_E4.puppetNurse.field_110;
    nurse->properties_E4.puppetNurse.damage_F4.position_0.vx = SquareRoot12(Q12_MULT_PRECISE(temp_s0_3, temp_s0_3) >> g_VBlanks);

    if (temp_s0_3 <= 0)
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vx = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vx;
    }

    temp_s0_3                                                = nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;
    nurse->properties_E4.puppetNurse.damage_F4.position_0.vy = SquareRoot12(Q12_MULT_PRECISE(temp_s0_3, temp_s0_3) >> g_VBlanks);

    if (temp_s0_3 <= 0)
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vy = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vy;
    }

    temp_s0_3 = nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;

    nurse->properties_E4.puppetNurse.damage_F4.position_0.vz = SquareRoot12(Q12_MULT_PRECISE(temp_s0_3, temp_s0_3) >> g_VBlanks);
    if (temp_s0_3 <= 0)
    {
        nurse->properties_E4.puppetNurse.damage_F4.position_0.vz = -nurse->properties_E4.puppetNurse.damage_F4.position_0.vz;
    }

    nurse->rotation_24.vy = func_8005BF38(nurse->rotation_24.vy);
}