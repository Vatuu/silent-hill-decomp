void Ai_HangedScratcher_Control_6(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    u16    temp_v1;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcherProps.timer_EA == Q12(0.0f) &&
        scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_15, true))
    {
        if (distToPlayer < Q12(12.0f) && !Rng_GenerateInt(0, 127)) // 1 in 128 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
        else if (distToPlayer < Q12(6.0f) && !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
    }

    // @bug Weird function pointer check, code will never run?
    if (&sharedFunc_800D3214_5_s00 == NULL && distToPlayer > Q12(24.0f))
    {
        scratcher->model_0.controlState_2 = HangedScratcherControl_None;
        scratcher->model_0.stateStep_3    = 3;
    }

    temp_v1                                           = scratcherProps.timer_EA;
    scratcherProps.timer_EA = MAX(Q12(0.0f), temp_v1 - g_DeltaTime0);

    #undef scratcherProps
}
