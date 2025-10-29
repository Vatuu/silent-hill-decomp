#ifndef _MAPS_CHARACTERS_CYBIL_H
#define _MAPS_CHARACTERS_CYBIL_H

// Two variables used by `Ai_Cybil_Init`.
extern s32 sharedData_800E2378_0_s01;
extern s32 sharedData_800E237C_0_s01;

void Ai_Cybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Cybil_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* coord);
void Ai_Cybil_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);
void Ai_Cybil_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Cybil_Init(s_SubCharacter* chara);

#endif
