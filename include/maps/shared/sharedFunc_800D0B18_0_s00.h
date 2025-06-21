s32 sharedFunc_800D0B18_0_s00(s32 arg0)
{
    s32 temp_a0_2;
    u16 temp;

    if (g_SysWork.field_234A != 0)
    {
        g_SysWork.field_2349 = arg0;
        g_SysWork.field_2348 = arg0;

        if (arg0 == 0)
        {
            sharedData_800E0CA8_0_s00 = 0;
        }
        else if (arg0 < 5)
        {
            sharedData_800E0CA8_0_s00 = 1;
        }
        else
        {
            sharedData_800E0CA8_0_s00 = 2;
        }

        if (sharedData_800E0CA8_0_s00 != 0)
        {
            sharedData_800E0CAC_0_s00 = (arg0 - 1) % 4U;
        }

        switch (sharedData_800E0CA8_0_s00)
        {
            case 1:
                sharedData_800DFB6C_0_s00 = 1;
                break;

            case 2:
                sharedData_800DFB70_0_s00 = 1;
#if !defined(MAP0_S01) && !defined(MAP0_S02) && !defined(MAP1_S00) && \
    !defined(MAP1_S06) && !defined(MAP2_S00) && !defined(MAP2_S02) && \
    !defined(MAP3_S00) && !defined(MAP3_S01) && !defined(MAP3_S06) && \
    !defined(MAP5_S01) && !defined(MAP5_S03) && !defined(MAP7_S03)
                sharedData_800E32D0_0_s00 = 0;
#endif
                break;

            default:
                break;
        }

        sharedData_800E0CB4_0_s00 &= 0xFFF;
        temp                      = (((u16)sharedData_800E0CA8_0_s00 * 4) + sharedData_800E0CAC_0_s00) << Q12_SHIFT;
        temp_a0_2                 = sharedData_800E0CB4_0_s00 | temp;
        sharedData_800E0CB4_0_s00 = (sharedData_800E0CB4_0_s00 | temp) & 0xF000;
        temp_a0_2                 = (temp_a0_2 * 8) & 0xE38;

        if (sharedData_800E0CA8_0_s00 != 0)
        {
            sharedData_800E0CB4_0_s00 += temp_a0_2 + (((sharedData_800E0CAC_0_s00 + 4) << Q12_SHIFT) >> (sharedData_800E0CA8_0_s00 * 6));
        }
        else
        {
            sharedData_800E0CB4_0_s00 += temp_a0_2;
        }

        if (sharedData_800E0CB4_0_s00 != sharedData_800E0CB6_0_s00)
        {
            g_SysWork.field_234A = 0;
        }

        if (sharedData_800E0CAC_0_s00 == 0 || sharedData_800E0CAC_0_s00 == 2)
        {
            sharedData_800E324C_0_s00.vy = 2;
        }
        else
        {
            sharedData_800E324C_0_s00.vy = 0;
        }

        sharedData_800E0CB8_0_s00 = (sharedData_800E0CB8_0_s00 & ~0xF) + (sharedData_800E0CB4_0_s00 >> Q12_SHIFT);
        return 1;
    }

    return 0;
}
