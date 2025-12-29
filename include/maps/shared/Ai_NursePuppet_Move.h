static void inline GetNewSpeed(s_SubCharacter* nurse, q19_12 dist)
{
    q19_12 limit;

    if (dist > Q12(0.0f))
    {
        limit = 0;
    }
    else
    {
        limit = Q12(-0.02f);
    }

    Chara_MoveSpeedUpdate2(nurse, Q12(4.0f), limit);
}

void Ai_NursePuppet_Move(s_SubCharacter* nurse)
{
    q3_12  angleDeltaToPlayer;
    q3_12  tmpAngle;
    q3_12  absAngle;
    q19_12 distToPlayer;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 addAngle;
    q19_12 distAbs;

    // TODO: Doesn't match?
    //distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx,
    //                                         g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz);
    deltaX             = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx);
    deltaZ             = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz);
    distToPlayer       = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ))) - Q12(0.76f);
    distAbs            = ABS(distToPlayer);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(nurse->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       nurse->rotation_24.vy);
    absAngle           = ABS(angleDeltaToPlayer);

    if (distAbs > Q12(0.03f))
    {
        GetNewSpeed(nurse, distToPlayer);
    }
    else
    {
        Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
    }
    
    if (absAngle > FP_ANGLE(10.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle * tmpAngle) + FP_ANGLE(45.0f);
        addAngle = FP_MULTIPLY_PRECISE(g_DeltaTime0, tmpAngle, Q12_SHIFT);
        if (angleDeltaToPlayer > FP_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += addAngle;
        }
        else
        {
            nurse->rotation_24.vy -= addAngle;
        }
    }
}
