void sharedFunc_800DDF74_2_s00(s_SubCharacter* airScreamer, q19_12 dist, q19_12 headingAngle)
{
    q19_12 newPosX;
    q19_12 newPosZ;
    q19_12 newPosY;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    newPosX = airScreamer->position_18.vx;
    newPosZ = airScreamer->position_18.vz;

    newPosX += Q12_MULT_PRECISE(dist, Math_Sin(headingAngle));
    newPosZ += Q12_MULT_PRECISE(dist, Math_Cos(headingAngle));
    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);

    airScreamerProps.targetPosition_F8.vx = newPosX;
    airScreamerProps.targetPosition_F8.vy = newPosY;
    airScreamerProps.targetPosition_F8.vz = newPosZ;
    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
