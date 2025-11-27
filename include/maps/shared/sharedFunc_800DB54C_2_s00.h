void sharedFunc_800DB54C_2_s00(s_SubCharacter* chara)
{
    s32    temp_a0;
    bool   field14C;
    s32    angleDelta;
    q19_12 angle;
    q19_12 dist;
    s32    temp_s7;
    s32    switchCond;
    q19_12 var_s3;
    s32    var_s5; // Possibly `bool`
    s32    animStatus;
    s32    new_var;

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(chara);
    dist       = sharedData_800E21D0_0_s01.dist_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s7    = new_var;
    var_s3     = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    temp_a0    = sharedFunc_800DC438_2_s00(chara);
    var_s5     = 0;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            var_s5     = sharedFunc_800DF24C_2_s00(chara);
            var_s3     = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angleDelta = FP_ANGLE_NORM_S(angle - chara->rotation_24.vy);
            if (!sharedFunc_800DC30C_2_s00(chara) || (angleDelta < FP_ANGLE(-30.0f) || angleDelta >= FP_ANGLE(30.0f)))
            {
                chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
                chara->model_0.stateStep_3                     = 1;
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 1:
            if (temp_a0 == 2)
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (temp_a0 == 1)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (var_s3 < Q12(2.0f) || (chara->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31))
            {
                var_s5 = sharedFunc_800DF24C_2_s00(chara);
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                chara->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                chara->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            switchCond = 2;
            break;
    }

    sharedFunc_800E021C_2_s00(chara, 2, 0);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (var_s5 || (((field14C != 0 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && var_s3 < Q12(1.5f)))
                    {
                        chara->model_0.state_2               = 38;
                        chara->model_0.stateStep_3           = 0;
                        chara->properties_E4.unk0.field_E8_8 = 3;
                        chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                    }
                    else if (dist > Q12(30.0f) && var_s3 < Q12(1.0f))
                    {
                        chara->model_0.state_2     = 36;
                        chara->model_0.stateStep_3 = 0;
                    }
                    return;
                case 1:
                    if (temp_s7 == 1)
                    {
                        chara->model_0.state_2     = 14;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
                case 2:
                    if (temp_s7 == 2)
                    {
                        chara->model_0.state_2     = 27;
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
            if (chara->health_B0 <= 0)
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
