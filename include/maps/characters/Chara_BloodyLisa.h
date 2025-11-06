#ifndef _MAPS_CHARACTERS_BLOODYLISA_H
#define _MAPS_CHARACTERS_BLOODYLISA_H

/** @brief Bloody Lisa character animation indices. */
typedef enum _BloodyLisaAnim
{
    BloodyLisaAnim_Still = 0,
    BloodyLisaAnim_Walk  = 1
} e_BloodyLisaAnim;

/** @brief Bloody Lisa character anim infos. */
extern s_AnimInfo BLOODY_LISA_ANIM_INFOS[];

/*s_AnimInfo BLOODY_LISA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(BloodyLisaAnim_Still, false), false, ANIM_STATUS(BloodyLisaAnim_Still, false), { Q12(0)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(BloodyLisaAnim_Still, true),  false, NO_VALUE,                                 { Q12(30) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(BloodyLisaAnim_Walk,  false), false, ANIM_STATUS(BloodyLisaAnim_Walk,  true),  { Q12(10) }, NO_VALUE, 0   },
    { Anim_Update0, ANIM_STATUS(BloodyLisaAnim_Walk,  true),  false, ANIM_STATUS(BloodyLisaAnim_Walk,  true),  { Q12(10) }, 0,        100 }
};*/

extern s32 sharedData_800E2C38_7_s01; // Used by `Ai_BloodyLisa_Init`.

void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_BloodyLisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_BloodyLisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_BloodyLisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

#endif
