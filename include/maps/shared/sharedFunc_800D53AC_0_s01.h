void sharedFunc_800D53AC_0_s01(s_SubCharacter* airScreamer)
{
    #define PLAYER_ANGLE_RANGE       FP_ANGLE(60.0f)
    #define AIR_SCREAMER_ANGLE_RANGE FP_ANGLE(90.0f)
    
    q19_12 targetPosX;
    q19_12 targetPosY;
    q19_12 targetPosZ;
    q19_12 groundHeight;
    q19_12 playerPosX;
    q19_12 playerPosY;
    q19_12 playerPosZ;
    q19_12 playerHeadingAngle;
    q19_12 playerRadius;
    q19_12 charaPosX;
    q19_12 charaPosY;
    q19_12 charaPosZ;
    q19_12 charaHeadingAngle;
    q19_12 charaRadius;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 distToPlayer;
    q19_12 angleToPlayer;
    q19_12 angleDeltaToPlayer;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    // Set player parameters.
    playerPosX         = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosY         = g_SysWork.playerWork_4C.player_0.position_18.vy;
    playerPosZ         = g_SysWork.playerWork_4C.player_0.position_18.vz;
    playerHeadingAngle = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    playerRadius       = g_SysWork.playerWork_4C.player_0.field_D4.radius_0;

    // Set Air Screamer parameters.
    charaPosX         = airScreamer->position_18.vx;
    charaPosY         = airScreamer->position_18.vy;
    charaPosZ         = airScreamer->position_18.vz;
    charaHeadingAngle = airScreamer->rotation_24.vy;
    charaRadius       = airScreamer->field_D4.radius_0;

    // Compute relations.
    deltaX        = playerPosX - charaPosX;
    deltaZ        = playerPosZ - charaPosZ;
    distToPlayer  = SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT));
    angleToPlayer = ratan2(deltaX, deltaZ);

    // Adjust angle depending on distance and heading. Some sort of avoidance handling?
    angleDeltaToPlayer = FP_ANGLE_NORM_S(angleToPlayer - charaHeadingAngle);
    if ((playerRadius + (charaRadius * 2)) < distToPlayer && Math_CheckSignedRange(angleDeltaToPlayer, PLAYER_ANGLE_RANGE))
    {
        angleToPlayer += (angleDeltaToPlayer > FP_ANGLE(0.0f)) ? FP_ANGLE(-60.0f) : FP_ANGLE(60.0f);
    }
    else
    {
        angleToPlayer += FP_ANGLE(180.0f); // Turn away?
    }

    // Compute target position based on player heading angle.
    if (Math_CheckSignedRange(FP_ANGLE_NORM_S(angleToPlayer - playerHeadingAngle), AIR_SCREAMER_ANGLE_RANGE))
    {
        targetPosX = playerPosX + FP_MULTIPLY_PRECISE(playerRadius, Math_Sin(angleToPlayer), Q12_SHIFT);
        targetPosY = playerPosY + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        targetPosZ = playerPosZ + FP_MULTIPLY_PRECISE(playerRadius, Math_Cos(angleToPlayer), Q12_SHIFT);
    }
    else
    {
        targetPosX = playerPosX + FP_MULTIPLY_PRECISE(playerRadius / 4, Math_Sin(angleToPlayer), Q12_SHIFT);
        targetPosY = playerPosY + g_SysWork.playerWork_4C.player_0.field_C8.field_0;
        targetPosZ = playerPosZ + FP_MULTIPLY_PRECISE(playerRadius / 4, Math_Cos(angleToPlayer), Q12_SHIFT);
    }

    // Clamp to ground. TODO: Doesn't match with `MAX` macro.
    groundHeight = Collision_GroundHeightGet(targetPosX, targetPosZ);
    groundHeight = MIN(airScreamerProps.groundHeight_124, groundHeight);
    if (groundHeight < sharedFunc_800D5274_0_s01())
    {
        groundHeight = sharedFunc_800D5274_0_s01();
    }
    targetPosY = MAX(groundHeight - Q12(2.0f), targetPosY);

    // Set Air Screamer position to target.
    airScreamerProps.targetPosition_F8.vx = targetPosX;
    airScreamerProps.targetPosition_F8.vy = targetPosY;
    airScreamerProps.targetPosition_F8.vz = targetPosZ;

    // Additional processing.
    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef PLAYER_ANGLE_RANGE
    #undef AIR_SCREAMER_ANGLE_RANGE
    #undef airScreamerProps
}
