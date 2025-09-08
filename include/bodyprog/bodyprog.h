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

// ========
// DEFINES
// ========

#define OPT_SOUND_VOLUME_MIN   0
#define OPT_SOUND_VOLUME_MAX   128
#define OPT_VIBRATION_DISABLED 0
#define OPT_VIBRATION_ENABLED  128

#define IPD_HEADER_MAGIC       20  // 0x14 / 20
#define PLM_HEADER_MAGIC       '0' // 0x30 / 48 / '0'

// ======
// ENUMS
// ======

typedef enum _SpeedZoneType
{
    SpeedZoneType_Slow   = 0,
    SpeedZoneType_Normal = 1,
    SpeedZoneType_Fast   = 2,
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
    s32               objectCount_8;
    struct TMD_STRUCT objects_C[1];
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

/** Returned by `func_800699F8`. Probably contains 2D point collision. */
typedef struct _s_func_800699F8
{
    q19_12 groundHeight_0;
    s16    field_4;
    s16    field_6;
    s8     field_8;
    u8     unk_9[3];
} s_func_800699F8;
STATIC_ASSERT_SIZEOF(s_func_800699F8, 12);

typedef struct
{
    VECTOR3  position_0;
    SVECTOR3 rotation_C;
    s8       field_12;
} s_func_8006AB50;

typedef struct
{
    s32     field_0;
    s32     field_4;
    s32     field_8; // 2D distance.
    SVECTOR field_C;
    s16     directionX_14;
    s16     directionZ_16;
    q23_8   positionX_18;
    q23_8   positionZ_1C;
    s32     field_20;
    s32     field_24;
    s16     field_28; // } `SVECTOR3`, packed rotation?
    s16     field_2A; // }
    s16     field_2C; // }
} s_func_8006ABC0;

typedef struct
{
    s16 field_0;
    u8  unk_2[2];
    s16 field_4;
} s_func_8006B1C8;

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
    u8  field_0;
    u8  field_1;
    u16 field_2;
    s32 field_4;
} s_func_8006CC44_A8;

typedef union
{
    s16 field_0;
    struct
    {
        u8 field_0;
        u8 field_1;
    } s_field_0;
} u_func_8006CC44_D8;

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
    s16                field_3C;
    s16                field_3E;
    s8                 unk_40[4];
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
    s32                field_80; // X
    s32                field_84; // Z
    s32                field_88; // X
    s32                field_8C; // Z
    s32                field_90; // `bool`?
    s32                field_94;
    s16                field_98;
    s16                field_9A;
    s16                field_9C;
    s16                field_9E;
    u8                 field_A0;
    u8                 field_A1;
    u8                 field_A2;
    u8                 field_A3;
    s_func_8006CA18*   field_A4;
    s_func_8006CC44_A8 field_A8[4];
    u8                 field_C8;
    u8                 unk_C9[1];
    s16                field_CA;
    s32                field_CC; // TODO: This is a `s_IpdCollisionData` pointer.
    u8                 field_D0;
    s8                 field_D1;
    u16                field_D2;
    s16                field_D4;
    s16                field_D6;
    u_func_8006CC44_D8 field_D8;
    u8                 field_DA;
    u8                 field_DB;
    u8                 field_DC;
    u8                 field_DD;
    s16                field_DE;
    s16                field_E0;
    u8                 unk_E2[2];
    s16                field_E4;
    s16                field_E6;
    u8                 unk_E8[4];
    s16                field_EC;
    s16                field_EE;
    s16                field_F0;
    s16                field_F2;
    u8                 field_F4;
    u8                 unk_F5[3];
    s32                field_F8;
    u16                field_FC;
    u8                 unk_FE[2];
    s16                field_100;
    s16                field_102;
    // TODO: May be incomplete. Maybe not, added the final padding based on `func_800699F8`
} s_func_8006CC44;

typedef struct
{
    s32      field_0;
    s16      field_4;
    s16      field_6;
    s16      field_8;
    s8       unk_A[2];
    s8       unk_C[20];
    s32      field_20;
    s8       unk_24[8];
    VECTOR3  field_2C; // Q23.8
    s8       unk_38[4];
    s32      field_3C;
    s32      field_40;
    s32      field_44;
    s8       unk_48[4];
    s16      field_4C;
    s16      field_4E;
    SVECTOR3 field_50; // Q23.8
    u16      field_56;
    s16      field_58;
    s16      field_5A;
    s16      field_5C;
    s16      field_5E;
    s16      field_60;
    s8       unk_62[2];
    s32      field_64;
    s32      field_68;
    s32      field_6C;
    s32      field_70;
    s16      field_74;
    s16      field_76;
    s16      field_78;
    s16      field_7A;
    s32      field_7C;
    s32      field_80;
    u16      field_84;
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
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2C;
} s_func_8006F338;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_func_8006E490_20;

typedef struct
{
    s8                 unk_0[16];
    s32                field_10;
    s32                field_14;
    s8                 unk_18[4];
    s32                field_1C;
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

typedef struct _ObjNormal
{
    s8 nx;
    s8 ny;
    s8 nz;
    u8 count;
} s_ObjNormal;
STATIC_ASSERT_SIZEOF(s_ObjNormal, 4);

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

    s_ObjNormal field_3A0;

    DVECTOR  screenPos_3A4;
    s32      depthP_3A8;
    SVECTOR  field_3AC;
    u8       unk_3B4[36];
    CVECTOR  field_3D8; // Written by `func_8005A42C`.
    DVECTOR  screenPos_3DC;
    s32      depthP_3E0;
    MATRIX   field_3E4;
} s_GteScratchData;

typedef struct _ObjPrimitive
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
} s_ObjPrimitive;
STATIC_ASSERT_SIZEOF(s_ObjPrimitive, 20);

typedef struct _ObjHeader
{
    u8 primitiveCount_0;
    u8 vertexCount_1;
    u8 normalCount_2;
    u8 unkCount_3;

    s_ObjPrimitive* primitives_4;
    DVECTOR*        vertexXy_8;
    s16*            vertexZ_C;
    s_ObjNormal*    normals_10;
    u8*             unkPtr_14;
} s_ObjHeader;
STATIC_ASSERT_SIZEOF(s_ObjHeader, 24);

typedef struct _ObjList
{
    u_Filename   objName_0;
    u8           meshCount_8;
    u8           vertexOffset_9;
    u8           normalOffset_A;
    u8           field_B_0 : 1;
    u8           field_B_1 : 3;
    u8           field_B_4 : 2;
    u8           unk_B_6   : 2;
    s_ObjHeader* meshes_C;
} s_ObjList;
STATIC_ASSERT_SIZEOF(s_ObjList, 16);

