void sharedFunc_800CD9F4_3_s03(s_SubCharacter* chara, s32 arg1)
{
    s_SfxPair* sfx;
    s32        idx;

    sfx = sharedData_800D57F0_3_s03;
    idx = (chara->properties_E4.npc.field_124->idx_1C * 9) + arg1;
    func_8005DC1C(sfx[idx].sfxId, &chara->position_18, sfx[idx].vol, 0);
}
