#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_AnimInfo HARRY_M2S03_ANIM_INFOS[] = {
    { Anim_Update2, 76, 0, 77, { Q12(10.0f) }, -1, 676 },
    { Anim_Update0, 77, 0, 77, { Q12(10.0f) }, 676, 677 },
    { Anim_Update2, 94, 0, 95, { Q12(10.0f) }, -1, 485 },
    { Anim_Update0, 95, 0, 95, { Q12(20.0f) }, 485, 502 },
    {}
};

s_UnkStruct3_Mo g_MapHeaderTable_38[3] = {
    { 19788, 0, 676, 677 },
    { 24414, 500, 485, 502 },
    {}
};

u8 LOADABLE_INVENTORY_ITEMS[] = { 0 };

u8 sharedData_800DD584_0_s00 = 0;

s32 sharedData_800DD598_0_s00 = 0;

u8 sharedData_800DD59C_0_s00 = 255;
