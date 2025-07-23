#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "bodyprog/text_draw.h" // TODO: Add to .c files that make use of this instead of including here.
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"
#include "types.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` that has not been identified to
 * be related a to currently recognized and separated section of
 * the engine (like player logic, save game or item screens).
 */

// ========
// DEFINES
// ========

#define TEMP_MEMORY_ADDR ((s8*)0x801A2600)

#define IMAGE_BUFFER_0 ((u_long*)0x801CFA00)
#define IMAGE_BUFFER_1 ((u_long*)0x801C8200)
#define IMAGE_BUFFER_2 ((u_long*)0x801ABE00)
#define FONT24_BUFFER ((u_long*)0x801F5600) // Loaded by `GameFs_StfRollBinLoad`.

#define CD_ADDR_0 ((u_long*)0x801E2600)

#define OPT_SOUND_VOLUME_MIN   0
#define OPT_SOUND_VOLUME_MAX   128
#define OPT_VIBRATION_DISABLED 0
#define OPT_VIBRATION_ENABLED  128

// TODO: Could be part of a larger SFX enum with every sound effect? Maybe registered like filesystem assets.
#define SFX_DENIED  0x518
#define SFX_BACK    0x519
#define SFX_CANCEL  0x51A
#define SFX_CONFIRM 0x51B

// ======
// ENUMS
// ======

/** Used by `func_8003F654` to cast a specific field to the desired type. */
typedef enum _MenuState
{
    MenuState_Start              = 0,
    MenuState_Main               = 1,
    MenuState_LoadGame           = 2,
    MenuState_DifficultySelector = 3,
    MenuState_NewGameStart       = 4
} e_MenuState;

typedef enum _PrimitiveType
{
    PrimitiveType_None = 0,
    PrimitiveType_S8   = 1,
    PrimitiveType_U8   = 2,
    PrimitiveType_S16  = 3,
    PrimitiveType_U16  = 4,
    PrimitiveType_S32  = 5
} s_PrimitiveType;

// ================
// UNKNOWN STRUCTS
// ================

/* Structs called by functions that haven't been identified. */

// Exception, as one of the unidentified structs uses this.
typedef struct
{
    s32 field_0;
    u8  field_4;
    u8  field_5;
    u16 field_6;
    s32 field_8;
    s32 field_C;
} s_8002AC04;
STATIC_ASSERT_SIZEOF(s_8002AC04, 16);

// Likely not `s_Skeleton` since `field_8` must be `s8`.
typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
    s8 unk_4[4];
    s8 field_8;
} s_80041CEC;

typedef struct 
{
    s32  field_0;
    u8   unk_4[12];
    s8*  field_16;
    u8   unk_20[4];
    s8   field_24;
    s8   field_25;
} s_func_8003C8F8;

typedef struct
{
    s32 field_0;
    s8* field_4;
} s_func_8003F654;

typedef struct
{
    s8  unk_0[4];
    s16 field_4;
    s8  unk_6[2];
    s8  unk_8[3];
    s8  unk_10[4];
    s32 field_14;
} s_func_8003FEC0;

typedef struct
{
    s_80041CEC* field_0;
    s32         field_4;
    s32         field_8;
} s_func_80041CB4;

typedef struct
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    s16 field_4;
    s16 field_6;
} s_func_8005660C_1;

typedef struct
{
    s8  unk_0[14];
    s8  field_E;
    s16 field_10;
    s8  unk_12[2];
    u8  field_14;
    u8  field_15;
} s_func_8005660C_0;

typedef struct
{
  u8 unk_0[24];
} s_func_800566B4_sub;
STATIC_ASSERT_SIZEOF(s_func_800566B4_sub, 24);

typedef struct
{
    s8                   unk_0[3];
    u8                   field_3; // Size of `field_4` array.
    s_func_800566B4_sub* field_4;
} s_func_800566B4;

typedef struct
{
    s8 unk_0[20];
    s8 field_14;
} s_func_8005B370;

typedef struct
{
    char pad[12];
} s_func_8005B424;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s8  unk_A;
    s8  field_B;
    s8  field_C;
    s8  field_D;
    s16 field_E;
    s32 field_10;
} s_func_800625F4;
STATIC_ASSERT_SIZEOF(s_func_800625F4, 20);

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u16 field_6_0  : 5; // TODO: Might be using `s_func_800699E4_18` substruct here? Won't fit though..
    u16 field_6_5  : 3;
    u16 field_6_8  : 3;
    u16 field_6_11 : 4;
    u16 field_6_15 : 1;
    s16 field_8;
    s16 field_A;
} s_func_800699E4_10;
STATIC_ASSERT_SIZEOF(s_func_800699E4_10, 12);

typedef struct
{
    u16 field_0_0  : 5;
    u16 field_0_5  : 3;
    u16 field_0_8  : 3;
    u16 field_0_11 : 4;
    u16 field_0_15 : 1;
    u8  unk_2[2];
    u8  unk_4[6];
} s_func_800699E4_18;
STATIC_ASSERT_SIZEOF(s_func_800699E4_18, 10);

typedef struct
{
    s32                 field_0;
    s32                 field_4;
    u32                 field_8_0  : 8;
    u32                 field_8_8  : 8;
    u32                 field_8_16 : 8;
    u32                 field_8_24 : 8;
    u8                  unk_C[4];
    s_func_800699E4_10* ptr_10;
    u8                  unk_14[4];
    s_func_800699E4_18* ptr_18;
    u8                  unk_1C[2];
    u8                  field_1E;
    u8                  unk_1F[1];
    s32*                field_20; // Might point to `s_func_8006B1C8`?
    u8                  unk_24[4];
    s8*                 field_28;
    s8*                 field_2C;
    u8                  field_30;
    u8                  unk_31[3];
    u8                  field_34[256];
} s_func_800699E4;

/** @brief Returned by `func_800699F8`, collision related? */
typedef struct _s_func_800699F8
{
    s32 chara_grnd_0;
    s16 field_4;
    s16 field_6;
    s8  field_8;
    u8  unk_9[3];
} s_func_800699F8;
STATIC_ASSERT_SIZEOF(s_func_800699F8, 12);

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s16 field_10;
    s16 field_12;
    s8  field_14;
    s8  unk_15[3];
    s32 field_18;
} s_func_8006A178;

typedef struct
{
    VECTOR3  pos_0;
    SVECTOR3 rot_C;
    s8       field_12;
} s_func_8006AB50;

typedef struct
{
    s32     field_0;
    s32     field_4;
    s32     field_8;
    SVECTOR field_C;
    s16     dirX_14;
    s16     dirZ_16;
    s32     posX_18;
    s32     posZ_1C;
    s32     field_20;
    s32     field_24;
    s16     field_28;
    s16     field_2A;
    s16     field_2C;
} s_func_8006ABC0;

typedef struct
{
    s16 field_0;
    u8  unk_2[2];
    s16 field_4;
} s_func_8006B1C8;

typedef struct
{
    s8  unk_0[48];
    s16 field_30;
    s8  unk_32[164];
    s16 field_D6;
    s8  unk_DA[8];
    s32 field_E0;
    s8  unk_E4[2];
    u16 field_E6;
    s8  unk_EA[2];
    s32 field_EC;
} s_func_8006BC34;

typedef struct
{
    s8  field_0;
    s8  unk_1;
    s16 field_2;
    s16 field_4;
} s_func_8006BDDC;

typedef struct
{
    u8  unk_0[2];
    s16 field_2;
    u8  unk_4[2];
    s16 field_6;
} s_func_8006CA18;

typedef struct
{
    u8  unk_0[1];
    u8  field_1;
    u8  unk_2[2];
    s32 field_4;
} s_func_8006CC44_A8;

typedef struct
{
    u8                 field_0_0  : 8;
    s8                 field_0_8  : 1;
    s8                 field_0_9  : 1;
    s8                 field_0_10 : 1;
    s8                 field_0_11 : 5;
    u16                field_2    : 16;
    s_func_8006ABC0    field_4;
    s32                field_34;
    s8                 unk_38[12];
    s8                 field_44;
    s8                 unk_45[5];
    s16                field_4A;
    s8                 field_4C;
    s8                 unk_4D[3];
    s8                 unk_50[36];
    s8                 field_74;
    s8                 unk_75[5];
    s16                field_7A;
    s32                field_7C;
    s32                field_80;
    s32                field_84;
    s32                field_88;
    s32                field_8C;
    s32                field_90;
    s32                field_94;
    s16                field_98;
    s16                field_9A;
    u8                 unk_9C[4];
    u8                 field_A0;
    u8                 field_A1;
    u8                 field_A2;
    u8                 field_A3;
    s_func_8006CA18*   field_A4;
    s_func_8006CC44_A8 field_A8[4];
    u8                 field_C8;
    u8                 unk_C9[1];
    s16                field_CA;
    u8                 unk_CC[4];
    u8                 unk_D0[8];
    u8                 field_D8;
    u8                 field_D9;
    // TODO: May be incomplete.
} s_func_8006CC44;

typedef struct
{
    s8  unk_0[22];
    s32 field_18;
} s_func_80089840;

typedef struct
{
    VECTOR3 field_0;
    VECTOR3 field_C;
    s8      unk_18[6];
    u8      field_1E;
    u8      field_1F;
} s_func_800CFFF8;

