#ifndef _MAP0_S01_H
#define _MAP0_S01_H

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s16 field_10;
    s8  unk_12[8];
} s_800E2490;

typedef struct
{
    s8  unk_0[8];
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} s_800A99E4;

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s8 D_800CBAD4;

/** Character name. */
extern char* D_800CCA64;

/** *Map `RECT`? */
extern RECT D_800CCAC8;

extern s8 D_800CCB00;

extern s8 D_800CCB0C;

extern s8 D_800CCB18;

extern s8 D_800CCB24;

extern s8 D_800CCB30;

extern s8 D_800CCB3C;

extern s8 D_800CCB48;

extern s8 D_800CCB54;

extern s8 D_800CCB60;

extern s8 D_800CCB6C;

extern s8 D_800CCB78;

extern SVECTOR3 D_800CCB84;

extern u16 D_800DE128;

extern s32 D_800E239C;

extern u8 D_800E23A0;

extern u8 D_800E23A1;

/** Target camera position for cutscene. */
extern VECTOR3 D_800E2380;

/** Target camera look-at for cutscene. */
extern VECTOR3 D_800E2390;

extern s_800BCE18_2BEC_0 D_800E23B0[];

extern s_800BCE18_2BEC_0 D_800E23D0[];

extern s_800BCE18_2BEC_0 D_800E23F0[];

extern s_800BCE18_2BEC_0 D_800E2450[];

extern s_800E2490 D_800E2490;

extern s_800E2490 D_800E24BC;

extern s_800E2490 D_800E24EC;

extern s_800E2490 D_800E251C;

extern s_800E2490 D_800E254C;

extern s16 D_800E2560;

extern s_800BCE18_2BEC_0 D_800E2570[];

/** `arg0` is a struct pointer, might be `s_SubCharacter`. */
void func_800D2364(s32 arg0);

void func_800D76A0(s_SubCharacter* chara);

void func_800D7E88(s_Model* model);

void func_800DA778(s32 arg0);

void func_800DA7AC();

void func_800DA7FC();

void func_800DA8A4();

void func_800DC34C();

void func_800DC394();

void func_800DC3C8();

void func_800DC830();

void func_800DC864();

void func_800DC8C8();

void func_800DC9C8();

void func_800DD2EC(s32 arg0);

#endif
