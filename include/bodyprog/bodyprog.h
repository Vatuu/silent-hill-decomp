#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "bodyprog/sound_effects.h"
#include "bodyprog/view/vw_system.h"
#include "main/fsqueue.h"

/** @brief This header is used to declare any variable, struct, or
 * function of `BODYPROG.BIN` that has not been identified to
 * be related to a currently recognized and separated section of
 * the engine (like player logic, save game, or item screens).
 */

// ==========
// CONSTANTS
// ==========

#define WORLD_OBJECT_COUNT_MAX 29

#define OPT_SOUND_VOLUME_MIN   0
#define OPT_SOUND_VOLUME_MAX   128
#define OPT_VIBRATION_DISABLED 0
#define OPT_VIBRATION_ENABLED  128

#define IPD_HEADER_MAGIC 20
#define LM_HEADER_MAGIC  '0'
#define LM_VERSION       6

#define CHARA_FORCE_FREE_ALL 0xFF /** `Chara_Load` can force free already loaded models to make room for new ones. */

// ==============
// HELPER MACROS
// ==============

/** @brief Compares 8-character filenames using `u32`. Similar to `strcmp`.
 *
 * @param a First filename.
 * @param b Second filename.
 * @return `true` if the filenames aren't equal, `false` otherwise.
 */
#define COMPARE_FILENAMES(a, b)                                  \
    (((u_Filename*)(a))->u32[0] != ((u_Filename*)(b))->u32[0] || \
     ((u_Filename*)(a))->u32[1] != ((u_Filename*)(b))->u32[1])

// ======
// ENUMS
// ======

/** @brief Background music flags. */
typedef enum _BgmFlags
{
    BgmFlag_Unk0 = 1 << 0,
    BgmFlag_Unk1 = 1 << 1,
    BgmFlag_Unk2 = 1 << 2,
    BgmFlag_Unk3 = 1 << 3,
    BgmFlag_Unk4 = 1 << 4,
    BgmFlag_Unk5 = 1 << 5,
    BgmFlag_Unk6 = 1 << 6,
    BgmFlag_Unk7 = 1 << 7,
    BgmFlag_Unk8 = 1 << 8,
    BgmFlag_Unk9 = 1 << 9
} e_BgmFlags;

typedef enum _CollisionType
{
    CollisionType_None = 0,
    CollisionType_Wall = 1,
    CollisionType_Unk2 = 2
} e_CollisionType;

/** Map flags. */
typedef enum _MapFlags
{
    MapFlag_FourActiveChunks = 0,      /** Used by exterior maps. */
    MapFlag_OneActiveChunk   = 1 << 0,
    MapFlag_TwoActiveChunks  = 1 << 1,
    MapFlag_Interior         = 1 << 2,
    MapFlag_Unk3             = 1 << 3  /** @unused Unused map type `XXX` has this flag. */
} e_MapFlags;

/** @brief Used as index into `MAP_INFOS` array.
 * TODO: Add descriptions for which areas are included in each type?
*/
typedef enum _MapType
{
    MapType_THR = 0,
    MapType_SC  = 1,
    MapType_SU  = 2,
    MapType_SPR = 3,
    MapType_SPU = 4,
    MapType_RSR = 5,
    MapType_RSU = 6,
    MapType_APR = 7, /** @unused */
    MapType_APU = 8,
    MapType_ER  = 9,
    MapType_ER2 = 10,
    MapType_DR  = 11,
    MapType_DRU = 12,
    MapType_HP  = 13,
    MapType_HU  = 14,
    MapType_XXX = 15, /** @unused */

    MapType_Count
} e_MapType;

typedef enum _BoneHierarchy
{
    BoneHierarchy_MultiModel = -3,
    BoneHierarchy_End        = -2
} e_BoneHierarchy;

typedef enum _EffectTextureFlags
{
    EffectTextureFlag_None         = 0,
    EffectTextureFlag_Glass        = 1 << 1, /** Broken glass in the cafe Air Screamer cutscene. */
    EffectTextureFlag_WaterRefract = 1 << 2, /** Water waves and light reflection in the sewer. */
    EffectTextureFlag_Water        = 1 << 3,
    EffectTextureFlag_Fire         = 1 << 4,
    EffectTextureFlag_Ef           = 1 << 5, // TODO: Rename. Looks like stringy flesh?
    EffectTextureFlag_Blood        = 1 << 6,
    EffectTextureFlag_WarmTest     = 1 << 7  /** @unused Test lens flare? */
} e_EffectTextureFlags;

typedef enum _SpeedZoneType
{
    SpeedZoneType_Slow   = 0,
    SpeedZoneType_Normal = 1,
    SpeedZoneType_Fast   = 2
} e_SpeedZoneType;

typedef enum _MainMenuEntry
{
    MainMenuEntry_Load     = 0,
    MainMenuEntry_Continue = 1,
    MainMenuEntry_Start    = 2,
    MainMenuEntry_Option   = 3,
    MainMenuEntry_Extra    = 4, /** @unused The extra options menu may have been accessible via the main menu. */

    MainMenuEntry_Count    = 5
} e_MainMenuEntry;

typedef enum _MainMenuState
{
    MenuState_Start              = 0,
    MenuState_Main               = 1,
    MenuState_LoadGame           = 2,
    MenuState_DifficultySelector = 3,
    MenuState_NewGameStart       = 4
} e_MainMenuState;

/** Used by `func_8003F654` to cast a specific field to the desired type. */
typedef enum _PrimitiveType
{
    PrimitiveType_None = 0,
    PrimitiveType_S8   = 1,
    PrimitiveType_U8   = 2,
    PrimitiveType_S16  = 3,
    PrimitiveType_U16  = 4,
    PrimitiveType_S32  = 5
} e_PrimitiveType;

typedef enum _LoadingScreenId
{
    LoadingScreenId_None              = 0,
    LoadingScreenId_PlayerRun         = 1,
    LoadingScreenId_BackgroundTexture = 2,
    LoadingScreenId_StageString       = 3
} e_LoadingScreenId;

typedef enum _StaticModelLoadState
{
    StaticModelLoadState_Invalid   = 0,
    StaticModelLoadState_Unloaded  = 1,
    StaticModelLoadState_Corrupted = 2, // Maybe wrong name for this.
    StaticModelLoadState_Loaded    = 3
} e_StaticModelLoadState;

// ================
// UNKNOWN STRUCTS
// ================

/* Structs called by functions that haven't been identified. */

/** SFX pair used for area loading (e.g. door opening and closing). */
typedef struct
{
    u16 sfx_0;
    u16 sfx_2;
} s_AreaLoadSfx;

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

typedef struct
{
    s32               id_0;
    s32               flags_4;
    s32               modelCount_8;
    struct TMD_STRUCT models_c[1];
} s_TmdFile;

typedef struct
{
    u8  unk_0;
    u8  field_1;
    u8  unk_2[18];
    s32 field_14;
} s_800C45C8;

typedef struct
{
    char pad[12];
} s_func_8005B424;

// Something related to enemies attacks.
typedef struct
{
    union
    {
        s32 vx_0; // Q23.8 } Displacement offset. `func_80062708` indicates Q12?
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
        struct
        {
            u16 field_0;
            u16 field_2;
        } s_1;
    } field_0;
    union
    {
        s32 vz_4; // Q23.8 } `func_80062708` indicates Q12?
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
    } field_4;
    s16 vy_8; // Q7.8
    u8  field_A;
    u8  field_B; // Flags?
    union
    {
        s32 field_0;
        struct
        {
            q3_12 field_0; // Angle.
            q3_12 field_2; // Angle.
        } s_0;
        struct
        {
            u8 field_0;
            u8 field_1;
            u8 field_2;
            u8 field_3;
        } s_1;
        struct
        {
            u16 field_0;
            u16 field_2;
        } s_2;
    } field_C;
    union
    {
        q20_12 field_0;
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
        struct
        {
            s16 field_0;
            u8  field_2;
            u8  field_3;
        } s_1;
        struct
        {
            u8 field_0;
            u8 field_1;
            u8 field_2;
            u8 field_3;
        } s_2;
        struct
        {
            u16 field_0;
            u16 field_2;
        } s_3;
    } field_10;
} s_MapHdr_field_4C;
STATIC_ASSERT_SIZEOF(s_MapHdr_field_4C, 20);

typedef struct _Collision
{
    q19_12 groundHeight_0;
    q3_12  field_4;  // } Angles??
    q3_12  field_6;  // }
    s8     field_8;  // Count of something, maybe valid ground at probed points around center? Set to 0, 7, or 12.
    // 3 bytes of padding.
} s_Collision;
STATIC_ASSERT_SIZEOF(s_Collision, 12);

typedef struct
{
    VECTOR3  position_0; // Q19.12
    SVECTOR3 rotation_C; // Q3.12
    s8       field_12;
} s_func_8006AB50;

typedef struct
{
    s32        field_0;
    s32        field_4; // `bool`?
    s32        field_8; // 2D distance.
    SVECTOR    field_C; // Q23.8 | Position.
    DVECTOR_XZ direction_14;
    q23_8      positionX_18;
    q23_8      positionZ_1C;
    s32        field_20;
    s32        field_24;
    s16        field_28; // } `SVECTOR3`, packed rotation? Probably not.
    s16        field_2A; // }
    s16        field_2C; // }
} s_func_8006ABC0;

typedef struct
{
    u8  unk_0[2];
    s16 field_2;
    u8  unk_4[2];
    s16 field_6;
} s_func_8006CA18;

typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s32 field_4;
} s_func_8006CC44_A8;

typedef struct
{
    s8      field_0;
    s8      unk_1;
    DVECTOR field_2; // Q3.12 | XY rotation.
} s_func_8006CC44_44_0;

typedef struct
{
    s_func_8006CC44_44_0 field_0;
    s16                  field_6;
    s_func_8006CC44_44_0 field_8;
    s16                  field_E;
    s8*                  field_10[8];
    s_func_8006CC44_44_0 field_30;
    s16                  field_36;
} s_func_8006CC44_44;

typedef struct
{
    q23_8 field_0; // X position.                } Q8 according to `func_8006EE0C`?
    q23_8 field_4; // Y position.                }
    q7_8  field_8; // Z position, but why `s16`? }
    q7_8  field_A; // Y??
    q7_8  field_C; // Some kind of bound or threshold?
    s16   field_E;
} s_RayState_6C; // Unknown size;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_RayState_8C;

/** @brief State for an in-progress ray trace. Contains pointers to active characters among other things. */
typedef struct
{
    s32              field_0;
    s16              field_4;
    s16              field_6;
    q7_8             field_8; // Distance X?
    s8               unk_A[2];
    q23_8            field_C;  // } Q23.8 `VECTOR3`
    q23_8            field_10; // }
    q23_8            field_14; // }
    s8               unk_18[4];
    q7_8             field_1C; // Distance Z?
    s8               unk_1E[2];
    s_SubCharacter*  field_20;
    s16              field_24; // X } Q19.12
    s16              field_26; // Z }
    s32              field_28;
    VECTOR3          field_2C; // Q23.8
    s8               unk_38[4];
    s32              field_3C; // X  } Q23.8 `VECTOR3`?
    s32              field_40; // Y? }
    s32              field_44; // Z  }
    s8               unk_48[4];
    q7_8             field_4C; // X?
    q7_8             field_4E; // Z?
    SVECTOR          field_50; // Q23.8
    u16              field_58;
    s16              field_5A;
    s16              field_5C;
    s16              field_5E;
    s16              field_60;
    s8               unk_62[2];
    s_SubCharacter** characters_64; // Active characters?
    s32              characterCount_68;
    s_RayState_6C    field_6C;
    s32              field_7C;
    s32              field_80;
    u16              field_84;
    u8               unk_86[2];
    s32              field_88;
    s_RayState_8C    field_8C[1]; // Unknown size.
} s_RayState;

// Function from lib_unk
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

typedef struct
{
    q19_12 field_0; // X position.
    q19_12 field_4; // Z position.
    s32    field_8;
    s32    field_C;
    q19_12 field_10; // X
    q19_12 field_14; // Z
    s32    field_18; // X } Bounds?
    s32    field_1C; // X }
    s32    field_20; // Z }
    s32    field_24; // Z }
    q19_12 field_28; // } Maybe XZ position.
    q19_12 field_2C; // }
} s_func_8006F338;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_func_8006E490_20;

typedef struct
{
    s8                 unk_0[8];
    DVECTOR            field_8;
    s16                field_C;
    s16                field_E;
    s32                field_10; // } X
    s32                field_14; // } Z?
    s16                field_18;
    s8                 unk_1A[2];
    s32                field_1C; // Index into `field_20`.
    s_func_8006E490_20 field_20[2];
} s_func_8006E490;

/** @brief Animation keyframe? Doesn't hold bone data, but something gameplay-related
 * which is derived from here.
 */
typedef struct _Keyframe
{
    q3_12 field_0;
    q3_12 field_2;
    q3_12 field_4;
    q3_12 field_6;
    q3_12 field_8;
    q3_12 field_A;
    q3_12 field_C;
    q3_12 field_E;
    q3_12 field_10; // X offset?
    q3_12 field_12; // Z offset?
} s_Keyframe;

// ========
// STRUCTS
// ========

typedef struct _Normal
{
    s8 nx;
    s8 ny;
    s8 nz;
    u8 count;
} s_Normal;
STATIC_ASSERT_SIZEOF(s_Normal, 4);

/** @brief 8-character string usually used for filenames. Can be compared via the `u32` field. */
typedef union _Filename
{
    char str[8];
    u32  u32[2];
} u_Filename;

/** @brief Struct used by many functions involved with GTE. Kept at `PSX_SCRATCH_ADDR` (possibly only temporarily). */
typedef struct _GteScratchData
{
    DVECTOR screenXy_0[90];
    u16     screenZ_168[18];

    s16 field_18C[99]; // The size changed from 150 due to the addition of `field_252`. Not sure if this is correct.
    u8  field_252[102];

    u8      field_2B8[200]; // Size likely incorrect.

    union
    {
        MATRIX field_0;
        struct
        {
            s32     field_0;
            s32     field_4;
            CVECTOR field_8;
            CVECTOR field_C;
            u8      field_10;
            u8      field_11;
            u8      field_12;
            u8      field_13;
            u8      field_14;
            u8      field_15;
            u8      field_16;
            u8      field_17;
            s32     field_18;
            s32     field_1C;
        } s_0;
    } field_380;

    s_Normal field_3A0;

    DVECTOR  screenPos_3A4;
    s32      depthP_3A8;
    SVECTOR  field_3AC;
    u8       unk_3B4[36];
    CVECTOR  field_3D8; // Written by `func_8005A42C`.
    DVECTOR  screenPos_3DC;
    s32      depthP_3E0;
    MATRIX   field_3E4;
} s_GteScratchData;

typedef struct _Primitive
{
    u16 field_0;
    u16 field_2;
    u16 field_4;
    union
    {
        struct
        {
            u8 field_6_0  : 8;
            s8 field_6_8  : 7;
            u8 field_6_15 : 1; // `bool`
        } bits;

        u16 flags; // @hack `func_8005AC50` accesses `field_6_15` above with some weird shifts, haven't found how to make it work with bitfield yet.
    } field_6;
    u16 field_8;
    u16 field_A;
    u8  field_C[4];  // } Unknown type. `func_8005AC50` reads these as `s32`, but that breaks other funcs which use this struct. `s32` reads might have just been `memcpy`?
    u8  field_10[4]; // }
} s_Primitive;
STATIC_ASSERT_SIZEOF(s_Primitive, 20);

typedef struct _MeshHeader
{
    u8 primitiveCount_0;
    u8 vertexCount_1;
    u8 normalCount_2;
    u8 unkCount_3;

    s_Primitive* primitives_4;
    DVECTOR*     verticesXy_8;
    s16*         verticesZ_C;
    s_Normal*    normals_10;
    u8*          unkPtr_14;
} s_MeshHeader;
STATIC_ASSERT_SIZEOF(s_MeshHeader, 24);

typedef struct _ModelHeader
{
    u_Filename    name_0;
    u8            meshCount_8;
    u8            vertexOffset_9;
    u8            normalOffset_A;
    u8            field_B_0 : 1;
    u8            field_B_1 : 3; // Value used in `func_800571D0` switch.
    u8            field_B_4 : 2;
    u8            unk_B_6   : 2;
    s_MeshHeader* meshHdrs_C;
} s_ModelHeader;
STATIC_ASSERT_SIZEOF(s_ModelHeader, 16);

typedef struct _Texture
{
    s_FsImageDesc imageDesc_0;
    u_Filename    name_8;
    u32           queueIdx_10;
    s8            refCount_14;
} s_Texture;

typedef struct _Material
{
    u_Filename name_0;
    s_Texture* texture_8;
    u8         field_C;
    u8         unk_D[1];
    u8         field_E;
    u8         field_F;
    u16        field_10;
    u16        field_12;
    union
    {
        u8  u8[2];
        u16 u16;
    } field_14;
    union
    {
        u8  u8[2];
        u16 u16;
    } field_16;
} s_Material;
STATIC_ASSERT_SIZEOF(s_Material, 24);

typedef struct _LmHeader
{
    u8             magic_0;    /** See `LM_HEADER_MAGIC`. */
    u8             version_1;  /** See `LM_VERSION`. */
    u8             isLoaded_2; /** `bool` */
    u8             materialCount_3;
    s_Material*    materials_4;
    u8             modelCount_8;
    u8             unk_9[3];
    s_ModelHeader* modelHdrs_C;
    u8*            modelOrder_10;
} s_LmHeader;

