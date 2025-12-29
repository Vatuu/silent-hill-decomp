void sharedFunc_800D274C_1_s05(s_SubCharacter* splitHead, s_AnmHeader* anmHdr) 
{
    SVECTOR     sp10;
    MATRIX      sp18;
    s32         i;
    s_AnimInfo* animInfo;

    #define splitHeadProps splitHead->properties_E4.splitHeadProps

    splitHead->rotation_24.vy = func_8005BF38(splitHead->rotation_24.vy);

    switch (splitHead->model_0.anim_4.status_0)
    {
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
        case 14:
        case 16:
        case 17:
        case 26:
        case 27:
        case 28:
        case 29:
            func_8003DD80(splitHead->model_0.charaId_0, 2);
            break;

        default:
            func_8003DD80(splitHead->model_0.charaId_0, 1);
            break;
    }

    switch (splitHead->model_0.anim_4.status_0)
    {
        case 19:
        case 23:
            switch (splitHead->model_0.controlState_2)
            {
                case SplitHeadControl_2:
                case SplitHeadControl_7:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT);

                    if (splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0])
                    {
                        if (splitHead->moveSpeed_38 >= Q12(0.0f))
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(8.0f));
                        } 
                        else
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-8.0f));
                        }
                    }
                    break;

                case SplitHeadControl_1:
                case SplitHeadControl_3:
                    if (!(splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x8))
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT), Q12(12.0f));

                        if (splitHead->moveSpeed_38 > Q12(0.0f))
                        {
                            splitHead->properties_E4.dummy.properties_E8[0].val16[0] |= 0x20;
                        } 
                        else if (splitHead->moveSpeed_38 < Q12(0.0f))
                        {
                            splitHead->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 5);
                        }
                    }
                    else
                    {
                        if (splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x20)
                        {
                            sharedData_800D5884_1_s05 = Q12(24.0f);
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = Q12(-24.0f);
                        }
                    }
                    break;

                case SplitHeadControl_4:
                    if (!(splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x8))
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT), Q12(12.0f));
                    }
                    else
                    {
                        if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 187 &&
                            FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 203) 
                        {
                            sharedData_800D5884_1_s05 = Q12(24.0f);
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = Q12(-24.0f);
                        }
                    }
                    break;

                case SplitHeadControl_5:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT);

                    if (splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0])
                    {
                        if (splitHead->moveSpeed_38 >= Q12(0.0f))
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(10.0f));
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-10.0f));
                        }
                    }
                    break;

                case SplitHeadControl_6:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT);

                    if (splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x20)
                    {
                        sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(12.0f));
                    }
                    else
                    {
                        sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-12.0f));
                    }
                    break;
            }

            SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0].duration_8.constant = sharedData_800D5884_1_s05;

        case 7:
            break;

        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(12.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(8.0f);
            }
            else
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(16.0f);
            }
            break;
    }

    Math_MatrixTransform(&splitHead->position_18, (SVECTOR* )&splitHead->rotation_24, sharedData_800D8610_1_s05);

    animInfo = &SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&splitHead->model_0, anmHdr, sharedData_800D8610_1_s05, animInfo);

    if ((splitHead->model_0.anim_4.status_0 == 23) && ((splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0])))
    {
        if ((splitHead->properties_E4.dummy.properties_E8[1].val16[0] < splitHead->rotation_24.vy && splitHead->moveSpeed_38 >= Q12(0.0f)) ||
            (splitHead->rotation_24.vy < splitHead->properties_E4.dummy.properties_E8[1].val16[0] && splitHead->moveSpeed_38 < Q12(0.0f)))
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = CLAMP_LOW(splitHead->properties_E4.dummy.properties_E8[1].val16[1] - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, Q12_SHIFT), -0xC0);
        }
        else
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = MIN(splitHead->properties_E4.dummy.properties_E8[1].val16[1] + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, Q12_SHIFT), 0xC0);
        }
    }
    else
    {
        if (splitHead->properties_E4.dummy.properties_E8[1].val16[1] > 0)
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = CLAMP_LOW(splitHead->properties_E4.dummy.properties_E8[1].val16[1] - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, Q12_SHIFT), Q12(0.0f));
        }
        else
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = MIN(splitHead->properties_E4.dummy.properties_E8[1].val16[1] + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, Q12_SHIFT), Q12(0.0f));
        }
    }

    if (splitHead->properties_E4.dummy.properties_E8[1].val16[1] != 0)
    {
        *(s32*)&sp10 = splitHead->properties_E4.dummy.properties_E8[1].val16[1] << 16;
        sp10.vz= 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);
        MulMatrix(&sharedData_800D8610_1_s05[1].coord, &sp18);

        *(s32*)&sp10 = (splitHead->properties_E4.dummy.properties_E8[1].val16[1] >> 3) << 16;
        sp10.vz = 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);

        for (i = 18; i < 25; i++)
        {
            MulMatrix(&sharedData_800D8610_1_s05[i].coord, &sp18);
        }
    }

    splitHead->properties_E4.dummy.properties_E8[1].val16[0] = splitHead->rotation_24.vy;

    #undef splitHeadProps
}
