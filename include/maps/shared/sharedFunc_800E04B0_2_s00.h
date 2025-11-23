void sharedFunc_800E04B0_2_s00(s_SubCharacter* chara)
{
    s32              idx;
    s_func_800D2E04* src;

    src = &sharedData_800CAA98_0_s01;

    idx = 0;
    sharedData_800E21D0_0_s01.field_B4[0][2] = src->unk_380[9][0];
    sharedData_800E21D0_0_s01.field_B4[0][1] = src->unk_380[9][1];

    idx = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = 0;

    idx = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = src->unk_380[26][0];
    sharedData_800E21D0_0_s01.field_B4[idx][1] = src->unk_380[26][1];

    idx = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] =src->unk_380[37][1];

    sharedFunc_800D5E78_0_s01(chara, 0);
}
