#ifndef _MAPS_MAP2_S00_H
#define _MAPS_MAP2_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 946
#define KEYFRAME_PlayerState_Unk60 961

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

extern u8 D_800F1CA8[3]; // = { 0, 1, 2 }

extern s16 D_800F22AE;

extern s16 D_800F538C[]; // } -- Might be one larger structure or array of stuff
extern s16 D_800F5344[]; // } -- I've seen more references to this general area on memory.

extern s16 D_800F228C;

extern u8 D_800F228E;

extern s32 D_800F2290;

extern u16 g_MapMsgSounds[2];

extern u8 g_MapMsgSoundIdx;

extern u8 D_800F2295;

extern s32 D_800F2298;

extern s32 D_800F229C;

extern s32 D_800F1A24;

extern s16 D_800F534E;

void func_800E7D54(void);

void MapEvent_AtWaterWorks(void);

void MapEvent_CherylsSketchbook(void);

void func_800E816C(void);

void func_800E8198(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

void MapEvent_SteelPipeTake(void);

void MapEvent_CutsceneExitCafe(void);

void MapEvent_CherylsSketchbook(void);

void MapEvent_DoghouseNote(void);

void MapEvent_DoghouseKeyTake(void);

void func_800E9A0C(void);

void func_800E9A74(void);

void func_800E9CB4(void);

void func_800EB3F4(void);

void MapEvent_KGordonKeyUse(void);

void func_800EB090(void);

void func_800EB758(void);

void func_800EB79C(void);

void func_800EB7E0(void);

void func_800EB824(s32);

s32 func_800EE518(void);

u8 func_800EE5A8(u32 arg0);

void func_800E8C0C(void);

/** @brief Handles the House Key use event. */
void MapEvent_HouseKeyUse(void);

void MapEvent_DoorOfEclipseEnter(void);

void func_800EA6E0(void);

void func_800EAD2C(void);

#endif
