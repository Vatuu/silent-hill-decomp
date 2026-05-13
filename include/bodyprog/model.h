#ifndef _BODYRPOG_MODEL_H
#define _BODYRPOG_MODEL_H

#include "bodyprog/anim.h"

/** @brief Character model animation. */
typedef struct _ModelAnim
{
    /* 0x0  */ u8          status;             /** Is active: bit 0, Anim index: bits 1-7. */
    /* 0x1  */ u8          mapAnimStatusStart; /** Start anim status of map-specific anim infos. Only used for Harry. */
    /* 0x2  */ u16         flags;              /** `e_AnimFlags` */
    /* 0x4  */ q19_12      time;               /** Time on timeline. */
    /* 0x8  */ s16         keyframeIdx;        /** Active keyframe index. */
    /* 0xA  */ q3_12       alpha;              /** Keyframe progress alpha. */
    /* 0xC  */ s_AnimInfo* baseAnimInfos;      /** Anim infos. For Harry, used for base anims. */
    /* 0x10 */ s_AnimInfo* mapAnimInfos;       /** Map-specific anim infos. Only used for Harry. */
} s_ModelAnim;
STATIC_ASSERT_SIZEOF(s_ModelAnim, 20);

/** @brief Character model. */
typedef struct _Model
{
    /* 0x0 */ s8          charaId;      /** `e_CharaId` */
    /* 0x1 */ u8          paletteIdx;   /** Changes the texture palette index for this model. */
    /* 0x2 */ u8          controlState; /** Active character control state. */
    /* 0x3 */ u8          stateStep;    /** Step for the current `controlState`. */ 
                                        // In `s_PlayerExtra` always 1, set to 0 for 1 tick when anim state appears to change.
                                        // Used differently in player's `s_SubCharacter`. 0: anim transitioning(?), bit 1: animated, bit 2: turning.
                                        // Sometimes holds actual anim index?
    /* 0x4 */ s_ModelAnim anim;
} s_Model;
STATIC_ASSERT_SIZEOF(s_Model, 24);

// TODO: Name might be wrong, but these have something to do with held item meshes.
// First index is the mesh variant, second is the container of meshes (not bone index in skeleton)?
// Data addresses are hardcoded.
/** @brief Packs a model bone containing a mesh variant index and ??? in a single value.
 *
 * @param variantIdx Mesh variant index.
 * @param idx1 ???
 * @return Packed model bone containing a mesh variant index and ???
 */
#define MODEL_BONE(variantIdx, idx1) \
    (s16)((variantIdx) | ((idx1) << 4))

/** @brief Retrieves the bone mesh variant index from a packed model bone.
 *
 * @param modelBone Packed model bone containing  a mesh variant index and ???
 * @return Bone mesh variant index.
 */
#define MODEL_BONE_MESH_VARIANT_IDX_GET(modelBone) \
    ((modelBone) & 0xF)

/** @brief Retrieves ???
 *
 * @param modelBone Packed model bone containing a mesh variant index and ???
 * @return Unknown second index.
 */
#define MODEL_BONE_IDX_1_GET(modelBone) \
    ((modelBone) & 0xF0)

/** @brief Sets given animation flags for a model.
 *
 * @param model Model to update (`s_Model`).
 * @param flag Flags to set.
 */
#define Model_AnimFlagsSet(model, setFlags) \
    (model)->anim.flags |= (setFlags)

/** @brief Clears given animation flags for a model.
 *
 * @param model Model to update (`s_Model`).
 * @param clearFlags Flags to clear.
 */
#define Model_AnimFlagsClear(model, clearFlags) \
    (model)->anim.flags &= ~(clearFlags)

/** @brief Similar to `Model_AnimStatusSet`, but also sets `anim.time` and `anim.keyframeIdx`
 * from the `animInfos` `s_AnimInfo` array.
 *
 * @param model Model to update.
 * @param animIdx Anim index to set.
 * @param isActive Active status to set.
 * @param animInfos Reference anim infos.
 * @param animInfosOffset Anim infos offset.
 */
#define Model_AnimStatusKeyframeSet(model, animIdx, isActive, animInfos, animInfosOffset)                                 \
    if ((model).stateStep == 0)                                                                                           \
    {                                                                                                                     \
        (model).anim.status = ANIM_STATUS(animIdx, isActive);                                                             \
        (model).stateStep++;                                                                                              \
        (model).anim.time        = Q12((animInfos)[ANIM_STATUS(animIdx, isActive) + (animInfosOffset)].startKeyframeIdx); \
        (model).anim.keyframeIdx = (animInfos)[ANIM_STATUS(animIdx, (isActive) + (animInfosOffset))].startKeyframeIdx;    \
    }

/** @brief Updates a model anim if `model->stateStep` is 0.
 *
 * @param model Model to update.
 * @param animIdx Anim index to set.
 * @param isActive Active status to set.
 */
static inline void Model_AnimStatusSet(s_Model* model, s32 animIdx, bool isActive)
{
    if (model->stateStep == 0)
    {
        model->anim.status = ANIM_STATUS(animIdx, isActive);
        model->stateStep++;
    }
}

/** @brief Increments the anim status of a model anim.
 *
 * @param anim Anim to update.
 */
static inline void ModelAnim_StatusIncrement(s_ModelAnim* anim)
{
    anim->status++;
}

/** @brief Decrements the anim status of a model anim.
 *
 * @param anim Anim to update.
 */
static inline void ModelAnim_StatusDecrement(s_ModelAnim* anim)
{
    anim->status--;
}

#endif
