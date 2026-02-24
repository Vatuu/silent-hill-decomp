#if defined(MAP7_S01) || defined(MAP7_S02)
    #define EventFlagBase0 EventFlag_213
    #define EventFlagBase1 EventFlag_212
    #define EventFlagBase2 EventFlag_216
#else
    #define EventFlagBase0 EventFlag_212
    #define EventFlagBase1 EventFlag_M3S01_GeneratorOn
    #define EventFlagBase2 EventFlag_215
#endif

#ifdef MAP3_S01
    #define MAX_IDX 7
#elif defined(MAP7_S01) || defined(MAP7_S02)
    #define MAX_IDX 5
#else
    #define MAX_IDX 6
#endif

#if defined(MAP7_S01) || defined(MAP7_S02)
    #define CHECK_IDX 4
#else
    #define CHECK_IDX 5
#endif

void sharedFunc_800D15F0_3_s01(void)
{
    s32 j;
    s32 i;
    s16 cursorX;
    s32 temp;
    s32 temp2;

    // Skip.
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
                if (Savegame_EventFlagGet(EventFlagBase0 + i))
                {
                    sharedData_800D4D14_3_s01 = (sharedData_800D4CD4_3_s01[i + 1][1] - 110) << 12;
                    sharedData_800D4D18_3_s01 = i;
                }
            }

            SysWork_StateStepIncrement(0);

        case 1:
#ifdef MAP3_S01
            if (Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_OperatingPrepRoomArrow) &&
                Savegame_MapMarkingGet(MapMarkFlag_AltHospital2F_CorridorMidArrows))
            {
                func_800862F8(7, Sfx_Unk1841, false);
            }
            else
            {
                func_800862F8(7, Sfx_Unk1840, false);
            }
#elif defined(MAP7_S01) || defined(MAP7_S02)
            func_800862F8(7, Sfx_Unk1842, false);
#else
            func_800862F8(7, Sfx_Unk1843, false);
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
            Gfx_CursorDraw(cursorX, FP_FROM(sharedData_800D4D14_3_s01, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 6);
                break;
            }

            if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0))
            {
                break;
            }

            for (i = 0; i < MAX_IDX; i++)
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

#if defined(MAP3_S03) || defined(MAP3_S04) || defined(MAP3_S05) || defined(MAP7_S01) || defined(MAP7_S02)
                SD_Call(Sfx_Unk1500);
#endif
                if (i == CHECK_IDX)
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
                    if (i <= 0 || !Savegame_EventFlagGet(EventFlagBase1 + i))
#endif
                    {
                        if (i != 0)
                        {
                            Savegame_EventFlagSet(EventFlagBase2 + i);
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
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-112.5f);
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(58.6f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(19.4f);
#elif defined(MAP7_S01) || defined(MAP7_S02)
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-101.9f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-60.3f);
#else
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-135.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(18.2f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(59.7f);
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
                g_SysWork.field_28 += g_DeltaTime;
                if (g_SysWork.field_28 > Q12(1.0f))
                {
                    g_SysWork.field_28 = Q12(1.0f);
                }

                func_8005DE0C(Sfx_Unk1499, &sharedData_800CB088_3_s01, g_SysWork.field_28 >> 5, Q12(16.0f), 0);
                SysWork_StateStepIncrementAfterFade(2, true, false, Q12(1.0f), false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, false, Q12(2.0f), false);
            }
            break;

        case 10:
            if (sharedData_800D4D10_3_s01 != 0)
            {
                SysWork_StateStepIncrementAfterFade(2, false, false, Q12(1.0f), false);
                func_8005DE0C(Sfx_Unk1499, &sharedData_800CB088_3_s01, Q8(0.5f), Q12(16.0f), 0u);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, false, false, Q12(2.0f), false);

                if (g_SysWork.sysStateStep_C[0] != 10)
                {
                    func_8005DC1C(Sfx_Unk1501, &sharedData_800CB094_3_s01, Q8(0.5f), 0);
                    SysWork_StateStepSet(0, 14);
                }
            }
            break;

        case 11:
            if (g_SysWork.field_28 > ((sharedData_800D4D18_3_s01 - 1) * Q12(0.75f)))
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                g_SysWork.field_28 += g_DeltaTime;
            }
            break;

        case 12:
            func_8005DE0C(Sfx_Unk1499, &sharedData_800CB088_3_s01, Q8(0.5f) - (g_SysWork.field_28 >> 5), Q12(16.0f), 0);

            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(0.5f))
            {
#if defined(MAP7_S01) || defined(MAP7_S02)
                func_8005DC1C(Sfx_Unk1498, &sharedData_800CB094_3_s01, Q8(0.5f), 0);
#else
                func_8005DC1C(Sfx_Unk1498, &sharedData_800CB088_3_s01, Q8(0.5f), 0);
#endif
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            func_8005DE0C(Sfx_Unk1499, &sharedData_800CB088_3_s01, Q8(0.25f) - (g_SysWork.field_28 >> 5), Q12(16.0f), 0);

            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(0.5f))
            {
                SD_Call(Sfx_Unk1502);
#if defined(MAP3_S03) || defined(MAP3_S04) || defined(MAP3_S05) || defined(MAP7_S01) || defined(MAP7_S02)
                func_8005DC1C(Sfx_Unk1501, &sharedData_800CB094_3_s01, Q8(0.5f), 0);
#else
                func_8005DC1C(Sfx_Unk1501, &sharedData_800CB0A0_3_s01, Q8(0.5f), 0);
#endif
                Sd_SfxStop(Sfx_Unk1499);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 14:
            sharedData_800D4D0C_3_s01.vx = MIN(Q12_MULT_PRECISE(g_DeltaTime, Q12(0.8f)) + sharedData_800D4D0C_3_s01.vx, Q12(0.35f));

            for (i = 0; i < 4; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, (i & 1) ? sharedData_800D4D0C_3_s01.vx : -sharedData_800D4D0C_3_s01.vx);
            }

            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 15:
        case 16:
            sharedData_800D4D0C_3_s01.vx = MIN(Q12_MULT_PRECISE(g_DeltaTime, Q12(0.8f)) + sharedData_800D4D0C_3_s01.vx, Q12(0.35f));
            sharedData_800D4D0C_3_s01.vy = MIN(Q12_MULT_PRECISE(g_DeltaTime, Q12(0.8f)) + sharedData_800D4D0C_3_s01.vy, Q12(0.35f));

            for (i = 0; i < 4; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, (i & 1) ? sharedData_800D4D0C_3_s01.vx : -sharedData_800D4D0C_3_s01.vx);
            }

            for (i = 4; i < 6; i++)
            {
                g_WorldObject_Dr[i].position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, (i & 1) ? sharedData_800D4D0C_3_s01.vy : -sharedData_800D4D0C_3_s01.vy);
            }

            if (g_SysWork.sysStateStep_C[0] == 15)
            {
                SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, false, Q12(1.5f), false);
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
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
#endif
            Sd_SfxStop(Sfx_Unk1499);
            Sd_SfxStop(Sfx_Unk1501);
            Sd_SfxStop(Sfx_Unk1498);
#if defined(MAP7_S01) || defined(MAP7_S02)
            temp2 = Q12(-60.9f);

            for (i = 5; i >= 0; i--)
            {
                g_WorldObject_Dr[i].position_1C.vz = temp2;
            }
#endif
            break;
    }
}