typedef struct _IpdCollisionData_10
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u16 field_6_0  : 5; // TODO: Might be using `s_IpdCollisionData_18` substruct here? Won't fit though.
    u16 field_6_5  : 3;
    u16 field_6_8  : 3;
    u16 field_6_11 : 4;
    u16 field_6_15 : 1;
    s16 field_8;
    s16 field_A;
} s_IpdCollisionData_10;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_10, 12);

typedef struct
{
    s16 field_0_0  : 14;
    u16 field_0_14 : 2;
    s16 field_2_0  : 14;
    u16 field_2_14 : 2;
    s16 field_4;
    u8  field_6;
    u8  field_7;
    u8  field_8;
    u8  field_9;
} s_IpdCollisionData_14;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_14, 10);

typedef struct
{
    s16 field_0;
    s8  unk_2[2];
} s_IpdCollisionData_20;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_20, 4);

typedef struct _IpdCollisionData_18
{
    u16      field_0_0  : 5;
    u16      field_0_5  : 3;
    u16      field_0_8  : 4;
    u16      field_0_12 : 3;
    u16      field_0_15 : 1;
    SVECTOR3 vec_2;
    s16      field_8;
} s_IpdCollisionData_18;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_18, 10);

typedef struct _IpdCollisionData
{
    s32                    positionX_0;
    s32                    positionZ_4;
    u32                    field_8_0  : 8;
    u32                    field_8_8  : 8;
    u32                    field_8_16 : 8;
    u32                    field_8_24 : 8;
    SVECTOR3*              ptr_C;
    s_IpdCollisionData_10* ptr_10;
    s_IpdCollisionData_14* ptr_14;
    s_IpdCollisionData_18* ptr_18;
    s16                    field_1C;
    u8                     field_1E; // } Used as multipliers for `field_1C` in `func_8006B004`.
    u8                     field_1F; // }
    s_IpdCollisionData_20* ptr_20;
    u16                    field_24; // `field_24/``field_26` defined in ipd2obj but haven't seen used yet, might be size of `ptr_28`/`ptr_2C`.
    u16                    field_26;
    u8*                    ptr_28; // Accessed as array of indices into `field_34` by `func_8006E53C`.
    void*                  ptr_2C;
    u8                     field_30;
    u8                     unk_31[3];
    u8                     field_34[256];
} s_IpdCollisionData;

typedef struct _IpdModelBuffer_C
{
    s_ModelHeader* modelHdr_0;
    MATRIX         field_4;
} s_IpdModelBuffer_C;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer_C, 36);

typedef struct _IpdModelBuffer
{
    u8                  field_0; // Count of `field_C` entries.
    u8                  field_1;
    u8                  field_2;
    s8                  unk_3;
    s16                 field_4;
    s16                 field_6;
    s16                 field_8;
    s16                 field_A;
    s_IpdModelBuffer_C* field_C;
    SVECTOR*            field_10; // Pointer to unknown collision data, type assumed.
    SVECTOR*            field_14; // Pointer to unknown collision data, type assumed.
} s_IpdModelBuffer;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer, 24);

typedef struct _IpdModelInfo
{
    u8             isGlobalPlm_0; // `false` if loaded from inside `IPD`, `true` if loaded from `*_GLB.PLM`.
    u8             unk_1[3];
    u_Filename     modelName_4;
    s_ModelHeader* modelHdr_C;
} s_IpdModelInfo;
STATIC_ASSERT_SIZEOF(s_IpdModelInfo, 16);

typedef struct _IpdHeader
{
    u8                 magic_0;
    u8                 isLoaded_1; /** `bool` */
    s8                 cellX_2;
    s8                 cellZ_3;
    s_LmHeader*        lmHdr_4;
    u8                 modelCount_8;
    u8                 modelBufferCount_9;
    u8                 modelOrderCount_A;
    u8                 unk_B[1];
    u8                 unk_C[8];
    s_IpdModelInfo*    modelInfo_14;
    s_IpdModelBuffer*  modelBuffers_18;
    u8                 textureCount_1C; // Should it be `u32`?
                                        // "`u8` - Relative pointer to textures list"
                                        // "`u32` - Relative pointer to object order"
    u8                 unk_1D[3];
    u8                 unk_20[48];
    u8*                modelOrderList_50;
    s_IpdCollisionData collisionData_54;
} s_IpdHeader;

// See: https://github.com/laura-a-n-n/silent-hill-museum/blob/main/ksy/sh1anm.ksy
typedef struct _AnmBindPose
{
    s8 parentBone;
    s8 rotationDataIdx_1;
    s8 translationDataIdx_2;
    s8 translationInitial_3[3];
} s_AnmBindPose;
STATIC_ASSERT_SIZEOF(s_AnmBindPose, 6);

typedef struct _AnmHeader
{
    u16           dataOffset_0;
    u8            rotationBoneCount_2;
    u8            translationBoneCount_3;
    u16           keyframeDataSize_4; // Size per keyframe, `(rotationBoneCount_2 * 9) + (translationBoneCount_3 * 3)`?
    u8            boneCount_6;
    u8            unk_7;
    u32           activeBones_8; // Holds bit field of bones to update.
    u32           fileSize_C;
    u16           keyframeCount_10;
    u8            scaleLog2_12;
    u8            rootYOffset_13;
    s_AnmBindPose bindPoses_14[0]; // Array size = `boneCount_6`.
} s_AnmHeader;
STATIC_ASSERT_SIZEOF(s_AnmHeader, 20);

typedef union
{
    s16 field_0;
    struct
    {
        u8 field_0;
        u8 field_1;
    } s_field_0;
} s_func_8006CC44_CC_C;

typedef struct
{
    DVECTOR_XZ field_0;
    DVECTOR_XZ field_4;
    u32        field_8;
    s32        field_C;
    s16        field_10;
    u8         unk_12[2];
    DVECTOR_XZ field_14;
} s_func_8006CC44_CC_20;

typedef struct
{
    s_IpdCollisionData*   ipdCollisionData_0;
    u8                    field_4; // Index.
    u8                    field_5;
    SVECTOR3              field_6;
    s_func_8006CC44_CC_C  field_C;
    u8                    field_E;
    u8                    field_F;
    u8                    field_10;
    u8                    field_11;
    SVECTOR3              field_12;
    SVECTOR3              field_18;
    s8                    unk_1E[2];
    s_func_8006CC44_CC_20 field_20;
} s_func_8006CC44_CC;
STATIC_ASSERT_SIZEOF(s_func_8006CC44_CC, 56);

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
    s16                field_38;
    s16                field_3A;
    s16                field_3C; // X?
    s16                field_3E; // Z?
    s8*                field_40;
    s_func_8006CC44_44 field_44;
    s32                field_7C;
    s32                field_80; // X
    s32                field_84; // Z
    s32                field_88; // X
    s32                field_8C; // Z
    s32                field_90; // `bool`?
    s32                field_94;
    union
    {
        DVECTOR_XZ vec_0;
        s32        field_0;
    } field_98;
    union
    {
        DVECTOR_XZ vec_0;
        s32        field_0;
    } field_9C;
    union
    {
        struct
        {
            u8                 field_0; // Start index for something.
            u8                 field_1;
            u8                 field_2;
            u8                 field_3;
            s_func_8006CA18*   field_4;
            s_func_8006CC44_A8 field_8[4];
        } s_0;
        struct
        {
            q7_8 field_0;
            q7_8 field_2;
            s16  field_4;
            u8   field_6;
            u8*  field_8;
            s8   unk_C[28];
        } s_1;
    } field_A0;
    u8                 field_C8;
    u8                 unk_C9[1];
    s16                field_CA;
    s_func_8006CC44_CC field_CC;
    // TODO: May be incomplete. Maybe not, added the final padding based on `Collision_Get`.
} s_func_8006CC44;

typedef struct _GlobalLm
{
    s_LmHeader* lmHdr_0;
    s32         fileIdx_4;
    s32         queueIdx_8;
} s_GlobalLm;

typedef struct
{
    s32            field_0; // Bone flags?
    GsCOORDINATE2* coord_4;
    s_ModelHeader* modelHdr_8;
    s32            modelIdx_C;
} s_ModelInfo;

typedef struct _Bone
{
    s_ModelInfo   modelInfo_0;
    s8            field_10;
    s8            unk_11[3];
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 20);

typedef struct _LinkedBone
{
    s_Bone              bone_0;
    struct _LinkedBone* next_14;
} s_LinkedBone;
STATIC_ASSERT_SIZEOF(s_LinkedBone, 24);

typedef struct
{
    u8            boneCount_0;
    u8            boneIdx_1;
    u8            field_2;
    s8            field_3;
    s_LinkedBone* bones_4;
    s_LinkedBone* bones_8;
    s_LinkedBone  bones_C[56];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 1356);

typedef struct
{
    s8  field_0;
    s8  field_1;
    s8  field_2;
    s8  field_3;
    s32 field_4[4];
} s_800382B0;

typedef struct
{
    s16 field_0; // Flags?
} s_8008D850;

// or `s_AnimMetadata`?
typedef struct _CharaAnimDataInfo
{
    s8             charaId0_0;  /** `e_CharacterId` */
    s8             charaId1_1;  /** `e_CharacterId` */
    // 2 bytes of padding.
    s32            animFile0_4; // s_AnmHeader* animFile0_4; // TODO: Needs to be a pointer.
    s_AnmHeader*   animFile1_8;
    s32            animBufferSize1_C;
    s32            animBufferSize2_10;
    GsCOORDINATE2* npcCoords_14;
} s_CharaAnimDataInfo;
STATIC_ASSERT_SIZEOF(s_CharaAnimDataInfo, 24);

/** Related to weapon attacks. Stats, SFX IDs, damange values, etc.? */
typedef struct
{
    q4_12 field_0;
    s16   field_2;
    u16   field_4;  // Related to damage. Multiplier?
    s8    field_6;  // Accessed by `func_8008BF84` as `u16`
    s8    unk_7;
    u8    field_8;  // Accessed by `func_8008BF84` as `u16`
    u8    field_9;  /** `e_CharacterId` */
    u8    field_A;  // Accessed by `func_8008BF84` as `u16`
    u8    field_B;
    u16   field_C;
    u8    field_E;  // Keyframe index offset?
    u8    field_F;  // Keyframe index offset?
    u8    field_10; // State.
    u8    field_11;
    u8    field_12;
    u8    unk_13;
    u32*  unk_14; // Some pointer. All entries have the same value `D_800AD4C4`.
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

/** @brief Collision point data. */
typedef struct
{
    VECTOR3     position_0; // Q19.12
    s_Collision collision_C;
    s32         field_18; // Count of points in circle?
} s_CollisionPoint;

typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800BCDA8;
STATIC_ASSERT_SIZEOF(s_800BCDA8, 4);

typedef struct _SpeedZone
{
    s8   type_0; /** `e_SpeedZoneType` */
    // 1 byte of padding.
    q11_4 minX_2;
    q11_4 maxX_4;
    q11_4 minZ_6;
    q11_4 maxZ_8;
} s_SpeedZone;

typedef struct _WaterZone
{
    u8  isEnabled_0; /** `bool` */
    // 1 byte of padding.
    s16 illumination_2;
    q11_4 minX_4;
    q11_4 maxX_6;
    q11_4 minZ_8;
    q11_4 maxZ_A;
} s_WaterZone;

typedef struct
{
    u8            charaId_0;  /** `e_CharacterId` */
    u8            isLoaded_1; /** `bool` */
    // 2 bytes of padding.
    s32           queueIdx_4;
    s_LmHeader*   lmHdr_8;
    s_FsImageDesc texture_C;
    s_Skeleton    skeleton_14;
} s_CharaModel;
STATIC_ASSERT_SIZEOF(s_CharaModel, 1376);

typedef struct _MapInfo
{
    s16                plmFileIdx_0;
    char               tag_2[4];
    u8                 flags_6; /** `e_MapFlags` */
    // 1 byte of padding.
    const s_WaterZone* waterZones_8;
    const s_SpeedZone* speedZones_C;
} s_MapInfo;

// Rough name.
typedef struct _WorldObjectMetadata
{
    u_Filename name_0;
    s8         field_8;
    s8         lmIdx_9; /** Set to 2 when found in `g_Map.globalLm_138.lmHdr_0` and 3-6 if found in `g_Map.ipdActive_15C[i] (i + 3)`. */
} s_WorldObjectMetadata;

// Rough name.
typedef struct _WorldObjectModel
{
    s_ModelInfo           modelInfo_0;
    s_WorldObjectMetadata metadata_10;
} s_WorldObjectModel;
STATIC_ASSERT_SIZEOF(s_WorldObjectModel, 28);

/** @brief Geometry space world object to draw. */
typedef struct _WorldObject
{
    s_WorldObjectModel* model_0;
    s32                 positionX_4 : 18; /** Q9.8 */
    s32                 positionY_4 : 14; /** Q5.8 */
    s32                 positionZ_8 : 18; /** Q9.8 */
    s32                 pad_8_18    : 14;
    s32                 rotationX_C : 10; /** Q0.10 */
    s32                 rotationY_C : 12; /** Q0.12 */
    s32                 rotationZ_C : 10; /** Q0.10 */
} s_WorldObject;
STATIC_ASSERT_SIZEOF(s_WorldObject, 16);

typedef struct
{
    u8  endOfArray_0_0 : 1;  // End of array marker.
    s32 positionX_0_1  : 10; // X
    s32 positionZ_0_11 : 10; // Z
    u32 sizeX_0_21     : 4;  // X size
    u32 sizeZ_0_25     : 4;  // Z size
    u32 field_0_29     : 3;  // Related to ground height? Used to set `s_func_8006F338::field_2C` which then gets copied by `func_8006F250`, that func has only been seen called by AirScreamer?
} s_func_8006F8FC;
STATIC_ASSERT_SIZEOF(s_func_8006F8FC, 4);

typedef struct _HeldItem
{
    s32           itemId_0; /** `e_InventoryItemId` */
    s32           queueIdx_4;
    char*         textureName_8;
    s_FsImageDesc imageDesc_C;
    s_LmHeader*   lmHdr_14;
    s_Bone        bone_18;
} s_HeldItem;
STATIC_ASSERT_SIZEOF(s_HeldItem, 0x2C);

/** @brief World GFX workspace.
 * TODO: Could be `s_RendererWork`? Will depend on where other data resides.
 * Will: `s_WorldModelWork` fits better, this is mainly responsible for handling model data.
 * `s_WorldEnvWork` should have this name as it is used for general GFX.
 */
typedef struct _WorldGfxWork
{
    s_MapInfo*        mapInfo_0;
    u8                useStoredPoint_4; /** `bool` */
    u8                unk_5[3];
    VECTOR3           ipdSamplePoint_8; /** Used by IPD logic to sample which chunks to load or unload. */
    u8*               charaLmBuffer_14;
    s_CharaModel*     registeredCharaModels_18[Chara_Count];
    s_CharaModel      charaModels_CC[GROUP_CHARA_COUNT];
    s_CharaModel      harryModel_164C;
    s_HeldItem        heldItem_1BAC;             /** The item held by the player. */
    s_func_8006F8FC*  field_1BD8;
    VC_CAMERA_INTINFO vcCameraInternalInfo_1BDC; /** Debug camera info. */
    s_LmHeader        itemLmHdr_1BE4;
    u8                itemLmData_1BF4[4096 - sizeof(s_LmHeader)]; // Retail game uses 2.75kb file, but they allocate 4kb for it.
    s32               itemLmQueueIdx_2BE4;
    s32               objectCount_2BE8;                     /** `objects_2BEC` size. */
    s_WorldObject     objects_2BEC[WORLD_OBJECT_COUNT_MAX]; /** World objects to draw. */
} s_WorldGfxWork;
STATIC_ASSERT_SIZEOF(s_WorldGfxWork, 11708);

// IPD data?
typedef struct
{
    s_IpdHeader* ipdHdr_0;
    s32          queueIdx_4;
    s16          cellX_8;
    s16          cellZ_A;
    q19_12       distance0_C;
    q19_12       distance1_10;
    u8           materialCount_14;
    s8           unk_15[3];
    s32          outsideCount_18;
} s_IpdChunk;
STATIC_ASSERT_SIZEOF(s_IpdChunk, 28);

typedef struct _IpdRow
{
    s16 idx[16];
} s_IpdColumn;
STATIC_ASSERT_SIZEOF(s_IpdColumn, 32);

typedef struct _ActiveTextures
{
    s32        count_0;
    s_Texture* textures_4[10];
} s_ActiveTextures;

typedef struct _IpdTextures
{
    s_ActiveTextures fullPage_0;
    s_ActiveTextures halfPage_2C;
    s_Texture        fullPageTextures_58[8];
    s_Texture        halfPageTextures_118[2];
} s_IpdTextures;
STATIC_ASSERT_SIZEOF(s_IpdTextures, 328);

typedef struct _Map
{
    s_IpdCollisionData collisionData_0; // Default chunk collision data?
    s32                texFileIdx_134;
    s_GlobalLm         globalLm_138;
    char               mapTag_144[4];
    s32                mapTagSize_148;
    s32                ipdFileIdx_14C;
    s_IpdHeader*       ipdBuffer_150;
    s32                ipdBufferSize_154;
    s32                ipdActiveSize_158;
    s_IpdChunk         ipdActive_15C[4];
    s_IpdColumn        ipdGrid_1CC[18];
    s8                 unk_40C[32];     // Could be one extra row in table above.
    s_IpdColumn*       ipdGridCenter_42C;
    s_IpdTextures      ipdTextures_430;
    q19_12             positionX_578;
    q19_12             positionX_57C;
    s32                cellX_580;
    s32                cellZ_584;
    bool               isExterior_588;
} s_Map;
STATIC_ASSERT_SIZEOF(s_Map, 1420);

typedef struct
{
    VECTOR3 field_0[2][1];
} s_WorldEnvWork_84;

/** @brief World environment workspace.
 *  Holds fog distances and ramps, lighting and color parameters,
 *  water zone references, and other per-map environmental data
 *  used during world rendering.
 */
typedef struct _WorldEnvWork
{
    u8            field_0;        // `bool`?
    u8            isFogEnabled_1; /** `bool` */
    u8            field_2;
    u8            field_3;        // Enviroment lighting.
    s_WaterZone*  waterZones_4;
    s32           screenBrightness_8;
    s32           fogNearDistance_C;
    q23_8         fogFarDistance_10; // "DrawDistanmce" in SHME, "has no effect when fog is disabled".
    s32           fogDepthShift_14;   // "FogThing1" from SHME. Affects the distance where fog begins.
    s32           fogIntensity_18;   // "FogThing2" from SHME. Affects the distance where fog begins.
    CVECTOR       fogColor_1C;
    s32           field_20;        // Map lighting.
    u8            field_24; // } RGB. Character color lighting.
    u8            field_25; // }
    u8            field_26; // }
    s8            unk_27;
    CVECTOR       worldTintColor_28;
    MATRIX        field_2C;
    s32           field_4C;
    s16           field_50;
    s32           field_54;
    SVECTOR       field_58; // Rotation.
    VECTOR3       field_60;
    SVECTOR       field_6C; // Player current angles?
    SVECTOR       field_74;
    SVECTOR       field_7C;
    s_WorldEnvWork_84 field_84[3];
    u8            fogRamp_CC[128]; // Fog-related values based on `fogNearDistance_C`/`fogFarDistance_10`.
    u16           field_14C;
} s_WorldEnvWork;

typedef struct
{
    u16              field_0; // Flags.
    u8               field_2; // Size of `field_4`.
    u8               unk_3;
    s_func_8006F8FC* field_4[20]; // Guessed size.
} s_800C4478;

typedef struct
{
    u8      field_0; // `bool`?
    u8      field_1; // `bool`?
    u8      field_2; // `bool`?
    u8      field_3;
    s8      unk_4[4];
    s16     field_8;
    s16     field_A;
    VECTOR3 field_C;
    s8      unk_18[4];
    s32     field_1C;
    s32     field_20;
} s_800C4818;

typedef struct
{
    u8  unk_0[4];
    s16 field_4;
    s16 field_6; // Keyframe index or time.
} s_800C44F0; // Probable size: 8 bytes.

/** Holds file IDs of anim/model/texture for each `e_CharacterId`, along with some data used in VC camera code. */
typedef struct
{
    s16            animFileIdx;
    s16            modelFileIdx;
    s16            textureFileIdx         : 16;
    q8_8           field_6                : 10;
    u16            materialBlendMode_6_10 : 6; /** `e_BlendMode` */
    s_FsImageDesc* field_8;                    // Extra texture pointer? Usually `NULL` in `CHARA_FILE_INFOS`.
    u16            cameraAnchor_C_0  : 2;      /** `e_CameraAnchor` */
    q19_12         cameraOffsetY_C_2 : 14;
    // 2 bytes of padding.
} s_CharaFileInfo;
STATIC_ASSERT_SIZEOF(s_CharaFileInfo, 16);

typedef struct
{
    SVECTOR3 positionTarget_0; /** Q7.8 */
    SVECTOR3 lookAtTarget_6;   /** Q7.8 */
    s16      field_C[2];       // `field_C[1]` gets passed to `vcChangeProjectionValue`.
} s_DmsKeyframeCamera;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCamera, 16);

