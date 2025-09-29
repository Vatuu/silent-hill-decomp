void sharedFunc_800D923C_0_s00(s_SubCharacter* chara)
{
    chara->model_0.stateStep_3 = 0;

    chara->field_C8           = Q12(0.0f);
    chara->field_CA           = Q12(0.0f);
    chara->field_CE           = Q12(0.0f);
    chara->field_D4           = Q12(0.0f);
    chara->field_D6           = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_2 = Q12(0.0f);
    chara->field_D8.offsetX_0 = Q12(0.0f);

    chara->properties_E4.player.positionY_EC = Q12(0.0f);
    chara->properties_E4.player.afkTimer_E8  = Q12(0.0f);
    chara->properties_E4.player.positionY_EC = Q12(0.0f);
    chara->properties_E4.player.field_F0     = 0;
    chara->properties_E4.player.field_F4     = 0;

    chara->model_0.state_2++;

    chara->field_E1_0 = 3;
}
