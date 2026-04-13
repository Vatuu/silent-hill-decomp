#ifndef _BODYPROG_GAMEBOOT_BACKGROUNDSOUNDINIT_H
#define _BODYPROG_GAMEBOOT_BACKGROUNDSOUNDINIT_H

s32 Bgm_Init(void);

/** @brief Checks if a given background music track is not currently playing.
 *
 * @param bgmIdx Index of the background music track to check.
 * @return `true` if the given track is not currently playing, `false` otherwise.
 */
bool Bgm_ActiveBgmTrackCheck(s32 bgmIdx);

void Bgm_TrackSet(s32 bgmIdx);

/** Executes sound command. */
void Bgm_ChannelSet(void);

void func_8003596C(void);

bool Sd_AmbientSfxInit(void);

bool Sd_IsCurrentAmbientTargetCheck(s32 ambientIdx);

void Sd_AmbientSfxSet(s32 idx);

#endif
