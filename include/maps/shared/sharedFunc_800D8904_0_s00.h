void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime)
{
    playerChara->properties_E4.player.field_126                               = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_RunTimer0] = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_Unk3]      = 0;
    playerChara->properties_E4.player.properties_E4[PlayerProperty_AfkTimer]  = afkTime;

    playerChara->model_0.stateStep_3 = 0;
}
