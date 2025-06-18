#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"

#define TEMP_MEMORY_ADDR ((s8*)0x801A2600)
#define DEMO_WORK()      ((s_DemoWork*)0x800FDE00) // TODO: Move closer to demo structs (or to separate header?)

#define IMAGE_BUFFER_0 ((u_long*)0x801CFA00)
#define IMAGE_BUFFER_1 ((u_long*)0x801C8200)
#define IMAGE_BUFFER_2 ((u_long*)0x801ABE00)
#define FONT24_BUFFER ((u_long*)0x801F5600) // Loaded by `GameFs_StfRollBinLoad`.

#define CD_ADDR_0 0x801E2600

#define OPT_SOUND_VOLUME_MIN   0
#define OPT_SOUND_VOLUME_MAX   128
#define OPT_VIBRATION_DISABLED 0
#define OPT_VIBRATION_ENABLED  128

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
    s8  field_0;
    s8  unk_1;
    s16 field_2;
    s16 field_4;
} s_func_8006BDDC;

typedef struct
{
    s8  unk_0[124];
    s32 field_7C;
    s32 field_80;
    s32 field_84;
    s32 field_88;
    s32 field_8C;
    s8  unk_90[4];
    s32 field_94;
} s_func_8006CC44;

typedef struct 
{
    u8 unk_0[2];
    s8 field_2;
    s8 field_3; 
    u8 unk_4[2];
} s_80024C90;

typedef struct
{
    s8 unk_0[16];
} s_8002AC04;
STATIC_ASSERT_SIZEOF(s_8002AC04, 16);
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

// Likely not skeleton since filed_8 must be `s8`.
typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
    s8 unk_4[4];
    s8 field_8;
} s_80041CEC;

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
    s8  unk_0[4];
    u8  field_4;
    u8  field_5;
    u16 field_6;
    s32 field_8;
    s32 field_C;
} s_func_8008973C;

typedef struct
{
    s8  unk_0[22];
    s32 field_18;
} s_func_80089840;

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
    s8  unk_0[4];
    u32 field_4; // Fields 4 and 8 are related.
    u32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
} s_800A992C;

typedef struct
{
    s8  unk_0[8];
    s32 field_8;
} s_800AA894;
STATIC_ASSERT_SIZEOF(s_800AA894, 12);

typedef struct
{
    s8 field_0[44];
} s_800A93CC;

typedef struct
{
    s16 unk_0;
    s16 field_2;
    s8  field_4;
} s_800ACAA8;

typedef struct
{
    s8 unk_0[15];
    s8 field_F;
    u8 field_10;
    s8 field_14[7];
} s_800AD4C8;
STATIC_ASSERT_SIZEOF(s_800AD4C8, 24);

typedef struct
{
    s8  unk_0[2];
    u8  field_2;
    s8  unk_6[4090];
    s32 queueIdx_1000;
} s_800BE9FC;

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
    s32 field_30;
    s32 field_34;
} s_800B5488;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
} s_800B55E8;

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

typedef struct
{
    s32*              field_0;
    s8                field_4;
    u8                unk_5[3];
    s32               field_8;
    s32               field_C;
    s32               field_10;
    s8                unk_14[4];
    s32               field_18[837];
    s32               field_D2C;
    u8                unk_D30[2332];
    s32               field_164C;
    u8                unk_1650[1372];
    s32               field_1BAC;
    u8                unk_1BB0[20];
    s32               field_1BC4;
    u8                unk_1BC8[16];
    s32               field_1BD8;
    VC_CAMERA_INTINFO vcCameraInternalInfo_1BDC; // Debug camera info.
    s_800BE9FC        field_1BE4;
    s32               field_2BE8;
} s_800BCE18;
STATIC_ASSERT_SIZEOF(s_800BCE18, 11244); // TODO: Likely even larger. `func_8003CB44` accesses some 16 byte fields at 0x2BEC. `func_8003BE50` also uses it.

