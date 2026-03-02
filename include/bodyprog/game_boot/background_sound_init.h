#ifndef _BODYPROG_GAMEBOOT_BACKGROUND_SOUND_INIT_H
#define _BODYPROG_GAMEBOOT_BACKGROUND_SOUND_INIT_H

s32 Bgm_Init(void);

/** @brief Checks if currently assigned song is the same as target. */
bool Bgm_IsCurrentBgmTargetCheck(s32 bgmIdx);

void Bgm_TrackSet(s32 bgmIdx);

/** Executes sound command. */
void Bgm_BgmChannelSet(void);

void func_8003596C(void);

s32 Sd_AmbientSfxInit(void);

bool Sd_IsCurrentAmbientTargetCheck(s32 ambIdx);

void Sd_AmbientSfxSet(s32 idx);

#endif
