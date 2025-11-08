#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_AnimInfo HARRY_M2S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10.0f) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10.0f) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10.0f) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15.0f) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10.0f) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10.0f) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10.0f) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15.0f) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10.0f) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15.0f) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10.0f) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10.0f) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10.0f) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10.0f) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10.0f) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(20.0f) }, 485, 502 },
    {}
};

s_UnkStruct3_Mo g_MapHeaderTable_38[] = {
    { 19788, 0, 676, 677 },
    { 20302, 200, 678, 688 },
    { 20816, 202, 689, 724 },
    { 21330, 210, 725, 743 },
    { 21844, 211, 744, 762 },
    { 22358, 212, 763, 781 },
    { 22872, 213, 782, 800 },
    { 23386, 500, 485, 502 },
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
