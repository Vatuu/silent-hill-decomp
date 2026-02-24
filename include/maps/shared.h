#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

#include "game.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/gfx/screen_draw.h"

// BIG TODO: Move tables below to wherever they belong when data migration is performed. I've split these into alphabetised player and NPC sections
// to make them easier to sort through. -- Sezz
//
// Noteworthy things:
// - The player has one base Harry anim info table plus several unique tables per map, wherea NPCs share single tables across maps.
// - Cybil's table is near-identical bewteen the two maps in which it's used, with minor differences in frame ranges for three of its entires.
// - Harry's tables tend to have a zeroed out anim info as their last entry.
// - Anim 0 of each character is a still frame, possibly used as a "home" pose.

// ===========
// NPC TABLES
// ===========

/*s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1, true), { Q12(10) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1,  true),  false, ANIM_STATUS(1, true), { Q12(10) }, 0, 54 },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2, true), { Q12(10) }, NO_VALUE, 55 },
    { Anim_Update0, ANIM_STATUS(2,  true),  false, ANIM_STATUS(2, true), { Q12(10) }, 55, 117 },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3, true), { Q12(10) }, NO_VALUE, 118 },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3, true), { Q12(10) }, 118, 152 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4, true), { Q12(10) }, NO_VALUE, 153 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4, true), { Q12(10) }, 153, 213 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5, true), { Q12(10) }, NO_VALUE, 214 },
    { Anim_Update1, ANIM_STATUS(5,  true),  false, NO_VALUE, { Q12(10) }, 214, 229 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6, true), { Q12(10) }, NO_VALUE, 230 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6, true), { Q12(10) }, 230, 260 },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7, true), { Q12(10) }, NO_VALUE, 261 },
    { Anim_Update1, ANIM_STATUS(7,  true),  false, NO_VALUE, { Q12(10) }, 261, 276 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8, true), { Q12(10) }, NO_VALUE, 277 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8, true), { Q12(10) }, 277, 295 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9, true), { Q12(10) }, NO_VALUE, 296 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9, true), { Q12(8) }, 296, 365 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(10) }, NO_VALUE, 366 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE, { Q12(10) }, 366, 382 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(10) }, NO_VALUE, 295 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true), { Q12(10) }, 295, 295 }
};*/

/*s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(5) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(15) }, 0, 15 }
};*/

/*s_AnimInfo INCUBATOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30)   }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(10)   }, NO_VALUE, 0   },
    { Anim_Update0, ANIM_STATUS(1, true),  false, ANIM_STATUS(1, true),  { Q12(6.1f) }, 0,        74  },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(10)   }, NO_VALUE, 75  },
    { Anim_Update0, ANIM_STATUS(2, true),  false, ANIM_STATUS(2, true),  { Q12(10)   }, 75,       115 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true),  { Q12(10)   }, NO_VALUE, 116 },
    { Anim_Update1, ANIM_STATUS(3, true),  false, NO_VALUE,              { Q12(10)   }, 116,      132 }
};*/

/*s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30) }, NO_VALUE, 1  },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(1)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              { func_800D8898 },  0,        23 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(5)  }, NO_VALUE, 24 }
};*/

/** @brief Heading angle quadrants. TODO: Order uncertain. North/South and East/West could be swapped. */
typedef enum _Quadrant
{
    Quadrant_South = 0,
    Quadrant_North = 1,
    Quadrant_West  = 2,
    Quadrant_East  = 3
} e_Quadrant;

typedef struct
{
    char unk_0[3420];
    u16  field_D5C;
    s16  field_D5E;
} s_func_800D8714;

/** @brief Stores SFX ID and volume.
 *  Volume union required becase one function reads the value as `u16`, another as `u8`.
 *  Actual value fits into `u8` (8 bit volume control).
 */
typedef struct _SfxVolume
{
    u16 id_0;
    union
    {
        u8  val8;
        u16 val16;
    } volume_2;
} s_SfxVolume;

typedef struct
{
    s_AnimInfo  animInfo_0[56];
    s32         unk_380[301][2]; // Unknown size, biggest constant index used is 35. Associated with anims.
    s_SfxVolume sfxVolumes_CE8[11];
    u_Property  properties_D14[4];
    u16         field_D24[2][3][2];
    u8          field_D3C[2][6];
    SVECTOR*    ptr_D48[5];
    s16         field_D5C[4][2]; // Related to animations. Move offset distances?
    s8          unk_D6C[4];
    s16         field_D70[2][2];
} s_func_800D2E04;

