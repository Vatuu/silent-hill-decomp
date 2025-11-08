#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

// 6768 start

s_AnimInfo HARRY_M2S01_ANIM_INFOS[] = {
    { Anim_Update2, 76, 0, 77, { Q12(10.0f) }, -1, 676 },
    { Anim_Update0, 77, 0, 77, { Q12(10.0f) }, 676, 677 },
    { Anim_Update2, 78, 0, 79, { Q12(10.0f) }, -1, 678 },
    { Anim_Update0, 79, 0, 79, { Q12(16.0f) }, 678, 722 },
    { Anim_Update2, 80, 0, 81, { Q12(10.0f) }, -1, 723 },
    { Anim_Update0, 81, 0, 81, { Q12(5.0f) }, 723, 744 },
    { Anim_Update2, 82, 0, 83, { Q12(10.0f) }, -1, 745 },
    { Anim_Update1, 83, 0, 255, { Q12(2.0f) }, 745, 748 },
    { Anim_Update2, 84, 0, 85, { Q12(10.0f) }, -1, 485 },
    { Anim_Update0, 85, 0, 85, { Q12(20.0f) }, 485, 502 },
    {}
};

s_UnkStruct3_Mo g_MapHeaderTable_38[] = {
    { 19788, 0, 676, 677 },
    { 20302, 387, 678, 722 },
    { 20816, 389, 723, 744 },
    { 21330, 400, 745, 748 },
    { 21844, 500, 485, 502 },
    {}
};

u8 LOADABLE_INVENTORY_ITEMS[] = {
    32, 33, 34, 128, 129, 132, 133, 135,
    160, 161, 162, 163, 192, 193, 194, 224,
    225, 65, 66, 67, 68, 71, 72, 83,
    84, 100, 76, 101, 102, 110, 130, 226,
    88, 134, 0
};

u8 sharedData_800DD584_0_s00 = 0;

s32 sharedData_800DD598_0_s00 = 0;

u8 sharedData_800DD59C_0_s00 = 255;

// 6874 end