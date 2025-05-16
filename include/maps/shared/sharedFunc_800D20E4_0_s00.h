void sharedFunc_800D20E4_0_s00()
{
    // TODO: Pointers here are odd, might be full of inlines.

    s_MainCharacterExtra* extra;
    s_SubCharacter*       chara;
    s_SysWork*            sysWork;

    sharedData_800DD59C_0_s00 = NO_VALUE;

    D_800C457C = 0;
    D_800C4588 = 0;
    D_800AF215 = 1;
    D_800AF214 = 0;

    extra   = &g_SysWork.player_4C.extra_128;
    chara   = &g_SysWork.player_4C.chara_0;
    sysWork = &g_SysWork;

    D_800AF216 = 0;

    chara->properties_E4[PlayerProperty_AfkTimer]      = 0;
    chara->properties_E4[PlayerProperty_RunTimer0]     = 0;
    chara->properties_E4[PlayerProperty_ExertionTimer] = 0;
    sysWork->player_4C.extra_128.field_1C              = 52;
    chara->model_0.isAnimStateUnchanged_3              = 0;
    chara->model_0.field_2                             = 0;
    extra->model_0.isAnimStateUnchanged_3              = 0;
    extra->model_0.field_2                             = 0;

    D_800C45C0 = 0;
    D_800C45BE = 0;
    D_800C45BC = 0;
    D_800C457E = 0;
    D_800C4604 = 0;
    D_800C45F0 = 0;
    D_800C45E8 = 0;
    D_800C4582 = 0;
    D_800C45AE = 0;
    D_800C4586 = 0;
    D_800C4580 = 0;
    D_800C45AC = 0;
    D_800C4584 = 0;

    sysWork->player_4C.extra_128.field_20 = 0;
    sysWork->player_4C.extra_128.field_24 = 0;

    sharedData_800E39D8_0_s00 = 0;

    chara->field_D6 = 0;
    sysWork->player_4C.chara_0.field_11C |= 0x30;
    chara->field_3E |= 8;
    chara->field_E0_8 = 4;

    if (sysWork->field_38.field_F < 32)
    {
        sysWork->field_38.field_F = (sysWork->field_38.field_F % 10);
    }
}
