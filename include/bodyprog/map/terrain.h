#ifndef _BODYPROG_MAP_TERRAIN_H
#define _BODYPROG_MAP_TERRAIN_H

#include "bodyprog/formats/ipd.h"
#include "bodyprog/formats/lm.h"

/** @brief IPD map geometry chunk. */
typedef struct _IpdChunk
{
    /* 0x0  */ s_IpdHeader* ipdHdr;
    /* 0x4  */ s32          queueIdx;
    /* 0x8  */ s16          cellX;
    /* 0xA  */ s16          cellZ;
    /* 0xC  */ q19_12       distance0;
    /* 0x10 */ q19_12       distance1;
    /* 0x14 */ u8           materialCount;
    /* 0x15 */ s8           __pad_15[3];
    /* 0x18 */ s32          outsideCount;
} s_IpdChunk;
STATIC_ASSERT_SIZEOF(s_IpdChunk, 28);

typedef struct _IpdRow
{
    /* 0x0 */ s16 idx[16];
} s_IpdColumn;
STATIC_ASSERT_SIZEOF(s_IpdColumn, 32);

typedef struct _ActiveTextures
{
    /* 0x0 */ s32        count;
    /* 0x4 */ s_Texture* textures[10];
} s_ActiveTextures;

typedef struct _IpdTextures
{
    /* 0x0   */ s_ActiveTextures fullPage;
    /* 0x2C  */ s_ActiveTextures halfPage;
    /* 0x58  */ s_Texture        fullPageTextures[8];
    /* 0x118 */ s_Texture        halfPageTextures[2];
} s_IpdTextures;
STATIC_ASSERT_SIZEOF(s_IpdTextures, 328);

/** @brief Map terrain layout. */
typedef struct _MapTerrain
{
    /* 0x0   */ s_IpdCollisionData collisionData; // Default chunk collision data?
    /* 0x134 */ s32                texFileIdx;
    /* 0x138 */ s_GlobalLm         globalLm;
    /* 0x144 */ char               mapTag[4];
    /* 0x148 */ s32                mapTagSize;
    /* 0x14C */ s32                ipdFileIdx;
    /* 0x150 */ s_IpdHeader*       ipdBuffer;
    /* 0x154 */ s32                ipdBufferSize;
    /* 0x158 */ s32                ipdActiveCount;
    /* 0x15C */ s_IpdChunk         ipdActive[4];
    /* 0x1CC */ s_IpdColumn        ipdGrid[18];
    /* 0x40C */ s8                 unk_40C[32]; // Could be one extra row in table above.
    /* 0x42C */ s_IpdColumn*       ipdGridCenter;
    /* 0x430 */ s_IpdTextures      ipdTextures;
    /* 0x578 */ q19_12             positionX;
    /* 0x57C */ q19_12             positionZ;
    /* 0x580 */ s32                cellX;
    /* 0x584 */ s32                cellZ;
    /* 0x588 */ bool               isExterior;
} s_MapTerrain;
STATIC_ASSERT_SIZEOF(s_MapTerrain, 1420);

#endif
