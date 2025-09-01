#ifndef _MAP0_S01_H
#define _MAP0_S01_H

#include "bodyprog/bodyprog.h"
#include "maps/shared.h"
#include "game.h"
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

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 vector_C;
} s_2Vectors;

extern s32 D_800DD798;

extern s32 D_800DE160;

extern s32 D_800DE164;

extern s_Particle g_Particles[300];

extern s32 D_800E214C;

extern s32 D_800E2150;

extern s_2Vectors D_800E2160;

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s8 D_800CBAD4;

extern u16 D_800DE124;

extern u16 D_800DE128;

extern s32 g_Timer0;

extern u8 g_SoundCmdIdx;

extern u8 D_800E23A1;

extern VECTOR3 g_CutsceneCameraPositionTarget;

extern VECTOR3 g_CutsceneCameraLookAtTarget;

extern s16 D_800E2560;

/** Size might be 6. Possibly related to NPCs. */
extern s_800BCE18_2BEC_0 D_800E2570[];

extern u16 g_SoundCmds[];

extern u8 D_800DE250;

extern u8 D_800DE251;

void func_800CE000(s32 arg1, s32 arg2, s32 arg3);

void func_800D16C4(s_SubCharacter* arg0, s_MainCharacterExtra* arg2, GsCOORDINATE2* arg3);

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s_SubCharacter* chara);

void func_800D3CC4(s_SubCharacter* chara);

void func_800D3DFC(s_SubCharacter* chara);

void func_800D7E88(s_Model* model);

void func_800DA778(s32 arg0);

void func_800DA7AC();

void func_800DA7FC();


void Gfx_LoadingScreen_StageString();

/** @brief Handles the Air Screamer cutscene in the cafe. */
void Event_AirScreamerIntroCutscene();

/** @brief Handles the pocket radio item pickup event. */
void Event_PocketRadioItemTake();

/** @brief Handles the flashlight item pickup event. */
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

/** @brief Handles the Air Screamer death event. */
void Event_AirScreamerDeath();

void func_800DC9C8();

void func_800DD2EC(s32 arg0);

s32 func_800D1E5C();

void func_800D2054(void);

void Player_FallBackward(void);

s32 func_800D20FC();

/** @brief @unused Handles the demo end screen event after the Air Screamer breaks through the cafe window. Seen in demo builds. */
void Event_ToBeContinued(void);

void Event_CafeCutscene();

#endif
