void sharedFunc_800D2444_1_s05(s_SubCharacter* splithead)
{
    s16 temp_v0;

    if (ANIM_STATUS_IDX_GET(splithead->model_0.anim_4.status_0) == SplitheadAnim_Unk9)
    {
        Chara_MoveSpeedUpdate3(splithead, Q12(0.8f), Q12(-1.2f));

        temp_v0 = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - splithead->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - splithead->position_18.vz) -
                                splithead->rotation_24.vy);

        if (((g_DeltaTime0 / 3) >> 3) + 1 < ABS(temp_v0)) // @hack `(g_DeltaTime0 / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?
        {
            if (temp_v0 > 0)
            {
                splithead->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                splithead->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }
        else
        {
            splithead->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - splithead->position_18.vx,
                                               g_SysWork.playerWork_4C.player_0.position_18.vz - splithead->position_18.vz);
        }
    }
    else
    {
        splithead->model_0.state_2 = 4;
    }
}
