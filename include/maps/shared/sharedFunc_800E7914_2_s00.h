void sharedFunc_800E7914_2_s00(void)
{
    extern u8 sharedData_800F06D4_2_s00[8];
    s32       flags;
    s32       mapRoomIdx;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    flags      = (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ? (1 << 2) : (1 << 1);

    switch (mapRoomIdx)
    {
        case 33:
            if (!Savegame_EventFlagGet(EventFlag_195))
            {
                if (Savegame_EventFlagGet(EventFlag_165))
                {
                    flags |= 1 << 4;
                }
            }
            break;

        case 37:
        case 38:
            flags = (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ? (1 << 1) : (1 << 0);
            break;

        case 27:
        case 30:
            flags |= 1 << 1;
            break;

        case 35:
            flags = (1 << 1) | (1 << 2);
            break;
    }

    if (flags & (1 << 3))
    {
        s8 tmp                       = func_800364BC();
        sharedData_800F06D4_2_s00[3] = tmp;
    }

    func_80035F4C(flags, Q12(0.1f), &sharedData_800F06D4_2_s00);
}
