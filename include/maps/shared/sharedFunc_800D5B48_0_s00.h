void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara)
{
    s32 moveSpeed;
    s32 newMoveSpeed;
    u16 flags;

    if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 13)))
    {
        moveSpeed = chara->moveSpeed_38;
        if (moveSpeed > 0)
        {
            newMoveSpeed = moveSpeed - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed < 0)
            {
                newMoveSpeed = 0;
            }
        }
        else
        {
            newMoveSpeed = moveSpeed + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed > 0)
            {
                newMoveSpeed = 0;
            }
        }
        chara->moveSpeed_38 = newMoveSpeed;
    }

    // 25% chance.
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS_GET(27, true) &&
        !Rng_GenerateInt(Rng_Rand16(), 0, 3))
    {
        flags = chara->properties_E4.larvalStalker.properties_E8[0].val16[0];
        if (!(flags & (1 << 13)))
        {
            chara->model_0.state_2                                       = (flags & (1 << 1)) ? 2 : 3;
            chara->model_0.anim_4.status_0                              = ANIM_STATUS_GET(30, false);
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = ANIM_STATUS_GET(27, true); // TODO: Maybe anim status.
            chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 427;
        }
    }
}
