#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"
#include "types.h"

s8* D_800C15B0;

// ========================================
// ANIMATION
// ========================================

void Anim_BoneInit(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800445A4
{
    s32            boneIdx;
    s32            i;
    s32            j;
    s_AnmBindPose* curBindPose;
    GsCOORDINATE2* curCoord;

    GsInitCoordinate2(NULL, boneCoords);

    for (boneIdx = 1, curBindPose = &anmHdr->bindPoses_14[1], curCoord = &boneCoords[1];
         boneIdx < anmHdr->boneCount_6;
         boneIdx++, curBindPose++, curCoord++)
    {
        curCoord->super = &boneCoords[anmHdr->bindPoses_14[boneIdx].parentBone];

        // If no translation for this bone, copy over `translationInitial_3`.
        if (curBindPose->translationDataIdx_2 < 0)
        {
            for (i = 0; i < 3; i++)
            {
                curCoord->coord.t[i] = anmHdr->bindPoses_14[boneIdx].translationInitial_3[i] << anmHdr->scaleLog2_12;
            }
        }

        // If no rotation for this bone, create identity matrix.
        if (curBindPose->rotationDataIdx_1 < 0)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    curCoord->coord.m[i][j] = ((j == i) ? Q12_ANGLE(360.0f) : Q12_ANGLE(0.0f));
                }
            }
        }
    }
}

void Anim_BoneUpdate(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, q19_12 alpha) // 0x800446D8
{
    s32            boneCount;
    bool           isPlayer;
    u32            activeBoneIdxs;
    s32            boneIdx;
    s32            scaleLog2;
    s32            boneTranslationDataIdx;
    s32            boneRotationDataIdx;
    s32            j;
    s32            i;
    s8*            frame0TranslationData;
    s8*            frame1TranslationData;
    s8*            frame0RotationData;
    s8*            frame1RotationData;
    void*          frame0Data;
    void*          frame0RotData;
    void*          frame1Data;
    void*          frame1RotData;
    GsCOORDINATE2* curBoneCoord;
    s_AnmBindPose* curBindPose;

    boneCount     = anmHdr->boneCount_6;
    frame0Data    = ((u8*)anmHdr + anmHdr->dataOffset_0) + (anmHdr->keyframeDataSize_4 * keyframe0);
    frame0RotData = frame0Data + (anmHdr->translationBoneCount_3 * 3);
    frame1Data    = ((u8*)anmHdr + anmHdr->dataOffset_0) + (anmHdr->keyframeDataSize_4 * keyframe1);
    frame1RotData = frame1Data + (anmHdr->translationBoneCount_3 * 3);

    // For player, use inverted mask of `extra_128.disabledAnimBones_18` to facilitate masking of upper and lower body.
    isPlayer = boneCoords == &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    if (isPlayer)
    {
        activeBoneIdxs = ~g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18;
    }
    else
    {
        activeBoneIdxs = anmHdr->activeBones_8;
    }

    // Skip root bone (index 0) and start processing from bone 1.
    boneCoords  = &boneCoords[1];
    curBindPose = &anmHdr->bindPoses_14[1];

    for (boneIdx = 1, curBoneCoord = boneCoords;
         boneIdx < boneCount;
         boneIdx++, curBindPose++, curBoneCoord++)
    {
        // Process bones marked as active.
        if (activeBoneIdxs & (1 << boneIdx))
        {
            curBoneCoord->flg = false;
            scaleLog2      = anmHdr->scaleLog2_12;

            boneTranslationDataIdx = curBindPose->translationDataIdx_2;
            if (boneTranslationDataIdx >= 0)
            {
                // 3-byte vector translation.
                frame0TranslationData = frame0Data + (boneTranslationDataIdx * 3);
                frame1TranslationData = frame1Data + (boneTranslationDataIdx * 3);

                // Interpolate XYZ translation components.
                for (i = 0; i < 3; i++)
                {
                    // Linear interpolation with scaling: `frame0 + (frame1 - frame0) * alpha`.
                    curBoneCoord->coord.t[i] = (*frame0TranslationData << scaleLog2) +
                                            (((*frame1TranslationData - *frame0TranslationData) * alpha) >> (Q12_SHIFT - scaleLog2));

                    frame0TranslationData++;
                    frame1TranslationData++;
                }

                if (boneTranslationDataIdx == 0)
                {
                    curBoneCoord->coord.t[1] -= anmHdr->rootYOffset_13; // TODO: Not sure of purpose of this yet.
                }
            }

            boneRotationDataIdx = curBindPose->rotationDataIdx_1;
            if (boneRotationDataIdx >= 0)
            {
                // 9-byte rotation matrix.
                frame0RotationData = frame0RotData + (boneRotationDataIdx * 9);
                frame1RotationData = frame1RotData + (boneRotationDataIdx * 9);

                // Interpolate rotation matrix.
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        curBoneCoord->coord.m[i][j] = (*frame0RotationData << 5) +
                                                   (((*frame1RotationData - *frame0RotationData) * alpha) >> 7);

                        frame0RotationData++;
                        frame1RotationData++;
                    }
                }
            }
        }
    }

    // Copy player hips translation to torso.
    if (isPlayer)
    {
        for (i = 0; i < 3; i++)
        {
            g_SysWork.playerBoneCoords_890[HarryBone_Torso].coord.t[i] = g_SysWork.playerBoneCoords_890[HarryBone_Hips].coord.t[i];
        }
    }
}