typedef struct
{
    SVECTOR3 position_0; /** Q7.8 */
    SVECTOR3 rotation_6; /** Q7.8 */
} s_DmsKeyframeCharacter;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCharacter, 12);

typedef struct
{
    s16       keyframeCount_0;
    u8        svectorCount_2;
    u8        field_3;      // Usually 0, but sometimes filled in, possibly junk data left in padding byte.
    char      name_4[4];    // First 4 chars of name. E.g. Code checks for "DAHLIA", file is "DAHL".
    SVECTOR3* svectorPtr_8; // Pointer to `SVECTOR3`s. Unknown purpose.
    union
    {
        s_DmsKeyframeCharacter* character;
        s_DmsKeyframeCamera*    camera;
    } keyframes_C;
} s_DmsEntry;
STATIC_ASSERT_SIZEOF(s_DmsEntry, 16);

typedef struct
{
    s16 startKeyframeIdx_0;
    s16 frameCount_2; /** Frame duration at 30 FPS. */
} s_DmsInterval;
STATIC_ASSERT_SIZEOF(s_DmsInterval, 4);

typedef struct
{
    u8             isLoaded_0; /** `bool` */
    u8             characterCount_1;
    u8             intervalCount_2;
    u8             field_3; // Usually 0, but sometimes filled in.
    u32            field_4; // Unknown, correlates with DMS file size.
    s_DmsInterval* intervalPtr_8;
    VECTOR3        origin_C; /** Q23.8 | Origin point. Gets added to character positions. */
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
    s8   field_6;  /** Height? */
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
    s_800AFE08 sub_0;
    s32        field_1C;
    s16        field_20;
    s16        field_22;
    s32        field_24;
    s32        field_28;
    s32        field_2C;
    s32        field_30;
    s32        field_34;
    s32        field_38;
    s32        field_3C;
    s32        field_40;
    s32        field_44;
    s32        field_48;
    s32        field_4C;
    s32        field_50;
    s32        field_54;
} s_800AFE24; // Size: 85

/** @brief Contains X/Z coordinates and optional 4 bytes of data.
 * Map headers include an array of these, into which `s_EventData` includes an index. */
typedef struct _MapPoint2d
{
    q19_12 positionX_0;

    // Optional data.
    u32   mapIdx_4_0          : 5; /** `e_PaperMapIdx`? */
    u32   field_4_5           : 4;
    u32   loadingScreenId_4_9 : 3; /** `e_LoadingScreenId` */
    u32   field_4_12          : 4;
    q24_8 triggerParam0_4_16  : 8; // Usually a `Q8_ANGLE`
    u32   triggerParam1_4_24  : 8;

    q19_12 positionZ_8;
} s_MapPoint2d;
STATIC_ASSERT_SIZEOF(s_MapPoint2d, 12);

typedef struct _SpawnInfo
{
    q19_12 positionX_0;
    s8  charaId_4;   /** `e_CharacterId` */
    u8  rotationY_5; /** Degrees in Q7.8, range [0, 256]. */
    s8  flags_6;     /** Copied to `stateStep_3` in `s_Model`, with `controlState_2 = ModelState_Uninitialized`. */
    s32 minGameDifficulty_7_0 : 4;
    q19_12 positionZ_8;
} s_SpawnInfo;
STATIC_ASSERT_SIZEOF(s_SpawnInfo, 12);

/** Special map-specific Harry anim data. */
typedef struct
{
    s16   status_0; /** Packed anim status. See `s_ModelAnim::status_0`. */
    s16   status_2; /** Packed anim status. See `s_ModelAnim::status_0`. */
    q3_12 time_4;   /** Fixed-point anim time. */
    s16   keyframeIdx_6;
} s_UnkStruct3_Mo; // Probable size: 8 bytes.

/** Guessed based on in-debugger observation during gameplay.
 * Everything is inited to 0xFFFF and some data is written when the player is hit by monsters.
 * Might be more generic particles/decals struct.
 */
typedef struct _BloodSplat
{
    s16 field_0; // Maybe an array of `u16`s? Contains indices.
} s_BloodSplat;

typedef struct
{
    u8    unk_0;
    u8    field_1;
    u8    field_2;
    u8    unk_3;
    u8    field_4;
    u8    field_5;
    u8    field_6;
    u8    unk_7;
    u8    unk_8[2];
    s16   field_A;
    u8    unk_C[2];
    s16   field_E;
    q3_12 field_10;
    u8    unk_12[4];
    s16   field_16;
    u8    unk_18[8];
    s32   field_20;
    s32   field_24;
} s_MapOverlayHeader_5C;

typedef struct
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} s_MapOverlayHeader_7C;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader_7C, 0x20);

typedef struct
{
    s32    field_0[4];
    s16    field_10[4];
    s32    field_18[4];
    u16    field_28[4];
    u8     field_30[4];
    q3_12  field_34[4]; // Y angles.
    u16    field_3C[4];
    u16    field_44[4];
    s16    field_4C[4];
    u16    field_54[4];
    u16    field_5C[4];
    q4_12  field_64[4];
    s16    field_6c[4];
    s16    field_74;
    s16    unk_76;
    u8     field_78;
} s_MapOverlayHeader_94;

/** TODO: `g_MapOverlayHeader` is part of the map overlay BIN files. Maybe should be moved to `maps/shared.h`.
 * If field has a comment that lists only certain map(s) it means all others set this field to 0.
 * func(?) means the signature is unknown and a default void() was selected for now.
 */
typedef struct _MapOverlayHeader
{
    s_MapInfo*             mapInfo_0;
    u8                     (*getMapRoomIdxFunc_4)(s32 x, s32 y); // Called by `Savegame_MapRoomIdxUpdate`.
    s8                     field_8;
    s32                    (*func_C)();
    // 3 bytes of padding.
    void                   (*bgmEvent_10)(bool);
    s8                     bgmIdx_14;           // Flags? Music related.
    u8                     ambientAudioIdx_15; // Ambient file index from `g_AmbientVabTaskLoadCmds`.
    s8                     field_16;           // Set ambient tint and render distance.
                                               // A value of 3 sets the map to night.
                                               // A value of 2 will sets the map to use a tint used during the hallaway
                                               // intro.
                                               // Giving this and next variable a name will require further investigation
                                               // of `particle.c` code.
    s8                     field_17;           // Set weather to play. Rain, heavy rain, or snow.
    void                   (**loadingScreenFuncs_18)();
    s_MapPoint2d*          mapPointsOfInterest_1C;
    void                   (**mapEventFuncs_20)(); /** Points to array of event functions. */
    s_EventData*           mapEvents_24;
    GsCOORDINATE2*         field_28;
    u8*                    loadableItems_2C;
    const char**           mapMessages_30; // Array of strings.
    s_AnimInfo*            animInfos_34;   // Map-specific anim infos for Harry (for anims 38+).
    s_UnkStruct3_Mo*       field_38; // Array of 40?
    void                   (*worldObjectsInit_3C)(void); // func(?).
    void                   (*worldObjectsUpdate_40)(void);
    void                   (*func_44)();
    void                   (*npcSpawnEvent_48)(); // func(?).
    s_MapHdr_field_4C*     unkTable1_4C; // Related to collision?
    s16                    unkTable1Count_50;
    // 2 bytes of padding.
    s_BloodSplat*          bloodSplats_54;
    s16                    bloodSplatCount_58;
    // 2 bytes of padding.
    s_MapOverlayHeader_5C* field_5C;
    void                   (*func_60)(s32, s32);
    s32                    (*func_64)(POLY_FT4** poly, s32);
    s32                    (*func_68)(POLY_FT4** poly, s32);
    void                   (*func_6C)(); // func(?).
    s32                    (*func_70)(POLY_FT4** poly, s32);
    void                   (*func_74)(); // func(?).
    s32                    (*func_78)(POLY_FT4** poly, s32);
    s_MapOverlayHeader_7C* field_7C;     // only map1_s01, map6_s04.
    void                   (*func_80)(); // func(?).
    s32                    (*func_84)(POLY_FT4** poly, s32);
    s32*                   func_88; // only map0_s01, map7_s01.
    s32                    (*func_8C)(POLY_FT4** poly, s32); // func(?) only map0_s01, map7_s01.
    s32                    (*func_90)(POLY_FT4** poly, s32); // func(?) only map5_s00.
    s_MapOverlayHeader_94* field_94;                    // only map1_s02, map1_s03.
    s32                    (*func_98)(POLY_FT4** poly, s32); // only map1_s02, map1_s03.
    void                   (*func_9C)();                // only map1_s02, map1_s03.
    s32*                   func_A0; // only map1_s03.
    s32                    (*func_A4)(POLY_FT4** poly, s32); // func(?) only map1_s03.
    void                   (*func_A8)(); // func(?) only map6_s02.
    s32                    (*func_AC)(POLY_FT4** poly, s32); // func(?) only map4_s03, map4_s05.
    s32                    (*func_B0)(POLY_FT4** poly, s32); // func(?) only map4_s03, map4_s05.
    s32                    (*func_B4)(POLY_FT4** poly, s32); // func(?) only map1_s03, map4_s05, map6_s01, map6_s02, map5_s01.
    void                   (*func_B8)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    void                   (*func_BC)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    void                   (*func_C0)(); // func(?).
    void                   (*playerMatchArmAnimDisable_C4)(); // func(?).
    void                   (*playerControlFreeze_C8)();
    void                   (*playerControlUnfreeze_CC)(bool setIdle);
    bool                   (*func_D0)(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount); // 0x800C964C
    s32                    (*func_D4)(s32 playerExtraState); // Points to `sharedFunc_800D2C7C_0_s00` which has `void` return type, but changing this funcptr causes mismatch in `func_80085EB8`
    void                   (*func_D8)();                     // Assumed return type.
    void                   (*playerAnimLock_DC)(void);
    void                   (*playerAnimIsLocked_E0)(); // func(?).
    s32                    (*playerAnimUnlock_E4)(s_SubCharacter*, s32); // Assumed return type.
    s64                    (*func_E8)(s_SubCharacter*);      // Is it really `s64`???
    bool                   (*playerMoveDistIsZero_EC)();
    void                   (*playerMoveDistClear_F0)(); // func(?).
    void                   (*playerFallBackward_F4)();
    void                   (*func_F8)(); // func(?).
    void                   (*playerDamageFeetFront_FC)(); // func(?).
    void                   (*func_100)(); // func(?).
    void                   (*func_104)(); // func(?).
    s32                    (*func_108)();
    void                   (*func_10C)(); // func(?).
    void                   (*func_110)(); // func(?).
    void                   (*func_114)(); // func(?).
    void                   (*func_118)(); // func(?).
    void                   (*func_11C)(); // func(?).
    void                   (*func_120)(); // func(?).
    void                   (*func_124)(s_SubCharacter*); // Assumed return type.
    s32                    (*func_128)(s_SubCharacter*); // Assumed return type.
    s32                    (*func_12C)(s_SubCharacter*); // Assumed return type.
    void                   (*func_130)(); // func(?).
    s32                    (*func_134)(s_SubCharacter*); // Assumed return type.
    s32                    (*func_138)(s_SubCharacter*); // Keyframe state getter. Return value depends on the anim update function being used.
    s32                    (*func_13C)(s32, s32, void*, s16, s32); // `arg0` is `s_SubCharacter*`.
    void                   (*func_140)(); // func(?).
    void                   (*func_144)(); // func(?).
    void                   (*func_148)(); // func(?).
    void                   (*func_14C)(); // func(?).
    void                   (*animStartKeyframeIdxGet_150)();
    void                   (*func_154)(); // func(?).
    void                   (*func_158)(q19_12 x, q19_12 z); // only map1_s05, map1_s06.
    void                   (*func_15C)(); // func(?) only map5_s01.
    void                   (*func_160)(); // func(?) only map5_s01.
    void                   (*func_164)(); // func(?) only map5_s01.
    void                   (*particlesUpdate_168)(s32 unused, s32 mapId, s32);
    void                   (*enviromentSet_16C)(s8, u32);
    void                   (*func_170)(); // func(?).
    void                   (*func_174)(); // func(?).
    void                   (*particleHyperBlasterBeamDraw_178)(VECTOR3* vec0, q19_12* rotX, q19_12* rotY);
    void                   (*particleBeamDraw_17C)(const VECTOR3* from, const VECTOR3* to);
    void                   (*particleSoundStop_17C)();
    s32*                   windSpeedX_184;
    s32*                   windSpeedZ_188;
    s32*                   data_18C;
    s32*                   data_190;
    void                   (*charaUpdateFuncs_194[Chara_Count])(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords); /** Guessed params. Funcptrs for each `e_CharacterId`, set to 0 for IDs not included in the map overlay. Called by `Game_NpcUpdate`. */
    s8                     charaGroupIds_248[GROUP_CHARA_COUNT];                              /** `e_CharacterId` values where if `s_SpawnInfo::charaId_4 == Chara_None`, `charaGroupIds_248[0]` is used for `charaSpawns_24C[0]` and `charaGroupIds_248[1]` for `charaSpawns_24C[1]`. */
    s_SpawnInfo            charaSpawns_24C[2][16];                                            /** Array of character type/position/flags. `flags_6 == 0` are unused slots? Read by `Game_NpcRoomInitSpawn`. */
    VC_ROAD_DATA           roadDataList_3CC[100];
    s_func_8006F8FC        field_D2C[200];
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 0x104C);

typedef struct
{
    s8 maxIdx_0;
    u8 selectedEntryIdx_1;
} s_MapMsgSelect;

// TODO: Might just be an array of `char*`, array is in `.data` while strings inside are in `.rodata`?
typedef struct
{
    char* field_0;               // `NULL`
    char* savePadName_4;         // "PAD_NEAR"
    char* firstAidKitName_8;     // "AIDKIT_N"
    char* healthDrinkName_C;     // "DRINK_NE"
    char* ampouleName_10;        // "AMPULE_N"
    char* handgunBulletsName_14; // "BULLET_N"
    char* shotgunShellsName_18;  // "SHELL_NE"
    char* rifleShellsName_1C;    // "SHOT_NEA"
} s_800A99E4;
STATIC_ASSERT_SIZEOF(s_800A99E4, 32);

