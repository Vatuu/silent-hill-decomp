q19_12 sharedFunc_800D77D0_0_s01(s_SubCharacter* airScreamer)
{
    q19_12 temp_a0;
    bool   isNotControlState1;
    q19_12 rot;
    q19_12 moveSpeed;
    q19_12 speed_2;
    q19_12 temp_lo;
    q19_12 distToGround;
    q19_12 speed1;
    q20_12 absRot;
    q20_12 absSpeed;
    q19_12 ret;
    q19_12 ret_3;
    q19_12 var_v1;
    s32    animStatus;
    q19_12 animTime;

    animStatus         = airScreamer->model_0.anim_4.status_0;
    isNotControlState1 = airScreamer->model_0.controlState_2 != AirScreamerControl_1;

    switch (animStatus)
    {
        case ANIM_STATUS(AirScreamerAnim_26, true):
            if (!(airScreamer->model_0.anim_4.keyframeIdx_8 == 96) < 1 & airScreamer->health_B0 < 1)
            {
                return Q12(0.0f);
            }
            else
            {
                return Q12(5.0f);
            }
            break;

        case ANIM_STATUS(AirScreamerAnim_13, true):
        case ANIM_STATUS(AirScreamerAnim_14, true):
        case ANIM_STATUS(AirScreamerAnim_23, true):
        case ANIM_STATUS(AirScreamerAnim_25, true):
            moveSpeed = airScreamer->moveSpeed_38 * Q12(0.01f);
            rot       = airScreamer->rotationSpeed_2C.vy * Q12(0.044f);

            if (!(moveSpeed | rot))
            {
                return Q12(0.0f);
            }

            if (moveSpeed < Q12(0.0f))
            {
                absSpeed = -moveSpeed;
            }
            else
            {
                absSpeed = moveSpeed;
            }

            if (rot < FP_ANGLE(0.0f))
            {
                absRot = -rot;
            }
            else
            {
                absRot = rot;
            }

            if (absRot < absSpeed)
            {
                if (absSpeed < Q12(20.0f))
                {
                    speed1 = Q12(20.0f);
                }
                else
                {
                    speed1 = moveSpeed;
                }
            }
            else
            {
                if (absRot < Q12(20.0f))
                {
                    speed1 = Q12(20.0f);
                }
                else
                {
                    speed1 = rot;
                }
            }
            return speed1;

        case ANIM_STATUS(AirScreamerAnim_19, true):
            if (isNotControlState1)
            {
                return Q12(24.0f);
            }
            return FP_MULTIPLY_PRECISE(airScreamer->field_34, Q12(-2.0f), Q12_SHIFT) + Q12(20.0f);

        case ANIM_STATUS(AirScreamerAnim_17, true):
            if (isNotControlState1)
            {
                return Q12(40.0f);
            }

            temp_a0 = airScreamer->field_34;
            var_v1  = airScreamer->moveSpeed_38 - Q12(4.0f);

            ret  = Q12(20.0f);
            ret += FP_MULTIPLY_PRECISE(ABS(var_v1), Q12(1.5f), Q12_SHIFT);
            ret += FP_MULTIPLY_PRECISE(temp_a0, Q12(-1.5f), Q12_SHIFT);
            return ret;

        case ANIM_STATUS(AirScreamerAnim_9, true):
        case ANIM_STATUS(AirScreamerAnim_10, true):
        case ANIM_STATUS(AirScreamerAnim_11, true):
        case ANIM_STATUS(AirScreamerAnim_16, true):
            distToGround = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) - airScreamer->position_18.vy;
            speed1       = Q12(20.0f);

            if (distToGround > Q12(0.0f))
            {
                speed_2  = airScreamer->field_34;
                animTime = airScreamer->model_0.anim_4.time_4;

                switch (animStatus)
                {
                    case ANIM_STATUS(AirScreamerAnim_16, true):
                        ret_3 = Q12(333.0f);
                        break;

                    case ANIM_STATUS(AirScreamerAnim_10, true):
                        ret_3 = Q12(189.0f);
                        break;

                    case ANIM_STATUS(AirScreamerAnim_11, true):
                        ret_3 = Q12(215.0f);
                        break;

                    case ANIM_STATUS(AirScreamerAnim_10, false):
                    default:
                        ret_3 = Q12(171.0f);
                        break;
                }

                temp_lo  = FP_TO(ret_3 - animTime, Q12_SHIFT) / distToGround;
                speed1 = FP_MULTIPLY_PRECISE(speed_2, temp_lo, Q12_SHIFT);
            }

            if (speed1 < Q12(0.3f))
            {
                speed1 = Q12(0.3f);
            }
            if (speed1 > Q12(30.0f))
            {
                speed1 = Q12(30.0f);
            }
            return speed1;
    }

    return Q12(10.0f);
}
