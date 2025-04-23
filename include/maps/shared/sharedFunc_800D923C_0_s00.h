void sharedFunc_800D923C_0_s00(s_SubCharacter* playerChara)
{
    s32 flags;

    flags = playerChara->flags_E0;
    flags = flags & ~((1 << 8) | (1 << 9) | (1 << 10) | (1 << 11));

    playerChara->model_0.isAnimStateUnchanged_3 = 0;

    playerChara->field_C8 = 0;
    playerChara->field_CA = 0;
    playerChara->field_CE = 0;
    playerChara->field_D4 = 0;
    playerChara->field_D6 = 0;
    playerChara->field_DE = 0;
    playerChara->field_DC = 0;
    playerChara->field_DA = 0;
    playerChara->field_D8 = 0;

    playerChara->properties_E4[PlayerProperty_PositionY] = 0;
    playerChara->properties_E4[PlayerProperty_AfkTimer]  = 0;
    playerChara->properties_E4[PlayerProperty_PositionY] = 0;
    playerChara->properties_E4[PlayerProperty_Unk3]      = 0;
    playerChara->properties_E4[PlayerProperty_Unk4]      = 0;

    playerChara->flags_E0 = flags | ((1 << 8) | (1 << 9));
    playerChara->model_0.field_2++;
}
