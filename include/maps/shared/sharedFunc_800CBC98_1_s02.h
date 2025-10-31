void sharedFunc_800CBC98_1_s02(void)
{
    s32 idx;
    s32 i;

    for (i = 0; i < sharedData_800E30C8_1_s02.field_74; i++)
    {
        idx = func_8005E7E0(27);
        if (idx == NO_VALUE)
        {
            break;
        }

        sharedFunc_800CBA4C_1_s02(idx, 2, 0);
    }

    for (i = 0; i < sharedData_800E30C8_1_s02.field_78; i++)
    {
        sharedData_800E30C8_1_s02.field_54[i] = 0;
    }

    D_800C4414 |= 1 << 3;
}
