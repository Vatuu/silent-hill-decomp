// Returns index. Called in `Ai_AirScreamer_Update`.
bool sharedFunc_800D62D8_0_s01(s_SubCharacter* airScreamer)
{
    if (sharedFunc_800D4A80_0_s01(airScreamer) != 0 && !(sharedData_800E21D0_0_s01.flags_0 & (1 << 29)))
    {
        sharedFunc_800D63A4_0_s01(airScreamer);
        sharedFunc_800D6600_0_s01(airScreamer);
        sharedFunc_800D633C_0_s01(airScreamer);
    }

    sharedFunc_800D7560_0_s01(airScreamer);
    return true;
}
