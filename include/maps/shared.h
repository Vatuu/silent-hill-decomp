#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

#include "game.h"

// TODO: Move these tables wherever they belong.

/*s_AnimInfo ALESSA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q19_12(0)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q19_12(30) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q19_12(5)  }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, NO_VALUE,               { Q19_12(15) }, 16,       44  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q19_12(10) }, NO_VALUE, 45  },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3,  true),  { Q19_12(10) }, 45,       131 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q19_12(20) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q19_12(10) }, 132,      170 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q19_12(10) }, NO_VALUE, 171 },
    { Anim_Update0, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q19_12(10) }, 171,      216 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q19_12(1)  }, NO_VALUE, 217 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6,  true),  { Q19_12(10) }, 217,      237 },
    { Anim_Update2, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(1)  }, NO_VALUE, 238 },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(10) }, 238,      288 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q19_12(10) }, NO_VALUE, 289 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q19_12(10) }, 289,      309 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q19_12(5)  }, NO_VALUE, 310 },
    { Anim_Update1, ANIM_STATUS(9,  true),  false, NO_VALUE,               { Q19_12(3)  }, 310,      325 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 326 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE,               { Q19_12(3)  }, 326,      341 }
};*/

/*s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0, false), { Q19_12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE, { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1, true), { Q19_12(10) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1,  true),  false, ANIM_STATUS(1, true), { Q19_12(10) }, 0, 54 },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2, true), { Q19_12(10) }, NO_VALUE, 55 },
    { Anim_Update0, ANIM_STATUS(2,  true),  false, ANIM_STATUS(2, true), { Q19_12(10) }, 55, 117 },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3, true), { Q19_12(10) }, NO_VALUE, 118 },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3, true), { Q19_12(10) }, 118, 152 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4, true), { Q19_12(10) }, NO_VALUE, 153 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4, true), { Q19_12(10) }, 153, 213 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5, true), { Q19_12(10) }, NO_VALUE, 214 },
    { Anim_Update1, ANIM_STATUS(5,  true),  false, NO_VALUE, { Q19_12(10) }, 214, 229 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6, true), { Q19_12(10) }, NO_VALUE, 230 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6, true), { Q19_12(10) }, 230, 260 },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7, true), { Q19_12(10) }, NO_VALUE, 261 },
    { Anim_Update1, ANIM_STATUS(7,  true),  false, NO_VALUE, { Q19_12(10) }, 261, 276 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8, true), { Q19_12(10) }, NO_VALUE, 277 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8, true), { Q19_12(10) }, 277, 295 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9, true), { Q19_12(10) }, NO_VALUE, 296 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9, true), { Q19_12(8) }, 296, 365 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q19_12(10) }, NO_VALUE, 366 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE, { Q19_12(10) }, 366, 382 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q19_12(10) }, NO_VALUE, 295 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true), { Q19_12(10) }, 295, 295 }
};*/

/*s_AnimInfo BLOODY_LISA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q19_12(30) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q19_12(10) }, NO_VALUE, 0   },
    { Anim_Update0, ANIM_STATUS(1, true),  false, ANIM_STATUS(1, true),  { Q19_12(10) }, 0,        100 }
};*/

typedef enum _CatAnim
{
    CatAnim_Still                 = 0,
    CatAnim_Jump                  = 1,
    CatAnim_Run                   = 2,
    CatAnim_TransitionStillToJump = 3,
    CatAnim_TransitionJumpToRun   = 4
} s_CatAnim;

/** Cat character anim infos.
 * @unused Frames [1, 6].
 */
/*s_AnimInfo CAT_ANIM_INFOS[] =
{
    { Anim_Update2, NO_VALUE,                                          false, ANIM_STATUS(CatAnim_Still,                 false), { Q19_12(0)     }, NO_VALUE, 0  },
    { NULL,         ANIM_STATUS(CatAnim_Still,                 false), false, ANIM_STATUS(CatAnim_Still,                 false), { Q19_12(0)     }, 0,        0  },
    { Anim_Update2, ANIM_STATUS(CatAnim_Jump,                  false), false, ANIM_STATUS(CatAnim_Jump,                  true),  { Q19_12(64)    }, NO_VALUE, 7  },
    { Anim_Update0, ANIM_STATUS(CatAnim_Jump,                  true),  false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), { Q19_12(15.8f) }, 7,        22 },
    { Anim_Update2, ANIM_STATUS(CatAnim_Run,                   false), false, ANIM_STATUS(CatAnim_Run,                   true),  { Q19_12(64)    }, NO_VALUE, 23 },
    { Anim_Update1, ANIM_STATUS(CatAnim_Run,                   true),  false, NO_VALUE,                                          { Q19_12(35)    }, 23,       43 },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionStillToJump, false), false, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  { Q19_12(0)     }, NO_VALUE, 7  },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  false, NO_VALUE,                                          { Q19_12(0)     }, 7,        8  },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  { Q19_12(0)     }, NO_VALUE, 22 },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  false, NO_VALUE,                                          { Q19_12(0)     }, 22,       23 }
};*/

