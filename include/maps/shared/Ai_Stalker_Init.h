void Ai_Stalker_Init(s_SubCharacter* chara)
{
    s32 i;

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->health_B0 = sharedData_800E3A20_0_s00;

#ifdef MAP6_S03
    // Change stalker health to 1.5x when not on easy difficulty.
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        chara->health_B0 = FP_MULTIPLY_FLOAT_PRECISE(sharedData_800E3A20_0_s00, 1.5f, Q12_SHIFT);
    }
#endif

    chara->moveSpeed_38   = Q12(0.0f);
    chara->field_34       = 0;
    chara->rotation_24.vz = 0;
    chara->rotation_24.vx = 0;
    //Character_AnimSet(chara, ANIM_STATUS(StalkerAnim_Unk30, true), 447); // TODO: Doesn't match?
    chara->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_Unk30, true);
    chara->model_0.anim_4.time_4        = Q12(477.0f);
    chara->model_0.anim_4.keyframeIdx_8 = 477;
    chara->headingAngle_3C = chara->rotation_24.vy;

    switch (chara->model_0.stateStep_3)
    {
        case 11:
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 2;

        case 3:
            chara->properties_E4.larvalStalker.properties_E8[4].val32     = Q12(2.5f);
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 0;

        case 8:
            chara->model_0.state_2 = 4;
            chara->field_E1_0      = 3;
            break;

        case 7:
            chara->model_0.state_2                                        = 4;
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 11;
            chara->field_E1_0                                             = 3;
            break;

        case 6:
            chara->model_0.state_2                                        = 2;
            chara->flags_3E                                              |= CharaFlag_Unk3;
            chara->properties_E4.larvalStalker.properties_E8[4].val32     = Q12(1.0f);
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 0) | (1 << 1);
            chara->field_E1_0                                             = 3;
            chara->flags_3E                                              &= ~CharaFlag_Unk5;
            break;

        case 5:
            chara->model_0.state_2 = 1;
            chara->field_E1_0      = 0;
            chara->flags_3E       |= CharaFlag_Unk5;
            break;

        case 9:
            chara->model_0.state_2              = 12;
            //Character_AnimSet(chara, ANIM_STATUS(StalkerAnim_Unk27, true), 427); // TODO: Doesn't match?
            chara->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_Unk27, true);
            chara->model_0.anim_4.time_4        = Q12(427.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 427;
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 0;
            chara->field_E1_0                                             = 3;
            break;

        case 10:
            chara->model_0.state_2              = 11;
            //Character_AnimSet(chara, ANIM_STATUS(StalkerAnim_Unk28, true), 442); // TODO: Doesn't match?
            chara->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_Unk28, true);
            chara->model_0.anim_4.time_4        = Q12(443.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 443;
            chara->field_E1_0                   = 3;
            break;

        case 17:
            chara->model_0.state_2              = 13;
            //Character_AnimSet(chara, ANIM_STATUS(StalkerAnim_Unk14, true), 176); // TODO: Doesn't match?
            chara->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_Unk14, true);
            chara->model_0.anim_4.time_4        = Q12(176.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 176;
            chara->field_E1_0                   = 0;
            break;
    }

    chara->model_0.stateStep_3 = 0;

    chara->properties_E4.larvalStalker.properties_E8[6].val16[1] = NO_VALUE;
    chara->properties_E4.larvalStalker.properties_E8[2].val32    = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[3].val32    = chara->position_18.vz;
    chara->properties_E4.larvalStalker.properties_E8[10].val32   = chara->health_B0;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, STALKER_ANIM_INFOS);

    Chara_DamageClear(chara);

#ifdef MAP6_S03
    chara->flags_3E |= CharaFlag_Unk9;
#endif
}
