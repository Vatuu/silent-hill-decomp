void sharedFunc_800E9B38_2_s02(void) // 0x800CC99C
{
    s32 flags;

    flags = 1 << 1;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 17:
            if (Savegame_EventFlagGet(EventFlag_295) && !Savegame_EventFlagGet(EventFlag_352))
            {
                flags = (1 << 1) | (1 << 2);
            }
            break;

        case 12:
            if (!Savegame_EventFlagGet(EventFlag_295))
            {
                flags = (1 << 1) | (1 << 4);
            }
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_M3S06_PickupAntiqueShopKey))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S02_AntiqueShopOpen))
        {
            flags |= 1 << 3;
        }
    }

    if (flags & (1 << 3))
    {
        s8 temp_v0 = func_800364BC();
        sharedData_800ED43C_2_s02[3] = temp_v0;
    }

    Bgm_Update(flags, Q12(0.1f), sharedData_800ED43C_2_s02);
}
