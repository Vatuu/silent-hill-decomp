// `StateStepIncrement_AfterTime`?
void SysWork_StateStepIncrementAfterTime(s32* timer, s32 inc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateStep) // 0x800DA8E8
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

        if (incStateStep)
        {
            SysWork_StateStepIncrement();
        }
    }
}