// Individual texture data.
typedef struct _PlmTexList_8
{
    s_FsImageDesc imageDesc_0;
    u_Filename    textureName_8;
    u32           queueIdx_10;
    s8            field_14;
} s_PlmTexList_8;

typedef struct _PlmTexList
{
    u_Filename      textureName_0;
    s_PlmTexList_8* field_8;
    u8              field_C;
    u8              unk_D[1];
    u8              field_E;
    u8              field_F;
    u16             field_10;
    u16             field_12;
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
} s_PlmTexList;
STATIC_ASSERT_SIZEOF(s_PlmTexList, 24);

typedef struct _PlmHeader
{
    u8            magic_0;
    u8            version_1;
    u8            isLoaded_2;
    u8            textureCount_3;
    s_PlmTexList* textureList_4;
    u8            objectCount_8;
    u8            unk_9[3];
    s_ObjList*    objectList_C;
    u8*           objectOrds_10;

    // File header ends, extra data below.
    // After this goes array of `s_PlmTexList`, `s_ObjList` `objOrder`.
    // See https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/sh1_model.bt
    s8            unk_11[4075];
    s32           queueIdx_1000;
} s_PlmHeader;

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

typedef struct _IpdCollisionData_18
{
    u16 field_0_0  : 5;
    u16 field_0_5  : 3;
    u16 field_0_8  : 4;
    u16 field_0_12 : 3;
    u16 field_0_15 : 1;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    u16 field_8;
} s_IpdCollisionData_18;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_18, 10);

typedef struct _IpdCollisionData
{
    s32                    posX_0;
    s32                    posZ_4;
    u32                    field_8_0  : 8;
    u32                    field_8_8  : 8;
    u32                    field_8_16 : 8;
    u32                    field_8_24 : 8;
    void*                  ptr_C;
    s_IpdCollisionData_10* ptr_10;
    void*                  ptr_14;
    s_IpdCollisionData_18* ptr_18;
    s16                    field_1C;
    u8                     field_1E;
    u8                     field_1F;
    s32*                   ptr_20;   // Might point to `s_func_8006B1C8`?
    u16                    field_24; // `field_24/``field_26` defined in ipd2obj but haven't seen used yet, might be size of `ptr_28`/`ptr_2C`.
    u16                    field_26;
    u8*                    ptr_28;
    void*                  ptr_2C;
    u8                     field_30;
    u8                     unk_31[3];
    u8                     field_34[256];
} s_IpdCollisionData;

typedef struct _IpdModelBuffer_C
{
    s_ObjList* objList_0;
    u8         unk_4[32];
} s_IpdModelBuffer_C;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer_C, 36);

typedef struct _IpdModelBuffer
{
    u8                  field_0; // Count of `field_C` entries.
    u8                  unk_1[3];
    u8                  unk_4[8];
    s_IpdModelBuffer_C* field_C;
    void*               field_10; // Pointer to unknown collision data.
    void*               field_14; // Pointer to unknown collision data.
} s_IpdModelBuffer;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer, 24);

typedef struct _IpdModelInfo
{
    u8         isGlobalPlm_0; // `false` if loaded from inside `IPD`, `true` if loaded from `*_GLB.PLM`.
    u8         unk_1[3];
    u_Filename modelName_4;
    s_ObjList* objList_C;
} s_IpdModelInfo;
STATIC_ASSERT_SIZEOF(s_IpdModelInfo, 16);

typedef struct _IpdHeader
{
    u8                 magic_0;
    u8                 isLoaded_1; /** `bool` */
    s8                 levelGridX_2;
    s8                 levelGridY_3;
    s_PlmHeader*       plmHeader_4;
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
    u16 dataOffset_0;
    u8  rotationBoneCount_2;
    u8  translationBoneCount_3;
    u16 frameDataSize_4; // Size per keyframe, `(rotationBoneCount_2 * 9) + (translationBoneCount_3 * 3)`?
    u8  boneCount_6;
    u8  unk_7;
    u32 activeBones_8; // Holds bit field of bones to update.
    u32 offset_C;      // In ANM files this points to another duplicate `s_AnmHeader` at end of the file, or might just be size of the main ANM data.
    u16 frameCount_10;
    u8  scaleLog2_12;
    u8  rootYOffset_13;

    s_AnmBindPose bindPoses_14[0]; // Array size = `boneCount_6`
} s_AnmHeader;
STATIC_ASSERT_SIZEOF(s_AnmHeader, 20);

// PLM data? Likely `D_800C1158`'s struct.
typedef struct
{
    s_PlmHeader* plmHeader_0;
    s32          fileIdx_4;
    s32          queueIdx_8; // Passed to `Fs_QueueEntryLoadStatusGet`, thus the name.
} s_func_80041CB4;

typedef struct
{
    u8 field_0;
    u8 field_1;
} s_func_800452EC_8;

// Probably Skeleton too.
typedef struct
{
    s8                      unk_0[8];
    s_func_800452EC_8*      field_8;
    s8                      unk_C[4];
    s8                      field_10;
    s8                      unk_11[3];
    struct s_func_800452EC* field_14;
} s_func_800452EC;

// Maybe a collection of matrices.
typedef struct
{
    s32        flags_0;
    s8         unk_4[4];
    s_ObjList* objList_8;
    s32        objListIdx_C;
    s8         field_10;
    s8         unk_11[3];
    s32        field_14;
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 24);

// PROBABLY skeleton data.
typedef struct
{
    u8               boneCount_0;
    u8               boneIdx_1; // Current bone index? Used in traversal.
    s8               field_2;
    s8               field_3;
    s_func_800452EC* field_4;
    s_Bone* bones_8;

    // Maybe incorrect.
    s8                 field_C[4]; // Maybe struct similar to `s_Bone` but smaller.
    u8                 field_10;   // Some count related to bone hierarchy.
    s8                 field_11;
    s8                 field_12;
    s8                 field_13;
    struct s_Skeleton* skeleton_14;
    s8                 unk_18[4];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 28);

typedef struct
{
    s32        field_0;
    u8         unk_4[4];
    s_ObjList* field_8;
    // Likely incomplete.
} s_func_80057344;

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

// Maybe level stream data?
typedef struct
{
    void* destBuffer_0;
    s32   queueEntryIdx_4;
    s16   fileChunkCoordX_8;
    s16   fileChunkCoordZ_A;
    s32   field_C;  // } Something to do with distance from file chunk edge.
    s32   field_10; // }
} s_80043338;

