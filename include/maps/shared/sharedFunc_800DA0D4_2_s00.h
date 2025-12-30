void sharedFunc_800DA0D4_2_s00(s_SubCharacter* airScreamer)
{
    s32  animStatus;
    s32  switchCond;
    s32  temp_fp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    bool cond;
    s32  temp_a0;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    cond = false;

    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_RandQ12() < Q12(0.1f))
            {
                airScreamer->model_0.stateStep_3 = 8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = 2;
            }

        case 1:
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamer->properties_E4.unk0.pos_104, Q12(3.0f));
            airScreamer->model_0.stateStep_3 = 2;
            break;

        case 2:
            cond = true;

        case 3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = 4;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = 8;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = 0;
            }
            else if (airScreamer->properties_E4.unk0.properties_120.val32 == 0)
            {
                airScreamer->model_0.stateStep_3 = 1;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = 3;

                if (field15C > 32)
                {
                    q19_12 angleDiff = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.unk0.pos_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DEC84_2_s00(airScreamer, Q12(3.0f), (angleDiff / 4) + airScreamer->rotation_24.vy);
                    airScreamer->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(16, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = 6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = 7;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = 5;
            }
            break;

        case 5:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                airScreamer->model_0.stateStep_3     = 7;
            }
            break;

        case 6:
            switchCond = 3;

            if (field14C_2 || field14C_1 || field14C_0)
            {
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

        case 8:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(15, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = 10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = 11;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = 9;
            }
            break;

        case 9:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 5;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                airScreamer->model_0.stateStep_3     = 11;
            }
            break;

        case 10:
            switchCond = 5;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = 11;
            }
            else
            {
                switchCond = 4;
            }
            break;

        case 11:
            switchCond = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2     = 37;
                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 rand   = Rng_RandQ12();
                        s32 var_a0 = 0;

                        if (airScreamer->properties_E4.unk0.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (rand < (Q12(0.7f) - (var_a0 * 2)))
                        {
                            airScreamer->model_0.controlState_2     = 35;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = 8;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = 6;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 3:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = 8;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = 7;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 4:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = 22;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = 20;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;

                case 5:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2     = 22;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2     = 21;
                            airScreamer->model_0.stateStep_3 = 0;
                        }
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 44;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 45;
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
