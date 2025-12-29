void sharedFunc_800D274C_1_s05(s_SubCharacter* splitHead, s_AnmHeader* anmHdr) 
{
    SVECTOR     sp10;
    MATRIX      sp18;
    s32         i;
    s_AnimInfo* animInfo;

    #define splitHeadProps splitHead->properties_E4.splitHead

    splitHead->rotation_24.vy = func_8005BF38(splitHead->rotation_24.vy);

    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_1, false):
        case ANIM_STATUS(SplitHeadAnim_1, true):
        case ANIM_STATUS(SplitHeadAnim_2, false):
        case ANIM_STATUS(SplitHeadAnim_2, true):
        case ANIM_STATUS(SplitHeadAnim_4, false):
        case ANIM_STATUS(SplitHeadAnim_7, false):
        case ANIM_STATUS(SplitHeadAnim_8, false):
        case ANIM_STATUS(SplitHeadAnim_8, true):
        case ANIM_STATUS(SplitHeadAnim_13, false):
        case ANIM_STATUS(SplitHeadAnim_13, true):
        case ANIM_STATUS(SplitHeadAnim_14, false):
        case ANIM_STATUS(SplitHeadAnim_14, true):
            func_8003DD80(splitHead->model_0.charaId_0, 2);
            break;

        default:
            func_8003DD80(splitHead->model_0.charaId_0, 1);
            break;
    }

    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_9, true):
        case ANIM_STATUS(SplitHeadAnim_11, true):
            switch (splitHead->model_0.controlState_2)
            {
                case SplitHeadControl_2:
                case SplitHeadControl_7:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT);

                    if (splitHead->rotation_24.vy != splitHeadProps.angle_EC)
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
                    if (!(splitHeadProps.flags_E8 & SplitHeadFlag_3))
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, Q12(9.3f), Q12_SHIFT), Q12(12.0f));

                        if (splitHead->moveSpeed_38 > Q12(0.0f))
                        {
                            splitHeadProps.flags_E8 |= SplitHeadFlag_5;
                        } 
                        else if (splitHead->moveSpeed_38 < Q12(0.0f))
                        {
                            splitHeadProps.flags_E8 &= ~(1 << 5);
                        }
                    }
                    else
                    {
                        if (splitHeadProps.flags_E8 & SplitHeadFlag_5)
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
                    if (!(splitHeadProps.flags_E8 & SplitHeadFlag_3))
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

                    if (splitHead->rotation_24.vy != splitHeadProps.angle_EC)
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

                    if (splitHeadProps.flags_E8 & SplitHeadFlag_5)
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

        case ANIM_STATUS(SplitHeadAnim_3, true):
            break;

        case ANIM_STATUS(SplitHeadAnim_2, true):
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

    Math_MatrixTransform(&splitHead->position_18, (SVECTOR*)&splitHead->rotation_24, sharedData_800D8610_1_s05);

    animInfo = &SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&splitHead->model_0, anmHdr, sharedData_800D8610_1_s05, animInfo);

    // TODO: Are the unconverted numbers angles or time values?
    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true) && (splitHead->rotation_24.vy != splitHeadProps.angle_EC))
    {
        if ((splitHeadProps.angle_EC   < splitHead->rotation_24.vy && splitHead->moveSpeed_38 >= Q12(0.0f)) ||
            (splitHead->rotation_24.vy < splitHeadProps.angle_EC   && splitHead->moveSpeed_38 <  Q12(0.0f)))
        {
            splitHeadProps.field_EE = CLAMP_LOW(splitHeadProps.field_EE - FP_MULTIPLY_PRECISE(g_DeltaTime0, 160, Q12_SHIFT), -192);
        }
        else
        {
            splitHeadProps.field_EE = MIN(splitHeadProps.field_EE + FP_MULTIPLY_PRECISE(g_DeltaTime0, 160, Q12_SHIFT), 192);
        }
    }
    else
    {
        if (splitHeadProps.field_EE > Q12(0.0f))
        {
            splitHeadProps.field_EE = CLAMP_LOW(splitHeadProps.field_EE - FP_MULTIPLY_PRECISE(g_DeltaTime0, 160, Q12_SHIFT), Q12(0.0f));
        }
        else
        {
            splitHeadProps.field_EE = MIN(splitHeadProps.field_EE + FP_MULTIPLY_PRECISE(g_DeltaTime0, 160, Q12_SHIFT), Q12(0.0f));
        }
    }

    if (splitHeadProps.field_EE != Q12(0.0f))
    {
        *(s32*)&sp10 = splitHeadProps.field_EE << 16;
        sp10.vz= 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);
        MulMatrix(&sharedData_800D8610_1_s05[1].coord, &sp18);

        *(s32*)&sp10 = (splitHeadProps.field_EE >> 3) << 16;
        sp10.vz = 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);

        for (i = 18; i < 25; i++)
        {
            MulMatrix(&sharedData_800D8610_1_s05[i].coord, &sp18);
        }
    }

    splitHeadProps.angle_EC = splitHead->rotation_24.vy;

    #undef splitHeadProps
}