/*s_AnimInfo CYBIL_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q19_12(0)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q19_12(30)  }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1,  true),  { Q19_12(5)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q19_12(5)   }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2,  true),  { Q19_12(5)   }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, ANIM_STATUS(2,  true),  { Q19_12(1)   }, 16,       21  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q19_12(100) }, NO_VALUE, 22  },
    { Anim_Update1, ANIM_STATUS(3,  true),  false, NO_VALUE,               { Q19_12(20)  }, 22,       49  },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q19_12(5)   }, NO_VALUE, 50  },
    { Anim_Update1, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q19_12(15)  }, 50,       62  },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q19_12(5)   }, NO_VALUE, 63  },
    { Anim_Update1, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q19_12(15)  }, 63,       75  },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q19_12(5)   }, NO_VALUE, 76  },
    { Anim_Update1, ANIM_STATUS(6,  true),  false, NO_VALUE,               { Q19_12(1)   }, 76,       79  },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7,  true),  { Q19_12(10)  }, NO_VALUE, 80  },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(3)   }, 80,       108 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q19_12(10)  }, NO_VALUE, 109 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q19_12(10)  }, 109,      122 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q19_12(10)  }, NO_VALUE, 123 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9,  true),  { Q19_12(18)  }, 123,      151 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q19_12(10)  }, NO_VALUE, 152 },
    { Anim_Update0, ANIM_STATUS(10, true),  false, ANIM_STATUS(10, true),  { Q19_12(7)   }, 152,      162 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true),  { Q19_12(10)  }, NO_VALUE, 163 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true),  { Q19_12(12)  }, 163,      173 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true),  { Q19_12(10)  }, NO_VALUE, 174 },
    { Anim_Update1, ANIM_STATUS(12, true),  false, NO_VALUE,               { Q19_12(1)   }, 174,      180 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true),  { Q19_12(10)  }, NO_VALUE, 181 },
    { Anim_Update0, ANIM_STATUS(13, true),  false, ANIM_STATUS(13, true),  { Q19_12(6)   }, 181,      228 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true),  { Q19_12(10)  }, NO_VALUE, 229 },
    { Anim_Update0, ANIM_STATUS(14, true),  false, ANIM_STATUS(14, true),  { Q19_12(10)  }, 229,      249 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true),  { Q19_12(10)  }, NO_VALUE, 250 },
    { Anim_Update0, ANIM_STATUS(15, true),  false, ANIM_STATUS(15, true),  { Q19_12(10)  }, 250,      270 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true),  { Q19_12(10)  }, NO_VALUE, 271 },
#if defined(MAP6_S01)
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q19_12(10)  }, 271,      276 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q19_12(10)  }, NO_VALUE, 284 },
    { Anim_Update0, ANIM_STATUS(17, true),  false, ANIM_STATUS(17, true),  { Q19_12(10)  }, 284,      292 },
#elif defined(MAP7_S03)
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q19_12(10) }, 271,       281 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q19_12(10) }, NO_VALUE,  282 },
    { Anim_Update0, ANIM_STATUS(17, true),  false, ANIM_STATUS(17, true),  { Q19_12(10) }, 282,       292 },
#endif
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true),  { Q19_12(10)  }, NO_VALUE, 293 },
    { Anim_Update0, ANIM_STATUS(18, true),  false, ANIM_STATUS(18, true),  { Q19_12(10)  }, 293,      302 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true),  { Q19_12(10)  }, NO_VALUE, 303 },
    { Anim_Update0, ANIM_STATUS(19, true),  false, ANIM_STATUS(19, true),  { Q19_12(10)  }, 303,      368 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true),  { Q19_12(10)  }, NO_VALUE, 369 },
    { Anim_Update0, ANIM_STATUS(20, true),  false, ANIM_STATUS(20, true),  { Q19_12(10)  }, 369,      403 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true),  { Q19_12(5)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(21, true),  false, NO_VALUE,               { Q19_12(20)  }, 0,        21  },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true),  { Q19_12(10)  }, NO_VALUE, 22  },
    { Anim_Update0, ANIM_STATUS(22, true),  false, ANIM_STATUS(22, true),  { Q19_12(10)  }, 22,       104 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true),  { Q19_12(10)  }, NO_VALUE, 105 },
    { Anim_Update0, ANIM_STATUS(23, true),  false, ANIM_STATUS(23, true),  { Q19_12(10)  }, 105,      144 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true),  { Q19_12(10)  }, NO_VALUE, 155 },
    { Anim_Update0, ANIM_STATUS(24, true),  false, ANIM_STATUS(24, true),  { Q19_12(10)  }, 155,      184 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true),  { Q19_12(10)  }, NO_VALUE, 185 },
    { Anim_Update0, ANIM_STATUS(25, true),  false, ANIM_STATUS(25, true),  { Q19_12(10)  }, 185,      278 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true),  { Q19_12(10)  }, NO_VALUE, 279 },
    { Anim_Update0, ANIM_STATUS(26, true),  false, ANIM_STATUS(26, true),  { Q19_12(10)  }, 279,      295 },
    { Anim_Update2, ANIM_STATUS(27, false), false, ANIM_STATUS(27, true),  { Q19_12(10)  }, NO_VALUE, 296 },
    { Anim_Update0, ANIM_STATUS(27, true),  false, ANIM_STATUS(27, true),  { Q19_12(10)  }, 296,      310 },
    { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true),  { Q19_12(10)  }, NO_VALUE, 311 },
    { Anim_Update0, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true),  { Q19_12(10)  }, 311,      324 },
    { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true),  { Q19_12(10)  }, NO_VALUE, 325 },
    { Anim_Update0, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true),  { Q19_12(10)  }, 325,      355 },
    { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true),  { Q19_12(10)  }, NO_VALUE, 167 },
    { Anim_Update0, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true),  { Q19_12(10)  }, 167,      184 },
    { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true),  { Q19_12(5)   }, NO_VALUE, 356 },
    { Anim_Update1, ANIM_STATUS(31, true),  false, NO_VALUE,               { Q19_12(2)   }, 356,      371 }
};*/

