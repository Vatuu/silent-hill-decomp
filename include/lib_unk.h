#ifndef _LIB_UNK_H
#define _LIB_UNK_H

// Konami library for handling DualShock vibration?
// Built with 2.7.2-970404 / 2.7.2-cdk compiler.

typedef struct
{
    s8  field_0[4];
    s32 field_4;
    s8  unk_8[4];
    s32 field_C;
} s_SysWork_2514_C;

typedef struct _s_SysWork_2514_18
{
    struct _s_SysWork_2514_18* next_0;
    s32                        field_4;
    u8                         unk_8[4];
    s32                        field_C;
    u8                         unk_10[8];
    u8                         unk_18[4];
    u16                        field_1C;
    u16                        field_1E;
} s_SysWork_2514_18;

typedef struct
{
    u32               field_0   : 8;
    u8                field_1   : 8;
    u32               field_2_0 : 1;
    u32               field_2_1 : 1;
    u32               field_2_2 : 4;
    u32               field_2_3 : 1;
    u32               field_2_4 : 1;
    u32               field_2_5 : 8;
    u8                unk_4[8];
    s_SysWork_2514_C* field_C;
    u8                unk_10[8];
    s_SysWork_2514_18 head_18;
} s_SysWork_2514;
STATIC_ASSERT_SIZEOF(s_SysWork_2514, 56);

typedef struct _s_SysWork_2510
{
    struct _s_SysWork_2510* next_0;
    u8                      key_4;
    u8                      pad_5[3];
    s32                     field_8;
    s32                     (*func_C)(void*, s32, s32, s32);
} s_SysWork_2510;
STATIC_ASSERT_SIZEOF(s_SysWork_2510, 16);

extern s_SysWork_2510 D_800B141C;
extern s_SysWork_2510 D_800B142C;

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* arg1);

bool func_8009E7D8(s_SysWork_2510* arg0);

bool func_8009E97C(s_SysWork_2510* arg0);

s_SysWork_2514_18* func_8009ED74(s_SysWork_2514* arg0);

s_SysWork_2514_18* func_8009ED7C(s_SysWork_2514_18* arg0);

s32 func_8009ED90(s_SysWork_2514_18* arg0);

#endif
