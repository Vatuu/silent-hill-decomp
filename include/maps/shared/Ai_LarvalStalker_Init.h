void Ai_LarvalStalker_Init(s_SubCharacter* larvalStalker)
{
    s32 i;

    #define larvalStalkerProps larvalStalker->properties_E4.larvalStalker

    larvalStalker->model_0.controlState_2              = 3;
    larvalStalker->model_0.anim_4.time_4        = 0;
    larvalStalker->model_0.anim_4.status_0      = ANIM_STATUS(LarvalStalkerAnim_10, false);
    larvalStalker->model_0.anim_4.time_4        = Q12(162.0f);
    larvalStalker->model_0.anim_4.keyframeIdx_8 = 162;

    larvalStalkerProps.flags_E8 = LarvalStalkerFlag_None;
    larvalStalker->model_0.anim_4.alpha_A = Q12(0.0f);
    larvalStalker->model_0.stateStep_3    = 0;
    ModelAnim_AnimInfoSet(&larvalStalker->model_0.anim_4, LARVAL_STALKER_ANIM_INFOS);

    larvalStalker->health_B0    = Q12(300.0f);
    larvalStalker->field_34     = 0;
    larvalStalker->moveSpeed_38 = 0;

    Chara_DamageClear(larvalStalker);
    larvalStalker->field_E1_0      = 0;
    larvalStalker->headingAngle_3C = larvalStalker->rotation_24.vy;

    Chara_PropertiesClear(larvalStalker);
    larvalStalkerProps.targetPositionX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    larvalStalkerProps.targetPositionZ = g_SysWork.playerWork_4C.player_0.position_18.vz;

    #undef larvalStalkerProps
}
