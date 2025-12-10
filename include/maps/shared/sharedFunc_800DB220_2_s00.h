void sharedFunc_800DB220_2_s00(s_SubCharacter* chara)
{
    s32    animStatus;
    s32    switchCond;
    s32    temp_s6;
    s32    temp_s6_tmp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    s32    temp_s4;
    q19_12 distFieldF8;
    q19_12 angFieldF8;
    u32    maxHack = FP_ANGLE(90.0f) * 2; // @hack Needed to get matching `sltu`

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack Weird variable juggling needed for match, is there another way to do this?
    temp_s6_tmp    = sharedFunc_800D4A80_0_s01(chara);
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s6        = temp_s6_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s4        = sharedFunc_800DC438_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DF22C_2_s00(chara);

        case 1:
            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            chara->model_0.stateStep_3                     = 2;
            break;

        case 2:
            distFieldF8 = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);

            if (temp_s4 == 2)
            {
                chara->model_0.stateStep_3 = 3;
            }
            else if (temp_s4 == 1)
            {
                chara->model_0.stateStep_3 = 5;
            }
            else if (distFieldF8 < Q12(0.5f))
            {
                if (sharedFunc_800DC30C_2_s00(chara) && Rng_RandQ12() < Q12(0.3f))
                {
                    chara->model_0.stateStep_3 = 5;
                }
                else
                {
                    switchCond = 1;
                }
            }
            else if (distFieldF8 < Q12(4.0f) && (angFieldF8 + FP_ANGLE(90.0f) > maxHack)) // @hack Should be `angFieldF8 >= FP_ANGLE(-90.0f) && angFieldF8 < FP_ANGLE(90.0f)`
            {
                switchCond = 2;
            }

            if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                sharedFunc_800DECA4_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.5f));
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 3;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 4;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            switchCond = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(chara, 1, 0);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                case 2:
                    if (sharedFunc_800DC67C_2_s00(chara))
                    {
                        chara->model_0.state_2 = 42;
                    }
                    else if (field14C_2)
                    {
                        chara->model_0.state_2 = 38;
                    }
                    else if (switchCond == 2)
                    {
                        chara->model_0.state_2 = 39;
                    }
                    else if (switchCond == 1)
                    {
                        chara->model_0.state_2 = 36;
                    }
                    else
                    {
                        break;
                    }

                    chara->model_0.stateStep_3 = 0;
                    break;

                case 3:
                    if (temp_s6 == 1)
                    {
                        if (!field14C_2)
                        {
                            chara->model_0.state_2 = 13;
                        }
                        else
                        {
                            chara->model_0.state_2 = 10;
                        }
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 4:
                    if (temp_s6 == 2)
                    {
                        if (field14C_2)
                        {
                            chara->model_0.state_2 = 23;
                        }
                        else
                        {
                            chara->model_0.state_2 = 26;
                        }
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2               = 44;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 45;
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
