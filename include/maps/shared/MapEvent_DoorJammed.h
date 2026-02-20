void MapEvent_DoorJammed(void)
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorJammed, Sfx_DoorJammed, &sfxPos);
}
