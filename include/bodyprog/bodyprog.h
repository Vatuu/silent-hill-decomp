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

/** @brief IPD chunk load states.
 *
 * See `Map_ChunkLoadStateGet`.
 */
typedef enum _ChunkLoadState
{
    ChunkLoadState_Invalid  = 0, /** Entry index is `NO_VALUE`. */
    ChunkLoadState_Unloaded = 1, /** Not currently loaded. */
    ChunkLoadState_Loaded   = 2  /** Currently loaded. */
} e_ChunkLoadState;

typedef enum _WorldModelLocation
{
    WorldModelLocation_None   = 0,
    WorldModelLocation_Global = 1,
    WorldModelLocation_Chunk1 = 2,
    WorldModelLocation_Chunk2 = 3,
    WorldModelLocation_Chunk3 = 4,
    WorldModelLocation_Chunk4 = 5
} e_WorldModelLocation;

/** @brief Character spawn flags. */
typedef enum _SpawnFlags
{
    SpawnFlag_None = 0,
    SpawnFlag_0    = 1 << 0,
    SpawnFlag_1    = 1 << 1,
    SpawnFlag_2    = 1 << 2,
    SpawnFlag_3    = 1 << 3,
    SpawnFlag_4    = 1 << 4
} e_SpawnFlags;

// Used by `func_8006E490` and `func_8006E150`.
typedef enum _OrientationFlags
{
    OrientationFlags_None    = 0,
    OrientationFlags_InvertX = 1 << 0,
    OrientationFlags_InvertZ = 1 << 1,
    OrientationFlags_SwapXz  = 1 << 2
} e_OrientationFlags;

/** @brief SFX pair indices. Used for `SFX_PAIRS`. */
typedef enum _SfxPairIdx
{
    SfxPairIdx_0  = 0,
    SfxPairIdx_1  = 1,
    SfxPairIdx_2  = 2,
    SfxPairIdx_3  = 3,
    SfxPairIdx_4  = 4,
    SfxPairIdx_5  = 5,
    SfxPairIdx_6  = 6,
    SfxPairIdx_7  = 7,
    SfxPairIdx_8  = 8,
    SfxPairIdx_9  = 9,
    SfxPairIdx_10 = 10,
    SfxPairIdx_11 = 11,
    SfxPairIdx_12 = 12,
    SfxPairIdx_13 = 13,
    SfxPairIdx_14 = 14,
    SfxPairIdx_15 = 15,
    SfxPairIdx_16 = 16,
    SfxPairIdx_17 = 17,
    SfxPairIdx_18 = 18,
    SfxPairIdx_19 = 19,
    SfxPairIdx_20 = 20,
    SfxPairIdx_21 = 21,
    SfxPairIdx_22 = 22,
    SfxPairIdx_23 = 23,
    SfxPairIdx_24 = 24
} e_SfxPairIdx;

/** @brief Animation playback states. Returned by `Chara_AnimPlaybackStateGet`. */
typedef enum _AnimPlaybackState
{
    AnimPlaybackState_Blend   = -2,
    AnimPlaybackState_Invalid = -1, // Unsure.
    AnimPlaybackState_Active  = 0,
    AnimPlaybackState_End     = 1
} e_AnimPlaybackState;

/** @brief Background music flags. */
typedef enum _BgmFlags
{
    BgmFlag_Layer0    = 1 << 0,
    BgmFlag_Layer1    = 1 << 1,
    BgmFlag_Layer2    = 1 << 2,
    BgmFlag_Layer3    = 1 << 3,
    BgmFlag_Layer4    = 1 << 4,
    BgmFlag_Layer5    = 1 << 5,
    BgmFlag_Layer6    = 1 << 6,
    BgmFlag_Layer7    = 1 << 7,
    BgmFlag_KeepAlive = 1 << 8,
    BgmFlag_MuteAll   = 1 << 9
} e_BgmFlags;

/** @brief Background music track indices. */
typedef enum _BgmTrackIdx
{
    BgmTrackIdx_None = 0,
    BgmTrackIdx_1    = 1,
    BgmTrackIdx_2    = 2,
    BgmTrackIdx_3    = 3,
    BgmTrackIdx_4    = 4,
    BgmTrackIdx_5    = 5,
    BgmTrackIdx_6    = 6,
    BgmTrackIdx_7    = 7,
    BgmTrackIdx_8    = 8,
    BgmTrackIdx_9    = 9,
    BgmTrackIdx_10   = 10,
    BgmTrackIdx_11   = 11,
    BgmTrackIdx_12   = 12,
    BgmTrackIdx_13   = 13,
    BgmTrackIdx_14   = 14,
    BgmTrackIdx_15   = 15,
    BgmTrackIdx_16   = 16,
    BgmTrackIdx_17   = 17,
    BgmTrackIdx_18   = 18,
    BgmTrackIdx_19   = 19,
    BgmTrackIdx_20   = 20,
    BgmTrackIdx_21   = 21,
    BgmTrackIdx_22   = 22,
    BgmTrackIdx_23   = 23,
    BgmTrackIdx_24   = 24,
    BgmTrackIdx_25   = 25,
    BgmTrackIdx_26   = 26,
    BgmTrackIdx_27   = 27,
    BgmTrackIdx_28   = 28,
    BgmTrackIdx_29   = 29,
    BgmTrackIdx_30   = 30,
    BgmTrackIdx_31   = 31,
    BgmTrackIdx_32   = 32,
    BgmTrackIdx_33   = 33,
    BgmTrackIdx_34   = 34,
    BgmTrackIdx_35   = 35,
    BgmTrackIdx_36   = 36,
    BgmTrackIdx_37   = 37,
    BgmTrackIdx_38   = 38,
    BgmTrackIdx_39   = 39,
    BgmTrackIdx_40   = 40,
    BgmTrackIdx_41   = 41
} e_BgmTrackIds;

/** @brief Global collision flags.
 * Applies for both NPCs and the player.
 */
typedef enum _CollisionFlags
{
    CollisionFlag_None = 0,
    CollisionFlag_0    = 1 << 0, // Enables map collisions.
    CollisionFlag_1    = 1 << 1, // Enables objects collisions.
    CollisionFlag_2    = 1 << 2, // Enables alternative objects collisions?
    CollisionFlag_3    = 1 << 3, // @unused Only ever call in `MAP6_S05`.
    CollisionFlag_All  = 0xFFFF
} e_CollisionFlags;

typedef enum _CollisionType
{
    CollisionType_None = 0,
    CollisionType_Wall = 1,
    CollisionType_Unk2 = 2
} e_CollisionType;

/** @brief Map flags. */
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

typedef enum _FloorType
{
    FloorType_0     = 0,
    FloorType_1     = 1,
    FloorType_2     = 2,
    FloorType_Grass = 3,
    FloorType_4     = 4,
    FloorType_5     = 5,
    FloorType_6     = 6,
    FloorType_7     = 7,
    FloorType_8     = 8,
    FloorType_9     = 9,
    FloorType_10    = 10,
    FloorType_11    = 11,
    FloorType_12    = 12
} e_FloorType;

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
    /* 0x0 */ s32               id;
    /* 0x4 */ s32               flags;
    /* 0x8 */ s32               modelCount;
    /* 0xC */ struct TMD_STRUCT models[1];
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
        q19_12 vx_0; // Displacement offset.
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
        q19_12 vz_4;
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
    } field_4;
    q3_12 vy_8;
    u8    field_A;
    u8    field_B; // Flags?
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
            q4_12 field_0;
            u16   field_2;
        } s_2;
    } field_C;
    union
    {
        q20_12 field_0; // Timer.
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
    /* 0x0 */ q19_12 groundHeight;
    /* 0x4 */ q3_12  field_4;  // X
    /* 0x6 */ q3_12  field_6;  // Z
    /* 0x8 */ s8     field_8;  // Count of something, maybe valid ground at probed points around center? Set to 0, 7, or 12.
    // 3 bytes of padding.
} s_Collision;
STATIC_ASSERT_SIZEOF(s_Collision, 12);

typedef struct _CollisionQuery
{
    /* 0x0  */ VECTOR3 position; /** Q19.12 */
    /* 0xC  */ q3_12   bottom;
    /* 0xE  */ q3_12   top;
    /* 0x10 */ q3_12   radius;         // Unsure. Set to cylinder radius.
    /* 0x14 */ s8      collisionState; /** `e_CharaCollisionState` */
} s_CollisionQuery;
STATIC_ASSERT_SIZEOF(s_CollisionQuery, 20);

// Collision-related.
typedef struct
{
    /* 0x0  */ s32        collisionState; /** `e_CharaCollisionState` */
    /* 0x4  */ bool       field_4;
    /* 0x8  */ q19_12     distance_8;
    /* 0xC  */ SVECTOR    offset_C; // Q23.8
    /* 0x14 */ DVECTOR_XZ direction_14;
    /* 0x18 */ q23_8      positionX_18;
    /* 0x1C */ q23_8      positionZ_1C;
    /* 0x20 */ q23_8      newPositionX_20;
    /* 0x24 */ q23_8      newPositionZ_24;
    /* 0x28 */ q7_8       field_28; // Radius.
    /* 0x2A */ q7_8       field_2A; // Wrong name. Top.
    /* 0x2C */ q7_8       field_2C; // Bottom.
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
} s_CollisionState_A8;

typedef struct
{
    s8      field_0;
    s8      unk_1;
    DVECTOR field_2; // Q3.12 | Angle constraint. X is min, Y is max. TODO: Don't use `DVECTOR` for this anymore.
} s_CollisionState_44_0;

typedef struct
{
    s_CollisionState_44_0 field_0;
    s16                  field_6;
    s_CollisionState_44_0 field_8;
    s16                  field_E;
    s8*                  field_10[8];
    s_CollisionState_44_0 field_30;
    s16                  field_36;
} s_CollisionState_44;

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
    q19_12 field_28; // Maybe XZ position.
    q19_12 field_2C; // Base height?
} s_func_8006F338;

typedef struct
{
    q3_12 field_0; // X
    q3_12 field_2; // Z
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

/** @brief Character keyframe collision info. */
typedef struct _Keyframe
{
    /* 0x0 */ s_CharaBox          box;
    /* 0xC */ s_CharaShapeOffsets shapeOffsets;
} s_Keyframe;

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
    s16      rotMatrix_3E4[3][3]; // Truncated `MATRIX` without the `long t[3];` transfer vector?
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
            u8 isTransparent : 1; /** `bool` */
        } bits;

        u16 flags; // @hack `func_8005AC50` accesses `isTransparent` above with some weird shifts, haven't found how to make it work with bitfield yet.
    } field_6;
    u16 field_8;
    u16 field_A;
    u8  field_C[4];  // } Unknown type. `func_8005AC50` reads these as `s32`, but that breaks other funcs which use this struct. `s32` reads might have just been `memcpy`?
    u8  field_10[4]; // }
} s_Primitive;
STATIC_ASSERT_SIZEOF(s_Primitive, 20);

typedef struct _MeshHeader
{
    /* 0x0  */ u8           primitiveCount;
    /* 0x1  */ u8           vertexCount;
    /* 0x2  */ u8           normalCount;
    /* 0x3  */ u8           unkCount_3;
    /* 0x4  */ s_Primitive* primitives;
    /* 0x8  */ DVECTOR*     verticesXy;
    /* 0xC  */ s16*         verticesZ;
    /* 0x10 */ s_Normal*    normals;
    /* 0x14 */ u8*          unkPtr_14;
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

/** @brief Model texture. */
typedef struct _Texture
{
    /* 0x0  */ s_FsImageDesc imageDesc;
    /* 0x8  */ u_Filename    name;
    /* 0x10 */ u32           queueIdx;
    /* 0x14 */ s8            refCount;
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

/** @brief LM file header. */
typedef struct _LmHeader
{
    /* 0x0  */ u8             magic;    /** See `LM_HEADER_MAGIC`. */
    /* 0x1  */ u8             version;  /** See `LM_VERSION`. */
    /* 0x2  */ u8             isLoaded; /** `bool` */
    /* 0x3  */ u8             materialCount;
    /* 0x4  */ s_Material*    materials;
    /* 0x8  */ u8             modelCount;
               // 3 bytes of padding.
    /* 0xC  */ s_ModelHeader* modelHdrs;
    /* 0x10 */ u8*            modelOrder;
} s_LmHeader;

typedef struct _IpdCollisionData_10
{
    s16 field_0;
    s16 field_2; // Q8? Related to ground height?
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
    s16 field_0; // Base index into `s_IpdCollisionData::ptr_28`.
    s8  __pad_2[2];
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
    s32                    positionX;
    s32                    positionZ;
    u32                    field_8_0  : 8;
    u32                    field_8_8  : 8;
    u32                    field_8_16 : 8;
    u32                    field_8_24 : 8;
    SVECTOR3*              ptr_C;
    s_IpdCollisionData_10* ptr_10;
    s_IpdCollisionData_14* ptr_14;
    s_IpdCollisionData_18* ptr_18;
    q7_8                   field_1C;
    u8                     field_1E; // } Used as multipliers for `field_1C` in `func_8006B004`.
    u8                     field_1F; // }
    s_IpdCollisionData_20* ptr_20;
    u16                    field_24; // `field_24/``field_26` defined in ipd2obj but haven't seen used yet, might be size of `ptr_28`/`ptr_2C`.
    u16                    field_26;
    u8*                    ptr_28; // Accessed as array of indices into `field_34` by `func_8006E53C`.
    void*                  ptr_2C;
    u8                     field_30;
    u8                     __pad_31[3];
    u8                     field_34[256];
} s_IpdCollisionData;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData, 308);

// Node of some kind?
typedef struct _IpdModelBuffer_C
{
    /* 0x0 */ s_ModelHeader* modelHdr;
    /* 0x4 */ MATRIX         mat;
} s_IpdModelBuffer_C;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer_C, 36);

