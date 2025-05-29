#ifndef _DEMO_SYSTEM_H
#define _DEMO_SYSTEM_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the demo game system.
 */

// ==========
// FUNCTIONS
// ==========

s32 Demo_SequenceAdvance(s32 incrementAmt);

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

s32 func_8008F434(s32 arg0);

s32 func_8008F470(s32 caseArg);

void Demo_ExitDemo();

void func_8008F518();

s32 func_8008F520();

/** Generates the backup random demo seed and stores it in `Demo_RandSeedBackup`. */
void Demo_DemoRandSeedBackup();

void Demo_DemoRandSeedRestore();

void Demo_DemoRandSeedAdvance();

s32 Demo_ControllerDataUpdate();

s32 Demo_PresentIntervalUpdate();

s32 Demo_GameRandSeedSet();

s32 func_8008F914();

#endif
