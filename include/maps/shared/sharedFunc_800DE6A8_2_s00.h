void sharedFunc_800DE6A8_2_s00(s_SubCharacter* chara, VECTOR3* vec, s32 distance)
{
    s32 scaledRadius;
    s32 angle;
    s32 posX;
    s32 posY;
    s32 posZ;

    scaledRadius = FP_MULTIPLY_PRECISE(distance, func_80080514(), Q12_SHIFT);
    angle        = func_80080514();
    posX         = vec->vx + FP_MULTIPLY_PRECISE(scaledRadius, Math_Sin(angle), Q12_SHIFT);
    posZ         = vec->vz + FP_MULTIPLY_PRECISE(scaledRadius, Math_Cos(angle), Q12_SHIFT);

    posY  = func_80080884(posX, posZ);
    posY  = MIN(chara->properties_E4.unk0.properties_124.val32, posY);
    posY -= Q12(1.5f) + (func_80080514() / 2);

    // `posY = MAX(posY, sharedFunc_800D5274_0_s01())`? Doesn't currently match.
    if (posY < sharedFunc_800D5274_0_s01())
    {
        posY = sharedFunc_800D5274_0_s01();
    }

    chara->properties_E4.unk0.field_F8.vx = posX;
    chara->properties_E4.unk0.field_F8.vy = posY;
    chara->properties_E4.unk0.field_F8.vz = posZ;

    sharedFunc_800D4E84_0_s01(chara);
}
