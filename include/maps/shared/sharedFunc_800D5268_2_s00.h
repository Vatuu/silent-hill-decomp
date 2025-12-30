void sharedFunc_800D5268_2_s00(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool cond1;
    u32  temp_v1;
    s32  animStatus;

    cond0      = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
            airScreamer->model_0.stateStep_3                     = 7;
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(56.0f);
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (airScreamer->properties_E4.unk0.properties_120.val32 == 0)
            {
                cond0 = true;
            }
            else if ((((u32)airScreamer->model_0.stateStep_3 - 1) * Q12(8.0f)) >= airScreamer->properties_E4.unk0.properties_120.val32 &&
                     animStatus == ANIM_STATUS(14, true))
            {
                airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(13, false);
                airScreamer->model_0.stateStep_3           = 8;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk2;
            }
            break;

        case 8:
            airScreamer->properties_E4.unk0.properties_120.val32 += g_DeltaTime0;

            if (animStatus == ANIM_STATUS(14, true))
            {
                temp_v1 = Rng_RandQ12() * 12;
                if (temp_v1 < airScreamer->properties_E4.unk0.properties_120.val32)
                {
                    airScreamer->properties_E4.unk0.properties_120.val32 -= temp_v1;
                }
                else
                {
                    airScreamer->properties_E4.unk0.properties_120.val32 = 0;
                }

                airScreamer->model_0.stateStep_3 = ((u32)airScreamer->properties_E4.unk0.properties_120.val32 / Q12(8.0f)) + 1;
            }
            break;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (cond0)
            {
                case 0:
                    if (ANIM_STATUS_IS_ACTIVE(animStatus))
                    {
                        if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
                        {
                            if (!airScreamer->properties_E4.unk0.field_E8_8)
                            {
                                cond1 = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                            }
                            else
                            {
                                cond1 = true;
                            }

                            if (cond1)
                            {
                                airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                                airScreamer->model_0.controlState_2               = 10;
                                airScreamer->model_0.stateStep_3           = 0;
                                airScreamer->flags_3E                     |= CharaFlag_Unk3;
                                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                                airScreamer->properties_E4.unk0.field_E8_8 = 3;
                            }
                        }
                        else if (airScreamer->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31 ||
                                 sharedData_800E21D0_0_s01.field_14C.bits.field_14C_1 ||
                                 sharedData_800E21D0_0_s01.field_15C > Q12(10.0f))
                        {
                            airScreamer->model_0.anim_4.status_0       = ANIM_STATUS(23, false);
                            airScreamer->model_0.controlState_2               = 7;
                            airScreamer->model_0.stateStep_3           = 0;
                            airScreamer->properties_E4.unk0.field_E8_8 = 3;
                        }
                    }
                    break;

                case 1:
                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    airScreamer->model_0.controlState_2         = 15;
                    airScreamer->model_0.stateStep_3     = 0;
                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 16;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

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
