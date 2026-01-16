#if !defined(M2CTX) // Inlines cause issues with M2C context

#define CheckRange(axis, low, high)    \
({                                     \
    s32 val = (axis);                  \
    (low) <= (val) && (val) <= (high); \
})

#define CheckNotInRange(axis, low, high)  \
({                                        \
    s32 val = (axis);                     \
    !((low) <= (val) && (val) <= (high)); \
})

#ifdef MAP5_S01
static inline u32 GetXIdx(q19_12 x, q19_12 z)
{
    if (CheckRange(x + Q12(38.5f), Q12(-16.5f), Q12(16.5f)) && z > Q12(-160.0f))
    {
        if (z < Q12(-120.0f) || (z < Q12(-24.0f) && x < Q12(-32.0f)) ||
            CheckRange(x + Q12(40.0f), Q12(-12.0f), Q12(12.0f)))
        {
            return 1;
        }
    }

    if (CheckRange(x + Q12(-38.0f), Q12(-6.0f), Q12(6.0f)) && z < Q12(-40.0f))
    {
        return 2;
    }

    return 0;
}
#else
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
#endif

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

#elif defined(MAP2_S02) || defined(MAP4_S00) || defined(MAP4_S02) || defined(MAP4_S03) || \
      defined(MAP4_S05) || defined(MAP4_S06)

    if (CheckRange(x + Q12(120.0f), Q12(-14.0f), Q12(14.0f)) && z < Q12(40.0f))
    {
        xIdx = 1;
    }
    else if (CheckRange(x + Q12(60.0f), Q12(-9.0f), Q12(9.0f)) &&
             CheckRange(z + Q12(40.0f), Q12(-34.0f), Q12(34.0f)))
    {
        xIdx = 2;
    }
    else if (CheckRange(x + Q12(0.0f), Q12(-14.0f), Q12(14.0f)) && z > Q12(-80.0f))
    {
        xIdx = 3;
    }
    else
    {
        xIdx = 0;
    }

    if (CheckNotInRange(x + Q12(40.0f), Q12(-120.0f), Q12(120.0f)))
    {
        yIdx = 0;
    }
    else if (CheckRange(z + Q12(80.0f), Q12(-14.0f), Q12(14.0f)))
    {
        yIdx = 1;
    }
    else if (CheckRange(z + Q12(0.0f), Q12(-14.0f), Q12(14.0f)))
    {
        yIdx = 2;
    }
    else
    {
        yIdx = 0;
    }

    res = sharedData_800ED430_2_s02[(xIdx * 3) + yIdx];

#elif defined(MAP5_S01)
    xIdx = GetXIdx(x, z);

    // TODO: Could this be a `GetYIdx` inline like one above? No luck changing it yet.
    yIdx = 0;
    if (CheckRange(z + Q12(163.0f), Q12(-18.0f), Q12(18.0f)))
    {
        yIdx = 1;
    }
    else if (x > Q12(-40.0f))
    {
        if (x > Q12(40.0f))
        {
            if (CheckRange(z + Q12(36.0f), Q12(-16.0f), Q12(16.0f)))
            {
                yIdx = 2;
            }
        }
        else if (CheckRange(z + Q12(43.5f), Q12(-12.0f), Q12(12.0f)))
        {
            yIdx = 2;
        }
    }

    res = sharedData_800ED430_2_s02[(xIdx * 3) + yIdx];
#endif

    // If no match in primary grid, try fallback grid.
    if (res == 0)
    {
#define MAP_ROOM_STRIDE_Z ((MAP_ROOM_MAX_Z - MAP_ROOM_MIN_Z) / CHUNK_CELL_SIZE)

        if (x < MAP_ROOM_MIN_X || x >= MAP_ROOM_MAX_X ||
            z < MAP_ROOM_MIN_Z || z >= MAP_ROOM_MAX_Z)
        {
            return 0;
        }

        x = (x - MAP_ROOM_MIN_X) / CHUNK_CELL_SIZE;
        z = (z - MAP_ROOM_MIN_Z) / CHUNK_CELL_SIZE;

        res = MAP_ROOM_IDXS[(x * MAP_ROOM_STRIDE_Z) + z];
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
#endif
