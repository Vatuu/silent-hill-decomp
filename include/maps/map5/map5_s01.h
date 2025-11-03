#ifndef _MAPS_MAP5_S01_H
#define _MAPS_MAP5_S01_H

extern s_FsImageDesc D_800A907C;

void func_800CD818(void);

void func_800DE514(s_SubCharacter* chara);

void func_800DE894(s_SubCharacter* chara);

void func_800DEF80(s_SubCharacter* chara);

void func_800DEFA0(s_SubCharacter* chara, s32 arg1, s32 angles);

void func_800DEFC0(s_SubCharacter* chara, s32* arg1, s32 arg2);

void func_800DF548(s_SubCharacter* chara);

void func_800DF568(s_SubCharacter* chara);

/** @breif Handles a First Aid Kit, Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

#endif
