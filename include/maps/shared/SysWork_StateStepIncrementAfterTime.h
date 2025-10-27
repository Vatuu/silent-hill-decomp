/** @brief Waits for an external timer to be above `timeMin`, incrementing the timer until it reaches
 * `timeMax`. After this time, it increments `StateStep`.
 *
 * @param timer External timer.
 * @param timeInc Time increment.
 * @param timeMin Minimum time before the external timer can be incremented.
 * @param timeMax Maximum time before the system state step can be incremented.
 * @param setTimerToMax Clamp the external timer to the max time when it is reached.
 * @param incStateStep Increment the system state step when max time is reached.
 */
void SysWork_StateStepIncrementAfterTime(s32* timer, s32 timeInc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateStep) // 0x800DA8E8
{
    if (*timer < timeMin)
    {
        *timer = timeMin;
        return;
    }

    *timer += FP_MULTIPLY_PRECISE(g_DeltaTime0, timeInc, Q12_SHIFT);
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
