#ifndef _MAPS_CHARACTERS_DAHLIA_H
#define _MAPS_CHARACTERS_DAHLIA_H

extern s32 sharedData_800D16E0_2_s01; // Used by `Ai_Dahlia_Init`.

void Ai_Dahlia_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Dahlia_AnimUpdate(s_SubCharacter* arg0, s_AnmHeader* arg1, GsCOORDINATE2* arg2);
void Ai_Dahlia_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);
void Ai_Dahlia_AnimStateUpdate(s_SubCharacter* dahlia, GsCOORDINATE2* coord);
void Ai_Dahlia_Init(s_SubCharacter* chara);

#endif
