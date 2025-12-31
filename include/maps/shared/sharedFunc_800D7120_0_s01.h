s32 sharedFunc_800D7120_0_s01(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_t0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    s32 temp_t1;
    s32 temp_a0;
    s32 new_var2;

    var_a1  = arg1;
    var_a3  = arg0;
    temp_v1 = arg2 - var_a3;

    if (var_a1 != 0 && temp_v1 != 0)
    {
        temp_t0  = temp_v1 < 1;
        temp_t1  = temp_v1 >= 1;
        new_var2 = arg2;

        // TODO: Can `temp_t0` / `temp_t1` be merged here somehow?
        if (temp_v1 != 0 & (var_a1 > 0 ? temp_t0 : temp_t1))
        {
            var_a1 = -var_a1;
        }

        // TODO: Related to `MoveSpeedUpdate`/`APPROACH` macros?
        if (var_a1 > 0)
        {
            if (temp_v1 > 0)
            {
                var_a3 += FP_MULTIPLY_PRECISE(g_DeltaTime0, var_a1, Q12_SHIFT);
                if (new_var2 < var_a3)
                {
                    var_a3 = new_var2;
                }
            }
        }
        else if (temp_v1 < 0)
        {
            var_a3 += FP_MULTIPLY_PRECISE(g_DeltaTime0, var_a1, Q12_SHIFT);
            if (var_a3 < new_var2)
            {
                var_a3 = new_var2;
            }
        }
    }

    return var_a3;
}
