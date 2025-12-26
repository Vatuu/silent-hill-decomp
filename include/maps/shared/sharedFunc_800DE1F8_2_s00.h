void sharedFunc_800DE1F8_2_s00(s_SubCharacter* chara) // 0x800DE514
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    newPosX = chara->properties_E4.player.field_104;
    newPosZ = chara->properties_E4.npc.field_10C;
    newPosY = Collision_GroundHeightGet(newPosX, newPosZ);

    // TODO: Find out which character this is for.
    chara->properties_E4.player.runTimer_F8        = newPosX;
    chara->properties_E4.player.exhaustionTimer_FC = newPosY;
    chara->properties_E4.player.field_100          = newPosZ;
    sharedFunc_800D4E84_0_s01(chara);
}
