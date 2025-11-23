s32 sharedFunc_800CEEAC_3_s03(void)
{
    s32 temp_a0;

    temp_a0 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3;
    if (temp_a0 == 0)
    {
        return 0;
    }
    else if (temp_a0 == 2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
