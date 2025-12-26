void sharedFunc_800D8244_1_s02(s_SubCharacter* creeper)
{
    switch (creeper->model_0.state_2)
    {
        case 1:
            sharedFunc_800D82F0_1_s02(creeper);
            break;

        case 2:
            sharedFunc_800D8684_1_s02(creeper);
            break;

        case 3:
            sharedFunc_800D8F30_1_s02(creeper);
            break;
    
        case 4:
            sharedFunc_800D9528_1_s02(creeper);
            break;

        case 5:
            sharedFunc_800D9774_1_s02(creeper);
            break;

        default:
            break;
    }

    // Reset alerted flag.
    creeper->properties_E4.creeper.flags_E8 &= ~CreeperFlag_Alerted;
}
