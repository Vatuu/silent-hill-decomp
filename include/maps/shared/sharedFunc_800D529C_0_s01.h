void sharedFunc_800D529C_0_s01(s_SubCharacter* chara, s32 thousand, s32 angles)
{
    s32 posX;
    s32 posZ;
    s32 posY;
    s32 posYMinus1_5;

    posX = chara->position_18.vx;
    posZ = chara->position_18.vz;

    posX = posX + FP_MULTIPLY_PRECISE(thousand, Math_Sin(angles), Q12_SHIFT);
    posZ = posZ + FP_MULTIPLY_PRECISE(thousand, Math_Cos(angles), Q12_SHIFT);

    posY = func_80080884(posX, posZ);

    if (posY > chara->properties_E4.unk0.properties_124.val32)
    {
        posY = chara->properties_E4.unk0.properties_124.val32;
    }

    posYMinus1_5 = posY - Q12(1.5f);

    posY = posYMinus1_5 - func_80080514() / 2;

    if (posY < sharedFunc_800D5274_0_s01())
    {
        posY = sharedFunc_800D5274_0_s01();
    }

    chara->properties_E4.unk0.field_F8.vx = posX;
    chara->properties_E4.unk0.field_F8.vy = posY;
    chara->properties_E4.unk0.field_F8.vz = posZ;

    sharedFunc_800D4E84_0_s01(chara);
}
