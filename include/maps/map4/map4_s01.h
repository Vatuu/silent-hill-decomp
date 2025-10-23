#ifndef _MAPS_MAP4_S01_H
#define _MAPS_MAP4_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk69
#define HAS_PlayerState_Unk105
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk116
#define HAS_PlayerState_Unk118
#define HAS_PlayerState_Unk119
#define HAS_PlayerState_Unk120
#define HAS_PlayerState_Unk121
#define HAS_PlayerState_Unk124
#define HAS_PlayerState_Unk130
#define HAS_PlayerState_Unk140
#define HAS_PlayerState_Unk142
#define HAS_PlayerState_Unk153
#define HAS_PlayerState_Unk186
#define KEYFRAME_PlayerState_Unk69 678

extern u16 g_MapMsgSounds[84];
extern u8 g_MapMsgSoundIdx;
extern u8 D_800D5AEB;
extern s32 g_Timer0;
extern VECTOR3 g_CutsceneCameraPos;
extern VECTOR3 g_CutsceneCameraLookAt;

extern s_WorldObjectDesc_norot Wobj_D_800D7FF0;
extern u8 D_800D8018;
extern s_WorldObjectDesc Wobj_D_800D8020;
extern s_WorldObjectDesc Wobj_D_800D8050;
extern s_WorldObjectPos  Wobj_D_800D8070;
extern s_WorldObjectPos  Wobj_D_800D8090;
extern s_WorldObjectDesc Wobj_D_800D80B0;
extern s_WorldObjectDesc_norot Wobj_D_800D80E0[2];

void func_800D1B78(s32 arg0);

void func_800D496C(void);

void func_800D4998(void);

void func_800D2408(void);

#endif
