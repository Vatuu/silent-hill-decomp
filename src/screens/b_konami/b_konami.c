#include "common.h"
#include "screens/b_konami/b_konami.h"

#include <libetc.h>

extern s32 D_800CA4F4;
extern s32 D_800CA4FC;
extern s32 D_800CA500;
extern s32 D_800CA504;
extern s32 D_800CA508;
extern s32 D_800CA50C;
extern s32 D_800CA510;

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C95AC);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9874);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C99A4);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9E6C);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9FB8);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800CA120);

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
    s32* temp_v0;

    var_a3 = 0;
    D_800CA4FC = 1;
    D_800CA500 = arg0;
    D_800CA504 = arg1;
    D_800CA50C = arg0 + arg2;
    D_800CA500 = arg0 + 4;
    do
    {
        temp_v0 = D_800CA4F4 + var_a3;
        var_a3 += 4;
        *temp_v0 = 0;
    }
    while (var_a3 < 0x1000);
    
    D_800CA508 = 0xFEE;
    D_800CA510 = 0;
}

s32 func_800CA2B8(void)
{
    return D_800CA4FC;
}

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800CA2C8);
