bool Ai_AirScreamer_Init(s_SubCharacter* chara)
{
    #define AIR_SCREAMER_BASE_HEALTH FP_HEALTH(380.0f)
    #define AIR_SCREAMER_RAND_MAX    100
    #define NIGHT_FLUTTER_RAND_MAX   300

    #define AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_EASY -100
    #define AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_HARD  100

    if (chara->model_0.state_2 != 0)
    {
        return false;
    }

    if (chara->model_0.charaId_0 == Chara_NightFlutter)
    {
        chara->health_B0 = AIR_SCREAMER_BASE_HEALTH, Q12_SHIFT + (func_80080514() * NIGHT_FLUTTER_RAND_MAX);
    }
    else
    {
        chara->health_B0 = AIR_SCREAMER_BASE_HEALTH, Q12_SHIFT + (func_80080514() * AIR_SCREAMER_RAND_MAX);
    }

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            chara->health_B0 += func_80080514() * AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_EASY;
            break;

        case GameDifficulty_Normal:
            break;

        case GameDifficulty_Hard:
            chara->health_B0 += func_80080514() * AIR_SCREAMER_RAND_MAX_HEALTH_BONUS_HARD;
            break;

        default:
            break;
    }

    sharedFunc_800D2BF4_0_s01(chara);
    sharedSymbol_800D3B0C_0_s01(chara);
    sharedFunc_800D2390_0_s01(chara);
    sharedFunc_800D2390_0_s01(chara);
    sharedFunc_800D2B00_0_s01(chara);
    sharedFunc_800D2B10_0_s01(chara);
    sharedFunc_800D2B28_0_s01(chara);
    sharedFunc_800D2B4C_0_s01(chara);
    sharedFunc_800D2BB0_0_s01(chara);
    sharedFunc_800D2BE4_0_s01(chara);

    return true;
}
