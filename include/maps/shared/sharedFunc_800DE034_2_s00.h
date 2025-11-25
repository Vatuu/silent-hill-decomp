void sharedFunc_800DE034_2_s00(s_SubCharacter* chara, VECTOR3* vec, q19_12 dist)
{
    q19_12 scaledRadius;
    q19_12 angle;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;

    scaledRadius = FP_MULTIPLY_PRECISE(dist, func_80080514(), Q12_SHIFT);
    angle        = func_80080514();
    posX         = vec->vx + FP_MULTIPLY_PRECISE(scaledRadius, Math_Sin(angle), Q12_SHIFT);
    posZ         = vec->vz + FP_MULTIPLY_PRECISE(scaledRadius, Math_Cos(angle), Q12_SHIFT);

    posY                                  = func_80080884(posX, posZ);
    chara->properties_E4.unk0.field_F8.vx = posX;
    chara->properties_E4.unk0.field_F8.vy = posY;
    chara->properties_E4.unk0.field_F8.vz = posZ;

    sharedFunc_800D4E84_0_s01(chara);
}
