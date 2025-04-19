#ifndef _MAP0_S00_H
#define _MAP0_S00_H

#include "common.h"

extern u8 D_800DD59C;

extern s32 D_800E3A30;

void func_800D0124();

void sharedFunc_800D0E04_0_s00();

void func_800D0E24();

void func_800D0E2C();

void func_800D209C();

void func_800D20E4();

void sharedFunc_800D20D8_0_s00();

void func_800D2C7C(s32 arg0);

void sharedFunc_800D2D2C_0_s00();

void sharedFunc_800D2D44_0_s00();

s32 sharedFunc_800D2D6C_0_s00();

void sharedFunc_800D2D84_0_s00();

/** Triggers at specific points after the start of a cutscene or dialogue. */
s32 sharedFunc_800D2E50_0_s00();

void sharedFunc_800D2E60_0_s00();

void func_800D2E6C();

void func_800D2E74();

void func_800D2E7C();

void func_800D2E84();

void func_800D2E8C();

s32 func_800D2E94();

void func_800D2E9C();

u8 sharedFunc_800D2EA4_0_s00();

void func_800D2EB4();

void func_800D2EF4();

void func_800D4924();

void func_800D654C();

void func_800D8888(s_SubCharacter* chara);

// TODO: sharedFuncs could go in their own header.

void sharedFunc_800D88AC_0_s00(s_SubCharacter* playerChara);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void func_800D88C0(s_SubCharacter* playerChara, s32 arg1);

void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* playerChara);

void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

void sharedFunc_800D923C_0_s00(s_SubCharacter* playerChara);

s32 func_800D929C();

void func_800DBE00();

#endif
