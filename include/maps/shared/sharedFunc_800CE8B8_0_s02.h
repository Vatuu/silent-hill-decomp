void sharedFunc_800CE8B8_0_s02(void)
{
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            Bgm_TrackChange(6);
            break;

        case 18:
            Bgm_TrackChange(!Savegame_EventFlagGet(EventFlag_379) ? 29 : 7);
            break;

        case 17:
            Bgm_TrackChange(7);
            break;
    }
}
