void sharedFunc_800DDA80_2_s00(s_SubCharacter* arg0)
{
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_v1;

    var_s0 = 0;

    temp_a1 = arg0->position_18.vx;
    temp_a2 = arg0->position_18.vz;

    temp_s4 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    temp_s3 = g_SysWork.playerWork_4C.player_0.position_18.vz;

    var_s1 = temp_a1;
    var_s2 = temp_a2;

    if (temp_s4 > 0x10000)
    {
        var_v1 = 2;
    }
    else
    {
        var_v1 = !(temp_s4 < -0x8000);
    }

    if (temp_s3 <= 0x8000)
    {
        var_a0 = !(temp_s3 < -0x8000);
    }
    else
    {
        var_a0 = 2;
    }

    switch (var_v1 + (var_a0 * 3))
    {
        case 8:
            var_s0 = !(temp_s4 - 0x10000 > temp_s3 - 0x8000) * 2;
            break;

        case 6:
            if (-0x8000 - temp_s4 > temp_s3 - 0x8000)
            {
                var_s0 = 0;
            }
            else
            {
                var_s0 = 3;
            }
            break;

        case 7:
            var_s0 = 0;
            break;

        case 5:
            var_s0 = 2;
            break;

        case 4:
            temp_v0 = (g_SysWork.playerWork_4C.player_0.rotation_24.vy - 0x200) & 0xFFF;
            switch (temp_v0 / 0x400)
            {
                case 1:
                    var_s0 = 3;
                    break;

                case 2:
                    var_s0 = 0;
                    break;

                case 3:
                    var_s0 = 2;
                    break;

                default:
                case 0:
                    var_s0 = 1;
                    break;
            }
            break;

        case 3:
            var_s0 = 3;
            break;

        case 1:
            var_s0 = 1;
            break;

        case 2:
            if (temp_s4 - 0x10000 > -0x8000 - temp_s3)
            {
                var_s0 = 1;
            }
            else
            {
                var_s0 = 2;
            }
            break;

        case 0:
            if (-0x8000 - temp_s4 > -0x8000 - temp_s3)
            {
                var_s0 = 1;
            }
            else
            {
                var_s0 = 3;
            }
            break;
    }

    switch (var_s0)
    {
        case 0:
        case 1:
            var_s1 = (temp_a1 + temp_s4) / 2;
            if (var_s1 > 0x10000)
            {
                var_s1 = 0x10000;
            }
            else if (var_s1 < -0x8000)
            {
                var_s1 = -0x8000;
            }

            var_s2 = 0x190000 - FP_SQUARE_PRECISE(var_s1 - temp_s4, Q12_SHIFT);
            if (var_s2 < 0)
            {
                var_s2 = temp_s3;

                if (var_s1 < temp_s4)
                {
                    var_s0 = 2;
                }
                else
                {
                    var_s0 = 3;
                }
            }
            else
            {
                var_s2 = SquareRoot12(var_s2);
                if (var_s0 == 0)
                {
                    var_s2 = var_s2 + temp_s3;
                }
                else
                {
                    var_s2 = temp_s3 - var_s2;
                }
            }
            break;

        case 2:
        case 3:
            var_s2 = (temp_a2 + temp_s3) / 2;

            if (var_s2 > 0x8000)
            {
                var_s2 = 0x8000;
            }
            else if (var_s2 < -0x8000)
            {
                var_s2 = -0x8000;
            }

            var_s1 = 0x190000 - FP_SQUARE_PRECISE(var_s2 - temp_s3, Q12_SHIFT);

            if (var_s1 < 0)
            {
                var_s1 = temp_s4;
                var_s0 = (var_s2 < temp_s3) ^ 1;
            }
            else
            {
                var_s1 = SquareRoot12(var_s1);
                if (var_s0 == 2)
                {
                    var_s1 = var_s1 + temp_s4;
                }
                else
                {
                    var_s1 = temp_s4 - var_s1;
                }
            }
            break;
    }

    switch (var_s0)
    {
        case 0:
            arg0->rotation_24.vy = 0x800;
            arg0->position_18.vy = -0x2000;
            break;

        case 1:
            arg0->rotation_24.vy = 0;

        default:
            arg0->position_18.vy = -0x2000;
            break;

        case 2:
            arg0->rotation_24.vy = 0xC00;
            arg0->position_18.vy = -0x2000;
            break;

        case 3:
            arg0->rotation_24.vy = 0x400;
            arg0->position_18.vy = -0x2000;
            break;
    }

    arg0->moveSpeed_38                                 = sharedData_800CAA98_0_s01.unk_380[9][0];
    arg0->position_18.vx                               = var_s1;
    arg0->position_18.vz                               = var_s2;
    arg0->properties_E4.dummy.properties_E8[0xE].val32 = 0xA000;

    sharedFunc_800DEC84_2_s00(arg0, 0x1E000, arg0->rotation_24.vy + ((Rng_RandQ12() - 0x800) >> 7));
    sharedFunc_800D4E84_0_s01(arg0);
}