typedef struct
{
    s32               flags_0;
    s_AnmHeader*      anmHdr_4;
    GsCOORDINATE2*    coords_8;
    VECTOR3           matrices_C[1]; // Unknown size.
    s8                unk_10[0x84];
    s_SubCharacter_C8 field_9C;
    s_SubCharacter_D4 field_A8;
    s_SubCharacter_D8 field_AC;
    s32               field_B4[6][4]; // [*][3] is angle.
    s32               field_114;
    s32               field_118;
    VECTOR3           field_11C; // Q19.12
    VECTOR3           field_128;
    VECTOR3           field_134;
    VECTOR3           unk_140;
    union
    {
        struct
        {
            u8  field_14C_0 : 1;
            u8  field_14C_1 : 1;
            u8  field_14C_2 : 1;
            u8  field_14C_3 : 1;
            u32 field_14C_4 : 28; // Unsure if used.
        } bits;
        // @hack Some functions only match when bits are defined as `u32`, but that breaks other functions.
        struct
        {
            u32 field_14C_0 : 1;
            u32 field_14C_1 : 1;
            u32 field_14C_2 : 1;
            u32 field_14C_3 : 1;
            u32 field_14C_4 : 28;
        } bits32;
        u32 flags;
    } field_14C;
    q19_12 distance_150;
    q19_12 angle_154;
    q19_12 field_158; // Displacement distance.
    s32    field_15C;
} s_sharedData_800E21D0_0_s01;

// Used by puzzle in M5S01 and M7S01.
typedef struct
{
    u8 field_0; // Q12
    u8 field_1;
} s_800F0158;

typedef struct
{
    u16 sfxId;
    u16 vol;
} s_SfxPair;

typedef struct
{
    SVECTOR3 vec;
    s16      idx;
} s_sharedData_800D5AB0_1_s05;

extern s_MapOverlayHeader_94 sharedData_800E30C8_1_s02;

#if defined(MAP_FIELD_4C_COUNT)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[MAP_FIELD_4C_COUNT];
#else
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[];
#endif

#if defined(MAP_BLOOD_SPLAT_COUNT_MAX)
    extern s_BloodSplat g_Effect_BloodSplats[MAP_BLOOD_SPLAT_COUNT_MAX];
#else
    extern s_BloodSplat g_Effect_BloodSplats[];
#endif

/** Air Screamer or Night Flutter control functions. Indexed using `e_AirScreamerControl`. */
extern void (*g_Ai_AirScreamer_ControlFuncs[52])(s_SubCharacter* airScreamer); // TODO: Use `AirScreamerControl_Count`.

extern s_MapPoint2d MAP_POINTS[];
extern s_EventData  MAP_EVENTS[];
extern void (*g_LoadScreenFuncs[])();
extern void (*g_MapEventFuncs[])();
extern u8 LOADABLE_INVENTORY_ITEMS[];
extern s_UnkStruct3_Mo g_MapHeaderTable_38[];

/** Scale. */
extern VECTOR sharedData_800DD870_0_s01;

/** Scale. */
extern VECTOR sharedData_800DD880_0_s01;

/** Could be a padded `VECTOR`, but the ASM for the function `vec = vec` assignments copies only the first 3 fields. */
extern VECTOR3 sharedData_800DE170_0_s01;
extern VECTOR3 sharedData_800DE180_0_s01; // Q19.12 player position relevant to Air Screamer.
extern VECTOR3 sharedData_800DE190_0_s01;

extern s_RayData sharedData_800E2330_0_s01;

/** Packed weapon attack. `See `WEAPON_ATTACK`. */
extern s8 sharedData_800DD59C_0_s00;

extern s32 sharedData_800DF1F4_0_s00;
extern s16 sharedData_800DF1F8_0_s00;
extern s16 sharedData_800DF1FA_0_s00;

/** Something related to rotation. */
extern s32 sharedData_800E39D8_0_s00;

// Next 4 set by `Ai_Stalker_Update`.
extern q19_12 sharedData_800E3A20_0_s00; // Health.
extern q19_12 sharedData_800E3A24_0_s00; // Health.
extern q19_12 sharedData_800E3A28_0_s00;
extern q19_12 sharedData_800E3A2C_0_s00;

// Used by `Ai_Stalker`/`Ai_LarvalStalker`.
extern u8  sharedData_800DD5A6_0_s00;
extern s32 sharedData_800E39E4_0_s00;
extern s32 sharedData_800E39E8_0_s00;
extern s32 sharedData_800E39EC_0_s00[];
extern u16 sharedData_800E3A0C_0_s00[];  // Angles?
extern q19_12 sharedData_800E3A18_0_s00; // Player X position?
extern q19_12 sharedData_800E3A1C_0_s00; // Player Z position?

