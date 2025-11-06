#ifndef _MAPS_CHARACTERS_ALESSA_H
#define _MAPS_CHARACTERS_ALESSA_H

/** @brief Alessa character anim infos. */
extern s_AnimInfo ALESSA_ANIM_INFOS[];

/*s_AnimInfo ALESSA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q12(0)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q12(30) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(10, true),  { Q12(5)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q12(5)  }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(10, true),  { Q12(5)  }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, NO_VALUE,               { Q12(15) }, 16,       44  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q12(10) }, NO_VALUE, 45  },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3,  true),  { Q12(10) }, 45,       131 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q12(20) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q12(10) }, 132,      170 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q12(10) }, NO_VALUE, 171 },
    { Anim_Update0, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q12(10) }, 171,      216 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q12(1)  }, NO_VALUE, 217 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6,  true),  { Q12(10) }, 217,      237 },
    { Anim_Update2, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q12(1)  }, NO_VALUE, 238 },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q12(10) }, 238,      288 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q12(10) }, NO_VALUE, 289 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q12(10) }, 289,      309 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q12(5)  }, NO_VALUE, 310 },
    { Anim_Update1, ANIM_STATUS(9,  true),  false, NO_VALUE,               { Q12(3)  }, 310,      325 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q12(5)  }, NO_VALUE, 326 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE,               { Q12(3)  }, 326,      341 }
};*/

extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

void Ai_Alessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_Init(s_SubCharacter* chara);

#endif
