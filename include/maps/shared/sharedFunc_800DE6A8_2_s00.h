void sharedFunc_800DE6A8_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist)
{
    q19_12 scaledRadius;
    q19_12 headingAngle;
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    scaledRadius = FP_MULTIPLY_PRECISE(dist, Rng_RandQ12(), Q12_SHIFT);
    headingAngle = Rng_RandQ12();
    newPosX      = vec->vx + FP_MULTIPLY_PRECISE(scaledRadius, Math_Sin(headingAngle), Q12_SHIFT);
    newPosZ      = vec->vz + FP_MULTIPLY_PRECISE(scaledRadius, Math_Cos(headingAngle), Q12_SHIFT);

    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);
    newPosY  = MIN(airScreamer->properties_E4.unk0.properties_124.val32, newPosY);
    newPosY -= Q12(1.5f) + (Rng_RandQ12() / 2);

    // `posY = MAX(posY, sharedFunc_800D5274_0_s01())`? Doesn't currently match.
    if (newPosY < sharedFunc_800D5274_0_s01())
    {
        newPosY = sharedFunc_800D5274_0_s01();
    }

    airScreamer->properties_E4.unk0.field_F8.vx = newPosX;
    airScreamer->properties_E4.unk0.field_F8.vy = newPosY;
    airScreamer->properties_E4.unk0.field_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);
}
