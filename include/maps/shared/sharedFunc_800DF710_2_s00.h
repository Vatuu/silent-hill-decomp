void sharedFunc_800DF710_2_s00(s_SubCharacter* chara)
{
    q19_12                       angle0;
    q19_12                       angle1;
    s32                          idx;
    s32                          animStatus;
    s32                          animIdx;
    s32                          element0;
    s32                          element1;
    s32                          element4;
    s32                          element3;
    s32                          element2;
    s_sharedData_800E21D0_0_s01* base;

    animStatus = chara->model_0.anim_4.status_0 | 1; // TODO: Use macro for this.
    angle0     = func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    angle0     = FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy);

    if (animStatus == ANIM_STATUS(22, true))
    {
        animIdx = 12;
    }
    else
    {
        animIdx = 11;
    }

    element0 = sharedData_800CAA98_0_s01.unk_380[29][0];
    element1 = sharedData_800CAA98_0_s01.unk_380[29][1];

    if (angle0 <= FP_ANGLE(0.5f))
    {
        element1 = -element1;
        if (angle0 < FP_ANGLE(-0.5f))
        {
            element0 = -element0;
        }
        else
        {
            element1 = 0;
            element0 = 0;
        }
    }

    element2 = sharedData_800CAA98_0_s01.unk_380[1][0];
    base     = &sharedData_800E21D0_0_s01;

    idx                    = 0;
    base->field_B4[idx][2] = element2;
    base->field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[1][1];

    idx                    = 1;
    element3               = sharedData_800CAA98_0_s01.unk_380[animIdx][0];
    element4               = sharedData_800CAA98_0_s01.unk_380[animIdx][1];
    base->field_B4[idx][2] = element3;
    base->field_B4[idx][1] = element4;

    idx                    = 3;
    base->field_B4[idx][2] = element0;
    base->field_B4[idx][1] = element1;
    base->field_B4[idx][3] = angle0;
    base->field_B4[idx][0] = 1;

    sharedFunc_800D5E78_0_s01(chara, angle0 / 2);
}
