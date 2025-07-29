#ifndef _MAP0_S00_H
#define _MAP0_S00_H

#include "common.h"

typedef struct {
    VECTOR3 pos1_0;
    VECTOR3 pos2_C;
} s_800E32DC;

extern s_800E32DC D_800E32DC;

/** "STAGE 0-0" string */
extern char D_800CAE7C[];

extern s32 D_800E3A30;

void func_800D0124();

/** @brief Lazy player XZ distance check against two positions
 *
 * Seems to be a lazy XZ distance check below a constant distance of 40.0
 * Instead of: (x1 - x2) * (x1 - x2) + (z1 - z2) * (z1 - z2) < (d * d)
 * it does:    abs(x1 - x2) + abs(z1 - z2) < d
 *
 * Compares the player position against two other positions
 * @return 1 if the player distance from either position is < 40.0, otherwise 0
 */
s32 func_800D0600();

void func_800D0E24();

void func_800D0E2C();

void func_800D2E6C();

void func_800D2E74();

void func_800D2E7C();

void func_800D2E84();

void func_800D2E8C();

s32 func_800D2E94();

void func_800D2E9C();

void func_800D4924();

void func_800D654C();

void Ai_Cheryl_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords); // 0x800D7FB8

void func_800D802C(s_SubCharacter*, s32, GsCOORDINATE2*); // `Chara_Cheryl` related.

void func_800D8124(s_SubCharacter*, GsCOORDINATE2*); // `Chara_Cheryl` related.

void func_800D8310(s_SubCharacter*, GsCOORDINATE2*); // `Chara_Cheryl` related.

void Ai_Cheryl_Init(s_SubCharacter* chara); // 0x800D8888

s32 func_800D929C();

void func_800D95D4();

void func_800DBE00();

#endif
