void Ai_Kaufmann_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);

    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[14].val32 = 0; // TODO: Change to `properties_E4.humanoid`?

    sharedData_800D5CF4_3_s00 = 0;

#ifdef MAP7_S03
    func_8003DD80(Chara_EndingKaufmann, 16); // TODO: MAP7_S03 Ai_Kaufmann funcs could be Ai_EndingKaufmann instead, if other Ai_Kaufmann funcs don't match other overlays.
#else
    func_8003DD80(Chara_Kaufmann, 16);
#endif

#ifdef MAP7_S02
    func_8003D468(Chara_Kaufmann, 1);
#endif
}
