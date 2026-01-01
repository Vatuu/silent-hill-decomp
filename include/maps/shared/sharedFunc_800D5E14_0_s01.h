void sharedFunc_800D5E14_0_s01(s_SubCharacter* airScreamer)
{
    s32                          idx;
    s_sharedData_800E21D0_0_s01* base;
    s_func_800D2E04*             src;

    src = &sharedData_800CAA98_0_s01;
    base = &sharedData_800E21D0_0_s01;

    idx = 0;
    base->field_B4[idx][2] = src->unk_380[7][0];
    base->field_B4[idx][1] = src->unk_380[7][1];

    idx = 1;
    base->field_B4[idx][2] = src->unk_380[19][0];
    base->field_B4[idx][1] = src->unk_380[19][1];

    idx = 3;
    base->field_B4[idx][2] = 0;
    base->field_B4[idx][1] = src->unk_380[35][1];

    sharedFunc_800D5E78_0_s01(airScreamer, 0);
}
