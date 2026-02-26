#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

// ========================================
// DMS FILE HANDLING
// ========================================

void DmsHeader_FixOffsets(s_DmsHeader* dmsHdr) // 0x8008C9A0
{
    s_DmsEntry* curEntry;

    if (dmsHdr->isLoaded_0)
    {
        return;
    }

    dmsHdr->isLoaded_0 = true;

    // Add memory address of DMS header to offsets in `dmsHdr`.
    dmsHdr->intervalPtr_8 = (u8*)dmsHdr->intervalPtr_8 + (u32)dmsHdr;
    dmsHdr->characters_18 = (u8*)dmsHdr->characters_18 + (u32)dmsHdr;

    DmsEntry_FixOffsets(&dmsHdr->camera_1C, dmsHdr);

    for (curEntry = dmsHdr->characters_18;
         curEntry < &dmsHdr->characters_18[dmsHdr->characterCount_1];
         curEntry++)
    {
        DmsEntry_FixOffsets(curEntry, dmsHdr);
    }
}

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* dmsHdr) // 0x8008CA44
{
    entry->keyframes_C.character = (u32)entry->keyframes_C.character + (u32)dmsHdr;
    entry->svectorPtr_8          = (u32)entry->svectorPtr_8 + (u32)dmsHdr;
}

s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* dmsHdr) // 0x8008CA60
{
    return &dmsHdr->intervalPtr_8[idx];
}

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CA74
{
    s32 charaIdx;

    charaIdx = Dms_CharacterFindIdxByName(charaName, dmsHdr);
    if (charaIdx == NO_VALUE)
    {
        // Character not found in DMS.
        Math_Vector3Zero(pos);
        Math_SVectorZero(rot);

        Text_Debug_PositionSet(SCREEN_POSITION_X(15.75f), SCREEN_POSITION_Y(37.5f));

#if VERSION_DATE <= VERSION_DATE_PROTO_981216
        // Code seen in 98-12-16 build.
        Text_Debug_Draw(charName);
        Text_Debug_Draw(" doesn't exist in dms.");
#endif
    }
    else
    {
        Dms_CharacterGetPosRotByIdx(pos, rot, charaIdx, time, dmsHdr);
    }
}

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* dmsHdr) // 0x8008CB10
{
    s32 i;

    for (i = 0; i < dmsHdr->characterCount_1; i++)
    {
        if (!strncmp(name, dmsHdr->characters_18[i].name_4, 4))
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CB90
{
    s_DmsEntry*             charaEntry;
    s32                     keyframePrev;
    s32                     keyframeNext;
    s32                     alpha;
    s_DmsKeyframeCharacter* keyframes;
    s_DmsKeyframeCharacter  curFrame;

    charaEntry = &dmsHdr->characters_18[charaIdx];
    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, charaEntry, dmsHdr);

    keyframes = charaEntry->keyframes_C.character;
    Dms_CharacterKeyframeInterpolate(&curFrame, &keyframes[keyframePrev], &keyframes[keyframeNext], alpha);

    // Set position.
    pos->vx = Q8_TO_Q12(curFrame.position_0.vx + dmsHdr->origin_C.vx);
    pos->vy = Q8_TO_Q12(curFrame.position_0.vy + dmsHdr->origin_C.vy);
    pos->vz = Q8_TO_Q12(curFrame.position_0.vz + dmsHdr->origin_C.vz);

    // Set rotation.
    rot->vx = curFrame.rotation_6.vx;
    rot->vy = curFrame.rotation_6.vy;
    rot->vz = curFrame.rotation_6.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions?
    result->position_0.vx = frame0->position_0.vx + Q12_MULT_PRECISE(frame1->position_0.vx - frame0->position_0.vx, alpha);
    result->position_0.vy = frame0->position_0.vy + Q12_MULT_PRECISE(frame1->position_0.vy - frame0->position_0.vy, alpha);
    result->position_0.vz = frame0->position_0.vz + Q12_MULT_PRECISE(frame1->position_0.vz - frame0->position_0.vz, alpha);

    // Higher-precision lerp between rotations?
    result->rotation_6.vx = Math_LerpFixed12(frame0->rotation_6.vx, frame1->rotation_6.vx, alpha);
    result->rotation_6.vy = Math_LerpFixed12(frame0->rotation_6.vy, frame1->rotation_6.vy, alpha);
    result->rotation_6.vz = Math_LerpFixed12(frame0->rotation_6.vz, frame1->rotation_6.vz, alpha);
}

q3_12 func_8008CDBC(q3_12 angle) // 0x8008CDBC
{
    return (96 * Math_Cos(angle / 2)) / Math_Sin(angle / 2);
}

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CE1C
{
    s32                 keyframePrev;
    s32                 keyframeNext;
    s32                 alpha;
    s_DmsKeyframeCamera curFrame;
    s32                 camProjValue;
    s_DmsEntry*         camEntry;

    camEntry = &dmsHdr->camera_1C;

    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, camEntry, dmsHdr);
    camProjValue = Dms_CameraKeyframeInterpolate(&curFrame, &camEntry->keyframes_C.camera[keyframePrev], &camEntry->keyframes_C.camera[keyframeNext], alpha);

    posTarget->vx = Q8_TO_Q12(curFrame.positionTarget_0.vx + dmsHdr->origin_C.vx);
    posTarget->vy = Q8_TO_Q12(curFrame.positionTarget_0.vy + dmsHdr->origin_C.vy);
    posTarget->vz = Q8_TO_Q12(curFrame.positionTarget_0.vz + dmsHdr->origin_C.vz);

    lookAtTarget->vx = Q8_TO_Q12(curFrame.lookAtTarget_6.vx + dmsHdr->origin_C.vx);
    lookAtTarget->vy = Q8_TO_Q12(curFrame.lookAtTarget_6.vy + dmsHdr->origin_C.vy);
    lookAtTarget->vz = Q8_TO_Q12(curFrame.lookAtTarget_6.vz + dmsHdr->origin_C.vz);

    if (arg2 != NULL)
    {
        *arg2 = curFrame.field_C[0];
    }

    // `camProjValue` comes from `curFrame.field_C[1]`, return value is passed to `vcChangeProjectionValue`.
    return camProjValue;
}

