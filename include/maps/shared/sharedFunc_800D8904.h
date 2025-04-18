void sharedFunc_800D8904(s_SubCharacter* playerChara, s32 afkTime)
{
    playerChara->field_126 = 0;
    playerChara->properties_E4[PlayerProperty_RunTimer0] = 0;
    playerChara->properties_E4[PlayerProperty_Unk3] = 0;
    playerChara->properties_E4[PlayerProperty_AfkTimer] = afkTime;
    playerChara->model_0.isAnimStateUnchanged_3 = 0;
}
