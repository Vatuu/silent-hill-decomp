void sharedFunc_800D6400_2_s00(s_SubCharacter* chara)
{
    sharedFunc_800DDF74_2_s00(chara, Q12(0.5f), chara->rotation_24.vy);
    sharedFunc_800DF2D0_2_s00(chara);
    chara->flags_3E &= ~CharaFlag_Unk3;

    switch (Ai_AirScreamer_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch ((u32)chara->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    chara->model_0.controlState_2     = 4;
                    chara->model_0.stateStep_3 = 0;
                    break;

                case 1:
                    chara->model_0.controlState_2     = 5;
                    chara->model_0.stateStep_3 = 0;
                    break;

                case 3:
                    chara->model_0.controlState_2     = 5;
                    chara->model_0.stateStep_3 = 0;
                    break;
            }
            break;

        case 1:
        case 2:
            chara->model_0.controlState_2               = 16;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2     = 17;
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
