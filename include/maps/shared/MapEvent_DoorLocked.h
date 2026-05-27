void MapEvent_DoorLocked(void)
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ };

#if defined(MAP1_S02)
    if (g_MapEventData->pointOfInterestIdx == 27)
    {
        Event_DisplayMapMsgWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#elif defined(MAP2_S00)
    if (g_MapEventData->pointOfInterestIdx == 57 || g_MapEventData->pointOfInterestIdx == 58)
    {
        Event_DisplayMapMsgWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#elif defined(MAP3_S02)
    Event_DisplayMapMsgWithSfx(16, Sfx_DoorLocked, &sfxPos); // "It's locked."
    return;
#endif

    Event_DisplayMapMsgWithSfx(MapMsgIdx_DoorLocked, Sfx_DoorLocked, &sfxPos);
}
