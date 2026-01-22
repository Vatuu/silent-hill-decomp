void Ai_HangedScratcher_Control_2(s_SubCharacter* chara)
{
    q19_12 distToPlayer;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    Chara_MoveSpeedUpdate(chara, Q12(4.0f));

    if (distToPlayer < Q12(5.0f) || (distToPlayer < Q12(20.0f) && Rng_Rand16() == 0))
    {
        chara->model_0.controlState_2         = HangedScratcherControl_3;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_17, false);
    }
}
