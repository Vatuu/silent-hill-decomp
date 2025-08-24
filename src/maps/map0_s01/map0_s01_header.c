#include "bodyprog/bodyprog.h"
#include "maps/map0/map0_s01.h"
#include "bodyprog/math.h"
#include "maps/shared.h"

#define func_800DCCF4 ((void(*)())0x800DCCF4)
#define func_800CD1F8 ((void(*)())0x800CD1F8)
#define func_800D0C3C ((void(*)())0x800D0C3C)
#define func_800D16C4 ((void(*)())0x800D16C4)
#define func_800D2094 ((void(*)())0x800D2094)
#define func_800D20E4 ((void(*)())0x800D20E4)
#define func_800D20EC ((void(*)())0x800D20EC)
#define func_800D20F4 ((void(*)())0x800D20F4)
#define func_800D2054 ((void(*)())0x800D2054)
#define func_800D2104 ((void(*)())0x800D2104)
#define func_800D9C60 ((void(*)())0x800D9C60)
#define func_800CE000 ((void(*)())0x800CE000)
#define func_800CFFD8 ((void(*)())0x800CFFD8)
#define func_800D0850 ((void(*)())0x800D0850)
#define func_800DA980 ((void(*)())0x800DA980)
#define func_800DB790 ((void(*)())0x800DB790)

#define sharedData_800DFB64_0_s00 (0x800DE254)
#define sharedData_800DFB68_0_s00 (0x800DE258)
#define sharedData_800DFB6C_0_s00 (0x800DE25C)
#define sharedData_800DFB70_0_s00 (0x800DE260)

extern u8 D_800DDFB8[];
extern s_AnimInfo g_AnimInfo[];
extern s_func_800625F4 D_800DE270[300];
extern s_BloodSplat D_800DF9E0[150];
extern s32 D_800DFB10[];

void (*g_LoadScreenFuncs[])() =
{
    NULL,
    Gfx_LoadingScreen_PlayerRun,
    Gfx_LoadingScreen_BackgroundTexture,
    Gfx_LoadingScreen_StageString
};

s_AreaLoadParams g_MapAreaLoadParams[] =
{
    #include "area_load_params.h"
};

void (*g_MapEventFuncs[])() = 
{
    NULL,
    NULL,
    Event_HealthItemTake,
    func_800DA980,
    func_800DB790,
    func_800DBAA0,
    Event_KitchenKnifeItemTake,
    Event_FlashlightItemTake,
    Event_MapItemTake,
    Event_PocketRadioItemTake,
    Event_EmptyFunction,
    Event_HandgunItemTake
};

const u32 D_800C9578 = 0x00000000; // rodata 0

