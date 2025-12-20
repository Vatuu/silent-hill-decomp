#ifndef _LIBUNK_H
#define _LIBUNK_H

// Konami library for handling DualShock vibration?
// Built with 2.7.2-970404 / 2.7.2-cdk compiler.

/** Based on LIBOVR.PDF `Buffer Data Format` section. */
typedef enum _PadTerminalType
{
    PadTerminalType_Mouse               = 1,
    PadTerminalType_16ButtonAnalog      = 2,
    PadTerminalType_GunControllerKonami = 3,
    PadTerminalType_16Button            = 4,
    PadTerminalType_AnalogJoystick      = 5,
    PadTerminalType_GunControllerNamco  = 6,
    PadTerminalType_AnalogController    = 7,
    PadTerminalType_MultitapAdapter     = 8
} e_PadTerminalType;

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
    struct _s_SysWork_2514_18* prev_4;
    u8                         unk_8[4];
    s32                        field_C;
    u8                         unk_10[8];
    u8                         unk_18[4];
    u16                        field_1C;
    u16                        field_1E;
} s_SysWork_2514_18;

typedef struct
{
    u32 padPort_0_0 : 8;
    u8  field_0_8   : 8;
    u32 field_0_16  : 1;
    u32 field_0_17  : 1;
    u32 field_0_18  : 1;
    u32 field_0_19  : 3;
    u32 field_0_22  : 1;
    u32 field_0_23  : 1;
    u32 field_0_24  : 8;
} s_SysWork_2514_0;

typedef struct
{
    s_SysWork_2514_0   field_0;
    s32                field_4;
    s16                field_8;
    s8                 field_A;
    u8                 unk_B[1];
    s_SysWork_2514_C*  field_C;
    s_SysWork_2514_18* field_10;
    s32                unk_14;
    s_SysWork_2514_18  head_18;
} s_SysWork_2514;
STATIC_ASSERT_SIZEOF(s_SysWork_2514, 56);

// Controller node?
typedef struct _s_SysWork_2510
{
    struct _s_SysWork_2510* next_0;
    u8                      key_4;
    u8                      pad_5[3];
    s32                     field_8;
    s32                     (*func_C)(s_SysWork_2514*, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);
} s_SysWork_2510;
STATIC_ASSERT_SIZEOF(s_SysWork_2510, 16);

bool func_8009E3B0(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);

bool func_8009E438(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);

s_SysWork_2510* func_8009E4F8(void);

s_SysWork_2510* func_8009E520(s_SysWork_2510* node, s32 key);

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* node);

bool func_8009E7D8(s_SysWork_2510* node);

s32 func_8009E82C(s_SysWork_2514*, s32, s32, s32);

bool func_8009E97C(s_SysWork_2510* node);

s32 func_8009E9D0(s_SysWork_2514*, s32, s32, s32);

bool func_8009EBB8(s_SysWork_2514* list, s_SysWork_2514_18* node, s32 count);

bool func_8009EC1C(s_SysWork_2514* list, s_SysWork_2514_18* node);

s_SysWork_2514_18* func_8009ED74(s_SysWork_2514* list);

s_SysWork_2514_18* func_8009ED7C(s_SysWork_2514_18* node);

s_SysWork_2514_18* func_8009ED90(s_SysWork_2514_18* node);

#endif