typedef struct
{
    s8             charaId0_0; /** `e_CharacterId`. */
    s8             charaId1_1; /** `e_CharacterId`. */
    s8             unk_2[2];
    s32            animFile0_4;//s_AnmHeader*    animFile0_4; // TODO: Needs to be a pointer.
    s_AnmHeader*   animFile1_8;
    s32            animFileSize1_C;
    s32            animFileSize2_10;
    GsCOORDINATE2* npcCoords_14;
} s_800A992C;
STATIC_ASSERT_SIZEOF(s_800A992C, 24);

typedef struct
{
    u8  field_0;
    u8  unk_1;
    u8  unk_2;
    u8  unk_3;
    u32 field_4    : 24;
    u8  field_4_24 : 8;
    u32 field_8    : 24;
    u8  field_8_24 : 8;
} s_800AA894;
STATIC_ASSERT_SIZEOF(s_800AA894, 12);

typedef struct
{
    u16 field_0;
    u8  unk_2[4];
    s8  field_6;
    s8  unk_7;
    u8  field_8;
    u8  field_9;
    u8  unk_A[4];
    u8  field_E;
    u8  field_F;
    u8  field_10;
    u8  field_11;
    u16 unk_12;  // Guessed.
    u32* unk_14; // Some pointer. All entries have the same value `D_800AD4C4`.
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

typedef struct
{
    VECTOR3         position_0;
    s_func_800699F8 field_C; // Collision data?
    s32             field_18;
} s_800AFC78;

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

typedef struct _SpeedZone
{
    s8 speedIdx_0;
    // 1 byte of padding.
    s16 minX_2; // } Q11.4? Q7.8 fits more cleanly, but `Map_SpeedZoneGet` uses `<< 8` for comparison with Q19.12 input position.
    s16 maxX_4; // }
    s16 minZ_6; // }
    s16 maxZ_8; // }
} s_SpeedZone;

typedef struct _WaterZone
{
    u8  enabled_0;
    // 1 byte of padding.
    s16 illumination_2;
    s16 minX_4; // } Q11.4? Q7.8 fits more cleanly, but a call to `Map_WaterZoneGet` uses `>> 8` with Q19.12 arg position.
    s16 maxX_6; // }
    s16 minZ_8; // }
    s16 maxZ_A; // }
} s_WaterZone;

// Looks similar to `s_Skeleton`
typedef struct
{
    u8            field_0;
    u8            field_1;
    u8            unk_2[2];
    s32           field_4;
    s_PlmHeader*  plmHeader_8;
    s_FsImageDesc texture_C;
    s_Skeleton    field_14; // Could be different struct?
} s_800BCE18_0_CC; // Unknown size.

typedef struct _MapType
{
    s16          plmFileIdx_0;
    char         tag_2[4];
    u8           flags_6;
    // 1 byte of padding.
    s_WaterZone* waterZones_8;
    s_SpeedZone* speedZones_C;
} s_MapType;

typedef struct
{
    s_MapType*        type_0;
    s8                field_4;
    u8                unk_5[3];
    VECTOR3           field_8;               // Position.
    s32               field_14;              // Used frequently as `s_PlmHeader*`, but code adds file lengths to it. Could just be `u8*` pointing to current file data?
    s_800BCE18_0_CC*  field_18[Chara_Count]; // Per-character data? So far only seen accessed by `map4_s03::800D59EC` which calls `func_8003BE50(Chara_Twinfeeler)`.
    s_800BCE18_0_CC   field_CC;
    u8                unk_D0[368];
    s32               field_26C;
    u8                unk_270[752];
} s_800BCE18_0;
STATIC_ASSERT_SIZEOF(s_800BCE18_0, 1376);

typedef struct
{
    char string_0[8];
    s8   field_8;
    s8   field_9;
} s_800BCE18_2BEC_0_10;

typedef struct
{
    s32                   field_0;
    s8                    unk_0[4];
    s_ObjList*            field_8;
    s32                   field_C;
    s_800BCE18_2BEC_0_10  field_10;
} s_800BCE18_2BEC_0;
STATIC_ASSERT_SIZEOF(s_800BCE18_2BEC_0, 28);

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
    s32           itemId_0; /** `e_InventoryItemId` or `e_CutsceneItemId` */
    s32           field_4;
    char*         field_8;
    s_FsImageDesc imageDesc_C;
    s_PlmHeader*  field_14;
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
    s_PlmHeader       field_1BE4;
    s32               field_2BE8;
    s_800BCE18_2BEC   field_2BEC[1]; // Unknown size, valid count determined by `field_2BE8`?
} s_800BCE18;
STATIC_ASSERT_SIZEOF(s_800BCE18, 11260);

// IPD data?
typedef struct
{
    s_IpdHeader* ipdHeader_0;
    s32          queueIdx_4;
    s16          field_8; // X cell coord?
    s16          field_A; // Z cell coord?
    s32          field_C;
    s32          field_10;
    u8           field_14;
    s8           unk_15[3];
    s32          field_18;
} s_800C117C;
STATIC_ASSERT_SIZEOF(s_800C117C, 28);

typedef struct _IpdRow
{
    s16 idx[16];
} s_IpdColumn;
STATIC_ASSERT_SIZEOF(s_IpdColumn, 32);

typedef struct
{
    s32             count_0;
    s_PlmTexList_8* entries_4[10];
} s_800C1450_0;

// Related to textures.
typedef struct
{
    s_800C1450_0   field_0;
    s_800C1450_0   field_2C;
    s_PlmTexList_8 field_58[8];
    s_PlmTexList_8 field_118[2];
} s_800C1450;
STATIC_ASSERT_SIZEOF(s_800C1450, 328);

typedef struct
{
    s_IpdCollisionData field_0;
    s32                field_134;
    s_func_80041CB4    field_138;
    char               mapTag_144[4];
    s32                mapTagSize_148;
    s32                field_14C;
    s_IpdHeader*       field_150;
    s32                field_154;
    s32                ipdTableSize_158;
    s_800C117C         ipdTable_15C[4]; // Temp name. Uses either 2 or 4 fields depending map type.
    s_IpdColumn        ipdGrid_1CC[18];
    s8                 unk_40C[32];     // Could be one extra row in table above.
    s_IpdColumn*       ipdGridCenter_42C;
    s_800C1450         field_430;
    s32                field_578;
    s32                field_57C;
    s32                field_580;
    s32                field_584;
    s32                field_588;
} s_800C1020;
STATIC_ASSERT_SIZEOF(s_800C1020, 1420);

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
    u16 field_0;
    u8  field_2;
    u8  unk_3;
    s32 field_4[20]; // Guessed size.
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
 * Everything is inited to 0xFFFF and some data is written when I get hit by monsters.
 * Might be more generic 'particles / decals' struct
 */
