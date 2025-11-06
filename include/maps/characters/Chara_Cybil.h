#ifndef _MAPS_CHARACTERS_CYBIL_H
#define _MAPS_CHARACTERS_CYBIL_H

/** @brief Cybil character anim infos. */
extern s_AnimInfo CYBIL_ANIM_INFOS[];

/*s_AnimInfo CYBIL_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q12(0.0f)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q12(30.0f)  }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1,  true),  { Q12(5.0f)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q12(5.0f)   }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2,  true),  { Q12(5.0f)   }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, ANIM_STATUS(2,  true),  { Q12(1.0f)   }, 16,       21  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q12(100.0f) }, NO_VALUE, 22  },
    { Anim_Update1, ANIM_STATUS(3,  true),  false, NO_VALUE,               { Q12(20.0f)  }, 22,       49  },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q12(5.0f)   }, NO_VALUE, 50  },
    { Anim_Update1, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q12(15)  }, 50,       62  },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q12(5)   }, NO_VALUE, 63  },
    { Anim_Update1, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q12(15.0f)  }, 63,       75  },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q12(5.0f)   }, NO_VALUE, 76  },
    { Anim_Update1, ANIM_STATUS(6,  true),  false, NO_VALUE,               { Q12(1.0f)   }, 76,       79  },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7,  true),  { Q12(10.0f)  }, NO_VALUE, 80  },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q12(3.0f)   }, 80,       108 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q12(10.0f)  }, NO_VALUE, 109 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q12(10.0f)  }, 109,      122 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q12(10.0f)  }, NO_VALUE, 123 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9,  true),  { Q12(18.0f)  }, 123,      151 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q12(10.0f)  }, NO_VALUE, 152 },
    { Anim_Update0, ANIM_STATUS(10, true),  false, ANIM_STATUS(10, true),  { Q12(7.0f)   }, 152,      162 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true),  { Q12(10.0f)  }, NO_VALUE, 163 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true),  { Q12(12.0f)  }, 163,      173 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true),  { Q12(10.0f)  }, NO_VALUE, 174 },
    { Anim_Update1, ANIM_STATUS(12, true),  false, NO_VALUE,               { Q12(1.0f)   }, 174,      180 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true),  { Q12(10.0f)  }, NO_VALUE, 181 },
    { Anim_Update0, ANIM_STATUS(13, true),  false, ANIM_STATUS(13, true),  { Q12(6.0f)   }, 181,      228 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true),  { Q12(10.0f)  }, NO_VALUE, 229 },
    { Anim_Update0, ANIM_STATUS(14, true),  false, ANIM_STATUS(14, true),  { Q12(10.0f)  }, 229,      249 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true),  { Q12(10.0f)  }, NO_VALUE, 250 },
    { Anim_Update0, ANIM_STATUS(15, true),  false, ANIM_STATUS(15, true),  { Q12(10.0f)  }, 250,      270 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true),  { Q12(10.0f)  }, NO_VALUE, 271 },
#if defined(MAP6_S01)
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q12(10.0f)  }, 271,      276 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q12(10.0f)  }, NO_VALUE, 284 },
    { Anim_Update0, ANIM_STATUS(17, true),  false, ANIM_STATUS(17, true),  { Q12(10.0f)  }, 284,      292 },
#elif defined(MAP7_S03)
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q12(10.0f) }, 271,       281 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q12(10.0f) }, NO_VALUE,  282 },
    { Anim_Update0, ANIM_STATUS(17, true),  false, ANIM_STATUS(17, true),  { Q12(10.0f) }, 282,       292 },
#endif
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true),  { Q12(10.0f)  }, NO_VALUE, 293 },
    { Anim_Update0, ANIM_STATUS(18, true),  false, ANIM_STATUS(18, true),  { Q12(10.0f)  }, 293,      302 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true),  { Q12(10.0f)  }, NO_VALUE, 303 },
    { Anim_Update0, ANIM_STATUS(19, true),  false, ANIM_STATUS(19, true),  { Q12(10.0f)  }, 303,      368 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true),  { Q12(10.0f)  }, NO_VALUE, 369 },
    { Anim_Update0, ANIM_STATUS(20, true),  false, ANIM_STATUS(20, true),  { Q12(10.0f)  }, 369,      403 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true),  { Q12(5.0f)   }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(21, true),  false, NO_VALUE,               { Q12(20.0f)  }, 0,        21  },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true),  { Q12(10.0f)  }, NO_VALUE, 22  },
    { Anim_Update0, ANIM_STATUS(22, true),  false, ANIM_STATUS(22, true),  { Q12(10.0f)  }, 22,       104 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true),  { Q12(10.0f)  }, NO_VALUE, 105 },
    { Anim_Update0, ANIM_STATUS(23, true),  false, ANIM_STATUS(23, true),  { Q12(10.0f)  }, 105,      144 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true),  { Q12(10.0f)  }, NO_VALUE, 155 },
    { Anim_Update0, ANIM_STATUS(24, true),  false, ANIM_STATUS(24, true),  { Q12(10.0f)  }, 155,      184 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true),  { Q12(10.0f)  }, NO_VALUE, 185 },
    { Anim_Update0, ANIM_STATUS(25, true),  false, ANIM_STATUS(25, true),  { Q12(10.0f)  }, 185,      278 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true),  { Q12(10.0f)  }, NO_VALUE, 279 },
    { Anim_Update0, ANIM_STATUS(26, true),  false, ANIM_STATUS(26, true),  { Q12(10.0f)  }, 279,      295 },
    { Anim_Update2, ANIM_STATUS(27, false), false, ANIM_STATUS(27, true),  { Q12(10.0f)  }, NO_VALUE, 296 },
    { Anim_Update0, ANIM_STATUS(27, true),  false, ANIM_STATUS(27, true),  { Q12(10.0f)  }, 296,      310 },
    { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true),  { Q12(10.0f)  }, NO_VALUE, 311 },
    { Anim_Update0, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true),  { Q12(10.0f)  }, 311,      324 },
    { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true),  { Q12(10.0f)  }, NO_VALUE, 325 },
    { Anim_Update0, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true),  { Q12(10.0f)  }, 325,      355 },
    { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true),  { Q12(10.0f)  }, NO_VALUE, 167 },
    { Anim_Update0, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true),  { Q12(10.0f)  }, 167,      184 },
    { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true),  { Q12(5.0f)   }, NO_VALUE, 356 },
    { Anim_Update1, ANIM_STATUS(31, true),  false, NO_VALUE,               { Q12(2.0f)   }, 356,      371 }
};*/

// Two variables used by `Ai_Cybil_Init`.
extern s32 sharedData_800E2378_0_s01;
extern s32 sharedData_800E237C_0_s01;

void Ai_Cybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Cybil_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* coords);
void Ai_Cybil_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Cybil_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Cybil_Init(s_SubCharacter* chara);

#endif
