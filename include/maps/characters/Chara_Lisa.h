#ifndef _MAPS_CHARACTERS_LISA_H
#define _MAPS_CHARACTERS_LISA_H

/** @brief Lisa character anim infos. */
extern s_AnimInfo LISA_ANIM_INFOS[];

/*s_AnimInfo LISA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q12(0.0f)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q12(30.0f)   }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1,  true),  { Q12(2.0f)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q12(5.0f)    }, 0,        9   },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2,  true),  { Q12(5.0f)    }, NO_VALUE, 10  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, NO_VALUE,               { Q12(20.0f)   }, 10,       37  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q12(10.0f)   }, NO_VALUE, 38  },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3,  true),  { Q12(1.5f)    }, 38,       58  },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q12(10.0f)   }, NO_VALUE, 59  },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q12(5.0f)    }, 59,       72  },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q12(10.0f)   }, NO_VALUE, 73  },
    { Anim_Update0, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q12(9.0f)    }, 73,       189 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q12(5.0f)    }, NO_VALUE, 190 },
    { Anim_Update1, ANIM_STATUS(6,  true),  false, NO_VALUE,               { Q12(5.0f)    }, 190,      205 },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7,  true),  { Q12(10.0f)   }, NO_VALUE, 206 },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q12(10.0f)   }, 206,      227 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q12(10.0f)   }, NO_VALUE, 228 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q12(10.0f)   }, 228,      248 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q12(10.0f)   }, NO_VALUE, 249 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9,  true),  { Q12(8.0f)    }, 249,      283 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q12(10.0f)   }, NO_VALUE, 284 },
    { Anim_Update0, ANIM_STATUS(10, true),  false, ANIM_STATUS(10, true),  { Q12(10.0f)   }, 284,      353 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true),  { Q12(10.0f)   }, NO_VALUE, 354 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true),  { Q12(3.5f)    }, 354,      403 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true),  { Q12(10.0f)   }, NO_VALUE, 404 },
    { Anim_Update0, ANIM_STATUS(12, true),  false, ANIM_STATUS(12, true),  { Q12(8.0f)    }, 404,      415 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true),  { Q12(8.0f)    }, NO_VALUE, 416 },
    { Anim_Update0, ANIM_STATUS(13, true),  false, ANIM_STATUS(13, true),  { Q12(7.5f)    }, 416,      436 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true),  { Q12(8.0f)    }, NO_VALUE, 437 },
    { Anim_Update0, ANIM_STATUS(14, true),  false, ANIM_STATUS(14, true),  { Q12(10.0f)   }, 437,      547 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true),  { Q12(10.0f)   }, NO_VALUE, 548 },
    { Anim_Update0, ANIM_STATUS(15, true),  false, ANIM_STATUS(15, true),  { Q12(10.0f)   }, 548,      572 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true),  { Q12(10.0f)   }, NO_VALUE, 573 },
    { Anim_Update0, ANIM_STATUS(16, true),  false, ANIM_STATUS(16, true),  { Q12(10.0f)   }, 573,      602 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true),  { Q12(2.0f)    }, NO_VALUE, 603 },
    { Anim_Update1, ANIM_STATUS(17, true),  false, NO_VALUE,               { Q12(5.0f)    }, 603,      618 }
};*/

extern s32 sharedData_800D6BB8_3_s04; // Used by `Ai_Lisa_Init`.

void Ai_Lisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Lisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Lisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Lisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Lisa_Init(s_SubCharacter* chara);

#endif
