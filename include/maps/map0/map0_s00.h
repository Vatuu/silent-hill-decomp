#ifndef _MAP0_S00_H
#define _MAP0_S00_H

#include "common.h"

typedef struct
{
    VECTOR3 position0_0;
    VECTOR3 position1_C;
} s_800E32DC;

extern s_800E32DC D_800E32DC;

/** "STAGE 0-0" string */
extern char D_800CAE7C[];

extern s32 D_800E3A30;

void func_800D0124();

/** @brief 2D player distance check on XZ plane.
 *
 * Checks against a constant 2D distance of `FP_METER(40.0f)` between the player and two positions.
 * This is a lazy check, i.e.
 * instead of: `(SQUARE(x1 - x2) + SQUARE(z1 - z2)) < SQUARE(d)`
 * it does:    `(ABS(x1 - x2) + ABS(z1 - z2)) < d`.
 *
 * @return `true` if the player distance from either position is `< FP_METER(40.0f)`,
 *          otherwise `false`.
 */
bool func_800D0600();

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
