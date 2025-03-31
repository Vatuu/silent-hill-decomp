#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
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

typedef struct
{
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s16 field_A;
    s32 field_C;
    s32 field_10;
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
    s8 unk_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
} s_800BCDA8;
STATIC_ASSERT_SIZEOF(s_800BCDA8, 4);

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
    u16 field_0;
    s8  unk_2[19];
    s8  field_15;
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
    s8 unk_0[28];
} s_800C117C;
STATIC_ASSERT_SIZEOF(s_800C117C, 28);

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
    s8  unk_0[4];
    u32 field_4;
    s32 field_8;
} s_800C37D8;

typedef struct
{
    s32 field_0;
    s8  unk_4[4];
    s8  field_8;
} s_800C4620;

typedef struct
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    s8  unk_4[4];
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s8  unk_E[12];
    s32 field_1C;
    s32 field_20;
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
    s8      field_1;
    s8      field_2;
    s8      field_3;
    s32     field_4;
    s_Bone* bones_8;

    // Maybe incorrect.
    s8      unk_C[3];
    u8      field_10;
    s8      unk_11;
    s8      field_12;
    s8      field_13;
    s8      field_14;
    s8      unk_15[8];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 28);

extern s8* D_8002510C;

/** "\x07PAUSED" string */
extern char D_80025394[];

extern s32 D_80025528; // Type assumed.

extern s32 D_80025530; // Type assumed.

extern RECT D_8002AB10;

extern s_8002AC04 D_8002AC04[];

extern s_800BE9FC D_8002B2CC;

extern s8 D_800A8E58;

extern s_FsImageDesc D_800A8FF4;

extern s_FsImageDesc D_800A8FFC;

extern s_FsImageDesc D_800A9014;

extern s_FsImageDesc D_800A901C;

extern s_FsImageDesc D_800A9024;

extern s_FsImageDesc D_800A902C;

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

extern void (*D_800A977C[])(void); // Function pointer array, maybe state funcs of some kind.

extern u8 D_800A97D4[];

extern s_800A992C D_800A992C[];

extern u8 D_800A9944;

/** Used in func_800D929C from map0_s00.c. */
extern s32 D_800A999C;

/** Array of indices? */
extern s8 D_800A99B4[];

/** Array of indices? */
extern s8 D_800A99CC[];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A1C;

extern s32 D_800A9A68;

extern s_FsImageDesc D_800A9EB4;

extern s16 D_800AD498;

extern s32 D_800AD49C;

extern s8 D_800AF214;

extern s_MaybeCharacterAnim g_MaybePlayerAnims[];

extern s32 D_800AFC7C;

extern s32 D_800AFC90;

extern s32 D_800AFD9C;

extern u16 D_800AFDBC;

extern s32 D_800AFDEC;

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

extern s8 D_800BCD78;

extern u8 D_800BCDD4;

extern u16 D_800BCE14;

extern s_800C1020 D_800C1020;

extern s_800C117C D_800C117C[];

extern u8 D_800C37D0;

extern s_800C37D8* D_800C37D8;

extern s32 D_800C4710[];

extern void (*D_800C9644)();

extern void (*D_800C9648)(s32);

extern s32 (*D_800C9668)();

extern u16 D_800BCCB0;

extern u16 D_800BCCB2;

/** Accessed by credits and saveload. */
extern s32 D_800BCD0C;

extern s8 D_800BCD40;

extern s_800BCDA8 D_800BCDA8[];

extern s32 D_800BCDB0; // Type assumed.

extern s8* D_800C15B0;

extern s8 D_800C15B4;

extern s16 D_800C15F8[];

extern s_800C1658 D_800C1658;

extern s_800C1670 D_800C1670;

extern u8 g_Sd_VolumeBgm; // 0x800C1685

extern u8 g_Sd_VolumeXa; // 0x800C1686

extern u8 g_Sd_VolumeSe; // 0x800C1684

extern s8 g_Sd_ReverbDepth; // 0x800C1687;

extern s_800BE9FC D_800BE9FC;

extern u8 D_800C37C8;

extern u32 D_800C37CC;

extern s_800C37D4* D_800C37D4;

extern s16 D_800C38A8;

extern s16 D_800C38AA;

extern s32 D_800C38AC;

extern s16 D_800C38FC;

extern s16 D_800C38FE;

extern s16 D_800C391C;

extern s16 D_800C391E;

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

extern s_800C4818 D_800C4818;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

extern u8* D_800C7018;

extern s8 D_800C9584;

extern s8 D_800C9590;

// TODO: Order these by address.

extern s32 g_MainLoop_FrameCount; // 0x800B9CCC

extern s32 g_Demo_VideoPresentInterval; // 0x800C4898

extern u32 g_Demo_PrevRandSeed; // 0x800C4888

extern u32 g_Demo_RandSeedBackup; // 0x800C488C

extern s_ControllerData* g_Demo_ControllerPacket; // 0x800C4890

extern s32 g_Demo_DemoStep; // 0x800C4894

extern s_FsImageDesc g_MainImg0; // 0x80022C74

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
 * - 'func_801E709C' in saveload.c */
void func_800314EC(s_FsImageDesc* image);

