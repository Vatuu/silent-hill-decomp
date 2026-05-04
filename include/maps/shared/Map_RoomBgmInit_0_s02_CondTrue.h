void Map_RoomBgmInit_CondTrue(void)
{
    switch (g_SavegamePtr->mapRoomIdx)
    {
        case 5:
            Bgm_TrackChange(BgmTrackIdx_6);
            break;

        case 18:
            Bgm_TrackChange(!Savegame_EventFlagGet(EventFlag_379) ? BgmTrackIdx_29 : BgmTrackIdx_7);
            break;

        case 17:
            Bgm_TrackChange(BgmTrackIdx_7);
            break;
    }
}
