/** @brief Waits for an external timer to be above `timeMin`, incrementing the timer until it reaches
 * `timeMax`. After this time, it increments the cutscene state step.
 *
 * TODO: Specific to cutscene map events. Revised name could be `SysWork_CutsceneStateStepIncrement` or `Map_CutsceneStateStepIncrement`.
 *
 * @param timer External timer.
 * @param timeInc Time increment.
 * @param timeMin Minimum time before the external timer can be incremented.
 * @param timeMax Maximum time before the system state step can be incremented.
 * @param setTimerToMax Clamp the external timer to the max time when it is reached.
 * @param incStateStep Increment the cutscene state step when max time is reached.
 */
void SysWork_StateStepIncrementAfterTime(q19_12* timer, q19_12 timeInc, q19_12 timeMin, q19_12 timeMax, bool setTimerToMax, bool incStateStep) // 0x800DA8E8
{
    // Clamp timer to min.
    if (*timer < timeMin)
    {
        *timer = timeMin;
        return;
    }

    // Increment timer.
    *timer += Q12_MULT_PRECISE(g_DeltaTime, timeInc);

    // End timer and increment state step.
    if (*timer > timeMax)
    {
        if (setTimerToMax)
        {
            *timer = timeMax;
        }

        if (incStateStep)
        {
            SysWork_StateStepIncrement(0);
        }
    }
}
