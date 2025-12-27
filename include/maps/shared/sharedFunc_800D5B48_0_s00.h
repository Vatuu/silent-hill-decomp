void sharedFunc_800D5B48_0_s00(s_SubCharacter* stalker)
{
    u16 flags;

    if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    // 25% chance.
    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(27, true) &&
        !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        flags = stalker->properties_E4.dummy.properties_E8[0].val16[0];
        if (!(flags & (1 << 13)))
        {
            stalker->model_0.state_2                                       = (flags & (1 << 1)) ? 2 : 3;
            stalker->model_0.anim_4.status_0                               = ANIM_STATUS(30, false);
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(27, true); // TODO: Maybe anim status.
            stalker->properties_E4.dummy.properties_E8[5].val16[1] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 427;
        }
    }
}
