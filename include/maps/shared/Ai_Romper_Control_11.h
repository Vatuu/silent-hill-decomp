void Ai_Romper_Control_11(s_SubCharacter* romper)
{
    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_12, true) &&
        (Rng_Rand16() % 8) == 0)
    {
        g_SysWork.field_2284[3]                  &= ~((1 << 0) | (1 << 1));
        romper->model_0.controlState_2                   = RomperControl_1;
        romper->properties_E4.romper.flags_E8 &= ~RomperFlag_11;
    }
}
