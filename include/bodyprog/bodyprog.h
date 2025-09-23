#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"
#include "types.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` that has not been identified to
 * be related a to currently recognized and separated section of
 * the engine (like player logic, save game or item screens).
 */

// ==========
// CONSTANTS
// ==========

#define OPT_SOUND_VOLUME_MIN   0
#define OPT_SOUND_VOLUME_MAX   128
#define OPT_VIBRATION_DISABLED 0
#define OPT_VIBRATION_ENABLED  128

#define IPD_HEADER_MAGIC 20
#define LM_HEADER_MAGIC  '0'
#define LM_VERSION       6

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

typedef enum _CollisionType
{
    CollisionType_None = 0,
    CollisionType_Wall = 1,
    CollisionType_Unk2 = 2
} e_CollisionType;

typedef enum _MapTypeFlags
{
    MapTypeFlag_FourActiveChunks = 0,      /** Used by exterior maps. */
    MapTypeFlag_OneActiveChunk   = 1 << 0,
    MapTypeFlag_TwoActiveChunks  = 1 << 1,
    MapTypeFlag_Interior         = 1 << 2,
    MapTypeFlag_Unk3             = 1 << 3  /** @unused Unused map type `XXX` has this flag. */
} e_MapTypeFlags;

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

typedef enum _Sfx
{
    Sfx_Base        = 1280,
				    
    Sfx_StartGame   = Sfx_Base + 1,  // `SND/FIRST.VAB`
				    
    Sfx_Denied      = Sfx_Base + 24, // `1ST/BASE.VAB` onward, but loaded out of order?
    Sfx_Back        = Sfx_Base + 25,
    Sfx_Cancel      = Sfx_Base + 26,
    Sfx_Confirm     = Sfx_Base + 27, // TODO: Continue this pattern.
				    
    Sfx_Unk1309     = 1309,
    Sfx_Unk1310     = 1310,
				    
    Sfx_Stumble0    = 1314,

    Sfx_Unk1317     = 1317,
    Sfx_Unk1318     = 1318,
    Sfx_Unk1319     = 1319,
    Sfx_HeavyBreath = 1320,
    Sfx_Unk1321     = 1321,
    Sfx_Unk1322     = 1322,
    Sfx_Unk1323     = 1323,
    Sfx_Unk1324     = 1324,
				    
    Sfx_Stumble1    = 1333,
				    
    Sfx_Unk1336     = 1336,
    Sfx_Unk1337     = 1337,
    Sfx_Unk1338     = 1338,
    Sfx_Unk1339     = 1339,
    Sfx_Unk1340     = 1340,
    Sfx_Unk1341     = 1341,
				    
    Sfx_Unk1351     = 1351,
    Sfx_Unk1352     = 1352,
				    
    Sfx_Unk1354     = 1354,
				    
    Sfx_Unk1357     = 1357,
    Sfx_Unk1358     = 1358,
    Sfx_Unk1359     = 1359,
    Sfx_Unk1360     = 1360,
    Sfx_Unk1361     = 1361,
				    
    Sfx_Unk1373     = 1373,
    Sfx_Unk1374     = 1374,
    Sfx_Unk1375     = 1375,
				    
    Sfx_Unk1387     = 1387,
				    
    Sfx_Unk1391     = 1391,
				    
    Sfx_Unk1396     = 1396,
    Sfx_Unk1397     = 1397,
    Sfx_Unk1398     = 1398,
    Sfx_Unk1399     = 1399,
				    
    Sfx_Unk1418     = 1418,
				    
    Sfx_Unk1431     = 1431,
    Sfx_Unk1432     = 1432,
				    
    Sfx_Unk1458     = 1458,
    Sfx_Unk1459     = 1459,
				    
    Sfx_Unk1487     = 1487,
				    
    Sfx_Unk1490     = 1490,
    Sfx_Unk1491     = 1491,
				    
    Sfx_Unk1501     = 1501,
    Sfx_Unk1502     = 1502,
				    
    Sfx_Unk1504     = 1504,
    Sfx_Unk1505     = 1505,
				    
    Sfx_Unk1521     = 1521,
				    
    Sfx_Unk1525     = 1525,
				    
    Sfx_Unk1527     = 1527,
				    
    Sfx_Unk1567     = 1567,
				    
    Sfx_Unk1590     = 1590,
				    
    Sfx_Unk1601     = 1601,
    Sfx_Unk1602     = 1602,
				    
    Sfx_Unk1604     = 1604,
    Sfx_Unk1605     = 1605,
				    
    Sfx_Unk1609     = 1609,
    Sfx_Unk1610     = 1610,
} e_Sfx;

typedef enum _MainMenuEntry
{
    MainMenuEntry_Load     = 0,
    MainMenuEntry_Continue = 1,
    MainMenuEntry_Start    = 2,
    MainMenuEntry_Option   = 3,
    MainMenuEntry_Extra    = 4 /** @unused The extra options menu may have been accessible via the main menu. */
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
    u8                  field_4;
    u8                  field_5;
    u16                 field_6;
    s32                 field_8;
    union
    {
        // `func_80089DF0` reads `field_C` as bitfield, other `D_800AFD08` funcptrs read as `u32`?
        // TODO: Some funcs also treat `field_8` differently, should probably be part of union too.
        struct
        {
            u32 field_C_0  : 16;
            u32 field_C_16 : 12;
            u32 field_C_28 : 3;
            u32 field_C_31 : 1;
        } bitField;
        u32 u32;
    } field_C;
} s_8002AC04;
STATIC_ASSERT_SIZEOF(s_8002AC04, 16);

typedef struct
{
    s32 field_0;
    s32 field_4;
} s_func_80089644_1;

typedef struct
{
    s32               id_0;
    s32               flags_4;
    s32               modelCount_8;
    struct TMD_STRUCT models_c[1];
} s_TmdFile;

// Used in string parsing.
typedef struct
{
    s32 lineCount_0;
    s8  unk_1;
    s8  unk_38B4;
} s_800C38B4;

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

typedef struct
{
    s32 vx_0;
    s32 vz_4;
    s16 vy_8;
    u8  field_A;
    s8  field_B;
    s8  field_C;
    s8  field_D;
    s16 field_E;
    s32 field_10;
} s_func_800625F4;
STATIC_ASSERT_SIZEOF(s_func_800625F4, 20);

typedef struct _Collision
{
    q19_12 groundHeight_0;
    s16    field_4;  // } Angles??
    s16    field_6;  // }
    s8     field_8;  // Count of something? 0, 7, 12 are significant.
    u8     unk_9[3]; // Padding?
} s_Collision;
STATIC_ASSERT_SIZEOF(s_Collision, 12);

typedef struct
{
    VECTOR3  position_0;
    SVECTOR3 rotation_C;
    s8       field_12;
} s_func_8006AB50;

typedef struct
{
    s32        field_0;
    s32        field_4; // `bool`?
    s32        field_8; // 2D distance.
    SVECTOR    field_C; // 2D position?
    DVECTOR_XZ direction_14;
    q23_8      positionX_18;
    q23_8      positionZ_1C;
    s32        field_20;
    s32        field_24;
    s16        field_28; // } `SVECTOR3`, packed rotation?
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
    DVECTOR field_2; // Rotation?
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
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
} s_func_8006DCE0_6C; // Unknown size;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_func_8006DCE0_8C;

// Contains pointers to active characters among other things.
typedef struct
{
    s32                  field_0;
    s16                  field_4;
    s16                  field_6;
    s16                  field_8;
    s8                   unk_A[2];
    s32                  field_C;
    s32                  field_10;
    s32                  field_14;
    s8                   unk_18[4];
    s16                  field_1C;
    s8                   unk_1E[2];
    s_SubCharacter*      field_20;
    s16                  field_24;
    s16                  field_26;
    s32                  field_28;
    VECTOR3              field_2C; // Q23.8
    s8                   unk_38[4];
    s32                  field_3C;
    s32                  field_40;
    s32                  field_44;
    s8                   unk_48[4];
    s16                  field_4C;
    s16                  field_4E;
    SVECTOR              field_50; // Q23.8
    u16                  field_58;
    s16                  field_5A;
    s16                  field_5C;
    s16                  field_5E;
    s16                  field_60;
    s8                   unk_62[2];
    s_SubCharacter**     characters_64; // Active characters?
    s32                  characterCount_68;
    s_func_8006DCE0_6C   field_6C;
    s32                  field_7C;
    s32                  field_80;
    u16                  field_84;
    u8                   unk_86[2];
    s32                  field_88;
    s_func_8006DCE0_8C   field_8C[1]; // Unknown size.
} s_func_8006DCE0;

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

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18; // X } Bounds?
    s32 field_1C; // X }
    s32 field_20; // Z }
    s32 field_24; // Z }
    s32 field_28; // } Q19.12, maybe XZ position.
    s32 field_2C; // }
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

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
} s_func_80070400_1;

typedef struct
{
    s32 field_0;
    s32 field_4;
} s_func_8006F250;

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
    s16     field_18C[150];
    u8      field_2B8[200]; // Size likely incorrect.
    MATRIX  field_380;

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
    u8  field_6_0  : 8;
    s8  field_6_8  : 7;
    u8  field_6_15 : 1; // `bool`
    u16 field_8;
    u16 field_A;
    u8  unk_C[8];
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
    u_Filename    modelName_0;
    u8            meshCount_8;
    u8            vertexOffset_9;
    u8            normalOffset_A;
    u8            field_B_0 : 1;
    u8            field_B_1 : 3;
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

    // File header ends, extra data below.
    // After this goes array of `s_Material`, `s_ModelHeader` `modelsOrder`.
    // See https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/sh1_model.bt
    s8            unk_11[4075];
    s32           queueIdx_1000;
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
    u8                     field_1E;
    u8                     field_1F;
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
    s8                 levelGridX_2;
    s8                 levelGridY_3;
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
    s_IpdCollisionData*   field_0;
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
            u8                 field_0;
            u8                 field_1;
            u8                 field_2;
            u8                 field_3;
            s_func_8006CA18*   field_4;
            s_func_8006CC44_A8 field_8[4];
        } s_0;
        struct
        {
            s16 field_0;
            s16 field_2;
            s16 field_4;
            u8  field_6;
            u8* field_8;
            s8  unk_C[28];
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
    s32            field_0;
    GsCOORDINATE2* field_4;
    s_ModelHeader* modelHdr_8;
    s32            modelIdx_C;
} s_ModelInfo;

typedef struct _Bone
{
    s_ModelInfo   modelInfo_0;
    s8            field_10;
    s8            unk_11[3];
    struct _Bone* next_14;
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 24);

