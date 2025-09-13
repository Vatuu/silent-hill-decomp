#ifndef _MAPS_MAP0_S01_H
#define _MAPS_MAP0_S01_H

#include "bodyprog/bodyprog.h"
#include "maps/shared.h"
#include "game.h"
#include "types.h"

typedef struct
{
    VECTOR3 position_0;
    s32     field_C;
    s16     field_10;
    s16     __pad_12;
} s_EventPosition;

typedef struct
{
    s_800BCE18_2BEC_0 field_0;
    s_EventPosition   eventPosition_1C;
} s_EventThing;

// TODO: Move to bodyprog, other maps also read from this.
// Might just be an array of `char*`, array is in `.data` while strings inside are in `.rodata`?
typedef struct
{
    char* field_0;               // `NULL`
    char* field_4;               // "PAD_NEAR"
    char* firstAidKitName_8;     // "AIDKIT_N"
    char* healthDrinkName_C;     // "DRINK_NE"
    char* ampouleName_10;        // "AMPULE_N"
    char* handgunBulletsName_14; // "BULLET_N"
    char* shotgunShellsName_18;  // "SHELL_NE"
    char* rifleShellsName_1C;    // "SHOT_NEA"
} s_800A99E4;

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

void func_800D16C4(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

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

void func_800DD2EC(s32 arg0);

s32 func_800D1E5C();

void func_800D2054(void);

void Player_FallBackward(void);

s32 func_800D20FC();

/** @brief @unused Handles the demo end screen event after the Air Screamer breaks through the cafe window. Seen in demo builds. */
void MapEvent_ToBeContinued(void);

void MapEvent_CafeCutscene();

#endif
