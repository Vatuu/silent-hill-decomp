bool sharedFunc_800D31D0_0_s01(s_SubCharacter* airScreamer, VECTOR3* pos, s32 arg2)
{
    q3_12  offsetHeadingAngle;
    q19_12 offsetDist;
    q19_12 offsetX;
    q19_12 offsetZ;
    q19_12 var_s1;
    q51_12 roughDist;
    q52_12 distMax;
    s32    idx;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    idx        = sharedData_800CAA98_0_s01.field_D3C[airScreamerProps.field_E8_4][airScreamerProps.field_E8_8];
    var_s1     = sharedData_800CAA98_0_s01.field_D24[1][idx][0];
    offsetDist = sharedData_800CAA98_0_s01.field_D24[1][idx][1];

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

    if (airScreamer->model_0.controlState_2 == AirScreamerControl_3 ||
        airScreamer->model_0.controlState_2 == AirScreamerControl_9)
    {
        var_s1 += Q12(1.0f);
    }

    offsetHeadingAngle = airScreamer->rotation_24.vy;
    offsetX            = pos->vx - (airScreamer->position_18.vx + FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(offsetHeadingAngle), Q12_SHIFT));
    offsetZ            = pos->vz - (airScreamer->position_18.vz + FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(offsetHeadingAngle), Q12_SHIFT));

    roughDist = FP_SQUARE_PRECISE(offsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    distMax   = FP_SQUARE_PRECISE(var_s1, Q12_SHIFT);
    distMax   = FP_MULTIPLY_PRECISE(distMax, arg2, Q12_SHIFT);
    if (roughDist > distMax)
    {
        return false;
    }
    else
    {
        return true;
    }

    #undef airScreamerProps
}
