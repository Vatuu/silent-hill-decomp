void sharedFunc_800D4070_1_s05(s_SubCharacter* splitHead)
{
    VECTOR3 sp20;
    VECTOR  sp30[2];
    s32     i;
    u32     temp_v1_2;
    s32     j;
    s16     var_v0_2;
    s32     animStatusIdx;
    s16     var_v1_2;
    int     new_var;

    if (g_DeltaTime0 != 0)
    {
        new_var = 0x2000;

        animStatusIdx = ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0);

        if ((ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) != 0xC) && animStatusIdx != 0xD)
        {
            if ((FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 0x14 || FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 0x23) &&
                (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 0xE && FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 0x14 ||
                 ((animStatusIdx == 1 || animStatusIdx == 9) && !Rng_TestProbabilityBits(2)) || !Rng_TestProbabilityBits(5)))
            {
                if (splitHead->model_0.anim_4.status_0 == 7)
                {
                    i = Rng_GenerateInt(0, 37);
                }
                else
                {
                    i = Rng_GenerateInt(0, 21);
                }

                sharedFunc_800D4408_1_s05(&sp20, sharedData_800D5AB0_1_s05[i].idx, sharedData_800D5AB0_1_s05[i].vec.vx, sharedData_800D5AB0_1_s05[i].vec.vy, sharedData_800D5AB0_1_s05[i].vec.vz);

                sp30[0].vx = sp20.vx >> 4;
                sp30[0].vy = sp20.vy >> 4;
                sp30[0].vz = sp20.vz >> 4;

                if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) >= 0xF &&
                    FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 0x14)
                {
                    var_v1_2 = new_var;
                    if (sharedData_800D5AB0_1_s05[i].idx < 0x14)
                    {
                        var_v0_2 = splitHead->rotation_24.vy + 0x400;
                    }
                    else
                    {
                        var_v0_2 = splitHead->rotation_24.vy - 0x400;
                    }
                }
                else
                {
                    temp_v1_2 = splitHead->moveSpeed_38;

                    if (splitHead->moveSpeed_38 > 0)
                    {
                        var_v0_2 = splitHead->rotation_24.vy;
                        var_v1_2 = temp_v1_2 >> 1;
                    }
                    else
                    {
                        temp_v1_2 = -temp_v1_2;
                        var_v1_2  = temp_v1_2 >> 1;
                        var_v0_2  = splitHead->rotation_24.vy + 0x800;
                    }
                }

                sharedFunc_800CBE7C_1_s05(sp30[0].vx, sp30[0].vy, sp30[0].vz, var_v1_2, var_v0_2 & 0xFFF);
            }
        }
    }

    switch (splitHead->model_0.anim_4.status_0)
    {
        case 16:
        case 17:
        case 26:
        case 27:
            splitHead->properties_E4.splitHead.field_EA = MAX(0, splitHead->properties_E4.splitHead.field_EA - g_DeltaTime0 / 68);

        case 3:
        case 5:
        case 28:
        case 29:
            for (i = 0; i < 6; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    sharedFunc_800D4408_1_s05(&sp20, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].idx, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vx,
                                              sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vy, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vz);

                    sp30[j].vx = sp20.vx >> 4;
                    sp30[j].vy = sp20.vy >> 4;
                    sp30[j].vz = sp20.vz >> 4;
                }

                sharedFunc_800CCE2C_1_s05(sharedData_800D5BE0_1_s05[i][2], splitHead->properties_E4.splitHead.field_EA,
                                          sp30[0].vx, sp30[0].vy, sp30[0].vz, sp30[1].vx, sp30[1].vy, sp30[1].vz);
            }
            break;
    }
}