void sharedFunc_800DF60C_2_s00(s_SubCharacter* airScreamer)
{
    s32 temp_s0;
    s32 temp_t1;
    s32 var_t2;
    s32 var_t3;
    s32 idx1;
    s32 temp3;
    s32 temp4;
    s32 idx0;
    s_func_800D2E04* ptr;

    temp_s0 = airScreamer->model_0.anim_4.status_0 | 1;
    temp_t1 = func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.airScreamer.targetPosition_F8);
    temp_t1 = FP_ANGLE_NORM_S(temp_t1 - airScreamer->rotation_24.vy);

    if (temp_s0 == 45)
    {
        idx1 = 12;
    }
    else
    {
        idx1 = 11;
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

    ptr = &sharedData_800CAA98_0_s01;

    sharedData_800E21D0_0_s01.field_B4[0][3] = 0;
    sharedData_800E21D0_0_s01.field_B4[0][0] = 1;
    sharedData_800E21D0_0_s01.field_B4[0][2] = ptr->unk_380[2][0];
    sharedData_800E21D0_0_s01.field_B4[0][1] = ptr->unk_380[2][1];

    temp3 = ptr->unk_380[idx1][0];
    temp4 = ptr->unk_380[idx1][1];

    idx0                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx0][2] = var_t2;
    sharedData_800E21D0_0_s01.field_B4[idx0][1] = var_t3;
    sharedData_800E21D0_0_s01.field_B4[idx0][3] = temp_t1;
    sharedData_800E21D0_0_s01.field_B4[idx0][0] = 1;

    idx0                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx0][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[idx0][1] = temp4;

    sharedFunc_800D5E78_0_s01(airScreamer, temp_t1 / 2);
}