typedef struct
{
    u8      boneCount_0;
    u8      boneIdx_1;
    u8      field_2;
    s8      field_3;
    s_Bone* bones_4;
    s_Bone* bones_8;
    s_Bone  bones_C[56];
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

typedef struct
{
    s8             charaId0_0;  /** `e_CharacterId`. */
    s8             charaId1_1;  /** `e_CharacterId`. */
    // 2 bytes padding.
    s32            animFile0_4; // s_AnmHeader*    animFile0_4; // TODO: Needs to be a pointer.
    s_AnmHeader*   animFile1_8;
    s32            animFileSize1_C;
    s32            animFileSize2_10;
    GsCOORDINATE2* npcCoords_14;
} s_800A992C;
STATIC_ASSERT_SIZEOF(s_800A992C, 24);

typedef struct
{
    u8  field_0;
    u8  unk_1; // } Padding?
    u8  unk_2; // }
    u8  unk_3; // }
    u32 field_4    : 24;
    u8  field_4_24 : 8;
    u32 field_8    : 24;
    u8  field_8_24 : 8;
} s_800AA894;
STATIC_ASSERT_SIZEOF(s_800AA894, 12);

typedef struct
{
    u16  field_0;
    u8   unk_2[4];
    s8   field_6;
    s8   unk_7;
    u8   field_8;
    u8   field_9;
    u8   unk_A[4];
    u8   field_E;
    u8   field_F;
    u8   field_10;
    u8   field_11;
    u16  unk_12; // Guessed.
    u32* unk_14; // Some pointer. All entries have the same value `D_800AD4C4`.
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

/** @brief Collision point data.
 * TODO: Not sure on the name, still don't know what `field_18` is for. -- Sezz
 */
typedef struct
{
    VECTOR3     position_0;
    s_Collision collision_C;
    s32         field_18;
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

typedef struct _MapType
{
    s16                plmFileIdx_0;
    char               tag_2[4];
    u8                 flags_6;
    // 1 byte of padding.
    const s_WaterZone* waterZones_8;
    const s_SpeedZone* speedZones_C;
} s_MapType;

typedef struct
{
    u_Filename modelName_0;
    s8         field_8;
    s8         lmIdx_9; /** Set to 2 when found in `g_Map.globalLm_138.lmHdr_0` and 3-6 if found in `g_Map.ipdActive_15C[i] (i + 3)`. */
} s_WorldObject_0_10;

typedef struct
{
    s_ModelInfo        modelInfo_0;
    s_WorldObject_0_10 field_10;
} s_WorldObject_0;
STATIC_ASSERT_SIZEOF(s_WorldObject_0, 28);

typedef struct
{
    s_WorldObject_0* field_0;
    s32              gsCoordinate0_4 : 18; // Used as `GsCOORDINATE2::coord.t[0].`
    s32              gsCoordinate1_4 : 14; // Used as `GsCOORDINATE2::coord.t[1].`
    s32              gsCoordinate2_8 : 18; // Used as `GsCOORDINATE2::coord.t[2].`
    s32              unk_8_18        : 14;
    s32              vx_C            : 10;
    s32              vy_C            : 12;
    s32              vz_C            : 10;
} s_WorldObject;
STATIC_ASSERT_SIZEOF(s_WorldObject, 16);

typedef struct _HeldItem
{
    s32           itemId_0; /** `e_InventoryItemId` */
    s32           queueIdx_4;
    char*         textureName_8;
    s_FsImageDesc imageDesc_C;
    s_LmHeader*   lmHdr_14;
    s_Bone        bone_18;
} s_HeldItem;

typedef struct _WorldGfx
{
    s_MapType*        type_0;
    u8                useStoredPoint_4; /** `bool` */
    u8                unk_5[3];
    VECTOR3           ipdSamplePoint_8; /** Used by IPD logic to sample which chunks to load or unload. */
    s32               dataPtr_14;       // Used frequently as `s_LmHeader*`, but code adds file lengths to it. Could just be `u8*` pointing to current file data?
    s_CharaModel*     charaModelsTable_18[Chara_Count];
    s_CharaModel      charaModels_CC[4];
    s_CharaModel      harryModel_164C;
    s_HeldItem        heldItem_1BAC;
    VC_CAMERA_INTINFO vcCameraInternalInfo_1BDC; /** Debug camera info. */
    s_LmHeader        itemLmHdr_1BE4;
    s32               objectCount_2BE8;
    s_WorldObject     objects_2BEC[29]; // Size based on the check in `g_WorldGfx_ObjectAdd`.
} s_WorldGfx;
STATIC_ASSERT_SIZEOF(s_WorldGfx, 11708);

// IPD data?
typedef struct
{
    s_IpdHeader* ipdHdr_0;
    s32          queueIdx_4;
    s16          coordX_8;
    s16          coordZ_A;
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
    s_IpdCollisionData field_0;
    s32                texFileIdx_134;
    s_GlobalLm         globalLm_138;
    char               mapTag_144[4];
    s32                mapTagSize_148;
    s32                ipdFileIdx_14C;
    s_IpdHeader*       ipdBuffer_150;
    s32                ipdBufSize_154;
    s32                ipdActiveSize_158;
    s_IpdChunk         ipdActive_15C[4];
    s_IpdColumn        ipdGrid_1CC[18];
    s8                 unk_40C[32];     // Could be one extra row in table above.
    s_IpdColumn*       ipdGridCenter_42C;
    s_IpdTextures      ipdTextures_430;
    s32                field_578;
    s32                field_57C;
    s32                field_580; // File chunk coord X.
    s32                field_584; // File chunk coord Z.
    bool               isExterior;
} s_Map;
STATIC_ASSERT_SIZEOF(s_Map, 1420);

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
    s8  field_C; // (?) volume?
    s8  field_D; // BGM volume?
    s8  field_E; // SE volume?
} s_800C1678;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
} s_800C1688;

/** Sound struct for currently used SFX? */
typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A; // Pitch?
    s16 volumeLeft_C;
    s16 volumeRight_E;
} s_800C1698;

typedef struct
{
    s8  field_0;
    s8  unk_1;
    u16 field_2;
    u32 field_4;
    s32 field_8;
} s_800C37D4;

// Used in string parsing.
typedef struct
{
    s8 field_0;
    s8 positionIdx_1;
} s_800C38B0;

typedef struct
{
    u8            field_0;
    u8            fogEnabled_1; // `bool`
    u8            field_2;
    u8            field_3;
    s_WaterZone*  waterZones_4;
    s32           screenBrightness_8;
    s8            unk_C[4];
    q23_8         drawDistance_10; // Name from SHME, "has no effect when fog is disabled".
    s32           fogRelated_14;   // "FogThing1" from SHME, seems to affect distance where fog begins.
    s32           fogRelated_18;   // "FogThing2" from SHME.
    CVECTOR       fogColor_1C;
    s32           field_20;
    u8            field_24;
    u8            field_25;
    u8            field_26;
    s8            unk_27;
    CVECTOR       worldTintColor_28;
    MATRIX        field_2C;
    s32           field_4C;
    s16           field_50;
    s32           field_54;
    SVECTOR       field_58;
    VECTOR3       field_60; // Type assumed.
    SVECTOR       field_6C; // Player current angles?
    SVECTOR       field_74;
    SVECTOR       field_7C;
    u8            unk_84[72];
    u8            field_CC[1]; // Unknown size.
} s_800C4168;

typedef struct
{
    s32 field_0_0  : 1;
    s32 field_0_1  : 10; // X
    s32 field_0_11 : 10; // Z
    u32 field_0_21 : 4;  // X
    u32 field_0_25 : 4;  // Z
    u32 field_0_29 : 3;
} s_func_8006F8FC;

typedef struct
{
    u16              field_0;
    u8               field_2;
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
    s16            textureFileIdx : 16;
    u16            field_6        : 10;
    u16            field_6_10     : 6;
    s_FsImageDesc* field_8; // Guessed type.
    u16            field_C_0  : 2;
    s32            field_C_2  : 14;
    u16            field_C_16 : 16;
} s_CharaFileInfo;
STATIC_ASSERT_SIZEOF(s_CharaFileInfo, 16);

typedef struct
{
    SVECTOR3 posTarget_0;    // Q7.8
    SVECTOR3 lookAtTarget_6; // Q7.8
    s16      field_C[2]; // `field_C[1]` gets passed to `vcChangeProjectionValue`.
} s_DmsKeyframeCamera;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCamera, 16);

