void sharedFunc_800D5C90_0_s01(s_SubCharacter* airScreamer)
{
    s32                          angle0;
    s32                          angle1;
    s32                          element0;
    s32                          element1;
    s32                          idx;
    s_sharedData_800E21D0_0_s01* base;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    angle0 = func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    angle1 = FP_ANGLE_NORM_S(angle0 - airScreamer->rotation_24.vy);

    element0 = sharedData_800CAA98_0_s01.unk_380[35][0] / 2;
    element1 = sharedData_800CAA98_0_s01.unk_380[35][1];

    if (angle1 <= FP_ANGLE(0.5f))
    {
        element1 = -element1;
        if (angle1 < FP_ANGLE(-0.5f))
        {
            element0 = -element0;
        }
        else
        {
            element1 = 0;
            element0 = 0;
        }
    }

    base = &sharedData_800E21D0_0_s01;

    idx = 0;
    base->field_B4[idx][3] = 0;
    base->field_B4[idx][0] = 1;
    base->field_B4[idx][2] = sharedData_800CAA98_0_s01.unk_380[7][0];
    base->field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[7][1];

    idx = 1;
    base->field_B4[idx][3] = 0;
    base->field_B4[idx][0] = 1;
    base->field_B4[idx][2] = sharedData_800CAA98_0_s01.unk_380[15][0];
    base->field_B4[idx][1] = sharedData_800CAA98_0_s01.unk_380[15][1];

    idx = 3;
    base->field_B4[idx][2] = element0;
    base->field_B4[idx][1] = element1;
    base->field_B4[idx][3] = angle1;
    base->field_B4[idx][0] = 1;

    sharedFunc_800D5E78_0_s01(airScreamer, angle1 / 2);

    #undef airScreamerProps
}