/** @brief IPD model buffer. */
typedef struct _IpdModelBuffer
{
    /* 0x0  */ u8                  field_0; // Count of `field_C` entries.
    /* 0x1  */ u8                  field_1;
    /* 0x2  */ u8                  subcellCount;
    /* 0x3  */ s8                  __pad_3;
    /* 0x4  */ q7_8                minX; // } TODO: Cell range or subcell range?
    /* 0x6  */ q7_8                maxX; // }
    /* 0x8  */ q7_8                minZ; // }
    /* 0xA  */ q7_8                maxZ; // }
    /* 0xC  */ s_IpdModelBuffer_C* field_C;
    /* 0x10 */ SVECTOR*            field_10;         // Pointer to unknown collision data.
    /* 0x14 */ SVECTOR*            subcellPositions; /** XZ positions. TODO: Use different struct. */
} s_IpdModelBuffer;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer, 24);

typedef struct _IpdModelInfo
{
    /** 0x0 */ u8             isGlobalPlm; // `false` if loaded from inside `IPD`, `true` if loaded from `*_GLB.PLM`.
               // 3 bytes of padding.
    /** 0x4 */ u_Filename     modelName;
    /** 0xC */ s_ModelHeader* modelHdr;
} s_IpdModelInfo;
STATIC_ASSERT_SIZEOF(s_IpdModelInfo, 16);

/** @brief IPD model file header. */
typedef struct _IpdHeader
{
    /* 0x0  */ u8                 magic;
    /* 0x1  */ u8                 isLoaded; /** `bool` */
    /* 0x3  */ s8                 cellX;
    /* 0x3  */ s8                 cellZ;
    /* 0x4  */ s_LmHeader*        lmHdr;
    /* 0x8  */ u8                 modelCount;
    /* 0x9  */ u8                 modelBufferCount;
    /* 0xA  */ u8                 modelOrderCount;
    /* 0xB  */ s8                 unk_B[9];
    /* 0x14 */ s_IpdModelInfo*    modelInfo;
    /* 0x18 */ s_IpdModelBuffer*  modelBuffers;
    /* 0x1C */ u8                 textureCount; // Should it be `u32`?
                                                // "`u8` - Relative pointer to textures list"
                                                // "`u32` - Relative pointer to object order"
    /* 0x1D */ s8                 unk_1D[51];
    /* 0x50 */ u8*                modelOrderList;
    /* 0x54 */ s_IpdCollisionData collisionData;
} s_IpdHeader;

// See: https://github.com/laura-a-n-n/silent-hill-museum/blob/main/ksy/sh1anm.ksy
typedef struct _AnmBindPose
{
    /* 0x0 */ s8 parentBone;
    /* 0x1 */ s8 rotationDataIdx;
    /* 0x2 */ s8 translationDataIdx;
    /* 0x3 */ s8 translationInitial[3];
} s_AnmBindPose;
STATIC_ASSERT_SIZEOF(s_AnmBindPose, 6);

/** @brief ANM file header. */
typedef struct _AnmHeader
{
    /* 0x0  */ u16           dataOffset;
    /* 0x2  */ u8            rotationBoneCount;
    /* 0x3  */ u8            translationBoneCount;
    /* 0x4  */ u16           keyframeDataSize; /** Size per keyframe. `(rotationBoneCount * 9) + (translationBoneCount * 3)`? */
    /* 0x6  */ u8            boneCount;        /** Size of `bindPoses`. */
               // 1 byte of padding.
    /* 0x8  */ u32           activeBones; /** Bit field of bones to update. */
    /* 0xC  */ u32           fileSize;
    /* 0x10 */ u16           keyframeCount;
    /* 0x12 */ u8            scaleLog2;
    /* 0x13 */ u8            rootYOffset;
    /* 0x14 */ s_AnmBindPose bindPoses[0];
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
} s_CollisionState_CC_C;

typedef struct
{
    DVECTOR_XZ field_0;
    DVECTOR_XZ field_4;
    u32        field_8;
    s32        field_C;
    s16        field_10;
    s8         __pad_12[2];
    DVECTOR_XZ field_14;
} s_CollisionState_CC_20;

typedef struct
{
    s_IpdCollisionData*   ipdCollisionData_0;
    u8                    field_4; // Index.
    u8                    field_5;
    SVECTOR3              field_6; // Q7.8 | Probe position?
    s_CollisionState_CC_C  field_C;
    u8                    field_E;
    u8                    field_F;
    u8                    field_10;
    u8                    field_11;
    SVECTOR3              field_12;
    SVECTOR3              field_18;
    s8                    unk_1E[2];
    s_CollisionState_CC_20 field_20;
} s_CollisionState_CC;
STATIC_ASSERT_SIZEOF(s_CollisionState_CC, 56);

typedef struct _CollisionState
{
    u8                 field_0_0  : 8; // Boolean? Code only assigns 1.
    s8                 field_0_8  : 1; // Something to do with collision. `bool` flag that states if there's a displacement?
    s8                 field_0_9  : 1;
    s8                 field_0_10 : 1;
    s8                 field_0_11 : 5;
    u16                flags_2    : 16; /** `e_CollisionFlags` */
    s_func_8006ABC0    field_4;
    s32                field_34;
    s16                field_38;
    s16                field_3A;
    s16                field_3C; // X?
    s16                field_3E; // Z?
    s8*                field_40;
    s_CollisionState_44 field_44;
    q23_8              field_7C; // Related to ground height?
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
            s_CollisionState_A8 field_8[4];
        } s_0;
        struct
        {
            q7_8 field_0; // Set to absolute character bottom height.
            q7_8 field_2; // Set to absolute character top height.
            s16  field_4;
            u8   collisionState; /** `e_CharaCollisionState` */
            u8*  field_8;
            s8   unk_C[28];
        } s_1;
    } field_A0;
    u8                 field_C8;
    u8                 unk_C9[1];
    /* 0xCA */ q7_8               groundHeight;
    s_CollisionState_CC field_CC;
    // TODO: Maybe incomplete. Maybe not, added the final padding based on `Collision_Get`.
} s_CollisionState;

/** @brief Global LM model. */
typedef struct _GlobalLm
{
    /* 0x0 */ s_LmHeader* lmHdr;
    /* 0x4 */ s32         fileIdx;
    /* 0x8 */ s32         queueIdx;
} s_GlobalLm;

typedef struct _ModelInfo
{
    /* 0x0 */ s32            field_0; // Bone flags?
    /* 0x4 */ GsCOORDINATE2* coord;
    /* 0x8 */ s_ModelHeader* modelHdr;
    /* 0xC */ s32            modelIdx;
} s_ModelInfo;

/** @brief IPD skeleton model bone. */
typedef struct _Bone
{
    /* 0x0  */ s_ModelInfo modelInfo;
    /* 0x10 */ s8          idx;
               // 3 bytes of padding.
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 20);

/** @brief IPD skeleton model bone node. */
typedef struct _LinkedBone
{
    /* 0x0  */ s_Bone              bone;
    /* 0x14 */ struct _LinkedBone* next;
} s_LinkedBone;
STATIC_ASSERT_SIZEOF(s_LinkedBone, 24);

typedef struct
{
    /* 0x0 */ u8            boneCount;
    /* 0x1 */ u8            boneIdx;
    /* 0x2 */ u8            field_2;
    /* 0x3 */ s8            field_3;
    /* 0x4 */ s_LinkedBone* bones_4;
    /* 0x8 */ s_LinkedBone* bones_8;
    /* 0xC */ s_LinkedBone  bones_C[56];
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
    /* 0x0  */ s8             charaId0_0;  /** `e_CharaId` */
    /* 0x1  */ s8             charaId1_1;  /** `e_CharaId` */
               // 2 bytes of padding.
    /* 0x4  */ s32            animFile0_4; // s_AnmHeader* animFile0_4; // TODO: Needs to be a pointer.
    /* 0x8  */ s_AnmHeader*   animFile1_8;
    /* 0xC  */ s32            animBufferSize1_C;
    /* 0x10 */ s32            animBufferSize2_10;
    /* 0x14 */ GsCOORDINATE2* npcBoneCoords;
} s_CharaAnimDataInfo;
STATIC_ASSERT_SIZEOF(s_CharaAnimDataInfo, 24);

