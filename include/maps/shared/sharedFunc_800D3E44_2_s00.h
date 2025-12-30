void sharedFunc_800D3E44_2_s00(s_SubCharacter* airScreamer)
{
    bool cond;

    if (airScreamer->model_0.stateStep_3 == 0)
    {
        sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
        airScreamer->model_0.stateStep_3 = 1;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
            {
                if (!airScreamer->properties_E4.unk0.field_E8_8)
                {
                    cond = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                }
                else
                {
                    cond = true;
                }

                if (cond)
                {
                    airScreamer->model_0.controlState_2               = 10;
                    airScreamer->model_0.stateStep_3           = 0;
                    airScreamer->flags_3E                     |= CharaFlag_Unk3;
                    airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                }
            }
            else
            {
                if (airScreamer->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31)
                {
                    airScreamer->model_0.controlState_2     = 7;
                    airScreamer->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2               = 16;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

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
