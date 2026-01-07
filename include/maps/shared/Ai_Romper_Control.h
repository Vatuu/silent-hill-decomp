void Ai_Romper_Control(s_SubCharacter* romper)
{
    u8 controlState;

    #define romperProps romper->properties_E4.romper

    if (romper->model_0.controlState_2 != RomperControl_5)
    {
        romper->field_44.field_0 = 0;
    }

    // Handle control state.
    controlState = romper->model_0.controlState_2;
    g_Romper_ControlFuncs[controlState](romper);
    if (romper->model_0.controlState_2 != controlState)
    {
        romperProps.field_120 = 0;
    }

    #undef romperProps
}
