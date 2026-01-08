#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map5/map5_s01.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/romper.h"

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800C9578);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CCA90

#include "maps/shared/sharedFunc_800CE688_1_s03.h" // 0x800CCB44

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CD20C);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CD51C);

void func_800CD818(void) // 0x800CD818
{
    Fs_QueueStartReadTim(FILE_ITEM_FOOK_TIM, FS_BUFFER_1, &D_800A907C);
    Fs_QueueStartRead(FILE_ITEM_FOOK_TMD, FS_BUFFER_21);
    Fs_QueueWaitForEmpty();
}

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CD860);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CDA8C);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CDB14);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CDB98);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800CE180);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE2B4

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE76C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE844

#include "maps/shared/Particle_Update.h" // 0x800CEB50

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CF250

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF720

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CF870

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CFC38

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CFD64

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CFD6C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CFE24

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFEAC

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA7F0);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA7F4);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA800);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA818);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA830);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA848);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
// TODO: Most of the code below also belongs to `air_screamer.c`, move there once `INCLUDE_ASM` gaps are matched.
#include "../src/maps/characters/air_screamer.c" // 0x800D225C

#include "maps/shared/Ai_AirScreamerControl_2.h" // 0x800D3F40

#include "maps/shared/Ai_AirScreamerControl_3.h" // 0x800D4160

#include "maps/shared/Ai_AirScreamerControl_4.h" // 0x800D42C0

#include "maps/shared/Ai_AirScreamerControl_5.h" // 0x800D4674

#include "maps/shared/Ai_AirScreamerControl_6.h" // 0x800D49E4

#include "maps/shared/Ai_AirScreamerControl_7.h" // 0x800D4DB8

#include "maps/shared/Ai_AirScreamerControl_8.h" // 0x800D5194

#include "maps/shared/Ai_AirScreamerControl_9.h" // 0x800D5584

#include "maps/shared/Ai_AirScreamerControl_10.h" // 0x800D5870

#include "maps/shared/Ai_AirScreamerControl_11.h" // 0x800D5C90

#include "maps/shared/Ai_AirScreamerControl_12.h" // 0x800D5EA4

#include "maps/shared/Ai_AirScreamerControl_13.h" // 0x800D60C8

#include "maps/shared/Ai_AirScreamerControl_14.h" // 0x800D6358

#include "maps/shared/Ai_AirScreamerControl_15.h" // 0x800D671C

#include "maps/shared/Ai_AirScreamerControl_16.h" // 0x800D6820

#include "maps/shared/Ai_AirScreamerControl_17.h" // 0x800D6CBC

#include "maps/shared/Ai_AirScreamerControl_18.h" // 0x800D6D98

#include "maps/shared/Ai_AirScreamerControl_19.h" // 0x800D7144

#include "maps/shared/Ai_AirScreamerControl_20.h" // 0x800D74C0

#include "maps/shared/Ai_AirScreamerControl_21.h" // 0x800D7888

#include "maps/shared/Ai_AirScreamerControl_22.h" // 0x800D7C68

#include "maps/shared/Ai_AirScreamerControl_23.h" // 0x800D8028

#include "maps/shared/Ai_AirScreamerControl_24.h" // 0x800D8408

#include "maps/shared/Ai_AirScreamerControl_25.h" // 0x800D8714

#include "maps/shared/Ai_AirScreamerControl_26.h" // 0x800D8934

#include "maps/shared/Ai_AirScreamerControl_27.h" // 0x800D8BA4

#include "maps/shared/Ai_AirScreamerControl_28.h" // 0x800D8F50

#include "maps/shared/Ai_AirScreamerControl_29.h" // 0x800D9060

#include "maps/shared/Ai_AirScreamerControl_30.h" // 0x800D94BC

#include "maps/shared/Ai_AirScreamerControl_31.h" // 0x800D95D0

#include "maps/shared/Ai_AirScreamerControl_32.h" // 0x800D9704

#include "maps/shared/Ai_AirScreamerControl_33.h" // 0x800D9808

#include "maps/shared/Ai_AirScreamerControl_34.h" // 0x800D9BF8

#include "maps/shared/Ai_AirScreamerControl_35.h" // 0x800D9F7C

#include "maps/shared/Ai_AirScreamerControl_36.h" // 0x800DA3F0

#include "maps/shared/Ai_AirScreamerControl_37.h" // 0x800DA8B4

#include "maps/shared/Ai_AirScreamerControl_38.h" // 0x800DAC1C

#include "maps/shared/Ai_AirScreamerControl_39.h" // 0x800DAFC4

#include "maps/shared/Ai_AirScreamerControl_40.h" // 0x800DB354

