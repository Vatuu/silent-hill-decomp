void sharedFunc_800DF60C_2_s00(s_SubCharacter* arg0)
{
    s32 temp_s0;
    s32 temp_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 temp3;
    s32 temp4;
    s32 idx;

    temp_s0 = arg0->model_0.anim_4.status_0 | 1;
    temp_t1 = func_80080478(&arg0->position_18, &arg0->properties_E4.airScreamer.targetPosition_F8);
    temp_t1 = FP_ANGLE_NORM_S(temp_t1 - arg0->rotation_24.vy);

    if (temp_s0 == 0x2D)
    {
        var_t4 = 0xC;
    }
    else
    {
        var_t4 = 0xB;
    }

    var_t2 = sharedData_800CAA98_0_s01.unk_380[30][0];
    var_t3 = sharedData_800CAA98_0_s01.unk_380[30][1];

    if (temp_t1 < 6)
    {
        if (temp_t1 < -5)
        {
            var_t3 = -var_t3;
            var_t2 = -var_t2;
        }
        else
        {
            var_t3 = 0;
            var_t2 = 0;
        }
    }

    sharedData_800E21D0_0_s01.field_B4[0][3] = 0;
    sharedData_800E21D0_0_s01.field_B4[0][0] = 1;
    sharedData_800E21D0_0_s01.field_B4[0][2] = sharedData_800CAA98_0_s01.unk_380[2][0];
    sharedData_800E21D0_0_s01.field_B4[0][1] = sharedData_800CAA98_0_s01.unk_380[2][1];

    temp3 = sharedData_800CAA98_0_s01.unk_380[var_t4][0];
    temp4 = sharedData_800CAA98_0_s01.unk_380[var_t4][1];

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_t2;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t3;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = temp_t1;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    idx                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = temp4;

    sharedFunc_800D5E78_0_s01(arg0, temp_t1 / 2);
}