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
    u32 bits_0_0   : 8;
    u32 bits_0_8   : 1;
    u32 bits_0_9   : 7;

    u32 bits_0_16  : 3;
    u32 bits_0_19  : 5;

    u32 bits_0_24  : 3;
    u32 bits_0_27  : 5;
} s_SysWork_2514_C_0;

typedef union
{
    s_SysWork_2514_C_0 flags;
    s32                value;
} u_SysWork_2514_C_0;

typedef struct
{
    s_SysWork_2514_C_0 flags;
    s32                data_4;
} s_SysWork_2514_C;

typedef struct _s_SysWork_2514_18
{
    struct _s_SysWork_2514_18* next_0;
    struct _s_SysWork_2514_18* prev_4;
    u_SysWork_2514_C_0         key_8;
    s32                        field_C;
    u8                         unk_10[8];
    struct _s_SysWork_2514_18* unk_18;
    u16                        field_1C;
    u16                        field_1E;
} s_SysWork_2514_18;

typedef struct
{
    u32 padPort_0_0 : 8;
    u32 field_0_8   : 8;
    u32 field_0_16  : 1;
    u32 field_0_17  : 1;
    u32 field_0_18  : 1;
    u32 field_0_19  : 3;
    u32 field_0_22  : 1;
    u32 field_0_23  : 1;
    u32 field_0_24  : 8;
} s_SysWork_2514_0;

// Related to controller data?
typedef struct
{
    s_SysWork_2514_0   field_0;
    s32                actuatorData_4;
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
    s8                      pad_5[3];
    s32                     field_8;
    s32                     (*func_C)(s_SysWork_2514* ptr, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);
} s_SysWork_2510;
STATIC_ASSERT_SIZEOF(s_SysWork_2510, 16);

// Exception, as one of the unidentified structs uses this.
typedef struct _s_8002AC04
{
    struct _s_8002AC04* field_0;

    union
    {
        u8 funcIdx_4; // `funcIdx_4` in structs below, needs to be part of those structs for match.

        struct
        {
            u8  funcIdx_4;
            u8  field_5;
            u16 field_6;
            s32 field_8;
            u32 field_C;
        } func_8008973C_data;
        struct
        {
            u8  funcIdx_4;
            u8  field_5;
            u16 field_6;
            s32 field_8;
            u32 field_C;
        } func_80089D0C_data;

        struct
        {
            u8                  funcIdx_4;
            u8                  field_5   : 7;
            u32                 field_5_7 : 1;
            u16                 field_6;
            struct _s_8002AC04* field_8;
            u32                 field_C;
        } func_80089BB8_data;

        struct
        {
            u8  funcIdx_4;
            u8  field_5;
            u16 field_6;
            u8* field_8;
            u32 field_C_0  : 16;
            u32 field_C_16 : 12;
            u32 field_C_28 : 3;
            u32 field_C_31 : 1;
        } func_80089DF0_data;
        struct
        {
            u8  funcIdx_4;
            u8  field_5_0 : 5;
            u32 field_5_5 : 1;
            u32 field_5_6 : 1;
            u32 field_5_7 : 1;
            u16 field_6;
            s32 field_8;
            u32 field_C;
        } func_80089A30_data;
    } field_4;
} s_8002AC04;
STATIC_ASSERT_SIZEOF(s_8002AC04, 16);

typedef struct _func_8009ECCC
{
    struct _func_8009ECCC* field_0; // TODO: Not sure if these point to other struct type or same type.
    struct _func_8009ECCC* field_4;
    s32                    field_8;
    s32                    field_C;
    s_8002AC04*            field_10;
    u32                    field_14_0  : 16;
    u32                    field_14_16 : 8;
    u32                    field_14_24 : 7;
    u32                    field_14_31 : 1;
    u32                    field_18;
    u16                    field_1C;
    u16                    field_1E;
} s_func_8009ECCC;

s32 func_8009E230(s_SysWork_2514* arg0);

s32 func_8009E268(s_SysWork_2514* arg0);

s32 func_8009E2A0(s_SysWork_2514* arg0);

s32 func_8009E2D8(s_SysWork_2514* arg0);

s32 func_8009E310(s_SysWork_2514* arg0, s_SysWork_2514_C* arg1, s32 arg2);

bool func_8009E3B0(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);

bool func_8009E438(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId);

s_SysWork_2510* func_8009E4F8(void);

s_SysWork_2510* func_8009E520(s_SysWork_2510* node, s32 key);

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* node);

bool func_8009E61C(s_SysWork_2514* arg0, s32 state, s_SysWork_2510* head);

bool func_8009E718(s_SysWork_2514* arg0);

bool func_8009E7D8(s_SysWork_2510* node);

bool func_8009E82C(s_SysWork_2514*, s32, s32, s32);

bool func_8009E97C(s_SysWork_2510* node);

bool func_8009E9D0(s_SysWork_2514* work, s32 padState, s_SysWork_2514_C* arg2, s32 arg3);

bool func_8009EBB8(s_SysWork_2514* list, s_SysWork_2514_18* node, s32 count);

bool func_8009EC1C(s_SysWork_2514* list, s_SysWork_2514_18* node);

/** @brief Ensures a node in a linked list is sorted based on its key value. */
bool func_8009EC64(s_SysWork_2514* work, s16 val);

s_SysWork_2514_18* func_8009ECCC(s_SysWork_2514* arg0, s32 key);

s_SysWork_2514_18* func_8009ED74(s_SysWork_2514* list);

s_SysWork_2514_18* func_8009ED7C(s_SysWork_2514_18* node);

s_SysWork_2514_18* func_8009ED90(s_SysWork_2514_18* node);

#endif
