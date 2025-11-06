#ifndef _MAPS_CHARACTERS_CHERYL_H
#define _MAPS_CHARACTERS_CHERYL_H

/** @brief Cheryl character anim infos. */
extern s_AnimInfo CHERYL_ANIM_INFOS[];

extern s32 D_800DF1CC;

/** Timer. */
extern q19_12 D_800E3A30;

void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Cheryl_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord);
void Ai_Cheryl_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);
void Ai_Cheryl_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
bool Ai_Cheryl_FootstepTrigger(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 distSqr, s32 pitch);
void Ai_Cheryl_Init(s_SubCharacter* chara);

#endif
