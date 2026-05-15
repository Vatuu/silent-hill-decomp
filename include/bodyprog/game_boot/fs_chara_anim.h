#ifndef _BODYPROG_GAMEBOOT_FSCHARAANIM_H
#define _BODYPROG_GAMEBOOT_FSCHARAANIM_H

#include "bodyprog/formats/anm.h"

// or `s_CharaAnimMetadata`?
typedef struct _CharaAnimMetadata
{
    /* 0x0  */ s8             charaId0_0;  /** `e_CharaId` */
    /* 0x1  */ s8             charaId1_1;  /** `e_CharaId` */
               // 2 bytes of padding.
    /* 0x4  */ s32            animFile0_4; // s_AnmHeader* animFile0_4; // TODO: Needs to be a pointer.
    /* 0x8  */ s_AnmHeader*   animFile1_8;
    /* 0xC  */ s32            animBufferSize1_C;
    /* 0x10 */ s32            animBufferSize2_10;
    /* 0x14 */ GsCOORDINATE2* boneCoords;
} s_CharaAnimMetadata;
STATIC_ASSERT_SIZEOF(s_CharaAnimMetadata, 24);

/** @brief Stores a loaded character's animation metadata. */
extern s_CharaAnimMetadata g_CharaTypeAnimMetadata[];

/** @brief Checks if the pointers of `g_CharaTypeAnimMetadata` overlap each other.
 *
 * @return `true` if the pointers overlap, `false` otherwise.
 */
bool Fs_CharaAnimDataSizeCheck(s32 animMetadataIdx0, s32 animMetadataIdx1);

/** @brief Finds for the index of the character animation data in `g_CharaTypeAnimMetadata`.
 *
 * @param charaId ID of the character for which to find the animation data.
 * @return Animation data index.
 */
s32 Fs_CharaAnimMetadataIdxGet(e_CharaId charaId);

/** Allocates and adjusts where animation data is allocated. */
void Fs_CharaAnimDataAlloc(s32 animMetadataIdx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords);

/** Called by `Fs_QueuePostLoadAnm`. Assigns information about animation data to `g_CharaTypeAnimMetadata`
 * and initializes NPC bones.
 */
void Fs_CharaAnimDataUpdate(s32 idx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords);

/** @brief Updates character type bone initialization coordinates and reinitializes them. */
void Fs_CharaAnimBoneInfoUpdate(void);

#endif
