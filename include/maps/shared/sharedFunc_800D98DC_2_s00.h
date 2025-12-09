void sharedFunc_800D98DC_2_s00(s_SubCharacter* chara)
{
    s32  animStatus;
    s32  switchCond;
    s32  sp10;
    bool cond;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    s32  temp_s4;
    s32  distFieldF8;
    s32  angFieldF8;
    u32  maxHack = FP_ANGLE(60.0f) * 2; // @hack Needed to get matching `sltu`

    animStatus     = chara->model_0.anim_4.status_0;
    switchCond     = 0;
    sp10           = sharedFunc_800D4A80_0_s01(chara);
    cond           = false;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s4        = sharedFunc_800DC438_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            cond                                           = 1;
            chara->properties_E4.unk0.properties_120.val32 = Q12(5.0f);
            sharedFunc_800DECC4_2_s00(chara);
            chara->model_0.stateStep_3 = 1;

        case 1:
            distFieldF8 = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);
            if (temp_s4 == 2)
            {
                chara->model_0.stateStep_3 = temp_s4;
            }
            else if (temp_s4 == 1 ||
                     (sharedFunc_800DC30C_2_s00(chara) && cond == true &&
                      chara->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31 &&
                      (distFieldF8 < Q12(2.0f) || angFieldF8 + FP_ANGLE(60.0f) > maxHack))) // @hack Should be `angFieldF8 >= FP_ANGLE(-60.0f) && angFieldF8 < FP_ANGLE(60.0f)`
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (sharedFunc_800DC3BC_2_s00(chara) && cond == true && distFieldF8 < Q12(4.0f) &&
                     (angFieldF8 >= FP_ANGLE(-30.0f) && angFieldF8 <= FP_ANGLE(30.0f)) && func_80080514() < Q12(0.7f))
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0 || distFieldF8 < Q12(2.0f))
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

    sharedFunc_800E021C_2_s00(chara, 0, 1);
    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if ((field14C_1 | field14C_0 | field14C_2) != 0)
                    {
                        chara->model_0.state_2     = 35;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
                case 1:
                    if (sp10 == switchCond)
                    {
                        chara->model_0.state_2     = (field14C_1 | field14C_0 | field14C_2) ? 6 : 5;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
                case 2:
                    if (sp10 == switchCond)
                    {
                        chara->model_0.state_2     = (field14C_1 | field14C_0 | field14C_2) ? 20 : 19;
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
