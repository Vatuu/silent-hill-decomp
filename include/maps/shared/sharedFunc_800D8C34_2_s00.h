void sharedFunc_800D8C34_2_s00(s_SubCharacter* airScreamer)
{
    sharedFunc_800D529C_0_s01(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800D598C_0_s01(airScreamer);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamer->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2     = 18;
                    airScreamer->model_0.stateStep_3 = 0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2     = 19;
                    airScreamer->model_0.stateStep_3 = 0;
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2               = 29;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

        case 2:
            airScreamer->model_0.controlState_2               = 30;
            airScreamer->model_0.stateStep_3           = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 32;
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
