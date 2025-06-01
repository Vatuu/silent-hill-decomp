s16 sharedFunc_800D921C_0_s00(s_SubCharacter* chara)
{
    // TODO: Not sure if any of these match sharedData_800DF174_0_s00 in other maps.
#if defined(MAP6_S01)
    extern s_AnimInfo D_800D35A0[];
    extern s_AnimInfo D_800D39A0[];
#elif defined(MAP6_S04)
    extern s_AnimInfo D_800EA718[];
    extern s_AnimInfo D_800EA9D8[];
    extern s_AnimInfo D_800EAB38[];
#elif defined(MAP7_S01)
    extern s_AnimInfo D_800DFC78[];
    extern s_AnimInfo D_800DFD98[];
    extern s_AnimInfo D_800DFFD8[];
#elif defined(MAP7_S02)
    extern s_AnimInfo D_800E7708[];
    extern s_AnimInfo D_800E7948[];
    extern s_AnimInfo D_800E7B68[];
    extern s_AnimInfo D_800E7EA8[];
    extern s_AnimInfo D_800E7FC8[];
#elif defined(MAP7_S03)
    extern s_AnimInfo D_800EA1E0[];
    extern s_AnimInfo D_800EA5E0[];
    extern s_AnimInfo D_800EA920[];
    extern s_AnimInfo D_800EAA80[];
    extern s_AnimInfo D_800EAC00[];
    extern s_AnimInfo D_800EAC80[];
    extern s_AnimInfo D_800EAF60[];
#endif

    s_AnimInfo* animInfo = NULL;
    switch (chara->model_0.charaId_0)
    {
#if defined(MAP3_S02) || defined(MAP5_S02) || defined(MAP5_S03) || defined(MAP6_S02)
        // animInfo left as NULL.
#elif defined(MAP6_S01)
        case 0x1A:
            animInfo = &D_800D35A0[chara->model_0.anim_4.animIdx_0];
            break;
        default:
            animInfo = &D_800D39A0[chara->model_0.anim_4.animIdx_0];
            break;
#elif defined(MAP6_S04)
        case 24:
            animInfo = &D_800EA718[chara->model_0.anim_4.animIdx_0];
            break;
        case 30:
            animInfo = &D_800EAB38[chara->model_0.anim_4.animIdx_0];
            break;
        case 34:
            animInfo = &D_800EA9D8[chara->model_0.anim_4.animIdx_0];
            break;
#elif defined(MAP7_S01)
        case 35:
            animInfo = &D_800DFC78[chara->model_0.anim_4.animIdx_0];
            break;
        case 32:
            animInfo = &D_800DFD98[chara->model_0.anim_4.animIdx_0];
            break;
        case 33:
            animInfo = &D_800DFFD8[chara->model_0.anim_4.animIdx_0];
            break;
#elif defined(MAP7_S02)
        case 30:
            animInfo = &D_800E7B68[chara->model_0.anim_4.animIdx_0];
            break;
        case 35:
            animInfo = &D_800E7EA8[chara->model_0.anim_4.animIdx_0];
            break;
        case 38:
            animInfo = &D_800E7FC8[chara->model_0.anim_4.animIdx_0];
            break;
        case 32:
            animInfo = &D_800E7708[chara->model_0.anim_4.animIdx_0];
            break;
        case 33:
            animInfo = &D_800E7948[chara->model_0.anim_4.animIdx_0];
            break;
#elif defined(MAP7_S03)
        case 0x1A:
        case 0x1B:
            animInfo = &D_800EA1E0[arg0->model_0.anim_4.animIdx_0];
            break;
        case 30:
        case 31:
            animInfo = &D_800EA5E0[arg0->model_0.anim_4.animIdx_0];
            break;
        case 34:
            animInfo = &D_800EA920[arg0->model_0.anim_4.animIdx_0];
            break;
        case 38:
        case 39:
            animInfo = &D_800EAC80[arg0->model_0.anim_4.animIdx_0];
            break;
        case 33:
            animInfo = &D_800EAF60[arg0->model_0.anim_4.animIdx_0];
            break;
        case 36:
            animInfo = &D_800EAC00[arg0->model_0.anim_4.animIdx_0];
            break;
        case 37:
            animInfo = &D_800EAA80[arg0->model_0.anim_4.animIdx_0];
            break;
#else
        default:
            animInfo = &sharedData_800DF174_0_s00[chara->model_0.anim_4.animIdx_0];
            break;
#endif
    }
    return animInfo->keyframeIdx0_C;
}
