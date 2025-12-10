void sharedFunc_800D92B4_2_s00(s_SubCharacter* chara)
{
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = (Rng_RandQ12() * 2) + Q12(0.5f);

            sharedFunc_800D529C_0_s01(chara,
                                      Q12(4.0f),
                                      chara->rotation_24.vy + FP_MULTIPLY_PRECISE(Rng_RandQ12() - FP_ANGLE(180.0f), FP_ANGLE(45.0f), Q12_SHIFT));

            chara->model_0.stateStep_3 = 1;
            break;

        case 1:
            if (chara->properties_E4.unk0.properties_120.val32 == 0 ||
                Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(2.0f))
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;
    }

    sharedFunc_800E012C_2_s00(chara);

    switch (Chara_DamageTake(chara, Q12(0.6f)))
    {
        case 0:
            break;

        case 1:
        case 2:
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
