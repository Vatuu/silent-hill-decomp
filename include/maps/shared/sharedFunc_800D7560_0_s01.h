void sharedFunc_800D7560_0_s01(s_SubCharacter* chara)
{
    s32      headingAngle;
    s32      sinHeadingAngle;
    s32      cosHeadingAngle;
    s32      offsetX;
    s32      offsetZ;
    MATRIX*  mat;
    SVECTOR* rot;
    VECTOR*  scale;

    mat                                       = (s32*)(sharedData_800E21D0_0_s01.coords_8) + 1;
    *(s32*)sharedData_800E21D0_0_s01.coords_8 = 0;
    rot                                       = &chara->rotation_24;
    func_80096E78(rot, mat);

    if ((chara->properties_E4.player.afkTimer_E8 & 0xF) == 3)
    {
        scale = &sharedData_800DD870_0_s01;
        ScaleMatrix(mat, scale);
    }
    else if (chara->properties_E4.player.flags_11C & PlayerFlag_Unk12)
    {
        scale = &sharedData_800DD880_0_s01;
        ScaleMatrix(mat, scale);
    }

    headingAngle = rot->vy;
    offsetZ      = 0;
    if (sharedData_800E21D0_0_s01.flags_0 < 0)
    {
        offsetX = 0;
    }
    else
    {
        sinHeadingAngle = Math_Sin(headingAngle);
        offsetX         = FP_MULTIPLY_PRECISE(sinHeadingAngle, -0x2B8, Q12_SHIFT);

        cosHeadingAngle = Math_Cos(headingAngle);
        offsetZ         = FP_MULTIPLY_PRECISE(cosHeadingAngle, -0x2B8, Q12_SHIFT);
    }

    mat->t[0] = FP_FROM(chara->position_18.vx + offsetX, Q4_SHIFT);
    mat->t[1] = FP_FROM(chara->position_18.vy, Q4_SHIFT);
    mat->t[2] = FP_FROM(chara->position_18.vz + offsetZ, Q4_SHIFT);
}