typedef struct
{
    u8 presetIdx1_0;
    u8 presetIdx2_1;
} s_MapEffectsPresetIdxs;

/** @brief Line of sight data for finished ray trace. TODO: Could rename to `s_Los` to keep "ray" as a generic math term? */
typedef struct
{
    s8              hasHit_0; /** `bool` */
    u8              field_1;
    s8              unk_2[2]; // Probably padding.
    VECTOR3         field_4;  // Q19.12
    s_SubCharacter* chara_10;
    q19_12          field_14; // Hit distance X?
    q19_12          field_18; // Hit distance Z?
    q7_8            field_1C; // Angle.
} s_RayData;

typedef struct
{
    VECTOR3 offset_0;  // Q19.12
    s32     field_C;   // Absolute ground height? Might be using `s_Collision` substruct?
    s16     field_10;
    s16     field_12;
    s8      field_14;  // Count of something? 12 is significant.
    s8      unk_15[3]; // Probably padding.
    s32     field_18;
} s_800C4590;

typedef struct
{
    DVECTOR  screenXy_0[90];
    s16      screenZ_168[18];
    s16      field_18C[72];
    s32      field_21C[39]; // Used as `VECTOR3`?
    u8       field_2B8[200];
    MATRIX   field_380;
    s_Normal field_3A0;
    DVECTOR  screenPos_3A4;
    s32      depthP_3A8;
    SVECTOR  field_3AC;
    u8       unk_3B4[36];
    CVECTOR  field_3D8;

    // Different functions access different data at 0x3DC onwards.
    // Union works for it, but also possible those functions just took different `s_GteScratchData` structs.
    union
    {
        struct
        {
            DVECTOR  screenPos_3DC;
            s32      depthP_3E0;
            MATRIX   field_3E4;
        } vertex;

        struct
        {
            s_Normal field_3DC;
            SVECTOR  field_3E0[3];
        } normal;

        struct
        {
            u8  field_0;
            u8  field_1;
            u8  field_2;
            u8  field_3;
            u8  field_4;
            u8  field_5;
            u8  field_6;
            u8  field_7;
            s32 field_8;
        } s_1;
    } u;
} s_GteScratchData2;

typedef struct
{
    s16   field_0;
    s16   field_2; // Move dist?
    q3_12 field_4; // Angle.
    s16   unk_6;
    s16   unk_8;
    s16   unk_A;
    s16   field_C;
    s16   field_E;
    s16   field_10;
    s16   unk_12;
    s16   field_14;
    s16   field_16;
    s16   field_18;
    s16   unk_1A;
} s_800AE204;

typedef struct
{
    s_800AE204* ptr_0;
    s16         count_4;
    s16         unk_6;
    u8          unk_8;
    u8          unk_9;
    u8          unk_A;
    u8          unk_B;
} s_800AE4DC;

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3; // Map marking sprite height?
} s_800AE8A0_0;

typedef struct
{
    s8 field_0;
    s8 field_1;
    u8 field_2;
    u8 field_3;
} s_800AE8A0_4;

/** Paper map marking graphic data? */
typedef struct
{
    POLY_FT4*    field_0;
    s_800AE8A0_0 field_4;
    s_800AE8A0_4 field_8;
    s32          field_C; // Count.
} s_func_80068E0C;

typedef struct
{
    POLY_FT4* field_0;
    SVECTOR   field_4; // Q23.8
    MATRIX    field_C;
    VECTOR3   field_2C; // Q23.8
    s32       field_38;
    DVECTOR   field_3C;
    s32       field_40;
    DVECTOR   field_44;
    DVECTOR   field_48;
} s_func_80065B94;

typedef struct
{
    POLY_GT4* field_0;
    MATRIX    field_4;
    SVECTOR   field_24[3];
    VECTOR3   field_3C; // Q19.12
    s32       field_48;
    DVECTOR   field_4C;
    DVECTOR   field_50;
    DVECTOR   field_54;
    DVECTOR   field_58;
    s32       field_5C;
    s32       field_60;
    s32       field_64;
    s32       field_68;
    s32       field_6C;
    s32       field_70;
    s32       field_74;
    s32       field_78;
} s_func_80066184;

typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s32 field_4;
    s32 field_8;
} s_800C42E8;

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    u16 field_8;
    u16 field_A;
    u8  field_C;
} s_800C4418;

typedef struct
{
    VECTOR3 field_0; // Q23.8 | Position.
    MATRIX  field_C;
    s32     field_2C;
    DVECTOR field_30;
    s16     field_34[24];
    s16     field_64[24];
    s16     field_94[24];
    s16     field_C4;
    s16     field_C6;
    s16     field_C8;
    s16     field_CA;
    s16     field_CC;
    s16     field_CE;
    s32     field_D0;
    s32     field_D4;
    s32     field_D8;
    s16     field_DC[4];
    s16     field_E4[4];
    union
    {
        DVECTOR field_0[4];
        s32     raw_0[4];
    } u_field_EC;
    union
    {
        DVECTOR field_0[4];
        s32     raw_0[4];
    } u_field_FC; // Q3.12 | Positions or offsets.
    s32     field_10C[4];
    s32     field_11C[4];
} s_func_8005E89C;

typedef struct
{
    s_func_8005E89C field_0;
    PACKET*         field_12C;
    CVECTOR         field_130;
    CVECTOR         field_134;
    SVECTOR         field_138;
    s32             field_140;
    DVECTOR         field_144;
    u16             field_148;
    u8              unk_14A[2];
    s32             field_14C;
    s32             field_150;
    s32             field_154;
    s32             field_158;
    s32             field_15C;
    s32             field_160;
    s32             field_164;
    s32             field_168;
    s32             field_16C;
    s32             field_170;
    s32             field_174;
} s_func_80060044;

typedef struct
{
    s_func_8005E89C field_0;
    CVECTOR         field_12C;
    CVECTOR         field_130;
    SVECTOR         field_134;
    SVECTOR         field_13C;
    SVECTOR         field_144;
    VECTOR3         field_14C;
    s32             field_158;
    s32             field_15C;
    s32             field_160;
    s32             field_164;
    s32             field_168;
    DVECTOR         field_16C;
    s32             field_170;
    s32             field_174;
    s32             field_178;
    s32             field_17C;
    s32             field_180;
    s32             field_184;
    s32             field_188;
    s32             field_18C;
    s32             field_190;
    s32             field_194;
    s32             field_198;
    s32             field_19C;
    s32             field_1A0;
} s_func_800611C0;

typedef struct
{
    s_func_8005E89C field_0;
    CVECTOR         field_12C;
    CVECTOR         field_130;
    SVECTOR         field_134[25];
    VECTOR3         field_1FC; // Q19.12
    q20_12          field_208;
    s32             field_20C;
    s32             field_210;
    s32             field_214[25];
    DVECTOR         field_278[25];
    s32             field_2DC;
} s_func_80062708;

typedef struct
{
    s_func_8005E89C field_0;
    SVECTOR field_12C;
    s8      unk_138[8];
    DVECTOR field_13C;
    s32     field_140;
    s32     field_144;
} s_func_80064FC0;

typedef struct
{
    POLY_G4*  field_0;
    DR_TPAGE* field_4;
    SVECTOR   field_8[3];
    MATRIX    field_20;
    VECTOR3   field_40; // Q23.8
    s32       field_4C;
    s16       field_50;
    s32       field_54[3];
    s16       field_60[3];
    s32       field_68;
} s_func_800652F4;

typedef struct
{
    s_func_8005E89C field_0;
    MATRIX          field_12C;
    SVECTOR         field_14C[3];
    SVECTOR         field_164;
    VECTOR          field_16C[3];
    VECTOR          field_19C;
    VECTOR          field_1AC; // Q27.4
    s32             field_1BC;
    s32             field_1C0;
    s32             field_1C4;
    s32             field_1C8;
    DVECTOR         field_1CC;
    s16             field_1D0;
    u8              unk_1D2[2];
    s32             field_1D4; // Count.
    s32             field_1D8;
    s32             field_1DC;
    s32             field_1E0;
    s32             field_1E4;
    s32             field_1E8;
} s_func_80063A50;

typedef struct
{
    s_func_8005E89C field_0;
    PACKET*         field_12C;
    CVECTOR         field_130;
    CVECTOR         field_134;
    SVECTOR         field_138;
    u8              unk_140[16];
    s32             field_150;
    DVECTOR         field_154;
    u16             field_158;
    u16             field_15A;
    u8              field_15C;
    s32             field_160;
    s32             field_164;
    s32             field_168;
} s_func_80064334;

typedef struct
{
    s_func_8005E89C field_0;
    s_Collision     field_12C;
    MATRIX          field_138;
    SVECTOR         field_158[4];
    VECTOR          field_178[4];
    CVECTOR         field_1B8;
    CVECTOR         field_1BC;
    s32             field_1C0;
    s32             field_1C4;
    s32             field_1C8;
    s32             field_1CC;
    s32             field_1D0;
    DVECTOR         field_1D4;
} s_func_800CD1F8;

typedef struct
{
    MATRIX  field_0;
    SVECTOR field_20;
    VECTOR  field_28; // Q27.4
    s32     field_38;
    s32     field_3C[5];
    s32     field_50;
} s_func_8006342C;

// ========
// GLOBALS
// ========

extern s_FsImageDesc g_MainImg0; // 0x80022C74 - TODO: Part of main exe, move to `main/` headers?

extern const s_MapInfo MAP_INFOS[MapType_Count];

extern char D_80028544[16];

extern RECT D_80028A20;

extern const s_AnimInfo D_80028B94[];

extern s_800C44F0 D_800294F4[];

extern const s_AnimInfo* D_800297B8;

extern u_Filename D_8002B2CC;

extern s_FsImageDesc g_Font16AtlasImg;
extern s_FsImageDesc g_KonamiLogoImg;
extern s_FsImageDesc g_KcetLogoImg;
extern s_FsImageDesc g_TitleImg;
extern s_FsImageDesc g_PaperMapImg;
extern s_FsImageDesc g_PaperMapMarkingAtlasImg;
extern s_FsImageDesc g_ItemInspectionImg;
extern s_FsImageDesc g_LoadingScreenImg;
extern s_FsImageDesc g_ControllerButtonAtlasImg;
extern s_FsImageDesc g_BrightnessScreenImg0;
extern s_FsImageDesc g_BrightnessScreenImg1;
extern s_FsImageDesc g_DeathTipImg;
extern s_FsImageDesc g_HealthPortraitImg;
extern s_FsImageDesc g_InventoryKeyItemTextureImg;
extern s_FsImageDesc g_FirstAidKitItemTextureImg;

/** Some intentory item texture (`ITEM/TIM07.TIM`). */
extern s_FsImageDesc D_800A9074;

extern s_FsImageDesc D_800A907C;

extern s_FsImageDesc D_800A9084;

extern s_FsImageDesc D_800A908C;

extern s_FsImageDesc D_800A9094;

extern s_FsImageDesc g_Font24AtlasImg; // 0x800A909C

/** Array containg file IDs used for each `e_CharacterId`, used in `Fs_QueueStartReadAnm`. */
extern s_CharaFileInfo CHARA_FILE_INFOS[Chara_Count]; // 0x800A90FC

extern s_MapEffectsInfo g_MapEffectsPresets[21];

extern s_StructUnk3 D_800A952C;

extern u16 g_BgmChannelSetTaskCmds[];

extern s32 D_800A9A20;

/** X. */
extern s32 D_800A9A24;

/** Z. */
extern s32 D_800A9A28;

/** Loaded NPC types in memory and their `g_CharaTypeAnimInfo` indices. */
extern s8 g_CharaAnimInfoIdxs[Chara_Count];

extern s32 D_800A9EB0;

extern s_FsImageDesc D_800A9EB4;

extern s_FsImageDesc D_800A9EBC;

extern s_FsImageDesc D_800A9EC4;

/** Related to sound commands. */
extern u16 g_BgmTaskLoadCmds[];

extern u16 g_AmbientVabTaskLoadCmds[];

/** @brief Stores a loaded character's animation data information. */
extern s_CharaAnimDataInfo g_CharaTypeAnimInfo[];

extern s32 D_800A9938;

extern u8 D_800A9944[];

/** Player anim info? */
extern s_AnimInfo D_800A998C;

/** Current player anim index store? */
extern u8 D_800A9990;

// Likely declared as static inside the function that uses it.
extern s32 D_800A99A0;

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s32 g_MapMsg_CurrentIdx;

extern s16 g_MapMsg_SelectFlashTimer;

extern s8 g_PaperMapFileIdxs[24];

extern s8 g_PaperMapMarkingFileIdxs[56];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A0C; // Old IDB name `FS_AllFilesLoaded`, though FS code doesn't set it.

extern s32 g_MapEventSysState; /** `e_InventoryItemId` */

extern s32 g_MapEventLastUsedItem; /** `e_InventoryItemId` */

/** Radio pitch state based on the distance from the player to an enemy. Range: `[0, 3]`. */
extern s32 g_RadioPitchState;

extern void (*g_SysStateFuncs[])(void);

extern s32 D_800A9A68;

/** Counts the amount of times that demos has been play in the current game session. */
extern s8 g_Demo_ReproducedCount;

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

extern s_MapEffectsPresetIdxs D_800A9F80;

extern s_MapEffectsPresetIdxs D_800A9F84;

extern s_MapEffectsPresetIdxs D_800A9F88;

extern s_MapEffectsPresetIdxs D_800A9F8C;

extern s_MapEffectsPresetIdxs D_800A9F98;

extern u32 D_800A9FB0;

extern s32 D_800A9FB4[];

extern u8 D_800AA604[][16];

extern u8 D_800AE185;

extern u8 D_800AE186;

extern u8 g_SysState_GameOver_TipIdx;

extern s8 pad_bss_800BCD81[3];

/** Copy of delta timers.
 * Appears to be used as save of the delta timer currently used as some instances where 2D backgrounds
 * are drawn uses `g_DeltaTimeRaw` while `g_DeltaTime` is being stopped.
 */
extern s32 g_DeltaTimeCpy;

extern s32 pad_bss_800BCD88[2];

extern s_EventData* g_ItemTriggerEvents[];

extern s32 pad_bss_800BCD94[5];

extern s_800BCDA8 D_800BCDA8[2];

extern s_MapPoint2d D_800BCDB0;

extern s32 pad_bss_800BCDD0;

/** Related to special item interactions. */
extern s32 g_ItemTriggerItemIds[5];

extern u8 D_800BCDD4;

extern s8 pad_bss_800BCDD5[3];

extern s_EventData* g_MapEventData;

/** `e_InventoryItemId` | related to displaying items. */
extern u8 D_800AE187;

extern s16 D_800AE1A8;

extern s_800AE204 D_800AE204[26];

extern s32 g_Items_PickupAnimState;

extern q19_12 g_Items_PickupScale;

extern s16 D_800AE520[];

extern s16 D_800AE564[];

extern s16 D_800AE5CC[];

extern s16 D_800AE5F0[];

extern u8 D_800AE700[];

/** `[1]` contains relative paper map file indices. */
extern u8 D_800AE740[][2];

extern s32 D_800AE770;

extern q3_12 g_Player_FlexRotationY;

extern q3_12 g_Player_FlexRotationX;

/** Related to player. */
extern u8 D_800AF220;

/** @brief Last weapon selected. While it is being assigned the value of
 * `g_SysWork::playerCombat_38::weaponAttack_F` this time it is used to determine
 * the last weapon used in order to load the required animation data.
 */
extern s32 g_Player_LastWeaponSelected;

extern s_AnimInfo HARRY_BASE_ANIM_INFOS[]; // Maybe part of bigger struct. 0x800AF228

extern s16 D_800AF506;

extern s16 D_800AF526;

extern s16 D_800AF5C6;

extern s16 D_800AF624;

/** Keyframe index. */
extern s16 D_800AF626;

/** Generic collision global used by high-level getters. */
extern s_CollisionPoint g_CollisionPoint;

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern const s_AreaLoadSfx SfxPairs[25];

extern s32 D_800AFD3C;

extern s32 D_800AFD44;

extern s32 D_800AFD60;

extern s32 D_800AFD9C;

extern SVECTOR D_800AFDB0;

extern s32 D_800AFDEC;

extern PACKET D_800BFBF0[2][0xA10];

extern u8 g_Items_GunsMaxLoadAmmo[36]; // Max loaded ammo that a weapon can hold. 0x800AD4A0

extern const char* INVENTORY_ITEM_NAMES[];

extern const char* g_ItemDescriptions[];

extern s_FsImageDesc D_800A90A4;

extern s_FsImageDesc D_800A90B4;

extern s_SubCharacter D_800BA00C; // Often passed to `func_800700F8`, might not be full `s_SubCharacter`?

extern u8 D_800BC74F;

extern u16 D_800BCCB0;

extern u32 D_800A999C;

extern u16 D_800BCCB2;

/** @brief Packed screen fade effect data. Uses `e_ScreenFadeState`.
 *
 * Data is packed as follows:
 * State as `e_ScreenFadeState`: bits 0-2.
 * Is white:                     bit 3.
 *
 * TODO: Reference enum entries for details below.
 * 0-1   - Nothing.
 * 2-5   - Fades to black and keeps the screen black.
 * 6-7   - Fades from black.
 * 10-15 - Fades to white and keeps the screen white.
 * 16    - Fades to black.
 */
extern s32 g_Screen_FadeStatus;

extern s32 D_800BCD5C;

extern s_MapMsgSelect g_MapMsg_Select;

extern u8 g_MapMsg_AudioLoadBlock;

extern s8 g_MapMsg_SelectCancelIdx;

extern s32 D_800BCD84;

