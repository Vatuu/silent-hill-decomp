void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara)
#ifdef SHARED_FUNC_IMPL
{
    s32 moveSpeed;
    s32 newMoveSpeed;
    u16 flags;

    if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 13)))
    {
        moveSpeed = chara->moveSpeed_38;
        if (moveSpeed > 0)
        {
            newMoveSpeed = moveSpeed - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed < 0)
            {
                newMoveSpeed = 0;
            }
        }
        else
        {
            newMoveSpeed = moveSpeed + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed > 0)
            {
                newMoveSpeed = 0;
            }
        }
        chara->moveSpeed_38 = newMoveSpeed;
    }

    if ((chara->model_0.anim_4.animIdx_0 == 0x37) && (Rng_Rand16() % 4) == 0)
    {
        flags = chara->properties_E4.larvalStalker.properties_E8[0].val16[0];
        if (!(flags & (1 << 13)))
        {
            chara->model_0.state_2                                       = (flags & (1 << 1)) ? 2 : 3;
            chara->model_0.anim_4.animIdx_0                              = 60;
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 55;
            chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 427;
        }
    }
}
#else
;
#endif
