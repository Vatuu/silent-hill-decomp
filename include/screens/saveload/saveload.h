#ifndef _SAVELOAD_H
#define _SAVELOAD_H

typedef struct
{
    s32 unk_0;
    s32 unk_4;
    s32 field_8; // Maybe bitfield.
} s_UnkSaveload0; // Size: >=12

extern s_FsImageDesc D_800A902C;
extern u8            D_800A97D4[];
extern s8            D_800A97D8;
extern s32           D_800B9FE0[];
extern u32           D_800BCD34;
extern s8            D_800BCD39;
extern s8            D_800BCD40;
extern s32           D_801E751C;
extern s32           D_801E7520;
extern s16           D_801E7570[];
extern s16           D_801E7578[];
extern s8            D_801E76D0;

void func_801E2F90(s32 idx);

s32 func_801E3078(s_UnkSaveload0* arg0);

void func_801E63C0(void);

void func_801E709C(void);

void func_801E7244(void);

void func_801E72DC(void);

#endif
