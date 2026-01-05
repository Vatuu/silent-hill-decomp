q19_12 sharedFunc_800DC894_2_s00(s_SubCharacter* airScreamer, q19_12 dist)
{
    q19_12 extraChance;
    q19_12 baseChance;

    extraChance = airScreamer->properties_E4.airScreamer.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

    baseChance = Q12(0.0f);
    switch (airScreamer->properties_E4.airScreamer.field_E8_8)
    {
        case 3:
            baseChance = Q12(1.0f);
            break;

        case 2:
            baseChance = Q12(0.7f) + (extraChance * 2);
            break;

        case 0:
            // @unused ASM includes an `ADDIU 0x7F` which then gets overwritten.
            // Divide by 128 is assumed code which also uses `ADDIU 0x7F`.
            // Likely the rest of divide/MAX code is optimized out since `var_s0` is immediately overwritten.
            // (also possible last line was meant to be `var_s0 +=` like in case 1 below, bug?
            baseChance = MAX((Q12(10.0f) - dist) / 128, Q12(0.0f));
            baseChance = Q12(0.4f) + (extraChance * 2);
            break;

        case 5:
            baseChance = Q12(0.2f) + (extraChance * 4);
            break;

        case 1:
        case 4:
            baseChance = MAX((Q12(10.0f) - dist) / 64, Q12(0.0f));
            baseChance += Q12(0.4f) + (extraChance * 2);
            break;
    }

    return baseChance + (sharedFunc_800D3814_0_s01(airScreamer) - Q12(1.0f)) / 8;
}
