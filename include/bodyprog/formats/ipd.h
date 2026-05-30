#ifndef _BODYPROG_FORMATS_IPD_H
#define _BODYPROG_FORMATS_IPD_H

#include "bodyprog/formats/lm.h"
#include "bodyprog/formats/model.h"

#define IPD_HEADER_MAGIC 20

/** @brief Ground material types. */
typedef enum _GroundType
{
    GroundType_Default = 0,
    GroundType_1       = 1,
    GroundType_2       = 2,
    GroundType_Grass   = 3,
    GroundType_4       = 4,
    GroundType_5       = 5,
    GroundType_6       = 6,
    GroundType_7       = 7,
    GroundType_8       = 8,
    GroundType_9       = 9,
    GroundType_10      = 10,
    GroundType_11      = 11,
    GroundType_12      = 12
} e_GroundType;

typedef struct _IpdCollisionData_10
{
    /* 0x0    */ s16   field_0;
    /* 0x2    */ s16   field_2; // Q8? Related to ground height?
    /* 0x4    */ s16   field_4;
    /* 0x6+0  */ u16   groundType : 5; /** `e_GroundType` */ // TODO: Might be using `s_IpdCollisionData_18` substruct here? Won't fit though.
    /* 0x6+5  */ u16   field_6_5  : 3; // `bool`?
    /* 0x6+8  */ u16   field_6_8  : 3;
    /* 0x6+11 */ u16   field_6_11 : 4;
    /* 0x6+15 */ u16   field_6_15 : 1;
    /* 0x8    */ q3_12 tiltAngleX;
    /* 0xA    */ q3_12 tiltAngleZ;
} s_IpdCollisionData_10;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_10, 12);

typedef struct
{
    /* 0x0+0  */ q7_8 field_0_0  : 14; // X.
    /* 0x0+14 */ u16  field_0_14 : 2;
    /* 0x2+0  */ q7_8 field_2_0  : 14; // Y.
    /* 0x2+14 */ u16  field_2_14 : 2;
    /* 0x4    */ q7_8 field_4;         // Z.
    /* 0x6    */ u8   vertCollPointIdx0; // Index of `vertCollPoints`.
    /* 0x7    */ u8   vertCollPointIdx1; // Index of `vertCollPoints`.
    /* 0x8    */ u8   field_8;
    /* 0x9    */ u8   field_9;
} s_IpdCollisionData_14;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData_14, 10);

typedef struct _IpdCellRange
{
    /* 0x0 */ s16 field_0; // Base index into `s_IpdCollisionData::ptr_28`.
    /* 0x2 */ s16 field_2;
} s_IpdCellRange;
STATIC_ASSERT_SIZEOF(s_IpdCellRange, 4);

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

/** @note Sparaga's investigation over this file format shows this information is actually embed
 * in the IPD file.
 */
typedef struct _IpdCollisionData
{
    /* 0x0    */ q23_8                  positionX;
    /* 0x4    */ q23_8                  positionZ;
    /* 0x8+0  */ u32                    collPointsCount : 8; // Amount of structs in `vertCollPoints`.
    /* 0x8+8  */ u32                    field_8_8       : 8; // Amount of structs in `ptr_10`.
    /* 0x8+16 */ u32                    field_8_16      : 8; // Amount of structs in `ptr_14`.
    /* 0x8+24 */ u32                    field_8_24      : 8; // Amount of structs in `ptr_18`.
    /* 0xC    */ SVECTOR3*              vertCollPoints;
    /* 0x10   */ s_IpdCollisionData_10* ptr_10;
    /* 0x14   */ s_IpdCollisionData_14* ptr_14;
    /* 0x18   */ s_IpdCollisionData_18* ptr_18;
    /* 0x1C   */ q7_8                   subCellSize;
    /* 0x1E   */ u8                     subCellXCount;
    /* 0x1F   */ u8                     subCellZCount;
    /* 0x20   */ s_IpdCellRange*        cellRanges;
    /* 0x24   */ u16                    field_24; // `field_24/``field_26` defined in ipd2obj but haven't seen used yet, might be size of `ptr_28`/`ptr_2C`.
                                                  // Both `field_24/field_26` are related to a amount of 1 byte things that are being pointed by
                                                  // `ptr_28`.
    /* 0x26   */ u16                    field_26;
    /* 0x28   */ u8*                    ptr_28;         // Accessed as array of indices into `field_34` by `func_8006E53C`.
    /* 0x2C   */ void*                  ptr_2C;         // Pointer to LM part of IPD file?
    /* 0x30   */ u8                     unkLoadedCount; // Directly related to `field_34`.
    /* 0x31   */ s8                     __pad[3];
    /* 0x34   */ u8                     field_34[256]; // Index container.
                                                       // This should be the same size as of the value assigned to
                                                       // `s_IpdCollisionData::field_8_16`, but instead is assigned the
                                                       // the max number that variable handles, which is 256 (same as a `char`).
} s_IpdCollisionData;
STATIC_ASSERT_SIZEOF(s_IpdCollisionData, 308);

// Node of some kind?
typedef struct _IpdModelBuffer_C
{
    /* 0x0 */ s_ModelHeader* modelHdr;
    /* 0x4 */ MATRIX         mat;
} s_IpdModelBuffer_C;
STATIC_ASSERT_SIZEOF(s_IpdModelBuffer_C, 36);

/** @brief IPD file model buffer. */
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

/** @brief IPD file model info. */
typedef struct _IpdModelInfo
{
    /* 0x0 */ u8             isGlobalPlm; // `false` if loaded from inside `IPD`, `true` if loaded from `*_GLB.PLM`.
    /* 0x1 */ s8             __pad_1[3];
    /* 0x4 */ u_Filename     modelName;
    /* 0xC */ s_ModelHeader* modelHdr;
} s_IpdModelInfo;
STATIC_ASSERT_SIZEOF(s_IpdModelInfo, 16);

/** @brief IPD file model file header. */
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
