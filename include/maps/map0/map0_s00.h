#ifndef _MAPS_MAP0_S00_H
#define _MAPS_MAP0_S00_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk74
#define HAS_PlayerState_Unk84

#define HAS_PARTICLE_CASE_1
#define PARTICLE_CASE_COUNT 1

#define HAS_Chara_Cheryl
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

typedef struct
{
    s16 field_0;
    s16 field_2; // Angle.
} s_800DFB44;

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
} s_800DFB48;

typedef struct
{
    s32 field_0;
} s_800E0C74;

/** `bool` */
extern u8 D_800DD593;

/** `bool` */
extern u8 D_800DD594;

/** Time. */
extern q19_12 D_800DFAB8;

extern u16 g_MapMsgSounds[]; // 0x800DFABC

extern u8 D_800DFAC2;

extern s32 D_800DFAC4;

extern u16 D_800DFAC8;

extern s32 D_800DFACC;

/** Distance. */
extern q19_12 D_800DFAD0;

extern s32 D_800DFAD4;

extern bool g_WarpCamera; // 0x800DFAD8

extern q19_12 D_800DFADC;

extern VECTOR3 D_800DFAE0[];  // }  TODO might be one big table.
extern VECTOR3 D_800DFB28[3]; // }

extern u8 g_MapMsgSoundIdx; // 0x800DFB58

extern s32 D_800DFB40;

extern s_800DFB44 D_800DFB44;

extern s_800DFB48 D_800DFB48;

extern s32 D_800DFB54;

extern s32 D_800DFB5C;

extern u8 D_800DFB60;

extern u8 D_800DFB61;

extern u8 D_800DF2F8;

extern s16 D_800DF300[];

extern s16 D_800E0C64;

extern s_800E0C74 D_800E0C74;

extern VECTOR3 D_800E32DC[4];

extern u8 D_800E34EC;

extern u8 D_800E39AC;

extern s_WorldObjectModel D_800E3A5C[2];

extern VECTOR3 D_800E3A9C;

extern SVECTOR3 D_800E3AAC;

void func_800D0124(void);

void MapEvent_CutsceneAlleyNightmare(void);

void func_800DBE00(void);

void func_800DC33C(void);

void func_800DC694(void);

void func_800DC8D8(void);

void func_800DCA30(void);

s32 func_800DCDA8(void);

s32 func_800DCF38(s32);

void func_800DD0CC(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void MapEvent_GreyChildrenSpawn(void);

void func_800DD0CC(void);

void func_800DCC54(void);

void func_800DA454(void);

void func_800DA5A0(void);

void func_800D9610(void);

void func_800D9D98(void);

void func_800DA028(void);

void func_800DA254(void);

void func_800DAA68(void);

void func_800DAB8C(void);

void func_800DACB0(void);

void func_800DADD4(void);

void func_800DAEFC(void);

void func_800DB26C(void);

void func_800DB514(void);

void func_800DB870(void);

void func_800DADD4(void);

void MapEvent_OpeningCutscene(void);

#endif
