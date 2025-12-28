void sharedFunc_800D8244_1_s02(s_SubCharacter* creeper)
{
    #define creeperProps creeper->properties_E4.creeper

    // Handle control state.
    switch (creeper->model_0.controlState_2)
    {
        case CreeperControl_1:
            Ai_Creeper_Control_1(creeper);
            break;

        case CreeperControl_2:
            Ai_Creeper_Control_2(creeper);
            break;

        case CreeperControl_3:
            Ai_Creeper_Control_3(creeper);
            break;
    
        case CreeperControl_4:
            Ai_Creeper_Control_4(creeper);
            break;

        case CreeperControl_5:
            Ai_Creeper_Control_5(creeper);
            break;
    }

    // Reset alerted flag.
    creeperProps.flags_E8 &= ~CreeperFlag_Alerted;

    #undef creeperProps
}
