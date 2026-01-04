q19_12 sharedFunc_800DC894_2_s00(s_SubCharacter* airScreamer, q19_12 dist)
{
    q19_12 var_a2;
    q19_12 var_s0;

    var_a2 = airScreamer->properties_E4.airScreamer.field_E8_4 ? Q12(0.1f) : 0;

    var_s0 = 0;
    switch (airScreamer->properties_E4.airScreamer.field_E8_8)
    {
        case 3:
            var_s0 = Q12(1.0f);
            break;

        case 2:
            var_s0 = Q12(0.7f) + (var_a2 * 2);
            break;

        case 0:
            // @unused ASM includes an `ADDIU 0x7F` which then gets overwritten.
            // Divide by 128 is assumed code which also uses `ADDIU 0x7F`.
            // Likely the rest of divide/MAX code is optimized out since `var_s0` is immediately overwritten.
            // (also possible last line was meant to be `var_s0 +=` like in case 1 below, bug?
            var_s0 = MAX((Q12(10.0f) - dist) / 128, 0);
            var_s0 = Q12(0.4f) + (var_a2 * 2);
            break;

        case 5:
            var_s0 = Q12(0.2f) + (var_a2 * 4);
            break;

        case 1:
        case 4:
            var_s0 = MAX((Q12(10.0f) - dist) / 64, 0);
            var_s0 += Q12(0.4f) + (var_a2 * 2);
            break;
    }

    return var_s0 + (sharedFunc_800D3814_0_s01(airScreamer) - Q12(1.0f)) / 8;
}
