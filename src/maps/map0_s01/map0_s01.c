#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
#include "maps/characters/air_screamer.h"

const VECTOR D_800CA5C8 = {};

#include "maps/shared/sharedFunc_800CCB8C_0_s01.h" // 0x800CCB8C

#include "maps/shared/sharedFunc_800CD1F8_0_s01.h" // 0x800CD1F8

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE000

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE59C

#include "maps/shared/Particle_Update.h" // 0x800CE8A8

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEE2C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CF3F4

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF8E8

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF8F0

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF9A8

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFA30

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CA9F4);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
// TODO: Most of the code below also belongs to `air_screamer.c`, move there once `INCLUDE_ASM` gaps are matched.
#include "../src/maps/characters/air_screamer.c" // 0x800D2170

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800D4A80

#include "maps/shared/sharedFunc_800D4AEC_0_s01.h" // 0x800D4AEC

#include "maps/shared/sharedFunc_800D4E84_0_s01.h" // 0x800D4E84

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800D5274

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800D529C

#include "maps/shared/sharedFunc_800D53AC_0_s01.h" // 0x800D53AC

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800D5638

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800D569C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800D57C8

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800D598C

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800D5B10

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800D5C90

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800D5D80

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800D5E14

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800D5E78

#include "maps/shared/sharedFunc_800D5F00_0_s01.h" // 0x800D5F00

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800D62D8

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800D633C

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800D63A4

#include "maps/shared/sharedFunc_800D6600_0_s01.h" // 0x800D6600

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800D6A60

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800D6C7C

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h" // 0x800D6EC4

#include "maps/shared/sharedFunc_800D7120_0_s01.h" // 0x800D7120

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800D71F0

#include "maps/shared/sharedFunc_800D72E8_0_s01.h" // 0x800D72E8

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800D7440

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800D7560

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800D76A0

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800D7714

#include "maps/shared/sharedFunc_800D77D0_0_s01.h" // 0x800D77D0

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800D7AB0

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800D7B14

q19_12 Model_AnimDurationGet(s_Model* model) // 0x800D7E88
{
    return Anim_DurationGet(model, func_80044918(&model->anim_4));
}

#include "maps/shared/sharedFunc_800D7EBC_0_s01.h" // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

#include "maps/shared/sharedFunc_800D81D0_0_s01.h" // 0x800D81D0

#include "maps/shared/sharedFunc_800D8244_0_s01.h" // 0x800D8244

#include "maps/shared/sharedFunc_800D82B8_0_s01.h" // 0x800D82B8

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800D8714

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800D87FC

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800D8804
