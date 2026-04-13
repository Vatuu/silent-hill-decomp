void Map_RoomBgmInit(bool arg0)
{
    s32 var_a0;
    s32 var_a1;
    s32 mapRoomIdx;
    u8* var_a2;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    var_a1  = Q12(0.1f);

    if (g_GameWork.bgmIdx_5B2 == 13)
    {
        var_a2 = sharedData_800ED418_4_s02;

        switch (mapRoomIdx)
        {
            case 15:
                var_a0 = 4;
                break;

            case 16:
                var_a0 = 6;
                break;

            case 14:
                if (Savegame_EventFlagGet(EventFlag_352))
                {
                    var_a1 = 0xA000;
                    var_a0 = 0x101;
                }
                else if (Savegame_EventFlagGet(EventFlag_350))
                {
                    var_a1 = 0x200;
                    var_a0 = 0x101;
                }
                else if (Savegame_EventFlagGet(EventFlag_348))
                {
                    if (g_SysWork.npcs_1A0[0].health < 0x3E8000)
                    {
                        var_a0 = 0x1FE;
                    }
                    else
                    {
                        if (g_SysWork.playerWork_4C.player_0.position.vy > -0x800)
                        {
                            sharedData_800ED420_4_s02 = 0x10A;
                        }
                        else if (g_SysWork.playerWork_4C.player_0.position.vy < -0x2800)
                        {
                            sharedData_800ED420_4_s02 = 0x112;
                        }

                        var_a0 = sharedData_800ED420_4_s02;

                        if (g_SysWork.npcs_1A0[0].health < 0x7D0000)
                        {
                            var_a0 |= 0x24;
                        }
                        else if (g_SysWork.npcs_1A0[0].health < 0xBB8000)
                        {
                            var_a0 |= 1 << 2;
                        }
                    }
                }
                else
                {
                    var_a1 = 0x1000;
                    var_a0 = 0x101;
                }
                break;

            default:
                var_a0 = 1;
                break;
        }
    }
    else if (g_GameWork.bgmIdx_5B2 == 0x21)
    {
        var_a2 = sharedData_800ED424_4_s02;

        switch (mapRoomIdx)
        {
            case 18:
                if (Savegame_EventFlagGet(EventFlag_334) || !Savegame_EventFlagGet(EventFlag_333))
                {
                    var_a0 = 2;
                }
                else
                {
                    if (Savegame_EventFlagGet(EventFlag_330))
                    {
                        var_a0 = 0x1E;
                        var_a1 = 0x28000;
                    }
                    else
                    {
                        var_a0 = 0xE;
                    }
                }
                break;

            case 19:
                Savegame_EventFlagSet(EventFlag_334);

                if (Savegame_EventFlagGet(EventFlag_320))
                {
                    var_a0 = 0x101;
                }
                else
                {
                    var_a0 = 0x104;
                }
                break;

            case 21:
                var_a0 = 8;
                break;

            case 20:
                if (Savegame_EventFlagGet(EventFlag_327))
                {
                    var_a0 = 0x110;
                }
                else if (Savegame_EventFlagGet(EventFlag_324) || Savegame_EventFlagGet(EventFlag_329))
                {
                    var_a1 = 0x800;

                    if (g_SysWork.npcs_1A0[0].health > Q12(0.0f) &&
                        g_SysWork.npcs_1A0[0].position.vy < Q12(1.0f))
                    {
                        var_a0 = 0x160;
                    }
                    else
                    {
                        var_a0 = 0x120;
                    }
                }
                else
                {
                    var_a0 = 0x110;
                }
                break;

            default:
                var_a0 = 0x101;
                break;
        }
    }
    else
    {
        var_a2 = sharedData_800ED458_4_s02;

        if (!Savegame_EventFlagGet(EventFlag_314))
        {
            if (g_SysWork.playerWork_4C.player_0.position.vz < 0x28000)
            {
                Savegame_EventFlagSet(EventFlag_314);
            }

            var_a0 = 2;
        }
        else
        {
            var_a0 = sharedData_800ED42C_4_s02[mapRoomIdx];
        }
    }

    Bgm_Update(var_a0, var_a1, var_a2);
}
