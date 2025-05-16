void sharedFunc_800D2C7C_0_s00(s32 arg0)
{
    s_MainCharacterExtra* extra = &g_SysWork.player_4C.extra_128;
    s_SubCharacter*       chara = &g_SysWork.player_4C.chara_0;

    extra = &g_SysWork.player_4C.extra_128;
    chara = &g_SysWork.player_4C.chara_0;

    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;

    D_800C4606 = 0;

    switch (arg0)
    {
        case 0x36:
            D_800C457C = 0;
            break;

        case 0x35:
            D_800C457C = 1;
            break;

        case 0x38:
            D_800C457C = 3;
            break;

        case 0x39:
            D_800C457C = 4;
            break;
    }

    g_SysWork.player_4C.extra_128.field_1C = arg0;

    chara->model_0.stateStep_3 = 0;
    chara->model_0.state_2     = 0;

    extra->model_0.stateStep_3 = 0;
    extra->model_0.state_2     = 0;

    g_SysWork.player_4C.extra_128.field_20 = 0;
    g_SysWork.player_4C.extra_128.field_24 = 0;
}
