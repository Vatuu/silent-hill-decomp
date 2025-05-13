void sharedFunc_800D0A60_0_s00(s32 caseArg)
{
    s32 var0;
    s32 var1;
    s32 var2;

    D_800C39A0 = caseArg;

    switch (caseArg)
    {
        case 0:
        case 2:
        case 3:
        case 7:
        case 9:
        case 11:
            var0 = 1;
            var1 = 0;
            var2 = 0;
            break;

        case 4:
            var0 = 0;
            var1 = 1;
            var2 = 0;
            break;

        case 5:
        case 10:
            var0 = 1;
            var1 = 1;
            var2 = 0;
            break;

        case 6:
        case 8:
            var0 = 1;
            var1 = 0;
            var2 = 1;
            break;

        default:
            var2 = 0;
            var1 = 0;
            var0 = 0;
            break;
    }

    sharedData_800E0CB0_0_s00 = (u16)sharedData_800E0CB0_0_s00 | ((var0 | (var1 * 16) | (var2 << 8)) << 16);
    sharedData_800E0CB8_0_s00 = (sharedData_800E0CB8_0_s00 & 0xF) | ((sharedData_800E0CB0_0_s00 >> 12) & 0x1110);
}