typedef struct _BloodSplat
{
    s16 unk_0; // At this point, maybe its an array of u16?
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
    s32               (*func_134)(s_SubCharacter*);           // Assumed return type.
    s32               (*func_138)(s_SubCharacter*);           // Assumed return type.
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
    s8                charaGroupIds_248[4];                                              /** `e_CharacterId` values where if `s_SpawnInfo.charaId_4` == 0, `charaGroupIds_248[0]` is used for `charaSpawns_24C[0]` and `charaGroupIds_248[1]` for `charaSpawns_24C[1]`. */
    s_SpawnInfo       charaSpawns_24C[2][16];                                            /** Array of character type/position/flags. `flags_6 == 0` are unused slots? Read by `func_80037F24`. */
    VC_ROAD_DATA      roadDataList_3CC[48];
    u32               unk_84C[512];
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 4172); // Size incomplete.

typedef struct
{
    s8 maxIdx_0;
    u8 selectedEntryIdx_1;
    u8 unk_2;
    u8 cancelIdx_3;
} s_MapMsgSelect;

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
    s16  field_1C;
} s_func_800700F8_2;

typedef struct
{
    VECTOR3 field_0;
    s32     field_C; // Y height?
    s16     field_10;
    s16     field_12;
    s8      field_14;
    s8      unk_15[3];
    s32     field_18;
} s_800C4590;

typedef struct
{
    DVECTOR     screenXy_0[90];
    u16         screenZ_168[18];
    s16         field_18C[72];
    s32         field_21C[39]; // Used as `VECTOR3`?
    u8          field_2B8[200];
    MATRIX      field_380;
    s_ObjNormal field_3A0;
    DVECTOR     screenPos_3A4;
    s32         depthP_3A8;
    SVECTOR     field_3AC;
    u8          unk_3B4[36];
    CVECTOR     field_3D8;

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
            s_ObjNormal field_3DC;
            SVECTOR     field_3E0[3];
        } normal;
    } u;
} s_GteScratchData2;

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 unk_6;
    s16 unk_8;
    s16 unk_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s16 unk_12;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16  unk_1A;
} s_800AE204;

typedef struct
{
    s32 field_0_0  : 1;
    s32 field_0_1  : 10;
    s32 field_0_11 : 10;
    u32 field_0_21 : 4;
    u32 field_0_25 : 4;
    u32 field_0_29 : 3;
} s_func_8006F8FC;

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

extern const s_MapType g_MapTypes[16];

extern u8 const g_12x16FontWidths[];

extern u32 g_MapMsg_Colors[];

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

extern s32 g_ScreenFadeProgress;

extern DR_MODE D_800A8E98[];

extern POLY_G4 D_800A8EB0[];

extern s32 D_800A8F40;

extern GsOT D_800A8F9C[];

extern s_FsImageDesc g_Font16AtlasImg;    // 0x800A8FF4
extern s_FsImageDesc g_KonamiLogoImg;     // 0x800A8FFC
extern s_FsImageDesc g_KcetLogoImg;       // 0x800A9004
extern s_FsImageDesc g_TitleImg;          // 0x800A9014
extern s_FsImageDesc g_MapImg;            // 0x800A901C
extern s_FsImageDesc g_MapMarkerAtlasImg; // 0x800A9024
extern s_FsImageDesc g_ItemInspectionImg; // 0x800A902C
extern s_FsImageDesc D_800A9034;
extern s_FsImageDesc D_800A905C;
extern s_FsImageDesc g_ControllerButtonAtlasImg;   // 0x800A903C
extern s_FsImageDesc g_BrightnessScreenImg0;       // 0x800A9044
extern s_FsImageDesc g_BrightnessScreenImg1;       // 0x800A904C
extern s_FsImageDesc g_DeathTipImg;                // 0x800A9054
extern s_FsImageDesc g_HealthPortraitImg;          // 0x800A905C
extern s_FsImageDesc g_InventoryKeyItemTextureImg; // 0x800A9064
extern s_FsImageDesc g_FirstAidKitItemTextureImg;  // 0x800A906C

/** Some intentory item texture (`ITEM/TIM07.TIM`). */
extern s_FsImageDesc D_800A9074;

/** `TEST/WARMTEST.TIM` texture loaded by `Ai_Twinfeeler_TextureLoad. Unused? */
extern s_FsImageDesc D_800A9094;

extern s_FsImageDesc g_Font24AtlasImg; // 0x800A909C

/** Array containg file IDs used for each `e_CharacterId`, used in `Fs_QueueStartReadAnm`. */
extern s_CharaFileInfo g_Chara_FileInfo[45]; // 0x800A90FC

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

/** Related to character animation allocation handling. */
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

extern u8 D_800AA5E0[];

extern u8 D_800AA604[][16];

extern s_800AA894 D_800AA894[];

extern u8 D_800AE185;

extern u8 D_800AE186;

extern u8 D_800AE187;

extern s16 D_800AE1A8;

extern s_800AE204 D_800AE204[26];

extern s32 g_PickupItemAnimState;

extern s32 D_800AE1B0;

extern s16 D_800AE520[];

extern s16 D_800AE564[];

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

extern s_800AFC78 D_800AFC78; // Maybe different struct.

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

extern const char* g_ItemNames[];

extern const char* g_ItemDescriptions[];

extern s32 g_PrevScreenFadeProgress;

extern s32 g_ScreenFadeTimestep;

extern s_800B5C40 D_800B5C40[];

// TODO: Overlapped variables
extern s8 D_800B5C50[][64];

extern s8 D_800B5C54[][64];

extern s8 D_800B5C58[][64];

extern s32 D_800B5C7C;

extern s_800B5D04 D_800B5D04[];

extern u8 D_800B7CC4[][8192];

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
extern s32 g_Gfx_ScreenFade;

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

/** TODO: These variables are part of `s_MapMsgSelect`, but must remain separate
 * because using struct fields instead of the direct addresses produces a mismatch.
 */
extern u8 g_MapMsg_AudioLoadBlock;
extern s8 g_MapMsg_SelectCancelIdx3;

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

extern s_800BCE18 D_800BCE18;

extern s32 D_800C1010[];

extern s_800C1020 D_800C1020;

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s32 D_800C15B8;

