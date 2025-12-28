bool sharedFunc_800D2FB4_0_s01(s_SubCharacter* airScreamer, VECTOR3* playerPos, s32 playerField10C)
{
    q3_12  rotY;
    q19_12 offsetY;
    q19_12 offsetZ;
    s32    idx;
    q19_12 dist;
    q19_12 var_s1;
    u64    roughDist;

    if (airScreamer->properties_E4.player.flags_11C & (PlayerFlag_Unk19 | PlayerFlag_Unk20))
    {
        idx = 2;
    }
    else
    {
        // TODO: Does `ANIM_STATUS_IS_ACTIVE` fit?
        if ((airScreamer->model_0.anim_4.status_0 | 0x1) == 27 ||
            (airScreamer->model_0.anim_4.status_0 | 0x1) == 29)
        {
            idx = 0;
        }
        else
        {
            idx = 1;
        }
    }

    var_s1  = sharedData_800CAA98_0_s01.field_D24[0][idx][0];
    dist = sharedData_800CAA98_0_s01.field_D24[0][idx][1];

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            break;

        case GameDifficulty_Normal:
            var_s1 += Q12(0.5f);
            break;

        case GameDifficulty_Hard:
            var_s1 += Q12(1.0f);
            break;
    }

    rotY    = airScreamer->rotation_24.vy;
    offsetY = playerPos->vx - (airScreamer->position_18.vx + FP_MULTIPLY_PRECISE(dist, Math_Sin(rotY), Q12_SHIFT));
    offsetZ = playerPos->vz - (airScreamer->position_18.vz + FP_MULTIPLY_PRECISE(dist, Math_Cos(rotY), Q12_SHIFT));

    roughDist = FP_SQUARE_PRECISE(offsetY, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    if (roughDist > FP_SQUARE_PRECISE(FP_MULTIPLY_PRECISE(var_s1, playerField10C, Q12_SHIFT), Q12_SHIFT))
    {
        return false;
    }
    else
    {
        return true;
    }
}
