#ifndef GAME_H
#define GAME_H

#include "gpu.h"

extern void* g_OvlDynamic;
extern void* g_OvlBodyprog;

typedef enum _PadButton
{
    Pad_BtnSelect    = 1 << 0,
    Pad_BtnL3        = 1 << 1,
    Pad_BtnR3        = 1 << 2,
    Pad_BtnStart     = 1 << 3,
    Pad_BtnDpadUp    = 1 << 4,
    Pad_BtnDpadRight = 1 << 5,
    Pad_BtnDpadDown  = 1 << 6,
    Pad_BtnDpadLeft  = 1 << 7,
    Pad_BtnL2        = 1 << 8,
    Pad_BtnR2        = 1 << 9,
    Pad_BtnL1        = 1 << 10,
    Pad_BtnR1        = 1 << 11,
    Pad_BtnTriangle  = 1 << 12,
    Pad_BtnCircle    = 1 << 13,
    Pad_BtnCross     = 1 << 14,
    Pad_BtnSquare    = 1 << 15,
    Pad_LSUp2        = 1 << 16,
    Pad_LSRight2     = 1 << 17,
    Pad_LSDown2      = 1 << 18,
    Pad_LSLeft2      = 1 << 19,
    Pad_RSUp         = 1 << 20,
    Pad_RSRight      = 1 << 21,
    Pad_RSDown       = 1 << 22,
    Pad_RSLeft       = 1 << 23,
    Pad_LSUp         = 1 << 24,
    Pad_LSRight      = 1 << 25,
    Pad_LSDown       = 1 << 26,
    Pad_LSLeft       = 1 << 27
} e_PadButton;

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
    u8                   optSoundType_1E;
    u8                   optVolumeBGM_1F;
    u8                   optVolumeSE_20;
    u8                   optVibrationEnabled_21;
    u8                   optBrightness_22;
    u8                   optWeaponCtrl_23;
    u8                   optBloodColor_24;
    u8                   optAutoLoad_25;
    u8                   unk_26;
    u8                   optExtraOptionsEnabled_27;
    u8                   optViewCtrl_28;
    s8                   optViewMode_29;
    u8                   optRetreatTurn_2A;
    u8                   optWalkRunCtrl_2B;
    u8                   optAutoAiming_2C;
    u8                   optBulletAdjust_2D;
    char                 unk_2E[0x2];
    char                 unk_30[8];
    s_ControllerData     controllers_38[2];
    char                 unk_90[0x27C];
    u8                   saveGame_30C[0x27C];
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
STATIC_ASSERT_SIZEOF(s_GameWork, 0x5D8);

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
    s_SubCharacter  characters_1A0[6];
    GsCOORDINATE2   unk_coord_890[2];
    GsCOORDINATE2   hero_neck_930;
    char            unk_980[0x22A4 - 0x980];
    s32             field_22A4;
    char            unk_22A8[0xD2];
    s16             cam_ang_y_237A;
    s16             cam_ang_z_237C;
    s16             field_237E;
    int             cam_r_xz_2380;
    int             cam_y_2384;
    u8              unk_2388[0x3E0];
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 0x2768);

/** s_ShSaveGameFooter: appended to ShSaveGame during game save, contains 8-bit XOR checksum + magic
    Checksum generated via SaveGame_ChecksumGenerate function */
#define SAVEGAME_FOOTER_MAGIC 0xDCDC
typedef struct _ShSaveGameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_ShSaveGameFooter;
STATIC_ASSERT_SIZEOF(s_ShSaveGameFooter, 4);

extern s_SysWork   g_SysWork;
extern s_GameWork  g_GameWork;
extern s_GameWork* g_pGameWork;
extern s_GameWork* g_pGameWork0;

extern s_ControllerData* g_pController1;
extern s_ControllerData* g_pController2;

extern s32 g_CurDeltaTime;

#endif
