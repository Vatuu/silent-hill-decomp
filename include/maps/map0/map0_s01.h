#ifndef _MAP0_S01_H
#define _MAP0_S01_H

#include "bodyprog/bodyprog.h"
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
    VECTOR3 position_0;
    s32     field_C;
    s16     field_10;
    s16     pad_12;
} s_EventPosition;

typedef struct
{
    s_800BCE18_2BEC_0 field_0;
    s_EventPosition   eventPosition_1C;
} s_EventThing;

typedef struct
{
    s8    unk_0[8]; // String?
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

extern s8 D_800CC908;

extern s32 D_800CCA1C; // Type assumed.

extern s32 D_800CCA28; // Type assumed.

extern VECTOR3 D_800CCA34;

extern s32 D_800CCA40; // Type assumed.

extern s32 D_800CCA4C; // Type assumed.

extern VECTOR3 D_800CCA58;

/** Character name. */
extern char* D_800CCA64;

extern u16 D_800DE124;

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

void Gfx_LoadingScreen_StageString();

/** Event function. */
void func_800DBAA0();

void Event_PocketRadioItemTake();

void Event_FlashlightItemTake();

/** @brief Handles the Silent Hill town map pickup event in the cafe.
 *
 * Also responsible for air screamer scene setup. */
void Event_MapItemTake();

/** @brief Handles the kitchen knife pickup event. */
void Event_KitchenKnifeItemTake();

void Event_EmptyFunction();

/** @brief Handles a first aid kit or health drink pickup event. */
void Event_HealthItemTake();

/** @brief Handles the handgun pickup event. */
void Event_HandgunItemTake();

void func_800DC9C8();

void func_800DD2EC(s32 arg0);

s32 func_800D1E5C();

s32 func_800D20FC();

#endif
