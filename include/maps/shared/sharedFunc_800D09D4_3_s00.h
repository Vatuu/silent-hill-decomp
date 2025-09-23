void sharedFunc_800D09D4_3_s00()
{
    s32         flags;
    s32         var;
    s32         mapRoomIdx;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    var        = 0x266;

    switch (g_GameWork.soundCmd_5B2)
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
                        if (g_SysWork.player_4C.chara_0.position_18.vz > Q12(143.2f))
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
                    if (Savegame_EventFlagGet(EventFlag_211))
                    {
                        flags |= 0x40;
                    }
                    break;
            }

            if ((g_SavegamePtr->mapMarkingFlags_1E0[18] & ((1 << 16) | (1 << 22))) == ((1 << 16) | (1 << 22)))
            {
                flags |= 0x11E;
            }
            break;

        case 34:
            if (!(g_SavegamePtr->mapMarkingFlags_1E0[14] & (1 << 19)))
            {
                var   = 0xF0000;
                flags = 0x201;
            }
            else if (Savegame_EventFlagGet(EventFlag_197))
            {
                var   = 0x333;
                flags = 0x201;
            }
            else
            {
                var   = 0xF0000;
                flags = 0x1FE;
            }
            break;

        case 25:
            if (!Savegame_EventFlagGet(EventFlag_295))
            {
                var   = 0xF0000;
                flags = 0x1FE;
            }
            else
            {
                var   = 0x333;
                flags = 0x301;
            }
            break;

        default:
            flags = 1;
            break;
    }

    func_80035F4C(flags, var, NULL);
}
