#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CAB58);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CACC0

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CAE40

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CAEF8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB05C

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CB07C);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CB8F4);

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBCE0

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CBFD4);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC400

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC43C

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CC448

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CC5A8

s32 func_800CC780()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC788

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC838

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC850

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC878

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC890

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC8B8

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC95C

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC96C

void func_800CC978(void) {}

void func_800CC980(void) {}

void func_800CC988(void) {}

void func_800CC990(void) {}

void func_800CC998(void) {}

s32 func_800CC9A0()
{
    return 0;
}

void func_800CC9A8(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC9B0

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC9C0

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CCA00

#include "maps/shared/Ai_Creaper_Update.h" // 0x800CCA14

#include "maps/shared/Ai_Creaper_Init.h" // 0x800CCAA4

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D7EE8_1_s02); // 0x800CCD64

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D8244_1_s02); // 0x800CD0C0

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CD16C);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CD500);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CDDAC);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CE3A4);

void func_800CE5F0(s_SubCharacter* chara, s32 moveSpeed) // 0x800CE5F0
{
    chara->flags_3E &= ~(1 << 1);

    if (chara->health_B0 == FP_HEALTH(0.0f) && func_8005C7D0(chara, moveSpeed) != g_SysWork.enemyTargetIdx_2353)
    {
        chara->health_B0   = NO_VALUE;
        chara->field_E0_8 &= (1 << 5) | (1 << 6) | (1 << 7);
    }

    if (chara->moveSpeed_38 == 0 && !(chara->properties_E4.player.afkTimer_E8 & 0xC))
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 3;

        func_80037DC4(chara);

        if (chara->model_0.anim_4.animIdx_0 == 29)
        {
            func_800622B8(3, chara, 10, 5);
        }
        else
        {
            func_800622B8(3, chara, 11, 5);
        }
    }
}

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800CE6B8

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D9960_1_s02); // 0x800CE7DC

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800D99D0_1_s02); // 0x800CE84C

#include "maps/shared/Ai_Alessa_Update.h" // 0x800CEC88

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800CECFC_3_s02);

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800CED44

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", sharedFunc_800CEEDC_3_s02);

#include "maps/shared/Ai_Alessa_Init.h" // 0x800CF3E0

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CF404

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CF418

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CF45C

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CF474

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CF480

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CF494

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CF4A8

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CF4BC

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CF548);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CFBAC

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CFBC0

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CFBD4

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CFCD0

#include "maps/shared/sharedFunc_800D921C_0_s00.h" // 0x800CFD64

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CFD70

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CFDD0

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CFDE0);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CFE78);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CFEAC);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800CFEEC);

void func_800D017C(void) {}

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D0184);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D0218);

void func_800D02AC(void) {}

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D02B4);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D03FC);

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800D0570

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D0608);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D0F8C);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D0F9C);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02", func_800D1354);
