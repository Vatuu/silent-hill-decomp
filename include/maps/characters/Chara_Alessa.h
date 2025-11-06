#ifndef _MAPS_CHARACTERS_ALESSA_H
#define _MAPS_CHARACTERS_ALESSA_H

/** @brief Alessa character animation indices. */
typedef enum _AlessaAnim
{
    AlessaAnim_Still = 0,
    AlessaAnim_1     = 1,
    AlessaAnim_2     = 2,
    AlessaAnim_3     = 3,
    AlessaAnim_4     = 4,
    AlessaAnim_5     = 5,
    AlessaAnim_6     = 6,
    AlessaAnim_7     = 7,
    AlessaAnim_8     = 8,
    AlessaAnim_9     = 9,
    AlessaAnim_10    = 10
} e_AlessaAnim;

/** @brief Alessa character anim infos. */
extern s_AnimInfo ALESSA_ANIM_INFOS[];

/*s_AnimInfo ALESSA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(AlessaAnim_Still,  false), false, ANIM_STATUS(AlessaAnim_Still,  false), { Q12(0.0f)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_Still,  true),  false, NO_VALUE,               { Q12(30.0f) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_1,  false), false, ANIM_STATUS(AlessaAnim_10, true),  { Q12(5.0f)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_1,  true),  false, NO_VALUE,               { Q12(5.0f)  }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_2,  false), false, ANIM_STATUS(AlessaAnim_10, true),  { Q12(5.0f)  }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_2,  true),  false, NO_VALUE,               { Q12(15.0f) }, 16,       44  },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_3,  false), false, ANIM_STATUS(AlessaAnim_3,  true),  { Q12(10.0f) }, NO_VALUE, 45  },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_3,  true),  false, ANIM_STATUS(AlessaAnim_3,  true),  { Q12(10.0f) }, 45,       131 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_4,  false), false, ANIM_STATUS(AlessaAnim_4,  true),  { Q12(20.0f) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_4,  true),  false, ANIM_STATUS(AlessaAnim_4,  true),  { Q12(10.0f) }, 132,      170 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_5,  false), false, ANIM_STATUS(AlessaAnim_5,  true),  { Q12(10.0f) }, NO_VALUE, 171 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_5,  true),  false, ANIM_STATUS(AlessaAnim_5,  true),  { Q12(10.0f) }, 171,      216 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_6,  false), false, ANIM_STATUS(AlessaAnim_6,  true),  { Q12(1.0f)  }, NO_VALUE, 217 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_6,  true),  false, ANIM_STATUS(AlessaAnim_6,  true),  { Q12(10.0f) }, 217,      237 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_7,  true),  false, ANIM_STATUS(AlessaAnim_7,  true),  { Q12(1.0f)  }, NO_VALUE, 238 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_7,  true),  false, ANIM_STATUS(AlessaAnim_7,  true),  { Q12(10.0f) }, 238,      288 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_8,  false), false, ANIM_STATUS(AlessaAnim_8,  true),  { Q12(10.0f) }, NO_VALUE, 289 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_8,  true),  false, ANIM_STATUS(AlessaAnim_8,  true),  { Q12(10.0f) }, 289,      309 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_9,  false), false, ANIM_STATUS(AlessaAnim_9,  true),  { Q12(5.0f)  }, NO_VALUE, 310 },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_9,  true),  false, NO_VALUE,               { Q12(3.0f)  }, 310,      325 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_10, false), false, ANIM_STATUS(AlessaAnim_10, true),  { Q12(5.0f)  }, NO_VALUE, 326 },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_10, true),  false, NO_VALUE,               { Q12(3.0f)  }, 326,      341 }
};*/

extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

void Ai_Alessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_Init(s_SubCharacter* chara);

#endif
