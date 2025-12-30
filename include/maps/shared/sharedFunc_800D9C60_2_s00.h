void sharedFunc_800D9C60_2_s00(s_SubCharacter* arg0)
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

    temp_s2 = arg0->model_0.anim_4.status_0;

    var_s1 = 0;

    temp_s7 = sharedFunc_800D4A80_0_s01(arg0);

    temp_s6 = sharedData_800E21D0_0_s01.field_15C;

    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    new_var3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = new_var3;
    temp_s4 = new_var;
    temp_s3 = new_var2;

    temp_a0 = sharedFunc_800DC438_2_s00(arg0);
    var_a1  = 0;

    switch (arg0->model_0.stateStep_3)
    {
        case 0:
            arg0->properties_E4.dummy.properties_E8[0xE].val32 = 0x6000;

        case 1:
            sharedFunc_800DECA4_2_s00(arg0, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[7], 0x2000);

            if (sharedFunc_800DC30C_2_s00(arg0) && Rng_RandQ12() < 0x199)
            {
                arg0->model_0.stateStep_3 = 8;
            }
            else
            {
                arg0->model_0.stateStep_3 = 2;
            }
            break;

        case 2:
            var_a1 = 1;

        case 3:
            if (temp_a0 == 2)
            {
                arg0->model_0.stateStep_3 = 4;
            }
            else
            {
                if (temp_a0 == 1)
                {
                    arg0->model_0.stateStep_3 = 8;
                }
                else if (arg0->properties_E4.dummy.properties_E8[0xE].val32 == 0)
                {
                    if (var_a1 != 0)
                    {
                        var_s1 = 1;
                    }
                    arg0->model_0.stateStep_3 = 0;
                }
                else if (Math_Distance2dGet(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4]) < 0x1000)
                {
                    arg0->model_0.stateStep_3 = 1;
                }
                else if (temp_s5 || temp_s4 || temp_s3)
                {
                    arg0->model_0.stateStep_3 = 3;
                    if (temp_s6 >= 0x21)
                    {

                        var_v0 = FP_ANGLE_NORM_S(func_80080478(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[7]) - arg0->rotation_24.vy);
                        if (var_v0 < 0)
                        {
                            var_v0 += 3;
                        }
                        sharedFunc_800DEC84_2_s00(arg0, 0x2000, (var_v0 >> 2) + arg0->rotation_24.vy);
                        arg0->properties_E4.dummy.properties_E8[0xE].val32 = 0x6000;
                    }
                }
            }
            break;

        case 4:
            if (temp_s2 == 0x23)
            {
                var_s1                        = 2;
                arg0->model_0.anim_4.status_0 = 0x20;

                if (!temp_s3 && !temp_s4)
                {
                    arg0->model_0.stateStep_3 = 6;
                }
                else
                {
                    arg0->model_0.stateStep_3 = 7;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                arg0->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (temp_s2 == 0x23)
            {
                var_s1                        = 3;
                arg0->model_0.anim_4.status_0 = 0x20;
                arg0->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 3;
                arg0->model_0.stateStep_3 = 7;
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
            if (temp_s2 == 0x23)
            {
                var_s1                        = 4;
                arg0->model_0.anim_4.status_0 = 0x1E;

                if (!temp_s3 && !temp_s4)
                {
                    arg0->model_0.stateStep_3 = 0xA;
                }
                else
                {
                    arg0->model_0.stateStep_3 = 0xB;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                arg0->model_0.stateStep_3 = 9;
            }
            break;

        case 9:
            if (temp_s2 == 0x23)
            {
                var_s1                        = 5;
                arg0->model_0.anim_4.status_0 = 0x1E;
                arg0->model_0.stateStep_3     = 0xB;
            }
            break;

        case 10:
            if (temp_s3 || temp_s4)
            {
                var_s1                    = 5;
                arg0->model_0.stateStep_3 = 0xB;
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

    sharedFunc_800E021C_2_s00(arg0, 0, 2);

    switch (Ai_AirScreamer_DamageTake(arg0, 0x1000))
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

                            if (arg0->properties_E4.airScreamer.field_E8_8 == var_s1)
                            {
                                var_a0 = 0x199;
                            }
                            else
                            {
                                var_a0 = 0;
                            }

                            if (temp_a1 < 0xB33 - var_a0 * 2)
                            {
                                arg0->model_0.controlState_2 = 0x2B;
                                arg0->model_0.stateStep_3    = 0;
                            }
                        }
                    }
                    else
                    {
                        arg0->model_0.controlState_2 = 0x24;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 1)
                    {
                        arg0->model_0.controlState_2 = 6;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 3:
                    if (temp_s7 == 1)
                    {
                        arg0->model_0.controlState_2 = 7;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 4:
                    if (temp_s7 == 2)
                    {
                        arg0->model_0.controlState_2 = 0x14;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 5:
                    if (temp_s7 == 2)
                    {
                        arg0->model_0.controlState_2 = 0x15;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            arg0->model_0.controlState_2                        = 0x2C;
            arg0->model_0.stateStep_3                           = 0;
            arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            break;

        case 3:
        case 4:
            arg0->model_0.controlState_2 = 0x2D;
            arg0->model_0.stateStep_3    = 0;
            if (arg0->health_B0 <= 0)
            {
                arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 0x40;
            }
            else
            {
                arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            }
            break;
    }
}