typedef struct
{
    SVECTOR3 position_0; // Q7.8
    SVECTOR3 rotation_6; // Q7.8
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
    s16 startKeyframeIdx_0;
    s16 frameCount_2; /** Keyframe count or frame duration at 30FPS? */
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
    VECTOR3        origin_C; // Q23.8 | Origin point, gets added to character positions.
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
/** TODO: Rename to `PointOfInterest` to match SilentHillMapExaminer name? The array inside map header seems more for holding data for points on the map rather than just chara positioning. */
/** This also makes use of union from 0x4 - 0x8 for different kinds of params, see https://github.com/Sparagas/Silent-Hill/blob/87549363834af24c65f6432908b2b036f9a300ad/010%20Editor%20-%20Binary%20Templates/sh1_overlays.bt#L126 */
typedef struct _AreaLoadParams
{
    q19_12 char_x_0; // TODO: Rename to `positionX_0`.
    u32    mapIdx_4_0          : 5; /** `e_Current2dMapIdx` */
    u32    field_4_5           : 4;
    u32    loadingScreenId_4_9 : 3; /** `e_LoadingScreenId`` */
    u32    field_4_12          : 4;
    u32    rotationY_4_16      : 8; /** Degrees in Q7.8, range [0, 256]. */
    u32    field_4_24          : 8;
    q19_12 char_z_8; // TODO: Rename to `positionZ_8`.
} s_AreaLoadParams;

typedef struct
{
    u8  field_0;
    u8  unk_1;
    u16 field_2;
    u8  field_4;
    s8  field_5;
} s_Sfx;

typedef struct _SpawnInfo
{
    q19_12 positionX_0;
    s8     charaId_4;   /** `e_CharacterId` */
    u8     rotationY_5; /** Degrees in Q7.8, range [0, 256]. */
    s8     flags_6;     /** Copied to `stateStep_3` in `s_Model`, with `state_2 = 0`. */
    s8     unk_7;
    q19_12 positionZ_8;
} s_SpawnInfo;
STATIC_ASSERT_SIZEOF(s_SpawnInfo, 12);

/** Contains loaded anim data? */
typedef struct
{
    s16 status_0; /** Packed anim status. See `s_ModelAnim::status_0`. */
    s16 status_2; /** Packed anim status. See `s_ModelAnim::status_0`. */
    s16 time_4;   /** Fixed-point anim time. */
    s16 field_6;
} s_UnkStruct3_Mo; // Probable size: 8 bytes.

/** Guessed based on in-debugger observation during gameplay.
 * Everything is inited to 0xFFFF and some data is written when the player is hit by monsters.
 * Might be more generic particles/decals struct.
 */
typedef struct _BloodSplat
{
    s16 unk_0; // Maybe an array of `u16`s?
} s_BloodSplat;

/** TODO: `g_MapOverlayHeader` is part of the map overlay BIN files. Maybe should be moved to `maps/shared.h`. 
 * If field has a comment that lists only certain map(s) it means all others set this field to 0.
 * func(?) means the signature is unknown and a default void() was selected for now.
 */
typedef struct _MapOverlayHeader
{
    s_MapType*        type_0;
    u8                (*getMapRoomIdxFunc_4)(s32 x, s32 y); // Called by `Savegame_MapRoomIdxSet`.
    s8                field_8;
    s8                unk_9[3];
    s32               (*func_C)();
    void              (*func_10)(s32 arg);
    s8                field_14; // Flags?
    u8                field_15;
    s8                field_16;
    s8                field_17;
    void              (**loadingScreenFuncs_18)();
    s_AreaLoadParams* mapAreaLoadParams_1C;
    void              (**mapEventFuncs_20)(); /** Points to array of event functions. */
    u8*               unk_24;
    GsCOORDINATE2*    field_28;
    u8*               loadableItems_2C;
    const char**      mapMessages_30; // Array of strings.
    s_AnimInfo*       animInfos_34;   // Map-specific anim infos for Harry (for anims 38+).
    s_UnkStruct3_Mo*  field_38;
    void              (*func_3C)(); // func(?).
    void              (*func_40)();
    void              (*func_44)();
    void              (*func_48)(); // func(?).
    s_func_800625F4*  unkTable1_4C;
    s16               unkTable1Count_50;
    s8                unk_52[2];
    s_BloodSplat*     bloodSplats_54;
    s16               bloodSplatCount_58;
    s8                unk_5A[2];
    s32               always0_5C;
    s32               always0_60;
    s32               always0_64;
    s32               always0_68;
    void              (*func_6C)(); // func(?).
    void              (*func_70)(); // func(?).
    void              (*func_74)(); // func(?).
    void              (*func_78)(); // func(?).
    u8*               unk_7C; // only map1_s01, map6_s04. 
    void              (*func_80)(); // func(?).
    void              (*func_84)(); // func(?).
    s32*              unk_88; // only map0_s01, map7_s01.
    void              (*func_8C)(); // func(?) only map0_s01, map7_s01.
    void              (*func_90)(); // func(?) only map5_s00.
    s32*              unk_94; // only map1_s02, map1_s03.
    s32*              unk_98; // only map1_s02, map1_s03.
    s32*              unk_9C; // only map1_s02, map1_s03.
    s32*              unk_A0; // only map1_s03.
    void              (*func_A4)(); // func(?) only map1_s03.
    void              (*func_A8)(); // func(?) only map6_s02.
    void              (*func_AC)(); // func(?) only map4_s03, map4_s05.
    void              (*func_B0)(); // func(?) only map4_s03, map4_s05.
    void              (*func_B4)(); // func(?) only map1_s03, map4_s05, map6_s01, map6_s02, map5_s01.
    void              (*func_B8)(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);
    void              (*func_BC)(s_SubCharacter*, s_MainCharacterExtra*, GsCOORDINATE2*);
    void              (*func_C0)(); // func(?).
    void              (*func_C4)(); // func(?).
    void              (*freezePlayerControl_C8)();
    void              (*unfreezePlayerControl_CC)(s32);
    s32               (*func_D0)(s32, void*, s16, s32); // 0x800C964C
    s32               (*func_D4)(s32);                  // Assumed return type.
    void              (*func_D8)();                     // Assumed return type.
    void              (*func_DC)();                     // Assumed return type.
    void              (*func_E0)(); // func(?).
    s32               (*func_E4)(s_SubCharacter*, s32); // Assumed return type.
    s64               (*func_E8)(s_SubCharacter*);      // Is it really `s64`???
    s32               (*func_EC)();
    void              (*func_F0)(); // func(?).
    void              (*func_F4)(); // func(?).
    void              (*func_F8)(); // func(?).
    void              (*func_FC)(); // func(?).
    void              (*func_100)(); // func(?).
    void              (*func_104)(); // func(?).
    s32               (*func_108)();
    void              (*func_10C)(); // func(?).
    void              (*func_110)(); // func(?).
    void              (*func_114)(); // func(?).
    void              (*func_118)(); // func(?).
    void              (*func_11C)(); // func(?).
    void              (*func_120)(); // func(?).
    void              (*func_124)(s_SubCharacter*); // Assumed return type.
    s32               (*func_128)(s_SubCharacter*); // Assumed return type.
    s32               (*func_12C)(s_SubCharacter*); // Assumed return type.
    void              (*func_130)(); // func(?).
    s32               (*func_134)(s_SubCharacter*); // Assumed return type.
    s32               (*func_138)(s_SubCharacter*); // Keyframe getter. Return value depends on the anim update function being used.
    s32               (*func_13C)(s32, s32, void*, s16, s32); // 0x800C96B8
    void              (*func_140)(); // func(?).
    void              (*func_144)(); // func(?).
    void              (*func_148)(); // func(?).
    void              (*func_14C)(); // func(?).
    void              (*func_150)(); // func(?).
    void              (*func_154)(); // func(?).
    void              (*func_158)(s32, s32); // only map1_s05, map1_s06.
    void              (*func_15C)(); // func(?) only map5_s01.
    void              (*func_160)(); // func(?) only map5_s01.
    void              (*func_164)(); // func(?) only map5_s01.
    void              (*func_168)(s32, s32, s32);
    void              (*func_16C)(VECTOR3*, s16);
    void              (*func_170)(); // func(?).
    void              (*func_174)(); // func(?).
    void              (*func_178)(void*, void*, void*);
    void              (*func_17C)(void*, void*);
    void              (*func_180)(); // func(?).
    s32*              windSpeedX_184;
    s32*              windSpeedZ_188;
    s32*              data_18C;
    s32*              data_190;
    void              (*charaUpdateFuncs_194[Chara_Count])(s_SubCharacter*, void*, s32); /** Guessed params. Funcptrs for each `e_CharacterId`, set to 0 for IDs not included in the map overlay. Called by `func_80038354`. */
    s8                charaGroupIds_248[4];                                              /** `e_CharacterId` values where if `s_SpawnInfo.charaId_4 == Chara_None`, `charaGroupIds_248[0]` is used for `charaSpawns_24C[0]` and `charaGroupIds_248[1]` for `charaSpawns_24C[1]`. */
    s_SpawnInfo       charaSpawns_24C[2][16];                                            /** Array of character type/position/flags. `flags_6 == 0` are unused slots? Read by `func_80037F24`. */
    VC_ROAD_DATA      roadDataList_3CC[48];
    u32               unk_84C[512];
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 4172); // Size incomplete.

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
    u8 field_0;
    u8 field_1;
} s_800A9F80;

typedef struct
{
    s8   field_0; /** `bool` */
    u8   field_1;
    s8   unk_2[2];
    s32* field_4;
    s32* field_8;
    s32  field_C;
    u32  field_10; // Maybe `bool`, not enough context.
    s32  field_14;
    s32  field_18;
    q7_8 field_1C; // Angle.
} s_func_800700F8_2;

typedef struct
{
    VECTOR3 field_0;
    s32     field_C; // Absolute ground height?
    s16     field_10;
    s16     field_12;
    s8      field_14; // Count of something? 12 is significant.
    s8      unk_15[3];
    s32     field_18;
} s_800C4590;

