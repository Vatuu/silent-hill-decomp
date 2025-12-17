s32 sharedFunc_800D2FB4_0_s01(s_SubCharacter* chara, VECTOR3* playerPos, s32 playerField10C)
{
    s16 rotY;
    s32 newY;
    s32 z;
    s32 var_a0;
    s32 temp_s2;
    s32 var_s1;
    u64 temp;

    if (chara->properties_E4.player.flags_11C & 0x180000)
    {
        var_a0 = 2;
    }
    else
    {
        if ((chara->model_0.anim_4.status_0 | 1) == 0x1B || (chara->model_0.anim_4.status_0 | 1) == 0x1D)
        {
            var_a0 = 0;
        }
        else
        {
            var_a0 = 1;
        }
    }

    var_s1  = sharedData_800CAA98_0_s01.field_D24[0][var_a0][0];
    temp_s2 = sharedData_800CAA98_0_s01.field_D24[0][var_a0][1];

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case -1:
            break;
        case 0:
            var_s1 += 0x800;
            break;
        case 1:
            var_s1 += 0x1000;
            break;
    }

    rotY = chara->rotation_24.vy;
    newY = playerPos->vx - (chara->position_18.vx + FP_MULTIPLY_PRECISE(temp_s2, Math_Sin(rotY), Q12_SHIFT));
    z    = playerPos->vz - (chara->position_18.vz + FP_MULTIPLY_PRECISE(temp_s2, Math_Cos(rotY), Q12_SHIFT));

    temp = FP_SQUARE_PRECISE(newY, Q12_SHIFT) + FP_SQUARE_PRECISE(z, Q12_SHIFT);

    if (temp > FP_SQUARE_PRECISE(FP_MULTIPLY_PRECISE(var_s1, playerField10C, Q12_SHIFT), Q12_SHIFT))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}