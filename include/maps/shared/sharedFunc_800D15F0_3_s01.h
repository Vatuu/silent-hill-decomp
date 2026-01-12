void sharedFunc_800D15F0_3_s01(void)
{
    s32 j;
    s32 i;
    s16 cursorX;
    s32 temp;
    s32 temp2;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 9 && g_SysWork.sysStateStep_C[0] < 17)
    {
        SysWork_StateStepSet(0, 17);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:

            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(false, true, false, false, false);
            sharedData_800D4D14_3_s01 = 0;
            sharedData_800D4D10_3_s01 = 0;

            for (i = 0; i < 8; i++)
            {
                Savegame_EventFlagClear(EventFlag_216 + i);
            }

            for (i = 0; i < 4; i++)
            {
                if (Savegame_EventFlagGet(EventFlag_212 + i))
                {
                    sharedData_800D4D14_3_s01 = (sharedData_800D4CD4_3_s01[i + 1][1] - 0x6E) << 12;
                    sharedData_800D4D18_3_s01 = i;
                }
            }

            SysWork_StateStepIncrement(0);

        case 1:
#ifdef MAP3_S01
            if (Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_OperatingPrepRoomArrow) &&
                Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_CorridorMidArrows))
            {
                func_800862F8(7, 0x731, false);
            }
            else
            {
                func_800862F8(7, 0x730, false);
            }
#else
            func_800862F8(7, 0x733, false);
#endif
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(true, true, false, false, false);
            break;

        case 3:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, false, false, false);
            break;

        case 4:
            func_800862F8(2, 0, false);
            sharedData_800D4D10_3_s01 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            sharedData_800D4D10_3_s01  = CLAMP_RANGE(sharedData_800D4D10_3_s01, Q12(-70.0f), Q12(68.0f));

            sharedData_800D4D14_3_s01 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            sharedData_800D4D14_3_s01  = CLAMP_RANGE(sharedData_800D4D14_3_s01, Q12(-110.0f), Q12(110.0f));

            Game_TimerUpdate();

            cursorX = FP_FROM(sharedData_800D4D10_3_s01, Q12_SHIFT) + 8;

            func_800881B8(cursorX, FP_FROM(sharedData_800D4D14_3_s01, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 6);
                break;
            }

            if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0))
            {
                break;
            }

#ifdef MAP3_S01
            for (i = 0; i < 7; i++)
#else
            for (i = 0; i < 6; i++)
#endif
            {
                temp = sharedData_800D4CD4_3_s01[i][0];

                if ((temp - 160) > FP_FROM(sharedData_800D4D10_3_s01, Q12_SHIFT))
                {
                    continue;
                }

                switch (i)
                {
                    case 0:
                        if ((temp - 140) >= FP_FROM(sharedData_800D4D10_3_s01, Q12_SHIFT))
                        {
                            break;
                        }
                        continue;

                    default:
                        if ((temp - 141) < FP_FROM(sharedData_800D4D10_3_s01, Q12_SHIFT))
                        {
                            continue;
                        }
                        break;
                }

                if ((sharedData_800D4CD4_3_s01[i][1] - 120) > FP_FROM(sharedData_800D4D14_3_s01, Q12_SHIFT) ||
                    (sharedData_800D4CD4_3_s01[i][1] - 100) < FP_FROM(sharedData_800D4D14_3_s01, Q12_SHIFT))
                {
                    continue;
                }
#if defined(MAP3_S03) || defined(MAP3_S04) || defined(MAP3_S05)
                SD_Call(Sfx_Unk1500);
#endif
                if (i == 5)
                {
#ifdef MAP3_S01
                    if (Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_OperatingPrepRoomArrow) &&
                        Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_CorridorMidArrows))
                    {
                        Savegame_EventFlagSet(EventFlag_224);
                        SysWork_StateStepSet(0, 5);
                        SD_Call(Sfx_Unk1500);
                        sharedData_800D4D10_3_s01 = 1;
                    }
#endif
                }
                else
                {
#ifdef MAP3_S01
                    if (i != 6 && (i <= 0 || !Savegame_EventFlagGet(EventFlag_M3S01_GeneratorOn + i)))
#else
                    if ((i <= 0 || !Savegame_EventFlagGet(EventFlag_M3S01_GeneratorOn + i)))
#endif
                    {
                        if (i != 0)
                        {
                            Savegame_EventFlagSet(EventFlag_215 + i);
                            sharedData_800D4D10_3_s01 = 1;

                            temp2                     = 1;
                            sharedData_800D4D18_3_s01 = ABS((sharedData_800D4D18_3_s01 + temp2) - i);
                            SysWork_StateStepSet(0, 5);
                        }
                        else
                        {
                            for (j = 0; j < 4; j++)
                            {
                                if (Savegame_EventFlagGet(EventFlag_212 + j))
                                {
                                    Savegame_EventFlagSet(EventFlag_216 + j);
                                    break;
                                }
                            }
                            sharedData_800D4D10_3_s01 = 0;
                            SysWork_StateStepSet(0, 5);
                        }
                    }
#ifdef MAP3_S01
                    SD_Call(Sfx_Unk1500);
#endif
                }
            }
            break;

        case 5:
            func_800862F8(2, 0, false);

            for (i = 0; i < 4; i++)
            {
                Savegame_EventFlagClear(EventFlag_212 + i);
            }
            sharedData_800D4D0C_3_s01.vy = 0;
            sharedData_800D4D0C_3_s01.vx = 0;

