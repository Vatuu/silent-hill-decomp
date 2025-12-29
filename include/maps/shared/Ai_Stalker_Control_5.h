void Ai_Stalker_Control_5(s_SubCharacter* stalker)
{
    #define DIST_TO_PLAYER_MAX Q12(0.9f)
    #define MOVE_SPEED_MAX     Q12(0.7f)

    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    q19_12 angle1;
    q19_12 newMoveSpeed0;
    s32    i;
    q19_12 newMoveSpeed1;

    #define stalkerProps stalker->properties_E4.stalker

    if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == StalkerAnim_30)
    {
        stalker->model_0.controlState_2 = StalkerControl_4;
        g_SysWork.field_2284[3] &= ~(1 << 1);
        return;
    }

    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 62, 64))
    {
        stalker->moveSpeed_38 = Q12(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 50, 61))
    {
        distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                           g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        for (i = 0; i < 6; i++)
        {
            angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                               stalker->rotation_24.vy);
            angle1 = TIMESTEP_ANGLE_2; // @hack `(g_DeltaTime0 / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?
            if ((angleDeltaToPlayer >= FP_ANGLE(0.0f) && angle1 <  angleDeltaToPlayer) ||
                (angleDeltaToPlayer <  FP_ANGLE(0.0f) && angle1 < -angleDeltaToPlayer))
            {
                if (angleDeltaToPlayer > FP_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.0833f, Q12_SHIFT) + stalker->rotation_24.vy;
                }
                else
                {
                    stalker->rotation_24.vy = stalker->rotation_24.vy - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.0833f, Q12_SHIFT);
                }
            }
        }

        if (!(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            if (distToPlayer > DIST_TO_PLAYER_MAX)
            {
                if (stalker->moveSpeed_38 > MOVE_SPEED_MAX)
                {
                    newMoveSpeed0 = stalker->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = MOVE_SPEED_MAX;
                    }
                }
                else
                {
                    newMoveSpeed0 = MOVE_SPEED_MAX;
                    newMoveSpeed1 = stalker->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed1 <= MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = newMoveSpeed1;
                    }
                }

                stalker->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            if (distToPlayer < MOVE_SPEED_MAX)
            {
                if (stalker->moveSpeed_38 > -MOVE_SPEED_MAX)
                {
                    newMoveSpeed0 = stalker->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed0 < -MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = -MOVE_SPEED_MAX;
                    }
                }
                else
                {
                    newMoveSpeed0 = -MOVE_SPEED_MAX;
                    newMoveSpeed1 = stalker->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.0f, Q12_SHIFT);
                    if (newMoveSpeed1 <= -MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = newMoveSpeed1;
                    }
                }

                stalker->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            Chara_MoveSpeedUpdate(stalker, Q12(6.0f));
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(stalker, Q12(6.0f));
    }

    #undef stalkerProps
}
