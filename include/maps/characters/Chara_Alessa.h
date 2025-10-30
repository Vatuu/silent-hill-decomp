#ifndef _MAPS_CHARACTERS_ALESSA_H
#define _MAPS_CHARACTERS_ALESSA_H

extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

void Ai_Alessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Alessa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Alessa_Init(s_SubCharacter* chara);

#endif