// Function from lib_unk
typedef struct
{
    char unk_0[0xC];
    s32 field_C;
    s_8002AC04* field_10;
    u32 field_14_0  : 16;
    u32 field_14_16 : 8;
    u32 field_14_24 : 7;
    u32 field_14_31 : 1;
    u32 field_18;
    u16 field_1C;
    u16 field_1E;
} s_func_8009ECCC;

// ========
// STRUCTS
// ========

typedef struct
{
    u16 field_0;
    u16 field_2; // Engine cmd.
} s_800252BC;

typedef struct
{
    s8  field_0;
    s8  field_1;
    s8  field_2;
    s8  field_3;
    s32 field_4[4];
} s_800382B0;

// Maybe same.
typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    struct s_80043F2C* field_C;
} s_80043F2C;
STATIC_ASSERT_SIZEOF(s_80043F2C, 16);
// Maybe same.
typedef struct
{
    u8  field_0;
    s8  unk_1[3];
    s32 field_4;
    s8  unk_2[3];
    s32 field_C;
} s_80043E50Sub;
STATIC_ASSERT_SIZEOF(s_80043E50Sub, 16);

typedef struct
{
    s32            field_0;
    s32            field_4;
    u8             elementCount_8;
    s8             unk_C[9];
    s_80043E50Sub* elements_14;
} s_80043E50;

typedef struct
{
    s8  unk_0;
    s8  field_1;
    s8  field_2;
    s8  field_3;
    s8  unk_4[80];
    s32 field_54;
    s32 field_58;
} s_80044044;

typedef struct
{
    s16 field_0; // Flags?
} s_8008D850;

// Maybe level stream data?
typedef struct
{
    s32 field_0;
    s32 queueEntryIdx_4;
    s16 fileChunkCoordX_8;
    s16 fileChunkCoordZ_A;
    s32 field_C;           // Something to do with distance from file chunk edge.
    s32 field_10;          // Something to do with distance from file chunk edge.
} s_80043338;

// Maybe s_Skeleton?
typedef struct
{
    s8  unk_0;
    u8  field_1;
    s8  unk_2[2];
    s32 field_4;
    s8  unk_8[12];
    s32 field_14;
    s32 unk_18; 
} s_80043B70;

typedef struct
{
    s8 unk_0;
    u8 field_1;
} s_80043BA4;

typedef struct
{
    s8 unk_0[14];
    u8 field_E;
    u8 field_F;
} s_8008A35C;

typedef struct
{
    u8  field_0;
    s8  unk_1;
    s16 field_2;
    s8  unk_4[4];
    s32 field_8;
} s_8008E51C;

typedef struct
{
    u8 unk_0[6];
    u8 field_6;
} s_800A992C_sub; // Size: 80?

typedef struct
{
    s8              field_0;
    s8              field_1; // Index.
    s8              unk_2[2];
    u32             field_4; // Size of `field_8` array?
    s_800A992C_sub* field_8;
    s32             field_C;
    s32             field_10;
    s32             field_14;
} s_800A992C;
STATIC_ASSERT_SIZEOF(s_800A992C, 24);

typedef struct
{
    u8  field_0;
    u8  unk_1[3];
    u32 field_4    : 24;
    u8  field_4_24 : 8;
    u32 field_8    : 24;
    u8  field_8_24 : 8;
} s_800AA894;
STATIC_ASSERT_SIZEOF(s_800AA894, 12);

typedef struct
{
    u8  field_0;
    u8  unk_1;
    u16 field_2;
    u8  field_4;
    s8  field_5;
} s_800ACAA8;

typedef struct
{
    s8 field_0;
    s8 unk_1[5];
    s8 field_6;
    s8 unk_7;
    u8 field_8;
    u8 field_9;
    s8 unk_A[5];
    s8 field_F;
    u8 field_10;
    u8 field_11;
    s8 field_12[6];
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

typedef struct
{
    u8  field_0;
    s8  unk1;
    u8  field_2;
    u8  unk3;
    u8* field_4;
    u8  field_8;
    u8  unk9;
    u8  unkA;
    u8  unkB;
    u8* field_C;
    u8* field_10;
    s8  unk_11[4075];
    s32 queueIdx_1000;
} s_800BE9FC;

typedef struct
{
    s32 field_0[16];
} s_800B5C40;

typedef struct
{
    s32 unk_0[2048];
} s_800B5D04;

typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800BCDA8;
STATIC_ASSERT_SIZEOF(s_800BCDA8, 4);

// Maybe a collection of matrices.
typedef struct
{
    s32 flags_0;
    s8  unk_4[12];
    s8  field_10;
    s8  unk_11[7];
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 24);

// PROBABLY skeleton data.
typedef struct
{
    u8      boneCount_0;
    u8      boneIdx_1; // Current bone index? Used in traversal.
    s8      field_2;
    s8      field_3;
    s32     field_4;
    s_Bone* bones_8;

    // Maybe incorrect.
    s8 field_C[3]; // Maybe struct similar to `s_Bone` but smaller.
    u8 field_10;   // Some count related to bone hierarchy.
    s8 unk_11;
    s8 field_12;
    s8 field_13;
    s8 field_14;
    s8 unk_15[8];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 28);

typedef struct
{
    s8 field_0;
    u8 unk_1;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
} s_800BCE18_0_0_C;

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 unk_4;
    u8  field_6;
    u8  unk_7;
    s32 field_8;
    s_800BCE18_0_0_C* field_C;
} s_sub_800BCE18_0;

// Looks similar to `s_Skeleton`
typedef struct
{
    u8            field_0;
    u8            field_1;
    u8            unk_2[2];
    s32           field_4;
    void*         field_8;
    s_FsImageDesc field_C;
    s_Skeleton    field_14; // Could be different struct?
} s_800BCE18_0_CC; // Unknown size.

typedef struct
{
    s_sub_800BCE18_0* field_0;
    s8                field_4;
    u8                unk_5[3];
    VECTOR3           field_8; // Vaguely assumed. Chane done for matching `func_8003C368`.
    s32               field_14;
    s_800BCE18_0_CC*  field_18[Chara_Count]; // Per-character data? So far only seen accessed by `map4_s03::800D59EC` which calls `func_8003BE50(Chara_Twinfeeler)`.
    s_800BCE18_0_CC   field_CC;
    u8                unk_D0[368];
    s32               field_26C;
    u8                unk_270[752];
} s_800BCE18_0;
STATIC_ASSERT_SIZEOF(s_800BCE18_0, 1376);

typedef struct
{
    s32 field_0;
    s32 field_4;
    u8  unk_8;
    s8  field_9;
} s_800BCE18_2BEC_0_10;

typedef struct
{
    s8                    unk_0[8];
    s_800BCE18_2BEC_0_10* field_8;
    s8                    unk_C[4];
    s_800BCE18_2BEC_0_10  field_10[1]; // Unknown length.
} s_800BCE18_2BEC_0;

typedef struct
{
    s_800BCE18_2BEC_0* field_0;
    s32                gsCoordinate0_4 : 18; // Used as `GsCOORDINATE2::coord.t[0].`
    s32                gsCoordinate1_4 : 14; // Used as `GsCOORDINATE2::coord.t[1].`
    s32                gsCoordinate2_8 : 18; // Used as `GsCOORDINATE2::coord.t[2].`
    s32                unk_8_18        : 14;
    s32                vx_C            : 10;
    s32                vy_C            : 12;
    s32                vz_C            : 10;
} s_800BCE18_2BEC;
STATIC_ASSERT_SIZEOF(s_800BCE18_2BEC, 16);

typedef struct
{
    s32           field_0;
    s32           field_4;
    char*         field_8;
    s_FsImageDesc imageDesc_C;
    s_800BE9FC*   field_14;
    s32           field_18;
    s32           field_1C;
    s32           field_20;
} s_800BCE18_1BAC;

typedef struct
{
    s_800BCE18_0      field_0[4];
    u8                unk_1580[204];
    s_800BCE18_0_CC   field_164C;
    u8                unk_1650[1328];
    s_800BCE18_1BAC   field_1BAC;
    u8                unk_1BD0[8];
    s32               field_1BD8;
    VC_CAMERA_INTINFO vcCameraInternalInfo_1BDC; // Debug camera info.
    s_800BE9FC        field_1BE4;
    s32               field_2BE8;
    s_800BCE18_2BEC   field_2BEC[1]; // Unknown size, valid count determined by `field_2BE8`?
} s_800BCE18;
STATIC_ASSERT_SIZEOF(s_800BCE18, 11260);

typedef struct
{
    s8  unk_0[28];
    s16 field_1C;
    s8  unk_1E[304];
    s32 field_150;
    s32 field_154;
    s32 field_158;
    s8  unk_15A[1060];
    s32 field_580;
    s32 field_584;
    s32 field_588;
    // More may follow.
} s_800C1020;

typedef struct
{
    s32 field_0;
    u8  unk_4[4];
    s16 field_8;
    s16 field_A;
    u8  unk_C[16];
} s_800C117C;
STATIC_ASSERT_SIZEOF(s_800C117C, 28);

typedef struct
{
    u8 field_0;
    u8 field_1;
} s_800C15F0;

typedef struct
{
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    u16 field_8[1]; // Unknown size.
    s16 field_A;
    s16 field_C;
    u16 field_E;
    union
    {
        s8  field_0[3];
        u16 field_01;
    } field_F;
    u8  field_14;
    u8  field_15;
    s8  field_16;
    s8  field_17;
} s_800C1658;

