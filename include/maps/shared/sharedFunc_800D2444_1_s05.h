void sharedFunc_800D2444_1_s05(s_SubCharacter* splitHead)
{
    q3_12 angleDeltaToPlayer;

    if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_9)
    {
        Chara_MoveSpeedUpdate3(splitHead, Q12(0.8f), Q12(-1.2f));

        angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                           splitHead->rotation_24.vy);
        if (TIMESTEP_ANGLE_2 < ABS(angleDeltaToPlayer)) // @hack `(g_DeltaTime0 / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                splitHead->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_4;
    }
}
