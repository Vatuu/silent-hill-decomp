s32 sharedFunc_800D31D0_0_s01(s_SubCharacter* chara, VECTOR3* arg1, s32 arg2)
{
    s16 rotY;
    s32 temp_s0_2;
    s32 temp_v0_3;
    s32 temp_s3;
    s32 var_s1;
    s64 temp;
    u64 temp2;
    s32 temp3;

    temp3 = sharedData_800CAA98_0_s01.field_D3C[chara->properties_E4.unk0.field_E8_4][chara->properties_E4.unk0.field_E8_8];

    var_s1  = sharedData_800CAA98_0_s01.field_D24[1][temp3][0];
    temp_s3 = sharedData_800CAA98_0_s01.field_D24[1][temp3][1];

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case -1:
            break;

        case 0:
            var_s1 += 0x800;
            break;

        case 1:
            var_s1 += 0x1000;
            break;
    }

    if (chara->model_0.state_2 == 3 || chara->model_0.state_2 == 9)
    {
        var_s1 += 0x1000;
    }

    rotY = chara->rotation_24.vy;

    temp_s0_2 = arg1->vx - (chara->position_18.vx + FP_MULTIPLY_PRECISE(temp_s3, Math_Sin(rotY), Q12_SHIFT));
    temp_v0_3 = arg1->vz - (chara->position_18.vz + FP_MULTIPLY_PRECISE(temp_s3, Math_Cos(rotY), Q12_SHIFT));

    temp  = FP_SQUARE_PRECISE(temp_s0_2, Q12_SHIFT) + FP_SQUARE_PRECISE(temp_v0_3, Q12_SHIFT);
    temp2 = FP_SQUARE_PRECISE(var_s1, Q12_SHIFT);
    temp2 = FP_MULTIPLY_PRECISE(temp2, arg2, Q12_SHIFT);

    if (temp > temp2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}