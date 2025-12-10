void sharedFunc_800DA598_2_s00(s_SubCharacter* chara)
{
    s32    temp_a0;
    q19_12 temp_s2;
    q19_12 dist;
    s32    temp_s4;
    bool   field14C;
    q19_12 angle;
    s32    switchCond;
    q19_12 temp_s1;
    s32    animStatus;
    s32    new_var;

    switchCond = 0;
    animStatus = chara->model_0.anim_4.status_0;
    new_var    = sharedFunc_800D4A80_0_s01(chara);
    dist       = sharedData_800E21D0_0_s01.distance_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s4    = new_var;
    temp_a0    = sharedFunc_800DC438_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            switchCond                                     = 1;
            chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
            chara->flags_3E                               |= CharaFlag_Unk3;

        case 1:
            sharedFunc_800DECA4_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(4.0f));
            chara->model_0.stateStep_3 = 2;
            break;

        case 2:
            if (temp_a0 == 2)
            {
                chara->model_0.stateStep_3 = 3;
            }
            else if (temp_a0 == 1)
            {
                chara->model_0.stateStep_3 = 5;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 2;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            switchCond = 3;
            break;
    }

    sharedFunc_800E021C_2_s00(chara, 2, 0);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!field14C)
                    {
                        chara->model_0.state_2     = 36;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (temp_s4 == 1)
                    {
                        chara->model_0.state_2     = 8;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 3:
                    if (temp_s4 == 2)
                    {
                        chara->model_0.state_2     = 22;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    temp_s1 = sharedFunc_800DC894_2_s00(chara, dist);
                    temp_s2 = sharedFunc_800DC6E4_2_s00(chara, dist);

                    if (FP_ANGLE_NORM_S(angle - chara->rotation_24.vy) >= FP_ANGLE(-22.5f) &&
                        FP_ANGLE_NORM_S(angle - chara->rotation_24.vy) <  FP_ANGLE(22.5f) &&
                        dist > Q12(4.0f) && dist < Q12(8.0f))
                    {
                        temp_s1 += Q12(0.2f);
                    }

                    if (Rng_RandQ12() < temp_s1)
                    {
                        if (chara->properties_E4.unk0.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(chara, chara->field_40 + 1, Q12(0.6f));
                        }
                        chara->model_0.state_2               = 38;
                        chara->model_0.stateStep_3           = 0;
                        chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                    }
                    else if (Rng_RandQ12() < temp_s2)
                    {
                        chara->model_0.state_2               = 42;
                        chara->model_0.stateStep_3           = 0;
                        chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
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
