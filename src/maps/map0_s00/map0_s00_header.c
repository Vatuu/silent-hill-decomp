#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h"

s32 sharedFunc_800D929C_0_s00();
s32 sharedFunc_800D2DAC_0_s00();
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara);
bool sharedFunc_800D9188_0_s00(s32 arg0, s_SubCharacter* arg1, s32 arg2, s32 sfx);
void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1);

// Undefined functions, unknown signature.
#define func_800D94F8 (void(*)(void))0x800D94F8
#define func_800DBE68 (void(*)(void))0x800DBE68
#define func_800DBF08 (void(*)(void))0x800DBF08
#define func_800DC1E8 (void(*)(void))0x800DC1E8
#define func_800D0E34 (void(*)(void))0x800D0E34
#define func_800D1C38 (void(*)(void))0x800D1C38
#define func_800D23EC (void(*)(void))0x800D23EC
#define func_800D8A00 (void(*)(void))0x800D8A00
#define func_800CB6B0 (void(*)(void))0x800CB6B0

#define func_800D9610 (void(*)(void))0x800D9610 
#define func_800D9748 (void(*)(void))0x800D9748
#define func_800D9D98 (void(*)(void))0x800D9D98
#define func_800DA028 (void(*)(void))0x800DA028
#define func_800DA254 (void(*)(void))0x800DA254
#define func_800DA5A0 (void(*)(void))0x800DA5A0
#define func_800DAA68 (void(*)(void))0x800DAA68
#define func_800DAB8C (void(*)(void))0x800DAB8C
#define func_800DACB0 (void(*)(void))0x800DACB0
#define func_800DADD4 (void(*)(void))0x800DADD4
#define func_800DAEFC (void(*)(void))0x800DAEFC
#define func_800DB26C (void(*)(void))0x800DB26C
#define func_800DB514 (void(*)(void))0x800DB514
#define func_800DB870 (void(*)(void))0x800DB870
#define func_800DB94C (void(*)(void))0x800DB94C
#define func_800DBE00 (void(*)(void))0x800DBE00

extern u8 D_800DF754[];
extern s_func_800625F4 D_800DFB7C[];
extern s32 D_800E0B1C[];

extern s_AnimInfo g_AnimInfo[];
void (*g_LoadScreenFuncs[])() = 
{
    0,
    Gfx_LoadingScreen_PlayerRun,
    0x80035BBC,
    func_800D95D4
};

s_AreaLoadParams g_MapAreaLoadParams[] = 
{
    #include "area_load_params.h"
};

void (*g_MapEventFuncs[])() = 
{
    func_800D9610,
    0x00000000,
    func_800D9748,
    func_800D9D98,
    func_800DA028,
    func_800DA254,
    func_800DA5A0,
    func_800DAA68,
    func_800DAB8C,
    func_800DACB0,
    func_800DADD4,
    func_800DAEFC,
    func_800DB26C,
    func_800DB514,
    func_800DB870,
    func_800DB94C,
    func_800DBE00,
};

