void sharedFunc_800E12D0_6_s04(void)
{
    q19_12 dist0;
    s32    flags;
    s32    fArg1;
    s32    soundCmd;
    q19_12 dist;
    u8*    dataPtr;

    fArg1    = Q12(0.2f);
    soundCmd = g_GameWork.soundCmd_5B2;
    if (soundCmd == 36)
    {
        dataPtr = &sharedData_800EB738_6_s04;
        fArg1   = Q12(0.1f);
        if (Savegame_EventFlagGet(EventFlag_465))
        {
            flags = 0x20;
        }
        else if (!Savegame_EventFlagGet(EventFlag_464))
        {
            fArg1 = Q12(240.0f);
            flags = 2;
        }
        else
        {
            flags = 0x10;
        }
    }
    else if (soundCmd == 39)
    {
        dataPtr = sharedData_800EB740_6_s04;

        if (Savegame_EventFlagGet(EventFlag_445))
        {
            if (Savegame_EventFlagGet(EventFlag_448))
            {
                flags = 0x100;
                if (Savegame_EventFlagGet(EventFlag_462))
                {
                    flags = 0x110;
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_470))
            {
                sharedData_800EB740_6_s04[1] = 0x80;
                fArg1                        = Q12(0.5f);

                if (!Savegame_EventFlagGet(EventFlag_447))
                {
                    flags = 0x102;
                    if (Savegame_EventFlagGet(EventFlag_463))
                    {
                        flags = 0x101;
                    }
                }
                else
                {
                    fArg1 = Q12(240.0f);
                    flags = 0x101;
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_446))
            {
                sharedData_800EB740_6_s04[1] = 0;
                fArg1                        = Q12(240.0f);
                flags                        = 0x101;
            }
            else
            {
                sharedData_800EB740_6_s04[1] = 0x60;
                flags                        = 0x10A;
            }
        }
        else
        {
            sharedData_800EB740_6_s04[1] = 0x60;

            if (Savegame_EventFlagGet(EventFlag_443))
            {
                flags = 0x108;
                if (!Savegame_EventFlagGet(EventFlag_444))
                {
                    if (Savegame_EventFlagGet(EventFlag_455))
                    {
                        flags = 0x10A;
                    }
                }
                else
                {
                    flags = 0x10A;
                }
            }
            else
            {
                fArg1 = Q12(240.0f);

                flags = 0x301;
                if (Savegame_EventFlagGet(EventFlag_461))
                {
                    flags = 0x104;
                }
            }
        }
    }
    else
    {
        dist    = Q12(0.0f);
        dataPtr = &sharedData_800EB748_6_s04;

        switch (g_SavegamePtr->mapRoomIdx_A5)
        {
            case 3:
                flags = 4;

                dist = Math_Distance2dGet(&g_SysWork.player_4C.chara_0.position_18, &sharedData_800EB750_6_s04);
                if (dist < Q12(10.0f))
                {
                    dist = Q12(0.03125f);
                }
                else
                {
                    dist = Q12(0.03125f) - FP_MULTIPLY_PRECISE(dist - Q12(10.0f), Q12(0.004f), Q12_SHIFT);
                    if (dist < Q12(0.0f))
                    {
                        dist = Q12(0.0f);
                    }
                }
                break;

            case 1:
            case 2:
            case 4:
            case 5:
                flags = 2;
                break;

            default:
                flags = 1;
                break;
        }

        sharedData_800EB74A_6_s04 = dist;
    }

    func_80035F4C(flags, fArg1, dataPtr);
}
