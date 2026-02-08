void sharedFunc_800D0110_7_s00(void)
{
    s32           temp_v0_2;
    s32           temp_v1_5;
    s32           i;
    s32           var_s2;
    s32           mapRoomIdx;
    s_Bgm_Update* bgmLayerLimitPtr;
    s32           flags;

    flags            = 1;
    var_s2           = 0x199;
    mapRoomIdx       = g_SavegamePtr->mapRoomIdx_A5;
    bgmLayerLimitPtr = NULL;

    switch (g_GameWork.bgmIdx_5B2)
    {
        case 5:
            g_SysWork.sysFlags_22A0 &= ~8;

            switch (g_GameWork.gameState_594)
            {
                case GameState_InventoryScreen:
                case GameState_LoadStatusScreen:
                    if (g_GameWork.gameState_594 != GameState_InventoryScreen || g_GameWork.gameStateStep_598[1] != 0x19)
                    {
                        flags = 0xFE;
                        if (g_GameWork.gameStatePrev_590 != GameState_Unk10)
                        {
                            var_s2 = 0xF0000;
                        }
                        else
                        {
                            flags  = 0x201;
                            var_s2 = 0x3000;
                        }
                    }
                    else
                    {
                        flags  = 0x201;
                        var_s2 = 0x3000;
                    }
                    break;

                case GameState_Unk10:
                    switch (g_Screen_FadeStatus)
                    {
                        default:
                            flags  = 0xFE;
                            var_s2 = 0xF0000;
                            break;

                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            flags  = 0x201;
                            var_s2 = 0x3000;
                            break;
                    }
                    break;

                default:
                    flags  = 0x201;
                    var_s2 = 0x3000;
                    break;
            }
            break;

        case 4:
            bgmLayerLimitPtr = &sharedData_800D2F18_7_s00;

            switch (mapRoomIdx)
            {
                case 0x14:
                case 0x15:
                case 0x17:
                case 0x18:
                    if (Savegame_EventFlagGet(EventFlag_482) || Savegame_EventFlagGet(EventFlag_483))
                    {
                        flags  = 4;
                        var_s2 = 0xF0000;
                    }
                    else if (Savegame_EventFlagGet(EventFlag_571))
                    {
                        if (Savegame_EventFlagGet(EventFlag_572))
                        {
                            var_s2 = 0x5000;
                            flags  = 4;
                        }
                        else
                        {
                            var_s2 = 0xF0000;
                            flags  = 0x201;

                            if (!func_80045BC8())
                            {
                                Savegame_EventFlagSet(EventFlag_572);
                            }
                        }
                    }
                    else if (Savegame_EventFlagGet(EventFlag_572))
                    {
                        var_s2 = 0x1000;
                        flags  = 0x201;
                    }
                    else if (Savegame_EventFlagGet(EventFlag_570))
                    {
                        var_s2 = 0x1000;
                        flags  = 0x201;

                        if (!func_80045BC8())
                        {
                            Savegame_EventFlagSet(EventFlag_572);
                        }
                    }
                    else
                    {
                        flags = 2;
                    }
                    break;

                default:
                    flags = 0x201;
                    break;
            }
            break;

        case 10:
        case 15:
            bgmLayerLimitPtr = &sharedData_800D2F20_7_s00;

            switch (mapRoomIdx)
            {
                default:
                    flags = 1;
                    break;

                case 1:
                    if (!Savegame_EventFlagGet(EventFlag_476))
                    {
                        flags = 1;
                    }
                    else if (Savegame_EventFlagGet(EventFlag_471))
                    {
                        var_s2 = 0xF0000;
                        flags  = 0x201;
                    }
                    else if (Savegame_EventFlagGet(EventFlag_474))
                    {
                        var_s2 = 0x199;
                        flags  = 1;
                    }
                    else
                    {
                        var_s2 = 0xF0000;
                        flags  = 0xFE;
                    }
                    break;

                case 2:
                    if (Savegame_EventFlagGet(EventFlag_475))
                    {
                        var_s2 = 0x1000;
                        flags  = 0xFE;
                    }
                    else
                    {
                        var_s2 = 0x400;
                        flags  = 0x201;
                    }
                    break;

                case 3:
                    var_s2 = 0x266;
                    flags  = 0x201;
                    break;
            }
            break;

        case 14:
        case 22:
            bgmLayerLimitPtr = &sharedData_800D2F74_7_s00;
            flags            = sharedData_800D2F28_7_s00[mapRoomIdx];

            switch (mapRoomIdx)
            {
                case 36:
                    var_s2 = 0x800;
                    break;

                case 21:
                    var_s2 = 0xF0000;
                    break;

                case 4:
                    if (!Savegame_EventFlagGet(EventFlag_485))
                    {
                        flags = 1;
                    }
                    break;

                case 7:
                    if (!Savegame_EventFlagGet(EventFlag_M7S01_PickupKeyOfPhaleg))
                    {
                        flags = 1;
                    }
                    break;

                case 22:
                    if (Savegame_EventFlagGet(EventFlag_487) && !Savegame_EventFlagGet(EventFlag_489))
                    {
                        flags = 0xC;
                    }
                    break;

                case 17:
                    if (Savegame_EventFlagGet(EventFlag_486))
                    {
                        if (!Savegame_EventFlagGet(EventFlag_549))
                        {
                            flags = 0x10;
                        }
                        else
                        {
                            flags = 4;
                        }
                    }
                    break;

                case 25:
                    if (!Savegame_EventFlagGet(EventFlag_492) && Savegame_EventFlagGet(EventFlag_498))
                    {
                        flags |= 4;
                    }

                    if (!Savegame_EventFlagGet(EventFlag_494) && Savegame_EventFlagGet(EventFlag_499))
                    {
                        flags |= 2;
                    }
                    break;

                case 29:
                    if (Savegame_EventFlagGet(EventFlag_555))
                    {
                        if (g_GameWork.bgmIdx_5B2 == 0x16)
                        {
                            flags = 4;
                        }
                        else
                        {
                            flags = 8;
                        }
                    }
                    else if (Savegame_EventFlagGet(EventFlag_573))
                    {
                        if (Savegame_EventFlagGet(EventFlag_552))
                        {
                            if (g_GameWork.bgmIdx_5B2 == 0x16)
                            {
                                flags = 8;
                            }
                            else
                            {
                                flags = 2;
                            }
                        }
                        else
                        {
                            if (g_GameWork.bgmIdx_5B2 == 0x16)
                            {
                                flags = 0x18;
                            }
                            else
                            {
                                flags = 0x12;
                            }
                        }
                    }
                    else
                    {
                        if (!Savegame_EventFlagGet(EventFlag_557))
                        {

                            if (Savegame_EventFlagGet(EventFlag_M7S02_PickupDaggerOfMelchior))
                            {
                                flags = 0xC;
                            }
                            else
                            {
                                flags = 4;
                            }
                        }
                        else
                        {
                            flags = 0x10;
                        }
                    }
                    break;

                case 31:
                    if (!Savegame_EventFlagGet(EventFlag_548))
                    {
                        flags = 1;
                    }
                    break;

                case 32:
                    if (!Savegame_EventFlagGet(EventFlag_551))
                    {
                        var_s2 = 0xF0000;
                        flags  = 1;
                    }
                    break;

                case 33:
                    if (!Savegame_EventFlagGet(EventFlag_560))
                    {
                        for (flags = 0, i = 0x21C; i < 0x221; i++)
                        {
                            if (Savegame_EventFlagGet(i))
                            {
                                flags = (flags * 2) | 2;
                            }
                        }
                    }
                    break;
            }

            if (g_GameWork.bgmIdx_5B2 == 0x16)
            {
                temp_v0_2 = flags & 2;
                temp_v1_5 = flags & 4;
                flags    ^= (temp_v0_2 | temp_v1_5);
                flags    |= (temp_v0_2 * 2) | (temp_v1_5 >> 1);
            }
            break;

        case 35:
            if (Savegame_EventFlagGet(EventFlag_582))
            {
                flags = 0x301;
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_580))
            {
                if (!Savegame_EventFlagGet(EventFlag_575))
                {
                    var_s2 = 0xF0000;
                    flags  = 0x120;
                }
                else
                {
                    var_s2 = 0x800;
                    flags  = 0x301;
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_577))
            {
                if (g_SysWork.npcs_1A0[0].health_B0 <= 0x1F3FFF)
                {
                    flags = 0x13E;
                }
                else
                {
                    flags = 0x128;
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_591))
            {
                flags = 0x102;
            }
            else
            {
                flags = 0x100;
            }

            if (Savegame_EventFlagGet(EventFlag_592))
            {
                flags |= 4;
            }

            if (Savegame_EventFlagGet(EventFlag_593))
            {
                flags |= 8;
            }

            if (Savegame_EventFlagGet(EventFlag_575))
            {
                flags |= 0x10;
            }

            if (Savegame_EventFlagGet(EventFlag_576))
            {
                var_s2 = 0xF0000;
            }

            if (flags == 0x100)
            {
                flags = 0x301;
            }
            break;

        case 29:
            bgmLayerLimitPtr = &sharedData_800D2F7C_7_s00;
            var_s2           = 0xF0000;

            if (!Savegame_EventFlagGet(EventFlag_576))
            {
                flags = 0x101;
            }
            else
            {
                if (Savegame_EventFlagGet(EventFlag_591))
                {
                    g_SysWork.sysFlags_22A0 |= 4;
                }
                flags = 0x100;
            }
            break;

        case 40:
            bgmLayerLimitPtr = &sharedData_800D2F84_7_s00;
            if (Savegame_EventFlagGet(EventFlag_575))
            {
                var_s2 = 0x400;
                flags  = 0x101;
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_580))
            {
                var_s2 = 0x2000;
                flags  = 0x301;
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_578))
            {
                if (!Savegame_EventFlagGet(EventFlag_593))
                {
                    var_s2 = 0xF0000;
                    flags  = 0x101;
                }
                else
                {
                    flags = 0x120;
                }

                if (Savegame_EventFlagGet(EventFlag_592))
                {
                    if (Savegame_EventFlagGet(EventFlag_593))
                    {
                        flags |= 0xC0;
                    }
                    else
                    {
                        flags |= 0x40;
                    }
                }
                break;
            }

            if (Savegame_EventFlagGet(EventFlag_577) || Savegame_EventFlagGet(EventFlag_591))
            {
                if (g_SysWork.bgmLayerVolumes_2748[1] == 0x1000)
                {
                    if (Savegame_EventFlagGet(EventFlag_577))
                    {
                        var_s2 = 0x1000;

                        if (!(g_SysWork.npcs_1A0[2].flags_3E & 4))
                        {
                            flags = 0x102;
                        }
                        else
                        {
                            flags = 0x11E;
                        }
                    }
                    else
                    {
                        var_s2 = 0x1EB;

                        if (g_SysWork.bgmLayerVolumes_2748[2] == 0x1000)
                        {
                            if (g_SysWork.bgmLayerVolumes_2748[3] == 0x1000)
                            {
                                flags = 0x11E;
                            }
                            else
                            {
                                flags = 0x10E;
                            }
                        }
                        else
                        {
                            if (Savegame_EventFlagGet(EventFlag_576))
                            {
                                flags = 0x106;
                            }
                            else
                            {
                                flags = 0x102;
                            }
                        }
                    }
                    break;
                }

                if (Savegame_EventFlagGet(EventFlag_577))
                {
                    var_s2 = 0xF0000;
                }

                flags = 0x102;

                if (g_SysWork.bgmLayerVolumes_2748[0] != 0x1000)
                {
                    if (!func_80045BC8())
                    {
                        Bgm_BgmChannelSet();
                    }
                    else
                    {
                        Sd_BgmLayerVolumeSet(0, 0x7F);
                        Sd_BgmLayerVolumeSet(1, 1);
                        g_SysWork.bgmLayerVolumes_2748[0] = 0x1000;
                        g_SysWork.bgmLayerVolumes_2748[1] = 0x20;
                    }
                }
            }
            else
            {
                flags = 0x301;
            }
            break;
    }

    Bgm_Update(flags, var_s2, bgmLayerLimitPtr);
}