void sharedFunc_800DF8A0_2_s00(s_SubCharacter* airScreamer)
{
    s32 var_a3;
    s32 idx0;
    s32 idx1;
    s32 temp3;
    s32 temp4;
    s_func_800D2E04* ptr;

    if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_4, true) &&
        airScreamer->model_0.anim_4.time_4 > Q12(64.0f))
    {
        idx0 = 4;
        var_a3 = 32;
    }
    else
    {
        idx0 = 2;
        var_a3 = 30;
    }

    temp3 = sharedData_800CAA98_0_s01.unk_380[idx0][0];
    temp4 = sharedData_800CAA98_0_s01.unk_380[idx0][1];

    sharedData_800E21D0_0_s01.field_B4[0][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[0][1] = temp4;

    ptr = &sharedData_800CAA98_0_s01;

    idx1                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx1][2] = ptr->unk_380[11][0];
    sharedData_800E21D0_0_s01.field_B4[idx1][1] = ptr->unk_380[11][1];

    idx1                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx1][1] = ptr->unk_380[var_a3][1];
    sharedData_800E21D0_0_s01.field_B4[idx1][2] = 0;

    sharedFunc_800D5E78_0_s01(airScreamer, 0);
}
