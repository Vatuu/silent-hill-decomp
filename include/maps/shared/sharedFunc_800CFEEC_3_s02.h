void sharedFunc_800CFEEC_3_s02(void)
{
    const static s_func_80035F4C D_800CA70C = { { 0x80, 0x70, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00 } };

    u16              flags;
    q19_12           fArg1;
    s_func_80035F4C* dataPtr;
    s_func_80035F4C  data;
    s32              roomIdx;

    dataPtr = sharedData_800D1D14_3_s02;
    roomIdx = g_SavegamePtr->mapRoomIdx_A5;

    if (g_GameWork.soundCmd_5B2 == 8)
    {
        fArg1 = Q12(240.0f);
        flags = 0xFE;
    }
    else if (g_GameWork.soundCmd_5B2 == 32)
    {
        fArg1 = Q12(0.15f);
        if (Savegame_EventFlagGet(EventFlag_338))
        {
            flags = 4;
            if (!Savegame_EventFlagGet(EventFlag_340))
            {
                flags = 2;
                if (Savegame_EventFlagGet(EventFlag_339))
                {
                    flags = 0xE;
                }
            }
        }
        else
        {
            flags = 1;
        }
    }
    else
    {
        flags = sharedData_800D1D1C_3_s02[roomIdx];
        fArg1 = Q12(0.15f);

        switch (roomIdx)
        {
            case 23:
            case 26:
            case 38:
            case 45:
                if (!(Savegame_EventFlagGet(EventFlag_285) || Savegame_EventFlagGet(EventFlag_286)))
                {
                    flags = 0x1E;
                }
                else if (Savegame_EventFlagGet(EventFlag_285))
                {
                    Savegame_EventFlagSet(EventFlag_286);
                }
                break;

            case 5:
            case 25:
            case 37:
                if (!Savegame_EventFlagGet(EventFlag_285) && Savegame_EventFlagGet(EventFlag_286))
                {
                    Savegame_EventFlagSet(EventFlag_285);
                    Savegame_EventFlagClear(EventFlag_286);
                }

                if (!Savegame_EventFlagGet(EventFlag_285))
                {
                    flags = 0x1FE;
                }
                else if (!Savegame_EventFlagGet(EventFlag_286))
                {
                    flags = 0x13E;
                }

                break;

            case 4:
                if (!Player_ItemRemove(InventoryItemId_ExaminationRoomKey, 0))
                {
                    flags = 1 << 0;
                }

            case 6:
            case 7:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 21:
            case 22:
            case 24:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 34:
            case 35:
            case 36:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 46:
            case 47:
                Savegame_EventFlagSet(EventFlag_286);
                break;

            case 3:
                if (g_GameWork.soundCmd_5B2 == 31)
                {
                    data    = D_800CA70C;
                    dataPtr = &data;

                    if (!Savegame_EventFlagGet(EventFlag_293))
                    {
                        fArg1 = Q12(240.0f);
                        flags = 1 << 2;
                    }
                    else if (!Savegame_EventFlagGet(EventFlag_298))
                    {
                        fArg1 = Q12(0.25f);
                        flags = 1 << 1;
                    }
                    else if (!Savegame_EventFlagGet(EventFlag_299))
                    {
                        fArg1 = Q12(0.125f);
                        flags = 1 << 3;
                    }
                    else
                    {
                        fArg1 = Q12(240.0f);
                        if (!Savegame_EventFlagGet(EventFlag_294))
                        {
                            fArg1 = Q12(0.5f);
                            flags = (1 << 0) | (1 << 9);
                        }
                        else
                        {
                            flags = 1 << 0;
                        }
                    }
                }
                else
                {
                    flags = (1 << 0) | (1 << 9);
                }
                break;

            case 58:
                if (!Savegame_EventFlagGet(EventFlag_260))
                {
                    flags = 1 << 0;
                }
                break;
        }
    }

    func_80035F4C(flags, fArg1, dataPtr);
}
