void sharedFunc_800DACA8_2_s00(s_SubCharacter* airScreamer)
{
    s32  sp10;
    s32  temp_a0;
    s32  temp_s0_2;
    s32  temp_s3;
    s32  temp_s5;
    s32  temp_s7;
    s32  temp_v0;
    s32  var_s4;
    s32  temp_s6;
    bool new_var;
    s32  temp_s8;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    temp_s6 = airScreamer->model_0.anim_4.status_0;
    var_s4  = 0;
    temp_v0 = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10    = new_var;

    temp_s5   = sharedData_800E21D0_0_s01.distance_150;
    temp_s7   = sharedData_800E21D0_0_s01.angle_154;
    temp_s8   = temp_v0;
    temp_s3   = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8);
    temp_s0_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_F8) - airScreamer->rotation_24.vy);
    temp_a0   = sharedFunc_800DC438_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DF24C_2_s00(airScreamer);
            Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_F8);

            if (temp_s5 > Q12(6.0f))
            {
                temp_s3 = Q12(6.0f);
            }
            else if (temp_s5 > Q12(2.0f))
            {
                temp_s3 = Q12(12.0f) - temp_s5;
            }
            else
            {
                temp_s3 = Q12(10.0f);
            }

            temp_s3  += Rng_RandQ12() * 2;
            temp_s0_2 = FP_ANGLE_NORM_S((temp_s7 + 0x800) - airScreamer->rotation_24.vy) / 2 + airScreamer->rotation_24.vy;

            sharedFunc_800DEC84_2_s00(airScreamer, temp_s3, temp_s0_2 + (Rng_RandQ12() - 0x800) / 8);
            airScreamerProps.timer_120 = Q12(5.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_s3 < Q12(2.0f) || Math_CheckSignedRange(temp_s0_2, 0x400) ||
                     airScreamerProps.timer_120 == Q12(0.0f))
            {
                var_s4 = 1;
            }
            break;

        case 2:
            if (temp_s6 == 35)
            {
                var_s4                         = 2;
                airScreamer->model_0.anim_4.status_0 = 32;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            var_s4 = 2;
            break;

        case 4:
            if (temp_s6 == 35)
            {
                var_s4                         = 3;
                airScreamer->model_0.anim_4.status_0 = 30;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            var_s4 = 3;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 1:
                    if (sp10 != 0)
                    {
                        if (temp_s5 > Q12(7.0f))
                        {
                            airScreamer->model_0.controlState_2= AirScreamerControl_38;
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                            break;
                        }
                    }

                    if (var_s4 == 1)
                    {
                        if (airScreamer->properties_E4.unk0.field_E8_8 != 3)
                        {
                            airScreamer->properties_E4.unk0.field_E8_8 = 2;
                        }
                        airScreamer->model_0.controlState_2= AirScreamerControl_41;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s8 == 1)
                    {
                        airScreamer->model_0.controlState_2= AirScreamerControl_13;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s8 == 2)
                    {
                        airScreamer->model_0.controlState_2= AirScreamerControl_26;
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;
        case 1:
        case 2:
            airScreamer->model_0.controlState_2= AirScreamerControl_44;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            airScreamerProps.flags_11C |= 8;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2= AirScreamerControl_45;
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
