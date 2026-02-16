#ifndef _BODYPROG_SOUNDBACKGROUND_H
#define _BODYPROG_SOUNDBACKGROUND_H


// ========
// STRUCTS
// ========

typedef struct
{
    u8 field_0[8];
} s_Bgm_Update;

// ==========
// FUNCTIONS
// ==========

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

void Bgm_TrackUpdate(bool);

void Bgm_AllLayersMute(void);

/** @unused. */
bool Bgm_LayerOnCheck(void);

void Bgm_GlobalLayerVariablesUpdate(void);

// Main music trigger and handler.
void Bgm_Update(s32 flags, q19_12 arg1, s_Bgm_Update* bgmLayerLimitPtr);

/** @brief Updates the track index and disables radio effects. */
void func_800363D0(void);

void Bgm_TrackChange(s32 idx);

#endif
