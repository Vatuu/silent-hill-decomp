// `StateStepIncrement_AfterTime`
void sharedFunc_800DA8E8_0_s01(s32* timer, s32 inc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateIdx) // 0x800DA8E8
{
    if (*timer < timeMin)
    {
        *timer = timeMin;
        return;
    }

    *timer += FP_MULTIPLY_PRECISE(g_DeltaTime0, inc, Q12_SHIFT);

    if (timeMax < *timer)
    {
        if (setTimerToMax)
        {
            *timer = timeMax;
        }

        if (incStateIdx)
        {
            SysWork_StateStepIncrement();
        }
    }
}
