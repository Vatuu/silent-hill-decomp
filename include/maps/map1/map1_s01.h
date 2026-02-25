#ifndef _MAPS_MAP1_S01_H
#define _MAPS_MAP1_S01_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk83
#define HAS_PlayerState_Unk85
#define HAS_PlayerState_Unk122
#define KEYFRAME_PlayerState_Unk59 873
#define KEYFRAME_PlayerState_Unk60 888

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

#define MAP_FIELD_4C_COUNT 300
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern s_AnimInfo CAT_ANIM_INFOS[]; // 0x800DC924

extern u8  D_800DC9FC;
extern u16 D_800DCA04[42];

extern s32 D_800DD4FC;

extern s8 g_PianoKeys[11]; // 0x800DD500

extern s8 g_PianoKeySequence[5]; // 0x800DD50C

extern s_WorldObjectPose g_CommonWorldObjectPoses[5]; // 0x800DD518

extern s32 D_800DD57C;

extern q19_12 g_PianoCursorX; // 0x800DD588

extern q19_12 g_PianoCursorY; // 0x800DD58C

extern s32 g_PianoKeyCounter; // 0x800DD590

extern s32 D_800DD594;

extern s_WorldObjectDesc g_WorldObject0; // 0x800DEF40
extern s_WorldObjectDesc g_WorldObject1; // 0x800DEF70
extern s_WorldObjectDesc g_WorldObject2; // 0x800DEFA0
extern s_WorldObjectDesc g_WorldObject3; // 0x800DEFD0

extern VECTOR3 D_800DF000;
extern VECTOR3 D_800DF010;

extern s_WorldObjectModel g_WorldObject4; // 0x800DF020
extern s_WorldObjectModel g_WorldObject5; // 0x800DF040
extern s_WorldObjectModel g_WorldObject6; // 0x800DF060
extern VECTOR3  D_800DF080;
extern s_WorldObjectDesc g_WorldObject7; // 0x800DF090
extern s_WorldObjectDesc g_WorldObject8; // 0x800DF0C0
extern s_WorldObjectDesc g_WorldObject9; // 0x800DF0F0
extern s_WorldObjectModel   g_CommonWorldObjects[6]; // 0x800DF120

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void MapEvent_DoorJammed(void);

void MapEvent_DoorLocked(void);

void MapEvent_DoorUnlocked(void);

void func_800D7214(void);

void func_800D72B0(void);

void func_800D72DC(void);

void func_800D7308(void);

void func_800D76F4(void);

void func_800D7830(void);

void func_800D7864(void);

void func_800D7EEC(void);

/** @brief Handles the piano puzzle event.
 *
 * @param playNote Play a note.
 */
void MapEvent_PianoPuzzle(bool playNote);

void func_800D857C(void);

void func_800D8794(void);

void func_800D87C0(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800D9DDC(void);

void func_800D9EC4(void);

#endif
