void sharedFunc_800D7D0C_2_s00(s_SubCharacter* airScreamer) // 0x800D7D0C
{
    s32     temp_fp;
    s32     temp_fp_tmp;
    bool    field14C_2;
    bool    field14C_2_tmp;
    bool    temp_s6;
    q19_12 dist0;
    q19_12 dist1;
    q19_12 posDiffAngle;
    q19_12 distTest;
    s32    switchCond;
    s32    animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist0      = sharedData_800E21D0_0_s01.distance_150;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp        = temp_fp_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s6        = sharedFunc_800DC50C_2_s00(airScreamer);

    sharedFunc_800D53AC_0_s01(airScreamer);
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            #define angleDiff FP_ANGLE_NORM_S(g_SysWork.playerWork_4C.player_0.rotation_24.vy - airScreamer->rotation_24.vy)
            
            distTest = dist0 + (Rng_RandQ12() * 4);
            if (sharedFunc_800DC200_2_s00(airScreamer) && distTest > Q12(8.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC3BC_2_s00(airScreamer) || distTest >= Q12(4.0f) ||
                     (angleDiff < FP_ANGLE(-30.0f) || angleDiff >= FP_ANGLE(30.0f)) ||
                     Rng_RandQ12() >= Q12(0.2f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

            airScreamerProps.timer_120 = Q12(4.0f);
            break;

            #undef angleDiff

        case 1:
            distTest = NO_VALUE;
            if (airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy > Q12(-0.2f) &&
                airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy < Q12(0.8f))
            {
                distTest = airScreamer->field_D4.radius_0 + Q12(0.15f);
            }

            dist1    = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            posDiffAngle = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s6)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (dist1 < distTest && (posDiffAngle >= FP_ANGLE(-22.5f) && posDiffAngle < FP_ANGLE(22.5f)))
            {
                switchCond = 1;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 2;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (field14C_2 == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.playerWork_4C.player_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == ANIM_STATUS(19, true))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_25;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        sharedFunc_800DE11C_2_s00(airScreamer);
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (temp_fp == switchCond)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
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