typedef struct
{
    s8  unk_0[28];
    s16 field_1C;
    s8  unk_1E[304];
    s32 field_150;
    s32 field_154;
    s32 field_158;
    s8  unk_15A[1068];
    s32 field_588;
    // More may follow.
} s_800C1020;

typedef struct
{
    s8 unk_0[28];
} s_800C117C;
STATIC_ASSERT_SIZEOF(s_800C117C, 28);

typedef struct
{
    u16 field_0;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    u16 field_E;
    union
    {
        s8  field_0[3];
        u16 field_01;
    } field_F;
    s8  field_14;
    u8  field_15;
    s8  field_16;
    s8  field_17;
} s_800C1658;

typedef struct
{
    u8 field_0;
    s8 field_1;
    s8 field_2;
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
    s8  unk_0[4];
    s32 field_4;
    s32 field_8;
} s_800C1688;

typedef struct
{
    s8  unk_0[2];
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
    s8  unk_0[12];
    s8  field_C;
    s8  field_D;
    s8  field_E;
    s8  unk_F;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s8  field_1C;
    s8  field_1D;
    s8  field_1E;
    s8  unk_1F;
} s_800C39A8;
STATIC_ASSERT_SIZEOF(s_800C39A8, 32);

typedef struct
{
    s32 unk_0[36];
    s32 field_24;
    s8  unk_2[212];
    s32 field_168;
    s32 field_16C;
    s32 field_170;
    s32 unk_174;
    s16 field_178;
    s16 field_17A;
    s16 field_17C;
    s32 field_180;
    s32 field_184;
    s32 field_188;
} s_800C3BE8;

typedef struct
{
    s8  unk_0[36];
    s32 field_24;
} s_800C3E18;

typedef struct
{
    s8      field_0;
    s8      field_1;
    s8      field_2;
    s8      field_3;
    s32     field_4;
    s32     field_8;
    s8      unk_C[12];
    s32     field_18;
    s8      field_1C;
    s8      field_1D;
    s8      field_1E;
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
} s_D_800C4168;

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

typedef struct
{
    s8   unk_0[216];
    void (*routine_D8)();
    s8   unk_DC[8];
    s32  (*routine_E4)(s_SubCharacter* chara0, s_SubCharacter* chara1);
} s_D_800C957C;

typedef struct
{
    VECTOR3 field_0;
    VECTOR3 field_C;
    s8      unk_18[6];
    u8      field_1E;
    u8      field_1F;
} s_func_800CFFF8;

/** Holds file IDs of anim/model/texture for each `e_ShCharacterId`, along with some data used in VC camera code. */
typedef struct
{
    s16   animFileIdx;
    s16   modelFileIdx;
    s16   textureFileIdx;
    s16   field_6;
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
    s8      unk_C[3];
    u8      field_10; // Some count related to bone hierarchy.
    s8      unk_11;
    s8      field_12;
    s8      field_13;
    s8      field_14;
    s8      unk_15[8];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 28);

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

/** @brief Initial demo game state data, stored inside MISC/DEMOXXXX.DAT files. */
typedef struct _DemoWork
{
    s_ShSaveUserConfig config_0;
    u8                 unk_38[200];
    s_ShSavegame       savegame_100;
    u8                 unk_37C[1148];
    u32                frameCount_7F8;
    u16                randSeed_7FC;
} s_DemoWork;
STATIC_ASSERT_SIZEOF(s_DemoWork, 2048);

/** @brief Per-frame demo data, stored inside MISC/PLAYXXXX.DAT files. */
typedef struct _DemoFrameData
{
    s_AnalogController analogController_0;
    s8              gameStateExpected_8; /** Expected value of `g_GameWork.gameState_594` before `analogController_0` is processed, if it doesn't match `Demo_Update` will display `STEP ERROR` and stop reading demo. */
    u8              videoPresentInterval_9;
    u8              unk_A[2];
    u32             randSeed_C;
} s_DemoFrameData;
STATIC_ASSERT_SIZEOF(s_DemoFrameData, 16);

