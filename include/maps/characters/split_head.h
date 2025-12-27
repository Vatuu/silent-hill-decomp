#ifndef _MAPS_CHARACTERS_SPLITHEAD_H
#define _MAPS_CHARACTERS_SPLITHEAD_H

/** @brief Split Head character flags. */
typedef enum _SplitHeadFlags
{
    SplitHeadFlag_None = 0,
    SplitHeadFlag_0    = 1 << 0,

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

#endif
