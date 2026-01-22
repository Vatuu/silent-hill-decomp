#ifndef _MAPS_CHARACTERS_FLOATSTINGER_H
#define _MAPS_CHARACTERS_FLOATSTINGER_H

/** @brief Floatstinger character flags. */
typedef enum _FloatstingerFlags
{
    FloatstingerFlag_None = 0,
    FloatstingerFlag_0    = 1 << 0,
    FloatstingerFlag_1    = 1 << 1,
    FloatstingerFlag_2    = 1 << 2,
    FloatstingerFlag_3    = 1 << 3,
    FloatstingerFlag_4    = 1 << 4
} e_FloatstingerFlags;

/** @brief Floatstinger character animation indices. */
typedef enum _FloatstingerAnim
{
    FloatstingerAnim_Still = 0,
    FloatstingerAnim_1     = 1,
    FloatstingerAnim_2     = 2,
    FloatstingerAnim_3     = 3,
    FloatstingerAnim_4     = 4,
    FloatstingerAnim_5     = 5,
    FloatstingerAnim_6     = 6,
    FloatstingerAnim_7     = 7,
    FloatstingerAnim_8     = 8,
    FloatstingerAnim_9     = 9,
    FloatstingerAnim_10    = 10,
    FloatstingerAnim_11    = 11,
    FloatstingerAnim_12    = 12
} e_FloatstingerAnim;

/** @brief Floatstinger character control states. */
typedef enum _FloatstingerControl
{
    FloatstingerControl_None = 0,
    FloatstingerControl_2    = 2,
    FloatstingerControl_3    = 3,
    FloatstingerControl_5    = 5
} e_FloatstingerControl;

/*s_AnimInfo FLOATSTINGER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(FloatstingerAnim_Still, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(FloatstingerAnim_Still, false), false, ANIM_STATUS(FloatstingerAnim_Still, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_1, false), false, ANIM_STATUS(FloatstingerAnim_1, true), { Q12(4) }, NO_VALUE, 1 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_1, true), false, ANIM_STATUS(FloatstingerAnim_9, false), { Q12(32) }, 1, 31 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_2, false), false, ANIM_STATUS(FloatstingerAnim_2, true), { Q12(5) }, NO_VALUE, 32 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_2, true), false, ANIM_STATUS(FloatstingerAnim_9, false), { Q12(20) }, 32, 57 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_3, false), false, ANIM_STATUS(FloatstingerAnim_3, true), { Q12(10) }, NO_VALUE, 58 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_3, true), false, ANIM_STATUS(FloatstingerAnim_11, false), { Q12(20) }, 58, 78 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_4, false), false, ANIM_STATUS(FloatstingerAnim_4, true), { Q12(20) }, NO_VALUE, 116 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_4, true), false, ANIM_STATUS(FloatstingerAnim_7, false), { Q12(0) }, 116, 136 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_5, false), false, ANIM_STATUS(FloatstingerAnim_5, true), { Q12(2) }, NO_VALUE, 85 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_5, true), false, ANIM_STATUS(FloatstingerAnim_3, false), { Q12(4) }, 85, 115 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_6, false), false, ANIM_STATUS(FloatstingerAnim_6, true), { Q12(20) }, NO_VALUE, 116 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_6, true), false, ANIM_STATUS(FloatstingerAnim_11, false), { Q12(0) }, 116, 136 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_7, false), false, ANIM_STATUS(FloatstingerAnim_7, true), { Q12(20) }, NO_VALUE, 137 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_7, true), false, NO_VALUE, { Q12(0) }, 137, 158 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_8, false), false, ANIM_STATUS(FloatstingerAnim_8, true), { Q12(20) }, NO_VALUE, 159 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_8, true), false, NO_VALUE, { Q12(20) }, 159, 190 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_9, false), false, ANIM_STATUS(FloatstingerAnim_9, true), { Q12(5) }, NO_VALUE, 191 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_9, true), false, NO_VALUE, { Q12(0) }, 191, 222 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_10, false), false, ANIM_STATUS(FloatstingerAnim_10, true), { Q12(20) }, NO_VALUE, 223 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_10, true), false, NO_VALUE, { Q12(20) }, 223, 254 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_11, false), false, ANIM_STATUS(FloatstingerAnim_11, true), { Q12(20) }, NO_VALUE, 78 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_11, true), false, NO_VALUE, { Q12(0) }, 78, 79 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_12, false), false, ANIM_STATUS(FloatstingerAnim_12, true), { Q12(4) }, NO_VALUE, 1 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_12, true), false, ANIM_STATUS(FloatstingerAnim_9, false), { Q12(32) }, 1, 31 }
};*/

#endif
