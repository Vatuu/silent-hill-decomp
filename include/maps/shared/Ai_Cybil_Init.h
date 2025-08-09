void Ai_Cybil_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800E2378_0_s01 = 0;
    sharedData_800E237C_0_s01 = 0;

#ifdef MAP7_S03
    func_8003DD80(Chara_EndingCybil, 17);
#else
    func_8003DD80(Chara_Cybil, 17);
#endif
}
