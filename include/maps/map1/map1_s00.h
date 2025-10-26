#ifndef _MAPS_MAP1_S00_H
#define _MAPS_MAP1_S00_H

#include "maps/shared.h"
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk87
#define HAS_PlayerState_Unk88

extern s32 D_800DD718;

extern s_WorldObjectPos g_CommonWorldObjectsPos[5]; // 0x800DD71C
extern s_WorldObjectDesc_norot g_WorldObj0;    // 800E0EF0
extern s_WorldObjectDesc_norot g_WorldObj1[6]; // 800E0F20
extern s_WorldObjectDesc_norot g_WorldObj2;    // 800E1010
extern s_WorldObjectDesc_norot g_WorldObj3;    // 800E1040
extern s_WorldObjectDesc_norot g_WorldObj4;    // 800E1070
extern s_WorldObjectDesc_norot g_WorldObj5;    // 800E10A0
extern s_WorldObjectDesc_norot g_WorldObj6[2]; // 800E10D0
extern s_WorldObjectDesc       g_WorldObj7;    // 800E1120
extern s_WorldObjectDesc       g_WorldObj8;    // 800E1150
extern u8 D_800E1180;
extern s16 D_800E1182;
extern s_WorldObjectDesc       g_WorldObj9;    // 800E1190
extern s_WorldObject_0         g_CommonWorldObjects[6]; // 800E11C0
extern s_MapPoint2d MAP_POINTS[];
extern u8 D_800DCC4C;
extern u16 D_800DCC54[42];

void func_800D7AC4(void);

void func_800D7AF8(void);

void func_800D7E48(void);

void func_800D7E7C(void);

void func_800D853C(void);

void func_800D8570(void);

void func_800D85A4(void);

void func_800D8CC4(void);

void Event_Boiler2(void);

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
