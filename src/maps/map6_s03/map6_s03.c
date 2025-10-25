#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s03.h"

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB26C

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB660

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB738

#include "maps/shared/Particle_Update.h" // 0x800CBA54

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CEFF4_0_s00); // 0x800CC07C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC790

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CEFD0_1_s02); // 0x800CC82C

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CFFF8_0_s00); // 0x800CCB00

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D0690_1_s03); // 0x800CCBC0

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCD0C

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCD14

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCDCC

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CCE88

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD030

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD0E8

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800CD288

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD3D4

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD3F4

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CDC6C

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE058

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CE58C

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CE9B8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CE9F4

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CEA00

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CEB60

s32 func_800CED38()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CED40

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CEDF0

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CEE08

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CEE30

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CEE48

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CEE70

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CEF14

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CEF24

void func_800CEF30(void) {}

void func_800CEF38(void) {}

void func_800CEF40(void) {}

void func_800CEF48(void) {}

void func_800CEF50(void) {}

s32 func_800CEF58()
{
    return 0;
}

void func_800CEF60(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CEF68

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CEF78

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CEFB8

#include "maps/shared/Ai_Stalker_Update.h" // 0x800CEFCC

#include "maps/shared/Ai_Stalker_Init.h" // 0x800CF160 - Differs to other maps `Ai_Stalker_Init`.

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D3308_0_s00); // 0x800CF414

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800CFC50

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D0000

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D4924_0_s00); // 0x800D0008

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D492C_0_s00); // 0x800D0BD8

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D1344

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D54A8_0_s00); // 0x800D1754

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D1DF4

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D5C64_0_s00); // 0x800D1F10

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D2278

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D267C

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D27F8

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D2800

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D29B8

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D2AA8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D6970_0_s00); // 0x800D2C1C

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D70C4_0_s00); // 0x800D3370

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D3E94

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D40B0

#include "maps/shared/Ai_HangedScratcher_Update.h" // 0x800D4264

#include "maps/shared/Ai_HangedScratcher_Init.h" // 0x800D42E8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CFF74_5_s00); // 0x800D45B4

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D029C_5_s00); // 0x800D48DC

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D4A38);

void func_800D4A5C(s_SubCharacter* chara) // 0x800D4A5C
{
    q19_12 playerDist;

    playerDist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    // TODO: Invert to return early instead?
    if (playerDist < Q12(1.0f) &&
        !func_800700F8(chara, &g_SysWork.player_4C.chara_0) &&
        (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2 && func_8006FD90(chara, 1, Q12(2.0f), Q12(1.5f))) ||
         ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) &&
          (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
          func_8006FD90(chara, 1, Q12(1.5f), Q12(0.3f)))))
    {
        chara->model_0.state_2         = 3;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    }
}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D4B54);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D4C7C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5284);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5544);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D56F8);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D58B4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5FEC);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6110);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D624C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6324);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D64C4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6680);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D67C0);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6A20);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D26D8_5_s00); // 0x800D6D18

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D2844_5_s00); // 0x800D6E84

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D2C18_5_s00); // 0x800D7258

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D7854);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D3300_5_s00); // 0x800D7998

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7F14

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D7F24);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D7F98);

void func_800D81A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~H\tThere_is_a_ ~C5 Sewer_map ~N\n\t(connecting_to_amusement_park) ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tGotta'_go_find_Cybil! ~N\n\tNo_time_to_go_back. ~E "
};

void func_800D81AC(void) // 0x800D81AC
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 10:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink0;
            break;

        case 11:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M6S03_HandgunBullets;
            break;

        case 12:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D822C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D84EC);

void func_800D87F0(void) // 0x800D87F0
{
    Event_MapTake(15, EventFlag_M6S03_PickupMap, 15);
}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D8818);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D89A0);

void func_800D936C(void) {
}

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800CB258);

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800CB260);