/*s_AnimInfo DAHLIA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q19_12(10) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q19_12(5) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q19_12(10) }, NO_VALUE, 16 },
    { Anim_Update1, ANIM_STATUS(2, true), false, NO_VALUE, { Q19_12(15) }, 16, 44 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q19_12(10) }, NO_VALUE, 45 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(3, true), { Q19_12(15) }, 45, 85 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q19_12(3) }, NO_VALUE, 86 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(4, true), { Q19_12(2) }, 86, 109 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q19_12(2) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(5, true), { Q19_12(3.5) }, 110, 166 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q19_12(5) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(6, true), { Q19_12(5) }, 176, 226 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q19_12(15) }, NO_VALUE, 227 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(7, true), { Q19_12(8) }, 236, 247 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q19_12(10) }, NO_VALUE, 248 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q19_12(5) }, 248, 263 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q19_12(10) }, NO_VALUE, 264 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(9, true), { Q19_12(6) }, 264, 304 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q19_12(10) }, NO_VALUE, 305 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(10, true), { Q19_12(10) }, 305, 335 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q19_12(10) }, NO_VALUE, 336 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(11, true), { Q19_12(10) }, 336, 349 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q19_12(10) }, NO_VALUE, 350 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q19_12(10) }, 350, 369 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q19_12(10) }, NO_VALUE, 370 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(13, true), { Q19_12(10) }, 370, 395 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q19_12(10) }, NO_VALUE, 16 },
    { Anim_Update0, ANIM_STATUS(14, true), false, ANIM_STATUS(14, true), { Q19_12(15) }, 16, 80 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q19_12(10) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(15, true), { Q19_12(10) }, 81, 96 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q19_12(10) }, NO_VALUE, 97 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(16, true), { Q19_12(10) }, 97, 103 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q19_12(10) }, NO_VALUE, 104 },
    { Anim_Update0, ANIM_STATUS(17, true), false, ANIM_STATUS(17, true), { Q19_12(10) }, 104, 139 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q19_12(10) }, NO_VALUE, 140 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q19_12(10) }, 140, 155 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q19_12(10) }, NO_VALUE, 156 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(19, true), { Q19_12(10) }, 156, 193 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q19_12(10) }, NO_VALUE, 194 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q19_12(10) }, 194, 209 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q19_12(10) }, NO_VALUE, 210 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(21, true), { Q19_12(10) }, 210, 228 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q19_12(10) }, NO_VALUE, 229 },
    { Anim_Update1, ANIM_STATUS(22, true), false, NO_VALUE, { Q19_12(10) }, 229, 244 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q19_12(10) }, NO_VALUE, 245 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(23, true), { Q19_12(10) }, 245, 259 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q19_12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(24, true), { Q19_12(10) }, 260, 296 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q19_12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(25, true), false, ANIM_STATUS(24, true), { Q19_12(0) }, 260, 296 }
};*/

/*s_AnimInfo GHOST_CHILD_ALESSA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q19_12(5) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q19_12(15) }, 0, 27 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q19_12(5) }, NO_VALUE, 28 },
    { Anim_Update1, ANIM_STATUS(2, true), false, NO_VALUE, { Q19_12(15) }, 28, 49 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q19_12(10) }, NO_VALUE, 50 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(3, true), { Q19_12(10) }, 50, 63 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q19_12(10) }, NO_VALUE, 64 },
    { Anim_Update1, ANIM_STATUS(4, true), false, NO_VALUE, { Q19_12(10) }, 64, 83 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q19_12(10) }, NO_VALUE, 84 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(5, true), { Q19_12(10) }, 84, 109 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q19_12(5) }, NO_VALUE, 110 },
    { Anim_Update1, ANIM_STATUS(6, true), false, NO_VALUE, { Q19_12(5) }, 110, 111 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q19_12(5) }, NO_VALUE, 112 },
    { Anim_Update1, ANIM_STATUS(7, true), false, NO_VALUE, { Q19_12(5) }, 112, 127 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q19_12(5) }, NO_VALUE, 128 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q19_12(5) }, 128, 137 }
};*/

/*s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q19_12(5) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q19_12(15) }, 0, 15 }
};*/

/*s_AnimInfo INCUBATOR_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q19_12(30)   }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q19_12(10)   }, NO_VALUE, 0   },
    { Anim_Update0, ANIM_STATUS(1, true),  false, ANIM_STATUS(1, true),  { Q19_12(6.1f) }, 0,        74  },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q19_12(10)   }, NO_VALUE, 75  },
    { Anim_Update0, ANIM_STATUS(2, true),  false, ANIM_STATUS(2, true),  { Q19_12(10)   }, 75,       115 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true),  { Q19_12(10)   }, NO_VALUE, 116 },
    { Anim_Update1, ANIM_STATUS(3, true),  false, NO_VALUE,              { Q19_12(10)   }, 116,      132 }
};*/

/*s_AnimInfo KAUFMANN_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0)  }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q19_12(5)  }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              { Q19_12(5)  }, 0,        5 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q19_12(5)  }, NO_VALUE, 6 }
};*/

