#ifndef _MAPS_CHARACTERS_CHARA_KAUFMANN_H
#define _MAPS_CHARACTERS_CHARA_KAUFMANN_H

extern s32 sharedData_800D5CF4_3_s00; // Used by `Ai_Kaufmann_Init`.

void Ai_Kaufmann_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Kaufmann_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Kaufmann_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Kaufmann_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Kaufmann_Init(s_SubCharacter* chara);

#endif
