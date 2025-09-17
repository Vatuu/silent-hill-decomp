#ifndef _MAPS_MAP0_S01_H
#define _MAPS_MAP0_S01_H

#include "bodyprog/bodyprog.h"
#include "maps/shared.h"
#include "game.h"
#include "types.h"

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 vector_C;
} s_2Vectors;

extern s32 D_800DD798;

extern s32 D_800DE160;

extern s32 D_800DE164;

extern CVECTOR D_800E214C;

extern CVECTOR D_800E2150;

extern s_2Vectors D_800E2160;

extern s8 D_800CBAD4;

extern u16 D_800DE124;

extern u16 D_800DE128;

extern s_EventPosition D_800DE12C;

extern s_EventPosition D_800DE140;

extern VECTOR3 D_800DE154;

extern s32 g_Timer0; // 0x800E239C

extern u8 g_SoundCmdIdx; // 0x800E23A0

extern u8 D_800E23A1;

extern VECTOR3 g_CutsceneCameraPositionTarget; // 0x800E2380

extern VECTOR3 g_CutsceneCameraLookAtTarget; // 0x800E2390

extern s_800BCE18_2BEC_0 D_800E23B0[1];
extern s_800BCE18_2BEC_0 D_800E23D0[1];
extern s_800BCE18_2BEC_0 D_800E23F0[3];
extern s_800BCE18_2BEC_0 D_800E2450[2];

extern s_EventPosition g_DefaultEventPosition; // 0x800E2490
extern s_EventThing g_EventThing_KitchenKnife; // 0x800E24A0
extern s_EventThing g_EventThing_Flashlight; // 0x800E24D0
extern s_EventThing g_EventThing_Map; // 0x800E2500
extern s_EventThing g_EventThing_PocketRadio; // 0x800E2530

extern s16 D_800E2560;

extern s_800BCE18_2BEC_0 D_800E258C;

/** Size might be 6. Possibly related to NPCs. */
extern s_800BCE18_2BEC_0 D_800E2570[];

extern u16 g_SoundCmds[];

extern u8 D_800DE250;

extern u8 D_800DE251;

void func_800CE000(s32 arg1, s32 arg2, s32 arg3);

void func_800D16C4(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s_SubCharacter* chara);

void func_800D3CC4(s_SubCharacter* chara);

void func_800D3DFC(s_SubCharacter* chara);

q19_12 func_800D7E88(s_Model* model);

void func_800DA778(s32 arg0);

void func_800DA7AC();

void func_800DA7FC();

void Gfx_LoadingScreen_StageString();

/** @brief Handles the Air Screamer cutscene in the cafe. */
void MapEvent_AirScreamerIntroCutscene();

/** @brief Handles the pocket radio item pickup event. */
void MapEvent_PocketRadioItemTake();

/** @brief Handles the flashlight item pickup event. */
void MapEvent_FlashlightItemTake();

/** @brief Handles the Silent Hill town map pickup event in the cafe.
 *
 * Also responsible for air screamer scene setup. */
void MapEvent_MapItemTake();

/** @brief Handles the kitchen knife pickup event. */
void MapEvent_KitchenKnifeItemTake();

void MapEvent_EmptyFunction();

/** @brief Handles a first aid kit or health drink pickup event. */
void MapEvent_CommonItemTake();

/** @brief Handles the Air Screamer death event. */
void MapEvent_AirScreamerDeath();

void func_800DC9C8();

void func_800DCCF4(void);

// Called by `func_800DCCF4` only.
void func_800DD2EC(s32 arg0);

s32 func_800D1E5C();

void func_800D2054(void);

void Player_FallBackward(void);

s32 func_800D20FC();

/** @brief @unused Handles the demo end screen event after the Air Screamer breaks through the cafe window. Seen in demo builds. */
void MapEvent_ToBeContinued(void);

void MapEvent_CafeCutscene();

#endif
