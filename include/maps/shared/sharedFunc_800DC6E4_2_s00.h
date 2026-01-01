s32 sharedFunc_800DC6E4_2_s00(s_SubCharacter* airScreamer, q19_12 arg1)
{
    s32    result;
    q19_12 mult;

    mult = Q12(0.0f);
    if (airScreamer->properties_E4.unk0.field_E8_4 != 0)
    {
        mult = Q12(0.1f);
    }

    result = 0;

    switch ((u32)airScreamer->properties_E4.unk0.field_E8_8)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;

        case 5:
            result  = MAX((Q12(10.0f) - arg1) / 128, 0);
            result += (sharedFunc_800D3814_0_s01(airScreamer) / 5) - (mult * 2);
            break;
    }

    if (airScreamer->health_B0 > Q12(300.0f))
    {
        result /= 2;
    }

    switch ((u32)airScreamer->properties_E4.unk0.field_E8_0)
    {
        case 3:
            result = 0;
            break;

        case 1:
            // TODO: Not sure what this is trying to do, getting index into `npcs_1A0` in strange way?
            if (!((g_SysWork.npcs_1A0 - airScreamer) & 1))
            {
                result = 0;
            }
            else
            {
                result /= 2;
            }
            break;

        case 0:
            if (!((g_SysWork.npcs_1A0 - airScreamer) & 1))
            {
                result /= 2;
            }
            break;
    }

    return result;
}