s_AnimInfo* func_80044918(s_ModelAnim* anim) // 0x80044918
{
    // `field_C`/`field_10` usually points to data at `0x800AF228` which contains funcptrs and other stuff.

    s_AnimInfo* animInfo_C;
    s_AnimInfo* animInfo_10;
    u8          animStatus0;
    s32         animStatus1;

    animInfo_C  = anim->animInfo_C;
    animInfo_10 = anim->animInfo_10;
    animStatus0 = anim->status_0;
    animStatus1 = anim->maybeSomeState_1;

    if (animInfo_10 != NULL && animStatus0 >= animStatus1)
    {
        animInfo_C  = animInfo_10;
        animInfo_C -= animStatus1;
    }

    return &animInfo_C[animStatus0];
}

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x80044950
{
    s_AnimInfo* animInfo;

    animInfo = func_80044918(&chara->model_0.anim_4);
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

q19_12 Anim_DurationGet(s_Model* unused, s_AnimInfo* animInfo) // 0x800449AC
{
    if (!animInfo->hasVariableDuration_5)
    {
        return animInfo->duration_8.constant;
    }

    return animInfo->duration_8.variableFunc();
}

/** @brief Computes the timestep of the target animation for the current tick.
 *
 * @param model Character model.
 * @param animInfo Animation info.
 * @return Animation timestep for the current tick.
 */
static inline q19_12 Anim_TimestepGet(s_Model* model, s_AnimInfo* animInfo)
{
    q19_12 duration;

    // Check if animation is unlocked.
    if (model->anim_4.flags_2 & AnimFlag_Unlocked)
    {
        duration = Anim_DurationGet(model, animInfo);
        return Q12_MULT_PRECISE(duration, g_DeltaTime);
    }

    return Q12(0.0f);
}

void Anim_Update0(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coords, s_AnimInfo* animInfo) // 0x800449F0
{
    bool setNewAnimStatus;
    s32  timestep;
    s32  newTime;
    s32  newKeyframeIdx;
    s32  startTime;
    s32  endTime;
    s32  alpha;

    setNewAnimStatus = false;

    // Get timestep.
    timestep = Anim_TimestepGet(model, animInfo);

    // Compute new time and keyframe index.
    newTime        = model->anim_4.time_4;
    newKeyframeIdx = FP_FROM(newTime, Q12_SHIFT);
    if (timestep != Q12(0.0f))
    {
        newTime += timestep;

        // Clamp new time to valid keyframe range.
        endTime = Q12(animInfo->endKeyframeIdx_E);
        if (newTime >= endTime)
        {
            newTime          = endTime;
            setNewAnimStatus = true;
        }
        else
        {
            startTime = Q12(animInfo->startKeyframeIdx_C);
            if (newTime <= startTime)
            {
                newTime          = startTime;
                setNewAnimStatus = true;
            }
        }

        newKeyframeIdx = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton.
    alpha = Q12_FRACT(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coords, newKeyframeIdx, newKeyframeIdx + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx;
    model->anim_4.alpha_A       = Q12(0.0f);

    // Update anim status if anim started or ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update1(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044B38
{
    s32 startKeyframeIdx;
    s32 endKeyframeIdx;
    s32 nextStartKeyframeIdx;
    s32 keyframeCount;
    s32 startTime;
    s32 nextStartTime;
    s32 duration;
    s32 timestep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 alpha;

    startKeyframeIdx     = animInfo->startKeyframeIdx_C;
    endKeyframeIdx       = animInfo->endKeyframeIdx_E;
    nextStartKeyframeIdx = endKeyframeIdx + 1;
    keyframeCount        = nextStartKeyframeIdx - startKeyframeIdx;

    startTime     = Q12(startKeyframeIdx);
    nextStartTime = Q12(nextStartKeyframeIdx);
    duration      = Q12(keyframeCount);

    // Get timestep.
    timestep = Anim_TimestepGet(model, animInfo);

    // Wrap new time to valid keyframe range.
    newTime = model->anim_4.time_4 + timestep;
    while (newTime < startTime)
    {
        newTime += duration;
    }
    while (newTime >= nextStartTime)
    {
        newTime -= duration;
    }

    // Compute new keyframe 1. Wrap to start to facilitate loop.
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    newKeyframeIdx1 = newKeyframeIdx0 + 1;
    if (newKeyframeIdx1 == nextStartKeyframeIdx)
    {
        newKeyframeIdx1 = startKeyframeIdx;
    }

    // Update skeleton.
    alpha = Q12_FRACT(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx0;
    model->anim_4.alpha_A       = Q12(0.0f);
}

void Anim_Update2(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044CA4
{
    bool setNewAnimStatus;
    s32  startKeyframeIdx;
    s32  endKeyframeIdx;
    s32  timestep;
    s32  alpha;

    setNewAnimStatus = false;
    startKeyframeIdx = animInfo->startKeyframeIdx_C;
    endKeyframeIdx   = animInfo->endKeyframeIdx_E;

    // If no start keyframe exists, default to active keyframe.
    if (startKeyframeIdx == NO_VALUE)
    {
        startKeyframeIdx = model->anim_4.keyframeIdx_8;
    }

    // Get timestep.
    timestep = Anim_TimestepGet(model, animInfo);

    // Update time to start or end keyframe, whichever is closest.
    alpha  = model->anim_4.alpha_A;
    alpha += timestep;
    if (alpha >= Q12(0.5f))
    {
        model->anim_4.time_4 = Q12(endKeyframeIdx);
    }
    else
    {
        model->anim_4.time_4 = Q12(startKeyframeIdx);
    }

    // Update frame data.
    if (alpha >= Q12(1.0f))
    {
        startKeyframeIdx            = endKeyframeIdx;
        model->anim_4.keyframeIdx_8 = endKeyframeIdx;

        alpha            = Q12(0.0f);
        setNewAnimStatus = true;
    }

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, startKeyframeIdx, endKeyframeIdx, alpha);
    }

    // Update alpha.
    model->anim_4.alpha_A = alpha;

    // Update anim status if anim ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update3(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044DF0
{
    s32    startKeyframeIdx;
    s32    endKeyframeIdx;
    s32    timeDelta;
    s32    timestep;
    s32    alpha;
    q19_12 sinVal;
    s32    newTime;
    s32    newAlpha;

    startKeyframeIdx = animInfo->startKeyframeIdx_C;
    endKeyframeIdx   = animInfo->endKeyframeIdx_E;

    // Compute timestep. TODO: Can't call `Anim_TimestepGet` inline due to register constraints.
    if (model->anim_4.flags_2 & AnimFlag_Unlocked)
    {
        timeDelta = Anim_DurationGet(model, animInfo);
        timestep  = Q12_MULT_PRECISE(timeDelta, g_DeltaTime);
    }
    else
    {
        timestep = Q12(0.0f);
    }

    // Update alpha.
    newAlpha              = model->anim_4.alpha_A;
    alpha                 = newAlpha + timestep;
    model->anim_4.alpha_A = alpha;

    // Compute ease-out alpha.
    sinVal   = Math_Sin((alpha / 2) - Q12(0.25f));
    newAlpha = (sinVal / 2) + Q12(0.5f);

    // Update time to start or end keyframe, whichever is closest.
    if (newAlpha >= Q12(0.5f))
    {
        newTime = Q12(startKeyframeIdx);
    }
    else
    {
        newTime = Q12(endKeyframeIdx);
    }

    alpha = newAlpha;

    // Update time.
    model->anim_4.time_4 = newTime;

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, startKeyframeIdx, endKeyframeIdx, alpha);
    }

    // Update active keyframe.
    model->anim_4.keyframeIdx_8 = FP_FROM(newTime, Q12_SHIFT);
}

// ========================================
// BONES AND SKELETONS
// ========================================

void func_80044F14(GsCOORDINATE2* coord, q3_12 rotZ, q3_12 rotX, q19_12 rotY) // 0x80044F14
{
    *(q3_12*)0x1F800004 = rotZ;
    *(q3_12*)0x1F800002 = rotY;
    *(q3_12*)0x1F800000 = rotX;

    // TODO: Make FS buffer constant for this.

    Math_RotMatrixZxyNegGte((SVECTOR*)0x1F800000, (MATRIX*)0x1F800008);
    MulMatrix(&coord->coord, (MATRIX*)0x1F800008);
}

s8 Bone_ModelIdxGet(s8* ptr, bool reset) // 0x80044F6C
{
    // These two are probably part of a bigger struct.
    // `boneMeshIdx` is not referenced directly anywhere else.
    // It must be reset somewhere at some point.
    #define boneIdxs    D_800C15B0
    #define boneMeshIdx D_800C15B4

    if (reset)
    {
        boneIdxs = ptr;
    }

    // LM has <= 1 model.
    if (boneIdxs[0] != -3)
    {
        // -2 for 0 models, 0 for 1 model.
        boneMeshIdx = boneIdxs[0];
        boneIdxs++;
    }
    // Increment `boneMeshIdx` and break loop when equal to number of models.
    else if (++boneMeshIdx >= (boneIdxs[1] - 1))
    {
        boneIdxs++;
    }

    return boneMeshIdx;
}

void Skeleton_Init(s_Skeleton* skel, s_LinkedBone* bones, u8 boneCount) // 0x80044FE0
{
    skel->bones_8 = bones;
    skel->boneCount_0 = boneCount;
    skel->boneIdx_1 = 0;
    skel->field_2 = 1;
    skel->bones_4 = NULL;

    func_80045014(skel);
}

void func_80045014(s_Skeleton* skel) // 0x80045014
{
    s_LinkedBone* curBone;

    // Traverse bone hierarchy and clear flags.
    for (curBone = &skel->bones_8[0]; curBone < &skel->bones_8[skel->boneCount_0]; curBone++)
    {
        curBone->bone_0.modelInfo_0.field_0 = 0;
    }
}

void func_8004506C(s_Skeleton* skel, s_LmHeader* lmHdr) // 0x8004506C
{
    u8  sp10[4]; // Size unsure, this could be larger.
    s32 modelCount;

    modelCount = LmHeader_ModelCountGet(lmHdr);
    sp10[0]    = 0;

    switch (modelCount)
    {
        case 0:
            sp10[0] = BoneHierarchy_End;
            break;

        case 1:
            sp10[0] = 0;
            sp10[1] = BoneHierarchy_End;
            break;

        default:
            sp10[1] = BoneHierarchy_MultiModel;
            sp10[2] = LmHeader_ModelCountGet(lmHdr) - 1;
            sp10[3] = BoneHierarchy_End;
            break;
    }

    func_80045108(skel, lmHdr, (s8*)sp10, 0);
}

// Anim func.
void func_80045108(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2, s32 arg3) // 0x80045108
{
    s_LinkedBone*  curBone;
    s_LinkedBone** curBoneOrd;
    s32      boneIdx;

    if (arg3 == 0)
    {
        skel->boneIdx_1 = 0;
        skel->bones_4   = NULL;
    }

    boneIdx = skel->boneIdx_1;
    Skeleton_BoneModelAssign(skel, lmHdr, arg2);

    curBoneOrd = &skel->bones_4;
    while (*curBoneOrd != NULL)
    {
        curBone    = *curBoneOrd;
        curBoneOrd = &curBone->next_14;
    }

    // `Skeleton_BoneModelAssign` increments `boneIdx_1`.
    func_80045258(curBoneOrd, &skel->bones_8[boneIdx], skel->boneIdx_1 - boneIdx, lmHdr);
    func_800453E8(skel, false);
}

void Skeleton_BoneModelAssign(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2) // 0x800451B0
{
    s32 modelIdx;

    modelIdx = Bone_ModelIdxGet(arg2, true);
    while (modelIdx != BoneHierarchy_End)
    {
        Bone_ModelAssign(&skel->bones_8[skel->boneIdx_1].bone_0, lmHdr, modelIdx);

        skel->boneIdx_1++;
        modelIdx = Bone_ModelIdxGet(arg2, false);
    }
}

void func_80045258(s_LinkedBone** boneOrd, s_LinkedBone* bones, s32 boneIdx, s_LmHeader* lmHdr) // 0x80045258
{
    s_LinkedBone* curBone;
    u8*     curObjOrd;

    for (curObjOrd = lmHdr->modelOrder_10; curObjOrd < &lmHdr->modelOrder_10[lmHdr->modelCount_8]; curObjOrd++)
    {
        for (curBone = bones; curBone < &bones[boneIdx]; curBone++)
        {
            if (curBone->bone_0.modelInfo_0.modelIdx_C == *curObjOrd)
            {
                *boneOrd = curBone;
                boneOrd  = &curBone->next_14;
            }
        }
    }

    *boneOrd = NULL;
}

// Anim func.
void func_800452EC(s_Skeleton* skel) // 0x800452EC
{
    s32            temp_a0;
    s32            var_v0;
    u32            temp_v1;
    s_LinkedBone* curBone;
    s_ModelHeader* modelHdr;

    curBone = skel->bones_4;
    while (curBone)
    {
        modelHdr = curBone->bone_0.modelInfo_0.modelHdr_8;
        temp_v1 = modelHdr->name_0.str[1] - '0';
        temp_a0 = modelHdr->name_0.str[0] - '0';

        if (temp_v1 < 10 && temp_a0 >= 0 && temp_a0 < 10)
        {
            var_v0 = (temp_a0 * 10) + temp_v1;
        }
        else
        {
            var_v0 = 0;
        }

        curBone->bone_0.field_10 = var_v0;

        curBone = curBone->next_14;
    }
}

void func_80045360(s_Skeleton* skel, s8* arg1) // 0x80045360
{
    s32 i;
    s32 status;

    for (status = Bone_ModelIdxGet(arg1, true), i = 0; status != -2; i++)
    {
        skel->bones_8[i].bone_0.field_10 = status;
        status = Bone_ModelIdxGet(arg1, false);
    }
}

void func_800453E8(s_Skeleton* skel, bool cond) // 0x800453E8
{
    s_LinkedBone* curBone;

    // Traverse bone hierarchy and set flags according to cond.
    for (curBone = &skel->bones_8[0]; curBone < &skel->bones_8[skel->boneCount_0]; curBone++)
    {
        if (cond)
        {
            curBone->bone_0.modelInfo_0.field_0 &= ~(1 << 31);
        }
        else
        {
            curBone->bone_0.modelInfo_0.field_0 |= 1 << 31;
        }
    }
}

void func_80045468(s_Skeleton* skel, s32* arg1, bool cond) // 0x80045468
{
    s_LinkedBone* bones;
    s32           modelIdx;

    bones = skel->bones_8;

    // Traverse bone hierarchy and set flag 31 according to some condition.
    modelIdx = Bone_ModelIdxGet(arg1, true);
    while (modelIdx != -2)
    {
        if (cond)
        {
            bones[modelIdx].bone_0.modelInfo_0.field_0 &= ~(1 << 31);
        }
        else
        {
            bones[modelIdx].bone_0.modelInfo_0.field_0 |= 1 << 31;
        }

        modelIdx = Bone_ModelIdxGet(arg1, false);
    }
}

extern s_WorldEnvWork const g_WorldEnvWork;

void func_80045534(s_Skeleton* skel, GsOT* ot, s32 arg2, GsCOORDINATE2* coord, q3_12 arg4, u16 arg5, s_FsImageDesc* images) // 0x80045534
{
    MATRIX         mat0;
    MATRIX         mat1;
    DVECTOR        sp60;
    s32            temp_a1;
    s16            var_fp;
    s16            var_s3;
    s16            var_s4;
    s16            var_s5;
    s16            var_s6;
    s16            var_s7;
    s32            temp_a0;
    s32            temp_s0;
    s32            temp_s1_2;
    s32            temp_s1_3;
    s32            temp_s1_4;
    s32            temp_v1;
    s32            var_s0;
    s32            var_s2;
    s32            var_s3_2;
    s32            var_v0_2;
    s32            var_v0_4;
    s32            var_v0_5;
    s_FsImageDesc* curImage;
    s_LinkedBone*  curBone;

    var_s5 = SHRT_MAX;
    var_s6 = SHRT_MAX;
    var_s4 = SHRT_MAX;
    var_s7 = -SHRT_MAX;
    var_fp = -SHRT_MAX;
    var_s3 = -SHRT_MAX;

    if (skel->field_2 == 0)
    {
        return;
    }

    var_s0 = NO_VALUE;

    if (images != NULL)
    {
        for (curImage = images; curImage->clutY != NO_VALUE; curImage++)
        {
            if (var_s0 != curImage->clutY)
            {
                var_s0 = curImage->clutY;
                func_80049AF8(&coord[var_s0], &mat0);
                SetRotMatrix(&mat0);
                SetTransMatrix(&mat0);
            }

            gte_ldv0(curImage);
            gte_rtps();
            gte_stsxy(&sp60);
            temp_a1 = gte_stSZ3();

            if (sp60.vx < var_s5)
            {
                var_s5 = sp60.vx;
            }

            if (var_s7 < sp60.vx)
            {
                var_s7 = sp60.vx;
            }

            if (sp60.vy < var_s6)
            {
                var_s6 = sp60.vy;
            }

            if (var_fp < sp60.vy)
            {
                var_fp = sp60.vy;
            }

            if (temp_a1 < var_s4)
            {
                var_s4 = temp_a1;
            }

            if (var_s3 < temp_a1)
            {
                var_s3 = temp_a1;
            }
        }
    }

    for (curBone = skel->bones_4; curBone != NULL; curBone = curBone->next_14)
    {
        if (curBone->bone_0.modelInfo_0.field_0 >= 0)
        {
            func_80049B6C(&coord[(u8)curBone->bone_0.field_10], &mat1, &mat0);

            if (curBone->bone_0.modelInfo_0.field_0 & (1 << 0))
            {
                mat0.m[2][2]         = 0;
                *(s32*)&mat0.m[2][0] = 0;
                *(s32*)&mat0.m[1][1] = 0;
                *(s32*)&mat0.m[0][2] = 0;
                *(s32*)&mat0.m[0][0] = 0;
            }

            func_80057090(&curBone->bone_0.modelInfo_0, ot, arg2, &mat0, &mat1, arg5);

            if (g_WorldEnvWork.isFogEnabled_1)
            {
                gte_SetRotMatrix(&mat0);
                gte_SetTransMatrix(&mat0);
                gte_ldvxy0_Zero();
                gte_gte_ldvz0();
                gte_rtps();
                gte_stsxy(&sp60);
                temp_a1 = gte_stSZ3();

                if (sp60.vx < var_s5)
                {
                    var_s5 = sp60.vx;
                }

                if (var_s7 < sp60.vx)
                {
                    var_s7 = sp60.vx;
                }

                if (sp60.vy < var_s6)
                {
                    var_s6 = sp60.vy;
                }

                if (var_fp < sp60.vy)
                {
                    var_fp = sp60.vy;
                }

                if (temp_a1 < var_s4)
                {
                    var_s4 = temp_a1;
                }

                if (var_s3 < temp_a1)
                {
                    var_s3 = temp_a1;
                }
            }
        }
    }

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        temp_s1_2 = g_SysWork.playerBoneCoords_890[1].coord.t[1];
        temp_s1_2 = CLAMP(temp_s1_2, Q8(-2.0f), Q8(0.0f));

        temp_s1_2 += Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vy);
        temp_s1_3  = Math_MulFixed(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx), GsWSMATRIX.m[2][0], Q12_SHIFT);
        temp_s0    = Math_MulFixed(temp_s1_2, GsWSMATRIX.m[2][1], Q12_SHIFT);
        temp_s1_4  = ((temp_s1_3 + temp_s0) + Math_MulFixed(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz), GsWSMATRIX.m[2][2], Q12_SHIFT)) + GsWSMATRIX.t[2];

        var_s3_2 = (var_s4 + var_s3) >> 1;
        temp_v1  = var_s3_2 - ((var_s3 - var_s4) >> 1);

        temp_a0 = temp_v1 - 0x33;

        if (temp_s1_4 >= (temp_v1 - 0x41A))
        {
            if (temp_s1_4 < (temp_v1 - 0x1A))
            {
                var_v0_2  = temp_s1_4 + 0x3E7;
                var_v0_2 -= temp_a0;
                var_v0_2  = Q12(var_v0_2);

                if (var_v0_2 < 0)
                {
                    var_v0_2 += 0x3FF;
                }

                var_s3_2 += Math_MulFixed(temp_a0 - var_s3_2, var_v0_2 >> 10, Q12_SHIFT);
            }
            else if (temp_s1_4 < temp_a0)
            {
                var_s3_2 = temp_a0;
            }
            else if (temp_s1_4 < var_s3_2)
            {
                var_s3_2 = temp_s1_4;
            }
        }

        var_s3_2 = MAX(var_s3_2, 4);

        var_s2 = Q8_TO_Q12(var_s4) - arg4;
        var_s2 = MAX(var_s2, 0);

        var_s0   = ReadGeomScreen();
        var_v0_4 = Q12_TO_Q8(arg4) * var_s0;

        if (var_s4 >= 5)
        {
            var_v0_5 = (var_v0_4 / var_s4) + 2;
        }
        else
        {
            var_v0_5 = (var_v0_4 / 4) + 2;
        }

        func_80056D8C(var_s5 - var_v0_5, var_s6 - var_v0_5, var_s7 + var_v0_5, var_fp + var_v0_5, var_s3_2 * 16, var_s2, ot, arg2);
    }
}
