#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
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
    dmsHdr->intervals  = (u8*)dmsHdr->intervals  + (u32)dmsHdr;
    dmsHdr->characters = (u8*)dmsHdr->characters + (u32)dmsHdr;

    Dms_EntryFixOffsets(&dmsHdr->camera, dmsHdr);

    for (curEntry = dmsHdr->characters; curEntry < &dmsHdr->characters[dmsHdr->characterCount]; curEntry++)
    {
        Dms_EntryFixOffsets(curEntry, dmsHdr);
    }
}

void Dms_EntryFixOffsets(s_DmsEntry* entry, s_DmsHeader* dmsHdr) // 0x8008CA44
{
    entry->keyframes.character = (u32)entry->keyframes.character + (u32)dmsHdr;
    entry->svectors            = (u32)entry->svectors + (u32)dmsHdr;
}

s_DmsInterval* Dms_IntervalGet(volatile s32 unused, s32 intervalIdx, s_DmsHeader* dmsHdr) // 0x8008CA60
{
    return &dmsHdr->intervals[intervalIdx];
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

void Dms_CharacterTransformGetByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CB90
{
    s32                     prevKeyframeIdx;
    s32                     nextKeyframeIdx;
    s32                     alpha;
    s_DmsKeyframeCharacter  curFrame;
    s_DmsEntry*             charaEntry;
    s_DmsKeyframeCharacter* charaKeyframes;

    // Get keyframe interpolation. 
    charaEntry = &dmsHdr->characters[charaIdx];
    Dms_CameraKeyframeInterpGet(&prevKeyframeIdx, &nextKeyframeIdx, &alpha, time, charaEntry, dmsHdr);

    // Interpolate frame.
    charaKeyframes = charaEntry->keyframes.character;
    Dms_CharacterKeyframeInterpolate(&curFrame,
                                     &charaKeyframes[prevKeyframeIdx], &charaKeyframes[nextKeyframeIdx],
                                     alpha);

    // Set position.
    pos->vx = Q8_TO_Q12(curFrame.position.vx + dmsHdr->origin.vx);
    pos->vy = Q8_TO_Q12(curFrame.position.vy + dmsHdr->origin.vy);
    pos->vz = Q8_TO_Q12(curFrame.position.vz + dmsHdr->origin.vz);

    // Set rotation.
    rot->vx = curFrame.rotation.vx;
    rot->vy = curFrame.rotation.vy;
    rot->vz = curFrame.rotation.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions.
    result->position.vx = frame0->position.vx + Q12_MULT_PRECISE(frame1->position.vx - frame0->position.vx, alpha);
    result->position.vy = frame0->position.vy + Q12_MULT_PRECISE(frame1->position.vy - frame0->position.vy, alpha);
    result->position.vz = frame0->position.vz + Q12_MULT_PRECISE(frame1->position.vz - frame0->position.vz, alpha);

    // High-precision lerp between rotations.
    result->rotation.vx = Dms_AngleLerp(frame0->rotation.vx, frame1->rotation.vx, alpha);
    result->rotation.vy = Dms_AngleLerp(frame0->rotation.vy, frame1->rotation.vy, alpha);
    result->rotation.vz = Dms_AngleLerp(frame0->rotation.vz, frame1->rotation.vz, alpha);
}

q3_12 Dms_FovScaleGet(q3_12 fovAngle) // 0x8008CDBC
{
    return (96 * Math_Cos(fovAngle / 2)) / Math_Sin(fovAngle / 2);
}

s32 Dms_CameraTargetGet(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CE1C
{
    s32                 keyframePrev;
    s32                 keyframeNext;
    s32                 alpha;
    s_DmsKeyframeCamera curFrame;
    s32                 camProjVal;
    s_DmsEntry*         camEntry;

    camEntry = &dmsHdr->camera;

    Dms_CameraKeyframeInterpGet(&keyframePrev, &keyframeNext, &alpha, time, camEntry, dmsHdr);
    camProjVal = Dms_CameraKeyframeInterpolate(&curFrame, &camEntry->keyframes.camera[keyframePrev], &camEntry->keyframes.camera[keyframeNext], alpha);

    posTarget->vx = Q8_TO_Q12(curFrame.positionTarget.vx + dmsHdr->origin.vx);
    posTarget->vy = Q8_TO_Q12(curFrame.positionTarget.vy + dmsHdr->origin.vy);
    posTarget->vz = Q8_TO_Q12(curFrame.positionTarget.vz + dmsHdr->origin.vz);

    lookAtTarget->vx = Q8_TO_Q12(curFrame.lookAtTarget.vx + dmsHdr->origin.vx);
    lookAtTarget->vy = Q8_TO_Q12(curFrame.lookAtTarget.vy + dmsHdr->origin.vy);
    lookAtTarget->vz = Q8_TO_Q12(curFrame.lookAtTarget.vz + dmsHdr->origin.vz);

    if (arg2 != NULL)
    {
        *arg2 = curFrame.field_C[0];
    }

    // `camProjVal` comes from `curFrame.field_C[1]`, return value is passed to `vcChangeProjectionValue`.
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

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, const s_DmsKeyframeCamera* frame0, const s_DmsKeyframeCamera* frame1, s32 alpha) // 0x8008CFEC
{
    result->positionTarget.vx = frame0->positionTarget.vx + Q12_MULT_PRECISE(frame1->positionTarget.vx - frame0->positionTarget.vx, alpha);
    result->positionTarget.vy = frame0->positionTarget.vy + Q12_MULT_PRECISE(frame1->positionTarget.vy - frame0->positionTarget.vy, alpha);
    result->positionTarget.vz = frame0->positionTarget.vz + Q12_MULT_PRECISE(frame1->positionTarget.vz - frame0->positionTarget.vz, alpha);

    result->lookAtTarget.vx = frame0->lookAtTarget.vx + Q12_MULT_PRECISE(frame1->lookAtTarget.vx - frame0->lookAtTarget.vx, alpha);
    result->lookAtTarget.vy = frame0->lookAtTarget.vy + Q12_MULT_PRECISE(frame1->lookAtTarget.vy - frame0->lookAtTarget.vy, alpha);
    result->lookAtTarget.vz = frame0->lookAtTarget.vz + Q12_MULT_PRECISE(frame1->lookAtTarget.vz - frame0->lookAtTarget.vz, alpha);

    result->field_C[0] = Dms_AngleLerp(frame0->field_C[0], frame1->field_C[0], alpha);
    result->field_C[1] = frame0->field_C[1] + Q12_MULT_PRECISE(frame1->field_C[1] - frame0->field_C[1], alpha);

    return result->field_C[1];
}

void Dms_CameraKeyframeInterpGet(s32* prevRelKeyframeIdx, s32* nextRelKeyframeIdx, q19_12* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr) // 0x8008D1D0
{
    s32 prevAbsKeyframeIdx;
    s32 nextAbsKeyframeIdx;

    prevAbsKeyframeIdx = 0;
    nextAbsKeyframeIdx = 0;

    switch (Dms_IntervalStateGet(time, dmsHdr))
    {
        case DmsIntervalState_Interpolating:
            prevAbsKeyframeIdx = FP_FROM(time, Q12_SHIFT);
            nextAbsKeyframeIdx = prevAbsKeyframeIdx + 1;
            *alpha             = Q12_FRACT(time);
            break;

        case DmsIntervalState_SingleFrame:
            prevAbsKeyframeIdx = FP_FROM(time, Q12_SHIFT);
            nextAbsKeyframeIdx = prevAbsKeyframeIdx;
            *alpha             = Q12(0.0f);
            break;

        case DmsIntervalState_Ending:
            prevAbsKeyframeIdx = FP_FROM(time, Q12_SHIFT) - 1;
            nextAbsKeyframeIdx = prevAbsKeyframeIdx + 1;
            *alpha             = Q12_FRACT(time) + Q12(1.0f);
            break;
    }

    *prevRelKeyframeIdx = Dms_CameraRelKeyframeIdxGet(prevAbsKeyframeIdx, camEntry);
    *nextRelKeyframeIdx = Dms_CameraRelKeyframeIdxGet(nextAbsKeyframeIdx, camEntry);
}

u32 Dms_IntervalStateGet(q19_12 time, s_DmsHeader* dmsHdr)
{
    s32            frameTime;
    s_DmsInterval* curInterval;

    frameTime = FP_FROM(time, Q12_SHIFT);

    for (curInterval = dmsHdr->intervals;
         curInterval < &dmsHdr->intervals[dmsHdr->intervalCount];
         curInterval++)
    {
        if (frameTime != ((curInterval->startKeyframeIdx + curInterval->frameCount) - 1))
        {
            continue;
        }

        if (curInterval->frameCount > 1)
        {
            return DmsIntervalState_Ending;
        }

        return DmsIntervalState_SingleFrame;
    }

    return DmsIntervalState_Interpolating;
}

s32 Dms_CameraRelKeyframeIdxGet(s32 absKeyframeIdx, s_DmsEntry* camEntry) // 0x8008D330
{
    s32       relKeyframeIdx0;
    s32       relKeyframeIdx1;
    SVECTOR3* curSegment;

    relKeyframeIdx0 = absKeyframeIdx;
    for (curSegment = camEntry->svectors; curSegment < &camEntry->svectors[camEntry->svectorCount]; curSegment++)
    {
        if (absKeyframeIdx < curSegment->vx)
        {
            break;
        }

        if (absKeyframeIdx <= curSegment->vy)
        {
            relKeyframeIdx0 = curSegment->vz;
            break;
        }

        relKeyframeIdx0 -= curSegment->vy - curSegment->vx;
    }

    if (relKeyframeIdx0 >= 0)
    {
        if ((camEntry->keyframeCount - 1) >= relKeyframeIdx0)
        {
            relKeyframeIdx1 = relKeyframeIdx0;
        }
        else
        {
            relKeyframeIdx1 = camEntry->keyframeCount - 1;
        }
    }
    else
    {
        relKeyframeIdx1 = 0;
    }

    return relKeyframeIdx1;
}

s32 Dms_AngleLerp(q3_12 angleFrom, q3_12 angleTo, q19_12 alpha) // 0x8008D3D4
{
    return Q12_ANGLE_NORM_S((s32)(Q12_MULT_PRECISE(Q12_ANGLE_NORM_S(angleTo - angleFrom), alpha)) + angleFrom);
}
