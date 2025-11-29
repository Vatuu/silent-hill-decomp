static void inline calcNewSpeed2(s_SubCharacter* nurse, s32 dist, s32 distAbs)
{
    s32 moveSpeed;
    s32 newMoveSpeed;
    s32 tmpSpeed;
    s32 limit;

    if (distAbs > 0x333)
    {
        limit = 0x333;
    }
    else
    {
        
        if (distAbs > 0xCC)
        {
            if (dist > 0)
            {
                limit = 0x999;
            }
            else
            {
                limit = -0x999;
            }
        }
        else
        {
            limit = 0;
        }
    }
    moveSpeed = nurse->moveSpeed_38;
    if (moveSpeed > limit)
    {
        newMoveSpeed = limit;
        tmpSpeed = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(2.0f), Q12_SHIFT);
        if (newMoveSpeed < tmpSpeed)
        {
            newMoveSpeed = tmpSpeed;
        }
    }
    else
    {
        newMoveSpeed = limit;
        tmpSpeed = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(2.0f), Q12_SHIFT);
        if (newMoveSpeed >= tmpSpeed)
        {
            newMoveSpeed = tmpSpeed;
        }
    }
    nurse->moveSpeed_38 = newMoveSpeed;
}

bool sharedFunc_800CE7C8_3_s03(s_SubCharacter* nurse)
{
    s32 deltaX;
    s32 deltaZ;
    s32 dist;
    s32 distAbs;
    s32 distSubtract;
    s32 moveSpeed;

    s16 angle;
    s16 angle2;
    s16 tmpAngle;
    s16 addAngle;
    s16 absAngle;

    distSubtract = Q12(0.78f);
    angle = func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx,
                                   g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz) - nurse->rotation_24.vy);
    absAngle = ABS(angle);

    angle2 = func_8005BF38(g_SysWork.player_4C.chara_0.rotation_24.vy - nurse->rotation_24.vy);
    angle2 = ABS(angle2);

    if (angle2 > Q12(0.25f))
    {
        distSubtract = Q12(0.85f);
    }
    deltaX = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz);
    dist = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ))) - distSubtract;
    distAbs = ABS(dist);

    if (dist > Q12(0.5f))
    {
        return false;
    }
    calcNewSpeed2(nurse, dist, distAbs);

    if (absAngle > FP_ANGLE(4.0f))
    {
        tmpAngle= 2;
        tmpAngle= (absAngle* tmpAngle) + FP_ANGLE(45.0f);
        addAngle= FP_MULTIPLY_PRECISE(g_DeltaTime0, tmpAngle, Q12_SHIFT);
        if (angle > FP_ANGLE(0.0f))
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

