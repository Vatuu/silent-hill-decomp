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
    s8  unk_0[8];
    s32 field_8;
    s8  unk_12[2];
    s32 field_14;
    s32 field_20;

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

extern s8* D_8002510C;

/** "\x07PAUSED" string */
extern char D_80025394[];

extern RECT D_8002AB10;

extern s32 D_800A8FEC; // Maybe a distance?

extern s_FsImageDesc D_800A9014;

extern s_FsImageDesc D_800A901C;

extern s_FsImageDesc D_800A9024;

extern s_FsImageDesc D_800A902C;

extern s32 D_800A9768;

extern s32 D_800A976C;

extern void (*D_800A977C[])(void); // Function pointer array, maybe state funcs of some kind.

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

extern s_800B5508 D_800B2780[];

extern s_800B5508 D_800B3680[];

extern s_800B5508 D_800B4580[];

extern s32 D_800B5480;

extern s32 D_800B5488; // Index or state?

extern s_800B5508 D_800B5508[];

extern s_800B5508 D_800B55E8;

extern s32 D_800B55FC;

extern s32 D_800B5618;

extern s32 D_800C4710[];

extern void (*D_800C9644)();

extern void (*D_800C9648)(s32);

extern s32 (*D_800C9668)();

extern s32 D_800B9CC8;

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

extern s8 D_800C457C;

extern u8 D_800C4606;

/** Unknown bodyprog var. Set in `Fs_QueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

extern u8* D_800C7018;

extern s32 g_MainLoop_FrameCount;

extern s32 g_Demo_VideoPresentInterval;

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

/** Bodyprog entrypoint. Called by `main`. */
void MainLoop();

void func_80033548(); // Return type assumed.

/** Unknown bodyprog func. Called by `Fs_QueuePostLoadAnm`. */
void func_80035560(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** Unknown bodyprog func. Called by `Fs_QueueDoThingWhenEmpty`. */
s32 func_8003c850();

void func_8003D160(); // Return type assumed.

/** Some kind of queue entry load status getter. */
s32 func_80041ADC(s32 queueIdx);

void func_80041CB4(s_80041CB4* arg0, s_80041CEC* arg1);

void func_80041CEC(s_80041CEC*);

/** Clears some field in some struct. */
void func_80041D10(s_80041D10* array, s32 size);

u8 func_80045B28();

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

void func_80091380();

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5);

/** Seeks for the English title screen background graphic. */
void GameFS_TitleGfxSeek();

/** Loads the English title screen background graphic. */
void GameFS_TitleGfxLoad();

/** Seeks for the stream overlay. */
void GameFS_StreamBinSeek();

/** Loads the stream overlay. */
void GameFS_StreamBinLoad();

/** Loads the options background graphic and overlay. */
void GameFS_OptionBinLoad();

/** Loads the save/load background graphic and overlay. */
void GameFS_SaveLoadBinLoad();

/** Draws some string in display space. */
void func_80032CE8();

void GFX_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b);

void GFX_VSyncCallback();

/** Sets the position of the next string to be drawn by GFX_StringDraw. */
void GFX_StringPosition(s32 x, s32 y);

/** Draws a string in display space. */
void GFX_StringDraw(char* str, s32 arg1);

void Settings_ScreenXYSet(s32 x, s32 y);

void Settings_ScreenAndVolUpdate();

void Settings_RestoreDefaults();

/** Passes a command to the sound driver. */
void SD_EngineCmd(s32 cmd);

/** Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
void SysWork_SaveGameUpdatePlayer();

/** Updates SysWork with player info from the savegame buffer (position, rotation, health). */
void SysWork_SaveGameReadPlayer();

void Game_SaveGameInitialize(s8 overlayIdx, s32 difficulty);

/** Resets player info in the savegame buffer (inventory, health, playtime). */
void Game_SaveGameResetPlayer();

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

#endif
