#ifndef _MAPS_MAP2_S00_H
#define _MAPS_MAP2_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 946
#define KEYFRAME_PlayerState_Unk60 961

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

extern u8 D_800F1CA8[3]; // = { 0, 1, 2 }

extern s16 D_800F22AE;


extern s16 D_800F228C;

extern u8 D_800F228E;

extern s32 D_800F2290;

extern u16 g_MapMsgSounds[2];

extern u8 g_MapMsgSoundIdx;

extern u8 D_800F2295;

extern s32 D_800F2298;

extern s32 D_800F229C;

extern s32 D_800F1A24;

extern s16 D_800F534E;


/* TODO: Rename these, give them a sequental name (not really essential, but'd be nice */
extern SVECTOR3               D_800F5344;
extern s8                     D_800F534C;
extern s_WorldObject_0        D_800F535C;
extern VECTOR3                D_800F537C;
extern SVECTOR3               D_800F538C;
extern s_WorldObjectDesc      g_WorldObject0;    // D_800F539C
extern s_WorldObjectDesc      g_WorldObject1;    // D_800F53CC
extern s_WorldObjectDesc      g_WorldObject2;    // D_800F53FC
extern s_WorldObjectDesc      g_WorldObject3;    // D_800F542C
extern s_WorldObjectDescNoRot g_WorldObjectB[3]; // D_800F545C
extern s_WorldObjectDesc      g_WorldObject4[3]; // D_800F54DC
extern s_WorldObject_0        g_WorldObject5[4]; // D_800F556C
extern VECTOR3                D_800F55DC[2];
extern s_WorldObject_0        g_WorldObject6[3]; // D_800F55FC
extern s_WorldObject_0        g_WorldObject7[4]; // D_800F565C
extern VECTOR3                D_800F56CC[2];
extern s8                     D_800F56E4;
extern s_WorldObject_0        D_800F56EC;
extern s_WorldObjectPose      D_800F570C;
extern s_WorldObjectPose      D_800F572C;
extern s_WorldObjectPose      D_800F574C;
extern s_WorldObjectDesc      g_WorldObject8;    // D_800F576C
extern s_WorldObjectDesc      g_WorldObject9;    // D_800F579C
extern s_WorldObjectDesc      g_WorldObjectA;    // D_800F57CC
extern s_WorldObject_0        g_CommonWorldObjects[6]; // D_800F57FC



void func_800EE5D0(void);

void func_800E7D54(void);

void MapEvent_AtWaterWorks(void);

void MapEvent_CherylsSketchbook(void);

void func_800E816C(void);

void func_800E8198(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

void MapEvent_SteelPipeTake(void);

void MapEvent_CutsceneExitCafe(void);

void MapEvent_CherylsSketchbook(void);

void MapEvent_DoghouseNote(void);

void MapEvent_DoghouseKeyTake(void);

void func_800E9A0C(void);

void func_800E9A74(void);

void func_800E9CB4(void);

void func_800EB3F4(void);

void MapEvent_KGordonKeyUse(void);

void func_800EB090(void);

void func_800EB758(void);

void func_800EB79C(void);

void func_800EB7E0(void);

void func_800EB824(s32);

s32 func_800EE518(void);

u8 func_800EE5A8(u32 arg0);

void func_800E8C0C(void);

/** @brief Handles the House Key use event. */
void MapEvent_HouseKeyUse(void);

void MapEvent_DoorOfEclipseEnter(void);

void func_800EA6E0(void);

void func_800EAD2C(void);

void func_800EA960(void);

void func_800EB174(void);

#endif