/** @brief Associates a demo number/ID with PLAYXXXX.DAT/DEMOXXXX.DAT file IDs. */
typedef struct _DemoFileInfo
{
    s16 demoFileId_0;       /** MISC/DEMOXXXX.DAT, initial gamestate for the demo and user config override. */
    s16 playFileId_2;       /** MISC/PLAYXXXX.DAT, data of button presses/randseed for each frame. */
    s32 (*canPlayDemo_4)(); /** Optional funcptr, returns whether this demo is eligible to be played (unused in retail demos). */
} s_DemoFileInfo;
STATIC_ASSERT_SIZEOF(s_DemoFileInfo, 8);

#define DEMO_FILE_COUNT_MAX 5
extern s_DemoFileInfo g_Demo_FileIds[DEMO_FILE_COUNT_MAX]; // 0x800AFDC4
/* TODO: data migration
s_DemoFileInfo g_Demo_FileIds[DEMO_FILE_COUNT_MAX] = {
    { FILE_MISC_DEMO0009_DAT, FILE_MISC_PLAY0009_DAT, NULL },
    { FILE_MISC_DEMO000A_DAT, FILE_MISC_PLAY000A_DAT, NULL },
    { FILE_MISC_DEMO0003_DAT, FILE_MISC_PLAY0003_DAT, NULL },
    { FILE_MISC_DEMO000B_DAT, FILE_MISC_PLAY000B_DAT, NULL },
    { FILE_MISC_DEMO0005_DAT, FILE_MISC_PLAY0005_DAT, NULL },
};
*/

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

typedef struct _800B5494
{
    s32 field_0;
    s32 unk_4[9];
} s_800B5494;
STATIC_ASSERT_SIZEOF(s_800B5494, 40);

extern s_800B5494 D_800B5494;

/** TODO: `g_MapOverlayHeader` is part of the overlay bin files. Maybe should be moved to `maps/shared.h` or `dynamic/dynamic.h`. */
typedef struct _MapOverlayHeader
{
    s8                unk_0[4];
    s8                (*getMapRoomIdxFunc_4)(s32 x, s32 y);                              // Called by `func_80036420`.
    s8                field_8;
    s8                unk_9[3];
    s8                unk_C[4];
    s32               (*func_10)();
    s8                field_14;
    s8                unk_15[3];
    s8                unk_18[4];
    s_AreaLoadParams* mapAreaLoadParams_1C;
    void              (**mapEventFuncs_20)();                                            /** Points to array of event functions. */
    s8                unk_24[12];
    char**            mapMessageStrings_30;                                              /** Points to array of `char*` for each displayed message in the map. */
    s_AnimInfo*       animInfo_34;
    s8                unk_38[8];
    void              (*func_40)();
    void              (*func_44)();
    s8                unk_48[4];
    s_func_800625F4*  field_4C;
    s8                unk_50[16];
    s8                unk_60[104];
    void              (*func_C8)();
    void              (*func_CC)(s32);
    s32               (*func_D0)(s32, void*, s16, s32); // 0x800C964C
    s8                unk_D4[24];
    s32               (*func_EC)();
    s8                unk_F0[76];
    s32               (*func_13C)(s32, s32, void*, s16, s32); // 0x800C96B8
    s8                unk_140[40];
    void              (*func_168)(void*, void*, void*);
    s8                unk_16C[4];
    s8                unk_170[36];
    void              (*charaUpdateFuncs_194[Chara_Count])(s_SubCharacter*, void*, s32); /** Guessed params. Funcptrs for each `e_ShCharacterId`, set to 0 for IDs not included in the map overlay. Called by `func_80038354`. */
    u8                charaGroupIds_248[4];                                              /** `e_ShCharacterId` values where if `s_SpawnInfo.charaId_4` == 0, `charaGroupIds_248[0]` is used for `charaSpawnsA_24C` and `charaGroupIds_248[1]` for `charaSpawnsB_30C`. */
    s_SpawnInfo       charaSpawnsA_24C[16];                                              /** Array of chara type/position/flags, flags_6 == 0 are unused slots? Read by `func_80037F24`. */
    s_SpawnInfo       charaSpawnsB_30C[16];                                              /** Array of chara type/position/flags, flags_6 == 0 are unused slots? Read by `func_80037F24`. */
    VC_ROAD_DATA      roadDataList_3CC[48];
    // TODO: A lot more in here.
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 2124); // Size incomplete.

