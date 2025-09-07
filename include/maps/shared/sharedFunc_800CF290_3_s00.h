void sharedFunc_800CF290_3_s00(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHeader, coord, animInfo);
    }
}
