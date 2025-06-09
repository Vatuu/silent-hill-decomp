#define chk_range(_v, _lower, _upper) ({\
    s32 _val = (_v);\
    _lower <= _val && _val <= _upper;\
})

// these are not really needed, but whatever
static inline s32 foo(s32 x) {
    if (chk_range(x + 0xF0000, -0x18000, 0x18000)) return 1;
    if (chk_range(x + 0x78000, -0x18000, 0x18000)) return 2;
    if (chk_range(x + 0x10000,        0, 0x28000)) return 3;
    if (chk_range(x - 0x78000, -0x18000, 0x18000)) return 4;
    
    return 0;
}

static inline s32 bar(s32 x, u32 y) {
    if (chk_range(y + 0xCA000, -0x12000, 0x12000)) return 1;
    if (chk_range(y + 0x4F000,  -0xF000,  0xF000) && x < 0xA0000) return 2;
    if (chk_range(y + 0x10000,        0, 0x20000)) return 3;
    if (chk_range(y - 0x7C000, -0x14000, 0x14000)) return 4;
    
    return 0;
}

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y)
{
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
        xIndex = foo(x);

        // Determine y index in primary grid
        yIndex = bar(x, y);
        
        result = D_800DF2DC[xIndex * 5 + yIndex];
    }
    
    // If no match in primary grid, try fallback grid
    if (result == 0)
    {   
        if ((x < -0x140000) || (x >= 0xF0000)) return 0;
        else if (y < -0xF0000) return 0;
        else if (y >= 0x190000) return 0;
        
        x = (x + 0x140000) / 0x28000;
        y = (y + 0xF0000) / 0x28000;
        result = D_800DF1FC[x * 16 + y];
        
        if (result == 0)
        {
            result = 0x1A;
        }
    }
    
    return result;
}
