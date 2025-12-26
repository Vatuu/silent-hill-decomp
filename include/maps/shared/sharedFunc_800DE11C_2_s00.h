void sharedFunc_800DE11C_2_s00(s_SubCharacter* chara)
{
    q19_12 playerPosX;
    q19_12 playerPosZ;
    q19_12 newPosX;
    q19_12 newPosY;
    q19_12 newPosZ;
    q19_12 headingAngle;
    q19_12 dist;

    playerPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    dist       = g_SysWork.playerWork_4C.player_0.field_D4.field_0;

    headingAngle = ratan2(chara->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx,
                          chara->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);
    newPosX      = playerPosX + FP_MULTIPLY_PRECISE(dist, Math_Sin(headingAngle), Q12_SHIFT);
    newPosZ      = playerPosZ + FP_MULTIPLY_PRECISE(dist, Math_Cos(headingAngle), Q12_SHIFT);
    newPosY      = Collision_GroundHeightGet(newPosX, newPosZ);

    // TODO: Work out which character this is for. Tracking projected player position?
    chara->properties_E4.unk0.field_F8.vx = newPosX;
    chara->properties_E4.unk0.field_F8.vy = newPosY;
    chara->properties_E4.unk0.field_F8.vz = newPosZ;

    sharedFunc_800D4E84_0_s01(chara);
}
