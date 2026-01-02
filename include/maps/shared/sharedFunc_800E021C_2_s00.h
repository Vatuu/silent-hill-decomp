void sharedFunc_800E021C_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2)
{
    VECTOR3*         temp_s0;
    s32              temp_a1;
    s32              temp_s2;
    s32              temp_t2;
    s32              temp_v1;
    s32              var_a2;
    s32              var_a3;
    s32              var_t0;
    s32              var_t3;
    s32              var_v1;
    s32              var_a0;
    s32              idx;
    s32              temp;
    s32              temp2;
    s32              temp3;
    s32              temp4;
    s_func_800D2E04* ptr;

    temp_s0 = &airScreamer->properties_E4.airScreamer.position_110;

    temp_s2 = func_80080478(&airScreamer->position_18, temp_s0);
    temp    = Math_Distance2dGet(&airScreamer->position_18, temp_s0);
    temp_t2 = sharedFunc_800D569C_0_s01(airScreamer, temp_s0->vy, temp);
    temp_s2 = FP_ANGLE_NORM_S(temp_s2 - airScreamer->rotation_24.vy);

    temp_t2 -= airScreamer->position_18.vy;
    temp_a1  = airScreamer->model_0.anim_4.status_0 | 1;

    var_t3 = 0;

    if (temp_s2 >= -0x200 && temp_s2 <= 0x200)
    {
        var_v1 = 0;
    }
    else
    {
        if (temp_s2 >= -0x600 && temp_s2 <= 0x600)
        {
            var_v1 = 1;
        }
        else
        {
            var_v1 = 2;
        }
    }

    arg1 &= 3;
    arg2 &= 3;

    var_a0  = sharedData_800EEAC4_2_s00[var_v1][arg1][arg2];
    temp_v1 = var_a0 + 0x1C;

    switch (temp_a1)
    {
        case 0x21:
            var_a0 = 0xA;
            var_a2 = 0x19;
            break;

        case 0x31:
            var_a2 = 0x18;
            break;

        default:
            var_t3 = 1;

            if (temp_t2 >= 0xCD)
            {
                var_a2 = 0x15;
            }
            else
            {
                if (temp_t2 < -0xCC)
                {
                    var_a2 = 0x17;
                }
                else
                {
                    var_a2 = 0x16;
                }
            }
            break;
    }

    var_a3 = sharedData_800CAA98_0_s01.unk_380[temp_v1][0];
    var_t0 = sharedData_800CAA98_0_s01.unk_380[temp_v1][1];

    if (temp_s2 < 6)
    {
        if (temp_s2 < -5)
        {
            var_t0 = -var_t0;
            var_a3 = -var_a3;
        }
        else
        {
            var_t0 = 0;
            var_a3 = 0;
        }
    }

    temp  = sharedData_800CAA98_0_s01.unk_380[var_a0][0];
    temp2 = sharedData_800CAA98_0_s01.unk_380[var_a0][1];

    sharedData_800E21D0_0_s01.field_B4[0][2] = temp;
    sharedData_800E21D0_0_s01.field_B4[0][1] = temp2;

    ptr   = &sharedData_800CAA98_0_s01;
    temp3 = ptr->unk_380[var_a2][0];
    temp4 = ptr->unk_380[var_a2][1];

    idx                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = temp3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = temp4;

    if (var_t3 != 0)
    {
        sharedData_800E21D0_0_s01.field_B4[idx][3] = temp_t2;
        sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;
    }

    do
    {
    } while (0); // @hack

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_a3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t0;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = temp_s2;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    sharedFunc_800D5E78_0_s01(airScreamer, temp_s2 / 2);
}