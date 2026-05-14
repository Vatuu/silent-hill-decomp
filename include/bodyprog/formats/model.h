#ifndef _BODYPROG_FORMATS_MODEL_H
#define _BODYPROG_FORMATS_MODEL_H

/** @brief Geometry primitive. */
typedef struct _Primitive
{
    /* 0x0  */ u16 field_0;
    /* 0x2  */ u16 field_2;
    /* 0x4  */ u16 field_4;
               union
               {
                   struct
                   {
                       /* 0x6+0  */ u8 field_6_0     : 8;
                       /* 0x6+8  */ s8 field_6_8     : 7;
                       /* 0x6+17 */ u8 isTransparent : 1; /** `bool` */
                   } bits;
                   u16 flags; // @hack `func_8005AC50` accesses `isTransparent` above with some weird shifts, haven't found how to make it work with bitfield yet.
    /* 0x6  */ } field_6;
    /* 0x8  */ u16 field_8;
    /* 0xA  */ u16 field_A;
    /* 0xC  */ u8  field_C[4];  // } Unknown type. `func_8005AC50` reads these as `s32`, but that breaks other funcs which use this struct. `s32` reads might have just been `memcpy`?
    /* 0x10 */ u8  field_10[4]; // }
} s_Primitive;
STATIC_ASSERT_SIZEOF(s_Primitive, 20);

/** @brief Mesh data header. */
typedef struct _MeshHeader
{
    /* 0x0  */ u8           primitiveCount;
    /* 0x1  */ u8           vertexCount;
    /* 0x2  */ u8           normalCount;
    /* 0x3  */ u8           unkCount_3;
    /* 0x4  */ s_Primitive* primitives;
    /* 0x8  */ DVECTOR*     verticesXy;
    /* 0xC  */ s16*         verticesZ;
    /* 0x10 */ s_Normal*    normals;
    /* 0x14 */ u8*          unkPtr_14;
} s_MeshHeader;
STATIC_ASSERT_SIZEOF(s_MeshHeader, 24);

/** @brief Model data header. */
typedef struct _ModelHeader
{
    /* 0x0   */ u_Filename    name_0;
    /* 0x8   */ u8            meshCount_8;
    /* 0x9   */ u8            vertexOffset_9;
    /* 0xA   */ u8            normalOffset_A;
    /* 0xB+0 */ u8            field_B_0 : 1;
    /* 0xB+1 */ u8            field_B_1 : 3; // Value used in `func_800571D0` switch.
    /* 0xB+4 */ u8            field_B_4 : 2;
    /* 0xB+6 */ u8            unk_B_6   : 2;
    /* 0xC   */ s_MeshHeader* meshHdrs_C;
} s_ModelHeader;
STATIC_ASSERT_SIZEOF(s_ModelHeader, 16);

typedef struct _ModelInfo
{
    /* 0x0 */ s32            field_0; // Bone flags?
    /* 0x4 */ GsCOORDINATE2* coord;
    /* 0x8 */ s_ModelHeader* modelHdr;
    /* 0xC */ s32            modelIdx;
} s_ModelInfo;

#endif