/** Related to weapon attacks. Stats, SFX IDs, damange values, etc.? */
typedef struct
{
    /* 0x0  */ q4_12 field_0;
    /* 0x2  */ q3_12 field_2;
    /* 0x4  */ u16   field_4; // Related to damage. Multiplier?
    /* 0x6  */ s8    field_6; // Accessed by `func_8008BF84` as `u16`
    /* 0x7  */ s8    unk_7;
    /* 0x8  */ u8    field_8;   // Accessed by `func_8008BF84` as `u16`
    /* 0x9  */ u8    charaId_9; /** `e_CharaId` */
    /* 0xA  */ u8    field_A;   // Accessed by `func_8008BF84` as `u16`
    /* 0xB  */ u8    field_B;
    /* 0xC  */ q4_12 field_C;
    /* 0xE  */ u8    field_E;  // Keyframe index offset?
    /* 0xF  */ u8    field_F;  // Keyframe index offset?
    /* 0x10 */ u8    field_10; // State.
    /* 0x11 */ u8    field_11;
    /* 0x12 */ u8    field_12; // SFX ID subgroup. Uses values 0-4.
    /* 0x13 */ s8    __pad_13;
    /* 0x14 */ u32*  unk_14; // Some pointer. All entries have the same value `D_800AD4C4`.
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

/** @brief Collision point data. */
typedef struct _CollisionPoint
{
    /* 0x0  */ VECTOR3     position; /** Q19.12 */
    /* 0xC  */ s_Collision collision;
    /* 0x18 */ s32         field_18; // Count of points in circle?
} s_CollisionPoint;

typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800BCDA8;
STATIC_ASSERT_SIZEOF(s_800BCDA8, 4);

/** @brief Speed zone. Defines a volume used for player speed modulation. */
typedef struct _SpeedZone
{
    /* 0x0 */ s8   type; /** `e_SpeedZoneType` */
              // 1 byte of padding.
    /* 0x2 */ q11_4 minX;
    /* 0x4 */ q11_4 maxX;
    /* 0x6 */ q11_4 minZ;
    /* 0x/ */ q11_4 maxZ;
} s_SpeedZone;

/** @brief Water zone. Defines a volume used for visual water effects. */
typedef struct _WaterZone
{
    /* 0x0 */ u8    isEnabled; /** `bool` */
              // 1 byte of padding.
    /* 0x2 */ q11_4 illumination;
    /* 0x4 */ q11_4 minX;
    /* 0x6 */ q11_4 maxX;
    /* 0x8 */ q11_4 minZ;
    /* 0xA */ q11_4 maxZ;
} s_WaterZone;

/** @brief Character model. */
typedef struct _CharaModel
{
    /* 0x0  */ u8            charaId;  /** `e_CharaId` */
    /* 0x1  */ u8            isLoaded; /** `bool` */
               // 2 bytes of padding.
    /* 0x4  */ s32           queueIdx;
    /* 0x8  */ s_LmHeader*   lmHdr;
    /* 0xC  */ s_FsImageDesc texture;
    /* 0x14 */ s_Skeleton    skeleton;
} s_CharaModel;
STATIC_ASSERT_SIZEOF(s_CharaModel, 1376);

/** @brief Map GFX info. */
typedef struct _MapGfxInfo
{
    /* 0x0 */ s16                plmFileIdx_0;
    /* 0x2 */ char               tag_2[4];
    /* 0x6 */ u8                 flags_6; /** `e_MapFlags` */
              // 1 byte of padding.
    /* 0x8 */ const s_WaterZone* waterZones_8;
    /* 0xC */ const s_SpeedZone* speedZones_C;
} s_MapInfo;

// Rough name.
typedef struct _WorldObjectMetadata
{
    /* 0x0 */ u_Filename name_0;
    /* 0x8 */ s8         field_8;
    /* 0x9 */ s8         lmIdx_9; /** Set to 2 when found in `g_Map.globalLm.lmHdr` and 3-6 if found in `g_Map.ipdActive[i] (i + 3)`. */
} s_WorldObjectMetadata;

// Rough name.
typedef struct _WorldObjectModel
{
    /* 0x0  */ s_ModelInfo           modelInfo;
    /* 0x10 */ s_WorldObjectMetadata metadata;
} s_WorldObjectModel;
STATIC_ASSERT_SIZEOF(s_WorldObjectModel, 28);

/** @brief Geometry-space world object to draw. */
typedef struct _WorldObject
{
    /* 0x0    */ s_WorldObjectModel* model;
    /* 0x4+0  */ s32                 positionX  : 18;
    /* 0x4+18 */ s32                 positionY  : 14;
    /* 0x8+0  */ s32                 positionZ : 18;
    /* 0x8+18 */ s32                 __pad_8_18 : 14;
    /* 0xC+0  */ s32                 rotationX  : 10;
    /* 0xC+10 */ s32                 rotationY  : 12;
    /* 0xC+22 */ s32                 rotationZ  : 10;
} s_WorldObject;
STATIC_ASSERT_SIZEOF(s_WorldObject, 16);

/** @brief World-space trigger zone. */
typedef struct _TriggerZone
{
    /* 0x0+0  */ u8  isEndOfArray : 1;  /** `bool` | Marks last entry. */
    /* 0x0+1  */ s32 positionX    : 10; /** Meter steps. */
    /* 0x0+11 */ s32 positionZ    : 10; /** Meter steps. */
    /* 0x0+21 */ u32 sizeX        : 4;  /** Meter steps. */
    /* 0x0+25 */ u32 sizeZ        : 4;  /** Meter steps. */
    /* 0x0+29 */ u32 height       : 3;  /** Half-meter steps. Used to set `s_func_8006F338::field_2C` which is then copied by `func_8006F250`. */
} s_TriggerZone;
STATIC_ASSERT_SIZEOF(s_TriggerZone, 4);

/** @brief Hand-held player item. */
typedef struct _HeldItem
{
    /* 0x0  */ s32           itemId; /** `e_InvItemId` */
    /* 0x4  */ s32           queueIdx;
    /* 0x8  */ char*         textureName;
    /* 0xC  */ s_FsImageDesc imageDesc;
    /* 0x14 */ s_LmHeader*   lmHdr;
    /* 0x18 */ s_Bone        bone;
} s_HeldItem;
STATIC_ASSERT_SIZEOF(s_HeldItem, 44);

/** @brief World GFX workspace.
 * TODO: Could be `s_RendererWork`? Will depend on where other data resides.
 * Will: `s_WorldModelWork` fits better, this is mainly responsible for handling model data.
 * `s_WorldEnvWork` should have this name as it is used for general GFX.
 * Will (2): Maybe isn't supposed to be something exclusively graphic related, but rather
 * general in-game world struct, as it also contains triggers and camera information.
 */
typedef struct _WorldGfxWork
{
    /* 0x0    */ s_MapInfo*        mapInfo;
    /* 0x4    */ u8                useStoredPoint; /** `bool` */
    /* 0x5    */ s8                __pad_5[3];
    /* 0x8    */ VECTOR3           ipdSamplePoint; /** Used by IPD logic to sample which chunks to load or unload. */
    /* 0x14   */ u8*               charaLmBuffer;
    /* 0x18   */ s_CharaModel*     registeredCharaModels[Chara_Count];
    /* 0xCC   */ s_CharaModel      charaModels[CHARA_GROUP_COUNT];
    /* 0x164C */ s_CharaModel      harryModel;
    /* 0x1BAC */ s_HeldItem        heldItem; /** Item held by the player. */
    /* 0x1BD8 */ s_TriggerZone*    triggerZone;
    /* 0x1BDC */ VC_CAMERA_INTINFO vcCameraInternalInfo; /** Debug camera info. */
    /* 0x1BE4 */ s_LmHeader        itemLmHdr;
    /* 0x1BF4 */ u8                itemLmData[4096 - sizeof(s_LmHeader)]; // 4kb allocated for 2.75kb game files.
    /* 0x2BE4 */ s32               itemLmQueueIdx;
    /* 0x2BE8 */ s32               objectCount;                     /** `objects` size. */
    /* 0x2BEC */ s_WorldObject     objects[WORLD_OBJECT_COUNT_MAX]; /** World objects to draw. */
} s_WorldGfxWork;
STATIC_ASSERT_SIZEOF(s_WorldGfxWork, 11708);

/** @brief IPD map geometry chunk. */
typedef struct _IpdChunk
{
    /* 0x0  */ s_IpdHeader* ipdHdr;
    /* 0x4  */ s32          queueIdx;
    /* 0x8  */ s16          cellX;
    /* 0xA  */ s16          cellZ;
    /* 0xC  */ q19_12       distance0;
    /* 0x10 */ q19_12       distance1;
    /* 0x14 */ u8           materialCount;
    /* 0x15 */ s8           __pad_15[3];
    /* 0x18 */ s32          outsideCount;
} s_IpdChunk;
STATIC_ASSERT_SIZEOF(s_IpdChunk, 28);

typedef struct _IpdRow
{
    s16 idx[16];
} s_IpdColumn;
STATIC_ASSERT_SIZEOF(s_IpdColumn, 32);

typedef struct _ActiveTextures
{
    /* 0x0 */ s32        count;
    /* 0x4 */ s_Texture* textures[10];
} s_ActiveTextures;

typedef struct _IpdTextures
{
    /* 0x0   */ s_ActiveTextures fullPage;
    /* 0x2C  */ s_ActiveTextures halfPage;
    /* 0x58  */ s_Texture        fullPageTextures[8];
    /* 0x118 */ s_Texture        halfPageTextures[2];
} s_IpdTextures;
STATIC_ASSERT_SIZEOF(s_IpdTextures, 328);

typedef struct _Map
{
    /* 0x0   */ s_IpdCollisionData collisionData; // Default chunk collision data?
    /* 0x134 */ s32                texFileIdx;
    /* 0x138 */ s_GlobalLm         globalLm;
    /* 0x144 */ char               mapTag[4];
    /* 0x148 */ s32                mapTagSize;
    /* 0x14C */ s32                ipdFileIdx;
    /* 0x150 */ s_IpdHeader*       ipdBuffer;
    /* 0x154 */ s32                ipdBufferSize;
    /* 0x158 */ s32                ipdActiveCount;
    /* 0x15C */ s_IpdChunk         ipdActive[4];
    /* 0x1CC */ s_IpdColumn        ipdGrid[18];
    /* 0x40C */ s8                 unk_40C[32]; // Could be one extra row in table above.
    /* 0x42C */ s_IpdColumn*       ipdGridCenter;
    /* 0x430 */ s_IpdTextures      ipdTextures;
    /* 0x578 */ q19_12             positionX;
    /* 0x57C */ q19_12             positionZ;
    /* 0x580 */ s32                cellX;
    /* 0x584 */ s32                cellZ;
    /* 0x588 */ bool               isExterior;
} s_Map;
STATIC_ASSERT_SIZEOF(s_Map, 1420);

/** @brief World fog info. */
typedef struct _Fog
{
    /* 0x0  */ s32     nearDistance;
    /* 0x4  */ q23_8   farDistance; // "DrawDistanmce" in SHME, "has no effect when fog is disabled".
    /* 0x8  */ s32     depthShift;  // "FogThing1" from SHME. Affects the distance where fog begins.
    /* 0xC  */ s32     intensity;   // "FogThing2" from SHME. Affects the distance where fog begins.
    /* 0x10 */ CVECTOR color;
} s_Fog;

// Related to `s_PointLight`.
typedef struct
{
    VECTOR3 field_0[2][1];
} s_WorldEnvWork_84;

/** @brief Dynamic point light. */
typedef struct _PointLight
{
    /* 0x0  */ s32               field_0; // Light intensity in Q4?
    /* 0x4  */ q3_12             lensFlareIntensity;
    /* 0x8  */ q19_12            intensity;
    /* 0xC  */ SVECTOR           direction; /** Q3.12 */
    /* 0x14 */ VECTOR3           position;  /** Q19.12 */
    /* 0x20 */ SVECTOR           rotation;  /** Q3.12 */
    /* 0x28 */ SVECTOR           field_28;  // Q8 light position for matrix?
    /* 0x30 */ SVECTOR           field_30;  // Light offset?
    /* 0x38 */ s_WorldEnvWork_84 field_38[3];
} s_PointLight;

/** @brief World environment workspace.
 *
 * Holds fog distances and ramps, lighting and color parameters, water zone references, and other per-map environmental
 * data used for world drawing.
 */
typedef struct _WorldEnvWork
{
    /* 0x0   */ u8           field_0;      // `bool`?
    /* 0x1   */ u8           isFogEnabled; /** `bool` */
    /* 0x2   */ u8           field_2;
    /* 0x3   */ u8           field_3; // Enviroment lighting.
    /* 0x4   */ s_WaterZone* waterZones;
    /* 0x8   */ s32          screenBrightness;
    /* 0xC   */ s_Fog        fog;
    /* 0x20  */ s32          field_20; // Map lighting.
    /* 0x24  */ CVECTOR      field_24; // Character color lighting.
    /* 0x28  */ CVECTOR      worldTintColor;
    /* 0x2C  */ MATRIX       colorMat;
    /* 0x50  */ s_PointLight light;
    /* 0xCC  */ u8           fogRamp[128]; // Fog-related values based on `fog.nearDistance`/`fog.farDistance`.
    /* 0x14C */ u16          field_14C;
} s_WorldEnvWork;

typedef struct
{
    u8      field_0; // `bool`?
    u8      field_1; // `bool`?
    u8      field_2; // `bool`?
    u8      field_3;
    s8      unk_4[4];
    s16     field_8;
    s16     field_A;
    VECTOR3 field_C; // Q19.12
    s8      unk_18[4];
    s32     field_1C;
    q19_12  field_20;
} s_800C4818;

typedef struct
{
    u8  unk_0[4];
    s16 field_4;
    s16 field_6; // Keyframe index or time.
} s_800C44F0; // Probable size: 8 bytes.

/** @brief Character file info.
 * Holds file IDs of anim/model/texture for each `e_CharaId` along with some data used in VC camera code.
 */
typedef struct _CharaFileInfo
{
    /* 0x0    */ s16            animFileIdx;
    /* 0x2    */ s16            modelFileIdx;
    /* 0x4+0  */ s16            textureFileIdx    : 16;
    /* 0x4+16 */ q8_8           field_6           : 10;
    /* 0x4+26 */ u16            materialBlendMode : 6; /** `e_BlendMode` */
    /* 0x8    */ s_FsImageDesc* field_8;               // TODO: Extra texture pointer? Usually `NULL` in `CHARA_FILE_INFOS`.
    /* 0xC+0  */ u16            cameraAnchor  : 2;     /** `e_CameraAnchor` */
    /* 0xC+2  */ q19_12         cameraOffsetY : 14;
                 // 2 bytes of padding.
} s_CharaFileInfo;
STATIC_ASSERT_SIZEOF(s_CharaFileInfo, 16);

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
    /* 0x0    */ q19_12 positionX;
    /* 0x4+0  */ u32    mapIdx_4_0      : 5; /** `e_PaperMapIdx`? */
    /* 0x4+5  */ u32    field_4_5       : 4;
    /* 0x4+9  */ u32    loadingScreenId : 3; /** `e_LoadingScreenId` */
    /* 0x4+12 */ u32    field_4_12      : 4;
    /* 0x4+16 */ q24_8  triggerParam0   : 8; // Usually a `Q8_ANGLE`.
    /* 0x4+24 */ u32    triggerParam1   : 8;
    /* 0x8    */ q19_12 positionZ;
} s_MapPoint2d;
STATIC_ASSERT_SIZEOF(s_MapPoint2d, 12);

/** @brief Character spawn info. */
typedef struct _SpawnInfo
{
    /* 0x0   */ q19_12 positionX;
    /* 0x4   */ s8     charaId; /** `e_CharaId` */
    /* 0x5   */ q0_8   rotationY;
    /* 0x6   */ s8     flags_6;               /** `e_SpawnFlags` | Copied to `stateStep` in `s_Model`, with `controlState = 0`. */
    /* 0x7+0 */ s32    gameDifficultyMin : 4; /** `e_GameDifficulty` | Minimum difficulty required for successful spawn. */
    /* 0x8   */ q19_12 positionZ;
} s_SpawnInfo;
STATIC_ASSERT_SIZEOF(s_SpawnInfo, 12);