const u32 D_800C9578 = 0x00000000; // rodata 0
const s_MapOverlayHeader g_MapOverlayHeader = 
{
    .field_0 = (s_UnkStruct2_Mo*)0x8002500C,
    .getMapRoomIdxFunc_4 = sharedFunc_800D92AC_0_s00,
    .field_8 = 0x22,
    .unk_9 = { 0x00, 0x00, 0x00 },
    .func_C = sharedFunc_800D929C_0_s00,
    .func_10 = func_800D94F8,
    .field_14 = 0x03, // Flags?
    .field_15 = 0x02,
    .field_16 = 0x01,
    .field_17 = 0x02,
    .loadingScreenFuncs_18 = g_LoadScreenFuncs,
    .mapAreaLoadParams_1C = g_MapAreaLoadParams,
    .mapEventFuncs_20 = g_MapEventFuncs,
    .unk_24 = D_800DF754,
    .field_28 = &g_SysWork.npcCoords_FC0[0],
    .field_2C = (s_UnkStruct_MO*)0x800DD57C,
    .mapMessageStrings_30 = g_MapMessages,
    .animInfo_34 = g_AnimInfo,
    .field_38 = (s_UnkStruct3_Mo*)0x800DD4EC,
    .func_3C = func_800DBE68,
    .func_40 = func_800DBF08,
    .func_44 = 0,
    .func_48 = func_800DC1E8,
    .field_4C = D_800DFB7C,
    .unk_50 = 0x000000C8,
    .unk_54 = D_800E0B1C,
    .unk_58 = 0x00000096,
    .unk_5C = 0x00000000,
    .unk_60 = {}, // 88 zeros.
    .func_B8 = func_800D0E34,
    .func_BC = func_800D1C38,
    .func_C0 = sharedFunc_800D209C_0_s00,
    .func_C4 = sharedFunc_800D20D8_0_s00,
    .func_C8 = sharedFunc_800D20E4_0_s00,
    .func_CC = sharedFunc_800D2244_0_s00,
    .func_D0 = func_800D23EC,
    .func_D4 = sharedFunc_800D2C7C_0_s00,
    .func_D8 = sharedFunc_800D2D2C_0_s00,
    .func_DC = sharedFunc_800D2D44_0_s00,
    .func_E0 = sharedFunc_800D2D6C_0_s00,
    .func_E4 = sharedFunc_800D2D84_0_s00,
    .func_E8 = sharedFunc_800D2DAC_0_s00,
    .func_EC = sharedFunc_800D2E50_0_s00,

    .func_F0 = sharedFunc_800D2E60_0_s00,
    .func_F4 = func_800D2E74,
    .func_F8 = func_800D2E7C,
    .func_FC = func_800D2E84,
    .func_100 = func_800D2E8C,
    .func_104 = func_800D2E6C,
    .func_108 = func_800D2E94,
    .func_10C = sharedFunc_800D2EB4_0_s00,
    .func_110 = sharedFunc_800D2EF4_0_s00,
    .func_114 = sharedFunc_800D2EA4_0_s00,
    .func_118 = func_800D2E9C,
    .func_11C = sharedFunc_800D88AC_0_s00,
    .func_120 = sharedFunc_800D88C0_0_s00,
    .func_124 = sharedFunc_800D8904_0_s00,
    .func_128 = sharedFunc_800D891C_0_s00,
    .func_12C = sharedFunc_800D8928_0_s00,
    .func_130 = sharedFunc_800D893C_0_s00,
    .func_134 = sharedFunc_800D8950_0_s00,
    .func_138 = sharedFunc_800D8964_0_s00, 
    .func_13C = func_800D8A00,
    .func_140 = sharedFunc_800D9064_0_s00,
    .func_144 = sharedFunc_800D9078_0_s00,
    .func_148 = sharedFunc_800D908C_0_s00,
    .func_14C = sharedFunc_800D9188_0_s00,
    .func_150 = sharedFunc_800D921C_0_s00,
    .func_154 = sharedFunc_800D923C_0_s00,
    .func_158 = 0,
    .unk_15C = {}, // 12 zeros.
    .func_168 = func_800CB6B0,
    .func_16C = sharedFunc_800D08B8_0_s00,
    .func_170 = sharedFunc_800D0A60_0_s00,
    .func_174 = sharedFunc_800D0B18_0_s00,
    .func_178 = func_800D0E24,
    .func_17C = func_800D0E2C,
    .func_180 = sharedFunc_800D0E04_0_s00,
    .func_184 = 0x800DFB64, // sharedData_800DFB64_0_s00`
    .func_188 = 0x800DFB68, // sharedData_800DFB68_0_s00`
    .func_18C = 0x800DFB6C, // sharedData_800DFB6C_0_s00`
    .func_190 = 0x800DFB70, // sharedData_800DFB70_0_s00`
    .charaUpdateFuncs_194 =
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        Ai_Stalker_Update,
        Ai_Stalker_Update,
        Ai_Stalker_Update,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        Ai_Cheryl_Update,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
    },
    .charaGroupIds_248 = {}, // 4 zeros.
    .charaSpawns_24C =
    {
        #include "chara_spawns.h"
    },
    .roadDataList_3CC =
    {
        #include "vc_road_data.h"
    },
    .unk_84C = 
    {
        #include "header_last_unknown_chunk.h"
    },
};
