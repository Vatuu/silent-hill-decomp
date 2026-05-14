#ifndef _BODYPROG_CHARAMODEL_H
#define _BODYPROG_CHARAMODEL_H

#include "bodyprog/formats/lm.h"
#include "bodyprog/formats/model.h"
#include "main/fsqueue.h"

/** @brief IPD skeleton model bone. */
typedef struct _Bone
{
    /* 0x0  */ s_ModelInfo modelInfo;
    /* 0x10 */ s8          idx;
               // 3 bytes of padding.
} s_Bone;
STATIC_ASSERT_SIZEOF(s_Bone, 20);

/** @brief IPD skeleton model bone node. */
typedef struct _LinkedBone
{
    /* 0x0  */ s_Bone              bone;
    /* 0x14 */ struct _LinkedBone* next;
} s_LinkedBone;
STATIC_ASSERT_SIZEOF(s_LinkedBone, 24);

typedef struct
{
    /* 0x0 */ u8            boneCount;
    /* 0x1 */ u8            boneIdx;
    /* 0x2 */ u8            field_2;
    /* 0x3 */ s8            field_3;
    /* 0x4 */ s_LinkedBone* bones_4;
    /* 0x8 */ s_LinkedBone* bones_8;
    /* 0xC */ s_LinkedBone  bones_C[56];
} s_Skeleton;
STATIC_ASSERT_SIZEOF(s_Skeleton, 1356);

/** @brief Skeletal character model. */
typedef struct _CharaModel
{
    /* 0x0  */ u8            charaId;  /** `e_CharaId` */
    /* 0x1  */ u8            isLoaded; /** `bool` */
               // 2 bytes of padding.
    /* 0x4  */ s32           queueIdx;
    /* 0x8  */ s_LmHeader*   lmHdr;
    /* 0xC  */ s_FsImageDesc texture;
    /* 0x14 */ s_Skeleton    skeleton;
} s_CharaModel;
STATIC_ASSERT_SIZEOF(s_CharaModel, 1376);

#endif
