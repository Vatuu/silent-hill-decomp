
void sharedFunc_800CBD58_1_s02(void)
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(sharedData_800E1FF8_1_s02); i++)
    {
        if (sharedData_800E1FF8_1_s02[i].field_A == 27 || sharedData_800E1FF8_1_s02[i].field_A == 28)
        {
            sharedData_800E1FF8_1_s02[i].field_A = 0;
        }
    }

    D_800C4414 &= ~(1 << 3);
}
