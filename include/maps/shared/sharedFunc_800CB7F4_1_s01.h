void sharedFunc_800CB7F4_1_s01(void)
{
    s32 count;
    s32 i;

    count = sharedData_800DEE50_1_s01.field_4;
    for (i = 0; i < ARRAY_SIZE(sharedData_800DFB7C_0_s00); i++)
    {
        if (sharedData_800DFB7C_0_s00[i].field_A != 0)
        {
            continue;
        }

        sharedData_800DFB7C_0_s00[i].field_A         = 13;
        sharedData_800DFB7C_0_s00[i].field_C.field_0 = ((TO_FIXED(sharedData_800DEE50_1_s01.field_6 - sharedData_800DEE50_1_s01.field_8, Q12_SHIFT) / sharedData_800DEE50_1_s01.field_C) * count) / sharedData_800DEE50_1_s01.field_4;

        count--;
        if (count == 0)
        {
            break;
        }
    }

    sharedData_800DEE50_1_s01.field_10 = 0;
    D_800C4414                        |= 1 << 1;
}
