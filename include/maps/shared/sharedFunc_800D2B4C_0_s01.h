void sharedFunc_800D2B4C_0_s01(s_SubCharacter* chara)
{
    q19_12         time;
    s_AnmHeader*   anmHdr;
    GsCOORDINATE2* coords;

    time   = g_DeltaTime0;
    anmHdr = sharedData_800E21D0_0_s01.anmHdr_4;
    coords = sharedData_800E21D0_0_s01.coords_8;

    g_DeltaTime0 = Q12(0.0f);

    func_80044950(chara, anmHdr, coords);

    g_DeltaTime0 = time;

    sharedFunc_800D7560_0_s01(chara);
    sharedFunc_800D82B8_0_s01(chara);
}
