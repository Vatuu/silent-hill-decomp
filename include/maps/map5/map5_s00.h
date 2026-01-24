#ifndef _MAPS_MAP5_S00_H
#define _MAPS_MAP5_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk87
#define HAS_PlayerState_Unk88
#define HAS_PlayerState_Unk114
#define KEYFRAME_PlayerState_Unk59 831
#define KEYFRAME_PlayerState_Unk60 846
#define KEYFRAME_PlayerState_Unk87 857
#define KEYFRAME_PlayerState_Unk88 894

typedef struct
{
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s8  unk_A;
    u8  field_B;
    u16 field_C;
    u8  field_E;
    s8  unk_F;
    s8  unk_10[4];
} s_800DAB90;

extern s32 D_800DAB78;

extern u8 D_800DAB7C[3];

extern s_WorldObjectDesc  g_WorldObject_Map;
extern s_WorldObjectDesc  g_WorldObject_SavePad0;
extern s_WorldObjectDesc  g_WorldObject_SavePad1;
extern s_WorldObjectModel g_CommonWorldObjects[6];

extern s_800DAB90 D_800DAB90[];

void func_800CB0D8(void);

s32 func_800D63DC(s32* screenXy);

void func_800D6414(void);

void func_800D6490(VECTOR3*);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Handles the Sewer Key item pickup event. */
void MapEvent_SewerKeyTake(void);

void func_800D6B00(void);

void func_800D732C(void);

// Next 4 functions are all very similar to each other, only differ in Q12 position values and flag numbers.
void func_800D75FC(void);
void func_800D7940(void);
void func_800D7C84(void);
void func_800D7F88(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

void Map_WorldObjectsInit(void);

bool func_800CB25C(POLY_FT4** arg0, s32 arg1);

#endif
