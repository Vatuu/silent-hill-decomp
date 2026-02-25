#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/map4/map4_s06.h"
#include "maps/particle.h"
#include "maps/characters/player.h"

extern s_AnimInfo HARRY_M4S06_ANIM_INFOS[];

void (*g_LoadScreenFuncs[])() = {
    NULL,
    Gfx_LoadingScreen_PlayerRun,
    Gfx_LoadingScreen_BackgroundTexture,
    Gfx_LoadingScreen_StageString
};

s_MapPoint2d MAP_POINTS[] = {
#include "map_points.h"
};

void (*g_MapEventFuncs[])() = {
    NULL
};

const s_MapOverlayHeader g_MapOverlayHeader = {
    .mapInfo_0                        = &MAP_INFOS[MapType_SPR],
    .getMapRoomIdxFunc_4              = Map_RoomIdxGet,
    .field_8                          = 15,
    .func_C                           = sharedFunc_800D929C_0_s00,
    .bgmEvent_10                      = Map_RoomBgmInit,
    .bgmIdx_14                        = 3,
    .ambientAudioIdx_15               = 11,
    .field_16                         = 1,
    .field_17                         = 2,
    .loadingScreenFuncs_18            = g_LoadScreenFuncs,
    .mapPointsOfInterest_1C           = MAP_POINTS,
    .mapEventFuncs_20                 = g_MapEventFuncs,
    .mapEvents_24                     = MAP_EVENTS,
    .field_28                         = &g_SysWork.npcCoords_FC0[0],
    .loadableItems_2C                 = LOADABLE_INVENTORY_ITEMS,
    .mapMessages_30                   = MAP_MESSAGES,
    .animInfos_34                     = HARRY_M4S06_ANIM_INFOS,
    .field_38                         = g_MapHeaderTable_38,
    .worldObjectsInit_3C              = Map_WorldObjectsInit,
    .worldObjectsUpdate_40            = Map_WorldObjectsUpdate,
    .func_44                          = NULL,
    .npcSpawnEvent_48                 = NULL,
    .unkTable1_4C                     = sharedData_800DFB7C_0_s00,
    .unkTable1Count_50                = ARRAY_SIZE(sharedData_800DFB7C_0_s00),
    .bloodSplats_54                   = g_Effect_BloodSplats,
    .bloodSplatCount_58               = ARRAY_SIZE(g_Effect_BloodSplats),
    .field_5C                         = NULL,
    .func_60                          = NULL,
    .func_64                          = NULL,
    .func_68                          = NULL,
    .func_6C                          = NULL,
    .func_70                          = NULL,
    .func_74                          = NULL,
    .func_78                          = NULL,
    .field_7C                         = NULL,
    .func_80                          = NULL,
    .func_84                          = NULL,
    .func_88                          = NULL,
    .func_8C                          = NULL,
    .func_90                          = NULL,
    .field_94                         = NULL,
    .func_98                          = NULL,
    .func_9C                          = NULL,
    .func_A0                          = NULL,
    .func_A4                          = NULL,
    .func_A8                          = NULL,
    .func_AC                          = NULL,
    .func_B0                          = NULL,
    .func_B4                          = NULL,
    .func_B8                          = sharedFunc_800CDAA8_0_s02,
    .func_BC                          = sharedFunc_800D1C38_0_s00,
    .func_C0                          = sharedFunc_800D209C_0_s00,
    .playerMatchArmAnimDisable_C4     = Player_MatchArmAnimDisable,
    .playerControlFreeze_C8           = Player_ControlFreeze,
    .playerControlUnfreeze_CC         = Player_ControlUnfreeze,
    .func_D0                          = sharedFunc_800D23EC_0_s00,
    .func_D4                          = sharedFunc_800D2C7C_0_s00,
    .func_D8                          = sharedFunc_800D2D2C_0_s00,
    .playerAnimLock_DC                = Player_AnimLock,
    .playerAnimIsLocked_E0            = Player_AnimIsLocked,
    .playerAnimUnlock_E4              = Player_AnimUnlock,
    .func_E8                          = sharedFunc_800D2DAC_0_s00,
    .playerMoveDistIsZero_EC          = Player_MoveDistanceIsZero,
    .playerMoveDistClear_F0           = Player_MoveDistanceClear,
    .playerFallBackward_F4            = Player_FallBackward,
    .func_F8                          = sharedFunc_800D2E7C_0_s00,
    .playerDamageFeetFront_FC         = Player_DamageFeetFront,
    .func_100                         = sharedFunc_800D2E8C_0_s00,
    .func_104                         = sharedFunc_800D2E6C_0_s00,
    .func_108                         = sharedFunc_800D2E94_0_s00,
    .func_10C                         = sharedFunc_800D2EB4_0_s00,
    .func_110                         = sharedFunc_800D2EF4_0_s00,
    .func_114                         = sharedFunc_800D2EA4_0_s00,
    .func_118                         = sharedFunc_800D2E9C_0_s00,
    .func_11C                         = NULL,
    .func_120                         = NULL,
    .func_124                         = NULL,
    .func_128                         = NULL,
    .func_12C                         = NULL,
    .func_130                         = NULL,
    .func_134                         = NULL,
    .func_138                         = NULL,
    .func_13C                         = NULL,
    .func_140                         = NULL,
    .func_144                         = NULL,
    .func_148                         = NULL,
    .func_14C                         = NULL,
    .animStartKeyframeIdxGet_150      = NULL,
    .func_154                         = NULL,
    .func_158                         = NULL,
    .func_15C                         = NULL,
    .func_160                         = NULL,
    .func_164                         = NULL,
    .particlesUpdate_168              = Particle_SystemUpdate,
    .enviromentSet_16C                = sharedFunc_800D08B8_0_s00,
    .func_170                         = sharedFunc_800D0A60_0_s00,
    .func_174                         = sharedFunc_800D0B18_0_s00,
    .particleHyperBlasterBeamDraw_178 = Particle_HyperBlasterBeamDraw,
    .particleBeamDraw_17C             = Particle_BeamDraw,
    .particleSoundStop_17C            = Particle_SoundStop,
    .windSpeedX_184                   = &g_Particle_SpeedX,
    .windSpeedZ_188                   = &g_Particle_SpeedZ,
    .data_18C                         = &sharedData_800DFB6C_0_s00,
    .data_190                         = &sharedData_800DFB70_0_s00,
    .charaUpdateFuncs_194             = {},
    .charaGroupIds_248                = {},
    .charaSpawns_24C                  = {
#include "chara_spawns.h"
    },
    .roadDataList_3CC = {
#include "vc_road_data.h"
    },
    .field_D2C = {
#include "header_field_D2C.h"
    },
};
