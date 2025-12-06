void sharedFunc_800E86C0_2_s02(s_SubCharacter* chara)
{
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(12, true) && (Rng_Rand16() % 8) == 0)
    {
        g_SysWork.field_2284[3]                 &= ~((1 << 0) | (1 << 1));
        chara->model_0.state_2                   = 1;
        chara->properties_E4.player.afkTimer_E8 &= ~(1 << 11);
    }
}
