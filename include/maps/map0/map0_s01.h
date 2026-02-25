#ifndef _MAPS_MAP0_S01_H
#define _MAPS_MAP0_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk71
#define HAS_PlayerState_Unk132
#define HAS_PlayerState_Unk76
#define HAS_PlayerState_Unk77
#define HAS_PlayerState_Unk78
#define HAS_PlayerState_Unk89
#define HAS_PlayerState_Unk90
#define HAS_PlayerState_Unk91
#define HAS_PlayerState_Unk92
#define HAS_PlayerState_Unk93
#define HAS_PlayerState_Unk110

#define HAS_Chara_Cybil
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

#define MAP_FIELD_4C_COUNT 300
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern u16 g_MapMsgSounds[]; // 0x800DE0CC

extern u16 D_800DE124;

extern u16 D_800DE128;

extern s_WorldObjectPose D_800DE12C;

extern s_WorldObjectPose D_800DE140;

extern VECTOR3 D_800DE154;

extern u8 D_800DE250;

extern u8 D_800DE251;

extern VECTOR3 g_CutsceneCameraPositionTarget; // 0x800E2380

extern VECTOR3 g_CutsceneCameraLookAtTarget; // 0x800E2390

extern q19_12 g_Timer0; // 0x800E239C

extern u8 g_MapMsgSoundIdx; // 0x800E23A0

extern u8 D_800E23A1;

extern s_WorldObjectModel D_800E23B0[1];
extern s_WorldObjectModel D_800E23D0[1];
extern s_WorldObjectModel D_800E23F0[3];
extern s_WorldObjectModel D_800E2450[2];

extern VECTOR3 g_CutscenePosition; // 0x800E2490
extern s_WorldObjectDesc g_EventThing_KitchenKnife; // 0x800E24A0
extern s_WorldObjectDesc g_EventThing_Flashlight; // 0x800E24D0
extern s_WorldObjectDesc g_EventThing_Map; // 0x800E2500
extern s_WorldObjectDesc g_EventThing_PocketRadio; // 0x800E2530

extern s16 D_800E2560;

extern s_WorldObjectModel g_CommonWorldObjects[]; // 0x800E2570

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s_SubCharacter* chara);

void func_800D426C(s_SubCharacter* chara);

void func_800D4420(s_SubCharacter* chara);

void func_800D45BC(s_SubCharacter* chara);

q19_12 Model_AnimDurationGet(s_Model* model);

/** @brief Handles the Air Screamer cutscene in the cafe. */
void MapEvent_AirScreamerIntroCutscene(void);

/** @brief Handles the Pocket Radio item pickup event. */
void MapEvent_PocketRadioItemTake(void);

/** @brief Handles the Flashlight item pickup event. */
void MapEvent_FlashlightItemTake(void);

/** @brief Handles the Silent Hill town map pickup event in the cafe.
 *
 * Also responsible for air screamer scene setup.
 */
void MapEvent_MapItemTake(void);

/** @brief Handles the Kitchen Knife item pickup event. */
void MapEvent_KitchenKnifeItemTake(void);

void MapEvent_EmptyFunction(void);

/** @brief Handles a First Aid Kit or Health Drink item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Handles the Air Screamer death event. */
void MapEvent_AirScreamerDeath(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void CutsceneObjects_Add(s32 arg0);

void func_800D46C4(s_SubCharacter* chara);

void func_800D5638(s_SubCharacter* chara);

void func_800D4E84(s_SubCharacter*);

void func_800D529C(s_SubCharacter* chara, q19_12 arg1, q19_12 angle);

void MapEvent_CafeCutscene(void);

/** @brief @unused Handles the demo end screen event after the Air Screamer breaks through the cafe window. Seen in demo builds. */
void MapEvent_ToBeContinued(void);

void func_800D49B0(s_SubCharacter* chara);

void func_800D4894(s_SubCharacter* chara);

void func_800D598C(s_SubCharacter* chara);

#endif
