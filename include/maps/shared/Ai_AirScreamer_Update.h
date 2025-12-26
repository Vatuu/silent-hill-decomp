void Ai_AirScreamer_Update(s_SubCharacter* airScreamer, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedFunc_800D21E4_0_s01(anmHdr, coords);
    sharedFunc_800D2200_0_s01(airScreamer);

    Ai_AirScreamer_Init(airScreamer);

    sharedFunc_800D2274_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D3928_0_s01(airScreamer);
    sharedFunc_800D62D8_0_s01(airScreamer);
    sharedFunc_800D7AB0_0_s01(airScreamer);
    sharedFunc_800D7EBC_0_s01(airScreamer);
    sharedFunc_800D81B0_0_s01(airScreamer);
}
