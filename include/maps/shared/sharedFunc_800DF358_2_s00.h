void sharedFunc_800DF358_2_s00(s_SubCharacter* chara)
{
    s32 angle0;
    s32 element0;
    s32 element1;
    s_sharedData_800E21D0_0_s01* base;
    s32 idx;

    angle0     = func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    angle0     = FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy);
    element0 = sharedData_800CAA98_0_s01.unk_380[30][0] / 2;
    element1 = sharedData_800CAA98_0_s01.unk_380[30][1];

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

    base     = &sharedData_800E21D0_0_s01;

    base->field_B4[0][3]   = 0;
    base->field_B4[0][0]   = 1;

    idx                    = 1;
    base->field_B4[0][2]   = sharedData_800CAA98_0_s01.unk_380[2][0];
    base->field_B4[0][1]   = sharedData_800CAA98_0_s01.unk_380[2][1];
    base->field_B4[idx][2] = sharedData_800CAA98_0_s01.unk_380[11][0];
    base->field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[11][1];
    base->field_B4[idx][3] = 0;
    base->field_B4[idx][0] = 1;

    idx                    = 3;
    base->field_B4[idx][2] = element0;
    base->field_B4[idx][1] = element1;
    base->field_B4[idx][3] = angle0;
    base->field_B4[idx][0] = 1;

    sharedFunc_800D5E78_0_s01(chara, angle0 / 2);
}
