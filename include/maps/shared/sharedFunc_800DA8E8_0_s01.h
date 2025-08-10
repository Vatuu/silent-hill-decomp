void sharedFunc_800DA8E8_0_s01(s32* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x800DA8E8
{
    if (*arg0 < arg2)
    {
        *arg0 = arg2;
        return;
    }

    *arg0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, arg1, Q12_SHIFT);

    if (arg3 < *arg0)
    {
        if (arg4 != 0)
        {
            *arg0 = arg3;
        }

        if (arg5 != 0)
        {
            SysWork_StateStepIncrement();
        }
    }
}
