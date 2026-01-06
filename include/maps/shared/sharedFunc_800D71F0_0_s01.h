q19_12 sharedFunc_800D71F0_0_s01(q19_12 moveSpeed, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_v1;
    s32 arg2Sqr;

    if (arg1 == 0)
    {
        return moveSpeed;
    }

    if (arg2 != 0)
    {
        if (arg1 < 0)
        {
            arg1 = -arg1;
        }

        arg2Sqr  = Q12_MULT_PRECISE(arg2, arg2) << Q12_SHIFT;
        arg2Sqr /= arg1 * 2;

        if (arg3 <= 0)
        {
            arg3 = -arg3;
        }

        if (arg3 < arg2Sqr)
        {
            var_v1 = SquareRoot12(Q12_MULT_PRECISE(arg3, arg1 * 2));
            if (var_v1 == 0)
            {
                var_v1 = 1;
            }

            if (arg2 > 0)
            {
                if (var_v1 < arg2)
                {
                    arg2 = var_v1;
                }
            }
            else
            {
                if (arg2 < -var_v1)
                {
                    arg2 = -var_v1;
                }
            }
        }
    }

    return sharedFunc_800D7120_0_s01(moveSpeed, arg1, arg2);
}