/** Related to main menu fog randomization. */
extern s8* D_800BCDE0; // Type assumed.

/** Angles. */
extern s16 D_800BCDE8[8];

extern u16 D_800BCE14;

// TODO: Rename to `g_WorldGfxWork`.
extern s_WorldGfxWork g_WorldGfx;

extern s_IpdCollisionData* D_800C1010[4];

extern s_Map g_Map;

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s16 D_800C16A4;

extern s16 D_800C391E;

extern s8 D_800C39A0;

/** Functions from `bodyprog_8003AB28` access `g_WorldEnvWork` as constant, but some functions from `bodyprog_80055028` write to it.
 * It appears that g_WorldEnvWork is intended to be defined inside `bodyprog_80055028` as writable and declared as read-only (`const`) outside of it.
 */
// extern s_WorldEnvWork g_WorldEnvWork;

extern GsCOORDINATE2* D_800C42B8;

extern VECTOR3 D_800C42C0;

extern VECTOR3* D_800C42CC;

extern u16 D_800C42D0;

extern u16 D_800C42D2;

extern s_800C42E8 D_800C42E8[24];

extern s16 D_800C4408;

extern s16 pad_bss_800C440A;

extern GsCOORDINATE2* D_800C440C;

extern GsCOORDINATE2* D_800C4410;

/** Flags. */
extern s8 D_800C4414;

extern s8 pad_bss_800C4415[3];

extern s_800C4418 D_800C4418;

extern s16 D_800C4454;

// emoose: Also works: `extern u16 D_800C4478[];`, `arg0->field_4 = D_800C4478[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_800C4478 D_800C4478;

extern s8 D_800C447A;

extern s16 D_800AEEDC[][2]; // Type assumed.

extern s16 D_800AEF78[][2]; //  Type assumed.

extern s16 D_800AF014[];

extern s16 D_800AF04C[];

extern s16 D_800AF070[]; // Type assumed.

extern s16 D_800AF1FC[]; // Type assumed.

extern u8 D_800C4606;

extern s_Collision D_800C4620;

extern VECTOR3 D_800C4640[2][8];

/** Y angles. */
extern q3_12 D_800C4700[8];

/** Times. */
extern q19_12 D_800C4710[];

/** Q19.12 */
extern VECTOR3 D_800C4788[];

extern VECTOR3 D_800C47B8;

extern VECTOR3 D_800C47C8[];

extern VECTOR3 D_800C47E8;

extern s_RayData D_800C47F8;

extern s_800C4818 D_800C4818;

extern s32 D_800C48F0;

extern u8 D_800AD480[24];

/** Weapon attacks. */
extern s_800AD4C8 D_800AD4C8[70];

extern const s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

extern s16 SQRT[100];

// ==========
// FUNCTIONS
// ==========

/** @unused Possibly a leftover from when the save menu was part of `BODYPROG.BIN`.
 * Draws some string in display space.
 */
void func_80032CE8(void);

void func_80032D1C(void);

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop(void);

/** @brief Set player position.
 * Used for setting the position of the player when transitioning in from rooms.
 */
void Chara_PositionSet(s_MapPoint2d* mapPoint);

void func_8003943C(void);

/** `SysState_Fmv` update function.
 * Movie to play is decided by `2072 - g_MapEventParam`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update(void);

s32 Map_TypeGet(void);

void CharaModel_Free(s_CharaModel* model);

void Ipd_PlayerChunkInit(s_MapOverlayHeader* mapHdr, s32 playerPosX, s32 playerPosZ);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 Ipd_ChunkInitCheck(void);

/** `arg0` should be `void*`? */
void Gfx_InGameDraw(s32 arg0);

void WorldObject_ModelNameSet(s_WorldObjectModel* arg0, char* newStr);

/** Submits a world object to draw. */
void WorldGfx_ObjectAdd(s_WorldObjectModel* arg0, const VECTOR3* pos, const SVECTOR3* rot);

/** @unused Returns held item ID. */
s32 WorldGfx_HeldItemIdGet(void);

s32 WorldGfx_PlayerPrevHeldItem(s_PlayerCombat* combat);

/** @brief Loads and sets an item held by the player.
 *
 * @param itemId ID of the held item to load (`e_InventoryItemId`).
 * @return Model or texture queue index.
 */
s32 WorldGfx_PlayerHeldItemSet(e_InventoryItemId itemId);

void func_8003D01C(void);

void func_8003D03C(void);

/** Loads the model of an item held by the player? */
void WorldGfx_HeldItemDraw(void);

bool WorldGfx_IsCharaModelPresent(e_CharacterId charaId);

/** @brief Sets the material for a character model.
 *
 * @param charaId ID of the character whose model to update.
 * @param blendMode Material blend mode to set (`e_BlendMode`).
 */
void WorldGfx_CharaModelMaterialSet(e_CharacterId charaId, s32 blendMode);

/** @brief Makes a character transparent. */
void WorldGfx_CharaModelTransparentSet(e_CharacterId charaId, bool enableTransparency);

void WorldGfx_CharaFree(s_CharaModel* model);

void WorldGfx_HarryCharaLoad(void);

/** @brief Loads default characters in the map overlay.
 *
 * @param mapHdr Map header.
 * @return Character model queue index.
 */
s32 WorldGfx_MapInitCharaLoad(s_MapOverlayHeader* mapHdr);

void WorldGfx_CharaLmBufferAssign(s8 forceFree);

s32 func_8003DD74(e_CharacterId charaId, s32 arg1);

/** `arg1` is packed data. Each byte is a separate value. */
void WorldGfx_HeldItemAttach(e_CharacterId charaId, s32 arg1); // Called by some chara init funcs.

void func_8003E740(void);

void Gfx_MapInitMapEffectsUpdate(s32 idx0, s32 idx1);

void func_8003EDA8(void);

void Gfx_MapEffectsUpdate(s32 idx0, s32 idx1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5);

q19_12 func_8003F4DC(GsCOORDINATE2** coords, SVECTOR* rot, q19_12 alpha, s32 arg3, u32 arg4, s_SysWork* sysWork);

u32 func_8003F654(s_SysWork_2388* arg0);

s32 func_8003F6F0(s32 arg0, s32 arg1, s32 arg2);

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight);

s32 func_800868F4(s32 arg0, s32 arg1, s32 idx);

/** @brief Computes the weighted average of `a` and `b`.
 *
 * @param a First value.
 * @param b Second value.
 * @param weight Weight as a fixed-point alpha in Q3.12, range `[0, 4096]`.
 * @return Weighted average of `a` and `b`.
 */
q19_12 Math_WeightedAverageGet(s32 a, s32 b, q19_12 weight);

void func_8003FCB0(s_MapEffectsInfo* arg0, s_MapEffectsInfo* arg1, s_MapEffectsInfo* arg2, q19_12 alphaTo);

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight0, q19_12 weight1, q19_12 alphaTo);

void func_8003FE04(s_MapEffectsInfo* arg0, s_MapEffectsInfo* arg1, s_MapEffectsInfo* arg2, q19_12 alphaTo);

s32 func_8003FEC0(s_MapEffectsInfo* arg0);

void func_8003FF2C(s_StructUnk3* arg0);

void func_80040004(s_MapOverlayHeader* overlayHdr);

void func_80040014(void);

/** @brief Computes the stereo sound balance based on the relative position to the camera.
 *
 * @param soundPos Sound source position.
 * @return Stereo sound balance in the range [-127, 127], where values affect the left-right channel balance.
 */
s8 Sound_StereoBalanceGet(const VECTOR3* soundPos);

bool func_80040B74(e_CharacterId charaId);

/** Related to the screen. */
void func_80040BAC(void);

void func_80040E7C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);

void func_80041074(GsOT* ot, s32 arg1, SVECTOR* rot, const VECTOR3* pos);

void func_800410D8(VECTOR3* pos0, q19_12* azimuthAngle, q19_12* altitudeAngle, SVECTOR* rot, const VECTOR3* pos1);

/** @brief Computes the relative spherical rotation on the Y-axis from one direction to another,
 * derived from normalized world-space offsets.
 *
 * @param azimuthAngle Output azimuth angle (Y rotation).
 * @param altitudeAngle Output altitude angle (X rotation).
 * @param offsetFrom First world-space offset (Q19.12).
 * @param offsetTo Second world-space offset (Q19.12).
 */
void Math_RelativeRotationGet(q19_12* azimuthAngle, q19_12* altitudeAngle, const VECTOR* offsetFrom, const VECTOR* offsetTo);

void func_8004137C(VECTOR3* result, const VECTOR* offset0, const VECTOR* offset1, s32 screenDist);

void func_800414E0(GsOT* arg0, VECTOR3* arg1, s32 arg2, q19_12 angle0, q19_12 angle1);

/** @brief Gets the load status of a queue entry by utilizing `Fs_QueueIsEntryLoaded`.
 *
 * @param queueIdx Index of the queue entry to check.
 * @return Queue entry load status (`e_FsQueueEntryLoadStatus`).
 */
u32 Fs_QueueEntryLoadStatusGet(s32 queueIdx);

void Map_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize);

void Lm_Init(s_GlobalLm* globalLm, s_LmHeader* lmHdr);

void LmHeader_Init(s_LmHeader* lmHdr);

/** @brief Clears `queueIdx_4` in array of `s_IpdChunk` */
void Ipd_ActiveChunksQueueIdxClear(s_IpdChunk* chunks, s32 chunkCount);

void Ipd_TexturesInit(void);

void Map_IpdCollisionDataInit(void);

/** @brief Places an IPD chunk at given XZ chunk cell coordinates.
 *
 * @param ipdFileIdx Index of the IPD chunk file to place.
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 */
void Map_PlaceIpdAtCell(s16 ipdFileIdx, s32 cellX, s32 cellZ);

void Ipd_ActiveMapChunksClear(void);

void Ipd_TexturesRefClear(void);

void Map_WorldClearReset(void);

void Map_GlobalLmFree(void);

s_Texture* Texture_InfoGet(char* texName);

void Ipd_MapFileInfoSet(char* mapTag, e_FsFile plmIdx, s32 activeIpdCount, bool isExterior, e_FsFile ipdFileIdx, e_FsFile texFileIdx);

void Ipd_ActiveChunksClear(s_Map* map, s32 arg1);

/** @brief Locates all IPD files for a given map type.
 *
 * Example:
 * Map type THR.
 * `file 1100` is `THR0205.IPD`, `ipdGridCenter_42C[2][5] = 1100`.
 */
void Map_MakeIpdGrid(s_Map* map, char* mapTag, e_FsFile fileIdxStart);

/** @brief Converts two hex `char`s to an integer hex value.
 *
 * @param out Output hex `int`.
 * @param hex0 First hex `char`.
 * @param hex1 Second hex `char`.
 */
bool ConvertHexToS8(s32* out, char hex0, char hex1);

s_IpdCollisionData** func_800425D8(s32* collDataIdx);

s_IpdCollisionData* func_800426E4(s32 posX, s32 posZ);

s32 func_8004287C(s_WorldObjectModel* arg0, s_WorldObjectMetadata* metadata, q19_12 posX, q19_12 posZ);

/** @brief Gets the load state of an LM file.
 *
 * @param
 * @return LM file load state `(e_StaticModelLoadState`).
 */
u32 LmHeader_LoadStateGet(s_GlobalLm* globalLm);

/** @brief Gets the load state of an IPD file.
 *
 * @param
 * @return IPD file load state `(e_StaticModelLoadState`).
 */
u32 IpdHeader_LoadStateGet(s_IpdChunk* chunk);

/** @brief Checks if an IPD file is loaded.
 *
 * @param ipdIdx IPD data index.
 * @return `true` if the IPD file is loaded, `false` otherwise.
 */
bool IpdHeader_IsLoaded(s32 ipdIdx);

/** Starts the process of loading map geometry and assigns textures when the game is set in a loading screen mode? */
void Ipd_ChunkInit(q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ);

/** @brief Computes the distance from an XZ position to the edge of an XZ chunk cell boundary.
 * For exteriors, the cell boundary is expanded by `Q12(1.0f)`.
 * If the position resides inside the chunk, the distance is `Q12(0.0f)`.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 * @param isExterior `true` for padded exterior, `false` for non-padded interior.
 * @return Padded distance from the XZ position to the XZ chunk cell.
 */
q19_12 Ipd_PaddedDistanceToEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ, bool isExterior);

/** @brief Computes the distance from an XZ position to the edge of an XZ chunk cell boundary.
 * If the position resides inside the chunk cell, the distance is `Q12(0.0f)`.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 * @return Distance from the XZ position to the XZ chunk cell boundary.
 */
q19_12 Ipd_DistanceToEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ);

/** Loads geometry, sets materials and properly assigns the position of the map when loading a new room/map? */
s32 Map_ChunkLoad(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ);

