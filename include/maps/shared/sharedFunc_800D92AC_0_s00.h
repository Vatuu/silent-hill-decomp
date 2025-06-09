#define chk_range(_v, _lower, _upper) ({\
    s32 _val = (_v);\
    _lower <= _val && _val <= _upper;\
})

// these are not really needed, but whatever
static inline s32 _GetXIndex(s32 x) {
    if (chk_range(x + 0xF0000, -0x18000, 0x18000)) return 1;
    if (chk_range(x + 0x78000, -0x18000, 0x18000)) return 2;
    if (chk_range(x + 0x10000,        0, 0x28000)) return 3;
    if (chk_range(x - 0x78000, -0x18000, 0x18000)) return 4;
    
    return 0;
}

static inline s32 _GetYIndex(s32 x, u32 y) {
    if (chk_range(y + 0xCA000, -0x12000, 0x12000)) return 1;
    if (chk_range(y + 0x4F000,  -0xF000,  0xF000) && x < 0xA0000) return 2;
    if (chk_range(y + 0x10000,        0, 0x20000)) return 3;
    if (chk_range(y - 0x7C000, -0x14000, 0x14000)) return 4;
    
    return 0;
}

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y)
{
    #if defined(MAP0_S00)
        extern u8 D_800DF2DC[];
        extern u8 D_800DF1FC[];
        #define PRIMARY_GRID_LT D_800DF2DC
        #define FALLBACK_GRID_LT D_800DF1FC
    #elif defined(MAP0_S01)
        extern u8 D_800DDD78[];
        extern u8 D_800DDC98[];
        #define PRIMARY_GRID_LT D_800DDD78
        #define FALLBACK_GRID_LT D_800DDC98
    #elif defined(MAP2_S00)
        extern u8 D_800F06B8[];
        extern u8 D_800F05D8[];
        #define PRIMARY_GRID_LT D_800F06B8
        #define FALLBACK_GRID_LT D_800F05D8
    #elif defined(MAP2_S03)
        extern u8 D_800CCC90[];
        extern u8 D_800CCBB0[];
        #define PRIMARY_GRID_LT D_800CCC90
        #define FALLBACK_GRID_LT D_800CCBB0
    #endif

    s32 xIndex;
    s32 yIndex;
    u8 result;
    
    // Check if coordinates are within primary grid bounds
    if ((x < -0x140000) || (x >= 0xF0000)) result = 0;
    else if (y < -0xF0000) result = 0;
    else if (y >= 0xC8000) result = 0;
    else
    {
        // Determine x index in primary grid
        xIndex = _GetXIndex(x);

        // Determine y index in primary grid
        yIndex = _GetYIndex(x, y);
        
        result = PRIMARY_GRID_LT[xIndex * 5 + yIndex];
    }
    
    // If no match in primary grid, try fallback grid
    if (result == 0)
    {   
        if ((x < -0x140000) || (x >= 0xF0000)) return 0;
        else if (y < -0xF0000) return 0;
        else if (y >= 0x190000) return 0;
        
        x = (x + 0x140000) / 0x28000;
        y = (y + 0xF0000) / 0x28000;
        result = FALLBACK_GRID_LT[x * 16 + y];
        
        if (result == 0)
        {
            result = 0x1A;
        }
    }
    
    return result;
}
