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
