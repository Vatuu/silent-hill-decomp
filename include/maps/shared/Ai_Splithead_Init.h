void Ai_Splithead_Init(s_SubCharacter* splitHead)
{
    s32 i;

    splitHead->health_B0                        = 25500; // TODO: Splithead health isn't stored as Q12?
    splitHead->properties_E4.splithead.flags_E8 = 0;
    splitHead->model_0.anim_4.alpha_A           = Q12(0.0f);
    splitHead->moveSpeed_38                     = 0;
    splitHead->headingAngle_3C                  = splitHead->rotation_24.vy;
    splitHead->field_E1_0                       = 4;

    for (i = 0; i < 16; i++)
    {
        splitHead->properties_E4.dummy.properties_E8[i].val32 = 0;
    }

    splitHead->model_0.state_2 = 8;
    Character_AnimSet(splitHead, ANIM_STATUS(SplitHeadAnim_Unk10, true), 162);
    ModelAnim_AnimInfoSet(&splitHead->model_0.anim_4, SPLITHEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;

    Chara_DamageClear(splitHead);

    *(u8*)&splitHead->properties_E4.dummy.properties_E8[0].val8[2] = 196;

    splitHead->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}
