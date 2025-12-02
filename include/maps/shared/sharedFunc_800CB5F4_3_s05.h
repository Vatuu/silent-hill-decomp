void sharedFunc_800CB5F4_3_s05(void) // 0x800CC19C
{
    s32 i;
    s32 counterC;

    if (sharedData_800DD180_3_s05.field_0 & (1 << 0))
    {
        sharedData_800DD180_3_s05.field_1A = sharedData_800DD180_3_s05.field_1C * 2;
        sharedData_800DD180_3_s05.field_18 = sharedData_800DD180_3_s05.field_1A;
    }
    else
    {
        sharedData_800DD180_3_s05.field_1C = (sharedData_800DD180_3_s05.field_18 + sharedData_800DD180_3_s05.field_1A) >> 1;
    }

    sharedData_800DD180_3_s05.field_16 = sharedData_800DD180_3_s05.field_12 - sharedData_800DD180_3_s05.field_14;
    if (sharedData_800DD180_3_s05.field_1)
    {
        sharedData_800DD180_3_s05.field_10 = Q12(1.0f);
    }
    else
    {
        sharedData_800DD180_3_s05.field_10 = Q12(0.0f);
    }

    counterC = sharedData_800DD180_3_s05.field_C;

    for (i = ARRAY_SIZE(sharedData_800DAD20_3_s05) - 1; i >= 0; i--)
    {
        if (sharedData_800DAD20_3_s05[i].field_A == 0)
        {
            if (sharedData_800DD180_3_s05.field_1 == 0)
            {
                sharedFunc_800CB71C_3_s05(i, 0);
            }
            else
            {
                sharedData_800DAD20_3_s05[i].field_A = 12;
            }

            counterC--;
            if (counterC == 0)
            {
                break;
            }
        }
    }

    D_800C4414 |= 1 << 0;
}
