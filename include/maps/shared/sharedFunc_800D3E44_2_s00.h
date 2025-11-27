void sharedFunc_800D3E44_2_s00(s_SubCharacter* chara)
{
    bool cond;

    if (chara->model_0.stateStep_3 == 0)
    {
        sharedFunc_800DDF74_2_s00(chara, Q12(0.1f), chara->rotation_24.vy);
        chara->model_0.stateStep_3 = 1;
    }

    sharedFunc_800DF2D0_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
            {
                if (!chara->properties_E4.unk0.field_E8_8)
                {
                    cond = sharedFunc_800D3814_0_s01(chara) >= Q12(2.0f);
                }
                else
                {
                    cond = true;
                }

                if (cond)
                {
                    chara->model_0.state_2               = 10;
                    chara->model_0.stateStep_3           = 0;
                    chara->flags_3E                     |= CharaFlag_Unk3;
                    chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                }
            }
            else
            {
                if (chara->properties_E4.unk0.flags_11C & CharaUnk0Flag_Unk31)
                {
                    chara->model_0.state_2     = 7;
                    chara->model_0.stateStep_3 = 0;
                }
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
