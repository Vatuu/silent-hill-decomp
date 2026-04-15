#ifndef _BODYPROG_EVENTS_BODYPROGDATA800A99B4_H
#define _BODYPROG_EVENTS_BODYPROGDATA800A99B4_H

extern const s_AreaLoadSfx SFX_PAIRS[25];

extern s8 g_PaperMapFileIdxs[];

extern s8 g_PaperMapMarkingFileIdxs[];

extern char* D_800A99E4[8];

extern s_FsImageDesc D_800A9A04;

extern s32 D_800A9A0C; // Old IDB name `FS_AllFilesLoaded`, though FS code doesn't set it.

extern s32 g_MapEventSysState; /** `e_InvItemId` */

extern u32 g_MapEventParam;

extern s32 g_MapEventLastUsedItem; /** `e_InvItemId` */

/** Radio pitch state based on the distance from the player to an enemy. Range: `[0, 3]`. */
extern s32 g_RadioPitchState;

#endif
