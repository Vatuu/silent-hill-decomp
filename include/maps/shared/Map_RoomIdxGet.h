u8 Map_RoomIdxGet(s32 x, s32 z)
{
    u32 ux;

    x += Q12(200.0f);
    ux = x;

    if (ux >= Q12(400.0f) || z < 0 || z >= Q12(120.0f))
    {
        return 0;
    }

    x /= Q12(40.0f);
    z /= Q12(40.0f);
    return ux = MAP_ROOM_IDXS[(x * 3) + z]; // @hack Permuter find.
}
