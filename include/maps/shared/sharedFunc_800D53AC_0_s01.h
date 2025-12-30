void sharedFunc_800D53AC_0_s01(s_SubCharacter* chara)
{
    s32 targetX, targetY, targetZ, altY;

    s32 playerX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    s32 playerY = g_SysWork.playerWork_4C.player_0.position_18.vy;
    s32 playerZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    s32 playerFacing = (s16)g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    s32 playerRadius = (s16)g_SysWork.playerWork_4C.player_0.field_D4.field_0;

    s32 charaX = chara->position_18.vx;
    s32 charaY = chara->position_18.vy;
    s32 charaZ = chara->position_18.vz;
    s32 charaFacing = (s16)chara->rotation_24.vy;
    s32 charaRadius = (s16)chara->field_D4.field_0;
    
    const s32 playerFacingCheck = FP_ANGLE(60.0f);
    const s32 charaFacingCheck = FP_ANGLE(90.0f);
    
    const s32 playerFacingCheckMin = -FP_ANGLE(60.0f);
    s32 playerFacingCheckMax = FP_ANGLE(60.0f);

    s32 xDelta = playerX - charaX;
    s32 zDelta = playerZ - charaZ;
    s32 distance = SquareRoot12(FP_MULTIPLY((s64)xDelta, (s64)xDelta, 12) + FP_MULTIPLY((s64)zDelta, (s64)zDelta, 12));
    s32 angle = ratan2(xDelta, zDelta);

    // Adjust the angle depending on distance and facing
    // Some sort of avoidance handling?
    s32 angleDelta = FP_ANGLE_NORM_S(angle - charaFacing);
    if (((playerRadius + (charaRadius * 2)) < distance) && Math_CheckSignedRange(angleDelta, playerFacingCheck))
    {
        angle += (angleDelta > 0 ? -FP_ANGLE(60.0f) : FP_ANGLE(60.0f));
    }
    else
    {
        angle += FP_ANGLE(180.0f); // Face away?
    }

    // Calculate a target position based on the player facing direction
    if (Math_CheckSignedRange(FP_ANGLE_NORM_S(angle - playerFacing), charaFacingCheck))
    {
        targetX = playerX + FP_MULTIPLY((s64)playerRadius, (s64)Math_Sin(angle), Q12_SHIFT);
        targetY = playerY + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        targetZ = playerZ + FP_MULTIPLY((s64)playerRadius, (s64)Math_Cos(angle), Q12_SHIFT);
    }
    else
    {
        targetX = playerX + FP_MULTIPLY((s64)playerRadius / 4, (s64)Math_Sin(angle), Q12_SHIFT);
        targetY = playerY + g_SysWork.playerWork_4C.player_0.field_C8.field_0;
        targetZ = playerZ + FP_MULTIPLY((s64)playerRadius / 4, (s64)Math_Cos(angle), Q12_SHIFT);
    }

    // Look for a more suitable target Y
    altY = Collision_GroundHeightGet(targetX, targetZ); // Ground height lookup?
    altY = MIN(chara->properties_E4.dummy.properties_E8[15].val32, altY);
    // Doesn't match with a MAX() macros
    if (altY < sharedFunc_800D5274_0_s01())
    {
        altY = sharedFunc_800D5274_0_s01();
    }
    targetY = MAX(altY - Q12(2.0), targetY);

    // Assign the target position to this character
    chara->properties_E4.npc.field_F8 = targetX;
    chara->properties_E4.npc.field_FC = targetY;
    chara->properties_E4.npc.field_100 = targetZ;

    // Additional processing
    sharedFunc_800D4E84_0_s01(chara);
}
