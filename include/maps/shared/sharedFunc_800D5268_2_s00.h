void sharedFunc_800D5268_2_s00(s_SubCharacter* chara)
{
    bool cond0;
    bool cond1;
    u32  temp_v1;
    s32  animStatus;

    cond0      = false;
    animStatus = chara->model_0.anim_4.status_0;

    switch ((u32)chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DDF74_2_s00(chara, Q12(0.1f), chara->rotation_24.vy);
            chara->model_0.stateStep_3                     = 7;
            chara->properties_E4.unk0.properties_120.val32 = Q12(56.0f);
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                cond0 = true;
            }
            else if ((((u32)chara->model_0.stateStep_3 - 1) * Q12(8.0f)) >= chara->properties_E4.unk0.properties_120.val32 &&
                     animStatus == ANIM_STATUS(14, true))
            {
                chara->model_0.anim_4.status_0       = ANIM_STATUS(13, false);
                chara->model_0.stateStep_3           = 8;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk2;
            }
            break;

        case 8:
            chara->properties_E4.unk0.properties_120.val32 += g_DeltaTime0;

            if (animStatus == ANIM_STATUS(14, true))
            {
                temp_v1 = func_80080514() * 12;
                if (temp_v1 < chara->properties_E4.unk0.properties_120.val32)
                {
                    chara->properties_E4.unk0.properties_120.val32 -= temp_v1;
                }
                else
                {
                    chara->properties_E4.unk0.properties_120.val32 = 0;
                }

                chara->model_0.stateStep_3 = ((u32)chara->properties_E4.unk0.properties_120.val32 / Q12(8.0f)) + 1;
            }
            break;
    }

    sharedFunc_800DF2D0_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (cond0)
            {
                case 0:
                    if (ANIM_STATUS_IS_ACTIVE(animStatus))
                    {
                        if (sharedData_800E21D0_0_s01.field_14C & (1 << 2))
                        {
                            if (!chara->properties_E4.unk0.field_E8_8)
                            {
                                cond1 = sharedFunc_800D3814_0_s01(chara) >= Q12(2.0f);
                            }
                            else
                            {
                                cond1 = true;
                            }

                            if (cond1)
                            {
                                chara->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                                chara->model_0.state_2               = 10;
                                chara->model_0.stateStep_3           = 0;
                                chara->flags_3E                     |= CharaFlag_Unk3;
                                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                                chara->properties_E4.unk0.field_E8_8 = 3;
                            }
                        }
                        else if (chara->properties_E4.unk0.flags_11C < CharaUnk0Flag_None ||
                                 (sharedData_800E21D0_0_s01.field_14C & (1 << 1)) ||
                                 sharedData_800E21D0_0_s01.field_15C > Q12(10.0f))
                        {
                            chara->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                            chara->model_0.state_2               = 7;
                            chara->model_0.stateStep_3           = 0;
                            chara->properties_E4.unk0.field_E8_8 = 3;
                        }
                    }
                    break;

                case 1:
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    chara->model_0.state_2         = 15;
                    chara->model_0.stateStep_3     = 0;
                    sharedFunc_800D3DFC_0_s01(chara);
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2               = 16;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

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
