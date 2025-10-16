#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CABA0);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CAC54);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CB31C);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CB484

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CB604

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CB6BC

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB820

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB840

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CC0B8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CC4A4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CCCF4

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CD120

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CD15C

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CD168

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CD2C8

s32 func_800CD4A0()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CD4A8

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CD558

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CD570

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CD598

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CD5B0

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CD5D8

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CD67C

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CD68C

void func_800CD698(void) {}

void func_800CD6A0(void) {}

void func_800CD6A8(void) {}

void func_800CD6B0(void) {}

void func_800CD6B8(void) {}

s32 func_800CD6C0()
{
    return 0;
}

void func_800CD6C8(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CD6D0

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CD6E0

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CD720

#include "maps/shared/Ai_Alessa_Update.h" // 0x800CD734

#include "maps/shared/sharedFunc_800CECFC_3_s02.h" // 0x800CD7A8

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800CD7F0

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", sharedFunc_800CEEDC_3_s02); // 0x800CD988

#include "maps/shared/Ai_Alessa_Init.h" // 0x800CDE8C

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CDEB0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CDEC4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CDF08

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CDF20

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CDF2C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CDF40

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CDF54

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CDF68

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CDFF4

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CE658

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CE66C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CE680

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CE77C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CE810

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CE81C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE87C

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CE88C);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CEA88);

void func_800CED6C(void) {}

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CED74);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CEF88);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CF01C);

void func_800CF0B0(void) {}

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\t...! ~E ",
    "~J0(1.0)\tWait! ~E ",
    "~J0(1.7)\tDamn! ~N\n\t\t\tI_was_too_late? ~E ",
    "~J0(1.5)\tSorry... ",
    "~J0(0.6)\tAh... ",
    "~J0(1.5)\t_ ",
    "~J0(3.6)\tLet_me_ask_you,_have_you_seen ~N\n\t\t\ta_little_girl_around_here? ~E ",
    "~J0(2.8)\tShort,_black_hair... ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CF0B8);

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800CFB9C

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800CAA98);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800CAAA0);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800CFC34);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D0500);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1040);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1330);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1658);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1718);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1AE4);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1D40);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D1EB8);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D2170);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D2364);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02", func_800D32D0);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800CAB90);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02", D_800CAB98);
