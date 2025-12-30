// Note: Very close match to `sharedFunc_800D46C8_2_s00` other than some checks being removed.
// Changes here should be copied over there.
void sharedFunc_800D4A9C_2_s00(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    s32  switchCond;
    bool var_s5;
    s32  temp_fp;
    s32  temp_fp_tmp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    var_s5         = false;
    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    temp_fp        = temp_fp_tmp;
    field14C_2     = field14C_2_tmp;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(6.0f);

        case 1:
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamer->properties_E4.unk0.pos_104, Q12(2.0f));

            if (!sharedFunc_800DC30C_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            else if (Rng_RandQ12() >= Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = 4;
            }
            break;

        case 2:
            var_s5 = true;

        case 3:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = 4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = 1;
            }
            else if (airScreamer->properties_E4.unk0.properties_120.val32 == 0)
            {
                if (var_s5)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = 0;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = 3;

                if (field15C > 32)
                {
                    s32 var_v0 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.unk0.pos_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DDF74_2_s00(airScreamer, Q12(1.5f), (var_v0 / 4) + airScreamer->rotation_24.vy);
                    airScreamer->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);

                if (field14C_1 || field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = 7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = 6;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            if (field14C_2 || field14C_1 || field14C_0)
            {
                switchCond                 = 3;
                airScreamer->model_0.stateStep_3 = 7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case 7:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2     = 8;
                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 randVal = Rng_RandQ12();

                        s32 var_a0  = Q12(0.0f);
                        if (airScreamer->properties_E4.unk0.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (randVal < Q12(0.7f) - (var_a0 * 2))
                        {
                            airScreamer->model_0.controlState_2     = 6;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 2)
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = 20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = 22;
                        }

                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;

                case 3:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = 22;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = 21;
                        }

                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 16;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
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
