void Ai_PuppetNurse_Move(s_SubCharacter* nurse)
{
    q3_12  angleDeltaToPlayer;
    q3_12  tmpAngle;
    q3_12  absAngle;
    q19_12 distToPlayer;
    q19_12 addAngle;
    q19_12 distAbs;
    q19_12 limit;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz) - Q12(0.76f);
    distAbs      = ABS(distToPlayer);

    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(nurse->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       nurse->rotation_24.vy);
    absAngle           = ABS(angleDeltaToPlayer);

    if (distAbs > Q12(0.03f))
    {
        if (distToPlayer > Q12(0.0f))
        {
            limit = Q12(0.0f);
        }
        else
        {
            limit = Q12(-0.02f);
        }

        Chara_MoveSpeedUpdate2(nurse, Q12(4.0f), limit);
    }
    else
    {
        Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
    }

    if (absAngle > Q12_ANGLE(10.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle * tmpAngle) + Q12_ANGLE(45.0f);
        addAngle = Q12_MULT_PRECISE(g_DeltaTime, tmpAngle);
        if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += addAngle;
        }
        else
        {
            nurse->rotation_24.vy -= addAngle;
        }
    }
}
