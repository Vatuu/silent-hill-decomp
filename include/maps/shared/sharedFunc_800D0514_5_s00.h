void sharedFunc_800D0514_5_s00(s_SubCharacter* subChar)
{
    s32 dx;
    s32 dz;
    s32 dist;

    dx   = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - subChar->position_18.vx);
    dz   = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz - subChar->position_18.vz);
    dist = Q6_TO_Q12(SquareRoot0(SQUARE(dx) + SQUARE(dz)));
    Chara_MoveSpeedUpdate(subChar, Q12(4.0));

    if (dist < Q12(5) || (dist < Q12(20) && Rng_Rand16() == 0))
    {
        subChar->model_0.state_2         = 3;
        subChar->model_0.anim_4.status_0 = ANIM_STATUS(17, false); // 17 << 1 | 0 = 34
    }
}