void Map_RoomBgmInit(bool arg0)
{
    extern u8 sharedData_800F06D4_2_s00[8];
    s32       bgmFlags;
    s32       mapRoomIdx;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx;
    bgmFlags   = (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ? BgmFlag_Layer2 : BgmFlag_Layer1;

    switch (mapRoomIdx)
    {
        case 33:
            if (!Savegame_EventFlagGet(EventFlag_195))
            {
                if (Savegame_EventFlagGet(EventFlag_165))
                {
                    bgmFlags |= BgmFlag_Layer4;
                }
            }
            break;

        case 37:
        case 38:
            bgmFlags = (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ? BgmFlag_Layer1 : BgmFlag_Layer0;
            break;

        case 27:
        case 30:
            bgmFlags |= BgmFlag_Layer1;
            break;

        case 35:
            bgmFlags = BgmFlag_Layer1 | BgmFlag_Layer2;
            break;
    }

    if (bgmFlags & BgmFlag_Layer3)
    {
        s8 tmp                       = func_800364BC();
        sharedData_800F06D4_2_s00[3] = tmp;
    }

    Bgm_Update(bgmFlags, Q12(0.1f), &sharedData_800F06D4_2_s00);
}
