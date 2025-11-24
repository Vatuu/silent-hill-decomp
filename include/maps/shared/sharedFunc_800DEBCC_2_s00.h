void sharedFunc_800DEBCC_2_s00(s_SubCharacter* chara)
{
    s32 posX;
    s32 posZ;
    s32 posY;

    posX = chara->properties_E4.unk0.pos_104.vx;
    posZ = chara->properties_E4.unk0.pos_104.vz;

    posY = func_80080884(posX, posZ);
    posY = MIN(chara->properties_E4.unk0.properties_124.val32, posY);

    posY -= Q12(1.7f);

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
