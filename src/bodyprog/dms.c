#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound/sound_system.h"
#include "main/fsqueue.h"

void Dms_HeaderFixOffsets(s_DmsHeader* dmsHdr) // 0x8008C9A0
{
    s_DmsEntry* curEntry;

    if (dmsHdr->isLoaded)
    {
        return;
    }

    dmsHdr->isLoaded = true;

    // Add memory address of DMS header to offsets in `dmsHdr`.
    dmsHdr->segments   = (u8*)dmsHdr->segments   + (u32)dmsHdr;
    dmsHdr->characters = (u8*)dmsHdr->characters + (u32)dmsHdr;

    Dms_EntryFixOffsets(&dmsHdr->camera, dmsHdr);

    for (curEntry = dmsHdr->characters; curEntry < &dmsHdr->characters[dmsHdr->characterCount]; curEntry++)
    {
        Dms_EntryFixOffsets(curEntry, dmsHdr);
    }
}

void Dms_EntryFixOffsets(s_DmsEntry* entry, const s_DmsHeader* dmsHdr) // 0x8008CA44
{
    entry->keyframes.character = (u32)entry->keyframes.character + (u32)dmsHdr;
    entry->holdRanges          = (u32)entry->holdRanges          + (u32)dmsHdr;
}

s_DmsSegment* Dms_SegmentGet(volatile s32 unused, s32 segmentIdx, s_DmsHeader* dmsHdr) // 0x8008CA60
{
    return &dmsHdr->segments[segmentIdx];
}

