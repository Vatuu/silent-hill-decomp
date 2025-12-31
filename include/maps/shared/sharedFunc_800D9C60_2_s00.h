void sharedFunc_800D9C60_2_s00(s_SubCharacter* airScreamer)
{
    s32  temp_a0;
    s32  temp_a1;
    s32  temp_s3;
    s32  temp_s4;
    s32  temp_s5;
    s32  temp_s6;
    s32  temp_s7;
    s32  var_a0;
    s32  var_a1;
    s32  var_v0;
    s32  var_s1;
    s32  temp_s2;
    bool new_var;
    bool new_var2;
    bool new_var3;

    temp_s2 = airScreamer->model_0.anim_4.status_0;

    var_s1 = 0;

    temp_s7 = sharedFunc_800D4A80_0_s01(airScreamer);

    temp_s6 = sharedData_800E21D0_0_s01.field_15C;

    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    new_var3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = new_var3;
    temp_s4 = new_var;
    temp_s3 = new_var2;

    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);
    var_a1  = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->properties_E4.dummy.properties_E8[14].val32 = Q12(6.0f);

        case 1:
            sharedFunc_800DECA4_2_s00(airScreamer, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[7], Q12(2.0f));

            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_RandQ12() < 0x199)
            {
                airScreamer->model_0.stateStep_3 = 8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            break;

        case 2:
            var_a1 = 1;

        case 3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = 4;
            }
            else
            {
                if (temp_a0 == 1)
                {
                    airScreamer->model_0.stateStep_3 = 8;
                }
                else if (airScreamer->properties_E4.dummy.properties_E8[14].val32 == 0)
                {
                    if (var_a1 != 0)
                    {
                        var_s1 = 1;
                    }
                    airScreamer->model_0.stateStep_3 = 0;
                }
                else if (Math_Distance2dGet(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[4]) < Q12(1.0f))
                {
                    airScreamer->model_0.stateStep_3 = 1;
                }
                else if (temp_s5 || temp_s4 || temp_s3)
                {
                    airScreamer->model_0.stateStep_3 = 3;
                    if (temp_s6 >= 33)
                    {

                        var_v0 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[7]) - airScreamer->rotation_24.vy);
                        if (var_v0 < 0)
                        {
                            var_v0 += 3;
                        }

                        sharedFunc_800DEC84_2_s00(airScreamer, Q12(2.0f), (var_v0 >> 2) + airScreamer->rotation_24.vy);
                        airScreamer->properties_E4.dummy.properties_E8[14].val32 = Q12(6.0f);
                    }
                }
            }
            break;

        case 4:
            if (temp_s2 == 35)
            {
                var_s1                        = 2;
                airScreamer->model_0.anim_4.status_0 = 32;

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = 6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = 7;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (temp_s2 == 35)
            {
                var_s1                        = 3;
                airScreamer->model_0.anim_4.status_0 = 32;
                airScreamer->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 3;
                airScreamer->model_0.stateStep_3 = 7;
            }
            else
            {
                var_s1 = 2;
            }
            break;

        case 7:
            var_s1 = 3;
            break;

        case 8:
            if (temp_s2 == 35)
            {
                var_s1                        = 4;
                airScreamer->model_0.anim_4.status_0 = 30;

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = 10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = 11;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = 9;
            }
            break;

        case 9:
            if (temp_s2 == 35)
            {
                var_s1                        = 5;
                airScreamer->model_0.anim_4.status_0 = 30;
                airScreamer->model_0.stateStep_3     = 11;
            }
            break;

        case 10:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 5;
                airScreamer->model_0.stateStep_3 = 11;
            }
            else
            {
                var_s1 = 4;
            }
            break;

        case 11:
            var_s1 = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 2);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s1)
            {
                case 0:
                case 1:
                    if (!temp_s3 && !temp_s4)
                    {
                        if (var_s1 == 1)
                        {
                            temp_a1 = Rng_RandQ12();

                            if (airScreamer->properties_E4.airScreamer.field_E8_8 == var_s1)
                            {
                                var_a0 = 0x199;
                            }
                            else
                            {
                                var_a0 = 0;
                            }

                            if (temp_a1 < (0xB33 - (var_a0 * 2)))
                            {
                                airScreamer->model_0.controlState_2 = 43;
                                airScreamer->model_0.stateStep_3    = 0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = 36;
                        airScreamer->model_0.stateStep_3    = 0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = 6;
                        airScreamer->model_0.stateStep_3    = 0;
                    }
                    break;

                case 3:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = 7;
                        airScreamer->model_0.stateStep_3    = 0;
                    }
                    break;

                case 4:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = 20;
                        airScreamer->model_0.stateStep_3    = 0;
                    }
                    break;

                case 5:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = 21;
                        airScreamer->model_0.stateStep_3    = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2                        = 44;
            airScreamer->model_0.stateStep_3                           = 0;
            airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = 45;
            airScreamer->model_0.stateStep_3    = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 1 << 6;
            }
            else
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            }
            break;
    }
}
