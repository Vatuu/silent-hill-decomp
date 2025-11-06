
#if !defined(MAP_CHARA_COUNT)
#define MAP_CHARA_COUNT 1
#endif

/*
 * Character case switch handling
 *
 * Maps define one or more HAS_Chara_X flags to include their
 * respective switch cases.
 * When only a single case is present (MAP_CHARA_COUNT == 1), the 
 * macro below replaces `case N:` with `default:` so that the compiler
 * collapses the switch into a direct block, matching single-case maps 
 * that skip checking the case entirely.
 *
 * `sharedFunc_800D8964_0_s00` includes very close copy of this switch.
 */

#if MAP_CHARA_COUNT > 1
#define CHARA_CASE(id) case id:
#else
#define CHARA_CASE(id) default:
#endif

s32 Anim_StartKeyframeIdxGet(s_SubCharacter* chara)
{
    s_AnimInfo* animInfo = NULL;

    switch (chara->model_0.charaId_0)
    {
#if defined(MAP5_S02) || defined(MAP5_S03)
        // `animInfo` left as `NULL`.
#else

#ifdef HAS_Chara_EndingCybil
        CHARA_CASE(Chara_Cybil)
        CHARA_CASE(Chara_EndingCybil)
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Cybil
        CHARA_CASE(Chara_Cybil)
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_MonsterCybil
        CHARA_CASE(Chara_MonsterCybil)
            animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_EndingDahlia
        CHARA_CASE(Chara_Dahlia)
        CHARA_CASE(Chara_EndingDahlia)
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Dahlia
    #if defined(MAP6_S01) // Some reason Dahlia is default case in M6S01?
        default:
    #else
        CHARA_CASE(Chara_Dahlia)
    #endif
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Alessa
        CHARA_CASE(Chara_Alessa)
            animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_GhostChildAlessa
        CHARA_CASE(Chara_GhostChildAlessa)
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_EndingKaufmann
        CHARA_CASE(Chara_Kaufmann)
        CHARA_CASE(Chara_EndingKaufmann)
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Kaufmann
        CHARA_CASE(Chara_Kaufmann)
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

// M7S02 uses Chara_GhostDoctor in sharedFunc_800D8964_0_s00, but includes Lisa/BloodyLisa here?
#if defined(HAS_Chara_Lisa) || defined(HAS_Chara_GhostDoctor)
        CHARA_CASE(Chara_Lisa)
            animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#if defined(HAS_Chara_BloodyLisa) || defined(HAS_Chara_GhostDoctor)
        CHARA_CASE(Chara_BloodyLisa)
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Incubator
        CHARA_CASE(Chara_Incubator)
            animInfo = &INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_BloodyIncubator
        CHARA_CASE(Chara_BloodyIncubator)
            animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Cheryl
        CHARA_CASE(Chara_Cheryl)
            animInfo = &CHERYL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif
#endif
    }

    return animInfo->startKeyframeIdx_C;
}

#undef CHARA_CASE