extern s_AnimInfo LARVAL_STALKER_ANIM_INFOS[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo STALKER_ANIM_INFOS[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creeper_Init`.
extern s_AnimInfo CREEPER_ANIM_INFOS[];
extern s8 sharedData_800E57CC_1_s02;

extern s_sharedData_800E21D0_0_s01 sharedData_800E21D0_0_s01;

extern s_func_800D2E04 const sharedData_800CAA98_0_s01; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

extern s_AnimInfo ROPMER_ANIM_INFOS[];

extern s_AnimInfo GROANER_ANIM_INFOS[];

extern s_AnimInfo HANGED_SCRATCHER_ANIM_INFOS[];

// Three variables used by `Ai_SplitHead_Init`.
extern s_AnimInfo SPLIT_HEAD_ANIM_INFOS[];
extern q3_12 sharedData_800D8614_1_s05; // Offset X.
extern q3_12 sharedData_800D8616_1_s05; // Offset Z.

extern s32 sharedData_800D5884_1_s05;

extern s16 sharedData_800D5A8C_1_s05;

extern u8 sharedData_800D5AAE_1_s05;
extern u8 sharedData_800D5AAF_1_s05;

extern u8      sharedData_800D5CF8_1_s05[];
extern u8      sharedData_800D5D08_1_s05[];
extern VECTOR3 sharedData_800D8618_1_s05[];
extern SVECTOR3 sharedData_800D5A90_1_s05[]; // Q7.8

extern s_sharedData_800D5AB0_1_s05 sharedData_800D5AB0_1_s05[];
extern s16                         sharedData_800D5BE0_1_s05[6][3];

extern u8  sharedData_800D16E4_2_s01;

extern s_AnimInfo BLOODSUCKER_ANIM_INFOS[];

extern u8 sharedData_800DD591_0_s00;
extern u8 sharedData_800DD584_0_s00;

extern s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[];
extern s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[];

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;

extern s32 sharedData_800DD58C_0_s00;
extern s32 sharedData_800E32CC_0_s00;

extern u16 sharedData_800D21E8_3_s00[];

extern u16 sharedData_800E32D4_0_s00;

extern s32 sharedData_800DD598_0_s00;

extern CVECTOR sharedData_800E3258_0_s00;

extern CVECTOR sharedData_800E325C_0_s00;

extern s32 sharedData_800E2370_0_s01[2];

// Each of these holds 8 bytes, passed to `Bgm_Update` which loops through each byte.
extern u8 sharedData_800CFB14_0_s02[8];
extern u8 sharedData_800CFB1C_0_s02[8];
extern u8 sharedData_800CFB24_0_s02[8];
extern u8 sharedData_800CFB2C_0_s02[8];
extern u8 sharedData_800CFB34_0_s02[8];
extern u8 sharedData_800CFB3C_0_s02[8];
extern u8 sharedData_800CFB44_0_s02[8];
extern u8 sharedData_800CFB4C_0_s02[8];
extern u8 sharedData_800CFB54_0_s02[8];

/** Q19.12 */
extern VECTOR3 sharedData_800DE1A0_0_s01;

extern VECTOR3 sharedData_800DE1B0_0_s01;

extern VECTOR3 sharedData_800DE1C0_0_s01;

extern VECTOR3 sharedData_800DE1E0_0_s01;

extern VECTOR3 sharedData_800DE1F0_0_s01; // Q19.12

extern s_800C4590 sharedData_800E2350_0_s01;

extern s_800C4590 sharedData_800E39BC_0_s00;

extern s32 sharedData_800DD5A0_0_s00;
extern s16 sharedData_800DD5A4_0_s00; // Used as index into array of vectors.
extern s16 sharedData_800E39E0_0_s00;
extern s16 sharedData_800E39E2_0_s00;

extern s32 sharedData_800D8684_1_s05;
extern s32 sharedData_800D8688_1_s05;

extern u8      sharedData_800EB738_6_s04;
extern u8      sharedData_800EB740_6_s04[2];
extern u8      sharedData_800EB748_6_s04;
extern s8      sharedData_800EB74A_6_s04;
extern VECTOR3 sharedData_800EB750_6_s04;

extern s16 sharedData_800D5880_1_s05;

extern u8 sharedData_800E1208_1_s02[8];
extern u16 sharedData_800E1210_1_s02[42]; // Flags.

typedef struct
{
    VECTOR3 field_0; // Rotation?
    s16     field_C;
    s16     field_E;
    s8      field_10;
    u8      field_11;
    u8      field_12;
    s8      field_13;
} s_800E34FC;
STATIC_ASSERT_SIZEOF(s_800E34FC, 20);

typedef struct
{
    VECTOR3  field_0;
    SVECTOR3 field_C; // 2D position or offset.
    u8       unk_12[2];
    u8       field_14;
    u8       field_15;
    u8       field_16; // Packed angle?
} s_800E330C;
STATIC_ASSERT_SIZEOF(s_800E330C, 24);

typedef struct
{
    s32   field_0;
    s32   field_4;
    q3_12 field_8; // Y offset.
    s16   field_A;
} s_D_800D5A8C;
STATIC_ASSERT_SIZEOF(s_D_800D5A8C, 12);

typedef struct _MapHeader_field_5C
{
    u8    flags_0;
    u8    field_1;
    u8    field_2;
    u8    field_3;
    u8    field_4;
    u8    field_5;
    u8    field_6;
    u8    field_7;
    u16   field_8;
    s16   field_A;
    u16   field_C;
    s16   field_E;
    q3_12 field_10;
    s16   field_12;
    s16   field_14;
    s16   field_16;
    s16   field_18;
    s16   field_1A;
    u16   field_1C;
    s16   field_1E;
    s32   field_20;
    s32   field_24;
} s_MapHeader_field_5C;

typedef struct
{
    s32 vx;
    s32 vy;
    s16 vz;
} s_sharedData_800DFB10_0_s01;

typedef struct
{
    q19_12 field_0; // Relative anim time?
    s32    field_4;
} s_sharedData_800ED2D4_2_s02;

extern s_MapHeader_field_5C sharedData_800D8568_1_s05;

extern s_800E330C sharedData_800E330C_0_s00[20];

extern s_800E34FC sharedData_800E34FC_0_s00[60];

extern const char* MAP_MESSAGES[]; // 0x800DF6B8

extern s_MapOverlayHeader_7C sharedData_800DEE50_1_s01;

extern u8 sharedData_800EEAC4_2_s00[][4][4];

extern VECTOR3 sharedData_800F216C_2_s00;

extern VECTOR3 sharedData_800F217C_2_s00;

extern VECTOR3 sharedData_800F21BC_2_s00;

extern VECTOR3 sharedData_800F21CC_2_s00;

extern VECTOR3 sharedData_800F21DC_2_s00;

extern VECTOR3 sharedData_800F21EC_2_s00;

extern VECTOR3 sharedData_800F21FC_2_s00;

extern VECTOR sharedData_800DE200_0_s01;

extern VECTOR3 sharedData_800DE210_0_s01;

extern SVECTOR sharedData_800DE220_0_s01;

extern MATRIX sharedData_800DE230_0_s01;

extern s32 g_PuppetNurseHurtSfxIdxs[4];

extern s_SfxPair g_NursePuppetSfxs[18];

// Only used by `Ai_PuppetNurse_AnimSfxGet`. Currently causes a mismatch. Try to move it when more code gets decompiled.
extern u8 g_NursePuppet_SfxOffsets[4]; // = { 9, 6, 7, 8 };

// Only used by `Ai_PuppetNurse_Control8`. Currently causes a mismatch. Try to move it when more code gets decompiled.
extern u16 g_PuppetNurse_ModelStates0[8]; // = { 9, 9, 9, 6, 6, 9, 7, 7 }; // + 2 bytes of padding.

extern u8 g_NursePuppet_AnimSfxs[580];

extern s32 g_PuppetNurse_AnimStatus0[2];

extern s32 g_PuppetNurse_AnimStatus1[2];

extern u8  g_PuppetNurse_AnimStatus2[2];

extern u8  g_PuppetNurse_AnimStatus3[4];

extern u8  g_PuppetNurse_AnimStatus4[4];

extern u8      sharedData_800D4CD4_3_s01[][2];
extern DVECTOR sharedData_800D4D0C_3_s01;
extern VECTOR3 sharedData_800CB088_3_s01;
extern VECTOR3 sharedData_800CB094_3_s01;
extern VECTOR3 sharedData_800CB0A0_3_s01;
extern s32     sharedData_800D4D10_3_s01;
extern s32     sharedData_800D4D14_3_s01;
extern s8      sharedData_800D4D18_3_s01;

extern s_D_800D5A8C sharedData_800D5A8C_3_s03[3];

extern u8 sharedData_800D1D14_3_s02[8];

/** Room flags? */
extern u16 sharedData_800D1D1C_3_s02[60];

extern s_sharedData_800DFB10_0_s01 sharedData_800DFB10_0_s01[];

extern u8 sharedData_800ED430_2_s02[];

extern u8 sharedData_800ED43C_2_s02[];

extern s_sharedData_800ED2D4_2_s02 sharedData_800ED2D4_2_s02[];

extern s32 sharedData_800EC950_2_s02;

extern s32 sharedData_800ECA4C_2_s02;

extern s32 sharedData_800ECACC_2_s02;

extern s16 sharedData_800ECB22_2_s02;

extern s16 sharedData_800ECBC2_2_s02;

extern s16 sharedData_800ECBD0_2_s02;

extern s_sharedData_800ED2D4_2_s02 sharedData_800ED314_2_s02[];

extern u8  sharedData_800EFCFC_6_s00[8];
extern s32 sharedData_800EFD04_6_s00;
extern u16 sharedData_800EFD08_6_s00[];
extern u16 sharedData_800EFD34_6_s00[];


extern u8 sharedData_800ED418_4_s02[8];
extern s32 sharedData_800ED420_4_s02;
extern u8 sharedData_800ED424_4_s02[8];
extern u16 sharedData_800ED42C_4_s02[];
extern u8 sharedData_800ED458_4_s02[8];

extern void (*g_Romper_ControlFuncs[])(s_SubCharacter* romper);

extern s_Bgm_Update sharedData_800D2F18_7_s00;
extern s_Bgm_Update sharedData_800D2F20_7_s00;
extern u16          sharedData_800D2F28_7_s00[38]; // Flags array.
extern s_Bgm_Update sharedData_800D2F74_7_s00;
extern s_Bgm_Update sharedData_800D2F7C_7_s00;
extern s_Bgm_Update sharedData_800D2F84_7_s00;

extern s32 sharedData_800E1570_7_s01;
extern s32 sharedData_800E1574_7_s01;
extern u8  sharedData_800E1578_7_s01[3][3][3][2];
extern u32 sharedData_800E1694_7_s01;
extern s32 sharedData_800E2CA8_7_s01;
extern s32 sharedData_800E2CAC_7_s01;

void sharedFunc_800DB60C_7_s01(void);

bool sharedFunc_800CE688_1_s03(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CD1F8_0_s01(POLY_FT4** poly, s32 idx);

void Map_RoomBgmInit(bool arg0);

void Map_RoomBgmInit_CondTrue(void);

void Map_RoomBgmInit_CondFalse(void);

void sharedFunc_800CAAD0_1_s05(void);

void sharedFunc_800CABF8_1_s05(s32 idx, bool arg1);

bool sharedFunc_800CB040_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CB884_1_s05(POLY_FT4** poly, s32 idx);

void sharedFunc_800CBE7C_1_s05(q23_8 posX, q23_8 posY, q23_8 posZ, s32 arg3, s32 arg4);

void sharedFunc_800CCDD4_1_s05(POLY_FT4** poly, s32 idx);

void sharedFunc_800CCE2C_1_s05(s32 arg0, s32 arg1, q23_8 posX0, q23_8 posY0, q23_8 posZ0, q23_8 posX1, q23_8 posY1, q23_8 posZ1);

void sharedFunc_800D4408_1_s05(VECTOR3* pos, s32 idx, q23_8 posX, q23_8 posY, q23_8 posZ);

q19_12 sharedFunc_800D7714_0_s01(s_SubCharacter* chara);

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Both are used in map0_s01 so ifdefs cannot be used based on the map name.
 * Sections under `#if 0` are what is missing compared to `sharedFunc_800D57C8_0_s01`.
 */
void sharedFunc_800D598C_0_s01(s_SubCharacter* airScreamer);

// Probably all Air Screamer section below. Unsure about functions above.

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Also look at `sharedFunc_800D598C_0_s01`.
 */
void sharedFunc_800D5B10_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5C90_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5D80_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5E14_0_s01(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_2(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_3(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_5(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_6(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_7(s_SubCharacter* airScreamer);

bool sharedFunc_800D4AEC_0_s01(s_SubCharacter* airScreamer, VECTOR3* arg1, VECTOR3* arg2, VECTOR3* arg3);

void Ai_AirScreamer_Control_8(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_9(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_11(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_12(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_13(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_14(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_15(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_16(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_17(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_18(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_19(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_20(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_21(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_22(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_23(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_24(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_25(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_26(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_27(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_28(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_30(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_31(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_32(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_33(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_34(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_36(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_37(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_40(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_41(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_42(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_43(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_44(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_45(s_SubCharacter* airScreamer);

bool sharedFunc_800DBF88_2_s00(s_SubCharacter* airScreamer, s32 arg1);

/** Checks if an Air Screamer is below the ground with a slight height intolerance. */
bool sharedFunc_800DC0A8_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* airScreamer, q19_12 moveSpeedMult);

bool sharedFunc_800DC200_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC30C_2_s00(s_SubCharacter* airScreamer);

/** Checks if an Air Screamer is near the ground? */
bool sharedFunc_800DC3BC_2_s00(s_SubCharacter* airScreamer);

/** State step getter. */
s32 sharedFunc_800DC438_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC50C_2_s00(s_SubCharacter* airScreamer);

s32 sharedFunc_800DC598_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC67C_2_s00(s_SubCharacter* airScreamer);

/** Chance getter? */
q19_12 sharedFunc_800DC6E4_2_s00(s_SubCharacter* airScreamer, q19_12 arg1);

/** Chance getter? */
q19_12 sharedFunc_800DC894_2_s00(s_SubCharacter* airScreamer, q19_12 dist);

void sharedFunc_800DD13C_2_s00(s_SubCharacter* airScreamer, s32 npcSlot, q19_12 spawnChance);

void sharedFunc_800DD2C4_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2);

void sharedFunc_800DD4A4_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD4EC_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD534_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD588_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD834_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDA80_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDE14_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDF74_2_s00(s_SubCharacter* airScreamer, q19_12 dist, q19_12 headingAngle);

void sharedFunc_800DE034_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE11C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DE250_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DE578_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DE6A8_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE7E0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DEBCC_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DECC4_2_s00(s_SubCharacter* airScreamer);

q19_12 sharedFunc_800DEE24_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF358_2_s00(s_SubCharacter* airScreamer);

/** Condition is probably to differentiate between an Air Screamer and Night Flutter. */
void sharedFunc_800DF448_2_s00(s_SubCharacter* airScreamer, bool cond);

void sharedFunc_800DF60C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF710_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF80C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF8A0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E012C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E021C_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2);

void sharedFunc_800E041C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E04B0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E0514_2_s00(s_SubCharacter* airScreamer);

/** Air Screamer state step getter. `const` is required for match. */
bool sharedFunc_800D5F00_0_s01(s_SubCharacter* const airScreamer);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* player, bool cond);

/** Resets some player properties. */
void sharedFunc_800D8904_0_s00(s_SubCharacter* player, q19_12 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* player);

/** Locks a character's animation. */
void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

/** Unlocked flag getter. */
s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

/** Unlocks a character's animation. */
void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

s32 Anim_StartKeyframeIdxGet(s_SubCharacter* chara);

/** Humanoid init function? */
void sharedFunc_800D923C_0_s00(s_SubCharacter* chara);

void SysWork_StateStepIncrementAfterTime(q19_12* timer, q19_12 inc, q19_12 timeMin, q19_12 timeMax, bool setTimerToMax, bool incStateStep);

void sharedFunc_800CB7F4_1_s01(void);

void sharedFunc_800CB8A0_1_s01(s32 idx);

bool sharedFunc_800CBA38_1_s01(s32 idx);

bool sharedFunc_800CBB30_1_s01(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CBDA8_1_s02(POLY_FT4** poly, s32 idx);

void sharedFunc_800CCE60_1_s02(void);

bool sharedFunc_800CBF74_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CC618_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CCF30_1_s05(POLY_FT4** poly, s32 idx);

/** Unsure which character this takes, stalker doesn't fit? */
void sharedFunc_800D88AC_0_s00(s_SubCharacter* stalker);

// MAP3_S03 puppet nurse/doctor funcs

void sharedFunc_800CDA88_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800CDB5C(s_SubCharacter* nurse, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* nurse, bool isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetDoctor_Update(s_SubCharacter* doctor, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetNurse_DamageHandle(s_SubCharacter* nurse);

s32 PuppetNurse_HurtSfxIdGet(s_SubCharacter* nurse);

void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx);

s32 Ai_PuppetNurse_AnimSfxGet(s32 idx);

/** Checks damage angle. */
bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse);

void Ai_PuppetNurse_Move(s_SubCharacter* nurse);

/** Checks if some special animation is set. */
bool sharedFunc_800CE398_3_s03(s32 animStatus);

void Ai_PuppetNurse_Control1(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control2(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, bool isDoctor);

bool sharedFunc_800CE7C8_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control5(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control6_7(s_SubCharacter* nurse, bool isDoctor);

void Ai_PuppetNurse_Control8(s_SubCharacter* nurse);

s32 sharedFunc_800CEEAC_3_s03(void);

void Ai_PuppetNurse_Control9(s_SubCharacter* nurse);

s32 sharedFunc_800CF600_3_s03(s_SubCharacter* nurse);

void sharedFunc_800CF7F4_3_s03(s_SubCharacter* nurse);

bool sharedFunc_800CF90C_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control12(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control10(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control11(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control13(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control(s_SubCharacter* nurse);

void sharedFunc_800D02E4_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords);

void sharedFunc_800D03E4_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_AnimUpdate(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

// Not Harry?
void sharedFunc_800D0828_3_s03(s_SubCharacter* harry, GsCOORDINATE2* coords);

void sharedFunc_800D0968_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords);

void Ai_Creeper_Update(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Creeper_Init(s_SubCharacter* creeper); // `map5_s00` version has extra code at end of func.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creeper);

void Ai_Creeper_ControlUpdate(s_SubCharacter* creeper);

void Ai_Creeper_Control_1(s_SubCharacter* creeper);

void Ai_Creeper_Control_2(s_SubCharacter* creeper);

void Ai_Creeper_Control_3(s_SubCharacter* creeper);

void Ai_Creeper_Control_4(s_SubCharacter* creeper);

void Ai_Creeper_Control_5(s_SubCharacter* creeper);

void sharedFunc_800D983C_1_s02(s_SubCharacter* creeper);

void sharedFunc_800D9960_1_s02(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800D99D0_1_s02(s_SubCharacter* creeper);

bool sharedFunc_800D3508_0_s01(s_SubCharacter* airScreamer, q19_12* dist);

bool sharedFunc_800D3630_0_s01(s_SubCharacter* airScreamer, q19_12* dist);

/** Returns flags? Specific to Air Screamer? */
s32 sharedFunc_800D3758_0_s01(s_SubCharacter* airScreamer, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4);

void Ai_Romper_Update(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Romper_Init(s_SubCharacter* romper);

/** Probably Romper func given the placement. */
void sharedFunc_800E5FC8_2_s02(s_SubCharacter* chara, s16 arg1, s16 arg2, u8* arg3);

void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper);

void sharedFunc_800E6420_2_s02(s_SubCharacter* romper);

void Ai_Romper_ControlUpdate(s_SubCharacter* romper);

void Ai_Romper_Control_1(s_SubCharacter* romper);

void Ai_Romper_Control_8(s_SubCharacter* romper);

void Ai_Romper_Control_9(s_SubCharacter* romper);

void Ai_Romper_Control_11(s_SubCharacter* romper);

void sharedFunc_800E8730_2_s02(s_SubCharacter* romper);

void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter* romper);

s32 sharedFunc_800E939C_2_s02(s_SubCharacter* romper);

s32 sharedFunc_800E94B4_2_s02(s_SubCharacter* romper);

void sharedFunc_800E9714_2_s02(s_SubCharacter* romper);

void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Groaner_Init(s_SubCharacter* groaner); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E33DC_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E39D8_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5930_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner);

/** Related to Air Screamer? */
extern GsCOORDINATE2* sharedData_800D8610_1_s05;

/** Unclear, but funcs past here may be specific to Air Screamer. */

void sharedFunc_800D8804_0_s01(void);

s32 sharedFunc_800D929C_0_s00(void);

/** NPC anim func. Checks if the active keyframe is at the start or end of the anim's range. */
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId);

bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch);

void sharedFunc_800CCB8C_0_s01(VECTOR* arg0, VECTOR* arg1, s16 arg2, s32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7);

s32 sharedFunc_800D569C_0_s01(s_SubCharacter* airScreamer, q19_12 posY, q19_12 dist);

void sharedFunc_800D57C8_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5E78_0_s01(s_SubCharacter* airScreamer, q19_12 angle);

s32 sharedFunc_800D6A60_0_s01(VECTOR3* offset, VECTOR3* vec1, s_SubCharacter* airScreamer, s32 arg3, VECTOR3* vec2);

void sharedFunc_800D6C7C_0_s01(VECTOR* arg0, s_SubCharacter* airScreamer, s32 arg2, VECTOR3* arg3);

/** Plays SFX. */
void sharedFunc_800D2364_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5638_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800DF2D0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800D4E84_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D529C_0_s01(s_SubCharacter* airScreamer, q19_12 radius, q19_12 headingAngle);

void sharedFunc_800D53AC_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ, q19_12 range);

void sharedFunc_800CD920_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ);

q19_12 sharedFunc_800CD940_3_s03(q19_12 pos0, q19_12 pos1);

s32 sharedFunc_800CD980_3_s03(s_SubCharacter* chara);

q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mat, s32 matCount, VECTOR3* center);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D7B14_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800CE5D4_1_s03(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3);

void sharedFunc_800CBA4C_1_s02(s32 idx, s32 arg1, s32 arg2);

void sharedFunc_800CBC98_1_s02(void);

void sharedFunc_800CBD58_1_s02(void);

void sharedFunc_800DE1F8_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DEC64_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DEC84_2_s00(s_SubCharacter* airScreamer, q19_12 radius, q19_12 angle);

void sharedFunc_800DECA4_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DF22C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DF24C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800D2FB4_0_s01(s_SubCharacter* airScreamer, VECTOR3* playerPos, s32 playerField10C);

void sharedFunc_800D72E8_0_s01(s_SubCharacter* airScreamer, q19_12 angle0, q19_12 rotSpeedY);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer);

/** @brief Handles the jammed door event. */
void MapEvent_DoorJammed(void);

/** @brief Handles the locked door event. */
void MapEvent_DoorLocked(void);

void sharedFunc_800D15F0_3_s01(void);

/** @brief Handles the unlocked door event. */
void MapEvent_DoorUnlocked(void);

void sharedFunc_800CEEE0_3_s03(s_SubCharacter* nurse);

void sharedFunc_800CF0B4_3_s03(s_SubCharacter* nurse);

bool sharedFunc_800CF294_3_s03(s_SubCharacter* nurse, q19_12 dist);

/** @brief Gets the room index corresponding to the current 2D position.
 *
 * @param x X position in Q19.12.
 * @param z Z position in Q19.12.
 * @return Room index.
 */
u8 Map_RoomIdxGet(s32 x, s32 z);

void sharedFunc_800CBE54_4_s03(VECTOR3* arg0, s32 arg1);

bool sharedFunc_800CC004_4_s03(POLY_FT4** poly, s32 arg1);

bool sharedFunc_800CB1B0_4_s03(POLY_FT4** poly, s32 arg1);

void sharedFunc_800CB0A4_4_s03(VECTOR3* arg0, VECTOR3* arg1);

void sharedFunc_800D0110_7_s00(void);

static inline void ModelAnim_AnimInfoSet(s_ModelAnim* anim, s_AnimInfo* animInfo)
{
    anim->animInfo_C  = animInfo;
    anim->animInfo_10 = NULL;
}

// TODO: Could also call this a "transform"? "Pose" is a less common term for a position+rotation struct.
typedef struct
{
    VECTOR3  position_0; // Q19.12
    SVECTOR3 rotation_C; // Q19.12
} s_WorldObjectPose;
STATIC_ASSERT_SIZEOF(s_WorldObjectPose, 0x14);

typedef struct
{
    s_WorldObjectModel object_0;
    VECTOR3         position_1C; // Q19.12
    SVECTOR3        rotation_28; // Q19.12
} s_WorldObjectDesc;
STATIC_ASSERT_SIZEOF(s_WorldObjectDesc, 0x30);

typedef struct
{
    s_WorldObjectModel object_0;
    VECTOR3         position_1C; // Q19.12
} s_WorldObjectDescNoRot;
STATIC_ASSERT_SIZEOF(s_WorldObjectDescNoRot, 40);

#define WorldObjectPoseInit(eventPos, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectPoseSet(eventPos, Q12(posX), Q12(posY), Q12(posZ), Q12_ANGLE(rotX), Q12_ANGLE(rotY), Q12_ANGLE(rotZ))

#define WorldObjectPoseSet(eventPose, posX, posY, posZ, rotX, rotY, rotZ) \
{                                                                         \
    Math_Vector3Set(&(eventPose)->position_0, posX, posY, posZ);          \
    Math_SetSVectorFast(&(eventPose)->rotation_C, rotX, rotY, rotZ);      \
}

#define WorldObjectInit(eventPos, name, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectSet(eventPos, name, Q12(posX), Q12(posY), Q12(posZ), Q12_ANGLE(rotX), Q12_ANGLE(rotY), Q12_ANGLE(rotZ))

#define WorldObjectSet(eventPose, name, posX, posY, posZ, rotX, rotY, rotZ) \
{                                                                           \
    Math_Vector3Set(&(eventPose)->position_1C, posX, posY, posZ);           \
    Math_SetSVectorFast(&(eventPose)->rotation_28, rotX, rotY, rotZ);       \
    WorldObject_ModelNameSet(&(eventPose)->object_0, (name));               \
}

#define WorldObjectNoRotInit(eventPos, name, posX, posY, posZ) \
    WorldObjectNoRotSet(eventPos, name, Q12(posX), Q12(posY), Q12(posZ))

#define WorldObjectNoRotSet(eventPose, name, posX, posY, posZ)    \
{                                                                 \
    Math_Vector3Set(&(eventPose)->position_1C, posX, posY, posZ); \
    WorldObject_ModelNameSet(&(eventPose)->object_0, (name));     \
}

#define APPROACH(current, target, step) \
    ((current) > (target) ? MAX((current) - (step), (target)) : MIN((target), (current) + (step)))

#define APPROACH_ALT(current, target, step) \
    ((current) > (target) ? MAX((current) - (step), (target)) : CLAMP_HIGH((current) + (step), (target)))

#define APPROACH_ALT2(current, target, step) \
    ((current) > (target) ? CLAMP_LOW((current) - (step), (target)) : CLAMP_HIGH((target), (current) + (step)))

/** @brief Updates the move speed of a character.
 *
 * @param chara Character to update.
 * @param speed Move speed (Q*.12).
 */
#define Chara_MoveSpeedUpdate(chara, speed) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, Q12(0.0f), Q12_MULT_PRECISE(g_DeltaTime, speed))

// TODO: Is it possible to merge these macros?
#define Chara_MoveSpeedUpdate2(chara, speed, limit)                       \
{                                                                         \
    q19_12 moveSpeed;                                                     \
    q19_12 newSpeed;                                                      \
    q19_12 newMoveSpeed;                                                  \
                                                                          \
    moveSpeed = chara->moveSpeed_38;                                      \
    if (moveSpeed > limit)                                                \
    {                                                                     \
        newMoveSpeed = limit;                                             \
        limit        = Q12(0.0f);                                         \
        newSpeed     = moveSpeed - Q12_MULT_PRECISE(g_DeltaTime, speed); \
        if (newMoveSpeed < newSpeed)                                      \
        {                                                                 \
            newMoveSpeed = newSpeed;                                      \
        }                                                                 \
    }                                                                     \
    else                                                                  \
    {                                                                     \
        newMoveSpeed = limit;                                             \
        newSpeed     = moveSpeed + Q12_MULT_PRECISE(g_DeltaTime, speed); \
        if (newMoveSpeed >= newSpeed)                                     \
        {                                                                 \
            newMoveSpeed = newSpeed;                                      \
        }                                                                 \
    }                                                                     \
    chara->moveSpeed_38 = newMoveSpeed;                                   \
}

#define Chara_MoveSpeedUpdate3(chara, speed, limit) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, limit, Q12_MULT_PRECISE(g_DeltaTime, speed))

#define Chara_MoveSpeedUpdate4(chara, speed, limit) \
    chara->moveSpeed_38 = APPROACH_ALT(chara->moveSpeed_38, limit, Q12_MULT_PRECISE(g_DeltaTime, speed))

#endif