/** Absolute SFX index. */
extern s16 D_800C15BC;

extern s16 D_800C15BE;

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

/** `bool` | is stereo enabled? */
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

extern s16 D_800C4408;

extern s8 D_800C4414;

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

extern s_func_800699F8 D_800C4620;

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

void func_8003C1AC(s_800BCE18_0_CC* arg0);

void func_8003C220(s_MapOverlayHeader* mapHeader, s32 playerPosX, s32 playerPosZ);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003C850();

void func_8003C878(s32 arg0);

void func_8003C8F8(s_800BCE18_2BEC_0* arg0, char* newStr);

void func_8003C92C(s_800BCE18_2BEC_0* arg0, const VECTOR3* pos, const SVECTOR3* rot);

void func_8003CD6C(s_PlayerCombat* combat);

/** Returns `bool`? */
s32 func_8003CDA0(s32 invSlotIdx);

void func_8003D01C();

void func_8003D03C();

s32 func_8003D444(s32 idx);

void func_8003D550(s32 arg0, s32 arg1);

/** Called by some chara init funcs, similar to `func_8003DD80`? */
void func_8003D468(s32 arg0, bool flag);

void func_8003D6A4(s_800BCE18_0_CC* arg0);

/** Return type assumed. */
void func_8003D160();

void func_8003D5B4(s8 arg0);

void func_8003D6E0(s32 arg0, s32 arg1, s_PlmHeader* plmHeader, s_FsImageDesc* tex);

/** Param types assumed. */
void func_8003DD80(s32 idx, s32 arg1); // Called by some chara init funcs.

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

void func_80040004(s_800BCE18* arg0);

void func_80040014();

/** @brief Computes the stereo sound balance based on the relative position to the camera.
 *
 * @param soundPos Sound source position.
 * @return Stereo sound balance in the range [-127, 127], where values affect the left-right channel balance.
 */
s8 Sound_StereoBalanceGet(const VECTOR3* soundPos);

bool func_80040B74(s32 arg0);

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

/** Used for loading maps */
void func_80041C24(s_PlmHeader* plmHeader, s32 arg1, s32 arg2);

void func_80041CB4(s_func_80041CB4* arg0, s_PlmHeader* plmHeader);

void func_80041CEC(s_PlmHeader* plmHeader);

/** @brief Clears `queueIdx_4` in array of `s_800C117C` */
void func_80041D10(s_800C117C* arg0, s32 size);

/** Crucial for map loading. */
void func_80041D48();

void func_80041E98();

void Map_PlaceIpdAtGridPos(s16 ipdFileIdx, s32 x, s32 z);

void func_80041FF0();

void func_8004201C();

void func_800420C0();

void func_800420FC();

s_PlmTexList_8* func_80042178(char* arg0);

void func_800421D8(char* mapTag, s32 plmIdx, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_80042300(s_800C1020* arg0, s32 arg1);

/** @brief Locates all IPD files for a given map type.
 *
 * Example:
 * Map type THR.
 * `file 1100` is `THR0205.IPD`, `ipdGridCenter_42C[2][5] = 1100`.
 */
void Map_MakeIpdGrid(s_800C1020* arg0, char* mapTag, s32 fileIdxStart);

/** @brief Converts two hex `char`s to an integer hex value.
 *
 * @param out Output hex `int`.
 * @param hex0 First hex `char`.
 * @param hex1 Second hex `char`.
 */
bool ConvertHexToS8(s32* out, char hex0, char hex1);

s32* func_800425D8(s32* arg0);

s_IpdCollisionData* func_800426E4(s32 posX, s32 posZ);

s32 func_8004287C(s_800BCE18_2BEC_0* arg0, s_800BCE18_2BEC_0_10* arg1, s32 posX, s32 posZ);

/** @brief Gets the load state of a PLM file.
 *
 * @param
 * @return PLM file load state `(e_StaticModelLoadState`).
 */
s32 PlmHeader_LoadStateGet(s_func_80041CB4* arg0);

/** @brief Gets the load state of an IPD file.
 *
 * @param
 * @return IPD file load state `(e_StaticModelLoadState`).
 */
u32 IpdHeader_LoadStateGet(s_800C117C* arg0);

/** @brief Checks if an IPD file is loaded.
 *
 * @param ipdIdx IPD data index.
 * @return `true` if the IPD file is loaded, `false` otherwise.
 */
bool IpdHeader_IsLoaded(s32 ipdIdx);

void func_80042C3C(s32 x0, s32 z0, s32 x1, s32 z1);

/** Gets distance to the edge of a file chunk? */
s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, bool clip);

void func_800431E4(s_800C1020* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, bool clip);

void func_800433B8(s_800C1020* arg0);

void func_800433B8(s_800C1020* arg0);

/** Args are X and Z? */
s16 func_80043554(s32 gridX, s32 gridZ);

bool func_80043578(s_800C117C* arg0, s32 arg1, s32 arg2);

s_800C117C* func_800435E4(s_800C117C* arg0, s32 arg1);

/** Maybe facilitates file chunk streaming as the player moves around the map. */
s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s16 fileChunkCoordX, s16 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, bool clip);

bool func_80043830(void);

void func_80043A24(GsOT* ot, s32 arg1);

bool func_80043B34(s_800C117C* arg0, s_800C1020* arg1);

/** Checks if PLM texture is loaded? */
bool IpdHeader_IsTextureLoaded(s_IpdHeader* ipdHeader);

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHeader);

void IpdHeader_FixOffsets(s_IpdHeader* ipdHeader, s_PlmHeader** plmHeaders, s32 plmHeaderCount, s_800C1450_0* arg3, s_800C1450_0* arg4, s32 arg5);

void func_80043C7C(s_IpdHeader* ipdHeader, s_800C1450_0* arg1, s_800C1450_0* arg2, s32 arg3);

/** Checks if IPD is loaded before returning texture count? */
s32 func_80043D00(s_IpdHeader* ipdHeader);

/** Returns inverse result of `PlmFilter_NameEndsWithH`. */
bool PlmFilter_NameDoesNotEndWithH(s_PlmTexList* texList);

bool PlmFilter_NameEndsWithH(s_PlmTexList* texList);

void IpdHeader_FixHeaderOffsets(s_IpdHeader* ipdHeader);

/** @brief Assigns `s_ObjList` pointers to models in `s_IpdHeader` by searching the given `s_PlmHeader` array. */
void IpdHeader_ModelLinkObjectLists(s_IpdHeader* ipdHeader, s_PlmHeader** plmHeaders, s32 plmHeaderCount);