typedef struct
{
    DVECTOR  screenXy_0[90];
    u16      screenZ_168[18];
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

// ========
// GLOBALS
// ========

extern s_FsImageDesc g_MainImg0; // 0x80022C74 - TODO: Part of main exe, move to `main/` headers?

extern const s_MapType MAP_TYPES[16];

extern char D_80028544[0x10];

extern RECT D_80028A20;

extern s_AnimInfo D_80028B94[];

extern s_800C44F0 D_800294F4[];

extern s_AnimInfo* D_800297B8;

extern u_Filename D_8002B2CC;

extern s32 g_MapMsg_WidthTable[];

extern u8 g_BackgroundColor;

extern DR_MODE D_800A8E5C[];

extern TILE D_800A8E74[];

extern q19_12 g_ScreenFadeProgress;

extern DR_MODE D_800A8E98[];

extern POLY_G4 D_800A8EB0[];

extern s32 D_800A8F40;

extern s_FsImageDesc g_Font16AtlasImg;    // 0x800A8FF4
extern s_FsImageDesc g_KonamiLogoImg;     // 0x800A8FFC
extern s_FsImageDesc g_KcetLogoImg;       // 0x800A9004
extern s_FsImageDesc g_TitleImg;          // 0x800A9014
extern s_FsImageDesc g_MapImg;            // 0x800A901C
extern s_FsImageDesc g_MapMarkerAtlasImg; // 0x800A9024
extern s_FsImageDesc g_ItemInspectionImg; // 0x800A902C
extern s_FsImageDesc D_800A9034;
extern s_FsImageDesc g_ControllerButtonAtlasImg;   // 0x800A903C
extern s_FsImageDesc g_BrightnessScreenImg0;       // 0x800A9044
extern s_FsImageDesc g_BrightnessScreenImg1;       // 0x800A904C
extern s_FsImageDesc g_DeathTipImg;                // 0x800A9054
extern s_FsImageDesc g_HealthPortraitImg;          // 0x800A905C
extern s_FsImageDesc g_InventoryKeyItemTextureImg; // 0x800A9064
extern s_FsImageDesc g_FirstAidKitItemTextureImg;  // 0x800A906C

/** Some intentory item texture (`ITEM/TIM07.TIM`). */
extern s_FsImageDesc D_800A9074;

extern s_FsImageDesc D_800A9084;

extern s_FsImageDesc D_800A908C;

extern s_FsImageDesc D_800A9094;

extern s_FsImageDesc g_Font24AtlasImg; // 0x800A909C

/** Array containg file IDs used for each `e_CharacterId`, used in `Fs_QueueStartReadAnm`. */
extern s_CharaFileInfo CHARA_FILE_INFOS[45]; // 0x800A90FC

extern s_sub_StructUnk3 D_800A93CC[];

extern s_StructUnk3 D_800A952C;

extern u16 D_800A9774[];

extern u16 g_UnknownEngineCmdTable1[];

extern s_800C37D4 D_800A986C[];

extern s32 D_800A9A20;

/** X. */
extern s32 D_800A9A24;

/** Z. */
extern s32 D_800A9A28;

/** Associates each character ID with a map's `charaGroupIds_248` index for that ID (+ 1?). */
extern s8 D_800A98FC[Chara_Count];

extern s32 D_800A9EB0;

extern s_FsImageDesc D_800A9EB4;

extern s_FsImageDesc D_800A9EBC;

extern s_FsImageDesc D_800A9EC4;

/** `Demo_FrameCount` */
extern s32 g_Demo_FrameCount;

extern s32 g_UnknownFrameCounter;

/** Function pointer array, maybe state funcs of some kind. */
extern void (*g_GameStateUpdateFuncs[])();

/** Related to sound commands. */
extern u16 g_UnknownEngineCmdTable0[];

extern u16 g_UnknownEngineCmdTable2[];

/** `D_800A992C` and `D_800A9944` are likely the same variable or they are inside a struct.
 * `D_800A992C` has values that seem related to the player, while `D_800A9944`
 * dynamically allocates data for other characters.
 *
 * `D_800A992C`'s `field_4` and `field_8` are set to `FS_BUFFER_0`.
 */
extern s_800A992C D_800A992C[];

extern u8 D_800A9944[];

/** Player anim info? */
extern s_AnimInfo D_800A998C;

/** Current player anim index store? */
extern u8 D_800A9990;

/** Used in `func_800D929C` from `map0_s00.c`. */
extern s32 D_800A999C;

extern s32 D_800A99A0;

extern u8 D_800A99A4[8];

/** Relative file offset for map texture? */
extern s8 D_800A99B5;

extern s_800A99E4 D_800A99E4;

extern s32 g_MapMsg_CurrentIdx;

extern s16 g_MapMsg_SelectFlashTimer;

extern s8 g_FullscreenMapTimFileIdxs[24];

extern s8 g_MapMarkingTimFileIdxs[56];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A0C; // Old IDB name `FS_AllFilesLoaded`, though FS code doesn't set it.

/** `e_SysState` */
extern s32 D_800A9A10;

extern s32 D_800A9A1C;

extern void (*g_SysStateFuncs[])();

extern s32 D_800A9A68;

extern s32 g_MainMenuState;

extern s32 g_MainMenu_SelectedEntry;

/** Flags for which main menu entries should be visible.
 * @unused Flag (1 << 5) corresponds to the "EXTRA" option, which is unused and never set.
 */
extern u32 g_MainMenu_VisibleEntryFlags;

/** Counts the amount of times that demos has been play in the current game session. */
extern s8 g_Demo_ReproducedCount;

extern s32 g_MainMenu_NewGameSelectedDifficultyIdx;

extern s32 g_PrevSavegameCount;

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

extern u8 REVERB_DEPTHS[];

extern u8 D_800AA604[][16];

extern s_800AA894 D_800AA894[];

extern u8 D_800AE185;

extern u8 D_800AE186;

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

extern u8 D_800AE740[];

/** Angle? */
extern s16 D_800AF210;

/** Angle? */
extern s16 D_800AF212;

extern u8 D_800AF220;

extern s32 D_800AF224;

extern s_AnimInfo HARRY_BASE_ANIM_INFOS[]; // Maybe part of bigger struct. 0x800AF228

extern s16 D_800AF506;

extern s16 D_800AF526;

extern s16 D_800AF5C6;

extern s16 D_800AF624;

/** Keyframe index. */
extern s16 D_800AF626;

extern s_CollisionPoint D_800AFC78; // Maybe different struct.

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern s32 D_800AFD3C;

extern s32 D_800AFD44;

extern s32 D_800AFD60;

extern s32 D_800AFD9C;

extern SVECTOR D_800AFDB0;

extern s32 D_800AFDEC;

extern s32 D_800B2618;

extern s32 D_800B261C;

extern s32 D_800B2620;

extern PACKET D_800BFBF0[][0xA10];

extern GsF_LIGHT D_800C3AC8[];

extern GsDOBJ2 D_800C3E08;

extern u8 g_Items_GunsMaxLoadAmmo[36]; // Max loaded ammo that a weapon can hold. 0x800AD4A0

extern const char* INVENTORY_ITEM_NAMES[];

extern const char* g_ItemDescriptions[];

extern q19_12 g_PrevScreenFadeProgress;

extern s32 g_ScreenFadeTimestep;

extern GsOT_TAG g_OtTags0[2][16];

extern GsOT_TAG g_OtTags1[2][2048];

extern s_SubCharacter D_800BA00C; // Often passed to `func_800700F8`, might not be full `s_SubCharacter`?

extern u8 D_800BC74F;

extern u16 D_800BCCB0;

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

extern s16 g_SavegameCount;

/** @brief Test if demo loading should be reinitialized.
 * This is used exclusively in `GameFs_MapStartup` with
 * the purpose of testing if demo loading should be reinitialized
 * if file load has failed.
 *
 * It makes up to 5 attemps. If the load fails, it restarts
 * the entire process by restarting the timer used to check if a demo
 * should be triggered.
 *
 * @note Strange decision to make this a global when it's
 * only ever used in that function.
 */
extern s32 g_DemoLoadAttempCount;

extern s8 D_800BCD50[8];

extern u32 D_800BCD58;

extern s32 D_800BCD5C;

extern s32 g_MapMsg_StateMachineIdx1;

extern s32 g_MapMsg_StateMachineIdx2;

extern s32 g_MapMsg_DisplayLength;

/** Map message index. */
extern s32 g_MapMsg_MainIdx;

/** How many glyphs at a time to advance the message roll. */
extern s32 g_MapMsg_DisplayInc;

extern s32 D_800BCD74;

extern s_MapMsgSelect g_MapMsg_Select;

extern u8 g_MapMsg_AudioLoadBlock;

extern s8 g_MapMsg_SelectCancelIdx;

extern s32 D_800BCD84;

extern s32 D_800BCD90[];

extern s_800BCDA8 D_800BCDA8[2];

extern s_AreaLoadParams D_800BCDB0;

/** Related to special item interactions. */
extern s32 D_800BCDC0[5];

extern u8 D_800BCDD4;

/** Related to main menu fog randomization. */
extern s8* D_800BCDE0; // Type assumed.

/** Angles. */
extern s16 D_800BCDE8[];

extern u16 D_800BCE14;

extern s_WorldGfx g_WorldGfx;

extern s_IpdCollisionData* D_800C1010[];

extern s_Map g_Map;

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s32 D_800C15B8;

/** Absolute SFX index. */
extern s16 D_800C15BC;

extern s16 g_Sound_ActiveSfxIdx;

extern u16 D_800C15C0;

/** Base-0 SFX index. */
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

/** `bool` */
extern u8 g_Sound_IsStereoEnabled;

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

extern u8 g_Sound_VolumeBgm; // 0x800C1685

extern u8 g_Sound_VolumeXa; // 0x800C1686

extern u8 g_Sound_VolumeSe; // 0x800C1684

extern u8 g_Sound_ReverbDepth; // 0x800C1687;

extern u8 D_800C1673;

extern s_800C1688 D_800C1688;

extern s_800C1698 D_800C1698;

extern s16 D_800C16A4;

extern u8 D_800C16A8[32];

extern s32 D_800C16C8; // Type assumed.

extern s32 D_800C3920;

extern s8 D_800C3950;

extern s32 D_800C3954;

extern s32 D_800C3958;

extern s32 D_800C395C;

extern s8 D_800C3960;

extern s8 D_800C3961;

extern s8 D_800C3962;

extern u8 D_800C3963;

/** Game difficulty. */
extern s32 D_800C3994;

extern u8 D_800C37D0;

extern s_800C37D4* D_800C37D8;

extern s_800C38B0 D_800C38B0;

extern s_800C38B4 D_800C38B4;

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

extern GsF_LIGHT D_800C3A88[];

extern u8 D_800C3E40;

/** Functions from `bodyprog_8003AB28` access `D_800C4168` as constant, but some functions from `bodyprog_80055028` write to it.
 * It appears that D_800C4168 is intended to be defined inside `bodyprog_80055028` as writable and declared as read-only (`const`) outside of it.
 */
// extern s_800C4168 D_800C4168;

extern u16 D_800C42B4; // TODO: May be part of `s_800C4168`.

extern GsCOORDINATE2* D_800C42B8;

extern VECTOR3 D_800C42C0;

extern VECTOR3* D_800C42CC;

extern u16 D_800C42D0;

extern u16 D_800C42D2;

extern u16 g_LoadedEffectTextureFlags;

extern s16 D_800C4408;

extern s8 D_800C4414;

extern s_SubCharacter* D_800C4458;

/** Array of active characters? */
extern s_SubCharacter** D_800C4474;

// emoose: Also works: `extern u16 D_800C4478[];`, `arg0->field_4 = D_800C4478[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_800C4478 D_800C4478;

extern s8 D_800C447A;

extern s32 D_800C44D0;

extern s32 D_800C44D4;

extern s_PlayerCombat D_800C44E0;

/** Table of player keyframe indices. Purpose unknown. */
extern s_800C44F0 D_800C44F0[10];

// Enemy target.
extern VECTOR3 g_TargetEnemyPosition; // 0x800C4540

extern s16 D_800C4554; // Timer?

extern s16 D_800C4556; // Timer?

extern s16 D_800AEEDC[][2]; // Type assumed.

extern s16 D_800AEF78[][2]; //  Type assumed.

extern s16 D_800AF014[];

extern s16 D_800AF04C[];

extern s16 D_800AF070[]; // Type assumed.

extern s16 D_800AF1FC[]; // Type assumed.

extern s8 D_800C4588;

extern s_800C4590 D_800C4590;

extern VECTOR3 D_800C45B0; // Assumed type

extern s_800C45C8 D_800C45C8;

/** Related to game difficulty. Maybe multiplier? */
extern s32 D_800C45EC;

extern u8 D_800C4606;

extern s32 D_800C4610;

extern s32 D_800C4618;

extern s8 D_800C4560;

extern u8 D_800C4561;

extern s_Collision D_800C4620;

extern VECTOR3 D_800C4640[][8]; // Or struct?

extern s32 D_800C46A0;

extern s16 D_800C4700[];

extern s16 D_800C4702;

extern s_800C4818 D_800C4818;

/** Something for demo handling. Set in `Fs_QueueDoThingWhenEmpty`. */
extern bool D_800C489C;

extern s32 D_800C48F0;

extern RECT D_801E557C[];

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

extern s16 D_800C6E26;

extern s16 D_800C6E8E;

extern u8 D_800C6E90;

extern s_Sfx g_Sfx_Table0[420];

extern u8 D_800AD480[24];

extern s_800AD4C8 D_800AD4C8[70];

extern const s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

// ==========
// FUNCTIONS
// ==========

/** Draws a background image.
 * Only applies to menus and the preview of maps when grabbing them.
 */
void Gfx_BackgroundSpriteDraw(s_FsImageDesc* image);

void Gfx_BackgroundSpritesTransition(s_FsImageDesc* image0, s_FsImageDesc* image1, s16 arg2);

/** Draws a background image.
 * Only applies to background images of notes or puzzles images.
 */
void Gfx_BackgroundSpriteDraw_2(s_FsImageDesc* image);

/** @brief Applies motion blur to the scene.
 *
 * Used only in the loading screen.
 */
bool Gfx_2dBackgroundMotionBlur(s32 arg0);

/** @unused Possibly a leftover from when the save menu was part of `BODYPROG.BIN`.
 * Draws some string in display space.
 */
void SaveLoad_NowLoadingStringDraw();

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

void Chara_PositionUpdateFromParams(s_AreaLoadParams* params);

void func_8003943C();

/** `SysState_Fmv` update function.
 * Movie to play is decided by `2072 - g_MapEventIdx`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update();

s32 Map_TypeGet();

void CharaModel_Free(s_CharaModel* model);

void func_8003C220(s_MapOverlayHeader* mapHdr, s32 playerPosX, s32 playerPosZ);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003C850();

void func_8003C878(s32 arg0);

void WorldObject_ModelNameSet(s_WorldObject_0* arg0, char* newStr);

void g_WorldGfx_ObjectAdd(s_WorldObject_0* arg0, const VECTOR3* pos, const SVECTOR3* rot);

/** Returns held item ID. */
s32 func_8003CD5C();

void func_8003CD6C(s_PlayerCombat* combat);

/** Returns `bool`? */
s32 func_8003CDA0(s32 invSlotIdx);

void func_8003D01C();

void func_8003D03C();

s32 func_8003D444(s32 charaId);

void func_8003D550(s32 charaId, s32 arg1);

/** Called by some chara init funcs, similar to `func_8003DD80`? */
void func_8003D468(s32 arg0, bool flag);

void func_8003D6A4(s_CharaModel* model);

/** Return type assumed. */
void func_8003D160();

s32 func_8003D21C(s_MapOverlayHeader* arg0);

void func_8003D5B4(s8 arg0);

void func_8003D6E0(s32 charaId, s32 modeIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

s32 func_8003DD74(s32 charaId, s32 arg1);

void func_8003DD80(s32 modelIdx, s32 arg1); // Called by some chara init funcs.

void func_8003E740();

void func_8003ED74(s32 arg0, s32 arg1);

void func_8003EDA8();

void func_8003EF10(s32 idx0, s32 idx1, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

s32 func_8003F4DC(GsCOORDINATE2** arg0, SVECTOR* rot, s32 arg2, s32 arg3, u32 arg4, s_SysWork* sysWork);

u32 func_8003F654(s_SysWork_2288* arg0);

s32 func_8003F6F0(s32 arg0, s32 arg1, s32 arg2);

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight);

/** @brief Computes the weighted average of `a` and `b`.
 *
 * @param a First value.
 * @param b Second value.
 * @param weight Weight as a fixed-point alpha in Q3.12, range `[0, 4096]`. 
 * @return Weighted average of `a` and `b`.
 */
s32 Math_WeightedAverageGet(s32 a, s32 b, s32 weight);

void func_8003FCB0(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 arg3);

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, s32 weight0, s32 weight1, s32 alphaTo);

void func_8003FE04(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s_sub_StructUnk3* arg2, s32 alphaTo);

s32 func_8003FEC0(s_sub_StructUnk3* arg0);

void func_8003FF2C(s_StructUnk3* arg0);

void func_80040004(s_WorldGfx* worldGfx);

void func_80040014();

/** @brief Computes the stereo sound balance based on the relative position to the camera.
 *
 * @param soundPos Sound source position.
 * @return Stereo sound balance in the range [-127, 127], where values affect the left-right channel balance.
 */
s8 Sound_StereoBalanceGet(const VECTOR3* soundPos);

bool func_80040B74(s32 charaId);

/** Related to the screen. */
void func_80040BAC();

void func_80040E7C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);

