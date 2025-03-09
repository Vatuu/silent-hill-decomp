#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

typedef struct
{
    s32 unk_00;
    s32 unk_04;
    s32 field_08;
} s_UnkSaveload0; // Size: >=12

void func_801E2F90(s32 idx);

s32 func_801E3078(s_UnkSaveload0* arg0);

void func_801E709C(void);

void func_801E7244(void);
void func_801E72DC(void);

#endif
