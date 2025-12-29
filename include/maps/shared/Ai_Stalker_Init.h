void Ai_Stalker_Init(s_SubCharacter* stalker)
{
    s32 i;

    #define stalkerProps stalker->properties_E4.stalker

    stalkerProps.flags_E8 = StalkerFlag_None;
    Chara_PropertiesClear(stalker);
    stalker->health_B0 = sharedData_800E3A20_0_s00;

#ifdef MAP6_S03
    // Set health to 1.5x when not on easy difficulty.
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        stalker->health_B0 = FP_MULTIPLY_FLOAT_PRECISE(sharedData_800E3A20_0_s00, 1.5f, Q12_SHIFT);
    }
#endif

    stalker->moveSpeed_38   = Q12(0.0f);
    stalker->field_34       = 0;
    stalker->rotation_24.vz = 0;
    stalker->rotation_24.vx = 0;
    //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_30, true), 447); // TODO: Doesn't match?
    stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_30, true);
    stalker->model_0.anim_4.time_4        = Q12(477.0f);
    stalker->model_0.anim_4.keyframeIdx_8 = 477;
    stalker->headingAngle_3C              = stalker->rotation_24.vy;

    switch (stalker->model_0.stateStep_3)
    {
        case 11:
            stalkerProps.flags_E8 |= StalkerFlag_2;

        case 3:
            stalkerProps.timer_F8  = Q12(2.5f);
            stalkerProps.flags_E8 |= StalkerFlag_0;

        case 8:
            stalker->model_0.controlState_2 = StalkerControl_4;
            stalker->field_E1_0      = 3;
            break;

        case 7:
            stalker->model_0.controlState_2 = StalkerControl_4;
            stalkerProps.flags_E8   |= StalkerFlag_11;
            stalker->field_E1_0      = 3;
            break;

        case 6:
            stalker->model_0.controlState_2 = StalkerControl_2;
            stalker->flags_3E       |= CharaFlag_Unk3;
            stalkerProps.timer_F8    = Q12(1.0f);
            stalkerProps.flags_E8   |= StalkerFlag_0 | StalkerFlag_1;
            stalker->field_E1_0      = 3;
            stalker->flags_3E       &= ~CharaFlag_Unk5;
            break;

        case 5:
            stalker->model_0.controlState_2 = StalkerControl_1;
            stalker->field_E1_0      = 0;
            stalker->flags_3E       |= CharaFlag_Unk5;
            break;

        case 9:
            stalker->model_0.controlState_2              = StalkerControl_12;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_27, true), 427); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_27, true);
            stalker->model_0.anim_4.time_4        = Q12(427.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 427;
            stalkerProps.flags_E8                |= StalkerFlag_0;
            stalker->field_E1_0                   = 3;
            break;

        case 10:
            stalker->model_0.controlState_2              = StalkerControl_11;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_28, true), 442); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_28, true);
            stalker->model_0.anim_4.time_4        = Q12(443.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 443;
            stalker->field_E1_0                   = 3;
            break;

        case 17:
            stalker->model_0.controlState_2              = StalkerControl_13;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_14, true), 176); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_14, true);
            stalker->model_0.anim_4.time_4        = Q12(176.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 176;
            stalker->field_E1_0                   = 0;
            break;
    }

    stalker->model_0.stateStep_3    = 0;
    stalkerProps.sfxId_102          = NO_VALUE;
    stalkerProps.targetPositionX_F0 = stalker->position_18.vx;
    stalkerProps.targetPositionZ_F4 = stalker->position_18.vz;
    stalkerProps.health_110         = stalker->health_B0;

    ModelAnim_AnimInfoSet(&stalker->model_0.anim_4, STALKER_ANIM_INFOS);
    Chara_DamageClear(stalker);

#ifdef MAP6_S03
    stalker->flags_3E |= CharaFlag_Unk9;
#endif

    #undef stalkerProps
}
