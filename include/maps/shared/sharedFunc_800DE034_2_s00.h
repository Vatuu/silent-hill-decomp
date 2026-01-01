void sharedFunc_800DE034_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist)
{
    q19_12 scaledRadius;
    q19_12 angle;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    scaledRadius = FP_MULTIPLY_PRECISE(dist, Rng_RandQ12(), Q12_SHIFT);
    angle        = Rng_RandQ12();
    posX         = vec->vx + FP_MULTIPLY_PRECISE(scaledRadius, Math_Sin(angle), Q12_SHIFT);
    posZ         = vec->vz + FP_MULTIPLY_PRECISE(scaledRadius, Math_Cos(angle), Q12_SHIFT);

    posY                                  = Collision_GroundHeightGet(posX, posZ);
    airScreamerProps.targetPosition_F8.vx = posX;
    airScreamerProps.targetPosition_F8.vy = posY;
    airScreamerProps.targetPosition_F8.vz = posZ;

    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamerProps
}
