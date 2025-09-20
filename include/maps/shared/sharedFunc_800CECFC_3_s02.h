void sharedFunc_800CECFC_3_s02(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord)
{
    if (chara->properties_E4.player.field_F0 == 0)
    {
        s_AnimInfo* animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coord, animInfo);
    }
}