#include "maps/shared/Ai_AirScreamerControl_41.h" // 0x800DB53C

#include "maps/shared/Ai_AirScreamerControl_42.h" // 0x800DB868

#include "maps/shared/Ai_AirScreamerControl_43.h" // 0x800DBBC8

#include "maps/shared/Ai_AirScreamerControl_44.h" // 0x800DBCD4

#include "maps/shared/Ai_AirScreamerControl_45.h" // 0x800DC108

void func_800DC208(void) {}

void func_800DC210(void) {}

void func_800DC218(void) {}

void func_800DC220(void) {}

void func_800DC228(void) {}

void func_800DC230(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DC238

#include "maps/shared/sharedFunc_800DBF88_2_s00.h" // 0x800DC2A4

#include "maps/shared/sharedFunc_800DC0A8_2_s00.h" // 0x800DC3C4

#include "maps/shared/sharedFunc_800DC0E4_2_s00.h" // 0x800DC400

#include "maps/shared/sharedFunc_800DC200_2_s00.h" // 0x800DC51C

#include "maps/shared/sharedFunc_800DC30C_2_s00.h" // 0x800DC628

#include "maps/shared/sharedFunc_800DC3BC_2_s00.h" // 0x800DC6D8

#include "maps/shared/sharedFunc_800DC438_2_s00.h" // 0x800DC754

#include "maps/shared/sharedFunc_800DC50C_2_s00.h" // 0x800DC828

#include "maps/shared/sharedFunc_800DC598_2_s00.h" // 0x800DC8B4

#include "maps/shared/sharedFunc_800DC67C_2_s00.h" // 0x800DC998

#include "maps/shared/sharedFunc_800DC6E4_2_s00.h" // 0x800DCA00

#include "maps/shared/sharedFunc_800DC894_2_s00.h" // 0x800DCBB0

#include "maps/shared/sharedFunc_800D4AEC_0_s01.h" // 0x800DCCA8

#include "maps/shared/sharedFunc_800D4E84_0_s01.h" // 0x800DD040

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DD430

#include "maps/shared/sharedFunc_800DD13C_2_s00.h" // 0x800DD458

#include "maps/shared/sharedFunc_800DD2C4_2_s00.h" // 0x800DD5E0

#include "maps/shared/sharedFunc_800DD4A4_2_s00.h" // 0x800DD7C0

#include "maps/shared/sharedFunc_800DD4EC_2_s00.h" // 0x800DD808

#include "maps/shared/sharedFunc_800DD534_2_s00.h" // 0x800DD850

#include "maps/shared/sharedFunc_800DD588_2_s00.h" // 0x800DD8A4

#include "maps/shared/sharedFunc_800DD834_2_s00.h" // 0x800DDB50

#include "maps/shared/sharedFunc_800DDA80_2_s00.h" // 0x800DDD9C

#include "maps/shared/sharedFunc_800DDE14_2_s00.h" // 0x800DE130

#include "maps/shared/sharedFunc_800DDF74_2_s00.h" // 0x800DE290

#include "maps/shared/sharedFunc_800DE034_2_s00.h" // 0x800DE350

#include "maps/shared/sharedFunc_800DE11C_2_s00.h" // 0x800DE438

#include "maps/shared/sharedFunc_800DE1F8_2_s00.h" // 0x800DE514

#include "maps/shared/sharedFunc_800DE250_2_s00.h" // 0x800DE56C

#include "maps/shared/sharedFunc_800DE578_2_s00.h" // 0x800DE894

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DE8B4

#include "maps/shared/sharedFunc_800DE6A8_2_s00.h" // 0x800DE9C4

#include "maps/shared/sharedFunc_800DE7E0_2_s00.h" // 0x800DEAFC

#include "maps/shared/sharedFunc_800D53AC_0_s01.h" // 0x800DEC5C

#include "maps/shared/sharedFunc_800DEBCC_2_s00.h" // 0x800DEEE8

#include "maps/shared/sharedFunc_800DEC64_2_s00.h" // 0x800DEF80

#include "maps/shared/sharedFunc_800DEC84_2_s00.h" // 0x800DEFA0

#include "maps/shared/sharedFunc_800DECA4_2_s00.h" // 0x800DEFC0

#include "maps/shared/sharedFunc_800DECC4_2_s00.h" // 0x800DEFE0

#include "maps/shared/sharedFunc_800DEE24_2_s00.h" // 0x800DF140

#include "maps/shared/sharedFunc_800DF22C_2_s00.h" // 0x800DF548

#include "maps/shared/sharedFunc_800DF24C_2_s00.h" // 0x800DF568

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DF588

#include "maps/shared/sharedFunc_800DF2D0_2_s00.h" // 0x800DF5EC

#include "maps/shared/sharedFunc_800DF358_2_s00.h" // 0x800DF674

#include "maps/shared/sharedFunc_800DF448_2_s00.h" // 0x800DF764

#include "maps/shared/sharedFunc_800DF60C_2_s00.h" // 0x800DF928

#include "maps/shared/sharedFunc_800DF710_2_s00.h" // 0x800DFA2C

#include "maps/shared/sharedFunc_800DF80C_2_s00.h" // 0x800DFB28

#include "maps/shared/sharedFunc_800DF8A0_2_s00.h" // 0x800DFBBC

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DFC6C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DFD98

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800DFF5C

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800E00E0

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800E0260

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800E0350

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800E03E4

#include "maps/shared/sharedFunc_800E012C_2_s00.h" // 0x800E0448

#include "maps/shared/sharedFunc_800E021C_2_s00.h" // 0x800E0538

#include "maps/shared/sharedFunc_800E041C_2_s00.h" // 0x800E0738

#include "maps/shared/sharedFunc_800E04B0_2_s00.h" // 0x800E07CC

#include "maps/shared/sharedFunc_800E0514_2_s00.h" // 0x800E0830

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800E092C

#include "maps/shared/sharedFunc_800D5F00_0_s01.h" // 0x800E09B4

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800E0D8C

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800E0DF0

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800E0E58

#include "maps/shared/sharedFunc_800D6600_0_s01.h" // 0x800E10B4

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800E1514

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800E1730

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h"

#include "maps/shared/sharedFunc_800D7120_0_s01.h" // 0x800E1BD4

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E1CA4

#include "maps/shared/sharedFunc_800D72E8_0_s01.h"

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E1EF4

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E2014

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E2154

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800E21C8

#include "maps/shared/sharedFunc_800D77D0_0_s01.h" // 0x800E2284

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E2564

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800E25C8

#include "maps/shared/sharedFunc_800D7EBC_0_s01.h" // 0x800E293C

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E2C30

#include "maps/shared/sharedFunc_800D81D0_0_s01.h" // 0x800E2C50

#include "maps/shared/sharedFunc_800D8244_0_s01.h" // 0x800E2CC4

#include "maps/shared/sharedFunc_800D82B8_0_s01.h" // 0x800E2D38

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E3194

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E327C

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800E3284

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E3294

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E3390

#include "maps/shared/sharedFunc_800E33DC_2_s00.h" // 0x800E3590

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", sharedFunc_800E384C_2_s00); // 0x800E3A00

#include "maps/shared/sharedFunc_800E39D8_2_s00.h" // 0x800E3B8C

#include "maps/shared/sharedFunc_800E3E94_2_s00.h" // 0x800E4048

#include "maps/shared/sharedFunc_800E4830_2_s00.h" // 0x800E49E4

#include "maps/shared/sharedFunc_800E4E84_2_s00.h" // 0x800E5038

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E5700

#include "maps/shared/sharedFunc_800E55B0_2_s00.h" // 0x800E5764

#include "maps/shared/sharedFunc_800E5930_2_s00.h" // 0x800E5AE4

#include "maps/shared/sharedFunc_800E5AA4_2_s00.h" // 0x800E5C58

#include "maps/shared/sharedFunc_800E5EC4_2_s00.h" // 0x800E6078

#include "maps/shared/sharedFunc_800E6338_2_s00.h" // 0x800E64EC

#include "maps/shared/sharedFunc_800E71E8_2_s00.h" // 0x800E739C

#include "maps/shared/Ai_Romper_Update.h" // 0x800E786C

#include "maps/shared/Ai_Romper_Init.h" // 0x800E790C

#include "maps/shared/sharedFunc_800E5FC8_2_s02.h" // 0x800E7AFC

#include "maps/shared/sharedFunc_800E60FC_2_s02.h" // 0x800E7C30

#include "maps/shared/sharedFunc_800E6420_2_s02.h" // 0x800E7F54

#include "maps/shared/Ai_Romper_Control.h" // 0x800E821C

#include "maps/shared/Ai_Romper_Control_1.h" // 0x800E828C

#include "maps/shared/Ai_Romper_Control_2.h" // 0x800E83AC

#include "maps/shared/sharedFunc_800E6C40_2_s02.h" // 0x800E8774

#include "maps/shared/sharedFunc_800E7540_2_s02.h" // 0x800E9074

#include "maps/shared/sharedFunc_800E79D8_2_s02.h" // 0x800E950C

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800E9B70);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800E9C8C);

