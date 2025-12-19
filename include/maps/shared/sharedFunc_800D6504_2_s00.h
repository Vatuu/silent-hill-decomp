// Very similar to `sharedFunc_800DB9B8_2_s00`, changes here should be copied there.

void sharedFunc_800D6504_2_s00(s_SubCharacter* chara)
{
    s32    animStatus;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   cond;
    s32    var_a0;
    q19_12 var_s1;

    animStatus       = chara->model_0.anim_4.status_0;
    field14C_2_tmp   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    chara->flags_3E |= CharaFlag_Unk3;
    field14C_2       = field14C_2_tmp;
    cond             = false;

    switch ((u32)chara->model_0.stateStep_3)
    {
        case 0:
            if (field14C_2)
            {
                sharedFunc_800DE11C_2_s00(chara);
            }
            else
            {
                sharedFunc_800DDF74_2_s00(chara, Q12(4.0f), func_80080478(&chara->position_18, &g_SysWork.playerWork_4C.player_0.position_18));
                chara->properties_E4.unk0.pos_104 = chara->properties_E4.unk0.field_F8;
            }

            chara->model_0.stateStep_3 = 1;

        case 1:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                chara->model_0.stateStep_3     = 2;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(6, false))
            {
                chara->model_0.stateStep_3           = 3;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 3:
            if (animStatus != ANIM_STATUS(6, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF80C_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (!cond)
            {
                break;
            }

            var_s1 = chara->properties_E4.unk0.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

            if (chara->properties_E4.unk0.field_E8_0 == 3)
            {
                sharedFunc_800DD13C_2_s00(chara, chara->field_40 + 1, Q12(0.7f));
            }

            if (field14C_2)
            {
                if (chara->properties_E4.unk0.field_E8_8 == 5)
                {
                    chara->model_0.state_2     = 14;
                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < ((FP_TO(chara->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 3;
                    }
                }
                else
                {
                    chara->model_0.state_2     = 10;
                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() <= ((FP_TO(chara->health_B0, Q12_SHIFT) / Q12(380.0f)) + (var_s1 * 2)))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 3;
                    }
                    else
                    {
                        chara->properties_E4.unk0.field_E8_8 = 5;
                    }
                }
                break;
            }

            switch (chara->properties_E4.unk0.field_E8_8)
            {
                case 3:
                    chara->model_0.state_2     = 13;
                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < ((Q12(0.5f) - (var_s1 * 3))))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 2;
                    }
                    break;

                case 2:
                    chara->model_0.state_2     = 7;
                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() > (FP_TO(chara->health_B0, Q12_SHIFT) / Q12(380.0f) + (var_s1 * 2)))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 5;
                    }
                    else if (Rng_RandQ12() < Q12(0.3f) + (var_s1 * 3))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 3;
                    }
                    break;

                case 5:
                    chara->model_0.state_2     = 14;
                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < FP_TO(chara->health_B0, Q12_SHIFT) / Q12(380.0f))
                    {
                        chara->properties_E4.unk0.field_E8_8 = 3;
                    }
                    break;

                case 1:
                case 4:
                    if (Rng_RandQ12() < (Q12(0.2f) + (var_s1 * 5)))
                    {
                        chara->model_0.state_2 = 7;
                    }
                    else
                    {
                        chara->model_0.state_2 = 14;
                    }

                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < (Q12(0.5f) + (var_s1 * 3)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    chara->properties_E4.unk0.field_E8_8 = var_a0;
                    break;

                case 0:
                default:
                    if (chara->properties_E4.unk0.field_E8_0 == 3)
                    {
                        var_s1 = Q12(1.0f);
                    }

                    if (Rng_RandQ12() < (Q12(0.4f) + (var_s1 * 3)))
                    {
                        chara->model_0.state_2 = 7;
                    }
                    else
                    {
                        chara->model_0.state_2 = 14;
                    }

                    chara->model_0.stateStep_3 = 0;

                    if (Rng_RandQ12() < (Q12(0.6f) + (var_s1 * 2)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    chara->properties_E4.unk0.field_E8_8 = var_a0;
                    break;
            }
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 17;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}
