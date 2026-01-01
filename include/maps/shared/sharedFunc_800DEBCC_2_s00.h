void sharedFunc_800DEBCC_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 newPosX;
    q19_12 groundHeight;
    q19_12 newPosZ;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    newPosX = airScreamerProps.position_104.vx;
    newPosZ = airScreamerProps.position_104.vz;

    groundHeight  = Collision_GroundHeightGet(newPosX, newPosZ);
    groundHeight  = MIN(airScreamerProps.groundHeight_124, groundHeight);
    groundHeight -= Q12(1.7f);
    if (groundHeight < sharedFunc_800D5274_0_s01())
    {
        groundHeight = sharedFunc_800D5274_0_s01();
    }

    // TODO: Work out which character this is for.
    airScreamerProps.targetPosition_F8.vx = newPosX;
    airScreamerProps.targetPosition_F8.vy = groundHeight;
    airScreamerProps.targetPosition_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