#ifdef MAP3_S01
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = -0x500;
            g_SysWork.playerWork_4C.player_0.position_18.vx = 0x3A999;
            g_SysWork.playerWork_4C.player_0.position_18.vz = 0x13666;
#else
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = -0x600;
            g_SysWork.playerWork_4C.player_0.position_18.vx = 0x12333;
            g_SysWork.playerWork_4C.player_0.position_18.vz = 0x3BB33;
#endif
            SysWork_StateStepSet(0, 8);
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        case 7:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(false, false, false, false, false);
            break;

        case 8:
            if (sharedData_800D4D10_3_s01 != 0)
            {
                SD_Call(Sfx_Unk1499);
            }
            SysWork_StateStepIncrement(0);

        case 9:
            func_800862F8(2, 0, false);

            if (sharedData_800D4D10_3_s01 != 0)
            {
                g_SysWork.field_28 += g_DeltaTime0;

                if (g_SysWork.field_28 > 0x1000)
                {
                    g_SysWork.field_28 = 0x1000;
                }
                func_8005DE0C(0x5DB, &sharedData_800CB088_3_s01, g_SysWork.field_28 >> 5, 0x10000, 0);

                SysWork_StateStepIncrementAfterFade(2, true, false, 0x1000, false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, false, 0x2000, false);
            }
            break;

        case 10:
            if (sharedData_800D4D10_3_s01 != 0)
            {
                SysWork_StateStepIncrementAfterFade(2, false, false, 0x1000, false);
                func_8005DE0C(0x5DB, &sharedData_800CB088_3_s01, 0x80, 0x10000, 0U);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, false, false, 0x2000, false);

                if (g_SysWork.sysStateStep_C[0] != 0xA)
                {
                    func_8005DC1C(0x5DD, &sharedData_800CB094_3_s01, 0x80, 0);
                    SysWork_StateStepSet(0, 14);
                }
            }
            break;

        case 11:
            if (g_SysWork.field_28 > ((sharedData_800D4D18_3_s01 - 1) * 0xC00))
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                g_SysWork.field_28 += g_DeltaTime0;
            }
            break;

        case 12:
            func_8005DE0C(0x5DB, &sharedData_800CB088_3_s01, 0x80 - (g_SysWork.field_28 >> 5), 0x10000, 0);
            g_SysWork.field_28 += g_DeltaTime0;

            if (g_SysWork.field_28 > 0x800)
            {
                func_8005DC1C(0x5DA, &sharedData_800CB088_3_s01, 0x80, 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            func_8005DE0C(0x5DB, &sharedData_800CB088_3_s01, 0x40 - (g_SysWork.field_28 >> 5), 0x10000, 0);
            g_SysWork.field_28 += g_DeltaTime0;

            if (g_SysWork.field_28 > 0x800)
            {
                SD_Call(Sfx_Unk1502);
#if defined(MAP3_S03) || defined(MAP3_S04) || defined(MAP3_S05)
                func_8005DC1C(0x5DD, &sharedData_800CB094_3_s01, 0x80, 0);
#else
                func_8005DC1C(0x5DD, &sharedData_800CB0A0_3_s01, 0x80, 0);
#endif
                Sd_SfxStop(0x5DB);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 14:
            sharedData_800D4D0C_3_s01.vx = MIN(Q12_MULT_PRECISE(g_DeltaTime0, 0xCCC) + sharedData_800D4D0C_3_s01.vx, 0x599);

            for (i = 0; i < 4; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime0, (i & 1) ? sharedData_800D4D0C_3_s01.vx : -sharedData_800D4D0C_3_s01.vx);
            }

            SysWork_StateStepIncrementDelayed(0x4CC, false);
            break;

        case 15:
        case 16:
            sharedData_800D4D0C_3_s01.vx = MIN(Q12_MULT_PRECISE(g_DeltaTime0, 0xCCC) + sharedData_800D4D0C_3_s01.vx, 0x599);
            sharedData_800D4D0C_3_s01.vy = MIN(Q12_MULT_PRECISE(g_DeltaTime0, 0xCCC) + sharedData_800D4D0C_3_s01.vy, 0x599);

            for (i = 0; i < 4; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime0, (i & 1) ? sharedData_800D4D0C_3_s01.vx : -sharedData_800D4D0C_3_s01.vx);
            }

            for (i = 4; i < 6; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime0, (i & 1) ? sharedData_800D4D0C_3_s01.vy : -sharedData_800D4D0C_3_s01.vy);
            }

            if (g_SysWork.sysStateStep_C[0] == 15)
            {
                SysWork_StateStepIncrementDelayed(0x4CC, false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, false, 0x1800, false);
            }
            break;

        case 17:
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
#ifdef MAP3_S01
            func_8008D448();
            Game_FlashlightAttributesFix();
            g_SysWork.pointLightIntensity_2378 = 0x1000;
#endif
            Sd_SfxStop(0x5DB);
            Sd_SfxStop(0x5DD);
            Sd_SfxStop(0x5DA);
            break;
    }
}