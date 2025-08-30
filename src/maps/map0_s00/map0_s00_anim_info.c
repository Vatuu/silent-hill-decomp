#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s_AnimInfo g_AnimInfo[] =
{
    { Anim_Update2, 76,  0, 77,  0, { FP_TIME(10.0f) }, -1,  676 },
    { Anim_Update0, 77,  0, 77,  0, { FP_TIME(10.0f) }, 676, 677 },
    { Anim_Update2, 78,  0, 79,  0, { FP_TIME(10.0f) }, -1,  678 },
    { Anim_Update0, 79,  0, 79,  0, { FP_TIME(10.0f) }, 678, 713 },
    { Anim_Update2, 80,  0, 81,  0, { FP_TIME(10.0f) }, -1,  718 },
    { Anim_Update0, 81,  0, 81,  0, { FP_TIME(15.0f) }, 718, 732 },
    { Anim_Update2, 82,  0, 83,  0, { FP_TIME(10.0f) }, -1,  737 },
    { Anim_Update0, 83,  0, 83,  0, { FP_TIME(15.0f) }, 737, 751 },
    { Anim_Update2, 84,  0, 85,  0, { FP_TIME(10.0f) }, -1,  758 },
    { Anim_Update0, 85,  0, 85,  0, { FP_TIME(15.0f) }, 758, 770 },
    { Anim_Update2, 86,  0, 87,  0, { FP_TIME(10.0f) }, -1,  777 },
    { Anim_Update0, 87,  0, 87,  0, { FP_TIME(15.0f) }, 777, 789 },
    { Anim_Update2, 88,  0, 89,  0, { FP_TIME(8.0f) }, -1,   790 },
    { Anim_Update1, 89,  0, -1,  0, { FP_TIME(18.0f) }, 790, 807 },
    { Anim_Update2, 90,  0, 91,  0, { FP_TIME(8.0f) }, -1,   808 },
    { Anim_Update1, 91,  0, -1,  0, { FP_TIME(18.0f) }, 808, 825 },
    { Anim_Update2, 92,  0, 93,  0, { FP_TIME(8.0f) }, -1,   826 },
    { Anim_Update0, 93,  0, 93,  0, { FP_TIME(18.0f) }, 826, 843 },
    { Anim_Update2, 94,  0, 95,  0, { FP_TIME(8.0f) }, -1,   844 },
    { Anim_Update0, 95,  0, 95,  0, { FP_TIME(18.0f) }, 844, 861 },
    { Anim_Update2, 96,  0, 97,  0, { FP_TIME(10.0f) }, -1,  862 },
    { Anim_Update0, 97,  0, 97,  0, { FP_TIME(15.0f) }, 862, 882 },
    { Anim_Update2, 98,  0, 99,  0, { FP_TIME(10.0f) }, -1,  883 },
    { Anim_Update0, 99,  0, 99,  0, { FP_TIME(15.0f) }, 883, 903 },
    { Anim_Update2, 100, 0, 101, 0, { FP_TIME(10.0f) }, -1,  904 },
    { Anim_Update0, 101, 0, 101, 0, { FP_TIME(15.0f) }, 904, 914 },
    { Anim_Update2, 102, 0, 103, 0, { FP_TIME(10.0f) }, -1,  915 },
    { Anim_Update0, 103, 0, 103, 0, { FP_TIME(15.0f) }, 915, 925 },
    { Anim_Update2, 104, 0, 105, 0, { FP_TIME(2.0f) }, -1,   926 },
    { Anim_Update0, 105, 0, 105, 0, { FP_TIME(4.0f) }, 926,  972 },
    { Anim_Update2, 106, 0, 107, 0, { FP_TIME(10.0f) }, -1,  973 },
    { Anim_Update0, 107, 0, 107, 0, { FP_TIME(15.0f) }, 973, 993 },
    { Anim_Update2, 108, 0, 109, 0, { FP_TIME(10.0f) }, -1,  994 },
    { Anim_Update0, 109, 0, 109, 0, { FP_TIME(25.0f) }, 994, 1026 },
    {} // End of list.
};

/* Not sure if the time_4 field (3rd) is actually time.
 * these numbers produce very small and non round numbers.
 * I also seen some code read this field and add very small numbers like 4 or 32.
 * This is why I don't use any FP macros here
 */
s_UnkStruct3_Mo g_MapHeaderTable_38[18] = {
    { 0x4d4c, 0x0,   0x2a4, 0x2a5 },
    { 0x4f4e, 0xca,  0x2a6, 0x2c9 },
    { 0x5150, 0xd2,  0x2ca, 0x2dc },
    { 0x5352, 0xd3,  0x2dd, 0x2ef },
    { 0x5554, 0xd4,  0x2f0, 0x302 },
    { 0x5756, 0xd5,  0x303, 0x315 },
    { 0x5958, 0xeb,  0x316, 0x327 },
    { 0x5b5a, 0xec,  0x328, 0x339 },
    { 0x5d5c, 0xf5,  0x33a, 0x34b },
    { 0x5f5e, 0xf6,  0x34c, 0x35d },
    { 0x6160, 0x154, 0x35e, 0x372 },
    { 0x6362, 0x155, 0x373, 0x387 },
    { 0x6564, 0x156, 0x388, 0x392 },
    { 0x6766, 0x157, 0x393, 0x39d },
    { 0x6968, 0x15e, 0x39e, 0x3cc },
    { 0x6b6a, 0x164, 0x3cd, 0x3e1 },
    { 0x6d6c, 0x165, 0x3e2, 0x402 },
    {}, // end of list
};

u8 g_LoadableItems[8] =
{
    InventoryItemId_HealthDrink,
    InventoryItemId_Chainsaw,
    InventoryItemId_HyperBlaster,
    InventoryItemId_RockDrill,
    InventoryItemId_GasolineTank,
    InventoryItemId_ChannelingStone,
    InventoryItemId_Katana,
    0
};
