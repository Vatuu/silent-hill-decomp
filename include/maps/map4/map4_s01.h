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

typedef struct _MapHeader_field_5C
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    u8  field_4;
    u8  field_5;
    u8  field_6;
    u8  field_7;
    s16 field_8;
    s16 field_A;
    u16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    u16 field_1C;
    s16 field_1E;
    s32 field_20;
    s32 field_24;
} s_mMpHeader_field_5C;

extern s_MapHeader_field_54 D_800D5B20[450];
extern s_MapHeader_field_5C D_800D7F20;

extern u16 g_MapMsgSounds[84];
extern u16 g_MapMsgSounds1[4];
extern u16 g_MapMsgSounds2[2];
extern u8 g_MapMsgSoundIdx;
extern u8 g_MapMsgSoundIdx1;
extern u8 g_MapMsgSoundIdx2;
extern u8 D_800D5AEB;
extern u8 D_800D5AF0;
extern s32 g_Timer0;
extern s32 g_Timer1;
extern s32 g_Timer2;
extern VECTOR3 g_CutsceneCameraPosition;
extern VECTOR3 g_CutsceneCameraLookAt;

extern s_WorldObjectDescNoRot WorldObject_D_800D7FF0;
extern u8 D_800D8018;
extern s_WorldObjectDesc WorldObject_D_800D8020;
extern s_WorldObjectDesc WorldObject_D_800D8050;
extern s_WorldObjectPose WorldObject_D_800D8070;
extern s_WorldObjectPose WorldObject_D_800D8090;
extern s_WorldObjectDesc WorldObject_D_800D80B0;
extern s_WorldObjectDescNoRot WorldObject_D_800D80E0[2];
extern s16 D_800D5AE8;

void func_800D1B78(s32 arg0);

void func_800D1FF0(void);

void func_800D496C(void);

void func_800D4998(void);

void func_800D49C4(void);

void func_800D4BA4(void);

void func_800D2408(void);

void func_800D4410(void);

void func_800CC2C4(s32 arg0, s32 arg1);

#endif
