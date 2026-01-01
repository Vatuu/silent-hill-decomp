void sharedFunc_800DE1F8_2_s00(s_SubCharacter* airScreamer) // 0x800DE514
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    newPosX = airScreamerProps.position_104.vx;
    newPosZ = airScreamerProps.position_104.vz;
    newPosY = Collision_GroundHeightGet(newPosX, newPosZ);

    airScreamerProps.targetPosition_F8.vx = newPosX;
    airScreamerProps.targetPosition_F8.vy = newPosY;
    airScreamerProps.targetPosition_F8.vz = newPosZ;
    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
