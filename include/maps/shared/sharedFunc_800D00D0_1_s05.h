void sharedFunc_800D00D0_1_s05(s_SubCharacter* chara)
{
    VECTOR unkPos;
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    
    // TODO: Use `Math_AngleBetweenPositionsGet`.
    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                              g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                       chara->rotation_24.vy);
    if (chara->model_0.anim_4.status_0 == 23)
    {
        if (distToPlayer > Q12(3.5f))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(2.4f), Q12(2.4f));
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > FP_ANGLE(90.0f) || distToPlayer > Q12(5.0f))
            {
                chara->model_0.controlState_2 = 5;
            }
            else
            {
                chara->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 3;
                Chara_MoveSpeedUpdate(chara, Q12(4.8f));

                if (sharedFunc_800D4530_1_s05(chara) != false)
                {
                    chara->model_0.anim_4.status_0 = 4;
                    func_8005DC1C(Sfx_Unk1475, &chara->position_18, Q8(0.5f), 0);
                }
            }
        }

        if (TIMESTEP_ANGLE_0 < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(2, false))
    {
        Chara_MoveSpeedUpdate(chara, Q12(4.8f));
    }
    else if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == ANIM_STATUS(5, false))
    {
        Chara_MoveSpeedUpdate(chara, Q12(4.8f));

        if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 6))
        {
            chara->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 6);

            if (!(Rng_Rand16() & 0x3))
            {
                chara->model_0.controlState_2  = 7;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
            }
            else
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(4, false);
            }
        }
        else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(10, true) && !Rng_TestProbabilityBits(5))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
            chara->model_0.controlState_2  = 5;
        }
    }
    else if (chara->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))
    {
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(2, true))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(14, false);
        }

        Chara_MoveSpeedUpdate3(chara, Q12(1.2f), Q12(0.0f));

        if (TIMESTEP_ANGLE_1 < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(14.95f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(14.95f), Q12_SHIFT);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }

        if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) == 35)
        {
            unkPos.vx = (g_SysWork.playerWork_4C.player_0.position_18.vx + Rng_TestProbabilityBits(10)) - Q12(0.25f);
            unkPos.vy = (g_SysWork.playerWork_4C.player_0.position_18.vy - Rng_TestProbabilityBits(11)) - Q12(1.0f);
            unkPos.vz = (g_SysWork.playerWork_4C.player_0.position_18.vz + Rng_TestProbabilityBits(10)) - Q12(0.25f);
            func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &unkPos, 2, 7);
        }
    }
    else
    {
        if (distToPlayer < Q12(2.8f))
        {
            Chara_MoveSpeedUpdate(chara, Q12(1.2f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(chara, Q12(1.2f), Q12(0.6f));
        }

        if (TIMESTEP_ANGLE_1 < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > FP_ANGLE(0.0f))
            {
                chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(14.95f), Q12_SHIFT);
            }
            else
            {
                chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(14.95f), Q12_SHIFT);
            }
        }
        else
        {
            chara->rotation_24.vy = Math_AngleBetweenPositionsGet(chara->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
}
