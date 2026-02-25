#ifndef _MAPS_MAP6_S00_H
#define _MAPS_MAP6_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk114
#define HAS_PlayerState_Unk126
#define HAS_PlayerState_Unk127
#define HAS_PlayerState_Unk133
#define KEYFRAME_PlayerState_Unk114 956

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

typedef struct
{
    POLY_GT4* field_0;
    MATRIX    field_4;
    MATRIX    field_24;
    SVECTOR   field_44[3];
    VECTOR3   field_5C;
    SVECTOR   field_68; // Q3.12
    CVECTOR   field_70;
    CVECTOR   field_74[4];
    s32       field_84;
    s32       field_88;
    s16       field_8C;
    s16       field_8E;
    u8        field_90[17][17];
    s32       field_1B4;
    s32       field_1B8;
    s32       field_1BC;
    s32       field_1C0;
    s32       field_1C4;
} s_func_800EC4B4;

typedef struct
{
    DVECTOR field_0[17][17];
    s32     field_484[17][17];
    CVECTOR field_908[17][17][2];
} s_func_800EC4B4_2;

extern u16     D_800F0038;
extern s32     D_800F0040;
extern s32     D_800F0044;
extern DVECTOR D_800F0084[17][17];
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

void func_800EAFF0(void);

/** @brief Handles a First Aid Kit, Health Drink, or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800EB11C(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800EC4B4(s32 arg0);

#endif
