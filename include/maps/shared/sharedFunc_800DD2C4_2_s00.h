void sharedFunc_800DD2C4_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2)
{
    q19_12 playerPosX;
    q19_12 playerPosZ;
    q19_12 newPosX;
    q19_12 newPosZ;
    q19_12 dist;
    q19_12 headingAngle;
    q19_12 angleStep;
    q19_12 unkDeltaAngle;
    s32    i;

    newPosX = airScreamer->position_18.vx;
    newPosZ = airScreamer->position_18.vz;
    playerPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;

    unkDeltaAngle = FP_ANGLE_NORM_S(airScreamer->rotation_24.vy - ratan2(newPosX - playerPosX, newPosZ - playerPosZ));
    headingAngle = airScreamer->rotation_24.vy + FP_ANGLE(180.0f);
    angleStep = unkDeltaAngle > FP_ANGLE(0.0f);
    angleStep = (arg2 != angleStep) ? FP_ANGLE(45.0f) : FP_ANGLE(-45.0f);

    airScreamer->properties_E4.unk0.field_F8.vx = playerPosX;
    airScreamer->properties_E4.unk0.field_F8.vz = playerPosZ;

    for (i = 8; i > 0; i--, headingAngle += angleStep)
    {
        dist = FP_MULTIPLY_PRECISE(Rng_RandQ12(), Q12(6.0f), Q12_SHIFT) + Q12(19.0f);
        newPosX = playerPosX + FP_MULTIPLY_PRECISE(dist, Math_Sin(headingAngle), Q12_SHIFT);
        newPosZ = playerPosZ + FP_MULTIPLY_PRECISE(dist, Math_Cos(headingAngle), Q12_SHIFT);

        unkDeltaAngle = Collision_GroundHeightGet(newPosX, newPosZ);
        unkDeltaAngle = MIN(unkDeltaAngle, 0);

        airScreamer->position_18.vy                 = unkDeltaAngle + arg1;
        airScreamer->position_18.vx                 = newPosX;
        airScreamer->position_18.vz                 = newPosZ;
        airScreamer->properties_E4.unk0.field_F8.vy = airScreamer->position_18.vy;

        if (func_8008F914(newPosX, newPosZ) && func_800808AC(newPosX, newPosZ) &&
            sharedFunc_800D4AEC_0_s01(airScreamer, NULL, &airScreamer->properties_E4.unk0.field_F8, NULL))
        {
            break;
        }
    }

    if (i == 0)
    {
        airScreamer->position_18.vx = playerPosX + Q12(50.0f);
        airScreamer->position_18.vy = sharedFunc_800D5274_0_s01() * 2;
        airScreamer->position_18.vz = playerPosZ + Q12(50.0f);
    }
}