void func_80041074(GsOT* arg0, s32 arg1, SVECTOR* arg2, VECTOR3* arg3);

void func_800410D8(VECTOR3* pos0, s32* arg1, s32* arg2, SVECTOR* rot, VECTOR3* pos1);

void func_8004122C(s32* angle0, s32* angle1, VECTOR* arg2, VECTOR* arg3);

void func_8004137C(VECTOR3* result, VECTOR* vec0, VECTOR* vec1, s32 screenDist);

void func_800414E0(GsOT* arg0, VECTOR3* arg1, s32 arg2, s32 arg3, s32 arg4);

/** @brief Gets the load status of a queue entry by utilizing `Fs_QueueIsEntryLoaded`.
 *
 * @param queueIdx Index of the queue entry to check.
 * @return Queue entry load status (`e_FsQueueEntryLoadStatus`).
 */
u32 Fs_QueueEntryLoadStatusGet(s32 queueIdx);

void Map_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize);

void GlobalLm_Init(s_GlobalLm* globalLm, s_LmHeader* lmHdr);

void LmHeader_Init(s_LmHeader* lmHdr);

/** @brief Clears `queueIdx_4` in array of `s_IpdChunk` */
void Ipd_ActiveChunksQueueIdxClear(s_IpdChunk* chunks, s32 chunkCount);

void Ipd_TexturesInit1();

void Map_IpdCollisionDataInit();

void Map_PlaceIpdAtGridPos(s16 ipdFileIdx, s32 chunkCoordX, s32 chunkCoordZ);

void Ipd_ActiveChunksClear0();

void Ipd_TexturesInit0();

void func_800420C0();

void Map_GlobalLmFree();

s_Texture* func_80042178(char* texName);

void func_800421D8(char* mapTag, s32 plmIdx, s32 activeIpdCount, bool isExterior, s32 ipdFileIdx, s32 texFileIdx);

void Ipd_ActiveChunksClear(s_Map* map, s32 arg1);

/** @brief Locates all IPD files for a given map type.
 *
 * Example:
 * Map type THR.
 * `file 1100` is `THR0205.IPD`, `ipdGridCenter_42C[2][5] = 1100`.
 */
void Map_MakeIpdGrid(s_Map* map, char* mapTag, s32 fileIdxStart);

/** @brief Converts two hex `char`s to an integer hex value.
 *
 * @param out Output hex `int`.
 * @param hex0 First hex `char`.
 * @param hex1 Second hex `char`.
 */
bool ConvertHexToS8(s32* out, char hex0, char hex1);

s_IpdCollisionData** func_800425D8(s32* collDataIdx);

s_IpdCollisionData* func_800426E4(s32 posX, s32 posZ);

s32 func_8004287C(s_WorldObject_0* arg0, s_WorldObject_0_10* arg1, s32 posX, s32 posZ);

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

void func_80042C3C(q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ);

/** @brief When `isExterior` is `true`, chunks are treated as if they were 1 meter larger in both axes. Then calls `Ipd_DistanceToEdgeGet`. */
q19_12 Ipd_DistanceToEdgeWithPaddingGet(q19_12 posX, q19_12 posZ, s32 ipdChunkCoordX, s32 ipdChunkCoordZ, bool isExterior);

/** @brief Returns `FP_METER(0.0f)` if inside the chunk, distance to closest edge otherwise. */
q19_12 Ipd_DistanceToEdgeGet(q19_12 posX, q19_12 posZ, s32 ipdChunkCoordX, s32 ipdChunkCoordZ);

s32 func_80042EBC(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ);

