#ifndef _MAPS_CHARACTERS_CAT_H
#define _MAPS_CHARACTERS_CAT_H

/** @brief Cat character animation indices. */
typedef enum _CatAnim
{
    CatAnim_Still                 = 0,
    CatAnim_Jump                  = 1,
    CatAnim_Run                   = 2,
    CatAnim_TransitionStillToJump = 3,
    CatAnim_TransitionJumpToRun   = 4
} e_CatAnim;

/** @brief Cat character anim infos.
 * @unused Frames `[1, 6]`.
 */
/*s_AnimInfo CAT_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE,                                          false, ANIM_STATUS(CatAnim_Still,                 false), { Q12(0)     }, NO_VALUE, 0  },
    { NULL,         ANIM_STATUS(CatAnim_Still,                 false), false, ANIM_STATUS(CatAnim_Still,                 false), { Q12(0)     }, 0,        0  },
    { Anim_Update2, ANIM_STATUS(CatAnim_Jump,                  false), false, ANIM_STATUS(CatAnim_Jump,                  true),  { Q12(64)    }, NO_VALUE, 7  },
    { Anim_Update0, ANIM_STATUS(CatAnim_Jump,                  true),  false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), { Q12(15.8f) }, 7,        22 },
    { Anim_Update2, ANIM_STATUS(CatAnim_Run,                   false), false, ANIM_STATUS(CatAnim_Run,                   true),  { Q12(64)    }, NO_VALUE, 23 },
    { Anim_Update1, ANIM_STATUS(CatAnim_Run,                   true),  false, NO_VALUE,                                          { Q12(35)    }, 23,       43 },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionStillToJump, false), false, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  { Q12(0)     }, NO_VALUE, 7  },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  false, NO_VALUE,                                          { Q12(0)     }, 7,        8  },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  { Q12(0)     }, NO_VALUE, 22 },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  false, NO_VALUE,                                          { Q12(0)     }, 22,       23 }
};*/

#endif
