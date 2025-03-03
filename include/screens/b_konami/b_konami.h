#ifndef B_KONAMI_H
#define B_KONAMI_H

#include "common.h"

extern s32 D_800A8FFC; // Type assumed.
extern u32 D_800A9004; // Type assumed.
extern s32 D_800B5C7C; // Type assumed.
extern s32 D_800B9FB8;
extern u8* D_800C7018; // Pointer to graphics commands?
extern s32 D_800CA4F4;
extern s32 D_800CA4FC;
extern s32 D_800CA500;
extern s32 D_800CA504;
extern s32 D_800CA508;
extern s32 D_800CA50C;
extern s32 D_800CA510;

void func_800CA234(void);

void func_800C9FB8(void);

void func_800CA120(void);

s32  func_800CA240(s32* arg0);

void func_800CA24C(s32 arg0, s32 arg1, s32 arg2);

s32  func_800CA2B8(void);

#endif
