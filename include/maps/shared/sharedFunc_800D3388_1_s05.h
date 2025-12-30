void sharedFunc_800D3388_1_s05(s_SubCharacter* splitHead, s32* arg1, s32* arg2)
{
    u8                           sp18[9];
    u8                           sp28[9];
    s_sharedFunc_800D4594_1_s05  sp38[9];
    s16                          spC8[9];
    s32                          spE0;
    s32                          spE4;
    s32                          temp_s7;
    s32                          j;
    s32                          var_s6;
    s32                          var_a0;
    s32                          var_a1;
    s32                          i;
    s32                          new_var;
    s_sharedFunc_800D4594_1_s05* ptr0;
    s_sharedFunc_800D4594_1_s05* ptr1;

    #define splitHeadProps = splitHead->properties_E4.splitHead

    var_s6 = 0;

    if (splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 2)
    {
        *arg2 = 0;
        *arg1 = 0;
        return;
    }

    spE0 = g_SysWork.playerWork_4C.player_0.position_18.vx + *arg1;
    spE4 = g_SysWork.playerWork_4C.player_0.position_18.vz + *arg2;

    for (i = sharedData_800D5AAE_1_s05; i < 9; i++)
    {
        sharedFunc_800D4594_1_s05(&sp38[var_s6], spE0, spE4, &sharedData_800D8618_1_s05[i], &sharedData_800D8618_1_s05[i == 8 ? sharedData_800D5AAE_1_s05 : i + 1]);

        sp18[i]              = sp38[var_s6].field_C;
        sp28[i]              = sp38[var_s6].field_D;
        sp38[var_s6].field_E = i;

        if (g_SysWork.playerWork_4C.player_0.field_D4.field_0 >= sp38[var_s6].field_0)
        {
            var_s6++;
        }
    }

    temp_s7 = var_s6;

    if (var_s6 != 0)
    {
        do
        {
            for (var_s6 = 0, j = 0; j < 5 && var_s6 == 0; j++)
            {
                for (i = 0; i < temp_s7; i++)
                {
                    if (j < 3)
                    {
                        if ((j == 0 && sp38[i].field_D != 0 && sp38[i].field_C == 2) ||
                            (j == 1 && sp38[i].field_C == j && sp38[(i + 1) % temp_s7].field_C == 0 &&
                             (sp38[i].field_E == 8 ? sharedData_800D5AAE_1_s05 : sp38[i].field_E + 1) == sp38[(i + 1) % temp_s7].field_E) ||
                            (j == 2 && sp38[i].field_D != 0))
                        {
                            ptr0 = &sp18[i * 16] + 0x20;
                            ptr1 = &sp18[var_s6 * 16] + 0x20;

                            ptr1->field_0 = ptr0->field_0;
                            ptr1->field_4 = ptr0->field_4;
                            ptr1->field_8 = ptr0->field_8;
                            ptr1->field_C = ptr0->field_C;
                            ptr1->field_D = ptr0->field_D;
                            ptr1->field_E = ptr0->field_E;

                            sp38[var_s6].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.field_0 - sp38[var_s6].field_0;
                            spC8[var_s6]         = ratan2(spE0 - sp38[i].field_4, spE4 - sp38[i].field_8);

                            var_s6++;

                            if (j == 1)
                            {
                                i += 1;
                            }
                        }
                    }
                    else
                    {

                        if (j == 3)
                        {
                            if (sp38[i].field_E != sharedData_800D5AAE_1_s05)
                            {
                                var_a0 = sp38[i].field_E - 1;
                            }
                            else
                            {
                                var_a0 = 8;
                            }

                            if (sp38[i].field_E == 8)
                            {
                                var_a1 = sharedData_800D5AAE_1_s05;
                            }
                            else
                            {
                                var_a1 = sp38[i].field_E + 1;
                            }
                        }
                        else
                        {
                            if (sharedData_800D5CF8_1_s05[sp38[i].field_E] != 0)
                            {
                                if (sp38[i].field_E == 8)
                                {
                                    var_a0 = sharedData_800D5AAE_1_s05;
                                }
                                else
                                {
                                    var_a0 = sp38[i].field_E + 1;
                                }
                                var_a1 = 0;
                            }
                            else
                            {
                                if (sp38[i].field_E != sharedData_800D5AAE_1_s05)
                                {
                                    var_a0 = sp38[i].field_E - 1;
                                }
                                else
                                {
                                    var_a0 = 8;
                                }
                                var_a1 = 0;
                            }
                        }

                        new_var = var_a0;

                        if ((j == 3 && sharedData_800D5CF8_1_s05[sp38[i].field_E] == 2 &&
                             (sharedData_800D5D08_1_s05[sp38[i].field_E] != 0 ||
                              (sharedData_800D5CF8_1_s05[new_var] == 1 && sharedData_800D5D08_1_s05[new_var] != 0) ||
                              (sharedData_800D5CF8_1_s05[var_a1] == 0 && sharedData_800D5D08_1_s05[var_a1] != 0))) ||

                            (j == 4 && sharedData_800D5CF8_1_s05[sp38[i].field_E] != 2 &&
                             (sharedData_800D5D08_1_s05[sp38[i].field_E] != 0 || sharedData_800D5D08_1_s05[new_var] != 0)))
                        {
                            ptr0 = &sp18[i * 16] + 0x20;
                            ptr1 = &sp18[var_s6 * 16] + 0x20;

                            ptr1->field_0 = ptr0->field_0;
                            ptr1->field_4 = ptr0->field_4;
                            ptr1->field_8 = ptr0->field_8;
                            ptr1->field_C = ptr0->field_C;
                            ptr1->field_D = ptr0->field_D;
                            ptr1->field_E = ptr0->field_E;

                            sp38[var_s6].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.field_0 + sp38[var_s6].field_0;
                            spC8[var_s6]         = ratan2(sp38[i].field_4 - spE0, sp38[i].field_8 - spE4);

                            var_s6++;

                            sp28[sp38[i].field_E] = sharedData_800D5D08_1_s05[sp38[i].field_E];
                            sp18[sp38[i].field_E] = sharedData_800D5CF8_1_s05[sp38[i].field_E];
                        }
                    }
                }
            }

        } while (0); // @hack

        if (var_s6 == 0)
        {
            for (i = 0; i < temp_s7; i++)
            {
                sp38[i].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.field_0 + sp38[i].field_0;
                spC8[i]         = ratan2(sp38[i].field_4 - spE0, sp38[i].field_8 - spE4);
            }
            var_s6 = temp_s7;
        }
    }

    *arg2 = 0;
    *arg1 = 0;

    for (i = 0; i < var_s6; i++)
    {
        *arg1 += FP_MULTIPLY(sp38[i].field_0, Math_Sin(spC8[i]), Q12_SHIFT);
        *arg2 += FP_MULTIPLY(sp38[i].field_0, Math_Cos(spC8[i]), Q12_SHIFT);

        if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 0xD && FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 0x22 &&
            (sp38[i].field_E < 2 || sp38[i].field_E > 6))
        {
            sharedData_800D5AAF_1_s05 = 1;
        }
    }

    for (i = 0; i < 9; i++)
    {
        sharedData_800D5CF8_1_s05[i] = sp18[i];
        sharedData_800D5D08_1_s05[i] = sp28[i];
    }

    #undef splitHeadProps
}
