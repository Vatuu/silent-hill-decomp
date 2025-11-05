void sharedFunc_800DE1F8_2_s00(s_SubCharacter* chara) // 0x800DE514
{
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;

    temp_s1                                        = chara->properties_E4.player.field_104;
    temp_s2                                        = chara->properties_E4.npc.field_10C;
    temp_v0                                        = func_80080884(temp_s1, temp_s2);
    chara->properties_E4.player.runTimer_F8        = temp_s1;
    chara->properties_E4.player.exhaustionTimer_FC = temp_v0;
    chara->properties_E4.player.field_100          = temp_s2;
    sharedFunc_800D4E84_0_s01(chara);
}
