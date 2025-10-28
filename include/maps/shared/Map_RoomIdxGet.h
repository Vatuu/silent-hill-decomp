u8 Map_RoomIdxGet(s32 x, s32 z)
{
    #define MAP_ROOM_STRIDE_Z ((MAP_ROOM_MAX_Z - MAP_ROOM_MIN_Z) / Q12(40.0f))

    if (x < MAP_ROOM_MIN_X || x >= MAP_ROOM_MAX_X ||
        z < MAP_ROOM_MIN_Z || z >= MAP_ROOM_MAX_Z)
    {
        return 0;
    }

    x = (x - MAP_ROOM_MIN_X) / Q12(40.0f);
    z = (z - MAP_ROOM_MIN_Z) / Q12(40.0f);

    return MAP_ROOM_IDXS[x * MAP_ROOM_STRIDE_Z + z];

    #undef MAP_ROOM_STRIDE_Z
}
