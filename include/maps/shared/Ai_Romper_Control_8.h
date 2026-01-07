void Ai_Romper_Control_8(s_SubCharacter* romper)
{
    #define romperProps romper->properties_E4.romper

    if (romper->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(romper))
        {
            romper->health_B0  = NO_VALUE;
            romper->field_E1_0 = 0;
        }
    }

    if (romper->moveSpeed_38 == Q12(0.0f) &&
        !(romperProps.flags_E8 & (RomperFlag_0 | RomperFlag_1)))
    {
        func_800622B8(3, romper, ANIM_STATUS(RomperAnim_6, true), 9);
        romperProps.flags_E8 |= RomperFlag_1;
    }

    #undef romperProps
}
