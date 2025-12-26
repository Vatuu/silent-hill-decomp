void sharedFunc_800DDF74_2_s00(s_SubCharacter* chara, s32 mulX, q19_12 headingAngle)
{
    q19_12 newPosX;
    q19_12 newPosZ;
    q19_12 newPosY;

    newPosX = chara->position_18.vx;
    newPosZ = chara->position_18.vz;

    newPosX += FP_MULTIPLY_PRECISE(mulX, Math_Sin(headingAngle), Q12_SHIFT);
    newPosZ += FP_MULTIPLY_PRECISE(mulX, Math_Cos(headingAngle), Q12_SHIFT);
    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);

    chara->properties_E4.unk0.field_F8.vx = newPosX;
    chara->properties_E4.unk0.field_F8.vy = newPosY;
    chara->properties_E4.unk0.field_F8.vz = newPosZ;
    sharedFunc_800D4E84_0_s01(chara);
}
