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
 * `Anim_StartKeyframeIdxGet` includes very close copy of this switch.
 */

#if MAP_CHARA_COUNT > 1
    #define CHARA_CASE(id) case id
#else
    #define CHARA_CASE(id) default
#endif

s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara)
{
    s_AnimInfo* animInfo = NULL;

    switch (chara->model_0.charaId_0)
    {
#ifdef HAS_Chara_EndingCybil
        CHARA_CASE(Chara_Cybil):
        CHARA_CASE(Chara_EndingCybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Cybil
        CHARA_CASE(Chara_Cybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_MonsterCybil
        CHARA_CASE(Chara_MonsterCybil):
            animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_EndingDahlia
        CHARA_CASE(Chara_Dahlia):
        CHARA_CASE(Chara_EndingDahlia):
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Dahlia
    #if defined(MAP6_S01) // Some reason Dahlia is default case in M6S01?
        default:
    #else
        CHARA_CASE(Chara_Dahlia):
    #endif
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Alessa
        CHARA_CASE(Chara_Alessa):
            animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_GhostChildAlessa
        CHARA_CASE(Chara_GhostChildAlessa):
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_EndingKaufmann
        CHARA_CASE(Chara_Kaufmann):
        CHARA_CASE(Chara_EndingKaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Kaufmann
        CHARA_CASE(Chara_Kaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Lisa
        CHARA_CASE(Chara_Lisa):
            animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_BloodyLisa
    #ifdef MAP7_S03 // In M7S03 this checks for Lisa instead of BloodyLisa (while Anim_StartKeyframeIdxGet checks for BloodyLisa instead?)
        CHARA_CASE(Chara_Lisa):
    #else
        CHARA_CASE(Chara_BloodyLisa):
    #endif
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_GhostDoctor
        CHARA_CASE(Chara_GhostDoctor):
            animInfo = &GHOST_DOCTOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Incubator
        CHARA_CASE(Chara_Incubator):
            animInfo = &INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_BloodyIncubator
        CHARA_CASE(Chara_BloodyIncubator):
            animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif

#ifdef HAS_Chara_Cheryl
        CHARA_CASE(Chara_Cheryl):
            animInfo = &CHERYL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif
    }

    if (animInfo->updateFunc_0 == Anim_Update0)
    {
        if (Anim_DurationGet(chara, animInfo) > Q12(0.0f))
        {
            return chara->model_0.anim_4.keyframeIdx_8 == animInfo->endKeyframeIdx_E;
        }
        else
        {
            return chara->model_0.anim_4.keyframeIdx_8 == animInfo->startKeyframeIdx_C;
        }
    }

    if (animInfo->updateFunc_0 == Anim_Update2)
    {
        return -2;
    }

    return -1;
}

#undef CHARA_CASE