void Ipd_ActiveChunksSample(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

void Ipd_DistanceToEdgeCalc(s_IpdChunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

void func_800433B8(s_Map* map);

void func_800433B8(s_Map* map);

s32 Map_IpdIdxGet(s32 gridX, s32 gridZ);

bool Map_IsIpdPresent(s_IpdChunk* chunks, s32 chunkCoordX, s32 chunkCoordZ);

s_IpdChunk* Ipd_FreeChunkFind(s_IpdChunk* chunks, bool isExterior);

s32 Ipd_LoadStart(s_IpdChunk* chunk, s32 fileIdx, s32 chunkCoordX, s32 chunkCoordZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

bool func_80043740();

bool func_80043830(void);

bool func_8004393C(q19_12 posX, q19_12 posZ);

void func_80043A24(GsOT* ot, s32 arg1);

bool func_80043B34(s_IpdChunk* chunk, s_Map* map);

/** Checks if PLM texture is loaded? */
bool IpdHeader_IsTextureLoaded(s_IpdHeader* ipdHdr);

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHdr);

void IpdHeader_FixOffsets(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount, s_ActiveTextures* arg3, s_ActiveTextures* arg4, s32 arg5);

void Ipd_MaterialsLoad(s_IpdHeader* ipdHdr, s_ActiveTextures* arg1, s_ActiveTextures* arg2, s32 fileIdx);

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

/** Sets IPD collision data grid coords? */
void func_80044044(s_IpdHeader* ipd, s32 gridX, s32 gridZ);

void func_80044090(s_IpdHeader* ipdHdr, s32 arg1, s32 arg2, GsOT* ot, void* arg4);

bool func_80044420(s_IpdModelBuffer* modelBuf, s16 arg1, s16 arg2, q23_8 x, q23_8 z);

/** Loads anim file? */
void Anim_BoneInit(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

s_AnimInfo* func_80044918(s_ModelAnim* anim);

void Anim_BoneUpdate(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, q19_12 alpha);

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

q19_12 Anim_DurationGet(s_Model* model, s_AnimInfo* anim);

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
void func_80044F14(GsCOORDINATE2* coord, s16 z, s16 x, s16 y);

s8 Bone_ModelIdxGet(s8* ptr, bool arg1);

/** Skeleton setup? Assigns bones pointer for the skeleton and resets fields. */
void Skeleton_Init(s_Skeleton* skel, s_Bone* bones, u8 boneCount);

/** Clears skeleton bone flags/mask. Called by `Skeleton_Init`. */
void func_80045014(s_Skeleton* skel);

/** Anim func. Used in tandem with skeleton bone traversal. */
void func_8004506C(s_Skeleton* skel, s_LmHeader* lmHdr);

/** Anim func. */
void func_80045108(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2, s32 arg3);

/** Anim func. */
void Skeleton_BoneModelAssign(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2);

/** Anim func. Param names are rough. */
void func_80045258(s_Bone** boneOrd, s_Bone* bones, s32 boneIdx, s_LmHeader* lmHdr);

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

void func_80045534(s_Skeleton* skel, GsOT* ot, void* arg2, GsCOORDINATE2* coord, s16 arg4, u16 arg5, s_FsImageDesc* images);

/** Passes a command to the sound driver. Plays SFX among other things. */
void Sd_EngineCmd(u32 cmd);

/** Sound func? */
u8 func_80045B28();

u16 func_80045BC8();

/** Sound func. */
void func_80045BD8(u16 cmd);

void func_80045D28(u8 isStereo);

void sd_init();

void sd_work_init();

u8 Sd_PlaySfx(u16 sfx, s8 balance, u8 vol);

/** SFX func. */
void func_800463C0(u16 sfx, s8 balance, u8 vol, s8 pitch);

/** SFX func. */
void func_80046620(u16 sfx, s8 balance, u8 vol, s8 pitch);

/** Sound command func. Unknown category. */
void func_800468EC();

/** SFX func. */
void func_8004690C(u16 sfx);

/** Sound command func. Unknown category. */
void func_8004692C(u16 cmd);

void func_800469AC();

void func_800469E8();

/** Sound command func. Unknown category. */
void func_80046A24(u16 cmd);

void func_80046A70();

void func_80046AD8();

void func_80046B04();

/** Sound command func. Unknown category. */
void func_80046B78();

u8 func_80046BB4(u8 arg0);

void func_80046C54(u8 arg0, u8 vol);

/** Sound command func. Unknown category. */
void func_80046D3C(u16 cmd);

s32 func_80046DCC(s32 idx);

void func_80046E00();

void func_8004729C(u16 arg0);

void func_800472BC(s32 arg0);

void func_80047308();

void func_8004760C();

/** Args are volume levels. */
void Sd_SetVolume(u8 arg0, s16 arg1, u8 arg2);

/** Sound func. */
void func_800478DC(u8 cmd);

void func_80047A70();

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

/** Sound func. */
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

/** Boolean. */
u8 func_80048954(s32 com, u8* param, u8* res);

void func_8004C564(u8, s32);

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

void GameFs_UniqueItemModelLoad(u8 itemId);

void GameFs_MapItemsTextureLoad(s32 mapId);

void func_800546A8(u8 weaponId);

void func_8005487C(s32);

void func_80054A04(u8 arg0);

bool Gfx_PickupItemAnimate(u8 itemId);

/** @brief Calculates the ammo needed to reload the equipped gun.
 * @param `currentAmmo` pointer to the variable holding the current amount of loaded ammunition of the equipped weapon.
 * @param `availableAmmo` pointer to the variable holding the current amount of available ammunition for the equipped weapon.
 * @param `gunIdx` Index of the gun being reloaded. `e_EquippedWeaponId`.
 */
void Items_AmmoReloadCalculation(s32* currentAmmo, s32* availableAmmo, u8 gunIdx); // 0x80054FC0

void func_80055028();

void func_800550D0();

void func_80055330(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

void Gfx_FogParamsSet(u8 fogEnabled, u8 fogColorR, u8 fogColorG, u8 fogColorB);

void func_800553E0(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);

/** `arg0` type assumed. */
void func_80055434(VECTOR3* vec);

s32 func_8005545C(SVECTOR* vec);

s32 func_80055490(SVECTOR* arg0);

void func_800554C4(s32 arg0, s16 arg1, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1, SVECTOR* svec, s32 x, s32 y, s32 z, s_WaterZone* waterZones);

void func_80055648(s32 arg0, SVECTOR* arg1);

s32 func_800557DC();

void func_80055814(s32 arg0);

u8 func_80055A50(s32 arg0);

void func_80055A90(CVECTOR* arg0, CVECTOR* arg1, u8 arg2, s32 arg3);

/** @brief Applies uniform lighting and fog shading to `color`, outputting to `result`.
 * The fog factor is derived from `arg2` via `D_800C4168.field_CC` and blends the lit color toward the far/fog color in `D_800C4168.field_1C/field_1D/field_1E`,
 * with lighting strength from `D_800C4168.field_20` applied equally on all axes.
 */
void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2);

void func_80055C3C(CVECTOR* result, CVECTOR* color, void* arg2, void* arg3, s32 arg4, s32 arg5);

u8 func_80055D78(void*, void*, s32);

void func_80055E90(CVECTOR* color, u8 fadeAmount);

void func_80055ECC(CVECTOR* color, SVECTOR3* arg1, SVECTOR3* arg2, MATRIX* mat);

u8 func_80055F08(SVECTOR3* arg0, SVECTOR3* arg1, MATRIX* mat);

void LmHeader_FixOffsets(s_LmHeader* lmHdr);

void ModelHeader_FixOffsets(s_ModelHeader* modelHdr, s_LmHeader* lmHdr);

void func_80056244(s_LmHeader* lmHdr, bool unkFlag);

s32 Lm_MaterialCount(bool (*filterFunc)(s_Material* mat), s_LmHeader* lmHdr);

/** TODO: Unknown `arg3` type. */
void func_80059D50(s32 arg0, s_ModelInfo* modelInfo, MATRIX* mat, void* arg3, GsOT_TAG* arg4);

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

void Texture_Init1(s_Texture* tex, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY);

void Texture_RefCountReset(s_Texture* tex);

/** @unused */
void func_8005B378(s_Texture* tex, char* arg1);

void Texture_Init0(s_Texture* tex);

void Material_TimFileNameGet(char* filename, s_Material* mat);

void func_8005B424(VECTOR3* vec0, VECTOR3* vec1);

/** @unused No references. */
void func_800563E8(s_LmHeader* lmHdr, s32 arg1, s32 arg2, s32 arg3);

void Lm_MaterialFileIdxApply(s_LmHeader* lmHdr, s32 fileIdx, s_FsImageDesc* image, s32 arg3);

void func_80056504(s_LmHeader* lmHdr, char* newStr, s_FsImageDesc* image, s32 arg3);

bool Lm_MaterialFsImageApply(s_LmHeader* lmHdr, char* fileName, s_FsImageDesc* image, s32 arg3);

void Material_FsImageApply(s_Material* mat, s_FsImageDesc* image, s32 arg2);

void func_800566B4(s_LmHeader* lmHdr, s_FsImageDesc* images, s8 unused, s32 startIdx, s32 arg4);

/** Unknown `arg4` type. */
void Lm_MaterialsLoadWithFilter(s_LmHeader* lmHdr, s_ActiveTextures* activeTexs, bool (*filterFunc)(s_Material* mat), s32 fileIdx, s32 arg4);

/** Checks if LM textures are loaded? */
bool LmHeader_IsTextureLoaded(s_LmHeader* lmHdr);

void Lm_MaterialFlagsApply(s_LmHeader* lmHdr);

void Model_MaterialFlagsApply(s_ModelHeader* modelHdr, s32 arg1, s_Material* mat, s32 flags);

void Lm_MaterialRefCountDec(s_LmHeader* lmHdr);

s32 LmHeader_ModelCountGet(s_LmHeader* lmHdr);

void Bone_ModelAssign(s_Bone* bone, s_LmHeader* lmHdr, s32 modelHdrIdx);

bool Lm_ModelFind(s_WorldObject_0* arg0, s_LmHeader* lmHdr, s_WorldObject_0_10* arg2);

void StringCopy(char* prevStr, char* newStr);

void func_80056D8C(s16, s16, s16, s16, s32, s32, GsOT*, void*);

void func_80057090(s_ModelInfo* modelInfo, GsOT* otTag, void* arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5);

s32 func_800571D0(u32 arg0);

void func_80057228(MATRIX* mat, s32 alpha, SVECTOR* arg2, VECTOR3* arg3);

/** TODO: Unknown `arg2` type. */
void func_80057344(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat);

void func_800574D4(s_MeshHeader* meshHdr, s_GteScratchData* scratchData);

void func_8005759C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 vertOffset, s32 normalOffset);

void func_80057658(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4);

void func_80057A3C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec);

/** `arg4` unused. */
s_Texture* Texture_Get(s_Material* mat, s_ActiveTextures* activeTexs, void* fsBuf9, s32 fileIdx, s32 arg4);

void func_8005B55C(GsCOORDINATE2* coord);

u32 func_8005C478(s16* arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2);

s32 func_8005C7D0(s_SubCharacter* chara);

void func_8005C814(s_SubCharacter_D8* arg0, s_SubCharacter* chara);

s32 func_8005C944(s_SubCharacter* chara, s_800C4590* arg1);

s32 func_8005D86C(s32 arg0);

/** Looks like a clamping function. */
s32 func_8005D974(s32 arg0);

s32 func_8005D9B8(VECTOR3* arg0, s32 arg1);

/** Spatial SFX func? */
void func_8005DC1C(s32 sfx, const VECTOR3* pos, s32 vol, s32 soundType); // Types assumed.

/** Spatial SFX func? */
void func_8005DC3C(s32 sfx, const VECTOR3* pos, s32 vol, s32 soundType, s32 pitch);

/** Spatial SFX func? */
void func_8005DD44(s32 sfx, VECTOR3* pos, s32 vol, s8 pitch); // Types assumed.

/** Checks `field_8` in collision struct. */
bool func_8005F680(s_Collision* coll);

/** Spatial SFX func? */
void func_8005DE0C(s32 sfx, VECTOR3*, s32, s32, s32); // Types assumed.

/** Something related to events of the map and loading of textures? */
void Map_EffectTexturesLoad(s32 mapIdx);

void func_8005E70C();

s32 func_8005E7E0(s32 arg0);

void func_8005E89C();

void func_8005F6B0(s_SubCharacter*, VECTOR*, s32, s32);

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
s16 func_8008CDBC(s16 angle);

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, const s_DmsKeyframeCamera* frame0, const s_DmsKeyframeCamera* frame1, s32 alpha);

void func_8008D1D0(s32* prevKeyframe, s32* nextKeyframe, s32* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr);

u32 Dms_IntervalStatusGet(s32 time, s_DmsHeader* dmsHdr);

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry);

s32 Math_LerpFixed12(s16 from, s16 to, s32 alpha);

void func_8008D41C();

void func_8008D438();

void func_8008D448();

void func_8008D454();

void func_8008D464();

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s_WaterZone* waterZones);

void func_8008D5A0(VECTOR3* arg0, s16 arg1);

s32 func_8008D8C0(s16 x0, s32 x1, s32 x2);

void func_8008D990(s32, s32, VECTOR3*, s32, s32);

/** @brief Gets the water zone at a given position.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @param waterZones Water zones to query.
 * @return Water zone at the given position.
 */
s_WaterZone* Map_WaterZoneGet(q27_4 posX, q27_4 posZ, s_WaterZone* waterZones);

void func_8008E5B4(void);

void func_8008E794(VECTOR3* arg0, s16 angle, s32 arg2);

void func_8008EA68(SVECTOR*, VECTOR3*, s32);

void func_80085D78(bool arg0);

void func_80085DC0(bool arg0, s32 sysStateStep);

void func_80085DF0();

void func_80085E6C(s32 delay, bool arg1);

void func_80085EB8(u32 arg0, s_SubCharacter* chara, s32 arg2, bool arg3);

void func_8008605C(s32 arg0, s32 arg1, s32 arg2, bool arg3);

/** TODO: Detailed doc here.
 * Enry arguments correspond to selectable dialog menu entries.
 */
void MapMsg_DisplayAndHandleSelection(bool hasSelection, s32 mapMsgIdx, s32 entry0, s32 entry1, s32 entry2, bool arg5);

/** Handles giving the player items. */
void func_8008616C(s32 arg0, bool arg1, s32 arg2, s32 fadeTimestep, bool arg4);

void func_800862F8(s32 arg0, s32 fileIdx, bool arg2);

void func_80086470(u32 switchVar, s32 arg1, s32 arg2, bool arg3);

void func_800865FC(s32 arg0, s32 idx0, s32 idx1, s16 arg3, s32 arg4, s32 arg5);

void func_800866D4(s32 arg0, s32 arg1, s32 arg2);

void func_80086728(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2);

void func_800867B4(s32 caseParam, s32 idx);

void func_800868DC(s32 idx);

void func_800869E4(s32 mapMsgIdx, u8* arg1, u16* arg2);

void Camera_TranslationSet(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCam);

void Camera_RotationSet(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
                        s32 xAngularAccel, s32 yAngularAccel, s32 xAngularSpeedMax, s32 yAngularSpeedMax, bool warpLookAt);

void func_80086C58(s_SubCharacter* chara, s32 arg1);

void func_80086D04(s_SubCharacter* chara);

void func_80086DA8(s32 fileIdx, s32 fadeTimestep);

void func_80086E50(s32 fileIdx, s32 fadeTimestep0, s32 fadeTimestep1);

