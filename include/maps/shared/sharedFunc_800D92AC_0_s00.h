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
    extern u8 sharedData_800DF2DC_0_s00[];
    extern u8 sharedData_800DF1FC_0_s00[];

    s32 xIdx;
    s32 yIdx;
    u8  res;
    
    // Check if coordinates are within primary grid bounds.
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
        res  = sharedData_800DF2DC_0_s00[(xIdx * 5) + yIdx];
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
        res = sharedData_800DF1FC_0_s00[(x * 16) + y];
        if (res == 0)
        {
            res = 26;
        }
    }

    return res;
}
