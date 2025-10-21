#ifndef _MAPS_MAP2_S01_H
#define _MAPS_MAP2_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk111
#define HAS_PlayerState_Unk113
#define KEYFRAME_PlayerState_Unk113 723

extern s_800C4590 D_800D16BC;
extern u16 g_MapMsgSounds[20];
extern q19_12 g_Timer0;
extern VECTOR3 g_CameraPositionTarget;
extern VECTOR3 g_CameraLookAtTarget;
extern u8 g_MapMsgSoundIdx;

extern s8 D_800CFDE3;
extern s32 D_800CFDE4;
extern s32 D_800D053C;
extern s32 D_800D0540;
extern s_ParticleVectors D_800D164C;
extern s_ParticleVectors D_800D167C;

void func_800CB010(s32 arg0, s32 arg1, s32 arg2);

void func_800CE858(s32 arg0);

void func_800CED44(void);

void func_800CED88(void);

void func_800CF798(void);

void func_800CF7C4(void);

void func_800CE88C(void);

void func_800CEB9C(void);

void func_800CEC30(void);

#endif
