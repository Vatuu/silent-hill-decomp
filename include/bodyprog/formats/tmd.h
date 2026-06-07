#ifndef _BODYPROG_FORMATS_TMD_H
#define _BODYPROG_FORMATS_ANM_H

/** @brief TMD model file info. */
typedef struct _TmdFile
{
    /* 0x0 */ s32               id;
    /* 0x4 */ s32               flags;
    /* 0x8 */ s32               modelCount;
    /* 0xC */ struct TMD_STRUCT models[1];
} s_TmdFile;

#endif
