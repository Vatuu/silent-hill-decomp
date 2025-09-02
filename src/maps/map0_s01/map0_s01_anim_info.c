#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s_AnimInfo g_AnimInfos[] =
{
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true),  false, ANIM_STATUS(38, true), 0, { FP_TIME(10.0f) },           676,      677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true),  false, ANIM_STATUS(39, true), 0, { FP_TIME(10.0f) },           678,      713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true),  false, ANIM_STATUS(40, true), 0, { FP_TIME(15.0f) },           718,      732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true),  false, ANIM_STATUS(41, true), 0, { FP_TIME(15.0f) },           737,      751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true),  false, ANIM_STATUS(42, true), 0, { FP_TIME(15.0f) },           758,      770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true),  false, ANIM_STATUS(43, true), 0, { FP_TIME(15.0f) },           777,      789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true),  false, ANIM_STATUS(44, true), 0, { FP_TIME(15.0f) },           790,      804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true),  false, ANIM_STATUS(45, true), 0, { FP_TIME(14.39990234375f) }, 805,      815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true),  false, ANIM_STATUS(46, true), 0, { FP_TIME(18.0f) },           816,      826 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 827 },
    { Anim_Update0, ANIM_STATUS(47, true),  false, ANIM_STATUS(47, true), 0, { FP_TIME(8.699951171875f) }, 827,      872 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 873 },
    { Anim_Update0, ANIM_STATUS(48, true),  false, ANIM_STATUS(48, true), 0, { FP_TIME(7.7998046875f) },   873,      900 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 901 },
    { Anim_Update0, ANIM_STATUS(49, true),  false, ANIM_STATUS(49, true), 0, { FP_TIME(4.0f) },            901,      916 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 917 },
    { Anim_Update0, ANIM_STATUS(50, true),  false, ANIM_STATUS(50, true), 0, { FP_TIME(15.0f) },           917,      947 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), 0, { FP_TIME(64.0f) },           NO_VALUE, 948 },
    { Anim_Update0, ANIM_STATUS(51, true),  false, ANIM_STATUS(51, true), 0, { FP_TIME(18.0f) },           948,      1026 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 1027 },
    { Anim_Update0, ANIM_STATUS(52, true),  false, ANIM_STATUS(52, true), 0, { FP_TIME(15.0f) },           1027,     1037 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 1038 },
    { Anim_Update0, ANIM_STATUS(53, true),  false, ANIM_STATUS(53, true), 0, { FP_TIME(15.0f) },           1038,     1054 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 1055 },
    { Anim_Update0, ANIM_STATUS(54, true),  false, ANIM_STATUS(54, true), 0, { FP_TIME(10.0f) },           1055,     1074 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 1075 },
    { Anim_Update1, ANIM_STATUS(55, true),  false, NO_VALUE,              0, { FP_TIME(1.0f) },            1075,     1080 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 1081 },
    { Anim_Update1, ANIM_STATUS(56, true),  false, NO_VALUE,              0, { FP_TIME(2.0f) },            1081,     1084 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), 0, { FP_TIME(10.0f) },           NO_VALUE, 815  },
    { Anim_Update0, ANIM_STATUS(57, true),  false, ANIM_STATUS(57, true), 0, { FP_TIME(15.0f) },           815,      815  },
    {} // End of list.
};

s_UnkStruct3_Mo g_MapHeaders_38[21] =
{
    { 0x4D4C, 0x0,   0x2A4, 0x2A5 },
    { 0x4F4E, 0xCA,  0x2A6, 0x2C9 },
    { 0x5150, 0xD2,  0x2CA, 0x2DC },
    { 0x5352, 0xD3,  0x2DD, 0x2EF },
    { 0x5554, 0xD4,  0x2F0, 0x302 },
    { 0x5756, 0xD5,  0x303, 0x315 },
    { 0x5958, 0xF2,  0x316, 0x324 },
    { 0x5B5A, 0x156, 0x325, 0x32F },
    { 0x5D5C, 0x157, 0x330, 0x33A },
    { 0x5F5E, 0x15F, 0x33B, 0x368 },
    { 0x6160, 0x160, 0x369, 0x384 },
    { 0x6362, 0x161, 0x385, 0x394 },
    { 0x6564, 0x168, 0x395, 0x3B3 },
    { 0x6766, 0x16B, 0x3B4, 0x402 },
    { 0x6968, 0x16D, 0x403, 0x40D },
    { 0x6B6A, 0x16E, 0x40E, 0x41E },
    { 0x6D6C, 0x16F, 0x41F, 0x432 },
    { 0x6F6E, 0x182, 0x433, 0x438 },
    { 0x7170, 0x190, 0x439, 0x43C },
    { 0x7372, 0x158, 0x32F, 0x32F },
    {} // End of list.
};

u8 g_LoadableInventoryItems[35] =
{
    InventoryItemId_HealthDrink,
    InventoryItemId_FirstAidKit,
    InventoryItemId_Ampoule,
    InventoryItemId_KitchenKnife,
    InventoryItemId_SteelPipe,
    InventoryItemId_Hammer,
    InventoryItemId_Chainsaw,
    InventoryItemId_Axe,
    InventoryItemId_Handgun,
    InventoryItemId_HuntingRifle,
    InventoryItemId_Shotgun,
    InventoryItemId_HyperBlaster,
    InventoryItemId_HandgunBullets,
    InventoryItemId_RifleShells,
    InventoryItemId_ShotgunShells,
    InventoryItemId_Flashlight,
    InventoryItemId_PocketRadio,
    InventoryItemId_HouseKey,
    InventoryItemId_KeyOfLion,
    InventoryItemId_KeyOfWoodman,
    InventoryItemId_KeyOfScarecrow,
    InventoryItemId_KGordonKey,
    InventoryItemId_DrawbridgeKey,
    InventoryItemId_NoteToSchool,
    InventoryItemId_NoteDoghouse,
    InventoryItemId_Flauros,
    InventoryItemId_AntiqueShopKey,
    InventoryItemId_PlasticBottle,
    InventoryItemId_UnknownLiquid,
    InventoryItemId_VideoTape,
    InventoryItemId_RockDrill,
    InventoryItemId_GasolineTank,
    InventoryItemId_ChannelingStone,
    InventoryItemId_Katana,
    InventoryItemId_Unequipped
};

u8 sharedData_800DD78B_0_s01 = 0;
s32 sharedData_800DD78C_0_s01[2] = {};
s8 sharedData_800DF158_1_s02 = 0;
u8 sharedData_800DD591_0_s00 = 0;
u8 sharedData_800DD796_0_s01 = 1;
u8 __padding = 0;