extern s_FsImageDesc g_MainImg0; // 0x80022C74 - TODO: part of main exe, move to main/ headers?

extern s_80024C90 D_80024C90; 

extern s32 D_8002500C; // Some sort of struct inside RODATA, likely a constant.

extern s8* D_8002510C;

/** "\x07PAUSED" string */
extern char D_80025394[];

extern s32 D_80025528; // Type assumed.

extern s32 D_80025530; // Type assumed.

extern u8 D_80025D6C[];

extern u32 D_80025DC0[];

extern RECT D_80028A20;

extern RECT D_8002AB10;

extern RECT D_8002ABA4;

extern s_8002AC04 D_8002AC04[];

extern s_800BE9FC D_8002B2CC;

extern u8 D_800A8E58;

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

extern u16 D_800A9774[];

extern s32 D_800A9EB0;

extern s32 D_800A9EBC; // Type assumed.

extern s32 D_800A9EC4; // Type assumed.

extern s_FsImageDesc D_800A9FA8;

extern s32 D_800A9768;

extern s32 D_800A976C;

extern void (*D_800A977C[])(); // Function pointer array, maybe state funcs of some kind.

extern u16 D_800A98AC[];

extern s_800A992C D_800A992C[];

extern u8 D_800A9944;

/** Used in func_800D929C from map0_s00.c. */
extern s32 D_800A999C;

/** Array of indices? */
extern s8 D_800A99B4[];

/** Array of indices? */
extern s8 D_800A99CC[];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A0C; // Old IDB name FS_AllFilesLoaded, though FS code doesn't set it.

extern s32 D_800A9A10;

extern s32 D_800A9A1C;

extern void (*D_800A9A2C[])(); // SysState func table.

extern s32 D_800A9A68;

extern s32 D_800A9A74;

extern s32 D_800A9A78;

extern u32 D_800A9A7C;

extern s8 D_800A9A80;

extern s32 D_800A9A84;

extern s32 D_800A9A88;

extern RECT D_800A9A6C; // RECT <320, 256, 160, 240>, only used in SysState_Fmv_Update?

extern s_FsImageDesc D_800A9EB4;

extern s_800C37D8 D_800AA274[];

extern s_800A93CC D_800A93CC[];

extern s_800AA894 D_800AA894[];

/** String color. */
extern s16 g_StringColorId; // 0x800AD498

extern s32 D_800AD49C;

extern s32 D_800AE178;

extern s32 D_800AE17C;

extern s32 D_800AE180;

extern u8 D_800AE184;

extern u8 D_800AE185;

extern u8 D_800AE186;

extern s8 D_800AE187;

extern s32 D_800AE1AC;

extern s32 D_800AE1B0;

extern s16 D_800AF210;

extern s16 D_800AF212;

extern s8 D_800AF214;

extern s8 D_800AF215;

extern s8 D_800AF216;

extern s_MaybeCharacterAnim g_MaybePlayerAnims[];

extern s32 D_800AFC7C;

extern s32 D_800AFC90;

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern s32 (*D_800AFD08[])(); // Function pointer array.

extern s32 D_800AFD9C;

extern s32 D_800AFDEC;

extern s_800AFE08 D_800AFE08;

extern s_800AFE24 D_800AFE24;

extern s_800B55E8 D_800B2780[];

extern s_800B55E8 D_800B3680[];

extern s_800B55E8 D_800B4580[];

extern s32 D_800B5480;

extern s_800B5488 D_800B5488;

extern s32 D_800B548C;

extern s32 D_800B54BC;

extern s_800B55E8 D_800B55E8[2];

extern s32 D_800B55FC;

extern s32 D_800B5618;

extern DVECTOR g_Gfx_DebugStringPosition0;

