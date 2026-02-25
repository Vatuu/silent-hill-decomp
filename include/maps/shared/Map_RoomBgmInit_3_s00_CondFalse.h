void Map_RoomBgmInit_CondFalse(void)
{
    s32    flags;
    q19_12 var;
    s32    mapRoomIdx;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    var        = Q12(0.15f);

    switch (g_GameWork.bgmIdx_5B2)
    {
        case 16:
            flags = sharedData_800D21E8_3_s00[mapRoomIdx];

            // Check a few specific room indices.
            switch (mapRoomIdx)
            {
                case 1:
                    if (!Savegame_EventFlagGet(EventFlag_197))
                    {
                        // Test player Z position against specific value.
                        if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(143.2f))
                        {
                            flags = 0x6;
                        }
                        else
                        {
                            flags = 0xE;
                        }
                    }
                    break;

                case 17:
                case 20:
                    if (Savegame_EventFlagGet(EventFlag_M3S01_GeneratorOn))
                    {
                        flags |= 0x40;
                    }
                    break;
            }

            if (Savegame_EventFlagGet(EventFlag_MapMark_AltHospital2F_OperatingPrepRoomArrow) &&
                Savegame_EventFlagGet(EventFlag_MapMark_AltHospital2F_CorridorMidArrows))
            {
                flags |= 0x11E;
            }
            break;

        case 34:
            if (!Savegame_EventFlagGet(EventFlag_MapMark_FogHospital1F_StairsLocked))
            {
                var   = Q12(240.0f);
                flags = 0x201;
            }
            else if (Savegame_EventFlagGet(EventFlag_197))
            {
                var   = Q12(0.2f);
                flags = 0x201;
            }
            else
            {
                var   = Q12(240.0f);
                flags = 0x1FE;
            }
            break;

        case 25:
            if (!Savegame_EventFlagGet(EventFlag_295))
            {
                var   = Q12(240.0f);
                flags = 0x1FE;
            }
            else
            {
                var   = Q12(0.2f);
                flags = 0x301;
            }
            break;

        default:
            flags = 1;
            break;
    }

    Bgm_Update(flags, var, NULL);
}
