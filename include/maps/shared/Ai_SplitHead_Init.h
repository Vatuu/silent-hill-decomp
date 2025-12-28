void Ai_SplitHead_Init(s_SubCharacter* splitHead)
{
    s32 i;

    #define splitHeadProps splitHead->properties_E4.splitHead

    splitHead->health_B0              = 25500; // TODO: Split Head health isn't stored as Q12?
    splitHeadProps.flags_E8           = SplitHeadFlag_None;
    splitHead->model_0.anim_4.alpha_A = Q12(0.0f);
    splitHead->moveSpeed_38           = Q12(0.0f);
    splitHead->headingAngle_3C        = splitHead->rotation_24.vy;
    splitHead->field_E1_0             = 4;
    Chara_PropertiesClear(splitHead);

    splitHead->model_0.controlState_2 = 8;
    Character_AnimSet(splitHead, ANIM_STATUS(SplitHeadAnim_10, true), 162);
    ModelAnim_AnimInfoSet(&splitHead->model_0.anim_4, SPLIT_HEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;

    Chara_DamageClear(splitHead);

    splitHeadProps.field_EA = 196;
    splitHead->flags_3E    |= CharaFlag_Unk9 | CharaFlag_Unk3;

    #undef splitHeadProps
}
