void Ai_HangedScratcher_Control_9(s_SubCharacter* scratcher)
{
    s_Collision coll;

    #define scratcherProps scratcher->properties_E4.hangedScratcher

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_14 &&
        scratcher->moveSpeed_38 == Q12(0.0f))
    {
        Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
        if (scratcher->health_B0 > Q12(100.0f) || coll.field_8 == 7)
        {
            if (scratcherProps.flags_E8 & HangedScratcherFlag_1)
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_8;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_16, false);
            }
            else if (!Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_3;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_17, false);
            }
        }
        else
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_11;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_10, false);
        }
    }

    #undef scratcherProps1
}
