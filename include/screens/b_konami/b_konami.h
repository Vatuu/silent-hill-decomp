#ifndef _SCREENS_B_KONAMI_H
#define _SCREENS_B_KONAMI_H

#include "common.h"

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} s_800CA4F0;

extern s_800CA4F0 D_800CA4F0;

/** Displays the Konami logo and starts loading base hero animations. */
void GameState_KonamiLogo_Update(void);

s32 func_800C9874(void);

/** Displays the KCET logo and starts loading various things. */
void GameState_KcetLogo_Update(void);

/** Draws segments of Konami and KCET logos. */
void Gfx_BootScreenImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y);

void Gfx_KonamiScreenDraw(void);

void Gfx_KcetScreenDraw(void);

// Resumable LZSS decompression routines.
// Used in JP release for decompressing SAFEx.BIN overlays, unused in other releases.

/* @brief Resets LZSS decompressor state. */
void Lzss_Reset(void);

/* @brief Fetches the decompressed size from an LZSS-compressed buffer.
 *
 * @param inData Compressed buffer pointer.
 * @return Size of decompressed data.
 */
s32 Lzss_DecompressedSizeGet(u8* inData);

/* @brief Initializes the decompressor.
 *
 * @param inData Compressed buffer pointer.
 * @param outData Output decompressed buffer pointer.
 * @param inDataLen Maximum length of compressed data to parse.
 */
void Lzss_Init(u8* inData, u8* outData, s32 inDataLen);

/* @brief Returns whether LZSS decompressor is still active / has data to parse.
 *
 * @return Active state of decompressor.
 */
bool Lzss_IsActive(void);

/* @brief Begins decoding LZSS compressed data. Optionally pauses decoding after a certain time limit.
 * Can be resumed by calling `Lzss_Decode` later on.
 *
 * @param timeLimit Maximum time to spend decompressing, in 60Hz frames. `NO_VALUE` for no time limit.
 */
void Lzss_Decode(s32 timeLimit);

#endif
