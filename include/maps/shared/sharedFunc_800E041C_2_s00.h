void sharedFunc_800E041C_2_s00(s_SubCharacter* chara)
{
    q19_12           angle0;
    q19_12           angle1;
    s32              idx;
    s_func_800D2E04* src;

    angle0 = func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    angle1 = FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy);

    src = &sharedData_800CAA98_0_s01;

    idx = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = 0;

    idx = 0;
    sharedData_800E21D0_0_s01.field_B4[0][2] = src->unk_380[9][0];
    sharedData_800E21D0_0_s01.field_B4[0][1] = src->unk_380[9][1];

    idx = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = src->unk_380[27][0];
    sharedData_800E21D0_0_s01.field_B4[idx][1] = src->unk_380[27][1];

    idx = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] =src->unk_380[37][1];

    if (angle1 < FP_ANGLE(0.0f))
    {
        angle1 += FP_ANGLE(0.3f);
    }

    sharedFunc_800D5E78_0_s01(chara, angle1 >> 2);
}
