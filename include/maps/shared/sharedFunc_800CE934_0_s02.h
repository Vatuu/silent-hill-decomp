void sharedFunc_800CE934_0_s02(void)
{
    s32 var_a0; // } Looks like numbers meant to be in hex? Could be `e_Sfx` or sound command related (upper 8 bits is cmd, lower 8 is param?)
    s32 var_a1; // }
    u8* var_a2; // Points to 8 bytes of data?

    var_a1 = 0x199;
    var_a2 = sharedData_800CFB14_0_s02;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 1:
            var_a1 = 0xF0000;
            var_a0 = Savegame_EventFlagGet(EventFlag_182) ? 0xFE : 0x201;
            break;

        case 2:
        case 3:
        case 4:
            var_a0 = (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) ? 2 : 1;
            var_a2 = sharedData_800CFB1C_0_s02;
            break;

        case 10:
        case 12:
        case 13:
            var_a1 = 0x400;
            var_a2 = sharedData_800CFB24_0_s02;

            if (Savegame_EventFlagGet(EventFlag_312))
            {
                var_a0 = 0xC;
            }
            else if (!Savegame_EventFlagGet(EventFlag_303))
            {
                if (Savegame_EventFlagGet(EventFlag_311))
                {
                    var_a1 = 0x200;
                    var_a0 = 2;
                }
                else
                {
                    var_a1 = 0xF0000;
                    var_a0 = 0x201;
                }
            }
            else
            {
                var_a0 = 8;
            }
            break;

        case 11:
            var_a0 = 0x201;
            break;

        case 17:
            var_a2 = sharedData_800CFB2C_0_s02;
            var_a0 = 0x201;
            break;

        case 18:
            var_a2 = g_GameWork.soundCmd_5B2 == 7 ? sharedData_800CFB34_0_s02 : sharedData_800CFB3C_0_s02;

            if (Savegame_EventFlagGet(EventFlag_379))
            {
                if (Savegame_EventFlagGet(EventFlag_381))
                {
                    var_a1 = 0xF0000;
                    Savegame_EventFlagClear(EventFlag_381);
                }
                else
                {
                    var_a1 = 0x200;
                }
                var_a0 = 0x301;
            }
            else if (Savegame_EventFlagGet(EventFlag_381))
            {
                var_a1 = 0xF0000;
                var_a0 = 0x1FE;
            }
            else
            {
                var_a1 = Savegame_EventFlagGet(EventFlag_378) ? 0x400 : 0x200;
                var_a0 = 0x301;
            }

            break;

        case 6:
        case 7:
        case 8:
        case 9:
            if (g_GameWork.soundCmd_5B2 == 34)
            {
                if (Savegame_EventFlagGet(EventFlag_391))
                {
                    var_a1 = 0xF0000;
                    var_a0 = 0x201;
                }
                else if (Savegame_EventFlagGet(EventFlag_395))
                {
                    var_a1 = 0xF0000;
                    var_a0 = 0xFE;
                }
                else
                {
                    var_a0 = 0x201;
                }
            }
            else
            {
                var_a2 = sharedData_800CFB44_0_s02;
                var_a0 = 1;
            }
            break;

        case 5:
            var_a0 = 1;
            break;

        case 19:
        case 20:
            if (g_GameWork.soundCmd_5B2 == 23)
            {
                var_a2 = sharedData_800CFB4C_0_s02;
                var_a1 = 0x400;

                if (Savegame_EventFlagGet(EventFlag_423) && !Savegame_EventFlagGet(EventFlag_424))
                {
                    var_a0 = Savegame_EventFlagGet(EventFlag_427) ? 0x1A : 0xE;
                }
                else if (Savegame_EventFlagGet(EventFlag_425) && !Savegame_EventFlagGet(EventFlag_426))
                {
                    var_a0 = 6;
                }
                else
                {
                    var_a0 = 2;
                }
            }
            else
            {
                var_a2 = sharedData_800CFB54_0_s02;
                var_a0 = 0x16;
            }
            break;

        default:
            var_a0 = 0xFE;
            break;
    }

    func_80035F4C(var_a0, var_a1, var_a2);
}
