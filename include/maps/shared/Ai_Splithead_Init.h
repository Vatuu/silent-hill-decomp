void Ai_Splithead_Init(s_SubCharacter* splithead)
{
    s32 i;

    splithead->health_B0                                             = Q12(6.2256f);
    splithead->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;
    splithead->model_0.anim_4.alpha_A                                = Q12(0.0f);
    splithead->moveSpeed_38                                          = 0;
    splithead->headingAngle_3C                                       = splithead->rotation_24.vy;
    splithead->field_E1_0                                            = 4;

    for (i = 0; i < 16; i++)
    {
        splithead->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    splithead->model_0.state_2 = 8;
    Character_AnimSet(splithead, ANIM_STATUS(SplitheadAnim_Unk10, true), 162);
    ModelAnim_AnimInfoSet(&splithead->model_0.anim_4, SPLITHEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;

    Chara_DamageClear(splithead);

    *(u8*)&splithead->properties_E4.larvalStalker.properties_E8[0].val8[2] = 196;

    splithead->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}