extern DVECTOR g_Gfx_DebugStringPosition1;

extern s32 D_800B5C28;

extern s32 D_800B5C30;

extern s_800B5C40 D_800B5C40[];

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

extern s32 D_800BCD5C;

extern s8 D_800BCD78;

extern s32 D_800BCD84;

extern s32 D_800BCD90[];

extern s_800BCDA8 D_800BCDA8[2];

extern s32 D_800BCDB0; // Type assumed.

extern s32 D_800BCDC0[];

extern u8 D_800BCDD4;

extern s8* D_800BCDE0; // Type assumed.

extern u16 D_800BCE14;

extern s_800BCE18 D_800BCE18;

extern s_800C1020 D_800C1020;

extern s_800C117C D_800C117C[];

extern s8* D_800C15B0;

extern s32 D_800C15B8;

extern s8 D_800C15B4;

extern s16 D_800C15C4;

extern s16 D_800C15C6;

extern s16 D_800C15C8;

extern s32 D_800C15E0;

extern u8 D_800C15F0;

extern s16 D_800C15F8[];

extern s_800C1658 D_800C1658;

extern u16 D_800C1666;

extern s8 D_800C166A;

extern s8 D_800C166C;

extern s8 D_800C166E;

extern s8 D_800C166F;

extern s16 D_800C167C;

extern s16 D_800C167E;

extern s_800C1670 D_800C1670;

extern s_800C1678 D_800C1678;

extern u8 g_Sd_VolumeBgm; // 0x800C1685

extern u8 g_Sd_VolumeXa; // 0x800C1686

extern u8 g_Sd_VolumeSe; // 0x800C1684

extern s8 g_Sd_ReverbDepth; // 0x800C1687;

extern u8 D_800C1673;

extern s_800C1688 D_800C1688;

extern u8 D_800C16A8[];

extern s32 D_800C16C8; // Type assumed.

extern GsCOORD2PARAM D_800C3928;

extern u8 D_800C3950;

extern s32 D_800C3954;

extern s32 D_800C3958;

extern s32 D_800C395C;

extern s32 D_800C3990;

extern s32 D_800C3994;

extern s32 D_800C3998;

extern s32 D_800C399C;

extern u8 D_800C37D0;

extern s_800C37D8* D_800C37D8;

extern s_800C38B0 D_800C38B0;

extern s32 D_800C38B4;

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

extern u8 D_800C39A0;

extern s_800C39A8 D_800C39A8[];

extern GsCOORDINATE2 D_800C3AE8;

extern SVECTOR3 D_800C3B38;

extern VbRVIEW D_800C3B48;

extern s_800C3BE8 D_800C3BE8;

extern s_800C3E18 D_800C3E18;

extern s_D_800C4168 D_800C4168;

extern s32 D_800C4558;

extern s32 D_800C455C;

extern s16 D_800C457E;

extern s16 D_800C4580;

extern s16 D_800C4582;

extern s16 D_800C4584;

extern s16 D_800C4586;

extern s8 D_800C4588;

extern s16 D_800C45AC;

extern s16 D_800C45AE;

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
extern s8 D_800C457C;

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

extern s_D_800C957C D_800C957C;

extern s32 (*D_800C9650)(s_SubCharacter*, s_SubCharacter*);

extern void (*D_800C9658)(s_SubCharacter*, s_SubCharacter*);

extern void (*D_800C9660)(s_SubCharacter*, s_SubCharacter*);

extern s64 (*D_800C9664)(s_SubCharacter*, s_SubCharacter*); // Is it really `s64`???

extern void (*D_800C96A0)(s_SubCharacter*, s_SubCharacter*);

extern s32 (*D_800C96A4)(s_SubCharacter*, s_SubCharacter*);

extern s32 (*D_800C96A8)(s_SubCharacter*, s_SubCharacter*);

extern s32 (*D_800C96B0)(s_SubCharacter*, s_SubCharacter*);

extern s32 (*D_800C96B4)(s_SubCharacter*, s_SubCharacter*); // or this???

