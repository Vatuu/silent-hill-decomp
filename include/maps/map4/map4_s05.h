#ifndef _MAPS_MAP4_S05_H
#define _MAPS_MAP4_S05_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk109

extern s32 D_800D7858;

extern q3_12 D_800D785C;

extern s_AnimInfo FLOATSTINGER_ANIM_INFOS[];

extern VECTOR3 D_800DB938;

extern VECTOR3 D_800DB948;

extern s32 D_800DB954;

extern s_FsImageDesc D_800D7D64;

extern s32 D_800D7D6C;

extern s16 D_800D7D70;

extern u16 D_800D7D74;

extern VECTOR3 D_800D7D88;

extern u8 D_800D7D94;

extern u8 D_800D7D95;

extern s32 D_800D7D6C;

extern s16 D_800D7D80;

extern u8 D_800D7D82;

extern s16 D_800DB898;

extern s16 D_800DB89C;

extern s16 D_800DB8A8[];

extern GsCOORDINATE2* D_800DB928;

void Ai_Floatstinger_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Floatstinger_Init(s_SubCharacter* chara);
void func_800D1968(s_SubCharacter*);
void func_800D1B98(s_SubCharacter*);
void func_800D35F0(s_SubCharacter*);
void func_800D37E8(s_SubCharacter*, s_AnmHeader*);
void func_800D3AD4(s_SubCharacter*);

void func_800D6800(void);

void func_800D6BC0(void);

#endif