typedef struct
{
    u8 field_0;
    s8 field_1;
    u8 field_2;
    s8 field_3;
} s_800C1670;

// Sound data struct?
typedef struct
{
    s16 volumeXa_0; // Might be wrong, but it's used in a `Sd_SetVolBXa` call.
    s16 field_2;
    u16 field_4;
    s16 field_6;
    s16 volumeBgm_8; // Might be wrong, but it's used in a `Sd_SetVolBgm` call.
    s16 field_A;
    s8  field_C;     // (?) volume?
    s8  field_D;     // BGM volume?
    s8  field_E;     // SE volume?
} s_800C1678;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
} s_800C1688;

typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
} s_800C1698;

typedef struct
{
    s8  field_0;
    s8  unk_1[1];
    u16 field_2;
    u32 field_4;
    s32 field_8;
} s_800C37D4;
// Maybe the same.
typedef struct
{
    u8  field_0;
    s8  unk_1[3];
    u32 field_4;
    s32 field_8;
} s_800C37D8;

typedef struct
{
    s8 field_0;
    s8 field_1;
} s_800C38B0;

typedef struct
{
    VECTOR  field_0;
    SVECTOR field_10;
    VECTOR  field_18;
} s_800C3BE8;

typedef struct
{
    s8      field_0;
    u8      field_1;
    s8      field_2;
    s8      field_3;
    s32     field_4;
    s32     field_8;
    s8      unk_C[12];
    s32     field_18;
    u8      field_1C;
    u8      field_1D;
    u8      field_1E;
    s32     field_20;
    s8      field_24;
    s8      field_25;
    s8      field_26;
    s8      unk_27;
    s8      field_28;
    s8      field_29;
    s8      field_2A;
    s16     field_2C;
    s16     field_2E;
    s16     field_30;
    s16     field_32;
    s16     field_34;
    s16     field_36;
    s16     field_38;
    s16     field_3A;
    s16     field_3C;
    s32     field_4C;
    s32     field_50;
    s8      unk_54[24];
    VECTOR3 field_60; // Type assumed.
} s_800C4168;

typedef struct
{
    s32 field_0;
    s8  unk_4[4];
    s8  field_8;
} s_800C4620;

typedef struct
{
    u8      field_0;
    u8      field_1;
    u8      field_2;
    u8      field_3;
    s8      unk_4[4];
    s16     field_8;
    s16     field_A;
    VECTOR3 field_C;
    s8      unk_18[4];
    s32     field_1C;
    s32     field_20;
} s_800C4818;

/** Holds file IDs of anim/model/texture for each `e_ShCharacterId`, along with some data used in VC camera code. */
typedef struct
{
    s16   animFileIdx;
    s16   modelFileIdx;
    s16   textureFileIdx : 16;
    s16   field_6        : 10;
    u16   field_6_10     : 6;
    void* field_8;
    u16   field_C_0 : 2;
    s32   field_C_2 : 14;
    u16   unk_C_16  : 16;
} s_CharaFileInfo;
STATIC_ASSERT_SIZEOF(s_CharaFileInfo, 16);

// Contains animation data? Size is rather small, so if it does, it would be indices to
// larger arrays containing actual data.
typedef struct
{
    s8  unk_0[12];
    s16 field_C;
    s8  unk_10[2];
} s_MaybeCharacterAnim;

typedef struct
{
    SVECTOR3 posTarget_0;
    SVECTOR3 lookAtTarget_6;
    s16      field_C[2]; // `field_C[1]` gets passed to `vcChangeProjectionValue`.
} s_DmsKeyframeCamera;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCamera, 16);

typedef struct
{
    SVECTOR3 position_0;
    SVECTOR3 rotation_6;
} s_DmsKeyframeCharacter;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCharacter, 12);

typedef struct
{
    s16       keyframeCount_0;
    u8        svectorCount_2;
    u8        field_3;        // Usually 0, but sometimes filled in, possibly junk data left in padding byte.
    char      name_4[4];      // First 4 chars of name. E.g. Code checks for "DAHLIA", file is "DAHL".
    SVECTOR3* svectorPtr_8;   // Pointer to `SVECTOR3`s. Unknown purpose.
    union
    {
        s_DmsKeyframeCharacter* character;
        s_DmsKeyframeCamera*    camera;
    } keyframes_C;
} s_DmsEntry;
STATIC_ASSERT_SIZEOF(s_DmsEntry, 16);

typedef struct
{
    s16 start;
    s16 duration;
} s_DmsInterval;
STATIC_ASSERT_SIZEOF(s_DmsInterval, 4);

typedef struct
{
    u8             isLoaded_0;
    u8             characterCount_1;
    u8             intervalCount_2;
    u8             field_3; // Usually 0, but sometimes filled in.
    u32            field_4; // Unknown, correlates with DMS file size.
    s_DmsInterval* intervalPtr_8;
    VECTOR3        origin_C; // Origin point, gets added to character positions.
    s_DmsEntry*    characters_18;
    s_DmsEntry     camera_1C;
} s_DmsHeader;
STATIC_ASSERT_SIZEOF(s_DmsHeader, 44);

/** @brief Used for normal credits screen. */
typedef struct
{
    s16  field_0;  /** Prim vertex X. */
    s16  field_2;  /** Prim vertex Y. */
    s16  field_4;  /** Width? */
    s8   field_6;  /** Height?  */
    s8   field_7;  /** Blend flag. */
    s32  field_8;  /** Rgb24 color + code. */
    s16* field_C;  /** Points to 0x801E5C24, data size 400. */
    s32* field_10; /** Points to 0x801E5E24, data size 28, rgb24 + code. */
    u16  field_14; /** Tpage for `setDrawTPage`, calculated from `field_18` with `func_801E434C`. */
    s16  field_16; /** Clut XY. */
    u32  field_18; /** Texture UV. */
} s_800AFE08;
STATIC_ASSERT_SIZEOF(s_800AFE08, 28);

/** @brief Used for UFO ending credits screen. */
typedef struct
{
    s16  field_0;  /** Prim vertex X. */
    s16  field_2;  /** Prim vertex Y. */
    s16  field_4;  /** Width? */
    s8   field_6;  /** Height?  */
    s8   field_7;  /** Blend flag. */
    s32  field_8;  /** Rgb24 color + code. */
    s16* field_C;  /** Points to 0x801E5C24, data size 400. */
    s32* field_10; /** Points to 0x801E5E40, data size 28, rgb24 + code. */
    u16  field_14; /** Tpage for `setDrawTPage`, calculated from `field_18` with `func_801E4BD4`. */
    s16  field_16; /** Clut XY. */
    u32  field_18; /** Texture UV. */
    s32  field_1C;
    s16  field_20;
    s16  field_22;
    s32  field_24;
    s32  field_28;
    s32  field_2C;
    s32  field_30;
    s32  field_34;
    s32  field_38;
    s32  field_3C;
    s32  field_40;
    s32  field_44;
    s32  field_48;
    s32  field_4C;
    s32  field_50;
    s32  field_54;
} s_800AFE24; // Size: 85

/** Part of map headers, pointer passed to `Chara_PositionUpdateFromParams`. */
typedef struct _AreaLoadParams
{
    s32 char_x_0;
    u32 mapIdx_4_0     : 5;
    u32 field_4_5      : 4;
    u32 field_4_9      : 3;
    u32 field_4_12     : 4;
    u32 rotationY_4_16 : 8;
    u32 field_4_24     : 8;
    s32 char_z_8;
} s_AreaLoadParams;

typedef struct _SpawnInfo
{
    q19_12 positionX_0;
    s8     charaId_4;   /** `e_ShCharacterId` */
    u8     rotationY_5; /** Multiplied by 16 to get `s_SubCharacter.rotation_24.vy` value. */
    s8     flags_6;     /** Copied to `stateStep_3` in `s_Model`, with `state_2 = 0`. */
    s8     unk_7;
    q19_12 positionZ_8;
} s_SpawnInfo;
STATIC_ASSERT_SIZEOF(s_SpawnInfo, 12);

typedef struct s_UnkStruct_MapOverlay
{
    u8 field_0[34]; /** `e_InventoryItemId` */
} s_UnkStruct_MO;

typedef struct
{
    u8 unk_0[6];
    u8 field_6;
} s_UnkStruct2_MO;