void Ipd_ActiveChunksSample(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

void Ipd_DistanceToEdgeCalc(s_IpdChunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

/** Sets materials for active chunks? */
void Ipd_ChunkMaterialsApply(s_Map* map);

s32 Map_IpdIdxGet(s32 cellX, s32 cellZ);

bool Map_IsIpdPresent(s_IpdChunk* chunks, s32 cellX, s32 cellZ);

s_IpdChunk* Ipd_FreeChunkFind(s_IpdChunk* chunks, bool isExterior);

s32 Ipd_LoadStart(s_IpdChunk* chunk, e_FsFile fileIdx, s32 cellX, s32 cellZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

/** Checks if currently loaded chunks have been loaded properly. */
bool Ipd_AreChunksLoaded(void);

bool func_80043830(void);

/** Checks if a position is within the current map chunk. */
bool func_8004393C(q19_12 posX, q19_12 posZ);

void Ipd_ChunkCheckDraw(GsOT* ot, s32 arg1);

bool Ipd_CellPositionMatchCheck(s_IpdChunk* chunk, s_Map* map);

/** Checks if PLM texture is loaded? */
bool IpdHeader_IsTextureLoaded(s_IpdHeader* ipdHdr);

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHdr);

void IpdHeader_FixOffsets(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount, s_ActiveTextures* fullPageActiveTexs, s_ActiveTextures* halfPageActiveTexs, e_FsFile fileIdx);

void Ipd_MaterialsLoad(s_IpdHeader* ipdHdr, s_ActiveTextures* fullPageActiveTexs, s_ActiveTextures* halfPageActiveTexs, e_FsFile fileIdx);

/** Checks if IPD is loaded before returning texture count? */
s32 Ipd_HalfPageMaterialCountGet(s_IpdHeader* ipdHdr);

/** Returns inverse result of `LmFilter_IsHalfPage`. */
bool LmFilter_IsFullPage(s_Material* mat);

bool LmFilter_IsHalfPage(s_Material* mat);

void IpdHeader_FixHeaderOffsets(s_IpdHeader* ipdHdr);

/** @brief Assigns `s_ModelHeader` pointers to models in `s_IpdHeader` by searching the given `s_LmHeader` array. */
void IpdHeader_ModelLinkObjectLists(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount);

/** @brief Searches `s_LmHeader` for objects with the given `objName`. */
s_ModelHeader* LmHeader_ModelHeaderSearch(u_Filename* modelName, s_LmHeader* lmHdr);

/** @brief Assigns `s_ModelHeader` pointers to each `s_IpdModelBuffer` in `s_IpdHeader`. */
void IpdHeader_ModelBufferLinkObjectLists(s_IpdHeader* ipdHdr, s_IpdModelInfo* ipdModels);

/** Sets IPD collision data chunk cells? */
void func_80044044(s_IpdHeader* ipd, s32 cellX, s32 cellZ);

/** @brief Draws an IPD chunk.
 *
 * @param ipdHdr Header of the IPD chunk to draw.
 * @param posX X world position.
 * @param posZ Z world position.
 * @param ot Ordering table.
 * @param arg4 TODO
 */
void Gfx_IpdChunkDraw(s_IpdHeader* ipdHdr, q19_12 posX, q19_12 posZ, GsOT* ot, s32 arg4);

bool func_80044420(s_IpdModelBuffer* modelBuf, s16 arg1, s16 arg2, q23_8 posX, q23_8 posZ);

/** Loads anim file? */
void Anim_BoneInit(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

s_AnimInfo* func_80044918(s_ModelAnim* anim);

void Anim_BoneUpdate(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, q19_12 alpha);

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

/** @brief Gets the duration of an animation. A duration can be constant or variable.
 *
 * @param unused @unused
 * @param animInfo Animation info from which to get the duration.
 * @return Animation duration.
 */
q19_12 Anim_DurationGet(s_Model* unused, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 0. First param might be `s_SubCharacter` instead.
 * Used for anim init?
 */
void Anim_Update0(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coords, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 1.
 * Used for looped anims?
 */
void Anim_Update1(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 2.
 * The generic update func?
 */
void Anim_Update2(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 3.
 * Same as `Anim_Update2` but sine-based?
 */
void Anim_Update3(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Something related to player weapon position. Takes coords to arm bones. */
void func_80044F14(GsCOORDINATE2* coord, q3_12 rotZ, q3_12 rotX, q19_12 rotY);

s8 Bone_ModelIdxGet(s8* ptr, bool arg1);

/** Skeleton setup? Assigns bones pointer for the skeleton and resets fields. */
void Skeleton_Init(s_Skeleton* skel, s_LinkedBone* bones, u8 boneCount);

/** Clears skeleton bone flags/mask. Called by `Skeleton_Init`. */
void func_80045014(s_Skeleton* skel);

/** Anim func. Used in tandem with skeleton bone traversal. */
void func_8004506C(s_Skeleton* skel, s_LmHeader* lmHdr);

/** Anim func. */
void func_80045108(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2, s32 arg3);

/** Anim func. */
void Skeleton_BoneModelAssign(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2);

/** Anim func. Param names are rough. */
void func_80045258(s_LinkedBone** boneOrd, s_LinkedBone* bones, s32 boneIdx, s_LmHeader* lmHdr);

/** Anim func. */
void func_800452EC(s_Skeleton* skel);

/** Anim func. Traverses skeleton bones for something. */
void func_80045360(s_Skeleton* skel, s8* arg1);

/** Anim func. Traverses skeleton bones to set flags/mask.
 * `cond` may actually be another `s_Skeleton` pointer.
 */
void func_800453E8(s_Skeleton* skel, bool cond);

/** Does something with skeleton bones. `arg0` is a struct pointer. */
void func_80045468(s_Skeleton* skel, s32* arg1, bool cond);

void func_80045534(s_Skeleton* skel, GsOT* ot, s32 arg2, GsCOORDINATE2* coord, q3_12 arg4, u16 arg5, s_FsImageDesc* images);

/** `arg0` is probably a bit flag. */
void func_8004C564(u8 arg0, s8 weaponAttack);

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

void GameFs_UniqueItemModelLoad(u8 itemId);

void GameFs_MapItemsTextureLoad(s32 mapId);

/** @brief Attaches a weapon model to the player's hand.
 *
 * @param weaponAttack Packed weapon attack. See `WEAPON_ATTACK`.
 */
void Gfx_PlayerHeldItemAttach(u8 weaponAttack);

void func_8005487C(s32);

void func_80054A04(u8 arg0);

bool Gfx_PickupItemAnimate(u8 itemId);

/** @brief Calculates the ammo needed to reload the equipped gun.
 * @param `currentAmmo` pointer to the variable holding the current amount of loaded ammunition of the equipped weapon.
 * @param `availableAmmo` pointer to the variable holding the current amount of available ammunition for the equipped weapon.
 * @param `gunIdx` Index of the gun being reloaded. `e_EquippedWeaponId`.
 */
void Items_AmmoReloadCalculation(s32* currentAmmo, s32* availableAmmo, u8 gunIdx); // 0x80054FC0

void WorldEnv_Init(void);

/** @brief Draws 2D screen effects for the flashlight's lens flare and glow. */
void Gfx_2dEffectsDraw(void);

/** Sets visual world parameters. */
void func_80055330(u8 arg0, s32 arg1, u8 arg2, s32 tintR, s32 tintG, s32 tintB, q23_8 brightness);

void WorldEnv_FogParamsSet(u8 isFogEnabled, u8 fogColorR, u8 fogColorG, u8 fogColorB);

void func_800553E0(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);

/** `arg0` type assumed. */
void func_80055434(VECTOR3* vec);

s32 func_8005545C(SVECTOR* vec);

s32 func_80055490(SVECTOR* arg0);

void func_800554C4(s32 arg0, s16 arg1, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1, SVECTOR* rot, q19_12 x, q19_12 y, q19_12 z, s_WaterZone* waterZones);

void func_80055648(s32 arg0, SVECTOR* arg1);

s32 func_800557DC(void);

void func_80055814(s32 arg0);

void WorldEnv_FogDistanceSet(q19_12 nearDist, q19_12 farDist);

s32 func_800559A8(s32 arg0);

u8 func_80055A50(s32 arg0);

void func_80055A90(CVECTOR* arg0, CVECTOR* arg1, u8 arg2, s32 arg3);

/** @brief Applies uniform lighting and fog shading to `color`, outputting to `result`.
 * The fog factor is derived from `arg2` via `g_WorldEnvWork.fogRamp_CC` and blends the lit color toward the far/fog color in `g_WorldEnvWork.field_1C/field_1D/field_1E`,
 * with lighting strength from `g_WorldEnvWork.field_20` applied equally on all axes.
 */
void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2);

void func_80055C3C(CVECTOR* result, CVECTOR* color, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

u8 func_80055D78(q19_12 posX, q19_12 posY, q19_12 posZ);

void func_80055E90(CVECTOR* color, u8 fadeAmount);

void func_80055ECC(CVECTOR* color, SVECTOR3* arg1, SVECTOR3* arg2, MATRIX* mat);

u8 func_80055F08(SVECTOR3* arg0, SVECTOR3* arg1, MATRIX* mat);

void LmHeader_FixOffsets(s_LmHeader* lmHdr);

void ModelHeader_FixOffsets(s_ModelHeader* modelHdr, s_LmHeader* lmHdr);

void Lm_TransparentPrimSet(s_LmHeader* lmHdr, bool transparency);

s32 Lm_MaterialCountGet(bool (*filterFunc)(s_Material* mat), s_LmHeader* lmHdr);

/** TODO: Unknown `arg3` type. */
void func_80059D50(s32 arg0, s_ModelInfo* modelInfo, MATRIX* mat, s32 arg3, GsOT_TAG* tag);

void func_80059E34(u32 arg0, s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 arg3, GsOT_TAG* tag);

/** TODO: Unknown `arg2` type. */
void func_8005A21C(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat);

/** @brief Computes a fog-shaded version of `D_800C4190` color using `arg1` as the distance factor?
 *  Stores the result at 0x3D8 into `arg0`.
 */
void func_8005A42C(s_GteScratchData* scratchData, q19_12 alpha);

void func_8005A478(s_GteScratchData* scratchData, q19_12 alpha);

/** `scratchData` is unused? */
void func_8005A838(s_GteScratchData* scratchData, s32 scale);

void func_8005A900(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* mat);

u8 func_8005AA08(s_MeshHeader* meshHdr, s32 arg1, s_GteScratchData2* scratchData);

void func_8005AC50(s_MeshHeader* meshHdr, s_GteScratchData2* scratchData, GsOT_TAG* ot, s32 arg3);

void Texture_Init(s_Texture* tex, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY);

void Texture_RefCountReset(s_Texture* tex);

/** @unused */
void func_8005B378(s_Texture* tex, char* arg1);

void Texture_RefClear(s_Texture* tex);

void Material_TimFileNameGet(char* filename, s_Material* mat);

void func_8005B424(VECTOR3* vec0, VECTOR3* vec1);

/** @unused No references. */
void func_800563E8(s_LmHeader* lmHdr, s32 arg1, s32 arg2, s32 arg3);

void Lm_MaterialFileIdxApply(s_LmHeader* lmHdr, e_FsFile fileIdx, s_FsImageDesc* image, s32 blendMode);

void Lm_MaterialFsImageApply1(s_LmHeader* lmHdr, char* newStr, s_FsImageDesc* image, s32 blendMode);

bool Lm_MaterialFsImageApply(s_LmHeader* lmHdr, char* fileName, s_FsImageDesc* image, s32 blendMode);

void Material_FsImageApply(s_Material* mat, s_FsImageDesc* image, s32 blendMode);

void func_800566B4(s_LmHeader* lmHdr, s_FsImageDesc* images, s8 unused, s32 startIdx, s32 blendMode);

void Lm_MaterialsLoadWithFilter(s_LmHeader* lmHdr, s_ActiveTextures* activeTexs, bool (*filterFunc)(s_Material* mat), e_FsFile fileIdx, s32 blendMode);

/** Checks if LM textures are loaded? */
bool LmHeader_IsTextureLoaded(s_LmHeader* lmHdr);

void Lm_MaterialFlagsApply(s_LmHeader* lmHdr);

void Model_MaterialFlagsApply(s_ModelHeader* modelHdr, s32 arg1, s_Material* mat, s32 matFlags);

void Lm_MaterialRefCountDec(s_LmHeader* lmHdr);

s32 LmHeader_ModelCountGet(s_LmHeader* lmHdr);

void Bone_ModelAssign(s_Bone* bone, s_LmHeader* lmHdr, s32 modelHdrIdx);

bool Lm_ModelFind(s_WorldObjectModel* arg0, s_LmHeader* lmHdr, s_WorldObjectMetadata* metadata);

void StringCopy(char* prevStr, char* newStr);

void func_80056D8C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, GsOT* arg6, s32 arg7);

/** Crucial 3D drawing function. */
void func_80057090(s_ModelInfo* modelInfo, GsOT* otTag, s32 arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5);

s32 func_800571D0(u32 arg0);

void func_80057228(MATRIX* mat, s32 alpha, SVECTOR* arg2, VECTOR3* arg3);

/** TODO: Unknown `arg2` type. */
void func_80057344(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat);

void func_800574D4(s_MeshHeader* meshHdr, s_GteScratchData* scratchData);

void func_8005759C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 vertOffset, s32 normalOffset);

void func_80057658(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4);

void func_80057A3C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec);

void func_80057B7C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* mat);

/** Main quad drawing func? */
void func_8005801C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, GsOT_TAG* tag, s32 arg3);

/** `arg4` unused. */
s_Texture* Texture_Get(s_Material* mat, s_ActiveTextures* activeTexs, void* fsBuf9, e_FsFile fileIdx, s32 arg4);

void func_8005B55C(GsCOORDINATE2* coord);

u32 func_8005C478(s16* arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2);

s32 Chara_NpcIdxGet(s_SubCharacter* chara);

void func_8005C814(s_SubCharacter_D8* arg0, s_SubCharacter* chara);

s32 func_8005C944(s_SubCharacter* chara, s_800C4590* arg1);

s32 func_8005D86C(s32 arg0);

/** Looks like a clamping function. */
s32 func_8005D974(s32 arg0);

s32 func_8005D9B8(VECTOR3* pos, q23_8 vol);

/** Spatial SFX func? */
void func_8005DC1C(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 soundType); // Types assumed.

/** Spatial SFX func? */
void func_8005DC3C(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 soundType, s32 pitch);

/** Spatial SFX func? */
void func_8005DD44(e_SfxId sfxId, VECTOR3* pos, q23_8 vol, s8 pitch); // Types assumed.

/** Checks `field_8` in collision struct. */
bool func_8005F680(s_Collision* coll);

/** Related to camera collision? */
void func_8005F6B0(s_SubCharacter* chara, VECTOR* pos, s32 arg2, s32 arg3);

/** Spatial SFX func? */
void func_8005DE0C(e_SfxId sfxId, VECTOR3* pos, s32 vol, q19_12 falloff, s8 pitch);

void Map_EffectTexturesLoad(s32 mapIdx);

void func_8005E414(s32 orgIdx);

/** @brief Does something with `unkTable1_4C`, clears blood splats and initialize drawn of objects. */
void func_8005E650(s32 mapId);

void func_8005E70C(void);

s32 func_8005E7E0(s32 arg0);

// Crucial for displaying particle effects. (Not general enviroments. Blood, shoot effects)
void func_8005E89C(void);

s32 func_8005F55C(s32 arg0);

void DmsHeader_FixOffsets(s_DmsHeader* dmsHdr);

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* dmsHdr);

/** @unused? `volatile` needed for match. */
s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* dmsHdr);

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, q19_12 time, s_DmsHeader* dmsHdr);

void Dms_CharacterGetStartPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, s32 time, s_DmsHeader* dmsHdr);

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* dmsHdr);

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, s_DmsHeader* dmsHdr);

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha);

/** @unused? Returns `96 * cotangent(angle / 2)`. Possibly camera/FOV related. */
q3_12 func_8008CDBC(q3_12 angle);

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr);

/** @unused Returns whether any axis differs by more than 22.5 degrees (1/16 of full rotation). */
bool func_8008CF54(SVECTOR3* rot0, SVECTOR3* rot1);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, const s_DmsKeyframeCamera* frame0, const s_DmsKeyframeCamera* frame1, s32 alpha);

void func_8008D1D0(s32* prevKeyframe, s32* nextKeyframe, q19_12* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr);

u32 Dms_IntervalStateGet(q19_12 time, s_DmsHeader* dmsHdr);

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry);

s32 Math_LerpFixed12(s16 from, s16 to, q19_12 alpha);

void func_8008D41C(void);

void func_8008D438(void);

void func_8008D448(void);

void func_8008D454(void);

void func_8008D464(void);

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s_WaterZone* waterZones);

void func_8008D5A0(VECTOR3* arg0, s16 arg1);

s32 func_8008D8C0(s16 x0, s32 x1, s32 x2);

void func_8008D990(s32 arg0, s32 arg1, VECTOR3* arg2, s32 arg3, s32 arg4);

/** @brief Gets the water zone at a given position.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @param waterZones Water zones to query.
 * @return Water zone at the given position.
 */
s_WaterZone* Map_WaterZoneGet(q27_4 posX, q27_4 posZ, s_WaterZone* waterZones);

void func_8008E5B4(void);

void func_8008E794(VECTOR3* posXz, q3_12 angle, q19_12 posY);

void func_8008EA68(SVECTOR* arg0, VECTOR3* posXz, q19_12 posY);

/** State step increment for some substate. */
void func_80085D78(bool reset);

/** State step setter for some substate. */
void func_80085DC0(bool arg0, s32 sysStateStep);

/** Calls `SysWork_StateStepIncrement(0)` with some preliminary safety check. */
void func_80085DF0(void);

void SysWork_StateStepIncrementDelayed(q19_12 delay, bool reset);

/** @brief Updates character states during events/cutscenes. */
void func_80085EB8(u32 arg0, s_SubCharacter* chara, s32 arg2, bool reset);

/** @brief Sets `sysStateStep_C` depending on whether `eventFlagIdx` flag is set.
 *
 * @param eventFlagIdx Flag index.
 * @param stepTrue Step to use if flag is set.
 * @param stepFalse Step to use if flag is not set.
 * @param stepSecondary If `true`, sets `sysStateStep_C[1]` instead of `sysStateStep_C[0]`, otherwise sets `sysStateStep_C[0]`.
 */
void func_8008605C(e_EventFlag eventFlagIdx, s32 stepTrue, s32 stepFalse, bool stepSecondary);

/** @brief Displays a selection menu and sets `sysStateStep_C` depending on the chosen value.
 *
 * @param hasSelection `true` if it waits for a selection, `false` if `sysStateStep_C` increments after displaying.
 * @param mapMsgIdx Map message index of the message to display.
 * @param step0 Step to use if selection #0 is chosen.
 * @param step1 Step to use if selection #1 is chosen.
 * @param step2 Step to use if selection #2 is chosen.
 * @param stepSecondary If `true`, sets `sysStateStep_C[1]` instead of `sysStateStep_C[0]`, otherwise sets `sysStateStep_C[0]`.
 */
void MapMsg_DisplayAndHandleSelection(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool stepSecondary);

/** Handles giving the player items. */
void SysWork_StateStepIncrementAfterFade(s32 stateStep, bool cond, s32 fadeType, q19_12 fadeTimestep, bool reset);

/** Handles a busy wait while loading assets? */
void func_800862F8(s32 stateStep, e_FsFile fileIdx, bool reset);

/** Stepped state handler for displaying picked up items? */
void func_80086470(u32 stateStep, e_InventoryItemId itemId, s32 itemCount, bool reset);

void func_800865FC(bool isPos, s32 idx0, s32 idx1, q3_12 angleY, q19_12 offsetOrPosX, q19_12 offsetOrPosZ);

/** State step increment. */
void func_800866D4(s32 arg0, s32 arg1, bool reset);

extern bool (*D_800AFD08[])(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3);

void func_80086728(s_SubCharacter* chara, s32 arg1, s32 arg2, bool reset);

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2);

/** Paper map state handler. Rough name could be `Map_PaperMapBackgroundStateUpdate`. */
void func_800867B4(s32 state, s32 paperMapFileIdx);

void func_800868DC(s32 idx);

/** @brief Displays a map message with a sound.
 *
 * @param mapMsgIdx Index of the message to display.
 * @param soundIdx Index of the sound to play.
 * @param sounds Sound indices.
 */
void Map_MessageWithAudio(s32 mapMsgIdx, u8* soundIdx, u16* soundsIdxs);

/** @brief Sets the camera position target.
 *
 * @param pos Target position (Q19.12).
 * @param offsetOrPosX If `pos` is valid, X offset for `pos`. If `pos` is `NULL`, X target position.
 * @param offsetOrPosY If `pos` is valid, Y offset for `pos`. If `pos` is `NULL`, Y target position.
 * @param offsetOrPosZ If `pos` is valid, Z offset for `pos`. If `pos` is `NULL`, Z target position.
 * @param accelX X acceleration.
 * @param accelY X acceleration.
 * @param speedXMax Max X speed.
 * @param speedYMax Max Y speed.
 * @param warp If `true`, warp to the position target, otherwise transition over time.
 */
void Camera_PositionSet(VECTOR3* pos, q19_12 offsetOrPosX, q19_12 offsetOrPosY, q19_12 offsetOrPosZ,
                        q19_12 accelXz, q19_12 accelY, q19_12 speedXzMax, q19_12 speedYMax, bool warp);

/** @brief Sets the camera rotation and look-at position targets.
 *
 * @param lookAt Target look-at position (Q19.12).
 * @param lookAtOffsetOrPosX If `lookAt` is valid, X offset for `lookAt`. If `lookAt` is `NULL`, X target look-at position.
 * @param lookAtOffsetOrPosY If `lookAt` is valid, X offset for `lookAt`. If `lookAt` is `NULL`, Y target look-at position.
 * @param lookAtOffsetOrPosZ If `lookAt` is valid, Z offset for `lookAt`. If `lookAt` is `NULL`, Z target look-at position.
 * @param angularAccelX TODO
 * @param angularAccelY TODO
 * @param angularSpeedXMax TODO
 * @param angularSpeedYMax TODO
 * @param warp If `true`, warp to the look-at target, otherwise transition over time.
 */
