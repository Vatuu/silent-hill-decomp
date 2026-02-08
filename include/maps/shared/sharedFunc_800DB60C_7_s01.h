void sharedFunc_800DB60C_7_s01(void)
{
    s32       temp_v1_4;
    s32       i;
    s32       k;
    s32       j;
    SPRT*     sprt;
    DR_TPAGE* tPage;
    s32       x;
    s32       y;
    s16       cursorX;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            sprt = (SPRT*)GsOUT_PACKET_P;

            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (sharedData_800E1694_7_s01 & (1 << ((i * 9 + k * 3) + j)))
                        {
                            setRGBC0(sprt, 0x80, 0x80, 0x80, 0x64);

                            x = sharedData_800E1578_7_s01[i][j][k][0];
                            y = sharedData_800E1578_7_s01[i][j][k][1];

                            setUV0(sprt, 0x40, 0x10);
                            setWH(sprt, 9, 9);
                            setXY0Fast(sprt, x - 0xA4, y - 0x7C);
                            sprt->clut = 0x38E;
                            addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[1], sprt, 4);
                            sprt++;
                        }
                    }
                }
            }

            tPage = (DR_TPAGE*)sprt;

            setDrawTPage(tPage, 0, 0, getTPageN(1, 0, 7, 0));
            AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[1], tPage);
            tPage++;

            GsOUT_PACKET_P = (PACKET*)tPage;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 2:
            g_SysWork.sysFlags_22A0 |= 1;
            Fs_QueueStartReadTim(FILE_TIM_3X3DOR_TIM, IMAGE_BUFFER_5, &g_ItemInspectionImg);
            Fs_QueueWaitForEmpty();
            sharedData_800E2CA8_7_s01 = 0;
            sharedData_800E2CAC_7_s01 = 0;
            sharedData_800E1694_7_s01 = 0;
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 4:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);

            sharedData_800E2CA8_7_s01 += (g_Controller0->sticks_24.sticks_0.leftX << 0xD) / 75;
            sharedData_800E2CA8_7_s01  = CLAMP_RANGE(sharedData_800E2CA8_7_s01, -0x73000, 0x73000);

            sharedData_800E2CAC_7_s01 += (g_Controller0->sticks_24.sticks_0.leftY << 0xD) / 75;
            sharedData_800E2CAC_7_s01  = CLAMP_RANGE(sharedData_800E2CAC_7_s01, -0x69000, 0x69000);

            Game_TimerUpdate();

            cursorX = FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT) + 8;
            Gfx_CursorDraw(cursorX, FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT) + 8, 8, 8, 0, 0x40, 0x20, 0x20, 0x80, 0xC0U, 0, 0xC);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
#ifndef MAP7_S02
                SD_Call(Sfx_Unk1652);
#endif
                if (sharedData_800E1694_7_s01 != 0)
                {

                    sharedData_800E1694_7_s01 = 0;
#ifdef MAP7_S02
                    SD_Call(Sfx_Unk1652);
#endif
                }
                else
                {
                    SysWork_StateStepSet(0, 8);
                }

                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        for (k = 0; k < 3; k++)
                        {
                            if ((sharedData_800E1578_7_s01[i][j][k][0] - 0xA9) > FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT) ||
                                (sharedData_800E1578_7_s01[i][j][k][0] - 0x97) < FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT))
                            {
                                continue;
                            }

                            if ((sharedData_800E1578_7_s01[i][j][k][1] - 0x81) > FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT) ||
                                (sharedData_800E1578_7_s01[i][j][k][1] - 0x6F) < FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT))
                            {
                                continue;
                            }

                            if ((SQUARE(sharedData_800E1578_7_s01[i][j][k][0] - 0xA0 - FP_FROM(sharedData_800E2CA8_7_s01, Q12_SHIFT)) +
                                 SQUARE(sharedData_800E1578_7_s01[i][j][k][1] - 0x78 - FP_FROM(sharedData_800E2CAC_7_s01, Q12_SHIFT))) > 0x51)
                            {
                                continue;
                            }

                            temp_v1_4 = 1 << ((i * 9 + k * 3) + j);

                            if (!(sharedData_800E1694_7_s01 & temp_v1_4))
                            {
                                sharedData_800E1694_7_s01 += temp_v1_4;
                            }
                            else
                            {
                                sharedData_800E1694_7_s01 -= temp_v1_4;
                            }

                            SD_Call(Sfx_Unk1652);

                            if ((sharedData_800E1694_7_s01 == sharedData_800E1574_7_s01 && Savegame_EventFlagGet(EventFlag_493)) ||
                                (sharedData_800E1694_7_s01 == sharedData_800E1570_7_s01 && Savegame_EventFlagGet(EventFlag_495)))
                            {
                                SysWork_StateStepSet(0, 5);
                            }
                        }
                    }
                }
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(0x999, false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 6:
            SD_Call(Sfx_Unk1343);

            if (!Savegame_EventFlagGet(EventFlag_493))
            {
                Savegame_EventFlagSet(EventFlag_494);
            }
            else
            {
                Savegame_EventFlagSet(EventFlag_492);
            }

            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementDelayed(0x800, false);
            break;

        case 8:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            Savegame_EventFlagClear(EventFlag_493);
            Savegame_EventFlagClear(EventFlag_495);
            break;
    }
}