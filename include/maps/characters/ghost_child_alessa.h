#ifndef _MAPS_CHARACTERS_GHOSTCHILDALESSA_H
#define _MAPS_CHARACTERS_GHOSTCHILDALESSA_H

/** @brief Ghost Child Alessa character animation indices. */
typedef enum _GhostChildAlessaAnim
{
    GhostChildAlessaAnim_Still = 0,
    GhostChildAlessaAnim_1     = 1,
    GhostChildAlessaAnim_2     = 2,
    GhostChildAlessaAnim_3     = 3,
    GhostChildAlessaAnim_4     = 4,
    GhostChildAlessaAnim_5     = 5,
    GhostChildAlessaAnim_6     = 6,
    GhostChildAlessaAnim_7     = 7,
    GhostChildAlessaAnim_8     = 8
} e_GhostChildAlessaAnim;

/** @brief Ghost Child Alessa character anim infos. */
extern s_AnimInfo GHOST_CHILD_ALESSA_ANIM_INFOS[];

/*s_AnimInfo GHOST_CHILD_ALESSA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_Still, false), false, ANIM_STATUS(GhostChildAlessaAnim_Still, false), { Q12(0.0f) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_Still, true), false, NO_VALUE, { Q12(30.0f) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_1, false), false, ANIM_STATUS(GhostChildAlessaAnim_1, true), { Q12(5.0f) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_1, true), false, NO_VALUE, { Q12(15.0f) }, 0, 27 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_2, false), false, ANIM_STATUS(2, true), { Q12(5.0f) }, NO_VALUE, 28 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_2, true), false, NO_VALUE, { Q12(15.0f) }, 28, 49 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_3, false), false, ANIM_STATUS(GhostChildAlessaAnim_3, true), { Q12(10.0f) }, NO_VALUE, 50 },
    { Anim_Update0, ANIM_STATUS(GhostChildAlessaAnim_3, true), false, ANIM_STATUS(GhostChildAlessaAnim_3, true), { Q12(10.0f) }, 50, 63 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_4, false), false, ANIM_STATUS(GhostChildAlessaAnim_4, true), { Q12(10.0f) }, NO_VALUE, 64 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_4, true), false, NO_VALUE, { Q12(10.0f) }, 64, 83 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_5, false), false, ANIM_STATUS(GhostChildAlessaAnim_5, true), { Q12(10.0f) }, NO_VALUE, 84 },
    { Anim_Update0, ANIM_STATUS(GhostChildAlessaAnim_5, true), false, ANIM_STATUS(GhostChildAlessaAnim_5, true), { Q12(10.0f) }, 84, 109 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_6, false), false, ANIM_STATUS(GhostChildAlessaAnim_6, true), { Q12(5.0f) }, NO_VALUE, 110 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_6, true), false, NO_VALUE, { Q12(5.0f) }, 110, 111 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_7, false), false, ANIM_STATUS(GhostChildAlessaAnim_7, true), { Q12(5.0f) }, NO_VALUE, 112 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_7, true), false, NO_VALUE, { Q12(5.0f) }, 112, 127 },
    { Anim_Update2, ANIM_STATUS(GhostChildAlessaAnim_8, false), false, ANIM_STATUS(GhostChildAlessaAnim_8, true), { Q12(5.0f) }, NO_VALUE, 128 },
    { Anim_Update1, ANIM_STATUS(GhostChildAlessaAnim_8, true), false, NO_VALUE, { Q12(5.0f) }, 128, 137 }
};*/

void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_GhostChildAlessa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_GhostChildAlessa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_GhostChildAlessa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_GhostChildAlessa_Init(s_SubCharacter* chara);

#endif
