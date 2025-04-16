#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"

#define TEMP_MEMORY_ADDR (s8*)0x801A2600

#define IMAGE_BUFFER_0 (u_long*)0x801CFA00
#define IMAGE_BUFFER_1 (u_long*)0x801C8200
#define IMAGE_BUFFER_2 (u_long*)0x801ABE00

#define CD_ADDR_0 0x801E2600

#define OPT_SOUND_VOLUME_MAX  128
#define OPT_VIBRATION_ENABLED 128

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

/** Something related to ANM files. See `D_800A90FC`. */
typedef struct
{
    s16 fileIdx;
    s16 field_2;
    u32 field_4;
    u32 field_8;
    u32 field_C;
} s_800A90FC;

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
    s8 unk_0[15];
    s8 field_F;
    s8 unk_10[8];
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
    s32                field_0;
    s8                 field_4[16]; 
    struct s_800B5508* field_14;
    s32                field_18; 
} s_800B5508;

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
    s8 unk_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800BCDA8;
STATIC_ASSERT_SIZEOF(s_800BCDA8, 4);

typedef struct _s_800BCE18
{
    s8                unk_0[4];
    s8                field_4;
    u8                unk_5[3];
    u8                unk_8[0x1644];
    s32               field_164C;
    u8                unk_1650[0x58C];
    VC_CAMERA_INTINFO vcCameraInternalInfo_1BDC; // Debug camera info.
    s_800BE9FC        field_1BE4;
    s32               field_2BE8;
} s_800BCE18;
STATIC_ASSERT_SIZEOF(s_800BCE18, 0x2BEC); // TODO: likely even larger. `func_8003CB44` accesses some 16 byte fields at 0x2BEC.

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
    s8  field_2[2];
    u16 field_4;
    u16 field_6;
    s8  unk_8[13];
    u8  field_15;
} s_800C1658;

