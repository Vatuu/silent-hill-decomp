#ifndef _MAP0_S01_H
#define _MAP0_S01_H
#include "types.h"

/** @brief Event flags specific to this map. */
typedef enum _EventFlags
{
    EventFlag_45 = 45,
    EventFlag_46 = 46,
    EventFlag_47 = 47,
    EventFlag_50 = 50,
    EventFlag_52 = 52
} e_EventFlags;

typedef struct
{
    q19_12 vx_0;
    q19_12 vy_4;
    q19_12 vz_8;
    s32    field_C;
    s16    field_10;
    s8     unk_12[8];
} s_800E2490;

typedef struct
{
    s8  unk_0[8];
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} s_800A99E4;

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s8 D_800CBAD4;

extern s8 D_800CC908;

extern s32 D_800CCA1C; // Type assumed.

extern s32 D_800CCA28; // Type assumed.

extern VECTOR3 D_800CCA34;

extern s32 D_800CCA40; // Type assumed.

extern s32 D_800CCA4C; // Type assumed.

extern VECTOR3 D_800CCA58;

/** Character name. */
extern char* D_800CCA64;

/** *Map `RECT`? */
extern RECT D_800CCAC8;

extern u16 D_800DE128;

extern s32 D_800E239C;

extern u8 D_800E23A0;

extern u8 D_800E23A1;

/** Target camera position for cutscene. */
extern VECTOR3 D_800E2380;

/** Target camera look-at for cutscene. */
extern VECTOR3 D_800E2390;

extern s_800E2490 D_800E2490;

extern s_800E2490 D_800E24BC;

extern s_800E2490 D_800E24EC;

extern s_800E2490 D_800E251C;

extern s_800E2490 D_800E254C;

extern s16 D_800E2560;

/** Size might be 6. Possibly related to NPCs. */
extern s_800BCE18_2BEC_0 D_800E2570[];

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s32 arg0);

s32 func_800D7440(VECTOR* vec0, VECTOR* vec1, s_SubCharacter* chara);

void func_800D76A0(s_SubCharacter* chara);

void func_800D7E88(s_Model* model);

void func_800D8714(s_SubCharacter*, s32, s32);

void func_800DA778(s32 arg0);

void func_800DA7AC();

void func_800DA7FC();

void func_800DA8A4();

/** Event function. */
void func_800DBAA0();

void Event_PocketRadioItemTake();

void Event_FlashlightItemTake();

/** Also responsible for air screamer scene setup in the cafe. */
void Event_MapItemTake();

void Event_KitchenKnifeItemTake();

void Event_HealthItemTake();

void Event_HandgunItemTake();

void func_800DC9C8();

void func_800DD2EC(s32 arg0);

#endif
