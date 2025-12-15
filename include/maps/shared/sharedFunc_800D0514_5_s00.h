void sharedFunc_800D0514_5_s00(s_SubCharacter* chara)
{
    q19_12 dist;

    dist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    Chara_MoveSpeedUpdate(chara, Q12(4.0f));

    if (dist < Q12(5.0f) || (dist < Q12(20.0f) && Rng_Rand16() == 0))
    {
        chara->model_0.state_2         = 3;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    }
}
