#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_AnimInfo HARRY_M0S00_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676  },
    { Anim_Update0, ANIM_STATUS(38, true),  false, ANIM_STATUS(38, true), { Q12(10) }, 676,      677  },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678  },
    { Anim_Update0, ANIM_STATUS(39, true),  false, ANIM_STATUS(39, true), { Q12(10) }, 678,      713  },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718  },
    { Anim_Update0, ANIM_STATUS(40, true),  false, ANIM_STATUS(40, true), { Q12(15) }, 718,      732  },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737  },
    { Anim_Update0, ANIM_STATUS(41, true),  false, ANIM_STATUS(41, true), { Q12(15) }, 737,      751  },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758  },
    { Anim_Update0, ANIM_STATUS(42, true),  false, ANIM_STATUS(42, true), { Q12(15) }, 758,      770  },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777  },
    { Anim_Update0, ANIM_STATUS(43, true),  false, ANIM_STATUS(43, true), { Q12(15) }, 777,      789  },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(8)  }, NO_VALUE, 790  },
    { Anim_Update1, ANIM_STATUS(44, true),  false, NO_VALUE,              { Q12(18) }, 790,      807  },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8)  }, NO_VALUE, 808  },
    { Anim_Update1, ANIM_STATUS(45, true),  false, NO_VALUE,              { Q12(18) }, 808,      825  },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8)  }, NO_VALUE, 826  },
    { Anim_Update0, ANIM_STATUS(46, true),  false, ANIM_STATUS(46, true), { Q12(18) }, 826,      843  },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8)  }, NO_VALUE, 844  },
    { Anim_Update0, ANIM_STATUS(47, true),  false, ANIM_STATUS(47, true), { Q12(18) }, 844,      861  },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 862  },
    { Anim_Update0, ANIM_STATUS(48, true),  false, ANIM_STATUS(48, true), { Q12(15) }, 862,      882  },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 883  },
    { Anim_Update0, ANIM_STATUS(49, true),  false, ANIM_STATUS(49, true), { Q12(15) }, 883,      903  },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 904  },
    { Anim_Update0, ANIM_STATUS(50, true),  false, ANIM_STATUS(50, true), { Q12(15) }, 904,      914  },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 915  },
    { Anim_Update0, ANIM_STATUS(51, true),  false, ANIM_STATUS(51, true), { Q12(15) }, 915,      925  },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(2)  }, NO_VALUE, 926  },
    { Anim_Update0, ANIM_STATUS(52, true),  false, ANIM_STATUS(52, true), { Q12(4)  }, 926,      972  },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 973  },
    { Anim_Update0, ANIM_STATUS(53, true),  false, ANIM_STATUS(53, true), { Q12(15) }, 973,      993  },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 994  },
    { Anim_Update0, ANIM_STATUS(54, true),  false, ANIM_STATUS(54, true), { Q12(25) }, 994,      1026 },
    {}
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
    {},
};

u8 LOADABLE_INVENTORY_ITEMS[8] =
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
