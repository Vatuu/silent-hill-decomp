void sharedFunc_800D5638_0_s01(s_SubCharacter* chara)
{
    s32                          idx0;
    s_sharedData_800E21D0_0_s01* dst;
    s_func_800D2E04*             src;

    src = &sharedData_800CAA98_0_s01;
    dst = &sharedData_800E21D0_0_s01;

    idx0 = 3;
    dst->field_B4[idx0][2] = 0;

    idx0 = 0;
    dst->field_B4[idx0][2] = src->unk_380[2][0];
    dst->field_B4[idx0][1] = src->unk_380[2][1];

    idx0 = 1;
    dst->field_B4[idx0][2] = src->unk_380[11][0];
    dst->field_B4[idx0][1] = src->unk_380[11][1];

    idx0 = 3;
    dst->field_B4[idx0][1] = src->unk_380[30][1];

    sharedFunc_800D5E78_0_s01(chara, FP_ANGLE(0.0f));
}
