void sharedFunc_800D8714_0_s01(s_SubCharacter* arg0, s32 arg1, s32 arg2)
{
    s32 arg2Cpy;
    s32 var_s2;
    s32 temp_v0;
    s16* ptr;
    s_func_800D2E04* base;
    s32 idx;
    s32 x;
    s32 z;

    arg2Cpy = arg2;
    idx = sharedFunc_800D4A80_0_s01(arg0);
    base = &sharedData_800CAA98_0_s01;
    temp_v0 = base->field_D5C[idx][1];
    arg0->field_CA = base->field_D5C[idx][0];

    if (arg1 == 0) 
    {
        arg0->field_D8.offsetX_4 = 0;
        arg0->field_D8.offsetZ_6 = 0;
        arg0->field_D4 = temp_v0;
        return;
    }
    var_s2 = temp_v0 - 0x666;
    if (var_s2 < 0)
    {
        var_s2 = 0;
    }
    if (arg1 < 0)
    {
        arg2Cpy ^= 0x800;
    }

    x = FP_MULTIPLY_PRECISE(var_s2,  Math_Sin(arg2Cpy), 12);
    z = FP_MULTIPLY_PRECISE(var_s2,  Math_Cos(arg2Cpy), 12);

    arg0->field_D8.offsetX_4 = x;
    arg0->field_D8.offsetZ_6 = z;
    arg0->field_D4 = 0x666;
}
