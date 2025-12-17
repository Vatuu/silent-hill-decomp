#ifndef _MAPS_MAP6_S02_H
#define _MAPS_MAP6_S02_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk71
#define HAS_PlayerState_Unk132
#define HAS_PlayerState_Unk111
#define HAS_PlayerState_Unk175
#define KEYFRAME_PlayerState_Unk111 915

extern u16 D_800D3B40;

extern s_FsImageDesc D_800D3B44[5];

extern u16 D_800D3B6C;

extern s_FsImageDesc D_800D3B70;

extern VECTOR3 D_800D3B78[];

extern u16 D_800D3C2C[];

extern u8 D_800D3C88;

/** Timer. */
extern s32 D_800D3C8C;

extern s32 D_800D3C90;

extern s16 D_800D3C94;

extern s32 D_800D3C98;

extern u8 D_800D3C9C;

extern s16 D_800D3C9E;

extern s32 D_800D3CA0;

extern u8 D_800D4E08;
extern s8 D_800D4E09;

extern VECTOR3 D_800D4E0C;

extern VECTOR3 D_800D4E1C;

extern s32 D_800D4E28;

extern s8 D_800D4E2C;

extern s8 D_800D4E2D;

extern s8 D_800D4E6C;
extern s8 D_800D4E6D;
extern s8 D_800D4E6E;

extern s16 D_800D4E70;

extern s_WorldObjectDesc g_WorldObject_SavePad;

extern s_FsImageDesc D_800CAB90;
extern RECT D_800CAB98;
extern u8 D_800D3C74[8];

void func_800CF0B8(void);

/** Func related to the UFO ending cutscene? */
void func_800CFC34(void);

void func_800D0500(void);

void func_800D1330(s16);

void Map_WorldObjectsInit(void);

s32 func_800D1D40(void);

void func_800D2170(s32 arg0);

void func_800D1718(void);

#endif
