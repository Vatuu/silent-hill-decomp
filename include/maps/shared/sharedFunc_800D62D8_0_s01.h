// Called in `Ai_AirScreamer_Update`.
s32 sharedFunc_800D62D8_0_s01(s_SubCharacter* chara)
{
    if (sharedFunc_800D4A80_0_s01(chara) != 0 && !(sharedData_800E21D0_0_s01 & 0x20000000))
    {
        sharedFunc_800D63A4_0_s01(chara);
        sharedFunc_800D6600_0_s01(chara);
        sharedFunc_800D633C_0_s01(chara);
    }

    sharedFunc_800D7560_0_s01(chara);
    return 1;
}
