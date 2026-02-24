void Map_RoomBgmInit(bool arg0)
{
    s32 var_s1;
    s32 var_s2;
    s32 temp_a2;
    u8* var_s3;
    u16 flags;

    var_s3  = sharedData_800EFCFC_6_s00;
    temp_a2 = g_SavegamePtr->mapRoomIdx_A5;
    var_s1  = Q12(0.2f);
    switch (g_GameWork.bgmIdx_5B2)
    {
        case 5:
            g_SysWork.sysFlags_22A0 &= ~SysFlag_3;

            switch (g_GameWork.gameState_594)
            {
                case GameState_InventoryScreen:
                case GameState_LoadStatusScreen:
                    if ((g_GameWork.gameState_594 != GameState_InventoryScreen) || (g_GameWork.gameStateStep_598[1] != 25))
                    {
                        flags = 0xFE;

                        if (g_GameWork.gameStatePrev_590 != GameState_SaveScreen)
                        {
                            var_s1 = Q12(240.0f);
                            break;
                        }
                    }

                    flags  = 0x201;
                    var_s1 = Q12(3.0f);
                    break;

                case GameState_SaveScreen:
                    if (g_Screen_FadeStatus >= 6)
                    {
                        flags  = 0xFE;
                        var_s1 = Q12(240.0f);
                    }
                    else if (g_Screen_FadeStatus < 2)
                    {
                        flags  = 0xFE;
                        var_s1 = Q12(240.0f);
                    }
                    else
                    {
                        flags  = 0x201;
                        var_s1 = Q12(3.0f);
                    }
                    break;

                default:
                    flags  = 0x201;
                    var_s1 = Q12(3.0f);
                    break;
            }
            break;

        case 41:
            var_s3 = NULL;
            if (Savegame_EventFlagGet(EventFlag_419))
            {
                var_s1 = Q12(2.0f);
                flags  = 0x104;
            }
            else
            {
                flags = 0x301;
                if (!Savegame_EventFlagGet(EventFlag_418))
                {
                    var_s1 = Q12(2.0f);
                    flags  = 0x102;
                }
            }

            break;

        case 21:
            flags = 0x301;

            if (!Savegame_EventFlagGet(EventFlag_469))
            {
                flags = 0x1FE;

                if (Savegame_EventFlagGet(EventFlag_417) && !Savegame_EventFlagGet(EventFlag_460))
                {
                    flags = 0x101;
                }
            }
            break;

        case 20:
        default:
            if (Savegame_EventFlagGet(EventFlag_410))
            {
                flags = sharedData_800EFD08_6_s00[temp_a2];
                if (Savegame_EventFlagGet(EventFlag_426))
                {
                    flags |= 0x80;
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_402))
            {
                flags = sharedData_800EFD34_6_s00[temp_a2];
            }
            else
            {
                flags = 6;
            }
            break;
    }

    var_s2 = 96;
    if (temp_a2 < 20)
    {
        if (temp_a2 >= 15)
        {
            var_s2 = 127;
        }
    }

    sharedData_800EFD04_6_s00   += g_DeltaTime;
    sharedData_800EFCFC_6_s00[2] = Q12_MULT_PRECISE(var_s2, (Math_Sin(sharedData_800EFD04_6_s00 / 12) + Q12(3.0f)) / 4);

    Bgm_Update(flags, var_s1, var_s3);
}