/** TODO: `g_MapOverlayHeader` is part of the map overlay BIN files. Maybe should be moved to `maps/shared.h`. */
typedef struct _MapOverlayHeader
{
    s_UnkStruct2_MO*  field_0;
    s8                (*getMapRoomIdxFunc_4)(s32 x, s32 y); // Called by `func_80036420`.
    s8                field_8;
    s8                unk_9[3];
    s8                unk_C[4];
    s32               (*func_10)();
    s8                field_14;
    u8                field_15;
    s8                field_16;
    s8                field_17;
    void              (**func_18)();
    s_AreaLoadParams* mapAreaLoadParams_1C;
    void              (**mapEventFuncs_20)(); /** Points to array of event functions. */
    s8                unk_24[4];
    GsCOORDINATE2*    field_28;
    s_UnkStruct_MO*   field_2C;
    char**            mapMessageStrings_30; /** Points to array of `char*` for each displayed message in the map. */
    s_AnimInfo*       animInfo_34;
    s8                unk_38[8];
    void              (*func_40)();
    void              (*func_44)();
    s8                unk_48[4];
    s_func_800625F4*  field_4C;
    s8                unk_50[16];
    s8                unk_60[88];
    void              (*func_B8)(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);
    void              (*func_BC)(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);
    s8                unk_C0[8];
    void              (*func_C8)();
    void              (*func_CC)(s32);
    s32               (*func_D0)(s32, void*, s16, s32); // 0x800C964C
    s32               (*func_D4)(s_SubCharacter*); // Assumed return type.
    void              (*func_D8)(); // Assumed return type.
    void              (*func_DC)(s_SubCharacter*); // Assumed return type.
    s8                unk_E0[4];
    s32               (*func_E4)(s_SubCharacter*, s_SubCharacter*); // Assumed return type.
    s64               (*func_E8)(s_SubCharacter*); // Is it really `s64`???
    s32               (*func_EC)();
    s8                unk_F0[24];
    s32               (*func_108)(s32, s32);
    s8                unk_10C[24];
    void              (*func_124)(s_SubCharacter*); // Assumed return type.
    s32               (*func_128)(s_SubCharacter*); // Assumed return type.
    s32               (*func_12C)(s_SubCharacter*); // Assumed return type.
    s8                unk_130[4];
    s32               (*func_134)(s_SubCharacter*); // Assumed return type.
    s32               (*func_138)(s_SubCharacter*); // Assumed return type.
    s32               (*func_13C)(s32, s32, void*, s16, s32); // 0x800C96B8
    s8                unk_140[40];
    void              (*func_168)(void*, void*, void*);
    void              (*func_16C)(VECTOR3*, s16);
    s8                unk_170[36];
    void              (*charaUpdateFuncs_194[Chara_Count])(s_SubCharacter*, void*, s32); /** Guessed params. Funcptrs for each `e_ShCharacterId`, set to 0 for IDs not included in the map overlay. Called by `func_80038354`. */
    s8                charaGroupIds_248[4];                                              /** `e_ShCharacterId` values where if `s_SpawnInfo.charaId_4` == 0, `charaGroupIds_248[0]` is used for `charaSpawnsA_24C` and `charaGroupIds_248[1]` for `charaSpawnsB_30C`. */
    s_SpawnInfo       charaSpawnsA_24C[16];                                              /** Array of chara type/position/flags, flags_6 == 0 are unused slots? Read by `func_80037F24`. */
    s_SpawnInfo       charaSpawnsB_30C[16];                                              /** Array of chara type/position/flags, flags_6 == 0 are unused slots? Read by `func_80037F24`. */
    VC_ROAD_DATA      roadDataList_3CC[48];
    // TODO: A lot more in here.
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 2124); // Size incomplete.

typedef struct
{
    s8 field_0;
    s8 field_1;
} s_800BCD78;

typedef struct
{
    u8 field_0;
    u8 field_1;
} s_800A9F80;

// ========
// GLOBALS
// ========

extern s_FsImageDesc g_MainImg0; // 0x80022C74 - TODO: part of main exe, move to main/ headers?

/** Some sort of struct inside RODATA, likely a constant. */
extern s32 D_8002500C;

extern s8* D_8002510C;

/** Default key bindings. Multiple configs probably? */
extern s_ControllerConfig D_8002511C[];

extern s_800252BC const D_800252BC[];

extern u8 D_80025D6C[];

extern u32 D_80025DC0[];

extern char D_80028544[0x10];

extern RECT D_80028A20;

extern RECT D_8002ABA4;

extern s_8002AC04 D_8002AC04[];

extern s_800BE9FC D_8002B2CC;

extern u8 D_800A8E58;

extern DR_MODE D_800A8E5C[];

extern TILE D_800A8E74[];

extern s32 D_800A8E94;

extern DR_MODE D_800A8E98[];

extern POLY_G4 D_800A8EB0[];

extern s32 D_800A8F40;

extern GsOT D_800A8F9C[];

extern s_FsImageDesc D_800A8FF4;

extern s_FsImageDesc D_800A8FFC;

extern s_FsImageDesc D_800A9004;

extern s_FsImageDesc D_800A9014;

extern s_FsImageDesc D_800A901C;

extern s_FsImageDesc D_800A9024;

/** Save screen background image. */
extern s_FsImageDesc D_800A902C;

extern s_FsImageDesc D_800A9034;

extern s_FsImageDesc D_800A903C;

extern s_FsImageDesc D_800A9044;

extern s_FsImageDesc D_800A904C;

extern s_FsImageDesc D_800A9054;

extern s_FsImageDesc D_800A9064;

extern s_FsImageDesc D_800A906C;

extern s_FsImageDesc D_800A9074;

extern s_FsImageDesc D_800A9094; // Used in `Ai_Twinfeeler_TextureLoad` to load `TEST/WARMTEST.TIM`.

extern s_FsImageDesc D_800A909C; // Passed to `func_800917C0` for loading `TIM/FONT24.TIM`.

/** Array containg file IDs used for each `e_ShCharacterId`, used in `Fs_QueueStartReadAnm`. */
extern s_CharaFileInfo g_Chara_FileInfo[45]; // 0x800A90FC

extern s_sub_StructUnk3 D_800A93CC[];

extern s_StructUnk3 D_800A952C;

extern u16 D_800A9774[];

extern u16 D_800A9858[];

extern s_800C37D4 D_800A986C[];

extern s32 D_800A9A20;

extern s32 D_800A9A24;

extern s32 D_800A9A28;

extern s8 D_800A98FC[];

extern s32 D_800A9EAC;

extern s32 D_800A9EB0;

extern s_FsImageDesc D_800A9EB4;

extern s_FsImageDesc D_800A9EBC;

extern s_FsImageDesc D_800A9EC4;

extern s_FsImageDesc D_800A9FA8;

extern s32 D_800A9768;

extern s32 D_800A976C;

/** Function pointer array, maybe state funcs of some kind. */
extern void (*D_800A977C[])();

/** Related to sound commands. */
extern u16 D_800A9804[];

extern u16 D_800A98AC[];

extern s_800A992C D_800A992C[];

extern u8 D_800A9944;

/** Player anim info? */
extern s_AnimInfo D_800A998C;

/** Current player anim index store? */
extern u8 D_800A9990;

/** Used in `func_800D929C` from `map0_s00.c`. */
extern s32 D_800A999C;

extern s32 D_800A99A0;

extern u8 D_800A99A4[];

extern s32 D_800A99AC;

extern s16 D_800A99B0;

/** Array of indices? */
extern s8 D_800A99B4[];

/** Array of indices? */
extern s8 D_800A99CC[];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A0C; // Old IDB name `FS_AllFilesLoaded`, though FS code doesn't set it.

/** `e_SysState` */
extern s32 D_800A9A10;

extern s32 D_800A9A1C;

extern void (*D_800A9A2C[])(); // SysState func table.

extern s32 D_800A9A68;

extern s32 g_MainMenuState;

extern s32 g_MainMenu_SelectedOptionIdx;

extern u32 D_800A9A7C;

/** Counts the amount of times that demos has been play in the current game session. */
extern s8 g_Demo_ReproducedCount;

extern s32 g_MainMenu_NewGameSelectedDifficultyIdx;

extern s32 D_800A9A88;

extern RECT D_800A9A6C; // `RECT<320, 256, 160, 240>`, only used in `SysState_Fmv_Update`?

extern u32 D_800A9AAC[];

extern s32 D_800A9ECC;

extern s32 D_800A9ED0;

extern s32 D_800A9ED4;

extern s32 D_800A9ED8;

extern s32 D_800A9EDC;

extern s32 D_800A9EE0;

extern s32 D_800A9EE4;

extern s32 D_800A9EE8;

extern s32 D_800A9EEC;

extern s32 D_800A9EF0;

extern s32 D_800A9EF4;

extern s32 D_800A9EF8;

extern s32 D_800A9EFC;

extern s32 D_800A9F00;

extern s32 D_800A9F04;

extern s32 D_800A9F08;

extern s32 D_800A9F0C;

extern s32 D_800A9F10;

extern s32 D_800A9F14;

extern s32 D_800A9F18;

extern s32 D_800A9F1C;

extern s32 D_800A9F20;

extern s32 D_800A9F28;

extern s32 D_800A9F2C;

extern s32 D_800A9F30;

extern s32 D_800A9F34;

extern s32 D_800A9F38;

extern s32 D_800A9F3C;

extern s32 D_800A9F40;

extern s32 D_800A9F44;

extern s32 D_800A9F48;

extern s32 D_800A9F4C;

extern s32 D_800A9F50;

extern s32 D_800A9F54;

extern s32 D_800A9F58;

extern s32 D_800A9F60;

extern s32 D_800A9F64;

extern s32 D_800A9F68;

extern s32 D_800A9F6C;

extern s32 D_800A9F74;

extern s32 D_800A9F78;

extern s32 D_800A9F7C;

extern s_800A9F80 D_800A9F80;

extern s_800A9F80 D_800A9F84;

extern s_800A9F80 D_800A9F88;

extern s_800A9F80 D_800A9F8C;

extern s_800A9F80 D_800A9F98;

extern u32 D_800A9FB0;

extern s32 D_800A9FB4[];

extern u8* D_800A9FC8[];

extern s32* D_800A9FD8[];

extern u8* D_800A9FDC[];

extern s_800C37D8 D_800AA274[];

extern u8 D_800AA5E0[];

extern u8 D_800AA604[][16];

extern s_800AA894 D_800AA894[];

extern s16 g_StringColorId; // 0x800AD498

extern s32 D_800AD49C;

