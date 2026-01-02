void sharedFunc_800DF448_2_s00(s_SubCharacter* airScreamer, bool cond)
{
    s32 temp_a1;
    s32 temp_s2;
    s32 temp_t3;
    s32 var_a0;
    s32 var_a2;
    s32 var_t1;
    s32 var_t2;
    u32 var_v1;
    s32 var_v1_2;
    s32 temp;
    s32 temp2;
    s32 temp3;
    s32 temp4;
    s32 idx;
    s_func_800D2E04* ptr;

    temp_s2 = func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.airScreamer.position_110);
    temp_t3 = Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.airScreamer.position_110);
    temp_s2 = FP_ANGLE_NORM_S(temp_s2 - airScreamer->rotation_24.vy);

    temp_a1 = airScreamer->model_0.anim_4.status_0 | 1;

    if (temp_a1 == 0x2D)
    {
        var_a2 = 0xC;
    }
    else if (temp_a1 == 0x31)
    {
        var_a2 = 0xD;
    }
    else
    {
        var_a2 = 0xB;
    }

    if (temp_a1 == 0x31)
    {
        var_a0   = 3;
        var_v1_2 = 0x1F;
    }
    else if (airScreamer->field_D4.radius_0 + 0xCC >= temp_t3)
    {
        var_a0   = 2;
        var_v1_2 = 0x1E;
    }
    else
    {
        if (cond)
        {
            var_v1 = 0x155;
        }
        else
        {
            var_v1 = 0x2AA;
        }

        if (temp_s2 + var_v1 < var_v1 * 2)
        {
            if (cond)
            {
                var_a0   = 3;
                var_v1_2 = 0x1F;
            }
            else
            {
                var_a0   = 0;
                var_v1_2 = 0x1C;
            }
        }
        else
        {
            var_a0   = 2;
            var_v1_2 = 0x1E;
        }
    }

    var_t1 = sharedData_800CAA98_0_s01.unk_380[var_v1_2][0];
    var_t2 = sharedData_800CAA98_0_s01.unk_380[var_v1_2][1];

    if (temp_s2 < 6)
    {
        if (temp_s2 < -5)
        {
            var_t2 = -var_t2;
            var_t1 = -var_t1;
        }
        else
        {
            var_t2 = 0;
            var_t1 = 0;
        }
    }

    temp  = sharedData_800CAA98_0_s01.unk_380[var_a0][0];
    temp2 = sharedData_800CAA98_0_s01.unk_380[var_a0][1];

    sharedData_800E21D0_0_s01.field_B4[0][1] = temp2;
    sharedData_800E21D0_0_s01.field_B4[0][2] = temp;

    if (temp_a1 != 0x31)
    {
        sharedData_800E21D0_0_s01.field_B4[0][3] = temp_t3;
        sharedData_800E21D0_0_s01.field_B4[0][0] = 1;
    }

    ptr = &sharedData_800CAA98_0_s01;

    temp3 = ptr->unk_380[var_a2][0];
    temp4 = ptr->unk_380[var_a2][1];

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_t1;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t2;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = temp_s2;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    idx                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = temp4;

    sharedFunc_800D5E78_0_s01(airScreamer, temp_s2 / 2);
}