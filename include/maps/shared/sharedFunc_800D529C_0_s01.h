void sharedFunc_800D529C_0_s01(s_SubCharacter* chara, s32 radius, s32 angle)
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    newPosX = chara->position_18.vx;
    newPosZ = chara->position_18.vz;

    newPosX = newPosX + FP_MULTIPLY_PRECISE(radius, Math_Sin(angle), Q12_SHIFT);
    newPosZ = newPosZ + FP_MULTIPLY_PRECISE(radius, Math_Cos(angle), Q12_SHIFT);

    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);
    newPosY  = MIN(chara->properties_E4.unk0.properties_124.val32, newPosY);
    newPosY -= Q12(1.5f) + Rng_RandQ12() / 2;
    if (newPosY < sharedFunc_800D5274_0_s01())
    {
        newPosY = sharedFunc_800D5274_0_s01();
    }

    chara->properties_E4.unk0.field_F8.vx = newPosX;
    chara->properties_E4.unk0.field_F8.vy = newPosY;
    chara->properties_E4.unk0.field_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(chara);
}