extern s32 D_800AE178;

extern s32 D_800AE180;

extern u8 D_800AE185;

extern u8 D_800AE186;

extern s8 D_800AE187;

extern s32 D_800AE190;

extern s16 D_800AE198;

extern s16 D_800AE19A;

extern s32 D_800AE19C;

extern s32 D_800AE1AC;

extern s32 D_800AE1B0;

extern s16 D_800AF210;

extern s16 D_800AF212;

extern s_MaybeCharacterAnim g_MaybePlayerAnims[];

extern s32 D_800AFC7C;

extern s32 D_800AFC90;

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern s32 (*D_800AFD08[])(s_SysWork_2514* arg0, s32 arg1, s_8002AC04* ptr, u32* arg3); // Function pointer array.

extern s32 D_800AFD9C;

extern s32 D_800AFDEC;

extern s_800AFE08 D_800AFE08;

extern s_800AFE24 D_800AFE24;

extern s32 D_800B2618;

extern s32 D_800B261C;

extern s32 D_800B2620;

extern DVECTOR g_Gfx_DebugStringPosition0;

extern DVECTOR g_Gfx_DebugStringPosition1;

extern s32 D_800B5C28;

extern s32 D_800B5C30;

extern s_800B5C40 D_800B5C40[];

// TODO: Overlapped variables
extern s8 D_800B5C50[][64];

extern s8 D_800B5C54[][64];

extern s8 D_800B5C58[][64];

extern s32 D_800B5C7C;

extern s_800B5D04 D_800B5D04[];

extern u8 D_800B7CC4[][8192];

extern u8 D_800BC74F;

extern u16 D_800BCCB0;

extern u16 D_800BCCB2;

/** @brief Seems to handle the screen fade effect.
 *
 * Accessed by `credits`, `options`, and `saveload`.
 *
 * 0-1   - Nothing.
 * 2-5   - Fades to black and keeps the screen black.
 * 6-7   - Fades from black.
 * 10-15 - Fades to white and keeps the screen white.
 * 16    - Fades to black.
 *
 * @note Other values causes flickers, likely a bug.
 */
extern s32 g_Gfx_ScreenFade;

extern s16 D_800BCD28;

extern s32 D_800BCD48;

extern s8 D_800BCD50[8];

extern u32 D_800BCD58;

extern s32 D_800BCD5C;

extern s32 D_800BCD60;

extern s32 D_800BCD64;

extern s32 D_800BCD68;

extern s32 D_800BCD6C;

extern s32 D_800BCD70;

extern s32 D_800BCD74;

extern s_800BCD78 D_800BCD78; // `s_800BCD78` might also encompass vars below.

extern u8 D_800BCD79;

extern u8 D_800BCD7A;

extern s8 D_800BCD7B;

extern s32 D_800BCD84;

extern s32 D_800BCD90[];

extern s_800BCDA8 D_800BCDA8[2];

extern s_AreaLoadParams D_800BCDB0;

extern s32 D_800BCDC0[];

extern u8 D_800BCDD4;

extern s8* D_800BCDE0; // Type assumed.

extern s16 D_800BCDE8[];

extern u16 D_800BCE14;

extern s_800BCE18 D_800BCE18;

extern s_800C1020 D_800C1020;

extern s32 D_800C1450;

extern s_800C117C D_800C117C[];

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s32 D_800C15B8;

extern s16 D_800C15BC;

extern s16 D_800C15BE;

extern u16 D_800C15C0;

extern s16 D_800C15C2;

extern s16 D_800C15C4;

extern s16 D_800C15C6;

extern s16 D_800C15C8;

extern u16 D_800C15CA;

extern u32 D_800C15CC;

extern u16 D_800C15D0;

extern u32 D_800C15D4;

extern s32 D_800C15D8;

extern s32 D_800C15DC; // Index.

extern s32 D_800C15E0;

extern s_800C15F0 D_800C15F0;

extern u16 D_800C15F8[];

extern s16 D_800C1628[];

extern s_800C1658 D_800C1658;

extern u16 D_800C165A;

extern u16 D_800C1666;

extern u8 D_800C166A;

extern s8 D_800C166C;

extern s8 D_800C166D;

extern u8 D_800C166E;

extern u8 D_800C166F;

extern u8 D_800C1671;

extern s16 D_800C167A;

extern s16 D_800C167C;

extern s16 D_800C167E;

extern s_800C1670 D_800C1670;

extern s_800C1678 D_800C1678;

extern s16 D_800C1680;

extern u8 g_Sd_VolumeBgm; // 0x800C1685

extern u8 g_Sd_VolumeXa; // 0x800C1686

extern u8 g_Sd_VolumeSe; // 0x800C1684

extern u8 g_Sd_ReverbDepth; // 0x800C1687;

extern u8 D_800C1673;

extern s_800C1688 D_800C1688;

extern s_800C1698 D_800C1698;

extern s16 D_800C16A4;

extern u8 D_800C16A8[];

extern s32 D_800C16C8; // Type assumed.

extern s32 D_800C3920;

extern GsCOORD2PARAM D_800C3928;

extern s8 D_800C3950;

extern s32 D_800C3954;

extern s32 D_800C3958;

extern s32 D_800C395C;

extern s8 D_800C3960;

extern s8 D_800C3961;

extern s8 D_800C3962;

extern u8 D_800C3963;

extern s32 D_800C3990; // Boolean.

extern s32 D_800C3994;

extern s32 D_800C3998;

extern s32 D_800C399C; /** `s_InventorySelectionId` */

extern u8 D_800C37D0;

extern s_800C37D8* D_800C37D8;

extern s_800C38B0 D_800C38B0;

extern s32 D_800C38B4;

extern u16 D_800C4478; // Might be struct.

extern s32 D_800C4710[];

extern u8 D_800C37C8;

extern u32 D_800C37CC;

extern s_800C37D4* D_800C37D4;

extern u8 D_800C37DC;

extern u8 D_800C37DD;

/** String position. */
extern DVECTOR g_StringPosition; // 0x800C38A8

/** String X position as `s32`. It's unclear why there are two. */
extern s32 g_StringPositionX1; // 0x800C38AC

/** String glyph sprite. */
extern GsSPRITE D_800C38F8;

extern s16 D_800C38FC;

extern s16 D_800C38FE;

extern s16 D_800C391C;

extern s16 D_800C391E;

extern s8 D_800C39A0;

extern GsF_LIGHT D_800C39A8[][2];

extern GsF_LIGHT D_800C3A88[];

extern GsCOORDINATE2 D_800C3AE8;

extern SVECTOR3 D_800C3B38;

extern VbRVIEW D_800C3B48;

extern u8 D_800C3BB8[48];

extern s_800C3BE8 D_800C3BE8[10];

extern GsDOBJ2 D_800C3D78[];

extern u8 D_800C3E40;

extern GsCOORDINATE2 D_800C3E48[];

extern u8 D_800C4169;

extern u8 D_800C416A;

extern s_800C4168 D_800C4168;

extern s32 D_800C4180;

extern s32 D_800C454C;

extern s32 D_800C4558;

extern s32 D_800C455C;

extern s16 D_800C457E;

extern u16 D_800C4580;

extern u16 D_800C4582;

extern u16 D_800C4584;

extern u16 D_800C4586;

extern s8 D_800C4588;

extern s16 D_800C45AC;

extern s16 D_800C45AE;

extern VECTOR3 D_800C45B0; // Assumed type

extern s16 D_800C45BC;

extern s16 D_800C45BE;

extern s16 D_800C45C0;

extern u8 D_800C45C9;

extern s16 D_800C45E8;

extern s16 D_800C45F0;

extern s16 D_800C4604;

extern u8 D_800C4561;

extern s8 D_800C4562;

/** D_800C457C could be related to animations that play during cutscenes.

 * Called by:
 * - 'func_800D2C7C' in map0_s00.c
 * - 'func_800D2D2C' in map0_s00.c
 
 Its value changes during cutscenes when Harry does any of the following
 actions:
 
 * 0 - Nothing
 * 1 - Walking
 * 3 - Moves to the right?
 * 4 - Moves to the left
 
 However this behaviour is irregular. After the first in-game dialogue
 with Harry, the value is kept as 1 (even when he is not walking or in
 a cutscene) until the next dialogue triggers (when Harry look sees
 Cheryl and the second FMV plays). Something similar happens on the
 next overlay and its value is 1 during the first
 cutscene and doesn't change until the player makes an input.
*/
extern u8 D_800C457C;

extern VECTOR3 D_800C45F8;

extern u8 D_800C4606;

extern s_800C4620 D_800C4620;

extern VECTOR3 D_800C4640[][8]; // Or struct?

extern s32 D_800C46A0;

extern s16 D_800C4700[];

extern s16 D_800C4702;

extern s_800C4818 D_800C4818;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

extern s32 D_800C48F0;

extern RECT D_801E557C[];

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

extern s16 D_800C6E26;

extern s16 D_800C6E8E;

extern u8 D_800C6E90;

extern s_800ACAA8 D_800ACAA8[];

extern u8 D_800AD480[24];

extern s_800AD4C8 D_800AD4C8[];

extern s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

// ==========
// FUNCTIONS
// ==========

s32 func_8002E76C(s32 idx);

/** Initializer for something before the game loop. */
void func_8002E7BC();

void func_8002E830();

void func_8002E85C();

void func_8002E86C();

s32 func_8002E898();

