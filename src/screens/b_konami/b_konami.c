#include "common.h"
#include "gpu.h"
#include "screens/b_konami/b_konami.h"

#include <libetc.h>

// ===== Temporary declarations =====

void func_800C9E6C(u32* arg0, s32 otz, s16 vramX, s16 vramY, s16 w, s16 h, s16 x, s16 y);

//===================================

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C95AC);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9874);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C99A4);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9E6C);

// TODO: Wait on fgsfd's investigations for cleaner match of graphics setup.
void func_800C9FB8(void)
{
    s32* temp_a1;

    func_800C9E6C(&D_800A8FFC, 0xF, 0, 0, 256, 256, -192, -192);
    func_800C9E6C(&D_800A8FFC, 0xF, 256, 0, 128, 256, 64, -192);
    func_800C9E6C(&D_800A8FFC, 0xF, 0, 256, 256, 128, -192, 64);
    func_800C9E6C(&D_800A8FFC, 0xF, 256, 256, 128, 128, 64, 64);

    temp_a1 = (D_800B9FB8 << 4) + &D_800B5C7C;

    // addPrim(temp_a1, D_800C7018);
    ((TILE*)D_800C7018)->tag = (u32)((*temp_a1 & 0xFFFFFF) | 0x03000000);
    setaddr(temp_a1, D_800C7018);
    
    setCodeWord((TILE*)D_800C7018, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)D_800C7018, -320, -240);
    setWH((TILE*)D_800C7018, 640, 480);

    D_800C7018 += sizeof(TILE);
}

// TODO: Wait on fgsfd's investigations for cleaner match of graphics setup.
void func_800CA120(void)
{
    u32* temp_a1;

    func_800C9E6C(&D_800A9004, 0xF, 0, 0, 256, 160, -208, -80);
    func_800C9E6C(&D_800A9004, 0xF, 256, 0, 160, 160, 48, -80);
    
    temp_a1 = (D_800B9FB8 << 4) + &D_800B5C7C;

    // addPrim(temp_a1, D_800C7018);
    ((TILE*)D_800C7018)->tag = (u32)((*temp_a1 & 0xFFFFFF) | 0x03000000);
    setaddr(temp_a1, D_800C7018);
    
    setCodeWord((TILE*)D_800C7018, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)D_800C7018, -320, -240);
    setWH((TILE*)D_800C7018, 640, 480);

    D_800C7018 += sizeof(TILE);
}

void func_800CA234(void)
{
    D_800CA4FC = 0;
}

s32 func_800CA240(s32* arg0)
{
    return *arg0;
}

void func_800CA24C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 var_a3;
    s32* somePtr;

    var_a3 = 0;
    D_800CA4FC = 1;
    D_800CA500 = arg0;
    D_800CA504 = arg1;
    D_800CA50C = arg0 + arg2;
    D_800CA500 = arg0 + 4;
    do
    {
        somePtr = D_800CA4F4 + var_a3;
        var_a3 += 4;
        *somePtr = 0;
    }
    while (var_a3 < 4096);
    
    D_800CA508 = 4078;
    D_800CA510 = 0;
}

s32 func_800CA2B8(void)
{
    return D_800CA4FC;
}

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800CA2C8);
