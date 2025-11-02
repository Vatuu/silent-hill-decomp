void MapEvent_DoorLocked(void)
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

#if defined(MAP1_S02)
    if (g_MapEventParam->field_5 == 27)
    {
        Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#elif defined(MAP2_S00)
    if (g_MapEventParam->field_5 == 57 || g_MapEventParam->field_5 == 58)
    {
        Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1349, &sfxPos);
        return;
    }
#endif

    Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_DoorLocked, &sfxPos);
}
