void sharedFunc_800D5D80_0_s01(s_SubCharacter* chara)
{
    q19_12                       angle0;
    q19_12                       angle1;
    s32                          idx;
    s_sharedData_800E21D0_0_s01* base;
    s_func_800D2E04*             src;

    angle0 = func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    angle1 = FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy);
    src = &sharedData_800CAA98_0_s01;
    base = &sharedData_800E21D0_0_s01;

    idx = 0;
    base->field_B4[idx][2] = src->unk_380[7][0];
    base->field_B4[idx][1] = src->unk_380[7][1];

    idx = 1;
    base->field_B4[idx][2] = src->unk_380[20][0];
    base->field_B4[idx][1] = src->unk_380[20][1];

    idx = 3;
    base->field_B4[idx][2] = 0;
    base->field_B4[idx][1] = src->unk_380[35][1];

    if (angle1 < FP_ANGLE(0.0f))
    {
        angle1 += FP_ANGLE(0.3f);
    }

    sharedFunc_800D5E78_0_s01(chara, angle1 >> 2);
}
