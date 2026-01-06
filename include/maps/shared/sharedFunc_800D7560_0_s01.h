void sharedFunc_800D7560_0_s01(s_SubCharacter* airScreamer)
{
    q19_12   headingAngle;
    q19_12   sinHeadingAngle;
    q19_12   cosHeadingAngle;
    q19_12   offsetX;
    q19_12   offsetZ;
    MATRIX*  mat;
    SVECTOR* rot;
    VECTOR*  scale;

    mat                                       = (s32*)(sharedData_800E21D0_0_s01.coords_8) + 1;
    *(s32*)sharedData_800E21D0_0_s01.coords_8 = 0;
    rot                                       = &airScreamer->rotation_24;
    Math_RotMatrixZxyNegGte(rot, mat);

    if ((airScreamer->properties_E4.player.afkTimer_E8 & 0xF) == 3)
    {
        scale = &sharedData_800DD870_0_s01;
        ScaleMatrix(mat, scale);
    }
    else if (airScreamer->properties_E4.player.flags_11C & PlayerFlag_Unk12)
    {
        scale = &sharedData_800DD880_0_s01;
        ScaleMatrix(mat, scale);
    }

    headingAngle = rot->vy;
    offsetZ      = Q12(0.0f);
    if (sharedData_800E21D0_0_s01.flags_0 < 0)
    {
        offsetX = Q12(0.0f);
    }
    else
    {
        sinHeadingAngle = Math_Sin(headingAngle);
        offsetX         = Q12_MULT_PRECISE(sinHeadingAngle, Q12(-0.17f));

        cosHeadingAngle = Math_Cos(headingAngle);
        offsetZ         = Q12_MULT_PRECISE(cosHeadingAngle, Q12(-0.17f));
    }

    mat->t[0] = Q12_TO_Q8(airScreamer->position_18.vx + offsetX);
    mat->t[1] = Q12_TO_Q8(airScreamer->position_18.vy);
    mat->t[2] = Q12_TO_Q8(airScreamer->position_18.vz + offsetZ);
}
