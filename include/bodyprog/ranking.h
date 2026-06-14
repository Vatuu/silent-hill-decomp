#ifndef _BODYPROG_RANKING_H
#define _BODYPROG_RANKING_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the ranking system.
 */

// ========
// STRUCTS
// ========

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
    u8 field_4;
    u8 field_5;
    u8 field_6;
    u8 field_7;
    u8 field_8;
} s_800C48E0;

// ========
// GLOBALS
// ========

// Data below is likely part of a collected results data struct.

//extern s_800AFDF4 D_800AFDF4;

/** Savegame count. */
extern s16 g_RankingSavegameCount;

/** Gameplay time. */
extern u16 g_RankingGameplayHours;

extern u16 g_RankingWalkDistKm;

extern u16 g_RankingWalkDistM;

extern u16 g_RankingRunDistKm;

extern u16 g_RankingRunDistM;

/** Picked up item count. */
extern u16 g_RankingPickedUpItemCount;

extern u8 g_RankingGameplayMinutes;

extern u8 g_RankingGameplaySeconds;

/** Clear game count. */
extern u8 g_RankingClearGameCount;

/** Clear game endings. */
extern u8 g_RankingClearGameEndings;

extern u8 g_RankingCurrentEndingFlags;

/** Location ID. */
extern u8 g_RankingEndLocationId;

extern u8 g_RankingPickedUpSpecialItemCount;

extern s8 g_RankingScore;

extern u8 g_RankingHasEventFlag61;

extern u8 g_RankingHasEventFlag183;

extern u16 g_RankingEnemyKillsShooting;

extern u16 g_RankingEnemyKillsMelee;

/** Has fired shots. */
extern bool g_RankingHasFiredShot;

/** Close range shot count. */
extern u32 g_RankingCloseRangeShotPercent;

/** Mid range shot count. */
extern u32 g_RankingMidRangeShotPercent;

/** Long range shot count. */
extern u32 g_RankingLongRangeShotPercent;

extern u32 g_RankingNoAimingShotPercent;

/** Game difficulty. */
extern s8 g_RankingGameDifficulty;

/** Continue count. */
extern u8 g_RankingContinueCount;

extern s8 __pad_bss_800C48D2[14];

extern s_800C48E0 D_800C48E0;

// ==========
// FUNCTIONS
// ==========

/** Processes and collects results data. */
void func_8008F94C(void);

void func_800904F4(void);

void Results_DisplayInfo(u32* arg0); // 0x80090664

void func_80090664(void);

u32 func_8009134C(u32 n);

void func_80091380(void);

void func_80091388(s32 arg0, s32 arg1, s32 arg2);

void func_80091464(void);

u32 func_8009146C(s32 arg0);

void func_800914C4(s32 arg0, u32 val);

void GameFs_StfRollBinLoad(void);

void func_800917C0(void* arg0, s32 arg1, s_FsImageDesc* img);

void func_8009185C(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

#endif
