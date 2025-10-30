#ifndef _MAPS_CHARACTERS_LISA_H
#define _MAPS_CHARACTERS_LISA_H

extern s32 sharedData_800D6BB8_3_s04; // Used by `Ai_Lisa_Init`.

void Ai_Lisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Lisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Lisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Lisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Lisa_Init(s_SubCharacter* chara);

#endif
