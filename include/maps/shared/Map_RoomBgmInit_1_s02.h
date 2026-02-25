void Map_RoomBgmInit(bool arg0)
{
    s32 fArg1;
    s32 roomIdx;
    s32 flags;

    roomIdx = g_SavegamePtr->mapRoomIdx_A5;
    flags = sharedData_800E1210_1_s02[roomIdx];
    fArg1 = Q12(0.1f);

    switch (roomIdx)
    {
        case 23:
            flags = 1 << 0;
            if (Savegame_MapMarkingGet(MapMarkFlag_AltSchool1F_CourtyardQuestion))
            {
                flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
                if (Savegame_MapMarkingGet(MapMarkFlag_308) || Savegame_MapMarkingGet(MapMarkFlag_AltSchool1F_CourtyardTopArrows))
                {
                    flags = 1 << 4;
                }
            }
            break;

        case 38:
            if (Savegame_EventFlagGet(EventFlag_100) && !Savegame_EventFlagGet(EventFlag_107))
            {
                flags = 1 << 0;
                fArg1 = Q12(0.3f);
            }
            break;

        case 5:
            if (Savegame_EventFlagGet(EventFlag_121))
            {
                fArg1 = Q12(240.0f);

                if (Savegame_EventFlagGet(EventFlag_96))
                {
                    flags |= 1 << 3;
                }
                else
                {
                    flags = 1 << 0;
                }
            }
            break;

        case 11:
            Savegame_EventFlagClear(EventFlag_121);
            break;

        case 7:
            if (!Savegame_EventFlagGet(EventFlag_98) && Savegame_EventFlagGet(EventFlag_122))
            {
                fArg1 = Q12(240.0f);
                flags = 1 << 0;
            }
            break;
    }

    Bgm_Update(flags, fArg1, sharedData_800E1208_1_s02);
}