void Gfx_DebugStringPosition(s16 x, s16 y);

void Gfx_DebugStringDraw(char* str);

char* Math_IntegerToString(s32 numDigits, s32 value);

void func_8003260C(); // Return type assumed.

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

s32 func_80033548();

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003c850();

/** Return type assumed. */
void func_8003D160();

/** Param types assumed. */
void func_8003DD80(s32, s32);

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

s32 func_80042DE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_80043338(s_80043338* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

s32 func_800436D8(s_80043338* arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

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

/** Updates a model's animation, variant 1. */
void Anim_Update(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a model's animation, variant 2. */
void func_80044B38(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a model's animation, variant 3. */
void func_80044CA4(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

/** Updates a model's animation, variant 4. */
void func_80044DF0(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_Model* targetModel);

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

u8 func_80045B28();

void func_8004690C(s32);

void Sd_SetVolBgm(s16 volLeft, s16 volRight);

void Sd_SetVolXa(s16 volLeft, s16 volRight);

s16 Sd_GetVolSe(s16 arg0);

void Sd_SetReverbDepth(s8 depth);

void Sd_SetReverbEnable(s32 mode);

void func_80047F18();

void func_80048000();

void func_800481F8();

void Sd_StopSeq();

/** CD function. */
void func_800483D4();

/** CD function. */
void func_80048424();

void func_800485C0(s32 idx);

s32 func_80048954(s32 com, u8* param, u8* res);

void func_8004729C(u16);

void func_8004B9F8(s32 arg0, u8 arg1); // Types assumed.

void func_8005E0DC(s32); // Types assumed.

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty`. */
void func_80089128();

/** Unknown bodyprog func. Called by `Fs_QueueWaitForEmpty` with `0` and then `1`. */
void func_800892A4(s32);

void func_801E2D8C();

void func_8004C8DC();

void func_80085D78(s32 arg0);

void func_80085DC0(s32 arg0, s32 sysStateStep);

void func_80085DF0();

/**  */
void func_80085E6C(s32 arg0, s32 arg1);

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5);

void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_800862F8(s32 arg0, s32 arg1, s32 arg2);

void func_800867B4(s32 caseParam, s32 idx);

void func_800868DC(s32 idx);

void func_800869E4(u8* arg1, u8* arg2, s16* arg3);

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

void func_8008944C();

void func_80089470();

void func_80089494();

void func_800894B8(s32 arg0);

void func_800894DC();

void func_80089500();

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

void func_8005BF0C(s16 arg0, s16 arg1, s16 arg2);

s16 func_8005BF38(s32 arg0);

/** Draws some string in display space. */
void func_80032CE8();

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void Gfx_VSyncCallback();

/** Sets the position of the next string to be drawn by Gfx_StringDraw. */
void Gfx_StringPosition(s32 x, s32 y);

/** Draws a string in display space. */
void Gfx_StringDraw(char* str, s32 arg1);

void Settings_ScreenXYSet(s32 x, s32 y);

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y);

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

/** Passes a command to the sound driver. */
void SD_EngineCmd(s32 cmd);

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SaveGameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SaveGameReadPlayer();

s32 MainLoop_ShouldWarmReset();

void JOY_Init();

void JOY_ReadP1();

void JOY_Update();

void func_800348C0();

void func_800348E8();

void Game_SaveGameInitialize(s8 overlayIdx, s32 difficulty);

/** Loads a map file into `g_OvlDynamic`. */
void GameFs_MapLoad(s32 mapIdx);

s32 func_8003528C(s32 idx0, s32 idx1);

void AreaLoad_UpdatePlayerPosition();

void func_800363D0();

void func_8003640C(s32 arg0);

s32 func_8003647C();

s32 func_80036498();

void func_8003708C(s16* ptr0, u16* ptr1);

void func_80037124();

void func_80037154();

/** SysState_GamePaused handler. */
void func_800391E8();

void SysWork_SaveGameUpdatePlayer();

void func_8003A16C();

void SysWork_SaveGameReadPlayer();

void func_8003BC8C();

void func_8003BCF4();

void func_8003BE28();

void GameFs_BgEtcGfxLoad();

void GameFs_BgItemLoad();

void func_8003BED0();

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad();

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SaveGameResetPlayer();

/** Loads player animations for a given map. Maybe for cutscenes? */
void GameFs_PlayerMapAnimLoad(s32 mapIdx);

/** Resets several global variables to 0. */
void func_8007F1CC();

void func_8007F250(u8* ptr, s8 arg1);

/** Some kind of player anim state check. */
s32 func_8007F26C();

/** Some kind of player anim state check. */
s32 func_8007F2AC();

/** Gets something from the player's current animation? */
s16 Player_AnimGetSomething();

/** Gets some property data from player. */
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

s32 func_800808F8(s32 arg0);

/** Copies savegame into an s_ShSaveGameContainer and calculates footer checksum. */
void SaveGame_CopyWithChecksum(s_ShSaveGameContainer* dest, s_ShSaveGame* src);

/** Updates the footer with the checksum of the given data. */
void SaveGame_ChecksumUpdate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/**
 * Generates a checksum of the given saveData and compares it against the checksum value in the footer.
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

#endif
