void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara)
{
    u16 flags;

    if (!(chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)))
    {
        Chara_MoveSpeedUpdate(chara, Q12(1.5f));
    }

    // 25% chance.
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(27, true) &&
        !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        flags = chara->properties_E4.dummy.properties_E8[0].val16[0];
        if (!(flags & (1 << 13)))
        {
            chara->model_0.state_2                                       = (flags & (1 << 1)) ? 2 : 3;
            chara->model_0.anim_4.status_0                               = ANIM_STATUS(30, false);
            chara->properties_E4.dummy.properties_E8[5].val16[0] = ANIM_STATUS(27, true); // TODO: Maybe anim status.
            chara->properties_E4.dummy.properties_E8[5].val16[1] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 427;
        }
    }
}
