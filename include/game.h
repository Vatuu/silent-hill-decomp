#ifndef GAME_H
#define GAME_H

#include "gpu.h"

extern void* g_OvlDynamic;
extern void* g_OvlBodyprog;

typedef struct _AnalogPadData
{
    u8  status;
    u8  data_format;
    u16 digitalButtons;
    u8  right_x;
    u8  right_y;
    u8  left_x;
    u8  left_y;
} s_AnalogPadData;

typedef enum _PadButton
{
    Pad_BtnSelect    = 0x1,
    Pad_BtnL3        = 0x2,
    Pad_BtnR3        = 0x4,
    Pad_BtnStart     = 0x8,
    Pad_BtnDpadUp    = 0x10,
    Pad_BtnDpadRight = 0x20,
    Pad_BtnDpadDown  = 0x40,
    Pad_BtnDpadLeft  = 0x80,
    Pad_BtnL2        = 0x100,
    Pad_BtnR2        = 0x200,
    Pad_BtnL1        = 0x400,
    Pad_BtnR1        = 0x800,
    Pad_BtnTriangle  = 0x1000,
    Pad_BtnCircle    = 0x2000,
    Pad_BtnCross     = 0x4000,
    Pad_BtnSquare    = 0x8000,
    Pad_LSUp2        = 0x10000,
    Pad_LSRight2     = 0x20000,
    Pad_LSDown2      = 0x40000,
    Pad_LSLeft2      = 0x80000,
    Pad_RSUp         = 0x100000,
    Pad_RSRight      = 0x200000,
    Pad_RSDown       = 0x400000,
    Pad_RSLeft       = 0x800000,
    Pad_LSUp         = 0x1000000,
    Pad_LSRight      = 0x2000000,
    Pad_LSDown       = 0x4000000,
    Pad_LSLeft       = 0x8000000,
} e_PadButton;

typedef struct _ControllerData
{
    s_AnalogPadData AnalogPad;
    int             field_8;
    e_PadButton     btns_held_C;
    e_PadButton     btns_new_10;
    char            field_14[4];
    e_PadButton     field_18;
    int             field_1C;
    char            field_20;
    char            field_21;
    char            field_22;
    char            field_23;
    char            field_24;
    char            field_25;
    char            field_26;
    char            field_27;
    int             field_28;
} s_ControllerData;

typedef struct _ControllerBindings
{
    u16 enter;
    u16 cancel;
    u16 skip;
    u16 action;
    u16 aim;
    u16 light;
    u16 run;
    u16 view;
    u16 step_l;
    u16 step_r;
    u16 pause;
    u16 item;
    u16 map;
    u16 option;
} s_ControllerBindings;

typedef struct _GameWork
{
    s_ControllerBindings controllerBinds_0;
    s8                   field_1C;
    s8                   field_1D;
    char                 unk_1E[9];
    u8                   extraOptionsEnabled_27;
    char                 unk_28[1];
    s8                   gameOptionsViewMode_29;
    char                 unk_2A[0xE];
    s_ControllerData     controllers_38[2];
    char                 pad90[0x4F8];
    u16                  gsScreenWidth_588;
    u16                  gsScreenHeight_58A;
    char                 unk_58C[4];
    s32                  field_590;
    s32                  field_594;
    s32                  field_598;
    s32                  field_59C;
    s32                  field_5A0;
    char                 unk_5A4[0x34];
} s_GameWork;

typedef struct _SubCharacter
{
    char    chara_type_0;
    char    field_1;
    char    field_2;
    char    field_3;
    char    flags_4[0x14];
    VECTOR3 position_18;
    SVECTOR rotation_24;
    SVECTOR rot_spd_2C;
    int     field_34;
    int     chara_mv_spd_38;
    s16     chara_mv_ang_y_3C;
    u8      pad_3E[2];
    u8      unk_40[0x128 - 0x40];
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 0x128);

typedef struct _MainCharacter
{
    s_SubCharacter c;
    u8             extra[0x2C];
} s_MainCharacter;
STATIC_ASSERT_SIZEOF(s_MainCharacter, 0x154);

typedef struct _SysWork
{
    char            unk_0[8];
    s32             field_8;
    s32             field_C;
    s32             field_10;
    s32             field_14;
    char            unk_18[4];
    s32             field_1C;
    s32             field_20;
    s32             field_24;
    s32             field_28;
    s32             field_2C;
    char            unk_30[0x1C];
    s_MainCharacter player_4C;
    char            unk_1A0[0x930 - 0x1A0];
    GsCOORDINATE2   hero_neck_930;
    char            unk_980[0x22A4 - 0x980];
    s32             field_22A4;
    char            unk_22A8[0xD2];
    s16             cam_ang_y_237A;
    s16             cam_ang_z_237C;
    s16             field_237E;
    int             cam_r_xz_2380;
    int             cam_y_2384;
    // more follows
} s_SysWork;

extern s_GameWork  g_GameWork;
extern s_SysWork   g_SysWork;
extern s_GameWork *g_pGameWork;

extern s_ControllerData *g_pController1;
extern s_ControllerData *g_pController2;
extern s_GameWork       *g_pGameWork0;

extern s32 g_CurDeltaTime;

#endif
