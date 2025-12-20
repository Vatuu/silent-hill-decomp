s32 sharedFunc_800D77D0_0_s01(s_SubCharacter* chara)
{
    s32 temp_a0;
    s32 nonState;
    s32 rot;
    s32 speed;
    s32 speed_2;
    s32 temp_lo;
    s32 div;
    s32 var_a0_3;
    u32 absRot;
    u32 absSpeed;
    s32 ret;
    s32 ret_3;
    s32 var_v1;
    s32 temp_s1;
    s32 animTime;

    temp_s1  = chara->model_0.anim_4.status_0;
    nonState = chara->model_0.state_2 != 1;

    switch (temp_s1)
    {
        case 0x35:
            if (!(chara->model_0.anim_4.keyframeIdx_8 == 0x60) < 1 & chara->health_B0 < 1)
            {
                return 0;
            }
            else
            {
                return 0x5000;
            }
            break;

        case 0x1B:
        case 0x1D:
        case 0x2F:
        case 0x33:
            speed = chara->moveSpeed_38 * Q12(0.01f);
            rot   = chara->rotationSpeed_2C.vy * Q12(0.044f);

            if (!(speed | rot))
            {
                return 0;
            }

            if (speed < 0)
            {
                absSpeed = -speed;
            }
            else
            {
                absSpeed = speed;
            }

            if (rot < 0)
            {
                absRot = -rot;
            }
            else
            {
                absRot = rot;
            }

            if (absRot < absSpeed)
            {
                if (absSpeed < 0x14000)
                {
                    var_a0_3 = 0x14000;
                }
                else
                {
                    var_a0_3 = speed;
                }
            }
            else
            {
                if (absRot < 0x14000)
                {
                    var_a0_3 = 0x14000;
                }
                else
                {
                    var_a0_3 = rot;
                }
            }
            return var_a0_3;

        case 0x27:
            if (nonState)
            {
                return 0x18000;
            }
            return FP_MULTIPLY_PRECISE(chara->field_34, -0x2000, Q12_SHIFT) + 0x14000;

        case 0x23:
            if (nonState)
            {
                return 0x28000;
            }
            temp_a0 = chara->field_34;
            var_v1  = chara->moveSpeed_38 - 0x4000;

            ret  = 0x14000;
            ret += FP_MULTIPLY_PRECISE(ABS(var_v1), 0x1800, Q12_SHIFT);
            ret += FP_MULTIPLY_PRECISE(temp_a0, -0x1800, Q12_SHIFT);
            return ret;

        case 0x13:
        case 0x15:
        case 0x17:
        case 0x21:
            div      = func_80080884(chara->position_18.vx, chara->position_18.vz) - chara->position_18.vy;
            var_a0_3 = 0x14000;

            if (div > 0)
            {
                speed_2  = chara->field_34;
                animTime = chara->model_0.anim_4.time_4;

                switch (temp_s1)
                {
                    case 0x21:
                        ret_3 = 0x14D000;
                        break;

                    case 0x15:
                        ret_3 = 0xBD000;
                        break;

                    case 0x17:
                        ret_3 = 0xD7000;
                        break;

                    case 0x14:
                    default:
                        ret_3 = 0xAB000;
                        break;
                }

                temp_lo  = FP_TO(ret_3 - animTime, Q12_SHIFT) / div;
                var_a0_3 = FP_MULTIPLY_PRECISE(speed_2, temp_lo, Q12_SHIFT);
            }

            if (var_a0_3 < 0x4CC)
            {
                var_a0_3 = 0x4CC;
            }

            if (var_a0_3 > 0x1E000)
            {
                var_a0_3 = 0x1E000;
            }
            return var_a0_3;
    }

    return 0xA000;
}