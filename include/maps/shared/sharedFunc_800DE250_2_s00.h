bool sharedFunc_800DE250_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 posX;
    q19_12 posZ;
    q19_12 groundHeight;
    q19_12 unkPosX;
    q19_12 unkPosZ;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 newPosZ;
    q19_12 newPosX;
    q19_12 targetPosX;
    q19_12 targetPosY;
    q19_12 angleToUnk;
    s32    sp28;
    bool   retCond;
    q19_12 angleStep;
    bool   cond;
    q19_12 unkDist;
    u32    cond1;
    q19_12 targetPosZ;
    q19_12 groundHeight1;
    q19_12 curAngle;
    s32    i;
    q19_12 dist;
    q19_12 distToUnk1;
    q19_12 unkDist1;

    targetPosX = Q12(0.0f);
    targetPosZ = Q12(0.0f);
    targetPosY = Q12(0.0f);
    retCond = false;
    dist = NO_VALUE;

    posX = airScreamer->position_18.vx;
    posZ = airScreamer->position_18.vz;
    groundHeight = airScreamer->properties_E4.airScreamer.groundHeight_124;

    unkPosX  = airScreamer->properties_E4.airScreamer.position_104.vx;
    unkPosZ = airScreamer->properties_E4.airScreamer.position_104.vz;

    cond = sharedFunc_800D4A80_0_s01(airScreamer) == 1;

    deltaX = posX - unkPosX;
    deltaZ = posZ - unkPosZ;
    angleToUnk = ratan2(deltaX, deltaZ);

    sp28    = SquareRoot12(FP_SQUARE_PRECISE(deltaX, Q12_SHIFT) + FP_SQUARE_PRECISE(deltaZ, Q12_SHIFT));
    unkDist = (Rng_RandQ12() * 4) + Q12(4.0f);

    if (Rng_TestProbability(Q12(0.5f)))
    {
        angleStep = FP_ANGLE(22.5f);
    }
    else
    {
        angleStep = FP_ANGLE(-22.5f);
    }

    for (i = 0, curAngle = angleToUnk; i < 16; i++, curAngle += angleStep)
    {
        // TODO: Same as
        // if (FP_ANGLE_NORM_S(var_s3 - sp24) >= FP_ANGLE(150.0f) || FP_ANGLE_NORM_S(var_s3 - sp24) < FP_ANGLE(-150.0f))
        // but that uses `sltiu` instead of `sltu`.
        cond1 = FP_ANGLE(300.0f) - 1;
        cond1 = cond1 < (FP_ANGLE_NORM_S(curAngle - angleToUnk) + FP_ANGLE(150.0f));
        if (!cond1)
        {
            deltaX = Q12_MULT_PRECISE(unkDist, Math_Sin(curAngle));
            newPosZ = Q12_MULT_PRECISE(unkDist, Math_Cos(curAngle));

            newPosX                      = posX + deltaX;
            sharedData_800F21CC_2_s00.vx = newPosX;

            newPosZ                     += posZ;
            sharedData_800F21CC_2_s00.vz = newPosZ;

            if (!cond)
            {
                groundHeight1 = Collision_GroundHeightGet(newPosX, newPosZ);
                if (groundHeight < groundHeight1)
                {
                    groundHeight1 = groundHeight;
                }

                groundHeight1 -= Q12(1.5f) + (Rng_RandQ12() / 2);
                if (groundHeight1 < sharedFunc_800D5274_0_s01())
                {
                    groundHeight1 = sharedFunc_800D5274_0_s01();
                }
                sharedData_800F21CC_2_s00.vy = groundHeight1;
            }

            sharedFunc_800D4AEC_0_s01(airScreamer, NULL, &sharedData_800F21CC_2_s00, &sharedData_800F21CC_2_s00);

            distToUnk1  = Math_Distance2dGet(&airScreamer->properties_E4.airScreamer.position_104, &sharedData_800F21CC_2_s00);
            unkDist1 = distToUnk1 + (Math_Distance2dGet(&airScreamer->position_18, &sharedData_800F21CC_2_s00) * 2);

            if (dist < unkDist1)
            {
                deltaZ = distToUnk1;
                retCond     = deltaZ < sp28;
                dist   = unkDist1 + Q12(0.1f);

                targetPosX   = sharedData_800F21CC_2_s00.vx;
                targetPosY   = sharedData_800F21CC_2_s00.vy;
                targetPosZ = sharedData_800F21CC_2_s00.vz;
            }
        }
    }

    // Set new target position.
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vx = targetPosX;
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vz = targetPosZ;
    if (cond)
    {
        airScreamer->properties_E4.airScreamer.targetPosition_F8.vy = Collision_GroundHeightGet(targetPosX, targetPosZ);
    }
    else
    {
        airScreamer->properties_E4.airScreamer.targetPosition_F8.vy = targetPosY;
    }

    sharedFunc_800D4E84_0_s01(airScreamer);

    return retCond;
}