#include "maps/shared/Ai_Romper_Control_8.h" // 0x800E9F08

#include "maps/shared/Ai_Romper_Control_9.h" // 0x800E9FAC

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800E9FB4);

#include "maps/shared/Ai_Romper_Control_11.h" // 0x800EA1F4

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", sharedFunc_800E8730_2_s02); // 0x800EA264

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", sharedFunc_800E8A40_2_s02); // 0x800EA574

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", sharedFunc_800E8DFC_2_s02); // 0x800EA930

#include "maps/shared/sharedFunc_800E939C_2_s02.h" // 0x800EAED0

#include "maps/shared/sharedFunc_800E94B4_2_s02.h" // 0x800EAFE8

#include "maps/shared/sharedFunc_800E9714_2_s02.h" // 0x800EB248

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800EB460

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800EB470);

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800EB6B0);

void func_800EB874(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800EB87C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800EB910

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~H\tThere_is_a_ ~C5 Resort_area_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual. ~E ",
    "\tUsed_the_ ~C2 Kaufmann_key ~C7 . ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void MapEvent_CommonItemTake(void) // 0x800EB9A4
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 40:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells0;
            break;

        case 41:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S01_HandgunBullets;
            break;

        case 42:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S01_FirstAidKit;
            break;

        case 43:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S01_HealthDrink;
            break;

        case 44:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800EBA40(void) // 0x800EBA40
{
    s32 i;
    s32 j;

    Game_RadioSoundStop();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            D_800F0358 = 0;
            D_800F0354 = 0;

            for (i = 0; i < ARRAY_SIZE(D_800F0350); i++)
            {
                D_800F0350[i] = 10;
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_800862F8(7, FILE_TIM_DORPANEL_TIM, false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            break;

        case 4:
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);

            D_800F0354 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            D_800F0354  = CLAMP_RANGE(D_800F0354, Q12(-160.0f), Q12(160.0f));

            D_800F0358 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            D_800F0358  = CLAMP_RANGE(D_800F0358, Q12(-120.0f), Q12(120.0f));

            Game_TimerUpdate();
            func_800881B8((s16)(FP_FROM(D_800F0354, Q12_SHIFT) + 8), FP_FROM(D_800F0358, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 7);
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                for (i = 0; i < ARRAY_SIZE(D_800F0158); i++)
                {
                    if ((D_800F0158[i].field_0 - 160) > FP_FROM(D_800F0354, Q12_SHIFT) ||
                        (D_800F0158[i].field_0 - 114) < FP_FROM(D_800F0354, Q12_SHIFT))
                    {
                        continue;
                    }

                    if ((D_800F0158[i].field_1 - 120) > FP_FROM(D_800F0358, Q12_SHIFT) ||
                        (D_800F0158[i].field_1 - 74) < FP_FROM(D_800F0358, Q12_SHIFT))
                    {
                        continue;
                    }

                    Sd_PlaySfx(Sfx_Unk1586, 0, Q8_CLAMPED(0.5f));

                    if (i < 11)
                    {
                        for (j = 0; j < (ARRAY_SIZE(D_800F0350) - 1); j++)
                        {
                            D_800F0350[j] = D_800F0350[j + 1];
                        }

                        D_800F0350[3] = i;
                        break;
                    }

                    for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                    {
                        if (D_800F0170[j] != D_800F0350[j])
                        {
                            break;
                        }
                    }

                    if (j == 4)
                    {
                        Savegame_EventFlagSet(EventFlag_387);
                        SysWork_StateStepIncrement(0);
                    }
                    else
                    {
                        for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                        {
                            D_800F0350[j] = 10;
                        }
                    }
                    break;
                }
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            break;

        case 6:
            Sd_PlaySfx(Sfx_Unk1587, 0, Q8_CLAMPED(0.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80037154();
            break;
    }
}

void MapEvent_MapTake(void) // 0x800EBF48
{
    Event_MapTake(4, EventFlag_M5S01_PickupMap, 15);
}

INCLUDE_ASM("maps/map5_s01/nonmatchings/map5_s01", func_800EBF70);

void func_800EC2D8(void) // 0x800EC2D8
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KaufmannKey, 1);
    Map_MessageWithSfx(17, Sfx_UseKey, &sfxPos); // "Used the Kaufmann key."
    Savegame_EventFlagSet(EventFlag_M5S01_KaufmannKeyUsed);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800EC394

void func_800EC42C(void) // 0x800EC42C
{
    s32    mulZ;
    s32    mulX;
    s32    pitch;
    s32    tmp0;
    s32    tmp1;
    q19_12 sin0;
    q19_12 sin1;

    tmp0 = D_800F0360;
    sin0 = Math_Sin(tmp0 >> 2);
    sin1 = Math_Sin(tmp0 >> 3);
    tmp1 = ((sin0 * 2) + sin1) + Math_Sin(Math_Cos(tmp0 >> 4));
    pitch = tmp1 >> 8;
    D_800F0360 += g_DeltaTime0;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800F035E -= Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.5f));
        if (D_800F035E < 0)
        {
            D_800F035E = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800F035E += Q12_MULT_PRECISE(g_DeltaTime0, Q12(0.25f));
        if (D_800F035E > Q12(0.9961f))
        {
            D_800F035E = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800F0178);
            Fs_QueueStartRead(FILE_ANIM_UFO3_DMS, FS_BUFFER_13);

            D_800F3E0C = NO_VALUE;

            ScreenFade_ResetTimestep();
            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800F035E = 0;
            D_800F0360 = 0;
            D_800F035D = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty() != false)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800F3E0C = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            DmsHeader_FixOffsets((s_DmsHeader* )FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            D_800F035C = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Map_MessageWithAudio(18, &D_800F035C, &D_800F0174);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F3E0C, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
    block_18:
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 19, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(-196.53f, -14.25f, -9.73f));
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(1.0f), Q12(0.1f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            g_SysWork.field_28 += g_DeltaTime0;

            switch (g_SysWork.field_28 / Q12(0.1f))
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    break;

                case 4:
                case 5:
                case 6:
                case 11:
                case 12:
                case 13:
                case 18:
                case 19:
                case 20:
                    mulX = Q12(-0.9f);
                    mulZ = Q12(1.0f);
                    break;

                case 7:
                case 8:
                case 9:
                case 10:
                case 14:
                case 15:
                case 16:
                case 17:
                case 21:
                case 22:
                case 23:
                case 24:
                    mulX = Q12(1.2f);
                    mulZ = Q12(1.0f);
                    break;

                case 25:
                    if (D_800F035D == 0)
                    {
                        D_800F0180.vy = Q12(-13.0f);
                        D_800F0180.vz = Q12(2.5f);
                        D_800F035D++;
                    }

                case 26:
                case 27:
                case 31:
                case 32:
                case 33:
                case 37:
                case 38:
                case 39:
                case 43:
                case 44:
                case 45:
                    mulX = Q12(-1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 28:
                case 29:
                case 30:
                case 34:
                case 35:
                case 36:
                case 40:
                case 41:
                case 42:
                    mulX = Q12(1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 46:
                    if (D_800F035D == 1)
                    {
                        D_800F0180.vy = Q12(-15.75f);
                        D_800F0180.vz = Q12(-12.25f);
                        D_800F035D++;
                    }

                case 59:
                    mulX = Q12(0.0f);
                    mulZ = Q12(-1.6f);
                    break;

                case 47:
                case 48:
                case 49:
                case 56:
                case 57:
                case 58:
                    mulX = Q12(0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    mulX = Q12(-0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                default:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    SysWork_StateStepIncrement(0);
                    break;
            }

            D_800F0180.vy += Q12_MULT_PRECISE(g_DeltaTime0, mulX * 4);
            D_800F0180.vz += Q12_MULT_PRECISE(g_DeltaTime0, mulZ * 4);

            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_458);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800F3E0C = NO_VALUE;

            Sd_SfxStop(Sfx_Unk1467);
            break;
    }

    if (D_800F3E0C >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800F3E0C, (s_DmsHeader*)FS_BUFFER_13);

        g_SysWork.playerWork_4C.player_0.position_18.vx -= Q12(20.0f);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800F3DF0, &D_800F3E00, NULL, D_800F3E0C, (s_DmsHeader*)FS_BUFFER_13));

        D_800F3DF0.vx -= Q12(20.0f);
        D_800F3E00.vx -= Q12(20.0f);

        vcUserCamTarget(&D_800F3DF0, NULL, true);
        vcUserWatchTarget(&D_800F3E00, NULL, true);
    }
}

void func_800ECB58(void) // 0x800ECB58
{
    WorldObjectNoRotInit(&g_WorldObject0, "RSRMAP_H", -46.5f, 0.0f, 2.5f);

    WorldObjectInit(&g_WorldObject1, "FOOK_HID", 52.15f, -1.359f, -57.925f, 0.0f, 0.0f, 5.8f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 5;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800ECC8C(void) // 0x800ECC8C
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0)))
    {
            if (!Savegame_EventFlagGet(EventFlag_M5S01_PickupMap))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
            if (!Savegame_EventFlagGet(EventFlag_371))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HandgunBullets))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_FirstAidKit))
        {
            g_WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}
