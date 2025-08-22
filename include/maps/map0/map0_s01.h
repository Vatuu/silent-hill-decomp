#ifndef _MAP0_S01_H
#define _MAP0_S01_H
#include "bodyprog/bodyprog.h"
#include "types.h"

typedef struct
{
    VECTOR3 v3_0;
    s32    field_C;
    s16    field_10;
    s16    __pad;
} s_eventPosition;

typedef struct
{
    s_800BCE18_2BEC_0 thing_0;
    s_eventPosition   ep_1C;
} s_eventThing;

typedef struct
{
    s8  unk_0[8];
    char* field_8;
    char* field_C;
    char* field_10;
    char* field_14;
    char* field_18;
    char* field_1C;
} s_800A99E4;

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s8 D_800CBAD4;

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
