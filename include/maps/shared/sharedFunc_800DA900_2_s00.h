void sharedFunc_800DA900_2_s00(s_SubCharacter* airScreamer)
{
    s32           sp10;
    s32           temp_s0;
    s32           temp_s0_2;
    s32           temp_s0_4;
    s32           temp_s3;
    s32           temp_s5;
    s32           temp_v0;
    s32           temp_v1_2;
    s32           var_s4;
    s32           temp_s7;
    s32           var_v0_2;
    bool          new_var;
    s32           temp_s6;
    s_PlayerWork* playerWork;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    temp_s7 = airScreamer->model_0.anim_4.status_0;
    var_s4  = 0;

    temp_v0 = sharedFunc_800D4A80_0_s01(airScreamer);

    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s0 = sharedData_800E21D0_0_s01.distance_150;
    sp10    = new_var;

    temp_s3 = sharedFunc_800DC438_2_s00(airScreamer);
    temp_s6 = sharedFunc_800DEE24_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            temp_s0_2 = temp_s0 + (Rng_RandQ12() * 4);

            if (!sharedFunc_800DC30C_2_s00(airScreamer) || temp_s0_2 >= Q12(3.0f) || Rng_RandQ12() >= 0x333)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            airScreamer->properties_E4.dummy.properties_E8[14].val32 = Q12(4.0f);
            break;

        case 1:
            temp_s5   = airScreamer->properties_E4.dummy.properties_E8[5].val32 - airScreamer->position_18.vy;
            temp_s0_4 = Math_Distance2dGet(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[4]);
            temp_v1_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[4]) - airScreamer->rotation_24.vy);

            if (temp_s3 == 2)
            {
                airScreamer->model_0.stateStep_3 = temp_s3;
            }
            else if (temp_s3 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if ((temp_s5 >= -0x333 && temp_s5 <= 0x333) &&
                     (temp_s6 > 0x599 && temp_s6 < 0x8CD) &&
                     (temp_v1_2 >= -0x80 && temp_v1_2 <= 0x80))
            {
                var_s4 = 1;
            }
            else
            {
                // @hack This check should be `if ((temp_v1_2 >= -0x400 && temp_v1_2 < 0x400) && temp_s0_4 < Q12(4.0f))`,
                if (Math_CheckSignedRange(temp_v1_2, 0x400) && (temp_s0_4 < Q12(4.0f)))
                {
                    var_s4 = 2;
                }
                else if (airScreamer->properties_E4.dummy.properties_E8[14].val32 == 0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
            }
            break;

        case 2:
            if (temp_s7 == 35)
            {
                var_s4                        = 3;
                airScreamer->model_0.anim_4.status_0 = 32;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            var_s4 = 3;
            break;

        case 4:
            if (temp_s7 == 35)
            {
                var_s4                        = 4;
                airScreamer->model_0.anim_4.status_0 = 30;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            var_s4 = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 2:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        var_v0_2 = 41;
                        if (sp10 != 0)
                        {
                            if (var_s4 == 2)
                            {
                                airScreamer->model_0.controlState_2= AirScreamerControl_39;
                                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                            }
                            break;
                        }
                    }
                    else
                    {
                        var_v0_2 = 42;
                    }

                    airScreamer->model_0.controlState_2 = var_v0_2;
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case 1:
                    playerWork = &g_SysWork.playerWork_4C;

                    if (!((u16)playerWork->player_0.flags_3E & 8) &&
                        (g_SysWork.npcIdxs_2354[0] == NO_VALUE && g_SysWork.npcIdxs_2354[1] == NO_VALUE) &&
                        temp_s7 == 0x23)
                    {
                        airScreamer->model_0.controlState_2= AirScreamerControl_40;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_v0 == 1)
                    {
                        sharedFunc_800DE11C_2_s00(airScreamer);
                        airScreamer->model_0.controlState_2= AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 4:
                    if (temp_v0 == 2)
                    {
                        airScreamer->model_0.controlState_2= AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2= AirScreamerControl_44;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2= AirScreamerControl_45;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 1 << 6;
            }
            else
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            }
            break;
    }

    #undef airScreamerProps
}
