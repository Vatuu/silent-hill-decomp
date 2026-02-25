#ifndef _MAPS_MAP4_S05_H
#define _MAPS_MAP4_S05_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk109

#define MAP_ROOM_MIN_X Q12(-240.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-120.0f)
#define MAP_ROOM_MAX_Z Q12(240.0f)

#define MAP_FIELD_4C_COUNT 250
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

typedef struct
{
    s32 field_0[2];
    s32 field_8[2];
    s32 field_10;
} s_func_800D4458;

extern q19_12 D_800D7858;

extern q3_12 D_800D785C;

extern s_AnimInfo FLOATSTINGER_ANIM_INFOS[];

extern VECTOR3 D_800DB938;

extern VECTOR3 D_800DB948;

extern s32 D_800DB954;

extern s_FsImageDesc D_800D7D64;

extern s32 D_800D7D6C;

extern s16 D_800D7D70;

extern u16 D_800D7D74;

extern VECTOR3 D_800D7D88;

extern u8 D_800D7D94;

extern u8 D_800D7D95;

extern s32 D_800D7D6C;

extern s16 D_800D7D80;

extern u8 D_800D7D82;

extern q3_12 D_800DB898;

extern q3_12 D_800DB89C;

extern s16 D_800DB8A8[];

extern GsCOORDINATE2* D_800DB928;

extern s_WorldObjectDescNoRot g_WorldObject_Kidn04;
extern s_WorldObjectDescNoRot g_WorldObject_Kidn05;

extern u8 D_800DB9B0;

extern void (*D_800D7A04[])(void);

extern SVECTOR D_800D7A20[];

extern SVECTOR D_800D7A30;

extern VECTOR3 D_800DB8C8[];

extern u8 D_800D7848[];

extern s32 D_800D799C;

extern u8 D_800D7A58[];

extern SVECTOR D_800D7A5C[];

extern s_func_800D4458 D_800D780C[];

extern s16 D_800DB89A;

extern s32 D_800D7860;

extern s16 D_800D7A38[];

void Ai_Floatstinger_Update(s_SubCharacter* floatstinger, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Floatstinger_Init(s_SubCharacter* floatstinger);

void func_800D1968(s_SubCharacter* floatstinger);

void Ai_Floatstinger_ControlUpdate(s_SubCharacter* floatstinger);

void func_800D1BF8(s_SubCharacter* floatstinger);

void func_800D2B90(s_SubCharacter* floatstinger);

void func_800D3424(s_SubCharacter* floatstinger);

void func_800D3564(s_SubCharacter* floatstinger);

void func_800D35F0(s_SubCharacter* floatstinger);

void func_800D37E8(s_SubCharacter* floatstinger, s_AnmHeader* anmHdr);

void func_800D3AD4(s_SubCharacter* floatstinger);

void func_800D3F84(VECTOR3* floatstinger, s32 arg1, s32 arg2);

void func_800D41F0(s_SubCharacter* floatstinger);

bool func_800D4458(s_SubCharacter* floatstinger, VECTOR3* arg1);

s32 func_800D48A4(s_SubCharacter* floatstinger, s16 arg1, s16 arg2);

void func_800D4A3C(s_SubCharacter* floatstinger, VECTOR3* pos, q3_12 angle);

void func_800D61A4(void);

void func_800D61AC(void);

void func_800D6800(void);

void func_800D6BC0(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
