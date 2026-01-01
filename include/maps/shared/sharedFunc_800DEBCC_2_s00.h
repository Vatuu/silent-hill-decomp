void sharedFunc_800DEBCC_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    newPosX = airScreamer->properties_E4.unk0.pos_104.vx;
    newPosZ = airScreamer->properties_E4.unk0.pos_104.vz;

    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);
    newPosY  = MIN(airScreamer->properties_E4.unk0.properties_124.val32, newPosY);
    newPosY -= Q12(1.7f);
    if (newPosY < sharedFunc_800D5274_0_s01())
    {
        newPosY = sharedFunc_800D5274_0_s01();
    }

    // TODO: Work out which character this is for.
    airScreamer->properties_E4.unk0.field_F8.vx = newPosX;
    airScreamer->properties_E4.unk0.field_F8.vy = newPosY;
    airScreamer->properties_E4.unk0.field_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);
}
