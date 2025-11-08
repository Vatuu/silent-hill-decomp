#ifndef _MAPS_MAP1_S05_H
#define _MAPS_MAP1_S05_H

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

typedef struct
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    u8  field_4;
    u8  field_5;
    u8  field_6;
    u16 field_8;
    u16 field_A;
    u16 field_C;
    s16 field_E;
    u16 field_10;
    s16 field_12;
    s16 field_14;
    u8  unk_16[6];
    u16 field_1C;
    u16 field_1E;
    u32 field_20;
    u32 field_24;
} s_800D8568;

extern u16 D_800D86F8[2];
extern u8 D_800D86FC[2];
extern s_800D8568 D_800D8568;

extern u8 D_800D5C3C;
extern s16 D_800D5880;
extern s8 D_800D86FE;
extern s_MapHdr_field_4C g_MapHdr_Table_4C[500];
extern s_WorldObjectDesc g_WorldObject0; //800D8698
extern s_WorldObjectDesc g_WorldObject1; //800D86C8

void func_800CAAD0(void);

s32 func_800CF7A4(void);

void func_800D263C(s_SubCharacter* chara);

void func_800D450C(s32 arg0, s32 arg1);

void func_800D17BC(s_SubCharacter* chara);

s32 func_800D4530(s_SubCharacter* chara);

s32 func_800D4530(s_SubCharacter* chara);

void func_800D494C(void);

void func_800D525C(void);

#endif
