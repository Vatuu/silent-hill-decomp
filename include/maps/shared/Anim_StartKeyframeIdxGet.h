s16 Anim_StartKeyframeIdxGet(s_SubCharacter* chara)
{
    // TODO: Not sure if any of these match `KAUFMANN_ANIM_INFOS` in other maps.
#if defined(MAP6_S01)
    extern s_AnimInfo CYBIL_ANIM_INFOS[];
    extern s_AnimInfo D_800D39A0[];
#elif defined(MAP6_S04)
    extern s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[];
    extern s_AnimInfo DAHLIA_ANIM_INFOS[];
#elif defined(MAP7_S01)
    extern s_AnimInfo GHOST_CHILD_ALESSA_ANIM_INFOS[];
    extern s_AnimInfo LISA_ANIM_INFOS[];
#elif defined(MAP7_S02)
    extern s_AnimInfo LISA_ANIM_INFOS[];
    extern s_AnimInfo DAHLIA_ANIM_INFOS[];
    extern s_AnimInfo GHOST_CHILD_ALESSA_ANIM_INFOS[];
#elif defined(MAP7_S03)
    extern s_AnimInfo CYBIL_ANIM_INFOS[];
    extern s_AnimInfo DAHLIA_ANIM_INFOS[];
    extern s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[];
    extern s_AnimInfo INCUBATOR_ANIM_INFOS[];
#endif

    s_AnimInfo* animInfo = NULL;

    switch (chara->model_0.charaId_0)
    {
#if defined(MAP3_S02) || defined(MAP5_S02) || defined(MAP5_S03) || defined(MAP6_S02)
        // `animInfo` left as `NULL`.
#elif defined(MAP6_S01)
        case Chara_Cybil:
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        default:
            animInfo = &D_800D39A0[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP6_S04)
        case Chara_MonsterCybil:
            animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Dahlia:
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Alessa:
            animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S01)
        case Chara_GhostChildAlessa:
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Lisa:
            animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyLisa:
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S02)
        case Chara_Dahlia:
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_GhostChildAlessa:
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Kaufmann:
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Lisa:
            animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyLisa:
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S03)
        case Chara_Cybil:
        case Chara_EndingCybil:
            animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Dahlia:
        case Chara_EndingDahlia:
            animInfo = &DAHLIA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Alessa:
            animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Kaufmann:
        case Chara_EndingKaufmann:
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyLisa:
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Incubator:
            animInfo = &INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyIncubator:
            animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#else
        default:
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif
    }

    return animInfo->startKeyframeIdx_C;
}
