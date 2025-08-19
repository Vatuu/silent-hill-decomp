#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || \
    defined(MAP4_S05) || defined(MAP5_S00) || defined(MAP6_S00) || defined(MAP6_S03)
#define SET_800E32D0 1
#endif

void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1)
#ifdef SHARED_FUNC_IMPL
{
    s32 temp_a1;
    s32 shiftAmt;
    s32 var_s0;
    s32 var_s1;

    if (arg1 != 127)
    {
        if (arg1 == 2)
        {
            D_800C39A0 = 3;
        }
        else
        {
            D_800C39A0 = arg1;
        }
    }

    sharedData_800E0CBA_0_s00 = arg0;

#ifdef SET_800E32D0
    sharedData_800E32D0_0_s00 = 0;
#endif

    switch (arg0)
    {
        case 0:
            var_s1                    = 0;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 0;
            break;
        case 1:
            var_s1                    = 1;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 1;
            sharedData_800DFB70_0_s00 = 0;
            break;
        case 2:
            var_s1                    = 1;
            var_s0                    = 1;
            sharedData_800DFB6C_0_s00 = 1;
            sharedData_800DFB70_0_s00 = 0;
            break;
        case 5:
            var_s1                    = 2;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 1;
#ifdef SET_800E32D0
            sharedData_800E32D0_0_s00 = 135000;
#endif
            break;
        case 6:
            var_s1                    = 2;
            var_s0                    = 1;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 1;
#ifdef SET_800E32D0
            sharedData_800E32D0_0_s00 = 135000;
#endif
            break;
        default:
            var_s0                    = 0;
            var_s1                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 0;
            break;
    }

    if (var_s1 == 0)
    {
        sharedData_800E0CB0_0_s00 = var_s0 * 0x1000;
    }
    else
    {
        sharedData_800E0CB0_0_s00 = (var_s1 * 0x4000) | (var_s0 * 0x1000);

        temp_a1  = var_s0 + 4;
        shiftAmt = (2 - var_s1) * 6;

        sharedData_800E0CB0_0_s00 = sharedData_800E0CB0_0_s00 | (temp_a1 << shiftAmt) | (temp_a1 << (shiftAmt + 3));
    }

    sharedFunc_800D0A60_0_s00(D_800C39A0);

    sharedData_800E0CA8_0_s00 = var_s1;
    sharedData_800E0CAC_0_s00 = var_s0;
}
#else
;
#endif

#ifdef SET_800E32D0
#undef SET_800E32D0
#endif
