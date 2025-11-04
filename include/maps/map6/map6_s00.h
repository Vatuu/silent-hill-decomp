#ifndef _MAPS_MAP6_S00_H
#define _MAPS_MAP6_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk114
#define HAS_PlayerState_Unk126
#define HAS_PlayerState_Unk127
#define HAS_PlayerState_Unk133
#define KEYFRAME_PlayerState_Unk114 956

void func_800DDBB4(s_SubCharacter* chara);

void func_800DDF34(s_SubCharacter* chara);

void func_800DE620(s_SubCharacter* chara);

void func_800DE640(s_SubCharacter* chara, s32 arg1, s32 angle);

void func_800DE660(s_SubCharacter* chara, s32* arg1, s32 arg2);

void func_800DEBE8(s_SubCharacter* chara);

void func_800DEC08(s_SubCharacter* chara);

/** @brief Handles a First Aid Kit, Health Drink, or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

#endif
