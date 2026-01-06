void sharedFunc_800DE11C_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 playerPosX;
    q19_12 playerPosZ;
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;
    q19_12 headingAngle;
    q19_12 dist;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    playerPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    dist       = g_SysWork.playerWork_4C.player_0.field_D4.radius_0;

    headingAngle = Math_AngleBetweenPositionsGet(g_SysWork.playerWork_4C.player_0.position_18, airScreamer->position_18);
    newPosX      = playerPosX + Q12_MULT_PRECISE(dist, Math_Sin(headingAngle));
    newPosZ      = playerPosZ + Q12_MULT_PRECISE(dist, Math_Cos(headingAngle));
    newPosY      = Collision_GroundHeightGet(newPosX, newPosZ);

    // TODO: Work out which character this is for. Tracking projected player position?
    airScreamerProps.targetPosition_F8.vx = newPosX;
    airScreamerProps.targetPosition_F8.vy = newPosY;
    airScreamerProps.targetPosition_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