/** @brief Searches `s_PlmHeader` for objects with the given `objName`. */
s_ObjList* PlmHeader_ObjectListSearch(u_Filename* objName, s_PlmHeader* plmHeader);

/** @brief Assigns `s_ObjList` pointers to each `s_IpdModelBuffer` in `s_IpdHeader`. */
void IpdHeader_ModelBufferLinkObjectLists(s_IpdHeader* ipdHeader, s_IpdModelInfo* ipdModels);

/** Sets IPD collision data grid coords? */
void func_80044044(s_IpdHeader* ipd, s32 x, s32 z);

/** Loads anim file? */
void Anim_BoneInit(s_AnmHeader* anmHeader, GsCOORDINATE2* boneCoords);

s_AnimInfo* func_80044918(s_ModelAnim* anim);

void Anim_BoneUpdate(s_AnmHeader* anmHeader, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, s32 alpha);

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords);

q19_12 Anim_DurationGet(s_Model* model, s_AnimInfo* anim);

/** Updates a character's animation, variant 0. First param might be `s_SubCharacter` instead.
 * Used for anim init?
 */
void Anim_Update0(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coords, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 1.
 * Used for looped anims?
 */
void Anim_Update1(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 2.
 * The generic update func?
 */
void Anim_Update2(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Updates a character's animation, variant 3.
 * Same as `Anim_Update2` but sine-based?
 */
void Anim_Update3(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo);

/** Something related to player weapon position. Takes coords to arm bones. */
void func_80044F14(GsCOORDINATE2* coord, s16 z, s16 x, s16 y);

s8 func_80044F6C(s8* ptr, bool arg1);

/** Skeleton setup? Assigns bones pointer for the skeleton and resets fields. */
void func_80044FE0(s_Skeleton* skel, s_Bone* bones, u8 boneCount);

/** Clears skeleton bone flags/mask. Called by `func_80044FE0`. */
void func_80045014(s_Skeleton* skel);

/** Anim func. Used in tandem with skeleton bone traversal. */
void func_8004506C(s_Skeleton* skel, s_PlmHeader* plmHeader);

/** Anim func. */
void func_80045108(s_Skeleton* arg0, s_PlmHeader* plmHeader, u8* arg2, s32 arg3);

/** Anim func. */
void func_800451B0(s_Skeleton* skel, s_PlmHeader* plmHeader, s32* arg2);

/** Anim func. Param names are rough. */
void func_80045258(s_Skeleton** skels, s_Bone* bones, s32 boneIdx, s_PlmHeader* plmHeader);

/** Anim func. */
void func_800452EC(s_Skeleton* skel);

/** Anim func. Traverses skeleton bones to set flags/mask. */
void func_800453E8(s_Skeleton* skel, bool cond);

/** Does something with skeleton bones. `arg0` is a struct pointer. */
void func_80045468(s_Skeleton* skel, s32* arg1, bool cond);

/** Passes a command to the sound driver. Plays SFX among other things. */
void Sd_EngineCmd(u32 cmd);

/** Sound func? */
u8 func_80045B28();

u16 func_80045BC8();

/** Sound func. */
void func_80045BD8(u16 cmd);

void func_80045D28(u8 caseArg);

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

void func_80046C54(u8 arg0, u8 arg1);

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

/** Returns `true` if player has usable ammo in inventory (i.e. ammo + gun needed for it, or gun with ammo loaded). */
s32 func_8004C328();

void func_8004C564(u8, s32);

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

void GameFs_UniqueItemModelLoad(u8 itemId);

void GameFs_MapItemsTextureLoad(s32 mapId);

void func_800546A8(s32 arg0);

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

void PlmHeader_FixOffsets(s_PlmHeader* plmHeader);

void ObjList_FixOffsets(s_ObjList* objList, s_PlmHeader* plmHeader);

void func_80056244(s_PlmHeader* plmHeader, bool flag);

/** Gets texture count? */
s32 func_80056348(bool (*arg0)(s_PlmTexList* texList), s_PlmHeader* plmHeader);

/** TODO: Unknown `arg3` type. */
void func_80059D50(s32 arg0, s_func_80057344* arg1, MATRIX* mat, void* arg3, GsOT_TAG* arg4);

/** TODO: Unknown `arg2` type. */
void func_8005A21C(s_func_80057344* arg0, GsOT_TAG* otTag, void* arg2, MATRIX* mat);

/** @brief Computes a fog-shaded version of `D_800C4190` color using `arg1` as the distance factor?
 *  Stores the result at 0x3D8 into `arg0`.
 */
void func_8005A42C(s_GteScratchData* scratchData, s32 arg1);

void func_8005A478(s_GteScratchData* scratchData, s32 alpha);

/** `scratchData` is unused? */
void func_8005A838(s_GteScratchData* scratchData, s32 scale);

void func_8005A900(s_ObjHeader* objHeader, s32 offset, s_GteScratchData* scratchData, MATRIX* mat);

u8 func_8005AA08(s_ObjHeader* objHeader, s32 arg1, s_GteScratchData2* scratchData);

/** Related to enviroment textures. */
void func_8005B1A0(s_PlmTexList_8* arg0, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY);

void func_8005B370(s_PlmTexList_8* arg0);

void func_8005B378(s_PlmTexList_8* arg0, char* arg1);

void func_8005B3A4(s_PlmTexList_8* arg0);

void func_8005B3BC(char* filename, s_PlmTexList* plmTexList);

void func_8005B424(VECTOR3* vec0, VECTOR3* vec1);

/** @unused No references. */
void func_800563E8(s_PlmHeader* plmHeader, s32 arg1, s32 arg2, s32 arg3);

void func_80056464(s_PlmHeader* plmHeader, s32 fileIdx, s_FsImageDesc* image, s32 arg3);

void func_80056504(s_PlmHeader* plmHeader, char* newStr, s_FsImageDesc* image, s32 arg3);

bool func_80056558(s_PlmHeader* plmHeader, char* fileName, s_FsImageDesc* image, s32 arg3);

void func_8005660C(s_PlmTexList* plmTexList, s_FsImageDesc* image, s32 arg2);

void func_800566B4(s_PlmHeader* plmHeader, s_FsImageDesc* image, s8 unused, s32 startIdx, s32 arg4);

/** Unknown `arg3` / `arg4` types. */
void func_80056774(s_PlmHeader* plmHeader, s_800C1450_0* arg1, bool (*func)(s_PlmTexList* plmTexList), void* arg3, s32 arg4);

/** Checks if PLM textures are loaded? */
bool PlmHeader_IsTextureLoaded(s_PlmHeader* plmHeader);

void func_80056954(s_PlmHeader* plmHeader);

void func_80056A88(s_ObjList* objList, s32 arg1, s_PlmTexList* plmTexList, s32 flags);

void func_80056BF8(s_PlmHeader* plmHeader);

s32 PlmHeader_ObjectCountGet(s_PlmHeader* plmHeader);

void func_80056C8C(s_Bone* bone, s_PlmHeader* plmHeader, s32 objListIdx);

bool func_80056CB4(s_800BCE18_2BEC_0* arg0, s_PlmHeader* plmHeader, s_800BCE18_2BEC_0_10* arg2);

void StringCopy(char* prevStr, char* newStr);

void func_80057090(s_func_80057344* arg0, GsOT* arg1, void* arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5);

s32 func_800571D0(u32 arg0);

void func_80057228(MATRIX* mat, s32 alpha, SVECTOR* arg2, VECTOR3* arg3);

/** TODO: Unknown `arg2` type. */
void func_80057344(s_func_80057344* arg0, GsOT_TAG* otTag, void* arg2, MATRIX* mat);

void func_800574D4(s_ObjHeader* header, s_GteScratchData* scratchData);

void func_8005759C(s_ObjHeader* header, s_GteScratchData* scratchData, s32 vertexOffset, s32 normalOffset);

void func_80057658(s_ObjHeader* header, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4);

void func_80057A3C(s_ObjHeader* header, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec);

s_PlmTexList_8* func_8005B1FC(s_PlmTexList* arg0, s_800C1450_0* arg1, void* fs_buffer_9, void* arg3, s32 arg4);

void func_8005B55C(GsCOORDINATE2* arg0);

s32 func_8005C7D0(s_SubCharacter* chara, s32 moveSpeed);

void func_8005C814(s_SubCharacter_D8* arg0, s_SubCharacter* chara);

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

s32 func_8005F680(s_func_800699F8* arg0);

/** Spatial SFX func? */
void func_8005DE0C(s32 sfx, VECTOR3*, s32, s32, s32); // Types assumed.

void func_8005E0DC(s32 mapIdx); // Types assumed.

void func_8005E70C();

s32 func_8005E7E0(s32 arg0);

void func_8005E89C();

void func_8005F6B0(s_SubCharacter*, s32*, s32, s32);

void DmsHeader_FixOffsets(s_DmsHeader* header);

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* header);

/** @unused? `volatile` needed for match. */
s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* header);

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, s32 time, s_DmsHeader* header);