extern RECT D_801E557C[];

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

extern s32 g_Demo_DemoFileIdx; // 0x800C4840

extern s32 g_Demo_PlayFileIdx; // 0x800C4844

extern s_ShSaveUserConfig g_Demo_UserConfigBackup; // 0x800C4850

extern u32 g_Demo_PrevRandSeed; // 0x800C4888

extern u32 g_Demo_RandSeedBackup; // 0x800C488C

extern s_DemoFrameData* g_Demo_CurFrameData; // 0x800C4890

extern s32 g_Demo_DemoStep; // 0x800C4894

extern s32 g_Demo_VideoPresentInterval; // 0x800C4898

extern s32 g_Demo_DemoId; // 0x800AFDB8

extern u16 g_Demo_RandSeed; // 0x800AFDBC

extern void* g_Demo_PlayFileBufferPtr; // 0x800AFDC0

extern s16 D_800C6E26;

extern s16 D_800C6E8E;

extern s_800ACAA8 D_800ACAA8[];

extern u8 D_800AD480[24];

extern s_800AD4C8 D_800AD4C8[];

extern s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

/** Initializer for something before the game loop. */
void func_8002E630();

void func_8002E6E4(s32 idx);

void func_8002E730(s32 idx);

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

void func_80031CCC(s32);

void Gfx_DebugStringPosition(s16 x, s16 y);

void Gfx_DebugStringDraw(char* str);

char* Math_IntegerToString(s32 widthMin, s32 value);

void Gfx_Init(u16 screenWidth, s32 isInterlaced);

void func_8003260C(); // Return type assumed.

void func_80032904();

/** Draws some string in display space. */
void func_80032CE8();

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

s32 func_80033548();

void func_80035338(s32 arg0, s8 arg1, u32 arg2, s32 arg3); // arg3 type assumed.

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

void func_80037188();

void Chara_PositionUpdateFromParams(s_AreaLoadParams* params);

void func_8003943C();

/** `SysState_Fmv` update function.
 * Movie to play is decided by `2072 - g_MapEventIdx`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update();

void func_8003B550();

s32 func_8003BD2C();

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003C850();

void func_8003C8F8(s_func_8003C8F8* arg0, s8* arg1);

void func_8003CD6C(s_MapWork* arg0);

void func_8003D01C();

void func_8003D03C();

s32 func_8003D444(s32 idx);

void func_8003D468(s32, s32); // Called by some chara init funcs, similar to `func_8003DD80`?

void func_8003D6A4(u8* arg0);

/** Return type assumed. */
void func_8003D160();

void func_8003D5B4(s8 arg0);

void func_8003D6E0(s32 arg0, s32 arg1, s32 arg2, void* arg3);

/** Param types assumed. */
void func_8003DD80(s32, s32); // Called by some chara init funcs.

void func_8003ED74(s32 arg0, s32 arg1);

void func_8003EDA8();

void func_8003EF10(s32 idx0, s32 idx1, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_80040014();

void func_800410D8(VECTOR3*, s32*, s32*, SVECTOR*, VECTOR3*);

/** Some kind of queue entry load status getter. */
s32 func_80041ADC(s32 queueIdx);

void func_80041C24(s_80041CEC* arg0, s32 arg1, s32 arg2);

/** `arg0` might be `s_Skeleton`, `arg1` might be `s_Bone`. */
void func_80041CB4(s_Skeleton* skel, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears `field_4` in array of skeletons? Might not be skeletons, but the struct fits. */
void func_80041D10(s_Skeleton* skels, s32 size);

void func_80041E98();

void func_80041FF0();

void func_800420C0();

u32 func_80041B1C(void* arg0);

s32 func_80042C04(s32 idx);

/** Gets distance to the edge of a file chunk? */
s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, s32 clip);

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip);

/** Maybe facilitates file chunk streaming as the player moves around the map. */
s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s16 fileChunkCoordX, s16 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip);

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

void func_80045D28(s32 caseArg);

void sd_init();

u8 func_80045B28();

void sd_work_init();

