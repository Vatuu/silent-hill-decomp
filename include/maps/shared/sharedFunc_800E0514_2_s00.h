void sharedFunc_800E0514_2_s00(s_SubCharacter* airScreamer)
{
    s32              temp_t4;
    s32              var_t5;
    s32              var_t6;
    s32              temp_a0;
    s32              idx;
    s32              idx2;
    s_func_800D2E04* ptr;
    s32              temp_s1;

    temp_s1 = airScreamer->properties_E4.airScreamer.targetPosition_F8.vy - airScreamer->position_18.vy;

    temp_t4 = func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.airScreamer.targetPosition_F8);
    temp_t4 = FP_ANGLE_NORM_S(temp_t4 - airScreamer->rotation_24.vy);

    temp_a0 = sharedData_800CAA98_0_s01.unk_380[37][0];
    var_t6  = sharedData_800CAA98_0_s01.unk_380[37][1];
    var_t5  = temp_a0 / 2;

    if (temp_t4 < 6)
    {
        if (temp_t4 < -5)
        {
            var_t6 = -var_t6;
            var_t5 = -var_t5;
        }
        else
        {
            var_t6 = 0;
            var_t5 = 0;
        }
    }

    idx2                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx2][3] = temp_s1;
    sharedData_800E21D0_0_s01.field_B4[idx2][0] = 1;

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_t5;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t6;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = temp_t4;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    ptr = &sharedData_800CAA98_0_s01;

    sharedData_800E21D0_0_s01.field_B4[0][2] = ptr->unk_380[9][0];
    sharedData_800E21D0_0_s01.field_B4[0][1] = ptr->unk_380[9][1];

    sharedData_800E21D0_0_s01.field_B4[idx2][2] = ptr->unk_380[22][0];
    sharedData_800E21D0_0_s01.field_B4[idx2][1] = ptr->unk_380[22][1];

    sharedFunc_800D5E78_0_s01(airScreamer, temp_t4 / 2);
}