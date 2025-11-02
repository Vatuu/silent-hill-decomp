#ifndef _MAPS_MAP1_S06_H
#define _MAPS_MAP1_S06_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 678
#define KEYFRAME_PlayerState_Unk60 693

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern u8 D_800D71E8[];

extern u8 D_800D7761;

/** Time. */
extern q3_12 D_800DAF78;

extern s_WorldObjectDesc D_800DAF84;

extern s_WorldObjectDesc D_800DAFB4;

extern s_WorldObjectDesc D_800DAFF4;

extern s_WorldObjectDesc D_800DB024;

extern s_WorldObjectDesc D_800DB064;

extern u8 D_800DAFE4;

/** Related to stereo sound balance. */
extern s8 D_800DB054;

/** Stereo sound balance. */
extern s8 D_800DB055;

extern u8 D_800D778D;

extern u8 D_800D778E;

extern u8 D_800D778F;

extern u8 D_800D7790;

extern s16 D_800D6E2E;

void func_800D2270(s_SubCharacter* chara);

void func_800D2CC8(s_SubCharacter* chara);

void func_800D30F0(s_SubCharacter* chara);

void func_800D4FC0(s32 arg0, s32 arg1);

void func_800D5400(void);

void func_800D5B98(void);

void func_800D5D6C(u16 arg0);

void func_800D5DD8(void);

void func_800D6338(void);

void func_800D63B0(void);

void Map_WorldObjectsInit(void);

void func_800D6578(void);

void func_800D6C88(void);

s32 func_800D4FE4(s_SubCharacter* chara, s32 moveSpeed);

#endif
