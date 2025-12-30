#ifndef _MAPS_CHARACTERS_SPLITHEAD_H
#define _MAPS_CHARACTERS_SPLITHEAD_H

/** @brief Split Head character flags. */
typedef enum _SplitHeadFlags
{
    SplitHeadFlag_None = 0,
    SplitHeadFlag_0    = 1 << 0,
    SplitHeadFlag_1    = 1 << 1,

    SplitHeadFlag_3    = 1 << 3,
    SplitHeadFlag_4    = 1 << 4,
    SplitHeadFlag_5    = 1 << 5,
    SplitHeadFlag_6    = 1 << 6,
    SplitHeadFlag_7    = 1 << 7,
    SplitHeadFlag_8    = 1 << 8
} e_SplitHeadFlags;

/** @brief Split Head character animation indices. */
typedef enum _SplitHeadAnim
{
    SplitHeadAnim_Still = 0,
    SplitHeadAnim_1     = 1,
    SplitHeadAnim_2     = 2,
    SplitHeadAnim_3     = 3,
    SplitHeadAnim_4     = 4,
    SplitHeadAnim_5     = 5,
    SplitHeadAnim_6     = 6,
    SplitHeadAnim_7     = 7,
    SplitHeadAnim_8     = 8,
    SplitHeadAnim_9     = 9,
    SplitHeadAnim_10    = 10,
    SplitHeadAnim_11    = 11,
    SplitHeadAnim_12    = 12,
    SplitHeadAnim_13    = 13,
    SplitHeadAnim_14    = 14
} e_SplitHeadAnim;

/** @brief Split Head character control states. */
typedef enum _SplitHeadControl
{
    SplitHeadControl_None = 0,
    SplitHeadControl_1    = 1,
    SplitHeadControl_2    = 2,
    SplitHeadControl_3    = 3,
    SplitHeadControl_4    = 4,
    SplitHeadControl_5    = 5,
    SplitHeadControl_6    = 6,
    SplitHeadControl_7    = 7,
    SplitHeadControl_8    = 8
} e_SplitHeadControl;

typedef struct
{
    s32  field_0; // Distance/Magnitude?
    s32  field_4; // X
    s32  field_8; // Z
    u8   field_C; // 0 / 1 / 2
    u8   field_D; // `bool`
    u8   field_E;
    s8   unk_F;
} s_sharedFunc_800D4594_1_s05;

/*s_AnimInfo SPLIT_HEAD_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(2) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(3.5f) }, 0, 13 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(8) }, NO_VALUE, 14 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(10, false), { Q12(0) }, 14, 40 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(18) }, NO_VALUE, 41 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(10, false), { Q12(12) }, 41, 50 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(12) }, NO_VALUE, 51 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(10, false), { Q12(12) }, 51, 60 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(12) }, NO_VALUE, 61 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(6, false), { Q12(12) }, 61, 63 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(12) }, NO_VALUE, 78 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(10, false), { Q12(12) }, 78, 80 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(4) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(12, false), { Q12(2) }, 94, 114 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(0.5f) }, NO_VALUE, 115 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(13, false), { Q12(1.5f) }, 115, 131 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(4) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(1, false), { Q12(0) }, 132, 161 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(8) }, NO_VALUE, 162 },
    { Anim_Update1, ANIM_STATUS(10, true), false, NO_VALUE, { Q12(6) }, 162, 171 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(4) }, NO_VALUE, 172 },
    { Anim_Update1, ANIM_STATUS(11, true), false, NO_VALUE, { Q12(0) }, 172, 201 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(8) }, NO_VALUE, 114 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(0) }, 114, 115 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(8) }, NO_VALUE, 131 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(0) }, 131, 132 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(2) }, NO_VALUE, 34 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(2) }, 34, 36 }
};*/

void Ai_SplitHead_Update(s_SubCharacter* splitHead, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_SplitHead_Init(s_SubCharacter* splitHead);

void sharedFunc_800CF990_1_s05(s_SubCharacter* splitHead);

void Ai_SplitHead_DamageTake(s_SubCharacter* splitHead);

void Ai_SplitHead_ControlUpdate(s_SubCharacter* splitHead);

void sharedFunc_800D267C_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D274C_1_s05(s_SubCharacter* splitHead, s_AnmHeader* anmHdr);

void sharedFunc_800D2D74_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D3388_1_s05(s_SubCharacter* splitHead, q19_12* offsetX, q19_12* offsetZ);

void sharedFunc_800D17BC_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D2214_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D2444_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D263C_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D3AFC_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D3B30_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D4070_1_s05(s_SubCharacter* splitHead);

/** Probably takes X and Z position values. Specific to Split Head? */
void sharedFunc_800D450C_1_s05(s32 arg0, s32 arg1);

bool sharedFunc_800D4530_1_s05(s_SubCharacter* splitHead);

void sharedFunc_800D4594_1_s05(s_sharedFunc_800D4594_1_s05* arg0, q19_12 posX, q19_12 posZ, VECTOR3* vec0, VECTOR3* vec1);

#endif