void func_80086F44(s32 fadeTimestep0, s32 fadeTimestep1);

void func_80086FE8(s32 mapMsgIdx, s32 sfx, VECTOR3* pos);

void func_8008716C(s32 itemId, s32 fadeTimestep0, s32 fadeTimestep1);

void func_80087360(s32 fileIdx, s32 fadeTimestep0, s32 fadeTimestep1, s32 mapMsgIdx);

void func_80087540(s32 fileIdx, s32 fadeTimestep0, s32 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1);

void Event_ItemTake(s32 itemId, s32 itemCount, s32 eventFlagIdx, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, s32 eventFlagIdx);

void Event_MapTake(s32 mapFlagIdx, s32 eventFlagIdx, s32 mapMsgIdx);

void func_80087EA8(s32 cmd);

void func_80087EDC(s32 arg0);

void func_80088028();

void func_80088048();

void func_800880F0(s32 arg0);

void func_800881B8(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

/** `arg5` could be a pointer.
 * `func_8003D6E0` uses this function and in the last argument
 * it input `arg5` and `arg5` is an undetermined function pointer
 */
bool Chara_Load(s32 modelIdx, s8 charaId, GsCOORDINATE2* coord, s8 flags, s_LmHeader* lmHdr, s_FsImageDesc* tex);

bool func_80088D0C();

void func_80088D34(s32 idx);

s32 Chara_Spawn(s32 charaId, s32 arg1, s32 posX, s32 posZ, s16 posY, u32 stateStep);

void func_80088F94(s_SubCharacter* chara, s32 unused1, s32 unused2);

void func_80088FF4(e_CharacterId charaId, s32 spawnIdx, s32 spawnFlags);

bool func_8008F434(s32 arg0);

/** Might retrun `bool`. */
void func_80089090(s32 arg0);

void func_800890B8();

s32 func_80089128();

void func_800892A4(s32 idx);

void func_800892DC(s32 idx, u8 arg1);

void func_80089314(s32 arg0);

void func_800893D0(q19_12 arg0);

void func_8008944C();

void func_80089470();

void func_80089494();

void func_800894B8(s32 arg0);

void func_800894DC();

void func_80089500();

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

s32 func_8008A0CC(); /** Returns 0. */

s64 func_8008A0D4(void); /** Returns 0. */

s32 func_8008A0E4(s32 arg0, e_EquippedWeaponId weaponId, s_SubCharacter* chara, s_PlayerCombat* combat, s32 arg4, s16 arg5, s16 arg6);

u8 func_8008A270(s32 idx);

s32 func_8008A35C(s_800AD4C8* arg0, s32 arg1);

void func_8008A384(s_SubCharacter* chara);

void func_8008A398(s_SubCharacter* chara);

void func_8008A3AC(s_SubCharacter* chara);

void func_8008B15C(s_SubCharacter* chara);

void func_8008B1DC(s_SubCharacter*, s32, s32);

void func_8008B398();

void func_8008B3E4(s32 arg0);

void func_8008B40C(s32 arg0, s32 arg1);

/** `arg0` is boolean. */
void func_8008B438(s32 arg0, s32 arg1, s32 arg2);

void func_8008B664(VECTOR3* pos, u32 caseVar);

s32 func_8008D850();

void func_8008E4EC(s_LmHeader* lmHdr);

void func_8008D78C();

void func_80091380();

// TODO: Arrange these in address order for better insight into the original interface. -- Sezz
// ------------------------------------------------------------------

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

/** Loads `Tim00` graphic. */
void GameFs_Tim00TIMLoad();

void GameFs_MapItemsModelLoad(u32 mapId);

void ActiveTextures_CountReset(s_ActiveTextures* activeTexs);

void ActiveTextures_PutTextures(s_ActiveTextures* activeTexs, s_Texture* texs, s32 texIdx);

s_Texture* ActiveTextures_FindTexture(char* texName, s_ActiveTextures* activeTexs);

/** Sets the debug string position. */
void func_8005BF0C(s16 unused, s16 x, s16 y);

/** Angle func. */
q3_12 func_8005BF38(q3_12 angle);

s16 func_8005C7B0(s32 arg0);

/** `arg0` type assumed. */
void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3);

void func_8006342C(s32 invItemId, s16, s16, GsCOORDINATE2*);

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, s16 x, s16 z);

void func_800622B8(s32 arg0, s_SubCharacter* chara, s32 animStatus, s32 arg3);

void func_80064F04(VECTOR3* arg0, s8 arg1, s16 arg2);

void func_80066D90();

void func_80066E40();

void func_80066E7C();

bool func_80068CC0(s32 arg0);

void func_800697EC();

u16 func_80069810();

void func_80069820(u16 arg0);

void func_8006982C(u16 arg0);

void func_80069844(s32 arg0);

void func_80069860(s32 arg0, s32 arg1, s_func_8006F8FC* arg2);

void IpdCollData_FixOffsets(s_IpdCollisionData* collData);

void func_80069994(s_IpdCollisionData* collData);

void func_800699E4(s_IpdCollisionData* collData);

void Collision_Get(s_Collision* coll, s32 posX, s32 posZ);

s32 func_80069B24(s_800C4590* arg0, VECTOR3* pos, s_SubCharacter* chara);

s32 func_80069BA8(s_800C4590* arg0, VECTOR3* pos, s_SubCharacter* chara, s32 arg4);

void func_80069DF0(s_800C4590* arg0, VECTOR3* pos, s32 arg2, s32 arg3);

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* pos, s_SubCharacter* chara);

void func_8006A178(s_800C4590* arg0, q19_12 posX, q19_12 posY, q19_12 posZ, q19_12 heightY);

s_SubCharacter** func_8006A1A4(s32* charaCount, s_SubCharacter* chara, bool arg2);

s32 func_8006A3B4(s32 arg0, VECTOR* pos, s_func_8006AB50* arg2);

s32 func_8006A42C(s32 arg0, VECTOR3* pos, s_func_8006AB50* arg2);

s32 func_8006A4A8(s_800C4590* arg0, VECTOR3* pos, s_func_8006AB50* arg2, s32 arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount);

void func_8006A940(VECTOR3* pos, s_func_8006AB50* arg1, s_SubCharacter** charas, s32 charaCount);

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* vec, s_func_8006AB50* arg2, s32 arg3);

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* vec, s_func_8006AB50* arg2);

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
void func_8006BCC4(s_func_8006CC44_44* arg0, s8* arg1, u32 arg2, s16 arg3, s16 arg4, s16 arg5);

void func_8006BDDC(s_func_8006CC44_44_0* arg0, s16 arg1, s16 arg2);

void func_8006BE40(s_func_8006CC44* arg0);

void func_8006BF88(s_func_8006CC44* arg0, SVECTOR3* arg1);

void func_8006C0C8(s_func_8006CC44*, s16, s16);

bool func_8006C1B8(u32 arg0, s16 arg1, s_func_8006CC44* arg2);

s16 func_8006C248(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

bool func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx);

void func_8006C45C(s_func_8006CC44* arg0);

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 arg2);

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

bool func_8006D90C(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2);

bool func_8006DA08(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2, s_SubCharacter* chara);

void func_8006DAE4(s_func_800700F8_2* arg0, VECTOR3* pos, VECTOR3* offset, s32 arg3);

bool func_8006DB3C(s_func_800700F8_2* arg0, VECTOR3* pos, VECTOR3* offset, s_SubCharacter* chara);

bool func_8006DC18(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2);

bool func_8006DCE0(s_func_8006DCE0* arg0, s32 arg1, s16 arg2, VECTOR3* pos, VECTOR3* offset, s32 arg5, s32 arg6, s_SubCharacter** charas, s32 charaCount);

bool func_8006DEB0(s_func_800700F8_2* arg0, s_func_8006DCE0* arg1);

void func_8006E0AC(s_func_8006DCE0* arg0, s_IpdCollisionData* ipdColl);

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2);

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ);

void func_8006E53C(s_func_8006DCE0* arg0, s_IpdCollisionData_20* arg1, s_IpdCollisionData* arg2);

void func_8006E78C(s_func_8006DCE0* arg0, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4);

void func_8006EB8C(s_func_8006DCE0* arg0, s_IpdCollisionData_18* arg1);

void func_8006EE0C(s_func_8006DCE0_6C* arg0, s32 arg1, s_SubCharacter* arg2);

void func_8006EEB8(s_func_8006DCE0* arg0, s_SubCharacter* arg1);

void func_8006F250(s_func_8006F250* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8006F338(s_func_8006F338* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

bool func_8006F3C4(s_func_8006F338* arg0, s_func_8006F8FC* arg1);

/** Translates something. */
s32 func_8006F620(VECTOR3* pos, s_func_8006AB50* arg1, s32 arg2, s32 arg3);

void func_8006F8FC(s32* outX, s32* outZ, s32 posX, s32 posZ, const s_func_8006F8FC* arg4);

q3_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle);

/** Creates random angle of some kind. */
q7_8 func_8006FAFC(s_SubCharacter* chara, s32 dist, s32 arg2, s32 arg3, s16 arg4, s32 arg5);

bool func_8006FD90(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3);

bool func_80070030(s_SubCharacter* chara, q19_12 x, q19_12 y, q19_12 z);

bool func_80070084(s_SubCharacter* chara, q19_12 x, q19_12 y, q19_12 z);

bool func_800700F8(s_SubCharacter* chara0, s_SubCharacter* chara1);

bool func_80070184(s_SubCharacter* chara, s32 arg1, s16 rotY);

bool func_80070320();

s32 func_80070360(s_SubCharacter* chara, s32 someDist, s16 arg2);

void func_80070400(s_SubCharacter* chara, s_func_80070400_1* arg1, s_func_80070400_1* arg2);

bool func_80070208(s_SubCharacter* chara, q19_12 dist);

s32 func_8007029C(s_SubCharacter* chara, q19_12 arg1, q3_12 angle);

void func_800705E4(GsCOORDINATE2* coord, s32 idx, s32 scaleX, s32 scaleY, s32 scaleZ);

void func_8007D6E0();

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2);

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

void Settings_RestoreControlDefaults(s32 arg0);

void nullsub_800334C8();

// Possibly related to save functionallity.
s32 func_800334D8(s32 idx);

bool func_80033548();

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SavegameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SavegameReadPlayer();

s32 MainLoop_ShouldWarmReset();

void Game_WarmBoot();

/** Handles `g_GameWork.gameStateStep_598[0]`.
 * Used to handle map loading and room changes.
 */
void GameFs_MapStartup(); // 0x80034964

/** Draws the loading screen with Harry running. */
void Gfx_LoadingScreenDraw(); // 0x80034E58

void func_80034EC8(); // 0x80034EC8

void func_80034F18(); // 0x80034F18

/** Crucial for getting in-game.
 * Removing it breaks the camera, inventory's 3D elements, effects
 * (lighting, fog, lens flare, etc.), NPCs don't spawn, and
 * doing any action unrelated to aiming a weapon or interacting
 * with the environment crashes the game.
 */
void Game_InGameInit(); // 0x80034FB8