/*s_AnimInfo LISA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q19_12(0)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q19_12(30)   }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1,  true),  { Q19_12(2)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q19_12(5)    }, 0,        9   },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2,  true),  { Q19_12(5)    }, NO_VALUE, 10  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, NO_VALUE,               { Q19_12(20)   }, 10,       37  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q19_12(10)   }, NO_VALUE, 38  },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3,  true),  { Q19_12(1.5f) }, 38,       58  },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q19_12(10)   }, NO_VALUE, 59  },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q19_12(5)    }, 59,       72  },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q19_12(10)   }, NO_VALUE, 73  },
    { Anim_Update0, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q19_12(9)    }, 73,       189 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q19_12(5)    }, NO_VALUE, 190 },
    { Anim_Update1, ANIM_STATUS(6,  true),  false, NO_VALUE,               { Q19_12(5)    }, 190,      205 },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7,  true),  { Q19_12(10)   }, NO_VALUE, 206 },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(10)   }, 206,      227 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q19_12(10)   }, NO_VALUE, 228 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q19_12(10)   }, 228,      248 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q19_12(10)   }, NO_VALUE, 249 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9,  true),  { Q19_12(8)    }, 249,      283 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q19_12(10)   }, NO_VALUE, 284 },
    { Anim_Update0, ANIM_STATUS(10, true),  false, ANIM_STATUS(10, true),  { Q19_12(10)   }, 284,      353 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true),  { Q19_12(10)   }, NO_VALUE, 354 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true),  { Q19_12(3.5f) }, 354,      403 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true),  { Q19_12(10)   }, NO_VALUE, 404 },
    { Anim_Update0, ANIM_STATUS(12, true),  false, ANIM_STATUS(12, true),  { Q19_12(8)    }, 404,      415 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true),  { Q19_12(8)    }, NO_VALUE, 416 },
    { Anim_Update0, ANIM_STATUS(13, true),  false, ANIM_STATUS(13, true),  { Q19_12(7.5f) }, 416,      436 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true),  { Q19_12(8)    }, NO_VALUE, 437 },
    { Anim_Update0, ANIM_STATUS(14, true),  false, ANIM_STATUS(14, true),  { Q19_12(10)   }, 437,      547 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true),  { Q19_12(10)   }, NO_VALUE, 548 },
    { Anim_Update0, ANIM_STATUS(15, true),  false, ANIM_STATUS(15, true),  { Q19_12(10)   }, 548,      572 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true),  { Q19_12(10)   }, NO_VALUE, 573 },
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q19_12(10)   }, 573,      602 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q19_12(2)    }, NO_VALUE, 603 },
    { Anim_Update1, ANIM_STATUS(17, true),  false, NO_VALUE,               { Q19_12(5)    }, 603,      618 }
};*/

/*s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q19_12(30) }, NO_VALUE, 1  },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q19_12(1)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              func_800D8898,  0,        23 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q19_12(5)  }, NO_VALUE, 24 }
};*/

// Unknown.
/*s_AnimInfo D_800D39A0[] =
{
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q19_12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q19_12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q19_12(10) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q19_12(5) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q19_12(10) }, NO_VALUE, 16 },
    { Anim_Update1, ANIM_STATUS(2, true), false, NO_VALUE, { Q19_12(15) }, 16, 44 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q19_12(10) }, NO_VALUE, 45 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(3, true), { Q19_12(15) }, 45, 85 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q19_12(3) }, NO_VALUE, 86 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(4, true), { Q19_12(2) }, 86, 109 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q19_12(2) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(5, true), { Q19_12(3.5) }, 110, 166 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q19_12(5) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(6, true), { Q19_12(5) }, 176, 226 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q19_12(15) }, NO_VALUE, 227 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(7, true), { Q19_12(8) }, 236, 247 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q19_12(10) }, NO_VALUE, 248 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q19_12(5) }, 248, 263 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q19_12(10) }, NO_VALUE, 264 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(9, true), { Q19_12(6) }, 264, 304 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q19_12(10) }, NO_VALUE, 305 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(10, true), { Q19_12(10) }, 305, 335 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q19_12(10) }, NO_VALUE, 336 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(11, true), { Q19_12(10) }, 336, 349 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q19_12(10) }, NO_VALUE, 350 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q19_12(10) }, 350, 369 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q19_12(10) }, NO_VALUE, 370 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(13, true), { Q19_12(10) }, 370, 395 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q19_12(10) }, NO_VALUE, 16 },
    { Anim_Update0, ANIM_STATUS(14, true), false, ANIM_STATUS(14, true), { Q19_12(15) }, 16, 80 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q19_12(10) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(15, true), { Q19_12(10) }, 81, 96 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q19_12(10) }, NO_VALUE, 97 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(16, true), { Q19_12(10) }, 97, 103 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q19_12(10) }, NO_VALUE, 104 },
    { Anim_Update0, ANIM_STATUS(17, true), false, ANIM_STATUS(17, true), { Q19_12(10) }, 104, 139 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q19_12(10) }, NO_VALUE, 140 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q19_12(10) }, 140, 155 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q19_12(10) }, NO_VALUE, 156 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(19, true), { Q19_12(10) }, 156, 193 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q19_12(10) }, NO_VALUE, 194 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q19_12(10) }, 194, 209 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q19_12(10) }, NO_VALUE, 210 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(21, true), { Q19_12(10) }, 210, 228 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q19_12(10) }, NO_VALUE, 229 },
    { Anim_Update1, ANIM_STATUS(22, true), false, NO_VALUE, { Q19_12(10) }, 229, 244 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q19_12(10) }, NO_VALUE, 245 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(23, true), { Q19_12(10) }, 245, 259 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q19_12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(24, true), { Q19_12(10) }, 260, 296 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q19_12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(25, true), false, ANIM_STATUS(24, true), { Q19_12(0) }, 260, 296 }
};*/

