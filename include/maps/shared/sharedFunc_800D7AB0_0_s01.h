bool sharedFunc_800D7AB0_0_s01(s_SubCharacter* chara)
{
    GsCOORDINATE2* coords;
    s_AnmHeader* animHdr;

    animHdr = sharedData_800E21D0_0_s01.anmHdr_4;
    coords = sharedData_800E21D0_0_s01.coords_8;
    sharedFunc_800D76A0_0_s01(chara);
    func_80044950(chara, animHdr, coords);
    sharedFunc_800D7B14_0_s01(chara, coords);

    return true;
}

