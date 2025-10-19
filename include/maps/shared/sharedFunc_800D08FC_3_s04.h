void sharedFunc_800D08FC_3_s04(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 != 0)
    {
        return;
    }

    // TODO: This func belongs to Lisa but the animinfo is misnamed or shared with KAUFMANN in some maps.
#if defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
    animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
#else
    animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
#endif
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}
