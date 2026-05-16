#ifndef _BODYPROG_FORMATS_IPD_H
#define _BODYPROG_FORMATS_IPD_H

#include "bodyprog/formats/lm.h"
#include "bodyprog/formats/model.h"

#define IPD_HEADER_MAGIC 20

typedef struct _IpdCollisionData_10
{
    /* 0x0    */ s16 field_0;
    /* 0x2    */ s16 field_2; // Q8? Related to ground height?
    /* 0x4    */ s16 field_4;
    /* 0x6+0  */ u16 groundType : 5; /** `e_GroundType` */ // TODO: Might be using `s_IpdCollisionData_18` substruct here? Won't fit though.
    /* 0x6+5  */ u16 field_6_5  : 3;
    /* 0x6+8  */ u16 field_6_8  : 3;
    /* 0x6+11 */ u16 field_6_11 : 4;
    /* 0x6+15 */ u16 field_6_15 : 1;
    /* 0x8    */ s16 field_8;
    /* 0xA    */ s16 field_A;
} s_IpdCollisionData_10;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_10, 12);

typedef struct
{
    /* 0x0+0  */ q3_12 field_0_0  : 14;
    /* 0x0+14 */ u16   field_0_14 : 2;
    /* 0x2+0  */ s16   field_2_0  : 14;
    /* 0x2+14 */ u16   field_2_14 : 2;
    /* 0x4    */ s16   field_4;
    /* 0x6    */ u8    field_6;
    /* 0x7    */ u8    field_7;
    /* 0x8    */ u8    field_8;
    /* 0x9    */ u8    field_9;
} s_IpdCollisionData_14;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_14, 10);

typedef struct
{
    /* 0x0 */ s16 field_0; // Base index into `s_IpdCollisionData::ptr_28`.
    /* 0x2 */ s8  __pad_2[2];
} s_IpdCollisionData_20;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_20, 4);

typedef struct _IpdCollisionData_18
{
    /* 0x0+0  */ u16      groundType : 5; /** `e_GroundType` */
    /* 0x0+5  */ u16      field_0_5  : 3;
    /* 0x0+8  */ u16      field_0_8  : 4;
    /* 0x0+12 */ u16      field_0_12 : 3;
    /* 0x0+15 */ u16      field_0_15 : 1;
    /* 0x2    */ SVECTOR3 vec_2;
    /* 0x8    */ q7_8     field_8;
} s_IpdCollisionData_18;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_18, 10);

typedef struct _IpdCollisionData
{
    /* 0x0    */ s32                    positionX;
    /* 0x4    */ s32                    positionZ;
    /* 0x8+0  */ u32                    field_8_0  : 8;
    /* 0x8+8  */ u32                    field_8_8  : 8;
    /* 0x8+16 */ u32                    field_8_16 : 8;
    /* 0x8+24 */ u32                    field_8_24 : 8;
    /* 0xC    */ SVECTOR3*              ptr_C;
    /* 0x10   */ s_IpdCollisionData_10* ptr_10;
    /* 0x14   */ s_IpdCollisionData_14* ptr_14;
    /* 0x18   */ s_IpdCollisionData_18* ptr_18;
    /* 0x1C   */ q7_8                   field_1C;
    /* 0x1E   */ u8                     field_1E; // Used as multipliers for `field_1C` in `func_8006B004`.
                                                  // Modify this may cause severe slowdowns.
                                                  // Probably some sort of index.
    /* 0x1F   */ u8                     field_1F;
    /* 0x20   */ s_IpdCollisionData_20* ptr_20;
    /* 0x24   */ u16                    field_24; // `field_24/``field_26` defined in ipd2obj but haven't seen used yet, might be size of `ptr_28`/`ptr_2C`.
    /* 0x26   */ u16                    field_26;
    /* 0x28   */ u8*                    ptr_28; // Accessed as array of indices into `field_34` by `func_8006E53C`.
    /* 0x2C   */ void*                  ptr_2C;
    /* 0x30   */ u8                     field_30;
    /* 0x31   */ s8                     __pad_31[3];
    /* 0x34   */ u8                     field_34[256];
} s_IpdCollisionData;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData, 308);

// Node of some kind?
typedef struct _IpdModelBuffer_C
{
    /* 0x0 */ s_ModelHeader* modelHdr;
    /* 0x4 */ MATRIX         mat;
} s_IpdModelBuffer_C;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer_C, 36);

/** @brief IPD model buffer. */
typedef struct _IpdModelBuffer
{
    /* 0x0  */ u8                  field_0; // Count of `field_C` entries.
    /* 0x1  */ u8                  field_1;
    /* 0x2  */ u8                  subcellCount;
    /* 0x3  */ s8                  __pad_3;
    /* 0x4  */ q7_8                minX; // } TODO: Cell range or subcell range?
    /* 0x6  */ q7_8                maxX; // }
    /* 0x8  */ q7_8                minZ; // }
    /* 0xA  */ q7_8                maxZ; // }
    /* 0xC  */ s_IpdModelBuffer_C* field_C;
    /* 0x10 */ SVECTOR*            field_10;         // Pointer to unknown collision data.
    /* 0x14 */ SVECTOR*            subcellPositions; /** XZ positions. TODO: Use different struct. */
} s_IpdModelBuffer;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer, 24);

typedef struct _IpdModelInfo
{
    /* 0x0 */ u8             isGlobalPlm; // `false` if loaded from inside `IPD`, `true` if loaded from `*_GLB.PLM`.
    /* 0x1 */ s8             __pad_1[3];
    /* 0x4 */ u_Filename     modelName;
    /* 0xC */ s_ModelHeader* modelHdr;
} s_IpdModelInfo;
STATIC_ASSERT_SIZEOF(s_IpdModelInfo, 16);

/** @brief IPD model file header. */
typedef struct _IpdHeader
{
    /* 0x0  */ u8                 magic;
    /* 0x1  */ u8                 isLoaded; /** `bool` */
    /* 0x3  */ s8                 cellX;
    /* 0x3  */ s8                 cellZ;
    /* 0x4  */ s_LmHeader*        lmHdr;
    /* 0x8  */ u8                 modelCount;
    /* 0x9  */ u8                 modelBufferCount;
    /* 0xA  */ u8                 modelOrderCount;
    /* 0xB  */ s8                 unk_B[9];
    /* 0x14 */ s_IpdModelInfo*    modelInfo;
    /* 0x18 */ s_IpdModelBuffer*  modelBuffers;
    /* 0x1C */ u8                 textureCount; // Should it be `u32`?
                                                // "`u8` - Relative pointer to textures list"
                                                // "`u32` - Relative pointer to object order"
    /* 0x1D */ s8                 unk_1D[51];   // TODO: Actual texture data array?
    /* 0x50 */ u8*                modelOrderList;
    /* 0x54 */ s_IpdCollisionData collisionData;
} s_IpdHeader;

#endif
