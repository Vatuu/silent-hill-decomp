void MapEvent_DoorLocked(void)
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ_8 };

#if defined(MAP1_S02)
    if (g_MapEventData->pointOfInterestIdx == 27)
    {
        Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#elif defined(MAP2_S00)
    if (g_MapEventData->pointOfInterestIdx == 57 || g_MapEventData->pointOfInterestIdx == 58)
    {
        Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#elif defined(MAP3_S02)
    Map_MessageWithSfx(16, Sfx_DoorLocked, &sfxPos); // "It's locked."
    return;
#endif

    Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_DoorLocked, &sfxPos);
}
