void Map_RoomBgmInit(bool arg0)
{
    s32 flags;
    s32 var_a1;
    s32 mapRoomIdx;
    u8* var_a2;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    var_a1  = Q12(0.1f);

    if (g_GameWork.bgmIdx == 13)
    {
        var_a2 = sharedData_800ED418_4_s02;

        switch (mapRoomIdx)
        {
            case 15:
                flags = 1 << 2;
                break;

            case 16:
                flags = (1 << 1) | (1 << 2);
                break;

            case 14:
                if (Savegame_EventFlagGet(EventFlag_352))
                {
                    var_a1 = Q12(10.0f);
                    flags = (1 << 0) | (1 << 8);
                }
                else if (Savegame_EventFlagGet(EventFlag_350))
                {
                    var_a1 = Q12(0.25f / 2.0f);
                    flags = (1 << 0) | (1 << 8);
                }
                else if (Savegame_EventFlagGet(EventFlag_348))
                {
                    if (g_SysWork.npcs[0].health < Q12(1000.0f))
                    {
                        flags = 0x1FE; // TODO: Demagic.
                    }
                    else
                    {
                        if (g_SysWork.playerWork.player.position.vy > Q12(-0.5f))
                        {
                            sharedData_800ED420_4_s02 = (1 << 1) | (1 << 3) | (1 << 8);
                        }
                        else if (g_SysWork.playerWork.player.position.vy < Q12(-2.5f))
                        {
                            sharedData_800ED420_4_s02 = (1 << 1) | (1 << 4) | (1 << 8);
                        }
                        flags = sharedData_800ED420_4_s02;

                        if (g_SysWork.npcs[0].health < Q12(2000.0f))
                        {
                            flags |= (1 << 2) | (1 << 5);
                        }
                        else if (g_SysWork.npcs[0].health < Q12(3000.0f))
                        {
                            flags |= 1 << 2;
                        }
                    }
                }
                else
                {
                    var_a1 = Q12(1.0f);
                    flags = (1 << 0) | (1 << 8);
                }
                break;

            default:
                flags = 1 << 0;
                break;
        }
    }
    else if (g_GameWork.bgmIdx == BgmTrackIdx_33)
    {
        var_a2 = sharedData_800ED424_4_s02;

        switch (mapRoomIdx)
        {
            case 18:
                if (Savegame_EventFlagGet(EventFlag_334) || !Savegame_EventFlagGet(EventFlag_333))
                {
                    flags = 1 << 1;
                }
                else
                {
                    if (Savegame_EventFlagGet(EventFlag_330))
                    {
                        flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
                        var_a1 = CHUNK_CELL_SIZE;
                    }
                    else
                    {
                        flags = (1 << 1) | (1 << 2) | (1 << 3);
                    }
                }
                break;

            case 19:
                Savegame_EventFlagSet(EventFlag_334);

                if (Savegame_EventFlagGet(EventFlag_320))
                {
                    flags = (1 << 0) | (1 << 8);
                }
                else
                {
                    flags = (1 << 2) | (1 << 8);
                }
                break;

            case 21:
                flags = 8;
                break;

            case 20:
                if (Savegame_EventFlagGet(EventFlag_327))
                {
                    flags = (1 << 4) | (1 << 8);
                }
                else if (Savegame_EventFlagGet(EventFlag_324) || Savegame_EventFlagGet(EventFlag_329))
                {
                    var_a1 = Q12(0.5f);

                    if (g_SysWork.npcs[0].health > Q12(0.0f) &&
                        g_SysWork.npcs[0].position.vy < Q12(1.0f))
                    {
                        flags = (1 << 5) | (1 << 6) | (1 << 8);
                    }
                    else
                    {
                        flags = (1 << 5) | (1 << 8);
                    }
                }
                else
                {
                    flags = (1 << 4) | (1 << 8);
                }
                break;

            default:
                flags = (1 << 0) | (1 << 8);
                break;
        }
    }
    else
    {
        var_a2 = sharedData_800ED458_4_s02;

        if (!Savegame_EventFlagGet(EventFlag_314))
        {
            if (g_SysWork.playerWork.player.position.vz < CHUNK_CELL_SIZE)
            {
                Savegame_EventFlagSet(EventFlag_314);
            }

            flags = 1 << 1;
        }
        else
        {
            flags = sharedData_800ED42C_4_s02[mapRoomIdx];
        }
    }

    Bgm_Update(flags, var_a1, var_a2);
}
