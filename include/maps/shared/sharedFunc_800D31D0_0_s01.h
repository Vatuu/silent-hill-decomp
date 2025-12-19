bool sharedFunc_800D31D0_0_s01(s_SubCharacter* chara, VECTOR3* pos, s32 arg2)
{
    q3_12  rotY;
    q19_12 offsetX;
    q19_12 offsetZ;
    s32    temp_s3;
    q19_12 var_s1;
    q51_12 roughDist;
    q52_12 distMax;
    s32    idx;

    idx     = sharedData_800CAA98_0_s01.field_D3C[chara->properties_E4.unk0.field_E8_4][chara->properties_E4.unk0.field_E8_8];
    var_s1  = sharedData_800CAA98_0_s01.field_D24[1][idx][0];
    temp_s3 = sharedData_800CAA98_0_s01.field_D24[1][idx][1];

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

    if (chara->model_0.state_2 == 3 || chara->model_0.state_2 == 9)
    {
        var_s1 += Q12(1.0f);
    }

    rotY    = chara->rotation_24.vy;
    offsetX = pos->vx - (chara->position_18.vx + FP_MULTIPLY_PRECISE(temp_s3, Math_Sin(rotY), Q12_SHIFT));
    offsetZ = pos->vz - (chara->position_18.vz + FP_MULTIPLY_PRECISE(temp_s3, Math_Cos(rotY), Q12_SHIFT));

    roughDist = FP_SQUARE_PRECISE(offsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    distMax = FP_SQUARE_PRECISE(var_s1, Q12_SHIFT);
    distMax = FP_MULTIPLY_PRECISE(distMax, arg2, Q12_SHIFT);
    if (roughDist > distMax)
    {
        return false;
    }
    else
    {
        return true;
    }
}
