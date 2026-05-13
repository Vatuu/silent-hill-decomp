#ifndef _BODYPROG_FORMATS_MODEL_H
#define _BODYPROG_FORMATS_MODEL_H

typedef struct _Primitive
{
    u16 field_0;
    u16 field_2;
    u16 field_4;
    union
    {
        struct
        {
            u8 field_6_0  : 8;
            s8 field_6_8  : 7;
            u8 isTransparent : 1; /** `bool` */
        } bits;

        u16 flags; // @hack `func_8005AC50` accesses `isTransparent` above with some weird shifts, haven't found how to make it work with bitfield yet.
    } field_6;
    u16 field_8;
    u16 field_A;
    u8  field_C[4];  // } Unknown type. `func_8005AC50` reads these as `s32`, but that breaks other funcs which use this struct. `s32` reads might have just been `memcpy`?
    u8  field_10[4]; // }
} s_Primitive;
STATIC_ASSERT_SIZEOF(s_Primitive, 20);

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

typedef struct _ModelHeader
{
    u_Filename    name_0;
    u8            meshCount_8;
    u8            vertexOffset_9;
    u8            normalOffset_A;
    u8            field_B_0 : 1;
    u8            field_B_1 : 3; // Value used in `func_800571D0` switch.
    u8            field_B_4 : 2;
    u8            unk_B_6   : 2;
    s_MeshHeader* meshHdrs_C;
} s_ModelHeader;
STATIC_ASSERT_SIZEOF(s_ModelHeader, 16);

#endif
