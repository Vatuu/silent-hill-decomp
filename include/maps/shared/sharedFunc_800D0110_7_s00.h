void sharedFunc_800D0110_7_s00(void)
{
    s32           temp_v0_2;
    s32           temp_v1_5;
    s32           i;
    q19_12        var_s2;
    s32           mapRoomIdx;
    s32           flags;
    s_Bgm_Update* bgmLayerLimit;

    flags            = 1 << 0;
    var_s2           = Q12(0.1f);
    mapRoomIdx       = g_SavegamePtr->mapRoomIdx_A5;
    bgmLayerLimit = NULL;

    switch (g_GameWork.bgmIdx_5B2)
    {
        case 5:
            g_SysWork.sysFlags_22A0 &= ~SysFlag_3;

            switch (g_GameWork.gameState_594)
            {
                case GameState_InventoryScreen:
                case GameState_LoadStatusScreen:
                    if (g_GameWork.gameState_594 != GameState_InventoryScreen || g_GameWork.gameStateStep_598[1] != 25)
                    {
                        flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
                        if (g_GameWork.gameStatePrev_590 != GameState_SaveScreen)
                        {
                            var_s2 = Q12(240.0f);
                        }
                        else
                        {
                            flags  = (1 << 0) | (1 << 9);
                            var_s2 = Q12(3.0f);
                        }
                    }
                    else
                    {
                        flags  = (1 << 0) | (1 << 9);
                        var_s2 = Q12(3.0f);
                    }
                    break;

                case GameState_SaveScreen:
                    switch (g_Screen_FadeStatus)
                    {
                        default:
                            flags  = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
                            var_s2 = Q12(240.0f);
                            break;

                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            flags  = (1 << 0) | (1 << 9);
                            var_s2 = Q12(3.0f);
                            break;
                    }
                    break;

                default:
                    flags  = (1 << 0) | (1 << 9);
                    var_s2 = Q12(3.0f);
                    break;
            }
            break;

        case 4:
            bgmLayerLimit = &sharedData_800D2F18_7_s00;

            switch (mapRoomIdx)
            {
                case 20:
                case 21:
                case 23:
                case 24:
                    if (Savegame_EventFlagGet(EventFlag_482) || Savegame_EventFlagGet(EventFlag_483))
                    {
                        flags  = 1 << 2;
                        var_s2 = Q12(240.0f);
                    }
                    else if (Savegame_EventFlagGet(EventFlag_571))
                    {
                        if (Savegame_EventFlagGet(EventFlag_572))
                        {
                            var_s2 = Q12(5.0f);
                            flags  = 1 << 2;
                        }
                        else
                        {
                            var_s2 = Q12(240.0f);
                            flags  = (1 << 0) | (1 << 9);

                            if (!func_80045BC8())
                            {
                                Savegame_EventFlagSet(EventFlag_572);
                            }
                        }
                    }
                    else if (Savegame_EventFlagGet(EventFlag_572))
                    {
                        var_s2 = Q12(1.0f);
                        flags  = (1 << 0) | (1 << 9);
                    }
                    else if (Savegame_EventFlagGet(EventFlag_570))
                    {
                        var_s2 = Q12(1.0f);
                        flags  = (1 << 0) | (1 << 9);

                        if (!func_80045BC8())
                        {
                            Savegame_EventFlagSet(EventFlag_572);
                        }
                    }
                    else
                    {
                        flags = 1 << 1;
                    }
                    break;

                default:
                    flags = (1 << 0) | (1 << 9);
                    break;
            }
            break;

        case 10:
        case 15:
            bgmLayerLimit = &sharedData_800D2F20_7_s00;

            switch (mapRoomIdx)
            {
                default:
                    flags = 1 << 0;
                    break;

                case 1:
                    if (!Savegame_EventFlagGet(EventFlag_476))
                    {
                        flags = 1 << 0;
                    }
                    else if (Savegame_EventFlagGet(EventFlag_471))
                    {
                        var_s2 = Q12(240.0f);
                        flags  = (1 << 0) | (1 << 9);
                    }
                    else if (Savegame_EventFlagGet(EventFlag_474))
                    {
                        var_s2 = Q12(0.1f);
                        flags  = 1 << 0;
                    }
                    else
                    {
                        var_s2 = Q12(240.0f);
                        flags  = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
                    }
                    break;

                case 2:
                    if (Savegame_EventFlagGet(EventFlag_475))
                    {
                        var_s2 = Q12(1.0f);
                        flags  = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
                    }
                    else
                    {
                        var_s2 = Q12(0.25f);
                        flags  = (1 << 0) | (1 << 9);
                    }
                    break;

                case 3:
                    var_s2 = Q12(0.15f);
                    flags  = (1 << 0) | (1 << 9);
                    break;
            }
            break;

        case 14:
        case 22:
            bgmLayerLimit = &sharedData_800D2F74_7_s00;
            flags            = sharedData_800D2F28_7_s00[mapRoomIdx];

            switch (mapRoomIdx)
            {
                case 36:
                    var_s2 = Q12(0.5f);
                    break;

                case 21:
                    var_s2 = Q12(240.0f);
                    break;

                case 4:
                    if (!Savegame_EventFlagGet(EventFlag_485))
                    {
                        flags = 1 << 0;
                    }
                    break;

                case 7:
                    if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupKeyOfPhaleg))
                    {
                        flags = 1 << 0;
                    }
                    break;

                case 22:
                    if (Savegame_EventFlagGet(EventFlag_487) && !Savegame_EventFlagGet(EventFlag_489))
                    {
                        flags = (1 << 2) | (1 << 3);
                    }
                    break;

                case 17:
                    if (Savegame_EventFlagGet(EventFlag_486))
                    {
                        if (!Savegame_EventFlagGet(EventFlag_549))
                        {
                            flags = 1 << 4;
                        }
                        else
                        {
                            flags = 1 << 2;
                        }
                    }
                    break;

                case 25:
                    if (!Savegame_EventFlagGet(EventFlag_492) && Savegame_EventFlagGet(EventFlag_498))
                    {
                        flags |= 1 << 2;
                    }

                    if (!Savegame_EventFlagGet(EventFlag_494) && Savegame_EventFlagGet(EventFlag_499))
                    {
                        flags |= 1 << 1;
                    }
                    break;

                case 29:
                    if (Savegame_EventFlagGet(EventFlag_555))
                    {
                        if (g_GameWork.bgmIdx_5B2 == 22)
                        {
                            flags = 1 << 2;
                        }
                        else
                        {
                            flags = 1 << 3;
                        }
                    }
                    else if (Savegame_EventFlagGet(EventFlag_573))
                    {
                        if (Savegame_EventFlagGet(EventFlag_552))
                        {
                            if (g_GameWork.bgmIdx_5B2 == 22)
                            {
                                flags = 1 << 3;
                            }
                            else
                            {
                                flags = 1 << 1;
                            }
                        }
                        else
                        {
                            if (g_GameWork.bgmIdx_5B2 == 22)
                            {
                                flags = (1 << 3) | (1 << 4);
                            }
                            else
                            {
                                flags = (1 << 1) | (1 << 4);
                            }
                        }
                    }
                    else
                    {
                        if (!Savegame_EventFlagGet(EventFlag_557))
                        {

                            if (Savegame_EventFlagGet(EventFlag_M7S02_PickupDaggerOfMelchior))
                            {
                                flags = (1 << 2) | (1 << 3);
                            }
                            else
                            {
                                flags = 1 << 2;
                            }
                        }
                        else
                        {
                            flags = 1 << 4;
                        }
                    }
                    break;

                case 31:
                    if (!Savegame_EventFlagGet(EventFlag_548))
                    {
                        flags = 1 << 0;
                    }
                    break;

                case 32:
                    if (!Savegame_EventFlagGet(EventFlag_551))
                    {
                        var_s2 = Q12(240.0f);
                        flags  = 1;
                    }
                    break;

                case 33:
                    if (!Savegame_EventFlagGet(EventFlag_560))
                    {
                        for (flags = 0, i = 540; i < 545; i++)
                        {
                            if (Savegame_EventFlagGet(i))
                            {
                                flags = (flags * 2) | (1 << 1);
                            }
                        }
                    }
                    break;
            }

            if (g_GameWork.bgmIdx_5B2 == 22)
            {
                temp_v0_2 = flags & (1 << 1);
                temp_v1_5 = flags & (1 << 2);
                flags    ^= (temp_v0_2 | temp_v1_5);
                flags    |= (temp_v0_2 * 2) | (temp_v1_5 >> 1);
            }
            break;

        case 35:
            if (Savegame_EventFlagGet(EventFlag_582))
            {
                flags = (1 << 0) | (1 << 8) | (1 << 9);
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_580))
            {
                if (!Savegame_EventFlagGet(EventFlag_575))
                {
                    var_s2 = Q12(240.0f);
                    flags  = (1 << 5) | (1 << 8);
                }
                else
                {
                    var_s2 = Q12(0.5f);
                    flags  = (1 << 0) | (1 << 8) | (1 << 9);
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_577))
            {
                if (g_SysWork.npcs_1A0[0].health_B0 < Q12(500.0f))
                {
                    flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 8);
                }
                else
                {
                    flags = (1 << 3) | (1 << 5) | (1 << 8);
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_591))
            {
                flags = (1 << 1) | (1 << 8);
            }
            else
            {
                flags = 1 << 8;
            }

            if (Savegame_EventFlagGet(EventFlag_592))
            {
                flags |= 1 << 2;
            }

            if (Savegame_EventFlagGet(EventFlag_593))
            {
                flags |= 1 << 3;
            }

            if (Savegame_EventFlagGet(EventFlag_575))
            {
                flags |= 1 << 4;
            }

            if (Savegame_EventFlagGet(EventFlag_576))
            {
                var_s2 = Q12(240.0f);
            }

            if (flags == (1 << 8))
            {
                flags = (1 << 0) | (1 << 8) | (1 << 9);
            }
            break;

        case 29:
            bgmLayerLimit = &sharedData_800D2F7C_7_s00;
            var_s2           = Q12(240.0f);

            if (!Savegame_EventFlagGet(EventFlag_576))
            {
                flags = (1 << 0) | (1 << 8);
            }
            else
            {
                if (Savegame_EventFlagGet(EventFlag_591))
                {
                    g_SysWork.sysFlags_22A0 |= SysFlag_2;
                }
                flags = 1 << 8;
            }
            break;

        case 40:
            bgmLayerLimit = &sharedData_800D2F84_7_s00;
            if (Savegame_EventFlagGet(EventFlag_575))
            {
                var_s2 = Q12(0.25f);
                flags  = (1 << 0) | (1 << 8);
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_580))
            {
                var_s2 = Q12(2.0f);
                flags  = (1 << 0) | (1 << 8) | (1 << 9);
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_578))
            {
                if (!Savegame_EventFlagGet(EventFlag_593))
                {
                    var_s2 = Q12(240.0f);
                    flags  = (1 << 0) | (1 << 8);
                }
                else
                {
                    flags = (1 << 5) | (1 << 8);
                }

                if (Savegame_EventFlagGet(EventFlag_592))
                {
                    if (Savegame_EventFlagGet(EventFlag_593))
                    {
                        flags |= (1 << 6) | (1 << 7);
                    }
                    else
                    {
                        flags |= 1 << 6;
                    }
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_577) || Savegame_EventFlagGet(EventFlag_591))
            {
                if (g_SysWork.bgmLayerVolumes_2748[1] == Q12(1.0f))
                {
                    if (Savegame_EventFlagGet(EventFlag_577))
                    {
                        var_s2 = Q12(1.0f);

                        if (!(g_SysWork.npcs_1A0[2].flags_3E & 4))
                        {
                            flags = (1 << 1) | (1 << 8);
                        }
                        else
                        {
                            flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 8);
                        }
                    }
                    else
                    {
                        var_s2 = Q12(0.12f);

                        if (g_SysWork.bgmLayerVolumes_2748[2] == Q12(1.0f))
                        {
                            if (g_SysWork.bgmLayerVolumes_2748[3] == Q12(1.0f))
                            {
                                flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 8);
                            }
                            else
                            {
                                flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 8);
                            }
                        }
                        else
                        {
                            if (Savegame_EventFlagGet(EventFlag_576))
                            {
                                flags = (1 << 1) | (1 << 2) | (1 << 8);
                            }
                            else
                            {
                                flags = (1 << 1) | (1 << 8);
                            }
                        }
                    }
                    break;
                }

                if (Savegame_EventFlagGet(EventFlag_577))
                {
                    var_s2 = Q12(240.0f);
                }

                flags = (1 << 1) | (1 << 8);

                if (g_SysWork.bgmLayerVolumes_2748[0] != Q12(1.0f))
                {
                    if (!func_80045BC8())
                    {
                        Bgm_BgmChannelSet();
                    }
                    else
                    {
                        Sd_BgmLayerVolumeSet(0, 0x7F);
                        Sd_BgmLayerVolumeSet(1, 1);

                        g_SysWork.bgmLayerVolumes_2748[0] = Q12(1.0f);
                        g_SysWork.bgmLayerVolumes_2748[1] = 32;
                    }
                }
            }
            else
            {
                flags = (1 << 0) | (1 << 8) | (1 << 9);
            }
            break;
    }

    Bgm_Update(flags, var_s2, bgmLayerLimit);
}