void Camera_LookAtSet(VECTOR3* lookAt, q19_12 lookAtOffsetOrPosX, q19_12 lookAtOffsetOrPosY, q19_12 lookAtOffsetOrPosZ,
                      q19_12 angularAccelX, q19_12 angularAccelY, q19_12 angularSpeedXMax, q19_12 angularSpeedYMax, bool warp);

/** Maybe `Chara_PlayAnim`. State handler. */
void func_80086C58(s_SubCharacter* chara, s32 arg1);

/** State handler. */
void func_80086D04(s_SubCharacter* chara);

/** State handler. */
void func_80086DA8(e_FsFile fileIdx, q19_12 fadeTimestep);

/** State handler. */
void func_80086E50(e_FsFile fileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

/** Odd code?
 * This function appears to circumvent an issue with fading.
 * When the player is about to leave the clock tower screen marking certain
 * times, breaking it causes the clock tower image to dissapear. It then fades in
 * and out to the black screen before returning to gameplay.
 */
void func_80086F44(s32 fadeTimestep0, q19_12 fadeTimestep1);

/** @brief Displays a map message with SFX.
 *
 * @param mapMsgIdx Index of the message to display.
 * @param sfxId ID of the SFX to play.
 * @param sfxPos SFX position.
 */
void Map_MessageWithSfx(s32 mapMsgIdx, e_SfxId sfxId, VECTOR3* sfxPos);

void func_8008716C(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

void MapMsg_DisplayWithTexture(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx);

/** @brief Displays a message with a background texture that is darken after reading the first sentence. */
void MapMsg_DisplayWithTexture1(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1);

void Event_ItemTake(e_InventoryItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx);

void Event_MapTake(s32 mapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

/** Sets sound command. */
void func_80087EA8(s32 cmd);

void func_80087EDC(s32 cmd);

/** Calls a state handler. */
void func_80088028(void);

/** State handler. */
void func_80088048(void);

/** State handler. */
void func_800880F0(s32 arg0);

void Gfx_CursorDraw(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

bool Chara_Load(s32 modelIdx, s8 charaId, GsCOORDINATE2* coords, s8 forceFree, s_LmHeader* lmHdr, s_FsImageDesc* tex);

bool Chara_ProcessLoads(void);

void func_80088D34(s32 idx);

s32 Chara_Spawn(e_CharacterId charaId, s32 arg1, q19_12 posX, q19_12 posZ, q3_12 rotY, u32 stateStep);

void func_80088F94(s_SubCharacter* chara, s32 unused1, s32 unused2);

void func_80088FF4(e_CharacterId charaId, s32 spawnIdx, s32 spawnFlags);

bool func_8008F434(s32 arg0);

/** Might retrun `bool`. */
void func_80089090(s32 arg0);

void func_800890B8(void);

s32 func_80089128(void);

void func_800892A4(s32 idx);

void func_800892DC(s32 idx, u8 arg1);

void func_80089314(s32 arg0);

void func_800893D0(q19_12 arg0);

void func_8008944C(void);

void func_80089470(void);

void func_80089494(void);

void func_800894B8(s32 arg0);

void func_800894DC(void);

void func_80089500(void);

/** Handles initial gamepad init. */
bool func_80089524(s_SysWork_2514* arg0, s32 padInfoMode);

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2);

bool func_80089644(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s32 arg2, u32 arg3);

bool func_80089A30(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3);

bool func_80089BB8(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3);

bool func_80089DF0(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3);

bool func_8008973C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3);

void func_80089840(s_SysWork_2514* arg0);

void func_8008989C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32));

void func_8008992C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32));

void func_800899BC(s_SysWork_2514* arg0, s32 arg1);

bool func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3);

u32 func_8008A058(s32 arg0);

s32 func_8008A0CC(void); /** Returns 0. */

s64 func_8008A0D4(void); /** Returns 0. */

s32 func_8008A0E4(s32 arg0, s32 weaponAttack, s_SubCharacter* chara, VECTOR3* pos, s_SubCharacter* chara2, q3_12 angle0, q3_12 angle1);

u32 func_8008A270(s32 idx);

s32 func_8008A35C(s_800AD4C8* arg0, s32 arg1);

void Chara_Flag8Clear(s_SubCharacter* chara);

void Chara_Flag8Set(s_SubCharacter* chara);

/** Large function. Runs if `CharaFlag_Unk8` is set. */
void func_8008A3AC(s_SubCharacter* chara);

s32 func_8008A3E0(s_SubCharacter* chara);

void func_8008B15C(s_SubCharacter* chara);

void func_8008B1DC(s_SubCharacter* chara, q19_12 angle0, q19_12 angle1);

void func_8008B398(void);

void func_8008B3E4(q23_8 vol);

void func_8008B40C(q23_8 vol, s32 soundType);

/** `arg0` is boolean. */
void func_8008B438(s32 arg0, q23_8 vol, s32 soundType);

bool func_8008B474(s32 arg0, q23_8 vol, s32 soundType);

void func_8008B664(VECTOR3* pos, u32 caseVar);

/** Main attack handling function. */
s32 func_8008B714(s_SubCharacter* attacker, s_SubCharacter* target, VECTOR3* arg2, s32 arg3);

s32 func_8008BF84(s_SubCharacter* chara, q19_12 angle, s_800AD4C8* arg2, s32 arg3);

s32 func_8008D850(void);

void func_8008E4EC(s_LmHeader* lmHdr);

void func_8008D78C(void);

void func_80091380(void);

// TODO: Arrange these in address order for better insight into the original interface. -- Sezz
// ------------------------------------------------------------------

/** Seeks for the English title screen background graphic. */
void GameFs_TitleGfxSeek(void);

/** Loads the English title screen background graphic. */
void GameFs_TitleGfxLoad(void);

/** Seeks for the stream overlay. */
void GameFs_StreamBinSeek(void);

/** Loads the stream overlay. */
void GameFs_StreamBinLoad(void);

/** Loads the options background graphic and overlay. */
void GameFs_OptionBinLoad(void);

/** Loads the save/load background graphic and overlay. */
void GameFs_SaveLoadBinLoad(void);

/** Loads `Tim00` graphic. */
void GameFs_Tim00TIMLoad(void);

void GameFs_MapItemsModelLoad(u32 mapId);

void Textures_ActiveTex_CountReset(s_ActiveTextures* activeTexs);

void Textures_ActiveTex_PutTextures(s_ActiveTextures* activeTexs, s_Texture* texs, s32 texIdx);

s_Texture* Textures_ActiveTex_FindTexture(char* texName, s_ActiveTextures* activeTexs);

/** @brief Sets the debug string position.
 *
 * @param unused @unused
 * @param posX X screen position.
 * @param posY Y screen position.
 */
void Gfx_DebugStringPositionSet(s16 unused, s16 posX, s16 posY);

/** Angle func. */
q3_12 func_8005BF38(q3_12 angle);

bool func_8005BF58(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

s32 func_8005C1CC(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

s32 func_8005C7B0(s32 arg0);

/** `arg0` type assumed. */
void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3);

bool func_80062708(POLY_FT4** poly, s32 idx);

bool func_80063A50(POLY_FT4** poly, s32 idx);

// Important for drawing gun smoke effect.
bool func_80064334(POLY_FT4** poly, s32 idx);

/** Displays gun shooting effects. */
void func_8006342C(s32 weaponAttack, q3_12 angle0, s16 angle1, GsCOORDINATE2* coord);

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, q3_12 offsetX, q3_12 offsetZ);

/** Computes something for a targeted NPC. */
bool func_8005D50C(s32* targetNpcIdx, q3_12* outAngle0, q3_12* outAngle1, VECTOR3* unkOffset, u32 npcIdx, q19_12 angleConstraint);

bool func_80060044(POLY_FT4** poly, s32 idx);

bool func_800611C0(POLY_FT4** poly, s32 idx);

void func_800622B8(s32 unused, s_SubCharacter* chara, s32 animStatus, s32 arg3);

void func_80064F04(VECTOR3* arg0, s8 arg1, s16 arg2);

bool func_80064FC0(POLY_FT4** polys, s32 idx);

void func_800652F4(VECTOR3* arg0, s16 arg1, s16 arg2, s16 arg3);

void func_80065B94(VECTOR3* arg0, s16 arg1);

void func_80066184(void);

void func_80066D90(void);

void func_80066E40(void);

void func_80066E7C(void);

s32 func_80067914(s32 paperMapIdx, u16 arg1, u16 arg2, u16 arg3);

bool func_80068CC0(s32 arg0);

/** Paper map func. Seems to draw map marking sprites. */
bool func_80068E0C(s32 arg0, s32 idx, s32 arg2, s32 shade, u16 arg4, u16 arg5, u16 arg6);

void func_800692A4(u16 arg0, u16 arg1, u16 arg2);

void func_800697EC(void);

/** Flags getter. */
u16 func_80069810(void);

/** Flags sette. */
void func_80069820(u16 flags);

/** Flags setter. */
void func_8006982C(u16 flags);

void func_80069844(s32 arg0);

void func_80069860(s32 arg0, s32 arg1, s_func_8006F8FC* arg2);

void IpdCollData_FixOffsets(s_IpdCollisionData* collData);

void func_80069994(s_IpdCollisionData* collData);

void func_800699E4(s_IpdCollisionData* collData);

/** @brief Gets the point collision at a given 2D world position.
 *
 * @param coll Output point collision.
 * @param posX X world position.
 * @param posZ Z world position.
 */
void Collision_Get(s_Collision* coll, q19_12 posX, q19_12 posZ);

s32 func_80069B24(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara);

s32 func_80069BA8(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara, s32 arg4);

void func_80069DF0(s_800C4590* arg0, VECTOR3* pos, s32 arg2, s32 arg3);

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara);

void func_8006A178(s_800C4590* arg0, q19_12 posX, q19_12 posY, q19_12 posZ, q19_12 heightY);

s_SubCharacter** func_8006A1A4(s32* charaCount, s_SubCharacter* chara, bool arg2);

s32 func_8006A3B4(s32 arg0, VECTOR* offset, s_func_8006AB50* arg2);

s32 func_8006A42C(s32 arg0, VECTOR3* offset, s_func_8006AB50* arg2);

s32 func_8006A4A8(s_800C4590* arg0, VECTOR3* offset, s_func_8006AB50* arg2, s32 arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount);

void func_8006A940(VECTOR3* offset, s_func_8006AB50* arg1, s_SubCharacter** charas, s32 charaCount);

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* pos, s_func_8006AB50* arg2, s32 arg3);

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* pos, s_func_8006AB50* arg2);

void func_8006AD44(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

bool func_8006AEAC(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

bool func_8006B004(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

void func_8006B1C8(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2);

bool func_8006B318(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx);

/** `arg1` is unused, but `func_8006B1C8` passes second arg to this. */
void func_8006B6E8(s_func_8006CC44* arg0, s_IpdCollisionData_20* arg1);

bool func_8006B7E0(s_func_8006CC44_A8* arg0, s_func_8006CC44_CC_20* arg1);

void func_8006B8F8(s_func_8006CC44_CC* arg0);

void func_8006B9C8(s_func_8006CC44* arg0);

void func_8006BB50(s_func_8006CC44* arg0, s32 arg1);

s32 func_8006BC34(s_func_8006CC44* arg0);

/** `arg3` and `arg4` might be XY or XZ position components. */
void func_8006BCC4(s_func_8006CC44_44* arg0, s8* arg1, u32 arg2, q3_12 deltaX, q3_12 deltaZ, s16 arg5);

void func_8006BDDC(s_func_8006CC44_44_0* arg0, q3_12 rotX, q3_12 rotY);

void func_8006BE40(s_func_8006CC44* arg0);

void func_8006BF88(s_func_8006CC44* arg0, SVECTOR3* arg1);

void func_8006C0C8(s_func_8006CC44*, s16, s16);

bool func_8006C1B8(u32 arg0, s16 arg1, s_func_8006CC44* arg2);

s16 func_8006C248(s32 arg0, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4);

bool func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx);

void func_8006C45C(s_func_8006CC44* arg0);

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 dist);

void func_8006C838(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

void func_8006CA18(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006CA18* arg2);

s16 func_8006CB90(s_func_8006CC44* arg0);

s32 func_8006CC44(q23_8 x, q23_8 z, s_func_8006CC44* arg2);

void func_8006CC9C(s_func_8006CC44* arg0);

void func_8006CF18(s_func_8006CC44* arg0, s_func_8006CF18* arg1, s32 idx);

void func_8006D01C(VECTOR3* arg0, VECTOR3* arg1, s16 arg2, s_func_8006CC44* arg3);

void func_8006D2B4(VECTOR3* arg0, s_func_8006CC44_44* arg1);

void func_8006D600(VECTOR3* pos, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8006D774(s_func_8006CC44* arg0, VECTOR3* arg1, VECTOR3* arg2);

/** `arg1` is likely Q23.8. */
void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2);

bool Ray_LineCheck(s_RayData* ray, VECTOR3* from, VECTOR3* to);

/** Ray function. */
bool func_8006DA08(s_RayData* ray, VECTOR3* from, VECTOR3* dir, s_SubCharacter* chara);

void Ray_MissSet(s_RayData* ray, VECTOR3* from, VECTOR3* dir, q23_8 arg3);

/** LOS function. */
bool func_8006DB3C(s_RayData* ray, VECTOR3* from, VECTOR3* dir, s_SubCharacter* chara);

bool func_8006DC18(s_RayData* ray, VECTOR3* vec1, VECTOR3* vec2);

bool Ray_TraceSetup(s_RayState* state, s32 arg1, s16 arg2, VECTOR3* pos, VECTOR3* dir, s32 arg5, s32 arg6, s_SubCharacter** charas, s32 charaCount);

bool Ray_TraceRun(s_RayData* ray, s_RayState* arg1);

void func_8006E0AC(s_RayState* state, s_IpdCollisionData* ipdColl);

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2);

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ);

void func_8006E53C(s_RayState* state, s_IpdCollisionData_20* arg1, s_IpdCollisionData* arg2);

void func_8006E78C(s_RayState* state, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4);

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1);

void func_8006EE0C(s_RayState_6C* arg0, s32 arg1, s_SubCharacter* chara);

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara);

void func_8006F250(s32* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

void func_8006F338(s_func_8006F338* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

bool func_8006F3C4(s_func_8006F338* arg0, s_func_8006F8FC* arg1);

/** Translates something. */
s32 func_8006F620(VECTOR3* pos, s_func_8006AB50* arg1, s32 arg2, s32 arg3);

void func_8006F8FC(q19_12* outX, q19_12* outZ, q19_12 posX, q19_12 posZ, const s_func_8006F8FC* arg4);

q19_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle);

/** Angle getter. Something to do with the direction from a character to a target position, probably for NPC AI.
 * Unsure if `spanAngle` is an angle.
 */
q19_12 Chara_HeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 targetPosX, q19_12 targetPosZ, q3_12 spanAngle, bool cond);

bool func_8006FD90(s_SubCharacter* chara, s32 count, q19_12 baseDistMax, q19_12 distStep);

bool func_80070030(s_SubCharacter* chara, q19_12 posX, q19_12 posY, q19_12 posZ);

/** Checks for character ray miss? */
bool func_80070084(s_SubCharacter* chara, q19_12 posX, q19_12 posY, q19_12 posZ);

bool func_800700F8(s_SubCharacter* npc, s_SubCharacter* player);

bool func_80070184(s_SubCharacter* chara, s32 arg1, q3_12 rotY);

bool func_80070320(void);

/** TODO: Return type uncertain. */
q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2);

/** @brief Sets a character's interpolated animation pose for the current tick.
 * TODO: Not really the pose, but frame-derived data. Need to deobfuscate more of
 * the structs to name an ddocument this properly.
 *
 * @param chara Character to update.
 * @param keyframe0 First keyframe.
 * @param keyframe1 Second keyframe.
 */
void func_80070400(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1);

bool func_80070208(s_SubCharacter* chara, q19_12 dist);

s32 func_8007029C(s_SubCharacter* chara, q19_12 dist, q3_12 rotY);

void func_800705E4(GsCOORDINATE2* coord, s32 idx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ);

void Player_FlexRotationYReset(void);

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2);

void Settings_ScreenAndVolUpdate(void);

void Settings_RestoreDefaults(void);

void Settings_RestoreControlDefaults(s32 arg0);

void nullsub_800334C8(void);

bool func_80033548(void);

/** @brief Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SavegameUpdatePlayer(void);

/** @brief Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SavegameReadPlayer(void);

/** @brief Handles a warm game reboot. */
void Game_WarmBoot(void);

/** Handles `g_GameWork.gameStateStep_598[0]`.
 * Used to handle map loading and room changes.
 */
void GameFs_MapStartup(void);

/** @brief Draws the motion-blurred loading screen of Harry running away from the camera. */
void Gfx_LoadingScreenDraw(void);

/** @brief Clears all NPC fields for reuse. */
void Game_NpcClear(void);

void Game_NpcInit(void);

/** Crucial for getting in-game.
 * Removing it breaks the camera, inventory's 3D elements, effects
 * (lighting, fog, lens flare, etc.), NPCs don't spawn, and
 * doing any action unrelated to aiming a weapon or interacting
 * with the environment crashes the game.
 */
void Game_InGameInit(void);

void Game_SavegameInitialize(s8 overlayId, s32 difficulty);

/** @brief Initializes the player character model. */
void Game_PlayerInit(void);

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

/** @brief Checks if the pointers of `g_CharaTypeAnimInfo` overlap each other.
 * Returns `false` if the compared pointers don't overlap.
 */
bool Fs_CharaAnimDataSizeCheck(s32 idx0, s32 idx1);

/** @brief Finds for the index of the character animation data in `g_CharaTypeAnimInfo`.
 *
 * @param charaId ID of the character for which to find the animation data.
 * @return Animation data index.
 */
