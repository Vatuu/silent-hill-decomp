void sharedFunc_800D8888_2_s00(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    s32    switchCond;
    s32    temp_fp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    q19_12 dist;
    q19_12 angle;
    q19_12 distFieldF8;
    s32    var_s6; // Possibly `bool`
    bool   cond;
    q19_12 angleDiff;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(airScreamer);
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    dist           = sharedData_800E21D0_0_s01.distance_150;
    angle          = sharedData_800E21D0_0_s01.angle_154;
    field14C_2     = field14C_2_tmp;

    distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8);
    var_s6      = 0;
    cond        = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            var_s6      = sharedFunc_800DEC64_2_s00(airScreamer);
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8);
            angleDiff   = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);

            if (sharedFunc_800DC200_2_s00(airScreamer) && airScreamer->moveSpeed_38 > Q12(1.5f) &&
                (Math_CheckSignedRange(angleDiff, FP_ANGLE(120.0f)) || ((dist < Q12(5.0f)) && Math_CheckSignedRange(angleDiff, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                airScreamerProps.timer_120 = Q12(2.0f);

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (cond)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (distFieldF8 < Q12(2.0f) || (airScreamerProps.flags_11C & CharaUnk0Flag_Unk31))
            {
                var_s6 = sharedFunc_800DEC64_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                switchCond                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 1;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_18, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                    if (var_s6 || ((field14C_2 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && distFieldF8 < Q12(1.5f))
                    {
                        airScreamer->model_0.controlState_2               = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8 = 3;
                        airScreamerProps.flags_11C |= CharaUnk0Flag_Unk4;
                    }
                    else if (dist > Q12(30.0f) && distFieldF8 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) || animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, false);
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        airScreamer->model_0.controlState_2     = AirScreamerControl_42;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
            airScreamer->model_0.controlState_2               = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2               = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2     = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }

    #undef airScreamerProps
}