void func_8002E8D4();

void func_8002E8E4();

s32 func_8002E914();

s32 func_8002E9A0(s32 idx);

// `Gfx_DrawBackgroundImage`
/** Draws a background image. */
void Gfx_BackgroundSpriteDraw(s_FsImageDesc* image);

void func_800317CC(s_FsImageDesc* image0, s_FsImageDesc* image1, s16 arg2);

void func_80031AAC(s_FsImageDesc* image);

s32 func_80031CCC(s32 arg0);

void Gfx_DebugStringPosition(s16 x, s16 y);

/** Draws debug strings using 8x8 glyphs from `FONT8.TIM`. Valid `char` range: `[42, 95]` (`*` to `_`). */
void Gfx_DebugStringDraw(char* str);

void func_8003260C(); // Return type assumed.

char* Math_IntegerToString(s32 widthMin, s32 value);

void func_800321EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Gfx_ScreenRefresh(s32 screenWidth, s32 isInterlaced);

void Gfx_Init(s32 screenWidth, s32 isInterlaced);

void Settings_ScreenXYSet(s32 x, s32 y);

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y);

void func_800325A4(DR_MODE* arg0);

int func_800325F8();

void func_80032904();

/** Draws some string in display space. */
void func_80032CE8();

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

void Chara_PositionUpdateFromParams(s_AreaLoadParams* params);

void func_8003943C();

/** `SysState_Fmv` update function.
 * Movie to play is decided by `2072 - g_MapEventIdx`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update();

void func_8003B550();

void Gfx_MainMenu_MainTextDraw();

s32 func_8003BD2C();

void func_8003C1AC(s_800BCE18_0_CC* arg0);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003C850();

void func_8003C878(s32 arg0);

void func_8003C8F8(s_func_8003C8F8* arg0, s8* arg1);

void func_8003C92C(s_800BCE18_2BEC_0* arg0, VECTOR3* arg1, SVECTOR3* arg2);

void func_8003CD6C(s_PlayerCombat* arg0);

s32 func_8003CDA0(s32 itemIdx);

void func_8003D01C();

void func_8003D03C();

s32 func_8003D444(s32 idx);

void func_8003D550(s32 arg0, s32 arg1);

void func_8003D468(s32, s32); // Called by some chara init funcs, similar to `func_8003DD80`?

void func_8003D6A4(s_800BCE18_0_CC* arg0);

/** Return type assumed. */
void func_8003D160();

void func_8003D5B4(s8 arg0);

void func_8003D6E0(s32 arg0, s32 arg1, void* arg2, s_FsImageDesc* arg3);

/** Param types assumed. */
void func_8003DD80(s32 idx, s32 arg1); // Called by some chara init funcs.

void func_8003E740();

void func_8003ED74(s32 arg0, s32 arg1);

void func_8003EDA8();

void func_8003EF10(s32 idx0, s32 idx1, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

s32 func_8003F4DC(GsCOORDINATE2** arg0, SVECTOR* rot, s32 arg2, s32 arg3, u32 arg4, s_SysWork* sysWork);

u32 func_8003F654(s_func_8003F654* arg0);

s32 func_8003F6F0(s32 arg0, s32 arg1, s32 arg2);

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight);

/** Computes the weighted average of `a` and `b`. */
s32 Math_GetWeightedAverage(s32 a, s32 b, s32 weight);

void func_8003FCB0(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 arg3);

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight0, s32 weight1, s32 alphaTo);

void func_8003FE04(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 alphaTo);

s32 func_8003FEC0(s_sub_StructUnk3* arg0);

void func_8003FF2C(s_StructUnk3* arg0);

void func_80040004(s_800BCE18* arg0);

void func_80040014();

s8 func_80040A64(VECTOR3* pos);

s32 func_80040B74(s32 arg0);

void func_800410D8(VECTOR3*, s32*, s32*, SVECTOR*, VECTOR3*);

void func_8004122C(s32* angle0, s32* angle1, VECTOR* arg2, VECTOR* arg3);

void func_8004137C(VECTOR3* result, VECTOR* vec0, VECTOR* vec1, s32 screenDist);

/** Some kind of queue entry load status getter. */
s32 func_80041ADC(s32 queueIdx);

/** Used for loading maps */
void func_80041C24(s_80041CEC* arg0, s32 arg1, s32 arg2);

void func_80041CB4(s_func_80041CB4* arg0, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears `field_4` in array of skeletons? Might not be skeletons, but the struct fits. */
void func_80041D10(s_Skeleton* skels, s32 size);

void func_80041E98();

void func_80041FF0();

void func_800420C0();

s32 func_80042178(s32* arg0);

u32 func_80041B1C(void* arg0);

s32 func_80042C04(s32 idx);

/** Gets distance to the edge of a file chunk? */
s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, s32 clip);

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip);

/** Maybe facilitates file chunk streaming as the player moves around the map. */
s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s16 fileChunkCoordX, s16 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip);

s32 func_80043B34(s_800C117C* arg0, s_800C1020* arg1);

s32 func_80043B70(s_80043B70* arg0);

s_80043BA4* func_80043BA4(s_80043BA4* arg0);

void func_80043BC4(s_80043B70* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_80043C7C(s_80043B70* arg0, s32 arg1, s32* arg2, s32 arg3);

s32 func_80043D00(s_80043B70* arg0);

s32 func_80043D44(s32 arg0);

s32 func_80043D64(s32 arg0); // Types assumed.

void func_80043E50(s_80043E50* arg0, s32* arg1, s32 arg2);

/** TODO: Maybe doesn't operate on a linked list. Need more context from other functions before committing to this. */
s_80043F2C* func_80043F2C(s_80043F2C* arg0, s_80043F2C* arg1);

void func_80044044(s_80044044* arg0, s32 arg1, s32 arg2);

s32 func_80044918(s_ModelAnim* anim);

void func_800446D8(s_Skeleton*, GsCOORDINATE2*, s32, s32, s32);

s32 func_800449AC(s_Model*, s_AnimInfo*);

/** Updates a character's animation, variant 0. First param might be `s_SubCharacter` instead. */
void Anim_Update0(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim);

/** Updates a character's animation, variant 1. */
void Anim_Update1(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim);

/** Updates a character's animation, variant 2. */
void Anim_Update2(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim);

/** Updates a character's animation, variant 3. */
void Anim_Update3(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim);

void func_80044F14(s32 mat, s16 z, s16 x, s16 y);

s8 func_80044F6C(s8* ptr, s32 arg1);

/** Skeleton setup? Assigns bones pointer for the skeleton and resets fields. */
void func_80044FE0(s_Skeleton* skel, s_Bone* bones, u8 boneCount);

/** Clears skeleton bone flags/mask. Called by `func_80044FE0`. */
void func_80045014(s_Skeleton* skel);

/** Anim func. Traverses skeleton bones to set flags/mask. */
void func_800453E8(s_Skeleton* skel, s32 cond);

/** Does something with skeleton bones. `arg0` is a struct pointer. */
void func_80045468(s_Skeleton* skel, s32* arg1, s32 cond);

/** Passes a command to the sound driver. */
void Sd_EngineCmd(u32 cmd);

/** Sound func? */
u8 func_80045B28();

u16 func_80045BC8();

void func_80045BD8(u16 caseArg);

void func_80045D28(u8 caseArg);

void sd_init();

u8 func_80045B28();

void sd_work_init();

u8 func_80046048(u16 cmd, s8 arg1, u8 vol); // SD Func. Last arg is a u8 value.

void func_800468EC();

void func_8004690C(u16 arg0);

void func_8004692C(u16);

void func_800469AC();

void func_800469E8();

void func_80046A24(u16);

void func_80046A70();

void func_80046AD8();

void func_80046B04();

/** Sound func. */
void func_80046B78();

u8 func_80046BB4(u8 arg0);

void func_80046C54(u8 arg0, u8 arg1);

void func_80046D3C(u16);

s32 func_80046DCC(s32 idx);

void func_80046E00();

void func_8004729C(u16 arg0);

void func_800472BC(s32 arg0);

void func_80047308();

void func_8004760C();

/** Args are volume levels. */
void Sd_SetVolume(u8 arg0, s16 arg1, u8 arg2);

void func_800478DC(u8 arg0);

void func_80047A70();

void func_8004729C(u16);

void Sd_SetVolBgm(s16 volLeft, s16 volRight);

void Sd_SetVolXa(s16 volLeft, s16 volRight);

s16 Sd_GetVolSe(s16 arg0);

void Sd_SetReverbDepth(u8 depth);

void Sd_SetReverbEnable(s32 mode);

void func_80047B24(s32 arg0);

void func_80047B80();

void func_80047D1C();

void func_80047D50();

void func_80047DB0();

void func_80047E3C();

void func_80047F18();

void func_80048000();

void func_8004807C();

void func_800480FC();

void func_800481F8();

void func_80048244(u16 cmd);

void func_800482D8();

void Sd_StopSeq();

/** CD function. */
void func_800483D4();

/** CD function. */
void func_80048424();

void func_80048498();

/** Nullsub */
void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4);

/** Nullsub */
void func_800485B8(s32 arg0, u8 arg1, u32 arg2);

void func_800485C0(s32 idx);

void func_800485D8();

u8 func_80048954(s32 com, u8* param, u8* res);

void func_8004729C(u16);

void func_8004BCBC(s32* buf);

void func_8004C040();

