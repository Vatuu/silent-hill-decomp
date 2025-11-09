#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_AnimInfo HARRY_M1S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10.0f) }, NO_VALUE, 676},
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10.0f) }, 676, 677},
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10.0f) }, NO_VALUE, 485},
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20.0f) }, 485, 502},
    {}
};

s_UnkStruct3_Mo g_MapHeaderTable_38[2] = {
    { 19788, 0, 676, 677, },
    {},
};

u8 LOADABLE_INVENTORY_ITEMS[] = {
    InventoryItemId_Unequipped
};

u8 sharedData_800DD584_0_s00 = 0;

s32 sharedData_800DD598_0_s00 = 0;

u8 sharedData_800DD59C_0_s00 = 255;
