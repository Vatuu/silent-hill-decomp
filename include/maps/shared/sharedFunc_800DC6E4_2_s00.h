q19_12 sharedFunc_800DC6E4_2_s00(s_SubCharacter* airScreamer, q19_12 arg1)
{
    q19_12 chance;
    q19_12 mult;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    mult = Q12(0.0f);
    if (airScreamerProps.field_E8_4)
    {
        mult = Q12(0.1f);
    }

    chance = Q12(0.0f);
    switch ((u32)airScreamerProps.field_E8_8)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;

        case 5:
            chance  = MAX((Q12(10.0f) - arg1) / 128, Q12(0.0f));
            chance += (sharedFunc_800D3814_0_s01(airScreamer) / 5) - (mult * 2);
            break;
    }

    if (airScreamer->health_B0 > Q12(300.0f))
    {
        chance /= 2;
    }

    switch ((u32)airScreamerProps.field_E8_0)
    {
        case 3:
            chance = Q12(0.0f);
            break;

        case 1:
            // TODO: Not sure what this is trying to do, getting index into `npcs_1A0` in strange way?
            if (!((g_SysWork.npcs_1A0 - airScreamer) & 0x1))
            {
                chance = Q12(0.0f);
            }
            else
            {
                chance /= 2;
            }
            break;

        case 0:
            if (!((g_SysWork.npcs_1A0 - airScreamer) & 0x1))
            {
                chance /= 2;
            }
            break;
    }

    return chance;
}
