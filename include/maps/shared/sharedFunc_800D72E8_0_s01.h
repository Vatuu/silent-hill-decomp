static void inline sharedFunc_800D72E8_0_s01_subfunc(s32 var_a0, s32 idx)
{
    s32 var_v1;

    if (var_a0 >= 6)
    {
        var_a0 -= 5;
    }
    else
    {
        if (var_a0 < -5)
        {
            var_a0 += 5;
        }
        else
        {
            var_a0 = 0;
        }
    }

    if (var_a0 > 0)
    {
        var_v1 = Q12(0.3333f);
    }
    else if (var_a0 < 0)
    {
        var_v1 = Q12(-0.3333f);
    }
    else
    {
        var_v1 = 0;
    }

    sharedData_800E21D0_0_s01.field_B4[idx][2] = var_v1;
    sharedData_800E21D0_0_s01.field_B4[idx][1] = Q12(1.3333f);
    sharedData_800E21D0_0_s01.field_B4[idx][3] = var_a0;
    sharedData_800E21D0_0_s01.field_B4[idx][0] = 1;
}

void sharedFunc_800D72E8_0_s01(s_SubCharacter* chara, s32 angle0, s32 angle1)
{
    s32 var_v1;

    // TODO: Not sure what these are multiplying with, different speeds?
    var_v1 = FP_MULTIPLY_PRECISE(angle0, Q12(-0.02f), Q12_SHIFT);
    if (var_v1 > FP_ANGLE(45.0f))
    {
        var_v1 = FP_ANGLE(45.0f);
    }
    else if (var_v1 < FP_ANGLE(-45.0f))
    {
        var_v1 = FP_ANGLE(-45.0f);
    }
    sharedFunc_800D72E8_0_s01_subfunc(var_v1 - chara->rotation_24.vx, 2);

    var_v1 = FP_MULTIPLY_PRECISE(angle1, Q12(0.15f), Q12_SHIFT);
    if (var_v1 > FP_ANGLE(45.0f))
    {
        var_v1 = FP_ANGLE(45.0f);
    }
    else if (var_v1 < FP_ANGLE(-45.0f))
    {
        var_v1 = FP_ANGLE(-45.0f);
    }
    sharedFunc_800D72E8_0_s01_subfunc(var_v1 - chara->rotation_24.vz, 4);
}