const s_MapOverlayHeader g_MapOverlayHeader = 
{
    .field_0 = (s_UnkStruct2_Mo*)0x8002500C,
    .getMapRoomIdxFunc_4 = sharedFunc_800D92AC_0_s00,
    .field_8 = 34,
    .unk_9 = { 0, 0, 0, },
    .func_C = sharedFunc_800D929C_0_s00,
    .func_10 = func_800DA778,
    .field_14 = 1,
    .field_15 = 3,
    .field_16 = 1,
    .field_17 = 2,
    .loadingScreenFuncs_18 = g_LoadScreenFuncs,
    .mapAreaLoadParams_1C = g_MapAreaLoadParams,
    .mapEventFuncs_20 = g_MapEventFuncs,
    .unk_24 = D_800DDFB8,
    .field_28 = &g_SysWork.npcCoords_FC0[0],
    .field_2C = (s_UnkStruct_MO*)0x800DD768,
    .mapMessageStrings_30 = g_MapMessages,
    .animInfo_34 = g_AnimInfo,
    .field_38 = (s_UnkStruct3_Mo*)0x800DD6C0,
    .func_3C = func_800DC9C8,
    .func_40 = func_800DCCF4,
    .func_44 = NULL,
    .func_48 = NULL,
    .unkTable1_4C = D_800DE270,
    .unkTable1Len_50 = ARRAY_SIZE(D_800DE270),
    .bloodSplats_54 = D_800DF9E0,
    .bloodSplatsLen_58 = ARRAY_SIZE(D_800DF9E0),
    .always0_5C = 0,
    .always0_60 = 0,
    .always0_64 = 0,
    .always0_68 = 0,
    .func_6C = NULL,
    .func_70 = NULL,
    .func_74 = NULL,
    .func_78 = NULL,
    .unk_7C = 0,
    .func_80 = NULL,
    .func_84 = NULL,
    .unk_88 = D_800DFB10,
    .func_8C = func_800CD1F8,
    .func_90 = NULL,
    .unk_94 = 0,
    .unk_98 = 0,
    .unk_9C = 0,
    .unk_A0 = 0,
    .func_A4 = NULL,
    .func_A8 = NULL,
    .func_AC = NULL,
    .func_B0 = NULL,
    .func_B4 = NULL,
    .func_B8 = func_800D0C3C,
    .func_BC = func_800D16C4,
    .func_C0 = sharedFunc_800D209C_0_s00,
    .func_C4 = sharedFunc_800D20D8_0_s00,
    .freezePlayerControl_C8 = sharedFunc_800D20E4_0_s00,
    .unfreezePlayerControl_CC = sharedFunc_800D2244_0_s00,
    .func_D0 = func_800D1E5C,
    .func_D4 = sharedFunc_800D2C7C_0_s00,
    .func_D8 = sharedFunc_800D2D2C_0_s00,
    .func_DC = sharedFunc_800D2D44_0_s00,
    .func_E0 = sharedFunc_800D2D6C_0_s00,
    .func_E4 = sharedFunc_800D2D84_0_s00,
    .func_E8 = sharedFunc_800D2DAC_0_s00,
    .func_EC = sharedFunc_800D2E50_0_s00,
    .func_F0 = sharedFunc_800D2E60_0_s00,
    .func_F4 = func_800D2094,
    .func_F8 = func_800D20E4,
    .func_FC = func_800D20EC,
    .func_100 = func_800D20F4,
    .func_104 = func_800D2054,
    .func_108 = func_800D20FC,
    .func_10C = sharedFunc_800D2EB4_0_s00,
    .func_110 = sharedFunc_800D2EF4_0_s00,
    .func_114 = sharedFunc_800D2EA4_0_s00,
    .func_118 = func_800D2104,
    .func_11C = sharedFunc_800D88AC_0_s00,
    .func_120 = sharedFunc_800D88C0_0_s00,
    .func_124 = sharedFunc_800D8904_0_s00,
    .func_128 = sharedFunc_800D891C_0_s00,
    .func_12C = sharedFunc_800D8928_0_s00,
    .func_130 = sharedFunc_800D893C_0_s00,
    .func_134 = sharedFunc_800D8950_0_s00,
    .func_138 = sharedFunc_800D8964_0_s00,
    .func_13C = func_800D9C60,
    .func_140 = sharedFunc_800D9064_0_s00,
    .func_144 = sharedFunc_800D9078_0_s00,
    .func_148 = sharedFunc_800D908C_0_s00,
    .func_14C = sharedFunc_800D9188_0_s00,
    .func_150 = sharedFunc_800D921C_0_s00,
    .func_154 = sharedFunc_800D923C_0_s00,
    .func_158 = NULL,
    .func_15C = NULL,
    .func_160 = NULL,
    .func_164 = NULL,
    .func_168 = func_800CE000,
    .func_16C = sharedFunc_800D08B8_0_s00,
    .func_170 = sharedFunc_800D0A60_0_s00,
    .func_174 = sharedFunc_800D0B18_0_s00,
    .func_178 = func_800CFFD8,
    .func_17C = func_800D0850,
    .func_180 = sharedFunc_800D0E04_0_s00,
    .windSpeedX_184 = sharedData_800DFB64_0_s00,
    .windSpeedZ_188 = sharedData_800DFB68_0_s00,
    .data_18C = sharedData_800DFB6C_0_s00,
    .data_190 = sharedData_800DFB70_0_s00,
    .charaUpdateFuncs_194 =
    {
        NULL,
        NULL,
        Ai_AirScreamer_Update,
        Ai_AirScreamer_Update,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        Ai_Cybil_Update,
        Ai_Cybil_Update,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    .charaGroupIds_248 = { Chara_None, Chara_None, Chara_None, Chara_None },
    .charaSpawns_24C = {},
    .roadDataList_3CC =
    {
        #include "vc_road_data.h"
    },
    .unk_84C = 
    {
        #include "header_last_unknown_chunk.h"
    }
};
