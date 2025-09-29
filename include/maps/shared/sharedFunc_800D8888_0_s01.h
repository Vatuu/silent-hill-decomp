void sharedFunc_800D8888_0_s01(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
    #if defined(MAP6_S01) || defined(MAP7_S03)
        animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
    #else
        animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
    #endif
        animInfo->updateFunc_0(&chara->model_0, animHdr, coord, animInfo);
    }
}
