#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/s00.h"

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CB6B0);

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBBBC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBC94);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBFB0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC04C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC6E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD1F4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE02C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE544);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEB24);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEFF4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF7AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF974);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CFFF8);

void func_800D0124() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D012C);

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800D01BC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0274);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0394);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0600);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0700);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D08B8);

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800D0A60

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800D0B18

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0CB8);

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800D0E04

void func_800D0E24() {}

void func_800D0E2C() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E34);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D1C38);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D209C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D20D8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D20E4

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2244);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D2C7C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D2D2C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2D44

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D2D6C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D2D84

s32 func_800D2DAC() // 0x800D2DAC
{
    s_Model*    playerModel = &g_SysWork.player_4C.chara_0.model_0;
    s_AnimInfo* animInfo    = &g_MapOverlayHeader.animInfo_34[playerModel->anim_4.animIdx_0 - 76];

    if (animInfo->funcPtr_0 == Anim_Update0)
    {
        if (func_800449AC(playerModel, animInfo) > 0)
        {
            return playerModel->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx1_E;
        }
        else
        {
            return playerModel->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx0_C;
        }
    }

    if (animInfo->funcPtr_0 == Anim_Update2)
    {
        return -2;
    }
    else
    {
        return -1;
    }
}

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2E50

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D2E60

void func_800D2E6C() {}

void func_800D2E74() {}

void func_800D2E7C() {}

void func_800D2E84() {}

void func_800D2E8C() {}

s32 func_800D2E94()
{
	return 0;
}

void func_800D2E9C() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D2EA4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D2EB4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2EF4
