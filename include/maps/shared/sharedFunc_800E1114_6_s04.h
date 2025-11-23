s32 sharedFunc_800E1114_6_s04(s32 arg0, s32 arg1)
{
    s32 result;

    if (arg1 > Q12(80.0f))
    {
        result = 5;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(16.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(64.0f), Q12_SHIFT) < Q12(SQUARE(18)))
    {
        result = 3;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(-14.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(28.0f), Q12_SHIFT) < Q12(SQUARE(18)))
    {
        result = 2;
    }
    else if (FP_SQUARE_PRECISE(arg0 + Q12(14.0f), Q12_SHIFT) + FP_SQUARE_PRECISE(arg1 + Q12(28.0f), Q12_SHIFT) < Q12(SQUARE(5)))
    {
        result = 4;
    }
    else
    {
        result = 1;
    }

    return result;
}
