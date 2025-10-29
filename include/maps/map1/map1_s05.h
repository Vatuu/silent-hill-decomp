#ifndef _MAPS_MAP1_S05_H
#define _MAPS_MAP1_S05_H

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern u8 D_800D5C3C;
extern s16 D_800D5880;
extern s_MapHdr_field_4C g_MapHdr_Table_4C[500];

s32 func_800CF7A4();

void func_800D263C(s_SubCharacter* chara);

void func_800D450C(s32 arg0, s32 arg1);

void func_800D17BC(s_SubCharacter* chara);

s32 func_800D4530(s_SubCharacter* chara);

s32 func_800D4530(s_SubCharacter* chara);

void func_800D494C(void);

#endif
