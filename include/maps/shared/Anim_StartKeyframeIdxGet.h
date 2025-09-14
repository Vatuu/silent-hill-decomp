s16 Anim_StartKeyframeIdxGet(s_SubCharacter* chara)
{
    // TODO: Not sure if any of these match `KAUFMANN_ANIM_INFOS` in other maps.
#if defined(MAP6_S01)
    extern s_AnimInfo CYBIL_ANIM_INFOS[];
    extern s_AnimInfo D_800D39A0[];
#elif defined(MAP6_S04)
    extern s_AnimInfo D_800EA718[];
    extern s_AnimInfo D_800EAB38[];
#elif defined(MAP7_S01)
    extern s_AnimInfo D_800DFC78[];
    extern s_AnimInfo D_800DFD98[];
#elif defined(MAP7_S02)
    extern s_AnimInfo D_800E7708[];
    extern s_AnimInfo D_800E7B68[];
    extern s_AnimInfo D_800E7EA8[];
#elif defined(MAP7_S03)
    extern s_AnimInfo D_800EA1E0[];
    extern s_AnimInfo D_800EA5E0[];
    extern s_AnimInfo D_800EAA80[];
    extern s_AnimInfo D_800EAC00[]; // Incubator.
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
            animInfo = &D_800EA718[chara->model_0.anim_4.status_0];
            break;

        case Chara_Dahlia:
            animInfo = &D_800EAB38[chara->model_0.anim_4.status_0];
            break;

        case Chara_Alessa:
            animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S01)
        case Chara_GhostChildAlessa:
            animInfo = &D_800DFC78[chara->model_0.anim_4.status_0];
            break;

        case Chara_Lisa:
            animInfo = &D_800DFD98[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyLisa:
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S02)
        case Chara_Dahlia:
            animInfo = &D_800E7B68[chara->model_0.anim_4.status_0];
            break;

        case Chara_GhostChildAlessa:
            animInfo = &D_800E7EA8[chara->model_0.anim_4.status_0];
            break;

        case Chara_Kaufmann:
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

        case Chara_Lisa:
            animInfo = &D_800E7708[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyLisa:
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;

#elif defined(MAP7_S03)
        case Chara_Cybil:
        case Chara_EndingCybil:
            animInfo = &D_800EA1E0[chara->model_0.anim_4.status_0];
            break;

        case Chara_Dahlia:
        case Chara_EndingDahlia:
            animInfo = &D_800EA5E0[chara->model_0.anim_4.status_0];
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
            animInfo = &D_800EAC00[chara->model_0.anim_4.status_0];
            break;

        case Chara_BloodyIncubator:
            animInfo = &D_800EAA80[chara->model_0.anim_4.status_0];
            break;

#else
        default:
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
            break;
#endif
    }

    return animInfo->startKeyframeIdx_C;
}