typedef struct
{
    u8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800C1670;

typedef struct
{
    s8 unk_0[12];
    s8 field_C;
    s8 field_D;
    s8 field_E;
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
    s32 field_4;
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

extern s8* D_8002510C;

/** "\x07PAUSED" string */
extern char D_80025394[];

extern s32 D_80025528; // Type assumed.

extern s32 D_80025530; // Type assumed.

extern RECT D_80028A20;

extern RECT D_8002AB10;

extern s_8002AC04 D_8002AC04[];

extern s_800BE9FC D_8002B2CC;

extern s8 D_800A8E58;

extern s_FsImageDesc D_800A8FF4;

extern s_FsImageDesc D_800A8FFC;

extern s_FsImageDesc D_800A9004;

extern s_FsImageDesc D_800A9014;

extern s_FsImageDesc D_800A901C;

extern s_FsImageDesc D_800A9024;

extern s_FsImageDesc D_800A902C;

extern s_FsImageDesc D_800A9044;

extern s_FsImageDesc D_800A904C;

extern s_FsImageDesc D_800A906C;

/** Unknown bodyprog var. Used in `Fs_QueueStartReadAnm`. */
extern s_800A90FC D_800A90FC[];

extern u16 D_800A9774[];

extern s32 D_800A9EB0;

extern s32 D_800A9EBC; // Type assumed.

extern s32 D_800A9EC4; // Type assumed.

extern s_FsImageDesc D_800A9FA8;

extern s32 D_800A9768;

extern s32 D_800A976C;

extern void (*D_800A977C[])(); // Function pointer array, maybe state funcs of some kind.

extern u8 D_800A97D4[]; // Something related to save slots.

extern s8 D_800A97D6; // Save slot index?

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

extern RECT D_800A9A6C; // RECT <320, 256, 160, 240>, only used in SysState_Fmv_Update?

extern s_FsImageDesc D_800A9EB4;

extern s_800C37D8 D_800AA274[];

/** String color. */
extern s16 g_StringColorId; // 0x800AD498

extern s32 D_800AD49C;

extern s32 D_800AE180;

extern s8 D_800AE187;

extern s32 D_800AE1AC;

extern s32 D_800AE1B0;

extern s8 D_800AF214;

extern s_MaybeCharacterAnim g_MaybePlayerAnims[];

extern s32 D_800AFC7C;

extern s32 D_800AFC90;

extern u8 D_800AFD04;

extern u8 D_800AFD05;

extern s32 D_800AFD9C;

extern u16 D_800AFDBC;

extern s32 D_800AFDEC;

extern s_800AFE08 D_800AFE08;

extern s_800AFE24 D_800AFE24;

extern s_800B55E8 D_800B2780[];

extern s_800B55E8 D_800B3680[];

extern s_800B55E8 D_800B4580[];

extern s32 D_800B5480;

extern s32 D_800B5488; // Index or state?

extern s_800B5508 D_800B5508[];

extern s_800B55E8 D_800B55E8[2];

extern s32 D_800B55FC;

extern s32 D_800B5618;

extern DVECTOR g_Gfx_DebugStringPosition0;

extern DVECTOR g_Gfx_DebugStringPosition1;

extern s32 D_800B5C30;

extern s_800B5C40 D_800B5C40[];

extern s32 D_800B5C7C;

extern u8 D_800BC74F;

extern u16 D_800BCCB0;

extern u16 D_800BCCB2;

extern s32 D_800B7CC4;

/** Accessed by credits, options, and saveload. */
extern s32 D_800BCD0C;

extern s16 D_800BCD28;

extern s8* D_800BCD2C;

extern u8 D_800BCD3E;

extern u8 D_800BCD3F;

extern s8 D_800BCD40;

extern s8 D_800BCD78;

extern s32 D_800BCD84;

extern s_800BCDA8 D_800BCDA8[];

extern s32 D_800BCDB0; // Type assumed.

extern u8 D_800BCDD4;

extern u16 D_800BCE14;

extern s_800BCE18 D_800BCE18;

extern s_800C1020 D_800C1020;

extern s_800C117C D_800C117C[];

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s16 D_800C15F8[];

extern s_800C1658 D_800C1658;
extern u16 D_800C1666;

extern s8 D_800C166A;

extern s8 D_800C166C;

extern s8 D_800C166F;

extern s16 D_800C167C;

extern s_800C1670 D_800C1670;

extern s_800C1678 D_800C1678;

extern u8 g_Sd_VolumeBgm; // 0x800C1685

extern u8 g_Sd_VolumeXa; // 0x800C1686

extern u8 g_Sd_VolumeSe; // 0x800C1684

extern s8 g_Sd_ReverbDepth; // 0x800C1687;

extern u8 D_800C1673;

extern s_800C1688 D_800C1688;

extern u8 D_800C16A8;

extern s32 D_800C16C8; // Type assumed.

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

/** String X position. */
extern s16 g_StringPositionX0; // 0x800C38A8

/** String Y position. */
extern s16 g_StringPositionY; // 0x800C38AA

/** String X position as `s32`. It's unclear why there are two. */
extern s32 g_StringPositionX1; // 0x800C38AC

extern s16 D_800C38FC;

extern s16 D_800C38FE;

extern s16 D_800C391C;

extern s16 D_800C391E;

extern s_800C39A8 D_800C39A8[];

extern s32 D_800C3AE8; // Type assumed.

extern s32 D_800C3B38; // Type assumed.

extern s32 D_800C3B48; // Type assumed.

extern s_800C3BE8 D_800C3BE8;

extern s_800C3E18 D_800C3E18;

extern s32 D_800C4558;

extern s32 D_800C455C;

extern s16 D_800C457E;

extern s16 D_800C4580;

extern s16 D_800C4582;

extern s16 D_800C4584;

extern s16 D_800C4586;

extern s16 D_800C45AC;

extern s16 D_800C45AE;

extern s16 D_800C45BC;

extern s16 D_800C45BE;

extern s16 D_800C45C0;

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

extern u8 D_800C4606;

extern s_800C4620 D_800C4620;

extern s32 D_800C4640; // Type assumed.

extern s32 D_800C46A0;

extern s16 D_800C4700;

extern s16 D_800C4702;

extern s_800C4818 D_800C4818;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

extern s32 D_800C48F0;

extern RECT D_801E557C[];

// TODO: Order these by address.

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

extern s32 g_Demo_VideoPresentInterval; // 0x800C4898

extern u32 g_Demo_PrevRandSeed; // 0x800C4888

extern u32 g_Demo_RandSeedBackup; // 0x800C488C

extern s_ControllerData* g_Demo_ControllerPacket; // 0x800C4890

extern s32 g_Demo_DemoStep; // 0x800C4894

extern s_FsImageDesc g_MainImg0; // 0x80022C74

extern s_800AD4C8 D_800AD4C8[];

/** TODO: `g_MapOverlayHeader` is part of the overlay bin files. Maybe should be moved to `maps/s00.h` or `dynamic/dynamic.h`. */
typedef struct _MapOverlayHeader
{
    u8           unk_0[8];
    s8           field_8;
    u8           unk_9[3];
    u8           unk_C[8];
    s8           field_14;
    u8           unk_15[3];
    u8           unk_18[8];
    void         (**mapEventFuncs_20)(); // Points to array of event functions.
    u8           unk_24[0x1C];
    void         (*func_40)();
    void         (*func_44)();
    u8           unk_48[128];
    void         (*func_C8)();
    void         (*func_CC)(s32);
    s32          (*func_D0)(s32, void*, s16, s32); // 0x800C964C
    u8           unk_D4[24];
    s32          (*func_EC)();
    u8           unk_F0[76];
    s32          (*func_13C)(s32, s32, void*, s16, s32); // 0x800C96B8
    u8           unk_140[40];
    void         (*func_168)(void*, void*, void*);
    u8           unk_16C[4];
    u8           unk_170[604];
    VC_ROAD_DATA roadDataList_3CC[48]; // Ends at 0x84C.
    // TODO: A lot more in here.
} s_MapOverlayHeader;

extern s_MapOverlayHeader g_MapOverlayHeader; // 0x800C957C

/** Initializer for something before the game loop. */
void func_8002E630();

void func_8002E6E4(s32 idx);

void func_8002E730(s32 idx);

/** Initializer for something before the game loop. */
void func_8002E7BC();

void func_8002E830();

void func_8002E85C();

void func_8002E8D4();

s32 func_8002E990();

void func_8002EB88(); // Return type assumed.

void func_8002ECE0(s_800B55E8* arg0);

void func_80030444();

void func_8003045C();

void func_80030530();

void func_800303E4();

/** Bodyprog function that fades the screen out?
 * Called by:
 * - `main` in main.c
 * - 'func_801E709C' in saveload.c
 * */
void func_800314EC(s_FsImageDesc* image);

void func_80031CCC(s32);

void Gfx_DebugStringPosition(s16 x, s16 y);

void Gfx_DebugStringDraw(char* str);

char* Math_IntegerToString(s32 widthMin, s32 value);

void func_8003260C(); // Return type assumed.

void func_80032904();

/** Draws some string in display space. */
void func_80032CE8();

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

s32 func_80033548();

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

void func_8003943C();

/** SysState_Fmv update function.
 * Movie to play is decided by `2072 - g_MapEventIdx`
 * After playback, savegame gets `D_800BCDD8->eventFlagNum_2` event flag set. */
void SysState_Fmv_Update();

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003c850();

/** Return type assumed. */
void func_8003D160();

/** Param types assumed. */
void func_8003DD80(s32, s32);

void func_80040014();

void func_800410D8(VECTOR3*, s32*, s32*, SVECTOR*, VECTOR3*);

/** Some kind of queue entry load status getter. */
s32 func_80041ADC(s32 queueIdx);

void func_80041C24(s_80041CEC* arg0, s32 arg1, s32 arg2);

/** arg0 might be s_Skeleton, arg1 might be s_Bone. */
void func_80041CB4(s_Skeleton* skel, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears field_4 field in array of skeletons? Might not be skeletons, but the struct fits. */
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

/** Updates a character's animation, variant 0. First param might be `s_SubCharacter` instead. */
void Anim_Update0(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a character's animation, variant 1. */
void Anim_Update1(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a character's animation, variant 2. */
void Anim_Update2(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a character's animation, variant 3. */
void Anim_Update3(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

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

void Sd_EngineCmd(s32 cmd);

/** Sound func? */
u8 func_80045B28();

u16 func_80045BC8();

void func_80045BD8(u16 caseArg);

void func_80045D28(s32 caseArg);

void Sd_DriverInit();

u8 func_80045B28();

void func_8004690C(s32);

void func_8004729C(u16);

void Sd_SetVolBgm(s16 volLeft, s16 volRight);

void Sd_SetVolXa(s16 volLeft, s16 volRight);

s16 Sd_GetVolSe(s16 arg0);

void Sd_SetReverbDepth(s8 depth);

void Sd_SetReverbEnable(s32 mode);

void func_80047F18();

void func_80048000();

void func_8004807C();

void func_800480FC();

void func_800481F8();

void func_80048244(s16 cmd);

void func_800482D8();

void Sd_StopSeq();

/** CD function. */
void func_800483D4();

/** CD function. */
void func_80048424();

void func_800485C0(s32 idx);

s32 func_80048954(s32 com, u8* param, u8* res);

void func_8004729C(u16);

void func_8004A8C0(s32 arg0);

void func_8004A8CC();

void func_8004B684();

void func_8004B6D4(s16 arg0, s16 arg1);

void func_8004B74C(s16 arg0);

void func_8004BCBC(s32 arg0);

// TODO: Can probably create status enums for the below funcs' return values to avoid magic,
// but other funcs using similar return patterns should be identified first if they exist.

// TODO: The name `Inventory_HyperBlasterCanAdd` may be suitable, though inventory
// funcs seem to be bunched at a different address.
/** @brief Used to check if the Hyper Blaster can be added to the inventory.
 *
 * @return -1 if it already exists in the inventory,
 *          1 if the Konami gun controller is connected or the savegame flag is set,
 *          0 otherwise.
 */
s32 func_8004C45C();

// TODO: The name `Inventory_HyperBlasterCanUse` may be suitable.
/** @brief Called by status screen to check if Hyper Blaster can be used?
 *
 * @return 2 if the savegame flag is set,
 *         1 if the Konami gun controller is connected,
 *         0 otherwise.
 */
s32 func_8004C4F8();

void func_8004C8DC();

void func_80054024(s8);

void func_800540A4(s8);

void func_800546A8(s32 arg0);

void func_80054928();

void func_80054A04(s8 arg0);

void func_8005E0DC(s32 arg0); // Types assumed.

void func_8005E89C();

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

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5);

void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_800862F8(s32 arg0, s32 arg1, s32 arg2);

void func_800866D4(s32 arg0, s32 arg1, s32 arg2);

void func_80086728(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8008677C(s32 arg0, s32 arg1, s32 arg2);

void func_800867B4(s32 caseParam, s32 idx);

void func_800868DC(s32 idx);

void func_800869E4(u8* arg0, u8* arg1, u16* arg2);

void Camera_SetTranslation(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCamFlag);

void Camera_SetRotation(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
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

void func_80087EA8(s32 arg0);

void func_80087EDC(s32 arg0);

s32 func_80088D0C();

void func_80088D34(s32 idx);

s32 func_8008F434(s32 arg0);

void func_800890B8();

void func_800892A4(s32 idx);

void func_800892DC(s32 idx, s32 arg1);

void func_80089314(s32 arg0);

void func_8008944C();

void func_80089470();

void func_80089494();

void func_800894B8(s32 arg0);

void func_800894DC();

void func_80089500();

s32 func_8008A35C(s_8008A35C* arg0, s32 arg1);

void func_8008A384(s_SubCharacter* chara);

void func_8008A398(s_SubCharacter* chara);

void func_8008A3AC(s_SubCharacter* chara);

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

s16 func_8005BF38(s32 arg0);

void func_80066E40();

void func_80066E7C();

void func_800699F8(s_func_800699F8* arg0, s32 arg1, s32 arg2);

s32 func_8006A3B4(s32 arg0, s32 arg1, s32 arg2);

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Gfx_VSyncCallback();

/** Sets the position of the next string to be drawn by Gfx_StringDraw. */
void Gfx_StringSetPosition(s32 x, s32 y);

/** Sets the color of the next string drawn by Gfx_StringDraw. (TODO: add color list) */
void Gfx_StringSetColor(s16 colorId);

/** Draws a string in display space. */
void Gfx_StringDraw(char* str, s32 arg1);

/** Draws an integer string in display space. */
void Gfx_StringDrawInt(s32 widthMin, s32 val);

void Settings_ScreenXYSet(s32 x, s32 y);

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y);

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

/** Passes a command to the sound driver. */
void Sd_EngineCmd(s32 cmd);

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SaveGameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SaveGameReadPlayer();

s32 MainLoop_ShouldWarmReset();

void Joy_Init();

void Joy_ReadP1();

void Joy_Update();

void func_800348C0();

void func_800348E8();

void Game_SaveGameInitialize(s8 overlayIdx, s32 difficulty);

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

s32 func_8003528C(s32 idx0, s32 idx1);

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

void func_800373CC(s32);

void func_80037F24(s32);

void func_80038354();

void SysWork_SaveGameUpdatePlayer();

void func_8003A16C();

void SysWork_SaveGameReadPlayer();

void func_8003BC8C();

void func_8003BCF4();

void func_8003BE28();

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

void func_8003ECBC();

void func_8003ECE4();

void func_8003ED08();

u8 func_8003ED64();

void func_8003EDA8();

void func_8003F170();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SaveGameResetPlayer();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

void func_800717D0(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord);

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord);

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

/** Forces Pad_Select button press. */
void func_80080458();

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1);

/** Generates a random value of some kind. */
s32 func_80080514();

/** Computes (abs(value) - subtractor) * copysign(value). */
s32 PreservedSignSubtract(s32 value, s32 subtractor);

s32 func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // arg3 type assumed.

void func_8008074C(int arg0, int arg1);

s32 func_80080884();

s32 func_800808AC();

/** Returns a Q shift based on a magnitude. */
s32 Math_GetMagnitudeShift(s32 mag);

/** Copies savegame into an s_ShSaveGameContainer and calculates footer checksum. */
void SaveGame_CopyWithChecksum(s_ShSaveGameContainer* dest, s_ShSaveGame* src);

/** Updates the footer with the checksum of the given data. */
void SaveGame_ChecksumUpdate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates a checksum of the given saveData and compares it against the checksum value in the footer.
 * Returns 1 if the checksums match, otherwise 0.
 */
s32 SaveGame_ChecksumValidate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates an 8-bit XOR checksum over the given data, only appears used with s_ShSaveGame data. */
u8 SaveGame_ChecksumGenerate(s8* saveData, s32 saveDataLength);

void Demo_GameRandSeedUpdate();

void Demo_GameRandSeedRestore();

void Demo_Start();

void Demo_Stop();

void Demo_ExitDemo();

/** Generates the backup random demo seed and stores it in Demo_RandSeedBackup. */
void Demo_DemoRandSeedBackup();

void Demo_DemoRandSeedRestore();

void Demo_DemoRandSeedAdvance();

s32 Demo_PresentIntervalUpdate();

s32 Demo_GameRandSeedSet();

u8 func_8008A2E0(s32 arg0);

#endif
