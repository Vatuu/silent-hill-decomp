void sharedFunc_800E6758_2_s02(s_SubCharacter* chara)
{
    s32    tmp0;
    q19_12 speed;
    s32    var;

    tmp0 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3;
    if (tmp0 == 0)
    {
        var = func_8006FD90(chara, 1, Q12(1.8f), Q12(4.0f));
    }
    else if (tmp0 == 2)
    {
        var = func_8006FD90(chara, 1, Q12(3.0f), Q12(7.0f));
    }
    else
    {
        var = func_8006FD90(chara, 1, Q12(1.0f), Q12(1.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var += func_80070360(chara, Q12(0.0f), Q12(0.4f));
    }

    speed               = chara->moveSpeed_38 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
    chara->moveSpeed_38 = MAX(speed, 0);

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(12, true) && (!(Rng_Rand16() & 0xFFF) || var))
    {
        chara->model_0.state_2         = 2;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
    }
}
