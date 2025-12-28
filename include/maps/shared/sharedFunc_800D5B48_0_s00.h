void sharedFunc_800D5B48_0_s00(s_SubCharacter* stalker)
{
    u16 flags;

    #define stalkerProps stalker->properties_E4.stalker

    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_27, true) &&
        !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        flags = stalkerProps.flags_E8;
        if (!(flags & StalkerFlag_13))
        {
            stalker->model_0.state_2         = (flags & StalkerFlag_1) ? 2 : 3;
            stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);
            stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_27, true);
            stalkerProps.relKeyframeIdx_FE   = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
        }
    }

    #undef stalkerProps
}
