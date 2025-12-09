#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_FsImageDesc D_800A8D98 = { { 16, 0 }, 0, 0, 8, 0 };
s_FsImageDesc D_800A8DA0 = { { 44, 0 }, 0, 0, 0, 0 };

// Could also be some `s_FsImageDesc`, but the big negative numbers suggest not.
// Might be some other primitive data (`POLY`, `RGBC0`, etc.).
u32 D_800A8DA8[] = {
    0x00010010,
    0x84438000,
    0x88658C62,
    0x8CA798A4,
    0xA10794C8,
    0xA92794EA,
    0xA16C992C,
    0xA9F3A58F,
    0xAE37AE16,
    0x0000008C,
    0x00000000,
    0x00100004,
    0x65553300,
    0x00001136,
    0x01113310,
    0x00033111,
    0x58ACC610,
    0x00132111,
    0xFFEEFC00,
    0x0022111A,
    0xFEDEED00,
    0x0022103D,
    0xEEEFFD10,
    0x0022116D,
    0x633AA510,
    0x0022158A,
    0x001CA500,
    0x00745CA5,
    0xCBDEEC00,
    0x00BB7CDE,
    0xDEDDEC00,
    0x004B79BC,
    0xACC8A800,
    0x00049978,
    0x8BCA8500,
    0x00049976,
    0x65558100,
    0x00097777,
    0x58AAA000,
    0x000B9444,
    0x246A5000,
    0x006CB422,
    0x01300000,
    0x06DCCA31,
};