/** @brief Special map-specific Harry anim data. */
typedef struct
{
    s16   status; /** Packed anim status. See `s_ModelAnim::status`. */
    s16   status_2; /** Packed anim status. See `s_ModelAnim::status`. */
    q3_12 time;   /** Fixed-point anim time. */
    s16   keyframeIdx_6;
} s_UnkStruct3_Mo;
STATIC_ASSERT_SIZEOF(s_UnkStruct3_Mo, 8);

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
    u8    field_0;
    u8    field_1;
    u8    field_2;
    u8    field_3;
    s16   field_4;
    s16   field_6;
    s16   field_8;
    s16   field_A;
    s16   field_C;
    s16   field_E;
    q3_12 field_10;
    s16   field_12;
    s32   field_14;
    s32   field_18;
    s32   field_1C;
} s_MapOverlayHeader_7C;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader_7C, 32);

typedef struct
{
    s32    field_0[4];
    s16    field_10[4];
    q19_12 field_18[4];
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
    s8     __pad_76[2];
    u8     field_78;
} s_MapOverlayHeader_94;

/** TODO: `g_MapOverlayHeader` is part of the map overlay BIN files. Maybe should be moved to `maps/shared.h`.
 * If field has a comment that lists only certain map(s) it means all others set this field to 0.
 * func(?) means the signature is unknown and a default void() was selected for now.
 */
typedef struct _MapOverlayHeader
{
    /* 0x0   */ s_MapInfo*             mapInfo;
    /* 0x4   */ u8                     (*mapRoomIdxGet)(q19_12 posX, q19_12 posY); // Called by `Savegame_MapRoomIdxUpdate`.
    /* 0x8   */ s8                     field_8;
    /* 0xC   */ s32                    (*func_C)();
                // 3 bytes of padding.
    /* 0x10  */ void                   (*bgmEvent)(bool);
    /* 0x14  */ s8                     bgmIdx;
    /* 0x15  */ u8                     ambientAudioIdx; // Ambient file index from `g_AmbientVabTaskLoadCmds`.
    /* 0x16  */ s8                     field_16;        // Set ambient tint and draw distance.
                                                        // A value of 3 sets the map to night.
                                                        // A value of 2 will sets the map to use a tint used during the hallaway
                                                        // intro.
                                                        // Giving this and next variable a name will require further investigation
                                                        // of `particle.c` code.
    /* 0x17  */ s8                     field_17;        // Set weather to play. Rain, heavy rain, or snow.
    /* 0x18  */ void                   (**loadingScreenFuncs)();
    /* 0x1C  */ s_MapPoint2d*          mapPoints;
    /* 0x20  */ void                   (**mapEventFuncs)(); /** Points to array of event functions. */
    /* 0x24  */ s_EventData*           mapEvents;
    /* 0x28  */ GsCOORDINATE2*         field_28; // Bone coords of some kind.
    /* 0x2C  */ u8*                    loadableItems;
    /* 0x30  */ const char**           mapMessages;
    /* 0x34  */ s_AnimInfo*            harryMapAnimInfos; /** Map-specific anim infos for Harry (for anims 38+). */
    /* 0x38  */ s_UnkStruct3_Mo*       field_38; // Array of 40?
    /* 0x3C  */ void                   (*initWorldObjects)(void);
    /* 0x40  */ void                   (*updateWorldObjects)(void);
    /* 0x44  */ void                   (*func_44)();
    /* 0x48  */ void                   (*npcSpawnEvent)();
    /* 0x4C  */ s_MapHdr_field_4C*     unkTable1_4C; // Related to collision?
    /* 0x50  */ s16                    unkTable1Count_50;
                // 2 bytes of padding.
    /* 0x54  */ s_BloodSplat*          bloodSplats;
    /* 0x58  */ s16                    bloodSplatCount;
                // 2 bytes of padding.
    /* 0x5C  */ s_MapOverlayHeader_5C* field_5C;
    /* 0x60  */ void                   (*func_60)(s32 idx, bool arg1);
    /* 0x64  */ s32                    (*func_64)(POLY_FT4** poly, s32);
    /* 0x68  */ s32                    (*func_68)(POLY_FT4** poly, s32);
    /* 0x6C  */ void                   (*func_6C)();
    /* 0x70  */ s32                    (*func_70)(POLY_FT4** poly, s32);
    /* 0x74  */ void                   (*func_74)();
    /* 0x78  */ s32                    (*func_78)(POLY_FT4** poly, s32);
    /* 0x7C  */ s_MapOverlayHeader_7C* field_7C; // Only map1_s01, map6_s04.
    /* 0x80  */ void                   (*func_80)();
    /* 0x84  */ s32                    (*func_84)(POLY_FT4** poly, s32);
    /* 0x88  */ s32*                   func_88;                          // Only map0_s01, map7_s01.
    /* 0x8C  */ s32                    (*func_8C)(POLY_FT4** poly, s32); // Only map0_s01, map7_s01.
    /* 0x90  */ s32                    (*func_90)(POLY_FT4** poly, s32); // Only map5_s00.
    /* 0x94  */ s_MapOverlayHeader_94* field_94;                         // Only map1_s02, map1_s03.
    /* 0x98  */ s32                    (*func_98)(POLY_FT4** poly, s32); // Only map1_s02, map1_s03.
    /* 0x9C  */ void                   (*func_9C)();                     // Only map1_s02, map1_s03.
    /* 0xA0  */ void*                  ptr_A0;                           // M1S03 only, pointer to `s_800E3A40` array.
    /* 0xA4  */ s32                    (*func_A4)(POLY_FT4** poly, s32); // Only map1_s03.
    /* 0xA8  */ void                   (*func_A8)();                     // Only map6_s02.
    /* 0xAC  */ s32                    (*func_AC)(POLY_FT4** poly, s32); // Only map4_s03, map4_s05.
    /* 0xB0  */ s32                    (*func_B0)(POLY_FT4** poly, s32); // Only map4_s03, map4_s05.
    /* 0xB4  */ s32                    (*func_B4)(POLY_FT4** poly, s32); // Only map1_s03, map4_s05, map6_s01, map6_s02, map5_s01.
    /* 0xB8  */ void                   (*func_B8)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    /* 0xBC  */ void                   (*func_BC)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    /* 0xC0  */ void                   (*func_C0)();
    /* 0xC4  */ void                   (*playerMatchArmAnimDisable)();
    /* 0xC8  */ void                   (*playerControlFreeze)();
    /* 0xCC  */ void                   (*playerControlUnfreeze)(bool setIdle);
    /* 0xD0  */ bool                   (*func_D0)(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount); // 0x800C964C
    /* 0xD4  */ s32                    (*func_D4)(s32 playerExtraState); // Points to `sharedFunc_800D2C7C_0_s00` which has `void` return type, but changing this funcptr causes mismatch in `func_80085EB8`
    /* 0xD8  */ void                   (*func_D8)();                     // Assumed return type.
    /* 0xDC  */ void                   (*playerAnimLock)(void);
    /* 0xE0  */ void                   (*isPlayerAnimLocked)();
    /* 0xE4  */ s32                    (*playerAnimUnlock)(s_SubCharacter*, s32); // Assumed return type.
    /* 0xE8  */ s64                    (*func_E8)(s_SubCharacter*);               // Is it really `s64`???
    /* 0xEC  */ bool                   (*playerMoveDistIsZero)();
    /* 0xF0  */ void                   (*playerMoveDistClear)();
    /* 0xF4  */ void                   (*playerFallBackward)();
    /* 0xF8  */ void                   (*func_F8)();
    /* 0xFC  */ void                   (*playerDamageFeetFront)();
    /* 0x100 */ void                   (*func_100)();
    /* 0x104 */ void                   (*func_104)();
    /* 0x108 */ s32                    (*func_108)();
    /* 0x10C */ void                   (*func_10C)();
    /* 0x110 */ void                   (*func_110)();
    /* 0x114 */ void                   (*func_114)();
    /* 0x118 */ void                   (*func_118)();
    /* 0x11C */ void                   (*func_11C)();
    /* 0x120 */ void                   (*func_120)();
    /* 0x124 */ void                   (*func_124)(s_SubCharacter*); // Assumed return type.
    /* 0x128 */ s32                    (*playerRunTimerReset)(s_SubCharacter* player);
    /* 0x12C */ s32                    (*charaLock)(s_SubCharacter* chara);
    /* 0x130 */ void                   (*charaIsLockedCheck)(s_SubCharacter* chara);
    /* 0x134 */ s32                    (*charaUnlock)(s_SubCharacter* chara);
    /* 0x138 */ s32                    (*charaAnimPlaybackStateGet)(s_SubCharacter* chara);
    /* 0x13C */ bool                   (*func_13C)(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);
    /* 0x140 */ void                   (*charaVisibleSet)(s_SubCharacter* chara);
    /* 0x144 */ void                   (*charaInvisibleSet)(s_SubCharacter* chara);
    /* 0x148 */ bool                   (*func_148)(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch);
    /* 0x14C */ bool                   (*func_14C)(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId); // Play SFX?
    /* 0x150 */ s32                    (*charaAnimStartKeyframeIdxGet)(s_SubCharacter* chara);
    /* 0x154 */ void                   (*charaCollisionReset)(s_SubCharacter* chara);
    /* 0x158 */ void                   (*func_158)(q19_12 x, q19_12 z); // Only map1_s05, map1_s06.
    /* 0x15C */ void                   (*func_15C)();                   // Only map5_s01.
    /* 0x160 */ void                   (*func_160)();                   // Only map5_s01.
    /* 0x164 */ void                   (*func_164)();                   // Only map5_s01.
    /* 0x168 */ void                   (*particlesUpdate)(s32 unused, s32 mapId, s32);
    /* 0x16C */ void                   (*enviromentSet)(s8, u32);
    /* 0x170 */ void                   (*func_170)();
    /* 0x174 */ void                   (*func_174)();
    /* 0x178 */ void                   (*particleHyperBlasterBeamDraw)(VECTOR3* vec0, q19_12* rotX, q19_12* rotY);
    /* 0x17C */ void                   (*particleBeamDraw)(const VECTOR3* from, const VECTOR3* to);
    /* 0x180 */ void                   (*particleSoundStop)();
    /* 0x184 */ s32*                   windSpeedX;
    /* 0x188 */ s32*                   windSpeedZ;
    /* 0x18C */ s32*                   data_18C;
    /* 0x190 */ s32*                   data_190;
    /* 0x194 */ void                   (*charaUpdateFuncs[Chara_Count])(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords); /** Guessed params. Funcptrs for each `e_CharaId`, set to 0 for IDs not included in the map overlay. Called by `Game_NpcUpdate`. */
    /* 0x248 */ s8                     charaGroupIds[CHARA_GROUP_COUNT]; /** `e_CharaId` values where if `s_SpawnInfo::charaId == Chara_None`, `charaGroupIds[0]` is used for `charaSpawns[0]` and `charaGroupIds[1]` for `charaSpawns[1]`. */
    /* 0x24C */ s_SpawnInfo            charaSpawns[2][16];               /** Array of character type/position/flags. `flags_6 == 0` are unused slots? Read by `Game_NpcRoomInitSpawn`. */
    /* 0x3CC */ VC_ROAD_DATA           cameraPaths[100];
    /* 0xD2C */ s_TriggerZone          triggerZones[200];
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 0x104C);

typedef struct _MapMsgSelect
{
    /* 0x0 */ s8 maxIdx;
    /* 0x1 */ u8 selectedEntryIdx;
} s_MapMsgSelect;

typedef struct _MapEffectsPresetIdxs
{
    u8 presetIdx1_0;
    u8 presetIdx2_1;
} s_MapEffectsPresetIdxs;

typedef struct
{
    q23_8 field_0; // X position.                } Offset ray hit position?
    q23_8 field_4; // Z position.                }
    q7_8  field_8; // Y position, but why `s16`? }
    q7_8  field_A; // Y??
    q7_8  field_C; // Some kind of bound or threshold or radius?
    s16   field_E;
} s_RayState_6C;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_RayState_8C;

