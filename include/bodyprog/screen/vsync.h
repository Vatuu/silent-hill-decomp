#ifndef _BODYPROG_SCREEN_VSYNC_H
#define _BODYPROG_SCREEN_VSYNC_H

/** @brief Sync modes used by `DrawSync` and `VSync`. */
typedef enum _SyncMode
{
    SyncMode_Count     = -1,
    SyncMode_Wait      = 0,
    SyncMode_Immediate = 1,
    SyncMode_Wait2     = 2,
    SyncMode_Wait3     = 3,
    SyncMode_Wait8     = 8
} e_SyncMode;

void Screen_VSyncCallback(void);

#endif
