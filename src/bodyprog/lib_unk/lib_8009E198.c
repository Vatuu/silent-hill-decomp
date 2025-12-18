#include "common.h"
#include <libpad.h>
#include "lib_unk.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E198);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E230);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E268);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E2A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E2D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E310);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E3B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E438);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E4F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E520);

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* arg1) // 0x8009E550
{
    s32 padState;
    s32 padInfoCurID;
    s32 padInfoCurExID;
    u8  padPort;

    padPort        = arg0->field_0;
    padState       = PadGetState(padPort);
    padInfoCurID   = PadInfoMode(padPort, InfoModeCurID, 0);
    padInfoCurExID = PadInfoMode(padPort, InfoModeCurExID, 0);

    while (arg1)
    {
        if (arg1->func_C != NULL && arg1->func_C(arg0, padState, padInfoCurID, padInfoCurExID) == 1)
        {
            break;
        }
        
        arg1 = arg1->next_0;
    }

    return padState;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E61C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E718);

bool func_8009E7D8(s_SysWork_2510* arg0) // 0x8009E7D8
{
    s_SysWork_2510* var_a1;

    for (var_a1 = arg0; var_a1; var_a1 = var_a1->next_0)
    {
        if (var_a1 == &D_800B141C)
        {
            return false;
        }
    }

    var_a1            = arg0->next_0;
    arg0->next_0      = &D_800B141C;
    D_800B141C.next_0 = var_a1;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E82C);

bool func_8009E97C(s_SysWork_2510* arg0) // 0x8009E97C
{
    s_SysWork_2510* var_a1;

    for (var_a1 = arg0; var_a1; var_a1 = var_a1->next_0)
    {
        if (var_a1 == &D_800B142C)
        {
            return false;
        }
    }

    var_a1            = arg0->next_0;
    arg0->next_0      = &D_800B142C;
    D_800B142C.next_0 = var_a1;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E9D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EBB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EC1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EC64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ECCC);

s_SysWork_2514_18* func_8009ED74(s_SysWork_2514* arg0) // 0x8009ED74
{
    return &arg0->head_18;
}

s_SysWork_2514_18* func_8009ED7C(s_SysWork_2514_18* arg0) // 0x8009ED7C
{
    if (arg0 != NULL)
    {
        return arg0->next_0;
    }

    return NULL;
}

s32 func_8009ED90(s_SysWork_2514_18* arg0) // 0x8009ED90
{
    if (arg0 != NULL)
    {
        return arg0->field_4; // TODO: Is this `s_SysWork_2514_18*`?
    }

    return 0;
}
