void sharedFunc_800D529C_0_s01(s_SubCharacter* airScreamer, q19_12 radius, q19_12 headingAngle)
{
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;

    newPosX = airScreamer->position_18.vx;
    newPosZ = airScreamer->position_18.vz;

    newPosX = newPosX + FP_MULTIPLY_PRECISE(radius, Math_Sin(headingAngle), Q12_SHIFT);
    newPosZ = newPosZ + FP_MULTIPLY_PRECISE(radius, Math_Cos(headingAngle), Q12_SHIFT);

    newPosY  = Collision_GroundHeightGet(newPosX, newPosZ);
    newPosY  = MIN(airScreamer->properties_E4.unk0.properties_124.val32, newPosY);
    newPosY -= Q12(1.5f) + Rng_RandQ12() / 2;
    if (newPosY < sharedFunc_800D5274_0_s01())
    {
        newPosY = sharedFunc_800D5274_0_s01();
    }

    airScreamer->properties_E4.unk0.field_F8.vx = newPosX;
    airScreamer->properties_E4.unk0.field_F8.vy = newPosY;
    airScreamer->properties_E4.unk0.field_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(airScreamer);
}
