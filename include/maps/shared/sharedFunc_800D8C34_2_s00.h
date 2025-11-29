void sharedFunc_800D8C34_2_s00(s_SubCharacter* chara)
{
    sharedFunc_800D529C_0_s01(chara, Q12(0.5f), chara->rotation_24.vy);
    sharedFunc_800D598C_0_s01(chara);
    chara->flags_3E &= ~CharaFlag_Unk3;

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)chara->properties_E4.unk0.field_E8_0)
            {
                case 0:
                    chara->model_0.state_2     = 18;
                    chara->model_0.stateStep_3 = 0;
                    break;
                case 1:
                case 3:
                    chara->model_0.state_2     = 19;
                    chara->model_0.stateStep_3 = 0;
                    break;
            }
            break;

        case 1:
            chara->model_0.state_2               = 29;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

        case 2:
            chara->model_0.state_2               = 30;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 32;
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