s32 Fs_CharaAnimDataInfoIdxGet(e_CharacterId charaId);

/** Allocates and adjust where is animation data allocated. */
void Fs_CharaAnimDataAlloc(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coords);

/** Called by `Fs_QueuePostLoadAnm`. Assigns information about animation data to `g_CharaTypeAnimInfo`
 * and initializes NPC bones.
 */
void Fs_CharaAnimInfoUpdate(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord);

/** @brief Updates character type bone initialization coordinates and reinitializes them. */
void Fs_CharaAnimBoneInfoUpdate(void);

/** @brief Updates the translation and rotation of a matrix in a coordinate.
 *
 * @param pos Translation to apply.
 * @param rot Rotation to apply.
 * @param coord Coordinate to update.
 */
void Math_MatrixTransform(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord);

/** @brief Sets general environmental effects such as lighting, fog, and screen effects.
 *
 * @note Specific effect for enviroments like snow, rain, and the ending's fire rain
 * are set by code only found in map overlays.
 */
void Gfx_MapEffectsSet(s32 unused);

void func_80035B98(void);

/** @unused and broken.
 * Intended to draw a background image when a loading screen with the string "STAGE X-X" appears.
 */
void Gfx_LoadingScreen_BackgroundTexture(void);

void Gfx_LoadingScreen_PlayerRun(void);

void Savegame_MapRoomIdxUpdate(void);

/** @Unused */
s32 func_8003647C(void);

/** @Unused */
s32 func_80036498(void);

/** @Unused */
u32 func_800364BC(void);

// Draws a pallete of colors in the frame buffer.
void func_8003652C(void);

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx);

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1);

/** @Unused */
void func_80036E48(u16* arg0, s16* arg1);

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124(void);

void func_80037154(void);

/** Radio sound related. */
void Game_RadioSoundStop(void);

/** Finds the ground hight and warps the player to it? */
void Game_PlayerHeightUpdate(void);

bool Event_CollideFacingCheck(s_MapPoint2d* mapPoint);

bool Event_CollideObbFacingCheck(s_MapPoint2d* mapPoint);

bool Event_CollideObbCheck(s_MapPoint2d* mapPoint);

void Savegame_EnemyStateUpdate(s_SubCharacter* chara);

void Event_Update(bool disableButtonEvents);

/** @brief Updates character's damage flag to reflect if damage was taken.
 *
 * @param chara Character to update.
 */
void Chara_DamagedFlagUpdate(s_SubCharacter* chara);

void func_80037E78(s_SubCharacter* chara);

s32 func_800382B0(s32 arg0);

/** @brief Computes the distance between two positions.
 *
 * @param from First position (Q19.12).
 * @param to Second position (Q19.12).
 * @return Distance between positions.
 */
q19_12 Math_DistanceGet(const VECTOR3* from, const VECTOR3* to);

/** @brief Computes the 2D distance on the XZ plane between two positions.
 *
 * @param from First position (Q19.12).
 * @param to Second position (Q19.12).
 * @return 2D distance between positions.
 */
q19_12 Math_Distance2dGet(const VECTOR3* from, const VECTOR3* to);

void func_800803FC(VECTOR3* pos, s32 idx);

/** @brief Forces a clicked controller input status for `ControllerFlag_Select`. */
void Input_SelectClickSet(void);

/** @brief Performs a 2D distance check on the XZ plane between two positions.
 *
 * @param from First position (Q19.12).
 * @param to Second position (Q19.12).
 * @param radius Intersection radius.
 * @return `true` if the 2D distance exceeds the radius, `false` otherwise.
 */
bool Math_Distance2dCheck(const VECTOR3* from, const VECTOR3* to, q19_12 radius);

/** @brief Computes the squared 2D distance on the XZ plane from the reference position to the camera.
 *
 * @param pos Reference position (Q19.12).
 * @return 2D distance to the camera. TODO: Does it stay in Q25.6?
 */
s32 Camera_Distance2dGet(const VECTOR3* pos);

/** Responsible for loading NPCs on the map. */
void Game_NpcRoomInitSpawn(bool cond);

/** @brief Main NPC update function. Runs through each NPC and calls `g_MapOverlayHeader.charaUpdateFuncs_194` for them. */
void Game_NpcUpdate(void);

void SysState_Gameplay_Update(void);

void SysState_GamePaused_Update(void);

void SysState_OptionsMenu_Update(void);

void func_8003943C(void);

void SysState_StatusMenu_Update(void);

void GameState_LoadStatusScreen_Update(void);

void SysState_MapScreen_Update(void);

void SysState_Fmv_Update(void);

void SysState_LoadArea_Update(void);

void AreaLoad_UpdatePlayerPosition(void);

/** @brief Plays door sound when transitioning areas.
 * Reduntant code. `SysState_LoadArea_Update` also performs this same code
 * in the exact way this function is doing it.
 */
void AreaLoad_TransitionSound(void);

s8 func_80039F90(void);

void SysState_ReadMessage_Update(void);

void func_8003A16C(void);

void SysState_SaveMenu_Update(void);

void SysState_EventCallFunc_Update(void);

void SysState_EventSetFlag_Update(void);

void SysState_EventPlaySound_Update(void);

void SysState_GameOver_Update(void);

// ====================
// Main menu functions - TODO: Maybe a split around here?
// ====================

void MainMenu_SelectedOptionIdxReset(void);

void Gfx_MainMenu_MainTextDraw(void);

void Gfx_MainMenu_DifficultyTextDraw(s32 idx);

void Gfx_MainMenu_BackgroundDraw(void);

void func_8003B7BC(void);

u32 func_8003B7FC(s32 idx);

PACKET* Gfx_MainMenu_FogPacketGet(GsOT* ot, PACKET* packet);

void Gfx_MainMenu_FogDraw(void);

void Gfx_MainMenu_FogRandomize(void);

void Gfx_MainMenu_FogScatter(void);

void Gfx_MainMenu_FogUpdate(void);

/** Related to main menu fog. */
void func_8003BCF4(void);

/** Related to main menu fog. */
void func_8003BE28(void);

// ====================

/** @brief Gets the bones of a registered character model.
 *
 * @param charaId ID of the character for which to get the skeleton bones (`e_CharacterId`).
 * @return Character model bones or `NULL` if the character model is unregistered.
 */
s_LinkedBone* WorldGfx_CharaModelBonesGet(e_CharacterId charaId);

void GameFs_BgEtcGfxLoad(void);

void GameFs_BgItemLoad(void);

void func_8003BED0(void);

/** @brief Gets the speed zone type at a given position.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @return Speed zone type at the given position (`e_SpeedZoneType`).
 */
s32 Map_SpeedZoneTypeGet(q19_12 posX, q19_12 posZ);

/** Used in map loading. Something related to screen.
 * Removing it causes the game to get stuck at the loading screen.
 */
void WorldGfx_MapInit(void);

/** Something related to player model loading. */
void Item_HeldItemModelFree(void);

/** Allocates player model? */
void CharaModel_AllModelsFree(void);

void CharaModel_Free(s_CharaModel* model);

/** @unused */
void Ipd_ActiveMapChunksClear0(void);

void Map_WorldClear(void);

void WorldGfx_IpdSamplePointStore(void);

void WorldGfx_IpdSamplePointReset(void);

/** Sets draw distance, and loads map models.
 * Breaking the function doesn't causes the game to crash, but instead
 * the world won't draw beyond what has been previously loaded. Some
 * circumstances can also cause the player to be unable to move.
 */
void Ipd_CloseRangeChunksInit(void);

/** @brief Clears the array containing world objects to draw by resetting its size variable.
 *
 * @param worldGfx World GFX workspace.
 */
void Gfx_WorldObjectsClear(s_WorldGfxWork* worldGfxWork);

/** @brief Draws all world objects submitted for the current tick.
 *
 * @param worldGfxWork World GFX workspace.
 */
void Gfx_WorldObjectsDraw(s_WorldGfxWork* worldGfxWork);

/** @brief Draws a world object.
 *
 * @param obj World object.
 */
void Gfx_WorldObjectDraw(s_WorldObject* obj);

void func_8003CC7C(s_WorldObjectModel* arg0, MATRIX* arg1, MATRIX* arg2);

/** @brief Advanced a character model LM buffer.
 *
 * @param buf Buffer to advance.
 * @param charaID  ID of the character whose model to use (`e_CharacterId`).
 */
void WorldGfx_CharaLmBufferAdvance(u8** buf, e_CharacterId charaId);

/** UV setup for character textures. */
void Chara_FsImageCalc(s_FsImageDesc* image, s32 groupIds, s32 modelIdx);

/** @brief Loads a character model, setting the LM header and texture UVs as a prerequisite.
 *
 * @param charaId ID of the character whose model to load (`e_CharacterId`).
 * @param modelIdx Slot index of the model array to load into.
 * @param lmHdr LM header.
 * @param tex Model texture.
 * @return Model or texture queue index.
 */
void WorldGfx_CharaLoad(e_CharacterId charaId, s32 modeIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

/** @brief Loads a character model.
 *
 * @param charaId ID of the character whose model to load (`e_CharacterId`).
 * @param modelIdx Slot index of the model array to load into.
 * @param lmHdr LM header.
 * @param tex Model texture.
 * @return Model or texture queue index.
 */
s32 WorldGfx_CharaModelLoad(e_CharacterId charaId, s32 modelIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

/** Something related to animations. */
void WorldGfx_PlayerModelProcessLoad(void);

void WorldGfx_CharaModelProcessAllLoads(void);

void WorldGfx_CharaModelProcessLoad(s_CharaModel* model);

void func_8003DA9C(e_CharacterId charaId, GsCOORDINATE2* coord, s32 arg2, q3_12 timer, s32 arg4);

/** Something for Harry. `arg` is a packed value. */
void func_8003DE60(s_Skeleton* skel, s32 arg1);

/** Something for Cybil. */
void func_8003DF84(s_Skeleton* skel, s32 arg1);

/** Something for Monster Cybil. */
void func_8003E08C(s_Skeleton* skel, s32 arg1);

/** Something for Dahlia. */
void func_8003E194(s_Skeleton* skel, s32 arg1);

/** Something for Kaufmann. */
void func_8003E238(s_Skeleton* skel, s32 arg1);

/** Something for Stalker. */
void func_8003E388(s_Skeleton* skel, s32 arg1);

/** Something for Split Head. */
void func_8003E414(s_Skeleton* skel, s32 arg1);

/** Something for Puppet Nurse. */
void func_8003E4A0(s_Skeleton* skel, s32 arg1);

/** Something for Puppet Doctor. */
void func_8003E544(s_Skeleton* skel, s32 arg1);

void Options_BrightnessMenu_LinesDraw(s32 arg0);

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad(void);

void Game_SpotlightLoadScreenAttribsFix(void);

/** @brief Determines what enviroment effects data from `g_MapEffectsPresets` will use
 * based on `s_MapOverlayHeader::field_16`.
 */
void Gfx_MapEffectsAssign(s_MapOverlayHeader* mapHdr);

/** @brief Adjust light point attributes to make it simile a flashlight. */
void Game_FlashlightAttributesFix(void);

void func_8003ECBC(void);

void func_8003ECE4(void);

void func_8003EDA8(void);

void func_8003EDB8(CVECTOR* color0, CVECTOR* color1);

/** @unused */
void func_8003EE30(s32 arg0, s32* arg1, s32 arg2, s32 arg3);

void Gfx_LoadScreenMapEffectsUpdate(s32 arg0, s32 arg1);

void Gfx_MapEffectsStepUpdate(s_MapEffectsInfo* preset0, s_MapEffectsInfo* preset1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5);

void Gfx_FogParametersSet(s_StructUnk3* arg0, s_MapEffectsInfo* preset);

void Gfx_FlashlightUpdate(void);

/** Resets player info such as the inventory, health, and playtime in the savegame buffer. */
void Game_SavegameResetPlayer(void);

void Game_PlayerInfoInit(void);

void func_8007E860(void);

void func_8007E8C0(void);

/** Loads player animations for a given map. Maybe for cutscenes?
 *
 * @param mapIdx Map index.
 */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_80070B84(s_SubCharacter* chara, q19_12 moveDistMax, q19_12 arg2, s32 keyframeIdx);

void func_80070DF0(s_PlayerExtra* extra, s_SubCharacter* chara, s32 weaponAttack, s32 animStatus);

// Variable anim duration func for player. It's nearly completely matched https://decomp.me/scratch/PBvwU.
s32 func_800706E4(s_Model* model);

/** Special player SFX handler for heavy breath and damage. */
bool func_80071620(u32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, e_SfxId sfxId);

void func_8007C0D8(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);

void func_8007D090(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);

void Player_CombatUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);

/** Player func. */
void func_8007E9C4(void);

/** Sound func. */
void func_8007F14C(u8 weaponAttack);

/** Resets several global variables to 0. */
void func_8007F1CC(void);

void Player_DisableDamage(u8* ptr, u8 disableDamage);

/** Some kind of player anim state check. */
bool Player_IsAttacking(void);

/** Some kind of player anim state check. */
bool Player_IsBusy(void);

/** Gets something from the player's current animation? */
s16 Player_AnimGetSomething(void);

/** @brief Computes the shortest angle between `angleFrom` and `angleTo`, outputting the result to `shortestAngle`.
 *
 * @param angleFrom First angle in Q3.12, range `[0, 4096]`.
 * @param angleTo Second angle in Q3.12, range `[0, 4096]`.
 * @param shortestAngle Shortest angle output in Q3.12, range `[0, 4096]`.
 */
void Math_ShortestAngleGet(q3_12 angleFrom, q3_12 angleTo, q3_12* shortestAngle);

/** Anim func.
 *
 * @param chara Player character.
 * @param extra Extra player character parameters.
 * @param animStatus Packed anim status.
 */
void func_8007FB94(s_SubCharacter* chara, s_PlayerExtra* extra, s32 animStatus);

/** Anim func.
 *
 * @param chara Player character.
 * @param extra Extra player character parameters.
 * @param animStatus Packed anim status.
 */
void func_8007FC48(s_SubCharacter* chara, s_PlayerExtra* extra, s32 animStatus);

/** Gets property 8 from player. */
s32 func_8007FD2C(void);

/** @unused Gets current value from the power timer for gas based weapons.
 *
 * @return Power timer.
 */
q19_12 Game_GasWeaponPowerTimerValue(void);

void func_8007FD4C(bool cond);

/** Returns footstep sound effect ID and random pitches? `arg0` usually comes from `s_Collision` */
void func_8007FDE0(s8 arg0, e_SfxId* sfxId, s8* pitch0, s8* pitch1);

/** Presumably, returns a heading angle from `from` to `to`. If so, rename to `Math_AngleBetweenPositionsGet`. */
q19_12 func_80080478(const VECTOR3* from, const VECTOR3* to);

/** @brief Generates a random Q12 fixed-point number in the range `[0.0f, 1.0f)`. Used for angles and multipliers.
 *
 * @return Random Q12 fixed-point number.
 */
q19_12 Rng_RandQ12(void);

s32 func_80080540(s32 arg0, s32 arg1, s32 arg2);

/** Computes (abs(value) - subtractor) * copysign(value). */
s32 Math_PreservedSignSubtract(s32 val, s32 subtractor);

void func_800805BC(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* rootCoord, s32 arg3);

bool func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // arg3 type assumed.

/** Probably returns `bool`. */
bool func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** Fills `g_CollisionPoint` with collision data at a given 2D position.
 *
 * @param posX X position.
 * @param posZ Z position.
 */
void Collision_Fill(q19_12 posX, q19_12 posZ);

/** @brief Gets the ground height at a given 2D position.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @return Ground height.
 */
q19_12 Collision_GroundHeightGet(q19_12 posX, q19_12 posZ);

/** Getter for collision circle point count? */
s32 func_800808AC(q19_12 posX, q19_12 posZ);

/** Returns a Q shift based on a magnitude. */
s32 Math_MagnitudeShiftGet(s32 mag);

u32 func_8008A2E0(s32 arg0);

void Anim_CharaTypeAnimInfoClear(void);

void GameState_Boot_Update(void);
void GameState_MovieIntroFadeIn_Update(void);
void GameState_AutoLoadSavegame_Update(void);
void GameState_MovieIntroAlternate_Update(void);
void GameState_MovieIntro_Update(void);
void GameState_MainMenu_Update(void);
void GameState_MovieOpening_Update(void);
void GameState_LoadScreen_Update(void);
void GameState_InGame_Update(void);
void GameState_MapEvent_Update(void);
void GameState_ExitMovie_Update(void);
void GameState_ItemScreens_Update(void);
void GameState_MapScreen_Update(void);
void GameState_LoadSavegameScreen_Update(void);
void GameState_DebugMoviePlayer_Update(void);
void GameState_Options_Update(void);
void GameState_LoadMapScreen_Update(void);
void GameState_Unk15_Update(void);

/** @brief Toggles the player's flashlight on. */
void Game_TurnFlashlightOn(void);

/** @brief Toggles the player's flashlight off. */
void Game_TurnFlashlightOff(void);

/** @brief Toggles the player's flashlight. */
void Game_FlashlightToggle(void);

/** @brief Checks if the player's flashlight is on.
 *
 * @return `true` if the flashlight is on, `false` otherwise.
 */
bool Game_FlashlightIsOn(void);

/** Handles character spawn? */
void func_80089034(e_CharacterId charaId, s32 spawnIdx, q19_12 posX, q19_12 posZ);

/* Does the map zoom in, red lines? Argument types guessed based on f`unc_800E83C0` in MAP2_S00. */
void Map_BoxOutlineDraw(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8);

#endif
