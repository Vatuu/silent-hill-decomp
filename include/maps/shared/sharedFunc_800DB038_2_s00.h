void sharedFunc_800DB038_2_s00(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0 = false;
    cond1 = false;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(17, true))
            {
                airScreamer->model_0.stateStep_3     = 2;
                airScreamer->model_0.anim_4.status_0 = 6;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(3, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3           = 3;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(17, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0                      = true;
                cond1                      = true;
                airScreamer->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DEE24_2_s00(airScreamer);
    sharedFunc_800E0514_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0:
            if (cond0)
            {
                if (airScreamer->properties_E4.unk0.field_E8_8 == 5 && cond1)
                {
                    airScreamer->properties_E4.unk0.field_E8_8 = 1;
                    airScreamer->model_0.controlState_2               = 42;
                }
                else
                {
                    airScreamer->model_0.controlState_2 = 39;
                }

                airScreamer->model_0.stateStep_3 = 0;
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

            if (airScreamer->health_B0 <= 0)
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
