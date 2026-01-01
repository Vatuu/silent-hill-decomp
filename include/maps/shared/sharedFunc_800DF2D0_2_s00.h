void sharedFunc_800DF2D0_2_s00(s_SubCharacter* airScreamer)
{
    q19_12                       angleDiff;
    s32                          idx0;
    s_sharedData_800E21D0_0_s01* dst;
    s_func_800D2E04*             src;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    angleDiff = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

    src = &sharedData_800CAA98_0_s01;
    dst = &sharedData_800E21D0_0_s01;

    idx0                   = 3;
    dst->field_B4[idx0][2] = 0;

    idx0                   = 0;
    dst->field_B4[idx0][2] = src->unk_380[2][0];
    dst->field_B4[idx0][1] = src->unk_380[2][1];

    idx0                   = 1;
    dst->field_B4[idx0][2] = src->unk_380[11][0];
    dst->field_B4[idx0][1] = src->unk_380[11][1];

    idx0                   = 3;
    dst->field_B4[idx0][1] = src->unk_380[30][1];

    sharedFunc_800D5E78_0_s01(airScreamer, angleDiff);

    #undef airScreamerProps
}