void Dms_CharacterTransformGet(VECTOR3* pos, SVECTOR3* rot, const char* charaName, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CA74
{
    s32 charaIdx;

    charaIdx = Dms_CharacterFindIdxByName(charaName, dmsHdr);
    if (charaIdx == NO_VALUE)
    {
        // Character not found in DMS.
        Math_Vector3Zero(pos);
        Math_SVectorZero(rot);

        Text_Debug_PositionSet(SCREEN_POSITION_X(15.75f), SCREEN_POSITION_Y(37.5f));

#if VERSION_EQUAL_OR_OLDER(PROTO_981216)
        // Code seen in 98-12-16 build.
        Text_Debug_Draw(charaName);
        Text_Debug_Draw(" doesn't exist in dms.");
#endif
    }
    else
    {
        Dms_CharacterTransformGetByIdx(pos, rot, charaIdx, time, dmsHdr);
    }
}

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* dmsHdr) // 0x8008CB10
{
    s32 i;

    for (i = 0; i < dmsHdr->characterCount; i++)
    {
        if (!strncmp(name, dmsHdr->characters[i].name, 4))
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Dms_CharacterTransformGetByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, const s_DmsHeader* dmsHdr) // 0x8008CB90
{
    s32                     prevKeyframeIdx;
    s32                     nextKeyframeIdx;
    s32                     alpha;
    s_DmsKeyframeCharacter  curKeyframe;
    s_DmsEntry*             charaEntry;
    s_DmsKeyframeCharacter* charaKeyframes;

    // Get keyframe interpolation. 
    charaEntry = &dmsHdr->characters[charaIdx];
    Dms_KeyframeInterpGet(&prevKeyframeIdx, &nextKeyframeIdx, &alpha, time, charaEntry, dmsHdr);

    // Interpolate frame.
    charaKeyframes = charaEntry->keyframes.character;
    Dms_CharacterKeyframeInterpolate(&curKeyframe,
                                     &charaKeyframes[prevKeyframeIdx], &charaKeyframes[nextKeyframeIdx],
                                     alpha);

    // Set position.
    pos->vx = Q8_TO_Q12(curKeyframe.position.vx + dmsHdr->origin.vx);
    pos->vy = Q8_TO_Q12(curKeyframe.position.vy + dmsHdr->origin.vy);
    pos->vz = Q8_TO_Q12(curKeyframe.position.vz + dmsHdr->origin.vz);

    // Set rotation.
    rot->vx = curKeyframe.rotation.vx;
    rot->vy = curKeyframe.rotation.vy;
    rot->vz = curKeyframe.rotation.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result,
                                      const s_DmsKeyframeCharacter* keyframe0, const s_DmsKeyframeCharacter* keyframe1,
                                      q19_12 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions.
    result->position.vx = keyframe0->position.vx + Q12_MULT_PRECISE(keyframe1->position.vx - keyframe0->position.vx, alpha);
    result->position.vy = keyframe0->position.vy + Q12_MULT_PRECISE(keyframe1->position.vy - keyframe0->position.vy, alpha);
    result->position.vz = keyframe0->position.vz + Q12_MULT_PRECISE(keyframe1->position.vz - keyframe0->position.vz, alpha);

    // High-precision lerp between rotations.
    result->rotation.vx = Dms_AngleLerp(keyframe0->rotation.vx, keyframe1->rotation.vx, alpha);
    result->rotation.vy = Dms_AngleLerp(keyframe0->rotation.vy, keyframe1->rotation.vy, alpha);
    result->rotation.vz = Dms_AngleLerp(keyframe0->rotation.vz, keyframe1->rotation.vz, alpha);
}

q3_12 Dms_FovScaleGet(q3_12 fovAngle) // 0x8008CDBC
{
    return (96 * Math_Cos(fovAngle / 2)) / Math_Sin(fovAngle / 2);
}

s32 Dms_CameraTargetGet(VECTOR3* posTarget, VECTOR3* lookAtTarget, q3_12* unusedAngle, q19_12 time,
                        const s_DmsHeader* dmsHdr) // 0x8008CE1C
{
    s32                 prevKeyframeIdx;
    s32                 nextKeyframeIdx;
    s32                 alpha;
    s_DmsKeyframeCamera curKeyframe;
    s32                 camProjVal;
    const s_DmsEntry*   camEntry;

    camEntry = &dmsHdr->camera;

    Dms_KeyframeInterpGet(&prevKeyframeIdx, &nextKeyframeIdx, &alpha, time, camEntry, dmsHdr);
    camProjVal = Dms_CameraKeyframeInterpolate(&curKeyframe, &camEntry->keyframes.camera[prevKeyframeIdx],
                                               &camEntry->keyframes.camera[nextKeyframeIdx],
                                               alpha);

    posTarget->vx = Q8_TO_Q12(curKeyframe.positionTarget.vx + dmsHdr->origin.vx);
    posTarget->vy = Q8_TO_Q12(curKeyframe.positionTarget.vy + dmsHdr->origin.vy);
    posTarget->vz = Q8_TO_Q12(curKeyframe.positionTarget.vz + dmsHdr->origin.vz);

    lookAtTarget->vx = Q8_TO_Q12(curKeyframe.lookAtTarget.vx + dmsHdr->origin.vx);
    lookAtTarget->vy = Q8_TO_Q12(curKeyframe.lookAtTarget.vy + dmsHdr->origin.vy);
    lookAtTarget->vz = Q8_TO_Q12(curKeyframe.lookAtTarget.vz + dmsHdr->origin.vz);

    // @unused Always passed as `NULL`.
    if (unusedAngle != NULL)
    {
        *unusedAngle = curKeyframe.unusedAngle;
    }

    // `camProjVal` comes from `curFrame.projectionDistance`, return value is passed to `vcChangeProjectionValue`.
    // Might be related to FOV?
    return camProjVal;
}

bool Dms_RotationsCompare(const SVECTOR3* rot0, const SVECTOR3* rot1) // 0x8008CF54
{
    #define ANGLE_EPSILON Q12_ANGLE(360.0f / 16.0f) // 22.5 degrees

    if (ABS(rot0->vx - rot1->vx) > ANGLE_EPSILON ||
        ABS(rot0->vy - rot1->vy) > ANGLE_EPSILON ||
        ABS(rot0->vz - rot1->vz) > ANGLE_EPSILON)
    {
        return true;
    }

    return false;
}

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result,
                                  const s_DmsKeyframeCamera* keyframe0, const s_DmsKeyframeCamera* keyframe1,
                                  q19_12 alpha) // 0x8008CFEC
{
    result->positionTarget.vx = keyframe0->positionTarget.vx + Q12_MULT_PRECISE(keyframe1->positionTarget.vx - keyframe0->positionTarget.vx, alpha);
    result->positionTarget.vy = keyframe0->positionTarget.vy + Q12_MULT_PRECISE(keyframe1->positionTarget.vy - keyframe0->positionTarget.vy, alpha);
    result->positionTarget.vz = keyframe0->positionTarget.vz + Q12_MULT_PRECISE(keyframe1->positionTarget.vz - keyframe0->positionTarget.vz, alpha);

    result->lookAtTarget.vx = keyframe0->lookAtTarget.vx + Q12_MULT_PRECISE(keyframe1->lookAtTarget.vx - keyframe0->lookAtTarget.vx, alpha);
    result->lookAtTarget.vy = keyframe0->lookAtTarget.vy + Q12_MULT_PRECISE(keyframe1->lookAtTarget.vy - keyframe0->lookAtTarget.vy, alpha);
    result->lookAtTarget.vz = keyframe0->lookAtTarget.vz + Q12_MULT_PRECISE(keyframe1->lookAtTarget.vz - keyframe0->lookAtTarget.vz, alpha);

    result->unusedAngle        = Dms_AngleLerp(keyframe0->unusedAngle, keyframe1->unusedAngle, alpha);
    result->projectionDistance = keyframe0->projectionDistance + Q12_MULT_PRECISE(keyframe1->projectionDistance - keyframe0->projectionDistance, alpha);

    return result->projectionDistance;
}

