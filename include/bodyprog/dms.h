#ifndef _BODYPROG_DMS_H
#define _BODYPROG_DMS_H

/** @brief DMS cutscene camera keyframe. */
typedef struct _DmsKeyframeCamera
{
    /* 0x0 */ SVECTOR3 positionTarget; /** Q7.8 */
    /* 0x6 */ SVECTOR3 lookAtTarget;   /** Q7.8 */
    /* 0xC */ s16      field_C[2];     // `field_C[1]` gets passed to `vcChangeProjectionValue`.
} s_DmsKeyframeCamera;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCamera, 16);

/** @brief DMS cutscene character transform keyframe. */
typedef struct _DmsKeyframeCharacter
{
    /* 0x0 */ SVECTOR3 position; /** Q7.8 */
    /* 0x6 */ SVECTOR3 rotation; /** Q7.8 */
} s_DmsKeyframeCharacter;
STATIC_ASSERT_SIZEOF(s_DmsKeyframeCharacter, 12);

/** @brief DMS cutscene entry. */
typedef struct _DmsEntry
{
    /* 0x0 */ s16       keyframeCount;
    /* 0x2 */ u8        svectorCount; /** `svectors` array size. */
    /* 0x3 */ u8        field_3;      // Usually 0, but sometimes filled in, possibly junk data left in padding byte.
    /* 0x4 */ char      name[4];      // First 4 `char`s of name. E.g. If code checks for "DAHLIA", file is "DAHL".
    /* 0x8 */ SVECTOR3* svectors;     // Pointer to `SVECTOR3`s. Unknown purpose.
              union
              {
                  s_DmsKeyframeCharacter* character;
                  s_DmsKeyframeCamera*    camera;
    /* 0xC */ } keyframes;
} s_DmsEntry;
STATIC_ASSERT_SIZEOF(s_DmsEntry, 16);

/** @brief DMS cutscene interval */
typedef struct _DmsInterval
{
    /* 0x0 */ s16 startKeyframeIdx;
    /* 0x2 */ s16 frameCount; /** Frame duration at 30 FPS. */
} s_DmsInterval;
STATIC_ASSERT_SIZEOF(s_DmsInterval, 4);

/** @brief DMS cutscene header. */
typedef struct _DmsHeader
{
    /* 0x0  */ u8             isLoaded;       /** `bool` */
    /* 0x1  */ u8             characterCount; /** `characters` array size. */
    /* 0x2  */ u8             intervalCount;  /** `intervals` array size. */
    /* 0x3  */ u8             field_3;        // Usually 0, but sometimes filled in.
    /* 0x4  */ u32            field_4;        // Unknown, correlates with DMS file size.
    /* 0x8  */ s_DmsInterval* intervals;
    /* 0xC  */ VECTOR3        origin;         /** Q23.8 | Origin position. Gets added to character positions. */
    /* 0x18 */ s_DmsEntry*    characters;
    /* 0x1C */ s_DmsEntry     camera;
} s_DmsHeader;
STATIC_ASSERT_SIZEOF(s_DmsHeader, 44);

// `dms.c` ================================================

void DmsHeader_FixOffsets(s_DmsHeader* dmsHdr);

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* dmsHdr);

/** @unused? `volatile` needed for match. */
s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* dmsHdr);

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, q19_12 time, s_DmsHeader* dmsHdr);

void Dms_CharacterGetStartPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, s32 time, s_DmsHeader* dmsHdr);

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* dmsHdr);

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, s_DmsHeader* dmsHdr);

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha);

/** @unused? Returns `96 * cotangent(angle / 2)`. Possibly camera/FOV related. */
q3_12 func_8008CDBC(q3_12 angle);

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr);

/** @unused Returns whether any axis differs by more than 22.5 degrees (1/16 of full rotation). */
bool func_8008CF54(SVECTOR3* rot0, SVECTOR3* rot1);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, const s_DmsKeyframeCamera* frame0, const s_DmsKeyframeCamera* frame1, s32 alpha);

void func_8008D1D0(s32* prevKeyframe, s32* nextKeyframe, q19_12* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr);

u32 Dms_IntervalStateGet(q19_12 time, s_DmsHeader* dmsHdr);

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry);

s32 Math_LerpFixed12(s16 from, s16 to, q19_12 alpha);

#endif