/** @brief State for an in-progress ray trace. Contains pointers to active characters among other things. */
typedef struct
{
    s32              field_0;
    s16              field_4; // Collision flags.
    s16              field_6;
    q7_8             field_8; // Hit distance? `SHRT_MAX` if no valid hit.
    s8               unk_A[2];
    q19_12           field_C;  // } Q19.12 `VECTOR3`
    q19_12           field_10; // }
    q19_12           field_14; // }
    s8               unk_18[4];
    q7_8             field_1C; // Distance Z?
    s8               unk_1E[2];
    s_SubCharacter*  field_20;
    q3_12            field_24; // X
    q3_12            field_26; // Z
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
    s16              field_5C; // 
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

/** @brief Ray trace line of sight info. */
typedef struct _RayTrace
{
    /* 0x0  */ s8              hasHit; /** `bool` */
    /* 0x1  */ u8              field_1;
    /* 0x2  */ s8              __pad_2[2];
    /* 0x4  */ VECTOR3         target; /** Q19.12 */
    /* 0x10 */ s_SubCharacter* character;
    /* 0x14 */ q19_12          field_14; // Hit distance X?
    /* 0x18 */ q19_12          field_18; // Hit distance Z?
    /* 0x1C */ q3_12           field_1C; // Angle? Counter??
} s_RayTrace;

typedef struct _CollisionResult
{
    /* 0x0  */ VECTOR3 offset_0; /** Q19.12 */
    /* 0xC  */ q19_12  groundHeight;
    /* 0x10 */ s16     field_10;
    /* 0x12 */ s16     field_12;
    /* 0x14 */ s8      field_14; /** `e_FloorType` */
    /* 0x18 */ q19_12  field_18;
} s_CollisionResult;

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
            DVECTOR screenPos_3DC;
            s32     depthP_3E0;
            s16     rotMatrix_3E4[3][3]; // Truncated `MATRIX` without the `long t[3];` transfer vector?
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

// Something for inventory items.
typedef struct
{
    /* 0x0  */ q3_12   positionY;
    /* 0x2  */ q3_12   field_2; // Move dist?
    /* 0x4  */ q3_12   field_4; // Angle.
    /* 0x6  */ s16     field_6;
    /* 0x8  */ s16     field_8;
    /* 0xA  */ s8      __pad_A[2];
    /* 0xC  */ SVECTOR field_C;  // Q3.12 | Offset?
    /* 0x14 */ SVECTOR position; /** Q3.12 */
} s_800AE204;

typedef struct
{
    /* 0x0 */ s_800AE204* ptr_0;
    /* 0x4 */ u8          count_4;
    /* 0x5 */ u8          unk_5;
    /* 0x6 */ q7_8        field_6;
    /* 0x8 */ u8          field_8;
    /* 0x9 */ u8          field_9;
    /* 0xA */ u8          field_A;
    /* 0xB */ u8          field_B;
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
    VECTOR3   field_2C; // Q23.8 | Set as grid-aligned player position in `func_80065B94`.
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
    s16 field_2; // XYZ? X and Y swapped?
    s32 field_4; //
    s32 field_8; //
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
    q3_12   field_34[24];
    q3_12   field_64[24];
    q3_12   field_94[24];
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
        DVECTOR field_0[4]; // Q19.12
        s32     raw_0[4];
    } u_field_EC;
    union
    {
        DVECTOR field_0[4];
        s32     raw_0[4];
    } u_field_FC; // Q3.12 | Positions or offsets.
    q19_12  field_10C[4]; // X offsets?
    q19_12  field_11C[4]; // Z offsets?
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
    q19_12          field_178;
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
    q19_12          field_1E8;
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
    MATRIX  field_0; // View matrix?
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

/** Array containg file IDs used for each `e_CharaId`, used in `Fs_QueueStartReadAnm`. */
extern s_CharaFileInfo CHARA_FILE_INFOS[Chara_Count]; // 0x800A90FC

extern s_MapEffectsInfo MAP_EFFECTS_INFOS[21];

extern s_StructUnk3 D_800A952C;

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

extern void (*g_SysStateFuncs[])(void);

extern s32 D_800A9A68;

/** Counts the amount of times that demos has been play in the current game session. */
extern s8 g_Demo_ReproducedCount;

extern RECT D_800A9A6C; // `RECT<320, 256, 160, 240>`, only used in `SysState_Fmv_Update`?

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

extern u8 D_800AA604[41][16];

extern u8 D_800AE185;

extern u8 D_800AE186;

extern s8 __pad_bss_800BCD81[3];

extern s32 g_DeltaTimeCpy;

extern s32 __pad_bss_800BCD88[2];

extern s_EventData* g_ItemTriggerEvents[];

extern s32 __pad_bss_800BCD94[5];

/** Radio SFX data. */
extern s_800BCDA8 D_800BCDA8[2];

extern s_MapPoint2d D_800BCDB0;

extern s32 __pad_bss_800BCDD0;

/** Related to special item interactions. */
extern s32 g_ItemTriggerItemIds[5];

extern u8 D_800BCDD4;

extern s8 __pad_bss_800BCDD5[3];

extern s_EventData* g_MapEventData;

/** `e_InvItemId` | related to displaying items. */
extern u8 D_800AE187;

extern s16 D_800AE1A8;

extern s_800AE204 D_800AE204[26];

extern s32 g_Items_PickupAnimState;

extern q19_12 g_Items_PickupScale;

extern s_800AE4DC D_800AE4DC[3];
extern SVECTOR    D_800AE500[4];

extern s16 D_800AE520[];

extern s16 D_800AE564[];

extern s16 D_800AE5CC[];

extern s16 D_800AE5F0[];

extern u8 D_800AE700[];

/** `[1]` contains relative paper map file indices. */
extern u8 D_800AE740[][2];

extern bool D_800AE770;

extern q3_12 g_Player_FlexRotationY;

extern q3_12 g_Player_FlexRotationX;

/** Related to player. */
extern u8 D_800AF220;

/** @brief Last weapon selected. While it is being assigned the value of
 * `g_SysWork::playerCombat::weaponAttack` this time it is used to determine
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
extern s_CollisionPoint g_CollisionPointCache;

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern s32 D_800AFD3C;

extern s32 D_800AFD44;

extern s32 D_800AFD60;

extern s32 D_800AFD9C;

extern SVECTOR D_800AFDB0;

extern s32 D_800AFDEC;

extern u8 g_Items_GunsMaxLoadAmmo[36]; // Max loaded ammo that a weapon can hold. 0x800AD4A0

extern const char* INVENTORY_ITEM_NAMES[];

extern const char* g_ItemDescriptions[];

extern s_FsImageDesc D_800A90A4;

extern s_FsImageDesc D_800A90B4;

extern s_SubCharacter D_800BA00C; // Often passed to `Ray_NpcToPlayerLosHitCheck`, might not be full `s_SubCharacter`?

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

extern u16 g_CollisionFlags;

extern s_WorldGfxWork g_WorldGfxWork;

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s16 D_800C16A4;

extern s16 D_800C391E;

extern s8 D_800C39A0;

/** Functions from `bodyprog_8003AB28` access `g_WorldEnvWork` as constant, but some functions from `bodyprog_80055028` write to it.
 * It appears that g_WorldEnvWork is intended to be defined inside `bodyprog_80055028` as writable and declared as read-only (`const`) outside of it.
 */
// extern s_WorldEnvWork g_WorldEnvWork;

extern GsCOORDINATE2* D_800C42B8; // Set to view coord.

extern VECTOR3 D_800C42C0;

extern VECTOR3* D_800C42CC;

extern u16 D_800C42D0;

extern u16 D_800C42D2;

extern s_800C42E8 D_800C42E8[24];

extern s16 D_800C4408;

extern s16 __pad_bss_800C440A;

extern GsCOORDINATE2* D_800C440C;

extern GsCOORDINATE2* D_800C4410;

/** Flags. */
extern s8 D_800C4414;

extern s8 __pad_bss_800C4415[3];

extern s_800C4418 D_800C4418;

extern q3_12 D_800C4454;

extern s8 D_800C447A;

extern s16 D_800AEEDC[][2]; // Type assumed.

extern s16 D_800AEF78[][2]; //  Type assumed.

extern s16 D_800AF014[];

extern s16 D_800AF04C[];

extern q3_12 D_800AF070[];

extern q3_12 D_800AF1FC[];

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

extern s_RayTrace D_800C47F8;

extern s_800C4818 D_800C4818;

extern s32 D_800C48F0;

extern u8 D_800AD480[24];

/** Weapon attacks. */
extern s_800AD4C8 D_800AD4C8[70];

extern const s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

extern s16 SQRT[100];

/** @brief Sets the collision shapes of a character from keyframe collision data.
 *
 * @param chara Character to update.
 * @param keyframe Keyframe collision data.
 */
#define Chara_CollisionSet(chara, keyframe)                                         \
{                                                                                   \
    s32 __temp;                                                                     \
                                                                                    \
    chara->collision.box.top = keyframe.box.top;                                    \
                                                                                    \
    __temp                      = keyframe.box.bottom;                              \
    chara->collision.box.bottom = __temp;                                           \
    chara->collision.box.height = keyframe.box.height;                              \
                                                                                    \
    __temp                                    = keyframe.box.offsetY;               \
    chara->collision.box.offsetY              = __temp;                             \
    chara->collision.shapeOffsets.cylinder.vx = keyframe.shapeOffsets.cylinder.vx;  \
                                                                                    \
    __temp                                    = keyframe.shapeOffsets.cylinder.vz;  \
    chara->collision.shapeOffsets.cylinder.vz = __temp;                             \
    chara->collision.cylinder.radius          = keyframe.box.field_8;               \
    chara->collision.shapeOffsets.box.vx      = keyframe.shapeOffsets.box.vx;       \
                                                                                    \
    __temp                               = keyframe.shapeOffsets.box.vz;            \
    chara->collision.shapeOffsets.box.vz = __temp;                                  \
                                                                                    \
    __temp                            = keyframe.box.field_A;                       \
    chara->collision.cylinder.field_2 = __temp;                                     \
}

/** @brief Alternative to `Chara_CollisionSet`. TODO: Can they be merged into one? */
#define Chara_CollisionSetAlt(chara, keyframe)                                     \
{                                                                                  \
    s32 __temp;                                                                    \
    s32 __temp2;                                                                   \
                                                                                   \
    chara->collision.box.top = keyframe.box.top;                                   \
                                                                                   \
    __temp                      = keyframe.box.bottom;                             \
    chara->collision.box.bottom = __temp;                                          \
    chara->collision.box.height = keyframe.box.height;                             \
                                                                                   \
    __temp                       = keyframe.box.offsetY;                           \
    chara->collision.box.offsetY = __temp;                                         \
    chara->collision.shapeOffsets.cylinder.vx = keyframe.shapeOffsets.cylinder.vx; \
                                                                                   \
    __temp                                    = keyframe.shapeOffsets.cylinder.vz; \
    chara->collision.shapeOffsets.cylinder.vz = __temp;                            \
    chara->collision.cylinder.radius          = keyframe.box.field_8;              \
    chara->collision.shapeOffsets.box.vx      = keyframe.shapeOffsets.box.vx;      \
                                                                                   \
    __temp                               = keyframe.shapeOffsets.box.vz;           \
    chara->collision.shapeOffsets.box.vz = __temp;                                 \
                                                                                   \
    __temp2                           = keyframe.box.field_A;                      \
    chara->collision.cylinder.field_2 = __temp2;                                   \
}

// ==========
// FUNCTIONS
// ==========

/** @brief @unused Loading screen text.
 *
 * Just like in earlier builds of Silent Hill 2, the game
 * was intended to show a black screen with
 * "Now loading" text in middle of the screen.
 */
void func_80032CE8(void);

void func_80032D1C(void);

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop(void);

void func_8003943C(void);

/** `SysState_Fmv` update function.
 * Movie to play is decided by `2072 - g_MapEventParam`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update(void);

s32 Map_TypeGet(void);

void func_8003BD48(const s_SubCharacter* chara);

void CharaModel_Free(s_CharaModel* model);

void Ipd_PlayerChunkInit(s_MapOverlayHeader* mapHdr, s32 playerPosX, s32 playerPosZ);

/** @brief Loads map chunks in view and checks if they are loaded.
 *
 * @param `true` if chunks in view are loaded, `false` otherwise.
 */
bool Ipd_ChunkInitCheck(void);

void Gfx_InGameDraw(bool arg0);

void WorldObject_ModelNameSet(s_WorldObjectModel* model, char* newStr);

/** Submits a world object to draw. */
void WorldGfx_ObjectAdd(s_WorldObjectModel* model, const VECTOR3* pos, const SVECTOR3* rot);

/** @unused Returns held item ID. */
s32 WorldGfx_HeldItemIdGet(void);

s32 WorldGfx_PlayerPrevHeldItem(s_PlayerCombat* combat);

/** @brief Loads and sets an item held by the player.
 *
 * @param itemId ID of the held item to load (`e_InvItemId`).
 * @return Model or texture queue index.
 */
s32 WorldGfx_PlayerHeldItemSet(e_InvItemId itemId);

void func_8003D01C(void);

void func_8003D03C(void);

/** Loads the model of an item held by the player? */
void WorldGfx_HeldItemDraw(void);

bool WorldGfx_IsCharaModelPresent(e_CharaId charaId);

/** @brief Sets the material for a character model.
 *
 * @param charaId ID of the character whose model to update.
 * @param blendMode Material blend mode to set (`e_BlendMode`).
 */
void WorldGfx_CharaModelMaterialSet(e_CharaId charaId, s32 blendMode);

/** @brief Makes a character transparent. */
void WorldGfx_CharaModelTransparentSet(e_CharaId charaId, bool isTransparent);

void WorldGfx_CharaFree(s_CharaModel* model);

void WorldGfx_HarryCharaLoad(void);

/** @brief Loads default characters in the map overlay.
 *
 * @param mapHdr Map header.
 * @return Character model queue index.
 */
s32 WorldGfx_MapInitCharaLoad(s_MapOverlayHeader* mapHdr);

void WorldGfx_CharaLmBufferAssign(s8 forceFree);

s32 func_8003DD74(e_CharaId charaId, s32 arg1);

void WorldGfx_HeldItemAttach(e_CharaId charaId, s32 modelBone); // Called by some chara init funcs.

s32 func_800868F4(s32 arg0, s32 arg1, s32 idx);

void Collision_OvlTriggerZonesPtrSet(s_MapOverlayHeader* overlayHdr);

void func_80040014(void);

bool Chara_ModelLoadedCheck(e_CharaId charaId);

/** Related to the screen. Called by `WorldEnv_Init`. */
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
 * @return Queue entry load status (`e_ChunkLoadState`).
 */
u32 Map_ChunkLoadStateGet(s32 queueIdx);

/** @brief Initializes map data and chunks.
 *
 * @param lmHdr LM header.
 * @param ipdBuf IPD chunk buffer.
 * @param ipdBufSize IPD chunk buffer size.
 */
void Map_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize);

