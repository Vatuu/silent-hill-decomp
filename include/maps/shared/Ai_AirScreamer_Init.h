s32 Ai_AirScreamer_Init(s_SubCharacter* chara)
{
#define AIRSCREAMER_BASE_HEALTH 380
#define AIRSCREAMER_RAND_MAX 100
#define NIGHTFLUTTER_RAND_MAX 300

#define AIRSCREAMER_RAND_MAX_HEALTHBONUS_EASY -100
#define AIRSCREAMER_RAND_MAX_HEALTHBONUS_HARD 100

    if (chara->model_0.state_2 != 0)
    {
        return 0;
    }

    if (chara->model_0.charaId_0 == Chara_NightFlutter)
    {
        chara->health_B0 = FP_TO(AIRSCREAMER_BASE_HEALTH, Q12_SHIFT) + (func_80080514() * NIGHTFLUTTER_RAND_MAX);
    }
    else
    {
        chara->health_B0 = FP_TO(AIRSCREAMER_BASE_HEALTH, Q12_SHIFT) + (func_80080514() * AIRSCREAMER_RAND_MAX);
    }

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            chara->health_B0 += (func_80080514() * AIRSCREAMER_RAND_MAX_HEALTHBONUS_EASY);
            break;
        case GameDifficulty_Normal:
            break;
        case GameDifficulty_Hard:
            chara->health_B0 += (func_80080514() * AIRSCREAMER_RAND_MAX_HEALTHBONUS_HARD);
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

    return 1;
}
