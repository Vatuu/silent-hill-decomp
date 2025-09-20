#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/map0/map0_s02.h"
#include "maps/shared.h"

#define BLOOD_SPLAT_COUNT_MAX 50

#define func_800CECB0 (0x800CECB0)
#define func_800CECDC (0x800CECDC)
#define func_800CE7EC (0x800CE7EC)
#define func_800CED08 (0x800CED08)
#define func_800CEFD4 (0x800CEFD4)
#define func_800CDD9C (0x800CDD9C)
#define func_800CACF0 (0x800CACF0)
#define func_800CCE44 (0x800CCE44)
#define func_800CD6BC (0x800CD6BC)

extern u8 D_800CFD90[];
extern s_func_800625F4 D_800D03DC[100];
extern s_BloodSplat g_Effect_BloodSplats[BLOOD_SPLAT_COUNT_MAX];
extern s_AnimInfo HARRY_M0S02_ANIM_INFOS[];

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
    MapEvent_CommonItemTake,
    MapEvent_EmptyFunction,
    MapEvent_GasolineTankItemTake,
    MapEvent_KatanaItemTake,
    MapEvent_ChannelingStoneItemTake
};

const u32 D_800C9578 = 0x00000000; // rodata 0

const s_MapOverlayHeader g_MapOverlayHeader = 
{
    .type_0 = &MAP_TYPES[9],
    .getMapRoomIdxFunc_4 = func_800CE7EC,
    .field_8 = 0xFF,
    .unk_9 = { 0, 0, 0 },
    .func_C = sharedFunc_800D929C_0_s00,
    .func_10 = func_800CE884,
    .field_14 = 0x6,
    .field_15 = 0xB,
    .field_16 = 0x1,
    .field_17 = 0x2,
    .loadingScreenFuncs_18 = g_LoadScreenFuncs,
    .mapAreaLoadParams_1C = g_MapAreaLoadParams,
    .mapEventFuncs_20 = g_MapEventFuncs,
    .unk_24 = D_800CFD90,
    .field_28 = &g_SysWork.npcCoords_FC0[0],
    .loadableItems_2C = (u8*)0x800CFABC,
    .mapMessages_30 = MAP_MESSAGES,
    .animInfos_34 = HARRY_M0S02_ANIM_INFOS,
    .field_38 = (s_UnkStruct3_Mo*)0x800CFA7C,
    .func_3C = func_800CED08,
    .func_40 = func_800CEFD4,
    .func_44 = NULL,
    .func_48 = NULL,
    .unkTable1_4C = D_800D03DC,
    .unkTable1Count_50 = ARRAY_SIZE(D_800D03DC),
    .bloodSplats_54 = g_Effect_BloodSplats,
    .bloodSplatCount_58 = ARRAY_SIZE(g_Effect_BloodSplats),
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
    .unk_88 = 0,
    .func_8C = NULL,
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
    .func_B8 = sharedFunc_800CDAA8_0_s02,
    .func_BC = func_800CDD9C,
    .func_C0 = sharedFunc_800D209C_0_s00,
    .func_C4 = sharedFunc_800D20D8_0_s00,
    .freezePlayerControl_C8 = sharedFunc_800D20E4_0_s00,
    .unfreezePlayerControl_CC = sharedFunc_800D2244_0_s00,
    .func_D0 = func_800CE548,
    .func_D4 = sharedFunc_800D2C7C_0_s00,
    .func_D8 = sharedFunc_800D2D2C_0_s00,
    .func_DC = sharedFunc_800D2D44_0_s00,
    .func_E0 = sharedFunc_800D2D6C_0_s00,
    .func_E4 = sharedFunc_800D2D84_0_s00,
    .func_E8 = sharedFunc_800D2DAC_0_s00,
    .func_EC = sharedFunc_800D2E50_0_s00,
    .func_F0 = sharedFunc_800D2E60_0_s00,
    .func_F4 = func_800CE748,
    .func_F8 = func_800CE750,
    .func_FC = func_800CE758,
    .func_100 = func_800CE760,
    .func_104 = func_800CE740,
    .func_108 = func_800CE768,
    .func_10C = sharedFunc_800D2EB4_0_s00,
    .func_110 = sharedFunc_800D2EF4_0_s00,
    .func_114 = sharedFunc_800D2EA4_0_s00,
    .func_118 = func_800CE770,
    .func_11C = NULL,
    .func_120 = NULL,
    .func_124 = NULL,
    .func_128 = NULL,
    .func_12C = NULL,
    .func_130 = NULL,
    .func_134 = NULL,
    .func_138 = NULL,
    .func_13C = NULL,
    .func_140 = NULL,
    .func_144 = NULL,
    .func_148 = NULL,
    .func_14C = NULL,
    .func_150 = NULL,
    .func_154 = NULL,
    .func_158 = NULL,
    .func_15C = NULL,
    .func_160 = NULL,
    .func_164 = NULL,
    .func_168 = func_800CACF0,
    .func_16C = sharedFunc_800D08B8_0_s00,
    .func_170 = sharedFunc_800D0A60_0_s00,
    .func_174 = sharedFunc_800D0B18_0_s00,
    .func_178 = func_800CCE44,
    .func_17C = func_800CD6BC,
    .func_180 = sharedFunc_800D0E04_0_s00,
    .windSpeedX_184 = (void*)&sharedData_800DFB64_0_s00,
    .windSpeedZ_188 = (void*)&sharedData_800DFB68_0_s00,
    .data_18C = (void*)&sharedData_800DFB6C_0_s00,
    .data_190 = (void*)&sharedData_800DFB70_0_s00,
    .charaUpdateFuncs_194 = {},
    .charaGroupIds_248 = {},
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
