#ifndef _BODYPROG_DEMO_H
#define _BODYPROG_DEMO_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the demo game system.
 */

// ======
// ENUMS
// ======

/** @brief Demo states. */
typedef enum _DemoState
{
    DemoState_Exit = -1,
    DemoState_None = 0,
    DemoState_Step = 1
} e_DemoState;

// ========
// STRUCTS
// ========

/** @brief Initial demo game state data, stored inside `MISC/DEMOXXXX.DAT` files. */
typedef struct _DemoWork
{
    s_SaveUserConfig config_0;
    u8               unk_38[200];
    s_Savegame       savegame_100;
    u8               unk_37C[1148];
    u32              frameCount_7F8;
    u16              randSeed_7FC;
} s_DemoWork;
STATIC_ASSERT_SIZEOF(s_DemoWork, 2048);

/** @brief Per-frame demo data, stored inside `MISC/PLAYXXXX.DAT` files. */
typedef struct _DemoFrameData
{
    s_AnalogController analogController_0;
    s8                 gameStateExpected_8; /** Expected value of `g_GameWork.gameState_594` before `analogController_0` is processed, if it doesn't match `Demo_Update` will display `STEP ERROR` and stop reading demo. */
    u8                 videoPresentInterval_9;
    s8                 unk_A[2];
    u32                randSeed_C;
} s_DemoFrameData;
STATIC_ASSERT_SIZEOF(s_DemoFrameData, 16);

/** @brief Associates a demo number/ID with `PLAYXXXX.DAT/DEMOXXXX.DAT` file IDs. */
typedef struct _DemoFileInfo
{
    s16 demoFileId_0;       /** `MISC/DEMOXXXX.DAT`, initial gamestate for the demo and user config override. */
    s16 playFileId_2;       /** `MISC/PLAYXXXX.DAT`, data of button presses/randseed for each frame. */
    s32 (*canPlayDemo_4)(); /** Optional funcptr, returns whether this demo is eligible to be played (unused in retail demos). */
} s_DemoFileInfo;
STATIC_ASSERT_SIZEOF(s_DemoFileInfo, 8);

// ========
// GLOBALS
// ========

#define DEMO_WORK() ((s_DemoWork*)0x800FDE00)

// TODO: Make local. Used in `Demo_Update`.
extern char D_8002B2D8[]; // "STEP ERROR:[H:"
extern char D_8002B2E8[]; // "]/[M:"
extern char D_8002B2F0[]; // "]"

extern s_DemoFrameData* g_Demo_PlayFileBufferPtr; // 0x800AFDC0

extern s32 g_Demo_DemoId; // 0x800AFDB8

extern u16 g_Demo_RandSeed; // 0x800AFDBC

extern s32 D_800AFDF0;

extern s32 g_Demo_DemoFileIdx; // 0x800C4840

extern s32 g_Demo_PlayFileIdx; // 0x800C4844

extern s_SaveUserConfig g_Demo_UserConfigBackup; // 0x800C4850

extern u32 g_Demo_PrevRandSeed; // 0x800C4888

extern u32 g_Demo_RandSeedBackup; // 0x800C488C

// Current packet/frame in buffer.
extern s_DemoFrameData* g_Demo_CurFrameData; // 0x800C4890

extern s32 g_Demo_DemoStep; // 0x800C4894

extern s32 g_Demo_VideoPresentInterval; // 0x800C4898

// ==========
// FUNCTIONS
// ==========

bool Demo_SequenceAdvance(s32 incrementAmt);

void Demo_DemoDataRead();

void Demo_PlayDataRead();

s32 Demo_PlayFileBufferSetup();

void Demo_DemoFileSavegameUpdate();

void Demo_GameGlobalsUpdate();

void Demo_GameGlobalsRestore();

void Demo_GameRandSeedUpdate();

void Demo_GameRandSeedRestore();

void Demo_Start();

void Demo_Stop();

bool func_8008F434(s32 arg0);

/** @brief Gets the active demo state.
 *
 * @param gameState Active game state (`e_GameState`).
 * @return Active demo state `(e_DemoState`).
 */
s32 Demo_StateGet(s32 gameState);

void Demo_ExitDemo();

void func_8008F518();

bool func_8008F520();

/** Generates the backup random demo seed and stores it in `Demo_RandSeedBackup`. */
void Demo_DemoRandSeedBackup();

void Demo_DemoRandSeedRestore();

void Demo_DemoRandSeedAdvance();

bool Demo_Update();

bool Demo_ControllerDataUpdate();

bool Demo_PresentIntervalUpdate();

bool Demo_GameRandSeedSet();

bool func_8008F914(s32 posX, s32 posZ);

#endif