bool func_8008CF54(SVECTOR3* rot0, SVECTOR3* rot1) // 0x8008CF54
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
    result->positionTarget_0.vx = frame0->positionTarget_0.vx + Q12_MULT_PRECISE(frame1->positionTarget_0.vx - frame0->positionTarget_0.vx, alpha);
    result->positionTarget_0.vy = frame0->positionTarget_0.vy + Q12_MULT_PRECISE(frame1->positionTarget_0.vy - frame0->positionTarget_0.vy, alpha);
    result->positionTarget_0.vz = frame0->positionTarget_0.vz + Q12_MULT_PRECISE(frame1->positionTarget_0.vz - frame0->positionTarget_0.vz, alpha);

    result->lookAtTarget_6.vx = frame0->lookAtTarget_6.vx + Q12_MULT_PRECISE(frame1->lookAtTarget_6.vx - frame0->lookAtTarget_6.vx, alpha);
    result->lookAtTarget_6.vy = frame0->lookAtTarget_6.vy + Q12_MULT_PRECISE(frame1->lookAtTarget_6.vy - frame0->lookAtTarget_6.vy, alpha);
    result->lookAtTarget_6.vz = frame0->lookAtTarget_6.vz + Q12_MULT_PRECISE(frame1->lookAtTarget_6.vz - frame0->lookAtTarget_6.vz, alpha);

    result->field_C[0] = Math_LerpFixed12(frame0->field_C[0], frame1->field_C[0], alpha);
    result->field_C[1] = frame0->field_C[1] + Q12_MULT_PRECISE(frame1->field_C[1] - frame0->field_C[1], alpha);

    return result->field_C[1];
}

void func_8008D1D0(s32* prevKeyframe, s32* nextKeyframe, q19_12* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr) // 0x8008D1D0
{
    s32 prevVal;
    s32 nextVal;

    prevVal = 0;
    nextVal = 0;

    switch (Dms_IntervalStateGet(time, dmsHdr))
    {
        case DmsIntervalState_Interpolating:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal + 1;
            *alpha  = Q12_FRACT(time);
            break;

        case DmsIntervalState_SingleFrame:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal;
            *alpha  = Q12(0.0f);
            break;

        case DmsIntervalState_Ending:
            prevVal = FP_FROM(time, Q12_SHIFT) - 1;
            nextVal = prevVal + 1;
            *alpha  = Q12_FRACT(time) + Q12(1.0f);
            break;
    }

    *prevKeyframe = func_8008D330(prevVal, camEntry);
    *nextKeyframe = func_8008D330(nextVal, camEntry);
}

u32 Dms_IntervalStateGet(q19_12 time, s_DmsHeader* dmsHdr)
{
    s32            frameTime;
    s_DmsInterval* curInterval;

    frameTime = FP_FROM(time, Q12_SHIFT);

    for (curInterval = dmsHdr->intervalPtr_8;
         curInterval < &dmsHdr->intervalPtr_8[dmsHdr->intervalCount_2];
         curInterval++)
    {
        if (frameTime != ((curInterval->startKeyframeIdx_0 + curInterval->frameCount_2) - 1))
        {
            continue;
        }

        if (curInterval->frameCount_2 > 1)
        {
            return DmsIntervalState_Ending;
        }

        return DmsIntervalState_SingleFrame;
    }

    return DmsIntervalState_Interpolating;
}

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry) // 0x8008D330
{
    s32       keyframeIdx0;
    s32       keyframeIdx1;
    SVECTOR3* curVec;

    keyframeIdx0 = arg0;
    for (curVec = camEntry->svectorPtr_8; curVec < &camEntry->svectorPtr_8[camEntry->svectorCount_2]; curVec++)
    {

        if (arg0 < curVec->vx)
        {
            break;
        }

        if (arg0 <= curVec->vy)
        {
            keyframeIdx0 = curVec->vz;
            break;
        }

        keyframeIdx0 -= curVec->vy - curVec->vx;
    }

    if (keyframeIdx0 >= 0)
    {
        if ((camEntry->keyframeCount_0 - 1) >= keyframeIdx0)
        {
            keyframeIdx1 = keyframeIdx0;
        }
        else
        {
            keyframeIdx1 = camEntry->keyframeCount_0 - 1;
        }
    }
    else
    {
        keyframeIdx1 = 0;
    }

    return keyframeIdx1;
}

s32 Math_LerpFixed12(s16 from, s16 to, q19_12 alpha) // 0x8008D3D4
{
    return Q12_ANGLE_NORM_S((s32)(Q12_MULT_PRECISE(Q12_ANGLE_NORM_S(to - from), alpha)) + from);
}
