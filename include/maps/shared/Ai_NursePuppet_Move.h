static void inline calcNewSpeed(s_SubCharacter* nurse, s32 dist)
{
    s32 moveSpeed;
    s32 newMoveSpeed;
    s32 tmpSpeed;
    s32 limit;

    if (dist > 0)
    {
        limit = 0;
    }
    else
    {
        limit = -0x51;
    }
    moveSpeed = nurse->moveSpeed_38;
    if (moveSpeed > limit)
    {
        newMoveSpeed = limit;
        tmpSpeed = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(4.0f), Q12_SHIFT);
        if (newMoveSpeed < tmpSpeed)
        {
            newMoveSpeed = tmpSpeed;
        }
    }
    else
    {
        newMoveSpeed = limit;
        tmpSpeed = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(4.0f), Q12_SHIFT);
        if (newMoveSpeed >= tmpSpeed)
        {
            newMoveSpeed = tmpSpeed;
        }
    }
    nurse->moveSpeed_38 = newMoveSpeed;
}

void Ai_NursePuppet_Move(s_SubCharacter* nurse)
{
    s16 angle;
    s16 tmpAngle;
    s16 absAngle;
    s32 dist;
    s32 deltaX;
    s32 deltaZ;
    s32 addAngle;
    s32 distAbs;

    q19_12 newMoveSpeed;
    q19_12 moveSpeed;

    deltaX = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz);
    dist = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ))) - Q12(0.76f);
    distAbs = ABS(dist);

    angle = func_8005BF38((ratan2(
        g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx,
        g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz) - nurse->rotation_24.vy));
    absAngle = ABS(angle);

    if (distAbs > Q12(0.03f))
    {
        calcNewSpeed(nurse, dist);
    }
    else
    {
        moveSpeed = nurse->moveSpeed_38;
        if (moveSpeed > Q12(0.0f))
        {
            newMoveSpeed = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(4.0f), Q12_SHIFT);
            if (newMoveSpeed < Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
            nurse->moveSpeed_38 = newMoveSpeed;
        }
        else
        {
            newMoveSpeed = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(4.0f), Q12_SHIFT);
            if (newMoveSpeed > Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
            nurse->moveSpeed_38 = newMoveSpeed;
        }
    }
    
    if (absAngle > FP_ANGLE(10.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle * tmpAngle) + FP_ANGLE(45.0f);
        addAngle = FP_MULTIPLY_PRECISE(g_DeltaTime0, tmpAngle, Q12_SHIFT);
        if (angle > FP_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += addAngle;
        }
        else
        {
            nurse->rotation_24.vy -= addAngle;
        }
    }
}