void Dms_CharacterGetStartPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, s32 time, s_DmsHeader* header);

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* header);

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, s32 time, s_DmsHeader* header);

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha);

/** @unused? Returns `96 * cotangent(angle / 2)`. Possibly camera/FOV related. */
s16 func_8008CDBC(s16 angle);

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, s32 time, s_DmsHeader* header);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, s_DmsKeyframeCamera* frame0, s_DmsKeyframeCamera* frame1, s32 alpha);

/** DMS func. */
void func_8008D1D0(s32* keyframePrev, s32* keyframeNext, s32* alpha, s32 time, s_DmsEntry* camEntry, s_DmsHeader* header);

u32 func_8008D2C4(s32 time, s_DmsHeader* header);

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

/** `posX` and `posX` appear to be in Q27.4. */
s_WaterZone* Map_WaterZoneGet(s32 posX, s32 posZ, s_WaterZone* waterZone);

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

void func_8008677C(s32 arg0, s32 arg1, s32 arg2);

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

void Event_ItemTake(s32 itemId, s32 itemCount, s32 globalPickupId, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, s32 globalPickupId);

void Event_MapTake(s32 mapFlagIdx, s32 eventFlagIdx, s32 mapMsgIdx);

void func_80087EA8(s32 cmd);

void func_80087EDC(s32 arg0);

void func_80088028();

void func_80088048();

void func_800880F0(s32 arg0);

void func_800881B8(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

/**
Could `arg5` be a struct pointer?
`func_8003D6E0` uses this function and in the last argument
it input `arg5` and `arg5` is an undetermined function pointer
*/
bool Chara_Load(s32 arg0, s8 charaId, GsCOORDINATE2* coord, s8 arg3, s_PlmHeader* plmHeader, s_FsImageDesc* tex);

bool func_80088D0C();

void func_80088D34(s32 idx);

s32 Chara_Spawn(s32 charaId, s32 arg1, s32 posX, s32 posZ, s16 posY, u32 stateStep);

void func_80088F94(s_SubCharacter* chara, s32 unused1, s32 unused2);

void func_80088FF4(s32 groupIdx, s32 spawnIdx, s32 spawnFlags);

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

void func_8008E4EC(s_PlmHeader* plmHeader);

void func_8008D78C();

s32 func_8008F470(s32 caseArg);

/** Returns 0. */
s32 func_8008F520();

s32 func_8008F914();

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

void func_8005B46C(s_800C1450_0* arg0);

/** Crucial for map loading. */
void func_8005B474(s_800C1450_0* arg0, s_PlmTexList_8* arg1, s32 idx);

s_PlmTexList_8* func_8005B4BC(char* str, s_800C1450_0* arg1);

/** Sets the debug string position. */
void func_8005BF0C(s16 unused, s16 x, s16 y);

/** Angle func. */
s16 func_8005BF38(s16 angle);

s16 func_8005C7B0(s32 arg0);

/** `arg0` type assumed. */
void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3);

void func_8006342C(s32 invItemId, s16, s16, GsCOORDINATE2*);

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, s16 x, s16 z);

void func_800622B8(s32, s_SubCharacter*, s32 animStatus, s32);

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

void IpdCollData_FixOffsets(s_IpdCollisionData* collData);

void func_80069994(s_IpdCollisionData* collData);

void func_800699E4(s_IpdCollisionData* collData);

/** Getter for 2D point collision? */
void func_800699F8(s_func_800699F8* coll, s32 posX, s32 posZ);

s32 func_80069B24(s_800C4590* arg0, VECTOR3* arg1, s_SubCharacter* chara);

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* arg1, s_SubCharacter* chara);

void func_8006A178(s_800C4590* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_8006A1A4(s32* arg0, s_SubCharacter* chara, s32 arg2);

s32 func_8006A4A8(s32, s32*, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_8006A3B4(s32 arg0, VECTOR* arg1, s32 arg2);

s32 func_8006A42C(s32 arg0, VECTOR3* arg1, s32 arg2);

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* vec, s_func_8006AB50* arg2, s32 arg3);

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* vec, s_func_8006AB50* arg2);