void func_80046048(u16 cmd, s32 arg1, s32 vol); // SD Func. Last arg is a u8 value.

void func_8004690C(s32);

/** Sound func. */
void func_80046B78();

s32 func_80046DCC(s32 idx);

void func_8004729C(u16 arg0);

void func_800472BC(s32 arg0);

void func_8004760C();

/** Args are volume levels. */
void Sd_SetVolume(u8 arg0, s16 arg1, u8 arg2);

void func_8004692C(u16);

void func_800469AC();

void func_800469E8();

void func_80046A24(u16);

void func_80046A70();

void func_80046AD8();

void func_80046D3C(u16);

void func_8004729C(u16);

void Sd_SetVolBgm(s16 volLeft, s16 volRight);

void Sd_SetVolXa(s16 volLeft, s16 volRight);

s16 Sd_GetVolSe(s16 arg0);

void Sd_SetReverbDepth(s8 depth);

void Sd_SetReverbEnable(s32 mode);

void func_80047B24(s32 arg0);

void func_80047D1C();

void func_80047D50();

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

/** Nullsub */
void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4);

/** Nullsub */
void func_800485B8(s32 arg0, u8 arg1, u32 arg2);

void func_800485C0(s32 idx);

s32 func_80048954(s32 com, u8* param, u8* res);

void func_8004729C(u16);

void func_8004A8C0(s32 arg0);

void func_8004A8CC();

void func_8004B684();

void func_8004B6D4(s16 arg0, s16 arg1);

void func_8004B74C(s16 arg0);

/** Draws string. */
void func_8004B76C(char* str, s32 useFixedWidth);

void func_8004BCBC(s32 arg0);

/** Used for item rotation and item scrolling in the inventory. */
void func_8004BCDC(SVECTOR* arg0, GsCOORDINATE2* arg1);

void func_8004BFE8();

void func_8004C040();

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

void GameFs_MapItemsTextureLoad(s32);

void func_800540A4(s8);

void func_80054634();

void func_800546A8(s32 arg0);

void func_800553C4(s8 arg0, s8 arg1, s8 arg2, s8 arg3);

/** `arg0` type assumed. */
void func_80055434(VECTOR3* vec);

void func_80054928();

void func_80054A04(s32 arg0);

void func_80056D64(s8* prevStr, s8* newStr);

s32 func_8005C7D0(s_SubCharacter*, s32);

void func_8005C814(s16*, s_SubCharacter*);

void func_8005DC1C(s32, VECTOR3*, s32, s32); // Types assumed.

void func_8005DD44(s32, VECTOR3*, s32, s8); // Types assumed.

void func_8005DE0C(s32, VECTOR3*, s32, s32, s32); // Types assumed.

void func_8005E0DC(s32 arg0); // Types assumed.

void func_8005E89C();

void func_8005F6B0(s_SubCharacter*, s32*, s32, s32);

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty`. */
void func_80089128();

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty` with `0` and then `1`. */
void func_800892A4(s32 arg0);

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

void func_80087EA8(s32 arg0);

void func_80087EDC(s32 arg0);

void func_80088028();

void func_80088048();

void func_800880F0(s32 arg0);

void func_800881B8(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB);

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5);

s32 func_80088D0C();

void func_80088D34(s32 idx);

s32 func_8008F434(s32 arg0);

void func_800890B8();

void func_800892A4(s32 idx);

void func_800892DC(s32 idx, s32 arg1);

void func_80089314(s32 arg0);

void func_800893D0(s32 arg0);

void func_8008944C();

void func_80089470();

void func_80089494();

void func_800894B8(s32 arg0);

void func_800894DC();

void func_80089500();

// `arg0` is a pointer.
s32 func_8008973C(s32 arg0, s32 arg1, s_func_8008973C* ptr);

void func_80089840(s_func_80089840* arg0);

s32 func_8008A35C(s_8008A35C* arg0, s32 arg1);

void func_8008A384(s_SubCharacter* chara);

void func_8008A398(s_SubCharacter* chara);