void Lm_Init(s_GlobalLm* globalLm, s_LmHeader* lmHdr);

void LmHeader_Init(s_LmHeader* lmHdr);

/** @brief Clears `queueIdx` in array of `s_IpdChunk` */
void Map_ChunkQueueIdxsClear(s_IpdChunk* chunks, s32 chunkCount);

void Ipd_TexturesInit(void);

void Map_CollisionDataInit(void);

/** @brief Places an chunk at given XZ chunk cell coordinates.
 *
 * @param ipdFileIdx Index of the IPD chunk file to place.
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 */
void Map_ChunkPlace(s16 ipdFileIdx, s32 cellX, s32 cellZ);

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
 * `file 1100` is `THR0205.IPD`, `ipdGridCenter[2][5] = 1100`.
 */
void Map_MakeIpdGrid(s_Map* map, char* mapTag, e_FsFile fileIdxStart);

/** @brief Converts two hex `char`s to an integer hex value.
 *
 * @param out Output hex `int`.
 * @param hex0 First hex `char`.
 * @param hex1 Second hex `char`.
 */
bool ConvertHexToS8(s32* out, char hex0, char hex1);

s_IpdCollisionData** Ipd_ActiveChunksCollisionDataGet(s32* collDataIdx);

/** @brief Gets the collision data at a given position.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @return Collision data.
 */
s_IpdCollisionData* Ipd_CollisionDataGet(q19_12 posX, q19_12 posZ);

/** @brief Gets the location of a nearby world object model.
 *
 * @param model Model to find.
 * @param metadata TODO
 * @param posX Search X position.
 * @param posZ Search Z position.
 * @return World object model location (`e_WorldModelLocation`).
 */
s32 Map_WorldObjectModelLocationGet(s_WorldObjectModel* model, s_WorldObjectMetadata* metadata, q19_12 posX, q19_12 posZ);

/** @brief Gets the load state of a global LM file.
 *
 * @param globalLm Global LM file to check.
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
q19_12 Map_PaddedDistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ, bool isExterior);

/** @brief Computes the distance from an XZ position to the edge of an XZ chunk cell boundary.
 * If the position resides inside the chunk cell, the distance is `Q12(0.0f)`.
 *
 * @param posX X position.
 * @param posZ Z position.
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 * @return Distance from the XZ position to the XZ chunk cell boundary.
 */
q19_12 Map_DistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ);

/** Loads geometry, sets materials and properly assigns the position of the map when loading a new room/map? */
s32 Map_ChunkLoad(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ);

void Ipd_ActiveChunksSample(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

/** @brief Computes the distance from a position to the nearest edge of a chunk.
 *
 * @param chunk Chunk to check.
 * @param TODO
 */
void Ipd_DistanceToEdgeCalc(s_IpdChunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

/** Sets materials for active chunks? */
void Ipd_ChunkMaterialsApply(s_Map* map);

/** @brief Gets the IPD chunk file index from cell coordinates.
 *
 * @param cellX X cell coordinate.
 * @param cellZ Z cell coordinate.
 * @return IPD chunk file index.
 */
s32 Map_IpdChunkFileIdxGet(s32 cellX, s32 cellZ);

bool Map_IsIpdPresentCheck(const s_IpdChunk* activeChunks, s32 cellX, s32 cellZ);

s_IpdChunk* Ipd_FreeChunkFind(s_IpdChunk* activeChunks, bool isExterior);

s32 Ipd_LoadStart(s_IpdChunk* chunk, e_FsFile fileIdx, s32 cellX, s32 cellZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior);

/** Checks if currently loaded chunks have been loaded properly. */
bool Ipd_ChunksLoadedCheck(void);

/** @brief Checks if the player is in close proximity to an unloaded ahead which should be loaded.
 *
 * @return `true` if a new chunk needs to be loaded, `false` otherwise.
 */
bool Ipd_NextChunkLoadCheck(void);

/** Checks if a position is within the current map chunk. */
bool func_8004393C(q19_12 posX, q19_12 posZ);

void Ipd_ChunksDraw(GsOT* ot, bool arg1);

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
void Ipd_ChunkDraw(s_IpdHeader* ipdHdr, q19_12 posX, q19_12 posZ, GsOT* ot, bool arg4);

/** @brief Checks if an IPD chunk subcell is visible.
 *
 * @param modelBuf IPD model buffer.
 * @param subcellX X subcell position.
 * @param subcellZ Z subcell position.
 * @param posX X cell position? TODO: Subcell/cell intent unclear, needs more research.
 */
bool Gfx_ChunkSubcellVisibleCheck(s_IpdModelBuffer* modelBuf, q7_8 subcellX, q7_8 subcellZ, q23_8 posX, q23_8 posZ);

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

/** * @brief Plays an animation once and clamps to the end keyframe, triggering a status transition to the linked
 * animation upon completion.
 *
 * @note Used for one-shot actions such as stopping and attacking.
 *
 * @param model Character model to animate.
 * @param anmHdr Active animation header.
 * @param boneCoords Character model bone coords.
 * @param animInfo Active character animation info.
 */
void Anim_PlaybackOnce(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s_AnimInfo* animInfo);

/** * @brief Loops an animation continuously, wrapping the time around to the start and end keyframes without
 * triggering a status transition.
 *
 * @note Used for looped actions such as running and walking.
 *
 * @param model Character model to animate.
 * @param anmHdr Active animation header.
 * @param boneCoords Character model bone coords.
 * @param animInfo Character animation info.
 */
void Anim_PlaybackLoop(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s_AnimInfo* animInfo);

/** * @brief Linearly interpolates between the current pose into a new target animation, triggering a status transition
 * to the linked animation when complete.
 *
 * @note Used as the entry transition for almost every new animation status.
 *
 * @param model Character model to animate.
 * @param anmHdr Active animation header.
 * @param boneCoords Character model bone coords.
 * @param animInfo Character animation info.
 */
void Anim_BlendLinear(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s_AnimInfo* animInfo);

/** * @brief Smoothly blends between the current pose into a new target animation using a sine-based ease-out
 * without triggering a status transition.
 *
 * @unused?
 *
 * @param model Character model to animate.
 * @param anmHdr Active animation header.
 * @param boneCoords Character model bone coords.
 * @param animInfo Character animation info.
 */
void Anim_BlendEaseOut(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s_AnimInfo* animInfo);

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

void func_80045534(s_Skeleton* skel, GsOT* ot, s32 arg2, GsCOORDINATE2* boneCoords, q3_12 arg4, u16 arg5, s_FsImageDesc* images);

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

/** @brief Gets the point light position.
 *
 * @param pos Output light position.
 */
void WorldEnv_LightPositionGet(VECTOR3* pos);

/** @brief Gets the point light rotation and intensity.
 *
 * @param rot Output light rotation.
 * @return Light intensity.
 */
s32 WorldEnv_LightRotationAndIntensityGet(SVECTOR* rot);

/** @brief Gets the point light direction and intensity.
 *
 * @param rot Output light direction.
 * @return Light intensity.
 */
s32 WorldEnv_LightDirectionAndIntensityGet(SVECTOR* dir);

/** Light function. */
void func_800554C4(q19_12 lightIntensity, q3_12 lensFlareIntensity, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1,
                   SVECTOR* rot, q19_12 posX, q19_12 posY, q19_12 posZ, s_WaterZone* waterZones);

/** Light function. */
void func_80055648(s32 lightIntensity, const SVECTOR* dir);

s32 func_800557DC(void);

void func_80055814(s32 arg0);

void WorldEnv_FogDistanceSet(q19_12 nearDist, q19_12 farDist);

s32 func_800559A8(s32 arg0);

u8 func_80055A50(s32 arg0);

void func_80055A90(CVECTOR* arg0, CVECTOR* arg1, u8 arg2, s32 arg3);

/** @brief Applies uniform lighting and fog shading to `color`, outputting to `result`.
 * The fog factor is derived from `arg2` via `g_WorldEnvWork.fogRamp` and blends the lit color toward the far/fog color in `g_WorldEnvWork.field_1C/field_1D/field_1E`,
 * with lighting strength from `g_WorldEnvWork.field_20` applied equally on all axes.
 */
void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2);

void func_80055C3C(CVECTOR* result, CVECTOR* color, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

u8 func_80055D78(q19_12 posX, q19_12 posY, q19_12 posZ);

void func_80055E90(CVECTOR* color, u8 fadeAmount);

void func_80055ECC(CVECTOR* color, SVECTOR3* arg1, SVECTOR3* arg2, MATRIX* worldMat);

u8 func_80055F08(SVECTOR3* arg0, SVECTOR3* arg1, MATRIX* worldMat);

void LmHeader_FixOffsets(s_LmHeader* lmHdr);

void ModelHeader_FixOffsets(s_ModelHeader* modelHdr, s_LmHeader* lmHdr);

void Lm_TransparentPrimSet(s_LmHeader* lmHdr, bool isTransparent);

s32 Lm_MaterialCountGet(bool (*filterFunc)(s_Material* mat), s_LmHeader* lmHdr);

/** TODO: Unknown `arg3` type. */
void func_80059D50(s32 arg0, s_ModelInfo* modelInfo, MATRIX* viewMat, bool arg3, GsOT_TAG* tag);

void func_80059E34(u32 arg0, s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 arg3, GsOT_TAG* tag);

void func_8005A21C(s_ModelInfo* modelInfo, GsOT_TAG* otTag, bool arg2, MATRIX* viewMat);

/** @brief Computes a fog-shaded version of `D_800C4190` color using `arg1` as the distance factor?
 *  Stores the result at 0x3D8 into `arg0`.
 */
void func_8005A42C(s_GteScratchData* scratchData, q19_12 alpha);

void func_8005A478(s_GteScratchData* scratchData, q19_12 alpha);

/** `scratchData` is unused? */
void func_8005A838(s_GteScratchData* scratchData, s32 scale);

void func_8005A900(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* viewMat);

u8 func_8005AA08(s_MeshHeader* meshHdr, s32 arg1, s_GteScratchData2* scratchData);

void func_8005AC50(s_MeshHeader* meshHdr, s_GteScratchData2* scratchData, GsOT_TAG* ot, bool arg3);

void Texture_Init(s_Texture* tex, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY);

void Texture_RefCountReset(s_Texture* tex);

/** @unused */
void func_8005B378(s_Texture* tex, char* arg1);

void Texture_RefClear(s_Texture* tex);

void Material_TimFileNameGet(char* filename, s_Material* mat);

void func_8005B424(VECTOR3* vec0, const VECTOR3* vec1);

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

bool Lm_ModelFind(s_WorldObjectModel* model, s_LmHeader* lmHdr, s_WorldObjectMetadata* metadata);

void StringCopy(char* prevStr, char* newStr);

/** @brief Draws a 2D fog overlay quad. */
void Gfx_FogOverlayQuadDraw(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, GsOT* ot, s32 arg7);

/** Crucial 3D drawing function. */
void func_80057090(s_ModelInfo* modelInfo, GsOT* otTag, s32 arg2, MATRIX* viewMat, MATRIX* worldMat, u16 arg5);

s32 func_800571D0(u32 arg0);

void WorldEnv_LightTransform(MATRIX* worldMat, s32 alpha, SVECTOR* arg2, VECTOR3* arg3);

void func_80057344(s_ModelInfo* modelInfo, GsOT_TAG* otTag, bool arg2, MATRIX* mat);

void func_800574D4(s_MeshHeader* meshHdr, s_GteScratchData* scratchData);

void func_8005759C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 vertOffset, s32 normalOffset);

void func_80057658(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4);

void func_80057A3C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec);