/** Returns `true` if player has usable ammo in inventory (i.e. ammo + gun needed for it, or gun with ammo loaded). */
s32 func_8004C328();

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

void GameFs_UniqueItemModelLoad(u8 itemId);

void GameFs_MapItemsTextureLoad(s32 mapId);

void func_800546A8(s32 arg0);

void func_80054720(void*, s32, s32);

void func_8005487C(s32);

void func_80055028();

void func_80055330(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

s32 func_80057208();

s32 func_80057200();

void func_800553C4(u8 arg0, u8 arg1, u8 arg2, u8 arg3);

void func_800553E0(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);

/** `arg0` type assumed. */
void func_80055434(VECTOR3* vec);

s32 func_800557DC();

void func_80055814(s32 arg0);

void func_800560FC(s_800BE9FC* arg0);

void func_8005B370(s_func_8005B370* arg0);

void func_8005B3BC(char* filename, s_func_800566B4_sub* arg1);

s32 func_800571D0(u32 arg0);

void func_80056504(s_800BE9FC* arg0, s8* arg1, s32* arg2, s32 arg3);

void func_80054A04(u8 arg0);

s32 func_80054AD8(u8);

void func_8005660C(s_func_8005660C_0* arg0, s_func_8005660C_1* arg1, s32 arg2);

void func_800566B4(s_func_800566B4* arg0, s_FsImageDesc* image, s8 unused, s32 startIdx, s32 arg4);

void func_80056D64(s8* prevStr, s8* newStr);

void func_8005B55C(GsCOORDINATE2*);

s32 func_8005C7D0(s_SubCharacter*, s32);

void func_8005C814(s16*, s_SubCharacter*);

void func_8005DC1C(s32, VECTOR3*, s32, s32); // Types assumed.

void func_8005DD44(s32, VECTOR3*, s32, s8); // Types assumed.

s32 func_8005F680(s_func_800699F8* arg0);

void func_8005DE0C(s32, VECTOR3*, s32, s32, s32); // Types assumed.

void func_8005E0DC(s32 mapIdx); // Types assumed.

void func_8005E89C();

void func_8005F6B0(s_SubCharacter*, s32*, s32, s32);

void DmsHeader_FixOffsets(s_DmsHeader* header);

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* header);

void Dms_CharacterGetStartPosRot(VECTOR3* pos, SVECTOR* rot, char* charName, s32 arg3, s_DmsHeader* header);

s32 Dms_CharacterFindIndexByName(char* name, s_DmsHeader* header);

void Dms_CharacterGetPosRotByIndex(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, s32 time, s_DmsHeader* header);

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha);

/** Unused function? Returns 96 * cotangent(angle / 2). Possibly camera/FOV related. */
s16 func_8008CDBC(s16 angle);

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, s32 time, s_DmsHeader* header);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, s_DmsKeyframeCamera* frame0, s_DmsKeyframeCamera* frame1, s32 alpha);

/** DMS func. */
void func_8008D1D0(s32* keyframePrev, s32* keyframeNext, s32* alpha, s32 time, s_DmsEntry* camEntry, s_DmsHeader* header);

u32 func_8008D2C4(s32 time, s_DmsHeader* header);

s32 Math_LerpFixed12(s16 from, s16 to, s32 alpha);

void func_8008D41C();

void func_8008D438();

void func_8008D448();

void func_8008D454();

void func_8008D464();

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s32 arg3);

void func_8008D5A0(VECTOR3*, s16);

s32 func_8008D8C0(s16, s32, s32);

void func_8008D990(s32, s32, VECTOR3*, s32, s32);

void func_8008E794(VECTOR3*, s16, s32);

void func_8008EA68(SVECTOR*, VECTOR3*, s32);

void func_80085D78(s32 arg0);

void func_80085DC0(s32 arg0, s32 sysStateStep);

void func_80085DF0();

void func_80085E6C(s32 arg0, s32 arg1);

void func_80085EB8(u32 arg0, s_SubCharacter* chara0, s_SubCharacter* chara1, s32 arg3);

void func_8008605C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** `arg1` might be `u8*`. */
void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5);

void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_800862F8(s32 arg0, s32 arg1, s32 arg2);

void func_80086470(u32 switchVar, s32 arg1, s32 arg2, s32 arg3);

void func_800865FC(s32 arg0, s32 idx0, s32 idx1, s16 arg3, s32 arg4, s32 arg5);

void func_800866D4(s32 arg0, s32 arg1, s32 arg2);

void func_80086728(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8008677C(s32 arg0, s32 arg1, s32 arg2);

void func_800867B4(s32 caseParam, s32 idx);

void func_800868DC(s32 idx);

void func_800869E4(u8* arg0, u8* arg1, u16* arg2);

void Camera_TranslationSet(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCamFlag);

void Camera_RotationSet(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
                        s32 xAngularAccel, s32 yAngularAccel, s32 xAngularSpeedMax, s32 yAngularSpeedMax, s32 warpLookAtFlag);

void func_80086C58(s32 arg0, s32 arg1);

void func_80086D04(s32 arg0);

void func_80086DA8(s32 arg0, s32 arg1);

void func_80086F44(s32 arg0, s32 arg1);

void func_80086FE8(s32 arg0, s32 arg1, s32 arg2);

void func_8008716C(s32 arg0, s32 arg1, s32 arg2);

void func_80087360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80087540(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/** Something to do with bullet adjust setting. */
void func_800879FC(u32 arg0, s32 arg1);

/** Inventory drawing? */
void func_80087AF4(s32 mapFlagIdx, s32 eventFlagIdx, s32 arg2);

void func_80087EA8(s32 cmd);

void func_80087EDC(s32 arg0);

void func_80088028();

void func_80088048();

void func_800880F0(s32 arg0);

void func_800881B8(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5);

s32 func_80088D0C();

void func_80088D34(s32 idx);

void func_80088F94(s_SubCharacter* chara);

s32 func_8008F434(s32 arg0);

void func_80089090(s32 arg0);

void func_800890B8();

s32 func_80089128();

void func_800892A4(s32 idx);

void func_800892DC(s32 idx, u8 arg1);

void func_80089314(s32 arg0);

void func_800893D0(s32 arg0);

void func_8008944C();

void func_80089470();

void func_80089494();

void func_800894B8(s32 arg0);

void func_800894DC();

void func_80089500();

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2);

s32 func_8008973C(s_SysWork_2514* arg0, s32 arg1, s_8002AC04* ptr, u32* arg3);

void func_80089840(s_func_80089840* arg0);

void func_8008989C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32));

s32 func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u8* arg3);

void func_8008992C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32));

s32 func_8008A35C(s_8008A35C* arg0, s32 arg1);

void func_8008A384(s_SubCharacter* chara);

void func_8008A398(s_SubCharacter* chara);

void func_8008A3AC(s_SubCharacter* chara);

void func_8008B398();

void func_8008B3E4(s32 arg0);

void func_8008B40C(s32 arg0, s32 arg1);

/** `arg0` is boolean. */
void func_8008B438(s32 arg0, s32 arg1, s32 arg2);

void func_8008B664(s32 arg0, u32 caseVar);

s32 func_8008D850();

void func_8008E4EC();

void func_8008D78C();

s32 func_8008F470(s32 caseArg);

/** Returns 0. */
s32 func_8008F520();

s32 func_8008F914();

void func_80091380();

// TODO: Arrange these in address order for better insight into the original interface. -- Sezz
// ------------------------------------------------------------------

/**
Could `arg5` be a struct pointer?
`func_8003D6E0` uses this function and in the last argument
it input `arg5` and `arg5` is an undetermined function pointer
*/
s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5); // arg2 type assumed.

/** Seeks for the English title screen background graphic. */
void GameFs_TitleGfxSeek();

/** Loads the English title screen background graphic. */
void GameFs_TitleGfxLoad();

/** Seeks for the stream overlay. */
void GameFs_StreamBinSeek();

/** Loads the stream overlay. */
void GameFs_StreamBinLoad();

/** Loads the options background graphic and overlay. */
void GameFs_OptionBinLoad();

/** Loads the save/load background graphic and overlay. */
void GameFs_SaveLoadBinLoad();

/** Loads "Tim00" graphic. */
void GameFs_Tim00TIMLoad();

void func_8005B46C(s32* arg0);

void func_8005B474(s32* arg0, u32 arg1, s32 idx);

s32 func_8005B4BC(void*, void*);

/** Sets the debug string position. */
void func_8005BF0C(s16 unused, s16 x, s16 y);

s16 func_8005BF38(s16 arg0);

/** `arg0` type assumed. */
void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3);

void func_8005CB20(s_SubCharacter*, void*, s16, s16);

void func_800622B8(s32, s_SubCharacter*, s32, s32);

void func_80066E40();

void func_80066E7C();

void func_800697EC();

u16 func_80069810();

void func_80069820(u16);

void func_80069994(s_func_800699E4* arg0);

void func_800699E4(s_func_800699E4* arg0);

void func_800699F8(s_func_800699F8* result, s32 posX, s32 posZ);

s32 func_80069B24(s32 arg0, void* arg1, void* arg2);

void func_8006A178(s_func_8006A178* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_8006A3B4(s32 arg0, s32 arg1, s32 arg2);

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* vec, s_func_8006AB50* arg2, s32 arg3);

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* vec, s_func_8006AB50* arg2);

void func_8006AD44(s_func_8006CC44* arg0, s_func_800699E4* arg1);