void func_8008A3AC(s_SubCharacter* chara);

void func_8008B398();

void func_8008B3E4(s32 arg0);

void func_8008B40C(s32 arg0, s32 arg1);

void func_8008B438(s32 arg0, s32 arg1, s32 arg2);

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

/** Sets the debug string position. */
void func_8005BF0C(s16 unused, s16 x, s16 y);

s16 func_8005BF38(s16 arg0);

/** `arg0` type assumed. */
void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3);

void func_8005CB20(s_SubCharacter*, void*, s16, s16);

void func_800622B8(s32, s_SubCharacter*, s32, s32);

void func_80066E40();

void func_80066E7C();

void func_800699F8(s_func_800699F8* arg0, s32 arg1, s32 arg2);

s32 func_80069B24(s32 arg0, void* arg1, void* arg2);

void func_8006A178(s_func_8006A178* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_8006A3B4(s32 arg0, s32 arg1, s32 arg2);

void func_8006BDDC(s_func_8006BDDC* arg0, s16 arg1, s16 arg2);

s32 func_8006CC44(s32 arg0, s32 arg1, s_func_8006CC44* arg2);

s32 func_8006FD90(s_SubCharacter*, s32, s32, s32);

s32 func_80070360(s_SubCharacter*, s32, s32);

void func_800705E4(GsCOORDINATE2*, s32, s32, s32, s32);

void func_80074254(s32 arg0, s32 arg1); // `arg1` is pointer?

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Gfx_VSyncCallback();

/** Sets the position of the next string to be drawn by `Gfx_StringDraw`. */
void Gfx_StringSetPosition(s32 x, s32 y);

/** Sets the color of the next string drawn by `Gfx_StringDraw`. (TODO: add color list) */
void Gfx_StringSetColor(s16 colorId);

/** Draws a string in display space. */
void Gfx_StringDraw(char* str, s32 arg1);

/** Draws an integer string in display space. */
void Gfx_StringDrawInt(s32 widthMin, s32 val);

void func_8004BB10();

void func_8004BB4C(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3);

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2);

void Settings_ScreenXYSet(s32 x, s32 y);

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y);

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SavegameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SavegameReadPlayer();

s32 MainLoop_ShouldWarmReset();

void Game_WarmBoot();

void Joy_Init();

void Joy_ReadP1();

void Joy_Update();

void func_800348C0();

void GameState_MainLoadScreen_Update();

void func_800348E8();

void Game_SavegameInitialize(s8 overlayId, s32 difficulty);

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

s32 func_8003528C(s32 idx0, s32 idx1);

void func_80035B04(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord);

void func_80035DB4(s32);

void AreaLoad_UpdatePlayerPosition();

void func_800363D0();

void func_8003640C(s32 arg0);

void func_80036420();

s32 func_8003647C();

s32 func_80036498();

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124();

void func_80037154();

void func_80037388();

void func_800373CC(s32);

void func_80037E40(s_SubCharacter* chara);

void func_80037E78(s_SubCharacter* chara);

void func_80037F24(s32);

void func_80038354();

void GameState_InGame_Update();

void SysState_GamePaused_Update();

void GameState_LoadStatusScreen_Update();

void GameState_LoadMapScreen_Update();

void SysState_Fmv_Update();

void AreaLoad_UpdatePlayerPosition();

s8 func_80039F90();

void SysWork_SavegameUpdatePlayer();

void func_8003A16C();

void SysWork_SavegameReadPlayer();

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

void func_8003C3A0();

void func_8003C3AC();

void func_8003C878(s32);

void func_8003CB3C(s_800BCE18* arg0);

void func_8003D938();

void func_8003DA9C(s32 arg0, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4);

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad();

void func_8003EB54();

void func_8003EBA0();

void func_8003ECBC();

void func_8003ECE4();

void func_8003ED08();

u8 func_8003ED64();

void func_8003EDA8();

void func_8003F170();

void func_80043740();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SavegameResetPlayer();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_800717D0(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord);

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

u8 func_8008A2E0(s32 arg0);

#endif
