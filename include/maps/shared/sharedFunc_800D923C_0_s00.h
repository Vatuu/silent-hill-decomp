void sharedFunc_800D923C_0_s00(s_SubCharacter* chara)
{
    chara->model_0.stateStep_3 = 0;

    chara->field_C8 = 0;
    chara->field_CA = 0;
    chara->field_CE = 0;
    chara->field_D4 = 0;
    chara->field_D6 = 0;
    chara->field_DE = 0;
    chara->field_DC = 0;
    chara->field_DA = 0;
    chara->field_D8 = 0;

    chara->properties_E4.player.properties_E4[PlayerProperty_PositionY] = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_AfkTimer]  = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_PositionY] = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_Unk3]      = 0;
    chara->properties_E4.player.properties_E4[PlayerProperty_Unk4]      = 0;

    chara->model_0.state_2++;

    chara->field_E0_8 = 3;
}
