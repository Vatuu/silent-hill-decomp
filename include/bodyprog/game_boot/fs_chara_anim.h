#ifndef _BODYPROG_GAMEBOOT_FS_CHARA_ANIM_H
#define _BODYPROG_GAMEBOOT_FS_CHARA_ANIM_H

/** @brief Checks if the pointers of `g_CharaTypeAnimInfo` overlap each other.
 * Returns `false` if the compared pointers don't overlap.
 */
bool Fs_CharaAnimDataSizeCheck(s32 idx0, s32 idx1);

/** @brief Finds for the index of the character animation data in `g_CharaTypeAnimInfo`.
 *
 * @param charaId ID of the character for which to find the animation data.
 * @return Animation data index.
 */
s32 Fs_CharaAnimDataInfoIdxGet(e_CharacterId charaId);

/** Allocates and adjust where is animation data allocated. */
void Fs_CharaAnimDataAlloc(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coords);

/** Called by `Fs_QueuePostLoadAnm`. Assigns information about animation data to `g_CharaTypeAnimInfo`
 * and initializes NPC bones.
 */
void Fs_CharaAnimInfoUpdate(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord);

/** @brief Updates character type bone initialization coordinates and reinitializes them. */
void Fs_CharaAnimBoneInfoUpdate(void);

#endif
