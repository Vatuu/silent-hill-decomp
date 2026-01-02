s32 sharedFunc_800DEE24_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 playerPosX;
    q19_12 playerPosY;
    q19_12 playerPosZ;
    q19_12 posX;
    q19_12 posZ;
    q19_12 moveSpeed;
    q19_12 rotY;
    q19_12 playerheadingAngle;
    q19_12 playerOffsetZ;
    q19_12 temp_s3;
    q19_12 temp_s4;
    q19_12 temp_v0_2;
    q19_12 playerOffsetX;
    q19_12 var_s2;
    q19_12 playerMoveSpeed;
    q19_12 var_v1;

    playerheadingAngle = g_SysWork.playerWork_4C.player_0.headingAngle_3C;
    playerMoveSpeed    = g_SysWork.playerWork_4C.player_0.moveSpeed_38;

    playerPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosY = g_SysWork.playerWork_4C.player_0.position_18.vy;
    playerPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;

    posX = airScreamer->position_18.vx;
    posZ = airScreamer->position_18.vz;

    rotY      = airScreamer->rotation_24.vy;
    moveSpeed = airScreamer->moveSpeed_38;

    playerOffsetX = FP_MULTIPLY_PRECISE(playerMoveSpeed, Math_Sin(playerheadingAngle), Q12_SHIFT);
    playerOffsetZ = FP_MULTIPLY_PRECISE(playerMoveSpeed, Math_Cos(playerheadingAngle), Q12_SHIFT);

    sharedData_800F21FC_2_s00.vy = Q12(0.0f);
    sharedData_800F21FC_2_s00.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, playerOffsetX, Q12_SHIFT);
    sharedData_800F21FC_2_s00.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, playerOffsetZ, Q12_SHIFT);

    if (g_DeltaTime0 != Q12(0.0f) &&
        func_80069B24(&sharedData_800E2350_0_s01, &sharedData_800F21FC_2_s00, &g_SysWork.playerWork_4C.player_0))
    {
        playerOffsetX = sharedData_800E2350_0_s01.offset_0.vx;
        playerOffsetZ = sharedData_800E2350_0_s01.offset_0.vz;

        playerMoveSpeed = SquareRoot12(FP_SQUARE_PRECISE(playerOffsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(playerOffsetZ, Q12_SHIFT));
        playerMoveSpeed = FP_TO(playerMoveSpeed, Q12_SHIFT) / g_DeltaTime0;
        playerheadingAngle = ratan2(playerOffsetX, playerOffsetZ);
    }

    temp_v0_2 = Math_Cos(FP_ANGLE_NORM_S(rotY - playerheadingAngle));

    playerOffsetX = playerPosX - posX;
    playerOffsetZ = playerPosZ - posZ;

    var_s2    = moveSpeed - FP_MULTIPLY_PRECISE(playerMoveSpeed, temp_v0_2, Q12_SHIFT);
    temp_v0_2 = FP_ANGLE_NORM_S(ratan2(playerOffsetX, playerOffsetZ) - rotY);

    if (temp_v0_2 > -0x2AB && temp_v0_2 < 0x2AA)
    {
        playerOffsetZ = SquareRoot12(FP_SQUARE_PRECISE(playerOffsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(playerOffsetZ, Q12_SHIFT));

        if (var_s2 < Q12(1.0f))
        {
            var_s2 = Q12(1.0f);
        }

        var_s2 = FP_TO(playerOffsetZ, Q12_SHIFT) / var_s2;
        playerOffsetZ = FP_MULTIPLY_PRECISE(playerMoveSpeed, var_s2, Q12_SHIFT);
        playerOffsetX = FP_MULTIPLY_PRECISE(playerOffsetZ, Math_Sin(playerheadingAngle), Q12_SHIFT);
        playerOffsetZ = FP_MULTIPLY_PRECISE(playerOffsetZ, Math_Cos(playerheadingAngle), Q12_SHIFT);
    }
    else
    {
        var_s2 = Q12(10.0f);
        playerOffsetX = 0;
        playerOffsetZ = 0;
    }

    temp_s4 = playerPosX + playerOffsetX;
    temp_s3 = playerPosZ + playerOffsetZ;
    playerOffsetX  = playerPosY + g_SysWork.playerWork_4C.player_0.field_C8.field_0;

    playerOffsetZ = Collision_GroundHeightGet(temp_s4, temp_s3);
    var_v1 = airScreamer->properties_E4.airScreamer.groundHeight_124;

    if (var_v1 < playerOffsetZ)
    {
        playerOffsetZ = var_v1;
    }

    if (playerOffsetZ < sharedFunc_800D5274_0_s01())
    {
        playerOffsetZ = sharedFunc_800D5274_0_s01();
    }

    var_v1 = playerOffsetZ - Q12(2.0f);
    if (playerOffsetX < var_v1)
    {
        playerOffsetX = var_v1;
    }

    airScreamer->properties_E4.airScreamer.targetPosition_F8.vx = temp_s4;
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vy = playerOffsetX;
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vz = temp_s3;

    sharedFunc_800D4E84_0_s01(airScreamer);

    return var_s2;
}
