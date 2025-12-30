void sharedFunc_800D8D44_2_s00(s_SubCharacter* arg0)
{
    s32  temp_s2;
    s32  var_a0;
    s32  var_s1;
    s32  var_s1_2;
    u32  temp_a0;
    u32  temp_v1;
    bool new_var;

    temp_a0         = arg0->model_0.anim_4.status_0;
    new_var         = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    var_s1          = 0;
    temp_s2         = new_var;
    temp_v1         = arg0->model_0.stateStep_3;
    arg0->flags_3E |= 4;

    switch (temp_v1)
    {
        case 0:
            if (temp_a0 & 1)
            {
                arg0->model_0.anim_4.status_0 = 0xE;
                arg0->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (temp_a0 != 0xE)
            {
                arg0->model_0.stateStep_3                           = 2;
                arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            }
            break;

        case 2:
            if (temp_a0 != 0xF)
            {
                var_s1 = 1;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(arg0);

    switch (Ai_AirScreamer_DamageTake(arg0, 0x999))
    {
        case 0:
        case 1:
            if (var_s1 != 0)
            {
                var_s1_2 = 0;

                if (arg0->properties_E4.airScreamer.field_E8_4)
                {
                    var_s1_2 = 0x199;
                }

                if (arg0->properties_E4.airScreamer.field_E8_0 == 3)
                {
                    sharedFunc_800DD13C_2_s00(arg0, arg0->field_40 + 1, 0xB33);
                }

                if (temp_s2 != 0)
                {
                    if (arg0->properties_E4.airScreamer.field_E8_8 == 5)
                    {
                        arg0->model_0.controlState_2 = 0x1B;
                        arg0->model_0.stateStep_3    = 0;

                        if (Rng_RandQ12() < FP_TO(arg0->health_B0, Q12_SHIFT) / 0x17C000 + var_s1_2 * 2)
                        {
                            arg0->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;
                    }

                    arg0->model_0.controlState_2 = 0x17;
                    arg0->model_0.stateStep_3    = 0;

                    if (Rng_RandQ12() > FP_TO(arg0->health_B0, Q12_SHIFT) / 0x17C000 + var_s1_2 * 2)
                    {
                        arg0->properties_E4.airScreamer.field_E8_8 = 5;
                    }
                    else
                    {
                        arg0->properties_E4.airScreamer.field_E8_8 = 3;
                    }
                    break;
                }

                switch (arg0->properties_E4.airScreamer.field_E8_8)
                {
                    case 3:
                        arg0->model_0.controlState_2 = 0x1A;
                        arg0->model_0.stateStep_3    = 0;

                        if (Rng_RandQ12() < 0x800 - var_s1_2 * 3)
                        {
                            arg0->properties_E4.airScreamer.field_E8_8 = 2;
                        }
                        break;

                    case 2:
                        arg0->model_0.controlState_2 = 0x15;
                        arg0->model_0.stateStep_3    = 0;

                        if (Rng_RandQ12() > FP_TO(arg0->health_B0, Q12_SHIFT) / 0x17C000 + var_s1_2 * 2)
                        {
                            arg0->properties_E4.airScreamer.field_E8_8 = 5;
                        }
                        else if (Rng_RandQ12() < var_s1_2 * 3 + 0x4CC)
                        {
                            arg0->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 5:
                        arg0->model_0.controlState_2 = 0x1B;
                        arg0->model_0.stateStep_3    = 0;

                        if (Rng_RandQ12() < FP_TO(arg0->health_B0, Q12_SHIFT) / 0x17C000)
                        {
                            arg0->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 1:
                    case 4:
                        if (Rng_RandQ12() >= var_s1_2 * 5 + 0x333)
                        {
                            arg0->model_0.controlState_2 = 0x1B;
                        }
                        else
                        {
                            arg0->model_0.controlState_2 = 0x15;
                        }

                        arg0->model_0.stateStep_3 = 0;

                        if (Rng_RandQ12() < var_s1_2 * 3 + 0x800)
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }
                        arg0->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;

                    default:
                    case 0:
                        if (arg0->properties_E4.airScreamer.field_E8_0 == 3)
                        {
                            var_s1_2 = 0x1000;
                        }

                        if (Rng_RandQ12() >= var_s1_2 * 3 + 0x666)
                        {
                            arg0->model_0.controlState_2 = 0x1B;
                        }
                        else
                        {
                            arg0->model_0.controlState_2 = 0x15;
                        }

                        arg0->model_0.stateStep_3 = 0;

                        if (Rng_RandQ12() < var_s1_2 * 2 + 0x999)
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }
                        arg0->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;
                }
            }
            break;

        case 2:
            arg0->model_0.controlState_2                        = 0x1E;
            arg0->model_0.stateStep_3                           = 0;
            arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            break;

        case 3:
        case 4:
            arg0->model_0.controlState_2 = 0x20;
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