#ifndef _MAPS_MAP7_S01_H
#define _MAPS_MAP7_S01_H

typedef struct
{
    u8  field_0;
    u8  unk_1[1];
    s16 field_2;
} s_800E1690;

/** Character ID. (TODO: Move to `bodyprog.h`)*/
extern s8 D_800A9945;

extern VECTOR3 D_800E00CC[]; // Assumed type.

extern u16 D_800E14E8;

extern u8 D_800E1670;
extern u8 D_800E1671;

extern s_800E1690 D_800E1690;

extern VECTOR3 D_800E2C48;
extern VECTOR3 D_800E2C58;

extern u8  D_800E2C64;
extern s32 D_800E2C68;

extern s_WorldObjectPos D_800E2C94; // Assumed type.

s32 func_800D1630();

bool func_800D238C(s32 arg0);

s32 func_800D2EA0(void);

void func_800D6810(s32 arg0);

void func_800D6844(s32 arg0);

void func_800D68F8(void);

void func_800D725C(void);

void func_800D7A60(void);

void func_800D8230(void);

void func_800D82C4(void);

void func_800D8358(void);

void func_800D83EC(void);

void func_800D8958(void);

void func_800D89D8(void);

void func_800D8A04(void);

void func_800D8A30(void);

void func_800D8FCC(void);

void func_800D93BC(void);

void func_800D93E8(void);

void func_800D9414(void);

void func_800D9440(void);

void func_800D946C(void);

void func_800D94A4(void);

void func_800D99DC(void);

void func_800DAD7C(void);

void func_800DADA8(void);

void func_800DADD4(void);

void func_800DAE00(void);

void func_800DC080(void);

void func_800DEDA4(void);

#endif
