#ifndef _MAPS_CHARACTERS_CHARA_KAUFMANN_H
#define _MAPS_CHARACTERS_CHARA_KAUFMANN_H

/** @brief Kaufmann character anim infos. */
extern s_AnimInfo KAUFMANN_ANIM_INFOS[];

/*s_AnimInfo KAUFMANN_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)  }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(5)  }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              { Q12(5)  }, 0,        5 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(5)  }, NO_VALUE, 6 }
};*/

extern s32 sharedData_800D5CF4_3_s00; // Used by `Ai_Kaufmann_Init`.

void Ai_Kaufmann_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Kaufmann_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Kaufmann_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Kaufmann_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Kaufmann_Init(s_SubCharacter* chara);

#endif
