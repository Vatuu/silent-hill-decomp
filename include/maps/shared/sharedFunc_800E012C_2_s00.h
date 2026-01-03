void sharedFunc_800E012C_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 angleDeltaToPlayer;
    s32    var_t0;
    s32    var_t1;
    s32    temp_a0;
    s32    idx;
    s32*   ptr;

    angleDeltaToPlayer = func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.airScreamer.targetPosition_F8);
    angleDeltaToPlayer = FP_ANGLE_NORM_S(angleDeltaToPlayer - airScreamer->rotation_24.vy);

    idx     = 33;
    temp_a0 = sharedData_800CAA98_0_s01.unk_380[idx][0];
    var_t1  = sharedData_800CAA98_0_s01.unk_380[idx][1];
    var_t0  = temp_a0 / 2;

    if (angleDeltaToPlayer <= FP_ANGLE(0.5f))
    {
        if (angleDeltaToPlayer < FP_ANGLE(-0.5f))
        {
            var_t1 = -var_t1;
            var_t0 = -var_t0;
        }
        else
        {
            var_t1 = 0;
            var_t0 = 0;
        }
    }

    sharedData_800E21D0_0_s01.field_B4[0][2] = sharedData_800CAA98_0_s01.unk_380[5][0] / 2;
    sharedData_800E21D0_0_s01.field_B4[0][1] = sharedData_800CAA98_0_s01.unk_380[5][1];

    idx                                        = 3;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_t0;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = var_t1;
    sharedData_800E21D0_0_s01.field_B4[idx][3] = angleDeltaToPlayer;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;

    ptr = sharedData_800CAA98_0_s01.unk_380[19];

    idx                                        = 1;
    sharedData_800E21D0_0_s01.field_B4[idx][2] = ptr[0];
    sharedData_800E21D0_0_s01.field_B4[idx][1] = ptr[1];

    sharedFunc_800D5E78_0_s01(airScreamer, angleDeltaToPlayer / 2);
}
