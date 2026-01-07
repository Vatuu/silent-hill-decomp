void Ai_Romper_Control_1(s_SubCharacter* romper)
{
    s32    flags;
    q19_12 newMoveSpeed;
    s32    var;

    flags = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1));
    if (flags == 0)
    {
        var = func_8006FD90(romper, 1, Q12(1.8f), Q12(4.0f));
    }
    else if (flags == (1 << 1))
    {
        var = func_8006FD90(romper, 1, Q12(3.0f), Q12(7.0f));
    }
    else
    {
        var = func_8006FD90(romper, 1, Q12(1.0f), Q12(1.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var += func_80070360(romper, Q12(0.0f), Q12(0.4f));
    }

    newMoveSpeed         = romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, Q12(15.0f));
    romper->moveSpeed_38 = MAX(newMoveSpeed, Q12(0.0f));

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_12, true) &&
        (Rng_GenerateUInt(0, 4095) == 0 || var)) // 1 in 4096 chance.
    {
        romper->model_0.controlState_2         = RomperControl_2;
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_15, false);
    }
}
