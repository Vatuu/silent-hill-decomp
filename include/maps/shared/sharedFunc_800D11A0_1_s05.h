void sharedFunc_800D11A0_1_s05(s_SubCharacter* chara)
{
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;

    // TODO: Use `Math_AngleBetweenPositionsGet`.
    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy);

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(11, true))
    {
        if (distToPlayer > Q12(4.0f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(4.0f), Q12(2.4f));
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > FP_ANGLE(90.0f) ||
                distToPlayer > Q12(8.0f) ||
                (distToPlayer < Q12(3.2f) && ABS(angleDeltaToPlayer) > FP_ANGLE(22.5f)))
            {
                chara->model_0.controlState_2 = 2;
            }
            else
            {
                chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 3;
                Chara_MoveSpeedUpdate(chara, Q12(16.0f));

                if (sharedFunc_800D4530_1_s05(chara))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(3, false);
                    func_8005DC1C(Sfx_Unk1471, &chara->position_18, Q8(0.5f), 0);
                }
            }
        }

        if (TIMESTEP_ANGLE_2 < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f), Q12_SHIFT);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 10)
    {
        Chara_MoveSpeedUpdate(chara, 0x1998); // TODO

        sharedData_800D5A8C_1_s05 += g_DeltaTime0;

        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(10, true) &&
            (!Rng_TestProbabilityBits(6) || sharedData_800D5A8C_1_s05 > Q12(4.0f)))
        {
            sharedData_800D5A8C_1_s05      = 0;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
            chara->model_0.controlState_2  = 2;
        }
    }
    else
    {
        if (distToPlayer < Q12(6.4f))
        {
            Chara_MoveSpeedUpdate(chara, Q12(4.0f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, Q12(4.0f), Q12(2.4f));
        }

        if (TIMESTEP_ANGLE_1 < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(15.0f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(15.0f), Q12_SHIFT);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
}