void func_8006B1C8(s_func_8006CC44* arg0, s_func_800699E4* arg1, s_func_8006B1C8* arg2);

void func_8006BDDC(s_func_8006BDDC* arg0, s16 arg1, s16 arg2);

void func_8006C838(s_func_8006CC44* arg0, s_func_800699E4* arg1);

void func_8006CA18(s_func_8006CC44* arg0, s_func_800699E4* arg1, s_func_8006CA18* arg2);

s32 func_8006CC44(s32 arg0, s32 arg1, s_func_8006CC44* arg2);

s8 func_8006DB3C(s8* arg0, VECTOR3* arg1, s32 arg2, SVECTOR3* arg3);

s32 func_8006FD90(s_SubCharacter*, s32, s32, s32);

s32 func_80070360(s_SubCharacter*, s32, s32);

void func_8007029C(VECTOR3* arg0, s32 arg1, s16 angle);

void func_800705E4(GsCOORDINATE2*, s32, s32, s32, s32);

void func_80074254(s32 arg0, s32 arg1); // `arg1` is pointer?

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2);

void func_8003289C(POLY_G4* arg0, s32 arg1);

void Gfx_VSyncCallback();

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

void Settings_RestoreControlDefaults(s32 arg0);

void nullsub_800334C8();

s32 func_800334D8(s32 idx);

s32 func_80033548();

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SavegameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SavegameReadPlayer();

s32 MainLoop_ShouldWarmReset();

void Game_WarmBoot();

void Joy_Init();

void Joy_ReadP1();

void Joy_Update();

void Joy_ControllerDataUpdate();

void ControllerData_AnalogToDigital(s_ControllerData* arg0, s32 arg1);

void func_800348C0();

void GameState_MainLoadScreen_Update();

/** Handles `g_GameWork.gameStateStep_598[0]`. */
void Demo_StartUp();

void func_80034E58();

void func_80034EC8();

void func_80034F18();

void func_80034FB8();

void Game_SavegameInitialize(s8 overlayId, s32 difficulty);

void func_80035178();

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

s32 func_8003528C(s32 idx0, s32 idx1);

s32 func_800352F8(s32 arg0);

void func_80035338(s32 arg0, s32 arg1, u32 arg2, s32 arg3);

/** Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 idx0, s32 idx1, s_800A992C_sub* ptr, GsCOORDINATE2* coord);

void func_8003569C();

s32 func_80035780();

/** Sets sound command. */
s32 func_800358A8(s32 cmd);

void func_800358DC(s32 cmd);

/** Executes sound command. */
void func_80035924();

void func_8003596C();

s32 func_8003599C();

s32 func_80035AB0(s32 arg0);

void func_80035AC8(s32 arg0);

void func_80035B04(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord);

void func_80035B58(s32 arg0);

void func_80035B98();

void func_80035BBC();

/** Player camera func. */
void func_80035BE0();

void func_80035DB4(s32);

void func_80035E1C();

/** Returns boolean status. */
s32 func_80035E44();

void func_80035ED0();

void func_80035F4C(s32 arg0, s32 arg1, u8* arg2);

void func_800363D0();

void func_8003640C(s32 arg0);

void func_80036420();

s32 func_8003647C();

s32 func_80036498();

u32 func_800364BC();

void func_8003652C();

s32 func_800365B8(s32 arg0);

s32 func_80036B5C(u8 arg0, s32* arg1);

void func_80036E48(u16* arg0, s16* arg1);

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124();

void func_80037154();

void func_80037188();

void func_80037334();

void func_80037388();

s32 func_800378D4(s_AreaLoadParams* areaLoadParams);

void func_80037DC4(s_SubCharacter* chara);

void func_800373CC(s32);

void func_80037E40(s_SubCharacter* chara);

void func_80037E78(s_SubCharacter* chara);

s32 func_800382B0(s32 arg0);

s32 func_80038A6C(VECTOR3* pos0, VECTOR3* pos1, s32 radius);

/** Computes the 2D distance on the XZ plane between the input position and the camera position. */
s32 func_80038B44(VECTOR3* pos);

void func_80037F24(s32);

void func_80038354();

void GameState_InGame_Update();

void SysState_Gameplay_Update();

void SysState_GamePaused_Update();

void SysState_OptionsMenu_Update();

void func_8003943C();

void SysState_StatusMenu_Update();

void GameState_LoadStatusScreen_Update();

void SysState_Unk3_Update();

void GameState_LoadMapScreen_Update();

void SysState_Fmv_Update();

void SysState_LoadArea_Update();

void AreaLoad_UpdatePlayerPosition();

void func_80039F54();

s8 func_80039F90();

void SysState_ReadMessage_Update(s32 arg0);

void SysWork_SavegameUpdatePlayer();

void func_8003A16C();

void SysWork_SavegameReadPlayer();

void SysState_SaveMenu_Update();

void SysState_EventCallFunc_Update();

void SysState_EventSetFlag_Update();

void SysState_EventPlaySound_Update();

void SysState_GameOver_Update();

void GameState_MapEvent_Update();

void func_8003BC8C();

void func_8003BCF4();

void func_8003BE28();

s32 func_8003BE50(s32 idx);

void GameFs_BgEtcGfxLoad();

void GameFs_BgItemLoad();

void func_8003BED0();

s32 func_8003BF60(s32 arg0, s32 arg1);

/** Used in map loading.
 * Removing it causes the game to get stuck at the loading screen.
 */
void func_8003C048();

void func_8003C0C0();

void func_8003C110();

void func_8003C1AC(s_800BCE18_0_CC* arg0);

void func_8003C2EC();

void func_8003C30C();

void func_8003C368();

void func_8003C3A0();

void func_8003C3AC();

void func_8003C878(s32);

void func_8003CB3C(s_800BCE18* arg0);

void func_8003CB44(s_800BCE18* arg0);

void func_8003CBA4(s_800BCE18_2BEC* arg0);

void func_8003CC7C(s_800BCE18_2BEC_0* arg0, MATRIX* arg1, MATRIX* arg2);

void func_8003D354(s32* arg0, s32 arg1);

void func_8003D3BC(s_FsImageDesc* img, s32 arg1, s32 arg2);

s32 func_8003D7D4(u32 arg0, s32 arg1, void* arg2, s_FsImageDesc* img);

void func_8003D938();

void func_8003D95C();

void func_8003D9C8(s_800BCE18_0_CC* arg0);

void func_8003DA9C(s32 arg0, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4);

void func_8003DD80(s32 arg0, s32 arg1);

void func_8003DE60(s_Skeleton* skel, s32 arg1);

void func_8003DF84(s_Skeleton* skel, s32 arg1);

void func_8003E08C(s_Skeleton* skel, s32 arg1);

void func_8003E194(s_Skeleton* skel, s32 arg1);

void func_8003E238(s_Skeleton* skel, s32 arg1);

void func_8003E388(s_Skeleton* skel, s32 arg1);

void func_8003E414(s_Skeleton* skel, s32 arg1);

void func_8003E4A0(s_Skeleton* skel, s32 arg1);

void func_8003E544(s_Skeleton* skel, s32 arg1);

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad();

void func_8003EB54();

void func_8003EBF4(s_MapOverlayHeader* arg0);

void func_8003EBA0();

void func_8003ECBC();

void func_8003ECE4();

void func_8003ED08();

u8 func_8003ED64();

void func_8003EDA8();

void func_8003EDB8(s32* arg0, s32* arg1);

void func_8003EE30(s32 arg0, s8* arg1, s32 arg2, s32 arg3);

void func_8003EEDC(s32 arg0, s32 arg1);

void func_8003EF74(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_8003F08C(s_StructUnk3* arg0, s_sub_StructUnk3* arg1);

void func_8003F170();

void func_80043740();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SavegameResetPlayer();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_800711C4(s32 arg1, s32 arg2);

void func_80071224(s32 arg1, s32 arg2);

void func_80071284(s32 arg0);

void func_800713B4(s_SubCharacter* chara, s32 arg1);

void func_80071968(s_SubCharacter*, s_MainCharacterExtra*, void*, GsCOORDINATE2*);

void func_80071CE8(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);

void func_8007C0D8(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);

void func_8007C800(s_SubCharacter*, s_MainCharacterExtra*);

void func_8007D090(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord);

void func_8007E9C4();

/** Resets several global variables to 0. */
void func_8007F1CC();

void func_8007F250(u8* ptr, s8 arg1);

/** Some kind of player anim state check. */
s32 func_8007F26C();

/** Some kind of player anim state check. */
s32 func_8007F2AC();

/** Gets something from the player's current animation? */
s16 Player_AnimGetSomething();

/** Gets property 8 from player. */
s32 func_8007FD2C();

/** Gets something from player. */
s32 func_8007FD3C();

/** Returns data in last 3 pointer args. */
void func_8007FDE0(s8, s32*, s8*, s8*);

/** Forces ControllerFlag_Select button press. */
void func_80080458();

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1);

/** Generates a random value of some kind. */
s32 func_80080514();

/** Computes (abs(value) - subtractor) * copysign(value). */
s32 PreservedSignSubtract(s32 value, s32 subtractor);

u32 func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // arg3 type assumed.

void func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_80080884();

s32 func_800808AC();

/** Returns a Q shift based on a magnitude. */
s32 Math_GetMagnitudeShift(s32 mag);

s32 func_80080A10();

u8 func_8008A2E0(s32 arg0);

#endif
