q19_12 sharedFunc_800D77D0_0_s01(s_SubCharacter* chara)
{
    q19_12 temp_a0;
    bool   isNotState1;
    q19_12 rot;
    q19_12 speed;
    q19_12 speed_2;
    q19_12 temp_lo;
    q19_12 div;
    q19_12 var_a0_3;
    q20_12 absRot;
    q20_12 absSpeed;
    q19_12 ret;
    q19_12 ret_3;
    q19_12 var_v1;
    s32    animStatus;
    q19_12 animTime;

    animStatus  = chara->model_0.anim_4.status_0;
    isNotState1 = chara->model_0.state_2 != 1;

    switch (animStatus)
    {
        case ANIM_STATUS(26, true):
            if (!(chara->model_0.anim_4.keyframeIdx_8 == 96) < 1 & chara->health_B0 < 1)
            {
                return Q12(0.0f);
            }
            else
            {
                return Q12(5.0f);
            }
            break;

        case ANIM_STATUS(13, true):
        case ANIM_STATUS(14, true):
        case ANIM_STATUS(23, true):
        case ANIM_STATUS(25, true):
            speed = chara->moveSpeed_38 * Q12(0.01f);
            rot   = chara->rotationSpeed_2C.vy * Q12(0.044f);

            if (!(speed | rot))
            {
                return Q12(0.0f);
            }

            if (speed < Q12(0.0f))
            {
                absSpeed = -speed;
            }
            else
            {
                absSpeed = speed;
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
                    var_a0_3 = Q12(20.0f);
                }
                else
                {
                    var_a0_3 = speed;
                }
            }
            else
            {
                if (absRot < Q12(20.0f))
                {
                    var_a0_3 = Q12(20.0f);
                }
                else
                {
                    var_a0_3 = rot;
                }
            }
            return var_a0_3;

        case ANIM_STATUS(19, true):
            if (isNotState1)
            {
                return Q12(24.0f);
            }
            return FP_MULTIPLY_PRECISE(chara->field_34, Q12(-2.0f), Q12_SHIFT) + Q12(20.0f);

        case ANIM_STATUS(17, true):
            if (isNotState1)
            {
                return Q12(40.0f);
            }

            temp_a0 = chara->field_34;
            var_v1  = chara->moveSpeed_38 - Q12(4.0f);

            ret  = Q12(20.0f);
            ret += FP_MULTIPLY_PRECISE(ABS(var_v1), Q12(1.5f), Q12_SHIFT);
            ret += FP_MULTIPLY_PRECISE(temp_a0, Q12(-1.5f), Q12_SHIFT);
            return ret;

        case ANIM_STATUS(9, true):
        case ANIM_STATUS(10, true):
        case ANIM_STATUS(11, true):
        case ANIM_STATUS(16, true):
            div      = func_80080884(chara->position_18.vx, chara->position_18.vz) - chara->position_18.vy;
            var_a0_3 = Q12(20.0f);

            if (div > Q12(0.0f))
            {
                speed_2  = chara->field_34;
                animTime = chara->model_0.anim_4.time_4;

                switch (animStatus)
                {
                    case ANIM_STATUS(16, true):
                        ret_3 = Q12(333.0f);
                        break;

                    case ANIM_STATUS(10, true):
                        ret_3 = Q12(189.0f);
                        break;

                    case ANIM_STATUS(11, true):
                        ret_3 = Q12(215.0f);
                        break;

                    case ANIM_STATUS(10, false):
                    default:
                        ret_3 = Q12(171.0f);
                        break;
                }

                temp_lo  = FP_TO(ret_3 - animTime, Q12_SHIFT) / div;
                var_a0_3 = FP_MULTIPLY_PRECISE(speed_2, temp_lo, Q12_SHIFT);
            }

            if (var_a0_3 < Q12(0.3f))
            {
                var_a0_3 = Q12(0.3f);
            }
            if (var_a0_3 > Q12(30.0f))
            {
                var_a0_3 = Q12(30.0f);
            }
            return var_a0_3;
    }

    return Q12(10.0f);
}