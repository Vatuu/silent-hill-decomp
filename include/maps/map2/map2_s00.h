#ifndef _MAPS_MAP2_S00_H
#define _MAPS_MAP2_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 946
#define KEYFRAME_PlayerState_Unk60 961

#define HAS_PARTICLE_CASE_1
#define HAS_PARTICLE_CASE_9
#define HAS_PARTICLE_CASE_10
#define HAS_PARTICLE_CASE_11
#define PARTICLE_CASE_COUNT 4

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

extern u8 D_800F1CA8[3]; // = { 0, 1, 2 }

extern s16 D_800F22AE;

/** Alpha value? */
extern q3_12 D_800F228C;

extern u8 D_800F228E;

/** 2D map marking color shade. Used to fade in the sprite to half opacity. */
extern s32 g_Gfx_Map2dMarkingFade;

extern u16 g_MapMsgSounds[2];

extern u8 g_MapMsgSoundIdx;

extern u8 D_800F2295;

extern s32 D_800F2298;

/** 2D map zoom counter or timer. */
extern s32 D_800F229C;

extern s32 D_800F1A24;

/** Time. */
extern q3_12 D_800F534E;

extern s_WorldObjectPose  g_CommonWorldObjectPoses[32];

extern s16 D_800F5350;

/* TODO: Rename these with sequental names (not really essential, but would be nice). */
extern SVECTOR3               D_800F5344;
extern s8                     D_800F534C;
extern s_WorldObject_0        D_800F535C;
extern VECTOR3                D_800F537C;
extern SVECTOR3               D_800F538C;
extern s_WorldObjectDesc      g_WorldObject0;
extern s_WorldObjectDesc      g_WorldObject1;
extern s_WorldObjectDesc      g_WorldObject2;
extern s_WorldObjectDesc      g_WorldObject3;
extern s_WorldObjectDescNoRot g_WorldObjectB[3];
extern s_WorldObjectDesc      g_WorldObject4[3];
extern s_WorldObject_0        g_WorldObject5[4];
extern VECTOR3                D_800F55DC[2];
extern s_WorldObject_0        g_WorldObject6[3];
extern s_WorldObject_0        g_WorldObject7[4];
extern VECTOR3                D_800F56CC[2];
extern u8                     D_800F56E4;
extern s_WorldObject_0        D_800F56EC;
extern s_WorldObjectPose      D_800F570C;
extern s_WorldObjectPose      D_800F572C;
extern s_WorldObjectPose      D_800F574C;
extern s_WorldObjectDesc      g_WorldObject8;
extern s_WorldObjectDesc      g_WorldObject9;
extern s_WorldObjectDesc      g_WorldObjectA;
extern s_WorldObject_0        g_CommonWorldObjects[6];

extern s_MapPoint2d D_800F1CAC[3][32];
extern s_FsImageDesc* D_800F22A0;
extern s_FsImageDesc* D_800F22A4;
extern s_FsImageDesc* D_800F22A8;
extern s16 g_DoorOfEclypse_MapMsgIdx;
extern s16 g_Gfx_LockTimFileIdxs[8];

void func_800D756C(s_SubCharacter* chara);

void func_800D794C(s_SubCharacter* chara);

void func_800DD588(s_SubCharacter* chara);

void func_800DD834(s_SubCharacter* chara);

void func_800E7D54(void);

void MapEvent_AtWaterWorks(void);

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

/** @brief Handles the House Key use event. */
void MapEvent_HouseKeyUse(void);

void func_800E9DD8(void);

void MapEvent_DoorOfEclipseEnter(void);

void func_800EA6E0(void);

void MapEvent_KGordonKeyUse(void);

void func_800EA960(void);

void func_800EAD2C(void);

void func_800EB090(void);

void func_800EB174(void);

void func_800EB3F4(void);

void func_800EB758(void);

void func_800EB79C(void);

void func_800EB7E0(void);

void func_800EB824(s32);

void func_800EC080(void);

/** Index getter. */
s32 func_800EE518(void);

s32 func_800EE5A8(u32 arg0);

void func_800EE5D0(void);

void func_800EE660(void);

#endif
