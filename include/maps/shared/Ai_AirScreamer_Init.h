bool Ai_AirScreamer_Init(s_SubCharacter* airScreamer)
{
    #define BASE_HEALTH                 Q12(380.0f)
    #define AIR_SCREAMER_RAND_MAX       100
    #define NIGHT_FLUTTER_RAND_MAX      300
    #define RAND_MAX_HEALTH_BONUS_EASY -100
    #define RAND_MAX_HEALTH_BONUS_HARD  100

    // Return early if already initialized.
    if (airScreamer->model_0.state_2 != ModelState_Uninitialized)
    {
        return false;
    }

    // Set base health with random variation, accounting for differences between Air Screamer and Night Flutter.
    if (airScreamer->model_0.charaId_0 == Chara_NightFlutter)
    {
        airScreamer->health_B0 = BASE_HEALTH + (Rng_RandQ12() * NIGHT_FLUTTER_RAND_MAX);
    }
    else
    {
        airScreamer->health_B0 = BASE_HEALTH + (Rng_RandQ12() * AIR_SCREAMER_RAND_MAX);
    }

    // Set health according to game difficulty.
    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            airScreamer->health_B0 += Rng_RandQ12() * RAND_MAX_HEALTH_BONUS_EASY;
            break;

        case GameDifficulty_Normal:
            break;

        case GameDifficulty_Hard:
            airScreamer->health_B0 += Rng_RandQ12() * RAND_MAX_HEALTH_BONUS_HARD;
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
    Ai_AirScreamer_GroundWarp(airScreamer);
    sharedFunc_800D2BE4_0_s01(airScreamer);

    return true;
}
