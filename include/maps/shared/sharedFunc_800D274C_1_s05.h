void sharedFunc_800D274C_1_s05(s_SubCharacter* splitHead, s_AnmHeader* arg1) 
{
    SVECTOR sp10;
    MATRIX sp18;
    s32 var_s2;
    s_AnimInfo* temp_a3;

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
                case 2:
                case 7:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, 0x94CC, 0xC);
                    if (splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0]) 
                    {
                        if (splitHead->moveSpeed_38 >= 0) 
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, 0x8000);
                        } 
                        else 
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, -0x8000);
                        }
                    }
                    break;
                    
                case 1:
                case 3:
                    if (!(splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 8)) 
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, 0x94CC, 0xC), 0xC000);
                        
                        if (splitHead->moveSpeed_38 > 0) 
                        {
                            splitHead->properties_E4.dummy.properties_E8[0].val16[0] |= 0x20;
                        } 
                        else if (splitHead->moveSpeed_38 < 0) 
                        {
                            splitHead->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFDF;
                        }
                    } 
                    else 
                    {
                        if (splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x20) 
                        {
                            sharedData_800D5884_1_s05 = 0x18000;
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = -0x18000;
                        }
                    }
                    break;
                    
                case 4:
                    if (!(splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 8)) 
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, 0x94CC, 0xC), 0xC000);
                    } 
                    else 
                    {
                        if ((FP_FROM(splitHead->model_0.anim_4.time_4, 0xC) > 0xBB && FP_FROM(splitHead->model_0.anim_4.time_4, 0xC) < 0xCB)) 
                        {
                            sharedData_800D5884_1_s05 = 0x18000;
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = -0x18000;
                        }
                    }
                    break;
                    
                case 5:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, 0x94CC, 0xC);
                    if (splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0]) 
                    {
                        if (splitHead->moveSpeed_38 >= 0) 
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, 0xA000);
                        } 
                        else 
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, -0xA000);
                        }
                    }
                    break;
                    
                case 6:
                    sharedData_800D5884_1_s05 = FP_MULTIPLY_PRECISE(splitHead->moveSpeed_38, 0x94CC, 0xC);
                    if (splitHead->properties_E4.dummy.properties_E8[0].val16[0] & 0x20) 
                    {
                        sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, 0xC000);
                    } 
                    else 
                    {
                        sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, -0xC000);
                    }
                    break;
            }
            SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0].duration_8.constant = sharedData_800D5884_1_s05;
        
        case 7:
            break;
            
        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == 0) 
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = 0xC000;
            } 
            else if (g_SavegamePtr->gameDifficulty_260 == -1) 
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = 0x8000;
            } 
            else 
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = 0x10000;
            }
            break;
    }
    
    Math_MatrixTransform(&splitHead->position_18, (SVECTOR* )&splitHead->rotation_24, sharedData_800D8610_1_s05);
    
    temp_a3 = &SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0];
    temp_a3->updateFunc_0(&splitHead->model_0, arg1, sharedData_800D8610_1_s05, temp_a3);
    
    if ((splitHead->model_0.anim_4.status_0 == 0x17) && ((splitHead->rotation_24.vy != splitHead->properties_E4.dummy.properties_E8[1].val16[0]))) 
    {
        if ((splitHead->properties_E4.dummy.properties_E8[1].val16[0] < splitHead->rotation_24.vy && splitHead->moveSpeed_38 >= 0) ||
            (splitHead->rotation_24.vy < splitHead->properties_E4.dummy.properties_E8[1].val16[0] && splitHead->moveSpeed_38 < 0)) 
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = CLAMP_LOW(splitHead->properties_E4.dummy.properties_E8[1].val16[1] - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, 0xC), -0xC0);
        }
        else
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = MIN(splitHead->properties_E4.dummy.properties_E8[1].val16[1] + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, 0xC), 0xC0);
        }
    } 
    else 
    {
        if (splitHead->properties_E4.dummy.properties_E8[1].val16[1] > 0) 
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = CLAMP_LOW(splitHead->properties_E4.dummy.properties_E8[1].val16[1] - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, 0xC), 0);
        } 
        else 
        {
            splitHead->properties_E4.dummy.properties_E8[1].val16[1] = MIN(splitHead->properties_E4.dummy.properties_E8[1].val16[1] + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0xA0, 0xC), 0);
        }
    }
    
    if (splitHead->properties_E4.dummy.properties_E8[1].val16[1] != 0) 
    {
        *(s32*)&sp10 = splitHead->properties_E4.dummy.properties_E8[1].val16[1] << 0x10;
        sp10.vz= 0;
        
        Math_RotMatrixZxyNegGte(&sp10, &sp18);
        MulMatrix(&sharedData_800D8610_1_s05[1].coord, &sp18);
        
        *(s32*)&sp10 = (splitHead->properties_E4.dummy.properties_E8[1].val16[1] >> 3) << 0x10;
        sp10.vz = 0;
        
        Math_RotMatrixZxyNegGte(&sp10, &sp18);
        
        for (var_s2 = 0x12; var_s2 < 0x19; var_s2++)
        {
            MulMatrix(&sharedData_800D8610_1_s05[var_s2].coord, &sp18);
        }
    }
    
    splitHead->properties_E4.dummy.properties_E8[1].val16[0] = splitHead->rotation_24.vy;
}