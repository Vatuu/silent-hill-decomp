void sharedFunc_800D7E04_0_s00(s_SubCharacter* chara, s32 caseArg)
{
    s32 var_s1;

    var_s1 = NO_VALUE;

    switch (caseArg)
    {
        case 0x555:
            if (*((u8*)&chara->properties_E4[9] + 2) < 3)
            {
                var_s1 = caseArg;

                *((u8*)&chara->properties_E4[9] + 2) = 3;
                *(u16*)&chara->properties_E4[9]      = (s32)Rng_Rand16() % 819;
            }
            break;

        case 0x554:
            if (*((u8*)&chara->properties_E4[9] + 2) < 2)
            {
                var_s1 = caseArg;

                *((u8*)&chara->properties_E4[9] + 2) = 2;
                *(u16*)&chara->properties_E4[9]      = (s32)Rng_Rand16() % 1228;
            }
            break;

        case 0x553:
            if (*((u8*)&chara->properties_E4[9] + 2) < 2)
            {
                var_s1 = caseArg;

                *((u8*)&chara->properties_E4[9] + 2) = 2;
                *(u16*)&chara->properties_E4[9]      = (s32)Rng_Rand16() % 1228;
            }
            break;

        case 0x556:
            if (*((u8*)&chara->properties_E4[9] + 2) < 2)
            {
                var_s1 = caseArg;

                *((u8*)&chara->properties_E4[9] + 2) = 2;
                *(u16*)&chara->properties_E4[9]      = (s32)Rng_Rand16() % 1228;
            }
            break;

        default:
            break;
    }

    if (var_s1 != NO_VALUE)
    {
        func_8004690C(*((u16*)&chara->properties_E4[7] + 1));
        *((u16*)&chara->properties_E4[7] + 1) = var_s1;
    }
}
