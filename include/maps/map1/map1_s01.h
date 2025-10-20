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

extern s_AnimInfo CAT_ANIM_INFOS[];

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D72B0(void);

void func_800D72DC(void);

void func_800D7830(void);

void func_800D7EEC(void);

void func_800D857C(void);

void func_800D8794(void);

#endif
