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

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* arg1)
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E7D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E82C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E97C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E9D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EBB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EC1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EC64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ECCC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ED74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ED7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ED90);
