#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/map6/map6_s02.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/alessa.h"

extern s_AnimInfo HARRY_M6S02_ANIM_INFOS[];

void (*g_LoadScreenFuncs[])() = {
    NULL,
    GameBoot_LoadScreen_PlayerRun,
    GameBoot_LoadScreen_BackgroundImg,
    GameBoot_LoadScreen_StageString
};

s_MapPoint2d MAP_POINTS[] = {
#include "map_points.h"
};

void (*g_MapEventFuncs[])() = {
    MapEvent_DoorJammed,
    MapEvent_DoorLocked,
    func_800CF0B0,
    func_800CF0B8,
    func_800CFC34,
    func_800D0500,
    func_800D32D0
};

const s_MapOverlayHeader g_MapOverlayHeader = {
    .mapInfo                        = &MAP_INFOS[MapType_RSU],
    .mapRoomIdxGet              = Map_RoomIdxGet,
    .field_8                          = 19,
    .func_C                           = sharedFunc_800D929C_0_s00,
    .bgmEvent                      = Map_RoomBgmInit,
    .bgmIdx                        = BgmTrackIdx_21,
    .ambientAudioIdx               = 33,
    .field_16                         = 2,
    .field_17                         = 0,
    .loadingScreenFuncs            = g_LoadScreenFuncs,
    .mapPoints           = MAP_POINTS,
    .mapEventFuncs                 = g_MapEventFuncs,
    .mapEvents                     = MAP_EVENTS,
    .npcBoneCoordBuffer                         = &g_SysWork.npcBoneCoordBuffer[0],
    .loadableItems                 = LOADABLE_INVENTORY_ITEMS,
    .mapMessages                   = MAP_MESSAGES,
    .harryMapAnimInfos                     = HARRY_M6S02_ANIM_INFOS,
    .field_38                         = g_MapHeaderTable_38,
    .initWorldObjects              = Map_WorldObjectsInit,
    .updateWorldObjects            = Map_WorldObjectsUpdate,
    .func_44                          = func_800D1AE4,
    .npcSpawnEvent                 = NULL,
    .unkTable1_4C                     = sharedData_800DFB7C_0_s00,
    .unkTable1Count_50                = ARRAY_SIZE(sharedData_800DFB7C_0_s00),
    .bloodSplats                   = g_Effect_BloodSplats,
    .bloodSplatCount               = ARRAY_SIZE(g_Effect_BloodSplats),
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
    .ptr_A0                           = NULL,
    .func_A4                          = NULL,
    .func_A8                          = func_800D2364,
    .func_AC                          = NULL,
    .func_B0                          = NULL,
    .func_B4                          = sharedFunc_800CE688_1_s03,
    .func_B8                          = sharedFunc_800CDAA8_0_s02,
    .func_BC                          = sharedFunc_800D1C38_0_s00,
    .func_C0                          = sharedFunc_800D209C_0_s00,
    .playerMatchArmAnimDisable     = Player_MatchArmAnimDisable,
    .playerControlFreeze           = Player_ControlFreeze,
    .playerControlUnfreeze         = Player_ControlUnfreeze,
    .func_D0                          = sharedFunc_800D23EC_0_s00,
    .func_D4                          = sharedFunc_800D2C7C_0_s00,
    .func_D8                          = sharedFunc_800D2D2C_0_s00,
    .playerAnimLock                = Player_AnimLock,
    .isPlayerAnimLocked            = Player_AnimIsLocked,
    .playerAnimUnlock              = Player_AnimUnlock,
    .func_E8                          = sharedFunc_800D2DAC_0_s00,
    .playerMoveDistIsZero          = Player_MoveDistanceIsZero,
    .playerMoveDistClear           = Player_MoveDistanceClear,
    .playerFallBackward            = Player_FallBackward,
    .func_F8                          = sharedFunc_800D2E7C_0_s00,
    .playerDamageFeetFront         = Player_DamageFeetFront,
    .func_100                         = sharedFunc_800D2E8C_0_s00,
    .func_104                         = sharedFunc_800D2E6C_0_s00,
    .func_108                         = sharedFunc_800D2E94_0_s00,
    .func_10C                         = sharedFunc_800D2EB4_0_s00,
    .func_110                         = sharedFunc_800D2EF4_0_s00,
    .func_114                         = sharedFunc_800D2EA4_0_s00,
    .func_118                         = sharedFunc_800D2E9C_0_s00,
    .func_11C                         = sharedFunc_800D88AC_0_s00,
    .func_120                         = sharedFunc_800D88C0_0_s00,
    .func_124                         = sharedFunc_800D8904_0_s00,
    .playerRunTimerReset                         = Player_RunTimerReset,
    .charaLock                         = Chara_Lock,
    .charaIsLockedCheck                         = Chara_IsLockedCheck,
    .charaUnlock                         = Chara_Unlock,
    .charaAnimPlaybackStateGet                         = Chara_AnimPlaybackStateGet,
    .func_13C                         = sharedFunc_800D8A00_0_s00,
    .charaVisibleSet                         = Chara_VisibleSet,
    .charaInvisibleSet                         = Chara_InvisibleSet,
    .func_148                         = sharedFunc_800D908C_0_s00,
    .func_14C                         = sharedFunc_800D9188_0_s00,
    .charaAnimStartKeyframeIdxGet      = Chara_AnimStartKeyframeIdxGet,
    .charaCollisionReset                         = Chara_CollisionReset,
    .func_158                         = NULL,
    .func_15C                         = NULL,
    .func_160                         = NULL,
    .func_164                         = NULL,
    .particlesUpdate              = Particle_SystemUpdate,
    .enviromentSet                = sharedFunc_800D08B8_0_s00,
    .func_170                         = sharedFunc_800D0A60_0_s00,
    .func_174                         = sharedFunc_800D0B18_0_s00,
    .particleHyperBlasterBeamDraw = Particle_HyperBlasterBeamDraw,
    .particleBeamDraw             = Particle_BeamDraw,
    .particleSoundStop            = Particle_SoundStop,
    .windSpeedX                   = &g_Particle_SpeedX,
    .windSpeedZ                   = &g_Particle_SpeedZ,
    .data_18C                         = &sharedData_800DFB6C_0_s00,
    .data_190                         = &sharedData_800DFB70_0_s00,
    .charaUpdateFuncs             = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, Alessa_Update },
    .charaGroupIds = {},
    .charaSpawnInfos   = {
#include "chara_spawns.h"
    },
    .cameraPaths = {
#include "vc_road_data.h"
    },
    .triggerZones = {
#include "header_field_D2C.h"
    },
};