void Dms_KeyframeInterpGet(s32* prevKeyframeIdx, s32* nextKeyframeIdx, q19_12* alpha, q19_12 time,
                           const s_DmsEntry* camEntry, const s_DmsHeader* dmsHdr) // 0x8008D1D0
{
    s32 prevFrameIdx;
    s32 nextFrameIdx;

    prevFrameIdx = 0;
    nextFrameIdx = 0;

    switch (Dms_SegmentStateGet(time, dmsHdr))
    {
        case DmsSegmentState_Interpolating:
            prevFrameIdx = FP_FROM(time, Q12_SHIFT);
            nextFrameIdx = prevFrameIdx + 1;
            *alpha       = Q12_FRACT(time);
            break;

        case DmsSegmentState_SingleFrame:
            prevFrameIdx = FP_FROM(time, Q12_SHIFT);
            nextFrameIdx = prevFrameIdx;
            *alpha       = Q12(0.0f);
            break;

        case DmsSegmentState_Ending:
            prevFrameIdx = FP_FROM(time, Q12_SHIFT) - 1;
            nextFrameIdx = prevFrameIdx + 1;
            *alpha       = Q12_FRACT(time) + Q12(1.0f);
            break;
    }

    *prevKeyframeIdx = Dms_KeyframeIdxGet(prevFrameIdx, camEntry);
    *nextKeyframeIdx = Dms_KeyframeIdxGet(nextFrameIdx, camEntry);
}

u32 Dms_SegmentStateGet(q19_12 time, const s_DmsHeader* dmsHdr)
{
    s32                 frameTime;
    const s_DmsSegment* curSegment;

    frameTime = FP_FROM(time, Q12_SHIFT);

    for (curSegment = dmsHdr->segments;
         curSegment < &dmsHdr->segments[dmsHdr->segmentCount];
         curSegment++)
    {
        if (frameTime != ((curSegment->startFrameIdx + curSegment->frameCount) - 1))
        {
            continue;
        }

        if (curSegment->frameCount > 1)
        {
            return DmsSegmentState_Ending;
        }

        return DmsSegmentState_SingleFrame;
    }

    return DmsSegmentState_Interpolating;
}

s32 Dms_KeyframeIdxGet(s32 frameIdx, const s_DmsEntry* entry) // 0x8008D330
{
    s32                   keyframeIdx0;
    s32                   keyframeIdx1;
    const s_DmsHoldRange* curRange;

    keyframeIdx0 = frameIdx;

    for (curRange = entry->holdRanges; 
         curRange < &entry->holdRanges[entry->holdRangeCount]; 
         curRange++)
    {
        if (frameIdx < curRange->startFrameIdx)
        {
            break;
        }

        if (frameIdx <= curRange->endFrameIdx)
        {
            keyframeIdx0 = curRange->keyframeIdx;
            break;
        }

        keyframeIdx0 -= curRange->endFrameIdx - curRange->startFrameIdx;
    }

    if (keyframeIdx0 >= 0)
    {
        if ((entry->keyframeCount - 1) >= keyframeIdx0)
        {
            keyframeIdx1 = keyframeIdx0;
        }
        else
        {
            keyframeIdx1 = entry->keyframeCount - 1;
        }
    }
    else
    {
        keyframeIdx1 = 0;
    }

    return keyframeIdx1;
}

s32 Dms_AngleLerp(q3_12 angleFrom, q3_12 angleTo, q19_12 alpha) // 0x8008D3D4
{
    return Q12_ANGLE_NORM_S((s32)(Q12_MULT_PRECISE(Q12_ANGLE_NORM_S(angleTo - angleFrom), alpha)) + angleFrom);
}
