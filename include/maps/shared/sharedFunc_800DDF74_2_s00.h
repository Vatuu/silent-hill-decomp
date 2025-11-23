void sharedFunc_800DDF74_2_s00(s_SubCharacter* chara, s32 mulX, q19_12 angle0)
{
    q19_12 posX;
    q19_12 posZ;
    q19_12 groundHeight;

    posX = chara->position_18.vx;
    posZ = chara->position_18.vz;

    posX        += FP_MULTIPLY_PRECISE(mulX, Math_Sin(angle0), Q12_SHIFT);
    posZ        += FP_MULTIPLY_PRECISE(mulX, Math_Cos(angle0), Q12_SHIFT);
    groundHeight = func_80080884(posX, posZ);

    chara->properties_E4.unk0.field_F8.vx = posX;
    chara->properties_E4.unk0.field_F8.vy = groundHeight;
    chara->properties_E4.unk0.field_F8.vz = posZ;
    sharedFunc_800D4E84_0_s01(chara);
}