#define PARTICLE_COUNT_MAX 300

typedef enum
{
    ParticleState_Spawn  = 0,
    ParticleState_Active = 1,
    ParticleState_Rest   = 2  
} e_ParticleState;

typedef enum
{
    ParticleType_Snow = 0,
    ParticleType_Unk1 = 1,
    ParticleType_Rain = 2
} e_ParticleType;

typedef enum
{
    SnowType_Light      = 0,
    SnowType_Heavy      = 1,
    SnowType_LightWindy = 2,
    SnowType_HeavyWindy = 3
} e_SnowType;

typedef struct
{
    VECTOR3     position0_0;  // Snow: position, Rain: streak start (bottom)
    VECTOR3     position1_C;  // Snow: unused, Rain: streak end (top)
    SVECTOR3    movement_18;  // Snow: random accumulation, Rain: Y accumulation (affects streak length).
    u8          stateStep_1E; /** `e_ParticleState` */
    u8          type_1F;      /** `e_ParticleType` */
} s_Particle;

typedef struct
{
    char unk_0[3420];
    u16  field_D5C;
    s16  field_D5E;
} s_func_800D8714;

typedef struct
{
    VECTOR3 field_0;
    VECTOR3 field_C;
    s16     field_18;
    s16     field_1A;
    s16     field_1C;
    u8      field_1E;
    s8      field_1F;
    char    unk_20[16];
} s_sharedFunc_800CEFD0_1_s02;

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 viewPosition_C; // Q19.12
    SVECTOR svec_18;
    SVECTOR viewRotation_20;
    s32     field_28;
} s_ParticleVectors;

/** Seems to be custom boundaries for snow/rain particle systems.
 * Only used in a small handful of maps, and not all fields are populated.
 *
 * Maybe 8 `VECTOR3`s holding positions in Q19.12? Se4ms to be an inefficient AABB.
 */
typedef struct
{
    VECTOR3 corners_0[8];
} s_func_800CB560;
STATIC_ASSERT_SIZEOF(s_func_800CB560, 96);

/** @brief Stores SFX ID and volume.
 * TODO: There's already an `s_Sfx` struct. Should harmonize the names once both are figured out.
 */
typedef struct _SfxVolume
{
    u16 id_0;
    u8  volume_2;
    u8  __pad_3;
} s_SfxVolume;
/** Likely maps onto another struct somewhere. Starts with an `s_AnimInfo`, has some index properties deeper in it. */
typedef struct
{
    s_AnimInfo  animInfo_0; // This might be a pointer instead - not enough clues available yet to tell.
    s8          unk_10[3288];
    s_SfxVolume sfxVolumes_CE8[11];
    u_Property  properties_D14[4]; // Read as 4 pairs of `u16`s.
} s_func_800D2E04;

typedef struct
{
    s32            flags_0;
    s32            field_4;
    GsCOORDINATE2* coords_8;
    MATRIX*        mat_C; // `MATRIX` array? Needs to be `s32` to match, weird.
} s_sharedData_800E21D0_0_s01;

extern s_SfxVolume g_SfxVolumes[46];

/** Scale. */
extern VECTOR sharedData_800DD870_0_s01;

/** Scale. */
extern VECTOR sharedData_800DD880_0_s01;

/** Could be a padded `VECTOR`, but the ASM for the function `vec = vec` assignments copies only the first 3 fields. */
extern VECTOR3 sharedData_800DE170_0_s01;
extern VECTOR3 sharedData_800DE180_0_s01;
extern VECTOR3 sharedData_800DE190_0_s01;

extern s_func_800700F8_2 sharedData_800E2330_0_s01;

extern u8 sharedData_800DF158_1_s02;

extern VECTOR sharedData_800CAB70_0_s00;

extern s32 sharedData_800E0CA8_0_s00;
extern s32 sharedData_800E0CAC_0_s00;
extern u32 sharedData_800E0CB0_0_s00;
extern u16 sharedData_800E0CB4_0_s00;
extern u16 sharedData_800E0CB6_0_s00;
extern u16 sharedData_800E0CB8_0_s00;
extern s8  sharedData_800E0CBA_0_s00;
extern s32 sharedData_800E32D0_0_s00;

/** `e_EquippedWeaponId` */
extern s8 sharedData_800DD59C_0_s00;

extern s32 sharedData_800DF1F4_0_s00;
extern s16 sharedData_800DF1F8_0_s00;
extern s16 sharedData_800DF1FA_0_s00;

extern s16 sharedData_800E0C6E_0_s00;

/** Related to particle position. */
extern VECTOR3 sharedData_800E323C_0_s00;

/** Previous particle position? */
extern VECTOR3 sharedData_800E324C_0_s00;

/** Previous particle Y angle? */
extern s16 sharedData_800E3260_0_s00;

extern s32 sharedData_800E39D8_0_s00;

// Next 4 set by `Ai_Stalker_Update`.
extern s32 sharedData_800E3A20_0_s00;
extern s32 sharedData_800E3A24_0_s00;
extern s32 sharedData_800E3A28_0_s00;
extern s32 sharedData_800E3A2C_0_s00;

