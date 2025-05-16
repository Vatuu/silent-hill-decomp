void sharedFunc_800D923C_0_s00(s_SubCharacter* playerChara)
{
    playerChara->model_0.stageStep_3 = 0;

    playerChara->field_C8 = 0;
    playerChara->field_CA = 0;
    playerChara->field_CE = 0;
    playerChara->field_D4 = 0;
    playerChara->field_D6 = 0;
    playerChara->field_DE = 0;
    playerChara->field_DC = 0;
    playerChara->field_DA = 0;
    playerChara->field_D8 = 0;

    playerChara->properties_E4.player.properties_E4[PlayerProperty_PositionY] = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_AfkTimer]  = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_PositionY] = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_Unk3]      = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_Unk4]      = 0;

    playerChara->model_0.stage_2++;

    playerChara->field_E0_8 = 3;
}
