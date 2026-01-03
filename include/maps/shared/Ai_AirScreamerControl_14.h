void Ai_AirScreamerControl_14(s_SubCharacter* airScreamer) // 0x800D603C
{
    s32    animStatus;
    s32    switchCond;
    s32    temp_s7;
    s32    temp_s7_tmp;
    q19_12 dist;
    q19_12 angle;
    bool   field14C_2;
    bool   field14C_2_tmp;
    q19_12 val2_0 = Q12(2.0f); // @hack Used to fix register order, couldn't find how to remove this yet.
    q19_12 distFieldF8;
    s32    var_s6;             // Possibly `bool`.
    q19_12 angleDelta;
    s32    temp_v0;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_s7_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist           = sharedData_800E21D0_0_s01.distance_150;
    angle          = sharedData_800E21D0_0_s01.angle_154;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s7        = temp_s7_tmp;
    field14C_2     = field14C_2_tmp;
    distFieldF8    = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    var_s6         = 0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            var_s6      = sharedFunc_800DE578_2_s00(airScreamer);
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDelta  = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);

            if (sharedFunc_800DC200_2_s00(airScreamer) &&
                (Math_CheckSignedRange(angleDelta, FP_ANGLE(120.0f)) ||
                 (dist < Q12(5.0f) && Math_CheckSignedRange(angleDelta, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC30C_2_s00(airScreamer) || (dist >= val2_0 && Rng_RandQ12() >= Q12(0.4f)))
            {
                airScreamerProps.timer_120 = Q12(2.0f);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                temp_v0                    = 1;
                airScreamer->model_0.stateStep_3 = temp_v0 * 2; // @hack Copy of `temp_v0 == 1` hack below for them to be folded together.
            }
            break;

        case 1:
            temp_v0 = sharedFunc_800DC598_2_s00(airScreamer);
            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = temp_v0 * 2; // @hack This should just be `= 2`, but that causes extra `li v0, 2` to be emitted here?
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (distFieldF8 < Q12(2.0f) || (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                var_s6 = sharedFunc_800DE578_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, true);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);

                    if (var_s6 || (((field14C_2 != 0 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && distFieldF8 < Q12(1.5f)))
                    {
                        airScreamer->model_0.controlState_2               = 10;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8 = 3;
                        airScreamerProps.flags_11C |= AirScreamerFlag_4;
                    }
                    else if (dist > Q12(30.0f) && distFieldF8 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2     = 7;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2     = 27;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 3)
                    {
                        airScreamer->model_0.controlState_2     = 42;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 16;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 17;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }

    #undef airScreamerProps
}