extern s_AnimInfo LARVAL_STALKER_ANIM_INFOS[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo STALKER_ANIM_INFOS[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creaper_Init`.
extern s_AnimInfo CREAPER_ANIM_INFOS[];
extern s8 sharedData_800E57CC_1_s02;

extern s_sharedData_800E21D0_0_s01 sharedData_800E21D0_0_s01;

extern s_func_800D2E04 sharedData_800CAA98_0_s01; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

extern s_AnimInfo sharedData_800EC954_2_s02[]; // Used by `Ai_Romper_Init`.

extern s_AnimInfo sharedData_800EEB14_2_s00[]; // Used by `Ai_Groaner_Init`.

extern s_AnimInfo sharedData_800D91A0_5_s00[]; // Used by `Ai_HangedScratcher_Init`.

// Three variables used by `Ai_Splithead_Init`.
extern s_AnimInfo sharedData_800D5888_1_s05[];
extern s16 sharedData_800D8614_1_s05; // These two s16s could be DVECTOR?
extern s16 sharedData_800D8616_1_s05;

extern u8 sharedData_800DCC14_1_s00[];

extern s32 sharedData_800D6BB8_3_s04; // Used by `Ai_Lisa_Init`.

extern s32 sharedData_800E2C38_7_s01; // Used by `Ai_BloodyLisa_Init`.

// Two variables used by `Ai_Cybil_Init`.
extern s32 sharedData_800E2378_0_s01;
extern s32 sharedData_800E237C_0_s01;

// Two variables used by `Ai_Dahlia_Init`.
extern s32 sharedData_800D16E0_2_s01;
extern s8  sharedData_800D16E4_2_s01;

extern s_AnimInfo ALESSA_ANIM_INFOS[];
extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

extern s32 sharedData_800D5CF4_3_s00; // Used by `Ai_Kaufmann_Init`.

extern s_AnimInfo BLOODSUCKER_ANIM_INFOS[]; // Used by `Ai_Bloodsucker_Init`.

extern u8 sharedData_800DD591_0_s00;
extern u8 sharedData_800DD78B_0_s01;
extern u8 sharedData_800DD796_0_s01;

/** `g_ParticlesAddedCounts`. Tracks how many total particles have been added. */
extern s32 sharedData_800DD78C_0_s01[2];

/** `g_ParticleSpawnCount`. Tracks how many particles have been added per call. */
extern u8 sharedData_800E2156_0_s01;

extern s_AnimInfo KAUFMANN_ANIM_INFOS[]; // Used by `Anim_StartKeyframeIdxGet`, `Ai_Kaufmann` related?

extern s_AnimInfo BLOODY_LISA_ANIM_INFOS[]; // `Ai_BloodyLisa` related?

/** Particle speed X. */
extern s32 sharedData_800DFB64_0_s00;

/** Particles speed Z. */
extern s32 sharedData_800DFB68_0_s00;

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;

extern s32 sharedData_800DD58C_0_s00;
extern s32 sharedData_800E32CC_0_s00;

extern s32 sharedData_800D32A0_0_s02; // `sharedFunc_800CDAA8_0_s02`

extern u16 sharedData_800D21E8_3_s00[];

extern s_func_800CB560 sharedData_800E5768_1_s02;

extern s_Particle g_Particles[PARTICLE_COUNT_MAX];

extern s_ParticleVectors g_ParticleVectors0;

extern s_ParticleVectors g_ParticleVectors1;

extern const char* MAP_MESSAGES[]; // 0x800DF6B8

bool sharedFunc_800CBBBC_0_s00();

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D0A60_0_s00(s32 caseArg);

bool sharedFunc_800D0B18_0_s00(s32 arg0);

void sharedFunc_800D0E04_0_s00();

void sharedFunc_800D209C_0_s00();

void sharedFunc_800D20D8_0_s00();

void sharedFunc_800D20E4_0_s00();

void sharedFunc_800D2244_0_s00(s32 arg0);

void sharedFunc_800D2C7C_0_s00(s32 arg0);

void sharedFunc_800D2D2C_0_s00();

void sharedFunc_800D2D44_0_s00();

s32 sharedFunc_800D2D6C_0_s00();

void sharedFunc_800D2D84_0_s00();

/** Triggers at specific points after the start of a cutscene or dialogue. */
s32 sharedFunc_800D2E50_0_s00();

void sharedFunc_800D2E60_0_s00();

u8 sharedFunc_800D2EA4_0_s00();

void sharedFunc_800D2EB4_0_s00();

void sharedFunc_800D2EF4_0_s00();

void sharedFunc_800D5098_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara);

void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara, s32 moveSpeed);

void sharedFunc_800D6554_0_s00(s_SubCharacter* chara);

void sharedFunc_800D670C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara);

void sharedFunc_800D7E04_0_s00(s_SubCharacter* chara, s32 caseArg);

void sharedFunc_800D88AC_0_s00(s_SubCharacter* playerChara);

void Ai_Stalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Stalker_Init(s_SubCharacter* chara); // Matches across all maps except `map6_s03`.

void sharedFunc_800D3308_0_s00(s_SubCharacter*);

void sharedFunc_800D3B44_0_s00(s_SubCharacter*);

void sharedFunc_800D6970_0_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D70C4_0_s00(s_SubCharacter*);

void sharedFunc_800D7BE8_0_s00(s_SubCharacter*);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* playerChara, s32 arg1);

/** Resets some player properties. */
void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* playerChara);

void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

s16 Anim_StartKeyframeIdxGet(s_SubCharacter* chara);

/** Humanoid init function? */
void sharedFunc_800D923C_0_s00(s_SubCharacter* chara);

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y);

/** Snow effect init. */
void sharedFunc_800CE59C_0_s01(s_Particle* particles);

/** Snow particle update. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime);

/** Snow particle init. */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand);

bool Particle_Update(s_Particle* partHead);

void sharedFunc_800CEFF4_0_s00(s_Particle* part, s32 arg1);

void sharedFunc_800CEB24_0_s00(s_Particle* part);

void sharedFunc_800CFFF8_0_s00(s32 pass, s_func_800CFFF8* part, s16* rand); // TODO: Make this match for `s_Particle`.

void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, s32* deltaTime);

void sharedFunc_800DA8E8_0_s01(s32* timer, s32 inc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateStep);

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

// MAP1_S00 LarvalStalker funcs
void Ai_LarvalStalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800CF168_1_s00(s_SubCharacter*);

void sharedFunc_800D140C_1_s00(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D1524_1_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void Ai_LarvalStalker_Init(s_SubCharacter* chara);

void sharedFunc_800D17BC_1_s00(s_SubCharacter*);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter*);

void sharedFunc_800CEFD0_1_s02(s32 arg0, s_sharedFunc_800CEFD0_1_s02* arg1, u16* arg2, s32* deltaTime); // TODO make this match for s_Particle

/** @brief Sets a map overlay value based on a whether a game event flag is set. */
void sharedFunc_800D0994_3_s00();

void sharedFunc_800D09D4_3_s00();

// MAP3_S03 puppet nurse/doctor funcs
void sharedFunc_800CDA88_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void func_800CDB5C(s_SubCharacter*, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_PuppetDoctor_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800CDF24_3_s03(s_SubCharacter*);

void sharedFunc_800CE3CC_3_s03(s_SubCharacter*);

void sharedFunc_800CE500_3_s03(s_SubCharacter*);

void sharedFunc_800CE5E4_3_s03(s_SubCharacter*, s32);

void sharedFunc_800CEA64_3_s03(s_SubCharacter*);

void sharedFunc_800CEB90_3_s03(s_SubCharacter*, s32);

void sharedFunc_800CEC88_3_s03(s_SubCharacter*);

void sharedFunc_800CF3AC_3_s03(s_SubCharacter*);

void sharedFunc_800CF9F8_3_s03(s_SubCharacter*);

void sharedFunc_800CFD18_3_s03(s_SubCharacter*);

void sharedFunc_800CFDD4_3_s03(s_SubCharacter*);

void sharedFunc_800D0110_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_Control(s_SubCharacter* chara);

void sharedFunc_800D02E4_3_s03(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D03E4_3_s03(s_SubCharacter*);

void sharedFunc_800D06AC_3_s03(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D0828_3_s03(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords);

void Ai_Creaper_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Creaper_Init(s_SubCharacter* chara); // `map5_s00` version has extra code at end of func.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter*);

void sharedFunc_800D8244_1_s02(s_SubCharacter* chara);

void sharedFunc_800D82F0_1_s02(s_SubCharacter*);

void sharedFunc_800D8684_1_s02(s_SubCharacter*);

void sharedFunc_800D8F30_1_s02(s_SubCharacter*);

void sharedFunc_800D9528_1_s02(s_SubCharacter*);

void sharedFunc_800D9774_1_s02(s_SubCharacter*);

void sharedFunc_800D983C_1_s02(s_SubCharacter*);

void sharedFunc_800D9960_1_s02(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D99D0_1_s02(s_SubCharacter*);

void Ai_HangedScratcher_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_HangedScratcher_Init(s_SubCharacter* chara);

void sharedFunc_800CFF74_5_s00(s_SubCharacter*);

void sharedFunc_800D029C_5_s00(s_SubCharacter*);

void sharedFunc_800D26D8_5_s00(s_SubCharacter*);

void sharedFunc_800D2844_5_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D2C18_5_s00(s_SubCharacter*);

void sharedFunc_800D3300_5_s00(s_SubCharacter*);

s32 sharedFunc_800D3508_0_s01(s_SubCharacter* chara, s32* arg1);

s32 sharedFunc_800D3630_0_s01(s_SubCharacter* chara, s32* arg1);

s32 sharedFunc_800D3758_0_s01(s_SubCharacter* chara, s32* outDistance, s32* outAngle, s32 arg3, s32 arg4);

void Ai_Romper_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Romper_Init(s_SubCharacter* chara);

void sharedFunc_800E60FC_2_s02(s_SubCharacter*);

void sharedFunc_800E6420_2_s02(s_SubCharacter*);

void sharedFunc_800E66E8_2_s02(s_SubCharacter*);

void sharedFunc_800E8730_2_s02(s_SubCharacter*);

void sharedFunc_800E8A40_2_s02(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter*);

void Ai_Groaner_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Groaner_Init(s_SubCharacter* chara); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E33DC_2_s00(s_SubCharacter*);

void sharedFunc_800E384C_2_s00(s_SubCharacter*); // `map2_s00` has different version to the other 4 maps which share this, shared sym is needed to share `Ai_Groaner_Update`.

void sharedFunc_800E5AA4_2_s00(s_SubCharacter*);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800E6338_2_s00(s_SubCharacter*);

void sharedFunc_800E71E8_2_s00(s_SubCharacter*);

void Ai_Splithead_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Splithead_Init(s_SubCharacter* chara);

void sharedFunc_800CF990_1_s05(s_SubCharacter*);

void sharedFunc_800CFE94_1_s05(s_SubCharacter*);

void sharedFunc_800D0054_1_s05(s_SubCharacter*);

void sharedFunc_800D267C_1_s05(s_SubCharacter*);

void sharedFunc_800D274C_1_s05(s_SubCharacter*, s32);

void sharedFunc_800D2D74_1_s05(s_SubCharacter*);

void sharedFunc_800D3AFC_1_s05(s_SubCharacter*);

void sharedFunc_800D3B30_1_s05(s_SubCharacter*);

void sharedFunc_800D4070_1_s05(s_SubCharacter*);

extern GsCOORDINATE2* sharedData_800D8610_1_s05;

void Ai_Cybil_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800D8888_0_s01(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D88D0_0_s01(s_SubCharacter* chara, GsCOORDINATE2* coord);

void sharedSymbol_800D8A68_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void Ai_Cybil_Init(s_SubCharacter* chara);

void Ai_AirScreamer_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

bool sharedFunc_800D21E4_0_s01(s32, GsCOORDINATE2* coords);

void sharedFunc_800D2200_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D2274_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2364_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2390_0_s01(s_SubCharacter*);

bool Ai_AirScreamer_Init(s_SubCharacter* chara);

void sharedFunc_800D2B00_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B10_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B28_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B4C_0_s01(s_SubCharacter*);

void sharedFunc_800D2BB0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BE4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* inVec, s32* outDist, s32* outAngle);

s32 sharedFunc_800D3430_0_s01(s_SubCharacter* chara, s32* arg1, s32* arg2);

s32 sharedFunc_800D3814_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D31D0_0_s01(s_SubCharacter* chara, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D3928_0_s01(s_SubCharacter*);

void sharedSymbol_800D3B0C_0_s01(s_SubCharacter*);

bool sharedFunc_800D62D8_0_s01(s_SubCharacter* chara);

/** Returns anim-related index. */
s32 sharedFunc_800D4A80_0_s01(s_SubCharacter*);

s32 sharedFunc_800D5274_0_s01();

void sharedFunc_800D633C_0_s01(s_SubCharacter*);
void sharedFunc_800D63A4_0_s01(s_SubCharacter*);
void sharedFunc_800D6600_0_s01(s_SubCharacter*);

s32 sharedFunc_800D7120_0_s01(s32, s32, s32);
s32 sharedFunc_800D71F0_0_s01(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 sharedFunc_800D7440_0_s01(VECTOR* vec0, VECTOR* vec1, s_SubCharacter* chara);

void sharedFunc_800D7560_0_s01(s_SubCharacter* chara);

void sharedFunc_800D76A0_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D77D0_0_s01(s_SubCharacter*); // Assumed return type.

void sharedFunc_800D7AB0_0_s01(s_SubCharacter*);

void sharedFunc_800D7EBC_0_s01(s_SubCharacter*);

bool sharedFunc_800D81B0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D82B8_0_s01(s_SubCharacter*);

void sharedFunc_800D8714_0_s01(s_SubCharacter*, s32, s32);

void sharedFunc_800D87FC_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D929C_0_s00();
s32 sharedFunc_800D2DAC_0_s00(); // Player anim func. Checks if the active keyframe is at the start or end of the anim's range.
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara); // NPC anim func. Checks if the active keyframe is at the start or end of the anim's range.
bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfx);
void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1);

// `Ai_Lisa` related
void Ai_Lisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D08FC_3_s04(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D0944_3_s04(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedSymbol_800D0ADC_3_s04(s_SubCharacter*, GsCOORDINATE2*); // `Ai_Lisa_Control`
void Ai_Lisa_Init(s_SubCharacter* chara);

// `Ai_BloodyLisa` related
void Ai_BloodyLisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D595C_7_s01(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void sharedFunc_800D59A4_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfx, s32 pitch);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

// `Ai_Kaufmann` related
void Ai_Kaufmann_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedSymbol_800CF470_3_s00(s_SubCharacter*, GsCOORDINATE2*);
void sharedFunc_800CF2D8_3_s00(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800CF290_3_s00(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void Ai_Kaufmann_Init(s_SubCharacter* chara);

// `Ai_GhostChildAlessa` related
void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D4A2C_7_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D4A74_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800D4C0C_7_s01(s_SubCharacter*, GsCOORDINATE2*);
void Ai_GhostChildAlessa_Init(s_SubCharacter* chara);

// `Ai_Alessa` related
void Ai_Alessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800CECFC_3_s02(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void sharedFunc_800CED44_3_s02(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800CEEDC_3_s02(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Alessa_Init(s_SubCharacter* chara);

// `Ai_Dahlia` related
void Ai_Dahlia_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800CD280_2_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800CD2C8_2_s01(s_SubCharacter*, GsCOORDINATE2*);
void sharedSymbol_800CD4A0_2_s01(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Dahlia_Init(s_SubCharacter* chara);

// `Ai_Bloodsucker` related
void Ai_Bloodsucker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void Ai_Bloodsucker_Init(s_SubCharacter*);
void sharedFunc_800D0E20_3_s03(s_SubCharacter*);
void sharedSymbol_800D0E38_3_s03(s_SubCharacter*);
void sharedFunc_800D0E80_3_s03(s_SubCharacter*);
void sharedSymbol_800D0ECC_3_s03(s_SubCharacter*);
void sharedFunc_800D0F28_3_s03(s_SubCharacter*, s32, GsCOORDINATE2*);

static inline void ModelAnim_AnimInfoSet(s_ModelAnim* anim, s_AnimInfo* animInfo)
{
    anim->animInfo_C  = animInfo;
    anim->animInfo_10 = NULL;
}

#endif
