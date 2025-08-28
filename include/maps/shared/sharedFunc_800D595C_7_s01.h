void sharedFunc_800D595C_7_s01(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &sharedData_800DFFD8_7_s01[chara->model_0.anim_4.status_0];
        animInfo->funcPtr_0(chara, arg1, coord, animInfo);
    }
}
