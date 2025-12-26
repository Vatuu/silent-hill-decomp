void sharedFunc_800D8244_1_s02(s_SubCharacter* creaper)
{
    switch (creaper->model_0.state_2)
    {
        case 1:
            sharedFunc_800D82F0_1_s02(creaper);
            break;

        case 2:
            sharedFunc_800D8684_1_s02(creaper);
            break;

        case 3:
            sharedFunc_800D8F30_1_s02(creaper);
            break;
    
        case 4:
            sharedFunc_800D9528_1_s02(creaper);
            break;

        case 5:
            sharedFunc_800D9774_1_s02(creaper);
            break;

        default:
            break;
    }

    // Reset alerted flag.
    creaper->properties_E4.creaper.flags_E8 &= ~CreaperFlag_Alerted;
}
