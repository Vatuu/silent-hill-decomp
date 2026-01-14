void sharedFunc_800CE8B8_0_s02(void)
{
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            Bgm_SongChange(6);
            break;

        case 18:
            Bgm_SongChange(!Savegame_EventFlagGet(EventFlag_379) ? 29 : 7);
            break;

        case 17:
            Bgm_SongChange(7);
            break;
    }
}