void func_8006AD44(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

bool func_8006B004(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

void func_8006B1C8(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006B1C8* arg2);

/** `arg1` is unused, but `func_8006B1C8` passes second arg to this. */
void func_8006B6E8(s_func_8006CC44* arg0, s_func_8006B1C8* arg1);

void func_8006B9C8(s_func_8006CC44* arg0);

s32 func_8006BC34(s_func_8006CC44* arg0);

void func_8006BCC4(s8*, s32, s32, s16, s16, s16);

void func_8006BDDC(s_func_8006BDDC* arg0, s16 arg1, s16 arg2);

void func_8006BE40(s_func_8006CC44* arg0);

void func_8006C0C8(s_func_8006CC44*, s16, s16, s32);

bool func_8006C1B8(u32 arg0, s16 arg1, s_func_8006CC44* arg2);

bool func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx);

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 arg2);

void func_8006C838(s_func_8006CC44* arg0, s_IpdCollisionData* collData);

void func_8006CA18(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006CA18* arg2);

s16 func_8006CB90(s_func_8006CC44* arg0);

s32 func_8006CC44(s32 x, s32 z, s_func_8006CC44* arg2);

void func_8006D01C(VECTOR3* arg0, VECTOR3* arg1, s16 arg2, s_func_8006CC44* arg3);

void func_8006D600(VECTOR3* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8006D774(s_func_8006CC44* arg0, VECTOR3* arg1, VECTOR3* arg2);

/** `arg1` is likely Q23.8. */
void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2);

bool func_8006D90C(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2);

bool func_8006DA08(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2, s_SubCharacter* chara);

void func_8006DAE4(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2, s32 arg3);

bool func_8006DB3C(s_func_800700F8_2* arg0, VECTOR3* arg1, VECTOR3* arg2, s_SubCharacter* chara);

bool func_8006DC18(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2);

bool func_8006DCE0(s_func_8006DCE0* arg0, s32 arg1, s16 arg2, VECTOR3* pos0, VECTOR3* pos1, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

void func_8006E0AC(s_func_8006DCE0* arg0, s_IpdCollisionData* arg1);

void func_8006E490(s_func_8006E490* arg0, u32 arg1, s32 arg2, s32 arg3);

void func_8006F250(s_func_8006F250* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8006F338(s_func_8006F338* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_8006F8FC(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s_func_8006F8FC* arg4);

s16 func_8006F99C(s_SubCharacter* chara, s32 arg1, s16 arg2);

bool func_8006FD90(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3);

bool func_80070030(s_SubCharacter* chara, s32 x, s32 y, s32 z);

bool func_80070084(s_SubCharacter* chara, s32 x, s32 y, s32 z);

bool func_800700F8(s_SubCharacter* chara0, s_SubCharacter* chara1);

bool func_80070184(s_SubCharacter* chara, s32 arg1, s16 rotY);

bool func_80070320();

s32 func_80070360(s_SubCharacter* chara, s32 someDist, s16 arg2);

void func_80070400(s_SubCharacter* chara, s_func_80070400_1* arg1, s_func_80070400_1* arg2);

bool func_80070208(s_SubCharacter* chara, s32 arg1);

s32 func_8007029C(s_SubCharacter* chara, s32 arg1, s16 angle);

void func_800705E4(GsCOORDINATE2*, s32, s32, s32, s32);

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
s32 Math_DistanceGet(const VECTOR3* pos0, const VECTOR3* pos1);

/** @brief Computes the 2D distance on the XZ plane between two positions.
 *
 * @param pos0 First position.
 * @param pos1 Second position.
 * @return 2D distance between positions.
 */
s32 Math_Distance2dGet(const VECTOR3* pos0, const VECTOR3* pos1);

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

s32 func_8003BE50(s32 idx);

void GameFs_BgEtcGfxLoad();

void GameFs_BgItemLoad();

void func_8003BED0();

s32 Map_SpeedZoneGet(s32 x, s32 z);

/** Used in map loading. Something related to screen.
 * Removing it causes the game to get stuck at the loading screen.
 */
void func_8003C048();

/** Something related to player model loading. */
void func_8003C0C0();

/** Allocates player model? */
void func_8003C110();

void func_8003C1AC(s_800BCE18_0_CC* arg0);

void func_8003C2EC();

void func_8003C30C();

void func_8003C368();

void func_8003C3A0();

/** Handles player movement. */
void func_8003C3AC();

void func_8003C878(s32);

void func_8003CB3C(s_800BCE18* arg0);

void func_8003CB44(s_800BCE18* arg0);

void func_8003CBA4(s_800BCE18_2BEC* arg0);

void func_8003CC7C(s_800BCE18_2BEC_0* arg0, MATRIX* arg1, MATRIX* arg2);

void func_8003D354(s32* arg0, s32 arg1);

/** Texture UV setup for NPCs. */
void func_8003D3BC(s_FsImageDesc* img, s32 arg1, s32 arg2);

s32 func_8003D7D4(u32 arg0, s32 arg1, s_PlmHeader* plmHeader, s_FsImageDesc* tex);

/** Something related to animations. */
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

void func_80043740();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SavegameResetPlayer();

void func_8007E5AC();

void func_8007E860();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_80070DF0(s_MainCharacterExtra* extra, s_SubCharacter* chara, s32 arg2, s32 animStatus);

/** Special player SFX handler for heavy breath and damage. */
bool func_80071620(u8 animStatus, s_SubCharacter*, s32, s32 sfx);

void func_8007C0D8(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

void func_8007D090(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord);

/** Player func. */
void func_8007E9C4();

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

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1);

/** Generates a random angle? */
s32 func_80080514(void);

/** Computes (abs(value) - subtractor) * copysign(value). */
s32 Math_PreservedSignSubtract(s32 val, s32 subtractor);

void func_800805BC(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* rootCoord, s32 arg3);

bool func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // arg3 type assumed.

/** Probably returns `bool`. */
bool func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** Collision func? */
void func_8008076C(s32 posX, s32 posZ);

/** Returns ground height? */
s32 func_80080884(s32 posX, s32 posZ);

s32 func_800808AC(s32 posX, s32 posZ);

/** Returns a Q shift based on a magnitude. */
s32 Math_MagnitudeShiftGet(s32 mag);

s32 func_80080A10();

u8 func_8008A2E0(s32 arg0);

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

void Game_TurnFlashlightOff();
#endif
