#ifndef _MAPS_MAP6_S00_H
#define _MAPS_MAP6_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk114
#define HAS_PlayerState_Unk126
#define HAS_PlayerState_Unk127
#define HAS_PlayerState_Unk133
#define KEYFRAME_PlayerState_Unk114 956

extern u16     D_800F0038;
extern s32     D_800F0040;
extern s32     D_800F0044;
extern VECTOR3 D_800F0668;
extern VECTOR3 D_800F0678;
extern u8      D_800F0684;
extern s16     D_800F0686;

extern s_WorldObjectDescNoRot g_WorldObject_Window;
extern s_WorldObjectDescNoRot g_WorldObject_DrOpen1;
extern s_WorldObjectDescNoRot g_WorldObject_DrOpen2;
extern s_WorldObjectDescNoRot g_WorldObject_DrClose;
extern s_WorldObjectModel        g_CommonWorldObjects[6];
extern s_WorldObjectPose      g_CommonWorldObjectPoses[3];

/** @brief Handles a First Aid Kit, Health Drink, or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800EB11C(void);

void Map_WorldObjectsInit(void);

void func_800EBEE0(void);

#endif