void func_80057B7C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* mat);

/** Main quad drawing func? */
void Gfx_MeshDraw(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, GsOT_TAG* tag, bool arg3);

/** `arg4` unused. */
s_Texture* Texture_Get(s_Material* mat, s_ActiveTextures* activeTexs, void* fsBuf9, e_FsFile fileIdx, s32 arg4);

/** Initializes values in `D_800AE204` array. */
void func_8005B55C(GsCOORDINATE2* viewCoord);

void Gfx_BillboardDraw(s32 idx, q19_12 posX, q19_12 posY, q19_12 posZ, GsOT* ot_arg4, s32 arg5);

u32 func_8005C478(s16* arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2);

s32 Chara_NpcIdxGet(s_SubCharacter* chara);

void func_8005C814(s_CharaShapeOffsets* offsets, s_SubCharacter* chara);

s32 func_8005C944(s_SubCharacter* chara, s_CollisionResult* collResult);

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

void func_8008D41C(void);

void func_8008D438(void);

void func_8008D448(void);

void func_8008D454(void);

void func_8008D464(void);

/** Light function. */
void func_8008D470(q3_12 lensFlareIntensity, SVECTOR* rot, VECTOR3* pos, s_WaterZone* waterZones);

void func_8008D5A0(VECTOR3* arg0, s16 arg1);

/** Light function. */
q19_12 func_8008D8C0(q3_12 lensFlareIntensity, q19_12 x1, q19_12 x2);

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

/** @brief Sets `sysStateSteps` depending on whether `eventFlagIdx` flag is set.
 *
 * @param eventFlagIdx Flag index.
 * @param stepTrue Step to use if flag is set.
 * @param stepFalse Step to use if flag is not set.
 * @param stepSecondary If `true`, sets `sysStateSteps[1]` instead of `sysStateSteps[0]`, otherwise sets `sysStateSteps[0]`.
 */
void func_8008605C(e_EventFlag eventFlagIdx, s32 stepTrue, s32 stepFalse, bool stepSecondary);

/** @brief Displays a selection menu and sets `sysStateSteps` depending on the chosen value.
 *
 * @param hasSelection `true` if it waits for a selection, `false` if `sysStateSteps` increments after displaying.
 * @param mapMsgIdx Map message index of the message to display.
 * @param step0 Step to use if selection #0 is chosen.
 * @param step1 Step to use if selection #1 is chosen.
 * @param step2 Step to use if selection #2 is chosen.
 * @param stepSecondary If `true`, sets `sysStateSteps[1]` instead of `sysStateSteps[0]`, otherwise sets `sysStateSteps[0]`.
 */
void MapMsg_DisplayAndHandleSelection(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool stepSecondary);

/** Handles giving the player items. */
void SysWork_StateStepIncrementAfterFade(s32 stateStep, bool cond, s32 fadeType, q19_12 fadeTimestep, bool reset);

/** Handles a busy wait while loading assets? */
void func_800862F8(s32 stateStep, e_FsFile fileIdx, bool reset);

/** Stepped state handler for displaying picked up items? */
void func_80086470(u32 stateStep, e_InvItemId itemId, s32 itemCount, bool reset);

void func_800865FC(bool isPos, s32 idx0, s32 idx1, q3_12 angleY, q19_12 offsetOrPosX, q19_12 offsetOrPosZ);

/** State step increment. */
void func_800866D4(s32 arg0, s32 arg1, bool reset);

extern bool (*D_800AFD08[])(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3);

void func_80086728(s_SubCharacter* chara, s32 arg1, s32 arg2, bool reset);

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2);

/** Paper map state handler. Rough name could be `Map_PaperMapBackgroundStateUpdate`. */
void func_800867B4(s32 state, s32 paperMapFileIdx);

void func_800868DC(s32 idx);

/** @brief Displays a map message with dialog audio and increments the audio index.
 *
 * @param mapMsgIdx Index of the message to display.
 * @param audioIdx Index of the dialog audio command to play.
 * @param audioCmds Dialog audio commands.
 */
void Map_MessageWithAudio(s32 mapMsgIdx, u8* audioIdx, const u16* audioCmds);

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

void Event_ItemTake(e_InvItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx);

void Event_MapTake(s32 mapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

// =========================
// `bodyprog_bgm_80087EA8.c`
// =========================

/** @brief Plays a new background music track. If the track is already playing, the request is ignored.
 *
 * @param bgmIdx Index of the background music track to play.
 */
void Bgm_PlayNewTrack(s32 bgmIdx);

/** @brief Handles a multi-step crossfade to a new track.
 *
 * @param bgmIdx Index of the background music track to play.
 */
void Bgm_CrossfadeToTrack(s32 bgmIdx);

/** @brief Crossfades the currently playing background music track to silence. */
void Bgm_CrossfadeToSilence(void);

/** State handler. */
void func_80088048(void);

/** State handler. */
void func_800880F0(bool bool);

// ========================

void Gfx_CursorDraw(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

// ========================
// `bodyprog/chara_spawn.c`
// ========================

bool Chara_Load(s32 modelIdx, s8 charaId, GsCOORDINATE2* coords, s8 forceFree, s_LmHeader* lmHdr, s_FsImageDesc* tex);

bool Chara_ProcessLoads(void);

void Chara_BonesInit(s32 idx);

s32 Chara_Spawn(e_CharaId charaId, s32 spawnFlags, q19_12 posX, q19_12 posZ, q3_12 rotY, u32 stateStep);

void Chara_ModelCharaIdClear(s_SubCharacter* chara, s32 unused0, s32 unused1);

void Chara_SpawnFlagsSet(e_CharaId charaId, s32 spawnIdx, s32 spawnFlags);

// ========================

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

/** Anim infos setup for character. */
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
s32 func_8008B714(s_SubCharacter* attacker, s_SubCharacter* target, VECTOR3* attackPos, s32 arg3);

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

/** @brief Normalizes a signed Q3.12 fixed-point angle to the clamped signed integer range `[-2048, 2047]`.
 *
 * TODO: Appears to have the same effect as `Q12_ANGLE_NORM_S` macro. Maybe this was written by someone unaware of that?
 * Once the build is shiftable, check if calls to this can simply be switched over to the macro.
 *
 * @param angle Angle to normalize.
 * @return Normalized angle.
 */
q3_12 Math_AngleNormalizeSigned(q3_12 angle);

bool func_8005BF58(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

s32 func_8005C1CC(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

s32 func_8005C7B0(s32 arg0);

void func_800625F4(VECTOR3* arg0, q3_12 angle, s32 arg2, s32 arg3);

bool func_80062708(POLY_FT4** poly, s32 idx);

bool func_80063A50(POLY_FT4** poly, s32 idx);

// Important for drawing gun smoke effect.
bool func_80064334(POLY_FT4** poly, s32 idx);

/** Displays gunfire effects. */
void func_8006342C(s32 weaponAttack, q3_12 rotY, q3_12 rotX, GsCOORDINATE2* coord);

s32 func_8005CB20(s_SubCharacter* chara, s_CollisionResult* collResult, q3_12 offsetX, q3_12 offsetZ);

/** Computes something for a targeted NPC. */
bool func_8005D50C(s32* targetNpcIdx, q3_12* outAngle0, q3_12* outAngle1, VECTOR3* from, u32 npcIdx, q19_12 angleConstraint);

bool func_80060044(POLY_FT4** poly, s32 idx);

bool func_800611C0(POLY_FT4** poly, s32 idx);

/** Spawns blood effect? */
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

// ============= `bodyprog/collision.c` ===============

/** @brief Initializes the collision subsystem, resetting flags and clearing the trigger zone count. */
void Collision_Init(void);

/** @brief Gets the active collision flags. */
u16 Collision_FlagsGet(void);

/** @brief Sets the active collision flags.
 *
 * @param collFlags New collision flags.
 */
void Collision_FlagsSet(u16 collFlags);

/** @brief Sets additional active collision flags using OR.
 *
 * @param collFlags Collision flag bits to set.
 */
void Collision_FlagBitsSet(u16 collFlags);

void func_80069844(s32 collFlags);

/** @brief Scans trigger zones and collects those containing the given XZ position.
 *
 * @param posX Query X position.
 * @param posZ Query Z position.
 * @param zones Array of trigger zone definitions.
 */
void Collision_TriggerZonesUpdate(q19_12 posX, q19_12 posZ, s_TriggerZone* zones);

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

/** @brief Detects a wall collision using the scratchpad for performance.
 *
 * @param collResult Output collision result.
 * @param offset Movement offset.
 * @param chara Character to check.
 * @return Wall response code.
 */
s32 Collision_WallDetect(s_CollisionResult* collResult, VECTOR3* offset, s_SubCharacter* chara);

/** @brief Handles a wall collision response by sampling the ground at 9 points around a character.
 *
 * @param collResult Output collision result.
 * @param offset Movement offset.
 * @param chara Character to check.
 * @param response Initial collision pass response.
 * @return Wall response code.
 */
s32 Collision_WallResponse(s_CollisionResult* collResult, const VECTOR3* offset, s_SubCharacter* chara, s32 response);

/** @brief Probes ground heights at 16 radial points to determine the terrain slope direction.
 * Creates a terrain avoidance force to push away from illegal positions.
 *
 * @param collResult Output collision result with XZ offset vector pointing away from the highest terrain.
 * @param pos Center position.
 * @param startGroundHeight Starting character Y position.
 * @param startHeadingAngle Starting heading angle on the XZ plane for the probe circle.
 */
void Collision_GroundProbeRadial(s_CollisionResult* collResult, const VECTOR3* pos,
                                 q19_12 startGroundHeight, q19_12 startHeadingAngle);

/** @brief Applies collision detection for a character's movement offset.
 *
 * @param collResult Output collision result.
 * @param offset Movement offset to test.
 * @param chara Character performing movement.
 * @return Collision result response.
 */
s32 Collision_CharaCollisionSetup(s_CollisionResult* collResult, VECTOR3* offset, s_SubCharacter* chara);

/** @brief Initializes a default collision result with a position and ground height.
 *
 * @param result Collision result to initialize.
 * @param offsetX X offset.
 * @param offsetY Y offset.
 * @param offsetZ Z offset.
 * @param groundHeight Ground height.
 */
void Collision_DefaultResultSet(s_CollisionResult* collResult, q19_12 offsetX, q19_12 offsetY, q19_12 offsetZ, q19_12 groundHeight);

/** @brief Gets an array of active characters for collision testing.
 *
 * @param charaCount Output number of characters found.
 * @param excludedChara Character to exclude, typically the one being tested.
 * @param includePlayer Filter out the player.
 * @return Active characters.
 */
s_SubCharacter** Collision_ActiveCharactersGet(s32* charaCount, const s_SubCharacter* excludedChara, bool includePlayer);

/** @brief Checks a movement offset against a collision result.
 *
 * @param collResult Collision result.
 * @param offset Movement offset to test.
 * @param query Collision query parameters.
 * @return `true` if movement is possible, `false` otherwise.
 */
s32 Collision_OffsetCheck(s_CollisionResult* collResult, VECTOR* offset, s_CollisionQuery* collQuery);

s32 func_8006A42C(s_CollisionResult* collResult, VECTOR3* offset, s_CollisionQuery* collQuery);

s32 func_8006A4A8(s_CollisionResult* collResult, VECTOR3* offset, s_CollisionQuery* collQuery, bool arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount);

// Claude suggests `Collision_NpcMovementDampen`? Investigate.
void func_8006A940(VECTOR3* offset, s_CollisionQuery* collQuery, s_SubCharacter** charas, s32 charaCount);

/** @brief Initializes a collision state for a new pass.
 *
 * @param collState Collision state to initialize.
 * @param offset Movement offset.
 * @param collQuery Input collision query parameters.
 * @param arg3 Configuration flag. TODO: What is it?
 */
void Collision_QueryInit(s_CollisionState* collState, VECTOR3* offset, s_CollisionQuery* collQuery, bool arg3);

/** @brief Calculates the movement direction vector and distance from a position offset.
 *
 * @param result Output movement direction and position data.
 * @param offset Movement offset.
 * @param collQuery Input collision query parameters.
 */
void Collision_QueryDirectionCalc(s_func_8006ABC0* result, const VECTOR3* offset, const s_CollisionQuery* collQuery);

void Ipd_GridCollisionQuery(s_CollisionState* collState, s_IpdCollisionData* collData);

bool func_8006AEAC(s_CollisionState* collState, const s_IpdCollisionData* collData);

bool func_8006B004(s_CollisionState* collState, const s_IpdCollisionData* collData);

void func_8006B1C8(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2);

bool func_8006B318(s_CollisionState* collState, const s_IpdCollisionData* collData, s32 idx);

/** `arg1` is unused, but `func_8006B1C8` passes second arg to this. */
void func_8006B6E8(s_CollisionState* collState, s_IpdCollisionData_20* arg1);

bool func_8006B7E0(s_CollisionState_A8* arg0, s_CollisionState_CC_20* arg1);

void func_8006B8F8(s_CollisionState_CC* arg0);

void func_8006B9C8(s_CollisionState* collState);

void func_8006BB50(s_CollisionState* collState, s32 arg1);

s32 func_8006BC34(s_CollisionState* collState);

/** `arg3` and `arg4` might be XY or XZ position components. */
void func_8006BCC4(s_CollisionState_44* arg0, s8* arg1, u32 arg2, q3_12 deltaX, q3_12 deltaZ, s16 arg5);

void func_8006BDDC(s_CollisionState_44_0* arg0, q3_12 rotX, q3_12 rotY);

void func_8006BE40(s_CollisionState* collState);

void func_8006BF88(s_CollisionState* collState, SVECTOR3* arg1);

void func_8006C0C8(s_CollisionState* collState, s16 arg1, s16 arg2);

bool func_8006C1B8(u32 arg0, s16 arg1, s_CollisionState* collState);

s16 func_8006C248(s32 packedDir, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4);

bool func_8006C3D4(s_CollisionState* collState, s_IpdCollisionData* collData, s32 idx);

void func_8006C45C(s_CollisionState* collState);

void func_8006C794(s_CollisionState* collState, s32 arg1, s32 dist);

void func_8006C838(s_CollisionState* collState, s_IpdCollisionData* collData);

void func_8006CA18(s_CollisionState* collState, s_IpdCollisionData* collData, s_func_8006CA18* arg2);

q3_12 Collision_OffsetAlphaGet(s_CollisionState* collState);

q23_8 Ipd_GroundHeightGet(q23_8 posX, q23_8 posZ, const s_CollisionState* collState);

void func_8006CC9C(s_CollisionState* collState);

void func_8006CF18(s_CollisionState* collState, s_func_8006CF18* arg1, s32 idx);

void func_8006D01C(VECTOR3* arg0, VECTOR3* offset, q3_12 offsetAlpha, s_CollisionState* collState);

void func_8006D2B4(VECTOR3* arg0, s_CollisionState_44* arg1);

void func_8006D600(VECTOR3* pos, q19_12 angle, q19_12 rotX, q19_12 rotY, s32 arg4);

void func_8006D774(s_CollisionState* collState, VECTOR3* arg1, VECTOR3* arg2);

/** `arg1` is likely Q23.8. */
void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2);

bool Ray_TraceQuery(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* to);

/** Ray function. */
bool Ray_CharaTraceQuery(s_RayTrace* trace, VECTOR3* from, VECTOR3* offset, s_SubCharacter* chara);

void Ray_MissSet(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, q23_8 arg3);

/** @brief Checks if an obstruction in a ray's line of sight has been hit, ignoring a specified character.
 *
 * @param trace Ray trace.
 * @param from Ray origin.
 * @param offset Ray target offset from origin.
 * @param excludedChara Character to exclude.
 * @return `true` if there is an obstruction, `false` otherwise.
 */
bool Ray_LosHitCheck(s_RayTrace* trace, VECTOR3* from, VECTOR3* offset, s_SubCharacter* excludedChara);

bool func_8006DC18(s_RayTrace* trace, VECTOR3* from, VECTOR3* offset);

bool Ray_TraceSetup(s_RayState* state, s32 arg1, s16 arg2, const VECTOR3* from, const VECTOR3* offset, s32 arg5, s32 arg6, s_SubCharacter** charas, s32 charaCount);

bool Ray_TraceRun(s_RayTrace* trace, s_RayState* state);

// Fills `state` with info.
void func_8006E0AC(s_RayState* state, s_IpdCollisionData* ipdColl);

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2);

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ);

void func_8006E53C(s_RayState* state, s_IpdCollisionData_20* arg1, s_IpdCollisionData* arg2);

void func_8006E78C(s_RayState* state, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4);

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1);

