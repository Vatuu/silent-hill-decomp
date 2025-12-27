void sharedFunc_800D5B48_0_s00(s_SubCharacter* stalker)
{
    u16 flags;

    if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_27, true) &&
        !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        flags = stalker->properties_E4.stalker.flags_E8;
        if (!(flags & StalkerFlag_13))
        {
            stalker->model_0.state_2                         = (flags & StalkerFlag_1) ? 2 : 3;
            stalker->model_0.anim_4.status_0                 = ANIM_STATUS(StalkerAnim_30, false);
            stalker->properties_E4.stalker.keyframeIdx_FC    = ANIM_STATUS(StalkerAnim_27, true);
            stalker->properties_E4.stalker.relKeyframeIdx_FE = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
        }
    }
}
