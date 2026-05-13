#ifndef _BODYPROG_FORMATS_LM_H
#define _BODYPROG_FORMATS_LM_H

#include "bodyprog/formats/model.h"
#include "bodyprog/formats/texture.h"

#define LM_HEADER_MAGIC  '0'
#define LM_VERSION       6

typedef struct _Material
{
    u_Filename name_0;
    s_Texture* texture_8;
    u8         field_C;
    u8         unk_D[1];
    u8         field_E;
    u8         field_F;
    u16        field_10;
    u16        field_12;
    union
    {
        u8  u8[2];
        u16 u16;
    } field_14;
    union
    {
        u8  u8[2];
        u16 u16;
    } field_16;
} s_Material;
STATIC_ASSERT_SIZEOF(s_Material, 24);

/** @brief LM file header. */
typedef struct _LmHeader
{
    /* 0x0  */ u8             magic;    /** See `LM_HEADER_MAGIC`. */
    /* 0x1  */ u8             version;  /** See `LM_VERSION`. */
    /* 0x2  */ u8             isLoaded; /** `bool` */
    /* 0x3  */ u8             materialCount;
    /* 0x4  */ s_Material*    materials;
    /* 0x8  */ u8             modelCount;
               // 3 bytes of padding.
    /* 0xC  */ s_ModelHeader* modelHdrs;
    /* 0x10 */ u8*            modelOrder;
} s_LmHeader;

#endif
