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

extern s32 D_800DAB78;

extern u8 D_800DAB7C[3];

void func_800D041C(s_SubCharacter* chara);

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

#endif
