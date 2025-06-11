#define CheckRange(_v, _lower, _upper) \
({                                     \
    s32 _val = (_v);                   \
    _lower <= _val && _val <= _upper;  \
})

static inline s32 GetXIndex(s32 x)
{
    if (CheckRange(x + FP_METER_REAL(240.0f), FP_METER_REAL(-24.0f), FP_METER_REAL(24.0f)))
    {
        return 1;
    }

    if (CheckRange(x + FP_METER_REAL(120.0f), FP_METER_REAL(-24.0f), FP_METER_REAL(24.0f)))
    {
        return 2;
    }

    if (CheckRange(x + FP_METER_REAL(16.0f), 0, FP_METER_REAL(40)))
    {
        return 3;
    }

    if (CheckRange(x - FP_METER_REAL(120.0f), FP_METER_REAL(-24.0f), FP_METER_REAL(24.0f)))
    {
        return 4;
    }
    
    return 0;
}

static inline s32 GetYIndex(s32 x, u32 y)
{
    if (CheckRange(y + FP_METER_REAL(202.0f), FP_METER_REAL(-18.0f), FP_METER_REAL(18.0f)))
    {
        return 1;
    }

    if (CheckRange(y + FP_METER_REAL(79.0f), FP_METER_REAL(-15.0f), FP_METER_REAL(15.0f)) && x < FP_METER_REAL(160.0f))
    {
        return 2;
    }

    if (CheckRange(y + FP_METER_REAL(16.0f), 0, FP_METER_REAL(32.0f)))
    {
        return 3;
    }

    if (CheckRange(y - FP_METER_REAL(124.0f), FP_METER_REAL(-20.0f), FP_METER_REAL(20.0f)))
    {
        return 4;
    }

    return 0;
}

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y)
{
    #if defined(MAP0_S00)
        extern u8 D_800DF2DC[];
        extern u8 D_800DF1FC[];

        #define PRIMARY_GRID_LT  D_800DF2DC
        #define FALLBACK_GRID_LT D_800DF1FC
    #elif defined(MAP0_S01)
        extern u8 D_800DDD78[];
        extern u8 D_800DDC98[];

        #define PRIMARY_GRID_LT  D_800DDD78
        #define FALLBACK_GRID_LT D_800DDC98
    #elif defined(MAP2_S00)
        extern u8 D_800F06B8[];
        extern u8 D_800F05D8[];

        #define PRIMARY_GRID_LT  D_800F06B8
        #define FALLBACK_GRID_LT D_800F05D8
    #elif defined(MAP2_S03)
        extern u8 D_800CCC90[];
        extern u8 D_800CCBB0[];

        #define PRIMARY_GRID_LT  D_800CCC90
        #define FALLBACK_GRID_LT D_800CCBB0
    #endif

    s32 xIdx;
    s32 yIdx;
    u8  res;
    
    // Check if coordinates are within primary grid bounds
    if (x < FP_METER_REAL(-320.0f) || x >= FP_METER_REAL(240.0f))
    {
        res = 0;
    }
    else if (y < FP_METER_REAL(-240.0f))
    {
        res = 0;
    }
    else if (y >= FP_METER_REAL(200.0f))
    {
        res = 0;
    }
    else
    {
        // Determine XY indices in primary grid.
        xIdx = GetXIndex(x);
        yIdx = GetYIndex(x, y);
        res  = PRIMARY_GRID_LT[(xIdx * 5) + yIdx];
    }
    
    // If no match in primary grid, try fallback grid.
    if (res == 0)
    {   
        if (x < FP_METER_REAL(-320.0f) || x >= FP_METER_REAL(240.0f))
        {
            return 0;
        }
        else if (y < FP_METER_REAL(-240.0f))
        {
            return 0;
        }
        else if (y >= FP_METER_REAL(400.0f))
        {
            return 0;
        }

        x   = (x + FP_METER_REAL(320.0f)) / FP_METER_REAL(40.0f);
        y   = (y + FP_METER_REAL(240.0f)) / FP_METER_REAL(40.0f);
        res = FALLBACK_GRID_LT[(x * 16) + y];
        if (res == 0)
        {
            res = 26;
        }
    }

    return res;
}