void Game_SavegameInitialize(s8 overlayId, s32 difficulty);

void Game_PlayerInit(); // 0x80035178

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

bool func_8003528C(s32 idx0, s32 idx1);

/** Searches for the index of the character animation data in `D_800A992C`. */
s32 func_800352F8(s32 charaId);

/** Either allocates or determines where to allocate animation data. */
void func_80035338(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coords);

/** Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord);

void func_8003569C();

s32 func_80035780();

/** Sets sound command. */
bool func_800358A8(s32 cmd);

void func_800358DC(s32 cmd);

/** Executes sound command. */
void func_80035924();

void func_8003596C();

s32 func_8003599C();

s32 func_80035AB0(s32 arg0);

void func_80035AC8(s32 idx);

/** Related to NPC and player movement? */
void func_80035B04(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord);

void func_80035B58(s32 arg0);

void func_80035B98();

/** @unused and broken.
 * Intended to draw a background image when a loading screen with the string "STAGE X-X" appears.
 */
void Gfx_LoadingScreen_BackgroundTexture();

void Gfx_LoadingScreen_PlayerRun();

void func_80035DB4(s32);

void func_80035E1C();

bool func_80035E44();

void func_80035ED0();

void func_80035F4C(s32 arg0, s32 arg1, u8* arg2);

void func_800363D0();

void func_8003640C(s32 arg0);

/** `Savegame_MapRoomIdxSet` */
void Savegame_MapRoomIdxSet();

s32 func_8003647C();

s32 func_80036498();

u32 func_800364BC();

void func_8003652C();

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx);

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1);

void func_80036E48(u16* arg0, s16* arg1);

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124();

void func_80037154();

void func_80037188();

/** Finds the ground hight and warps the player to it? */
void func_80037334();

void func_80037388();

bool func_800378D4(s_AreaLoadParams* areaLoadParams);

bool func_80037A4C(s_AreaLoadParams* areaLoadParams);

bool func_80037C5C(s_AreaLoadParams* areaLoadParams);

void func_80037DC4(s_SubCharacter* chara);

void func_800373CC(s32);

void func_80037E40(s_SubCharacter* chara);

void func_80037E78(s_SubCharacter* chara);

s32 func_800382B0(s32 arg0);

/** @brief Computes the distance between two positions.
 *
 * @param pos0 First position.
 * @param pos1 Second position.
 * @return Distance between positions.
 */
q19_12 Math_DistanceGet(const VECTOR3* pos0, const VECTOR3* pos1);

/** @brief Computes the 2D distance on the XZ plane between two positions.
 *
 * @param pos0 First position.
 * @param pos1 Second position.
 * @return 2D distance between positions.
 */
q19_12 Math_Distance2dGet(const VECTOR3* pos0, const VECTOR3* pos1);

/** @brief Forces a clicked controller input status for `ControllerFlag_Select`. */
void Input_SelectClickSet();

/** @brief Performs a 2D distance check on the XZ plane between two positions.
 *
 * @param pos0 First position.
 * @param pos1 Second position.
 * @param radius Intersection radius.
 * @return `true` if the 2D distance exceeds the radius, `false` otherwise.
 */
bool Math_Distance2dCheck(const VECTOR3* pos0, const VECTOR3* pos1, s32 radius);

/** @brief Computes the squared 2D distance on the XZ plane from the reference position to the camera.
 *
 * @param pos Reference position.
 * @return 2D distance to the camera.
 */
s32 Camera_Distance2dGet(const VECTOR3* pos);

void func_80037F24(s32);

void func_80038354();

void SysState_Gameplay_Update();

void SysState_GamePaused_Update();

void SysState_OptionsMenu_Update();

void func_8003943C();

void SysState_StatusMenu_Update();

void GameState_LoadStatusScreen_Update();

void SysState_MapScreen_Update();

void SysState_Fmv_Update();

void SysState_LoadArea_Update();

void AreaLoad_UpdatePlayerPosition();

void func_80039F54();

s8 func_80039F90();

void SysState_ReadMessage_Update(s32 arg0);

void func_8003A16C();

void SysState_SaveMenu_Update();

void SysState_EventCallFunc_Update();

void SysState_EventSetFlag_Update();

void SysState_EventPlaySound_Update();

void SysState_GameOver_Update();

// ====================
// Main menu functions - TODO: Maybe a split around here?
// ====================

void MainMenu_SelectedOptionIdxReset();

void Gfx_MainMenu_MainTextDraw();

void Gfx_MainMenu_DifficultyTextDraw(s32 arg0);

void Gfx_MainMenu_BackgroundDraw();

void func_8003B7BC();

u32 func_8003B7FC(s32 idx);

PACKET* Gfx_MainMenu_FogPacketGet(GsOT* ot, PACKET* packet);

void Gfx_MainMenu_FogDraw();

void Gfx_MainMenu_FogRandomize();

void Gfx_MainMenu_FogScatter();

void Gfx_MainMenu_FogUpdate();

/** Related to main menu fog. */
void func_8003BCF4();

/** Related to main menu fog. */
void func_8003BE28();

// ====================

s_Bone* func_8003BE50(s32 modelIdx);

void GameFs_BgEtcGfxLoad();

void GameFs_BgItemLoad();

void func_8003BED0();

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
void func_8003C048();

/** Something related to player model loading. */
void func_8003C0C0();

/** Allocates player model? */
void func_8003C110();

void CharaModel_Free(s_CharaModel* model);

/** @unused */
void Ipd_ActiveChunksClear1();

void func_8003C30C();

void WorldGfx_IpdSamplePointStore();

void WorldGfx_IpdSamplePointReset();

/** Handles player movement. */
void func_8003C3AC();

void func_8003C878(s32);

void func_8003CB3C(s_WorldGfx* worldGfx);

void func_8003CB44(s_WorldGfx* worldGfx);

void func_8003CBA4(s_WorldObject* obj);

void func_8003CC7C(s_WorldObject_0* arg0, MATRIX* arg1, MATRIX* arg2);

void func_8003D354(s32* arg0, s32 charaId);

/** Texture UV setup for NPCs. */
void func_8003D3BC(s_FsImageDesc* image, s32 groupIds, s32 modelIdx);

s32 func_8003D7D4(u32 charaId, s32 modelIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

/** Something related to animations. */
void func_8003D938();

void func_8003D95C();

void func_8003D9C8(s_CharaModel* model);

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

void func_8003E5E8(s32 arg0);

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad();

void func_8003EB54();

void func_8003EBF4(s_MapOverlayHeader* arg0);

void func_8003EBA0();

void func_8003ECBC();

void func_8003ECE4();

void func_8003ED08();

u32 func_8003ED64();

void func_8003EDA8();

void func_8003EDB8(CVECTOR* color0, CVECTOR* color1);

void func_8003EE30(s32 arg0, s8* arg1, s32 arg2, s32 arg3);

void func_8003EEDC(s32 arg0, s32 arg1);

void func_8003EF74(s_sub_StructUnk3* arg0, s_sub_StructUnk3* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_8003F08C(s_StructUnk3* arg0, s_sub_StructUnk3* arg1);

void func_8003F170();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SavegameResetPlayer();

void func_8007E5AC();

void func_8007E860();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_80070B84(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3);

void func_80070DF0(s_MainCharacterExtra* extra, s_SubCharacter* chara, s32 arg2, s32 animStatus);

// Variable anim duration func for player. It's nearly completely matched https://decomp.me/scratch/PBvwU.
s32 func_800706E4();

/** Special player SFX handler for heavy breath and damage. */
bool func_80071620(u8 animStatus, s_SubCharacter*, s32, s32 sfx);

void func_8007C0D8(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

void func_8007D090(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord);

/** Player func. */
void func_8007E9C4();

/** Sound func. */
void func_8007F14C(u8 arg0);

void func_8007FB94(s_SubCharacter*, s_MainCharacterExtra*, s32);

void func_8007FD4C(s32);

/** Resets several global variables to 0. */
void func_8007F1CC();

void func_8007F250(u8* ptr, s8 disableDamage);

/** Some kind of player anim state check. */
bool func_8007F26C();

/** Some kind of player anim state check. */
bool func_8007F2AC();

/** Gets something from the player's current animation? */
s16 Player_AnimGetSomething();

/** @brief Computes the shortest angle between `angleFrom` and `angleTo`, outputting the result to `shortestAngle`.
 *
 * @param angleFrom First angle in Q3.12, range `[0, 4096]`.
 * @param angleTo Second angle in Q3.12, range `[0, 4096]`.
 * @param shortestAngle Shortest angle output in Q3.12, range `[0, 4096]`.
 */
void Math_ShortestAngleGet(s16 angleFrom, s16 angleTo, s16* shortestAngle);

/** Anim func. */
void func_8007FB94(s_SubCharacter* chara, s_MainCharacterExtra* extra, s32 animStatus);

/** Anim func. */
void func_8007FC48(s_SubCharacter* chara, s_MainCharacterExtra* extra, s32 animStatus);

/** Gets property 8 from player. */
s32 func_8007FD2C();

/** @unused Gets current value from the power timer for gas based weapons. */
q19_12 Game_GasWeaponPowerTimerValue();

void func_8007FD4C(s32 arg0);

/** Returns data in last 3 pointer args. Outputs? */
void func_8007FDE0(s8, s32* sfx, s8* pitch0, s8* pitch1);

s32 func_80080478(const VECTOR3* pos0, const VECTOR3* pos1);

/** Generates a random angle? */
s32 func_80080514(void);

/** Computes (abs(value) - subtractor) * copysign(value). */
s32 Math_PreservedSignSubtract(s32 val, s32 subtractor);

void func_800805BC(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* rootCoord, s32 arg3);

bool func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // arg3 type assumed.

/** Probably returns `bool`. */
bool func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** Fills special collision global with collision data. */
void func_8008076C(s32 posX, s32 posZ);

/** Returns ground height? */
s32 func_80080884(s32 posX, s32 posZ);

s32 func_800808AC(s32 posX, s32 posZ);

/** Returns a Q shift based on a magnitude. */
s32 Math_MagnitudeShiftGet(s32 mag);

s32 func_80080A10();

u8 func_8008A2E0(s32 arg0);

void func_800348C0();

void GameState_Boot_Update();
void GameState_StartMovieIntro_Update();
void GameState_DeathLoadScreen_Update();
void GameState_MovieIntroAlternate_Update();
void GameState_MovieIntro_Update();
void GameState_MainMenu_Update();
void GameState_MovieOpening_Update();
void GameState_LoadScreen_Update();
void GameState_InGame_Update();
void GameState_MapEvent_Update();
void GameState_ExitMovie_Update();
void GameState_ItemScreens_Update();
void GameState_MapScreen_Update();
void GameState_SaveScreen_Update();
void GameState_DebugMoviePlayer_Update();
void GameState_Options_Update();
void GameState_LoadMapScreen_Update();
void GameState_Unk15_Update();

void Game_TurnFlashlightOn();
void Game_TurnFlashlightOff();
#endif