// Fils ray hit data?
void func_8006EE0C(s_RayState_6C* arg0, s32 arg1, s_SubCharacter* chara);

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara);

void func_8006F250(q19_12* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

void func_8006F338(s_func_8006F338* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

bool func_8006F3C4(s_func_8006F338* arg0, const s_TriggerZone* zone);

/** Translates something. Unsure on 3rd param's name. */
q19_12 func_8006F620(VECTOR3* pos, s_CollisionQuery* collQuery, q19_12 dist, q19_12 offsetY);

void func_8006F8FC(q19_12* outX, q19_12* outZ, q19_12 posX, q19_12 posZ, const s_TriggerZone* zone);

q19_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle);

/** Angle getter. Something to do with the direction from a character to a target position, probably for NPC AI.
 * Unsure if `spanAngle` is an angle.
 */
q19_12 Chara_HeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 toX, q19_12 toZ, q3_12 spanAngle, bool cond);

bool func_8006FD90(s_SubCharacter* chara, s32 count, q19_12 baseDistMax, q19_12 distStep);

/** @brief Checks if there's an obstructed target-based line of sight between a character and a target position.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Ray_CharaToTargetLosHitCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed target-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_CharaToCharaTargetLosCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed line of sight between an NPC and a player.
 *
 * @param fromNpc Origin NPC character.
 * @param toPlayer Target player character.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_NpcToPlayerLosHitCheck(s_SubCharacter* fromNpc, s_SubCharacter* toPlayer);

/** @brief Checks if there's an unobstructed distance-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_CharaToCharaDistLosCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

/** @brief @unused Checks if there's another character obstructing the distance-based line of sight in front of a
 * character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @return `true` if there's another character in front, `false` otherwise.
 */
bool Ray_CharaToCharaFrontLosHitCheck(s_SubCharacter* fromChara, q19_12 dist);

/** @brief Checks if there's an obstructed distance-based line of sight from a character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Ray_CharaLosHitCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

bool func_80070320(void);

/** TODO: Return type uncertain. */
q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2);

/** @brief Sets a character's interpolated collision shapes for the active animation frame.
 *
 * @param chara Character to update.
 * @param keyframe0 First keyframe.
 * @param keyframe1 Second keyframe.
 */
void Collision_CharaAnimShapesSet(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1);

void func_800705E4(GsCOORDINATE2* coord, s32 idx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ);

// ======================================

void Player_FlexRotationYReset(void);

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2);

void Settings_ScreenAndVolUpdate(void);

void Settings_RestoreDefaults(void);

void Settings_RestoreControlDefaults(s32 configIdx);

void nullsub_800334C8(void);

/** @brief Updates the savegame buffer with current player info (position, rotation, health, event index). */
void SysWork_SavegameUpdatePlayer(void);

/** @brief Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SavegameReadPlayer(void);

/** @brief Handles a warm game reboot. */
void Game_WarmBoot(void);

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx);

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1);

/** @unused */
void func_80036E48(u16* arg0, s16* arg1);

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124(void);

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

/** @brief Updates the active autosave savegame entry with the most recent savegame. */
void SysWork_AutosaveUpdate(void);

void SysState_SaveMenu_Update(void);

void SysState_EventCallback_Update(void);

void SysState_EventSetFlag_Update(void);

void SysState_EventPlaySound_Update(void);

void SysState_GameOver_Update(void);

// ====================
// Main menu functions - TODO: Maybe a split around here?
// ====================

void MainMenu_SelectedOptionIdxReset(void);

// ====================

/** @brief Gets the bones of a registered character model.
 *
 * @param charaId ID of the character for which to get the skeleton bones (`e_CharaId`).
 * @return Character model bones or `NULL` if the character model is unregistered.
 */
s_LinkedBone* WorldGfx_CharaModelBonesGet(e_CharaId charaId);

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

void func_8003CC7C(s_WorldObjectModel* model, MATRIX* viewMat, MATRIX* worldMat);

/** @brief Advanced a character model LM buffer.
 *
 * @param buf Buffer to advance.
 * @param charaID  ID of the character whose model to use (`e_CharaId`).
 */
void WorldGfx_CharaLmBufferAdvance(u8** buf, e_CharaId charaId);

/** UV setup for character textures. */
void Chara_FsImageCalc(s_FsImageDesc* image, s32 groupIds, s32 modelIdx);

/** @brief Loads a character model, setting the LM header and texture UVs as a prerequisite.
 *
 * @param charaId ID of the character whose model to load (`e_CharaId`).
 * @param modelIdx Slot index of the model array to load into.
 * @param lmHdr LM header.
 * @param tex Model texture.
 * @return Model or texture queue index.
 */
void WorldGfx_CharaLoad(e_CharaId charaId, s32 modeIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

/** @brief Loads a character model.
 *
 * @param charaId ID of the character whose model to load (`e_CharaId`).
 * @param modelIdx Slot index of the model array to load into.
 * @param lmHdr LM header.
 * @param tex Model texture.
 * @return Model or texture queue index.
 */
s32 WorldGfx_CharaModelLoad(e_CharaId charaId, s32 modelIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex);

/** Something related to animations. */
void WorldGfx_PlayerModelProcessLoad(void);

void WorldGfx_CharaModelProcessAllLoads(void);

void WorldGfx_CharaModelProcessLoad(s_CharaModel* model);

void func_8003DA9C(e_CharaId charaId, GsCOORDINATE2* boneCoords, s32 arg2, q3_12 timer, s32 arg4);

/** Something for Harry. `arg` is a packed value. */
void func_8003DE60(s_Skeleton* skel, s32 modelBone);

/** Something for Cybil. */
void func_8003DF84(s_Skeleton* skel, s32 modelBone);

/** Something for Monster Cybil. */
void func_8003E08C(s_Skeleton* skel, s32 modelBone);

/** Something for Dahlia. */
void func_8003E194(s_Skeleton* skel, s32 modelBone);

/** Something for Kaufmann. */
void func_8003E238(s_Skeleton* skel, s32 modelBone);

/** Something for Stalker. */
void func_8003E388(s_Skeleton* skel, s32 modelBone);

/** Something for Split Head. */
void func_8003E414(s_Skeleton* skel, s32 modelBone);

/** Something for Puppet Nurse. */
void func_8003E4A0(s_Skeleton* skel, s32 modelBone);

/** Something for Puppet Doctor. */
void func_8003E544(s_Skeleton* skel, s32 modelBone);

void func_8003ECBC(void);

void func_8003ECE4(void);

void func_8003EDA8(void);

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

void func_80070B84(s_SubCharacter* player, q19_12 moveDistMax, q19_12 arg2, s32 keyframeIdx);

void func_80070DF0(s_PlayerExtra* extra, s_SubCharacter* player, s32 weaponAttack, s32 animStatus);

/** @brief Gets the variable animation duration for the player.
 *
 * @param model Player model.
 * @return Variable animation duration.
 */
q19_12 Player_VariableAnimDurationGet(s_Model* model);

/** Special player SFX handler for heavy breath and damage. */
bool func_80071620(u32 animStatus, s_SubCharacter* player, s32 keyframeIdx, e_SfxId sfxId);

void func_8007C0D8(s_SubCharacter* player, s_PlayerExtra* extra, GsCOORDINATE2* boneCoords);

void func_8007D090(s_SubCharacter* player, s_PlayerExtra* extra, GsCOORDINATE2* boneCoords);

void Player_CombatUpdate(s_SubCharacter* player, GsCOORDINATE2* coord);

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

/** @brief Determine the step sound and pitch of the step sound. */
void func_8007FDE0(s8 floorType, e_SfxId* sfxId, s8* pitch0, s8* pitch1);

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

/** Fills `g_CollisionPointCache` with collision data at a given 2D position.
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

/** Handles character spawn? */
void Chara_SpawnPositionSet(e_CharaId charaId, s32 spawnIdx, q19_12 posX, q19_12 posZ);

/* Does the map zoom in, red lines? Argument types guessed based on f`unc_800E83C0` in MAP2_S00. */
void Map_BoxOutlineDraw(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8);

#endif
