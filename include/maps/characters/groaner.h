#ifndef _MAPS_CHARACTERS_GROANER_H
#define _MAPS_CHARACTERS_GROANER_H

typedef enum _GroanerAnim
{
    GroanerAnim_Still = 0,

    GroanerAnim_Unk17 = 17,
} e_GroanerAnim;

/*s_AnimInfo GROANER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(2) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(18, false), { Q12(3) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(16) }, NO_VALUE, 19 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(9, false), { Q12(24.8f) }, 19, 36 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(16) }, NO_VALUE, 39 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(4, false), { Q12(0) }, 39, 77 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(1) }, NO_VALUE, 78 },
    { Anim_Update1, ANIM_STATUS(4, true), false, NO_VALUE, { Q12(4) }, 78, 93 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(2) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(19, false), { Q12(3.5f) }, 94, 110 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(16) }, NO_VALUE, 114 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 114, 130 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(16) }, NO_VALUE, 134 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(8, false), { Q12(0) }, 134, 164 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(1) }, NO_VALUE, 165 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q12(6) }, 165, 190 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(2) }, NO_VALUE, 191 },
    { Anim_Update1, ANIM_STATUS(9, true), false, NO_VALUE, { Q12(7) }, 191, 206 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(20) }, NO_VALUE, 214 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(16, false), { Q12(0) }, 214, 243 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(2) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(20, false), { Q12(3.5f) }, 244, 264 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(16) }, NO_VALUE, 268 },
    { Anim_Update0, ANIM_STATUS(12, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 268, 284 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(32) }, NO_VALUE, 288 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(14, false), { Q12(0) }, 288, 318 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(1) }, NO_VALUE, 319 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(6) }, 319, 345 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(32) }, NO_VALUE, 346 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(10, false), { Q12(54) }, 346, 362 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 363 },
    { Anim_Update1, ANIM_STATUS(16, true), false, NO_VALUE, { Q12(0) }, 363, 370 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(2) }, NO_VALUE, 371 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(11.5f) }, 371, 396 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(16) }, NO_VALUE, 15 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(0) }, 15, 16 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(16) }, NO_VALUE, 110 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, { Q12(0) }, 110, 111 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(16) }, NO_VALUE, 264 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(0) }, 264, 265 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(16) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(4, false), { Q12(12) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(8, false), { Q12(12) }, 94, 110 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(16) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(14, false), { Q12(12) }, 244, 264 }
};*/

#endif
