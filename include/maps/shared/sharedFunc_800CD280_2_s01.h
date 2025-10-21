void sharedFunc_800CD280_2_s01(s_SubCharacter* arg0, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
#if defined(MAP2_S01) || defined(MAP3_S06)
    #define ANIM_INFO_OBJ KAUFMANN_ANIM_INFOS
    extern s_AnimInfo KAUFMANN_ANIM_INFOS[];
#elif defined(MAP6_S01)
    #define ANIM_INFO_OBJ D_800D39A0
    extern s_AnimInfo D_800D39A0[];
#else
    #define ANIM_INFO_OBJ DAHLIA_ANIM_INFOS
    extern s_AnimInfo DAHLIA_ANIM_INFOS[];
#endif

    s_AnimInfo* animInfo;

    if (!arg0->properties_E4.player.field_F0)
    {
        animInfo = &ANIM_INFO_OBJ[arg0->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&arg0->model_0, arg1, arg2, animInfo);
    }
}
