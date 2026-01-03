void Ai_AirScreamerControl_10(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    s32    sp14;
    s32    sp18;
    s32    temp_s3_2;
    s32    temp_s7;
    s32    temp_fp;
    q19_12 unkDist;
    s32    temp_s1_2;
    s32    temp_s1_3;
    s32    temp_s4_2;
    s32    temp_s5;
    s32    temp_s6;
    s32    switchCond;
    bool   new_var;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    sp14       = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp18       = new_var;
    unkDist    = sharedData_800E21D0_0_s01.distance_150;

    sharedFunc_800DE11C_2_s00(airScreamer);
    switchCond = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            temp_s5 = unkDist + (Rng_RandQ12() * 4);

            if (sharedFunc_800DC200_2_s00(airScreamer) && temp_s5 > Q12(8.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC30C_2_s00(airScreamer) || temp_s5 <= Q12(4.0f) && Rng_RandQ12() >= Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

            airScreamerProps.timer_120 = Q12(4.0f);
            break;

        case AirScreamerStateStep_1:

            temp_s1_2 = sharedFunc_800DC598_2_s00(airScreamer);
            temp_s5   = Q12(0.6f);
            temp_fp   = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);

            if (temp_s1_2 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_s1_2 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_fp < Q12(1.1f))
            {
                temp_s6   = airScreamer->position_18.vy + airScreamer->field_C8.field_0 + Q12(0.1f);
                temp_s1_3 = g_SysWork.playerWork_4C.player_0.position_18.vy;
                temp_s3_2 = g_SysWork.playerWork_4C.player_0.field_C8.field_4;
                temp_s7   = g_SysWork.playerWork_4C.player_0.field_C8.field_0;

                temp_s4_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

                if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    if ((temp_s1_3 + temp_s3_2) < temp_s6 || temp_s6 < (temp_s1_3 + temp_s7))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                        break;
                    }
                }

                if (temp_fp < temp_s5)
                {
                    if (temp_s4_2 > -0x101 && temp_s4_2 < 0x100)
                    {
                        switchCond = 1;
                    }
                }
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 2;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, 1);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (sp18 == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.playerWork_4C.player_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                            animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_12;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (sp14 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (sp14 == 3)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2        = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3           = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

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