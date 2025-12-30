void sharedFunc_800DB8AC_2_s00(s_SubCharacter* airScreamer)
{
    sharedFunc_800DEC84_2_s00(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamer->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2     = 33;
                    airScreamer->model_0.stateStep_3 = 0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2     = 34;
                    airScreamer->model_0.stateStep_3 = 0;
                    break;
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
