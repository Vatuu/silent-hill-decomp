#ifndef _MAPS_MAP1_S00_H
#define _MAPS_MAP1_S00_H

#include "maps/shared.h"

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk87
#define HAS_PlayerState_Unk88

extern s32 D_800DD718;

extern s_WorldObjectPose 	  g_CommonWorldObjectPoses[5];
extern s_WorldObjectDescNoRot g_WorldObject0;
extern s_WorldObjectDescNoRot g_WorldObject1[6];
extern s_WorldObjectDescNoRot g_WorldObject2;
extern s_WorldObjectDescNoRot g_WorldObject3;
extern s_WorldObjectDescNoRot g_WorldObject4;
extern s_WorldObjectDescNoRot g_WorldObject5;
extern s_WorldObjectDescNoRot g_WorldObject6[2];
extern s_WorldObjectDesc      g_WorldObject7;
extern s_WorldObjectDesc      g_WorldObject8;

extern u8 D_800E1180;
extern s16 D_800E1182;

extern s_MapPoint2d MAP_POINTS[];
extern u8 D_800DCC4C;
extern u16 D_800DCC54[42];

void func_800D77F8(void);

void func_800D786C(void);

void func_800D7900(void);

void func_800D7994(void);

void func_800D7AC4(void);

void func_800D7AF8(void);

void func_800D7B2C(void);

void func_800D7E48(void);

void func_800D7E7C(void);

void func_800D7EB0(void);

void func_800D81CC(void);

void func_800D8354(void);

void func_800D853C(void);

void func_800D8570(void);

void func_800D85A4(void);

void func_800D85D8(void);

void func_800D8948(void);

void func_800D8CC4(void);

/** @brief Map pickup event. */
void func_800D922C(void);

void func_800D9254(void);

void func_800D928C(void);

void func_800DA3FC(void);

void Event_Boiler0(void);

void Event_Boiler1(void);

void Event_Boiler2(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
