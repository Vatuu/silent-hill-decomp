#ifndef _MAPS_CHARACTERS_ROMPER_H
#define _MAPS_CHARACTERS_ROMPER_H

/** @brief Romper character flags. */
typedef enum _RomperFlags
{
    RomperFlag_None = 0,
    RomperFlag_0    = 1 << 0,
    RomperFlag_1    = 1 << 1,
    RomperFlag_2    = 1 << 2,
    RomperFlag_3    = 1 << 3,
    RomperFlag_4    = 1 << 4,
    RomperFlag_5    = 1 << 5,
    RomperFlag_6    = 1 << 6,
    RomperFlag_7    = 1 << 7,
    RomperFlag_8    = 1 << 8,
    RomperFlag_9    = 1 << 9,
    RomperFlag_10   = 1 << 10,
    RomperFlag_11   = 1 << 11
} e_RomperFlags;

/** @brief Romper character animation indices. */
typedef enum _RomperAnim
{
    RomperAnim_Still = 0,
    RomperAnim_1     = 1,
    RomperAnim_2     = 2,
    RomperAnim_3     = 3,
    RomperAnim_4     = 4,
    RomperAnim_5     = 5,
    RomperAnim_6     = 6,
    RomperAnim_7     = 7,
    RomperAnim_8     = 8,
    RomperAnim_9     = 9,
    RomperAnim_10    = 10,
    RomperAnim_11    = 11,
    RomperAnim_12    = 12,
    RomperAnim_13    = 13,
    RomperAnim_14    = 14,
    RomperAnim_15    = 15,
    RomperAnim_16    = 16,
    RomperAnim_17    = 17,
    RomperAnim_18    = 18,
    RomperAnim_19    = 19
} e_RomperAnim;

/** @brief Romper character control states. */
typedef enum _RomperControl
{
    RomperControl_None = 0, // Assigned function is `NULL`, different from other charas. Check.
    RomperControl_1    = 1,
    RomperControl_2    = 2,
    RomperControl_3    = 3,
    RomperControl_4    = 4,
    RomperControl_5    = 5,
    RomperControl_6    = 6,
    RomperControl_7    = 7,
    RomperControl_8    = 8,
    RomperControl_9    = 9,
    RomperControl_10   = 10,
    RomperControl_11   = 11
} e_RomperControl;

/*s_AnimInfo ROMPER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(20) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(10) }, 0, 1 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(18) }, NO_VALUE, 2 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(4, false), { Q12(12) }, 2, 7 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(15) }, NO_VALUE, 8 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(5, false), { Q12(15) }, 8, 14 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(20) }, NO_VALUE, 15 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(13, false), { Q12(12) }, 15, 19 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(15) }, NO_VALUE, 20 },
    { Anim_Update1, ANIM_STATUS(5, true), false, NO_VALUE, { Q12(15) }, 20, 33 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(20) }, NO_VALUE, 34 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(16, false), { Q12(5) }, 34, 38 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(10) }, NO_VALUE, 39 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(13, false), { Q12(8) }, 39, 49 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(10) }, NO_VALUE, 50 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(13, false), { Q12(8) }, 50, 60 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(10) }, NO_VALUE, 61 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(21, false), { Q12(10) }, 61, 87 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(20) }, NO_VALUE, 88 },
    { Anim_Update1, ANIM_STATUS(10, true), false, NO_VALUE, { Q12(5) }, 88, 92 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(4) }, NO_VALUE, 93 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(10, false), { Q12(6.5f) }, 93, 99 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(10) }, NO_VALUE, 100 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(6) }, 100, 108 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(20) }, NO_VALUE, 109 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(0) }, 109, 130 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(6) }, NO_VALUE, 131 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(0) }, 131, 146 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(16) }, NO_VALUE, 147 },
    { Anim_Update1, ANIM_STATUS(15, true), false, NO_VALUE, { Q12(4) }, 147, 162 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 38 },
    { Anim_Update1, ANIM_STATUS(16, true), false, NO_VALUE, { Q12(0) }, 38, 39 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(0) }, NO_VALUE, 120 },
    { Anim_Update0, ANIM_STATUS(17, true), false, ANIM_STATUS(7, false), { Q12(0) }, 120, 127 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(0) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(18, true), false, ANIM_STATUS(8, false), { Q12(0) }, 110, 116 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(12) }, NO_VALUE, 109 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(13, false), { Q12(0) }, 109, 130 }
};*/

#endif
