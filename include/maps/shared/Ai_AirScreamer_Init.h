bool Ai_AirScreamer_Init(s_SubCharacter* airScreamer)
{
    #define AIR_SCREAMER_BASE_HEALTH Q12(380.0f)
    #define AIR_SCREAMER_RAND_MAX    100
    #define NIGHT_FLUTTER_RAND_MAX   300

    #define AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_EASY -100
    #define AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_HARD  100

    if (airScreamer->model_0.state_2 != 0)
    {
        return false;
    }

    if (airScreamer->model_0.charaId_0 == Chara_NightFlutter)
    {
        airScreamer->health_B0 = AIR_SCREAMER_BASE_HEALTH + (Rng_RandQ12() * NIGHT_FLUTTER_RAND_MAX);
    }
    else
    {
        airScreamer->health_B0 = AIR_SCREAMER_BASE_HEALTH + (Rng_RandQ12() * AIR_SCREAMER_RAND_MAX);
    }

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            airScreamer->health_B0 += Rng_RandQ12() * AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_EASY;
            break;

        case GameDifficulty_Normal:
            break;

        case GameDifficulty_Hard:
            airScreamer->health_B0 += Rng_RandQ12() * AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_HARD;
            break;
    }

    sharedFunc_800D2BF4_0_s01(airScreamer);
    sharedSymbol_800D3B0C_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D2B00_0_s01(airScreamer);
    sharedFunc_800D2B10_0_s01(airScreamer);
    sharedFunc_800D2B28_0_s01(airScreamer);
    sharedFunc_800D2B4C_0_s01(airScreamer);
    sharedFunc_800D2BB0_0_s01(airScreamer);
    sharedFunc_800D2BE4_0_s01(airScreamer);

    return true;
}
