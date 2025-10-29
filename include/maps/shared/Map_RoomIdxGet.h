#define CheckRange(axis, low, high)        \
    ({                                     \
        s32 val = (axis);                  \
        (low) <= (val) && (val) <= (high); \
    })

static inline s32 GetXIdx(q19_12 posX)
{
    if (CheckRange(posX + Q12(240.0f), Q12(-24.0f), Q12(24.0f)))
    {
        return 1;
    }

    if (CheckRange(posX + Q12(120.0f), Q12(-24.0f), Q12(24.0f)))
    {
        return 2;
    }

    if (CheckRange(posX + Q12(16.0f), Q12(0.0f), Q12(40.0f)))
    {
        return 3;
    }

    if (CheckRange(posX - Q12(120.0f), Q12(-24.0f), Q12(24.0f)))
    {
        return 4;
    }

    return 0;
}

static inline s32 GetYIdx(q19_12 posX, q19_12 posY)
{
    if (CheckRange(posY + Q12(202.0f), Q12(-18.0f), Q12(18.0f)))
    {
        return 1;
    }

    if (CheckRange(posY + Q12(79.0f), Q12(-15.0f), Q12(15.0f)) && posX < Q12(160.0f))
    {
        return 2;
    }

    if (CheckRange(posY + Q12(16.0f), 0, Q12(32.0f)))
    {
        return 3;
    }

    if (CheckRange(posY - Q12(124.0f), Q12(-20.0f), Q12(20.0f)))
    {
        return 4;
    }

    return 0;
}

u8 Map_RoomIdxGet(s32 x, s32 z)
{
    extern u8 MAP_ROOM_IDXS[];

    s32 xIdx;
    s32 yIdx;
    u8  res = 0;

    // TODO: Used in map0_s00/map0_s01/map2_s00/map2_s03, maybe some kind of outdoor/exterior grid?
#ifdef MAP_HAS_SECONDARY_GRID
    extern u8 sharedData_800DF2DC_0_s00[];

    // Check if coordinates are within primary grid bounds.
    if (x < Q12(-320.0f) || x >= Q12(240.0f) ||
        z < Q12(-240.0f) || z >= Q12(200.0f))
    {
        res = 0;
    }
    else
    {
        // Determine XY indices in primary grid.
        xIdx = GetXIdx(x);
        yIdx = GetYIdx(x, z);
        res  = sharedData_800DF2DC_0_s00[(xIdx * 5) + yIdx];
    }
#endif

    // If no match in primary grid, try fallback grid.
    if (res == 0)
    {
#define MAP_ROOM_STRIDE_Z ((MAP_ROOM_MAX_Z - MAP_ROOM_MIN_Z) / Q12(40.0f))

        if (x < MAP_ROOM_MIN_X || x >= MAP_ROOM_MAX_X ||
            z < MAP_ROOM_MIN_Z || z >= MAP_ROOM_MAX_Z)
        {
            return 0;
        }

        x = (x - MAP_ROOM_MIN_X) / Q12(40.0f);
        z = (z - MAP_ROOM_MIN_Z) / Q12(40.0f);

        res = MAP_ROOM_IDXS[x * MAP_ROOM_STRIDE_Z + z];
#ifdef MAP_HAS_SECONDARY_GRID
        if (res == 0)
        {
            res = 26;
        }
#endif

#undef MAP_ROOM_STRIDE_Z
    }

    return res;
}
