#ifndef _BODYPROG_H
#define _BODYPROG_H

#include "game.h"
#include "main/fsqueue.h"

#define TEMP_MEMORY_ADDR (s8*)0x801A2600

#define IMAGE_BUFFER_0 (u_long*)0x801CFA00
#define IMAGE_BUFFER_1 (u_long*)0x801C8200
#define IMAGE_BUFFER_2 (u_long*)0x801ABE00

#define OPT_SOUND_VOLUME_MAX  128
#define OPT_VIBRATION_ENABLED 128

typedef struct
{
    s16 field_0; // Flags?
} s_8008D850;

typedef struct
{
    s32 field_0;
    s32 field_4; // Maybe index?
    s32 field_8;
} s_80041CB4;

typedef struct
{
    s8  unk_0[4];
    s32 field_4;
    s8  unk_8[18];
} s_80041D10; // Size: 28

typedef struct
{
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
    s8 unk_4[4];
    s8 field_8;
} s_80041CEC;

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
    s32                field_0;
    s32                field_4; // Index into some array.
    s32                field_8;
    s32                field_C;
    s32                field_10;
    struct s_800B5508* field_14;
    s32                field_18; 
} s_800B5508;

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

extern s8* D_8002510C;

/** "\x07PAUSED" string */
extern char D_80025394[];

extern RECT D_8002AB10;

extern s_FsImageDesc D_800A8FF4;

extern s_FsImageDesc D_800A8FFC;

extern s_FsImageDesc D_800A9014;

extern s_FsImageDesc D_800A901C;

extern s_FsImageDesc D_800A9024;

extern s_FsImageDesc D_800A902C;

extern s_FsImageDesc D_800A906C;

extern u16 D_800A9774[];

extern s_FsImageDesc D_800A9FA8;

extern s32 D_800A9768;

extern s32 D_800A976C;

extern void (*D_800A977C[])(void); // Function pointer array, maybe state funcs of some kind.

extern u8 D_800A9944;

/** Used in func_800D929C from map0_s00.c. */
extern s32 D_800A999C;

extern s32 D_800A9A68;

/** Array of indices? */
extern s8 D_800A99B4[];

/** Array of indices? */
extern s8 D_800A99CC[];

extern s16 D_800AD498;

extern s32 D_800AD49C;

/** Unknown bodyprog var. Used in `Fs_QueueStartReadAnm`. */
extern s_800A90FC D_800A90FC[];

extern s_800A992C D_800A992C[];

extern s8 D_800AF214;

extern s_MaybeCharacterAnim g_MaybePlayerAnims[];

extern u16 D_800AFDBC;

extern s32 D_800AFDEC;

extern s_800B5508 D_800B2780[];

extern s_800B5508 D_800B3680[];

extern s_800B5508 D_800B4580[];

extern s32 D_800B5480;

extern s32 D_800B5488; // Index or state?

extern s_800B5508 D_800B5508[];

extern s_800B5508 D_800B55E8;

extern s32 D_800B55FC;

extern s32 D_800B5618;

extern u8 D_800BCDD4;

extern s32 D_800C4710[];

extern void (*D_800C9644)();

extern void (*D_800C9648)(s32);

extern s32 (*D_800C9668)();

extern u16 D_800BCCB0;

extern u16 D_800BCCB2;

/** Accessed by credits and saveload. */
extern s32 D_800BCD0C;

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

extern s_800C4818 D_800C4818;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

extern u8* D_800C7018;

// TODO: Order these by address and add address comments.

extern s32 g_MainLoop_FrameCount;

extern s32 g_Demo_VideoPresentInterval;

extern u32 g_Demo_PrevRandSeed;

extern u32 g_Demo_RandSeedBackup;

extern s_ControllerData* g_Demo_ControllerPacket;

extern s32 g_Demo_DemoStep;

extern s_FsImageDesc g_MainImg0;

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

void func_8002ECE0(s_800B5508* arg0);

void func_80030444();

void func_8003045C();

void func_80030530();

void func_800303E4();

/** Bodyprog function that fades the screen out?
 * Called by:
 * - `main` in main.c
 * - 'func_801E709C' in saveload.c */
void func_800314EC(s_FsImageDesc* image);

void func_8003260C(); // Return type assumed.

void func_80032D1C();

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

void func_80033548(); // Return type assumed.

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

void func_80041CB4(s_80041CB4* arg0, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears some field in some struct. */
void func_80041D10(s_80041D10* array, s32 size);

u8 func_80045B28();

void func_8004690C(s32);

void func_8004729C(u16);

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

void func_80087EA8(s32 arg0);

void func_80087EDC(s32 arg0);

s32 func_80088D0C();

void func_80088D34(s32 idx);

s32 func_8008F434(s32 arg0);

void func_800890B8();

s32 func_8008D850();

void func_8008D78C();

s32 func_8008F470(s32 caseArg);

/** Returns 0. */
s32 func_8008F520();

s32 func_8008F914();

void func_80091380();

// TODO: Arrange these in address order for better insight into the original interface. -- Sezz
// ------------------------------------------------------------------

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5);

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

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad();

/** Loads "Tim00" graphic. */
void GameFs_Tim00TIMLoad();

/** Draws some string in display space. */
void func_80032CE8();

void GFX_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void GFX_VSyncCallback();

/** Sets the position of the next string to be drawn by GFX_StringDraw. */
void GFX_StringPosition(s32 x, s32 y);

/** Draws a string in display space. */
void GFX_StringDraw(char* str, s32 arg1);

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
