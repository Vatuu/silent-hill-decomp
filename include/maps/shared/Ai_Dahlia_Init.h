void Ai_Dahlia_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);

    sharedData_800D16E0_2_s01 = 0;
    sharedData_800D16E4_2_s01 = 0;

#ifdef MAP7_S03
    func_8003DD80(Chara_EndingDahlia, 1); // TODO: MAP7_S03 Ai_Dahlia funcs could be Ai_EndingDahlia instead, if other Ai_Dahlia funcs don't match other overlays.
#else
    func_8003DD80(Chara_Dahlia, 1);
#endif

#ifdef MAP7_S02
    func_8003D468(Chara_Dahlia, true);
#endif
}
