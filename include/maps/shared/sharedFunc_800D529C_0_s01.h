void sharedFunc_800D529C_0_s01(s_SubCharacter* airScreamer, q19_12 radius, q19_12 headingAngle)
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    newPosX = airScreamer->position_18.vx;
    newPosZ = airScreamer->position_18.vz;

    newPosX = newPosX + Q12_MULT_PRECISE(radius, Math_Sin(headingAngle));
    newPosZ = newPosZ + Q12_MULT_PRECISE(radius, Math_Cos(headingAngle));

    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);
    newPosY  = MIN(airScreamerProps.groundHeight_124, newPosY);
    newPosY -= Q12(1.5f) + Rng_RandQ12() / 2;
    if (newPosY < sharedFunc_800D5274_0_s01())
    {
        newPosY = sharedFunc_800D5274_0_s01();
    }

    airScreamerProps.targetPosition_F8.vx = newPosX;
    airScreamerProps.targetPosition_F8.vy = newPosY;
    airScreamerProps.targetPosition_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
