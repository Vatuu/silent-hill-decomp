#ifndef _BODYPROG_GAMEBOOT_FSCHARAANIM_H
#define _BODYPROG_GAMEBOOT_FSCHARAANIM_H

#include "bodyprog/formats/anm.h"

// or `s_CharaAnimMetadata`?
typedef struct _CharaAnimDataInfo
{
    /* 0x0  */ s8             charaId0_0;  /** `e_CharaId` */
    /* 0x1  */ s8             charaId1_1;  /** `e_CharaId` */
               // 2 bytes of padding.
    /* 0x4  */ s32            animFile0_4; // s_AnmHeader* animFile0_4; // TODO: Needs to be a pointer.
    /* 0x8  */ s_AnmHeader*   animFile1_8;
    /* 0xC  */ s32            animBufferSize1_C;
    /* 0x10 */ s32            animBufferSize2_10;
    /* 0x14 */ GsCOORDINATE2* npcBoneCoords;
} s_CharaAnimDataInfo;
STATIC_ASSERT_SIZEOF(s_CharaAnimDataInfo, 24);

/** @brief Stores a loaded character's animation data information. */
extern s_CharaAnimDataInfo g_CharaTypeAnimInfo[];

/** @brief Checks if the pointers of `g_CharaTypeAnimInfo` overlap each other.
 * Returns `false` if the compared pointers don't overlap.
 */
bool Fs_CharaAnimDataSizeCheck(s32 idx0, s32 idx1);

/** @brief Finds for the index of the character animation data in `g_CharaTypeAnimInfo`.
 *
 * @param charaId ID of the character for which to find the animation data.
 * @return Animation data index.
 */
s32 Fs_CharaAnimDataInfoIdxGet(e_CharaId charaId);

/** Allocates and adjust where is animation data allocated. */
void Fs_CharaAnimDataAlloc(s32 idx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords);

/** Called by `Fs_QueuePostLoadAnm`. Assigns information about animation data to `g_CharaTypeAnimInfo`
 * and initializes NPC bones.
 */
void Fs_CharaAnimInfoUpdate(s32 idx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords);

/** @brief Updates character type bone initialization coordinates and reinitializes them. */
void Fs_CharaAnimBoneInfoUpdate(void);

#endif
