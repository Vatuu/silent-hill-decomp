void sharedFunc_800DF8A0_2_s00(s_SubCharacter* arg0)
{
    s32 var_a3;
    s32 var_v0;
    s32 idx;
    s32 temp3;
    s32 temp4;

    if (arg0->model_0.anim_4.status_0 == 9 && arg0->model_0.anim_4.time_4 > 0x40000)
    {
        var_v0 = 4;
        var_a3 = 0x20;
    }
    else
    {
        var_v0 = 2;
        var_a3 = 0x1E;
    }

    temp3 = sharedData_800CAA98_0_s01.unk_380[var_v0][0];
    temp4 = sharedData_800CAA98_0_s01.unk_380[var_v0][1];

    sharedData_800E21D0_0_s01.field_B4[0][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[0][1] = temp4;

    idx                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = sharedData_800CAA98_0_s01.unk_380[11][0];
    sharedData_800E21D0_0_s01.field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[11][1];

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[var_a3][1];
    sharedData_800E21D0_0_s01.field_B4[idx][2] = 0;

    sharedFunc_800D5E78_0_s01(arg0, 0);
}