void sharedFunc_800D5554_2_s00(s_SubCharacter* chara)
{
    s32  animStatus;
    s32  sp14;
    s32  sp18;
    s32  temp_s3_2;
    s32  temp_s7;
    s32  temp_fp;
    s32  temp_s1;
    s32  temp_s1_2;
    s32  temp_s1_3;
    s32  temp_s4_2;
    s32  temp_s5;
    s32  temp_s6;
    s32  switchCond;
    bool new_var;

    animStatus = chara->model_0.anim_4.status_0;
    sp14       = sharedFunc_800D4A80_0_s01(chara);
    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp18       = new_var;
    temp_s1    = sharedData_800E21D0_0_s01.distance_150;
    sharedFunc_800DE11C_2_s00(chara);
    switchCond = 0;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            temp_s5 = temp_s1 + (Rng_RandQ12() * 4);

            if (sharedFunc_800DC200_2_s00(chara) && temp_s5 > Q12(8.0f))
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (!sharedFunc_800DC30C_2_s00(chara) || (temp_s5 <= Q12(4.0f) && Rng_RandQ12() >= Q12(0.5f)))
            {
                chara->model_0.stateStep_3 = 1;
            }
            else
            {
                chara->model_0.stateStep_3 = 2;
            }

            chara->properties_E4.unk0.properties_120.val32 = 0x4000;
            break;

        case 1:

            temp_s1_2 = sharedFunc_800DC598_2_s00(chara);
            temp_s5   = 0x999;
            temp_fp   = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);

            if (temp_s1_2 == 1)
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (temp_s1_2 == 2)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (temp_fp < 0x1199)
            {
                temp_s6   = chara->position_18.vy + chara->field_C8.field_0 + 0x199;
                temp_s1_3 = g_SysWork.playerWork_4C.player_0.position_18.vy;
                temp_s3_2 = g_SysWork.playerWork_4C.player_0.field_C8.field_4;
                temp_s7   = g_SysWork.playerWork_4C.player_0.field_C8.field_0;

                temp_s4_2 = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);

                if (sharedFunc_800DC30C_2_s00(chara))
                {
                    if (temp_s1_3 + temp_s3_2 < temp_s6 || temp_s6 < temp_s1_3 + temp_s7)
                    {
                        chara->model_0.stateStep_3 = 2;
                        break;
                    }
                }

                if (temp_fp < temp_s5)
                {
                    if (temp_s4_2 > -0x101 && temp_s4_2 < 0x100)
                    {
                        switchCond = 1;
                    }
                }
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 2:
            if (animStatus == 0x2F || animStatus == 0x33)
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = 0x2C;
                chara->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            switchCond = 2;
            break;

        case 4:
            if (animStatus == 0x2F || animStatus == 0x33)
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = 0x30;
                chara->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(chara, 1);

    switch (Ai_AirScreamer_DamageTake(chara, 0x1000))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(chara))
                    {
                        if (sp18 == 0)
                        {
                            chara->model_0.controlState_2 = 0xD;
                            chara->model_0.stateStep_3    = 0;
                        }
                    }
                    else
                    {
                        chara->model_0.controlState_2 = 0xE;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.playerWork_4C.player_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == 0x33 || animStatus == 0x2F)
                        {
                            chara->model_0.controlState_2 = 0xC;
                            chara->model_0.stateStep_3    = 0;
                        }
                    }
                    else
                    {
                        chara->model_0.controlState_2 = 0xB;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;

                case 2:
                    if (sp14 == 2)
                    {
                        chara->model_0.controlState_2 = 0x17;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;

                case 3:
                    if (sp14 == 3)
                    {
                        chara->model_0.controlState_2 = 0x26;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.controlState_2        = 0x10;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= 8;
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2 = 0x11;
            chara->model_0.stateStep_3    = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= 0x40;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= 8;
            }
            break;
    }
}