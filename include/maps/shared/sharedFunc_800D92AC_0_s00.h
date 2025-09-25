#define CheckRange(axis, low, high)    \
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

u8 sharedFunc_800D92AC_0_s00(s32 posX, s32 posY)
{
    extern u8 sharedData_800DF2DC_0_s00[];
    extern u8 sharedData_800DF1FC_0_s00[];

    s32 xIdx;
    s32 yIdx;
    u8  res;
    
    // Check if coordinates are within primary grid bounds.
    if (posX < Q12(-320.0f) || posX >= Q12(240.0f))
    {
        res = 0;
    }
    else if (posY < Q12(-240.0f))
    {
        res = 0;
    }
    else if (posY >= Q12(200.0f))
    {
        res = 0;
    }
    else
    {
        // Determine XY indices in primary grid.
        xIdx = GetXIdx(posX);
        yIdx = GetYIdx(posX, posY);
        res  = sharedData_800DF2DC_0_s00[(xIdx * 5) + yIdx];
    }
    
    // If no match in primary grid, try fallback grid.
    if (res == 0)
    {   
        if (posX < Q12(-320.0f) || posX >= Q12(240.0f))
        {
            return 0;
        }
        else if (posY < Q12(-240.0f))
        {
            return 0;
        }
        else if (posY >= Q12(400.0f))
        {
            return 0;
        }

        posX = (posX + Q12(320.0f)) / Q12(40.0f);
        posY = (posY + Q12(240.0f)) / Q12(40.0f);
        res  = sharedData_800DF1FC_0_s00[(posX * 16) + posY];
        if (res == 0)
        {
            res = 26;
        }
    }

    return res;
}
