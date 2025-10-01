#ifndef _MAPS_MAP0_S01_H
#define _MAPS_MAP0_S01_H

#include "bodyprog/bodyprog.h"
#include "maps/shared.h"
#include "game.h"
#include "types.h"

extern s8 D_800CBAD4;

extern u16 D_800DE124;

extern u16 D_800DE128;

extern s_WorldObjectPos D_800DE12C;

extern s_WorldObjectPos D_800DE140;

extern VECTOR3 D_800DE154;

extern q19_12 g_Timer0; // 0x800E239C

extern u8 g_MapMsgSoundIdx; // 0x800E23A0

extern u8 D_800E23A1;

extern VECTOR3 g_CutsceneCameraPositionTarget; // 0x800E2380

extern VECTOR3 g_CutsceneCameraLookAtTarget; // 0x800E2390

extern s_WorldObject_0 D_800E23B0[1];
extern s_WorldObject_0 D_800E23D0[1];
extern s_WorldObject_0 D_800E23F0[3];
extern s_WorldObject_0 D_800E2450[2];

extern VECTOR3 g_CutscenePosition; // 0x800E2490
extern s_WorldObjectDesc g_EventThing_KitchenKnife; // 0x800E24A0
extern s_WorldObjectDesc g_EventThing_Flashlight; // 0x800E24D0
extern s_WorldObjectDesc g_EventThing_Map; // 0x800E2500
extern s_WorldObjectDesc g_EventThing_PocketRadio; // 0x800E2530

extern s16 D_800E2560;

extern s_WorldObject_0 g_CommonWorldObjects[];

extern u16 g_MapMsgSounds[];

extern u8 D_800DE250;

extern u8 D_800DE251;

void func_800D16C4(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s_SubCharacter* chara);

q19_12 Model_AnimDurationGet(s_Model* model);

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

void Map_WorldObjectsInit();

void Map_WorldObjectsUpdate(void);

void CutsceneObjects_Add(s32 arg0);

s32 func_800D1E5C();

void func_800D2054(void);

void Player_FallBackward(void);

s32 func_800D20FC();

/** @brief @unused Handles the demo end screen event after the Air Screamer breaks through the cafe window. Seen in demo builds. */
void MapEvent_ToBeContinued(void);

void MapEvent_CafeCutscene();

void func_800D53AC(s_SubCharacter*);

s32 func_800D5F00(s_SubCharacter* arg0);

void sharedFunc_800D2364_0_s01(s_SubCharacter* chara);

void func_800D5638(s_SubCharacter* arg0);

void func_800D4E84(s_SubCharacter*);

void func_800D529C(s_SubCharacter* chara, s32 thousand, s32 angle);

void func_800D598C(s_SubCharacter* chara);

#endif
