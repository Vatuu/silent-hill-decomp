void sharedFunc_800D4358_2_s00(s_SubCharacter* chara)
{
    s32  animStatus;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool new_var1;
    bool new_var2;
    bool new_var3;
    s32  switchCond;
    bool cond;
    s32  temp_fp;
    s32  new_var;
    s32  angFieldF8;
    s32  distFieldF8;
    s32  temp_v0;
    u32  maxHack = Q12(2.0f);

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;
    cond       = false;

    new_var    = sharedFunc_800D4A80_0_s01(chara);
    new_var1   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp    = new_var;
    field14C_0 = new_var1;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DDE14_2_s00(chara);
            chara->model_0.stateStep_3 = 1;
            break;

        case 1:
            cond = true;

            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);

            chara->model_0.stateStep_3 = 2;

        case 2:
            distFieldF8 = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);
            temp_v0     = sharedFunc_800DC598_2_s00(chara);
            if (temp_v0 == 1)
            {
                chara->model_0.stateStep_3 = 3;
            }
            else if (temp_v0 == 2)
            {
                chara->model_0.stateStep_3 = 5;
            }
            else if ((distFieldF8 < Q12(0.5f) && (angFieldF8 >= FP_ANGLE(-5.0f) && angFieldF8 <= FP_ANGLE(5.0f))) ||
                     (chara->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31))
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 1;
            }
            else if (cond)
            {
                if (sharedFunc_800DC200_2_s00(chara) && distFieldF8 > Q12(6.0f))
                {
                    chara->model_0.stateStep_3 = 5;
                }
                else if (sharedFunc_800DC30C_2_s00(chara))
                {
                    // @hack This check should be
                    // `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`
                    // But that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` that we need.

                    int diff = (chara->properties_E4.unk0.field_F8.vy - chara->position_18.vy);
                    if (diff + Q12(1.0f) > maxHack)
                    {
                        chara->model_0.stateStep_3 = 3;
                    }
                }
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 1;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                chara->model_0.stateStep_3     = 4;
            }
            break;

        case 4:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                chara->model_0.stateStep_3     = 6;
            }
            break;

        case 6:
            switchCond = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(chara, 0);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        chara->model_0.state_2     = 6;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            chara->model_0.state_2 = 20;
                        }
                        else
                        {
                            chara->model_0.state_2 = 19;
                        }
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            chara->model_0.state_2 = 35;
                        }
                        else
                        {
                            chara->model_0.state_2 = 34;
                        }

                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2               = 16;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 17;
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
