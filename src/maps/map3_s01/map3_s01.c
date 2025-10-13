#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s01.h"

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB214

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB7E0

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB8B8

#include "maps/shared/Particle_Update.h" // 0x800CBBC4

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800CEB24_0_s00); // 0x800CC194

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC650

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800CEFD0_1_s02); // 0x800CC7A0

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CCB68

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCC94

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCC9C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCD54

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CCDDC

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CCF94

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD114

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD1CC

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD364

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD384

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CDBFC

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800CDFE8);

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CE3E8

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CE838

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CE874

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CE880

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CE9E0

s32 func_800CEBB8()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CEBC0

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CEC70

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CEC88

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CECB0

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CECC8

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CECF0

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CED94

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CEDA4

void func_800CEDB0(void) {}

void func_800CEDB8(void) {}

void func_800CEDC0(void) {}

void func_800CEDC8(void) {}

void func_800CEDD0(void) {}

s32 func_800CEDD8()
{
    return 0;
}

void func_800CEDE0(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CEDE8

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CEDF8

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CEE38

#include "maps/shared/Ai_Creaper_Update.h" // 0x800CEE4C

#include "maps/shared/Ai_Creaper_Init.h" // 0x800CEEDC

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D7EE8_1_s02); // 0x800CF19C

#include "maps/shared/sharedFunc_800D8244_1_s02.h" // 0x800CF4F8

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D82F0_1_s02); // 0x800CF5A4

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D8684_1_s02); // 0x800CF938

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D8F30_1_s02); // 0x800D01E4

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D9528_1_s02); // 0x800D07DC

#include "maps/shared/sharedFunc_800D9774_1_s02.h" // 0x800D0A28

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800D0AF0

#include "maps/shared/sharedFunc_800D9960_1_s02.h" // 0x800D0C14

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", sharedFunc_800D99D0_1_s02); // 0x800D0C84

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D10C0

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D10D0);

void func_800D1178(s32 arg0) // 0x800D1178
{
    if (arg0 != 0)
    {
        sharedFunc_800D0994_3_s00();
    }
    else
    {
        sharedFunc_800D09D4_3_s00();
    }
}

#include "maps/shared/sharedFunc_800D0994_3_s00.h" // 0x800D11AC

#include "maps/shared/sharedFunc_800D09D4_3_s00.h" // 0x800D11EC

void func_800D138C(void) {}

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D1394);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D1428);

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "\tThe_elevator_doesn't ~N\n\tappear_to_be_working. ~E ",
    "\tA_glass_vial_lies_shattered. ",
    "\tIt's_not_just_broken. ~N\n\tIt_looks_smashed_on_purpose. ~E ",
    "\tThe_remaining_liquid_is_emptied ~N\n\tinto_the_ ~C2 Plastic_bottle ~C7 . ",
    "\tNow_what_have_we_here? ~E ",
    "\tA_glass_vial_lies_shattered. ~E ",
    "\tThere_is_a_ ~C2 Plastic_bottle ~C7 . ~N\n\tTake_it? ~S4 ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "~H\tThere_is_a ~N\n\t~C5 Hospital_basement_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Basement_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "~C3\tThe_in-house_generator ~N\n\t\tpowers_elevators,_ICUs ~N\n\t\tand_operating_rooms_only. ",
    "\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tThe_generator_is_on. ~E ",
    "\tUsed_the_ ~C2 Basement_key ~C7 _. ~E ",
    "\tI_should_search_the_hospital. ~E ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tThe_shelves_are_all_messed_up. ~N\n\tWho_did_this? ~E ",
    "\tBooks_are_scattered ~N\n\taround_the_desk. ~N\n\tNothing_else_special_here. ~E ",
    "\tThe_phone's_out. ~N\n\tCan't_get_a_dial_tone. ~E ",
    "\tThere's_a_white_board. ~N\n\tNothing_special_written_here. ~E ",
    "\tThere_is_a_newspaper. ",
    "\tThis_article's_been ~N\n\tclipped_out... ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

void func_800D14BC(void) // 0x800D14BC
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 101:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S01_HealthDrink;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D1500(void) // 0x800D1500
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D1524);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB088);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB094);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB0A0);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D15F0);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D23AC);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB124);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D25A8);

void func_800D2720(void) // 0x800D2720
{
    Event_ItemTake(InventoryItemId_PlasticBottle, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S01_PickupPlasticBottle, 21);
}

void func_800D274C(void) // 0x800D274C
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 22);
}

void func_800D2774(void) // 0x800D2774
{
    Event_MapTake(16, EventFlag_M3S01_PickupMap, 23);
}

void func_800D279C(void) // 0x800D279C
{
    Event_ItemTake(InventoryItemId_BasementKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S01_PickupBasementKey, 24);
}

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB148);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D27C8);

void func_800D29A4(void) // 0x800D29A4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 27, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(0x60); // Hex?
}

void func_800D2A88(void) // 0x800D2A88
{
    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_Unk1308, &D_800CB170, 128, 0);
    }

    func_80087360(Sfx_Unk1916, Q12(0.0f), Q12(0.0f), 36);
    Savegame_EventFlagSet(EventFlag_203);
}

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB170);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D2AF4);

INCLUDE_ASM("asm/maps/map3_s01/nonmatchings/map3_s01", func_800D2E54);

INCLUDE_RODATA("asm/maps/map3_s01/nonmatchings/map3_s01", D_800CB20C);
