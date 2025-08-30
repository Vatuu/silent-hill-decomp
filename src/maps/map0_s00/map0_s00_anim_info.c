#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s_AnimInfo g_AnimInfo[] =
{
    { Anim_Update2, 76,  0, 77,       0, { FP_TIME(10.0f) }, NO_VALUE, 676 },
    { Anim_Update0, 77,  0, 77,       0, { FP_TIME(10.0f) }, 676,      677 },
    { Anim_Update2, 78,  0, 79,       0, { FP_TIME(10.0f) }, NO_VALUE, 678 },
    { Anim_Update0, 79,  0, 79,       0, { FP_TIME(10.0f) }, 678,      713 },
    { Anim_Update2, 80,  0, 81,       0, { FP_TIME(10.0f) }, NO_VALUE, 718 },
    { Anim_Update0, 81,  0, 81,       0, { FP_TIME(15.0f) }, 718,      732 },
    { Anim_Update2, 82,  0, 83,       0, { FP_TIME(10.0f) }, NO_VALUE, 737 },
    { Anim_Update0, 83,  0, 83,       0, { FP_TIME(15.0f) }, 737,      751 },
    { Anim_Update2, 84,  0, 85,       0, { FP_TIME(10.0f) }, NO_VALUE, 758 },
    { Anim_Update0, 85,  0, 85,       0, { FP_TIME(15.0f) }, 758,      770 },
    { Anim_Update2, 86,  0, 87,       0, { FP_TIME(10.0f) }, NO_VALUE, 777 },
    { Anim_Update0, 87,  0, 87,       0, { FP_TIME(15.0f) }, 777,      789 },
    { Anim_Update2, 88,  0, 89,       0, { FP_TIME(8.0f) },  NO_VALUE, 790 },
    { Anim_Update1, 89,  0, NO_VALUE, 0, { FP_TIME(18.0f) }, 790,      807 },
    { Anim_Update2, 90,  0, 91,       0, { FP_TIME(8.0f) },  NO_VALUE, 808 },
    { Anim_Update1, 91,  0, NO_VALUE, 0, { FP_TIME(18.0f) }, 808,      825 },
    { Anim_Update2, 92,  0, 93,       0, { FP_TIME(8.0f) },  NO_VALUE, 826 },
    { Anim_Update0, 93,  0, 93,       0, { FP_TIME(18.0f) }, 826,      843 },
    { Anim_Update2, 94,  0, 95,       0, { FP_TIME(8.0f) },  NO_VALUE, 844 },
    { Anim_Update0, 95,  0, 95,       0, { FP_TIME(18.0f) }, 844,      861 },
    { Anim_Update2, 96,  0, 97,       0, { FP_TIME(10.0f) }, NO_VALUE, 862 },
    { Anim_Update0, 97,  0, 97,       0, { FP_TIME(15.0f) }, 862,      882 },
    { Anim_Update2, 98,  0, 99,       0, { FP_TIME(10.0f) }, NO_VALUE, 883 },
    { Anim_Update0, 99,  0, 99,       0, { FP_TIME(15.0f) }, 883,      903 },
    { Anim_Update2, 100, 0, 101,      0, { FP_TIME(10.0f) }, NO_VALUE, 904 },
    { Anim_Update0, 101, 0, 101,      0, { FP_TIME(15.0f) }, 904,      914 },
    { Anim_Update2, 102, 0, 103,      0, { FP_TIME(10.0f) }, NO_VALUE, 915 },
    { Anim_Update0, 103, 0, 103,      0, { FP_TIME(15.0f) }, 915,      925 },
    { Anim_Update2, 104, 0, 105,      0, { FP_TIME(2.0f) },  NO_VALUE, 926 },
    { Anim_Update0, 105, 0, 105,      0, { FP_TIME(4.0f) },  926,      972 },
    { Anim_Update2, 106, 0, 107,      0, { FP_TIME(10.0f) }, NO_VALUE, 973 },
    { Anim_Update0, 107, 0, 107,      0, { FP_TIME(15.0f) }, 973,      993 },
    { Anim_Update2, 108, 0, 109,      0, { FP_TIME(10.0f) }, NO_VALUE, 994 },
    { Anim_Update0, 109, 0, 109,      0, { FP_TIME(25.0f) }, 994,      1026 },
    {} // End of list.
};

// Not sure if the `time_4 field` (3rd) is actually time.
// These numbers produce very small and non-round values.
// I also seen some code read this field and add very small numbers like 4 or 32.
// This is why FP macros aren't used.
s_UnkStruct3_Mo g_MapHeaderTable_38[18] =
{
    { 0x4D4C, 0x0,   0x2A4, 0x2A5 },
    { 0x4F4E, 0xCA,  0x2A6, 0x2C9 },
    { 0x5150, 0xD2,  0x2CA, 0x2DC },
    { 0x5352, 0xD3,  0x2DD, 0x2EF },
    { 0x5554, 0xD4,  0x2F0, 0x302 },
    { 0x5756, 0xD5,  0x303, 0x315 },
    { 0x5958, 0xEB,  0x316, 0x327 },
    { 0x5B5A, 0xEC,  0x328, 0x339 },
    { 0x5D5C, 0xF5,  0x33A, 0x34B },
    { 0x5F5E, 0xF6,  0x34C, 0x35D },
    { 0x6160, 0x154, 0x35E, 0x372 },
    { 0x6362, 0x155, 0x373, 0x387 },
    { 0x6564, 0x156, 0x388, 0x392 },
    { 0x6766, 0x157, 0x393, 0x39D },
    { 0x6968, 0x15E, 0x39E, 0x3CC },
    { 0x6B6A, 0x164, 0x3CD, 0x3E1 },
    { 0x6D6C, 0x165, 0x3E2, 0x402 },
    {}, // End of list.
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
    InventoryItemId_Unequipped
};
