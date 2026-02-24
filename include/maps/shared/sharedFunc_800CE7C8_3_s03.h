bool sharedFunc_800CE7C8_3_s03(s_SubCharacter* nurse)
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist;
    q19_12 distAbs;
    q19_12 distSubtract;
    q19_12 moveSpeed;
    q3_12  angle;
    q3_12  angle2;
    q3_12  tmpAngle;
    q3_12  addAngle;
    q3_12  absAngle;
    q19_12 limit;

    distSubtract = Q12(0.78f);
    angle        = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx,
                                        g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz) - nurse->rotation_24.vy);
    absAngle = ABS(angle);

    angle2 = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - nurse->rotation_24.vy);
    angle2 = ABS(angle2);

    if (angle2 > Q12_ANGLE(90.0f))
    {
        distSubtract = Q12(0.85f);
    }

    deltaX  = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx);
    deltaZ  = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz);
    dist    = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ))) - distSubtract;
    distAbs = ABS(dist);

    if (dist > Q12(0.5f))
    {
        return false;
    }

    if (distAbs > Q12(0.2f))
    {
        limit = Q12(0.2f);
    }
    else
    {
        if (distAbs > Q12(0.05f))
        {
            if (dist > Q12(0.0f))
            {
                limit = Q12(0.6f);
            }
            else
            {
                limit = Q12(-0.6f);
            }
        }
        else
        {
            limit = Q12(0.0f);
        }
    }

    Chara_MoveSpeedUpdate2(nurse, Q12(2.0f), limit);

    if (absAngle > Q12_ANGLE(4.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle* tmpAngle) + Q12_ANGLE(45.0f);
        addAngle = Q12_MULT_PRECISE(g_DeltaTime, tmpAngle);
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += addAngle;
        }
        else
        {
            nurse->rotation_24.vy -= addAngle;
        }
    }

    return true;
}

