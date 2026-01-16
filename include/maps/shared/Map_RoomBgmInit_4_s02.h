void Map_RoomBgmInit(bool arg0)
{
    s32              var_a0;
    s32              var_a1;
    s32              temp_a3;
    u8* var_a2;

    temp_a3 = g_SavegamePtr->mapRoomIdx_A5;
    var_a1  = 0x199;

    if (g_GameWork.bgmIdx_5B2 == 0xD)
    {
        var_a2 = sharedData_800ED418_4_s02;

        switch (temp_a3)
        {
            case 0xF:
                var_a0 = 4;
                break;

            case 0x10:
                var_a0 = 6;
                break;

            case 0xE:
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
                    if (g_SysWork.npcs_1A0[0].health_B0 < 0x3E8000)
                    {
                        var_a0 = 0x1FE;
                    }
                    else
                    {
                        if (g_SysWork.playerWork_4C.player_0.position_18.vy > -0x800)
                        {
                            sharedData_800ED420_4_s02 = 0x10A;
                        }
                        else if (g_SysWork.playerWork_4C.player_0.position_18.vy < -0x2800)
                        {
                            sharedData_800ED420_4_s02 = 0x112;
                        }

                        var_a0 = sharedData_800ED420_4_s02;

                        if (g_SysWork.npcs_1A0[0].health_B0 < 0x7D0000)
                        {
                            var_a0 |= 0x24;
                        }
                        else if (g_SysWork.npcs_1A0[0].health_B0 < 0xBB8000)
                        {
                            var_a0 |= 4;
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

        switch (temp_a3)
        {
            case 0x12:
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

            case 0x13:
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

            case 0x15:
                var_a0 = 8;
                break;

            case 0x14:
                if (Savegame_EventFlagGet(EventFlag_327))
                {
                    var_a0 = 0x110;
                }
                else if (Savegame_EventFlagGet(EventFlag_324) || Savegame_EventFlagGet(EventFlag_329))
                {
                    var_a1 = 0x800;

                    if (g_SysWork.npcs_1A0[0].health_B0 > 0 && g_SysWork.npcs_1A0[0].position_18.vy < 0x1000)
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
            if (g_SysWork.playerWork_4C.player_0.position_18.vz < 0x28000)
            {
                Savegame_EventFlagSet(EventFlag_314);
            }
            var_a0 = 2;
        }
        else
        {
            var_a0 = sharedData_800ED42C_4_s02[temp_a3];
        }
    }

    Bgm_Update(var_a0, var_a1, var_a2);
}
