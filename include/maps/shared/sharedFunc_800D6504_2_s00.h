// Very similar to `sharedFunc_800DB9B8_2_s00`, changes here should be copied there.

void sharedFunc_800D6504_2_s00(s_SubCharacter* airScreamer)
{
    s32    animStatus;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   cond;
    s32    var_a0;
    q19_12 var_s1;

    animStatus       = airScreamer->model_0.anim_4.status_0;
    field14C_2_tmp   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    airScreamer->flags_3E |= CharaFlag_Unk3;
    field14C_2       = field14C_2_tmp;
    cond             = false;

    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case 0:
            if (field14C_2)
            {
                sharedFunc_800DE11C_2_s00(airScreamer);
            }
            else
            {
                sharedFunc_800DDF74_2_s00(airScreamer, Q12(4.0f), func_80080478(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18));
                airScreamer->properties_E4.unk0.pos_104 = airScreamer->properties_E4.unk0.field_F8;
            }

            airScreamer->model_0.stateStep_3 = 1;

        case 1:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                airScreamer->model_0.stateStep_3     = 2;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(6, false))
            {
                airScreamer->model_0.stateStep_3           = 3;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 3:
            if (animStatus != ANIM_STATUS(6, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF80C_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (!cond)
            {
                break;
            }

            var_s1 = airScreamer->properties_E4.unk0.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

            if (airScreamer->properties_E4.unk0.field_E8_0 == 3)
            {
                sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
            }

            if (field14C_2)
            {
                if (airScreamer->properties_E4.unk0.field_E8_8 == 5)
                {
                    airScreamer->model_0.controlState_2     = 14;
                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 3;
                    }
                }
                else
                {
                    airScreamer->model_0.controlState_2     = 10;
                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() <= ((FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 3;
                    }
                    else
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 5;
                    }
                }
                break;
            }

            switch (airScreamer->properties_E4.unk0.field_E8_8)
            {
                case 3:
                    airScreamer->model_0.controlState_2     = 13;
                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < ((Q12(0.5f) - (var_s1 * 3))))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 2;
                    }
                    break;

                case 2:
                    airScreamer->model_0.controlState_2     = 7;
                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() > (FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f) + (var_s1 * 2)))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 5;
                    }
                    else if (Rng_RandQ12() < Q12(0.3f) + (var_s1 * 3))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 3;
                    }
                    break;

                case 5:
                    airScreamer->model_0.controlState_2     = 14;
                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < FP_TO(airScreamer->health_B0, Q12_SHIFT) / Q12(380.0f))
                    {
                        airScreamer->properties_E4.unk0.field_E8_8 = 3;
                    }
                    break;

                case 1:
                case 4:
                    if (Rng_RandQ12() < (Q12(0.2f) + (var_s1 * 5)))
                    {
                        airScreamer->model_0.controlState_2 = 7;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = 14;
                    }

                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < (Q12(0.5f) + (var_s1 * 3)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamer->properties_E4.unk0.field_E8_8 = var_a0;
                    break;

                case 0:
                default:
                    if (airScreamer->properties_E4.unk0.field_E8_0 == 3)
                    {
                        var_s1 = Q12(1.0f);
                    }

                    if (Rng_RandQ12() < (Q12(0.4f) + (var_s1 * 3)))
                    {
                        airScreamer->model_0.controlState_2 = 7;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = 14;
                    }

                    airScreamer->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < (Q12(0.6f) + (var_s1 * 2)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamer->properties_E4.unk0.field_E8_8 = var_a0;
                    break;
            }
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 17;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}
