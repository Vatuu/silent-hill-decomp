void sharedFunc_800E021C_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2)
{
    VECTOR3*         pos;
    s32              temp_a1;
    s32              angleToUnk;
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

    pos = &airScreamer->properties_E4.airScreamer.position_110;

    angleToUnk = func_80080478(&airScreamer->position_18, pos);
    temp    = Math_Distance2dGet(&airScreamer->position_18, pos);
    temp_t2 = sharedFunc_800D569C_0_s01(airScreamer, pos->vy, temp);
    angleToUnk = FP_ANGLE_NORM_S(angleToUnk - airScreamer->rotation_24.vy);

    temp_t2 -= airScreamer->position_18.vy;
    temp_a1  = airScreamer->model_0.anim_4.status_0 | 0x1; // TODO: Macro.

    var_t3 = 0;

    if (angleToUnk >= FP_ANGLE(-45.0f) && angleToUnk <= FP_ANGLE(45.0f))
    {
        var_v1 = 0;
    }
    else
    {
        if (angleToUnk >= FP_ANGLE(-135.0f) && angleToUnk <= FP_ANGLE(135.0f))
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
        case 33:
            var_a0 = 10;
            var_a2 = 25;
            break;

        case 49:
            var_a2 = 24;
            break;

        default:
            var_t3 = 1;

            if (temp_t2 >= 205)
            {
                var_a2 = 21;
            }
            else
            {
                if (temp_t2 < -204)
                {
                    var_a2 = 23;
                }
                else
                {
                    var_a2 = 22;
                }
            }
            break;
    }

    var_a3 = sharedData_800CAA98_0_s01.unk_380[temp_v1][0];
    var_t0 = sharedData_800CAA98_0_s01.unk_380[temp_v1][1];

    if (angleToUnk <= FP_ANGLE(0.5f))
    {
        if (angleToUnk < FP_ANGLE(-0.5f))
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

    do {} while (false); // @hack

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_a3;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t0;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = angleToUnk;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    sharedFunc_800D5E78_0_s01(airScreamer, angleToUnk / 2);
}
