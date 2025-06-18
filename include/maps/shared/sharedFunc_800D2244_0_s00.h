void sharedFunc_800D2244_0_s00(s32 arg0)
{
    s_MainCharacterExtra* extra;
    s_SubCharacter*       player;

    D_800AF215 = 0;

    extra  = &g_SysWork.player_4C.extra_128;
    player = &g_SysWork.player_4C.chara_0;

    if (arg0 != 0)
    {
        g_SysWork.player_4C.extra_128.field_1C = 0;
        g_SysWork.player_4C.extra_128.field_20 = 0;
        g_SysWork.player_4C.extra_128.field_24 = 0;

        player->model_0.anim_4.animIdx_0      = 53;
        player->model_0.anim_4.keyframeIdx0_8 = 503;
        extra->model_0.anim_4.animIdx_0       = 53;
        extra->model_0.anim_4.keyframeIdx0_8  = 503;

        player->model_0.anim_4.time_4         = FP_TO(503, Q12_SHIFT);
        player->model_0.anim_4.keyframeIdx1_A = 4096;
        extra->model_0.anim_4.time_4          = FP_TO(503, Q12_SHIFT);
        extra->model_0.anim_4.keyframeIdx1_A  = 4096;
    }
    else
    {
        g_SysWork.player_4C.extra_128.field_1C = 0;

        player->model_0.stateStep_3 = 0;
        player->model_0.state_2     = 0;
        extra->model_0.stateStep_3  = 0;
        extra->model_0.state_2      = 0;

        g_SysWork.player_4C.extra_128.field_20 = 0;
        g_SysWork.player_4C.extra_128.field_24 = 0;
    }

    player->unk_40[1]     = -1;
    player->unk_40[0]     = -1;
    g_SysWork.unk_2354[1] = -1;
    g_SysWork.unk_2354[0] = -1;

#if !defined(MAP0_S00) && !defined(MAP0_S01)
    func_8003D01C();
#endif

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

    g_SysWork.isPlayerInCombatMode_4B = 0;

    player->field_D6 = 942;

    g_SysWork.player_4C.chara_0.field_C8 = -0x1999; // TODO: Q19.12?
    g_SysWork.player_4C.chara_0.field_CE = -0x1199;
    g_SysWork.player_4C.chara_0.field_CA = 0;
    g_SysWork.player_4C.chara_0.field_DE = 0;
    g_SysWork.player_4C.chara_0.field_DC = 0;
    g_SysWork.player_4C.chara_0.field_DA = 0;
    g_SysWork.player_4C.chara_0.field_D8 = 0;
    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~((1 << 2) | (1 << 13) | (1 << 14) | (1 << 15));

    player->flags_3E &= ~CharaFlag_Unk4;
    player->field_E0_8 = 3;

    Player_AnimFlag_Set(AnimFlag_Unk1);

    D_800C45F8.vx = player->position_18.vx;
    D_800C45F8.vz = player->position_18.vz;

#if !defined(MAP0_S00)
    D_800AF210 = 0;
    D_800AF212 = 0;
#endif
}
